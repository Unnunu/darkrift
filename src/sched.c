#include "common.h"
#include "string.h"
#include "camera.h"
#include "task.h"
#include "ld_addrs.h"

void x_82b801fe(void);
extern void *x_40c4fc96;

extern long long int gspDarkRift3DTextStart[], gspDarkRift3DTextEnd[];
extern long long int gspDarkRift3DDataStart[], gspDarkRift3DDataEnd[];

extern OSMesgQueue x_c0f7aef0;
extern OSMesgQueue x_72d58a77;
extern OSMesgQueue x_a4cdf342;
extern OSMesgQueue x_9e70b6be;
extern OSMesgQueue x_76074a65;

extern OSTime D_8005BEE8;
extern OSTime D_8005BEF0;

extern OSTask D_8004CBC8;
extern OSTask D_8004CC88;
extern OSTask D_801389B8;
extern x_ee01e8c6 *D_80080100;
extern Gfx *x_9a3c07b8;
extern Gfx *x_d8cbce84;
extern x_320b5d80 *x_8a79b283;
extern u8 *x_96f79785[];
extern u16 D_8005BFCE;
extern u16 x_a4f5fb93;
extern s32 D_8013F0B0;
extern x_ee01e8c6 D_8005BFF0[2];

extern x_cc16c016 D_8004937C;
extern x_cc16c016 D_80049384;
void x_43d722ac(void);
void x_ab4a6fed(s32 x_cc1d0de5, s32 x_84ff873b);
void x_342bc581(void);
void x_14384217(void);
void x_3ef429e1(void);
Object *x_7b6cfabc(void);
void x_6491559d(void);
void x_15468514(s32);
void x_13905dd7(void);
void x_38c80ca9(void);
extern s16 D_800800FA;

extern s32 x_e74df613;
extern s32 x_6c647b3a;
extern s32 D_80081428;
extern s32 D_80049CF0;

void x_fd701d0e(void);
void x_29f4699a(void);
void x_1e7c754d(void);
void x_3c16ed51(void);

s32 x_1790ee2a(void);

/* .bss */
s16 D_80080110;
s16 D_80080112;
s16 D_80080114;
s16 D_80080116;
s16 D_80080118;
s32 D_8008011C;
u16 *D_80080120;
u16 *D_80080124;
u8 D_80080128;
u8 D_80080129;
s32 D_8008012C;
s16 D_80080130;
s16 D_80080132;
s16 D_80080134;
s16 D_80080136;
s16 D_80080138;
x_1c3c0f22 x_9d6e6e5f[20];
s32 x_ba260e1b[20];
s16 D_800801E0;
u8 D_800801E2;
u8 D_800801E3;
s8 D_800801E4;
s8 D_800801E5;
s32 D_800801E8;

void x_46665fe1(void) {
    s32 i;

    for (i = 0; i < x_e286d4b7(x_9d6e6e5f); i++) {
        x_9d6e6e5f[i] = NULL;
    }
}

void x_71257e81(s32 (*x_f6382727)(void *), void *arg) {
    s32 i;

    for (i = 0; i < x_e286d4b7(x_9d6e6e5f); i++) {
        if (x_9d6e6e5f[i] == 0) {
            x_9d6e6e5f[i] = x_f6382727;
            x_ba260e1b[i] = arg;
            return;
        }
    }
}

void x_bdf191dd(void) {
    gDPPipeSync(x_9a3c07b8++);
    gDPSetCycleType(x_9a3c07b8++, G_CYC_FILL);

    if (!(D_8008012C & x_666c9508)) {
        gDPSetDepthImage(x_9a3c07b8++, x_c485761a(D_80080120));
        gDPSetColorImage(x_9a3c07b8++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, x_c485761a(D_80080120));
        gDPSetFillColor(x_9a3c07b8++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
        gDPFillRectangle(x_9a3c07b8++, 0, 0, x_c84980f9 - 1, x_a4f5fb93 - 1);
        D_800801E2 = FALSE;
    } else {
        D_800801E2 = TRUE;
    }

    gDPSetColorImage(x_9a3c07b8++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x01000000);

    if (D_80080129) {
        if (x_6c647b3a > 0) {
            gDPSetFillColor(x_9a3c07b8++, (GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) |
                                              GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
            gDPFillRectangle(x_9a3c07b8++, 0, 0, x_c84980f9 - 1, x_6c647b3a + 20);
        }
    } else {
        gDPSetFillColor(x_9a3c07b8++, (GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1) << 16) |
                                          GPACK_RGBA5551(D_80080110, D_80080112, D_80080114, 1));
        gDPFillRectangle(x_9a3c07b8++, 0, 0, x_c84980f9 - 1, x_a4f5fb93 - 1);
    }

    gDPPipeSync(x_9a3c07b8++);
    gDPSetCycleType(x_9a3c07b8++, G_CYC_COPY);
}

void x_596c5c60(void) {
    D_8004CBC8.t.ucode_boot = rspbootTextStart;
    D_8004CBC8.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    D_8004CBC8.t.ucode = gspFast3DTextStart;
    D_8004CBC8.t.ucode_data = gspFast3DDataStart;
    memcpy(&D_801389B8, &D_8004CBC8, sizeof(OSTask));

    D_801389B8.t.ucode = gspFast3DTextStart;
    D_801389B8.t.ucode_data = gspFast3DDataStart;

    D_8004CC88.t.ucode_boot = rspbootTextStart;
    D_8004CC88.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    D_8004CC88.t.ucode = gspDarkRift3DTextStart;
    D_8004CC88.t.ucode_data = gspDarkRift3DDataStart;

    D_8008011C = 0;
}

void x_0ab76ff1(void *x_cc1d0de5) {
    OSMesg task;
    OSTime x_a8947c6a;

    while (TRUE) {
        // receive task from task queue
        if (osRecvMesg(&x_72d58a77, &task, OS_MESG_NOBLOCK) == -1) {
            // no pending tasks
            D_800801E4 = 0;
            // notify the other threads that RCP is idle
            osSendMesg(&x_c0f7aef0, (OSMesg) 0x7777, OS_MESG_NOBLOCK);
            // wait until at least one task appears
            osRecvMesg(&x_72d58a77, &task, OS_MESG_BLOCK);
        }

        // clear sp and dp queues
        while (osRecvMesg(&x_a4cdf342, NULL, OS_MESG_NOBLOCK) != -1) {}
        while (osRecvMesg(&x_9e70b6be, NULL, OS_MESG_NOBLOCK) != -1) {}

        D_800801E8 = ((OSTask *) task)->t.type;

        // start task and wait for its completion
        osSpTaskStart(task);
        x_a8947c6a = osGetTime();
        D_800801E4 = 1;
        osRecvMesg(&x_a4cdf342, NULL, OS_MESG_BLOCK);

        D_8005BEE8 += osGetTime() - x_a8947c6a;

        // wait for RDP sync
        if (D_800801E8 != M_AUDTASK) {
            D_800801E4 = 2;
            osRecvMesg(&x_9e70b6be, NULL, OS_MESG_BLOCK);
        }

        D_8005BEF0 += osGetTime() - x_a8947c6a;
    }
}

void x_9d40d8e1(void) {
    while (osRecvMesg(&x_c0f7aef0, NULL, OS_MESG_NOBLOCK) != -1) {}

    osWritebackDCacheAll();
    D_8008011C = x_1790ee2a();
    if (D_80080128 == 0) {
        // prepare two graphics task, one for f3d ucode, and the other for dr ucode
        D_8004CBC8.t.data_ptr = D_80080100->x_700a6ea1;
        D_8004CBC8.t.data_size = (x_9a3c07b8 - D_80080100->x_700a6ea1) * sizeof(Gfx);

        D_8004CC88.t.data_ptr = D_80080100->x_79588dca;
        D_8004CC88.t.data_size = (x_8a79b283 - D_80080100->x_79588dca) * sizeof(x_320b5d80);

        osSendMesg(&x_72d58a77, (OSMesg) &D_8004CBC8, OS_MESG_BLOCK);
        osSendMesg(&x_72d58a77, (OSMesg) &D_8004CC88, OS_MESG_BLOCK);

        D_8008011C += 2;

        if (D_8008012C & x_48752861) {
            D_801389B8.t.data_ptr = D_80080100->x_a4c192ba;
            D_801389B8.t.data_size = (x_d8cbce84 - D_80080100->x_a4c192ba) * sizeof(Gfx);
            osSendMesg(&x_72d58a77, (OSMesg) &D_801389B8, OS_MESG_BLOCK);
            D_8008011C++;
        }
    }
}

void x_d4af6341(void) {
    D_800801E5 = 0;
    if (D_8008011C != 0) {
        D_800801E5 = 7;
        osRecvMesg(&x_c0f7aef0, NULL, OS_MESG_BLOCK);
        D_8008011C = 0;
        D_800801E5 = 1;
        osSetTime(0);
    }
}

void x_08779f06(u8 x_cc1d0de5) {
    if (MQ_IS_FULL(&x_76074a65)) {
        osRecvMesg(&x_76074a65, NULL, OS_MESG_BLOCK);
        D_80080128 = 1;
    } else {
        D_80080128 = 0;
        osRecvMesg(&x_76074a65, NULL, OS_MESG_BLOCK);
        if (x_cc1d0de5) {
            osViSwapBuffer(x_96f79785[D_8005BFCE]);
            D_8005BFCE = 1 - D_8005BFCE;
        }
    }
}

#ifdef NON_EQUIVALENT
void x_16b2a52b(u16 x_7cedc3fb) {
    s32 unused[18];
    u32 a3;
    s32 x_cf10d3eb;
    x_cc16c016 x_5aee6615 = { 0, 90, 0, 0 };
    x_cc16c016 x_dd7ffac5 = { 0, 233, 500, 0 };

    x_c84980f9 = 320;
    x_a4f5fb93 = 240;
    a3 = 0x80400000 - 2 * 2 * 320 * 240 - 64;

    x_96f79785[0] = a3;
    x_cf10d3eb = x_a4f5fb93 * x_c84980f9;
    x_96f79785[1] = a3 + 2 * x_cf10d3eb;

    D_80080124 = D_80080120 = ((u32) x_9caeba2b + 0x40) & ~0x3F;
    x_40c4fc96 = (void *) (((u32) D_80080120 + 0x25800 + 0x40) & ~0x3F);
    x_82b801fe();
    x_43d722ac();
    x_ab4a6fed(D_80080124, 0x25800);
    x_342bc581();
    x_14384217();
    x_3ef429e1();
    x_596c5c60();
    D_80080110 = x_4540c33c[x_7cedc3fb].x_b8173ab8;
    D_80080112 = x_4540c33c[x_7cedc3fb].x_d863406f;
    D_80080114 = x_4540c33c[x_7cedc3fb].x_f6c089c5;
    x_7824740c(&x_30839b82, 50, sizeof(x_41a0e1e6));
    x_3c16ed51();
    x_f4bce728 = x_7b6cfabc();
    D_80080136 = x_4540c33c[x_7cedc3fb].x_d23de2ad;
    D_80080138 = x_4540c33c[x_7cedc3fb].x_55739355;
    D_80080130 = x_4540c33c[x_7cedc3fb].x_60c27ea9;
    D_80080132 = x_4540c33c[x_7cedc3fb].x_ee25ce89;
    D_80080134 = x_4540c33c[x_7cedc3fb].x_747e2503;
    D_8008012C = x_0745dc0e;
    if (!x_cf10d3eb) {}
    memcpy(&D_801389B8, &D_8004CBC8, sizeof(OSTask));

    D_8013C228 = NULL;
    D_80080116 = D_80080118 = 0;
    D_80080129 = TRUE;
    x_46665fe1();
    x_6491559d();
    x_e30d50d2 = x_86c5bc33;
    x_15468514(0);
    x_15468514(1);
    D_8005BFF0[0].perspNorm = 0;
    D_8005BFF0[1].perspNorm = 1;
    D_8005BFCE = 0;
    x_13905dd7();
    x_38c80ca9();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/sched/x_16b2a52b.s")
void x_16b2a52b(u16 x_7cedc3fb);
#endif

void x_a892f516(u16 x_7cedc3fb) {
    x_3b49183f = NULL;
    x_e74df613 = 0;
    x_6c647b3a = 0;
    D_80081428 = 0;
    x_fd701d0e();
    x_29f4699a();
    x_1e7c754d();
    D_80080110 = x_4540c33c[x_7cedc3fb].x_b8173ab8;
    D_80080112 = x_4540c33c[x_7cedc3fb].x_d863406f;
    D_80080114 = x_4540c33c[x_7cedc3fb].x_f6c089c5;
    x_7824740c(&x_30839b82, 50, sizeof(x_41a0e1e6));
    x_3c16ed51();
    x_f4bce728 = x_7b6cfabc();
    x_14384217();
    x_596c5c60();
    D_80049CF0 = 0;
    D_80080136 = x_4540c33c[x_7cedc3fb].x_d23de2ad;
    D_80080138 = x_4540c33c[x_7cedc3fb].x_55739355;
    D_80080130 = x_4540c33c[x_7cedc3fb].x_60c27ea9;
    D_80080132 = x_4540c33c[x_7cedc3fb].x_ee25ce89;
    D_80080134 = x_4540c33c[x_7cedc3fb].x_747e2503;
    D_8008012C = x_0745dc0e;
    D_8013C228 = NULL;
    D_80080118 = 0;
    D_80080129 = TRUE;
    x_46665fe1();
    x_6491559d();
    x_e30d50d2 = x_86c5bc33;
    D_80080128 = 1;
    x_13905dd7();
    x_38c80ca9();
}
