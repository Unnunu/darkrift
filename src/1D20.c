#include "common.h"

typedef struct UnkDelta {
    /* 0x00 */ void (*unk_00)(void);
    /* 0x04 */ char unk_04[0x1C];
} UnkDelta; // size = 0x20

#define	PUSH_UNK_DISP(pkt, a, b, c, d) \
    pkt->unk_00 = a; \
    pkt->unk_04 = b; \
    pkt->unk_08 = c; \
    pkt->unk_0C = d; \
    pkt++;

extern UnkDelta D_8004BB48[];

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

extern s32 D_8004CC20[]; // TODO struct maybe?
extern s32 D_8004CCC8;
extern s32 D_8004CD30;

extern s16 D_8005BED0;
extern u16 D_8005BED2;
extern u16 D_8005BFC0;
extern u16 D_8005BFC2;
extern u16 D_8005BFCE;
extern void* D_8005BFD0[];
extern Gfx* D_8005BFD8;
extern UnkDispStruct* D_8005BFE4;
extern DisplayData D_8005BFF0[];
extern DisplayData* D_80080100;

void func_800030E4(void);
void func_80003150(s32);
void func_80002F60(void);
void func_800031FC(u16);
void func_80006CEC(void);
void func_80002448(void);
void func_8002BB6C(void(*)(void), s32);
void func_80003468(u16);

#ifdef NON_MATCHING
void func_80001120(void) {
    D_80080100 = &D_8005BFF0[D_8005BFCE];
    D_8005BFD8 = D_8005BFF0[D_8005BFCE].unk_80;
    D_8005BFE4 = D_8005BFF0[D_8005BFCE].unk_8080;

    gSPSegment(D_8005BFD8++, 0x01, D_8005BFD0[D_8005BFCE]);
    gSPSegment(D_8005BFD8++, 0x00, 0x00000000);

    D_8004CC20[4] = 0;
    D_8004CC20[5] = PHYSICAL_TO_VIRTUAL(D_8005BFD0[D_8005BFCE]);

    PUSH_UNK_DISP(D_8005BFE4, osVirtualToPhysical(D_8004CC20), &D_8004CCC8, 0, 0);
    gDPFullSync(D_8005BFD8++);
    gSPEndDisplayList(D_8005BFD8++);
    PUSH_UNK_DISP(D_8005BFE4, 0, &D_8004CD30, 0, 0);
    PUSH_UNK_DISP(D_8005BFE4, 0, 0, 0, 0);
    func_800030E4();
    func_80003150(1);
    func_80002F60();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001120.s")
void func_80001120(void);
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_8000132C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_8000194C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_800019B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001C6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001D88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001FB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002340.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_800023E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002448.s")

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