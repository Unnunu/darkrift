#include "common.h"
#include "camera.h"
#include "PR/gt.h"

typedef struct UnkThetaSub {
    /* 0x00 */ Vec4i pos;
    /* 0x10 */ Vec4i vel;
    /* 0x20 */ u8 unk_20;
    /* 0x24 */ s32 unk_24;
} UnkThetaSub; // size = 0x28

typedef struct UnkTheta {
    /* 0x0000 */ BatchInfo unk_00[12];
    /* 0x0420 */ Vtx unk_420[120];
    /* 0x0BA0 */ Vtx unk_BA0[120];
    /* 0x1320 */ s32 unk_1320;
    /* 0x1324 */ s32 unk_1324;
    /* 0x1328 */ s32 unk_1328;
    /* 0x132C */ Vtx *unk_132C[2];
    /* 0x1334 */ Vtx *unk_1334[2];
    /* 0x133C */ UnkThetaSub unk_133C[20];
    /* 0x165C */ char unk_165C[4];
    /* 0x1660 */ Gfx unk_1660[4];
    /* 0x1680 */ s32 unk_1680;
    /* 0x1684 */ Object *unk_1684;
    /* 0x1688 */ u32 unk_1688;
    /* 0x168C */ u32 unk_168C;
    /* 0x1690 */ u32 unk_1690;
    /* 0x1694 */ u32 unk_1694;
    /* 0x1698 */ s32 unk_1698;
    /* 0x169C */ s32 unk_169C;
} UnkTheta; // size = 0x16A0

u8 D_8004A4D0[] = {
    0, 1, 2, 0, 3, 4, 5, 0, 6, 7, 8, 0, 9, 10, 11, 0, 12, 13, 14, 0,
};

UnkTheta D_800A4930[4];
u8 D_800AA3B0[4];
BatchInfo D_800AA3B8;
Gfx D_800AA410[4];

void func_80023100(BatchInfo *batch, Gfx *gfx) {
    batch->header.unk_00 = 0;
    batch->header.unk_0B = 1;
    batch->header.unk_04 = 0;
    batch->header.numVertices = 15;
    batch->header.unk_09 = 0;
    batch->header.numTriangles = 5;
    batch->header.texGfx = gfx;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gSPNoOp(gfx++);

    gtStateSetOthermode(&batch->header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&batch->header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&batch->header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&batch->header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);
}

void func_80023200(void) {
    s16 j;
    s16 i;
    s32 k;
    UnkTheta *s2;
    UnkThetaSub *s0;
    Vtx *ptr1;
    Vtx *ptr2;

    for (i = 0; i < 4; i++) {
        s2 = &D_800A4930[i];
        D_800AA3B0[i] = FALSE;

        for (j = 0; j < 12; j++) {
            func_80023100(&s2->unk_00[j], s2->unk_1660);
        }

        for (j = 0; j < 20; j++) {
            s0 = &s2->unk_133C[j];

            s0->vel.x = (guRandom() % 10) << 16;
            if (guRandom() & 1) {
                s0->vel.x = -s0->vel.x;
            }
            s0->unk_24 = s0->vel.y = (-29 << 16) - ((guRandom() % 10) << 16);
            s0->vel.z = (guRandom() % 10) << 16;
            if (guRandom() & 1) {
                s0->vel.z = -s0->vel.z;
            }
        }

        mem_fill(s2->unk_BA0, 0, sizeof(s2->unk_BA0));
        mem_fill(s2->unk_420, 0, sizeof(s2->unk_420));

        s2->unk_132C[0] = s2->unk_BA0;
        s2->unk_132C[1] = s2->unk_BA0 + 60;
        s2->unk_1334[0] = s2->unk_420;
        s2->unk_1334[1] = s2->unk_420 + 60;

        s2->unk_1680 = i;

        ptr1 = s2->unk_BA0;
        ptr2 = s2->unk_420;
        for (k = 0; k < 120; k++) {
            ptr1[k].v.cn[0] = ptr1[k].v.cn[1] = ptr1[k].v.cn[2] = ptr1[k].v.cn[3] = 255;
            ptr2[k].v.cn[0] = ptr2[k].v.cn[1] = ptr2[k].v.cn[2] = ptr2[k].v.cn[3] = 255;
        }
    }

    func_80023100(&D_800AA3B8, D_800AA410);

    D_800AA3B8.header.numTriangles = D_800AA3B8.header.numVertices = 0;
    gDPSetPrimColor(&D_800AA410[0], 0, 0, 255, 255, 255, 255);
}

void func_800234E4(UnkTheta *arg0) {
    s32 s2;
    s32 s5;
    Vtx *s4;
    BatchInfo *s00;

    s2 = arg0->unk_1324;
    s5 = TRUE;
    s4 = arg0->unk_1334[D_8005BFCE];

    while (s2 > 0) {
        s2 -= 5;
        s00 = &arg0->unk_00[arg0->unk_1328];
        if (s2 < 0) {
            s00->header.numVertices = (s2 + 5) * 3;
            s00->header.numTriangles = s2 + 5;
        } else {
            s00->header.numVertices = 15;
            s00->header.numTriangles = 5;
        }

        gOverlayBatchPos->info = s00;
        gOverlayBatchPos->context = NULL;
        gOverlayBatchPos->vertices = s4;
        gOverlayBatchPos->triangles = D_8004A4D0;

        if (s5) {
            s5 = FALSE;
            math_mtxf2mtx(&s00->transform, &gCameraProjectionMatrix);
            s00->header.unk_0B = 0;
        } else {
            s00->header.unk_0B = 1;
        }
        gOverlayBatchPos++;

        s4 += 15;
        arg0->unk_1328++;
    }
}

#ifdef NON_MATCHING
void func_80023628(Object *obj) {
    s32 pad[7];
    Vtx *temp;
    Vtx *t02;
    s32 t0;
    Vec4i *spB4;
    Vec4i spA4;
    s32 v1; // spA0
    s32 pad2[11];
    UnkTheta *s2 = (UnkTheta *) obj->varObj[0];
    ColorRGBA *color;
    s32 s3;
    s16 i;
    Vtx *a3;
    UnkThetaSub *s0;
    s16 x, y, z;
    s32 d1, d2;
    BatchInfo *s00;
    Vec4i *pos;
    Vec4i *vel;

    if (D_8005BFC0 & 0x2000) {
        D_800AA3B0[s2->unk_1680] = FALSE;
        obj->flags |= 0x10;
        return;
    }

    spB4 = &s2->unk_1684->pos;
    s2->unk_1324 = 0;
    s2->unk_1328 = D_8005BFCE * 5;
    color = (ColorRGBA *) obj->varObj[1];

    t0 = TRUE;
    s3 = TRUE;

    if (--s2->unk_1698 < 0) {
        if (s2->unk_1688 >= 3) {
            s2->unk_1688 -= 3;
        } else {
            s2->unk_1688 = color->r;
        }

        if (s2->unk_168C >= 2) {
            s2->unk_168C -= 2;
        } else {
            s2->unk_168C = color->g;
        }

        if (s2->unk_1690 >= 0) {
            s2->unk_1690 -= 0;
        } else {
            s2->unk_1690 -= 0;
        }

        if (s2->unk_1694 >= 2) {
            s2->unk_1694 -= 2;
        } else {
            s2->unk_1694 = 0;
        }

        gDPSetPrimColor(s2->unk_1660, 0, 0, s2->unk_1688, s2->unk_168C, s2->unk_1690, s2->unk_1694);
    }

    s0 = s2->unk_133C;
    for (i = 0; i < 20; i++) {
        if (!s0[i].unk_20) {
            pos = &s0[i].pos;
            vel = &s0[i].vel;
            t0 = FALSE;
            pos->x += vel->x;
            pos->z += vel->z;
            vel->y += 0x28000;
            pos->y += vel->y;

            if (pos->y >= 0) {
                pos->y = 0;
                vel->y >>= 1;
                if (vel->y < 0x28000) {
                    s0[i].unk_20 = TRUE;
                } else {
                    vel->y = -vel->y;
                }
            }
        }
    }

    if (t0) {
        D_800AA3B0[s2->unk_1680] = FALSE;
        obj->flags |= 0x10;
        return;
    }

    spA4.x = 4;
    spA4.y = 6;
    spA4.z = 0;

    func_8001370C(&spA4, &D_8013C668);

    t02 = s2->unk_132C[D_8005BFCE];
    a3 = s2->unk_1334[D_8005BFCE];

    d1 = gCameraProjectionMatrix.x.z * spB4->x + gCameraProjectionMatrix.y.z * spB4->y +
         gCameraProjectionMatrix.z.z * spB4->z + gCameraProjectionMatrix.w.z;

    s2->unk_1320 = 0;
    s2->unk_1324 = 0;

    for (i = 0; i < 20; i++) {
        if (!s0[i].unk_20) {
            pos = &s0[i].pos;
            vel = &s0[i].vel;
            x = pos->x >> 16;
            y = pos->y >> 16;
            z = pos->z >> 16;

            d2 = gCameraProjectionMatrix.x.z * x + gCameraProjectionMatrix.y.z * y + gCameraProjectionMatrix.z.z * z +
                 gCameraProjectionMatrix.w.z;

            if (d1 < d2) {
                t02->v.ob[0] = x - spA4.x;
                t02->v.ob[1] = y - spA4.y;
                t02->v.ob[2] = z - spA4.z;
                t02++;

                t02->v.ob[0] = x + spA4.x;
                t02->v.ob[1] = y - spA4.y;
                t02->v.ob[2] = z + spA4.z;
                t02++;

                t02->v.ob[0] = x;
                t02->v.ob[1] = y + spA4.y;
                t02->v.ob[2] = z;
                t02++;

                s2->unk_1320++;
            } else {
                a3->v.ob[0] = x - spA4.x;
                a3->v.ob[1] = y - spA4.y;
                a3->v.ob[2] = z - spA4.z;
                a3++;

                a3->v.ob[0] = x + spA4.x;
                a3->v.ob[1] = y - spA4.y;
                a3->v.ob[2] = z + spA4.z;
                a3++;

                a3->v.ob[0] = x;
                a3->v.ob[1] = y + spA4.y;
                a3->v.ob[2] = z;
                a3++;

                s2->unk_1324++;
            }
            // if (1) {}
        }
    }

    v1 = s2->unk_1320;
    t02 = s2->unk_132C[D_8005BFCE];
    while (v1 > 0) {
        v1 -= 5;
        s00 = &s2->unk_00[s2->unk_1328];
        if (v1 < 0) {
            s00->header.numVertices = (v1 + 5) * 3;
            s00->header.numTriangles = v1 + 5;
        } else {
            s00->header.numVertices = 15;
            s00->header.numTriangles = 5;
        }

        // gSPTriBatch(gMainBatchPos, NULL, s00, t03, D_8004A4D0);
        gMainBatchPos->info = s00;
        gMainBatchPos->context = NULL;
        gMainBatchPos->vertices = t02;
        gMainBatchPos->triangles = D_8004A4D0;

        if (s3) {
            s3 = FALSE;
            math_mtxf2mtx(&s00->transform, &gCameraProjectionMatrix);
            s00->header.unk_0B = 0;
        } else {
            s00->header.unk_0B = 1;
        }
        gMainBatchPos++;

        t02 += 15;
        s2->unk_1328++;
    }

    // gSPTriBatch(gMainBatchPos, NULL, &D_800AA3B8, NULL, NULL);
    gMainBatchPos->info = &D_800AA3B8;
    gMainBatchPos->context = NULL;
    gMainBatchPos->vertices = NULL;
    gMainBatchPos->triangles = NULL;
    gMainBatchPos++;
    func_800234E4(s2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/23D00/func_80023628.s")
void func_80023628(Object *);
#endif

void func_80023BE4(Vec4s *arg0, Object *arg1, ColorRGBA *arg2) {
    s16 i;
    s16 j;
    Object *v0;
    s32 pad[2];
    UnkTheta *a2;

    for (i = 0; D_800AA3B0[i] && i < 4; i++) {}

    if (i != 4) {
        D_800AA3B0[i] = TRUE;
        a2 = &D_800A4930[i];

        for (j = 0; j < 20; j++) {
            a2->unk_133C[j].pos.x = arg0->x << 16;
            a2->unk_133C[j].pos.y = arg0->y << 16;
            a2->unk_133C[j].pos.z = arg0->z << 16;
            a2->unk_133C[j].vel.y = a2->unk_133C[j].unk_24;
            a2->unk_133C[j].unk_20 = FALSE;
        }

        v0 = create_worker(func_80023628, 0xE00);
        v0->varObj[0] = a2;
        v0->varObj[1] = arg2;

        a2->unk_1684 = arg1;
        a2->unk_1324 = 0;
        a2->unk_1688 = 255;
        a2->unk_168C = 255;
        a2->unk_1690 = 255;
        a2->unk_1694 = 255;
        a2->unk_1698 = 7;
    }
}
