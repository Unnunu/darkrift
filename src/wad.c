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

typedef struct WadStructGamma {
    /* 0x00 */ void *data;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char name[20];
    /* 0x24 */ s32 size;
    /* 0x28 */ s32 unpacked_size;
    /* 0x2C */ u16 type;
    /* 0x2E */ s16 flags;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ char pad_32[2];
    /* 0x34 */ u8 *romAddr;
} WadStructGamma; // size = 0x38

extern s32 D_80051F40;

extern WadStructGamma D_80138A00[256];
extern s32 D_8013C200;
extern WadFile *D_8013C204;
extern s32 D_8013C208;
extern u8 *D_8013C20C;
extern WadFolder *D_8013C210;
extern s32 D_8013C214;
extern s32 D_8013C218;
extern u32 D_8013C21C;
extern u32 D_8013C220;

void func_80025A0C(WadStructGamma *);
void func_800264B4(s32);
void func_80026C38(void);
void dma_read(s32 romAddr, void *vramAddr, s32 size);
void func_80000E0C(u8 *arg0, u8 arg1, u32 arg2);

void func_80026B74(WadStructGamma *);
void func_80026BE0(WadStructGamma *arg0);
void func_80027680(WadStructGamma *);

void func_800276F0(WadStructGamma *);
void func_80027918(WadStructGamma *);
void func_80026EEC(WadStructGamma *);
void func_800279E4(WadStructGamma *);
void func_80027A14(WadStructGamma *);
void func_80027C0C(WadStructGamma *);
void func_80027DA4(WadStructGamma *);
void func_80027EFC(WadStructGamma *);
void func_80027780(WadStructGamma *);
void func_80027804(WadStructGamma *);
void func_80027888(WadStructGamma *);
void func_80026DF0(WadStructGamma *);

void func_80025B40(void) {
    u32 i;

    for (i = 0; i < D_80051F40; i++) {}
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

u32 func_80025DB4(char *name, s32 arg1) {
    u32 i;

    str_toupper(name);
    for (i = 0; i < D_80051F40; i++) {
        if (str_compare(name, D_80138A00[i].name) == 0 && arg1 == D_80138A00[i].unk_30) {
            return i;
        }
    }

    return -1;
}

void func_80025E6C(void) {
    u32 i;

    D_80051F40 = 0;
    for (i = 0; i < 256; i++) {
        D_80138A00[i].unk_08 = D_80138A00[i].unk_0C = -1;
        D_80138A00[i].flags = 1;
        D_80138A00[i].name[0] = '\0';
    }
}

void func_80025EDC(s32 arg0, s32 size) {
    D_8013C200 = arg0;
    D_8013C204 = D_8013C200;
    D_8013C208 = D_8013C200 + 0x2800;
    D_8013C214 = D_8013C208 - arg0;
    D_8013C218 = size - D_8013C214;
}

void wad_open_wad(char *name) {
    s32 i;
    char fullname[20];
    WadFileEntry *firstFile;
    WadFileEntry *file;

    firstFile = D_8013C210->offset + (u8 *) D_8013C204;
    str_copy(fullname, name);
    str_concat(fullname, ".WAD");

    for (i = 0, file = firstFile; i < D_8013C21C; i++, file++) {
        if (str_compare(file->name, fullname) == 0) {
            D_8013C20C += file->offset;
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

    folders = D_8013C204->folders;
    for (i = 0; i < D_8013C220; i++) {
        if (str_compare(folderName, folders[i].name) == 0) {
            D_8013C210 = &folders[i];
            D_8013C220 = 1;
            D_8013C21C = folders[i].numFiles;
            return TRUE;
        }
    }

    return FALSE;
}

void func_800260AC(char *name) {
    if (name[0] == '\0') {
        // load root wad
        D_8013C20C = resources_ROM_START;
        dma_read(D_8013C20C, D_8013C204, D_8013C214);
        D_8013C210 = D_8013C204->folders;
        D_8013C220 = D_8013C204->numFolders;
        D_8013C21C = D_8013C210->numFiles;
    } else if (!wad_select_folder(name)) {
        wad_open_wad(name);
        dma_read(D_8013C20C, D_8013C204, D_8013C214);
        D_8013C210 = D_8013C204->folders;
        D_8013C220 = D_8013C204->numFolders;
        D_8013C21C = D_8013C210[0].numFiles;
    }
}

void func_80026198(char *path) {
    s32 len;
    char folder[24];
    u32 i;
    u32 j;

    len = strlen(path);
    j = 0;
    str_toupper(path);
    folder[0] = '\0';

    for (i = 0; i < len; i++) {
        if (path[i] != '/') {
            folder[j++] = path[i];
        } else {
            folder[j] = '\0';
            j = 0;
            func_800260AC(folder);
        }
    }

    folder[j] = '\0';
    func_800260AC(folder);
}

void func_80026250(void) {
    u32 i;

    for (i = 0; i < D_80051F40; i++) {
        if (D_80138A00[i].unk_08 >= 0) {
            D_80138A00[i].data = D_8005AEB8[D_80138A00[i].unk_08].unk_04;
        }
        if (D_80138A00[i].unk_0C >= 0) {
            D_80138A00[i].unk_04 = D_8005AEB8[D_80138A00[i].unk_0C].unk_04;
        }
    }
}

void func_800262B8(char *path, s32 arg1) {
    func_80026C38();
    func_80026198(path);
    func_800264B4(arg1);
    func_80000E0C(D_8013C204, 0, D_8013C214);
    func_80026C38();
}

void func_8002630C(s32 arg0) {
    u32 i;

    for (i = 0; i < D_80051F40; i++) {
        if (arg0 == D_80138A00[i].unk_30) {
            func_80026B74(D_80138A00 + i);
        }
    }

    func_80026C38();
}

void func_800263A8(void) {
    u32 i;

    for (i = 0; i < D_80051F40; i++) {
        func_80026B74(D_80138A00 + i);
    }

    func_80026C38();
}

void func_80026418(s32 arg0) {
    u32 i;

    for (i = 0; i < D_80051F40; i++) {
        if (arg0 == D_80138A00[i].type) {
            func_80026B74(D_80138A00 + i);
        }
    }

    func_80026C38();
}

void func_800264B4(s32 arg0) {
    s32 pad[2];
    u32 i;
    u32 free_memory;
    WadFileEntry *file;
    s32 v0;

    free_memory = get_free_mem(sFreeChunksList);
    file = (WadFileEntry *) ((u8 *) D_8013C204 + D_8013C210->offset);

    for (i = 0; i < D_8013C21C; i++) {
        v0 = func_80025DB4(file[i].name, arg0);

        if (v0 >= 0) {
            switch (file[i].type) {
                case WAD_FILE_3:
                    func_80027680(D_80138A00 + v0);
                    break;
                case WAD_FILE_TMD:
                    func_800276F0(D_80138A00 + v0);
                    break;
                case WAD_FILE_GMD:
                    func_80027918(D_80138A00 + v0);
                    break;
                case WAD_FILE_SP2:
                    func_80026EEC(D_80138A00 + v0);
                    break;
                case WAD_FILE_TBL:
                    func_800279E4(D_80138A00 + v0);
                    break;
                case WAD_FILE_SEQ:
                    func_80027A14(D_80138A00 + v0);
                    break;
                case WAD_FILE_SFXBL:
                    func_80027C0C(D_80138A00 + v0);
                    break;
                case WAD_FILE_SP3:
                    func_80027DA4(D_80138A00 + v0);
                    break;
                case WAD_FILE_K2:
                    func_80027EFC(D_80138A00 + v0);
                    break;
                case WAD_FILE_K3:
                    func_80027780(D_80138A00 + v0);
                    break;
                case WAD_FILE_K4:
                    func_80027804(D_80138A00 + v0);
                    break;
                case WAD_FILE_K5:
                    func_80027888(D_80138A00 + v0);
                    break;
            }
        } else if (file[i].unpackedSize <= free_memory) {
            str_copy(D_80138A00[D_80051F40].name, file[i].name);
            D_80138A00[D_80051F40].size = file[i].size;
            D_80138A00[D_80051F40].unk_30 = arg0;
            D_80138A00[D_80051F40].type = file[i].type;
            D_80138A00[D_80051F40].romAddr = D_8013C20C + file[i].offset;
            D_80138A00[D_80051F40].unpacked_size = file[i].unpackedSize;

            if (file[i].size != file[i].unpackedSize) {
                D_80138A00[D_80051F40].flags = 2;
                D_80051F40++;
            } else {
                D_80138A00[D_80051F40].flags = 0;
                D_80051F40++;
            }

            switch (file[i].type) {
                case WAD_FILE_ANM:
                    func_80026DF0(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_TEX:
                    func_80026ECC(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_SP2:
                    func_80027054(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_3:
                    func_800271C0(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_GMD:
                    func_80027270(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_TMD:
                    func_800275A4(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_CTL:
                    func_80027988(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_SEQ:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    func_80027A14(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_TBL:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    func_800279E4(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_SP3:
                    func_80027CAC(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_SFTBL:
                    func_80027B7C(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_SFXBL:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    func_80027C0C(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_K2:
                    func_80027E20(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_MOV:
                    func_80027F8C(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_OC:
                    func_80027D84(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_SYM:
                    func_80027FCC(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_VOX:
                    func_80027B10(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_K3:
                    func_80027320(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_K4:
                    func_800273F4(D_80138A00 + D_80051F40 - 1);
                    break;
                case WAD_FILE_K5:
                    func_800274C8(D_80138A00 + D_80051F40 - 1);
                    break;
                default:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    break;
            }
        }
    }
}

void func_80026A94(WadStructGamma *arg0, s32 arg1) {
    s32 index;
    index = func_80000EA8(arg1);
    arg0->unk_08 = index;
    arg0->data = D_8005AEB8[index].unk_04;
}

void func_80026AD4(WadStructGamma *arg0) {
    func_80000F70(arg0->unk_08);
    arg0->unk_08 = -1;
}

void func_80026B04(WadStructGamma *arg0) {
    func_80000F70(arg0->unk_0C);
    arg0->unk_0C = -1;
}

void func_80026B34(WadStructGamma *arg0, s32 arg1) {
    s32 index;
    index = func_80000EA8(arg1);
    arg0->unk_0C = index;
    arg0->unk_04 = D_8005AEB8[index].unk_04;
}

void func_80026B74(WadStructGamma *arg0) {
    arg0->flags = 1;

    if (arg0->unk_08 >= 0) {
        func_80000F70(arg0->unk_08);
    }

    if (arg0->unk_0C >= 0) {
        func_80000F70(arg0->unk_0C);
    }

    arg0->unk_08 = -1;
    arg0->unk_0C = -1;
    arg0->name[0] = '\0';
    arg0->data = arg0->unk_04 = NULL;
}

void func_80026BE0(WadStructGamma *arg0) {
    func_80026A94(arg0, arg0->unpacked_size);
    if (arg0->flags & 2) {
        func_80025A0C(arg0);
    } else {
        dma_read(arg0->romAddr, arg0->data, arg0->unpacked_size);
    }
}

void func_80026C38(void) {
    u32 i, j;
    u32 s3;

    s3 = 0;
    for (i = 0; i < D_80051F40; i++) {
        if (D_80138A00[i].flags & 1) {
            for (j = i + 1; j < D_80051F40; j++) {
                if (!(D_80138A00[j].flags & 1)) {
                    break;
                }
            }

            if (j != D_80051F40) {
                D_80138A00[i].data = D_80138A00[j].data;
                D_80138A00[i].unk_04 = D_80138A00[j].unk_04;
                D_80138A00[i].size = D_80138A00[j].size;
                D_80138A00[i].unpacked_size = D_80138A00[j].unpacked_size;
                D_80138A00[i].type = D_80138A00[j].type;
                D_80138A00[i].flags = D_80138A00[j].flags;
                D_80138A00[i].unk_08 = D_80138A00[j].unk_08;
                D_80138A00[i].unk_0C = D_80138A00[j].unk_0C;
                D_80138A00[i].unk_30 = D_80138A00[j].unk_30;
                str_copy(D_80138A00[i].name, D_80138A00[j].name);
                D_80138A00[j].name[0] = '\0';
                D_80138A00[j].unk_0C = -1;
                D_80138A00[j].unk_08 = -1;
                D_80138A00[j].flags = 1;
                s3++;
            } else {
                D_80138A00[i].name[0] = '\0';
                D_80138A00[i].unk_0C = -1;
                D_80138A00[i].unk_08 = -1;
                D_80138A00[i].flags = 1;
                D_80051F40 = s3;
                return;
            }
        } else {
            s3++;
        }
    }

    D_80051F40 = s3;
    for (i = 0; i < D_80051F40; i++) {}
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
