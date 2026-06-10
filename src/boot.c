#include "common.h"

#define IDLE_STACK_SIZE 0x400
#define MAIN_STACK_SIZE 0x2000
#define RSP_STACK_SIZE 0x400

s32 sBootFlags = 0;

u8 sIdleStack[IDLE_STACK_SIZE];
OSThread sIdleThread;
OSThread sMainThread;
u8 sMainStack[MAIN_STACK_SIZE];
OSThread sRspThread;
u8 sRspStack[RSP_STACK_SIZE];

u8 sPad11B0[0x15b0 - 0x400];

OSMesg sPiMgrMesgs[8];
OSMesgQueue sPiMgrMesgQueue;
OSMesgQueue sViEventQueue;
OSMesg sViMesg[1];
OSMesgQueue gPiMessageQueue;
OSMesgQueue sSpEventQueue;
OSMesgQueue sDpEventQueue;
OSMesgQueue sContMesgQueue;
OSMesgQueue gRspMessageQueue;
OSMesg sSchedMesgs[1];
OSMesg sSpMesg[1];
OSMesg sDpMesg[1];
OSMesg sContMesgs[1];
OSMesg sRspMesgs[4];

void idle_thread_func(void *);
void main_thread_func(void *);
void rsp_scheduler_thread(void *);

/**
 * @brief Initializes the OS and creates the idle thread (thread 1)
 *
 * This function sets up the operating system and creates the first thread,
 * which is responsible for initializing other system components.
 */
void boot_entry(void) {
    osInitialize();
    osCreateThread(&sIdleThread, 1, &idle_thread_func, NULL, sIdleStack + IDLE_STACK_SIZE, 10);
    osStartThread(&sIdleThread);
}

/**
 * @brief IDLE thread function (thread 1)
 *
 * Initializes VI and PI managers, then creates and starts the main game thread (thread 3)
 * and scheduler thread (thread 4). Runs an infinite loop after initialization.
 *
 * @param arg0 Unused argument (standard for thread entry points)
 */
void idle_thread_func(void *arg) {
    osCreateViManager(OS_PRIORITY_VIMGR);
    if (osTvType == OS_TV_NTSC) {
        osViModeTable[OS_VI_NTSC_LAN1].comRegs.burst &= ~0xFF;
        osViModeTable[OS_VI_NTSC_LAN1].comRegs.burst |= 76;
        osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
    } else if (osTvType == OS_TV_PAL || osTvType == OS_TV_MPAL) {
        osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1 - 14]);
    }
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_DITHER_OFF | OS_VI_GAMMA_OFF);
    osViBlack(1);
    osCreatePiManager(OS_PRIORITY_PIMGR, &sPiMgrMesgQueue, sPiMgrMesgs, ARRAY_COUNT(sPiMgrMesgs));
    osCreateThread(&sMainThread, 3, &main_thread_func, arg, sMainStack + MAIN_STACK_SIZE, 10);
    osCreateThread(&sRspThread, 4, &rsp_scheduler_thread, arg, sRspStack + RSP_STACK_SIZE, 11);
    if (sBootFlags == 0) {
        osStartThread(&sMainThread);
    }
    osSetThreadPri(NULL, 0);

    while (1) {}
}

/**
 * @brief Main game thread function (thread 3)
 *
 * Sets up all scheduler message queues and event handlers, initializes controllers,
 * starts the scheduler thread (thread 4), then enters the main game loop.
 *
 * @param arg0 Unused argument (standard for thread entry points)
 */
void main_thread_func(void *arg) {
    osCreateMesgQueue(&gPiMessageQueue, sSchedMesgs, ARRAY_COUNT(sSchedMesgs));

    osCreateMesgQueue(&sSpEventQueue, sSpMesg, ARRAY_COUNT(sSpMesg));
    osSetEventMesg(OS_EVENT_SP, &sSpEventQueue, 0);

    osCreateMesgQueue(&sDpEventQueue, sDpMesg, ARRAY_COUNT(sDpMesg));
    osSetEventMesg(OS_EVENT_DP, &sDpEventQueue, 0);

    osCreateMesgQueue(&sViEventQueue, sViMesg, ARRAY_COUNT(sViMesg));
    osViSetEvent(&sViEventQueue, 0, 1);

    controller_init(MAXCONTROLLERS);

    osCreateMesgQueue(&sContMesgQueue, sContMesgs, ARRAY_COUNT(sContMesgs));
    osCreateMesgQueue(&gRspMessageQueue, sRspMesgs, ARRAY_COUNT(sRspMesgs));
    osStartThread(&sRspThread);
    main_game_loop();
}