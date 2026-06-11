#include "common.h"
#include "string.h"
#include "camera.h"
#include "task.h"
#include "ld_addrs.h"

void mem_pool_init(void);
extern void *sHeapBase;

extern long long int gspDarkRift3DTextStart[], gspDarkRift3DTextEnd[];
extern long long int gspDarkRift3DDataStart[], gspDarkRift3DDataEnd[];

extern OSMesgQueue sContMesgQueue;
extern OSMesgQueue gRspMessageQueue;
extern OSMesgQueue sSpEventQueue;
extern OSMesgQueue sDpEventQueue;
extern OSMesgQueue sViEventQueue;

extern OSTime gRspTimeTotal;
extern OSTime gRdpTimeTotal;

extern OSTask sGfxTaskF3D;
extern OSTask sGfxTaskDR;
extern OSTask sGfxTaskExtra;
extern x_ee01e8c6 *D_80080100;
extern Gfx *gF3dDisplayListPtr;
extern Gfx *gF3dExtraListPtr;
extern x_320b5d80 *gDrBatchPtr;
extern u8 *gFramebuffers[];
extern u16 D_8005BFCE;
extern u16 x_a4f5fb93;
extern s32 D_8013F0B0;
extern x_ee01e8c6 D_8005BFF0[2];

extern UnkStruct10 D_8004937C;
extern UnkStruct10 D_80049384;
void wad_entries_reset(void);
void wad_load_area_init(s32 x_cc1d0de5, s32 x_84ff873b);
void matrix_system_init(void);
void button_state_reset(void);
void audio_init(void);
Object *x_7b6cfabc(void);
void model_light_pool_init(void);
void button_remap_reset(s32);
void model_texture_reset(void);
void spark_init_all(void);
extern s16 D_800800FA;

extern s32 x_e74df613;
extern s32 x_6c647b3a;
extern s32 D_80081428;
extern s32 D_80049CF0;

void mem_defrag(void);
void wad_sync_dma_slots(void);
void audio_reinit(void);
void pool_init_core(void);

s32 audio_submit_task(void);

/* .bss */
s16 sClearColorR;
s16 sClearColorG;
s16 sClearColorB;
s16 sOverlayBrightness;
s16 sFadeThreshold;
s32 sGfxTaskCount;
u16 *sFramebuffer;
u16 *sZbuffer;
u8 sFbBusy;
u8 sClearZbuffer;
s32 gGfxFlags;
s16 sFogColorR;
s16 sFogColorG;
s16 sFogColorB;
s16 sFogMin;
s16 sFogMax;
RenderCallback sRenderCallbacks[20];
s32 sRenderCallbackArgs[20];
s16 D_800801E0;
u8 sZbufFillSkipped;
u8 D_800801E3;
s8 sRspStatus;
s8 sRspSyncState;
s32 sCurrentTaskType;

void rsp_clear_callbacks(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sRenderCallbacks); i++) {
        sRenderCallbacks[i] = NULL;
    }
}

void rsp_register_callback(s32 (*callback)(void *), void *arg) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sRenderCallbacks); i++) {
        if (sRenderCallbacks[i] == 0) {
            sRenderCallbacks[i] = callback;
            sRenderCallbackArgs[i] = arg;
            return;
        }
    }
}

void rsp_clear_screen(void) {
    gDPPipeSync(gF3dDisplayListPtr++);
    gDPSetCycleType(gF3dDisplayListPtr++, G_CYC_FILL);

    if (!(gGfxFlags & GFX_NO_ZCLEAR)) {
        gDPSetDepthImage(gF3dDisplayListPtr++, x_c485761a(sFramebuffer));
        gDPSetColorImage(gF3dDisplayListPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, x_c485761a(sFramebuffer));
        gDPSetFillColor(gF3dDisplayListPtr++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
        gDPFillRectangle(gF3dDisplayListPtr++, 0, 0, x_c84980f9 - 1, x_a4f5fb93 - 1);
        sZbufFillSkipped = FALSE;
    } else {
        sZbufFillSkipped = TRUE;
    }

    gDPSetColorImage(gF3dDisplayListPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x01000000);

    if (sClearZbuffer) {
        if (x_6c647b3a > 0) {
            gDPSetFillColor(gF3dDisplayListPtr++, (GPACK_RGBA5551(sClearColorR, sClearColorG, sClearColorB, 1) << 16) |
                                                      GPACK_RGBA5551(sClearColorR, sClearColorG, sClearColorB, 1));
            gDPFillRectangle(gF3dDisplayListPtr++, 0, 0, x_c84980f9 - 1, x_6c647b3a + 20);
        }
    } else {
        gDPSetFillColor(gF3dDisplayListPtr++, (GPACK_RGBA5551(sClearColorR, sClearColorG, sClearColorB, 1) << 16) |
                                                  GPACK_RGBA5551(sClearColorR, sClearColorG, sClearColorB, 1));
        gDPFillRectangle(gF3dDisplayListPtr++, 0, 0, x_c84980f9 - 1, x_a4f5fb93 - 1);
    }

    gDPPipeSync(gF3dDisplayListPtr++);
    gDPSetCycleType(gF3dDisplayListPtr++, G_CYC_COPY);
}

void rsp_task_init(void) {
    sGfxTaskF3D.t.ucode_boot = rspbootTextStart;
    sGfxTaskF3D.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    sGfxTaskF3D.t.ucode = gspFast3DTextStart;
    sGfxTaskF3D.t.ucode_data = gspFast3DDataStart;
    memcpy(&sGfxTaskExtra, &sGfxTaskF3D, sizeof(OSTask));

    sGfxTaskExtra.t.ucode = gspFast3DTextStart;
    sGfxTaskExtra.t.ucode_data = gspFast3DDataStart;

    sGfxTaskDR.t.ucode_boot = rspbootTextStart;
    sGfxTaskDR.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    sGfxTaskDR.t.ucode = gspDarkRift3DTextStart;
    sGfxTaskDR.t.ucode_data = gspDarkRift3DDataStart;

    sGfxTaskCount = 0;
}

void rsp_scheduler_thread(void *x_cc1d0de5) {
    OSMesg task;
    OSTime x_a8947c6a;

    while (TRUE) {
        // receive task from task queue
        if (osRecvMesg(&gRspMessageQueue, &task, OS_MESG_NOBLOCK) == -1) {
            // no pending tasks
            sRspStatus = 0;
            // notify the other threads that RCP is idle
            osSendMesg(&sContMesgQueue, (OSMesg) 0x7777, OS_MESG_NOBLOCK);
            // wait until at least one task appears
            osRecvMesg(&gRspMessageQueue, &task, OS_MESG_BLOCK);
        }

        // clear sp and dp queues
        while (osRecvMesg(&sSpEventQueue, NULL, OS_MESG_NOBLOCK) != -1) {}
        while (osRecvMesg(&sDpEventQueue, NULL, OS_MESG_NOBLOCK) != -1) {}

        sCurrentTaskType = ((OSTask *) task)->t.type;

        // start task and wait for its completion
        osSpTaskStart(task);
        x_a8947c6a = osGetTime();
        sRspStatus = 1;
        osRecvMesg(&sSpEventQueue, NULL, OS_MESG_BLOCK);

        gRspTimeTotal += osGetTime() - x_a8947c6a;

        // wait for RDP sync
        if (sCurrentTaskType != M_AUDTASK) {
            sRspStatus = 2;
            osRecvMesg(&sDpEventQueue, NULL, OS_MESG_BLOCK);
        }

        gRdpTimeTotal += osGetTime() - x_a8947c6a;
    }
}

void rsp_submit_gfx_tasks(void) {
    while (osRecvMesg(&sContMesgQueue, NULL, OS_MESG_NOBLOCK) != -1) {}

    osWritebackDCacheAll();
    sGfxTaskCount = audio_submit_task();
    if (!sFbBusy) {
        // prepare two graphics task, one for f3d ucode, and the other for dr ucode
        sGfxTaskF3D.t.data_ptr = D_80080100->x_700a6ea1;
        sGfxTaskF3D.t.data_size = (gF3dDisplayListPtr - D_80080100->x_700a6ea1) * sizeof(Gfx);

        sGfxTaskDR.t.data_ptr = D_80080100->x_79588dca;
        sGfxTaskDR.t.data_size = (gDrBatchPtr - D_80080100->x_79588dca) * sizeof(x_320b5d80);

        osSendMesg(&gRspMessageQueue, (OSMesg) &sGfxTaskF3D, OS_MESG_BLOCK);
        osSendMesg(&gRspMessageQueue, (OSMesg) &sGfxTaskDR, OS_MESG_BLOCK);

        sGfxTaskCount += 2;

        if (gGfxFlags & GFX_EXTRA_DL) {
            sGfxTaskExtra.t.data_ptr = D_80080100->x_a4c192ba;
            sGfxTaskExtra.t.data_size = (gF3dExtraListPtr - D_80080100->x_a4c192ba) * sizeof(Gfx);
            osSendMesg(&gRspMessageQueue, (OSMesg) &sGfxTaskExtra, OS_MESG_BLOCK);
            sGfxTaskCount++;
        }
    }
}

void rsp_wait_idle(void) {
    sRspSyncState = 0;
    if (sGfxTaskCount != 0) {
        sRspSyncState = 7;
        osRecvMesg(&sContMesgQueue, NULL, OS_MESG_BLOCK);
        sGfxTaskCount = 0;
        sRspSyncState = 1;
        osSetTime(0);
    }
}

void rsp_vi_sync(u8 x_cc1d0de5) {
    if (MQ_IS_FULL(&sViEventQueue)) {
        osRecvMesg(&sViEventQueue, NULL, OS_MESG_BLOCK);
        sFbBusy = TRUE;
    } else {
        sFbBusy = FALSE;
        osRecvMesg(&sViEventQueue, NULL, OS_MESG_BLOCK);
        if (x_cc1d0de5) {
            osViSwapBuffer(gFramebuffers[D_8005BFCE]);
            D_8005BFCE = 1 - D_8005BFCE;
        }
    }
}

#ifdef NON_EQUIVALENT
void rsp_game_init(u16 x_7cedc3fb) {
    s32 unused[18];
    u32 a3;
    s32 x_cf10d3eb;
    UnkStruct10 x_5aee6615 = { 0, 90, 0, 0 };
    UnkStruct10 x_dd7ffac5 = { 0, 233, 500, 0 };

    x_c84980f9 = 320;
    x_a4f5fb93 = 240;
    a3 = 0x80400000 - 2 * 2 * 320 * 240 - 64;

    gFramebuffers[0] = a3;
    x_cf10d3eb = x_a4f5fb93 * x_c84980f9;
    gFramebuffers[1] = a3 + 2 * x_cf10d3eb;

    sZbuffer = sFramebuffer = ((u32) x_9caeba2b + 0x40) & ~0x3F;
    sHeapBase = (void *) (((u32) sFramebuffer + 0x25800 + 0x40) & ~0x3F);
    mem_pool_init();
    wad_entries_reset();
    wad_load_area_init(sZbuffer, 0x25800);
    matrix_system_init();
    button_state_reset();
    audio_init();
    rsp_task_init();
    sClearColorR = gScreenProfiles[x_7cedc3fb].clearColorR;
    sClearColorG = gScreenProfiles[x_7cedc3fb].clearColorG;
    sClearColorB = gScreenProfiles[x_7cedc3fb].clearColorB;
    pool_init(&gTaskPool, 50, sizeof(TaskNode));
    pool_init_core();
    x_f4bce728 = x_7b6cfabc();
    sFogMin = gScreenProfiles[x_7cedc3fb].fogMin;
    sFogMax = gScreenProfiles[x_7cedc3fb].fogMax;
    sFogColorR = gScreenProfiles[x_7cedc3fb].fogColorR;
    sFogColorG = gScreenProfiles[x_7cedc3fb].fogColorG;
    sFogColorB = gScreenProfiles[x_7cedc3fb].fogColorB;
    gGfxFlags = GFX_NONE;
    if (!x_cf10d3eb) {}
    memcpy(&sGfxTaskExtra, &sGfxTaskF3D, sizeof(OSTask));

    sWadMovCallback = NULL;
    sOverlayBrightness = sFadeThreshold = 0;
    sClearZbuffer = TRUE;
    rsp_clear_callbacks();
    model_light_pool_init();
    x_e30d50d2 = x_86c5bc33;
    button_remap_reset(0);
    button_remap_reset(1);
    D_8005BFF0[0].perspNorm = 0;
    D_8005BFF0[1].perspNorm = 1;
    D_8005BFCE = 0;
    model_texture_reset();
    spark_init_all();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/rsp/rsp_game_init.s")
void rsp_game_init(u16 x_7cedc3fb);
#endif

void rsp_game_reinit(u16 x_7cedc3fb) {
    x_3b49183f = NULL;
    x_e74df613 = 0;
    x_6c647b3a = 0;
    D_80081428 = 0;
    mem_defrag();
    wad_sync_dma_slots();
    audio_reinit();
    sClearColorR = gScreenProfiles[x_7cedc3fb].clearColorR;
    sClearColorG = gScreenProfiles[x_7cedc3fb].clearColorG;
    sClearColorB = gScreenProfiles[x_7cedc3fb].clearColorB;
    pool_init(&gTaskPool, 50, sizeof(TaskNode));
    pool_init_core();
    x_f4bce728 = x_7b6cfabc();
    button_state_reset();
    rsp_task_init();
    D_80049CF0 = 0;
    sFogMin = gScreenProfiles[x_7cedc3fb].fogMin;
    sFogMax = gScreenProfiles[x_7cedc3fb].fogMax;
    sFogColorR = gScreenProfiles[x_7cedc3fb].fogColorR;
    sFogColorG = gScreenProfiles[x_7cedc3fb].fogColorG;
    sFogColorB = gScreenProfiles[x_7cedc3fb].fogColorB;
    gGfxFlags = GFX_NONE;
    sWadMovCallback = NULL;
    sFadeThreshold = 0;
    sClearZbuffer = TRUE;
    rsp_clear_callbacks();
    model_light_pool_init();
    x_e30d50d2 = x_86c5bc33;
    sFbBusy = TRUE;
    model_texture_reset();
    spark_init_all();
}
