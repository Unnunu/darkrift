#include "common.h"
#include "PR/gt.h"
#include "task.h"

#define gSPPerspNorm(pkt, dl)                       \
    {                                               \
        Gfx *_g = (Gfx *) (pkt);                    \
        _g->words.w0 = _SHIFTL(G_PERSPNORM, 24, 8); \
        _g->words.w1 = (dl);                        \
    }

typedef s32 (*DISPCB)(s32);

extern u16 D_80049330[];
extern s32 D_80049CF0;
extern GameMode gGameModes[];
extern Gfx D_8004CA68[];
extern Gfx D_8004CB00[];

extern Gfx D_8005BF10;
extern Gfx D_8005BF58[2];
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

extern u16 D_8005BED2;
extern BatchInfo D_8005BF00;
extern u16 D_8005BFC0;
extern u16 gGameMode;
extern u16 D_8005BFCE;
extern void *gFramebuffers[];

extern Gfx *D_8005BFDC;
extern Gfx *gOverlayGfxPos;
extern DisplayData D_8005BFF0[];
extern DisplayData *D_80080100;
extern s16 D_80080116;
extern s32 D_8008012C;
extern DISPCB D_80080140[20];
extern s32 D_80080190[20];

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
// void func_80024C98(void);
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
    OSTime time1;
    Batch *ptr;
    s32 i;

    time1 = osGetTime();
    func_80024C98();

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

    if (D_8008012C & 2) {
        gSPDisplayList(gOverlayGfxPos++, D_8004CA68);
    }

    gSPTriBatch(gMainBatchPos, (RenderContext *) osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    obj_update_all();
    gSPDisplayList(gMainGfxPos++, D_8004CA68);
    func_80002978();
    bg_draw();

    if (!(D_8008012C & 1)) {
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

    D_8005BEE0 += osGetTime() - time1;
    func_800030E4();

    for (i = 0; i < ARRAY_COUNT(D_80080140); i++) {
        if (D_80080140[i] != NULL && D_80080140[i](D_80080190[i]) == 0) {
            D_80080140[i] = NULL;
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
    gTasksDisabled = TRUE;
    D_8005BEFC = 0;
    return obj;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/func_800019B0.s")
void func_800019B0(s32);

void func_80001C6C(void) {
    D_8005BFC0 = 0;
    gTasksDisabled = TRUE;
    gSoundVolumeFading = gMusicVolumeFading = 1800;

    create_worker(func_80002744, 0x1000);
    while (!(D_8005BFC0 & 0x1)) {
        func_8000132C();
    }
    gTasksDisabled = FALSE;

    while (gPlayerInput[0].buttons == (INP_START | INP_ZTRIG) || gPlayerInput[1].buttons == (INP_START | INP_ZTRIG)) {
        func_8000132C();
    }

    gGameMode = GAME_MODE_0;

    while (gPlayerInput[0].buttons == (INP_START | INP_ZTRIG) || gPlayerInput[1].buttons == (INP_START | INP_ZTRIG)) {
        func_8000132C();
    }

    func_800030E4();
    sched_wait_vretrace(FALSE);
}

void func_80001D88(void) {
    D_8005BFCE = D_8005BEF8 = D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;

    while (!(D_8005BFC0 & 1) || !(D_8005BFC0 & 0x1000)) {
        if (!(D_8005BFC0 & 0x200) && !(D_8005BFC0 & 0x4) && gPlayerInput[0].buttons == INP_START &&
            gPlayerInput[0].unk_0A && gPlayerInput[0].unk_08) {
            func_800019B0(0);
        } else if (!(D_8005BFC0 & 0x200) && !(D_8005BFC0 & 0x4) && gPlayerInput[1].buttons == INP_START &&
                   gPlayerInput[1].unk_0A && gPlayerInput[1].unk_08) {
            func_800019B0(1);
        }

        if (D_8005BFC0 & 0x200) {
            gTasksDisabled = 1 - gTasksDisabled;
        }
        func_8000132C();
    }

    D_8005BFC0 &= ~0x201;
    D_8005BFC0 |= 0x2000;

    if (!(D_8005BFC0 & 0x10)) {
        if (!(D_8005BFC0 & 0x20)) {
            gTasksDisabled = TRUE;
        }
        create_worker(func_80002744, 0x1000);
        while (!(D_8005BFC0 & 0x1)) {
            func_8000132C();
        }
        gTasksDisabled = FALSE;
    }

    D_8005BFC0 &= ~0x2000;

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

    gDPPipeSync(&D_8005BF58);
    gDPSetCombineMode(&D_8005BF60, G_CC_SHADE, G_CC_SHADE);

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
        D_8008012C &= ~0x10;
        obj->flags |= 0x10;
        D_8005BFC0 |= 0x100;

        if (obj->vars[4] == 0) {
            D_8005BFC0 &= ~0x4;
        }
        D_8005BFC0 |= 0x1000;
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
    if (D_8005BFC0 & 0x400) {
        D_8005BFC0 |= 0x1000;
        return;
    }
    D_8008012C |= 0x10;
    osViBlack(TRUE);
    D_8005BFC0 &= ~0x1000;
    func_80021918(obj, 0);
    if (D_8005BFC0 & 4) {
        obj->vars[4] = 1;
    }
    D_8005BFC0 |= 4;
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
        D_8005BFC0 |= 1;
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
    if (!(D_8005BFC0 & 0x800)) {
        osViBlack(1);
    }

    func_80001FB0(D_8005BEFC, NULL);
    obj->vars[0] = 0;
}

void func_80002648(Object *obj) {
    D_8008012C |= 0x10;
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
    if (!(D_8005BFC0 & 0x800)) {
        osViBlack(1);
    }

    func_80001FB0(D_8005BEFC, NULL);
    obj->vars[0] = 0;
}

void func_80002744(Object *obj) {
    if (!(D_8005BFC0 & 0x80)) {
        D_8005BEFC = 0;
    }

    D_8005BFC0 &= ~0x80;
    obj->fn_render = func_80002648;
    func_80002178(D_8005BEFC, NULL);
}

void func_800027A0(void) {
    gGameMode = GAME_MODE_LOGO;
    func_800031FC(gGameMode);
    func_80006CEC();

    while (TRUE) {
        D_8005BED0 = gGameMode;
        create_worker(func_80002448, 0x1100);
        gGameModes[gGameMode].fn_run();
        if (!(D_8005BFC0 & 0x800)) {
            osViBlack(1);
        }
        func_800030E4();
        sched_wait_vretrace(FALSE);
        D_8005BED2 = D_8005BED0;
        func_80003468(gGameMode);
    }
}