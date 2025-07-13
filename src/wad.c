#include "common.h"
#include "ld_addrs.h"
#include "string.h"

typedef struct WadStructAlpha {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} WadStructAlpha; // size >= 0x20

typedef struct WadStructBeta {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} WadStructBeta; // size = 0x24

typedef struct WadFile {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ char pad1[4];
    /* 0x08 */ WadStructAlpha data[1];
} WadFile;

extern s32 D_80051F40;

extern WadStructGamma D_80138A00[256];
extern s32 D_8013C200;
extern WadFile *D_8013C204;
extern s32 D_8013C208;
extern u8 *D_8013C20C;
extern WadStructAlpha *D_8013C210;
extern s32 D_8013C214;
extern s32 D_8013C218;
extern u32 D_8013C21C;
extern u32 D_8013C220;

void func_800264B4(s32);
void func_80026C38(void);
void dma_read(s32 romAddr, void *vramAddr, s32 size);
void func_80000E0C(u8 *arg0, u8 arg1, u32 arg2);

void func_80026B74(WadStructGamma *);
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

void func_80025B68(char *arg0, char *arg1) {
    u32 size1 = strlen(arg0);
    u32 size2 = strlen(arg1);
    s32 i;

    for (i = 0; i < size2; i++) {
        arg0[size1 + i] = *arg1++;
    }

    arg0[size1 + size2] = 0;
}

void func_80025BE0(char *arg0, char *arg1) {
    u32 size = strlen(arg1);
    s32 i;

    for (i = 0; i < size; i++) {
        *arg0++ = *arg1++;
    }

    *arg0 = 0;
}

s32 func_80025C40(char *arg0, char *arg1) {
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

void toupper(char *str) {
    u32 size = strlen(str);
    u32 i;

    for (i = 0; i < size; i++) {
        str[i] = (str[i] >= 'a') ? str[i] -= 'a' - 'A' : str[i];
    }
}

u32 func_80025DB4(char *arg0, s32 arg1) {
    u32 i;

    toupper(arg0);
    for (i = 0; i < D_80051F40; i++) {
        if (func_80025C40(arg0, D_80138A00[i].unk_10) == 0 && arg1 == D_80138A00[i].unk_30) {
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
        D_80138A00[i].unk_2E = 1;
        D_80138A00[i].unk_10[0] = '\0';
    }
}

void func_80025EDC(s32 arg0, s32 arg1) {
    D_8013C200 = arg0;
    D_8013C204 = D_8013C200;
    D_8013C208 = D_8013C200 + 0x2800;
    D_8013C214 = D_8013C208 - arg0;
    D_8013C218 = arg1 - D_8013C214;
}

void func_80025F20(char *name) {
    s32 i;
    char fullname[20];
    WadStructBeta *sp2C;
    WadStructBeta *ptr;

    sp2C = D_8013C210->unk_14 + (u8 *) D_8013C204;
    func_80025BE0(fullname, name);
    func_80025B68(fullname, ".WAD");

    for (i = 0, ptr = sp2C; i < D_8013C21C; i++, ptr++) {
        if (func_80025C40(ptr->unk_00, fullname) == 0) {
            D_8013C20C += ptr->unk_14;
            return;
        }
        if (ptr && ptr) {
            // FAKE MATCH
        }
    }
}

s32 func_80025FEC(char *arg0) {
    s32 pad;
    u32 i;
    WadStructAlpha *entries;

    entries = D_8013C204->data;
    for (i = 0; i < D_8013C220; i++) {
        if (func_80025C40(arg0, entries[i].unk_00) == 0) {
            D_8013C210 = &entries[i];
            D_8013C220 = 1;
            D_8013C21C = entries[i].unk_18;
            return 1;
        }
    }

    return 0;
}

void func_800260AC(char *name) {
    if (name[0] == 0) {
        D_8013C20C = resources_ROM_START;
        dma_read(D_8013C20C, D_8013C204, D_8013C214);
        D_8013C210 = D_8013C204->data;
        D_8013C220 = D_8013C204->unk_00;
        D_8013C21C = D_8013C210->unk_18;
    } else if (!func_80025FEC(name)) {
        func_80025F20(name);
        dma_read(D_8013C20C, D_8013C204, D_8013C214);
        D_8013C210 = D_8013C204->data;
        D_8013C220 = D_8013C204->unk_00;
        D_8013C21C = D_8013C210->unk_18;
    }
}

void func_80026198(char *name) {
    s32 len;
    char sp44[24];
    u32 i;
    u32 j;

    len = strlen(name);
    j = 0;
    toupper(name);
    sp44[0] = '\0';

    for (i = 0; i < len; i++) {
        if (name[i] != '/') {
            sp44[j++] = name[i];
        } else {
            sp44[j] = '\0';
            j = 0;
            func_800260AC(sp44);
        }
    }

    sp44[j] = '\0';
    func_800260AC(sp44);
}

void func_80026250(void) {
    u32 i;

    for (i = 0; i < D_80051F40; i++) {
        if (D_80138A00[i].unk_08 >= 0) {
            D_80138A00[i].unk_00 = D_8005AEB8[D_80138A00[i].unk_08].unk_04;
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
        if (arg0 == D_80138A00[i].unk_2C) {
            func_80026B74(D_80138A00 + i);
        }
    }

    func_80026C38();
}

void func_800264B4(s32 arg0) {
    s32 pad[2];
    u32 i;
    u32 sp30;
    WadStructBeta *s3;
    s32 v0;

    sp30 = get_free_mem(sFreeChunksList);
    s3 = (WadStructBeta *) ((u8 *) D_8013C204 + D_8013C210->unk_14);

    for (i = 0; i < D_8013C21C; i++) {
        v0 = func_80025DB4(s3[i].unk_00, arg0);

        if (v0 >= 0) {
            switch (s3[i].unk_18) {
                case 3:
                    func_80027680(D_80138A00 + v0);
                    break;
                case 8:
                    func_800276F0(D_80138A00 + v0);
                    break;
                case 7:
                    func_80027918(D_80138A00 + v0);
                    break;
                case 2:
                    func_80026EEC(D_80138A00 + v0);
                    break;
                case 11:
                    func_800279E4(D_80138A00 + v0);
                    break;
                case 9:
                    func_80027A14(D_80138A00 + v0);
                    break;
                case 14:
                    func_80027C0C(D_80138A00 + v0);
                    break;
                case 12:
                    func_80027DA4(D_80138A00 + v0);
                    break;
                case 15:
                    func_80027EFC(D_80138A00 + v0);
                    break;
                case 20:
                    func_80027780(D_80138A00 + v0);
                    break;
                case 21:
                    func_80027804(D_80138A00 + v0);
                    break;
                case 22:
                    func_80027888(D_80138A00 + v0);
                    break;
            }
        } else if (s3[i].unk_20 <= sp30) {
            func_80025BE0(D_80138A00[D_80051F40].unk_10, s3[i].unk_00);
            D_80138A00[D_80051F40].unk_24 = s3[i].unk_1C;
            D_80138A00[D_80051F40].unk_30 = arg0;
            D_80138A00[D_80051F40].unk_2C = s3[i].unk_18;
            D_80138A00[D_80051F40].unk_34 = D_8013C20C + s3[i].unk_14;
            D_80138A00[D_80051F40].unk_28 = s3[i].unk_20;

            if (s3[i].unk_1C != s3[i].unk_20) {
                D_80138A00[D_80051F40].unk_2E = 2;
                D_80051F40++;
            } else {
                D_80138A00[D_80051F40].unk_2E = 0;
                D_80051F40++;
            }

            switch (s3[i].unk_18) {
                case 0:
                    func_80026DF0(D_80138A00 + D_80051F40 - 1);
                    break;
                case 1:
                    func_80026ECC(D_80138A00 + D_80051F40 - 1);
                    break;
                case 2:
                    func_80027054(D_80138A00 + D_80051F40 - 1);
                    break;
                case 3:
                    func_800271C0(D_80138A00 + D_80051F40 - 1);
                    break;
                case 7:
                    func_80027270(D_80138A00 + D_80051F40 - 1);
                    break;
                case 8:
                    func_800275A4(D_80138A00 + D_80051F40 - 1);
                    break;
                case 10:
                    func_80027988(D_80138A00 + D_80051F40 - 1);
                    break;
                case 9:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    func_80027A14(D_80138A00 + D_80051F40 - 1);
                    break;
                case 11:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    func_800279E4(D_80138A00 + D_80051F40 - 1);
                    break;
                case 12:
                    func_80027CAC(D_80138A00 + D_80051F40 - 1);
                    break;
                case 13:
                    func_80027B7C(D_80138A00 + D_80051F40 - 1);
                    break;
                case 14:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    func_80027C0C(D_80138A00 + D_80051F40 - 1);
                    break;
                case 15:
                    func_80027E20(D_80138A00 + D_80051F40 - 1);
                    break;
                case 16:
                    func_80027F8C(D_80138A00 + D_80051F40 - 1);
                    break;
                case 17:
                    func_80027D84(D_80138A00 + D_80051F40 - 1);
                    break;
                case 18:
                    func_80027FCC(D_80138A00 + D_80051F40 - 1);
                    break;
                case 19:
                    func_80027B10(D_80138A00 + D_80051F40 - 1);
                    break;
                case 20:
                    func_80027320(D_80138A00 + D_80051F40 - 1);
                    break;
                case 21:
                    func_800273F4(D_80138A00 + D_80051F40 - 1);
                    break;
                case 22:
                    func_800274C8(D_80138A00 + D_80051F40 - 1);
                    break;
                default:
                    func_80026BE0(D_80138A00 + D_80051F40 - 1);
                    break;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026A94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026AD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026B04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026B34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026B74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026C38.s")

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
