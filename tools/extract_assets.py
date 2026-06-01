#!/usr/bin/env python3
from pathlib import Path
from struct import unpack_from, calcsize, pack
import subprocess
import shutil
from n64img.image import CI8, CI4

ROMFILE = "darkrift.z64"
RAW_ASSETS_PATH = "game_assets/raw"
ASSETS_OFFSET = 0x57AE0

class BinaryReader:
    def __init__(self, data, path = '', offset = 0):
        self.data = data
        self.offset = offset
        self.path = Path(path)
        self.cache = {}
        self.saved_hashes = {}

    def trim_name(self, data):
        bin_name = data["name"]
        name = bin_name.split(b'\x00', 1)[0]
        data["name"] = name.decode()
        data["junk_after_name"] = bin_name[len(name):]
        
    def read(self, fmt, names):
        size = calcsize(fmt)
        values = unpack_from(fmt, self.data, self.offset)
        self.offset += size
        return dict(zip(names, values))
    
    def read_wad(self, name=''):
        header = self.read(">II", ("numFolders", "unknown"))
        print(header)

        self.folders = []
        for i in range(header['numFolders']):
            folder = self.read(">20sIII", ("name", "offset", "fileCount", "folderIndex"))
            self.trim_name(folder)
            print("\t", folder)
            self.folders.append(folder)

        for f in self.folders:
            assert self.offset == f["offset"]

            files = []
            for i in range(f['fileCount']):
                file = self.read(">20sIIII", ("name", "offset", "type", "size", "unpacked_size"))
                self.trim_name(file)
                print("\t\t", file)
                files.append(file)
            f["files"] = files

        for f in self.folders:
            for file in f["files"]:
                self.save_file(file, f)

    def save_file(self, file, folder):
        if False:
            file_content = self.cache[file['offset']]
        else:
            self.offset = file["offset"]
            file_content = self.data[file["offset"]:file["offset"] + file["size"]]
            self.offset += file["size"]

        import hashlib
        h = hashlib.sha256(file_content).hexdigest()
        if h in self.saved_hashes:
            return
        self.saved_hashes[h] = True

        file_name = file["name"]
        if file["size"] != file["unpacked_size"]:
            is_packed = True
            real_file_name = file_name
            file_name = "c_" + file_name
            file_content = pack("<I", file["unpacked_size"]) + file_content
            
        else:
            is_packed = False

        file_path = self.path / folder["name"] / file_name
        if is_packed:
            real_file_path = self.path / folder["name"] / real_file_name

        if file["type"] != 4:            
            file_path.parent.mkdir(parents=True, exist_ok=True)
            file_path.write_bytes(file_content)
            self.cache[file["offset"]] = file_content
            #decode
            if is_packed:
                subprocess.run(["tools/lzhuf", "d", file_path, real_file_path])
                file_path.unlink()
        else:
            # parse inner wad file
            print("opening wad", file_path)
            reader = BinaryReader(file_content, file_path.with_suffix(''))
            reader.saved_hashes = self.saved_hashes  # share dedup tracker
            reader.read_wad()

def trim_name(name):
    return name.split(b'\x00', 1)[0].decode()

def replace_path(p):
    parts = list(p.parts)
    parts[1] = "extracted"
    return Path(*parts)

def save_texture(data, width, height, fmt, palette, outpath):
    if fmt == 8:
        img = CI8(data, width, height)
    elif fmt == 4:
        img = CI4(data, width, height)
    else:
        raise ValueError(f"Unsupported format: {fmt}")
    img.set_palette(palette)
    img.write(outpath)

def process_tex():
    for g in Path(RAW_ASSETS_PATH).glob('**/*.TEX'):
        content = g.read_bytes()
        width, height = unpack_from(">II", content)
        data = content[0x10:0x10 + width * height]
        palette = content[0x10 + width * height:]
        if len(palette) != 512:
            continue
        outpath = replace_path(g).with_suffix(".png")
        outpath.parent.mkdir(parents=True, exist_ok=True)
        save_texture(data, width, height, 8, palette, outpath)

def process_sp2():
    for g in Path(RAW_ASSETS_PATH).glob('**/*.SP2'):
        content = g.read_bytes()
        size, numSprites, tex1, tex2, tex3, tex4, offset = unpack_from(">II16s16s16s16sI", content)
        textures = [tex1, tex2, tex3, tex4]
        textures = [trim_name(t).upper() for t in textures]
        #print(g, size, numSprites, textures, offset)

        #load textures
        tex_data = []
        for t in textures:
            if t:
                tex_content = Path(g.parent / t).read_bytes()
                width, height = unpack_from(">II", tex_content)
                tex_image = tex_content[0x10:0x10 + width * height]
                tex_palette = tex_content[0x10 + width * height:]
                tex_data.append((width, height, tex_image, tex_palette))


        for i in range(numSprites):
            numParts, partsOffset, texIndex, junk = unpack_from(">IIII", content, offset)
            offset += 16
            
            #print(i, partsOffset, texIndex)
            parts = []
            for j in range(numParts):
                t1, s1, s2, t2, x, y = unpack_from(">iiiiii", content, partsOffset)
                partsOffset += 24
                #print("\t", s1, s2, t1, t2, x, y)
                parts.append([s1, s2, t1, t2, x, y])

            minx = min(p[4] for p in parts)
            maxx = max(p[4] + p[1] - p[0] for p in parts)
            miny = min(p[5] for p in parts)
            maxy = max(p[5] + p[3] - p[2] for p in parts)
            #print(minx, miny, maxx, maxy)
            
            #create image
            dest_width = maxx - minx
            dest_height = maxy - miny
            imgdata = bytearray(dest_width * dest_height)            
            w, h, tex_image, tex_palette = tex_data[texIndex]
            for s1, s2, t1, t2, x, y in parts:
                # copy line by line from the texture
                for t in range(t1, t2):
                    dest_x = x - minx
                    dest_y = y - miny + t - t1
                    imgdata[dest_y * dest_width + dest_x : dest_y * dest_width + dest_x + s2 - s1] = \
                        tex_image[t * w + s1 : t * w + s2]
            
            img = CI8(imgdata, dest_width, dest_height)
            img.set_palette(tex_palette)
            outpath = replace_path(g).with_suffix("")/ f"{i}.png"
            outpath.parent.mkdir(parents=True, exist_ok=True)
            img.write(outpath)

def process_sym():
    for g in Path(RAW_ASSETS_PATH).glob('**/*.SYM'):
        content = g.read_bytes()
        off1, off2, off3, off4 = unpack_from(">IIII", content)
        off5 = len(content)
        list1 = []
        list2 = []
        list3 = []
        list4 = []
        for off in range(off1, off2, 16):
            list1.append(content[off:off+16].decode('ascii').rstrip('\x00'))
        for off in range(off2, off3, 32):
            list2.append(content[off:off+32].decode('ascii').rstrip('\x00'))
        for off in range(off3, off4, 32):
            list3.append(content[off:off+32].decode('ascii').rstrip('\x00'))
        for off in range(off4, off5, 32):
            list4.append(content[off:off+32].decode('ascii').rstrip('\x00'))
        outpath = replace_path(g).with_name(f"{g.name}.txt")
        outpath.parent.mkdir(parents=True, exist_ok=True)
        with open(outpath, "w") as outf:
            print("===== LIST 1 =====", file=outf)
            for l in list1:
                print(f"\t{l}", file=outf)
            print("===== LIST 2 =====", file=outf)
            for l in list2:
                print(f"\t{l}", file=outf)
            print("===== LIST 3 =====", file=outf)
            for l in list3:
                print(f"\t{l}", file=outf)
            print("===== LIST 4 =====", file=outf)
            for l in list3:
                print(f"\t{l}", file=outf)

def get_buttons(x):
    if x == 0xFFFF:
        return "ANY"
    if x == 0x5FFF:
        return "NO_LEFT_RIGHT"
    if x == 0xAFFF:
        return "NO_UP_DOWN"
    if x == 0xBFFF:
        return "NO_DOWN"
    names = ['L','A','R','B', 'CUP','CRIGHT','CDOWN','CLEFT','ZTRIG','','','START','UP','RIGHT','DOWN','LEFT']
    return '+'.join(names[i] for i in range(16) if (x & 2**i))


def get_move_flags(x):
    return ' | '.join(f"TF_{1<<i:x}" for i in range(16) if (x & 2**i))

def get_csf_flags(x):
    return ' | '.join(f"CSF_{1<<i:x}" for i in range(32) if (x & 2**i))

def read_sym(f):
    content = f.read_bytes()
    off1, off2, off3, off4 = unpack_from(">IIII", content)
    off5 = len(content)
    list1 = []
    list2 = []
    list3 = []
    list4 = []
    for off in range(off1, off2, 16):
        list1.append(content[off:off+16].decode('ascii').rstrip('\x00'))
    for off in range(off2, off3, 32):
        list2.append(content[off:off+32].decode('ascii').rstrip('\x00'))
    for off in range(off3, off4, 32):
        list3.append(content[off:off+32].decode('ascii').rstrip('\x00'))
    for off in range(off4, off5, 32):
        list4.append(content[off:off+32].decode('ascii').rstrip('\x00'))
    
    return (list1, list2, list3, list4)

# Character name → character ID mapping (from include/enums.h)
# enum CharacterIds { AARON=0, DEMITRON=1, DEMONICA=2, EVE=3, GORE=4,
#                     CHARACTER_5=5 (cut), MORPHIX=6, NIIKI=7,
#                     SCARLET=8, SONORK=9, ZENMURON=10, NUM_CHARACTERS=11 }
CHAR_NAMES_BY_ID = {
    0: "AARO",
    1: "DEMI",
    2: "DEMO",
    3: "EVE",
    4: "GORE",
    5: "[CUT]",
    6: "MORP",
    7: "NIIK",
    8: "SCAR",
    9: "SONO",
    10: "ZENM",
}
FOLDER_TO_CHAR_ID = {name: id for id, name in CHAR_NAMES_BY_ID.items()}
CHAR_RESPONSE_NAMES = {}  # char_id -> list of response SYM names

def build_char_name_map():
    """Pre-load all characters' response SYM names for cross-referencing."""
    for g in sorted(Path(RAW_ASSETS_PATH).glob('**/*.DB')):
        folder_name = g.parent.parent.name
        char_id = FOLDER_TO_CHAR_ID.get(folder_name)
        if char_id is not None:
            sym = read_sym(g.with_suffix(".SYM"))
            CHAR_RESPONSE_NAMES[char_id] = sym[1]

def process_db():
    for g in sorted(Path(RAW_ASSETS_PATH).glob('**/*.DB')):

        symbols = read_sym(g.with_suffix(".SYM"))

        content = g.read_bytes()
        dbdata = {}
        offs = unpack_from(">IIIIIIIIIIIIIIIII", content)
        
        l = []
        for off in range(offs[0], offs[1], 16):
            e = unpack_from(">hhhhhhhh", content, off)
            l.append({"unk00":e[0], "unk02":e[1], "unk04":e[2], "unk06":e[3],
                      "unk08":e[4], "unk0A":e[5], "unk0C":e[6], "unk0E":e[7]})
        dbdata["player_28"] = l

        l = []
        i = 0
        for off in range(offs[1] + 4, offs[2], 28):
            head = unpack_from(">hHHHhhH", content, off)
            forChar = list(unpack_from("11B", content, off + 14))
            selfResp = unpack_from("B", content, off + 25)[0]
            # annotate response indices with character names (skip cut char 5)
            from collections import defaultdict
            by_name = defaultdict(list)
            for idx, val in enumerate(forChar):
                if idx == 5:
                    continue
                ch = CHAR_NAMES_BY_ID.get(idx, f"CHAR{idx}")
                names = CHAR_RESPONSE_NAMES.get(idx, [])
                if val == 0xFF:
                    by_name["0xFF (none)"].append(ch)
                elif val < len(names):
                    by_name[names[val]].append((ch, val))
                else:
                    by_name["(???)"].append((ch, val))
            forCharAnnotated = []
            if len(by_name) == 1:
                (name, entries) = next(iter(by_name.items()))
                if name == "0xFF (none)":
                    forCharAnnotated.append("ALL:0xFF (none)")
                else:
                    forCharAnnotated.append(f"ALL:`{name}`")
            else:
                for idx, val in enumerate(forChar):
                    if idx == 5:
                        continue
                    ch = CHAR_NAMES_BY_ID.get(idx, f"CHAR{idx}")
                    names = CHAR_RESPONSE_NAMES.get(idx, [])
                    if val == 0xFF:
                        forCharAnnotated.append(f"{ch}:0xFF (none)")
                    elif val < len(names):
                        forCharAnnotated.append(f"{ch}:{val}:`{names[val]}`")
                    else:
                        forCharAnnotated.append(f"{ch}:{val}:(???)")
            l.append({"name":symbols[0][i], "index":i, "index_in_field28":head[0], "buttons":get_buttons(head[1]), "flags":get_move_flags(head[2]), "unk06":head[3],
                      "behavior":f"BHV_{head[4]}", "actionState": f"CS_{head[5]}", "button_mask":get_buttons(head[6]),
                      "aiResponseForChar":forCharAnnotated, "aiResponseSelf":selfResp})
            i += 1
        dbdata["transitionTable"] = l

        # transition table
        transGroups = {0:'ROOT'}
        l = []
        i = 0
        newGroup = True
        groupName = ''
        for off in range(offs[2], offs[3], 4):
            e = unpack_from(">hh", content, off)
            if e[0] == 0:
                break

            if newGroup:
                groupName = transGroups[i]
                l.append({groupName: []})
                newGroup = False

            if e[0] == -1:
                newGroup = True
            else:
                if e[1] != -1:
                    transGroups[e[1]] = dbdata["transitionTable"][e[0]]["name"]
                l[-1][groupName].append({ "index": i, "transitionId":e[0], "transitionName": dbdata["transitionTable"][e[0]]["name"], "nextLogicState": e[1] })
            i += 2
        dbdata["logicStates"] = l

        l = []
        for off in range(offs[3], offs[4], 4):
            e = unpack_from(">hH", content, off)
            l.append({"index_in_field1C":e[0], "count":e[1]})
        dbdata["player_30"] = l

        l = []
        for off in range(offs[4], offs[5], 8):
            e = unpack_from(">hhhh", content, off)
            l.append({"unk_00":e[0], "unk_02":e[1], "unk_04":e[2], "unk_06":e[3]})
        dbdata["player_1C"] = l

        l = []
        for off in range(offs[5] + 4, offs[6], 56):
            e = unpack_from(">26hI", content, off)
            l.append({"index": f"CS_{(off - offs[5] - 4) // 56}", "minFrame":e[0], "maxFrame":e[1], "unk_04":e[2], "unk_06":e[3],
                      "animationId":e[4], "unk_0A":e[5], "unk_0C":e[6], "unk_0E":e[7],
                      "unk_10":e[8], "unk_12":e[9], "unk_14":e[10], "unk_16":e[11],
                      "unk_18":e[12], "unk_1A":e[13], "unk_1C":e[14], "unk_1E":e[15],
                      "damage":e[16], "unk_22":e[17], "unk_24":e[18], "unk_26":e[19],
                      "unk_28":e[20], "unk_2A":e[21], "unk_2C":e[22], "unk_2E":e[23],
                      "unk_30":e[24], "unk_32":e[25], "flags":get_csf_flags(e[26])})
        dbdata["actionStates"] = l

        l = []
        for off in range(offs[6] + 4, offs[7], 8):
            e = unpack_from(">BBBBBBBB", content, off)
            l.append({"sound1":e[0], "frame1":e[1], "sound2":e[2], "frame2":e[3],
                      "sound3":e[4], "frame3":e[5], "sound4":e[6], "frame4":e[7]})
        dbdata["sounds"] = l

        l = []
        e = unpack_from(">I", content, offs[7])
        l.append({"unk_num": e[0]})
        dbdata["player_6C"] = l

        l = []
        for off in range(offs[8], offs[9], 2):
            e = unpack_from(">h", content, off)
            l.append({"moveId": f"MOVE_ID_{(off - offs[8]) // 2}", "logicState":e[0]})
        dbdata["player_38"] = l

        l = []
        for off in range(offs[9], offs[10], 1):
            e = unpack_from(">B", content, off)
            l.append({"frame":e[0]})
        dbdata["player_44"] = l

        # ProjectileDef (76 bytes each)
        l = []
        for off in range(offs[10], offs[11], 76):
            e = unpack_from(">hhiiiiiihhhhiihhhhhhhhihh8s", content, off)
            l.append({
                "lifetime":e[0], "boneId":e[1],
                "originX":e[2], "originY":e[3], "originZ":e[4],
                "velocityX":e[5], "velocityY":e[6], "velocityZ":e[7],
                "spriteFrame":e[8], "unk_1E":e[9], "spriteIndex":e[10], "modelIndex":e[11],
                "unk_24":e[12], "unk_28":e[13],
                "flags":e[14], "unk_2E":e[15], "unk_30":e[16], "unk_32":e[17],
                "unk_34":e[18], "unk_36":e[19], "unk_38":e[20], "unk_3A":e[21],
                "unk_3C":e[22], "unk_40":e[23], "unk_42":e[24],
                "lightColors":e[25].hex()
            })
        dbdata["projectileDefs"] = l

        # ProjectileBarrage (24 bytes each = 8 ProjectileShot)
        l = []
        for off in range(offs[11], offs[12], 24):
            shots = []
            for si in range(8):
                s = unpack_from(">BBB", content, off + si * 3)
                if s[0] == 0xFF:
                    break
                shots.append({"projectileId":s[0], "frameIndex":s[1], "unk_02":s[2]})
            l.append({"shots": shots})
        dbdata["projectileBarrages"] = l

        # aiActionTable → grouped rows by aiActionIndexMap
        l_rows = []
        idxmap_vals = []
        for off in range(offs[13], offs[14], 2):
            idxmap_vals.append(unpack_from(">h", content, off)[0])
        for i, offset in enumerate(idxmap_vals):
            off_bytes = offs[12] + offset * 2
            if off_bytes + 6 > offs[13]:
                l_rows.append({
                    "index": i,
                    "name": symbols[3][i] if i < len(symbols[3]) else f"ACT_{i}",
                    "callbackIdx": 0, "actionParam": 0, "conditionFlags": 0, "moves": []
                })
                continue
            cb = unpack_from(">h", content, off_bytes)[0]
            param = unpack_from(">h", content, off_bytes + 2)[0]
            cond = unpack_from(">H", content, off_bytes + 4)[0]
            moves = []
            pos = off_bytes + 6
            while pos < offs[13]:
                val = unpack_from(">h", content, pos)[0]
                if val == -1:
                    break
                moves.append(val)
                pos += 2
            l_rows.append({
                "index": i,
                "name": symbols[3][i] if i < len(symbols[3]) else f"ACT_{i}",
                "callbackIdx": cb,
                "actionParam": param,
                "conditionFlags": cond,
                "moves": moves
            })
        dbdata["aiActionRows"] = l_rows

        # AiCandidate section: s32 count + AiAction[count] (12B each) + s16 sequenceTable
        l_cands = []
        l_seq_groups = []
        if offs[14] < offs[15]:
            cand_count = unpack_from(">I", content, offs[14])[0]
            cand_off = offs[14] + 4
            for i in range(cand_count):
                e = unpack_from(">hhhhHH", content, cand_off + i * 12)
                l_cands.append({
                    "name": symbols[2][i] if i < len(symbols[2]) else f"CAND_{i}",
                    "actionIndex":e[0], "difficultyMask":e[1], "distanceMax":e[2],
                    "distanceMin":e[3], "conditionFlags":e[4], "unk_0A":e[5]
                })
            seq_off = cand_off + cand_count * 12
            group = []
            for off in range(seq_off, offs[15], 2):
                val = unpack_from(">h", content, off)[0]
                if val == -1:
                    if group:
                        l_seq_groups.append({"actions": group})
                        group = []
                else:
                    name = symbols[3][val] if val < len(symbols[3]) else f"ACT_{val}"
                    group.append({"index": val, "name": name})
            if group:
                l_seq_groups.append({"actions": group})
        dbdata["aiCandidateTable"] = l_cands
        dbdata["aiSequenceGroups"] = l_seq_groups

        # AiResponse section: s32 count + s16 indexMap[count] + s16 responseData[]
        l_resp = []
        if offs[15] < offs[16]:
            resp_count = unpack_from(">I", content, offs[15])[0]
            idx_off = offs[15] + 4
            idxmap_vals = []
            for i in range(resp_count):
                e = unpack_from(">h", content, idx_off + i * 2)
                idxmap_vals.append(e[0])
            resp_off = idx_off + resp_count * 2
            s16_data = unpack_from(f">{ (offs[16] - resp_off)//2 }h", content, resp_off) if resp_off < offs[16] else []
            for i, start in enumerate(idxmap_vals):
                if start >= len(s16_data):
                    break
                flags = s16_data[start]
                v1 = s16_data[start + 1] if start + 1 < len(s16_data) else 0
                v2 = s16_data[start + 2] if start + 2 < len(s16_data) else 0
                adj = s16_data[start + 3] if start + 3 < len(s16_data) else 0
                cands = []
                pos = start + 4
                while pos < len(s16_data) and s16_data[pos] != -1:
                    cands.append(s16_data[pos] & 0xFF)
                    pos += 1
                l_resp.append({
                    "name": symbols[1][i] if i < len(symbols[1]) else f"RESP_{i}",
                    "flags":flags, "val1":v1, "val2":v2, "adj":adj, "candidates":cands
                })
        dbdata["aiResponseTable"] = l_resp

        # unk_68 (offs[16] -> EOF, raw bytes)
        dbdata["unk_68"] = content[offs[16]:].hex()

        outpath = replace_path(g).with_name(f"{g.name}.txt")
        outpath.parent.mkdir(parents=True, exist_ok=True)
        with open(outpath, 'w') as outfile:
            def p(line=""):
                print(line, file=outfile)

            for k, v in dbdata.items():

                # ── Timing Data ──
                if k == "player_28":
                    p("### Timing Frame Data (16B × N entries) ###")
                    for i, e in enumerate(v):
                        p(f"  [{i:3d}] fMin={e['unk00']:4d}  fMax={e['unk02']:4d}"
                          f"  {e['unk04']:4d}  {e['unk06']:4d}  {e['unk08']:4d}  {e['unk0A']:4d}"
                          f"  {e['unk0C']:4d}  {e['unk0E']:4d}")
                    p()

                # ── Transition Rules ──
                elif k == "transitionTable":
                    p("### Transition Rules (28B each) ###")
                    for e in v:
                        resp_str = "  ".join(r for r in e['aiResponseForChar'])
                        state_str = e['actionState']
                        btn_str = e['buttons'] if e['buttons'] else "—"
                        mask_str = e['button_mask'] if e['button_mask'] else "—"
                        p(f"  [{e['index']:3d}] \"{e['name']}\"")
                        p(f"        tOff={e['index_in_field28']:3d}  btn={btn_str:15s}  flags={e['flags']:25s}  hold={e['unk06']:5d}"
                          f"  bhv={e['behavior']:>8s}  state={state_str:>8s}  mask={mask_str}")
                        p(f"        self={e['aiResponseSelf']:3d}  aiResp→ {resp_str}")
                    p()

                # ── Logic States ──
                elif k == "logicStates":
                    p("### State Machine (Logic States) ###")
                    for group in v:
                        for grp_name, entries in group.items():
                            p(f"  [{grp_name}]")
                            for m in entries:
                                ns = m['nextLogicState']
                                ns_str = f"→ state_{ns}" if ns >= 0 else "→ TERMINAL"
                                p(f"      step {m['index']:3d}: transition={m['transitionId']:3d} \"{m['transitionName']}\"  {ns_str}")
                    p()

                # ── Player_30 (transition group indices) ──
                elif k == "player_30":
                    p("### Player_30 (Transition Group Counts) ###")
                    for i, e in enumerate(v):
                        p(f"  [{i:3d}] index={e['index_in_field1C']:4d}  count={e['count']:3d}")
                    p()

                # ── Player_1C ──
                elif k == "player_1C":
                    p("### Player_1C (4×s16 per entry, 8B each) ###")
                    for i, e in enumerate(v):
                        p(f"  [{i:3d}]  {e['unk_00']:5d}  {e['unk_02']:5d}  {e['unk_04']:5d}  {e['unk_06']:5d}")
                    p()

                # ── Combat States ──
                elif k == "actionStates":
                    p("### Combat States (56B each) ###")
                    for e in v:
                        dmg = e['damage']
                        dmg_str = f"dmg={dmg:4d}" if dmg else "dmg=———"
                        p(f"  {e['index']}:"
                          f"  frame={e['minFrame']:4d}..{e['maxFrame']:4d}"
                          f"  anim={e['animationId']:3d}"
                          f"  {dmg_str}"
                          f"  flags={e['flags']}")
                        unk_str = "  ".join(f"{k}={v}" for k, v in e.items()
                                            if k.startswith('unk_'))
                        if unk_str:
                            p(f"        {unk_str}")
                    p()

                # ── Sounds ──
                elif k == "sounds":
                    p("### Sound/Frame Triggers (8B each) ###")
                    for i, e in enumerate(v):
                        parts = []
                        for j in range(1, 5):
                            s = e[f'sound{j}']
                            frm = e[f'frame{j}']
                            if s != 0xFF:
                                parts.append(f"snd={s:2d} @f:{frm:3d}")
                        p(f"  [{i:3d}]  {'  '.join(parts) if parts else '(empty)'}")
                    p()

                # ── Player_6C ──
                elif k == "player_6C":
                    p("### Player_6C ###")
                    for e in v:
                        p(f"  unk_num={e['unk_num']}")
                    p()

                # ── Move-to-LogicState Map ──
                elif k == "player_38":
                    p("### Move-to-LogicState Map (2B each) ###")
                    for e in v:
                        p(f"  {e['moveId']:>12s}  →  {e['logicState']:4d}")
                    p()

                # ── Player_44 (per-frame data) ──
                elif k == "player_44":
                    p("### Player_44 (Per-Frame Bytes) ###")
                    frames_per_line = 20
                    entries = v
                    for start in range(0, len(entries), frames_per_line):
                        chunk = entries[start:start + frames_per_line]
                        line = f"  [{start:4d}] " + " ".join(f"{e['frame']:3d}" for e in chunk)
                        p(line)
                    p()

                # ── Projectile Definitions ──
                elif k == "projectileDefs":
                    p("### Projectile Definitions (76B each) ###")
                    for i, e in enumerate(v):
                        p(f"  [{i:3d}] lifetime={e['lifetime']:3d}  boneId={e['boneId']:3d}"
                          f"  origin=({e['originX']:4d},{e['originY']:4d},{e['originZ']:4d})"
                          f"  velocity=({e['velocityX']:4d},{e['velocityY']:4d},{e['velocityZ']:4d})"
                          f"  sprite=({e['spriteIndex']},{e['spriteFrame']})"
                          f"  modelIdx={e['modelIndex']}")
                        p(f"        flags={e['flags']:#06x}  "
                          f"{e['unk_1E']:4d} {e['unk_24']:4d} {e['unk_28']:4d}"
                          f" {e['unk_2E']:4d} {e['unk_30']:4d} {e['unk_32']:4d}"
                          f" {e['unk_34']:4d} {e['unk_36']:4d} {e['unk_38']:4d}"
                          f" {e['unk_3A']:4d} {e['unk_3C']:4d} {e['unk_40']:4d} {e['unk_42']:4d}"
                          f"  light={e['lightColors']}")
                    p()

                # ── Projectile Barrages ──
                elif k == "projectileBarrages":
                    p("### Projectile Barrages (8 shots × 3B each) ###")
                    for i, e in enumerate(v):
                        shots_str = ", ".join(f"proj{s['projectileId']:d}@f:{s['frameIndex']:d}" for s in e['shots'])
                        p(f"  [{i:3d}] {len(e['shots'])} shots: {shots_str}")
                    p()

                # ── AI Action Rows ──
                elif k == "aiActionRows":
                    AI_CALLBACK_NAMES = [
                        "approach",          # 0  - wait until opponent within actionParam
                        "retreat",           # 1  - wait until opponent beyond actionParam
                        "immediate",         # 2  - returns 0 immediately (no-op)
                        "timer",             # 3  - actionParam countdown, done when 0
                        "anim_half",         # 4  - wait until past first half of animation
                        "punish",            # 5  - watch opponent hitbox, punish whiffs
                        "reset",             # 6  - returns -1 immediately (force reset)
                        "blockstring",       # 7  - pressure/blockstring mixup
                        "breaker_crouch",    # 8  - combo breaker setup (crouching variant)
                        "counter_stand",     # 9  - counter setup (standing variant)
                        "random_delay",      #10  - set random delay timer, then countdown
                        "distance",          #11  - raw distance check (no anim guard)
                        "delay_advance",     #12  - random delay, then advance+execute next
                        "delay_advance2",    #13  - random delay variant (identical to 12)
                        "response_gate",     #14  - opponent response flag gate (hit confirm)
                        "loop_back",         #15  - rewind sequence by 2 steps
                    ]
                    p("### AI Action Rows ###")
                    for r in v:
                        if r['callbackIdx'] == -1:
                            cb = "none"
                        else:
                            cb = AI_CALLBACK_NAMES[r['callbackIdx']]
                        moves_str = ", ".join(str(m) for m in r['moves'])
                        p(f"  [{r['index']:3d}] \"{r['name']}\""
                          f"  cb={cb}  param={r['actionParam']:5d}"
                          f"  cond=0x{r['conditionFlags']:04x}"
                          f"  moves=[{moves_str}]")
                    p()

                # ── AI Candidate Table ──
                elif k == "aiCandidateTable":
                    p("### AI Candidate Table (12B each) ###")
                    for i, c in enumerate(v):
                        p(f"  [{i:3d}] \"{c['name']}\""
                          f"  seqIdx={c['actionIndex']:3d}"
                          f"  diffMask=0x{c['difficultyMask']:04x}"
                          f"  dist=({c['distanceMin']:5d},{c['distanceMax']:5d})"
                          f"  cond=0x{c['conditionFlags']:04x}")
                    p()

                # ── AI Sequence Groups ──
                elif k == "aiSequenceGroups":
                    p("### AI Sequence Groups (× actionIndex) ###")
                    for i, g in enumerate(v):
                        acts = ", ".join(f'{a["index"]}:"{a["name"]}"' for a in g["actions"])
                        p(f"  group {i:3d}: [{acts}]")
                    p()

                # ── AI Response Table ──
                elif k == "aiResponseTable":
                    p("### AI Response Table (per-state AI decisions) ###")
                    for i, r in enumerate(v):
                        p(f"  [{i:3d}] \"{r['name']}\""
                          f"  flags=0x{r['flags']:04x}"
                          f"  v1={r['val1']:4d}  v2={r['val2']:4d}  adj={r['adj']:4d}"
                          f"  candidates={r['candidates']}")
                    p()

                # ── Raw unk_68 ──
                elif k == "unk_68":
                    p("### Unknown Data (offset 16 → EOF) ###")
                    hex_str = v
                    for start in range(0, len(hex_str), 64):
                        p(f"  {hex_str[start:start+64]}")
                    p()

                # ── anything else ──
                else:
                    p(f"### {k} ###")
                    for entry in v:
                        p(f"  {entry}")
                    p()

def process_models():
    for ext in ("*.TMD", "*.GMD", "*.K2", "*.K3", "*.K4", "*.K5"):
        for mdl in Path(RAW_ASSETS_PATH).glob(f'**/{ext}'):
            content = mdl.read_bytes()

            # ---- Header ----
            signature = content[0:4]
            if signature != b'2KMD':
                raise NotImplementedError(f"Unsupported signature: {signature}")

            numNodes = unpack_from(">I", content, 4)[0]

            pos = 8
            nodeOffsets = [unpack_from(">I", content, pos + 4 * i)[0] for i in range(numNodes)]
            pos += 4 * numNodes

            numTextures = unpack_from(">I", content, pos)[0]; pos += 4
            textureOffsets = [unpack_from(">I", content, pos + 4 * i)[0] for i in range(numTextures)]
            pos += 4 * numTextures

            nodeHierarchyOffset = unpack_from(">i", content, pos)[0]; pos += 4
            batchOffsets = [unpack_from(">I", content, pos + 4 * i)[0] for i in range(numNodes)]
            pos += 4 * numNodes

            ci4PaletteOffset = unpack_from(">i", content, pos)[0]; pos += 4
            ci8PaletteOffset = unpack_from(">i", content, pos)[0]; pos += 4

            # ---- Palettes ----
            fileSize = len(content)

            ci4Palettes = []
            if ci4PaletteOffset != -1:
                end = ci8PaletteOffset if ci8PaletteOffset != -1 else fileSize
                palData = content[ci4PaletteOffset:end]
                num = len(palData) // 32
                ci4Palettes = [palData[i * 32:(i + 1) * 32] for i in range(num)]

            ci8Palettes = []
            if ci8PaletteOffset != -1:
                palData = content[ci8PaletteOffset:]
                num = len(palData) // 512
                ci8Palettes = [palData[i * 512:(i + 1) * 512] for i in range(num)]

            # ---- Textures ----
            texInfos = []
            for texOff in textureOffsets:
                width, height, fmt, palIdx = unpack_from(">IIii", content, texOff)
                if fmt not in (4, 8):
                    print(f"  {mdl.name}: skipping texture fmt={fmt}")
                    texInfos.append(None)
                    continue
                dataSize = (width * height) // (8 // fmt)
                data = content[texOff + 0x10:texOff + 0x10 + dataSize]
                palList = ci4Palettes if fmt == 4 else ci8Palettes
                palette = palList[palIdx] if palIdx < len(palList) else None
                texInfos.append(dict(width=width, height=height, format=fmt,
                                     palIndex=palIdx, data=data, palette=palette))

            # ---- Output dirs ----
            outdir = replace_path(mdl)
            outdir.mkdir(parents=True, exist_ok=True)
            texDir = outdir / "Textures"
            texDir.mkdir(parents=True, exist_ok=True)

            for i, tex in enumerate(texInfos):
                if tex is not None and tex["palette"] is not None:
                    save_texture(tex["data"], tex["width"], tex["height"],
                                 tex["format"], tex["palette"], texDir / f"tex_{i}.png")

            # ---- Nodes ----
            nodes = []
            for nodeOff in nodeOffsets:
                numV, numT, offV, offT, offNumBatches, unused = unpack_from(">IIIIII", content, nodeOff)

                verts = []
                baseV = nodeOff + offV
                for j in range(numV):
                    o = baseV + j * 16
                    x, y, z, flag, u, v, r, g, b, a = unpack_from(">hhhHhhBBBB", content, o)
                    verts.append((x, y, z, flag, u, v, r, g, b, a))

                tris = []
                baseT = nodeOff + offT
                for j in range(numT):
                    i0, i1, i2 = unpack_from(">HHH", content, baseT + j * 6)
                    tris.append((i0, i1, i2))

                numBatches = unpack_from(">I", content, nodeOff + offNumBatches)[0]
                nodes.append(dict(verts=verts, tris=tris, numBatches=numBatches))

            # ---- Batches ----
            allBatches = []
            for ni in range(numNodes):
                bo = batchOffsets[ni]
                nb = nodes[ni]["numBatches"]
                batches = []
                for j in range(nb):
                    texIdx, vi, to, nv, nt, _ptr = unpack_from(">IHHHHI", content, bo + j * 16)
                    batches.append(dict(texIndex=texIdx, vertIndex=vi, triOffset=to,
                                        numVertices=nv, numTriangles=nt))
                allBatches.append(batches)

            # ---- Hierarchy ----
            hierarchy = []
            if nodeHierarchyOffset != -1:
                for i in range(numNodes + 1):
                    p, x, y, z = unpack_from(">iiii", content, nodeHierarchyOffset + i * 16)
                    hierarchy.append((p, x, y, z))

            # ---- Write output ----
            outpath = outdir / f"{mdl.name}.txt"
            with open(outpath, "w") as f:
                print(f"# Model: {mdl.name}", file=f)
                print(f"# Nodes: {numNodes}", file=f)
                print(f"# Textures: {numTextures}", file=f)
                print(file=f)

                print("=== TEXTURES ===", file=f)
                for i, tex in enumerate(texInfos):
                    if tex is None:
                        print(f"Texture {i}: INVALID", file=f)
                    else:
                        print(f"Texture {i}: {tex['width']}x{tex['height']} CI{tex['format']} palIdx={tex['palIndex']}", file=f)
                print(file=f)

                print("=== NODE HIERARCHY ===", file=f)
                for i, (p, x, y, z) in enumerate(hierarchy):
                    if i == 0:
                        print(f"Base: num_nodes={p} pos=({x}, {y}, {z})", file=f)
                    else:
                        print(f"Node {i - 1}: parent={p} pos=({x}, {y}, {z})", file=f)
                print(file=f)

                for ni in range(numNodes):
                    node = nodes[ni]
                    verts, tris = node["verts"], node["tris"]
                    nb = node["numBatches"]
                    print(f"=== NODE {ni} ({len(verts)} verts, {len(tris)} tris, {nb} batches) ===", file=f)

                    print("--- Vertices (global) ---", file=f)
                    for j, (x, y, z, flag, u, v, r, g, b, a) in enumerate(verts):
                        print(f"  v {x} {y} {z}  uv={u} {v}  rgba={r} {g} {b} {a}", file=f)

                    print("--- Triangles (global) ---", file=f)
                    for j, (i0, i1, i2) in enumerate(tris):
                        print(f"  f {i0} {i1} {i2}", file=f)

                    print(f"=== BATCHES FOR NODE {ni} ===", file=f)
                    for bj, batch in enumerate(allBatches[ni]):
                        ti = batch["texIndex"]
                        print(f"--- Batch {bj}: texIndex={ti} vertStart={batch['vertIndex']} "
                              f"numVerts={batch['numVertices']} triStart={batch['triOffset']} "
                              f"numTris={batch['numTriangles']} ---", file=f)
                        vs = batch["vertIndex"]
                        ve = vs + batch["numVertices"]
                        for vj in range(vs, ve):
                            x, y, z, flag, u, v, r, g, b, a = verts[vj]
                            print(f"  v {x} {y} {z}  uv={u} {v}  rgba={r} {g} {b} {a}", file=f)
                        ts = batch["triOffset"]
                        te = ts + batch["numTriangles"]
                        for tj in range(ts, te):
                            i0, i1, i2 = tris[tj]
                            ri0, ri1, ri2 = i0 - vs, i1 - vs, i2 - vs
                            print(f"  f {i0} {i1} {i2}  (rel: {ri0} {ri1} {ri2})", file=f)
                    print(file=f)

def analyze():
    process_tex()
    process_sp2()
    process_sym()
    build_char_name_map()
    process_db()
    process_models()
        
def main():
    raw_root = Path(RAW_ASSETS_PATH) / "ROOT"
    extracted_root = Path("game_assets/extracted") / "ROOT"
    for p in (raw_root, extracted_root):
        if p.exists():
            shutil.rmtree(p)
            print(f"Cleaned {p}")
    assets = Path(ROMFILE).read_bytes()[ASSETS_OFFSET:]
    reader = BinaryReader(assets, RAW_ASSETS_PATH)
    reader.read_wad()
    analyze()

if __name__ == "__main__":
    main()