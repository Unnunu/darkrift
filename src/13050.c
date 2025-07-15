#include "common.h"

typedef struct UnkMu {
    /* 0x00 */ Mtx unk_00;
    /* 0x40 */ Mtx unk_40;
    /* 0x80 */ struct UnkMu *unk_80;
    /* 0x84 */ struct UnkMu *unk_84;
    /* 0x88 */ struct UnkMu *unk_88;
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ s32 unk_90;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ MtxF unk_98;
    /* 0xD8 */ MtxF unk_D8;
} UnkMu; // size >= 0x118

extern f32 D_80050F14[]; // sin table

void func_80012AA8(MtxF mf);
void func_80012B34(Mtx *m);

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012450.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012518.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012854.s")

#ifdef NON_MATCHING
f32 func_80012978(s16 arg0) {
    s32 v0;

    v0 = arg0 & 0xFFF;

    if (v0 < 0x400) {
        return D_80050F14[v0];
    }
    if (v0 < 0x800) {
        return -D_80050F14[0x800 - v0];
    }

    arg0 = v0 - 0x800;

    v0 = arg0 & 0xFFFF;
    if (v0 < 0x400) {
        return -D_80050F14[v0];
    }
    if (v0 < 0x1000) {
        return D_80050F14[0x800 - v0];
    }

    v0 = arg0 & 0xFFFF; // @fake
    return 0.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012978.s")
f32 func_80012978(s16 arg0);
#endif

void func_80012A20(UnkMu *arg0, UnkMu *arg1, s32 arg2, s32 arg3) {
    func_80012B34(&arg1->unk_00);
    func_80012B34(&arg1->unk_40);
    func_80012AA8(arg1->unk_98);
    func_80012AA8(arg1->unk_D8);

    arg1->unk_90 = arg3;
    arg1->unk_8C = arg2;

    if (arg0 != NULL) {
        UnkMu *temp = arg0->unk_80;
        arg0->unk_80 = arg1;

        arg1->unk_80 = NULL;
        arg1->unk_84 = temp;
    } else {
        arg1->unk_80 = NULL;
        arg1->unk_84 = NULL;
    }

    arg1->unk_88 = arg0;
}

#ifdef NON_MATCHING
void func_80012AA8(MtxF mf) {
    mf[0][1] = 0;
    mf[0][2] = 0;
    mf[0][3] = 0;
    mf[1][0] = 0;
    mf[1][2] = 0;
    mf[1][3] = 0;
    mf[2][0] = 0;
    mf[2][1] = 0;
    mf[2][3] = 0;
    mf[3][0] = 0;
    mf[3][1] = 0;
    mf[3][2] = 0;

    mf[0][0] = mf[1][1] = mf[2][2] = mf[3][3] = 1.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012AA8.s")
void func_80012AA8(float mf[4][4]);
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012AF4.s")

void func_80012B34(Mtx *m) {
    m->m[0][1] = 0;
    m->m[0][3] = 0;
    m->m[1][0] = 0;
    m->m[1][2] = 0;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = 0;
    m->m[2][3] = 0;
    m->m[3][0] = 0;
    m->m[3][1] = 0;
    m->m[3][2] = 0;
    m->m[3][3] = 0;

    m->m[0][0] = FTOFIX32(1);
    m->m[0][2] = FTOFIX32(1) >> 16;
    m->m[1][1] = FTOFIX32(1);
    m->m[1][3] = FTOFIX32(1) >> 16;
}

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012B80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012BBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012E58.s")

//!
#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_8001305C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800134B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800136B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800136CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_8001370C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_8001386C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800139A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80013A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80013D08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80013D14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80013E64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800140A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80014110.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_8001417C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80014204.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80014464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800146B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80014718.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80014974.s")

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800149F0.s")
