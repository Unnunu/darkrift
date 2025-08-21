#include "common.h"
#include "camera.h"

typedef struct PclAsset {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} PclAsset;

Gfx **D_80049CF0 = NULL;

Vec4i D_800814E0[8];
Vec4i D_80081560[8];
s16 D_800815E0;
s16 D_800815E2;
s16 D_800815E4;
s16 D_800815E6;
s16 D_800815E8;
s16 D_800815EA;
s16 D_800815EC;
s16 D_800815EE;
s16 D_800815F0;
s16 D_800815F2;
s16 D_800815F4;
s16 D_800815F6;
s16 D_800815F8;
s16 D_800815FA;
s16 D_800815FC;
s16 D_800815FE;
s16 D_80081600;
s16 D_80081602;
s16 D_80081604;
s16 D_80081606;
s16 D_80081608;
UnkFrodo *D_8008160C;
u16 *D_80081610;
Mtx D_80081618;

#ifdef NON_EQUIVALENT
void func_8001AAE0(void) {
    Vec3s sp90;
    s32 sp84;
    s32 t1;
    s32 t5;
    s16 dx, dy, dz;
    s16 dxAbs, dyAbs, dzAbs;
    s16 i;
    s32 x1, y1, z1;
    s32 x2, y2, z2;

    dx = gCameraTarget.x - gCamera->pos.x;
    dy = gCameraTarget.y - gCamera->pos.y;
    dz = gCameraTarget.z - gCamera->pos.z;

    dxAbs = ABS(dx);
    dzAbs = ABS(dz);
    dyAbs = ABS(dy);
    sp84 = DISTANCE(dxAbs, dzAbs);
    t1 = -DISTANCE(sp84, dyAbs);
    t5 = 7500 - t1;

    x1 = ((gScreenWidth * (D_8013C588 + 1000) / D_8013C588) >> 1);
    D_800814E0[0].x = x1;
    D_800814E0[1].x = -x1;
    D_800814E0[2].x = x1;
    D_800814E0[3].x = -x1;

    y1 = D_8013C588 + 1000 + t1;
    D_800814E0[0].y = y1;
    D_800814E0[1].y = y1;
    D_800814E0[2].y = y1;
    D_800814E0[3].y = y1;

    z1 = ((gScreenHeight * (D_8013C588 + 1000) / D_8013C588) >> 1);
    D_800814E0[0].z = z1;
    D_800814E0[1].z = z1;
    D_800814E0[2].z = -z1;
    D_800814E0[3].z = -z1;

    x2 = ((gScreenWidth * t5 / D_8013C588) >> 1);
    y2 = 7500;
    z2 = ((gScreenHeight * t5 / D_8013C588) >> 1);

    D_800814E0[4].x = x2;
    D_800814E0[4].y = y2;
    D_800814E0[4].z = z2;

    D_800814E0[5].x = -x2;
    D_800814E0[5].y = y2;
    D_800814E0[5].z = z2;

    D_800814E0[6].x = -x2;
    D_800814E0[6].y = y2;
    D_800814E0[6].z = -z2;

    D_800814E0[7].x = x2;
    D_800814E0[7].y = y2;
    D_800814E0[7].z = -z2;

    sp90.x = func_80012518(sp84, dy);
    sp90.y = func_80012518(dx, dz);
    sp90.z = 0;

    math_rotate(&D_800813E0, &sp90);
    func_8001386C(&D_800814E0[0], &D_80081560[0], &D_800813E0);
    func_8001386C(&D_800814E0[1], &D_80081560[1], &D_800813E0);
    func_8001386C(&D_800814E0[2], &D_80081560[2], &D_800813E0);
    func_8001386C(&D_800814E0[3], &D_80081560[3], &D_800813E0);
    func_8001386C(&D_800814E0[4], &D_80081560[4], &D_800813E0);
    func_8001386C(&D_800814E0[5], &D_80081560[5], &D_800813E0);
    func_8001386C(&D_800814E0[6], &D_80081560[6], &D_800813E0);
    func_8001386C(&D_800814E0[7], &D_80081560[7], &D_800813E0);

    D_80081560[0].x += gCameraTarget.x;
    D_80081560[0].z += gCameraTarget.z;
    D_800815E2 = D_800815E0 = D_80081560[0].x;
    D_800815E6 = D_800815E4 = D_80081560[0].z;

    for (i = 1; i < 8; i++) {
        D_80081560[i].x += gCameraTarget.x;
        D_80081560[i].y += gCameraTarget.y;
        D_80081560[i].z += gCameraTarget.z;

        if (D_800815E0 > D_80081560[i].x) {
            D_800815E0 = D_80081560[i].x;
        } else if (D_800815E2 < D_80081560[i].x) {
            D_800815E2 = D_80081560[i].x;
        }

        if (D_800815E4 > D_80081560[i].z) {
            D_800815E4 = D_80081560[i].z;
        } else if (D_800815E6 < D_80081560[i].z) {
            D_800815E6 = D_80081560[i].z;
        }
    }

    if (D_800815E4 < 0) {
        D_80081604 = D_800815F4 - (D_800815E4 - D_800815EE) / D_800815EE;
    } else {
        D_80081604 = D_800815F4 - D_800815E4 / D_800815EE;
    }

    if (D_800815E6 < 0) {
        D_80081602 = D_800815F4 - (D_800815E6 - D_800815EE) / D_800815EE;
    } else {
        D_80081602 = D_800815F4 - D_800815E6 / D_800815EE;
    }

    if (D_800815E0 < 0) {
        D_800815FE = D_800815F2 + (D_800815E0 - D_800815EC) / D_800815EC;
    } else {
        D_800815FE = D_800815F2 + D_800815E0 / D_800815EC;
    }

    if (D_800815E2 < 0) {
        D_80081600 = D_800815F2 + (D_800815E2 - D_800815EC) / D_800815EC;
    } else {
        D_80081600 = D_800815F2 + D_800815E2 / D_800815EC;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/gmd_pcl/func_8001AAE0.s")
void func_8001AAE0(void);
#endif

void func_8001B26C(void) {
    s16 i, j;
    s16 v0, a0;

    func_8001AAE0();

    gDPLoadTLUT_pal16(gMainGfxPos++, 0, VIRTUAL_TO_PHYSICAL(D_80081610));
    gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&D_80081618), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    for (i = D_80081602 - 1; i < D_80081604 + 1; i++) {
        for (j = D_800815FE; j < D_80081600 + 1; j++) {
            if (j >= 0) {
                a0 = j % D_800815E8;
            } else {
                a0 = j % D_800815E8;
                if (a0 != 0) {
                    a0 += D_800815E8;
                }
            }

            if (i >= 0) {
                v0 = i % D_800815EA;
            } else {
                v0 = i % D_800815EA;
                if (v0 != 0) {
                    v0 += D_800815EA;
                }
            }

            gSPDisplayList(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(D_80049CF0[v0 * D_800815E8 + a0]));
        }
    }
}

void func_8001B5B0(char *name, s32 arg1) {
    PclAsset *sp74;
    AssetGmdSub2 *sub2;
    char sp5C[20];
    char sp48[20];
    Vec3s sp40;
    s32 unused;
    AssetGmdSub4 *a3;
    AssetGmdSub1 *sub1;
    Vec4i sp24 = { 0, 0, 6000, 0 };

    str_copy(sp5C, name);
    str_concat(sp5C, ".pcl");
    sp74 = gAssets[asset_find(sp5C, arg1)].data;

    str_copy(sp48, name);
    str_concat(sp48, ".GMD");
    D_8008160C = gAssets[asset_find(sp48, arg1)].aux_data;
    D_80049CF0 = &D_8008160C->sam.unk_154; // TODO: type

    sub2 = D_8008160C->sam.unk_04->unk_04;
    sub1 = sub2->unk_1C;
    a3 = sub1->unk_0C;
    if (a3->unk_08 == 4) {
        D_80081610 = D_8008160C->sam.unk_04->unk_C0 + a3->unk_0C * 0x20; // TODO: type
    } else {
        D_80081610 = D_8008160C->sam.unk_04->unk_C4 + a3->unk_0C * 0x200; // TODO: type
    }

    D_800815E8 = sp74->unk_00;
    D_800815EA = sp74->unk_04;
    D_800815EC = sp74->unk_08;
    D_800815EE = sp74->unk_0C;

    D_800815F0 = D_800815E8 * D_800815EA;
    D_80081606 = D_800815E8 * D_800815EC;
    D_80081608 = D_800815EA * D_800815EE;

    D_800815F2 = D_800815E8 / 2;
    D_800815F4 = D_800815E8 / 2;

    func_80012AA8(&D_800813E0);
    sp40.y = sp40.z = 0;
    sp40.x = -0x400;
    math_rotate(&D_800813E0, &sp40);
    math_mtxf2mtx(&D_80081618, &D_800813E0);
}
