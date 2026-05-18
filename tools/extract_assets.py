#!/usr/bin/env python3
from pathlib import Path
from struct import unpack_from, calcsize, pack
import subprocess
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

def process_db():
    for g in Path(RAW_ASSETS_PATH).glob('**/*.DB'):

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
            e = unpack_from(">hHHHhhH14IIIH", content, off)
            l.append({"name":symbols[0][i], "index":i, "index_in_field28":e[0], "buttons":get_buttons(e[1]), "flags":get_move_flags(e[2]), "unk06":e[3],
                      "index_in_field24":f"f24_{e[4]}_", "actionState":e[5], "button_mask":get_buttons(e[6]), "unk0E":[e[7],e[8],e[9],e[10]]})
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
            l.append({"unk_00":e[0], "unk_02":e[1], "unk_04":e[2], "unk_06":e[3],
                      "animationId":e[4], "unk_0A":e[5], "unk_0C":e[6], "unk_0E":e[7],
                      "unk_10":e[8], "unk_12":e[9], "unk_14":e[10], "unk_16":e[11],
                      "unk_18":e[12], "unk_1A":e[13], "unk_1C":e[14], "unk_1E":e[15],
                      "damage":e[16], "unk_22":e[17], "unk_24":e[18], "unk_26":e[19],
                      "unk_28":e[20], "unk_2A":e[21], "unk_2C":e[22], "unk_2E":e[23],
                      "unk_30":e[24], "unk_32":e[25], "flags":e[26]})
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
            l.append({"logicState":e[0]})
        dbdata["player_38"] = l

        l = []
        for off in range(offs[9], offs[10], 1):
            e = unpack_from(">B", content, off)
            l.append({"frame":e[0]})
        dbdata["player_44"] = l

        l = []
        for off in range(offs[10], offs[11], 76):
            e = unpack_from(">B", content, off)
            l.append({"frame":e[0]})
        dbdata["player_48"] = l

        outpath = replace_path(g).with_name(f"{g.name}.txt")
        outpath.parent.mkdir(parents=True, exist_ok=True)
        with open(outpath, 'w') as outfile:
            for k,v in dbdata.items():
                print(f"{k}:", file=outfile)
                if k == "logicStates":
                    for l in v:
                        for k1, v1 in l.items():
                            print(f"\t{k1}:", file=outfile)
                            for m in v1:
                                print(f"\t\t{m}", file=outfile)
                else:
                    for l in v:
                        print(f"\t{l}", file=outfile)

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
                    print(f"Node {i}: parent={p} pos=({x}, {y}, {z})", file=f)
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
    process_db()
    process_models()
        
def main():
    assets = Path(ROMFILE).read_bytes()[ASSETS_OFFSET:]
    reader = BinaryReader(assets, RAW_ASSETS_PATH)
    reader.read_wad()
    analyze()

if __name__ == "__main__":
    main()