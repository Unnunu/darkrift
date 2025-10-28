#include "common.h"

#define THREAD_1_STACK_SIZE 0x400
#define THREAD_3_STACK_SIZE 0x2000
#define THREAD_4_STACK_SIZE 0x400

s32 D_80049270 = 0;

u8 sThread1Stack[THREAD_1_STACK_SIZE];
OSThread sThread1;
OSThread sThread3;
u8 sThread3Stack[THREAD_3_STACK_SIZE];
OSThread sThread4;
u8 sThread4Stack[THREAD_4_STACK_SIZE];

u8 unknown_buffer[0x15b0 - 0x400];

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
OSMesg D_8005AE74[1];
OSMesg gSchedDPMessages[1];
OSMesg D_8005AE7C[1];
OSMesg gSchedSPTaskMessages[4];

void thread1_idle(void *);
void thread3_main(void *);
void sched_run(void *);

void func_80000450(void) {
    osInitialize();
    osCreateThread(&sThread1, 1, &thread1_idle, NULL, sThread1Stack + THREAD_1_STACK_SIZE, 10);
    osStartThread(&sThread1);
}

void thread1_idle(void *arg0) {
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
    osCreatePiManager(OS_PRIORITY_PIMGR, &sPIcmdQ, sPIcmdBuf, ARRAY_COUNT(sPIcmdBuf));
    osCreateThread(&sThread3, 3, &thread3_main, arg0, sThread3Stack + THREAD_3_STACK_SIZE, 10);
    osCreateThread(&sThread4, 4, &sched_run, arg0, sThread4Stack + THREAD_4_STACK_SIZE, 11);
    if (D_80049270 == 0) {
        osStartThread(&sThread3);
    }
    osSetThreadPri(NULL, 0);

    while (1) {}
}

void thread3_main(void *arg0) {
    osCreateMesgQueue(&gSchedDMAQueue, gSchedDMAMessages, ARRAY_COUNT(gSchedDMAMessages));

    osCreateMesgQueue(&gSchedSPQueue, D_8005AE74, ARRAY_COUNT(D_8005AE74));
    osSetEventMesg(OS_EVENT_SP, &gSchedSPQueue, 0);

    osCreateMesgQueue(&gSchedDPQueue, gSchedDPMessages, ARRAY_COUNT(gSchedDPMessages));
    osSetEventMesg(OS_EVENT_DP, &gSchedDPQueue, 0);

    osCreateMesgQueue(&gSchedVRetraceQueue, gSchedVRetraceMessages, ARRAY_COUNT(gSchedVRetraceMessages));
    osViSetEvent(&gSchedVRetraceQueue, 0, 1);

    cont_init(4);

    osCreateMesgQueue(&gSchedTaskRequestQueue, D_8005AE7C, ARRAY_COUNT(D_8005AE7C));
    osCreateMesgQueue(&gSchedSPTaskQueue, gSchedSPTaskMessages, ARRAY_COUNT(gSchedSPTaskMessages));
    osStartThread(&sThread4);
    game_main();
}