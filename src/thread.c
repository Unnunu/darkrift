#include "common.h"

#define x_d84e55d1 0x400
#define x_b7a8fb33 0x2000
#define x_a819b0ad 0x400

s32 D_80049270 = 0;

u8 x_607bed22[x_d84e55d1];
OSThread x_12856845;
OSThread x_e5e2fe89;
u8 x_4882e498[x_b7a8fb33];
OSThread x_5cb83de5;
u8 x_2923a40b[x_a819b0ad];

u8 x_d7e5a3b9[0x15b0 - 0x400];

OSMesg x_2c62e827[8];
OSMesgQueue x_5eac317e;
OSMesgQueue x_76074a65;
OSMesg x_c35756dd[1];
OSMesgQueue x_0c7f0f6c;
OSMesgQueue x_a4cdf342;
OSMesgQueue x_9e70b6be;
OSMesgQueue x_c0f7aef0;
OSMesgQueue x_72d58a77;
OSMesg x_4af5dc00[1];
OSMesg D_8005AE74[1];
OSMesg x_76886650[1];
OSMesg D_8005AE7C[1];
OSMesg x_ae4dbfde[4];

void x_9bc493d4(void *);
void x_e090ae0b(void *);
void x_0ab76ff1(void *);

/**
 * @brief Initializes the OS and creates the idle thread (thread 1)
 *
 * This function sets up the operating system and creates the first thread,
 * which is responsible for initializing other system components.
 */
void x_74dda22f(void) {
    osInitialize();
    osCreateThread(&x_12856845, 1, &x_9bc493d4, NULL, x_607bed22 + x_d84e55d1, 10);
    osStartThread(&x_12856845);
}

/**
 * @brief IDLE thread function (thread 1)
 *
 * Initializes VI and PI managers, then creates and starts the main game thread (thread 3)
 * and scheduler thread (thread 4). Runs an infinite loop after initialization.
 *
 * @param arg0 Unused argument (standard for thread entry points)
 */
void x_9bc493d4(void *x_cc1d0de5) {
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
    osCreatePiManager(OS_PRIORITY_PIMGR, &x_5eac317e, x_2c62e827, x_e286d4b7(x_2c62e827));
    osCreateThread(&x_e5e2fe89, 3, &x_e090ae0b, x_cc1d0de5, x_4882e498 + x_b7a8fb33, 10);
    osCreateThread(&x_5cb83de5, 4, &x_0ab76ff1, x_cc1d0de5, x_2923a40b + x_a819b0ad, 11);
    if (D_80049270 == 0) {
        osStartThread(&x_e5e2fe89);
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
void x_e090ae0b(void *x_cc1d0de5) {
    osCreateMesgQueue(&x_0c7f0f6c, x_4af5dc00, x_e286d4b7(x_4af5dc00));

    osCreateMesgQueue(&x_a4cdf342, D_8005AE74, x_e286d4b7(D_8005AE74));
    osSetEventMesg(OS_EVENT_SP, &x_a4cdf342, 0);

    osCreateMesgQueue(&x_9e70b6be, x_76886650, x_e286d4b7(x_76886650));
    osSetEventMesg(OS_EVENT_DP, &x_9e70b6be, 0);

    osCreateMesgQueue(&x_76074a65, x_c35756dd, x_e286d4b7(x_c35756dd));
    osViSetEvent(&x_76074a65, 0, 1);

    x_083782bc(MAXCONTROLLERS);

    osCreateMesgQueue(&x_c0f7aef0, D_8005AE7C, x_e286d4b7(D_8005AE7C));
    osCreateMesgQueue(&x_72d58a77, x_ae4dbfde, x_e286d4b7(x_ae4dbfde));
    osStartThread(&x_5cb83de5);
    x_14ae77a0();
}