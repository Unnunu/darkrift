#include "common.h"

extern f32 D_80050F14[]; // sin table

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
    func_80012AA8(&arg1->unk_98);
    func_80012AA8(&arg1->unk_D8);

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
void func_80012AA8(Matrix4f *mf) {
    mf->x.y = 0;
    mf->x.z = 0;
    mf->x.w = 0;

    mf->y.x = 0;
    mf->y.z = 0;
    mf->z.w = 0;

    mf->z.x = 0;
    mf->z.y = 0;
    mf->z.w = 0;

    mf->w.x = 0;
    mf->w.y = 0;
    mf->w.z = 0;

    mf->x.x = mf->y.y = mf->z.z = mf->w.w = 1.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_80012AA8.s")
void func_80012AA8(Matrix4f *mf);
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

void func_800134B4(Vec3s *arg0, Mtx *arg1) {
    s32 unused;
    s32 xx, xy, xz, xw, yx, yy, yz, yw, zx, zy, zz, zw;

    func_8001305C(&D_800813E0, arg0);

    xx = FTOFIX32(D_800813E0.x.x);
    xy = FTOFIX32(D_800813E0.x.y);
    xz = FTOFIX32(D_800813E0.x.z);
    xw = FTOFIX32(D_800813E0.x.w);
    yx = FTOFIX32(D_800813E0.y.x);
    yy = FTOFIX32(D_800813E0.y.y);
    yz = FTOFIX32(D_800813E0.y.z);
    yw = FTOFIX32(D_800813E0.y.w);
    zx = FTOFIX32(D_800813E0.z.x);
    zy = FTOFIX32(D_800813E0.z.y);
    zz = FTOFIX32(D_800813E0.z.z);
    zw = FTOFIX32(D_800813E0.z.w);

    arg1->m[0][0] = (xx & 0xFFFF0000) | ((xy >> 16) & 0xFFFF);
    arg1->m[0][1] = (xz & 0xFFFF0000) | ((xw >> 16) & 0xFFFF);
    arg1->m[0][2] = (yx & 0xFFFF0000) | ((yy >> 16) & 0xFFFF);
    arg1->m[0][3] = (yz & 0xFFFF0000) | ((yw >> 16) & 0xFFFF);
    arg1->m[1][0] = (zx & 0xFFFF0000) | ((zy >> 16) & 0xFFFF);
    arg1->m[1][1] = (zz & 0xFFFF0000) | ((zw >> 16) & 0xFFFF);

    arg1->m[2][0] = ((xx & 0xFFFF) << 16) | (xy & 0xFFFF);
    arg1->m[2][1] = ((xz & 0xFFFF) << 16) | (xw & 0xFFFF);
    arg1->m[2][2] = ((yx & 0xFFFF) << 16) | (yy & 0xFFFF);
    arg1->m[2][3] = ((yz & 0xFFFF) << 16) | (yw & 0xFFFF);
    arg1->m[3][0] = ((zx & 0xFFFF) << 16) | (zy & 0xFFFF);
    arg1->m[3][1] = ((zz & 0xFFFF) << 16) | (zw & 0xFFFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/13050/func_800136B0.s")

void func_800136CC(Matrix4f *arg0, Vec4i *arg1) {
    arg0->w.x = arg1->x;
    arg0->w.y = arg1->y;
    arg0->w.z = arg1->z;
}

void func_8001370C(Vec4i *arg0, Vec3s *arg1) {
    f32 x, y, z;
    f64 temp;
    func_8001305C(&D_800813E0, arg1);

    x = D_800813E0.x.x * arg0->x + D_800813E0.y.x * arg0->y + D_800813E0.z.x * arg0->z;
    y = D_800813E0.x.y * arg0->x + D_800813E0.y.y * arg0->y + D_800813E0.z.y * arg0->z;
    z = D_800813E0.x.z * arg0->x + D_800813E0.y.z * arg0->y + D_800813E0.z.z * arg0->z;

    arg0->x = temp = x >= 0.0 ? x + 0.5 : x - 0.5;
    arg0->y = temp = y >= 0.0 ? y + 0.5 : y - 0.5;
    arg0->z = temp = z >= 0.0 ? z + 0.5 : z - 0.5;
}

void func_8001386C(Vec3i *arg0, Vec3i *arg1, Matrix4f *arg2) {
    f32 x, y, z;
    f64 temp;

    x = arg2->x.x * arg0->x + arg2->y.x * arg0->y + arg2->z.x * arg0->z;
    y = arg2->x.y * arg0->x + arg2->y.y * arg0->y + arg2->z.y * arg0->z;
    z = arg2->x.z * arg0->x + arg2->y.z * arg0->y + arg2->z.z * arg0->z;

    arg1->x = temp = x >= 0.0 ? x + 0.5 : x - 0.5;
    arg1->y = temp = y >= 0.0 ? y + 0.5 : y - 0.5;
    arg1->z = temp = z >= 0.0 ? z + 0.5 : z - 0.5;
}

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
