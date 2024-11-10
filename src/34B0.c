#include "common.h"
#include "string.h"

void init_heap(void);
extern void* gHeapBase;

extern long long int	gspUltraFast3DTextStart[], gspUltraFast3DTextEnd[];
extern long long int	gspUltraFast3DDataStart[], gspUltraFast3DDataEnd[];

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
extern u16* D_80080124;

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
extern s32 D_80080140[20];
extern s32 D_80080190[20];
extern s32 D_8013F0B0;
extern s32 D_8013C550;

typedef struct UnkStruct800031FC {
    /* 0x00 */ char unk_00[8];
} UnkStruct800031FC;

extern UnkStruct800031FC D_8004937C;
extern UnkStruct800031FC D_80049384;
void func_80025E6C(void);
void func_80025EDC(s32 arg0, s32 arg1);
void func_80012490(void);
void func_80024D2C(void);
void func_800207E4(void);
void func_8002A8C0(s32*, s32, s32);
s32 func_800395D4(void);
void func_80034508(void);
void func_80024A38(s32);
void func_800343EC(void);
void func_80023200(void);
extern s32 D_8013C560;
extern UnkDelta D_8004BB48[];
extern s32 D_8008012C;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;
extern u16 D_80080136;
extern u16 D_80080138;
extern s32 D_8013C228;
extern s16 D_80080116;
extern s16 D_80080118;
extern s16 D_8005BFC0;
extern s16 D_8006E072;
extern s16 D_800800FA;

extern s32 D_80049AE0;
extern s32 D_80049AE4;
extern s32 D_80049AE8;
extern s32 D_80081428;
extern s32 D_80049CF0;

void func_800007C8(void);
void func_80026250(void);
void func_80020BB4(void);
void func_8002AC10(void);

s32 func_80021338(void);

void func_800028B0(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80080140); i++) {
        D_80080140[i] = 0;
    }
}

void func_800028E0(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80080140); i++) {
        if (D_80080140[i] == 0) {
            D_80080140[i] = arg0;
            D_80080190[i] = arg1;
            return;
        }
    }
}

#ifdef NON_MATCHING
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
            gDPSetFillColor(D_8005BFD8++, ((u16)GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) | GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
            gDPFillRectangle(D_8005BFD8++, 0, 0, D_8005BFC8 - 1, D_80049AE8 + 20);
        }
    } else {
        gDPSetFillColor(D_8005BFD8++, ((u16)GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) | GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
        gDPFillRectangle(D_8005BFD8++, 0, 0, D_8005BFC8 - 1, D_8005BFCA - 1);
    }

    gDPPipeSync(D_8005BFD8++);
    gDPSetCycleType(D_8005BFD8++, G_CYC_COPY);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/34B0/func_80002978.s")
#endif

void func_80002C54(void) {
    D_8004CBC8.t.ucode_boot = rspbootTextStart;
    D_8004CBC8.t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;
    D_8004CBC8.t.ucode = gspFast3DTextStart;
    D_8004CBC8.t.ucode_data = gspFast3DDataStart;
    memcpy(&D_801389B8, &D_8004CBC8, sizeof(OSTask));

    D_801389B8.t.ucode = gspFast3DTextStart;
    D_801389B8.t.ucode_data = gspFast3DDataStart;

    D_8004CC88.t.ucode_boot = rspbootTextStart;
    D_8004CC88.t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;
    D_8004CC88.t.ucode = gspUltraFast3DTextStart;
    D_8004CC88.t.ucode_data = gspUltraFast3DDataStart;

    D_8008011C = 0;
}

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

#ifdef NON_MATCHING
void func_800031FC(u16 arg0) {
    s32 unused[20];
    UnkStruct800031FC sp28;
    UnkStruct800031FC sp20;
    s32 tmp;

    sp28 = D_8004937C;
    sp20 = D_80049384;
    D_8005BFC8 = 320;
    D_8005BFCA = 240;

    D_8005BFD0[0] = 0x803B4FC0;
    tmp = D_8005BFC8 * D_8005BFCA;
    D_8005BFD0[1] = 0x803B4FC0 + tmp * 2;

    D_80080120 = 
    D_80080124 = ((u32)&D_8013F0B0 + 0x40) & ~0x3F;
    gHeapBase = ((u32)D_80080124 + 0x25800 + 0x40) & ~0x3F;
    init_heap();
    func_80025E6C();
    func_80025EDC(D_80080124, 0x25800);
    func_80012490();
    func_80024D2C();
    func_800207E4();
    func_80002C54();
    D_80080110 = D_8004BB48[arg0].unk_0C;
    D_80080112 = D_8004BB48[arg0].unk_0D;
    D_80080114 = D_8004BB48[arg0].unk_0E;
    func_8002A8C0(&D_8013C550, 0x32, 0xA0);
    func_8002AC10();
    D_8013C560 = func_800395D4();
    D_80080136 = D_8004BB48[arg0].unk_14;
    D_80080138 = D_8004BB48[arg0].unk_16;
    D_80080130 = D_8004BB48[arg0].unk_10;
    D_80080132 = D_8004BB48[arg0].unk_11;
    D_80080134 = D_8004BB48[arg0].unk_12;
    D_8008012C = 0;
    memcpy(&D_801389B8, &D_8004CBC8, sizeof(OSTask));
    D_8013C228 = 0;
    D_80080116 = D_80080118 = 0;
    D_80080129 = 1;
    func_800028B0();
    func_80034508();
    D_8005BFC0 = 4;
    func_80024A38(0);
    func_80024A38(1);
    D_8006E072 = 0;
    D_800800FA = 1;
    D_8005BFCE = 0;
    func_800343EC();
    func_80023200();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/34B0/func_800031FC.s")
void func_800031FC(u16 arg0);
#endif

void func_80003468(u16 arg0) {
    D_80049AE0 = 0;
    D_80049AE4 = 0;
    D_80049AE8 = 0;
    D_80081428 = 0;
    func_800007C8();
    func_80026250();
    func_80020BB4();
    D_80080110 = D_8004BB48[arg0].unk_0C;
    D_80080112 = D_8004BB48[arg0].unk_0D;
    D_80080114 = D_8004BB48[arg0].unk_0E;
    func_8002A8C0(&D_8013C550, 50, 160);
    func_8002AC10();
    D_8013C560 = func_800395D4();
    func_80024D2C();
    func_80002C54();
    D_80049CF0 = 0;
    D_80080136 = D_8004BB48[arg0].unk_14;
    D_80080138 = D_8004BB48[arg0].unk_16;
    D_80080130 = D_8004BB48[arg0].unk_10;
    D_80080132 = D_8004BB48[arg0].unk_11;
    D_80080134 = D_8004BB48[arg0].unk_12;
    D_8008012C = 0;
    D_8013C228 = 0;
    D_80080118 = 0;
    D_80080129 = 1;
    func_800028B0();
    func_80034508();
    D_8005BFC0 = 4;
    D_80080128 = 1;
    func_800343EC();
    func_80023200();
}
