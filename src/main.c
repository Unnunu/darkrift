#include "common.h"
#include "PR/gt.h"
#include "task.h"

#define gSPPerspNorm(pkt, dl)                       \
    {                                               \
        Gfx *_g = (Gfx *) (pkt);                    \
        _g->words.w0 = _SHIFTL(G_PERSPNORM, 24, 8); \
        _g->words.w1 = (dl);                        \
    }

typedef s32 (*DISPCB)(void *);

extern s32 D_80049CF0;
extern GameMode gGameModes[];
extern Gfx D_8004CA68[];
extern Gfx D_8004CB00[];

extern Gfx D_8005BF60;
extern Vtx D_800492B0[];
extern s32 gMusicVolumeFading;
extern s32 gSoundVolumeFading;

/*
OSTask D_8004CBC8 = {
    {
        M_GFXTASK,
        OS_TASK_DP_WAIT,
        NULL,
        0,
        NULL,
        0x1000,
        NULL,
        0x800,
        0x800B85B0,
        0x400,
        0x800B89B0,
        0x801389B0,
        NULL,
        0,
        NULL,
        0
    }
};
*/

extern RenderContext D_8004CC20;
/*
OSTask D_8004CC88 = {
    {
        M_GFXTASK,
        OS_TASK_DP_WAIT,
        NULL,
        0,
        NULL,
        0x1000,
        NULL,
        0x800,
        NULL,
        0x400,
        NULL,
        NULL,
        NULL,
        0,
        NULL,
        0
    }
};
*/
extern BatchInfo D_8004CCC8;
extern BatchInfo D_8004CD30;

extern u16 gPreviousGameMode;
extern u16 D_8005BFC0;
extern u16 gNextGameMode;
extern u16 D_8005BFCE;
extern void *gFramebuffers[];

extern Gfx *D_8005BFDC;
extern Gfx *gOverlayGfxPos;
extern DisplayData D_8005BFF0[];
extern DisplayData *D_80080100;
extern s16 D_80080116;
extern s32 D_8008012C;
extern DISPCB gPostRenderCallbacks[20];
extern s32 gPostRenderArgs[20];

OSTime D_8005BEE0;
OSTime D_8005BEE8;
OSTime D_8005BEF0;
s32 D_8005BEF8;
s32 D_8005BEFC;

void func_800030E4(void);
// void sched_execute_tasks(void);
void func_800031FC(u16);
void func_80006CEC(void);
void func_80003468(u16);
void obj_update_all(void);
void func_80002978(void);
void bg_draw(void);
void func_8001B26C(void);
void func_800212C8(void);
void func_80002744(Object *obj);

void func_80001120(void) {
    D_80080100 = &D_8005BFF0[D_8005BFCE];
    gMainGfxPos = D_80080100->gfxMain;
    gMainBatchPos = D_80080100->batchMain;

    gSPSegment(gMainGfxPos++, 0x01, gFramebuffers[D_8005BFCE]);
    gSPSegment(gMainGfxPos++, 0x00, 0x00000000);

    D_8004CC20.segmentTable[0] = 0;
    D_8004CC20.segmentTable[1] = PHYSICAL_TO_VIRTUAL(gFramebuffers[D_8005BFCE]);

    gSPTriBatch(gMainBatchPos, (RenderContext *) osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);
    gSPTriBatch(gMainBatchPos, NULL, &D_8004CD30, NULL, NULL);
    gSPTriBatch(gMainBatchPos, NULL, NULL, NULL, NULL);
    func_800030E4();
    sched_wait_vretrace(TRUE);
    sched_execute_tasks();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
}

void func_8000132C(void) {
    OSTime frameStartTime;
    Batch *ptr;
    s32 i;

    frameStartTime = osGetTime();
    input_update();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
    gMainGfxPos = D_80080100->gfxMain;
    D_8005BFDC = D_80080100->unk_4080;
    gOverlayGfxPos = D_80080100->gfxOverlay;
    gMainBatchPos = D_80080100->batchMain;
    gOverlayBatchPos = D_80080100->batchOverlay;

    gSPSegment(gMainGfxPos++, 0x01, gFramebuffers[D_8005BFCE]);
    gSPSegment(gMainGfxPos++, 0x00, 0x00000000);

    D_8004CC20.segmentTable[0] = 0;
    D_8004CC20.segmentTable[1] = VIRTUAL_TO_PHYSICAL(gFramebuffers[D_8005BFCE]);

    if (D_8008012C & GFX_FLAG_OVERLAY) {
        gSPDisplayList(gOverlayGfxPos++, D_8004CA68);
    }

    gSPTriBatch(gMainBatchPos, (RenderContext *) osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    obj_update_all();
    gSPDisplayList(gMainGfxPos++, D_8004CA68);
    func_80002978();
    bg_draw();

    if (!(D_8008012C & GFX_FLAG_1)) {
        gSPDisplayList(gMainGfxPos++, D_80080100->unk_4080);
    }
    gSPDisplayList(gMainGfxPos++, D_8004CB00);
    gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&D_80080100->mtxViewProj),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNorm(gMainGfxPos++, D_80080100->perspNorm);
    D_8004CC20.perspNorm = D_80080100->perspNorm;
    gDPSetFogColor(gMainGfxPos++, D_80080130, D_80080132, D_80080134, 255);
    gSPFogPosition(gMainGfxPos++, D_80080136, D_80080138);
    if (D_80049CF0 != 0) {
        func_8001B26C();
    }
    func_800212C8();

    for (ptr = D_80080100->batchOverlay; ptr != gOverlayBatchPos; ptr++) {
        gSPTriBatch(gMainBatchPos, ptr->context, ptr->info, ptr->vertices, ptr->triangles);
    }
    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);

    gSPEndDisplayList(D_8005BFDC++);

    gDPFullSync(gOverlayGfxPos++);
    gSPEndDisplayList(gOverlayGfxPos++);

    gSPTriBatch(gMainBatchPos, NULL, &D_8004CD30, NULL, NULL);
    gSPTriBatch(gMainBatchPos, NULL, NULL, NULL, NULL);

    D_8005BEE0 += osGetTime() - frameStartTime;
    func_800030E4();

    for (i = 0; i < ARRAY_COUNT(gPostRenderCallbacks); i++) {
        if (gPostRenderCallbacks[i] != NULL && gPostRenderCallbacks[i](gPostRenderArgs[i]) == 0) {
            gPostRenderCallbacks[i] = NULL;
        }
    }

    sched_wait_vretrace(TRUE);
    sched_execute_tasks();

    if (++D_8005BEF8 >= 0x100) {
        D_8005BEF8 = 0;
        D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;
    }
}

Object *func_8000194C(void) {
    Object *obj;

    obj = func_80015FB4(1);
    if (obj == NULL) {
        return NULL;
    }

    obj->fn_render = func_80015C58;
    sound_play(2, obj->vars[2]);
    gIsPaused = TRUE;
    D_8005BEFC = 0;
    return obj;
}

void func_800019B0(s16 playerId) {
    Object *v0;
    Object *v1;
    s16 pad;
    u8 sp35;
    u8 sp34;
    u8 sp33;
    s32 counter;
    s32 sp28;

    counter = 6;

    sp33 = FALSE;
    gPlayerInput[playerId].unk_08 = FALSE;

    while (gTaskPool.count < 10 || gModelInstancePool.count <= 0) {
        func_8000132C();
    }

    switch (gPlayMode) {
        case PLAY_MODE_PRACTICE:
            practice_enter_pause(playerId);
            break;
        case PLAY_MODE_TOURNAMENT_P1:
        case PLAY_MODE_TOURNAMENT_P2:
            if (gBattleSettings[playerId].isCpu) {
                v0 = func_8000194C();
                if (v0 == NULL) {
                    sp33 = TRUE;
                } else {
                    gPlayerInput[playerId].enabled = FALSE;
                }
                break;
            }
            /* fallthrough */
        default:
            v1 = func_80015E74(&D_8004C008[9], 0xABAB);
            if (v1 != NULL) {
                v1->vars[0] = playerId;
            } else {
                sp33 = TRUE;
            }
            break;
    }

    if (!sp33) {
        sound_set_volume(0, 0);
        sound_set_volume(1, 0);
        music_set_volume(1800);
        func_8000132C();

        alSeqpStop(gMusicPlayer);

        sp34 = gPlayerInput[PLAYER_1].isMirrored;
        sp35 = gPlayerInput[PLAYER_2].isMirrored;
        sp28 = D_8008012C & GFX_FLAG_10;
        D_8008012C |= GFX_FLAG_10;

        while (!(D_8005BFC0 & GAME_FLAG_40)) {
            if (gPlayMode != PLAY_MODE_PRACTICE) {
                gPlayerInput[PLAYER_1].isMirrored = gPlayerInput[PLAYER_2].isMirrored = FALSE;
            }
            func_8000132C();
        }

        if (!sp28) {
            D_8008012C &= ~GFX_FLAG_10;
        }
        gPlayerInput[PLAYER_1].isMirrored = sp34;
        gPlayerInput[PLAYER_2].isMirrored = sp35;

        gPlayerInput[playerId].unk_08 = FALSE;
        gIsPaused = FALSE;
        D_8005BFC0 &= ~GAME_FLAG_40;
        alSeqSetLoc(gMusicSequence, &gMusicMarkerStart);
        alSeqpPlay(gMusicPlayer);
        music_set_volume(gMusicVolume);
        sound_set_volume(0, gSoundVolume);
        sound_set_volume(1, gSoundVolume);
    } else {

        while (--counter > 0) {
            func_8000132C();
        }
    }
}

void unused_func_80001C6C(void) {
    D_8005BFC0 = 0;
    gIsPaused = TRUE;
    gSoundVolumeFading = gMusicVolumeFading = 1800;

    create_worker(func_80002744, 0x1000);
    while (!(D_8005BFC0 & GAME_FLAG_MODE_DONE)) {
        func_8000132C();
    }
    gIsPaused = FALSE;

    while (gPlayerInput[0].buttons == (INP_START | INP_ZTRIG) || gPlayerInput[1].buttons == (INP_START | INP_ZTRIG)) {
        func_8000132C();
    }

    gNextGameMode = GAME_MODE_MAIN_MENU;

    while (gPlayerInput[0].buttons == (INP_START | INP_ZTRIG) || gPlayerInput[1].buttons == (INP_START | INP_ZTRIG)) {
        func_8000132C();
    }

    func_800030E4();
    sched_wait_vretrace(FALSE);
}

void main_loop(void) {
    D_8005BFCE = D_8005BEF8 = D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;

    while (!(D_8005BFC0 & GAME_FLAG_MODE_DONE) || !(D_8005BFC0 & GAME_FLAG_1000)) {
        if (!(D_8005BFC0 & GAME_FLAG_200) && !(D_8005BFC0 & GAME_FLAG_4) && gPlayerInput[0].buttons == INP_START &&
            gPlayerInput[PLAYER_1].enabled && gPlayerInput[PLAYER_1].unk_08) {
            func_800019B0(PLAYER_1);
        } else if (!(D_8005BFC0 & GAME_FLAG_200) && !(D_8005BFC0 & GAME_FLAG_4) &&
                   gPlayerInput[PLAYER_2].buttons == INP_START && gPlayerInput[PLAYER_2].enabled &&
                   gPlayerInput[PLAYER_2].unk_08) {
            func_800019B0(PLAYER_2);
        }

        if (D_8005BFC0 & GAME_FLAG_200) {
            gIsPaused = 1 - gIsPaused;
        }
        func_8000132C();
    }

    D_8005BFC0 &= ~(GAME_FLAG_200 | GAME_FLAG_MODE_DONE);
    D_8005BFC0 |= GAME_FLAG_2000;

    if (!(D_8005BFC0 & GAME_FLAG_10)) {
        if (!(D_8005BFC0 & GAME_FLAG_20)) {
            gIsPaused = TRUE;
        }
        create_worker(func_80002744, 0x1000);
        while (!(D_8005BFC0 & GAME_FLAG_MODE_DONE)) {
            func_8000132C();
        }
        gIsPaused = FALSE;
    }

    D_8005BFC0 &= ~GAME_FLAG_2000;

    func_80001120();
    func_80001120();

    func_800030E4();
    sched_wait_vretrace(FALSE);

    func_800030E4();
    sched_wait_vretrace(FALSE);
}

#ifdef NON_MATCHING
void func_80001FB0(s32 arg0, Vtx *arg1) {
    if (arg1 == NULL) {
        arg1 = &D_800492B0[D_8005BFCE * 4];
    }

    D_8005BF00.header.unk_00 = 0;
    D_8005BF00.header.unk_04 = 0;
    D_8005BF00.header.numVertices = 4;
    D_8005BF00.header.unk_09 = 0;
    D_8005BF00.header.numTriangles = 2;
    D_8005BF00.header.unk_0B = 2;
    D_8005BF00.header.texGfx = &D_8005BF58;

    gDPPipeSync(&D_8005BF58[0]);
    gDPSetCombineMode(&D_8005BF58[1], G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&D_8005BF10, GT_RENDERMODE, G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gtStateSetOthermode(&D_8005BF10, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&D_8005BF10, GT_PIPELINE, G_PM_NPRIMITIVE);

    arg1[0].v.cn[3] = arg0;
    arg1[0].v.cn[0] = arg1[0].v.cn[1] = arg1[0].v.cn[2] = D_80080116;
    arg1[1].v.cn[3] = arg0;
    arg1[1].v.cn[0] = arg1[1].v.cn[1] = arg1[1].v.cn[2] = D_80080116;
    arg1[2].v.cn[3] = arg0;
    arg1[2].v.cn[0] = arg1[2].v.cn[1] = arg1[2].v.cn[2] = D_80080116;
    arg1[3].v.cn[3] = arg0;
    arg1[3].v.cn[0] = arg1[3].v.cn[1] = arg1[3].v.cn[2] = D_80080116;

    gSPTriBatch(gOverlayBatchPos, NULL, &D_8005BF00, arg1, D_80049330);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/main/func_80001FB0.s")
void func_80001FB0(s32 arg0, Vtx *arg1);
#endif

#ifdef NON_MATCHING
void func_80002178(s32 arg0, Vtx *vertices) {
    Gfx *gfx = D_8005BF58;

    if (vertices == NULL) {
        vertices = &D_800492B0[D_8005BFCE << 2];
    }

    D_8005BF00.header.unk_00 = 0;
    D_8005BF00.header.unk_04 = 0;
    D_8005BF00.header.numVertices = 4;
    D_8005BF00.header.unk_09 = 0;
    D_8005BF00.header.numTriangles = 2;
    D_8005BF00.header.unk_0B = 2;
    D_8005BF00.header.texGfx = D_8005BF58;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    vertices[0].v.cn[3] = arg0;
    vertices[0].v.cn[0] = vertices[0].v.cn[1] = vertices[0].v.cn[2] = D_80080116;
    vertices[1].v.cn[3] = arg0;
    vertices[1].v.cn[0] = vertices[1].v.cn[1] = vertices[1].v.cn[2] = D_80080116;
    vertices[2].v.cn[3] = arg0;
    vertices[2].v.cn[0] = vertices[2].v.cn[1] = vertices[2].v.cn[2] = D_80080116;
    vertices[3].v.cn[3] = arg0;
    vertices[3].v.cn[0] = vertices[3].v.cn[1] = vertices[3].v.cn[2] = D_80080116;

    gSPTriBatch(gOverlayBatchPos, NULL, &D_8005BF00, vertices, D_80049330);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/main/func_80002178.s")
void func_80002178(s32 arg0, Vtx *arg1);
#endif

void func_80002340(Object *obj) {
    if (D_8005BEFC - 8 < D_80080118) {
        D_8008012C &= ~GFX_FLAG_10;
        obj->flags |= 0x10;
        D_8005BFC0 |= GAME_FLAG_100;

        if (obj->vars[4] == 0) {
            D_8005BFC0 &= ~GAME_FLAG_4;
        }
        D_8005BFC0 |= GAME_FLAG_1000;
    } else {
        D_8005BEFC -= 8;
        func_80002178(D_8005BEFC, NULL);
    }
}

void func_800023E4(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] >= 7) {
        osViBlack(0);
        D_8005BEFC = 255;
        obj->fn_render = func_80002340;
    }

    func_80002178(255, NULL);
}

void func_80002448(Object *obj) {
    func_80021918(obj, 0);
    if (D_8005BFC0 & GAME_FLAG_400) {
        D_8005BFC0 |= GAME_FLAG_1000;
        return;
    }
    D_8008012C |= GFX_FLAG_10;
    osViBlack(TRUE);
    D_8005BFC0 &= ~GAME_FLAG_1000;
    func_80021918(obj, 0);
    if (D_8005BFC0 & GAME_FLAG_4) {
        obj->vars[4] = 1;
    }
    D_8005BFC0 |= GAME_FLAG_4;
    if (obj->flags & 0x10) {
        obj->flags &= ~0x10;
        obj->fn_render = func_800023E4;
    }
    func_80002178(255, NULL);
}

void func_80002528(Object *obj) {
    func_80001FB0(D_8005BEFC, NULL);
    obj->vars[0]++;

    if (obj->vars[0] >= 5) {
        D_8005BFC0 |= GAME_FLAG_MODE_DONE;
        obj->flags |= 0x10;
    }
}

void func_80002590(Object *obj) {
    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    if (D_8005BEFC + 1 < 255) {
        D_8005BEFC++;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    obj->fn_render = func_80002528;
    if (!(D_8005BFC0 & GAME_FLAG_800)) {
        osViBlack(1);
    }

    func_80001FB0(D_8005BEFC, NULL);
    obj->vars[0] = 0;
}

void func_80002648(Object *obj) {
    D_8008012C |= GFX_FLAG_10;
    audio_fade_out_all(obj, 0);

    if (obj->fn_render != func_80002648) {
        obj->fn_render = func_80002590;
    }

    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    if (D_8005BEFC + 1 < 255) {
        D_8005BEFC++;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    obj->fn_render = func_80002528;
    if (!(D_8005BFC0 & GAME_FLAG_800)) {
        osViBlack(1);
    }

    func_80001FB0(D_8005BEFC, NULL);
    obj->vars[0] = 0;
}

void func_80002744(Object *obj) {
    if (!(D_8005BFC0 & GAME_FLAG_80)) {
        D_8005BEFC = 0;
    }

    D_8005BFC0 &= ~GAME_FLAG_80;
    obj->fn_render = func_80002648;
    func_80002178(D_8005BEFC, NULL);
}

void game_main(void) {
    gNextGameMode = GAME_MODE_LOGO;
    func_800031FC(gNextGameMode);
    func_80006CEC();

    while (TRUE) {
        gCurrentGameMode = gNextGameMode;
        create_worker(func_80002448, 0x1100);
        gGameModes[gNextGameMode].fn_run();
        if (!(D_8005BFC0 & GAME_FLAG_800)) {
            osViBlack(1);
        }
        func_800030E4();
        sched_wait_vretrace(FALSE);
        gPreviousGameMode = gCurrentGameMode;
        func_80003468(gNextGameMode);
    }
}