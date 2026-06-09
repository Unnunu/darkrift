#include "common.h"
#include "PR/gt.h"
#include "task.h"

extern x_88f11482 D_8004A5D0[];
extern x_88f11482 D_8004A680[];

extern s32 D_80081434;
extern s32 D_80081438;

void x_eff6c1a4(Object *obj);

x_8b39d614 D_80051F50 = { "dusthit.sp3", x_eff6c1a4, 0, 0x1100, 0, 0x2800, 0 };
s16 D_80051F68 = 0;
s16 D_80051F6C = 0;
s16 D_80051F70 = 0;
Vtx D_80051F78[2][4] = { { { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } },
                         { { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } } };
Vtx D_80051FF8[2][4] = { { { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } },
                         { { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } } };
x_88f11482 D_80052078 = { 63, 220, 0, 0 };
x_88f11482 D_80052088 = { 72, 220, 0, 0 };
x_88f11482 D_80052098 = { 81, 220, 0, 0 };
x_88f11482 D_800520A8 = { 268, 220, 0, 0 };
x_88f11482 D_800520B8 = { 277, 220, 0, 0 };
x_88f11482 D_800520C8 = { 286, 220, 0, 0 };
x_88f11482 *D_800520D8[] = { &D_80052078, &D_80052088, &D_80052098, &D_800520A8, &D_800520B8, &D_800520C8 };

s16 D_8013C230;
s16 D_8013C232;
x_425d6ed3 *D_8013C234;
x_425d6ed3 *D_8013C238;
Object *D_8013C23C;
Object *D_8013C240;
Object *D_8013C244;
Object *D_8013C248;
u16 D_8013C24C;
u16 D_8013C24E;
u16 x_33abac12;
s32 x_ab22f1f9;
Object *D_8013C258[2][10];
s16 D_8013C2A8;
s16 D_8013C2AA;

void x_9564f634(Object *obj);
void x_4740163c(Object *obj);
void x_f058b0f7(Object *obj);
void x_af61e89b(void);

void x_bf666432(Object *obj) {
    obj->flags &= ~x_c537cafa;
    if (obj->x_5fcb1654 <= 12) {
        obj->x_5fcb1654++;
        if (obj->color.a > 100) {
            obj->color.a -= 8;
        } else if (obj->color.a > 3) {
            obj->color.a -= 3;
        }
        obj->x_64946db0->x_c7f843c2 = 2;
    } else {
        obj->flags |= x_c537cafa | x_f51cb721;
        x_5e6f40dd(obj->x_64946db0);
    }
}

void x_27a93dac(Object *obj) {
    if (--obj->x_0f4167b4[1] <= 0) {
        obj->flags &= ~x_c537cafa;
        if (obj->x_5fcb1654 <= 8) {
            obj->x_5fcb1654++;
            if (obj->color.a > 100) {
                obj->color.a -= 8;
            } else if (obj->color.a > 4) {
                obj->color.a -= 2;
            }
            obj->x_64946db0->x_c7f843c2 = 2;
        } else {
            obj->flags |= x_c537cafa | x_f51cb721;
            x_5e6f40dd(obj->x_64946db0);
        }
    }
}

void x_342a32f9(Object *obj, x_6fc0b62f *x_84ff873b, x_88f11482 *x_b35af211) {
    x_88f11482 pos;

    pos.x = x_84ff873b->x_1422e8f9;
    pos.y = x_84ff873b->x_6f7546e4;
    pos.z = x_84ff873b->x_95b3e972;

    x_e5c4361f(&D_800813E0);
    x_fc6adb04(&D_800813E0, &pos);
    x_20ce5003(&D_800813E0, &obj->x_20d20338->transforms[x_84ff873b->x_32485e13].x_0c1a9bdd);

    x_b35af211->x = D_800813E0.w.x;
    x_b35af211->y = D_800813E0.w.y;
    x_b35af211->z = D_800813E0.w.z;
}

void x_47cbb2c0(s16 x_cc1d0de5, x_88f11482 *x_84ff873b, x_88f11482 *x_2092f891) {
    s32 x_32f1d6e2;
    s32 x_5aee6615;
    s32 x_5bbba600;
    s32 x_dd7ffac5;
    s32 x_4346f5cb;

    x_5aee6615 = x_84ff873b->x;
    x_5bbba600 = x_84ff873b->z;
    x_32f1d6e2 = (u32) (sqrtf(x_84ce1cfb(x_5aee6615) + x_84ce1cfb(x_5bbba600)) + 0.5);
    x_dd7ffac5 = x_cc1d0de5 + x_32f1d6e2;
    x_4346f5cb = x_47d273d8(x_5bbba600, x_5aee6615);

    x_2092f891->x = (x_d9b20313(x_4346f5cb) * x_dd7ffac5) >> 12;
    x_2092f891->z = (-x_d9b20313(x_4346f5cb + 0x400) * x_dd7ffac5) >> 12;
    x_2092f891->y = x_84ff873b->y;
}

void x_73651cea(Object *obj) {
    Object *v0;
    Object *v1;

    if (--obj->x_f9866d50 <= 0) {
        obj->x_f9866d50 = obj->x_0f4167b4[2];
        v1 = obj->x_e2f64c57[3];
        v0 = x_1d5cf6e2(&v1->pos, &D_80051F50, x_2587f84f);
        if (v0 == NULL) {
            return;
        } else {
            v0->x_64946db0->x_f6382727 = x_bf666432;
            v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
            if (--obj->x_0f4167b4[1] < 0) {
                obj->flags |= x_f51cb721;
            }
        }
    }
}

void x_709712b3(Object *obj) {
    Object *v0;
    Player *player = (Player *) obj->x_e2f64c57[0];

    v0 = x_4495b42c(x_73651cea, 0x1000);
    if (v0 == NULL) {
        return;
    }

    v0->x_e2f64c57[0] = player;
    v0->x_0f4167b4[1] = 4;
    v0->x_0f4167b4[2] = 3;
    v0->x_e2f64c57[3] = obj;
    v0->color.a = 100;
    v0->x_f9866d50 = 0;
}

void x_ad14714d(Object *obj) {
    s16 x_30bbe547 = obj->x_0f4167b4[0];
    Object *v0 = x_824b9544[x_30bbe547].obj;
    x_88f11482 x_dd7ffac5;

    if (v0->pos.y != 0) {
        return;
    }
    x_dd7ffac5.x = v0->x_20d20338->x_abd7b3c4.x_0c1a9bdd.w.x;
    x_dd7ffac5.y = v0->x_20d20338->x_abd7b3c4.x_0c1a9bdd.w.y;
    x_dd7ffac5.z = v0->x_20d20338->x_abd7b3c4.x_0c1a9bdd.w.z;

    if (obj) {} // @fake

    if (obj->x_0f4167b4[2] != 0) {
        x_47cbb2c0(obj->x_0f4167b4[2], &x_dd7ffac5, &obj->pos);
    } else {
        obj->pos.x = x_dd7ffac5.x;
        obj->pos.z = x_dd7ffac5.z;
    }

    obj->pos.y = 0;
    obj->x_64946db0->x_f6382727 = x_27a93dac;
}

void x_eff6c1a4(Object *obj) {
    obj->x_64946db0->x_f6382727 = x_ad14714d;
}

void x_ebe27fa0(Object *obj) {
    Object *v0;
    s16 s0 = ((Player *) obj->x_e2f64c57[0])->x_30bbe547;

    v0 = x_1d5cf6e2(&x_c787d34b, &D_80051F50, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->x_64946db0->x_c7f843c2 = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 0;
        v0->x_0f4167b4[2] = 150;
        v0->color.a = 60;
        v0->flags |= x_c537cafa;
    }

    v0 = x_1d5cf6e2(&x_c787d34b, &D_80051F50, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->x_64946db0->x_c7f843c2 = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 3;
        v0->x_0f4167b4[2] = 50;
        v0->color.a = 60;
        v0->flags |= x_c537cafa;
    }

    v0 = x_1d5cf6e2(&x_c787d34b, &D_80051F50, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->x_64946db0->x_c7f843c2 = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 5;
        v0->x_0f4167b4[2] = -200;
        v0->color.a = 40;
        v0->flags |= x_c537cafa;
    }

    v0 = x_1d5cf6e2(&x_c787d34b, &D_80051F50, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->x_64946db0->x_c7f843c2 = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 7;
        v0->x_0f4167b4[2] = 100;
        v0->color.a = 40;
        v0->flags |= x_c537cafa;
    }

    v0 = x_1d5cf6e2(&x_c787d34b, &D_80051F50, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_64946db0->x_c7f843c2 = 10;
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 9;
        v0->x_0f4167b4[2] = -250;
        v0->color.a = 30;
        v0->flags |= x_c537cafa;
    }
}

void x_7621a350(Object *obj) {
    u32 i;
    Object *v0;
    s16 s4 = ((Player *) obj->x_e2f64c57[0])->x_30bbe547;
    s32 a, b;

    a = 0;
    b = -250;
    for (i = 0; i < 13; i++) {
        v0 = x_1d5cf6e2(&x_c787d34b, &D_80051F50, x_2587f84f);
        if (v0 == NULL) {
            return;
        }

        v0->x_0f4167b4[1] = a;
        v0->x_0f4167b4[2] = b;
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s4;
        v0->color.a = 40;
        v0->flags |= x_c537cafa;

        b += 50;
        a += 3;
    }
}

void x_fc7d8f37(Object *obj) {
    x_59ce598c[x_83106b21].enabled = FALSE;
    x_59ce598c[x_6f0b3be3].enabled = FALSE;

    if (obj->x_0f4167b4[0] == 0) {
        if (x_824b9544[x_83106b21].x_a4b33e43 == 0 && x_824b9544[x_6f0b3be3].x_a4b33e43 == 0) {
            x_af61e89b();
            obj->x_0f4167b4[0] = 240;
        }
    } else {
        obj->x_0f4167b4[0]--;
        if (obj->x_0f4167b4[0] == 0) {
            x_e30d50d2 |= x_bee364e0;
            x_5e6f40dd(obj->x_64946db0);
        }
    }
}

s16 x_c0a56b97(s16 x_30bbe547) {
    return (u32) (x_824b9544[x_30bbe547].obj->x_9200c538 * 80 * 0x10000) / 400 / 0x10000;
}

void x_e7887022(Vtx *vtx) {
    Gfx *gfx = D_8005BF58;

    if (D_8008012C & x_f846a903) {
        return;
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

    x_50746900(x_ee137e39, NULL, &D_8005BF00, vtx, D_80049330);
}

void x_fb66828a(Object *obj) {
    s32 unused;
    s16 x_6913166b;
    s16 a2;
    s16 x_f6289181;
    s16 x_4346f5cb;

    x_6913166b = D_8005BFCE;

    if (x_9df63a90) {
        D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
    }

    if (D_8013C2A8 != 0) {
        x_e7887022(D_80051F78[x_6913166b]);
        D_8013C2A8--;
    } else if (D_80051F6C > 0) {
        D_80051F6C--;
        D_80051F78[x_6913166b][0].v.ob[0] = D_80051F78[x_6913166b][2].v.ob[0] = D_80051F78[x_6913166b][1].v.ob[0] - 4 * D_80051F6C;
        x_e7887022(D_80051F78[x_6913166b]);
    }

    x_4346f5cb = x_c0a56b97(x_83106b21);
    if (x_4346f5cb != D_8013C230) {
        a2 = D_8013C230 - x_4346f5cb;
        D_8013C2A8 = 30 - D_8013C2A8 - D_80051F6C;
        if (D_8013C2A8 < 0) {
            D_8013C2A8 = 0;
        }

        D_80051F6C += a2;
        D_8013C234->x_b88b3756 += a2;
        D_8013C234->x_e7f1952a += a2;
        if (D_8013C234->x_b88b3756 >= D_8013C234->rightS) {
            D_8013C234->x_b88b3756 = D_8013C234->rightS;
        }

        D_80051F78[0][1].v.ob[0] = D_80051F78[1][1].v.ob[0] = D_80051F78[0][3].v.ob[0] = D_80051F78[1][3].v.ob[0] =
            (35 + D_8013C234->x_b88b3756) << 2;
        D_80051F78[0][0].v.ob[0] = D_80051F78[1][0].v.ob[0] = D_80051F78[0][2].v.ob[0] = D_80051F78[1][2].v.ob[0] =
            D_80051F78[0][1].v.ob[0] - 4 * D_80051F6C;

        x_e7887022(D_80051F78[x_6913166b]);
        D_8013C230 = x_4346f5cb;
    }

    if (D_8013C2AA != 0) {
        x_e7887022(D_80051FF8[x_6913166b]);
        D_8013C2AA--;
    } else if (D_80051F70 > 0) {
        D_80051F70--;
        D_80051FF8[x_6913166b][1].v.ob[0] = D_80051FF8[x_6913166b][3].v.ob[0] = D_80051FF8[x_6913166b][0].v.ob[0] + 4 * D_80051F70;
        x_e7887022(D_80051FF8[x_6913166b]);
    }

    x_f6289181 = x_c0a56b97(x_6f0b3be3);
    if (x_f6289181 != D_8013C232) {
        a2 = D_8013C232 - x_f6289181;
        // clang-format off
        D_8013C2AA = 30 - D_8013C2AA - D_80051F70;\
        if (D_8013C2AA < 0) {
            D_8013C2AA = 0;
        }
        // clang-format on

        D_80051F70 += a2;
        D_8013C238->rightS -= a2;
        if (D_8013C238->x_b88b3756 >= D_8013C238->rightS) {
            D_8013C238->x_b88b3756 = D_8013C238->rightS;
        }

        D_80051FF8[0][0].v.ob[0] = D_80051FF8[1][0].v.ob[0] = D_80051FF8[0][2].v.ob[0] = D_80051FF8[1][2].v.ob[0] =
            (217 + D_8013C238->rightS) << 2;
        D_80051FF8[0][1].v.ob[0] = D_80051FF8[1][1].v.ob[0] = D_80051FF8[0][3].v.ob[0] = D_80051FF8[1][3].v.ob[0] =
            D_80051FF8[0][0].v.ob[0] + 4 * D_80051F70;

        x_e7887022(D_80051FF8[x_6913166b]);
        D_8013C232 = x_f6289181;
    }
}

void x_af61e89b(void) {
    s16 v0, v1;

    v0 = x_824b9544[x_83106b21].obj->x_9200c538;
    v1 = x_824b9544[x_6f0b3be3].obj->x_9200c538;
    if (v0 > v1) {
        x_e914de48(&x_824b9544[x_83106b21], x_fefa7415, 1);
        x_e914de48(&x_824b9544[x_6f0b3be3], x_f6ac8484, 1);
    } else if (v0 < v1) {
        x_e914de48(&x_824b9544[x_83106b21], x_f6ac8484, 1);
        x_e914de48(&x_824b9544[x_6f0b3be3], x_fefa7415, 1);
    } else {
        x_e914de48(&x_824b9544[x_83106b21], x_f6ac8484, 1);
        x_e914de48(&x_824b9544[x_6f0b3be3], x_f6ac8484, 1);
    }
}

void x_34018036(Object *obj) {
    Object *v1;

    if (x_9df63a90) {
        x_5e6f40dd(obj->x_64946db0);
    }

    obj->x_64946db0->x_c7f843c2 = 60;

    v1 = obj->x_e2f64c57[0];
    if (--v1->x_5fcb1654 < 0) {
        v1->x_5fcb1654 = 9;
        if (--obj->x_5fcb1654 < 0) {
            obj->x_5fcb1654 = 0;
            x_9df63a90 = TRUE;
            v1->x_5fcb1654 = 0;
            x_5e6f40dd(obj->x_64946db0);
        }
    }
}

void x_fd44eb65(void) {
    if (x_5e4e2788 != x_79c2dc5b && x_c8356c60 != 0) {
        D_8013C240->x_64946db0->x_f6382727 = x_34018036;
        D_8013C240->x_64946db0->x_c7f843c2 = 0;
        D_8013C240->x_64946db0->flags = x_0fb55613;
        D_8013C23C->x_64946db0->x_c7f843c2 = 120;
    }
}

void x_d265c713(void) {
    s16 i = 0;
    Object *a0;

    if (D_8013C248 != NULL) {
        D_8013C248->flags |= x_f51cb721;
        D_8013C248->flags &= ~x_5a44854c;
        D_80081438++;
        D_80081434++;

        while (D_8013C248->x_e2f64c57[i] != NULL) {
            D_80081438++;
            D_80081434++;
            D_8013C248->x_e2f64c57[i]->flags |= x_f51cb721;
            D_8013C248->x_e2f64c57[i]->flags &= ~x_5a44854c;
            i++;
        }

        D_8013C248 = NULL;
    }
}

void x_ea2a7987(void) {
    x_f0d7e70f x_8a9089b3 = { 28, NULL, x_5a44854c, 0x1001, "bars.sp2" };
    x_f0d7e70f x_331089fa = { 27, NULL, x_5a44854c, 0x1001, "bars.sp2" };
    x_88f11482 x_2a89e429 = { 32, 220, 0, 0 };
    x_88f11482 x_081c4eef = { 236, 220, 0, 0 };
    s16 s0;
    s16 s3;
    s16 s2;
    Object *v0;

    D_8013C248 = NULL;
    s0 = x_77831b2c[x_83106b21].x_7d8e7a6f;
    if (s0 != 0) {
        D_8013C248 = x_12014163(&x_2a89e429, &x_331089fa, x_2587f84f);
        D_80081438--;
        D_80081434--;
        s3 = 0;
        s2 = 0;

        if (s0 >= 1000) {
            s0 = 1;
            x_77831b2c[x_83106b21].x_7d8e7a6f = 1;
        }

        if (s0 >= 100) {
            v0 = x_12014163(D_800520D8[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->x_5fcb1654 = 28 + (s0 / 100);
            D_8013C248->x_e2f64c57[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 100;
            task_free_list(v0->x_d178c88f);
            v0->x_d178c88f = NULL;
        }

        if (x_77831b2c[x_83106b21].x_7d8e7a6f >= 10) {
            v0 = x_12014163(D_800520D8[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->x_5fcb1654 = 28 + (s0 / 10);
            D_8013C248->x_e2f64c57[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 10;
            task_free_list(v0->x_d178c88f);
            v0->x_d178c88f = NULL;
        }

        v0 = x_12014163(D_800520D8[s3], &x_8a9089b3, x_2587f84f);
        D_80081438--;
        v0->x_5fcb1654 = 28 + s0;
        D_8013C248->x_e2f64c57[s2] = v0;
        s2++;
        D_8013C248->x_e2f64c57[s2] = NULL;
        task_free_list(v0->x_d178c88f);
        v0->x_d178c88f = NULL;

        task_free_list(D_8013C248->x_d178c88f);
        D_8013C248->x_d178c88f = NULL;
    }

    s0 = x_77831b2c[x_6f0b3be3].x_7d8e7a6f;
    if (s0 != 0) {
        D_8013C248 = x_12014163(&x_081c4eef, &x_331089fa, x_2587f84f);
        D_80081438--;
        s3 = 3;
        s2 = 0;

        if (s0 >= 1000) {
            s0 = 1;
            x_77831b2c[x_6f0b3be3].x_7d8e7a6f = 1;
        }

        if (s0 >= 100) {
            v0 = x_12014163(D_800520D8[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->x_5fcb1654 = 28 + (s0 / 100);
            D_8013C248->x_e2f64c57[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 100;
            task_free_list(v0->x_d178c88f);
            v0->x_d178c88f = NULL;
        }

        if (x_77831b2c[x_6f0b3be3].x_7d8e7a6f >= 10) {
            v0 = x_12014163(D_800520D8[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->x_5fcb1654 = 28 + (s0 / 10);
            D_8013C248->x_e2f64c57[s2] = v0;
            s2++;

            s0 = s0 % 10;
            s3++;
            task_free_list(v0->x_d178c88f);
            v0->x_d178c88f = NULL;
        }

        v0 = x_12014163(D_800520D8[s3], &x_8a9089b3, x_2587f84f);
        D_80081438--;
        v0->x_5fcb1654 = 28 + s0;
        D_8013C248->x_e2f64c57[s2] = v0;
        s2++;
        D_8013C248->x_e2f64c57[s2] = NULL;
        task_free_list(v0->x_d178c88f);
        v0->x_d178c88f = NULL;

        task_free_list(D_8013C248->x_d178c88f);
        D_8013C248->x_d178c88f = NULL;
    }
}

void x_41d6ae47(void) {
    Object *v0;
    Object *x_65cbb149;
    s16 s0;
    s16 s1;
    x_f0d7e70f x_4fc490a9 = { 10, NULL, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_24cd786b = { 10, NULL, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_fd599243 = { 0, NULL, 0, 0x1001, "bars.sp2" };
    x_f0d7e70f x_cadba9e3 = { 0, NULL, 0, 0x1001, "bars.sp2" };
    s32 pad[2];
    x_88f11482 x_6b913371 = { 167, 49, 0, 0 };
    x_88f11482 x_4a496b1d = { 160, 75, 0, 0 };
    x_88f11482 x_30a44af1 = { 173, 75, 0, 0 };
    x_88f11482 x_a438747c = { 75, 39, 0, 0 };
    x_88f11482 x_5b215acc = { 257, 39, 0, 0 };
    x_88f11482 x_5c787447 = { 146, 64, 0, 0 };
    x_88f11482 x_af0e6490 = { 187, 64, 0, 0 };
    x_88f11482 x_840385a0 = { 74, 39, 0, 0 };
    x_88f11482 x_54406eae = { 257, 39, 0, 0 };

    if (x_5e4e2788 == x_79c2dc5b) {
        return;
    }

    x_12014163(&x_6b913371, &x_24cd786b, x_2587f84f);

    switch (x_c8356c60) {
        case 0:
            break;
        case 1:
        case 2:
            x_65cbb149 = x_12014163(&x_30a44af1, &x_fd599243, x_2587f84f);
            v0 = x_12014163(&x_4a496b1d, &x_cadba9e3, x_2587f84f);
            v0->x_5fcb1654 = x_c8356c60 * 3 + 3;
            v0->x_e2f64c57[0] = x_65cbb149;
            D_8013C240 = v0;
            break;
    }

    v0 = x_12014163(&x_a438747c, &x_4fc490a9, x_2587f84f);
    v0->x_5fcb1654 = 11;
    task_free_list(v0->x_d178c88f);
    v0->x_d178c88f = NULL;

    v0 = x_12014163(&x_5b215acc, &x_4fc490a9, x_2587f84f);
    v0->x_5fcb1654 = 11;
    task_free_list(v0->x_d178c88f);
    v0->x_d178c88f = NULL;

    s0 = 0;
    for (s1 = 0; s1 < x_77831b2c[x_83106b21].x_b2b764b3; s1++) {
        D_8013C258[x_83106b21][s1] = v0 = x_12014163(&x_5c787447, &x_4fc490a9, x_2587f84f);
        v0->x_5fcb1654 = 13;
        x_5c787447.x -= 8;
        s0++;
        task_free_list(v0->x_d178c88f);
        v0->x_d178c88f = NULL;
    }

    for (; s0 < x_adcfd05c; s0++) {
        D_8013C258[x_83106b21][s0] = v0 = x_12014163(&x_5c787447, &x_4fc490a9, x_2587f84f);
        v0->x_5fcb1654 = 12;
        x_5c787447.x -= 8;
        task_free_list(v0->x_d178c88f);
        v0->x_d178c88f = NULL;
    }

    s0 = 0;
    for (s1 = 0; s1 < x_77831b2c[x_6f0b3be3].x_b2b764b3; s1++) {
        D_8013C258[x_6f0b3be3][s1] = v0 = x_12014163(&x_af0e6490, &x_4fc490a9, x_2587f84f);
        v0->x_5fcb1654 = 13;
        x_af0e6490.x += 8;
        s0++;
        task_free_list(v0->x_d178c88f);
        v0->x_d178c88f = NULL;
    }

    for (; s0 < x_adcfd05c; s0++) {
        D_8013C258[x_6f0b3be3][s0] = v0 = x_12014163(&x_af0e6490, &x_4fc490a9, x_2587f84f);
        v0->x_5fcb1654 = 12;
        x_af0e6490.x += 8;
        task_free_list(v0->x_d178c88f);
        v0->x_d178c88f = NULL;
    }

    v0 = x_12014163(&x_840385a0, &x_4fc490a9, x_2587f84f);
    v0->x_5fcb1654 = 15;
    D_8013C234 = v0->x_904eaf67->x_a34b89cc[15].parts;
    D_8013C234->x_e7f1952a = D_8013C234->x_e7f1952a - D_8013C234->x_b88b3756 + D_8013C234->rightS - 88;
    D_8013C234->x_b88b3756 = D_8013C234->rightS - 88;

    v0 = x_12014163(&x_54406eae, &x_4fc490a9, x_2587f84f);
    v0->x_5fcb1654 = 14;
    D_8013C238 = v0->x_904eaf67->x_a34b89cc[14].parts;
    D_8013C238->rightS = D_8013C238->x_b88b3756 + 80;

    v0 = x_12014163(&D_8004A5D0[x_77831b2c[x_83106b21].x_eb1fe45b], &x_4fc490a9, x_2587f84f);
    if (x_77831b2c[x_83106b21].x_eb1fe45b < x_e235676f) {
        v0->x_5fcb1654 = 16 + x_77831b2c[x_83106b21].x_eb1fe45b;
    } else {
        v0->x_5fcb1654 = 16 + x_77831b2c[x_83106b21].x_eb1fe45b - 1;
    }
    task_free_list(v0->x_d178c88f);
    v0->x_d178c88f = NULL;

    v0 = x_12014163(&D_8004A680[x_77831b2c[x_6f0b3be3].x_eb1fe45b], &x_4fc490a9, x_2587f84f);
    if (x_77831b2c[x_6f0b3be3].x_eb1fe45b < x_e235676f) {
        v0->x_5fcb1654 = 16 + x_77831b2c[x_6f0b3be3].x_eb1fe45b;
    } else {
        v0->x_5fcb1654 = 16 + x_77831b2c[x_6f0b3be3].x_eb1fe45b - 1;
    }
    task_free_list(v0->x_d178c88f);
    v0->x_d178c88f = NULL;

    D_8013C232 = D_8013C230 = 80;
    D_8013C244 = x_4495b42c(x_fb66828a, 0x1000);
    x_ea2a7987();
}

// TODO split files, so D_80052220 (52E20) is in another file

void x_1f0fbecd(Object *obj) {
    if (--obj->x_5fcb1654 < 2) {
        x_e30d50d2 |= x_700de048;
        obj->flags |= x_f51cb721;
    }

    D_8005BEFC -= 2;
    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_7a336326(Object *obj) {
    x_e1511bdd(D_8005BEFC, NULL);
    obj->flags |= x_f51cb721;
}

void x_58906f63(Object *obj) {
    if (++obj->x_5fcb1654 >= 130) {
        x_e30d50d2 |= x_700de048 | x_bee364e0;
        x_e38a6e19 = x_901b251f;
        x_e30d50d2 |= x_ecbcd14e;
        obj->flags &= ~x_e411fefb;
        obj->x_0232396f = x_7a336326;
    }

    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_7ab6c8e2(Object *obj) {
    if (--obj->x_5fcb1654 <= 60) {
        obj->x_0232396f = x_9564f634;
    }

    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_a1847541(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = x_58906f63;
    } else if (buttons & x_fc4a9735) {
        obj->x_5fcb1654 = 118;
        obj->x_0232396f = x_f058b0f7;
    }

    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_f058b0f7(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = x_7ab6c8e2;
    } else if (buttons & x_ad1aebe6) {
        obj->x_5fcb1654 = 120;
        obj->x_0232396f = x_a1847541;
    }

    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_22da107b(Object *obj) {
    if (obj->x_5fcb1654 >= 118) {
        obj->x_0232396f = x_f058b0f7;
    } else {
        obj->x_5fcb1654++;
    }

    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_9564f634(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = x_22da107b;
    } else if (buttons & x_f7763ed8) {
        obj->x_0232396f = x_4740163c;
        obj->x_5fcb1654 = 58;
    }

    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_4740163c(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = x_1f0fbecd;
    } else if (buttons & x_b8c91680) {
        obj->x_0232396f = x_9564f634;
        obj->x_5fcb1654 = 60;
    }

    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_d9c3c170(Object *obj) {
    if (obj->x_5fcb1654 >= 58) {
        obj->x_0232396f = x_4740163c;
    } else {
        obj->x_5fcb1654++;
    }
    D_8005BEFC += 2;
    x_e1511bdd(D_8005BEFC, NULL);
    x_0022bfc3(obj);
}

void x_751dec03(Object *obj) {
    obj->x_0232396f = x_d9c3c170;
    obj->flags &= ~x_c537cafa;
    obj->x_5fcb1654++;
    obj->x_64946db0->x_f6382727 = task_remove_current;
    x_66c4e9c7 = TRUE;
    obj->flags |= x_e411fefb;
    D_8005BEFC = 0;
}

void x_c85182b9(Object *obj) {
    if (obj->x_5fcb1654++ > 16) {
        obj->flags |= x_f51cb721;
    }
    obj->x_64946db0->x_c7f843c2 = 2;
}
