#include "common.h"
#include "camera.h"
#include "sprite_ids.h"
#include "task.h"

extern s16 D_80051F68;

extern s32 D_8008012C;
extern Object *x_fa7941af;
extern s16 D_80049B30[];

extern u8 x_a7d9a1e8;
extern s32 x_66ddef46;
extern s32 x_15814eea;
extern u8 D_80080129;
extern s16 D_80081250;
extern x_4a7d6dd4 *D_80081254;
extern s16 D_80080116;
extern s16 x_4090e698;
extern s16 x_2615d8ad;
extern s16 D_8013C226;
extern s8 D_80081430;
extern s32 D_800AA480;
extern s16 x_1acf99bf;

extern u32 x_6db66fc3;
extern u16 x_33abac12;

void x_d2b7f1c2(Object *);
void x_5638088b(Object *);
void x_d23046bd(Object *, s32);
Object *x_572f827d(x_88f11482 *, s32, void (*)(Object *), Model *);
void x_91e62f73(Object *);
void x_8daf2444(Object *);
void x_37361bf1(Object *);
void x_6eea7033(Object *, s16);
// s32 menu_rank_init(void);
void x_6ed74c52(s16 x_cc1d0de5);
void x_7a8b20f2(char *, s32);
void x_41d6ae47(void);
void x_a92790e6(Object *);
void task_remove_current(Object *);
void x_0073afdd(Object *);
void x_a9342b2f(Object *);
void x_d4ae14dc(Object *);
void x_2cae892b(Object *);
void x_a2a8ba2f(Object *);
void x_bc5bf713(Object *);
void x_0e243657(Object *);
void x_4d34121d(Object *);
void x_c1c0a10d(Object *);
void x_ff609efb(Object *);
void x_28ceb562(Object *);
void x_12081995(Object *);
void x_53598eda(Object *);
void x_b5c125fc(Object *);
void x_dd25b026(Object *);
void x_f9bb9d72(Object *);
void x_070b94ab(Object *);
void x_64109585(Object *);
void x_bc6a41ae(Object *);

s32 D_800493F0[] = { 0, -783, -2453, 0 };

/* .bss */
u8 x_9df63a90;
u8 D_800801F1;
s32 D_800801F4;
s32 D_800801F8;
s32 D_800801FC;
s32 D_80080200;
s32 D_80080204;
s32 D_80080208;
s32 x_09a33777;
s32 x_9a96200f;
s32 D_80080214;
s32 D_80080218;
s32 D_8008021C;
x_88f11482 *x_159f4e5a;
x_88f11482 *x_f8109afd;
Object *x_3ac11521[2];

void x_7bc4ef6e(void) {
    x_158622fa = x_b717ed65[x_e720f37d("comhit.k5", x_2587f84f)].x_4962fc73;
    x_14a060ce = x_b717ed65[x_e720f37d("comblock.k5", x_2587f84f)].x_4962fc73;

    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    if (x_5e4e2788 == x_79c2dc5b) {
        x_59ce598c[1 - x_08051143].enabled = FALSE;
    } else {
        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    }

    x_9df63a90 = FALSE;
    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
    x_33abac12 = 0;
}

void x_91192da2(void) {
    x_77831b2c[x_83106b21].x_b2b764b3 = x_77831b2c[x_6f0b3be3].x_b2b764b3 = 0;
    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;

    if (x_5e4e2788 == x_79c2dc5b) {
        x_59ce598c[1 - x_08051143].enabled = FALSE;
    } else {
        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    }

    x_9df63a90 = FALSE;
    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    D_800801F1 = FALSE;
    D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
}

void x_2d5f067a(void) {
    u8 i, j;

    D_800AA480 = 0;

    x_77831b2c[x_83106b21].x_eb1fe45b = x_537ef8a7;
    x_77831b2c[x_83106b21].x_fb21ca8c = TRUE;
    x_77831b2c[x_83106b21].x_03604d94 = FALSE;
    x_77831b2c[x_83106b21].x_b2b764b3 = 0;
    x_77831b2c[x_6f0b3be3].x_eb1fe45b = x_c4ddde6d;
    x_77831b2c[x_6f0b3be3].x_fb21ca8c = FALSE;
    x_77831b2c[x_6f0b3be3].x_03604d94 = FALSE;
    x_77831b2c[x_6f0b3be3].x_b2b764b3 = 0;
    x_77831b2c[x_83106b21].x_6128220f = FALSE;
    x_77831b2c[x_6f0b3be3].x_6128220f = FALSE;
    x_77831b2c[x_83106b21].x_c35c64af = 400;
    x_77831b2c[x_6f0b3be3].x_c35c64af = 400;
    x_77831b2c[x_83106b21].x_8a8d66c9 = x_77831b2c[x_6f0b3be3].x_8a8d66c9 = TRUE;
    x_77831b2c[x_83106b21].x_178eafa6 = x_77831b2c[x_6f0b3be3].x_178eafa6 = 0;

    x_1acf99bf = x_5e4e2788 = x_96f25e0a;
    D_800801F1 = TRUE;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            D_800B6350[i][j] = 0;
        }
    }

    for (j = 0; j < 11; j++) {
        D_800B6368[j].x_a962826d = D_800B6368[j].x_3f3ac621 = 0;
    }

    x_77831b2c[x_83106b21].x_cc57155e = 7;
    x_77831b2c[x_6f0b3be3].x_cc57155e = 7;
    x_08051143 = 0;
}

void x_d5d8f7a7(Object *obj) {
    if (--obj->x_0f4167b4[0] < 0) {
        obj->flags |= x_f51cb721;
        x_e30d50d2 |= x_bee364e0;
        x_5e6f40dd(obj->x_64946db0);
        osViBlack(0);
    }
}

void x_005cc66f(void) {
    Object *obj;
    x_4a7d6dd4 *x_c9614940;
    u16 x_18643961;
    u16 x_32f1d6e2;
    u16 x_1c32c793;

    x_18643961 = D_80080110;
    x_1c32c793 = D_80080114;
    x_32f1d6e2 = D_80080112;

    D_80080110 = D_80080112 = D_80080114 = 0;
    x_6c647b3a = 0;

    x_0928eec2("/title/wait", x_30af3448);
    x_c9614940 = x_a0e73601("wait", 0, 0, 0, 0, x_96186256, 0x6000);
    x_e30d50d2 |= x_23ebd6b0 | x_d4c59644;
    D_8008012C |= x_8df87377;

    obj = x_4495b42c(&x_d5d8f7a7, 0x1000);
    obj->x_0f4167b4[0] = 6;
    x_82df7d23();

    D_80080110 = x_18643961;
    D_80080112 = x_32f1d6e2;
    D_80080114 = x_1c32c793;
    x_e30d50d2 &= ~(x_23ebd6b0 | x_d4c59644 | x_bee364e0);
    D_8008012C &= ~x_8df87377;
    x_ad9889cf(0x6000);
    x_25025961(x_c9614940);
}

void x_10430200(void) {
    x_2615d8ad = x_e3a9f332 % 5;
    D_8013C226 = 0;
    D_80081430 = 0;
    x_77831b2c[x_83106b21].x_178eafa6 = x_77831b2c[x_6f0b3be3].x_178eafa6 = 0;

    if (x_4090e698 != x_802d9c2e) {
        x_005cc66f();
    }

    if (x_5e4e2788 != x_79c2dc5b) {
        x_0928eec2("/bars/bars", x_2587f84f);
    } else {
        x_0928eec2("/bars/bars2", x_2587f84f);
    }

    x_6ed74c52(0);
    x_6ed74c52(1);

    if (D_800801F1) {
        x_91192da2();
    } else {
        x_7bc4ef6e();
    }
    osViBlack(1);
}

void x_eb73d70f(void) {
    x_ad9889cf(x_2587f84f);
    x_ad9889cf(0x5000);
    x_ad9889cf(0x5001);
}

void x_5bf0e9e5(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg3", 0, 74, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();

    x_eb73d70f();
}

void x_bf79c7ba(Object *obj) {
    if (x_59ce598c[x_6f0b3be3].x_33260da8 & x_ffe9ce36) {
        obj->x_224610f1.y -= 10;
    } else if (x_59ce598c[x_6f0b3be3].x_33260da8 & x_37f8540c) {
        obj->x_224610f1.y += 10;
    }
    x_5ff12555(obj);
}

// unknown data
s32 D_80049400[] = { 0x40000, task_remove_current, 0x2800, 0x10000000, 0, "tc", x_bf79c7ba, 0x1000, 0 };

void x_6d8e5572(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_88f11482 x_4346f5cb = { 0, -500, 0, 0 };
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, 74, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_79c3a331(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, -20, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_ac7d3df0(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, 40, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_0f26cf14(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, 52, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 0, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_370978d4(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, 96, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_97f45a12(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_10430200();
    x_a0e73601("bg2", 0, 94, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_a0e73601("bg0", 0, -8, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_855a469e(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, -7, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, -64, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_8081616c(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, 20, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_5f5796f4(void) {
    s32 x_32f1d6e2 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    x_10430200();
    x_3f14db6e = x_a0e73601("bg2", 0, -6, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 4, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    x_7a8b20f2("arena", x_32f1d6e2);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_7bc4ef6e();
    x_82df7d23();
    x_eb73d70f();
}

void x_3253cdf0(Object *obj) {
    s16 a3;

    a3 = 1 - x_77831b2c[x_6f0b3be3].x_03604d94; // @bug maybe
    D_80080118 = 100;

    if (x_e30d50d2 & x_80ca0761) {
        obj->x_0f4167b4[1]++;
        if (obj->x_0f4167b4[1] == 4) {
            obj->x_0f4167b4[1] = 0;
            if (D_80081250 + D_80081254->x_64a8566c + 40) {
                D_80081254->x_64a8566c--;
            } else {
                if (x_5e4e2788 != x_3658fb97) {
                    x_77831b2c[x_6db66fc3].x_fb21ca8c = TRUE;
                    x_77831b2c[1 - x_6db66fc3].x_fb21ca8c = FALSE;
                    x_e38a6e19 = x_77831b2c[x_6db66fc3].x_eb1fe45b + x_a98e3fb7;
                } else {
                    x_e38a6e19 = x_77831b2c[1 - x_6db66fc3].x_eb1fe45b + x_a98e3fb7;
                    x_77831b2c[x_83106b21].x_03604d94 = TRUE;
                }
                x_e30d50d2 |= x_ecbcd14e | x_bee364e0;
                obj->flags |= x_f51cb721;
            }
        }

        x_59ce598c[a3].x_c4397934 = TRUE;
        if ((x_59ce598c[a3].buttons & x_9cefe76c) ||
            x_5e4e2788 == x_3658fb97 && (x_59ce598c[1 - a3].buttons & x_9cefe76c)) {
            x_25025961(D_80081254);
            if (x_5e4e2788 != x_3658fb97) {
                x_e38a6e19 = x_77831b2c[x_6db66fc3].x_eb1fe45b + x_a98e3fb7;
                x_77831b2c[x_6db66fc3].x_fb21ca8c = TRUE;
                x_77831b2c[1 - x_6db66fc3].x_fb21ca8c = FALSE;
            } else {
                x_e38a6e19 = x_901b251f;
            }
            x_e30d50d2 |= x_ecbcd14e | x_bee364e0;
            obj->flags |= x_f51cb721;
            D_80081254->flags &= ~x_8ce7ef70;
        }
    }
}

u16 D_80049434[] = { 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 298, 314, 330, 315, 316, 298, 331, 0 };

void x_c9523e04(Player *x_cc1d0de5, Object *x_84ff873b, s32 x_2092f891) {
    s16 i;
    s16 a1;
    s16 v0;
    s16 s4;
    char *name = "intXX.mov";

    s4 = 0;
    for (i = 0; D_80049434[i] != 0; i++) {
        // modifying string stored in .rodata section isn't good practice
        name[3] = (i / 10) + '0';
        name[4] = (i % 10) + '0';

        if ((v0 = x_e720f37d(name, x_2092f891)) >= 0) {
            a1 = x_cc1d0de5->x_68a6b5cd[D_80049434[i]].x_43d35340;
            x_84ff873b->x_20d20338->x_50771dcd[a1] = x_b717ed65[v0].data;
            s4++;
            x_cc1d0de5->x_68a6b5cd[D_80049434[i]].x_bab9966d = x_d8998bf6(x_84ff873b->x_20d20338, a1);
        }
    }
}

void x_af961405(u8 x_cc1d0de5, s16 x_84ff873b, s32 x_2092f891) {
    s32 s0;
    Object *obj;
    Object *a1;
    Object *v1;

    s0 = x_77831b2c[x_6f0b3be3].x_03604d94; // @bug maybe
    x_ad9889cf(x_2587f84f);
    x_77831b2c[s0].x_178eafa6 = 1;
    x_77831b2c[1 - s0].x_178eafa6 = 0;

    if (x_4090e698 != x_802d9c2e && x_f71086e0 != x_2a3e474b) {
        x_005cc66f();
    }

    if (x_cc1d0de5) {
        obj = x_4495b42c(x_3253cdf0, 0x1000);
        obj->x_0f4167b4[0] = 480;
    }

    x_6ed74c52(0);
    x_6ed74c52(1);

    x_77831b2c[x_83106b21].x_8a8d66c9 = x_77831b2c[x_6f0b3be3].x_8a8d66c9 = TRUE;

    a1 = x_3ac11521[1 - s0];
    a1->pos.x = 0;
    a1->pos.z = 0;
    a1->x_224610f1.y = 0x400;

    x_3ac11521[s0]->pos.x = -5000;
    x_3ac11521[s0]->pos.z = -5000;
    x_3ac11521[s0]->flags |= x_c537cafa;

    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    if (x_77831b2c[1 - s0].x_eb1fe45b != x_b52da315) {
        a1->flags |= x_3e24eba7;
    }

    x_e30d50d2 |= x_86c5bc33;

    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

    x_9df63a90 = FALSE;

    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;

    x_5e6f40dd(x_824b9544[x_83106b21].x_08b62e4f);
    x_5e6f40dd(x_824b9544[x_6f0b3be3].x_08b62e4f);

    x_c9523e04(x_824b9544 + 1 - s0, a1, x_2092f891);
    x_70e8be1f(x_f4bce728);
    x_e914de48(x_824b9544 + 1 - s0, x_84ff873b, 1);
    D_8008012C |= x_3309dc13;
}

void x_de15f6f9(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/gore/goreint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("goreint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg3", 0, 74, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();

    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_7dc0432e(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/aaro/aaroint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("aaroint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 74, 0x10000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 15, 0x8000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();

    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_075dfbb4(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/demi/demiint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("demiint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, -8, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_fff9464d(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/demo/demoint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("demoint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 32, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_bdd3194d(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/eve/eveint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("eveint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 52, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 0, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_7e48e02a(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/morp/morpint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("morpint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 96, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_2c237ab0(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/niik/niikint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("niikint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 94, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -8, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_10209bac(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/scar/scarint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("scarint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 0, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -64, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_67466a36(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/sono/sonoint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("sonoint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 26, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_1b39c152(void) {
    s32 x_a7710cd7 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;

    x_0928eec2("/zenm/zenmint", x_46bec5bf);
    x_af961405(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("zenmint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, -6, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 4, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    x_7a8b20f2("arena", x_a7710cd7);
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_eb73d70f();
    if (x_5e4e2788 != x_3658fb97) {
        x_ad9889cf(x_a7710cd7);
    }
}

void x_317f92d9(Object *obj) {
    if (x_824b9544[x_83106b21].x_7f68c36b->x_bab9966d - 2 == x_824b9544[x_83106b21].obj->x_5fcb1654) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
        x_e38a6e19 = x_c4da946c;
    }
}

void x_cb578282(Object *obj) {
    obj->x_5fcb1654++;
    if (obj->x_5fcb1654 >= obj->x_20d20338->x_8e601526 - 1) {
        obj->x_5fcb1654 = 0;
    }
}

void x_d7f2443f(void) {
    Object *obj;
    Object *x_942c59c7;
    void *a3;
    x_88f11482 x_93463df6 = { -200, 0, 0, 0 };
    x_4a7d6dd4 *x_3f14db6e;

    x_77831b2c[x_83106b21].x_eb1fe45b = x_968cc9a2;
    x_77831b2c[x_83106b21].x_fb21ca8c = TRUE;
    x_77831b2c[x_6f0b3be3].x_fb21ca8c = FALSE;
    x_77831b2c[x_83106b21].x_03604d94 = FALSE;
    x_77831b2c[x_6f0b3be3].x_03604d94 = TRUE;

    x_ad9889cf(0);
    x_e30d50d2 |= x_23ebd6b0 | x_d4c59644;
    D_8008012C |= x_8df87377;

    x_0928eec2("/sono/prize", x_46bec5bf);
    x_3f14db6e = x_a0e73601("prize", 0, 100, 0, 0, x_8ce7ef70, 0x3000);
    obj = x_4495b42c(x_d5d8f7a7, 0x1000);
    obj->x_0f4167b4[0] = 6;
    x_82df7d23();

    x_e30d50d2 &= ~(x_d4c59644 | x_bee364e0);
    D_8008012C &= ~x_8df87377;
    x_0928eec2("/sono/sonoboss", x_46bec5bf);
    x_af961405(FALSE, 346, 0x3000);
    x_a0e73601("bg2", 0, 26, 0x2000, 0x10000, 0, 0);
    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, 0);
    x_7a8b20f2("arena", 0);
    a3 = x_b717ed65[x_e720f37d("relic.k2", 0x3000)].x_4962fc73;
    x_942c59c7 = x_572f827d(&x_93463df6, 0x1000, x_cb578282, a3);
    x_942c59c7->x_224610f1.y = 0x400;
    x_942c59c7->color.a = 80;
    x_4495b42c(x_317f92d9, 0x1000);
    x_25025961(x_3f14db6e);
    x_82df7d23();

    x_ad9889cf(0x3000);
    x_ad9889cf(0);
    x_ad9889cf(1);
    if (D_80051F68 == 0) {
        x_e38a6e19 = x_3dba3c6c;
    }
}

void x_526ab60f(void) {
    Object *obj;
    x_88f11482 x_54406eae = { -800, -100, 0, 0 };
    Object *a1;
    s32 x_fc517ba8;
    s16 x_ea78ab9e;
    void *a3;
    s32 padding;

    x_fc517ba8 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_ea78ab9e = x_77831b2c[x_6f0b3be3].x_03604d94;

    x_ad9889cf(x_2587f84f);
    x_0928eec2("/demi/demiboss", x_46bec5bf);
    x_6ed74c52(0);
    x_6ed74c52(1);

    a1 = x_824b9544[x_ea78ab9e].obj;
    a1->pos.x = a1->pos.z = 0;
    a1->x_224610f1.y = 0x400;

    x_3ac11521[1 - x_ea78ab9e]->pos.x = -5000;
    x_3ac11521[1 - x_ea78ab9e]->pos.z = -5000;
    x_3ac11521[1 - x_ea78ab9e]->flags |= x_c537cafa;

    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    a1->flags |= x_3e24eba7;
    x_e30d50d2 |= x_86c5bc33;

    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

    x_9df63a90 = FALSE;

    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    x_5e6f40dd(x_824b9544[x_83106b21].x_08b62e4f);
    x_5e6f40dd(x_824b9544[x_6f0b3be3].x_08b62e4f);

    x_c9523e04(&x_824b9544[x_ea78ab9e], a1, 0x3000);
    x_70e8be1f(x_f4bce728);
    x_e914de48(&x_824b9544[x_ea78ab9e], x_467d52ce, 1);
    D_8008012C |= x_3309dc13;
    x_4495b42c(x_d2b7f1c2, 0x1000);
    x_7bc4ef6e();

    a3 = x_b717ed65[x_e720f37d("relic.k5", 0x3000)].x_4962fc73;
    obj = x_572f827d(&x_54406eae, 0x1000, x_cb578282, a3);
    obj->x_224610f1.y = 0x400;
    obj->color.a = 80;

    x_a0e73601("bg2", 0, -32, 0x2000, 0x10000, 0, x_fc517ba8);
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_fc517ba8);
    x_7a8b20f2("arena", x_fc517ba8);
    x_9df63a90 = TRUE;
    x_82df7d23();
    x_ad9889cf(0x3000);
    x_e38a6e19 = x_1a4de9e0;
}

void x_97d4c18e(void) {
    u16 x_4c3c4684;
    u16 x_de61763c;
    Object *obj;
    char x_fc517ba8[12];
    char x_49781937[12];

    x_4c3c4684 = 1 - x_77831b2c[x_6f0b3be3].x_03604d94;
    x_de61763c = x_824b9544[x_4c3c4684].x_eb1fe45b;
    x_40b36af5();
    x_0928eec2("/title/ending", x_f238a878);

    x_dab0846a(x_fc517ba8, "/");
    x_8c518b47(x_fc517ba8, D_8004B844[x_de61763c].x_1256da71->name);
    x_8c518b47(x_fc517ba8, "/");
    x_8c518b47(x_fc517ba8, D_8004B844[x_de61763c].x_1256da71->name);
    x_8c518b47(x_fc517ba8, "end");
    x_0928eec2(x_fc517ba8, x_f238a878);

    obj = x_4495b42c(x_5638088b, 0x1000);
    obj->x_0f4167b4[0] = 60;

    x_dab0846a(x_49781937, D_8004B844[x_de61763c].x_1256da71->name);
    x_8c518b47(x_49781937, "end1");

    D_80081254 = x_a0e73601(x_49781937, 0, 40, 0, 0, x_96186256, 0x4000);
    D_80081254 = x_a0e73601("passwd", 0, 205, 0, 0, x_96186256, 0x4000);
    x_e30d50d2 |= x_86c5bc33;
    D_8008012C |= x_8df87377;
    x_82df7d23();
    x_ad9889cf(0x4000);
}

void x_0f62bcb4(void) {
    Object *x_87eba76e;

    x_40b36af5();
    x_0928eec2("/title/credit", x_f238a878);
    D_80081254 = x_a0e73601("credit", 0, 250, 0, 0, x_8ce7ef70, 0x4000);
    D_80081250 = D_80081254->height;
    x_87eba76e = x_4495b42c(x_070b94ab, 0x1000);
    x_87eba76e->x_0f4167b4[2] = 4;
    x_6eea7033(x_87eba76e, 0x4000);
    D_80080129 = FALSE;
    x_e30d50d2 |= x_86c5bc33;
    D_8008012C |= x_8df87377;
    x_82df7d23();
    x_ad9889cf(0x4000);
}

void x_e8d61695(Object *obj) {
    if (x_59ce598c[D_8013C24C].buttons & x_9cefe76c) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
    }
}

void x_39ec2f37(void) {
    x_40b36af5();
    x_0928eec2("/title/easywin", x_f238a878);
    x_a0e73601("easyimg", 0, 0, 0, 0, x_96186256, 0x4000);
    x_4495b42c(x_e8d61695, 0x1000);
    D_80080129 = TRUE;
    x_e30d50d2 |= x_86c5bc33;
    D_8008012C |= x_8df87377;
    x_82df7d23();
    x_ad9889cf(0x4000);
    x_e38a6e19 = x_a3a32a2b;
}

void x_a7b2701f(s32 x_cc1d0de5) {
    D_80080136 = x_4540c33c[x_cc1d0de5].x_d23de2ad;
    D_80080138 = x_4540c33c[x_cc1d0de5].x_55739355;
    D_80080130 = x_4540c33c[x_cc1d0de5].x_60c27ea9;
    D_80080132 = x_4540c33c[x_cc1d0de5].x_ee25ce89;
    D_80080134 = x_4540c33c[x_cc1d0de5].x_747e2503;
    D_80080110 = x_4540c33c[x_cc1d0de5].x_b8173ab8;
    D_80080112 = x_4540c33c[x_cc1d0de5].x_d863406f;
    D_80080114 = x_4540c33c[x_cc1d0de5].x_f6c089c5;
}

void x_84948d12(u8 x_cc1d0de5) {
    x_88f11482 x_fd09f53e[] = { { -1152, 0, 0, 0 }, { 0, 0, 0, 0 } };
    u32 x_b3c51f8a;
    s32 s1;
    s16 x_05e00b01;
    u16 t9;
    Object *s0;
    Object *a3;

    s1 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    t9 = 1 - s1;
    x_b3c51f8a = s1;
    x_6ed74c52(0);
    x_6ed74c52(1);

    s0 = x_824b9544[t9].obj;
    a3 = x_824b9544[x_b3c51f8a].obj;

    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    s0->pos.x = x_fd09f53e[1].x;
    s0->pos.y = x_fd09f53e[1].y;
    s0->pos.z = x_fd09f53e[1].z;
    a3->pos.x = x_fd09f53e[0].x;
    a3->pos.y = x_fd09f53e[0].y;
    a3->pos.z = x_fd09f53e[0].z;

    if (!x_cc1d0de5) {
        if (x_77831b2c[t9].x_eb1fe45b == x_968cc9a2) {
            x_824b9544[t9].obj->pos.x -= 400;
        } else if (x_77831b2c[t9].x_eb1fe45b == x_73cf9ceb) {
            x_824b9544[t9].obj->pos.x += 1200;
            if (x_824b9544[x_b3c51f8a].obj) {} // required to match
        }
    }

    s0->x_224610f1.y = 0x400;

    x_05e00b01 = x_77831b2c[t9].x_eb1fe45b; // required to match
    if ((x_05e00b01 == x_968cc9a2 || x_05e00b01 == x_73cf9ceb) && !x_cc1d0de5) {
        a3->x_224610f1.y = 0x400;
    } else {
        a3->x_224610f1.y = 0xC00;
    }

    if (x_77831b2c[t9].x_eb1fe45b != x_b52da315) {
        s0->flags |= x_3e24eba7;
    }
    a3->flags |= x_3e24eba7;

    x_e30d50d2 |= x_86c5bc33;
    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    x_9df63a90 = FALSE;

    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    x_5e6f40dd(x_824b9544[x_83106b21].x_08b62e4f);
    x_5e6f40dd(x_824b9544[x_6f0b3be3].x_08b62e4f);

    x_70e8be1f(x_f4bce728);
    x_c9523e04(&x_824b9544[x_b3c51f8a], a3, 0x4000);
    x_c9523e04(&x_824b9544[t9], s0, 0x4000);
    D_8008012C |= x_3309dc13;
    x_a0e73601("bg2", 0, -27, 0x2000, 0x10000, 0, x_b3c51f8a);
    x_a0e73601("bg0", x_b3c51f8a * 0, 8, 0x1000, 0x10000, x_96186256, x_b3c51f8a);
    x_a7b2701f(x_1a4de9e0);
    x_7a8b20f2("arena", x_b3c51f8a);
    x_9df63a90 = TRUE;
}

void x_5f08f251(void) {
    u16 x_21e2fc34;
    u16 x_5bbba600;
    char x_32f1d6e2[80];

    x_21e2fc34 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_5bbba600 = 1 - x_21e2fc34;
    x_77831b2c[x_83106b21].x_178eafa6 = x_77831b2c[x_6f0b3be3].x_178eafa6 = 0;
    x_9df63a90 = TRUE;
    D_80080234 = 1;

    switch (x_77831b2c[x_5bbba600].x_eb1fe45b) {
        case x_c4ddde6d:
            x_dab0846a(x_32f1d6e2, "/aaro/aarogend");
            break;
        case x_ff5073d4:
            x_dab0846a(x_32f1d6e2, "/demi/demigend");
            break;
        case x_73cf9ceb:
            x_dab0846a(x_32f1d6e2, "/demo/demogend");
            break;
        case x_6a049984:
            x_dab0846a(x_32f1d6e2, "/eve/evegend");
            break;
        case x_537ef8a7:
            x_dab0846a(x_32f1d6e2, "/gore/goregend");
            break;
        case x_b52da315:
            x_dab0846a(x_32f1d6e2, "/morp/morpgend");
            break;
        case x_13ed828f:
            x_dab0846a(x_32f1d6e2, "/niik/niikgend");
            break;
        case x_12e7e1dc:
            x_dab0846a(x_32f1d6e2, "/scar/scargend");
            break;
        case x_968cc9a2:
            x_dab0846a(x_32f1d6e2, "/sono/sonogend");
            break;
        case x_379149a4:
            x_dab0846a(x_32f1d6e2, "/zenm/zenmgend");
            break;
    }

    x_0928eec2(x_32f1d6e2, x_f238a878);
    if (x_6b61a084(x_32f1d6e2, "/demi/demigend") != 0) {
        if (x_77831b2c[x_5bbba600].x_eb1fe45b != x_968cc9a2 && x_77831b2c[x_5bbba600].x_eb1fe45b != x_73cf9ceb) {
            x_0928eec2("/demi/demigend", x_f238a878);
        }
    }

    switch (x_77831b2c[x_5bbba600].x_eb1fe45b) {
        case x_73cf9ceb:
            x_0928eec2("/demi/demigen3", x_f238a878);
            x_4495b42c(x_64109585, 0x1000);
            break;
        case x_968cc9a2:
            x_0928eec2("/demi/demigen2", x_f238a878);
            x_4495b42c(x_64109585, 0x1000);
            break;
    }

    x_84948d12(FALSE);
    x_0928eec2("/demi/demidust", x_2587f84f);
    x_e914de48(&x_824b9544[x_21e2fc34], x_9b1bc46c, 1);
    x_e914de48(&x_824b9544[x_5bbba600], x_41323a8a, 1);
    x_4495b42c(x_bc6a41ae, 0x1000);
    x_82df7d23();
    x_ad9889cf(0x4000);
    x_ad9889cf(x_2587f84f);
    x_e38a6e19 = x_896bb5ec;
}

void x_2d92be0a(void) {
    u16 x_1a071863;
    u16 x_de61763c;
    char x_f10a928a[12];
    char x_d16311d7[12];
    Object *obj;

    x_1a071863 = 1 - x_77831b2c[x_6f0b3be3].x_03604d94;
    x_de61763c = x_824b9544[x_1a071863].x_eb1fe45b;

    x_0928eec2("/title/ending", x_f238a878);

    x_dab0846a(x_f10a928a, "/");
    x_8c518b47(x_f10a928a, D_8004B844[x_de61763c].x_1256da71->name);
    x_8c518b47(x_f10a928a, "/");
    x_8c518b47(x_f10a928a, D_8004B844[x_de61763c].x_1256da71->name);
    x_8c518b47(x_f10a928a, "end");
    x_0928eec2(x_f10a928a, x_f238a878);

    x_dab0846a(x_d16311d7, D_8004B844[x_de61763c].x_1256da71->name);
    x_8c518b47(x_d16311d7, "end");
    D_80081254 = x_a0e73601(x_d16311d7, 0, 250, 0, 0, x_8ce7ef70, 0x4000);
    D_80081250 = D_80081254->height;

    obj = x_4495b42c(x_070b94ab, 0x1000);
    obj->x_0f4167b4[2] = 5;
    obj->x_0f4167b4[1] = 0;
    obj->x_0f4167b4[0] = 0;

    D_80080129 = FALSE;
    x_e30d50d2 |= x_86c5bc33;
    x_d23046bd(x_f4bce728, x_1a071863);
}

void x_6da0c319(void) {
    Object *obj;
    Model *a3;
    x_88f11482 x_048c1e73 = { -600, 0, -30, 0 };
    x_88f11482 x_c188a78e = { -400, 0, 200, 0 };
    x_88f11482 x_dcccc364 = { -400, 0, 0, 0 };
    u16 x_21e2fc34;
    u16 x_5bbba600;
    Player *x_13d65ace;
    Player *x_c48d15e0;
    char x_32f1d6e2[72];

    x_21e2fc34 = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_5bbba600 = 1 - x_21e2fc34;

    x_c48d15e0 = &x_824b9544[x_5bbba600];
    x_13d65ace = &x_824b9544[x_21e2fc34];

    x_9df63a90 = TRUE;
    D_80080234 = 1;
    x_77831b2c[x_21e2fc34].x_178eafa6 = x_77831b2c[x_5bbba600].x_178eafa6 = 0;

    switch (x_77831b2c[x_5bbba600].x_eb1fe45b) {
        case x_c4ddde6d:
            x_dab0846a(x_32f1d6e2, "/aaro/aaroclos");
            break;
        case x_ff5073d4:
            x_dab0846a(x_32f1d6e2, "/demi/demiclos");
            break;
        case x_73cf9ceb:
            x_dab0846a(x_32f1d6e2, "/demo/democlos");
            break;
        case x_6a049984:
            x_dab0846a(x_32f1d6e2, "/eve/eveclos");
            break;
        case x_537ef8a7:
            x_dab0846a(x_32f1d6e2, "/gore/goreclos");
            break;
        case x_b52da315:
            x_dab0846a(x_32f1d6e2, "/morp/morpclos");
            break;
        case x_13ed828f:
            x_dab0846a(x_32f1d6e2, "/niik/niikclos");
            break;
        case x_12e7e1dc:
            x_dab0846a(x_32f1d6e2, "/scar/scarclos");
            break;
        case x_968cc9a2:
            x_dab0846a(x_32f1d6e2, "/sono/sonoclos");
            break;
        case x_379149a4:
            x_dab0846a(x_32f1d6e2, "/zenm/zenmclos");
            break;
    }
    x_0928eec2(x_32f1d6e2, x_f238a878);

    if (x_77831b2c[x_5bbba600].x_eb1fe45b == x_73cf9ceb) {
        x_dab0846a(x_32f1d6e2, "/demi/demigen3");
    } else {
        x_dab0846a(x_32f1d6e2, "/demi/demigen2");
    }
    x_0928eec2(x_32f1d6e2, x_f238a878);

    x_84948d12(TRUE);
    x_e914de48(x_13d65ace, x_dd751953, 1);
    x_e914de48(x_c48d15e0, x_c8c943ae, 1);
    x_13d65ace->obj->flags |= x_c537cafa;
    x_2d92be0a();

    x_0928eec2("/demi/relic", x_f238a878);
    a3 = x_b717ed65[x_e720f37d("relic.k5", 0x4000)].x_4962fc73;
    obj = x_572f827d(&x_dcccc364, 0x1000, x_cb578282, a3);
    obj->color.a = 80;

    if (x_77831b2c[x_5bbba600].x_eb1fe45b == x_968cc9a2 || x_77831b2c[x_5bbba600].x_eb1fe45b == x_73cf9ceb) {
        if (x_5bbba600 != 0) {
            a3 = x_b717ed65[x_e720f37d("dheadp2.k2", 0x4000)].x_4962fc73;
        } else {
            a3 = x_b717ed65[x_e720f37d("dheadp1.k2", 0x4000)].x_4962fc73;
        }
        obj = x_572f827d(&x_dcccc364, 0x1000, NULL, a3);
        obj->x_224610f1.y = -1179;
        obj->color.a = 255;
        obj->flags |= x_3e24eba7;
    }

    x_82df7d23();
    x_40b36af5();
}

void x_c9505e23(void) {
    s32 i;

    D_800801F1 = TRUE;
    x_77831b2c[x_83106b21].x_7d8e7a6f = x_77831b2c[x_6f0b3be3].x_7d8e7a6f = 0;

    for (i = 0; i < 11; i++) {
        D_800B6350[x_6f0b3be3][i] = 0;
        D_800B6350[x_83106b21][i] = 0;
    }

    x_77831b2c[x_83106b21].x_8a8d66c9 = x_77831b2c[x_6f0b3be3].x_8a8d66c9 = TRUE;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    x_77831b2c[x_83106b21].x_c35c64af = x_77831b2c[x_6f0b3be3].x_c35c64af = 400;
    x_77831b2c[x_83106b21].x_cc57155e = x_77831b2c[x_6f0b3be3].x_cc57155e = 0;
}

void x_da1161b7(void) {
    Object *x_a7ef4a30;
    x_f0d7e70f x_081c4eef = { x_35414b8d, x_f9bb9d72, 0, 0x1000, "options2.sp2" };
    x_88f11482 x_c9614940 = { 164, 155, 0, 0 };

    x_40b36af5();
    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    x_0928eec2("/title", x_35b88489);
    x_a0e73601("dr_title", 0, 0, 0, 0, x_96186256, x_35b88489);
    D_8008012C |= x_8df87377;
    x_e30d50d2 |= x_86c5bc33;

    if (x_4090e698 == x_f699a14d) {
        Model *x_2ac4abbe = x_b717ed65[x_e720f37d("title.k2", x_35b88489)].x_4962fc73;
        x_a7ef4a30 = x_572f827d(&x_c787d34b, 0x1000, x_91e62f73, x_2ac4abbe);
        x_a7ef4a30->flags |= x_a816b63b;
    } else {
        x_a7ef4a30 = x_12014163(&x_c9614940, &x_081c4eef, x_35b88489);
    }

    x_a7ef4a30->x_64946db0->x_c7f843c2 = 30;

    x_4495b42c(x_8daf2444, 0x1000);
    x_c9505e23();
    x_82df7d23();

    x_ad9889cf(0x2000);
    if (x_e38a6e19 != x_802d9c2e) {
        x_ad9889cf(x_24b231d4);
    }
}

void x_cb95930b(Object *obj) {
    x_e1511bdd(D_8005BEFC, 0);

    if (D_8005BEFC - 2 > 0) {
        D_8005BEFC -= 2;
        return;
    }

    obj->flags |= x_f51cb721;
    D_80080116 = 0;
}

void x_200fa268(Object *obj) {
    x_f0d7e70f x_fc517ba8 = { 83, x_f9bb9d72, 0, 0x1000, "options2.sp2" };
    x_88f11482 x_93463df6 = { 160, 155, 0, 0 };
    Object *v0;

    D_80080116 = 200;
    x_e1511bdd(D_8005BEFC, NULL);

    if (D_8005BEFC + 32 < 255) {
        D_8005BEFC += 32;
        return;
    }

    x_f3da6ca2(0x2000, 8);
    obj->x_0232396f = x_cb95930b;
    x_a0e73601("dr_title", 0, 0, 0, 0, x_96186256, x_35b88489);
    v0 = x_12014163(&x_93463df6, &x_fc517ba8, 0x2000);
    v0->x_64946db0->x_c7f843c2 = 60;
    x_f4bce728->pos.z = -2200;
    x_4495b42c(x_8daf2444, 0x1000);
}

void x_2c292a7b(void) {
    s32 unused;
    Object *v0;
    x_f0d7e70f x_d16311d7 = { 83, x_f9bb9d72, 0, 0x1000, "options2.sp2" };
    x_88f11482 x_32f1d6e2 = { 160, 155, 0, 0 };

    D_80080129 = FALSE;
    D_8008012C |= x_8df87377;
    x_e30d50d2 |= x_86c5bc33;
    x_0928eec2("/title/tit_int", x_35b88489);
    x_0928eec2("/plyrsel/plyrsel", x_24b231d4);
    v0 = x_4495b42c(x_37361bf1, 0x1000);
    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    x_6eea7033(v0, 0x2000);

    D_80081254 = x_a0e73601("oplog", 0, 250, 0, 0x10000, x_8ce7ef70, x_35b88489);
    D_80081250 = D_80081254->height;

    x_c9505e23();
    x_82df7d23();
    x_ad9889cf(0x2000);
    if (x_e38a6e19 != x_802d9c2e) {
        x_ad9889cf(x_24b231d4);
    }
}

void x_1c76abdb(void) {
    x_0928eec2("/title/error", x_35b88489);
    x_a0e73601("messpg", 0, 90, 0, 180, x_96186256, x_35b88489);
    x_82df7d23();
}

void x_cbafccd1(void) {
    x_40b36af5();
    x_e30d50d2 |= x_86c5bc33;
    D_8008012C |= x_8df87377;
    D_8008012C |= x_bbfa9667;
    if (!x_59ce598c[x_83106b21].x_12a7bd86 && !x_59ce598c[x_6f0b3be3].x_12a7bd86) {
        x_1c76abdb();
    }

    x_0928eec2("/title/logo", x_35b88489);
    x_a0e73601("vic", 0, 30, 0, 180, x_96186256, x_35b88489);
    x_a0e73601("n64lic", 0, 190, 0, 240, x_96186256, x_35b88489);
    x_4495b42c(x_baaaa706, 0x1000);
    x_82df7d23();
    x_ad9889cf(0x2000);
}

void x_3ecc4edc(void) {
    Object *controller;
    Object *obj;
    x_f0d7e70f x_910f3493 = { x_e7beedae, x_a2a8ba2f, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_dfcbab92 = { x_edf70307, x_bc5bf713, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_3d280011 = { x_adc09931, x_0e243657, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_f2490cb2 = { x_0357f149, x_4d34121d, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_4b76305b = { x_4b8a6796, x_c1c0a10d, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_d252ddf2 = { x_86be64ca, x_ff609efb, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_7b5eb252 = { x_86be64ca, x_28ceb562, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_6a701386 = { x_51d9e266, x_12081995, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_4ae9ab69 = { x_273c3512, x_53598eda, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_f4b84c7c = { x_9b5ea511, x_b5c125fc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_e8326674 = { x_8bab2f3e, x_dd25b026, 0, x_9d442987, "options2.sp2" };
    x_88f11482 x_7b3384f3 = { 130, 130, 0, 0 };
    x_88f11482 x_98eec76d = { 181, 74, 0, 0 };
    x_88f11482 x_39a42620 = { 181, 91, 0, 0 };
    x_88f11482 x_4ff52ceb = { 181, 105, 0, 0 };
    x_88f11482 x_867609ad = { 181, 121, 0, 0 };
    x_88f11482 x_49ea79b4 = { 181, 136, 0, 0 };
    x_88f11482 x_eeea4d36 = { 181, 151, 0, 0 };
    x_88f11482 x_375e794a = { 118, 166, 0, 0 };
    x_88f11482 x_ac1eaa4d = { 117, 181, 0, 0 };
    x_88f11482 x_5a64842d = { 135, 198, 0, 0 };
    x_88f11482 x_cdcf9ce9 = { 146, 228, 0, 0 };

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    x_0928eec2("/title/option", x_35b88489);
    x_a0e73601("bgopt", 0, 0, 0, 0, x_96186256, x_35b88489);
    D_8008012C |= x_8df87377;
    x_e30d50d2 |= x_86c5bc33;

    controller = x_12014163(&x_7b3384f3, &x_910f3493, x_35b88489);

    obj = x_12014163(&x_98eec76d, &x_dfcbab92, x_35b88489);
    obj->x_5fcb1654 = x_028e5846 + x_be30259d;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_39a42620, &x_3d280011, x_35b88489);
    obj->x_5fcb1654 = x_c8356c60 + x_336693df;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_4ff52ceb, &x_f2490cb2, x_35b88489);
    obj->x_5fcb1654 = x_adcfd05c + x_afcff1b4;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_867609ad, &x_4b76305b, x_35b88489);
    obj->x_5fcb1654 = x_a7d9a1e8 + x_4b8a6796;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_49ea79b4, &x_d252ddf2, x_35b88489);
    obj->x_5fcb1654 = x_66ddef46 / (0x8000 / 9) + x_afcff1b4;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_eeea4d36, &x_7b5eb252, x_35b88489);
    obj->x_5fcb1654 = x_15814eea / (0x8000 / 9) + x_afcff1b4;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_375e794a, &x_6a701386, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_ac1eaa4d, &x_4ae9ab69, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_5a64842d, &x_f4b84c7c, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = x_12014163(&x_cdcf9ce9, &x_e8326674, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    x_82df7d23();
    x_ad9889cf(x_35b88489);
}

void x_038a90c5(Object *obj, s16 x_30bbe547) {
    s16 i;
    s16 button;

    button = D_80049B30[obj->x_0f4167b4[x_13266785]];
    for (i = 0; i < 8; i++) {
        if (x_013307ec[x_30bbe547][i] == button) {
            break;
        }
    }

    switch (i) {
        case 0:
            obj->x_5fcb1654 = x_729a61e6;
            break;
        case 1:
            obj->x_5fcb1654 = x_a9cd5d36;
            break;
        case 2:
            obj->x_5fcb1654 = x_6dce29db;
            break;
        case 3:
            obj->x_5fcb1654 = x_23d505ec;
            break;
        case 4:
            obj->x_5fcb1654 = x_810a8a6e;
            break;
        case 5:
            obj->x_5fcb1654 = x_acee1321;
            break;
        case 6:
            obj->x_5fcb1654 = x_a4344608;
            break;
        case 7:
            obj->x_5fcb1654 = x_ab3153db;
            break;
    }
}

void x_35ffeb22(void) {
    Object *x_6dc41566;
    Object *x_abfe8d41;
    Object *obj;
    x_f0d7e70f x_d772ebb4 = { x_42fcfcea, NULL, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_43f9ca3f = { x_7eb4b3f4, x_a9342b2f, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_fa93fe6a = { x_ab3153db, x_d4ae14dc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_c592c457 = { x_a4344608, x_d4ae14dc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_f13e2bec = { x_acee1321, x_d4ae14dc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_1ccec23b = { x_23d505ec, x_d4ae14dc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_23c4e7d3 = { x_729a61e6, x_d4ae14dc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_c1e64f43 = { x_6dce29db, x_d4ae14dc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_1c7346b1 = { x_a9cd5d36, x_d4ae14dc, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_cc88bd06 = { x_8bab2f3e, x_2cae892b, 0, x_9d442987, "options2.sp2" };
    x_88f11482 x_0bef2693 = { 133, 126, 0, 0 };
    x_88f11482 x_bf23db74 = { 40, 82, 0, 0 };
    x_88f11482 x_7e4f6c9d = { 179, 82, 0, 0 };
    x_88f11482 x_e725bb19 = { 40, 96, 0, 0 };
    x_88f11482 x_fef76a74 = { 179, 96, 0, 0 };
    x_88f11482 x_77027484 = { 40, 110, 0, 0 };
    x_88f11482 x_e0e052f7 = { 179, 110, 0, 0 };
    x_88f11482 x_ebe59286 = { 40, 124, 0, 0 };
    x_88f11482 x_b42630db = { 179, 124, 0, 0 };
    x_88f11482 x_c9b06339 = { 40, 138, 0, 0 };
    x_88f11482 x_2a8bc04d = { 179, 138, 0, 0 };
    x_88f11482 x_887b975c = { 40, 152, 0, 0 };
    x_88f11482 x_03f0364f = { 179, 152, 0, 0 };
    x_88f11482 x_aa4f74c9 = { 40, 166, 0, 0 };
    x_88f11482 x_48fb41dd = { 179, 166, 0, 0 };
    x_88f11482 x_fde88f40 = { 40, 180, 0, 0 };
    x_88f11482 x_09ae4a39 = { 179, 180, 0, 0 };
    x_88f11482 x_20652c2f = { 149, 224, 0, 0 };

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    x_0928eec2("/title/control", x_35b88489);
    x_a0e73601("bgcont", 0, 0, 0, 0, x_96186256, x_35b88489);
    D_8008012C |= x_8df87377;
    x_e30d50d2 |= x_86c5bc33;

    x_12014163(&x_0bef2693, &x_d772ebb4, x_35b88489);

    x_6dc41566 = x_12014163(&x_bf23db74, &x_43f9ca3f, x_35b88489);
    x_6dc41566->x_0f4167b4[x_0371940a] = x_6dc41566;
    x_6dc41566->x_0f4167b4[x_13266785] = 0;
    x_038a90c5(x_6dc41566, 0);

    obj = x_12014163(&x_e725bb19, &x_fa93fe6a, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 1;
    x_038a90c5(obj, 0);

    obj = x_12014163(&x_77027484, &x_c592c457, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 2;
    x_038a90c5(obj, 0);

    obj = x_12014163(&x_ebe59286, &x_f13e2bec, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 3;
    x_038a90c5(obj, 0);

    obj = x_12014163(&x_c9b06339, &x_1ccec23b, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 4;
    x_038a90c5(obj, 0);

    obj = x_12014163(&x_887b975c, &x_23c4e7d3, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 5;
    x_038a90c5(obj, 0);

    obj = x_12014163(&x_aa4f74c9, &x_c1e64f43, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 6;
    x_038a90c5(obj, 0);

    obj = x_12014163(&x_fde88f40, &x_1c7346b1, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 7;
    x_038a90c5(obj, 0);

    x_abfe8d41 = x_12014163(&x_7e4f6c9d, &x_43f9ca3f, x_35b88489);
    x_abfe8d41->x_0f4167b4[x_0371940a] = x_abfe8d41;
    x_abfe8d41->x_0f4167b4[x_13266785] = 0;
    x_abfe8d41->x_0f4167b4[x_283009b1] = x_6f0b3be3;
    x_038a90c5(x_abfe8d41, 1);

    obj = x_12014163(&x_fef76a74, &x_fa93fe6a, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 1;
    x_038a90c5(obj, 1);

    obj = x_12014163(&x_e0e052f7, &x_c592c457, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 2;
    x_038a90c5(obj, 1);

    obj = x_12014163(&x_b42630db, &x_f13e2bec, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 3;
    x_038a90c5(obj, 1);

    obj = x_12014163(&x_2a8bc04d, &x_1ccec23b, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 4;
    x_038a90c5(obj, 1);

    obj = x_12014163(&x_03f0364f, &x_23c4e7d3, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 5;
    x_038a90c5(obj, 1);

    obj = x_12014163(&x_48fb41dd, &x_c1e64f43, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 6;
    x_038a90c5(obj, 1);

    obj = x_12014163(&x_09ae4a39, &x_1c7346b1, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 7;
    x_038a90c5(obj, 1);

    obj = x_12014163(&x_20652c2f, &x_cc88bd06, x_35b88489);
    obj->x_0f4167b4[x_f2901470] = x_6dc41566;
    obj->x_0f4167b4[x_88d435fa] = x_abfe8d41;

    x_82df7d23();
    x_ad9889cf(x_35b88489);
}

void x_9450f821(void) {
    x_f0d7e70f x_b97c1d15 = { x_87664290, x_0073afdd, 0, x_9d442987, "options2.sp2" };
    x_88f11482 x_b0e0e2fc = { 133, 126, 0, 0 };

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    x_0928eec2("/title/rank", x_35b88489);
    x_a0e73601("bgrank", 0, 4, 0, 0, x_96186256, x_35b88489);
    x_fa7941af = x_12014163(&x_b0e0e2fc, &x_b97c1d15, x_35b88489);
    x_8da34614();
    D_8008012C |= x_8df87377;
    x_e30d50d2 |= x_86c5bc33;
    x_82df7d23();
    x_ad9889cf(x_35b88489);
}

void x_2288fd1a(void) {
    x_ad9889cf(0);
    x_ad9889cf(1);
    x_ad9889cf(x_2587f84f);

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    x_0928eec2("/title/stats", x_35b88489);
    x_a0e73601("aarost", 0, 13, 0, 0, x_96186256, x_35b88489);
    D_8008012C |= x_8df87377;
    x_e30d50d2 |= x_86c5bc33;
    x_4495b42c(x_8383794c, x_9d442987);
    x_82df7d23();
    x_ad9889cf(x_35b88489);
}

static void x_4700bff9(void) {
}

void x_64d3e54a(void) {
    s32 unused;
    x_2758cdab x_8a9089b3 = { 0, -400, 0, 0 };
    x_88f11482 x_7d0aaee0 = { -400, 0, 0, 0 };
    x_88f11482 x_de61763c = { 400, 0, 0, 0 };
    s32 x_f0d1d935;
    s32 x_54406eae = x_77831b2c[x_6f0b3be3].x_fb21ca8c;
    x_aece7675 x_d16311d7 = { "gore", task_remove_current, 0, 0x1000, 0 };
    x_aece7675 x_32f1d6e2 = { "arena", task_remove_current, 0, 0x1000, 0 };

    x_0928eec2("/bars", x_2587f84f);
    x_6ed74c52(0);
    x_6ed74c52(1);
    x_a0e73601("bg2", 0, 74, 0x2000, 0x10000, 0, x_54406eae);
    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_54406eae);
    x_7a8b20f2("arena", x_54406eae);
    x_41d6ae47();

    x_f4bce728->x_64946db0->x_c7f843c2 = 0;
    x_f4bce728->x_64946db0->flags = x_0fb55613;
    x_f4bce728->x_64946db0->x_f6382727 = x_a92790e6;
    x_f4bce728->x_64946db0->x_116c9ff3 = 0;

    x_82df7d23();
}
