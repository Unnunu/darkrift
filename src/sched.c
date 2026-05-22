#include "common.h"
#include "string.h"
#include "camera.h"
#include "task.h"
#include "ld_addrs.h"

void heap_init(void);
extern void *gHeapBase;

extern long long int gspDarkRift3DTextStart[], gspDarkRift3DTextEnd[];
extern long long int gspDarkRift3DDataStart[], gspDarkRift3DDataEnd[];

extern OSMesgQueue gSchedTaskRequestQueue;
extern OSMesgQueue gSchedSPTaskQueue;
extern OSMesgQueue gSchedSPQueue;
extern OSMesgQueue gSchedDPQueue;
extern OSMesgQueue gSchedVRetraceQueue;

extern OSTime D_8005BEE8;
extern OSTime D_8005BEF0;

extern OSTask D_8004CBC8;
extern OSTask D_8004CC88;
extern OSTask D_801389B8;
extern DisplayData *D_80080100;
extern Gfx *gMainGfxPos;
extern Gfx *gOverlayGfxPos;
extern Batch *gMainBatchPos;
extern u8 *gFramebuffers[];
extern u16 D_8005BFCE;
extern u16 gScreenHeight;
extern s32 D_8013F0B0;
extern DisplayData D_8005BFF0[2];

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
extern s32 D_80049CF0;

void heap_reset(void);
void func_80026250(void);
void audio_reset(void);
void func_8002AC10(void);

s32 func_80021338(void);

/* .bss */
s16 D_80080110;
s16 D_80080112;
s16 D_80080114;
s16 D_80080116;
s16 D_80080118;
s32 D_8008011C;
u16 *D_80080120;
u16 *D_80080124;
u8 D_80080128;
u8 D_80080129;
s32 D_8008012C;
s16 D_80080130;
s16 D_80080132;
s16 D_80080134;
s16 D_80080136;
s16 D_80080138;
DISPCB gPostRenderCallbacks[20];
s32 gPostRenderArgs[20];
s16 D_800801E0;
u8 D_800801E2;
u8 D_800801E3;
s8 D_800801E4;
s8 D_800801E5;
s32 D_800801E8;

void reset_post_render_hooks(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPostRenderCallbacks); i++) {
        gPostRenderCallbacks[i] = NULL;
    }
}

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

void func_80002978(void) {
    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_FILL);

    if (!(D_8008012C & GFX_FLAG_ZBUFFER)) {
        gDPSetDepthImage(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(D_80080120));
        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, VIRTUAL_TO_PHYSICAL(D_80080120));
        gDPSetFillColor(gMainGfxPos++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
        gDPFillRectangle(gMainGfxPos++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
        D_800801E2 = FALSE;
    } else {
        D_800801E2 = TRUE;
    }

    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x01000000);

    if (D_80080129) {
        if (gBgScrollY > 0) {
            gDPSetFillColor(gMainGfxPos++, (GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) |
                                               GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
            gDPFillRectangle(gMainGfxPos++, 0, 0, gScreenWidth - 1, gBgScrollY + 20);
        }
    } else {
        gDPSetFillColor(gMainGfxPos++, (GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) |
                                           GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
        gDPFillRectangle(gMainGfxPos++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
    }

    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_COPY);
}

void func_80002C54(void) {
    D_8004CBC8.t.ucode_boot = rspbootTextStart;
    D_8004CBC8.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    D_8004CBC8.t.ucode = gspFast3DTextStart;
    D_8004CBC8.t.ucode_data = gspFast3DDataStart;
    memcpy(&D_801389B8, &D_8004CBC8, sizeof(OSTask));

    D_801389B8.t.ucode = gspFast3DTextStart;
    D_801389B8.t.ucode_data = gspFast3DDataStart;

    D_8004CC88.t.ucode_boot = rspbootTextStart;
    D_8004CC88.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    D_8004CC88.t.ucode = gspDarkRift3DTextStart;
    D_8004CC88.t.ucode_data = gspDarkRift3DDataStart;

    D_8008011C = 0;
}

void sched_run(void *arg0) {
    OSMesg task;
    OSTime task_start;

    while (TRUE) {
        // receive task from task queue
        if (osRecvMesg(&gSchedSPTaskQueue, &task, OS_MESG_NOBLOCK) == -1) {
            // no pending tasks
            D_800801E4 = 0;
            // notify the other threads that RCP is idle
            osSendMesg(&gSchedTaskRequestQueue, (OSMesg) 0x7777, OS_MESG_NOBLOCK);
            // wait until at least one task appears
            osRecvMesg(&gSchedSPTaskQueue, &task, OS_MESG_BLOCK);
        }

        // clear sp and dp queues
        while (osRecvMesg(&gSchedSPQueue, NULL, OS_MESG_NOBLOCK) != -1) {}
        while (osRecvMesg(&gSchedDPQueue, NULL, OS_MESG_NOBLOCK) != -1) {}

        D_800801E8 = ((OSTask *) task)->t.type;

        // start task and wait for its completion
        osSpTaskStart(task);
        task_start = osGetTime();
        D_800801E4 = 1;
        osRecvMesg(&gSchedSPQueue, NULL, OS_MESG_BLOCK);

        D_8005BEE8 += osGetTime() - task_start;

        // wait for RDP sync
        if (D_800801E8 != M_AUDTASK) {
            D_800801E4 = 2;
            osRecvMesg(&gSchedDPQueue, NULL, OS_MESG_BLOCK);
        }

        D_8005BEF0 += osGetTime() - task_start;
    }
}

void sched_execute_tasks(void) {
    while (osRecvMesg(&gSchedTaskRequestQueue, NULL, OS_MESG_NOBLOCK) != -1) {}

    osWritebackDCacheAll();
    D_8008011C = func_80021338();
    if (D_80080128 == 0) {
        // prepare two graphics task, one for f3d ucode, and the other for dr ucode
        D_8004CBC8.t.data_ptr = D_80080100->gfxMain;
        D_8004CBC8.t.data_size = (gMainGfxPos - D_80080100->gfxMain) * sizeof(Gfx);

        D_8004CC88.t.data_ptr = D_80080100->batchMain;
        D_8004CC88.t.data_size = (gMainBatchPos - D_80080100->batchMain) * sizeof(Batch);

        osSendMesg(&gSchedSPTaskQueue, (OSMesg) &D_8004CBC8, OS_MESG_BLOCK);
        osSendMesg(&gSchedSPTaskQueue, (OSMesg) &D_8004CC88, OS_MESG_BLOCK);

        D_8008011C += 2;

        if (D_8008012C & GFX_FLAG_OVERLAY) {
            D_801389B8.t.data_ptr = D_80080100->gfxOverlay;
            D_801389B8.t.data_size = (gOverlayGfxPos - D_80080100->gfxOverlay) * sizeof(Gfx);
            osSendMesg(&gSchedSPTaskQueue, (OSMesg) &D_801389B8, OS_MESG_BLOCK);
            D_8008011C++;
        }
    }
}

void func_800030E4(void) {
    D_800801E5 = 0;
    if (D_8008011C != 0) {
        D_800801E5 = 7;
        osRecvMesg(&gSchedTaskRequestQueue, NULL, OS_MESG_BLOCK);
        D_8008011C = 0;
        D_800801E5 = 1;
        osSetTime(0);
    }
}

void sched_wait_vretrace(u8 arg0) {
    if (MQ_IS_FULL(&gSchedVRetraceQueue)) {
        osRecvMesg(&gSchedVRetraceQueue, NULL, OS_MESG_BLOCK);
        D_80080128 = 1;
    } else {
        D_80080128 = 0;
        osRecvMesg(&gSchedVRetraceQueue, NULL, OS_MESG_BLOCK);
        if (arg0) {
            osViSwapBuffer(gFramebuffers[D_8005BFCE]);
            D_8005BFCE = 1 - D_8005BFCE;
        }
    }
}

#ifdef NON_EQUIVALENT
void func_800031FC(u16 gameMode) {
    s32 unused[18];
    u32 a3;
    s32 tmp;
    UnkStruct800031FC sp28 = { 0, 90, 0, 0 };
    UnkStruct800031FC sp20 = { 0, 233, 500, 0 };

    gScreenWidth = 320;
    gScreenHeight = 240;
    a3 = 0x80400000 - 2 * 2 * 320 * 240 - 64;

    gFramebuffers[0] = a3;
    tmp = gScreenHeight * gScreenWidth;
    gFramebuffers[1] = a3 + 2 * tmp;

    D_80080124 = D_80080120 = ((u32) main_VRAM_END + 0x40) & ~0x3F;
    gHeapBase = (void *) (((u32) D_80080120 + 0x25800 + 0x40) & ~0x3F);
    heap_init();
    func_80025E6C();
    func_80025EDC(D_80080124, 0x25800);
    func_80012490();
    func_80024D2C();
    audio_init();
    func_80002C54();
    D_80080110 = gGameModes[gameMode].unk_0C;
    D_80080112 = gGameModes[gameMode].unk_0D;
    D_80080114 = gGameModes[gameMode].unk_0E;
    func_8002A8C0(&gTaskPool, 50, sizeof(ObjectTask));
    func_8002AC10();
    gCamera = camera_create();
    D_80080136 = gGameModes[gameMode].unk_14;
    D_80080138 = gGameModes[gameMode].unk_16;
    D_80080130 = gGameModes[gameMode].unk_10;
    D_80080132 = gGameModes[gameMode].unk_11;
    D_80080134 = gGameModes[gameMode].unk_12;
    D_8008012C = GFX_FLAG_NONE;
    if (!tmp) {}
    memcpy(&D_801389B8, &D_8004CBC8, sizeof(OSTask));

    D_8013C228 = NULL;
    D_80080116 = D_80080118 = 0;
    D_80080129 = TRUE;
    reset_post_render_hooks();
    reset_lights();
    gGlobalFlags = GAME_FLAG_4;
    func_80024A38(0);
    func_80024A38(1);
    D_8005BFF0[0].perspNorm = 0;
    D_8005BFF0[1].perspNorm = 1;
    D_8005BFCE = 0;
    reset_scrollable_textures();
    func_80023200();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/sched/func_800031FC.s")
void func_800031FC(u16 gameMode);
#endif

void func_80003468(u16 gameMode) {
    gBgLayerList = NULL;
    gBgScrollX = 0;
    gBgScrollY = 0;
    D_80081428 = 0;
    heap_reset();
    func_80026250();
    audio_reset();
    D_80080110 = gGameModes[gameMode].unk_0C;
    D_80080112 = gGameModes[gameMode].unk_0D;
    D_80080114 = gGameModes[gameMode].unk_0E;
    func_8002A8C0(&gTaskPool, 50, sizeof(ObjectTask));
    func_8002AC10();
    gCamera = camera_create();
    func_80024D2C();
    func_80002C54();
    D_80049CF0 = 0;
    D_80080136 = gGameModes[gameMode].unk_14;
    D_80080138 = gGameModes[gameMode].unk_16;
    D_80080130 = gGameModes[gameMode].unk_10;
    D_80080132 = gGameModes[gameMode].unk_11;
    D_80080134 = gGameModes[gameMode].unk_12;
    D_8008012C = GFX_FLAG_NONE;
    D_8013C228 = NULL;
    D_80080118 = 0;
    D_80080129 = TRUE;
    reset_post_render_hooks();
    reset_lights();
    gGlobalFlags = GAME_FLAG_4;
    D_80080128 = 1;
    reset_scrollable_textures();
    func_80023200();
}
