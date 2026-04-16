#include "common.h"
#include "PR/gt.h"

extern Matrix4f D_80049A94;

extern Gfx D_80081280[];

void func_80010B00(PlayerSub6Sub4 *arg0, s32 arg1) {
    arg0->unk_40 = 0;
    arg0->unk_44 = 0;
    arg0->unk_48 = arg1;
    arg0->unk_4C = 0;
}

void func_80010B14(PlayerSub6Sub4 *arg0, Vec4i *arg1) {
    s32 v0;

    v0 = arg0->unk_44;

    if (arg0->unk_4C != 0 && arg0->unk_40 == v0) {
        arg0->unk_40++;
        arg0->unk_40 &= arg0->unk_48;
    } else {
        arg0->unk_4C++;
    }

    arg0->unk_00[v0].x = arg1->x;
    arg0->unk_00[v0].y = arg1->y;
    arg0->unk_00[v0].z = arg1->z;

    v0++;
    v0 &= arg0->unk_48;
    arg0->unk_44 = v0;
}

s32 func_80010B84(PlayerSub6Sub4 *arg0, Vec4i **arg1) {
    s32 v1;

    v1 = arg0->unk_40;
    if (arg0->unk_4C == 0) {
        v1--;
        if (v1 < 0) {
            v1 = 3;
        }
        *arg1 = &arg0->unk_00[v1 - 1];
        return 0;
    } else {
        *arg1 = &arg0->unk_00[v1];
        v1++;
        v1 &= arg0->unk_48;
        arg0->unk_40 = v1;
        arg0->unk_4C--;
    }
}

void func_80010BE4(PlayerSub6Sub1 *arg0) {
    func_80010B00(&arg0->unk_00, 3);
    func_80010B00(&arg0->unk_50, 3);
}

s32 func_80010C18(PlayerSub6Sub1 *arg0) {
    Matrix4f *A0;
    Vec4i *sp30;
    Vec4i *sp2C;
    Vec4i *sp28;
    Vec4i *sp24;

    A0 = &arg0->unk_A0;

    if (arg0->unk_00.unk_4C != 4) {
        return FALSE;
    }

    func_80010B84(&arg0->unk_00, &sp30);
    func_80010B84(&arg0->unk_00, &sp2C);
    func_80010B84(&arg0->unk_00, &sp28);
    func_80010B84(&arg0->unk_00, &sp24);

    A0->x.x = D_80049A94.x.x * sp30->x + D_80049A94.x.y * sp2C->x + D_80049A94.x.z * sp28->x + D_80049A94.x.w * sp24->x;
    A0->y.x = D_80049A94.y.x * sp30->x + D_80049A94.y.y * sp2C->x + D_80049A94.y.z * sp28->x + D_80049A94.y.w * sp24->x;
    A0->z.x = D_80049A94.z.x * sp30->x + D_80049A94.z.y * sp2C->x + D_80049A94.z.z * sp28->x + D_80049A94.z.w * sp24->x;
    A0->w.x = D_80049A94.w.x * sp30->x + D_80049A94.w.y * sp2C->x + D_80049A94.w.z * sp28->x + D_80049A94.w.w * sp24->x;

    A0->x.y = D_80049A94.x.x * sp30->y + D_80049A94.x.y * sp2C->y + D_80049A94.x.z * sp28->y + D_80049A94.x.w * sp24->y;
    A0->y.y = D_80049A94.y.x * sp30->y + D_80049A94.y.y * sp2C->y + D_80049A94.y.z * sp28->y + D_80049A94.y.w * sp24->y;
    A0->z.y = D_80049A94.z.x * sp30->y + D_80049A94.z.y * sp2C->y + D_80049A94.z.z * sp28->y + D_80049A94.z.w * sp24->y;
    A0->w.y = D_80049A94.w.x * sp30->y + D_80049A94.w.y * sp2C->y + D_80049A94.w.z * sp28->y + D_80049A94.w.w * sp24->y;

    A0->x.z = D_80049A94.x.x * sp30->z + D_80049A94.x.y * sp2C->z + D_80049A94.x.z * sp28->z + D_80049A94.x.w * sp24->z;
    A0->y.z = D_80049A94.y.x * sp30->z + D_80049A94.y.y * sp2C->z + D_80049A94.y.z * sp28->z + D_80049A94.y.w * sp24->z;
    A0->z.z = D_80049A94.z.x * sp30->z + D_80049A94.z.y * sp2C->z + D_80049A94.z.z * sp28->z + D_80049A94.z.w * sp24->z;
    A0->w.z = D_80049A94.w.x * sp30->z + D_80049A94.w.y * sp2C->z + D_80049A94.w.z * sp28->z + D_80049A94.w.w * sp24->z;

    func_80010B14(&arg0->unk_00, sp2C);
    func_80010B14(&arg0->unk_00, sp28);
    func_80010B14(&arg0->unk_00, sp24);

    return TRUE;
}

void func_80011258(PlayerSub6Sub1 *arg0, Vec4i *arg1) {
    f32 fs0, fs1, fs2;
    f32 fs3, fs4, fs5;
    s32 i;
    f32 spB0, spAC, spA8;
    f32 spA4, spA0, sp9C;
    Vec4i sp8C;
    Matrix4f *A0;

    A0 = &arg0->unk_A0;

    func_80010B14(arg0, arg1);

    if (func_80010C18(arg0)) {
        fs0 = 0.015625f * A0->x.x + 0.0625f * A0->y.x + 0.25f * A0->z.x;
        fs1 = 0.015625f * A0->x.y + 0.0625f * A0->y.y + 0.25f * A0->z.y;
        fs2 = 0.015625f * A0->x.z + 0.0625f * A0->y.z + 0.25f * A0->z.z;

        spB0 = 0.09375f * A0->x.x;
        spAC = 0.09375f * A0->x.y;
        spA8 = 0.09375f * A0->x.z;

        fs3 = spB0 + 0.125f * A0->y.x;
        fs4 = spAC + 0.125f * A0->y.y;
        fs5 = spA8 + 0.125f * A0->y.z;
        spA4 = A0->w.x;
        spA0 = A0->w.y;
        sp9C = A0->w.z;

        for (i = 0; i < 4; i++) {
            spA4 += fs0;
            spA0 += fs1;
            sp9C += fs2;

            sp8C.x = spA4;
            sp8C.y = spA0;
            sp8C.z = sp9C;

            fs0 += fs3;
            fs1 += fs4;
            fs2 += fs5;

            fs3 += spB0;
            fs4 += spAC;
            fs5 += spA8;

            func_80010B14(&arg0->unk_50, &sp8C);
        }
    }
}

void func_800114BC(PlayerSub6Sub1 *arg0, Vec4i **arg1) {
    func_80010B84(&arg0->unk_50, arg1);
}

void func_800114DC(BatchInfo *batch) {
    batch->header.triMask = 0x200;
    batch->header.unk_0B = 1;
    batch->header.unk_04 = 0;
    batch->header.vtxNum = 10;
    batch->header.vtxOffset = 0;
    batch->header.numTriangles = 8;
    batch->header.texGfx = NULL;

    gtStateSetOthermode(&batch->header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&batch->header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&batch->header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);
}

#pragma GLOBAL_ASM("asm/nonmatchings/11700/func_800115A0.s")

#ifdef NON_EQUIVALENT
void func_80012150(PlayerSub6 *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4,
                   ColorRGBA *arg5) {
    u32 i, j;
    Gfx *gfx;
    u32 a;
    PlayerSub6Sub2 *s6;
    BatchInfo *bi;

    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->unk_08 = arg3;

    func_80010BE4(&arg0->unk_0C);
    func_80010BE4(&arg0->unk_EC);

    arg0->unk_1CC = 0;
    arg0->unk_1D0 = 0;
    arg0->unk_1450 = arg4;

    gfx = D_80081280;
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
    gSPNoOp(gfx++);

    for (i = 0, bi = arg0->unk_12D8; i < 4; i++, bi++) {
        func_800114DC(bi);
        bi->header.texGfx = D_80081280;
        bi->header.unk_0B = 0;
    }

    for (i = 0; i < 16; i++) {
        s6 = &arg0->unk_1D8[i];
        func_800114DC(&s6->unk_00);
        mem_fill(s6->unk_58, 0, sizeof(s6->unk_58));

        if (i == 0) {
            a = 200;
            for (j = 0; j < 4; j++) {
                s6->unk_58[j].unk_00.r = arg5->r;
                s6->unk_58[j].unk_00.g = arg5->g;
                s6->unk_58[j].unk_00.b = arg5->b;
                s6->unk_58[j].unk_00.a = a;
                s6->unk_58[j].unk_04.r = arg5->r;
                s6->unk_58[j].unk_04.g = arg5->g;
                s6->unk_58[j].unk_04.b = arg5->b;
                s6->unk_58[j].unk_04.a = a;
                a += 4;
            }
        } else {
            a = 204;
            for (j = 0; j < 4; j++) {
                s6->unk_58[j].unk_00.r = arg5->r;
                s6->unk_58[j].unk_00.g = arg5->g;
                s6->unk_58[j].unk_00.b = arg5->b;
                s6->unk_58[j].unk_00.a = a;
                s6->unk_58[j].unk_04.r = arg5->r;
                s6->unk_58[j].unk_04.g = arg5->g;
                s6->unk_58[j].unk_04.b = arg5->b;
                s6->unk_58[j].unk_04.a = a;
                a += 4;
                if (a > 255) {
                    a = 255;
                }
            }
        }

        s6->unk_F8 = -1;
    }

    arg0->unk_1438 = arg0->unk_143C = arg0->unk_1440 = 0.0f;
    arg0->unk_1444 = arg0->unk_1448 = arg0->unk_144C = 0.0f;

    arg0->unk_1454.r = arg5->r;
    arg0->unk_1454.g = arg5->g;
    arg0->unk_1454.b = arg5->b;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/11700/func_80012150.s")
#endif
