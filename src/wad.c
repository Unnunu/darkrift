#include "common.h"
#include "ld_addrs.h"
#include "string.h"

enum WadFileTypes {
    WAD_FILE_ANM = 0,
    WAD_FILE_TEX = 1,
    WAD_FILE_SP2 = 2,
    WAD_FILE_3 = 3,
    WAD_FILE_WAD = 4,
    WAD_FILE_DB = 5,
    WAD_FILE_PCL = 6,
    WAD_FILE_GMD = 7,
    WAD_FILE_TMD = 8,
    WAD_FILE_SEQ = 9,
    WAD_FILE_CTL = 10,
    WAD_FILE_TBL = 11,
    WAD_FILE_SP3 = 12,
    WAD_FILE_SFTBL = 13,
    WAD_FILE_SFXBL = 14,
    WAD_FILE_K2 = 15,
    WAD_FILE_MOV = 16,
    WAD_FILE_OC = 17,
    WAD_FILE_SYM = 18,
    WAD_FILE_VOX = 19,
    WAD_FILE_K3 = 20,
    WAD_FILE_K4 = 21,
    WAD_FILE_K5 = 22
};

typedef struct WadFolder {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 numFiles;
    /* 0x1C */ s32 folderIndex;
} WadFolder; // size >= 0x20

typedef struct WadFileEntry {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 type;
    /* 0x1C */ s32 size;
    /* 0x20 */ s32 unpackedSize;
} WadFileEntry; // size = 0x24

typedef struct WadFile {
    /* 0x00 */ u32 numFolders;
    /* 0x04 */ u32 unk_04; // unknown, same as numFolders
    /* 0x08 */ WadFolder folders[1];
} WadFile;

extern s32 gNumAssets;

extern Asset gAssets[256];
extern s32 D_8013C200;
extern WadFile *gWadFile;
extern s32 D_8013C208;
extern u8 *gWadRomAddress;
extern WadFolder *gWadCurrentFolder;
extern s32 D_8013C214;
extern s32 D_8013C218;
extern u32 gWadNumFiles;
extern u32 gWadNumFolders;

void func_80025A0C(Asset *);
void asset_read(s32);
void assets_clear_unused(void);
void dma_read(s32 romAddr, void *vramAddr, s32 size);

void func_80026B74(Asset *);
void func_80026BE0(Asset *arg0);
void func_80027680(Asset *);

void func_800276F0(Asset *);
void func_80027918(Asset *);
void func_80026EEC(Asset *);
void func_800279E4(Asset *);
void func_80027A14(Asset *);
void func_80027C0C(Asset *);
void func_80027DA4(Asset *);
void func_80027EFC(Asset *);
void func_80027780(Asset *);
void func_80027804(Asset *);
void func_80027888(Asset *);
void func_80026DF0(Asset *);

void func_80025B40(void) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {}
}

void str_concat(char *dst, char *src) {
    u32 dst_len = strlen(dst);
    u32 src_len = strlen(src);
    s32 i;

    for (i = 0; i < src_len; i++) {
        dst[dst_len + i] = *src++;
    }

    dst[dst_len + src_len] = 0;
}

void str_copy(char *arg0, char *arg1) {
    u32 size = strlen(arg1);
    s32 i;

    for (i = 0; i < size; i++) {
        *arg0++ = *arg1++;
    }

    *arg0 = 0;
}

s32 str_compare(char *arg0, char *arg1) {
    u32 sp1C;
    u32 len2;
    u32 i;

    sp1C = strlen(arg0);
    len2 = strlen(arg1);
    if (sp1C != len2) {
        return 1;
    }

    for (i = 0; i < sp1C; i++) {
        if (*arg0++ != *arg1++) {
            return 1;
        }
    }

    return 0;
}

void str_toupper(char *str) {
    u32 size = strlen(str);
    u32 i;

    for (i = 0; i < size; i++) {
        str[i] = (str[i] >= 'a') ? str[i] -= 'a' - 'A' : str[i];
    }
}

u32 asset_find(char *name, s32 owner) {
    u32 i;

    str_toupper(name);
    for (i = 0; i < gNumAssets; i++) {
        if (str_compare(name, gAssets[i].name) == 0 && owner == gAssets[i].owner) {
            return i;
        }
    }

    return -1;
}

void func_80025E6C(void) {
    u32 i;

    gNumAssets = 0;
    for (i = 0; i < 256; i++) {
        gAssets[i].memory_slot = gAssets[i].aux_memory_slot = -1;
        gAssets[i].flags = 1;
        gAssets[i].name[0] = '\0';
    }
}

void func_80025EDC(s32 arg0, s32 size) {
    D_8013C200 = arg0;
    gWadFile = D_8013C200;
    D_8013C208 = D_8013C200 + 0x2800;
    D_8013C214 = D_8013C208 - arg0;
    D_8013C218 = size - D_8013C214;
}

void wad_find_wad(char *name) {
    s32 i;
    char fullname[20];
    WadFileEntry *firstFile;
    WadFileEntry *file;

    firstFile = gWadCurrentFolder->offset + (u8 *) gWadFile;
    str_copy(fullname, name);
    str_concat(fullname, ".WAD");

    for (i = 0, file = firstFile; i < gWadNumFiles; i++, file++) {
        if (str_compare(file->name, fullname) == 0) {
            gWadRomAddress += file->offset;
            return;
        }
        if (file && file) {
            // FAKE MATCH
        }
    }
}

s32 wad_select_folder(char *folderName) {
    s32 pad;
    u32 i;
    WadFolder *folders;

    folders = gWadFile->folders;
    for (i = 0; i < gWadNumFolders; i++) {
        if (str_compare(folderName, folders[i].name) == 0) {
            gWadCurrentFolder = &folders[i];
            gWadNumFolders = 1;
            gWadNumFiles = folders[i].numFiles;
            return TRUE;
        }
    }

    return FALSE;
}

void wad_open_one(char *name) {
    if (name[0] == '\0') {
        // load root wad
        gWadRomAddress = resources_ROM_START;
        dma_read(gWadRomAddress, gWadFile, D_8013C214);
        gWadCurrentFolder = gWadFile->folders;
        gWadNumFolders = gWadFile->numFolders;
        gWadNumFiles = gWadCurrentFolder->numFiles;
    } else if (wad_select_folder(name)) {
        // select folder in current wad file
    } else {
        wad_find_wad(name);
        dma_read(gWadRomAddress, gWadFile, D_8013C214);
        gWadCurrentFolder = gWadFile->folders;
        gWadNumFolders = gWadFile->numFolders;
        gWadNumFiles = gWadCurrentFolder[0].numFiles;
    }
}

void wad_open_path(char *path) {
    s32 len;
    char path_item[24];
    u32 i;
    u32 j;

    len = strlen(path);
    j = 0;
    str_toupper(path);
    path_item[0] = '\0';

    for (i = 0; i < len; i++) {
        if (path[i] != '/') {
            path_item[j++] = path[i];
        } else {
            path_item[j] = '\0';
            j = 0;
            wad_open_one(path_item);
        }
    }

    path_item[j] = '\0';
    wad_open_one(path_item);
}

void func_80026250(void) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        if (gAssets[i].memory_slot >= 0) {
            gAssets[i].data = D_8005AEB8[gAssets[i].memory_slot].unk_04;
        }
        if (gAssets[i].aux_memory_slot >= 0) {
            gAssets[i].aux_data = D_8005AEB8[gAssets[i].aux_memory_slot].unk_04;
        }
    }
}

void func_800262B8(char *path, s32 owner) {
    assets_clear_unused();
    wad_open_path(path);
    asset_read(owner);
    func_80000E0C(gWadFile, 0, D_8013C214);
    assets_clear_unused();
}

void func_8002630C(s32 arg0) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        if (arg0 == gAssets[i].owner) {
            func_80026B74(gAssets + i);
        }
    }

    assets_clear_unused();
}

void func_800263A8(void) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        func_80026B74(gAssets + i);
    }

    assets_clear_unused();
}

void func_80026418(s32 arg0) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        if (arg0 == gAssets[i].type) {
            func_80026B74(gAssets + i);
        }
    }

    assets_clear_unused();
}

void asset_read(s32 owner) {
    s32 pad[2];
    u32 i;
    u32 free_memory;
    WadFileEntry *file;
    s32 v0;

    free_memory = get_free_mem(sFreeChunksList);
    file = (WadFileEntry *) ((u8 *) gWadFile + gWadCurrentFolder->offset);

    for (i = 0; i < gWadNumFiles; i++) {
        v0 = asset_find(file[i].name, owner);

        if (v0 >= 0) {
            switch (file[i].type) {
                case WAD_FILE_3:
                    func_80027680(gAssets + v0);
                    break;
                case WAD_FILE_TMD:
                    func_800276F0(gAssets + v0);
                    break;
                case WAD_FILE_GMD:
                    func_80027918(gAssets + v0);
                    break;
                case WAD_FILE_SP2:
                    func_80026EEC(gAssets + v0);
                    break;
                case WAD_FILE_TBL:
                    func_800279E4(gAssets + v0);
                    break;
                case WAD_FILE_SEQ:
                    func_80027A14(gAssets + v0);
                    break;
                case WAD_FILE_SFXBL:
                    func_80027C0C(gAssets + v0);
                    break;
                case WAD_FILE_SP3:
                    func_80027DA4(gAssets + v0);
                    break;
                case WAD_FILE_K2:
                    func_80027EFC(gAssets + v0);
                    break;
                case WAD_FILE_K3:
                    func_80027780(gAssets + v0);
                    break;
                case WAD_FILE_K4:
                    func_80027804(gAssets + v0);
                    break;
                case WAD_FILE_K5:
                    func_80027888(gAssets + v0);
                    break;
            }
        } else if (file[i].unpackedSize <= free_memory) {
            str_copy(gAssets[gNumAssets].name, file[i].name);
            gAssets[gNumAssets].size = file[i].size;
            gAssets[gNumAssets].owner = owner;
            gAssets[gNumAssets].type = file[i].type;
            gAssets[gNumAssets].romAddr = gWadRomAddress + file[i].offset;
            gAssets[gNumAssets].unpacked_size = file[i].unpackedSize;

            if (file[i].size != file[i].unpackedSize) {
                gAssets[gNumAssets].flags = 2;
                gNumAssets++;
            } else {
                gAssets[gNumAssets].flags = 0;
                gNumAssets++;
            }

            switch (file[i].type) {
                case WAD_FILE_ANM:
                    func_80026DF0(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_TEX:
                    func_80026ECC(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SP2:
                    func_80027054(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_3:
                    func_800271C0(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_GMD:
                    func_80027270(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_TMD:
                    func_800275A4(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_CTL:
                    func_80027988(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SEQ:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    func_80027A14(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_TBL:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    func_800279E4(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SP3:
                    func_80027CAC(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SFTBL:
                    func_80027B7C(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SFXBL:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    func_80027C0C(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K2:
                    func_80027E20(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_MOV:
                    func_80027F8C(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_OC:
                    func_80027D84(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SYM:
                    func_80027FCC(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_VOX:
                    func_80027B10(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K3:
                    func_80027320(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K4:
                    func_800273F4(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K5:
                    func_800274C8(gAssets + gNumAssets - 1);
                    break;
                default:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    break;
            }
        }
    }
}

void func_80026A94(Asset *asset, s32 size) {
    s32 index;
    index = func_80000EA8(size);
    asset->memory_slot = index;
    asset->data = D_8005AEB8[index].unk_04;
}

void func_80026AD4(Asset *arg0) {
    func_80000F70(arg0->memory_slot);
    arg0->memory_slot = -1;
}

void func_80026B04(Asset *arg0) {
    func_80000F70(arg0->aux_memory_slot);
    arg0->aux_memory_slot = -1;
}

void func_80026B34(Asset *arg0, s32 arg1) {
    s32 index;
    index = func_80000EA8(arg1);
    arg0->aux_memory_slot = index;
    arg0->aux_data = D_8005AEB8[index].unk_04;
}

void func_80026B74(Asset *arg0) {
    arg0->flags = 1;

    if (arg0->memory_slot >= 0) {
        func_80000F70(arg0->memory_slot);
    }

    if (arg0->aux_memory_slot >= 0) {
        func_80000F70(arg0->aux_memory_slot);
    }

    arg0->memory_slot = -1;
    arg0->aux_memory_slot = -1;
    arg0->name[0] = '\0';
    arg0->data = arg0->aux_data = NULL;
}

void func_80026BE0(Asset *asset) {
    func_80026A94(asset, asset->unpacked_size);
    if (asset->flags & 2) {
        func_80025A0C(asset);
    } else {
        dma_read(asset->romAddr, asset->data, asset->unpacked_size);
    }
}

void assets_clear_unused(void) {
    u32 i, j;
    u32 s3;

    s3 = 0;
    for (i = 0; i < gNumAssets; i++) {
        if (gAssets[i].flags & 1) {
            for (j = i + 1; j < gNumAssets; j++) {
                if (!(gAssets[j].flags & 1)) {
                    break;
                }
            }

            if (j != gNumAssets) {
                gAssets[i].data = gAssets[j].data;
                gAssets[i].aux_data = gAssets[j].aux_data;
                gAssets[i].size = gAssets[j].size;
                gAssets[i].unpacked_size = gAssets[j].unpacked_size;
                gAssets[i].type = gAssets[j].type;
                gAssets[i].flags = gAssets[j].flags;
                gAssets[i].memory_slot = gAssets[j].memory_slot;
                gAssets[i].aux_memory_slot = gAssets[j].aux_memory_slot;
                gAssets[i].owner = gAssets[j].owner;
                str_copy(gAssets[i].name, gAssets[j].name);
                gAssets[j].name[0] = '\0';
                gAssets[j].aux_memory_slot = -1;
                gAssets[j].memory_slot = -1;
                gAssets[j].flags = 1;
                s3++;
            } else {
                gAssets[i].name[0] = '\0';
                gAssets[i].aux_memory_slot = -1;
                gAssets[i].memory_slot = -1;
                gAssets[i].flags = 1;
                gNumAssets = s3;
                return;
            }
        } else {
            s3++;
        }
    }

    gNumAssets = s3;
    for (i = 0; i < gNumAssets; i++) {}
}

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026DF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026ECC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026EEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027054.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800271C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027270.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027320.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800273F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800274C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800275A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027680.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800276F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027804.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027888.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027918.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027988.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800279E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027A14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027B10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027B7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027C0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027C54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027CAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027D84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027DA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027E20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027EFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027F8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028010.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800281F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028400.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002856C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800287AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028890.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028AE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028E84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028F38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80028FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029044.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029630.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029D04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029D84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029DC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029E5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029EBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029F58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80029FF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A050.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A0EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A188.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A1F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A288.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A4E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002A870.s")
