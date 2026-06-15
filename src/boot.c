#include "common.h"

/**
 * @file boot.c
 * @brief OS and thread initialization
 *
 * Creates the idle, game, and scheduler threads. Initializes VI/PI managers
 * and the message queues/events that the scheduler needs.
 *
 * Thread layout:
 *   Thread 1 (idle):   VI/PI init → spawns threads 3 & 4 → idle loop
 *   Thread 3 (game):   Queues/events → cont_init → game_mode_manager
 *   Thread 4 (sched):  RSP/RDP task scheduling
 */

#define IDLE_THREAD_STACK_SIZE 0x400
#define GAME_THREAD_STACK_SIZE 0x2000
#define SCHED_THREAD_STACK_SIZE 0x400

s32 sSkipGameThread = 0; // debug: skip starting the game thread

u8 sIdleThreadStack[IDLE_THREAD_STACK_SIZE];
OSThread sIdleThread;
OSThread sGameThread;
u8 sGameThreadStack[GAME_THREAD_STACK_SIZE];
OSThread sSchedThread;
u8 sSchedThreadStack[SCHED_THREAD_STACK_SIZE];

u8 boot_pad1[0x11b0]; // unused

OSMesg sPIcmdBuf[8];
OSMesgQueue sPIcmdQ;
OSMesgQueue gSchedVRetraceQueue;
OSMesg gSchedVRetraceMessages[1];
OSMesgQueue gSchedDMAQueue;
OSMesgQueue gSchedSPQueue;
OSMesgQueue gSchedDPQueue;
OSMesgQueue gSchedTaskRequestQueue;
OSMesgQueue gSchedSPTaskQueue;
OSMesg gSchedDMAMessages[1];
OSMesg sSchedSPEventMessages[1];
OSMesg gSchedDPMessages[1];
OSMesg sSchedTaskRequestMessages[1];
OSMesg gSchedSPTaskMessages[4];

void idle_thread(void *);
void game_thread(void *);
void sched_run(void *);

/**
 * @brief First C function called after boot. Initializes the OS and starts
 *        thread 1 (idle), which will then set up the rest of the system.
 */
void boot_main(void) {
    osInitialize();
    osCreateThread(&sIdleThread, 1, &idle_thread, NULL, sIdleThreadStack + IDLE_THREAD_STACK_SIZE, 10);
    osStartThread(&sIdleThread);
}

/**
 * @brief Idle thread body. Initializes display, PI DMA, and spawns the
 *        game + scheduler threads before dropping to lowest priority.
 */
void idle_thread(void *arg0) {
    osCreateViManager(OS_PRIORITY_VIMGR);
    if (osTvType == OS_TV_NTSC) {
        /* Replace low byte of NTSC burst timing with 76 (custom value) */
        osViModeTable[OS_VI_NTSC_LAN1].comRegs.burst &= ~0xFF;
        osViModeTable[OS_VI_NTSC_LAN1].comRegs.burst |= 76;
        osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
    } else if (osTvType == OS_TV_PAL || osTvType == OS_TV_MPAL) {
        osViSetMode(&osViModeTable[OS_VI_PAL_LAN1]);
    }
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_DITHER_OFF | OS_VI_GAMMA_OFF);
    osViBlack(1);
    osCreatePiManager(OS_PRIORITY_PIMGR, &sPIcmdQ, sPIcmdBuf, ARRAY_COUNT(sPIcmdBuf));
    osCreateThread(&sGameThread, 3, &game_thread, arg0, sGameThreadStack + GAME_THREAD_STACK_SIZE, 10);
    osCreateThread(&sSchedThread, 4, &sched_run, arg0, sSchedThreadStack + SCHED_THREAD_STACK_SIZE, 11);
    if (sSkipGameThread == 0) {
        osStartThread(&sGameThread);
    }
    osSetThreadPri(NULL, OS_PRIORITY_IDLE);

    while (1) {}
}

/**
 * @brief Game thread (thread 3). Creates all scheduler queues and event
 *        handlers, initializes controllers, then runs game_mode_manager().
 */
void game_thread(void *arg0) {
    osCreateMesgQueue(&gSchedDMAQueue, gSchedDMAMessages, ARRAY_COUNT(gSchedDMAMessages));

    osCreateMesgQueue(&gSchedSPQueue, sSchedSPEventMessages, ARRAY_COUNT(sSchedSPEventMessages));
    osSetEventMesg(OS_EVENT_SP, &gSchedSPQueue, 0);

    osCreateMesgQueue(&gSchedDPQueue, gSchedDPMessages, ARRAY_COUNT(gSchedDPMessages));
    osSetEventMesg(OS_EVENT_DP, &gSchedDPQueue, 0);

    osCreateMesgQueue(&gSchedVRetraceQueue, gSchedVRetraceMessages, ARRAY_COUNT(gSchedVRetraceMessages));
    osViSetEvent(&gSchedVRetraceQueue, 0, 1);

    cont_init(MAXCONTROLLERS);

    osCreateMesgQueue(&gSchedTaskRequestQueue, sSchedTaskRequestMessages, ARRAY_COUNT(sSchedTaskRequestMessages));
    osCreateMesgQueue(&gSchedSPTaskQueue, gSchedSPTaskMessages, ARRAY_COUNT(gSchedSPTaskMessages));
    osStartThread(&sSchedThread);
    game_mode_manager();
}