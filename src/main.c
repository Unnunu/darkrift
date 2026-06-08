#include "common.h"
#include "PR/gt.h"
#include "task.h"

#define x_d8fc928a(pkt, dl)                       \
    {                                               \
        Gfx *_g = (Gfx *) (pkt);                    \
        _g->words.w0 = _SHIFTL(G_PERSPNORM, 24, 8); \
        _g->words.w1 = (dl);                        \
    }

extern s32 D_80049CF0;
extern x_d0fba50a x_4540c33c[];
extern Gfx D_8004CA68[];
extern Gfx D_8004CB00[];

extern s32 x_b5cc849a;
extern s32 x_aec099eb;

extern x_3e2f9cf1 D_8004CC20;
extern x_c1cedf06 D_8004CCC8;
extern x_c1cedf06 D_8004CD30;

extern u16 x_e30d50d2;
extern u16 x_e38a6e19;
extern u16 D_8005BFCE;

extern Gfx *D_8005BFDC;
extern s16 D_80080116;
extern s32 D_8008012C;
extern x_1c3c0f22 x_9d6e6e5f[20];
extern s32 x_ba260e1b[20];

/* .data */

s16 D_80049290[] = { 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 1000, 0 };
s32 x_e3a9f332 = 0;
Vtx D_800492B0[2][4] = { { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { x_56e08f29 << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { 0, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { x_56e08f29 << 2, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } },
                         { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { x_56e08f29 << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { 0, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { x_56e08f29 << 2, x_84e8ddf2 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } } };
x_562d2a02 D_80049330[] = { { 0, 1, 2, 0 }, { 2, 1, 3, 0 } };
s32 D_80049338[] = { 0, 0, 0 };
x_acccb624 x_acab9952 = { 0, 0, 0 };
x_88f11482 x_c787d34b = { 0, 0, 0, 0 };
x_2bb4cf6f D_8004935C = { { { { 255, 255, 255, 255 }, 0, 0, -127 }, { { 0, 0, 0, 255 }, 73, -73, -73 } } };
x_cc16c016 D_8004937C = { 0, 90, 0, 0 };
x_cc16c016 D_80049384 = { 0, 233, 500, 0 };

/* .bss */
s16 x_f71086e0;
s16 x_4090e698;
OSTime unused;
OSTime D_8005BEE0;
OSTime D_8005BEE8;
OSTime D_8005BEF0;
s32 D_8005BEF8;
s32 D_8005BEFC;
x_c1cedf06 D_8005BF00;
Gfx D_8005BF58[5];
Mtx D_8005BF80;
u16 x_e30d50d2;
u16 x_e38a6e19;
s32 D_8005BFC4;
u16 x_c84980f9;
u16 x_a4f5fb93;
u16 D_8005BFCC;
u16 D_8005BFCE;
void *x_96f79785[2];
Gfx *x_9a3c07b8;
Gfx *D_8005BFDC;
Gfx *x_d8cbce84;
x_320b5d80 *x_8a79b283;
x_320b5d80 *x_ee137e39;
x_ee01e8c6 D_8005BFF0[2];
x_ee01e8c6 *D_80080100;

void x_d4af6341(void);
// void execute_scheduled_tasks(void);
void x_16b2a52b(u16);
void x_2d5f067a(void);
void x_a892f516(u16);
void x_efb29a7d(void);
void x_bdf191dd(void);
void x_77751af8(void);
void x_ff4031b5(void);
void x_06fa0af9(void);
void x_4f944650(Object *obj);

void x_225c77c4(void) {
    D_80080100 = &D_8005BFF0[D_8005BFCE];
    x_9a3c07b8 = D_80080100->x_700a6ea1;
    x_8a79b283 = D_80080100->x_79588dca;

    gSPSegment(x_9a3c07b8++, 0x01, x_96f79785[D_8005BFCE]);
    gSPSegment(x_9a3c07b8++, 0x00, 0x00000000);

    D_8004CC20.x_cf1ea5d1[0] = 0;
    D_8004CC20.x_cf1ea5d1[1] = x_a4e17949(x_96f79785[D_8005BFCE]);

    x_50746900(x_8a79b283, (x_3e2f9cf1 *) osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    gDPFullSync(x_9a3c07b8++);
    gSPEndDisplayList(x_9a3c07b8++);
    x_50746900(x_8a79b283, NULL, &D_8004CD30, NULL, NULL);
    x_50746900(x_8a79b283, NULL, NULL, NULL, NULL);
    x_d4af6341();
    x_08779f06(TRUE);
    x_9d40d8e1();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
}

void x_da2cde4c(void) {
    OSTime x_de1dd2f4;
    x_320b5d80 *ptr;
    s32 i;

    x_de1dd2f4 = osGetTime();
    x_0dd43bb1();

    D_80080100 = &D_8005BFF0[D_8005BFCE];
    x_9a3c07b8 = D_80080100->x_700a6ea1;
    D_8005BFDC = D_80080100->x_5b2cc439;
    x_d8cbce84 = D_80080100->x_a4c192ba;
    x_8a79b283 = D_80080100->x_79588dca;
    x_ee137e39 = D_80080100->x_b8131490;

    gSPSegment(x_9a3c07b8++, 0x01, x_96f79785[D_8005BFCE]);
    gSPSegment(x_9a3c07b8++, 0x00, 0x00000000);

    D_8004CC20.x_cf1ea5d1[0] = 0;
    D_8004CC20.x_cf1ea5d1[1] = x_c485761a(x_96f79785[D_8005BFCE]);

    if (D_8008012C & x_48752861) {
        gSPDisplayList(x_d8cbce84++, D_8004CA68);
    }

    x_50746900(x_8a79b283, (x_3e2f9cf1 *) osVirtualToPhysical(&D_8004CC20), &D_8004CCC8, NULL, NULL);
    x_efb29a7d();
    gSPDisplayList(x_9a3c07b8++, D_8004CA68);
    x_bdf191dd();
    x_77751af8();

    if (!(D_8008012C & x_f846a903)) {
        gSPDisplayList(x_9a3c07b8++, D_80080100->x_5b2cc439);
    }
    gSPDisplayList(x_9a3c07b8++, D_8004CB00);
    gSPMatrix(x_9a3c07b8++, x_c485761a(&D_80080100->x_0f39faa7),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    x_d8fc928a(x_9a3c07b8++, D_80080100->perspNorm);
    D_8004CC20.perspNorm = D_80080100->perspNorm;
    gDPSetFogColor(x_9a3c07b8++, D_80080130, D_80080132, D_80080134, 255);
    gSPFogPosition(x_9a3c07b8++, D_80080136, D_80080138);
    if (D_80049CF0 != 0) {
        x_ff4031b5();
    }
    x_06fa0af9();

    for (ptr = D_80080100->x_b8131490; ptr != x_ee137e39; ptr++) {
        x_50746900(x_8a79b283, ptr->context, ptr->info, ptr->vertices, ptr->triangles);
    }
    gDPFullSync(x_9a3c07b8++);
    gSPEndDisplayList(x_9a3c07b8++);

    gSPEndDisplayList(D_8005BFDC++);

    gDPFullSync(x_d8cbce84++);
    gSPEndDisplayList(x_d8cbce84++);

    x_50746900(x_8a79b283, NULL, &D_8004CD30, NULL, NULL);
    x_50746900(x_8a79b283, NULL, NULL, NULL, NULL);

    D_8005BEE0 += osGetTime() - x_de1dd2f4;
    x_d4af6341();

    for (i = 0; i < x_e286d4b7(x_9d6e6e5f); i++) {
        if (x_9d6e6e5f[i] != NULL && x_9d6e6e5f[i](x_ba260e1b[i]) == 0) {
            x_9d6e6e5f[i] = NULL;
        }
    }

    x_08779f06(TRUE);
    x_9d40d8e1();

    if (++D_8005BEF8 >= 0x100) {
        D_8005BEF8 = 0;
        D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;
    }
}

Object *x_a1378aba(void) {
    Object *obj;

    obj = x_68289eaa(x_69f86dd8);
    if (obj == NULL) {
        return NULL;
    }

    obj->x_0232396f = x_a1821d40;
    x_7e194d55(2, obj->x_0f4167b4[2]);
    x_66c4e9c7 = TRUE;
    D_8005BEFC = 0;
    return obj;
}

void x_14a106cd(s16 x_ce13e71a) {
    Object *v0;
    Object *v1;
    s16 pad;
    u8 x_235d81c7;
    u8 x_93463df6;
    u8 x_5cb3a50d;
    s32 counter;
    s32 x_5aee6615;

    counter = 6;

    x_5cb3a50d = FALSE;
    x_59ce598c[x_ce13e71a].x_c4397934 = FALSE;

    while (x_30839b82.count < 10 || x_5c163218.count <= 0) {
        x_da2cde4c();
    }

    switch (x_5e4e2788) {
        case x_79c2dc5b:
            x_3c859f4e(x_ce13e71a);
            break;
        case x_e483bf48:
        case x_557d3dd6:
            if (x_77831b2c[x_ce13e71a].x_03604d94) {
                v0 = x_a1378aba();
                if (v0 == NULL) {
                    x_5cb3a50d = TRUE;
                } else {
                    x_59ce598c[x_ce13e71a].enabled = FALSE;
                }
                break;
            }
        /* fallthrough */
        default:
            v1 = x_1bb3ac04(&x_dd2c4e91[x_2d0f1752], x_2587f84f);
            if (v1 != NULL) {
                v1->x_0f4167b4[0] = x_ce13e71a;
            } else {
                x_5cb3a50d = TRUE;
            }
            break;
    }

    if (!x_5cb3a50d) {
        x_62551fe9(0, 0);
        x_62551fe9(1, 0);
        x_20c52092(1800);
        x_da2cde4c();

        alSeqpStop(x_85a4d96f);

        x_93463df6 = x_59ce598c[x_83106b21].x_d93bcabf;
        x_235d81c7 = x_59ce598c[x_6f0b3be3].x_d93bcabf;
        x_5aee6615 = D_8008012C & x_c626209d;
        D_8008012C |= x_c626209d;

        while (!(x_e30d50d2 & x_700de048)) {
            if (x_5e4e2788 != x_79c2dc5b) {
                x_59ce598c[x_83106b21].x_d93bcabf = x_59ce598c[x_6f0b3be3].x_d93bcabf = FALSE;
            }
            x_da2cde4c();
        }

        if (!x_5aee6615) {
            D_8008012C &= ~x_c626209d;
        }
        x_59ce598c[x_83106b21].x_d93bcabf = x_93463df6;
        x_59ce598c[x_6f0b3be3].x_d93bcabf = x_235d81c7;

        x_59ce598c[x_ce13e71a].x_c4397934 = FALSE;
        x_66c4e9c7 = FALSE;
        x_e30d50d2 &= ~x_700de048;
        alSeqSetLoc(x_d896e1bb, &x_9ae0d7c5);
        alSeqpPlay(x_85a4d96f);
        x_20c52092(x_66ddef46);
        x_62551fe9(0, x_15814eea);
        x_62551fe9(1, x_15814eea);
    } else {

        while (--counter > 0) {
            x_da2cde4c();
        }
    }
}

void x_60affc72(void) {
    x_e30d50d2 = 0;
    x_66c4e9c7 = TRUE;
    x_aec099eb = x_b5cc849a = 1800;

    x_4495b42c(x_4f944650, 0x1000);
    while (!(x_e30d50d2 & x_bee364e0)) {
        x_da2cde4c();
    }
    x_66c4e9c7 = FALSE;

    while (x_59ce598c[x_83106b21].buttons == (x_9cefe76c | x_1c9950cc) ||
           x_59ce598c[x_6f0b3be3].buttons == (x_9cefe76c | x_1c9950cc)) {
        x_da2cde4c();
    }

    x_e38a6e19 = x_901b251f;

    while (x_59ce598c[x_83106b21].buttons == (x_9cefe76c | x_1c9950cc) ||
           x_59ce598c[x_6f0b3be3].buttons == (x_9cefe76c | x_1c9950cc)) {
        x_da2cde4c();
    }

    x_d4af6341();
    x_08779f06(FALSE);
}

void x_82df7d23(void) {
    D_8005BFCE = D_8005BEF8 = D_8005BEF0 = D_8005BEE8 = D_8005BEE0 = 0;

    while (!(x_e30d50d2 & x_bee364e0) || !(x_e30d50d2 & x_e3ff543d)) {
        if (!(x_e30d50d2 & x_dd99cbfb) && !(x_e30d50d2 & x_86c5bc33) &&
            x_59ce598c[x_83106b21].buttons == x_9cefe76c && x_59ce598c[x_83106b21].enabled &&
            x_59ce598c[x_83106b21].x_c4397934) {
            x_14a106cd(x_83106b21);
        } else if (!(x_e30d50d2 & x_dd99cbfb) && !(x_e30d50d2 & x_86c5bc33) &&
                   x_59ce598c[x_6f0b3be3].buttons == x_9cefe76c && x_59ce598c[x_6f0b3be3].enabled &&
                   x_59ce598c[x_6f0b3be3].x_c4397934) {
            x_14a106cd(x_6f0b3be3);
        }

        if (x_e30d50d2 & x_dd99cbfb) {
            x_66c4e9c7 = 1 - x_66c4e9c7;
        }
        x_da2cde4c();
    }

    x_e30d50d2 &= ~(x_dd99cbfb | x_bee364e0);
    x_e30d50d2 |= x_520a704c;

    if (!(x_e30d50d2 & x_d4c59644)) {
        if (!(x_e30d50d2 & x_b9be821f)) {
            x_66c4e9c7 = TRUE;
        }
        x_4495b42c(x_4f944650, 0x1000);
        while (!(x_e30d50d2 & x_bee364e0)) {
            x_da2cde4c();
        }
        x_66c4e9c7 = FALSE;
    }

    x_e30d50d2 &= ~x_520a704c;

    x_225c77c4();
    x_225c77c4();

    x_d4af6341();
    x_08779f06(FALSE);

    x_d4af6341();
    x_08779f06(FALSE);
}

#ifdef x_26a627fb
void x_b7eeb04a(s32 x_cc1d0de5, Vtx *x_84ff873b) {
    if (x_84ff873b == NULL) {
        x_84ff873b = &D_800492B0[D_8005BFCE];
    }

    D_8005BF00.header.x_09cf7a45 = 0;
    D_8005BF00.header.x_1256da71 = 0;
    D_8005BF00.header.x_4c5e05f8 = 4;
    D_8005BF00.header.x_ed66866b = 0;
    D_8005BF00.header.x_8a54e96a = 2;
    D_8005BF00.header.x_70b508ea = 2;
    D_8005BF00.header.x_b7ba6d35 = D_8005BF58;

    gDPPipeSync(&D_8005BF58[0]);
    gDPSetCombineMode(&D_8005BF58[1], G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_RENDERMODE, G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    x_84ff873b[0].v.cn[3] = x_cc1d0de5;
    x_84ff873b[0].v.cn[0] = x_84ff873b[0].v.cn[1] = x_84ff873b[0].v.cn[2] = D_80080116;
    x_84ff873b[1].v.cn[3] = x_cc1d0de5;
    x_84ff873b[1].v.cn[0] = x_84ff873b[1].v.cn[1] = x_84ff873b[1].v.cn[2] = D_80080116;
    x_84ff873b[2].v.cn[3] = x_cc1d0de5;
    x_84ff873b[2].v.cn[0] = x_84ff873b[2].v.cn[1] = x_84ff873b[2].v.cn[2] = D_80080116;
    x_84ff873b[3].v.cn[3] = x_cc1d0de5;
    x_84ff873b[3].v.cn[0] = x_84ff873b[3].v.cn[1] = x_84ff873b[3].v.cn[2] = D_80080116;

    x_50746900(x_ee137e39, NULL, &D_8005BF00, x_84ff873b, D_80049330);
}
#else
#pragma x_eda6f9e3("asm/nonmatchings/main/draw_solid_quad.s")
void x_b7eeb04a(s32 x_cc1d0de5, Vtx *x_84ff873b);
#endif

#ifdef x_26a627fb
void x_e1511bdd(s32 x_cc1d0de5, Vtx *vertices) {
    Gfx *gfx = D_8005BF58;

    if (vertices == NULL) {
        vertices = D_800492B0[D_8005BFCE];
    }

    D_8005BF00.header.x_09cf7a45 = 0;
    D_8005BF00.header.x_1256da71 = 0;
    D_8005BF00.header.x_4c5e05f8 = 4;
    D_8005BF00.header.x_ed66866b = 0;
    D_8005BF00.header.x_8a54e96a = 2;
    D_8005BF00.header.x_70b508ea = 2;
    D_8005BF00.header.x_b7ba6d35 = D_8005BF58;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&D_8005BF00.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    vertices[0].v.cn[3] = x_cc1d0de5;
    vertices[0].v.cn[0] = vertices[0].v.cn[1] = vertices[0].v.cn[2] = D_80080116;
    vertices[1].v.cn[3] = x_cc1d0de5;
    vertices[1].v.cn[0] = vertices[1].v.cn[1] = vertices[1].v.cn[2] = D_80080116;
    vertices[2].v.cn[3] = x_cc1d0de5;
    vertices[2].v.cn[0] = vertices[2].v.cn[1] = vertices[2].v.cn[2] = D_80080116;
    vertices[3].v.cn[3] = x_cc1d0de5;
    vertices[3].v.cn[0] = vertices[3].v.cn[1] = vertices[3].v.cn[2] = D_80080116;

    x_50746900(x_ee137e39, NULL, &D_8005BF00, vertices, D_80049330);
}
#else
#pragma x_eda6f9e3("asm/nonmatchings/main/draw_translucent_quad.s")
void x_e1511bdd(s32 x_cc1d0de5, Vtx *x_84ff873b);
#endif

void x_ce9e82b1(Object *obj) {
    if (D_8005BEFC - 8 < D_80080118) {
        D_8008012C &= ~x_c626209d;
        obj->flags |= x_f51cb721;
        x_e30d50d2 |= x_80ca0761;

        if (obj->x_0f4167b4[4] == 0) {
            x_e30d50d2 &= ~x_86c5bc33;
        }
        x_e30d50d2 |= x_e3ff543d;
    } else {
        D_8005BEFC -= 8;
        x_e1511bdd(D_8005BEFC, NULL);
    }
}

void x_5e57d033(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] >= 7) {
        osViBlack(0);
        D_8005BEFC = 255;
        obj->x_0232396f = x_ce9e82b1;
    }

    x_e1511bdd(255, NULL);
}

void x_6b09ed5a(Object *obj) {
    x_292e1d02(obj, 0);
    if (x_e30d50d2 & x_23ebd6b0) {
        x_e30d50d2 |= x_e3ff543d;
        return;
    }

    D_8008012C |= x_c626209d;
    osViBlack(TRUE);
    x_e30d50d2 &= ~x_e3ff543d;
    x_292e1d02(obj, 0);
    if (x_e30d50d2 & x_86c5bc33) {
        obj->x_0f4167b4[4] = 1;
    }
    x_e30d50d2 |= x_86c5bc33;
    if (obj->flags & x_f51cb721) {
        obj->flags &= ~x_f51cb721;
        obj->x_0232396f = x_5e57d033;
    }
    x_e1511bdd(255, NULL);
}

void x_f73a506e(Object *obj) {
    x_b7eeb04a(D_8005BEFC, NULL);
    obj->x_0f4167b4[0]++;

    if (obj->x_0f4167b4[0] >= 5) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
    }
}

void x_8cc3627e(Object *obj) {
    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
        x_e1511bdd(D_8005BEFC, NULL);
        return;
    }

    if (D_8005BEFC + 1 < 255) {
        D_8005BEFC++;
        x_e1511bdd(D_8005BEFC, NULL);
        return;
    }

    obj->x_0232396f = x_f73a506e;
    if (!(x_e30d50d2 & x_3b812e44)) {
        osViBlack(1);
    }

    x_b7eeb04a(D_8005BEFC, NULL);
    obj->x_0f4167b4[0] = 0;
}

void x_6e9e48e4(Object *obj) {
    D_8008012C |= x_c626209d;
    x_f1ca6ba2(obj, 0);

    if (obj->x_0232396f != x_6e9e48e4) {
        obj->x_0232396f = x_8cc3627e;
    }

    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
        x_e1511bdd(D_8005BEFC, NULL);
        return;
    }

    if (D_8005BEFC + 1 < 255) {
        D_8005BEFC++;
        x_e1511bdd(D_8005BEFC, NULL);
        return;
    }

    obj->x_0232396f = x_f73a506e;
    if (!(x_e30d50d2 & x_3b812e44)) {
        osViBlack(1);
    }

    x_b7eeb04a(D_8005BEFC, NULL);
    obj->x_0f4167b4[0] = 0;
}

void x_4f944650(Object *obj) {
    if (!(x_e30d50d2 & x_ecbcd14e)) {
        D_8005BEFC = 0;
    }

    x_e30d50d2 &= ~x_ecbcd14e;
    obj->x_0232396f = x_6e9e48e4;
    x_e1511bdd(D_8005BEFC, NULL);
}

void x_14ae77a0(void) {
    x_e38a6e19 = x_c4da946c;
    x_16b2a52b(x_e38a6e19);
    x_2d5f067a();

    while (TRUE) {
        x_f71086e0 = x_e38a6e19;
        x_4495b42c(x_6b09ed5a, 0x1100);
        x_4540c33c[x_e38a6e19].x_bdfdc522();
        if (!(x_e30d50d2 & x_3b812e44)) {
            osViBlack(1);
        }
        x_d4af6341();
        x_08779f06(FALSE);
        x_4090e698 = x_f71086e0;
        x_a892f516(x_e38a6e19);
    }
}