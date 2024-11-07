#include "common.h"

extern OSMesgQueue D_8005AE40;
extern OSMesgQueue D_8005AE58;
extern OSMesgQueue D_8005AE10;
extern OSMesgQueue D_8005AE28;
extern OSMesgQueue D_8005ADD8;

extern OSTime D_8005BEE8;
extern OSTime D_8005BEF0;

extern s32 D_8008011C;
extern u8 D_80080128;
extern s8 D_800801E2;
extern s8 D_800801E4;
extern s8 D_800801E5;
extern s32 D_800801E8;
extern s32 D_8008012C;
extern u16* D_80080120;

extern OSTask D_8004CBC8;
extern OSTask D_8004CC88;
extern OSTask D_801389B8;
extern DisplayData* D_80080100;
extern Gfx* D_8005BFD8;
extern Gfx* D_8005BFE0;
extern UnkDispStruct* D_8005BFE4;
extern u8* D_8005BFD0[];
extern u16 D_8005BFCE;
extern u16 D_8005BFC8;
extern u16 D_8005BFCA;
extern u8 D_80080129;
extern s32 D_80049AE8;
extern s16 D_80080110;
extern s16 D_80080112;
extern s16 D_80080114;

s32 func_80021338(void);

#pragma GLOBAL_ASM("asm/nonmatchings/34B0/func_800028B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/34B0/func_800028E0.s")

void func_80002978(void) {
    gDPPipeSync(D_8005BFD8++);
    gDPSetCycleType(D_8005BFD8++, G_CYC_FILL);

    if (!(D_8008012C & 8)) {
        gDPSetDepthImage(D_8005BFD8++, VIRTUAL_TO_PHYSICAL(D_80080120));
        gDPSetColorImage(D_8005BFD8++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, VIRTUAL_TO_PHYSICAL(D_80080120));
        gDPSetFillColor(D_8005BFD8++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
        gDPFillRectangle(D_8005BFD8++, 0, 0, D_8005BFC8 - 1, D_8005BFCA - 1);
        D_800801E2 = 0;
    } else {
        D_800801E2 = 1;
    }

    gDPSetColorImage(D_8005BFD8++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x01000000);

    if (D_80080129 != 0) {
        if (D_80049AE8 > 0) {
            gDPSetFillColor(D_8005BFD8++, (GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) | GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
            gDPFillRectangle(D_8005BFD8++, 0, 0, D_8005BFC8 - 1, D_80049AE8 + 20);
        }
    } else {
        gDPSetFillColor(D_8005BFD8++, (GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) | GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
        gDPFillRectangle(D_8005BFD8++, 0, 0, D_8005BFC8 - 1, D_8005BFCA - 1);
    }

    gDPPipeSync(D_8005BFD8++);
    gDPSetCycleType(D_8005BFD8++, G_CYC_COPY);
}

#pragma GLOBAL_ASM("asm/nonmatchings/34B0/func_80002C54.s")

void func_80002D14(void* arg0) {
    OSMesg sp54;
    OSTime sp4C;
    
    while (TRUE) {
        if (osRecvMesg(&D_8005AE58, &sp54, OS_MESG_NOBLOCK) == -1) {
            D_800801E4 = 0;
            osSendMesg(&D_8005AE40, (OSMesg)0x7777, OS_MESG_NOBLOCK);
            osRecvMesg(&D_8005AE58, &sp54, OS_MESG_BLOCK);
        }

        while (osRecvMesg(&D_8005AE10, NULL, OS_MESG_NOBLOCK) != -1) {}
        while (osRecvMesg(&D_8005AE28, NULL, OS_MESG_NOBLOCK) != -1) {}

        D_800801E8 = ((OSTask*)sp54)->t.type; // wut?

        osSpTaskStart(sp54);
        sp4C = osGetTime();
        D_800801E4 = 1;
        osRecvMesg(&D_8005AE10, NULL, OS_MESG_BLOCK);

        D_8005BEE8 += osGetTime() - sp4C;

        if (D_800801E8 != M_AUDTASK) {
            D_800801E4 = 2;
            osRecvMesg(&D_8005AE28, NULL, OS_MESG_BLOCK);
        }

        D_8005BEF0 += osGetTime() - sp4C;
    }
}

void func_80002F60(void) {
    while (osRecvMesg(&D_8005AE40, NULL, OS_MESG_NOBLOCK) != -1) {}

    osWritebackDCacheAll();
    D_8008011C = func_80021338();
    if (D_80080128 == 0) {
        D_8004CBC8.t.data_ptr = D_80080100->unk_80;
        D_8004CBC8.t.data_size = (D_8005BFD8 - D_80080100->unk_80) * sizeof(Gfx);

        D_8004CC88.t.data_ptr = D_80080100->unk_8080;
        D_8004CC88.t.data_size = (D_8005BFE4 - D_80080100->unk_8080) * sizeof(UnkDispStruct);

        osSendMesg(&D_8005AE58, (OSMesg)&D_8004CBC8, OS_MESG_BLOCK);
        osSendMesg(&D_8005AE58, (OSMesg)&D_8004CC88, OS_MESG_BLOCK);

        D_8008011C += 2;

        if (D_8008012C & 2) {
            D_801389B8.t.data_ptr = D_80080100->unk_6080;
            D_801389B8.t.data_size = (D_8005BFE0 - D_80080100->unk_6080) * sizeof(Gfx);
            osSendMesg(&D_8005AE58, (OSMesg)&D_801389B8, OS_MESG_BLOCK);
            D_8008011C++;
        }
    }
}

void func_800030E4(void) {
    D_800801E5 = 0;
    if (D_8008011C != 0) {
        D_800801E5 = 7;
        osRecvMesg(&D_8005AE40, NULL, OS_MESG_BLOCK);
        D_8008011C = 0;
        D_800801E5 = 1;
        osSetTime(0);
    }
}

void func_80003150(u8 arg0) {
    if (MQ_IS_FULL(&D_8005ADD8)) {
        osRecvMesg(&D_8005ADD8, NULL, OS_MESG_BLOCK);
        D_80080128 = 1;
    } else {
        D_80080128 = 0;
        osRecvMesg(&D_8005ADD8, NULL, OS_MESG_BLOCK);
        if (arg0) {
            osViSwapBuffer(D_8005BFD0[D_8005BFCE]);
            D_8005BFCE = 1 - D_8005BFCE;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/34B0/func_800031FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/34B0/func_80003468.s")
