#include "common.h"

/* -------- data ---------- */

OSContPad gDefaultContData = { 0, 0, 0, 0 };
s32 gNumControllers = 0;

/* --------- bss ---------- */

OSMesgQueue gContMessageQueue;
OSMesg gContMessages[1];
OSContStatus gContStatus[MAXCONTROLLERS];
OSContPad gContDataArray[MAXCONTROLLERS];
OSContPad *gContData[MAXCONTROLLERS];

s32 cont_init(s32 maxControllers) {
    s32 i;
    u8 bitpattern;
    OSMesgQueue messageQueue;
    OSMesg message[1];

    osCreateMesgQueue(&messageQueue, message, 1);
    osSetEventMesg(OS_EVENT_SI, &messageQueue, (OSMesg) 1);
    osContInit(&messageQueue, &bitpattern, gContStatus);

    osCreateMesgQueue(&gContMessageQueue, gContMessages, 1);
    osSetEventMesg(OS_EVENT_SI, &gContMessageQueue, (OSMesg) 0);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        gContData[i] = &gDefaultContData;
    }

    gPlayerInput[0].unk_0B = gPlayerInput[1].unk_0B = 0;

    for (i = 0; i < 2; i++, gNumControllers++) {
        if ((bitpattern & (1 << i)) && !(gContStatus[i].errno & CONT_NO_RESPONSE_ERROR)) {
            gContData[i] = &gContDataArray[i];
            gPlayerInput[i].unk_0B = 1;
            if (gNumControllers == maxControllers) {
                return gNumControllers;
            }
        }
    }

    osContStartReadData(&gContMessageQueue);
    return gNumControllers;
}

void cont_read(void) {
    if (osRecvMesg(&gContMessageQueue, NULL, OS_MESG_NOBLOCK) != -1) {
        osContGetReadData(gContDataArray);
        osContStartReadData(&gContMessageQueue);
    }
}
