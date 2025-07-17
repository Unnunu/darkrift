#!/usr/bin/env python3
from pathlib import Path
from struct import unpack_from, calcsize

ROMFILE = "darkrift.z64"
ASSETS_PATH = "game_assets"
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
        print(file["name"], file["offset"], self.offset)

        if file['offset'] in self.cache:
            file_content = self.cache[file['offset']]
        else:
            self.offset = file["offset"]
            file_content = self.data[file["offset"]:file["offset"] + file["size"]]
            self.offset += file["size"]

        file_name = file["name"]
        if file["size"] != file["unpacked_size"]:
            file_name = "c_" + file_name

        file_path = self.path / folder["name"] / file_name

        if file["type"] != 4:            
            file_path.parent.mkdir(parents=True, exist_ok=True)
            file_path.write_bytes(file_content)
            self.cache[file["offset"]] = file_content
        else:
            # parse inner wad file
            print("opening wad", file_path)
            reader = BinaryReader(file_content, file_path)
            reader.read_wad()
        
def main():
    assets = Path(ROMFILE).read_bytes()[ASSETS_OFFSET:]
    reader = BinaryReader(assets, ASSETS_PATH)
    reader.read_wad()
    print(reader.offset)

if __name__ == "__main__":
    main()