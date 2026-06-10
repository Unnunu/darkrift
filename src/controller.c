#include "common.h"

/* -------- data ---------- */

OSContPad x_fec6efbe = { 0, 0, 0, 0 };
s32 x_10ff46c3 = 0;

/* --------- bss ---------- */

OSMesgQueue x_e43285bd;
OSMesg x_3142d020[1];
OSContStatus x_a11b92aa[MAXCONTROLLERS];
OSContPad x_0cc0a659[MAXCONTROLLERS];
OSContPad *x_f72c20e6[MAXCONTROLLERS];

s32 controller_init(s32 maxControllers) {
    s32 i;
    u8 x_4cee67f2;
    OSMesgQueue messageQueue;
    OSMesg message[1];

    osCreateMesgQueue(&messageQueue, message, 1);
    osSetEventMesg(OS_EVENT_SI, &messageQueue, (OSMesg) 1);
    osContInit(&messageQueue, &x_4cee67f2, x_a11b92aa);

    osCreateMesgQueue(&x_e43285bd, x_3142d020, 1);
    osSetEventMesg(OS_EVENT_SI, &x_e43285bd, (OSMesg) 0);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        x_f72c20e6[i] = &x_fec6efbe;
    }

    x_59ce598c[x_83106b21].x_12a7bd86 = x_59ce598c[x_6f0b3be3].x_12a7bd86 = FALSE;

    for (i = 0; i < 2; i++, x_10ff46c3++) {
        if ((x_4cee67f2 & (1 << i)) && !(x_a11b92aa[i].errno & CONT_NO_RESPONSE_ERROR)) {
            x_f72c20e6[i] = &x_0cc0a659[i];
            x_59ce598c[i].x_12a7bd86 = TRUE;
            if (x_10ff46c3 == maxControllers) {
                return x_10ff46c3;
            }
        }
    }

    osContStartReadData(&x_e43285bd);
    return x_10ff46c3;
}

void x_bb61051c(void) {
    if (osRecvMesg(&x_e43285bd, NULL, OS_MESG_NOBLOCK) != -1) {
        osContGetReadData(x_0cc0a659);
        osContStartReadData(&x_e43285bd);
    }
}
