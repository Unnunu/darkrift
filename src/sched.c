/**
 * @file sched.c
 * @brief RSP/DP task scheduler, frame buffer management, and game-mode
 *        initialisation.
 *
 * The scheduler runs as a standalone thread (sched_run) that receives RSP
 * tasks from the main thread and waits for their completion.  The main thread
 * submits tasks via submit_scheduled_tasks(), syncs via
 * sync_scheduler_tasks(), and waits for vblank via sched_wait_vretrace().
 *
 * Also contains the Z-buffer / background-fill setup, and the heavyweight
 * per-mode initialisation (initialize_game_mode / reset_game_mode_systems).
 *
 * ── Task synchronisation scheme ──────────────────────────────────
 *
 *   Main thread                          Scheduler thread (sched_run)
 *   ═══════════════════════════          ═══════════════════════════════
 *   1. submit_scheduled_tasks():
 *      - drain stale 0x7777 tokens        (idle loop — waiting for task)
 *      - func_80021338() → audio OSTask
 *      - F3D OSTask → gSchedSPTaskQueue
 *      - DarkRift OSTask → gSchedSPTaskQueue
 *      - Overlay OSTask (if flag)
 *                                         2. osRecvMesg(gSchedSPTaskQueue)
 *                                            → osSpTaskStart()
 *                                            → wait SP done (gSchedSPQueue)
 *                                            → wait DP done (gSchedDPQueue)
 *                                         3. If queue now empty →
 *                                            osSendMesg(0x7777)
 *                                            [goto 2 / idle-wait]
 *   4. sync_scheduler_tasks():
 *      - osRecvMesg(gSchedTaskRequestQueue)
 *        blocks until 0x7777 arrives
 *        → all RSP tasks done
 *      - osSetTime(0) [profiling reset]
 *   5. sched_wait_vretrace():
 *      - osRecvMesg(gSchedVRetraceQueue)
 *      - if swapBuffers:
 *          osViSwapBuffer(fb[gFramebufferIndex])
 *          gFramebufferIndex ^= 1
 *
 * ── Frame dropping ───────────────────────────────────────────────
 *
 *   If the vblank queue is full (MQ_IS_FULL), the CPU is running
 *   slower than the display.  One pending vblank is drained and
 *   sVBlankBehind is set — submit_scheduled_tasks skips task
 *   submission for one frame, letting the RCP catch up.
 *
 * ── Double-buffered data ─────────────────────────────────────────
 *
 *   gDisplayData[2]   — two copies of frame-local render state
 *                        (display lists, batches, etc.)
 *   gActiveDisplayData — pointer to the current frame's display data
 *   gFramebufferIndex  — toggles each vblank, selects which 320×240
 *                        16-bit buffer the VI displays
 *
 *   The main thread writes to gActiveDisplayData while the RSP
 *   processes the previous frame's data — the two are decoupled by
 *   the task queue.
 */

#include "common.h"
#include "string.h"
#include "camera.h"
#include "task.h"
#include "ld_addrs.h"

void initialize_memory_heap(void);
extern void *gHeapBase;

extern long long int gspDarkRift3DTextStart[], gspDarkRift3DTextEnd[];
extern long long int gspDarkRift3DDataStart[], gspDarkRift3DDataEnd[];

extern OSMesgQueue gSchedTaskRequestQueue;
extern OSMesgQueue gSchedSPTaskQueue;
extern OSMesgQueue gSchedSPQueue;
extern OSMesgQueue gSchedDPQueue;
extern OSMesgQueue gSchedVRetraceQueue;

extern OSTime sFrameProfilingMin; // debug leftover, result unused
extern OSTime sFrameProfilingMax; // debug leftover, result unused

extern OSTask sF3dTask;
extern OSTask sDarkRiftTask;
extern OSTask sOverlayTask;
extern DisplayData *gActiveDisplayData;
extern Gfx *gMainGfxPos;
extern Gfx *gOverlayGfxPos;
extern Batch *gMainBatchPos;
extern u8 *gFramebuffers[];
extern u16 gFramebufferIndex;
extern u16 gScreenHeight;
extern s32 D_8013F0B0;
extern DisplayData gDisplayData[2];

extern UnkStruct800031FC D_8004937C;
extern UnkStruct800031FC D_80049384;
void func_80025E6C(void);
void func_80025EDC(s32 arg0, s32 arg1);
void func_80012490(void);
void func_80024D2C(void);
void audio_init(void);
Object *camera_create(void);
void reset_lights(void);
void func_80024A38(s32);
void reset_scrollable_textures(void);
void func_80023200(void);
extern s16 D_800800FA;

extern s32 gBgScrollX;
extern s32 gBgScrollY;
extern s32 D_80081428;
extern s32 gBgDlists;

void reset_and_compact_heap(void);
void func_80026250(void);
void audio_reset(void);
void func_8002AC10(void);

s32 func_80021338(void);

/* .bss */
s16 gFillColorR;
s16 gFillColorG;
s16 gFillColorB;
s16 sQuadColor;
s16 sFadeThreshold;
s32 gSchedTaskCount;
u16 *gZBuffer;
u16 *sWadMemBase;
u8 sVBlankBehind;
u8 sScrollFillEnabled;
s32 gGfxFlags;
s16 gFogColorR;
s16 gFogColorG;
s16 gFogColorB;
s16 gFogNear;
s16 gFogFar;
DISPCB gPostRenderCallbacks[20];
s32 gPostRenderArgs[20];
s16 UnusedSched1;
u8 sZBufferMode;
u8 UnusedSched2;
s8 sRspState;
s8 sSyncState;
s32 sLastTaskType;

/**
 * @brief Clear all post-render callback slots.
 */
void reset_post_render_hooks(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPostRenderCallbacks); i++) {
        gPostRenderCallbacks[i] = NULL;
    }
}

/**
 * @brief Register a callback to run at the end of each frame.
 *        Stores into the first free slot; silently drops if all slots full.
 */
void set_post_render_hook(s32 (*func)(void *), void *arg) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPostRenderCallbacks); i++) {
        if (gPostRenderCallbacks[i] == 0) {
            gPostRenderCallbacks[i] = func;
            gPostRenderArgs[i] = arg;
            return;
        }
    }
}

/**
 * @brief Prepare the Z-buffer and fill the background colour.
 *
 * If Z-buffering is enabled, the Z-buffer (gZBuffer) is cleared to
 * G_MAXFBZ.  The colour buffer is then filled with the scroll-fill
 * colour (gFillColorR/gFillColorG/gFillColorB).  When scrolling is
 * active only the strip uncovered by the scroll is filled, otherwise the
 * whole screen.
 */
void setup_zbuffer_and_clear(void) {
    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_FILL);

    if (!(gGfxFlags & GFX_FLAG_NO_ZBUFFER)) {
        gDPSetDepthImage(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(gZBuffer));
        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, VIRTUAL_TO_PHYSICAL(gZBuffer));
        gDPSetFillColor(gMainGfxPos++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
        gDPFillRectangle(gMainGfxPos++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
        sZBufferMode = FALSE;
    } else {
        sZBufferMode = TRUE;
    }

    // segment 0x01 = gFramebuffers[gFramebufferIndex] (set by gSPSegment in gfx_init_frame)
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, 0x01000000);

    if (sScrollFillEnabled) {
        if (gBgScrollY > 0) {
            gDPSetFillColor(gMainGfxPos++, (GPACK_RGBA5551(gFillColorR, gFillColorG, gFillColorB, 1) << 16) |
                                               GPACK_RGBA5551(gFillColorR, gFillColorG, gFillColorB, 1));
            // +20 covers the strip freshly scrolled-in plus a pixel margin
            gDPFillRectangle(gMainGfxPos++, 0, 0, gScreenWidth - 1, gBgScrollY + 20);
        }
    } else {
        gDPSetFillColor(gMainGfxPos++, (GPACK_RGBA5551(gFillColorR, gFillColorG, gFillColorB, 1) << 16) |
                                           GPACK_RGBA5551(gFillColorR, gFillColorG, gFillColorB, 1));
        gDPFillRectangle(gMainGfxPos++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
    }

    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_COPY);
}

/**
 * @brief Initialise the three OSTask structures with the correct microcode
 *        pointers (rspboot, gspFast3D, gspDarkRift3D).
 *
 * sF3dTask       → Fast3D ucode (display-list processing)
 * sDarkRiftTask  → DarkRift3D ucode (batch processing)
 * sOverlayTask   → clone of F3D task for overlay rendering
 */
void init_rsp_task_ucodes(void) {
    sF3dTask.t.ucode_boot = rspbootTextStart;
    sF3dTask.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    sF3dTask.t.ucode = gspFast3DTextStart;
    sF3dTask.t.ucode_data = gspFast3DDataStart;
    memcpy(&sOverlayTask, &sF3dTask, sizeof(OSTask));

    sOverlayTask.t.ucode = gspFast3DTextStart;
    sOverlayTask.t.ucode_data = gspFast3DDataStart;

    sDarkRiftTask.t.ucode_boot = rspbootTextStart;
    sDarkRiftTask.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    sDarkRiftTask.t.ucode = gspDarkRift3DTextStart;
    sDarkRiftTask.t.ucode_data = gspDarkRift3DDataStart;

    gSchedTaskCount = 0;
}

/**
 * @brief Scheduler thread entry.  Infinite loop: wait for an RSP task,
 *        start it, wait for SP (and optionally DP) completion, then loop.
 *
 * State variable sRspState:
 *   RSP_IDLE — RCP idle (no task running)
 *   RSP_BUSY — SP (RSP) busy
 *   RDP_BUSY — SP + DP (RDP) busy
 *
 * When the RCP is idle, a 0x7777 token is sent to the request queue so
 * the main thread knows it is safe to submit new work.
 */
void sched_run(void *arg0) {
    OSMesg task;
    OSTime task_start;

    while (TRUE) {
        // receive task from task queue
        if (osRecvMesg(&gSchedSPTaskQueue, &task, OS_MESG_NOBLOCK) == -1) {
            // no pending tasks
            sRspState = RSP_IDLE;
            // notify the other threads that RCP is idle
            osSendMesg(&gSchedTaskRequestQueue, (OSMesg) 0x7777, OS_MESG_NOBLOCK);
            // wait until at least one task appears
            osRecvMesg(&gSchedSPTaskQueue, &task, OS_MESG_BLOCK);
        }

        // clear sp and dp queues
        while (osRecvMesg(&gSchedSPQueue, NULL, OS_MESG_NOBLOCK) != -1) {}
        while (osRecvMesg(&gSchedDPQueue, NULL, OS_MESG_NOBLOCK) != -1) {}

        sLastTaskType = ((OSTask *) task)->t.type;

        // start task and wait for its completion
        osSpTaskStart(task);
        task_start = osGetTime();
        sRspState = RSP_BUSY;
        osRecvMesg(&gSchedSPQueue, NULL, OS_MESG_BLOCK);

        sFrameProfilingMin += osGetTime() - task_start;

        // wait for RDP sync
        if (sLastTaskType != M_AUDTASK) {
            sRspState = RDP_BUSY;
            osRecvMesg(&gSchedDPQueue, NULL, OS_MESG_BLOCK);
        }

        sFrameProfilingMax += osGetTime() - task_start;
    }
}

/**
 * @brief Submit RSP tasks for the current frame.
 *
 * Drains the task-request queue (collecting outstanding 0x7777 tokens),
 * writes back the CPU data cache for RSP coherence, then sends up to
 * three tasks to the SP task queue:
 *   1. Fast3D task   – processes the main display list (gfxMain)
 *   2. DarkRift task – processes the batch stream (batchMain)
 *   3. Overlay task  – processes the overlay display list (gfxOverlay,
 *                      only when GFX_FLAG_OVERLAY is set)
 *
 * Tasks are skipped when sVBlankBehind is non-zero
 * (frame-dropping catch-up).
 */
void submit_scheduled_tasks(void) {
    // consume any stale 0x7777 tokens left from the previous sync cycle
    while (osRecvMesg(&gSchedTaskRequestQueue, NULL, OS_MESG_NOBLOCK) != -1) {}

    osWritebackDCacheAll();
    // func_80021338 submits the audio OSTask (if audio active) and returns 1 (submitted) or 0 (muted)
    gSchedTaskCount = func_80021338();
    if (!sVBlankBehind) {
        // prepare two graphics task, one for f3d ucode, and the other for dr ucode
        sF3dTask.t.data_ptr = gActiveDisplayData->gfxMain;
        sF3dTask.t.data_size = (gMainGfxPos - gActiveDisplayData->gfxMain) * sizeof(Gfx);

        sDarkRiftTask.t.data_ptr = gActiveDisplayData->batchMain;
        sDarkRiftTask.t.data_size = (gMainBatchPos - gActiveDisplayData->batchMain) * sizeof(Batch);

        osSendMesg(&gSchedSPTaskQueue, (OSMesg) &sF3dTask, OS_MESG_BLOCK);
        osSendMesg(&gSchedSPTaskQueue, (OSMesg) &sDarkRiftTask, OS_MESG_BLOCK);

        gSchedTaskCount += 2;

        if (gGfxFlags & GFX_FLAG_OVERLAY) {
            sOverlayTask.t.data_ptr = gActiveDisplayData->gfxOverlay;
            sOverlayTask.t.data_size = (gOverlayGfxPos - gActiveDisplayData->gfxOverlay) * sizeof(Gfx);
            osSendMesg(&gSchedSPTaskQueue, (OSMesg) &sOverlayTask, OS_MESG_BLOCK);
            gSchedTaskCount++;
        }
    }
}

/**
 * @brief Block until all previously submitted RSP tasks have completed.
 *
 * Resets the system timer (osSetTime(0)) after sync — this provides a
 * clean time-base for per-frame profiling (sFrameProfilingMin/Max).
 */
void sync_scheduler_tasks(void) {
    sSyncState = SYNC_START;
    if (gSchedTaskCount != 0) {
        sSyncState = SYNC_WAITING;
        osRecvMesg(&gSchedTaskRequestQueue, NULL, OS_MESG_BLOCK);
        gSchedTaskCount = 0;
        sSyncState = SYNC_DONE;
        osSetTime(0);
    }
}

/**
 * @brief Wait for a vertical retrace (vblank).
 *
 * When the vblank queue is already full (multiple vblanks missed) the
 * function sets sVBlankBehind so submit_scheduled_tasks will skip
 * one frame to catch up.
 *
 * @param swapBuffers  if TRUE, swap the front/back framebuffers and
 *                     toggle gFramebufferIndex.
 */
void sched_wait_vretrace(u8 swapBuffers) {
    // MQ_IS_FULL → queue at capacity → missed at least one vblank.
    // Drain one message and skip frame submission to let the RCP catch up.
    if (MQ_IS_FULL(&gSchedVRetraceQueue)) {
        osRecvMesg(&gSchedVRetraceQueue, NULL, OS_MESG_BLOCK);
        sVBlankBehind = TRUE;
    } else {
        sVBlankBehind = FALSE;
        osRecvMesg(&gSchedVRetraceQueue, NULL, OS_MESG_BLOCK);
        if (swapBuffers) {
            osViSwapBuffer(gFramebuffers[gFramebufferIndex]);
            gFramebufferIndex = 1 - gFramebufferIndex;
        }
    }
}

#ifdef NON_EQUIVALENT
/**
 * @brief Full initialisation of a game mode — called once at boot.
 *
 * Sets up framebuffers at the top of RDRAM, allocates the Z-buffer
 * right after the ROM data, places the heap after the Z-buffer,
 * then calls every sub-system init function.
 */
void initialize_game_mode(u16 gameMode) {
    s32 unused[18];
    u32 a3;
    s32 tmp;
    // matching artifacts — local copies of D_8004937C / D_80049384
    UnkStruct800031FC sp28 = { 0, 90, 0, 0 };
    UnkStruct800031FC sp20 = { 0, 233, 500, 0 };

    gScreenWidth = 320;
    gScreenHeight = 240;
    // framebuffers at top of RDRAM: 2 bufs × 2 bytes/pixel × 320 × 240, minus 64 margin
    a3 = 0x80400000 - 2 * 2 * 320 * 240 - 64;

    gFramebuffers[0] = a3;
    tmp = gScreenHeight * gScreenWidth;
    gFramebuffers[1] = a3 + 2 * tmp;

    // Z-buffer starts at the end of ROM data, 64-byte aligned
    sWadMemBase = gZBuffer = ((u32) main_VRAM_END + 0x40) & ~0x3F;
    // heap starts right after the Z-buffer (0x25800 = 320×240×2 bytes)
    gHeapBase = (void *) (((u32) gZBuffer + 0x25800 + 0x40) & ~0x3F);
    initialize_memory_heap();
    func_80025E6C();
    func_80025EDC(sWadMemBase, 0x25800);
    func_80012490();
    func_80024D2C();
    audio_init();
    init_rsp_task_ucodes();
    gFillColorR = gGameModes[gameMode].unk_0C;
    gFillColorG = gGameModes[gameMode].unk_0D;
    gFillColorB = gGameModes[gameMode].unk_0E;
    func_8002A8C0(&gTaskPool, TASK_POOL_SIZE, sizeof(ObjectTask));
    func_8002AC10();
    gCamera = camera_create();
    gFogNear = gGameModes[gameMode].unk_14;
    gFogFar = gGameModes[gameMode].unk_16;
    gFogColorR = gGameModes[gameMode].unk_10;
    gFogColorG = gGameModes[gameMode].unk_11;
    gFogColorB = gGameModes[gameMode].unk_12;
    gGfxFlags = GFX_FLAG_NONE;
    if (!tmp) {} // matching artifact — original had code here
    memcpy(&sOverlayTask, &sF3dTask, sizeof(OSTask));

    D_8013C228 = NULL;
    sQuadColor = sFadeThreshold = 0;
    sScrollFillEnabled = TRUE;
    reset_post_render_hooks();
    reset_lights();
    gGlobalFlags = GAME_FLAG_TRANSITION;
    func_80024A38(0);
    func_80024A38(1);
    gDisplayData[0].perspNorm = 0;
    gDisplayData[1].perspNorm = 1; // likely a dev oversight — should be 0 like slot 0?
    gFramebufferIndex = 0;
    reset_scrollable_textures();
    func_80023200();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/sched/initialize_game_mode.s")
void initialize_game_mode(u16 gameMode);
#endif

/**
 * @brief Re-initialise sub-systems between game modes (lighter than
 *        a full initialize_game_mode).
 *
 * Resets backgrounds, heap, audio, task pool, camera, and re-reads the
 * per-mode fog / fill-colour values from the GameMode table.
 */
void reset_game_mode_systems(u16 gameMode) {
    gBgLayerList = NULL;
    gBgScrollX = 0;
    gBgScrollY = 0;
    D_80081428 = 0;
    reset_and_compact_heap();
    func_80026250();
    audio_reset();
    gFillColorR = gGameModes[gameMode].unk_0C;
    gFillColorG = gGameModes[gameMode].unk_0D;
    gFillColorB = gGameModes[gameMode].unk_0E;
    func_8002A8C0(&gTaskPool, TASK_POOL_SIZE, sizeof(ObjectTask));
    func_8002AC10();
    gCamera = camera_create();
    func_80024D2C();
    init_rsp_task_ucodes();
    gBgDlists = NULL;
    gFogNear = gGameModes[gameMode].unk_14;
    gFogFar = gGameModes[gameMode].unk_16;
    gFogColorR = gGameModes[gameMode].unk_10;
    gFogColorG = gGameModes[gameMode].unk_11;
    gFogColorB = gGameModes[gameMode].unk_12;
    gGfxFlags = GFX_FLAG_NONE;
    D_8013C228 = NULL;
    sFadeThreshold = 0;
    sScrollFillEnabled = TRUE;
    reset_post_render_hooks();
    reset_lights();
    gGlobalFlags = GAME_FLAG_TRANSITION;
    sVBlankBehind = TRUE;
    reset_scrollable_textures();
    func_80023200();
}
