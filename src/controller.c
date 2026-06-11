#include "common.h"

/* -------- data ---------- */

OSContPad sNullPad = { 0, 0, 0, 0 };
s32 sControllerCount = 0;

/* --------- bss ---------- */

OSMesgQueue sSiMessageQueue;
OSMesg sSiMesg[1];
OSContStatus sContStatus[MAXCONTROLLERS];
OSContPad sContPad[MAXCONTROLLERS];
OSContPad *gContPadPtrs[MAXCONTROLLERS];

s32 controller_init(s32 maxControllers) {
    s32 i;
    u8 x_4cee67f2;
    OSMesgQueue messageQueue;
    OSMesg message[1];

    osCreateMesgQueue(&messageQueue, message, 1);
    osSetEventMesg(OS_EVENT_SI, &messageQueue, (OSMesg) 1);
    osContInit(&messageQueue, &x_4cee67f2, sContStatus);

    osCreateMesgQueue(&sSiMessageQueue, sSiMesg, 1);
    osSetEventMesg(OS_EVENT_SI, &sSiMessageQueue, (OSMesg) 0);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        gContPadPtrs[i] = &sNullPad;
    }

    x_59ce598c[x_83106b21].x_12a7bd86 = x_59ce598c[x_6f0b3be3].x_12a7bd86 = FALSE;

    for (i = 0; i < 2; i++, sControllerCount++) {
        if ((x_4cee67f2 & (1 << i)) && !(sContStatus[i].errno & CONT_NO_RESPONSE_ERROR)) {
            gContPadPtrs[i] = &sContPad[i];
            x_59ce598c[i].x_12a7bd86 = TRUE;
            if (sControllerCount == maxControllers) {
                return sControllerCount;
            }
        }
    }

    osContStartReadData(&sSiMessageQueue);
    return sControllerCount;
}

void controller_read_frame(void) {
    if (osRecvMesg(&sSiMessageQueue, NULL, OS_MESG_NOBLOCK) != -1) {
        osContGetReadData(sContPad);
        osContStartReadData(&sSiMessageQueue);
    }
}
