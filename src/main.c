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
OSMesgQueue D_8005ADD8;
OSMesg D_8005ADF0[1];
OSMesgQueue D_8005ADF8;
OSMesgQueue D_8005AE10;
OSMesgQueue D_8005AE28;
OSMesgQueue D_8005AE40;
OSMesgQueue D_8005AE58;
OSMesg D_8005AE70[1];
OSMesg D_8005AE74[1];
OSMesg D_8005AE78[1];
OSMesg D_8005AE7C[1];
OSMesg D_8005AE80[4];

void thread1_idle(void *);
void thread3_main(void *);
void func_80002D14(void *);

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
    osCreateThread(&sThread4, 4, &func_80002D14, arg0, sThread4Stack + THREAD_4_STACK_SIZE, 11);
    if (D_80049270 == 0) {
        osStartThread(&sThread3);
    }
    osSetThreadPri(NULL, 0);

    while (1) {}
}

void thread3_main(void *arg0) {
    osCreateMesgQueue(&D_8005ADF8, D_8005AE70, ARRAY_COUNT(D_8005AE70));

    osCreateMesgQueue(&D_8005AE10, D_8005AE74, ARRAY_COUNT(D_8005AE74));
    osSetEventMesg(OS_EVENT_SP, &D_8005AE10, 0);

    osCreateMesgQueue(&D_8005AE28, D_8005AE78, ARRAY_COUNT(D_8005AE78));
    osSetEventMesg(OS_EVENT_DP, &D_8005AE28, 0);

    osCreateMesgQueue(&D_8005ADD8, D_8005ADF0, ARRAY_COUNT(D_8005ADF0));
    osViSetEvent(&D_8005ADD8, 0, 1);

    cont_init(4);

    osCreateMesgQueue(&D_8005AE40, D_8005AE7C, ARRAY_COUNT(D_8005AE7C));
    osCreateMesgQueue(&D_8005AE58, D_8005AE80, ARRAY_COUNT(D_8005AE80));
    osStartThread(&sThread4);
    func_800027A0();
}