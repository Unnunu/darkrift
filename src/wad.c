#include "common.h"
#include "string.h"
#include "ld_addrs.h"

typedef struct UnkEpsilon {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} UnkEpsilon; // size >= 0x1C

typedef struct UnkZeta {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char unk_18[0xC];
} UnkZeta; // size = 0x24

typedef struct WadFile {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ char pad1[4];
    /* 0x08 */ UnkEpsilon data[1];
} WadFile;

extern u32 D_80051F40;

extern s32 D_8013C200;
extern WadFile* D_8013C204;
extern s32 D_8013C208;
extern u8* D_8013C20C;
extern UnkEpsilon* D_8013C210;
extern s32 D_8013C214;
extern s32 D_8013C218;
extern u32 D_8013C21C;
extern u32 D_8013C220;

void dma_read(s32 romAddr, void* vramAddr, s32 size);

void func_80025B40(void) {
    s32 i;

    for (i = 0; i < D_80051F40; i++) {

    }
}

void func_80025B68(char* arg0, char* arg1) {
    u32 size1 = strlen(arg0);
    u32 size2 = strlen(arg1);
    s32 i;

    for (i = 0; i < size2; i++) {
        arg0[size1 + i] = *arg1++;
    }

    arg0[size1 + size2] = 0;
}

void func_80025BE0(char* arg0, char* arg1) {
    u32 size = strlen(arg1);
    s32 i;

    for (i = 0; i < size; i++) {
        *arg0++ = *arg1++;
    }

    *arg0 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80025C40.s")
s32 func_80025C40(UnkZeta*, char*);

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80025D54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80025DB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80025E6C.s")

void func_80025EDC(s32 arg0, s32 arg1) {
    D_8013C200 = arg0;
    D_8013C204 = D_8013C200;
    D_8013C208 = D_8013C200 + 0x2800;
    D_8013C214 = D_8013C208 - arg0;
    D_8013C218 = arg1 - D_8013C214;
}

void func_80025F20(char* name) {
    s32 i;
    char fullname[20];
    UnkZeta* sp2C;
    UnkZeta* ptr;
    
    sp2C = D_8013C210->unk_14 + (u8*)D_8013C204;
    func_80025BE0(fullname, name);
    func_80025B68(fullname, ".WAD");
    
    for (i = 0, ptr = sp2C; i < D_8013C21C; i++, ptr++) {
        if (func_80025C40(ptr, fullname) == 0) {
            D_8013C20C += ptr->unk_14;
            return;
        }
        if (ptr && ptr) {
            // FAKE MATCH
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80025FEC.s")

s32 func_80025FEC(void);

void func_800260AC(char* name) {
    if (name[0] == 0) {
        D_8013C20C = resources_ROM_START;
        dma_read(D_8013C20C, D_8013C204, D_8013C214);
        D_8013C210 = D_8013C204->data;
        D_8013C220 = D_8013C204->unk_00;
        D_8013C21C = D_8013C210->unk_18;
        return;
    }
    if (func_80025FEC() == 0) {
        func_80025F20(name);
        dma_read(D_8013C20C, D_8013C204, D_8013C214);
        D_8013C210 = D_8013C204->data;
        D_8013C220 = D_8013C204->unk_00;
        D_8013C21C = D_8013C210->unk_18;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026198.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800262B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_8002630C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800263A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80026418.s")

#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_800264B4.s")

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
