#include "common.h"

#define PUSH_UNK_DISP(pkt, a, b, c, d) \
    pkt->unk_00 = a;                   \
    pkt->unk_04 = b;                   \
    pkt->unk_08 = c;                   \
    pkt->unk_0C = d;                   \
    pkt++;

#define gUnkRdpHalfCommand(pkt, dl)                  \
    {                                                \
        Gfx *_g = (Gfx *) (pkt);                     \
        _g->words.w0 = _SHIFTL(G_RDPHALF_1, 24, 8);  \
        _g->words.w1 = (unsigned int) (dl & 0xFFFF); \
    }

typedef s32 (*DISPCB)(s32);

extern s32 D_80049CF0;
extern UnkDelta D_8004BB48[];
extern Gfx D_8004CA68[];
extern Gfx D_8004CB00[];

/*
OSTask D_8004CBC8 = {
    {
        M_GFXTASK,
        OS_TASK_DP_WAIT,
        NULL,
        0,
        NULL,
        0x1000,
        NULL,
        0x800,
        0x800B85B0,
        0x400,
        0x800B89B0,
        0x801389B0,
        NULL,
        0,
        NULL,
        0
    }
};
*/

extern UnkDispStructPart1 D_8004CC20;
/*
OSTask D_8004CC88 = {
    {
        M_GFXTASK,
        OS_TASK_DP_WAIT,
        NULL,
        0,
        NULL,
        0x1000,
        NULL,
        0x800,
        NULL,
        0x400,
        NULL,
        NULL,
        NULL,
        0,
        NULL,
        0
    }
};
*/
extern UnkDispStructPart2 D_8004CCC8;
extern UnkDispStructPart2 D_8004CD30;

extern s8 D_80053020;

extern s16 D_8005BED0;
extern u16 D_8005BED2;
extern OSTime D_8005BEE0;
extern OSTime D_8005BEE8;
extern OSTime D_8005BEF0;
extern s32 D_8005BEF8;
extern s32 D_8005BEFC;
extern u16 D_8005BFC0;
extern u16 D_8005BFC2;
extern u16 D_8005BFCE;
extern void *D_8005BFD0[];
extern Gfx *D_8005BFD8;
extern Gfx *D_8005BFDC;
extern Gfx *D_8005BFE0;
extern UnkDispStruct *D_8005BFE4;
extern UnkDispStruct *D_8005BFE8;
extern DisplayData D_8005BFF0[];
extern DisplayData *D_80080100;
extern s32 D_8008012C;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;
extern s16 D_80080136;
extern s16 D_80080138;
extern DISPCB D_80080140[20];
extern s32 D_80080190[20];

void func_800030E4(void);
void func_80003150(s32);
void func_80002F60(void);
void func_800031FC(u16);
void func_80006CEC(void);
GlobalObjA *func_8002BB6C(void (*)(void), s32);
void func_80003468(u16);
void func_80024C98(void);
void func_8002B0AC(void);
void func_80002978(void);
void func_800153C4(void);
void func_8001B26C(void);
void func_800212C8(void);

void func_80001120(void) {
    D_80080100 = &D_8005BFF0[D_8005BFCE];
    D_8005BFD8 = D_80080100->unk_80;
    D_8005BFE4 = D_80080100->unk_8080;

    gSPSegment(D_8005BFD8++, 0x01, D_8005BFD0[D_8005BFCE]);
    gSPSegment(D_8005BFD8++, 0x00, 0x00000000);

    D_8004CC20.unk_10 = 0;
    D_8004CC20.unk_14 = PHYSICAL_TO_VIRTUAL(D_8005BFD0[D_8005BFCE]);

    PUSH_UNK_DISP(D_8005BFE4, osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    gDPFullSync(D_8005BFD8++);
    gSPEndDisplayList(D_8005BFD8++);
    PUSH_UNK_DISP(D_8005BFE4, NULL, &D_8004CD30, NULL, NULL);
    PUSH_UNK_DISP(D_8005BFE4, NULL, NULL, NULL, NULL);
    func_800030E4();
    func_80003150(1);
    func_80002F60();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
}

#ifdef NON_MATCHING
void func_8000132C(void) {
    UnkDispStruct *ptr;
    OSTime time1;
    s32 i;

    time1 = osGetTime();
    func_80024C98();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
    D_8005BFD8 = D_80080100->unk_80;
    D_8005BFDC = D_80080100->unk_4080;
    D_8005BFE0 = D_80080100->unk_6080;
    D_8005BFE4 = D_80080100->unk_8080;
    D_8005BFE8 = &D_80080100->unk_8080[0x800];

    gSPSegment(D_8005BFD8++, 0x01, D_8005BFD0[D_8005BFCE]);
    gSPSegment(D_8005BFD8++, 0x00, 0x00000000);

    D_8004CC20.unk_10 = 0;
    D_8004CC20.unk_14 = VIRTUAL_TO_PHYSICAL(D_8005BFD0[D_8005BFCE]);

    if (D_8008012C & 2) {
        gSPDisplayList(D_8005BFE0++, D_8004CA68);
    }

    PUSH_UNK_DISP(D_8005BFE4, osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    func_8002B0AC();
    gSPDisplayList(D_8005BFD8++, D_8004CA68);
    func_80002978();
    func_800153C4();
    if (!(D_8008012C & 1)) {
        gSPDisplayList(D_8005BFD8++, D_80080100->unk_4080);
    }
    gSPDisplayList(D_8005BFD8++, D_8004CB00);
    gSPMatrix(D_8005BFD8++, &D_80080100->unk_00, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gUnkRdpHalfCommand(D_8005BFD8++, D_80080100->unk_12080);
    D_8004CC20.unk_00 = D_80080100->unk_12080;
    gDPSetFogColor(D_8005BFD8++, D_80080130, D_80080132, D_80080134, 255);
    gSPFogPosition(D_8005BFD8++, D_80080136, D_80080138);
    if (D_80049CF0 != 0) {
        func_8001B26C();
    }
    func_800212C8();

    for (ptr = D_80080100->unk_10080; ptr != D_8005BFE8; ptr++) {
        PUSH_UNK_DISP(D_8005BFE4, ptr->unk_00, ptr->unk_04, ptr->unk_08, ptr->unk_0C);
    }
    gDPFullSync(D_8005BFD8++);
    gSPEndDisplayList(D_8005BFD8++);

    gSPEndDisplayList(D_8005BFDC++);

    gDPFullSync(D_8005BFE0++);
    gSPEndDisplayList(D_8005BFE0++);

    PUSH_UNK_DISP(D_8005BFE4, NULL, &D_8004CD30, NULL, NULL);
    PUSH_UNK_DISP(D_8005BFE4, NULL, NULL, NULL, NULL);

    D_8005BEE0 += osGetTime() - time1;
    func_800030E4();

    for (i = 0; i < ARRAY_COUNT(D_80080140); i++) {
        if (D_80080140[i] != NULL && D_80080140[i](D_80080190[i]) == 0) {
            D_80080140[i] = NULL;
        }
    }

    func_80003150(1);
    func_80002F60();
    D_8005BEF8++;
    if (D_8005BEF8 >= 0x100) {
        D_8005BEF8 = 0;
        D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_8000132C.s")
#endif

GlobalObjA *func_8000194C(void) {
    GlobalObjA *obj;

    obj = func_80015FB4(1);
    if (obj == NULL) {
        return NULL;
    }

    obj->unk_1EC = func_80015C58;
    func_800213E0(2, obj->unk_098);
    D_80053020 = 1;
    D_8005BEFC = 0;
    return obj;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_800019B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001C6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001D88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001FB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002340.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_800023E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002448.s")
void func_80002448(GlobalObjA*);

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002528.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002590.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002744.s")

void func_800027A0(void) {
    D_8005BFC2 = 0x21;
    func_800031FC(D_8005BFC2);
    func_80006CEC();

    while (TRUE) {
        D_8005BED0 = D_8005BFC2;
        func_8002BB6C(func_80002448, 0x1100);
        D_8004BB48[D_8005BFC2].unk_00();
        if (!(D_8005BFC0 & 0x800)) {
            osViBlack(1);
        }
        func_800030E4();
        func_80003150(0);
        D_8005BED2 = D_8005BED0;
        func_80003468(D_8005BFC2);
    }
}