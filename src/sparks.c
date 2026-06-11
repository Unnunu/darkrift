#include "common.h"
#include "camera.h"
#include "PR/gt.h"

typedef struct x_6548b963 {
    /* 0x00 */ x_88f11482 pos;
    /* 0x10 */ x_88f11482 x_4a6530b1;
    /* 0x20 */ u8 x_034f3eb1;
    /* 0x24 */ s32 x_817784f2;
} x_6548b963; // size = 0x28

typedef struct x_2f5c3183 {
    /* 0x0000 */ x_c1cedf06 x_af0aa1f8[12];
    /* 0x0420 */ Vtx x_aa3a09af[120];
    /* 0x0BA0 */ Vtx x_38ecfcaf[120];
    /* 0x1320 */ s32 x_8921bd8d;
    /* 0x1324 */ s32 x_d5f67ba6;
    /* 0x1328 */ s32 x_0f978d0c;
    /* 0x132C */ Vtx *x_b050a210[2];
    /* 0x1334 */ Vtx *x_112d334c[2];
    /* 0x133C */ x_6548b963 x_db6e53e7[20];
    /* 0x165C */ char x_e168a0c4[4];
    /* 0x1660 */ Gfx x_e4004f0d[4];
    /* 0x1680 */ s32 x_261d2b52;
    /* 0x1684 */ Object *x_4b93a6ff;
    /* 0x1688 */ u32 x_85866139;
    /* 0x168C */ u32 x_0dfa9ae9;
    /* 0x1690 */ u32 x_c013378a;
    /* 0x1694 */ u32 x_0a7ceb42;
    /* 0x1698 */ s32 x_737c37b5;
    /* 0x169C */ s32 x_49531f72;
} x_2f5c3183; // size = 0x16A0

x_562d2a02 D_8004A4D0[] = {
    { 0, 1, 2, 0 }, { 3, 4, 5, 0 }, { 6, 7, 8, 0 }, { 9, 10, 11, 0 }, { 12, 13, 14, 0 },
};

x_2f5c3183 D_800A4930[4];
u8 D_800AA3B0[4];
x_c1cedf06 D_800AA3B8;
Gfx D_800AA410[4];

void x_31ea5572(x_c1cedf06 *x_4bb24efc, Gfx *gfx) {
    x_4bb24efc->header.x_09cf7a45 = 0;
    x_4bb24efc->header.x_70b508ea = 1;
    x_4bb24efc->header.x_1256da71 = 0;
    x_4bb24efc->header.x_4c5e05f8 = 15;
    x_4bb24efc->header.x_ed66866b = 0;
    x_4bb24efc->header.x_8a54e96a = 5;
    x_4bb24efc->header.x_b7ba6d35 = gfx;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gSPNoOp(gfx++);

    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&x_4bb24efc->header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);
}

void x_38c80ca9(void) {
    s16 j;
    s16 i;
    s32 k;
    x_2f5c3183 *s2;
    x_6548b963 *s0;
    Vtx *x_d8f5cfb2;
    Vtx *x_4cf2fcb6;

    for (i = 0; i < 4; i++) {
        s2 = &D_800A4930[i];
        D_800AA3B0[i] = FALSE;

        for (j = 0; j < 12; j++) {
            x_31ea5572(&s2->x_af0aa1f8[j], s2->x_e4004f0d);
        }

        for (j = 0; j < 20; j++) {
            s0 = &s2->x_db6e53e7[j];

            s0->x_4a6530b1.x = (guRandom() % 10) << 16;
            if (guRandom() & 1) {
                s0->x_4a6530b1.x = -s0->x_4a6530b1.x;
            }
            s0->x_817784f2 = s0->x_4a6530b1.y = (-29 << 16) - ((guRandom() % 10) << 16);
            s0->x_4a6530b1.z = (guRandom() % 10) << 16;
            if (guRandom() & 1) {
                s0->x_4a6530b1.z = -s0->x_4a6530b1.z;
            }
        }

        mem_set(s2->x_38ecfcaf, 0, sizeof(s2->x_38ecfcaf));
        mem_set(s2->x_aa3a09af, 0, sizeof(s2->x_aa3a09af));

        s2->x_b050a210[0] = s2->x_38ecfcaf;
        s2->x_b050a210[1] = s2->x_38ecfcaf + 60;
        s2->x_112d334c[0] = s2->x_aa3a09af;
        s2->x_112d334c[1] = s2->x_aa3a09af + 60;

        s2->x_261d2b52 = i;

        x_d8f5cfb2 = s2->x_38ecfcaf;
        x_4cf2fcb6 = s2->x_aa3a09af;
        for (k = 0; k < 120; k++) {
            x_d8f5cfb2[k].v.cn[0] = x_d8f5cfb2[k].v.cn[1] = x_d8f5cfb2[k].v.cn[2] = x_d8f5cfb2[k].v.cn[3] = 255;
            x_4cf2fcb6[k].v.cn[0] = x_4cf2fcb6[k].v.cn[1] = x_4cf2fcb6[k].v.cn[2] = x_4cf2fcb6[k].v.cn[3] = 255;
        }
    }

    x_31ea5572(&D_800AA3B8, D_800AA410);

    D_800AA3B8.header.x_8a54e96a = D_800AA3B8.header.x_4c5e05f8 = 0;
    gDPSetPrimColor(&D_800AA410[0], 0, 0, 255, 255, 255, 255);
}

void x_071f1bfa(x_2f5c3183 *x_cc1d0de5) {
    s32 s2;
    s32 s5;
    Vtx *s4;
    x_c1cedf06 *x_65cbb149;

    s2 = x_cc1d0de5->x_d5f67ba6;
    s5 = TRUE;
    s4 = x_cc1d0de5->x_112d334c[D_8005BFCE];

    while (s2 > 0) {
        s2 -= 5;
        x_65cbb149 = &x_cc1d0de5->x_af0aa1f8[x_cc1d0de5->x_0f978d0c];
        if (s2 < 0) {
            x_65cbb149->header.x_4c5e05f8 = (s2 + 5) * 3;
            x_65cbb149->header.x_8a54e96a = s2 + 5;
        } else {
            x_65cbb149->header.x_4c5e05f8 = 15;
            x_65cbb149->header.x_8a54e96a = 5;
        }

        gExtraBatchPtr->info = x_65cbb149;
        gExtraBatchPtr->context = NULL;
        gExtraBatchPtr->vertices = s4;
        gExtraBatchPtr->triangles = D_8004A4D0;

        if (s5) {
            s5 = FALSE;
            mat4_to_mtx(&x_65cbb149->transform, &x_7eefcd11);
            x_65cbb149->header.x_70b508ea = 0;
        } else {
            x_65cbb149->header.x_70b508ea = 1;
        }
        gExtraBatchPtr++;

        s4 += 15;
        x_cc1d0de5->x_0f978d0c++;
    }
}

#ifdef NON_MATCHING
void x_dbbadf22(Object *obj) {
    s32 pad[7];
    Vtx *temp;
    Vtx *x_ec427b59;
    s32 t0;
    x_88f11482 *x_70eb54d5;
    x_88f11482 x_5d45b0f8;
    s32 v1; // spA0
    s32 pad2[11];
    x_2f5c3183 *s2 = (x_2f5c3183 *) obj->x_e2f64c57[0];
    x_6751d717 *color;
    s32 s3;
    s16 i;
    Vtx *a3;
    x_6548b963 *s0;
    s16 x, y, z;
    s32 d1, d2;
    x_c1cedf06 *x_65cbb149;
    x_88f11482 *pos;
    x_88f11482 *x_4a6530b1;

    if (x_e30d50d2 & x_520a704c) {
        D_800AA3B0[s2->x_261d2b52] = FALSE;
        obj->flags |= x_f51cb721;
        return;
    }

    x_70eb54d5 = &s2->x_4b93a6ff->pos;
    s2->x_d5f67ba6 = 0;
    s2->x_0f978d0c = D_8005BFCE * 5;
    color = (x_6751d717 *) obj->x_e2f64c57[1];

    t0 = TRUE;
    s3 = TRUE;

    if (--s2->x_737c37b5 < 0) {
        if (s2->x_85866139 >= 3) {
            s2->x_85866139 -= 3;
        } else {
            s2->x_85866139 = color->r;
        }

        if (s2->x_0dfa9ae9 >= 2) {
            s2->x_0dfa9ae9 -= 2;
        } else {
            s2->x_0dfa9ae9 = color->g;
        }

        if (s2->x_c013378a >= 0) {
            s2->x_c013378a -= 0;
        } else {
            s2->x_c013378a -= 0;
        }

        if (s2->x_0a7ceb42 >= 2) {
            s2->x_0a7ceb42 -= 2;
        } else {
            s2->x_0a7ceb42 = 0;
        }

        gDPSetPrimColor(s2->x_e4004f0d, 0, 0, s2->x_85866139, s2->x_0dfa9ae9, s2->x_c013378a, s2->x_0a7ceb42);
    }

    s0 = s2->x_db6e53e7;
    for (i = 0; i < 20; i++) {
        if (!s0[i].x_034f3eb1) {
            pos = &s0[i].pos;
            x_4a6530b1 = &s0[i].x_4a6530b1;
            t0 = FALSE;
            pos->x += x_4a6530b1->x;
            pos->z += x_4a6530b1->z;
            x_4a6530b1->y += 0x28000;
            pos->y += x_4a6530b1->y;

            if (pos->y >= 0) {
                pos->y = 0;
                x_4a6530b1->y >>= 1;
                if (x_4a6530b1->y < 0x28000) {
                    s0[i].x_034f3eb1 = TRUE;
                } else {
                    x_4a6530b1->y = -x_4a6530b1->y;
                }
            }
        }
    }

    if (t0) {
        D_800AA3B0[s2->x_261d2b52] = FALSE;
        obj->flags |= x_f51cb721;
        return;
    }

    x_5d45b0f8.x = 4;
    x_5d45b0f8.y = 6;
    x_5d45b0f8.z = 0;

    vec_rotate_by_euler(&x_5d45b0f8, &D_8013C668);

    x_ec427b59 = s2->x_b050a210[D_8005BFCE];
    a3 = s2->x_112d334c[D_8005BFCE];

    d1 = x_7eefcd11.x.z * x_70eb54d5->x + x_7eefcd11.y.z * x_70eb54d5->y + x_7eefcd11.z.z * x_70eb54d5->z +
         x_7eefcd11.w.z;

    s2->x_8921bd8d = 0;
    s2->x_d5f67ba6 = 0;

    for (i = 0; i < 20; i++) {
        if (!s0[i].x_034f3eb1) {
            pos = &s0[i].pos;
            x_4a6530b1 = &s0[i].x_4a6530b1;
            x = pos->x >> 16;
            y = pos->y >> 16;
            z = pos->z >> 16;

            d2 = x_7eefcd11.x.z * x + x_7eefcd11.y.z * y + x_7eefcd11.z.z * z + x_7eefcd11.w.z;

            if (d1 < d2) {
                x_ec427b59->v.ob[0] = x - x_5d45b0f8.x;
                x_ec427b59->v.ob[1] = y - x_5d45b0f8.y;
                x_ec427b59->v.ob[2] = z - x_5d45b0f8.z;
                x_ec427b59++;

                x_ec427b59->v.ob[0] = x + x_5d45b0f8.x;
                x_ec427b59->v.ob[1] = y - x_5d45b0f8.y;
                x_ec427b59->v.ob[2] = z + x_5d45b0f8.z;
                x_ec427b59++;

                x_ec427b59->v.ob[0] = x;
                x_ec427b59->v.ob[1] = y + x_5d45b0f8.y;
                x_ec427b59->v.ob[2] = z;
                x_ec427b59++;

                s2->x_8921bd8d++;
            } else {
                a3->v.ob[0] = x - x_5d45b0f8.x;
                a3->v.ob[1] = y - x_5d45b0f8.y;
                a3->v.ob[2] = z - x_5d45b0f8.z;
                a3++;

                a3->v.ob[0] = x + x_5d45b0f8.x;
                a3->v.ob[1] = y - x_5d45b0f8.y;
                a3->v.ob[2] = z + x_5d45b0f8.z;
                a3++;

                a3->v.ob[0] = x;
                a3->v.ob[1] = y + x_5d45b0f8.y;
                a3->v.ob[2] = z;
                a3++;

                s2->x_d5f67ba6++;
            }
            // if (1) {}
        }
    }

    v1 = s2->x_8921bd8d;
    x_ec427b59 = s2->x_b050a210[D_8005BFCE];
    while (v1 > 0) {
        v1 -= 5;
        x_65cbb149 = &s2->x_af0aa1f8[s2->x_0f978d0c];
        if (v1 < 0) {
            x_65cbb149->header.x_4c5e05f8 = (v1 + 5) * 3;
            x_65cbb149->header.x_8a54e96a = v1 + 5;
        } else {
            x_65cbb149->header.x_4c5e05f8 = 15;
            x_65cbb149->header.x_8a54e96a = 5;
        }

        // gSPTriBatch(gMainBatchPos, NULL, s00, t03, D_8004A4D0);
        gDrBatchPtr->info = x_65cbb149;
        gDrBatchPtr->context = NULL;
        gDrBatchPtr->vertices = x_ec427b59;
        gDrBatchPtr->triangles = D_8004A4D0;

        if (s3) {
            s3 = FALSE;
            mat4_to_mtx(&x_65cbb149->transform, &x_7eefcd11);
            x_65cbb149->header.x_70b508ea = 0;
        } else {
            x_65cbb149->header.x_70b508ea = 1;
        }
        gDrBatchPtr++;

        x_ec427b59 += 15;
        s2->x_0f978d0c++;
    }

    // gSPTriBatch(gMainBatchPos, NULL, &D_800AA3B8, NULL, NULL);
    gDrBatchPtr->info = &D_800AA3B8;
    gDrBatchPtr->context = NULL;
    gDrBatchPtr->vertices = NULL;
    gDrBatchPtr->triangles = NULL;
    gDrBatchPtr++;
    x_071f1bfa(s2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/sparks/x_dbbadf22.s")
void x_dbbadf22(Object *);
#endif

void x_ae0d8704(x_2758cdab *x_cc1d0de5, Object *x_84ff873b, x_6751d717 *x_2092f891) {
    s16 i;
    s16 j;
    Object *v0;
    s32 pad[2];
    x_2f5c3183 *a2;

    for (i = 0; D_800AA3B0[i] && i < 4; i++) {}

    if (i != 4) {
        D_800AA3B0[i] = TRUE;
        a2 = &D_800A4930[i];

        for (j = 0; j < 20; j++) {
            a2->x_db6e53e7[j].pos.x = x_cc1d0de5->x << 16;
            a2->x_db6e53e7[j].pos.y = x_cc1d0de5->y << 16;
            a2->x_db6e53e7[j].pos.z = x_cc1d0de5->z << 16;
            a2->x_db6e53e7[j].x_4a6530b1.y = a2->x_db6e53e7[j].x_817784f2;
            a2->x_db6e53e7[j].x_034f3eb1 = FALSE;
        }

        v0 = x_4495b42c(x_dbbadf22, 0xE00);
        v0->x_e2f64c57[0] = a2;
        v0->x_e2f64c57[1] = x_2092f891;

        a2->x_4b93a6ff = x_84ff873b;
        a2->x_d5f67ba6 = 0;
        a2->x_85866139 = 255;
        a2->x_0dfa9ae9 = 255;
        a2->x_c013378a = 255;
        a2->x_0a7ceb42 = 255;
        a2->x_737c37b5 = 7;
    }
}
