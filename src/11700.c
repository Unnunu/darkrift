#include "common.h"
#include "PR/gt.h"
#include "task.h"
#include "camera.h"

extern s32 D_80049A58[];
extern s32 D_80049A70[];
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
        // @bug UB: should be return 1;
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

s32 func_800114BC(PlayerSub6Sub1 *arg0, Vec4i **arg1) {
    return func_80010B84(&arg0->unk_50, arg1);
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

// #pragma GLOBAL_ASM("asm/nonmatchings/11700/func_800115A0.s")
void func_800115A0(PlayerSub6 *arg0, u8 arg1) {
    Vec4i spF8;
    Vec4i *spF4;
    u8 spF3;
    u8 spF2;
    Matrix4f *s0;
    Matrix4f *v0;
    PlayerSub6Sub2 *s5;
    PlayerSub6Sub2 *s4;
    u32 t2;
    u32 spD8;
    s32 s3;
    Vtx *s2;
    s32 _a2, _a1, _a0, _t4, _t3, _t1, _t0, _a3;
    Vec4i *spAC; // ok
    u32 v1;
    s32 lo1, lo2, lo3, lo4, lo5, lo6, lo7, lo8;
    u32 i;
    u32 j;
    BatchInfo *s03;
    s32 k;
    Vtx *vtx_v0;
    s32 temp1, temp2;
    PlayerSub6Sub2 *sub2;
    f32 temp;
    f32 x;

    v0 = arg0->unk_08;
    s0 = arg0->unk_04;
    spAC = arg0->unk_1450;

    x = v0->w.x;                                                                // @FAKE
    temp = v0->w.x * v0->w.x + v0->w.y * v0->w.y + v0->w.z * v0->w.z + v0->w.z; // @FAKE
    if (temp == 0) {}                                                           // @FAKE
    spF8.x = v0->w.x;
    spF8.y = v0->w.y;
    spF8.z = v0->w.z;
    arg0->unk_1438 = spF8.x;
    arg0->unk_143C = spF8.y;
    arg0->unk_1440 = spF8.z;
    func_80011258(&arg0->unk_0C, &spF8);

    temp = s0->w.x * s0->w.x + s0->w.y * s0->w.y + s0->w.z * s0->w.z + s0->w.z; // @FAKE
    if (temp == 0) {}                                                           // @FAKE
    spF8.x = s0->w.x;
    spF8.y = s0->w.y;
    spF8.z = s0->w.z;
    arg0->unk_1444 = spF8.x;
    arg0->unk_1448 = spF8.y;
    arg0->unk_144C = spF8.z;
    func_80011258(&arg0->unk_EC, &spF8);

    if (!gIsPaused && arg1 && !(D_8005BFC0 & GAME_FLAG_200) && arg0->unk_1D0 < 16) {
        s5 = &arg0->unk_1D8[arg0->unk_1D0];
        s4 = NULL;

        if (arg0->unk_1D0 == 0) {
            s3 = 0;
            s2 = s5->unk_58;
        } else {
            s4 = &arg0->unk_1D8[arg0->unk_1D0 - 1];
            vtx_v0 = s4->unk_58;
            s2 = s5->unk_58;

            if (arg0->unk_1D0 == 1) {
                s2[0].v.ob[0] = vtx_v0[3].v.ob[0];
                s2[0].v.ob[1] = vtx_v0[3].v.ob[1];
                s2[0].v.ob[2] = vtx_v0[3].v.ob[2];
                s2[0].v.cn[3] = 200;

                i = s4->unk_FC - 1;

                s2[1].v.ob[0] = vtx_v0[i].v.ob[0];
                s2[1].v.ob[1] = vtx_v0[i].v.ob[1];
                s2[1].v.ob[2] = vtx_v0[i].v.ob[2];
                s2[1].v.cn[3] = 200;
            } else {
                s2[0].v.ob[0] = vtx_v0[5].v.ob[0];
                s2[0].v.ob[1] = vtx_v0[5].v.ob[1];
                s2[0].v.ob[2] = vtx_v0[5].v.ob[2];
                s2[0].v.cn[3] = 200;

                i = s4->unk_FC - 1;
                if (i < 6) {
                    i = 1;
                }

                s2[1].v.ob[0] = vtx_v0[i].v.ob[0];
                s2[1].v.ob[1] = vtx_v0[i].v.ob[1];
                s2[1].v.ob[2] = vtx_v0[i].v.ob[2];
                s2[1].v.cn[3] = 200;
            }
            s3 = 2;
        }

        arg0->unk_1D0++;
        s5->unk_F8 = arg0->unk_1D0 * 16;
        if (s5->unk_F8 > 14) {
            s5->unk_F8 = 14;
        }

        func_800114BC(&arg0->unk_0C, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        func_800114BC(&arg0->unk_0C, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        func_800114BC(&arg0->unk_0C, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        func_800114BC(&arg0->unk_0C, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        if (func_800114BC(&arg0->unk_EC, &spF4)) {
            if (arg0->unk_1D0 == 1 || spF4->x != s2[1].v.ob[0] || spF4->y != s2[1].v.ob[1] ||
                spF4->z != s2[1].v.ob[2]) {
                s2[s3].v.cn[3] = 200;
                s2[s3].v.ob[0] = spF4->x;
                s2[s3].v.ob[1] = spF4->y;
                s2[s3].v.ob[2] = spF4->z;
                s3++;
            }
            temp2 = gCameraProjectionMatrix.x.z * spAC->x + gCameraProjectionMatrix.y.z * spAC->y +
                    gCameraProjectionMatrix.z.z * spAC->z + gCameraProjectionMatrix.w.z;
            temp1 = gCameraProjectionMatrix.x.z * spF4->x + gCameraProjectionMatrix.y.z * spF4->y +
                    gCameraProjectionMatrix.z.z * spF4->z + gCameraProjectionMatrix.w.z;
            s5->unk_108 = temp1 < temp2;
        } else if (s4 != NULL) {
            s5->unk_108 = s4->unk_108;
        } else {
            arg0->unk_1D0 = 0;
            return;
        }

        if (func_800114BC(&arg0->unk_EC, &spF4)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = spF4->x;
            s2[s3].v.ob[1] = spF4->y;
            s2[s3].v.ob[2] = spF4->z;
            s3++;
        }
        if (func_800114BC(&arg0->unk_EC, &spF4)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = spF4->x;
            s2[s3].v.ob[1] = spF4->y;
            s2[s3].v.ob[2] = spF4->z;
            s3++;
        }
        if (func_800114BC(&arg0->unk_EC, &spF4)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = spF4->x;
            s2[s3].v.ob[1] = spF4->y;
            s2[s3].v.ob[2] = spF4->z;
            s3++;
        }

        s5->unk_FC = s3;
        s5->unk_100 = s3 - 2;
        if (arg0->unk_1D0 == 1) {
            s5->unk_104 = D_80049A70[s3];
        } else {
            s5->unk_104 = D_80049A58[s3];
        }
    }

    spF3 = FALSE;
    spF2 = TRUE;

    if (arg0->unk_1D0 != 0) {
        t2 = v1 = 0;
        spF3 = FALSE;

        for (i = 0; i < arg0->unk_1D0; i++) {
            sub2 = arg0->unk_1D8 + i;
            if (i != 0) {
                t2 += 5;
                v1 += sub2->unk_FC - 5;
            } else {
                t2 += 4;
                v1 += sub2->unk_FC - 4;
            }
        }

        _t4 = _t3 = 0;
        _a2 = _a1 = _a0 = 255;
        _t1 = _t0 = _a3 = 255;

        lo1 = (255 - arg0->unk_1454.r) / t2;
        lo2 = (255 - arg0->unk_1454.g) / t2;
        lo3 = (255 - arg0->unk_1454.b) / t2;

        lo4 = (255 - arg0->unk_1454.r) / v1;
        lo5 = (255 - arg0->unk_1454.g) / v1;
        lo6 = (255 - arg0->unk_1454.b) / v1;

        lo7 = 140 / t2;
        lo8 = 140 / v1;

        sub2 = arg0->unk_1D8;
        vtx_v0 = sub2->unk_58;
        for (k = 0; k < 4; k++) {
            vtx_v0[k].v.cn[3] = _t4;
            vtx_v0[k].v.cn[(k < 4) * 0] = _a2; // @FAKE
            vtx_v0[k].v.cn[1] = _a1;
            vtx_v0[k].v.cn[2] = _a0;

            vtx_v0[4 + k].v.cn[3] = _t3;

            _t1 -= lo1;
            _t0 -= lo2;
            _a3 -= lo3;

            _a0 -= lo6;
            _a1 -= lo5;
            _a2 -= lo4;

            _t4 += lo7;
            _t3 += lo8;
        }

        for (spD8 = 1; spD8 < arg0->unk_1D0; spD8++) {
            sub2 = arg0->unk_1D8 + spD8;
            vtx_v0 = sub2->unk_58;

            vtx_v0[0].v.cn[0] = _t1;
            vtx_v0[0].v.cn[1] = _t0;
            vtx_v0[0].v.cn[2] = _a3;
            vtx_v0[0].v.cn[3] = _t4;

            vtx_v0[1].v.cn[0] = _a2;
            vtx_v0[1].v.cn[1] = _a1;
            vtx_v0[1].v.cn[2] = _a0;
            vtx_v0[1].v.cn[3] = _t3;

            _a3 -= lo3;
            _t0 -= lo2;
            _t1 -= lo1;
            _t4 += lo7;

            _a0 -= lo6;
            _a1 -= lo5;
            _a2 -= lo4;
            _t3 += lo8;

            for (k = 2; k < 6; k++) {
                vtx_v0[k].v.cn[0] = _t1;
                vtx_v0[k].v.cn[1] = _t0;
                vtx_v0[k].v.cn[2] = _a3;
                vtx_v0[k].v.cn[3] = _t4;

                _t4 += lo7;
                _t1 -= lo1;
                _a3 -= lo3;
                _t0 -= lo2;

                if (_t1 < arg0->unk_1454.r) {
                    _t1 = arg0->unk_1454.r;
                }
                if (_t0 < arg0->unk_1454.g) {
                    _t0 = arg0->unk_1454.g;
                }
                if (_a3 < arg0->unk_1454.b) {
                    _a3 = arg0->unk_1454.b;
                }

                vtx_v0[4 + k].v.cn[0] = _a2;
                vtx_v0[4 + k].v.cn[1] = _a1;
                vtx_v0[4 + k].v.cn[2] = _a0;
                vtx_v0[4 + k].v.cn[3] = _t3;

                _t3 += lo8;
                _a2 -= lo4;
                _a0 -= lo6;
                _a1 -= lo5;

                if (_a2 < arg0->unk_1454.r) {
                    _a2 = arg0->unk_1454.r;
                }
                if (_a1 < arg0->unk_1454.g) {
                    _a1 = arg0->unk_1454.g;
                }
                if (_a0 < arg0->unk_1454.b) {
                    _a0 = arg0->unk_1454.b;
                }
            }
        }
    }

    for (j = 0; j < arg0->unk_1D0; j++) {
        sub2 = arg0->unk_1D8 + j;
        if (!gIsPaused) {
            sub2->unk_F8--;
        }
        if (D_8008012C & GFX_FLAG_10) {
            sub2->unk_F8 -= 2;
        }

        if (sub2->unk_F8 > 0 && !sub2->unk_108) {
            gMainBatchPos->context = NULL;

            if (!spF3) {
                s03 = arg0->unk_12D8 + D_8005BFCE;
                math_mtxf2mtx(&s03->transform, &gCameraProjectionMatrix);
                spF3 = TRUE;
                spF2 = FALSE;
            } else {
                s03 = &sub2->unk_00;
            }
            s03->header.vtxNum = sub2->unk_FC;
            s03->header.numTriangles = sub2->unk_100;
            gMainBatchPos->info = s03;
            gMainBatchPos->vertices = sub2->unk_58;
            gMainBatchPos->triangles = sub2->unk_104;
            gMainBatchPos++;
        }
    }

    spF3 = FALSE;
    for (j = 0; j < arg0->unk_1D0; j++) {
        sub2 = arg0->unk_1D8 + j;

        if (!gIsPaused) {
            sub2->unk_F8--;
        }
        if (D_8008012C & GFX_FLAG_10) {
            sub2->unk_F8 -= 2;
        }

        if (sub2->unk_F8 > 0 && sub2->unk_108) {
            gOverlayBatchPos->context = NULL;

            if (!spF3) {
                s03 = arg0->unk_12D8 + 2 + D_8005BFCE;
                math_mtxf2mtx(&s03->transform, &gCameraProjectionMatrix);
                spF3 = TRUE;
                spF2 = FALSE;
            } else {
                s03 = &sub2->unk_00;
            }
            s03->header.vtxNum = sub2->unk_FC;
            s03->header.numTriangles = sub2->unk_100;
            gOverlayBatchPos->info = s03;
            gOverlayBatchPos->vertices = sub2->unk_58;
            gOverlayBatchPos->triangles = sub2->unk_104;
            gOverlayBatchPos++;
        }
    }

    if (spF2) {
        arg0->unk_1D0 = 0;
    }
}

void func_80012150(PlayerSub6 *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4,
                   ColorRGBA *arg5) {
    u32 i, j;
    Gfx *gfx;
    u32 a;
    PlayerSub6Sub2 *s6;
    BatchInfo *s2;

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

    for (i = 0; i < 4; i++) {
        s2 = arg0->unk_12D8 + i;
        func_800114DC(s2);
        s2->header.texGfx = D_80081280;
        s2->header.unk_0B = 0;
    }

    for (i = 0; i < 16; i++) {
        s6 = &arg0->unk_1D8[i];
        func_800114DC(&s6->unk_00);
        mem_fill(s6->unk_58, 0, sizeof(Vtx) * 8);

        a = 200;
        if (i == 0) {
            for (j = 0; j < 4; j++) {
                s6->unk_58[j].v.cn[0] = arg5->r;
                s6->unk_58[j].v.cn[1] = arg5->g;
                s6->unk_58[j].v.cn[2] = arg5->b;
                s6->unk_58[j].v.cn[3] = a;
                s6->unk_58[j + 4].v.cn[0] = arg5->r;
                s6->unk_58[j + 4].v.cn[1] = arg5->g;
                s6->unk_58[j + 4].v.cn[2] = arg5->b;
                s6->unk_58[j + 4].v.cn[3] = a;
                a += 4;
            }
        } else {
            s6->unk_58[0].v.cn[0] = arg5->r;
            s6->unk_58[0].v.cn[1] = arg5->g;
            s6->unk_58[0].v.cn[2] = arg5->b;
            s6->unk_58[0].v.cn[3] = a;
            s6->unk_58[1].v.cn[0] = arg5->r;
            s6->unk_58[1].v.cn[1] = arg5->g;
            s6->unk_58[1].v.cn[2] = arg5->b;
            s6->unk_58[1].v.cn[3] = a;
            a += 4;

            for (j = 2; j < 6; j++) {
                s6->unk_58[j].v.cn[0] = arg5->r;
                s6->unk_58[j].v.cn[1] = arg5->g;
                s6->unk_58[j].v.cn[2] = arg5->b;
                s6->unk_58[j].v.cn[3] = a;
                s6->unk_58[j + 4].v.cn[0] = arg5->r;
                s6->unk_58[j + 4].v.cn[1] = arg5->g;
                s6->unk_58[j + 4].v.cn[2] = arg5->b;
                s6->unk_58[j + 4].v.cn[3] = a;
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
