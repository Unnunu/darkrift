#!/usr/bin/env python3
from pathlib import Path
from struct import unpack_from, calcsize, pack
import subprocess
from n64img.image import CI8
import pprint

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

def process_tex():
    for g in Path(RAW_ASSETS_PATH).glob('**/*.TEX'):
        content = g.read_bytes()
        width, height = unpack_from(">II", content)
        
        img = CI8(content[0x10:0x10 + width * height], width, height)

        palette = content[0x10 + width * height:]
        if len(palette) != 512:
            # something wrong, continue
            continue
        img.set_palette(palette)

        outpath = replace_path(g).with_suffix(".png")
        outpath.parent.mkdir(parents=True, exist_ok=True)
        img.write(outpath)

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
    names = ['L','A','R','B', 'CUP','CRIGHT','CDOWN','CLEFT','ZTRIG','','','START','UP','RIGHT','DOWN','LEFT']
    return '+'.join(names[i] for i in range(16) if (x & 2**i))

def process_db():
    for g in Path(RAW_ASSETS_PATH).glob('**/*.DB'):
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
        for off in range(offs[1] + 4, offs[2], 28):
            e = unpack_from(">hHHHhhH14IIIH", content, off)
            l.append({"index_in_field28":e[0], "buttons":get_buttons(e[1]), "flags":e[2], "unk06":e[3],
                      "index_in_field24":e[4], "stateId":e[5], "button_mask":e[6], "unk0E":[e[7],e[8],e[9],e[10]]})
        dbdata["player_2C"] = l

        l = []
        for off in range(offs[2], offs[3], 4):
            e = unpack_from(">hh", content, off)
            l.append({"index_in_field2C":e[0], "next_move_maybe":e[1]})
        dbdata["player_34"] = l

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
        dbdata["states"] = l

        outpath = replace_path(g).with_name(f"{g.name}.txt")
        outpath.parent.mkdir(parents=True, exist_ok=True)
        with open(outpath, 'w') as outfile:
            for k,v in dbdata.items():
                print(f"{k}:", file=outfile)
                for l in v:
                    print(f"\t{l}", file=outfile)
            

def analyze():
    process_tex()
    process_sp2()
    process_sym()
    process_db()
        
def main():
    assets = Path(ROMFILE).read_bytes()[ASSETS_OFFSET:]
    reader = BinaryReader(assets, RAW_ASSETS_PATH)
    reader.read_wad()
    analyze()

if __name__ == "__main__":
    main()