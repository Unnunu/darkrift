#include "common.h"
#include "PR/gt.h"

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

extern u16 D_80049330[];
extern s32 D_80049CF0;
extern UnkDelta D_8004BB48[];
extern Gfx D_8004CA68[];
extern Gfx D_8004CB00[];

extern Gfx D_8005BF10;
extern Gfx D_8005BF58;
extern Gfx D_8005BF60;
extern Vtx D_800492B0[];

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

extern u8 D_80053020;

extern s16 D_8005BED0;
extern u16 D_8005BED2;
extern OSTime D_8005BEE0;
extern OSTime D_8005BEE8;
extern OSTime D_8005BEF0;
extern s32 D_8005BEF8;
extern s32 D_8005BEFC;
extern UnkDispStructPart2 D_8005BF00;
extern u16 D_8005BFC0;
extern u16 gGameMode;
extern u16 D_8005BFCE;
extern void *gFramebuffers[];
extern Gfx *D_8005BFD8;
extern Gfx *D_8005BFDC;
extern Gfx *D_8005BFE0;
extern UnkDispStruct *D_8005BFE4;
extern UnkDispStruct *D_8005BFE8;
extern DisplayData D_8005BFF0[];
extern DisplayData *D_80080100;
extern s16 D_80080116;
extern s16 D_80080118;
extern s32 D_8008012C;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;
extern s16 D_80080136;
extern s16 D_80080138;
extern DISPCB D_80080140[20];
extern s32 D_80080190[20];

void func_800030E4(void);
void sched_wait_vretrace(s32);
void sched_execute_tasks(void);
void func_800031FC(u16);
void func_80006CEC(void);
Object *func_8002BB6C(void (*)(Object *), s32);
void func_80003468(u16);
void func_80024C98(void);
void func_8002B0AC(void);
void func_80002978(void);
void func_800153C4(void);
void func_8001B26C(void);
void func_800212C8(void);
void func_80002744(Object *obj);

void func_80001120(void) {
    D_80080100 = &D_8005BFF0[D_8005BFCE];
    D_8005BFD8 = D_80080100->unk_80;
    D_8005BFE4 = D_80080100->unk_8080;

    gSPSegment(D_8005BFD8++, 0x01, gFramebuffers[D_8005BFCE]);
    gSPSegment(D_8005BFD8++, 0x00, 0x00000000);

    D_8004CC20.unk_10 = 0;
    D_8004CC20.unk_14 = PHYSICAL_TO_VIRTUAL(gFramebuffers[D_8005BFCE]);

    PUSH_UNK_DISP(D_8005BFE4, osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    gDPFullSync(D_8005BFD8++);
    gSPEndDisplayList(D_8005BFD8++);
    PUSH_UNK_DISP(D_8005BFE4, NULL, &D_8004CD30, NULL, NULL);
    PUSH_UNK_DISP(D_8005BFE4, NULL, NULL, NULL, NULL);
    func_800030E4();
    sched_wait_vretrace(TRUE);
    sched_execute_tasks();

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
    D_8005BFE8 = D_80080100->unk_10080;

    gSPSegment(D_8005BFD8++, 0x01, gFramebuffers[D_8005BFCE]);
    gSPSegment(D_8005BFD8++, 0x00, 0x00000000);

    D_8004CC20.unk_10 = 0;
    D_8004CC20.unk_14 = VIRTUAL_TO_PHYSICAL(gFramebuffers[D_8005BFCE]);

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

    sched_wait_vretrace(TRUE);
    sched_execute_tasks();
    D_8005BEF8++;
    if (D_8005BEF8 >= 0x100) {
        D_8005BEF8 = 0;
        D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_8000132C.s")
void func_8000132C(void);
#endif

Object *func_8000194C(void) {
    Object *obj;

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
void func_800019B0(s32);

#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001C6C.s")

void func_80001D88(void) {
    D_8005BFCE = D_8005BEF8 = D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;

    while (!(D_8005BFC0 & 1) || !(D_8005BFC0 & 0x1000)) {
        if (!(D_8005BFC0 & 0x200) && !(D_8005BFC0 & 0x4) && gPlayerInput[0].unk_00 == INP_START &&
            gPlayerInput[0].unk_0A && gPlayerInput[0].unk_08) {
            func_800019B0(0);
        } else if (!(D_8005BFC0 & 0x200) && !(D_8005BFC0 & 0x4) && gPlayerInput[1].unk_00 == INP_START &&
                   gPlayerInput[1].unk_0A && gPlayerInput[1].unk_08) {
            func_800019B0(1);
        }

        if (D_8005BFC0 & 0x200) {
            D_80053020 = 1 - D_80053020;
        }
        func_8000132C();
    }

    D_8005BFC0 &= ~0x201;
    D_8005BFC0 |= 0x2000;

    if (!(D_8005BFC0 & 0x10)) {
        if (!(D_8005BFC0 & 0x20)) {
            D_80053020 = 1;
        }
        func_8002BB6C(func_80002744, 0x1000);
        while (!(D_8005BFC0 & 0x1)) {
            func_8000132C();
        }
        D_80053020 = 0;
    }

    D_8005BFC0 &= ~0x2000;

    func_80001120();
    func_80001120();
    func_800030E4();
    sched_wait_vretrace(FALSE);
    func_800030E4();
    sched_wait_vretrace(FALSE);
}

#ifdef NON_MATCHING
void func_80001FB0(s32 arg0, Vtx *arg1) {
    if (arg1 == NULL) {
        arg1 = &D_800492B0[D_8005BFCE * 4];
    }

    D_8005BF00.unk_00 = 0;
    D_8005BF00.unk_04 = 0;
    D_8005BF00.unk_08 = 4;
    D_8005BF00.unk_09 = 0;
    D_8005BF00.unk_0B = D_8005BF00.unk_0A = 2;
    D_8005BF00.unk_0C = &D_8005BF58;

    gDPPipeSync(D_8005BF00.unk_0C);
    gDPSetCombineMode(&D_8005BF60, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&D_8005BF10, GT_RENDERMODE, G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gtStateSetOthermode(&D_8005BF10, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&D_8005BF10, GT_PIPELINE, G_PM_NPRIMITIVE);

    arg1[0].v.cn[3] = arg0;
    arg1[0].v.cn[0] = arg1[0].v.cn[1] = arg1[0].v.cn[2] = D_80080116;
    arg1[1].v.cn[3] = arg0;
    arg1[1].v.cn[0] = arg1[1].v.cn[1] = arg1[1].v.cn[2] = D_80080116;
    arg1[2].v.cn[3] = arg0;
    arg1[2].v.cn[0] = arg1[2].v.cn[1] = arg1[2].v.cn[2] = D_80080116;
    arg1[3].v.cn[3] = arg0;
    arg1[3].v.cn[0] = arg1[3].v.cn[1] = arg1[3].v.cn[2] = D_80080116;

    PUSH_UNK_DISP(D_8005BFE8, NULL, &D_8005BF00, arg1, D_80049330);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80001FB0.s")
void func_80001FB0(s32 arg0, Vtx *arg1);
#endif

#ifdef NON_MATCHING
void func_80002178(s32 arg0, Vtx *arg1) {
    if (arg1 == NULL) {
        arg1 = &D_800492B0[D_8005BFCE * 4];
    }

    D_8005BF00.unk_00 = 0;
    D_8005BF00.unk_04 = 0;
    D_8005BF00.unk_08 = 4;
    D_8005BF00.unk_09 = 0;
    D_8005BF00.unk_0B = D_8005BF00.unk_0A = 2;
    D_8005BF00.unk_0C = &D_8005BF58;

    gDPPipeSync(D_8005BF00.unk_0C);
    gDPSetCombineMode(&D_8005BF60, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&D_8005BF10, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&D_8005BF10, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&D_8005BF10, GT_PIPELINE, G_PM_NPRIMITIVE);

    arg1[0].v.cn[3] = arg0;
    arg1[0].v.cn[0] = arg1[0].v.cn[1] = arg1[0].v.cn[2] = D_80080116;
    arg1[1].v.cn[3] = arg0;
    arg1[1].v.cn[0] = arg1[1].v.cn[1] = arg1[1].v.cn[2] = D_80080116;
    arg1[2].v.cn[3] = arg0;
    arg1[2].v.cn[0] = arg1[2].v.cn[1] = arg1[2].v.cn[2] = D_80080116;
    arg1[3].v.cn[3] = arg0;
    arg1[3].v.cn[0] = arg1[3].v.cn[1] = arg1[3].v.cn[2] = D_80080116;

    PUSH_UNK_DISP(D_8005BFE8, NULL, &D_8005BF00, arg1, D_80049330);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1D20/func_80002178.s")
void func_80002178(s32 arg0, Vtx *arg1);
#endif

void func_80002340(Object *obj) {
    if (D_8005BEFC - 8 < D_80080118) {
        D_8008012C &= ~0x10;
        obj->unk_080 |= 0x10;
        D_8005BFC0 |= 0x100;

        if (obj->unk_0A0 == 0) {
            D_8005BFC0 &= ~0x4;
        }
        D_8005BFC0 |= 0x1000;
    } else {
        D_8005BEFC -= 8;
        func_80002178(D_8005BEFC, NULL);
    }
}

void func_800023E4(Object *obj) {
    obj->unk_090++;
    if (obj->unk_090 >= 7) {
        osViBlack(0);
        D_8005BEFC = 255;
        obj->unk_1EC = func_80002340;
    }

    func_80002178(255, NULL);
}

void func_80002448(Object *obj) {
    func_80021918(obj, 0);
    if (D_8005BFC0 & 0x400) {
        D_8005BFC0 |= 0x1000;
        return;
    }
    D_8008012C |= 0x10;
    osViBlack(1);
    D_8005BFC0 &= ~0x1000;
    func_80021918(obj, 0);
    if (D_8005BFC0 & 4) {
        obj->unk_0A0 = 1;
    }
    D_8005BFC0 |= 4;
    if (obj->unk_080 & 0x10) {
        obj->unk_080 &= ~0x10;
        obj->unk_1EC = func_800023E4;
    }
    func_80002178(255, NULL);
}

void func_80002528(Object *obj) {
    func_80001FB0(D_8005BEFC, NULL);
    obj->unk_090++;

    if (obj->unk_090 >= 5) {
        D_8005BFC0 |= 1;
        obj->unk_080 |= 0x10;
    }
}

void func_80002590(Object *obj) {
    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    if (D_8005BEFC + 1 < 255) {
        D_8005BEFC++;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    obj->unk_1EC = func_80002528;
    if (!(D_8005BFC0 & 0x800)) {
        osViBlack(1);
    }

    func_80001FB0(D_8005BEFC, NULL);
    obj->unk_090 = 0;
}

void func_80002648(Object *obj) {
    D_8008012C |= 0x10;
    func_800217A0(obj, 0);

    if (obj->unk_1EC != func_80002648) {
        obj->unk_1EC = func_80002590;
    }

    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    if (D_8005BEFC + 1 < 255) {
        D_8005BEFC++;
        func_80002178(D_8005BEFC, NULL);
        return;
    }

    obj->unk_1EC = func_80002528;
    if (!(D_8005BFC0 & 0x800)) {
        osViBlack(1);
    }

    func_80001FB0(D_8005BEFC, NULL);
    obj->unk_090 = 0;
}

void func_80002744(Object *obj) {
    if (!(D_8005BFC0 & 0x80)) {
        D_8005BEFC = 0;
    }

    D_8005BFC0 &= ~0x80;
    obj->unk_1EC = func_80002648;
    func_80002178(D_8005BEFC, NULL);
}

void func_800027A0(void) {
    gGameMode = 0x21;
    func_800031FC(gGameMode);
    func_80006CEC();

    while (TRUE) {
        D_8005BED0 = gGameMode;
        func_8002BB6C(func_80002448, 0x1100);
        D_8004BB48[gGameMode].fn_run();
        if (!(D_8005BFC0 & 0x800)) {
            osViBlack(1);
        }
        func_800030E4();
        sched_wait_vretrace(FALSE);
        D_8005BED2 = D_8005BED0;
        func_80003468(gGameMode);
    }
}