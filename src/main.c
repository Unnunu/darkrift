/**
 * @file main.c
 * @brief Main game loop, frame rendering, and fade transition system
 *
 * Houses the top-level game mode manager, the per-frame render pipeline
 * (setup → objects → backgrounds → overlay → post-render callbacks),
 * and a two-sequence fade system:
 *
 *   EXIT  (visible→black):  start_exit_fade
 *                            → exit_fade_active (audio fade + alpha 0→255)
 *                            → exit_fade_active_no_audio
 *                            → exit_fade_wait (solid black 5 frames)
 *
 *   ENTER (black→visible):  enter_black_screen
 *                           → enter_black_countdown (7 frames black)
 *                           → enter_fade_in (alpha 255→0 until threshold)
 *
 * The two sequences are independent (no shared state machine).
 */

#include "common.h"
#include "PR/gt.h"
#include "task.h"

// volume level used as: music_set_volume target before stopping,
// and as fade-start value during reset_to_main_menu
#define AUDIO_VOLUME_1800 1800

// custom RSP command: set perspective normalization factor
#define gSPPerspNorm(pkt, dl)                       \
    {                                               \
        Gfx *_g = (Gfx *) (pkt);                    \
        _g->words.w0 = _SHIFTL(G_PERSPNORM, 24, 8); \
        _g->words.w1 = (dl);                        \
    }

extern s32 gBgDlists;
extern GameMode gGameModes[];
extern Gfx sCopyCycleDl[];
extern Gfx sModelRenderSetupDl[];

extern s32 gMusicVolumeFading;
extern s32 gSoundVolumeFading;

extern RenderContext sRenderContext;
extern BatchInfo sBatchInfoIdentity;
extern BatchInfo sBatchInfoEndOfFrame;

extern u16 gGlobalFlags;
extern u16 gNextGameMode;
extern u16 gFramebufferIndex;

extern Gfx *gBgGfxPos;
extern s16 sQuadColor;
extern s32 gGfxFlags;
extern DISPCB gPostRenderCallbacks[20];
extern s32 gPostRenderArgs[20];

/* .data */

s16 mainUnused1[] = { 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 1000, 0 };
s32 gFrameCounter = 0;
Vtx sFullscreenQuadVtx[2][4] = {
    { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
      { { { SCREEN_WIDTH << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
      { { { 0, SCREEN_HEIGHT << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
      { { { SCREEN_WIDTH << 2, SCREEN_HEIGHT << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } },
    { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
      { { { SCREEN_WIDTH << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
      { { { 0, SCREEN_HEIGHT << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
      { { { SCREEN_WIDTH << 2, SCREEN_HEIGHT << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } }
};
BatchTriangle sQuadTriangles[] = { { 0, 1, 2, 0 }, { 2, 1, 3, 0 } };
s32 mainUnused2[] = { 0, 0, 0 };
Vec3s gZeroRotation = { 0, 0, 0 };
Vec4i gZeroPosition = { 0, 0, 0, 0 };
CharLighting gDefaultLighting = { { { { 255, 255, 255, 255 }, 0, 0, -127 }, { { 0, 0, 0, 255 }, 73, -73, -73 } } };
UnkStruct800031FC D_8004937C = { 0, 90, 0, 0 };
UnkStruct800031FC D_80049384 = { 0, 233, 500, 0 };

/* .bss */
s16 gCurrentGameMode;
s16 gPreviousGameMode;
OSTime unusedTimer;
OSTime sFrameProfilingAccum;
OSTime sFrameProfilingMin;
OSTime sFrameProfilingMax;
s32 sFrameProfilingCounter;
s32 gFadeAlpha;
BatchInfo sQuadBatchInfo;
Gfx sQuadTexDl[5];
Mtx unusedMainMatrix;
u16 gGlobalFlags;
u16 gNextGameMode;
s32 mainUnused3;
u16 gScreenWidth;
u16 gScreenHeight;
u16 mainUnused4;
u16 gFramebufferIndex;
void *gFramebuffers[2];
Gfx *gMainGfxPos;
Gfx *gBgGfxPos;
Gfx *gOverlayGfxPos;
Batch *gMainBatchPos;
Batch *gOverlayBatchPos;
DisplayData gDisplayData[2];
DisplayData *gActiveDisplayData;

void sync_scheduler_tasks(void);
// void submit_scheduled_tasks(void);
void initialize_game_mode(u16);
void initialize_battle_globals(void);
void reset_game_mode_systems(u16);
void update_all_game_objects(void);
void setup_zbuffer_and_clear(void);
void bg_draw_all(void);
void update_pcl_and_render_backgrounds(void);
void process_audio_completion(void);
void start_exit_fade(Object *obj);

/**
 * @brief Initialise the display data and batch/display-list pointers for a
 *        new frame. Sets segment 1 to the current framebuffer, renders start-
 *        of-frame batch markers, syncs the scheduler, waits for vblank, and
 *        executes any pending scheduled tasks.
 */
void gfx_init_frame(void) {
    gActiveDisplayData = &gDisplayData[gFramebufferIndex];
    gMainGfxPos = gActiveDisplayData->gfxMain;
    gMainBatchPos = gActiveDisplayData->batchMain;

    gSPSegment(gMainGfxPos++, 0x01, gFramebuffers[gFramebufferIndex]);
    gSPSegment(gMainGfxPos++, 0x00, 0x00000000);

    sRenderContext.segmentTable[0] = 0;
    sRenderContext.segmentTable[1] = PHYSICAL_TO_VIRTUAL(gFramebuffers[gFramebufferIndex]);

    gSPTriBatch(gMainBatchPos, (RenderContext *) osVirtualToPhysical(&sRenderContext), &sBatchInfoIdentity, NULL, NULL);
    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);
    gSPTriBatch(gMainBatchPos, NULL, &sBatchInfoEndOfFrame, NULL, NULL);
    gSPTriBatch(gMainBatchPos, NULL, NULL, NULL, NULL);
    sync_scheduler_tasks();
    sched_wait_vretrace(TRUE);
    submit_scheduled_tasks();

    gActiveDisplayData = &gDisplayData[gFramebufferIndex];
}

/**
 * @brief Render one complete frame.
 *
 * Pipeline: input → display-list setup → game-object update → Z-buffer clear
 * → background draw → projection/fog setup → audio → overlay batches →
 * post-render callbacks → scheduler sync → vblank wait → task execution.
 */
void render_frame(void) {
    OSTime frameStartTime;
    Batch *ptr;
    s32 i;

    frameStartTime = osGetTime();
    input_update();

    gActiveDisplayData = &gDisplayData[gFramebufferIndex];
    gMainGfxPos = gActiveDisplayData->gfxMain;
    gBgGfxPos = gActiveDisplayData->gfxBg;
    gOverlayGfxPos = gActiveDisplayData->gfxOverlay;
    gMainBatchPos = gActiveDisplayData->batchMain;
    gOverlayBatchPos = gActiveDisplayData->batchOverlay;

    gSPSegment(gMainGfxPos++, 0x01, gFramebuffers[gFramebufferIndex]);
    gSPSegment(gMainGfxPos++, 0x00, 0x00000000);

    sRenderContext.segmentTable[0] = 0;
    sRenderContext.segmentTable[1] = VIRTUAL_TO_PHYSICAL(gFramebuffers[gFramebufferIndex]);

    if (gGfxFlags & GFX_FLAG_OVERLAY) {
        gSPDisplayList(gOverlayGfxPos++, sCopyCycleDl);
    }

    gSPTriBatch(gMainBatchPos, (RenderContext *) osVirtualToPhysical(&sRenderContext), &sBatchInfoIdentity, NULL, NULL);
    update_all_game_objects();
    gSPDisplayList(gMainGfxPos++, sCopyCycleDl);
    setup_zbuffer_and_clear();
    bg_draw_all();

    if (!(gGfxFlags & GFX_FLAG_CUTSCENE)) {
        gSPDisplayList(gMainGfxPos++, gActiveDisplayData->gfxBg);
    }
    gSPDisplayList(gMainGfxPos++, sModelRenderSetupDl);
    gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gActiveDisplayData->mtxViewProj),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNorm(gMainGfxPos++, gActiveDisplayData->perspNorm);
    sRenderContext.perspNorm = gActiveDisplayData->perspNorm;
    gDPSetFogColor(gMainGfxPos++, gFogColorR, gFogColorG, gFogColorB, 255);
    gSPFogPosition(gMainGfxPos++, gFogNear, gFogFar);
    if (gBgDlists != NULL) {
        update_pcl_and_render_backgrounds();
    }
    process_audio_completion();

    for (ptr = gActiveDisplayData->batchOverlay; ptr != gOverlayBatchPos; ptr++) {
        gSPTriBatch(gMainBatchPos, ptr->context, ptr->info, ptr->vertices, ptr->triangles);
    }
    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);

    gSPEndDisplayList(gBgGfxPos++);

    gDPFullSync(gOverlayGfxPos++);
    gSPEndDisplayList(gOverlayGfxPos++);

    gSPTriBatch(gMainBatchPos, NULL, &sBatchInfoEndOfFrame, NULL, NULL);
    gSPTriBatch(gMainBatchPos, NULL, NULL, NULL, NULL);

    sFrameProfilingAccum += osGetTime() - frameStartTime;
    sync_scheduler_tasks();

    for (i = 0; i < ARRAY_COUNT(gPostRenderCallbacks); i++) {
        if (gPostRenderCallbacks[i] != NULL && gPostRenderCallbacks[i](gPostRenderArgs[i]) == 0) {
            gPostRenderCallbacks[i] = NULL;
        }
    }

    sched_wait_vretrace(TRUE);
    submit_scheduled_tasks();

    if (++sFrameProfilingCounter >= 0x100) {
        sFrameProfilingCounter = 0;
        sFrameProfilingMax = sFrameProfilingMin = sFrameProfilingAccum = 0;
    }
}

/**
 * @brief Create a challenge-pause overlay (MESSAGE_ID_CHAL).
 *        In tournament mode (P1 vs CPU), a second human player on controller 2
 *        can press START — since gBattleSettings[PLAYER_2].isCpu is TRUE,
 *        this function fires instead of a normal pause.
 *        (CPU input is disabled by the caller after this returns.)
 */
Object *create_challenge_pause(void) {
    Object *obj;

    obj = func_80015FB4(MESSAGE_ID_CHAL);
    if (obj == NULL) {
        return NULL;
    }

    obj->fn_render = func_80015C58;
    sound_play(2, obj->vars[2]);
    gIsPaused = TRUE;
    gFadeAlpha = 0;
    return obj;
}

/**
 * @brief Handle the START button during gameplay.
 *
 * Behaviour depends on play mode:
 *   - PRACTICE → practice_enter_pause()
 *   - TOURNAMENT with CPU → create a challenge pause (only for CPU side)
 *   - otherwise → create a standard pause HUD message
 *
 * Pauses music, enters a render loop waiting for GAME_FLAG_UNPAUSE to be set
 * (indicating unpause), then restores audio and resumes.
 */
void handle_start_button_press(s16 whoPressed) {
    Object *chalObj;
    Object *pauseMsg;
    s16 pad;
    u8 savedP2Mirrored;
    u8 savedP1Mirrored;
    u8 failed;
    s32 counter;
    s32 savedFlag;

    counter = 6;

    failed = FALSE;
    gPlayerInput[whoPressed].pendingInput = FALSE;

    // wait for object pools to have capacity for a pause overlay
    while (gTaskPool.count < 10 || gModelInstancePool.count <= 0) {
        render_frame();
    }

    switch (gPlayMode) {
        case PLAY_MODE_PRACTICE:
            practice_enter_pause(whoPressed);
            break;
        case PLAY_MODE_TOURNAMENT_P1:
        case PLAY_MODE_TOURNAMENT_P2:
            if (gBattleSettings[whoPressed].isCpu) {
                chalObj = create_challenge_pause();
                if (chalObj == NULL) {
                    failed = TRUE;
                } else {
                    gPlayerInput[whoPressed].enabled = FALSE;
                }
                break;
            }
        /* fallthrough */
        default:
            pauseMsg = create_hud_message(&gGeneralMessages[MESSAGE_ID_PAUSE], CONTEXT_ABAB);
            if (pauseMsg != NULL) {
                pauseMsg->vars[0] = whoPressed;
            } else {
                failed = TRUE;
            }
            break;
    }

    if (!failed) {
        sound_set_volume(0, 0);
        sound_set_volume(1, 0);
        music_set_volume(AUDIO_VOLUME_1800);
        // one frame between volume change and seq stop — timing quirk
        render_frame();

        alSeqpStop(gMusicPlayer);

        savedP1Mirrored = gPlayerInput[PLAYER_1].mirrored;
        savedP2Mirrored = gPlayerInput[PLAYER_2].mirrored;
        savedFlag = gGfxFlags & GFX_FLAG_10;
        gGfxFlags |= GFX_FLAG_10;

        while (!(gGlobalFlags & GAME_FLAG_UNPAUSE)) {
            if (gPlayMode != PLAY_MODE_PRACTICE) {
                gPlayerInput[PLAYER_1].mirrored = gPlayerInput[PLAYER_2].mirrored = FALSE;
            }
            render_frame();
        }

        if (!savedFlag) {
            gGfxFlags &= ~GFX_FLAG_10;
        }
        gPlayerInput[PLAYER_1].mirrored = savedP1Mirrored;
        gPlayerInput[PLAYER_2].mirrored = savedP2Mirrored;

        gPlayerInput[whoPressed].pendingInput = FALSE;
        gIsPaused = FALSE;
        gGlobalFlags &= ~GAME_FLAG_UNPAUSE;
        alSeqSetLoc(gMusicSequence, &gMusicMarkerStart);
        alSeqpPlay(gMusicPlayer);
        music_set_volume(gMusicVolume);
        sound_set_volume(0, gSoundVolume);
        sound_set_volume(1, gSoundVolume);
    } else {
        // overlay creation failed — brief cooldown, return without pausing
        while (--counter > 0) {
            render_frame();
        }
    }
}

/**
 * @brief Reset global state and transition to the main menu.
 *        Plays a fade-out effect, waits for START+Z to be released,
 *        sets gNextGameMode to GAME_MODE_MAIN_MENU, and syncs the scheduler.
 */
void reset_to_main_menu(void) {
    gGlobalFlags = 0;
    gIsPaused = TRUE;
    gSoundVolumeFading = gMusicVolumeFading = AUDIO_VOLUME_1800;

    create_worker(start_exit_fade, OBJ_PRIO_DEFAULT);
    while (!(gGlobalFlags & GAME_FLAG_MODE_DONE)) {
        render_frame();
    }
    gIsPaused = FALSE;

    // ensure START+Z released before and after setting next mode
    while (gPlayerInput[PLAYER_1].buttons == (INP_START | INP_ZTRIG) ||
           gPlayerInput[PLAYER_2].buttons == (INP_START | INP_ZTRIG)) {
        render_frame();
    }

    gNextGameMode = GAME_MODE_MAIN_MENU;

    while (gPlayerInput[PLAYER_1].buttons == (INP_START | INP_ZTRIG) ||
           gPlayerInput[PLAYER_2].buttons == (INP_START | INP_ZTRIG)) {
        render_frame();
    }

    sync_scheduler_tasks();
    sched_wait_vretrace(FALSE);
}

/**
 * @brief Main game loop. Runs the active game mode until it signals exit.
 *
 * Monitors START button (pause/challenge), toggles pause when a battle
 * finishes, plays a fade-out transition when the mode exits, ensures the
 * display pipeline is in a clean state for the next mode.
 */
void game_main_loop(void) {
    gFramebufferIndex = sFrameProfilingCounter = sFrameProfilingMax = sFrameProfilingMin = sFrameProfilingAccum = 0;

    // loop until BOTH mode-done AND enter-done are set
    while (!(gGlobalFlags & GAME_FLAG_MODE_DONE) || !(gGlobalFlags & GAME_FLAG_ENTER_DONE)) {
        if (!(gGlobalFlags & GAME_FLAG_BATTLE_FINISHED) && !(gGlobalFlags & GAME_FLAG_TRANSITION) &&
            gPlayerInput[PLAYER_1].buttons == INP_START && gPlayerInput[PLAYER_1].enabled &&
            gPlayerInput[PLAYER_1].pendingInput) {
            handle_start_button_press(PLAYER_1);
        } else if (!(gGlobalFlags & GAME_FLAG_BATTLE_FINISHED) && !(gGlobalFlags & GAME_FLAG_TRANSITION) &&
                   gPlayerInput[PLAYER_2].buttons == INP_START && gPlayerInput[PLAYER_2].enabled &&
                   gPlayerInput[PLAYER_2].pendingInput) {
            handle_start_button_press(PLAYER_2);
        }

        // unclear why gIsPaused toggles every frame during BATTLE_FINISHED
        if (gGlobalFlags & GAME_FLAG_BATTLE_FINISHED) {
            gIsPaused = 1 - gIsPaused;
        }
        render_frame();
    }

    gGlobalFlags &= ~(GAME_FLAG_BATTLE_FINISHED | GAME_FLAG_MODE_DONE);
    gGlobalFlags |= GAME_FLAG_MODE_EXITING;

    if (!(gGlobalFlags & GAME_FLAG_SKIP_EXIT_FADE)) {
        if (!(gGlobalFlags & GAME_FLAG_20)) {
            gIsPaused = TRUE;
        }
        create_worker(start_exit_fade, OBJ_PRIO_DEFAULT);
        while (!(gGlobalFlags & GAME_FLAG_MODE_DONE)) {
            render_frame();
        }
        gIsPaused = FALSE;
    }

    gGlobalFlags &= ~GAME_FLAG_MODE_EXITING;

    // first call drains pending vblank/tasks, second sets clean frame state
    gfx_init_frame();
    gfx_init_frame();

    // drain scheduler and RDP twice to guarantee clean state before next mode
    sync_scheduler_tasks();
    sched_wait_vretrace(FALSE);

    sync_scheduler_tasks();
    sched_wait_vretrace(FALSE);
}

/**
 * @brief Draw an opaque fullscreen quad using the overlay batch.
 *        Sets up triangle-batch state with opaque render mode and solid
 *        shade combine, then submits the quad triangles.
 */
void draw_solid_quad(s32 alpha, Vtx *vertices) {
    Gfx *gfx = sQuadTexDl;
    s32 i;

    if (vertices == NULL) {
        vertices = sFullscreenQuadVtx[gFramebufferIndex];
    }

    sQuadBatchInfo.header.triMask = 0;
    sQuadBatchInfo.header.unk_04 = 0;
    sQuadBatchInfo.header.vtxNum = 4;
    sQuadBatchInfo.header.vtxOffset = 0;
    sQuadBatchInfo.header.numTriangles = 2;
    sQuadBatchInfo.header.unk_0B = 2;
    sQuadBatchInfo.header.texGfx = sQuadTexDl;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_RENDERMODE, G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    for (i = 0; i < 4; i++) {
        vertices[i].v.cn[3] = alpha;
        vertices[i].v.cn[0] = vertices[i].v.cn[1] = vertices[i].v.cn[2] = sQuadColor;
    }

    gSPTriBatch(gOverlayBatchPos, NULL, &sQuadBatchInfo, vertices, sQuadTriangles);
}

/**
 * @brief Draw a translucent fullscreen quad using the overlay batch.
 *        Same as draw_solid_quad but with G_RM_XLU_SURF render mode.
 */
void draw_translucent_quad(s32 alpha, Vtx *vertices) {
    Gfx *gfx = sQuadTexDl;
    s32 i;

    if (vertices == NULL) {
        vertices = sFullscreenQuadVtx[gFramebufferIndex];
    }

    sQuadBatchInfo.header.triMask = 0;
    sQuadBatchInfo.header.unk_04 = 0;
    sQuadBatchInfo.header.vtxNum = 4;
    sQuadBatchInfo.header.vtxOffset = 0;
    sQuadBatchInfo.header.numTriangles = 2;
    sQuadBatchInfo.header.unk_0B = 2;
    sQuadBatchInfo.header.texGfx = sQuadTexDl;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&sQuadBatchInfo.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    for (i = 0; i < 4; i++) {
        vertices[i].v.cn[3] = alpha;
        vertices[i].v.cn[0] = vertices[i].v.cn[1] = vertices[i].v.cn[2] = sQuadColor;
    }

    gSPTriBatch(gOverlayBatchPos, NULL, &sQuadBatchInfo, vertices, sQuadTriangles);
}

/**
 * @brief Final step of the fade-in effect. Decreases alpha by 8 per frame;
 *        once below sFadeThreshold, clears the overlay-black flag, marks the
 *        object for deletion, and signals the game mode entry is done.
 */
void enter_fade_in(Object *obj) {
    if (gFadeAlpha - 8 < sFadeThreshold) {
        gGfxFlags &= ~GFX_FLAG_10;
        obj->flags |= OBJ_FLAG_DELETE;
        gGlobalFlags |= GAME_FLAG_FADE_IN_DONE;

        if (obj->vars[4] == 0) {
            gGlobalFlags &= ~GAME_FLAG_TRANSITION;
        }
        gGlobalFlags |= GAME_FLAG_ENTER_DONE;
    } else {
        gFadeAlpha -= 8;
        draw_translucent_quad(gFadeAlpha, NULL);
    }
}

/**
 * @brief Fade-in initialisation. Runs for 7 frames showing a translucent
 *        black quad, then blacks the screen and switches to
 *        enter_fade_in (which will fade back in by decreasing
 *        alpha).
 */
void enter_black_countdown(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] >= 7) {
        osViBlack(0);
        gFadeAlpha = 255;
        obj->fn_render = enter_fade_in;
    }

    draw_translucent_quad(255, NULL);
}

/**
 * @brief Game-mode transition handler. Blackens the screen, sets GFX_FLAG_10
 *        (overlay-black flag), plays the new mode's music, and optionally
 *        transitions to the fade-in effect if this is a restart (detected by
 *        OBJ_FLAG_DELETE being set).
 */
void enter_black_screen(Object *obj) {
    music_play(obj, 0);
    if (gGlobalFlags & GAME_FLAG_NO_TRANSITION) {
        gGlobalFlags |= GAME_FLAG_ENTER_DONE;
        return;
    }

    gGfxFlags |= GFX_FLAG_10;
    osViBlack(TRUE);
    gGlobalFlags &= ~GAME_FLAG_ENTER_DONE;
    music_play(obj, 0);
    if (gGlobalFlags & GAME_FLAG_TRANSITION) {
        obj->vars[4] = 1;
    }
    gGlobalFlags |= GAME_FLAG_TRANSITION;
    if (obj->flags & OBJ_FLAG_DELETE) {
        obj->flags &= ~OBJ_FLAG_DELETE;
        obj->fn_render = enter_black_countdown;
    }
    draw_translucent_quad(255, NULL);
}

/**
 * @brief Finalise the exit-fade. Draws a solid black quad for 5 frames,
 *        then signals GAME_FLAG_MODE_DONE and deletes the object.
 */
void exit_fade_wait(Object *obj) {
    draw_solid_quad(gFadeAlpha, NULL);
    obj->vars[0]++;

    if (obj->vars[0] >= 5) {
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        obj->flags |= OBJ_FLAG_DELETE;
    }
}

/**
 * @brief Exit-fade step (no audio fade). Increases alpha by 8 per frame
 *        until near 255, then switches to exit_fade_wait. Draws a
 *        translucent black quad each frame.
 */
void exit_fade_active_no_audio(Object *obj) {
    if (gFadeAlpha + 8 < 255) {
        gFadeAlpha += 8;
        draw_translucent_quad(gFadeAlpha, NULL);
        return;
    }

    if (gFadeAlpha + 1 < 255) {
        gFadeAlpha++;
        draw_translucent_quad(gFadeAlpha, NULL);
        return;
    }

    obj->fn_render = exit_fade_wait;
    if (!(gGlobalFlags & GAME_FLAG_NO_VI_BLACK)) {
        osViBlack(1);
    }

    draw_solid_quad(gFadeAlpha, NULL);
    obj->vars[0] = 0;
}

/**
 * @brief Entry point for the fade-out transition. Fades audio out, ramps up
 *        the overlay-alpha (gFadeAlpha) by 8 per frame, and when full
 *        (≥ 255) switches to exit_fade_wait (which draws solid black for
 *        5 frames then exits).
 */
void exit_fade_active(Object *obj) {
    gGfxFlags |= GFX_FLAG_10;
    audio_fade_out_all(obj, 0);

    if (obj->fn_render != exit_fade_active) {
        obj->fn_render = exit_fade_active_no_audio;
    }

    if (gFadeAlpha + 8 < 255) {
        gFadeAlpha += 8;
        draw_translucent_quad(gFadeAlpha, NULL);
        return;
    }

    if (gFadeAlpha + 1 < 255) {
        gFadeAlpha++;
        draw_translucent_quad(gFadeAlpha, NULL);
        return;
    }

    obj->fn_render = exit_fade_wait;
    if (!(gGlobalFlags & GAME_FLAG_NO_VI_BLACK)) {
        osViBlack(1);
    }

    draw_solid_quad(gFadeAlpha, NULL);
    obj->vars[0] = 0;
}

/**
 * @brief Worker entry for the fade-out effect. Initialises alpha to 0 (or
 *        preserves it if GAME_FLAG_PRESERVE_FADE_ALPHA is set), then delegates to
 *        exit_fade_active.
 */
void start_exit_fade(Object *obj) {
    if (!(gGlobalFlags & GAME_FLAG_PRESERVE_FADE_ALPHA)) {
        gFadeAlpha = 0;
    }

    gGlobalFlags &= ~GAME_FLAG_PRESERVE_FADE_ALPHA;
    obj->fn_render = exit_fade_active;
    draw_translucent_quad(gFadeAlpha, NULL);
}

/**
 * @brief Top-level game-mode manager.
 *
 * Starts at LOGO, then cycles through game modes forever:
 *   1. Create an enter_black_screen worker
 *   2. Run the mode's fnRun
 *   3. Black the screen, sync the scheduler
 *   4. Call reset_game_mode_systems() for the next mode
 */
void game_mode_manager(void) {
    gNextGameMode = GAME_MODE_LOGO;
    initialize_game_mode(gNextGameMode);
    initialize_battle_globals();

    while (TRUE) {
        gCurrentGameMode = gNextGameMode;
        create_worker(enter_black_screen, OBJ_PRIO_HIGHER);
        gGameModes[gNextGameMode].fnRun();
        if (!(gGlobalFlags & GAME_FLAG_NO_VI_BLACK)) {
            osViBlack(1);
        }
        sync_scheduler_tasks();
        sched_wait_vretrace(FALSE);
        gPreviousGameMode = gCurrentGameMode;
        reset_game_mode_systems(gNextGameMode);
    }
}