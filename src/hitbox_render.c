#include "common.h"
#include "PR/gt.h"
#include "task.h"
#include "camera.h"

BatchTriangle D_800499B0[] = {
    { 0, 1, 4, 0 },
    { 1, 2, 4, 0 },
    { 2, 3, 4, 0 },
};
BatchTriangle D_800499BC[] = {
    { 0, 1, 4, 0 },
    { 4, 1, 5, 0 },
    { 1, 2, 5, 0 },
    { 2, 3, 5, 0 },
};
BatchTriangle D_800499CC[] = {
    { 0, 1, 4, 0 }, { 4, 1, 5, 0 }, { 5, 1, 2, 0 }, { 5, 2, 6, 0 }, { 6, 2, 3, 0 },
};
BatchTriangle D_800499E0[] = {
    { 0, 1, 4, 0 }, { 4, 1, 5, 0 }, { 5, 1, 2, 0 }, { 5, 2, 6, 0 }, { 6, 2, 3, 0 }, { 6, 3, 7, 0 },
};

BatchTriangle D_800499F8[] = {
    { 0, 2, 1, 0 },
    { 2, 3, 1, 0 },
    { 3, 4, 1, 0 },
    { 4, 5, 1, 0 },
};
BatchTriangle D_80049A08[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 2, 3, 6, 0 }, { 3, 4, 6, 0 }, { 4, 5, 6, 0 },
};
BatchTriangle D_80049A1C[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 2, 3, 6, 0 }, { 6, 3, 7, 0 }, { 3, 4, 7, 0 }, { 4, 5, 7, 0 },
};
BatchTriangle D_80049A34[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 6, 2, 3, 0 }, { 6, 3, 7, 0 }, { 7, 3, 4, 0 }, { 7, 4, 8, 0 }, { 8, 4, 5, 0 },
};
BatchTriangle D_80049A50[] = {
    { 0, 2, 1, 0 }, { 1, 2, 6, 0 }, { 6, 2, 3, 0 }, { 6, 3, 7, 0 },
    { 7, 3, 4, 0 }, { 7, 4, 8, 0 }, { 8, 4, 5, 0 }, { 8, 5, 9, 0 },
};

BatchTriangle *D_80049A70[] = { D_800499F8, D_80049A08, D_80049A1C, D_80049A34, D_80049A50 };
BatchTriangle *D_80049A84[] = { D_800499B0, D_800499BC, D_800499CC, D_800499E0 };

Matrix4f D_80049A94 = {
    { -0.5, 1.5, -1.5, 0.5 },
    { 1, -2.5, 2, -0.5 },
    { -0.5, 0, 0.5, 0 },
    { 0, 1, 0, 0 },
};

/* .bss */
Gfx D_80081280[4];

void ring_buffer_init(PositionRingBuffer *arg0, s32 arg1) {
    arg0->readIndex = 0;
    arg0->writeIndex = 0;
    arg0->bufferMask = arg1;
    arg0->count = 0;
}

void ring_buffer_push(PositionRingBuffer *arg0, Vec4i *arg1) {
    s32 v0;

    v0 = arg0->writeIndex;

    if (arg0->count != 0 && arg0->readIndex == v0) {
        arg0->readIndex++;
        arg0->readIndex &= arg0->bufferMask;
    } else {
        arg0->count++;
    }

    arg0->positions[v0].x = arg1->x;
    arg0->positions[v0].y = arg1->y;
    arg0->positions[v0].z = arg1->z;

    v0++;
    v0 &= arg0->bufferMask;
    arg0->writeIndex = v0;
}

s32 ring_buffer_pop(PositionRingBuffer *arg0, Vec4i **arg1) {
    s32 v1;

    v1 = arg0->readIndex;
    if (arg0->count == 0) {
        v1--;
        if (v1 < 0) {
            v1 = 3;
        }
        *arg1 = &arg0->positions[v1 - 1];
        return 0;
    } else {
        *arg1 = &arg0->positions[v1];
        v1++;
        v1 &= arg0->bufferMask;
        arg0->readIndex = v1;
        arg0->count--;
        // @bug UB: should be return 1;
    }
}

void spline_interpolator_init(SplineInterpolator *arg0) {
    ring_buffer_init(&arg0->inputBuffer, 3);
    ring_buffer_init(&arg0->outputBuffer, 3);
}

s32 spline_compute_basis(SplineInterpolator *arg0) {
    Matrix4f *A0;
    Vec4i *sp30;
    Vec4i *sp2C;
    Vec4i *sp28;
    Vec4i *sp24;

    A0 = &arg0->splineMatrix;

    if (arg0->inputBuffer.count != 4) {
        return FALSE;
    }

    ring_buffer_pop(&arg0->inputBuffer, &sp30);
    ring_buffer_pop(&arg0->inputBuffer, &sp2C);
    ring_buffer_pop(&arg0->inputBuffer, &sp28);
    ring_buffer_pop(&arg0->inputBuffer, &sp24);

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

    ring_buffer_push(&arg0->inputBuffer, sp2C);
    ring_buffer_push(&arg0->inputBuffer, sp28);
    ring_buffer_push(&arg0->inputBuffer, sp24);

    return TRUE;
}

void spline_feed_position(SplineInterpolator *arg0, Vec4i *arg1) {
    f32 fs0, fs1, fs2;
    f32 fs3, fs4, fs5;
    s32 i;
    f32 spB0, spAC, spA8;
    f32 spA4, spA0, sp9C;
    Vec4i sp8C;
    Matrix4f *A0;

    A0 = &arg0->splineMatrix;

    ring_buffer_push(arg0, arg1);

    if (spline_compute_basis(arg0)) {
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

            ring_buffer_push(&arg0->outputBuffer, &sp8C);
        }
    }
}

s32 spline_read_output(SplineInterpolator *arg0, Vec4i **arg1) {
    return ring_buffer_pop(&arg0->outputBuffer, arg1);
}

void init_overlay_batch_info(BatchInfo *batch) {
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

void hitbox_render_update(MotionTrail *arg0, u8 arg1) {
    Vec4i spF8;
    Vec4i *spF4;
    u8 spF3;
    u8 spF2;
    Matrix4f *s0;
    Matrix4f *v0;
    HitboxTrailSegment *s5;
    HitboxTrailSegment *s4;
    u32 t2;
    u32 spD8;
    s32 s3;
    Vtx *s2;
    s32 _a2, _a1, _a0, _t4, _t3, _t1, _t0, _a3;
    Vec4i *spAC;
    u32 v1;
    s32 lo1, lo2, lo3, lo4, lo5, lo6, lo7, lo8;
    u32 i;
    u32 j;
    BatchInfo *s03;
    s32 k;
    Vtx *vtx_v0;
    s32 temp1, temp2;
    HitboxTrailSegment *sub2;
    f32 temp;
    f32 x;

    v0 = arg0->boneMatrixB;
    s0 = arg0->boneMatrixA;
    spAC = arg0->refPosition;

    x = v0->w.x;                                                                // @FAKE
    temp = v0->w.x * v0->w.x + v0->w.y * v0->w.y + v0->w.z * v0->w.z + v0->w.z; // @FAKE
    if (temp == 0) {}                                                           // @FAKE
    spF8.x = v0->w.x;
    spF8.y = v0->w.y;
    spF8.z = v0->w.z;
    arg0->boneBPosX = spF8.x;
    arg0->boneBPosY = spF8.y;
    arg0->boneBPosZ = spF8.z;
    spline_feed_position(&arg0->splineB, &spF8);

    temp = s0->w.x * s0->w.x + s0->w.y * s0->w.y + s0->w.z * s0->w.z + s0->w.z; // @FAKE
    if (temp == 0) {}                                                           // @FAKE
    spF8.x = s0->w.x;
    spF8.y = s0->w.y;
    spF8.z = s0->w.z;
    arg0->boneAPosX = spF8.x;
    arg0->boneAPosY = spF8.y;
    arg0->boneAPosZ = spF8.z;
    spline_feed_position(&arg0->splineA, &spF8);

    if (!gIsPaused && arg1 && !(gGlobalFlags & GAME_FLAG_BATTLE_FINISHED) && arg0->segmentCount < 16) {
        s5 = &arg0->segments[arg0->segmentCount];
        s4 = NULL;

        if (arg0->segmentCount == 0) {
            s3 = 0;
            s2 = s5->vertices;
        } else {
            s4 = &arg0->segments[arg0->segmentCount - 1];
            vtx_v0 = s4->vertices;
            s2 = s5->vertices;

            if (arg0->segmentCount == 1) {
                s2[0].v.ob[0] = vtx_v0[3].v.ob[0];
                s2[0].v.ob[1] = vtx_v0[3].v.ob[1];
                s2[0].v.ob[2] = vtx_v0[3].v.ob[2];
                s2[0].v.cn[3] = 200;

                i = s4->vertexCount - 1;

                s2[1].v.ob[0] = vtx_v0[i].v.ob[0];
                s2[1].v.ob[1] = vtx_v0[i].v.ob[1];
                s2[1].v.ob[2] = vtx_v0[i].v.ob[2];
                s2[1].v.cn[3] = 200;
            } else {
                s2[0].v.ob[0] = vtx_v0[5].v.ob[0];
                s2[0].v.ob[1] = vtx_v0[5].v.ob[1];
                s2[0].v.ob[2] = vtx_v0[5].v.ob[2];
                s2[0].v.cn[3] = 200;

                i = s4->vertexCount - 1;
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

        arg0->segmentCount++;
        s5->lifetime = arg0->segmentCount * 16;
        if (s5->lifetime > 14) {
            s5->lifetime = 14;
        }

        spline_read_output(&arg0->splineB, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        spline_read_output(&arg0->splineB, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        spline_read_output(&arg0->splineB, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        spline_read_output(&arg0->splineB, &spF4);
        s2[s3].v.cn[3] = 200;
        s2[s3].v.ob[0] = spF4->x;
        s2[s3].v.ob[1] = spF4->y;
        s2[s3].v.ob[2] = spF4->z;
        s3++;

        if (spline_read_output(&arg0->splineA, &spF4)) {
            if (arg0->segmentCount == 1 || spF4->x != s2[1].v.ob[0] || spF4->y != s2[1].v.ob[1] ||
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
            s5->isBehind = temp1 < temp2;
        } else if (s4 != NULL) {
            s5->isBehind = s4->isBehind;
        } else {
            arg0->segmentCount = 0;
            return;
        }

        if (spline_read_output(&arg0->splineA, &spF4)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = spF4->x;
            s2[s3].v.ob[1] = spF4->y;
            s2[s3].v.ob[2] = spF4->z;
            s3++;
        }
        if (spline_read_output(&arg0->splineA, &spF4)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = spF4->x;
            s2[s3].v.ob[1] = spF4->y;
            s2[s3].v.ob[2] = spF4->z;
            s3++;
        }
        if (spline_read_output(&arg0->splineA, &spF4)) {
            s2[s3].v.cn[3] = 200;
            s2[s3].v.ob[0] = spF4->x;
            s2[s3].v.ob[1] = spF4->y;
            s2[s3].v.ob[2] = spF4->z;
            s3++;
        }

        s5->vertexCount = s3;
        s5->triangleCount = s3 - 2;
        if (arg0->segmentCount == 1) {
            s5->triangles = D_80049A84[s3 - 5];
        } else {
            s5->triangles = D_80049A70[s3 - 6];
        }
    }

    spF3 = FALSE;
    spF2 = TRUE;

    if (arg0->segmentCount != 0) {
        t2 = v1 = 0;
        spF3 = FALSE;

        for (i = 0; i < arg0->segmentCount; i++) {
            sub2 = arg0->segments + i;
            if (i != 0) {
                t2 += 5;
                v1 += sub2->vertexCount - 5;
            } else {
                t2 += 4;
                v1 += sub2->vertexCount - 4;
            }
        }

        _t4 = _t3 = 0;
        _a2 = _a1 = _a0 = 255;
        _t1 = _t0 = _a3 = 255;

        lo1 = (255 - arg0->baseColor.r) / t2;
        lo2 = (255 - arg0->baseColor.g) / t2;
        lo3 = (255 - arg0->baseColor.b) / t2;

        lo4 = (255 - arg0->baseColor.r) / v1;
        lo5 = (255 - arg0->baseColor.g) / v1;
        lo6 = (255 - arg0->baseColor.b) / v1;

        lo7 = 140 / t2;
        lo8 = 140 / v1;

        sub2 = arg0->segments;
        vtx_v0 = sub2->vertices;
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

        for (spD8 = 1; spD8 < arg0->segmentCount; spD8++) {
            sub2 = arg0->segments + spD8;
            vtx_v0 = sub2->vertices;

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

                if (_t1 < arg0->baseColor.r) {
                    _t1 = arg0->baseColor.r;
                }
                if (_t0 < arg0->baseColor.g) {
                    _t0 = arg0->baseColor.g;
                }
                if (_a3 < arg0->baseColor.b) {
                    _a3 = arg0->baseColor.b;
                }

                vtx_v0[4 + k].v.cn[0] = _a2;
                vtx_v0[4 + k].v.cn[1] = _a1;
                vtx_v0[4 + k].v.cn[2] = _a0;
                vtx_v0[4 + k].v.cn[3] = _t3;

                _t3 += lo8;
                _a2 -= lo4;
                _a0 -= lo6;
                _a1 -= lo5;

                if (_a2 < arg0->baseColor.r) {
                    _a2 = arg0->baseColor.r;
                }
                if (_a1 < arg0->baseColor.g) {
                    _a1 = arg0->baseColor.g;
                }
                if (_a0 < arg0->baseColor.b) {
                    _a0 = arg0->baseColor.b;
                }
            }
        }
    }

    for (j = 0; j < arg0->segmentCount; j++) {
        sub2 = arg0->segments + j;
        if (!gIsPaused) {
            sub2->lifetime--;
        }
        if (D_8008012C & GFX_FLAG_10) {
            sub2->lifetime -= 2;
        }

        if (sub2->lifetime > 0 && !sub2->isBehind) {
            gMainBatchPos->context = NULL;

            if (!spF3) {
                s03 = arg0->unk_12D8 + D_8005BFCE;
                math_mtxf2mtx(&s03->transform, &gCameraProjectionMatrix);
                spF3 = TRUE;
                spF2 = FALSE;
            } else {
                s03 = &sub2->batchInfo;
            }
            s03->header.vtxNum = sub2->vertexCount;
            s03->header.numTriangles = sub2->triangleCount;
            gMainBatchPos->info = s03;
            gMainBatchPos->vertices = sub2->vertices;
            gMainBatchPos->triangles = sub2->triangles;
            gMainBatchPos++;
        }
    }

    spF3 = FALSE;
    for (j = 0; j < arg0->segmentCount; j++) {
        sub2 = arg0->segments + j;

        if (!gIsPaused) {
            sub2->lifetime--;
        }
        if (D_8008012C & GFX_FLAG_10) {
            sub2->lifetime -= 2;
        }

        if (sub2->lifetime > 0 && sub2->isBehind) {
            gOverlayBatchPos->context = NULL;

            if (!spF3) {
                s03 = arg0->unk_12D8 + 2 + D_8005BFCE;
                math_mtxf2mtx(&s03->transform, &gCameraProjectionMatrix);
                spF3 = TRUE;
                spF2 = FALSE;
            } else {
                s03 = &sub2->batchInfo;
            }
            s03->header.vtxNum = sub2->vertexCount;
            s03->header.numTriangles = sub2->triangleCount;
            gOverlayBatchPos->info = s03;
            gOverlayBatchPos->vertices = sub2->vertices;
            gOverlayBatchPos->triangles = sub2->triangles;
            gOverlayBatchPos++;
        }
    }

    if (spF2) {
        arg0->segmentCount = 0;
    }
}

void motion_trail_init(MotionTrail *trail, ModelInstance *modelInst, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4,
                       ColorRGBA *arg5) {
    u32 i, j;
    Gfx *gfx;
    u32 a;
    HitboxTrailSegment *s6;
    BatchInfo *s2;

    trail->modelInst = modelInst;
    trail->boneMatrixA = arg2;
    trail->boneMatrixB = arg3;

    spline_interpolator_init(&trail->splineB);
    spline_interpolator_init(&trail->splineA);

    trail->unk_1CC = 0;
    trail->segmentCount = 0;
    trail->refPosition = arg4;

    gfx = D_80081280;
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
    gSPNoOp(gfx++);

    for (i = 0; i < 4; i++) {
        s2 = trail->unk_12D8 + i;
        init_overlay_batch_info(s2);
        s2->header.texGfx = D_80081280;
        s2->header.unk_0B = 0;
    }

    for (i = 0; i < 16; i++) {
        s6 = &trail->segments[i];
        init_overlay_batch_info(&s6->batchInfo);
        mem_fill(s6->vertices, 0, sizeof(Vtx) * 8);

        a = 200;
        if (i == 0) {
            for (j = 0; j < 4; j++) {
                s6->vertices[j].v.cn[0] = arg5->r;
                s6->vertices[j].v.cn[1] = arg5->g;
                s6->vertices[j].v.cn[2] = arg5->b;
                s6->vertices[j].v.cn[3] = a;
                s6->vertices[j + 4].v.cn[0] = arg5->r;
                s6->vertices[j + 4].v.cn[1] = arg5->g;
                s6->vertices[j + 4].v.cn[2] = arg5->b;
                s6->vertices[j + 4].v.cn[3] = a;
                a += 4;
            }
        } else {
            s6->vertices[0].v.cn[0] = arg5->r;
            s6->vertices[0].v.cn[1] = arg5->g;
            s6->vertices[0].v.cn[2] = arg5->b;
            s6->vertices[0].v.cn[3] = a;
            s6->vertices[1].v.cn[0] = arg5->r;
            s6->vertices[1].v.cn[1] = arg5->g;
            s6->vertices[1].v.cn[2] = arg5->b;
            s6->vertices[1].v.cn[3] = a;
            a += 4;

            for (j = 2; j < 6; j++) {
                s6->vertices[j].v.cn[0] = arg5->r;
                s6->vertices[j].v.cn[1] = arg5->g;
                s6->vertices[j].v.cn[2] = arg5->b;
                s6->vertices[j].v.cn[3] = a;
                s6->vertices[j + 4].v.cn[0] = arg5->r;
                s6->vertices[j + 4].v.cn[1] = arg5->g;
                s6->vertices[j + 4].v.cn[2] = arg5->b;
                s6->vertices[j + 4].v.cn[3] = a;
                a += 4;
                if (a > 255) {
                    a = 255;
                }
            }
        }

        s6->lifetime = -1;
    }

    trail->boneBPosX = trail->boneBPosY = trail->boneBPosZ = 0.0f;
    trail->boneAPosX = trail->boneAPosY = trail->boneAPosZ = 0.0f;

    trail->baseColor.r = arg5->r;
    trail->baseColor.g = arg5->g;
    trail->baseColor.b = arg5->b;
}
