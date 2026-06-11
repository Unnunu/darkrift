#include "common.h"
#include "PR/gt.h"
#include "task.h"

#define g_PERSPNORM(pkt, dl)                        \
    {                                               \
        Gfx *_g = (Gfx *) (pkt);                    \
        _g->words.w0 = _SHIFTL(G_PERSPNORM, 24, 8); \
        _g->words.w1 = (dl);                        \
    }

extern s32 D_80049CF0;
extern ScreenProfile gScreenProfiles[];
extern Gfx D_8004CA68[];
extern Gfx D_8004CB00[];

extern s32 x_b5cc849a;
extern s32 x_aec099eb;

extern x_3e2f9cf1 D_8004CC20;
extern x_c1cedf06 D_8004CCC8;
extern x_c1cedf06 D_8004CD30;

extern u16 x_e30d50d2;
extern u16 x_e38a6e19;
extern u16 D_8005BFCE;

extern Gfx *gOverlayDlPtr;
extern s16 sOverlayBrightness;
extern s32 gGfxFlags;
extern RenderCallback sRenderCallbacks[20];
extern s32 sRenderCallbackArgs[20];

/* .data */

s16 D_80049290[] = { 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 1000, 0 };
s32 gFrameCounter = 0;
Vtx sQuadVtx[2][4] = { { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                         { { { x_56e08f29 << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                         { { { 0, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                         { { { x_56e08f29 << 2, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } },
                       { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                         { { { x_56e08f29 << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                         { { { 0, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                         { { { x_56e08f29 << 2, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } } };
x_562d2a02 sQuadTri[] = { { 0, 1, 2, 0 }, { 2, 1, 3, 0 } };
s32 D_80049338[] = { 0, 0, 0 };
x_acccb624 sZeroVelocity = { 0, 0, 0 };
x_88f11482 sZeroPosition = { 0, 0, 0, 0 };
x_2bb4cf6f sDefaultLights = { { { { 255, 255, 255, 255 }, 0, 0, -127 }, { { 0, 0, 0, 255 }, 73, -73, -73 } } };
UnkStruct10 D_8004937C = { 0, 90, 0, 0 };
UnkStruct10 D_80049384 = { 0, 233, 500, 0 };

/* .bss */
s16 gCurrentScreenId;
s16 sPrevScreenId;
OSTime unused;
OSTime sRenderTimeAccum;
OSTime gRspTimeTotal;
OSTime gRdpTimeTotal;
s32 sFrameCounter;
s32 sFadeAlpha;
x_c1cedf06 sQuadBatch;
Gfx sQuadDl[5];
Mtx sScratchMtx;
u16 x_e30d50d2;
u16 x_e38a6e19;
s32 D_8005BFC4;
u16 x_c84980f9;
u16 x_a4f5fb93;
u16 D_8005BFCC;
u16 D_8005BFCE;
void *gFramebuffers[2];
Gfx *gF3dDisplayListPtr;
Gfx *gOverlayDlPtr;
Gfx *gF3dExtraListPtr;
x_320b5d80 *gDrBatchPtr;
x_320b5d80 *gExtraBatchPtr;
x_ee01e8c6 D_8005BFF0[2];
x_ee01e8c6 *D_80080100;

void rsp_wait_idle(void);
// void execute_scheduled_tasks(void);
void rsp_game_init(u16);
void x_2d5f067a(void);
void rsp_game_reinit(u16);
void obj_scene_update(void);
void rsp_clear_screen(void);
void x_77751af8(void);
void x_ff4031b5(void);
void x_06fa0af9(void);
void tr_fade_start(Object *obj);

void gfx_init_frame(void) {
    D_80080100 = &D_8005BFF0[D_8005BFCE];
    gF3dDisplayListPtr = D_80080100->x_700a6ea1;
    gDrBatchPtr = D_80080100->x_79588dca;

    gSPSegment(gF3dDisplayListPtr++, 0x01, gFramebuffers[D_8005BFCE]);
    gSPSegment(gF3dDisplayListPtr++, 0x00, 0x00000000);

    D_8004CC20.x_cf1ea5d1[0] = 0;
    D_8004CC20.x_cf1ea5d1[1] = x_a4e17949(gFramebuffers[D_8005BFCE]);

    x_50746900(gDrBatchPtr, (x_3e2f9cf1 *) osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    gDPFullSync(gF3dDisplayListPtr++);
    gSPEndDisplayList(gF3dDisplayListPtr++);
    x_50746900(gDrBatchPtr, NULL, &D_8004CD30, NULL, NULL);
    x_50746900(gDrBatchPtr, NULL, NULL, NULL, NULL);
    rsp_wait_idle();
    rsp_vi_sync(TRUE);
    rsp_submit_gfx_tasks();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
}

void gfx_render_frame(void) {
    OSTime x_de1dd2f4;
    x_320b5d80 *ptr;
    s32 i;

    x_de1dd2f4 = osGetTime();
    button_update_frame();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
    gF3dDisplayListPtr = D_80080100->x_700a6ea1;
    gOverlayDlPtr = D_80080100->x_5b2cc439;
    gF3dExtraListPtr = D_80080100->x_a4c192ba;
    gDrBatchPtr = D_80080100->x_79588dca;
    gExtraBatchPtr = D_80080100->x_b8131490;

    gSPSegment(gF3dDisplayListPtr++, 0x01, gFramebuffers[D_8005BFCE]);
    gSPSegment(gF3dDisplayListPtr++, 0x00, 0x00000000);

    D_8004CC20.x_cf1ea5d1[0] = 0;
    D_8004CC20.x_cf1ea5d1[1] = x_c485761a(gFramebuffers[D_8005BFCE]);

    if (gGfxFlags & GFX_EXTRA_DL) {
        gSPDisplayList(gF3dExtraListPtr++, D_8004CA68);
    }

    x_50746900(gDrBatchPtr, (x_3e2f9cf1 *) osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    obj_scene_update();
    gSPDisplayList(gF3dDisplayListPtr++, D_8004CA68);
    rsp_clear_screen();
    x_77751af8();

    if (!(gGfxFlags & GFX_SKIP_SCENE)) {
        gSPDisplayList(gF3dDisplayListPtr++, D_80080100->x_5b2cc439);
    }
    gSPDisplayList(gF3dDisplayListPtr++, D_8004CB00);
    gSPMatrix(gF3dDisplayListPtr++, x_c485761a(&D_80080100->x_0f39faa7), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    g_PERSPNORM(gF3dDisplayListPtr++, D_80080100->perspNorm);
    D_8004CC20.perspNorm = D_80080100->perspNorm;
    gDPSetFogColor(gF3dDisplayListPtr++, sFogColorR, sFogColorG, sFogColorB, 255);
    gSPFogPosition(gF3dDisplayListPtr++, sFogMin, sFogMax);
    if (D_80049CF0 != 0) {
        x_ff4031b5();
    }
    x_06fa0af9();

    for (ptr = D_80080100->x_b8131490; ptr != gExtraBatchPtr; ptr++) {
        x_50746900(gDrBatchPtr, ptr->context, ptr->info, ptr->vertices, ptr->triangles);
    }
    gDPFullSync(gF3dDisplayListPtr++);
    gSPEndDisplayList(gF3dDisplayListPtr++);

    gSPEndDisplayList(gOverlayDlPtr++);

    gDPFullSync(gF3dExtraListPtr++);
    gSPEndDisplayList(gF3dExtraListPtr++);

    x_50746900(gDrBatchPtr, NULL, &D_8004CD30, NULL, NULL);
    x_50746900(gDrBatchPtr, NULL, NULL, NULL, NULL);

    sRenderTimeAccum += osGetTime() - x_de1dd2f4;
    rsp_wait_idle();

    for (i = 0; i < ARRAY_COUNT(sRenderCallbacks); i++) {
        if (sRenderCallbacks[i] != NULL && sRenderCallbacks[i](sRenderCallbackArgs[i]) == 0) {
            sRenderCallbacks[i] = NULL;
        }
    }

    rsp_vi_sync(TRUE);
    rsp_submit_gfx_tasks();

    if (++sFrameCounter >= 0x100) {
        sFrameCounter = 0;
        gRdpTimeTotal = gRspTimeTotal = sRenderTimeAccum = 0;
    }
}

Object *tr_obj_alloc(void) {
    Object *obj;

    obj = x_68289eaa(x_69f86dd8);
    if (obj == NULL) {
        return NULL;
    }

    obj->x_0232396f = x_a1821d40;
    x_7e194d55(2, obj->x_0f4167b4[2]);
    gTaskLock = TRUE;
    sFadeAlpha = 0;
    return obj;
}

void tr_player_load(s16 x_ce13e71a) {
    Object *v0;
    Object *v1;
    s16 pad;
    u8 x_235d81c7;
    u8 x_93463df6;
    u8 x_5cb3a50d;
    s32 counter;
    s32 x_5aee6615;

    counter = 6;

    x_5cb3a50d = FALSE;
    x_59ce598c[x_ce13e71a].x_c4397934 = FALSE;

    while (gTaskPool.count < 10 || gPhysicsPool.count <= 0) {
        gfx_render_frame();
    }

    switch (x_5e4e2788) {
        case x_79c2dc5b:
            x_3c859f4e(x_ce13e71a);
            break;
        case x_e483bf48:
        case x_557d3dd6:
            if (x_77831b2c[x_ce13e71a].x_03604d94) {
                v0 = tr_obj_alloc();
                if (v0 == NULL) {
                    x_5cb3a50d = TRUE;
                } else {
                    x_59ce598c[x_ce13e71a].enabled = FALSE;
                }
                break;
            }
        /* fallthrough */
        default:
            v1 = x_1bb3ac04(&x_dd2c4e91[x_2d0f1752], x_2587f84f);
            if (v1 != NULL) {
                v1->x_0f4167b4[0] = x_ce13e71a;
            } else {
                x_5cb3a50d = TRUE;
            }
            break;
    }

    if (!x_5cb3a50d) {
        x_62551fe9(0, 0);
        x_62551fe9(1, 0);
        x_20c52092(1800);
        gfx_render_frame();

        alSeqpStop(x_85a4d96f);

        x_93463df6 = x_59ce598c[x_83106b21].x_d93bcabf;
        x_235d81c7 = x_59ce598c[x_6f0b3be3].x_d93bcabf;
        x_5aee6615 = gGfxFlags & GFX_SHADOW_MODE;
        gGfxFlags |= GFX_SHADOW_MODE;

        while (!(x_e30d50d2 & x_700de048)) {
            if (x_5e4e2788 != x_79c2dc5b) {
                x_59ce598c[x_83106b21].x_d93bcabf = x_59ce598c[x_6f0b3be3].x_d93bcabf = FALSE;
            }
            gfx_render_frame();
        }

        if (!x_5aee6615) {
            gGfxFlags &= ~GFX_SHADOW_MODE;
        }
        x_59ce598c[x_83106b21].x_d93bcabf = x_93463df6;
        x_59ce598c[x_6f0b3be3].x_d93bcabf = x_235d81c7;

        x_59ce598c[x_ce13e71a].x_c4397934 = FALSE;
        gTaskLock = FALSE;
        x_e30d50d2 &= ~x_700de048;
        alSeqSetLoc(x_d896e1bb, &x_9ae0d7c5);
        alSeqpPlay(x_85a4d96f);
        x_20c52092(x_66ddef46);
        x_62551fe9(0, x_15814eea);
        x_62551fe9(1, x_15814eea);
    } else {

        while (--counter > 0) {
            gfx_render_frame();
        }
    }
}

void func_80001C6C(void) {
    x_e30d50d2 = 0;
    gTaskLock = TRUE;
    x_aec099eb = x_b5cc849a = 1800;

    obj_create_task(tr_fade_start, 0x1000);
    while (!(x_e30d50d2 & x_bee364e0)) {
        gfx_render_frame();
    }
    gTaskLock = FALSE;

    while (x_59ce598c[x_83106b21].buttons == (x_9cefe76c | x_1c9950cc) ||
           x_59ce598c[x_6f0b3be3].buttons == (x_9cefe76c | x_1c9950cc)) {
        gfx_render_frame();
    }

    x_e38a6e19 = SCREEN_ATTRACT;

    while (x_59ce598c[x_83106b21].buttons == (x_9cefe76c | x_1c9950cc) ||
           x_59ce598c[x_6f0b3be3].buttons == (x_9cefe76c | x_1c9950cc)) {
        gfx_render_frame();
    }

    rsp_wait_idle();
    rsp_vi_sync(FALSE);
}

void tr_scene_loop(void) {
    D_8005BFCE = sFrameCounter = gRdpTimeTotal = gRspTimeTotal = sRenderTimeAccum = 0;

    while (!(x_e30d50d2 & x_bee364e0) || !(x_e30d50d2 & x_e3ff543d)) {
        if (!(x_e30d50d2 & x_dd99cbfb) && !(x_e30d50d2 & x_86c5bc33) && x_59ce598c[x_83106b21].buttons == x_9cefe76c &&
            x_59ce598c[x_83106b21].enabled && x_59ce598c[x_83106b21].x_c4397934) {
            tr_player_load(x_83106b21);
        } else if (!(x_e30d50d2 & x_dd99cbfb) && !(x_e30d50d2 & x_86c5bc33) &&
                   x_59ce598c[x_6f0b3be3].buttons == x_9cefe76c && x_59ce598c[x_6f0b3be3].enabled &&
                   x_59ce598c[x_6f0b3be3].x_c4397934) {
            tr_player_load(x_6f0b3be3);
        }

        if (x_e30d50d2 & x_dd99cbfb) {
            gTaskLock = 1 - gTaskLock;
        }
        gfx_render_frame();
    }

    x_e30d50d2 &= ~(x_dd99cbfb | x_bee364e0);
    x_e30d50d2 |= x_520a704c;

    if (!(x_e30d50d2 & x_d4c59644)) {
        if (!(x_e30d50d2 & x_b9be821f)) {
            gTaskLock = TRUE;
        }
        obj_create_task(tr_fade_start, 0x1000);
        while (!(x_e30d50d2 & x_bee364e0)) {
            gfx_render_frame();
        }
        gTaskLock = FALSE;
    }

    x_e30d50d2 &= ~x_520a704c;

    gfx_init_frame();
    gfx_init_frame();

    rsp_wait_idle();
    rsp_vi_sync(FALSE);

    rsp_wait_idle();
    rsp_vi_sync(FALSE);
}

#ifdef NON_MATCHING
void tr_quad_opaque(s32 x_cc1d0de5, Vtx *x_84ff873b) {
    if (x_84ff873b == NULL) {
        x_84ff873b = &sQuadVtx[D_8005BFCE];
    }

    sQuadBatch.header.x_09cf7a45 = 0;
    sQuadBatch.header.x_1256da71 = 0;
    sQuadBatch.header.x_4c5e05f8 = 4;
    sQuadBatch.header.x_ed66866b = 0;
    sQuadBatch.header.x_8a54e96a = 2;
    sQuadBatch.header.x_70b508ea = 2;
    sQuadBatch.header.x_b7ba6d35 = sQuadDl;

    gDPPipeSync(&sQuadDl[0]);
    gDPSetCombineMode(&sQuadDl[1], G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_RENDERMODE, G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    x_84ff873b[0].v.cn[3] = x_cc1d0de5;
    x_84ff873b[0].v.cn[0] = x_84ff873b[0].v.cn[1] = x_84ff873b[0].v.cn[2] = sOverlayBrightness;
    x_84ff873b[1].v.cn[3] = x_cc1d0de5;
    x_84ff873b[1].v.cn[0] = x_84ff873b[1].v.cn[1] = x_84ff873b[1].v.cn[2] = sOverlayBrightness;
    x_84ff873b[2].v.cn[3] = x_cc1d0de5;
    x_84ff873b[2].v.cn[0] = x_84ff873b[2].v.cn[1] = x_84ff873b[2].v.cn[2] = sOverlayBrightness;
    x_84ff873b[3].v.cn[3] = x_cc1d0de5;
    x_84ff873b[3].v.cn[0] = x_84ff873b[3].v.cn[1] = x_84ff873b[3].v.cn[2] = sOverlayBrightness;

    x_50746900(gExtraBatchPtr, NULL, &sQuadBatch, x_84ff873b, sQuadTri);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/main/tr_quad_opaque.s")
void tr_quad_opaque(s32 x_cc1d0de5, Vtx *x_84ff873b);
#endif

#ifdef NON_MATCHING
void tr_quad_xlu(s32 x_cc1d0de5, Vtx *vertices) {
    Gfx *gfx = sQuadDl;

    if (vertices == NULL) {
        vertices = sQuadVtx[D_8005BFCE];
    }

    sQuadBatch.header.x_09cf7a45 = 0;
    sQuadBatch.header.x_1256da71 = 0;
    sQuadBatch.header.x_4c5e05f8 = 4;
    sQuadBatch.header.x_ed66866b = 0;
    sQuadBatch.header.x_8a54e96a = 2;
    sQuadBatch.header.x_70b508ea = 2;
    sQuadBatch.header.x_b7ba6d35 = sQuadDl;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    vertices[0].v.cn[3] = x_cc1d0de5;
    vertices[0].v.cn[0] = vertices[0].v.cn[1] = vertices[0].v.cn[2] = sOverlayBrightness;
    vertices[1].v.cn[3] = x_cc1d0de5;
    vertices[1].v.cn[0] = vertices[1].v.cn[1] = vertices[1].v.cn[2] = sOverlayBrightness;
    vertices[2].v.cn[3] = x_cc1d0de5;
    vertices[2].v.cn[0] = vertices[2].v.cn[1] = vertices[2].v.cn[2] = sOverlayBrightness;
    vertices[3].v.cn[3] = x_cc1d0de5;
    vertices[3].v.cn[0] = vertices[3].v.cn[1] = vertices[3].v.cn[2] = sOverlayBrightness;

    x_50746900(gExtraBatchPtr, NULL, &sQuadBatch, vertices, sQuadTri);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/main/tr_quad_xlu.s")
void tr_quad_xlu(s32 x_cc1d0de5, Vtx *x_84ff873b);
#endif

void tr_fade_out(Object *obj) {
    if (sFadeAlpha - 8 < sFadeThreshold) {
        gGfxFlags &= ~GFX_SHADOW_MODE;
        obj->flags |= x_f51cb721;
        x_e30d50d2 |= x_80ca0761;

        if (obj->x_0f4167b4[4] == 0) {
            x_e30d50d2 &= ~x_86c5bc33;
        }
        x_e30d50d2 |= x_e3ff543d;
    } else {
        sFadeAlpha -= 8;
        tr_quad_xlu(sFadeAlpha, NULL);
    }
}

void tr_fade_out_delay(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] >= 7) {
        osViBlack(0);
        sFadeAlpha = 255;
        obj->x_0232396f = tr_fade_out;
    }

    tr_quad_xlu(255, NULL);
}

void tr_scene_change(Object *obj) {
    x_292e1d02(obj, 0);
    if (x_e30d50d2 & x_23ebd6b0) {
        x_e30d50d2 |= x_e3ff543d;
        return;
    }

    gGfxFlags |= GFX_SHADOW_MODE;
    osViBlack(TRUE);
    x_e30d50d2 &= ~x_e3ff543d;
    x_292e1d02(obj, 0);
    if (x_e30d50d2 & x_86c5bc33) {
        obj->x_0f4167b4[4] = 1;
    }
    x_e30d50d2 |= x_86c5bc33;
    if (obj->flags & x_f51cb721) {
        obj->flags &= ~x_f51cb721;
        obj->x_0232396f = tr_fade_out_delay;
    }
    tr_quad_xlu(255, NULL);
}

void tr_fade_hold(Object *obj) {
    tr_quad_opaque(sFadeAlpha, NULL);
    obj->x_0f4167b4[0]++;

    if (obj->x_0f4167b4[0] >= 5) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
    }
}

void tr_fade_in(Object *obj) {
    if (sFadeAlpha + 8 < 255) {
        sFadeAlpha += 8;
        tr_quad_xlu(sFadeAlpha, NULL);
        return;
    }

    if (sFadeAlpha + 1 < 255) {
        sFadeAlpha++;
        tr_quad_xlu(sFadeAlpha, NULL);
        return;
    }

    obj->x_0232396f = tr_fade_hold;
    if (!(x_e30d50d2 & x_3b812e44)) {
        osViBlack(1);
    }

    tr_quad_opaque(sFadeAlpha, NULL);
    obj->x_0f4167b4[0] = 0;
}

void tr_fade_in_setup(Object *obj) {
    gGfxFlags |= GFX_SHADOW_MODE;
    x_f1ca6ba2(obj, 0);

    if (obj->x_0232396f != tr_fade_in_setup) {
        obj->x_0232396f = tr_fade_in;
    }

    if (sFadeAlpha + 8 < 255) {
        sFadeAlpha += 8;
        tr_quad_xlu(sFadeAlpha, NULL);
        return;
    }

    if (sFadeAlpha + 1 < 255) {
        sFadeAlpha++;
        tr_quad_xlu(sFadeAlpha, NULL);
        return;
    }

    obj->x_0232396f = tr_fade_hold;
    if (!(x_e30d50d2 & x_3b812e44)) {
        osViBlack(1);
    }

    tr_quad_opaque(sFadeAlpha, NULL);
    obj->x_0f4167b4[0] = 0;
}

void tr_fade_start(Object *obj) {
    if (!(x_e30d50d2 & x_ecbcd14e)) {
        sFadeAlpha = 0;
    }

    x_e30d50d2 &= ~x_ecbcd14e;
    obj->x_0232396f = tr_fade_in_setup;
    tr_quad_xlu(sFadeAlpha, NULL);
}

void main_game_loop(void) {
    x_e38a6e19 = SCREEN_BOOT;
    rsp_game_init(x_e38a6e19);
    x_2d5f067a();

    while (TRUE) {
        gCurrentScreenId = x_e38a6e19;
        obj_create_task(tr_scene_change, 0x1100);
        gScreenProfiles[x_e38a6e19].initFunc();
        if (!(x_e30d50d2 & x_3b812e44)) {
            osViBlack(1);
        }
        rsp_wait_idle();
        rsp_vi_sync(FALSE);
        sPrevScreenId = gCurrentScreenId;
        rsp_game_reinit(x_e38a6e19);
    }
}