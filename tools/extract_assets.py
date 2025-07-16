#!/usr/bin/env python3
from pathlib import Path
from struct import unpack_from, calcsize

ROMFILE = "darkrift.z64"
ASSETS_OFFSET = 0x57AE0

class BinaryReader:
    def __init__(self, data, offset = 0):
        self.data = data
        self.offset = offset

    def read(self, fmt, names):
        size = calcsize(fmt)
        values = unpack_from(fmt, self.data, self.offset)
        self.offset += size
        return dict(zip(names, values))
    
    def read_wad(self):
        header = self.read(">II20s", ("numFolders", "unknown", "name"))
        print(header)
        for i in range(header['numFolders']):
            pass
        
def main():
    assets = Path(ROMFILE).read_bytes()
    reader = BinaryReader(assets, ASSETS_OFFSET)
    reader.read_wad()

if __name__ == "__main__":
    main()