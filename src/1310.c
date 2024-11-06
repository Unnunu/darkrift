#include "common.h"

typedef struct UnkAlpha {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ struct UnkAlpha* unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x0C */ s32 unk_10;
} UnkAlpha; // size >= 0x10

typedef struct UnkBeta {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ struct UnkBeta* unk_08;
    /* 0x0C */ struct UnkBeta* unk_0C;
} UnkBeta; // size >= 0x10

typedef struct UnkGamma {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkGamma; // size = 0x10

s32 func_80000A60(UnkAlpha* arg0);
void func_80000A8C(UnkBeta* arg0, UnkBeta** arg1);

extern UnkAlpha* D_80049280;
extern UnkAlpha* D_80049284;

extern OSMesgQueue D_8005ADF8;

extern OSIoMesg D_8005AE90;
extern s32 D_8005AEB0;
extern s32 D_8005AEB4;
extern UnkGamma D_8005AEB8[];
extern UnkAlpha* D_8005BEC0;

void func_80000710(s32 arg0, s32 arg1) {
    s32 i, j;

    for (i = 0; i != arg1; i++) {
        for (j = 2; j < 10; j += 4) {
            // do nothing
        }
    }
}

void func_80000744(void) {
    D_80049280 = D_8005BEC0;
    
    D_80049280->unk_04 = ((u32)(D_8005BEC0) + 0x23E806) & ~7;
    D_80049280->unk_00 = 1;
    D_80049280->unk_08 = 0;
    D_80049280->unk_0C = 0;
    D_8005AEB0 = 0;
    D_80049280->unk_10 = 0xABCD6789;

    D_8005AEB4 = func_80000A60(D_80049280);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_800007C8.s")

void func_800009D8(UnkAlpha* arg0, s32 arg1) {
    arg0->unk_04 = arg1;
    arg0->unk_00 = 1;
    arg0->unk_08 = 0;
    arg0->unk_0C = 0;
    arg0->unk_10 = 0xABCD6789;
    func_80000A8C(arg0, &D_80049280);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000A1C.s")
/*
s32 func_80000A1C(void) {
    UnkAlpha* ptr;
    s32 ret = TRUE;
    
    for (ptr = D_80049284; ptr != NULL; ptr = ptr->unk_08) {
        if (ptr->unk_10 != 0xABCD6789) {
            ret = FALSE;
            break;
        }
    }

    return ret;
}
*/

s32 func_80000A60(UnkAlpha* arg0) {
    s32 v1 = 0;

    while (arg0 != NULL) {
        v1 += arg0->unk_04 - (u32)arg0;
        arg0 = arg0->unk_08;
        v1 -= 0x18;
    }

    return v1;
}

void func_80000A8C(UnkBeta* arg0, UnkBeta** arg1) {
    arg0->unk_08 = *arg1;
    if (arg0->unk_08 != NULL) {
        arg0->unk_08->unk_0C = arg0;
    }
    *arg1 = arg0;
    arg0->unk_0C = NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000AA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000B30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000BD8.s")
s32 func_80000BD8(s32);

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000D88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000E0C.s")
void func_80000E0C(u8* arg0, u8 arg1, u32 arg2);
#if 0
void func_80000E0C(u8* arg0, u8 arg1, u32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        arg0[i] = arg1;
    }
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000E40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1310/func_80000EA8.s")

void func_80000F70(s32 arg0) {
    func_80000D88(D_8005AEB8[arg0].unk_04);
    D_8005AEB8[arg0].unk_00 = 1;
    D_8005AEB8[arg0].unk_0C = 0;
}

void dmaRead(s32 romAddr, void* vramAddr, s32 size) {
    osWritebackDCacheAll();
    while (osRecvMesg(&D_8005ADF8, 0, 0) != -1) { }
    osPiStartDma(&D_8005AE90, 0, OS_READ, romAddr, vramAddr, size, &D_8005ADF8);
    osRecvMesg(&D_8005ADF8, 0, 1);
    osInvalDCache(0, 0x3FFFFF);
}

void func_80001068(s32 romAddr, void* vramAddr, s32 size) {
    osWritebackDCacheAll();
    osPiStartDma(&D_8005AE90, 0, OS_READ, romAddr, vramAddr, size, &D_8005ADF8);
    osInvalDCache(0, 0x3FFFFF);
}

void func_800010D4(s32 arg0, s32 arg1, s32 arg2) {
    D_8005AEB8[arg0].unk_0C = arg1;
    D_8005AEB8[arg0].unk_08 = arg2;
}

s32 func_800010F0(s32 arg0, s32 arg1, s32 arg2) {
    return func_80000BD8(arg0);
}
