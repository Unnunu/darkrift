#include "common.h"
#include "PR/gt.h"
#include "task.h"
#include "camera.h"

x_562d2a02 D_800499B0[] = {
    { 0, 1, 4, 0 },
    { 1, 2, 4, 0 },
    { 2, 3, 4, 0 },
};
x_562d2a02 D_800499BC[] = {
    { 0, 1, 4, 0 },
    { 4, 1, 5, 0 },
    { 1, 2, 5, 0 },
    { 2, 3, 5, 0 },
};
x_562d2a02 D_800499CC[] = {
    { 0, 1, 4, 0 }, { 4, 1, 5, 0 }, { 5, 1, 2, 0 }, { 5, 2, 6, 0 }, { 6, 2, 3, 0 },
};
x_562d2a02 D_800499E0[] = {
    { 0, 1, 4, 0 }, { 4, 1, 5, 0 }, { 5, 1, 2, 0 }, { 5, 2, 6, 0 }, { 6, 2, 3, 0 }, { 6, 3, 7, 0 },
};

x_562d2a02 D_800499F8[] = {
    { 0, 2, 1, 0 },
    { 2, 3, 1, 0 },
    { 3, 4, 1, 0 },
    { 4, 5, 1, 0 },
};
x_562d2a02 D_80049A08[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 2, 3, 6, 0 }, { 3, 4, 6, 0 }, { 4, 5, 6, 0 },
};
x_562d2a02 D_80049A1C[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 2, 3, 6, 0 }, { 6, 3, 7, 0 }, { 3, 4, 7, 0 }, { 4, 5, 7, 0 },
};
x_562d2a02 D_80049A34[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 6, 2, 3, 0 }, { 6, 3, 7, 0 }, { 7, 3, 4, 0 }, { 7, 4, 8, 0 }, { 8, 4, 5, 0 },
};
x_562d2a02 D_80049A50[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 6, 2, 3, 0 }, { 6, 3, 7, 0 },
    { 7, 3, 4, 0 }, { 7, 4, 8, 0 }, { 8, 4, 5, 0 }, { 8, 5, 9, 0 },
};

x_562d2a02 *D_80049A70[] = { D_800499F8, D_80049A08, D_80049A1C, D_80049A34, D_80049A50 };
x_562d2a02 *D_80049A84[] = { D_800499B0, D_800499BC, D_800499CC, D_800499E0 };

x_f9704fd6 D_80049A94 = {
    { -0.5, 1.5, -1.5, 0.5 },
    { 1, -2.5, 2, -0.5 },
    { -0.5, 0, 0.5, 0 },
    { 0, 1, 0, 0 },
};

/* .bss */
Gfx D_80081280[4];

void x_51d7e40d(x_c2fa3c06 *x_cc1d0de5, s32 x_84ff873b) {
    x_cc1d0de5->x_5e0afed5 = 0;
    x_cc1d0de5->x_e7f3bb4b = 0;
    x_cc1d0de5->x_e8bea4b4 = x_84ff873b;
    x_cc1d0de5->count = 0;
}

void x_339d85cc(x_c2fa3c06 *x_cc1d0de5, x_88f11482 *x_84ff873b) {
    s32 v0;

    v0 = x_cc1d0de5->x_e7f3bb4b;

    if (x_cc1d0de5->count != 0 && x_cc1d0de5->x_5e0afed5 == v0) {
        x_cc1d0de5->x_5e0afed5++;
        x_cc1d0de5->x_5e0afed5 &= x_cc1d0de5->x_e8bea4b4;
    } else {
        x_cc1d0de5->count++;
    }

    x_cc1d0de5->x_f50871d1[v0].x = x_84ff873b->x;
    x_cc1d0de5->x_f50871d1[v0].y = x_84ff873b->y;
    x_cc1d0de5->x_f50871d1[v0].z = x_84ff873b->z;

    v0++;
    v0 &= x_cc1d0de5->x_e8bea4b4;
    x_cc1d0de5->x_e7f3bb4b = v0;
}

s32 x_fa3a2a63(x_c2fa3c06 *x_cc1d0de5, x_88f11482 **x_84ff873b) {
    s32 v1;

    v1 = x_cc1d0de5->x_5e0afed5;
    if (x_cc1d0de5->count == 0) {
        v1--;
        if (v1 < 0) {
            v1 = 3;
        }
        *x_84ff873b = &x_cc1d0de5->x_f50871d1[v1 - 1];
        return 0;
    } else {
        *x_84ff873b = &x_cc1d0de5->x_f50871d1[v1];
        v1++;
        v1 &= x_cc1d0de5->x_e8bea4b4;
        x_cc1d0de5->x_5e0afed5 = v1;
        x_cc1d0de5->count--;
        // @bug UB: should be return 1;
    }
}

void x_3c2e0c67(x_12f9ebc0 *x_cc1d0de5) {
    x_51d7e40d(&x_cc1d0de5->x_646d43df, 3);
    x_51d7e40d(&x_cc1d0de5->x_48fb4701, 3);
}

s32 x_61a58c70(x_12f9ebc0 *x_cc1d0de5) {
    x_f9704fd6 *A0;
    x_88f11482 *x_c9614940;
    x_88f11482 *x_32f1d6e2;
    x_88f11482 *x_5aee6615;
    x_88f11482 *x_5bbba600;

    A0 = &x_cc1d0de5->x_1996624f;

    if (x_cc1d0de5->x_646d43df.count != 4) {
        return FALSE;
    }

    x_fa3a2a63(&x_cc1d0de5->x_646d43df, &x_c9614940);
    x_fa3a2a63(&x_cc1d0de5->x_646d43df, &x_32f1d6e2);
    x_fa3a2a63(&x_cc1d0de5->x_646d43df, &x_5aee6615);
    x_fa3a2a63(&x_cc1d0de5->x_646d43df, &x_5bbba600);

    A0->x.x = D_80049A94.x.x * x_c9614940->x + D_80049A94.x.y * x_32f1d6e2->x + D_80049A94.x.z * x_5aee6615->x +
              D_80049A94.x.w * x_5bbba600->x;
    A0->y.x = D_80049A94.y.x * x_c9614940->x + D_80049A94.y.y * x_32f1d6e2->x + D_80049A94.y.z * x_5aee6615->x +
              D_80049A94.y.w * x_5bbba600->x;
    A0->z.x = D_80049A94.z.x * x_c9614940->x + D_80049A94.z.y * x_32f1d6e2->x + D_80049A94.z.z * x_5aee6615->x +
              D_80049A94.z.w * x_5bbba600->x;
    A0->w.x = D_80049A94.w.x * x_c9614940->x + D_80049A94.w.y * x_32f1d6e2->x + D_80049A94.w.z * x_5aee6615->x +
              D_80049A94.w.w * x_5bbba600->x;

    A0->x.y = D_80049A94.x.x * x_c9614940->y + D_80049A94.x.y * x_32f1d6e2->y + D_80049A94.x.z * x_5aee6615->y +
              D_80049A94.x.w * x_5bbba600->y;
    A0->y.y = D_80049A94.y.x * x_c9614940->y + D_80049A94.y.y * x_32f1d6e2->y + D_80049A94.y.z * x_5aee6615->y +
              D_80049A94.y.w * x_5bbba600->y;
    A0->z.y = D_80049A94.z.x * x_c9614940->y + D_80049A94.z.y * x_32f1d6e2->y + D_80049A94.z.z * x_5aee6615->y +
              D_80049A94.z.w * x_5bbba600->y;
    A0->w.y = D_80049A94.w.x * x_c9614940->y + D_80049A94.w.y * x_32f1d6e2->y + D_80049A94.w.z * x_5aee6615->y +
              D_80049A94.w.w * x_5bbba600->y;

    A0->x.z = D_80049A94.x.x * x_c9614940->z + D_80049A94.x.y * x_32f1d6e2->z + D_80049A94.x.z * x_5aee6615->z +
              D_80049A94.x.w * x_5bbba600->z;
    A0->y.z = D_80049A94.y.x * x_c9614940->z + D_80049A94.y.y * x_32f1d6e2->z + D_80049A94.y.z * x_5aee6615->z +
              D_80049A94.y.w * x_5bbba600->z;
    A0->z.z = D_80049A94.z.x * x_c9614940->z + D_80049A94.z.y * x_32f1d6e2->z + D_80049A94.z.z * x_5aee6615->z +
              D_80049A94.z.w * x_5bbba600->z;
    A0->w.z = D_80049A94.w.x * x_c9614940->z + D_80049A94.w.y * x_32f1d6e2->z + D_80049A94.w.z * x_5aee6615->z +
              D_80049A94.w.w * x_5bbba600->z;

    x_339d85cc(&x_cc1d0de5->x_646d43df, x_32f1d6e2);
    x_339d85cc(&x_cc1d0de5->x_646d43df, x_5aee6615);
    x_339d85cc(&x_cc1d0de5->x_646d43df, x_5bbba600);

    return TRUE;
}

void x_90ab8f92(x_12f9ebc0 *x_cc1d0de5, x_88f11482 *x_84ff873b) {
    f32 fs0, fs1, fs2;
    f32 fs3, fs4, fs5;
    s32 i;
    f32 x_4cec9290, x_30a44af1, x_0ae713be;
    f32 x_5d45b0f8, x_048c1e73, x_a438747c;
    x_88f11482 x_5b215acc;
    x_f9704fd6 *A0;

    A0 = &x_cc1d0de5->x_1996624f;

    x_339d85cc(x_cc1d0de5, x_84ff873b);

    if (x_61a58c70(x_cc1d0de5)) {
        fs0 = 0.015625f * A0->x.x + 0.0625f * A0->y.x + 0.25f * A0->z.x;
        fs1 = 0.015625f * A0->x.y + 0.0625f * A0->y.y + 0.25f * A0->z.y;
        fs2 = 0.015625f * A0->x.z + 0.0625f * A0->y.z + 0.25f * A0->z.z;

        x_4cec9290 = 0.09375f * A0->x.x;
        x_30a44af1 = 0.09375f * A0->x.y;
        x_0ae713be = 0.09375f * A0->x.z;

        fs3 = x_4cec9290 + 0.125f * A0->y.x;
        fs4 = x_30a44af1 + 0.125f * A0->y.y;
        fs5 = x_0ae713be + 0.125f * A0->y.z;
        x_5d45b0f8 = A0->w.x;
        x_048c1e73 = A0->w.y;
        x_a438747c = A0->w.z;

        for (i = 0; i < 4; i++) {
            x_5d45b0f8 += fs0;
            x_048c1e73 += fs1;
            x_a438747c += fs2;

            x_5b215acc.x = x_5d45b0f8;
            x_5b215acc.y = x_048c1e73;
            x_5b215acc.z = x_a438747c;

            fs0 += fs3;
            fs1 += fs4;
            fs2 += fs5;

            fs3 += x_4cec9290;
            fs4 += x_30a44af1;
            fs5 += x_0ae713be;

            x_339d85cc(&x_cc1d0de5->x_48fb4701, &x_5b215acc);
        }
    }
}

s32 x_0643a037(x_12f9ebc0 *x_cc1d0de5, x_88f11482 **x_84ff873b) {
    return x_fa3a2a63(&x_cc1d0de5->x_48fb4701, x_84ff873b);
}

void x_19200409(x_c1cedf06 *x_4bb24efc) {
    x_4bb24efc->header.x_09cf7a45 = 0x200;
    x_4bb24efc->header.x_70b508ea = 1;
    x_4bb24efc->header.x_1256da71 = 0;
    x_4bb24efc->header.x_4c5e05f8 = 10;
    x_4bb24efc->header.x_ed66866b = 0;
    x_4bb24efc->header.x_8a54e96a = 8;
    x_4bb24efc->header.x_b7ba6d35 = NULL;

    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);
}

void x_f7a1a468(x_056d4f07 *x_cc1d0de5, u8 x_84ff873b) {
    x_88f11482 x_fd599243;
    x_88f11482 *x_ec0139c7;
    u8 x_d647d552;
    u8 x_5c10660a;
    x_f9704fd6 *s0;
    x_f9704fd6 *v0;
    x_90f055ea *s5;
    x_90f055ea *s4;
    u32 t2;
    u32 x_5fd741dc;
    s32 s3;
    Vtx *s2;
    s32 x_282dc94b, x_7767c65d, x_3d141102, x_b7cf5a8d, x_191af220, x_8784fa74, x_84a2d18f, x_bd3b6690;
    x_88f11482 *x_30a44af1;
    u32 v1;
    s32 x_d331272a, x_58b21343, x_cb50aeea, x_399ba316, x_b4579e51, x_777a942d, x_5e00e277, x_e455762f;
    u32 i;
    u32 j;
    x_c1cedf06 *x_a52ba8b1;
    s32 k;
    Vtx *x_f82ccdb1;
    s32 x_8c5f8c03, x_df21a243;
    x_90f055ea *x_94b671c9;
    f32 temp;
    f32 x;

    v0 = x_cc1d0de5->x_007a9250;
    s0 = x_cc1d0de5->x_89f63109;
    x_30a44af1 = x_cc1d0de5->x_36bb3f9b;

    x = v0->w.x;                                                                // @FAKE
    temp = v0->w.x * v0->w.x + v0->w.y * v0->w.y + v0->w.z * v0->w.z + v0->w.z; // @FAKE
    if (temp == 0) {}                                                           // @FAKE
    x_fd599243.x = v0->w.x;
    x_fd599243.y = v0->w.y;
    x_fd599243.z = v0->w.z;
    x_cc1d0de5->x_c08ab25c = x_fd599243.x;
    x_cc1d0de5->x_9810c807 = x_fd599243.y;
    x_cc1d0de5->x_b8fd00e2 = x_fd599243.z;
    x_90ab8f92(&x_cc1d0de5->x_1091fcc6, &x_fd599243);

    temp = s0->w.x * s0->w.x + s0->w.y * s0->w.y + s0->w.z * s0->w.z + s0->w.z; // @FAKE
    if (temp == 0) {}                                                           // @FAKE
    x_fd599243.x = s0->w.x;
    x_fd599243.y = s0->w.y;
    x_fd599243.z = s0->w.z;
    x_cc1d0de5->x_bc587679 = x_fd599243.x;
    x_cc1d0de5->x_fc05a02f = x_fd599243.y;
    x_cc1d0de5->x_1ba29927 = x_fd599243.z;
    x_90ab8f92(&x_cc1d0de5->x_60635a2d, &x_fd599243);

    if (!gTaskLock && x_84ff873b && !(x_e30d50d2 & x_dd99cbfb) && x_cc1d0de5->x_b1f57d55 < 16) {
        s5 = &x_cc1d0de5->x_08fddbc8[x_cc1d0de5->x_b1f57d55];
        s4 = NULL;

        if (x_cc1d0de5->x_b1f57d55 == 0) {
            s3 = 0;
            s2 = s5->vertices;
        } else {
            s4 = &x_cc1d0de5->x_08fddbc8[x_cc1d0de5->x_b1f57d55 - 1];
            x_f82ccdb1 = s4->vertices;
            s2 = s5->vertices;

            if (x_cc1d0de5->x_b1f57d55 == 1) {
                s2[0].v.ob[0] = x_f82ccdb1[3].v.ob[0];
                s2[0].v.ob[1] = x_f82ccdb1[3].v.ob[1];
                s2[0].v.ob[2] = x_f82ccdb1[3].v.ob[2];
                s2[0].v.cn[3] = 200;

                i = s4->x_723971cf - 1;

                s2[1].v.ob[0] = x_f82ccdb1[i].v.ob[0];
                s2[1].v.ob[1] = x_f82ccdb1[i].v.ob[1];
                s2[1].v.ob[2] = x_f82ccdb1[i].v.ob[2];
                s2[1].v.cn[3] = 200;
            } else {
                s2[0].v.ob[0] = x_f82ccdb1[5].v.ob[0];
                s2[0].v.ob[1] = x_f82ccdb1[5].v.ob[1];
                s2[0].v.ob[2] = x_f82ccdb1[5].v.ob[2];
                s2[0].v.cn[3] = 200;

                i = s4->x_723971cf - 1;
                if (i < 6) {
                    i = 1;
                }

                s2[1].v.ob[0] = x_f82ccdb1[i].v.ob[0];
                s2[1].v.ob[1] = x_f82ccdb1[i].v.ob[1];
                s2[1].v.ob[2] = x_f82ccdb1[i].v.ob[2];
                s2[1].v.cn[3] = 200;
            }
            s3 = 2;
        }

        x_cc1d0de5->x_b1f57d55++;
        s5->x_6f6a6d94 = x_cc1d0de5->x_b1f57d55 * 16;
        if (s5->x_6f6a6d94 > 14) {
            s5->x_6f6a6d94 = 14;
        }

        x_0643a037(&x_cc1d0de5->x_1091fcc6, &x_ec0139c7);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = x_ec0139c7->x;
        s2[s3].v.ob[1] = x_ec0139c7->y;
        s2[s3].v.ob[2] = x_ec0139c7->z;
        s3++;

        x_0643a037(&x_cc1d0de5->x_1091fcc6, &x_ec0139c7);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = x_ec0139c7->x;
        s2[s3].v.ob[1] = x_ec0139c7->y;
        s2[s3].v.ob[2] = x_ec0139c7->z;
        s3++;

        x_0643a037(&x_cc1d0de5->x_1091fcc6, &x_ec0139c7);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = x_ec0139c7->x;
        s2[s3].v.ob[1] = x_ec0139c7->y;
        s2[s3].v.ob[2] = x_ec0139c7->z;
        s3++;

        x_0643a037(&x_cc1d0de5->x_1091fcc6, &x_ec0139c7);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = x_ec0139c7->x;
        s2[s3].v.ob[1] = x_ec0139c7->y;
        s2[s3].v.ob[2] = x_ec0139c7->z;
        s3++;

        if (x_0643a037(&x_cc1d0de5->x_60635a2d, &x_ec0139c7)) {
            if (x_cc1d0de5->x_b1f57d55 == 1 || x_ec0139c7->x != s2[1].v.ob[0] || x_ec0139c7->y != s2[1].v.ob[1] ||
                x_ec0139c7->z != s2[1].v.ob[2]) {
                s2[s3].v.cn[3] = 200;
                s2[s3].v.ob[0] = x_ec0139c7->x;
                s2[s3].v.ob[1] = x_ec0139c7->y;
                s2[s3].v.ob[2] = x_ec0139c7->z;
                s3++;
            }
            x_df21a243 = x_7eefcd11.x.z * x_30a44af1->x + x_7eefcd11.y.z * x_30a44af1->y +
                         x_7eefcd11.z.z * x_30a44af1->z + x_7eefcd11.w.z;
            x_8c5f8c03 = x_7eefcd11.x.z * x_ec0139c7->x + x_7eefcd11.y.z * x_ec0139c7->y +
                         x_7eefcd11.z.z * x_ec0139c7->z + x_7eefcd11.w.z;
            s5->x_24fe8ee6 = x_8c5f8c03 < x_df21a243;
        } else if (s4 != NULL) {
            s5->x_24fe8ee6 = s4->x_24fe8ee6;
        } else {
            x_cc1d0de5->x_b1f57d55 = 0;
            return;
        }

        if (x_0643a037(&x_cc1d0de5->x_60635a2d, &x_ec0139c7)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = x_ec0139c7->x;
            s2[s3].v.ob[1] = x_ec0139c7->y;
            s2[s3].v.ob[2] = x_ec0139c7->z;
            s3++;
        }
        if (x_0643a037(&x_cc1d0de5->x_60635a2d, &x_ec0139c7)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = x_ec0139c7->x;
            s2[s3].v.ob[1] = x_ec0139c7->y;
            s2[s3].v.ob[2] = x_ec0139c7->z;
            s3++;
        }
        if (x_0643a037(&x_cc1d0de5->x_60635a2d, &x_ec0139c7)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = x_ec0139c7->x;
            s2[s3].v.ob[1] = x_ec0139c7->y;
            s2[s3].v.ob[2] = x_ec0139c7->z;
            s3++;
        }

        s5->x_723971cf = s3;
        s5->x_a1256713 = s3 - 2;
        if (x_cc1d0de5->x_b1f57d55 == 1) {
            s5->triangles = D_80049A84[s3 - 5];
        } else {
            s5->triangles = D_80049A70[s3 - 6];
        }
    }

    x_d647d552 = FALSE;
    x_5c10660a = TRUE;

    if (x_cc1d0de5->x_b1f57d55 != 0) {
        t2 = v1 = 0;
        x_d647d552 = FALSE;

        for (i = 0; i < x_cc1d0de5->x_b1f57d55; i++) {
            x_94b671c9 = x_cc1d0de5->x_08fddbc8 + i;
            if (i != 0) {
                t2 += 5;
                v1 += x_94b671c9->x_723971cf - 5;
            } else {
                t2 += 4;
                v1 += x_94b671c9->x_723971cf - 4;
            }
        }

        x_b7cf5a8d = x_191af220 = 0;
        x_282dc94b = x_7767c65d = x_3d141102 = 255;
        x_8784fa74 = x_84a2d18f = x_bd3b6690 = 255;

        x_d331272a = (255 - x_cc1d0de5->x_57e44061.r) / t2;
        x_58b21343 = (255 - x_cc1d0de5->x_57e44061.g) / t2;
        x_cb50aeea = (255 - x_cc1d0de5->x_57e44061.b) / t2;

        x_399ba316 = (255 - x_cc1d0de5->x_57e44061.r) / v1;
        x_b4579e51 = (255 - x_cc1d0de5->x_57e44061.g) / v1;
        x_777a942d = (255 - x_cc1d0de5->x_57e44061.b) / v1;

        x_5e00e277 = 140 / t2;
        x_e455762f = 140 / v1;

        x_94b671c9 = x_cc1d0de5->x_08fddbc8;
        x_f82ccdb1 = x_94b671c9->vertices;
        for (k = 0; k < 4; k++) {
            x_f82ccdb1[k].v.cn[3] = x_b7cf5a8d;
            x_f82ccdb1[k].v.cn[(k < 4) * 0] = x_282dc94b; // @FAKE
            x_f82ccdb1[k].v.cn[1] = x_7767c65d;
            x_f82ccdb1[k].v.cn[2] = x_3d141102;

            x_f82ccdb1[4 + k].v.cn[3] = x_191af220;

            x_8784fa74 -= x_d331272a;
            x_84a2d18f -= x_58b21343;
            x_bd3b6690 -= x_cb50aeea;

            x_3d141102 -= x_777a942d;
            x_7767c65d -= x_b4579e51;
            x_282dc94b -= x_399ba316;

            x_b7cf5a8d += x_5e00e277;
            x_191af220 += x_e455762f;
        }

        for (x_5fd741dc = 1; x_5fd741dc < x_cc1d0de5->x_b1f57d55; x_5fd741dc++) {
            x_94b671c9 = x_cc1d0de5->x_08fddbc8 + x_5fd741dc;
            x_f82ccdb1 = x_94b671c9->vertices;

            x_f82ccdb1[0].v.cn[0] = x_8784fa74;
            x_f82ccdb1[0].v.cn[1] = x_84a2d18f;
            x_f82ccdb1[0].v.cn[2] = x_bd3b6690;
            x_f82ccdb1[0].v.cn[3] = x_b7cf5a8d;

            x_f82ccdb1[1].v.cn[0] = x_282dc94b;
            x_f82ccdb1[1].v.cn[1] = x_7767c65d;
            x_f82ccdb1[1].v.cn[2] = x_3d141102;
            x_f82ccdb1[1].v.cn[3] = x_191af220;

            x_bd3b6690 -= x_cb50aeea;
            x_84a2d18f -= x_58b21343;
            x_8784fa74 -= x_d331272a;
            x_b7cf5a8d += x_5e00e277;

            x_3d141102 -= x_777a942d;
            x_7767c65d -= x_b4579e51;
            x_282dc94b -= x_399ba316;
            x_191af220 += x_e455762f;

            for (k = 2; k < 6; k++) {
                x_f82ccdb1[k].v.cn[0] = x_8784fa74;
                x_f82ccdb1[k].v.cn[1] = x_84a2d18f;
                x_f82ccdb1[k].v.cn[2] = x_bd3b6690;
                x_f82ccdb1[k].v.cn[3] = x_b7cf5a8d;

                x_b7cf5a8d += x_5e00e277;
                x_8784fa74 -= x_d331272a;
                x_bd3b6690 -= x_cb50aeea;
                x_84a2d18f -= x_58b21343;

                if (x_8784fa74 < x_cc1d0de5->x_57e44061.r) {
                    x_8784fa74 = x_cc1d0de5->x_57e44061.r;
                }
                if (x_84a2d18f < x_cc1d0de5->x_57e44061.g) {
                    x_84a2d18f = x_cc1d0de5->x_57e44061.g;
                }
                if (x_bd3b6690 < x_cc1d0de5->x_57e44061.b) {
                    x_bd3b6690 = x_cc1d0de5->x_57e44061.b;
                }

                x_f82ccdb1[4 + k].v.cn[0] = x_282dc94b;
                x_f82ccdb1[4 + k].v.cn[1] = x_7767c65d;
                x_f82ccdb1[4 + k].v.cn[2] = x_3d141102;
                x_f82ccdb1[4 + k].v.cn[3] = x_191af220;

                x_191af220 += x_e455762f;
                x_282dc94b -= x_399ba316;
                x_3d141102 -= x_777a942d;
                x_7767c65d -= x_b4579e51;

                if (x_282dc94b < x_cc1d0de5->x_57e44061.r) {
                    x_282dc94b = x_cc1d0de5->x_57e44061.r;
                }
                if (x_7767c65d < x_cc1d0de5->x_57e44061.g) {
                    x_7767c65d = x_cc1d0de5->x_57e44061.g;
                }
                if (x_3d141102 < x_cc1d0de5->x_57e44061.b) {
                    x_3d141102 = x_cc1d0de5->x_57e44061.b;
                }
            }
        }
    }

    for (j = 0; j < x_cc1d0de5->x_b1f57d55; j++) {
        x_94b671c9 = x_cc1d0de5->x_08fddbc8 + j;
        if (!gTaskLock) {
            x_94b671c9->x_6f6a6d94--;
        }
        if (gGfxFlags & GFX_SHADOW_MODE) {
            x_94b671c9->x_6f6a6d94 -= 2;
        }

        if (x_94b671c9->x_6f6a6d94 > 0 && !x_94b671c9->x_24fe8ee6) {
            gDrBatchPtr->context = NULL;

            if (!x_d647d552) {
                x_a52ba8b1 = x_cc1d0de5->x_ad2af5d9 + D_8005BFCE;
                mat4_to_mtx(&x_a52ba8b1->transform, &x_7eefcd11);
                x_d647d552 = TRUE;
                x_5c10660a = FALSE;
            } else {
                x_a52ba8b1 = &x_94b671c9->x_3ab7202f;
            }
            x_a52ba8b1->header.x_4c5e05f8 = x_94b671c9->x_723971cf;
            x_a52ba8b1->header.x_8a54e96a = x_94b671c9->x_a1256713;
            gDrBatchPtr->info = x_a52ba8b1;
            gDrBatchPtr->vertices = x_94b671c9->vertices;
            gDrBatchPtr->triangles = x_94b671c9->triangles;
            gDrBatchPtr++;
        }
    }

    x_d647d552 = FALSE;
    for (j = 0; j < x_cc1d0de5->x_b1f57d55; j++) {
        x_94b671c9 = x_cc1d0de5->x_08fddbc8 + j;

        if (!gTaskLock) {
            x_94b671c9->x_6f6a6d94--;
        }
        if (gGfxFlags & GFX_SHADOW_MODE) {
            x_94b671c9->x_6f6a6d94 -= 2;
        }

        if (x_94b671c9->x_6f6a6d94 > 0 && x_94b671c9->x_24fe8ee6) {
            gExtraBatchPtr->context = NULL;

            if (!x_d647d552) {
                x_a52ba8b1 = x_cc1d0de5->x_ad2af5d9 + 2 + D_8005BFCE;
                mat4_to_mtx(&x_a52ba8b1->transform, &x_7eefcd11);
                x_d647d552 = TRUE;
                x_5c10660a = FALSE;
            } else {
                x_a52ba8b1 = &x_94b671c9->x_3ab7202f;
            }
            x_a52ba8b1->header.x_4c5e05f8 = x_94b671c9->x_723971cf;
            x_a52ba8b1->header.x_8a54e96a = x_94b671c9->x_a1256713;
            gExtraBatchPtr->info = x_a52ba8b1;
            gExtraBatchPtr->vertices = x_94b671c9->vertices;
            gExtraBatchPtr->triangles = x_94b671c9->triangles;
            gExtraBatchPtr++;
        }
    }

    if (x_5c10660a) {
        x_cc1d0de5->x_b1f57d55 = 0;
    }
}

void shadow_init(x_056d4f07 *x_897abbb1, x_6fcfcf46 *x_c657ede8, x_f9704fd6 *x_2092f891, x_f9704fd6 *x_ee71e5cb,
                 x_88f11482 *x_a0e63e9c, x_6751d717 *x_1011f751) {
    u32 i, j;
    Gfx *gfx;
    u32 a;
    x_90f055ea *s6;
    x_c1cedf06 *s2;

    x_897abbb1->x_c657ede8 = x_c657ede8;
    x_897abbb1->x_89f63109 = x_2092f891;
    x_897abbb1->x_007a9250 = x_ee71e5cb;

    x_3c2e0c67(&x_897abbb1->x_1091fcc6);
    x_3c2e0c67(&x_897abbb1->x_60635a2d);

    x_897abbb1->x_30459015 = 0;
    x_897abbb1->x_b1f57d55 = 0;
    x_897abbb1->x_36bb3f9b = x_a0e63e9c;

    gfx = D_80081280;
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
    gSPNoOp(gfx++);

    for (i = 0; i < 4; i++) {
        s2 = x_897abbb1->x_ad2af5d9 + i;
        x_19200409(s2);
        s2->header.x_b7ba6d35 = D_80081280;
        s2->header.x_70b508ea = 0;
    }

    for (i = 0; i < 16; i++) {
        s6 = &x_897abbb1->x_08fddbc8[i];
        x_19200409(&s6->x_3ab7202f);
        mem_set(s6->vertices, 0, sizeof(Vtx) * 8);

        a = 200;
        if (i == 0) {
            for (j = 0; j < 4; j++) {
                s6->vertices[j].v.cn[0] = x_1011f751->r;
                s6->vertices[j].v.cn[1] = x_1011f751->g;
                s6->vertices[j].v.cn[2] = x_1011f751->b;
                s6->vertices[j].v.cn[3] = a;
                s6->vertices[j + 4].v.cn[0] = x_1011f751->r;
                s6->vertices[j + 4].v.cn[1] = x_1011f751->g;
                s6->vertices[j + 4].v.cn[2] = x_1011f751->b;
                s6->vertices[j + 4].v.cn[3] = a;
                a += 4;
            }
        } else {
            s6->vertices[0].v.cn[0] = x_1011f751->r;
            s6->vertices[0].v.cn[1] = x_1011f751->g;
            s6->vertices[0].v.cn[2] = x_1011f751->b;
            s6->vertices[0].v.cn[3] = a;
            s6->vertices[1].v.cn[0] = x_1011f751->r;
            s6->vertices[1].v.cn[1] = x_1011f751->g;
            s6->vertices[1].v.cn[2] = x_1011f751->b;
            s6->vertices[1].v.cn[3] = a;
            a += 4;

            for (j = 2; j < 6; j++) {
                s6->vertices[j].v.cn[0] = x_1011f751->r;
                s6->vertices[j].v.cn[1] = x_1011f751->g;
                s6->vertices[j].v.cn[2] = x_1011f751->b;
                s6->vertices[j].v.cn[3] = a;
                s6->vertices[j + 4].v.cn[0] = x_1011f751->r;
                s6->vertices[j + 4].v.cn[1] = x_1011f751->g;
                s6->vertices[j + 4].v.cn[2] = x_1011f751->b;
                s6->vertices[j + 4].v.cn[3] = a;
                a += 4;
                if (a > 255) {
                    a = 255;
                }
            }
        }

        s6->x_6f6a6d94 = -1;
    }

    x_897abbb1->x_c08ab25c = x_897abbb1->x_9810c807 = x_897abbb1->x_b8fd00e2 = 0.0f;
    x_897abbb1->x_bc587679 = x_897abbb1->x_fc05a02f = x_897abbb1->x_1ba29927 = 0.0f;

    x_897abbb1->x_57e44061.r = x_1011f751->r;
    x_897abbb1->x_57e44061.g = x_1011f751->g;
    x_897abbb1->x_57e44061.b = x_1011f751->b;
}
