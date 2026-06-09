#include "common.h"
#include "sprite_ids.h"
#include "task.h"

#define x_0140ad12 0
#define x_82e2e1db 1
#define x_a44625a6 2

#define x_d0d35cc6 0xFFFF

typedef struct x_64b038aa {
    /* 0x00 */ u16 *sequence;
    /* 0x04 */ void (*handler)(s16, u16, u16);
    /* 0x08 */ s16 x_273c58c6;
    /* 0x0A */ s16 x_08455b9a;
} x_64b038aa; // size = 0xC

typedef struct x_5aaa1a5b {
    /* 0x00 */ x_64b038aa *x_3a1b45d4;
    /* 0x04 */ s32 x_e4b35e9b;
    /* 0x08 */ s32 x_30f758ad;
} x_5aaa1a5b;

extern s16 x_5e4e2788;
extern s16 D_80049390;
extern x_425d6ed3 *D_8013C234;
extern x_425d6ed3 *D_8013C238;

u8 x_5c207a56 = FALSE;
u8 x_aee302fc = FALSE;

Object *x_696804c5[2];
u32 x_6db66fc3;

void x_35e81a03(Object *obj, Object *x_84ff873b);

void x_eb293927(Object *obj) {
    s16 a3;
    s16 v0;
    s16 x_33260da8;
    s16 buttons;
    s16 x_30bbe547;

    x_30bbe547 = obj->x_0f4167b4[0];
    x_33260da8 = obj->x_0f4167b4[1];
    obj->x_0f4167b4[1] = buttons = x_59ce598c[x_30bbe547].buttons;
    a3 = obj->x_0f4167b4[2]--;

    if (buttons & x_9cefe76c) {
        if (a3 <= 0) {
            obj->x_0f4167b4[2] = 10;
        } else {
            return;
        }
    }
    if (buttons & x_1c9950cc) {
        if (a3 <= 0 || buttons != x_33260da8) {
            obj->x_0f4167b4[2] = 10;
        } else {
            return;
        }
    }

    v0 = obj->frameCounter;

    if (buttons & (x_ad1aebe6 | x_fc4a9735)) {
        if (buttons & x_ad1aebe6) {
            obj->pos.x--;
        } else {
            obj->pos.x++;
        }
    }
    if (buttons & (x_f7763ed8 | x_b8c91680)) {
        if (buttons & x_f7763ed8) {
            obj->pos.y--;
        } else {
            obj->pos.y++;
        }
    }
    if (buttons & (x_64a28e7d | x_af0e0a9f)) {
        if (buttons & x_64a28e7d) {
            obj->pos.z--;
        } else {
            obj->pos.z++;
        }
    }
    if (buttons & (x_c7089780 | x_29dbff14)) {
        if (buttons & x_c7089780) {
            v0--;
        } else {
            v0++;
        }
    }
    if (buttons & (x_37f8540c | x_ffe9ce36)) {
        if (buttons & x_37f8540c) {
            obj->x_860b579a += 0x10;
        } else {
            obj->x_860b579a -= 0x10;
        }
    }
    if (buttons & (x_84d0a51b | x_b2ae561b)) {
        if (buttons & x_84d0a51b) {
            obj->x_2fa0bbed += 0x10;
        } else {
            obj->x_2fa0bbed -= 0x10;
        }
    }

    if (v0 < 0) {
        v0 = obj->x_904eaf67->x_5b30c492 - 1;
    }
    if (v0 > obj->x_904eaf67->x_5b30c492 - 1) {
        v0 = 0;
    }
    obj->frameCounter = v0;
}

#ifdef NON_MATCHING
s32 x_a2f41f91(s32 x_30bbe547) {
    s32 v1;
    u32 i;
    u32 j;

    v1 = 0;
    for (i = x_c4ddde6d; i < x_edb381f3; i++) {
        j = i;
        if (j == x_ff5073d4 || j == x_e235676f || j == x_968cc9a2) {
            continue;
        }
        if (FALSE) {}
        if (!D_800B6350[x_30bbe547][i]) {
            v1++;
        }
    }

    return v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/pregame/x_a2f41f91.s")
s32 x_a2f41f91(s32 x_30bbe547);
#endif

#ifdef NON_EQUIVALENT
u8 x_7dc12b61(u8 x_30bbe547) {
    u8 x_1be999e5[x_edb381f3];
    s32 pad;
    u8 x_eb1fe45b;
    u8 v1;
    u8 i;

    v1 = 0;
    x_eb1fe45b = x_77831b2c[1 - x_30bbe547].x_eb1fe45b;

    if (D_80049390 != -1 && x_eb1fe45b != D_80049390 && D_80049390 != x_968cc9a2 && D_80049390 != x_ff5073d4) {
        x_eb1fe45b = D_80049390;
        D_80049390 = -1;
        return x_eb1fe45b;
    }

    while (TRUE) {
        for (i = 0; i < x_edb381f3; i++) {
            if (x_eb1fe45b != i || x_eb1fe45b == x_ff5073d4 || x_eb1fe45b == x_968cc9a2) {
                if (i == x_ff5073d4 || i == x_e235676f || i == x_968cc9a2) {
                    continue;
                }
                if (FALSE) {}
                if (!D_800B6350[x_30bbe547][i]) {
                    x_1be999e5[v1++] = i;
                }
            }
        }

        if (v1 == 0) {
            if (!D_800B6350[x_30bbe547][x_eb1fe45b] && x_eb1fe45b != x_ff5073d4) {
                return x_eb1fe45b;
            } else if (!D_800B6350[x_30bbe547][x_968cc9a2]) {
                return x_968cc9a2;
            } else if (!D_800B6350[x_30bbe547][x_ff5073d4] && x_028e5846 >= x_c74743bd) {
                return x_ff5073d4;
            } else {
                return -1;
            }
        }

        if (v1 != 0) {
            return x_1be999e5[gFrameCounter % v1];
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/pregame/x_7dc12b61.s")
u8 x_7dc12b61(u8 x_30bbe547);
#endif

void x_8aee6708(Object *obj) {
    Object *a1;
    Object *x_d16311d7[2];
    Object *x_49781937;
    s16 x_cf10d3eb;
    s16 x_93463df6;
    u8 x_523c079f;
    u8 x_d413f652;

    a1 = obj->x_e2f64c57[1];

    x_cf10d3eb = obj->x_0f4167b4[2]--;
    if (x_cf10d3eb < 0) {
        x_d16311d7[x_83106b21] = x_696804c5[x_83106b21]->x_e2f64c57[4];
        x_d16311d7[x_6f0b3be3] = x_696804c5[x_6f0b3be3]->x_e2f64c57[4];
        x_49781937 = x_696804c5[x_83106b21]->x_e2f64c57[5];

        if (x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) {
            x_93463df6 = (x_5e4e2788 == x_557d3dd6);
            TASK_END(x_696804c5[x_93463df6]->currentTask);
            x_d16311d7[x_93463df6]->x_0f4167b4[7] = 20;
            x_35e81a03(x_696804c5[x_93463df6], x_49781937);
            x_696804c5[1 - x_93463df6]->x_0f4167b4[6] = x_7dc12b61(1 - x_93463df6);
        } else {
            TASK_END(x_696804c5[x_83106b21]->currentTask);
            TASK_END(x_696804c5[x_6f0b3be3]->currentTask);
            x_d16311d7[x_83106b21]->x_0f4167b4[7] = 20;
            x_d16311d7[x_6f0b3be3]->x_0f4167b4[7] = 20;
            x_35e81a03(x_696804c5[x_83106b21], x_49781937);
            x_35e81a03(x_696804c5[x_6f0b3be3], x_49781937);
        }

        TASK_END(obj->currentTask);
        return;
    }

    x_523c079f = x_cf10d3eb / 10;
    x_d413f652 = x_cf10d3eb - x_523c079f * 10;
    obj->frameCounter = x_d413f652;
    a1->frameCounter = x_523c079f;
    obj->currentTask->delay = 60;
}

void x_35e81a03(Object *obj, Object *x_84ff873b) {
    s16 x_30bbe547;

    x_30bbe547 = obj->x_0f4167b4[0];
    x_84ff873b->x_0f4167b4[8]++;

    if (obj->frameCounter >= 5) {
        x_84ff873b->x_0f4167b4[9 + x_30bbe547] = x_77831b2c[x_30bbe547].x_eb1fe45b = obj->frameCounter + 1;
    } else {
        x_84ff873b->x_0f4167b4[9 + x_30bbe547] = x_77831b2c[x_30bbe547].x_eb1fe45b = obj->frameCounter;
    }

    if (x_84ff873b->x_0f4167b4[11] == -1) {
        x_84ff873b->x_0f4167b4[11] = x_30bbe547;
    }
}

s16 x_ff9be353(s16 x_30bbe547) {
    return (u32) (x_77831b2c[x_30bbe547].x_c35c64af * 80 * 0x10000) / 400 / 0x10000;
}

void x_6aa7260b(Object *obj) {
    s16 x_30bbe547;
    s16 buttons;
    Object *a0;
    s16 x_464d68e5;

    x_30bbe547 = obj->x_0f4167b4[0];
    obj->x_0f4167b4[1] = buttons = x_59ce598c[x_30bbe547].buttons;

    if (buttons & x_9cefe76c) {
        x_7e194d55(2, x_a7d9a1e8 != 0 ? 0 : x_30bbe547 + 4);
        x_35e81a03(obj, obj->x_e2f64c57[5]);
        TASK_END(obj->currentTask);
    } else if (buttons & (x_ad1aebe6 | x_fc4a9735)) {
        a0 = obj->x_e2f64c57[9];
        if (x_30bbe547 == x_83106b21 && (buttons & x_ad1aebe6) || x_30bbe547 == x_6f0b3be3 && (buttons & x_fc4a9735)) {
            x_77831b2c[x_30bbe547].x_c35c64af += obj->x_0f4167b4[7];
            if (x_77831b2c[x_30bbe547].x_c35c64af > 400) {
                x_77831b2c[x_30bbe547].x_c35c64af = 400;
                a0->x_0f4167b4[2] = 15;
            }
        } else {
            x_77831b2c[x_30bbe547].x_c35c64af -= obj->x_0f4167b4[7];
            if (x_77831b2c[x_30bbe547].x_c35c64af < 40) {
                x_77831b2c[x_30bbe547].x_c35c64af = 40;
                a0->x_0f4167b4[2] = 15;
            }
        }

        x_464d68e5 = x_ff9be353(x_30bbe547);
        if (x_30bbe547 == x_83106b21) {
            D_8013C234->x_e7f1952a =
                D_8013C234->x_e7f1952a - D_8013C234->x_b88b3756 + D_8013C234->rightS - x_464d68e5 - 8;
            D_8013C234->x_b88b3756 = D_8013C234->rightS - x_464d68e5 - 8;
        } else {
            D_8013C238->rightS = D_8013C238->x_b88b3756 + x_464d68e5;
        }

        if (obj->x_0f4167b4[8]-- < 1) {
            obj->x_0f4167b4[8] = 1;
            if (++obj->x_0f4167b4[7] > 28) {
                obj->x_0f4167b4[7] = 28;
            }
        }
    } else {
        obj->x_0f4167b4[7] = 1;
    }
}

void x_a70125d9(Object *obj, Object *x_84ff873b, Object *x_2092f891) {
    s16 v0;
    s16 x_cf10d3eb;
    u8 x_a8677df7;
    u8 x_523c079f;
    u8 x_d413f652;
    s32 x_6e3cc34e;

    v0 = obj->x_0f4167b4[0];

    if (obj->x_0f4167b4[2] > 0) {
        obj->x_0f4167b4[2]--;
        obj->frameCounter = 0x29 + (x_77831b2c[v0].x_c35c64af == 400);
        x_2092f891->flags |= x_c537cafa;
        x_84ff873b->flags |= x_c537cafa;
        obj->flags &= ~x_c537cafa;
        return;
    }

    x_cf10d3eb = x_77831b2c[v0].x_c35c64af * 100 / 400;
    x_a8677df7 = x_cf10d3eb / 100;
    x_cf10d3eb -= x_a8677df7 * 100;
    x_523c079f = x_cf10d3eb / 10;
    x_d413f652 = x_cf10d3eb - x_523c079f * 10;

    x_2092f891->flags &= ~x_c537cafa;
    x_84ff873b->flags &= ~x_c537cafa;
    obj->flags &= ~x_c537cafa;

    if (!x_a8677df7) {
        x_2092f891->flags |= x_c537cafa;
        if (x_523c079f == 0) {
            x_84ff873b->flags |= x_c537cafa;
        }
    }

    if (!obj->x_0f4167b4[1]) {
        x_2092f891->flags |= x_c537cafa;
        x_84ff873b->flags |= x_c537cafa;
        obj->flags |= x_c537cafa;
    }

    if ((gFrameCounter % 15) == 0) {
        x_6e3cc34e = ((gFrameCounter % 30) == 0);
        obj->x_0f4167b4[1] = x_6e3cc34e;
    }

    obj->frameCounter = 0x1C + x_d413f652;
    x_84ff873b->frameCounter = 0x1C + x_523c079f;
    x_2092f891->frameCounter = 0x1C + x_a8677df7;
}

void x_6e0d3e38(Object *obj) {
    s16 x_b2bb447b;
    Object *v0;
    Object *x_32f1d6e2;
    Object *x_5aee6615;
    Object *x_5bbba600;
    s32 v02;

    x_32f1d6e2 = obj->x_e2f64c57[5];
    x_5aee6615 = obj->x_e2f64c57[6];
    x_5bbba600 = obj->x_e2f64c57[7];
    x_a70125d9(x_32f1d6e2, x_5aee6615, x_5bbba600);

    x_b2bb447b = obj->x_0f4167b4[0];
    v02 = obj->x_0f4167b4[2]--; // reuse required to match
    if (v02 < 0) {
        obj->x_0f4167b4[2] = 15;
        obj->frameCounter = 0x4f - obj->frameCounter;
    }

    if (x_696804c5[x_b2bb447b]->x_0f4167b4[1] & x_9cefe76c) {
        v0 = obj->x_e2f64c57[3];
        v0->flags |= x_f51cb721;
        v0 = obj->x_e2f64c57[4];
        v0->flags |= x_f51cb721;
        x_32f1d6e2->flags |= x_f51cb721;
        x_5aee6615->flags |= x_f51cb721;
        x_5bbba600->flags |= x_f51cb721;
        obj->flags |= x_f51cb721;
    }

    v02 = x_ff9be353(x_b2bb447b);
    if (x_b2bb447b == x_83106b21) {
        obj->pos.x = obj->x_0f4167b4[1] - v02;
    } else {
        obj->pos.x = obj->x_0f4167b4[1] + v02;
    }
}

void x_0362e0e0(Object *obj) {
    s16 s1;
    s16 x_464d68e5;
    x_f0d7e70f x_d65a2f4e = { 11, NULL, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_15702e8a = { 39, x_6e0d3e38, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_f4254db5 = { 28, NULL, 0, 0x1000, "bars.sp2" };
    x_88f11482 x_522f451d[] = { { 78, 220, 0, 0 }, { 248, 220, 0, 0 } };
    x_88f11482 x_d753d975[] = { { 77, 220, 0, 0 }, { 248, 220, 0, 0 } };
    x_88f11482 x_dcab8ab0[] = { { 39, 216, 0, 0 }, { 289, 216, 0, 0 } };
    x_88f11482 x_fd09f53e[] = { { 60, 203, 0, 0 }, { 229, 203, 0, 0 } };
    Object *s2;
    Object *x_2bf9ce78;
    Object *x_7f4af95e;
    Object *s3;
    Object *v0;

    s1 = obj->x_0f4167b4[0];

    s3 = x_12014163(&x_522f451d[s1], &x_d65a2f4e, x_24b231d4);
    v0 = x_12014163(&x_dcab8ab0[s1], &x_15702e8a, x_24b231d4);
    v0->x_0f4167b4[0] = s1;
    v0->x_0f4167b4[3] = s3;
    s3 = x_12014163(&x_d753d975[s1], &x_d65a2f4e, x_24b231d4);
    s3->frameCounter = 15 - s1;
    v0->x_0f4167b4[4] = s3;

    x_464d68e5 = x_ff9be353(s1);
    if (s1 == 0) {
        D_8013C234 = s3->x_904eaf67->x_a34b89cc[15].parts;
        D_8013C234->x_e7f1952a = D_8013C234->x_e7f1952a - D_8013C234->x_b88b3756 + D_8013C234->rightS - x_464d68e5 - 8;
        D_8013C234->x_b88b3756 = D_8013C234->rightS - x_464d68e5 - 8;
        v0->x_0f4167b4[1] = 119;
        v0->pos.x = 119 - x_464d68e5;
    } else {
        D_8013C238 = s3->x_904eaf67->x_a34b89cc[14].parts;
        D_8013C238->rightS = D_8013C238->x_b88b3756 + x_464d68e5;
        v0->x_0f4167b4[1] = 0xD1;
        v0->pos.x = 0xD1 + x_464d68e5;
    }

    s2 = x_12014163(&x_fd09f53e[s1], &x_f4254db5, x_24b231d4);
    x_fd09f53e[s1].x += 10;
    x_2bf9ce78 = x_12014163(&x_fd09f53e[s1], &x_f4254db5, x_24b231d4);
    x_fd09f53e[s1].x += 10;
    x_7f4af95e = x_12014163(&x_fd09f53e[s1], &x_f4254db5, x_24b231d4);
    x_7f4af95e->x_0f4167b4[0] = s1;

    x_a70125d9(x_7f4af95e, x_2bf9ce78, s2);

    v0->x_0f4167b4[5] = x_7f4af95e;
    v0->x_0f4167b4[6] = x_2bf9ce78;
    v0->x_0f4167b4[7] = s2;

    obj->x_0f4167b4[1] = 0;
    obj->x_0f4167b4[9] = x_7f4af95e;
    obj->currentTask->callback = x_6aa7260b;
    obj->currentTask->delay = 20;
}

void x_0f87e747(Object *obj) {
    Object *x_aaadc3e8;
    s16 v1;
    s16 x_30bbe547;

    if (!(x_e30d50d2 & x_e3ff543d)) {
        return;
    }

    x_30bbe547 = obj->x_0f4167b4[0];
    x_aaadc3e8 = obj->x_e2f64c57[5];

    if (!x_77831b2c[1 - x_30bbe547].x_03604d94 && x_aaadc3e8->x_0f4167b4[8] == 0) {
        return;
    }

    if (obj->x_0f4167b4[2]-- > 0) {
        return;
    }

    obj->x_0f4167b4[2] = 15;
    if (obj->frameCounter >= 5) {
        v1 = obj->frameCounter + 1;
    } else {
        v1 = obj->frameCounter;
    }

    if (obj->x_0f4167b4[6] == 9 || obj->x_0f4167b4[6] == 1) {
        v1 = obj->x_0f4167b4[6];
        obj->frameCounter = v1 - (v1 == x_968cc9a2);
    }

    if (v1 == obj->x_0f4167b4[6]) {
        x_7e194d55(2, x_a7d9a1e8 != 0 ? 0 : x_30bbe547 + 4);
        x_35e81a03(obj, x_aaadc3e8);
        x_aaadc3e8 = obj->x_e2f64c57[4];
        x_aaadc3e8->x_0f4167b4[7] = 20;
        TASK_END(obj->currentTask);
        return;
    }

    x_7e194d55(2, 6 + x_30bbe547);

    if (abs(v1 - obj->x_0f4167b4[6]) <= 5) {
        if (v1 < obj->x_0f4167b4[6]) {
            v1++;
            if (v1 == x_e235676f || v1 == x_968cc9a2 || v1 == x_ff5073d4) {
                v1++;
            }
        } else {
            v1--;
            if (v1 == x_e235676f || v1 == x_968cc9a2 || v1 == x_ff5073d4) {
                v1--;
            }
        }
    } else {
        if (v1 < obj->x_0f4167b4[6]) {
            v1--;
            if (v1 == x_e235676f || v1 == x_968cc9a2 || v1 == x_ff5073d4) {
                v1--;
            }
        } else {
            v1++;
            if (v1 == x_e235676f || v1 == x_968cc9a2 || v1 == x_ff5073d4) {
                v1++;
            }
        }
    }

    if (v1 < x_c4ddde6d) {
        v1 = x_379149a4;
    } else if (v1 > x_379149a4) {
        v1 = x_c4ddde6d;
    }

    if (v1 >= x_e235676f) {
        obj->frameCounter = v1 - 1;
    } else {
        obj->frameCounter = v1;
    }
}

void x_34648a7a(Object *obj) {
    s16 a1;
    s16 v0;
    s16 v1;
    s32 x_6e3cc34e;
    s16 a3;
    s16 x_cf10d3eb;

    a3 = obj->x_0f4167b4[0];
    a1 = obj->x_0f4167b4[1];

    if (x_5e4e2788 == x_79c2dc5b) {
        Object *x_aaadc3e8 = obj->x_e2f64c57[5];
        if (a3 != x_08051143) {
            if (x_aaadc3e8->x_0f4167b4[8] == 0) {
                obj->x_0f4167b4[1] = 0x800;
                obj->x_0f4167b4[2] = 60;
                return;
            }
        }
        x_6e3cc34e = x_08051143;
        obj->x_0f4167b4[1] = v1 = x_59ce598c[x_6e3cc34e].buttons;
    } else {
        obj->x_0f4167b4[1] = v1 = x_59ce598c[a3].buttons;
    }

    x_cf10d3eb = obj->x_0f4167b4[2]--;
    if (x_cf10d3eb <= 0 || v1 != a1) {
        obj->x_0f4167b4[2] = 15;
        if (v1 & x_9cefe76c) {
            Object *x_aaadc3e8;
            x_7e194d55(2, x_a7d9a1e8 != 0 ? 0 : a3 + 4);
            x_aaadc3e8 = obj->x_e2f64c57[4];
            x_aaadc3e8->x_0f4167b4[7] = 20;

            if (x_5e4e2788 == x_96f25e0a) {
                x_0362e0e0(obj);
            } else {
                x_35e81a03(obj, obj->x_e2f64c57[5]);
                if (x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) {
                    x_696804c5[1 - a3]->x_0f4167b4[6] = x_7dc12b61(1 - a3);
                }
                TASK_END(obj->currentTask);
            }
        } else if (v1 & (x_ad1aebe6 | x_fc4a9735)) {
            x_7e194d55(2, 6 + a3);

            v0 = obj->frameCounter;
            if (v1 & x_ad1aebe6) {
                v0--;
            } else {
                v0++;
            }

            if (!x_5c207a56 && v0 == 8 || !x_aee302fc && v0 == 1) {
                if (v1 & x_ad1aebe6) {
                    v0--;
                } else {
                    v0++;
                }
            }

            if (v0 < 0) {
                v0 = 9;
            } else if (v0 > 9) {
                v0 = 0;
            }

            obj->frameCounter = v0;
        }
    }
}

void x_044d3222(Object *obj) {
    if (obj->x_0f4167b4[7] != 0) {
        if (obj->x_0f4167b4[8]-- == 0) {
            obj->frameCounter = obj->x_0f4167b4[0] * 4 - obj->frameCounter + 171;
            obj->x_0f4167b4[8] = -254 - (obj->x_0f4167b4[0] * 2 - obj->frameCounter) * 3;
        }

        if (--obj->x_0f4167b4[7] == 0) {
            obj->frameCounter = obj->x_0f4167b4[0] * 2 + 86;
            TASK_END(obj->currentTask);
        }
    }
}

void x_6fa3f96e(Object *obj) {
    if (obj->x_0f4167b4[8] < 2) {
        return;
    }

    if (obj->x_0f4167b4[8] == 2) {
        obj->x_0f4167b4[8] = 3;
        obj->currentTask->delay = 10;
        x_696804c5[0]->flags |= x_5a44854c;
        x_696804c5[1]->flags |= x_5a44854c;
        return;
    }

    if (obj->x_0f4167b4[8] == 3) {
        obj->x_0f4167b4[8] = 4;
        x_696804c5[0]->flags |= x_5a44854c;
        x_696804c5[1]->flags |= x_5a44854c;
        obj->flags &= ~x_c537cafa;
        obj->currentTask->delay = 20;
        return;
    }

    x_77831b2c[x_83106b21].x_fb21ca8c = x_77831b2c[x_6f0b3be3].x_fb21ca8c = 0;
    x_77831b2c[x_83106b21].x_eb1fe45b = obj->x_0f4167b4[9];
    x_77831b2c[x_6f0b3be3].x_eb1fe45b = obj->x_0f4167b4[10];
    x_77831b2c[x_83106b21].x_b2b764b3 = x_77831b2c[x_6f0b3be3].x_b2b764b3 = 0;
    x_77831b2c[x_83106b21].x_c35c64af &= ~3;
    x_77831b2c[x_6f0b3be3].x_c35c64af &= ~3;
    if (0) {} // required to match
    x_e30d50d2 |= x_bee364e0;

    if (x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) {
        x_e38a6e19 = x_77831b2c[x_6db66fc3].x_eb1fe45b + x_a98e3fb7;
        if (x_77831b2c[x_83106b21].x_7d8e7a6f + x_77831b2c[x_6f0b3be3].x_7d8e7a6f == 0) {
            x_e38a6e19 = x_77831b2c[1 - x_6db66fc3].x_eb1fe45b + x_d61e86e9;
            x_77831b2c[1 - x_6db66fc3].x_fb21ca8c = 1;
        } else {
            x_77831b2c[x_6db66fc3].x_fb21ca8c = 1;
        }
        if (x_77831b2c[x_6db66fc3].x_eb1fe45b == x_ff5073d4) {
            x_e38a6e19 = x_3509e8f6;
        }
    } else {
        x_e38a6e19 = x_77831b2c[obj->x_0f4167b4[11]].x_eb1fe45b + x_a98e3fb7;
        x_77831b2c[obj->x_0f4167b4[11]].x_fb21ca8c++;
    }

    TASK_END(obj->currentTask);
}

void x_7447fdfb(Object *obj) {
    s16 x_30bbe547;
    Object *x_e9508efc;

    if (obj->x_0f4167b4[2]-- < 0) {
        obj->x_0f4167b4[2] = 15;
        obj->frameCounter = obj->x_0f4167b4[1] - obj->frameCounter;
    }

    x_30bbe547 = obj->x_0f4167b4[0];
    x_e9508efc = x_696804c5[x_30bbe547]->x_e2f64c57[4];
    if (x_e9508efc->x_0f4167b4[7]) {
        obj->flags |= x_f51cb721;
    }
}

void x_95e711cc(Object *obj) {
    if (obj->x_0f4167b4[x_a44625a6]-- < 0) {
        obj->x_0f4167b4[x_a44625a6] = 15;
        obj->frameCounter = obj->x_0f4167b4[x_82e2e1db] - obj->frameCounter;
    }

    if (x_59ce598c[obj->x_0f4167b4[x_0140ad12]].buttons & x_9cefe76c) {
        obj->frameCounter = x_aaa2c518 - 2 * obj->x_0f4167b4[0];
        obj->x_0f4167b4[x_82e2e1db] = obj->frameCounter * 2 + 1;
        obj->pos.x = 245 - obj->x_0f4167b4[x_0140ad12] * 167;

        obj->x_0f4167b4[x_0140ad12] = 1 - obj->x_0f4167b4[x_0140ad12];
        obj->currentTask->callback = x_7447fdfb;
    }
}

void x_2c1b660c(void) {
    Object *x_523933cc[2];
    Object *x_fd096fa8;
    Object *obj;
    s16 x_13d65ace;
    Object *x_994c79b3;
    x_f0d7e70f x_c3be5f96 = { x_0857a6f7, x_34648a7a, 0, 0x1000, "grpp1.sp2" };
    x_f0d7e70f x_a8ee65ba = { x_fa2a4086, x_34648a7a, 0, 0x1000, "grpp2.sp2" };
    x_f0d7e70f x_37539a8c = { x_bdf6d812, x_044d3222, 0, 0x1000, "options2.sp2" };
    x_f0d7e70f x_b610af55 = { x_76b8b516, x_044d3222, 0, 0x1000, "options2.sp2" };
    x_f0d7e70f x_5601faec = { 26, x_6fa3f96e, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_652f5000 = { 0, x_8aee6708, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_4fea1147 = { 6, NULL, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_8fcab22c = { x_35414b8d, x_7447fdfb, 0, 0x1000, "options2.sp2" };
    x_f0d7e70f x_3bfdbaa4 = { x_b4568ba1, x_95e711cc, 0, 0x1000, "practice.sp2" };
    x_f0d7e70f x_93121a84 = { x_823ba8a7, x_95e711cc, 0, 0x1000, "practice.sp2" };
    x_88f11482 x_5c2a3a42 = { 84, 129, 0, 0 };
    x_88f11482 x_0cbc7c1c = { 252, 129, 0, 0 };
    x_88f11482 x_a3f0c785 = { 56, 60, 0, 0 };
    x_88f11482 x_3dfff383 = { 224, 60, 0, 0 };
    x_88f11482 x_3eeec712 = { 162, 130, 0, 0 };
    x_88f11482 x_9d69f44f = { 171, 75, 0, 0 };
    x_88f11482 x_9e7fdb6b = { 158, 75, 0, 0 };
    x_88f11482 x_4a1fd4d1 = { 82, 217, 0, 0 };
    x_88f11482 x_331089fa = { 251, 217, 0, 0 };
    x_88f11482 x_2a89e429 = { 78, 217, 0, 0 };
    x_88f11482 x_081c4eef = { 245, 217, 0, 0 };
    s16 x_c16a42f3, x_fb97b65c;
    s32 unused;

    x_c16a42f3 = x_77831b2c[x_83106b21].x_eb1fe45b;
    x_fb97b65c = x_77831b2c[x_6f0b3be3].x_eb1fe45b;

    if (x_c16a42f3 == x_ff5073d4 && x_aee302fc == 0) {
        x_c16a42f3 = x_537ef8a7;
    }
    if (x_fb97b65c == x_ff5073d4 && x_aee302fc == 0) {
        x_fb97b65c = x_537ef8a7;
    }
    if (x_c16a42f3 == x_968cc9a2 && !x_5c207a56) {
        x_c16a42f3 = x_c4ddde6d;
    }
    if (x_fb97b65c == x_968cc9a2 && !x_5c207a56) {
        x_fb97b65c = x_c4ddde6d;
    }

    if (x_c16a42f3 >= x_e235676f) {
        x_c16a42f3--;
    }
    if (x_fb97b65c >= x_e235676f) {
        x_fb97b65c--;
    }

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    D_8008012C |= x_8df87377;
    x_e30d50d2 |= x_86c5bc33;

    x_0928eec2("/plyrsel/plyrsel", x_24b231d4);
    x_0928eec2("/plyrsel/music", x_24b231d4);

    x_e30d50d2 |= x_3b812e44;

    switch (x_5e4e2788) {
        case x_e483bf48:
            obj = x_12014163(&x_4a1fd4d1, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = x_83106b21;
            obj->x_0f4167b4[1] = 167;
            x_0928eec2("/plyrsel/select", x_24b231d4);
            break;
        case x_557d3dd6:
            obj = x_12014163(&x_331089fa, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = x_6f0b3be3;
            obj->x_0f4167b4[1] = 167;
            x_0928eec2("/plyrsel/select", x_24b231d4);
            break;
        case x_96f25e0a:
        case x_3658fb97:
        case x_a5f164ca:
            obj = x_12014163(&x_4a1fd4d1, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = 0;
            obj->x_0f4167b4[1] = 167;
            obj = x_12014163(&x_331089fa, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = 1;
            obj->x_0f4167b4[1] = 167;
            x_0928eec2("/plyrsel/select2", x_24b231d4);
            break;
        case x_79c2dc5b:
            if (x_08051143 == x_83106b21) {
                obj = x_12014163(&x_2a89e429, &x_3bfdbaa4, x_24b231d4);
                obj->x_0f4167b4[x_0140ad12] = x_83106b21;
                obj->x_0f4167b4[x_82e2e1db] = x_b4568ba1 * 2 + 1;
            } else {
                obj = x_12014163(&x_081c4eef, &x_93121a84, x_24b231d4);
                obj->x_0f4167b4[x_0140ad12] = x_6f0b3be3;
                obj->x_0f4167b4[x_82e2e1db] = x_823ba8a7 * 2 + 1;
            }
            x_0928eec2("/plyrsel/select3", x_24b231d4);
            break;
    }

    x_a0e73601("select", 0, 8, 0, 0, x_96186256, x_24b231d4);

    x_696804c5[0] = x_12014163(&x_5c2a3a42, &x_c3be5f96, x_24b231d4);
    x_696804c5[0]->x_0f4167b4[0] = x_83106b21;
    x_696804c5[0]->frameCounter = x_c16a42f3;
    x_696804c5[0]->currentTask->delay = 20;

    x_696804c5[1] = x_12014163(&x_0cbc7c1c, &x_a8ee65ba, x_24b231d4);
    x_696804c5[1]->x_0f4167b4[0] = x_6f0b3be3;
    x_696804c5[1]->frameCounter = x_fb97b65c;
    x_696804c5[1]->currentTask->delay = 20;

    x_523933cc[0] = x_12014163(&x_a3f0c785, &x_37539a8c, x_24b231d4);
    x_523933cc[0]->x_0f4167b4[0] = x_83106b21;

    x_523933cc[1] = x_12014163(&x_3dfff383, &x_b610af55, x_24b231d4);
    x_523933cc[1]->x_0f4167b4[0] = x_6f0b3be3;

    x_fd096fa8 = x_12014163(&x_3eeec712, &x_5601faec, x_24b231d4);
    x_fd096fa8->flags |= x_c537cafa;
    x_fd096fa8->x_0f4167b4[11] = -1;
    x_fd096fa8->flags |= x_5a44854c;

    x_994c79b3 = x_12014163(&x_9e7fdb6b, &x_4fea1147, x_24b231d4);
    obj = x_12014163(&x_9d69f44f, &x_652f5000, x_24b231d4);
    obj->x_0f4167b4[2] = 60;
    obj->x_e2f64c57[1] = x_994c79b3;
    obj->x_e2f64c57[5] = x_fd096fa8;

    x_696804c5[0]->x_e2f64c57[4] = x_523933cc[0];
    x_696804c5[0]->x_e2f64c57[5] = x_fd096fa8;
    x_696804c5[1]->x_e2f64c57[4] = x_523933cc[1];
    x_696804c5[1]->x_e2f64c57[5] = x_fd096fa8;

    switch (x_5e4e2788) {
        case x_e483bf48:
        case x_557d3dd6:
            x_13d65ace = (x_5e4e2788 == x_557d3dd6);
            x_696804c5[1 - x_13d65ace]->currentTask->callback = x_0f87e747;
            x_696804c5[1 - x_13d65ace]->currentTask->delay = 0;
            x_696804c5[1 - x_13d65ace]->currentTask->flags = TASK_RUNNABLE;

            if (x_77831b2c[x_13d65ace].x_b2b764b3 != 0) {
                x_696804c5[1 - x_13d65ace]->x_0f4167b4[6] = x_7dc12b61(1 - x_13d65ace);
                TASK_END(x_696804c5[x_13d65ace]->currentTask);
                x_523933cc[x_13d65ace]->x_0f4167b4[7] = 20;
                x_fd096fa8->x_0f4167b4[8] = 1;
                x_fd096fa8->x_0f4167b4[9 + x_13d65ace] = x_77831b2c[x_13d65ace].x_eb1fe45b;
            }
            break;
        case x_3658fb97:
            x_696804c5[0]->currentTask->callback = x_0f87e747;
            x_696804c5[0]->currentTask->delay = 0;
            x_696804c5[0]->currentTask->flags = TASK_RUNNABLE;
            x_696804c5[0]->x_0f4167b4[6] = x_7dc12b61(0);

            x_696804c5[1]->currentTask->callback = x_0f87e747;
            x_696804c5[1]->currentTask->delay = 0;
            x_696804c5[1]->currentTask->flags = TASK_RUNNABLE;
            x_696804c5[1]->x_0f4167b4[6] = x_7dc12b61(1);
            break;
        case x_96f25e0a:
        case x_79c2dc5b:
        case x_a5f164ca:
            break;
    }

    x_82df7d23();
    x_ad9889cf(x_24b231d4);
}

void x_d74e99e0(s16 x_30bbe547, u16 x_1819574a, u16 x_6388adb6) {
    x_5c207a56 = x_1819574a;
    x_aee302fc = x_6388adb6;
}

void x_9f82ca8d(s16 x_05e00b01, s16 x_30bbe547) {
    x_e30d50d2 |= x_bee364e0;
    x_e38a6e19 = x_fa31c524;

    x_77831b2c[x_30bbe547].x_eb1fe45b = x_05e00b01;
    x_77831b2c[x_30bbe547].x_03604d94 = FALSE;
    x_77831b2c[x_30bbe547].x_fb21ca8c = 0;

    x_77831b2c[1 - x_30bbe547].x_eb1fe45b = x_ff5073d4;
    x_77831b2c[1 - x_30bbe547].x_03604d94 = TRUE;
    x_77831b2c[1 - x_30bbe547].x_fb21ca8c = 1;

    x_49d7310c(x_30bbe547 + x_e483bf48);
}

void x_47955556(s16 x_30bbe547, u16 x_05e00b01, u16 x_2092f891) {
    x_9f82ca8d(x_05e00b01, x_30bbe547);
}

void x_5b38dd2f(s16 x_30bbe547, u16 x_84ff873b, u16 x_2092f891) {
    x_9f82ca8d(x_ff5073d4, x_30bbe547);
    x_e38a6e19 = x_3509e8f6;
}

void x_2cd57f74(s16 x_30bbe547, u16 x_84ff873b, u16 x_2092f891) {
    x_77831b2c[x_83106b21].x_cc57155e = x_77831b2c[x_6f0b3be3].x_cc57155e = x_84ff873b;
}

void x_7caf7d71(s16 x_30bbe547, u16 x_84ff873b, u16 x_2092f891) {
    s16 i;

    x_77831b2c[1 - x_30bbe547].x_fb21ca8c = 1;
    x_77831b2c[x_30bbe547].x_fb21ca8c = 0;
    x_77831b2c[x_30bbe547].x_03604d94 = FALSE;
    x_77831b2c[1 - x_30bbe547].x_03604d94 = TRUE;
    D_800801F1 = TRUE;

    for (i = 0; i < 11; i++) {
        D_800B6350[0][i] = D_800B6350[1][i] = 0;
    }

    x_e30d50d2 |= x_bee364e0;
    x_49d7310c(x_30bbe547 + x_e483bf48);
}

void x_d8d91897(s16 x_30bbe547, u16 x_05e00b01, u16 x_7cedc3fb) {
    x_77831b2c[1 - x_30bbe547].x_eb1fe45b = x_05e00b01;
    x_77831b2c[1 - x_30bbe547].x_03604d94 = TRUE;
    x_e38a6e19 = x_7cedc3fb;
}

u16 x_872278ef[] = { x_af0e0a9f, x_64a28e7d, x_84d0a51b, x_b2ae561b, x_ffe9ce36, x_37f8540c, x_d0d35cc6 };
u16 x_af558c92[] = { x_29dbff14, x_c7089780, x_64a28e7d, x_af0e0a9f, x_b2ae561b, x_84d0a51b, x_d0d35cc6 };

u16 x_da3e5ada[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_64a28e7d, x_64a28e7d, x_ffe9ce36, x_d0d35cc6 };
u16 x_2b6f9733[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_64a28e7d, x_64a28e7d, x_84d0a51b, x_d0d35cc6 };
u16 x_7eaa6bad[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_64a28e7d, x_64a28e7d, x_37f8540c, x_d0d35cc6 };
u16 x_e694052f[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_64a28e7d, x_64a28e7d, x_b2ae561b, x_d0d35cc6 };
u16 x_49a7f1c5[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_64a28e7d, x_64a28e7d, x_c7089780, x_d0d35cc6 };
u16 x_0f81075a[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_64a28e7d, x_64a28e7d, x_29dbff14, x_d0d35cc6 };
u16 x_42d5a2ea[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_af0e0a9f, x_af0e0a9f, x_ffe9ce36, x_d0d35cc6 };
u16 x_b6970c24[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_af0e0a9f, x_af0e0a9f, x_84d0a51b, x_d0d35cc6 };
u16 x_f9cc0201[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_af0e0a9f, x_af0e0a9f, x_37f8540c, x_d0d35cc6 };
u16 x_a8689ca4[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_af0e0a9f, x_af0e0a9f, x_b2ae561b, x_d0d35cc6 };

u16 D_8004A114[] = { x_f7763ed8, x_ffe9ce36, x_64a28e7d, x_fc4a9735, x_b8c91680,
                     x_c7089780, x_c7089780, x_c7089780, x_84d0a51b, x_d0d35cc6 };

u16 D_8004A128[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_c7089780,
                     x_c7089780, x_c7089780, x_c7089780, x_d0d35cc6 };
u16 D_8004A13C[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_ffe9ce36, x_d0d35cc6 };
u16 D_8004A14C[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_84d0a51b, x_d0d35cc6 };
u16 D_8004A15C[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_37f8540c, x_d0d35cc6 };
u16 D_8004A16C[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_b2ae561b, x_d0d35cc6 };
u16 D_8004A17C[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_29dbff14, x_ffe9ce36, x_d0d35cc6 };
u16 D_8004A18C[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_29dbff14, x_84d0a51b, x_d0d35cc6 };
u16 D_8004A19C[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_29dbff14, x_37f8540c, x_d0d35cc6 };
u16 D_8004A1AC[] = { x_ad1aebe6, x_84d0a51b, x_ffe9ce36, x_84d0a51b, x_29dbff14, x_29dbff14, x_b2ae561b, x_d0d35cc6 };

u16 D_8004A1BC[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b, x_c7089780, x_ffe9ce36, x_d0d35cc6 };
u16 D_8004A1CC[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b,
                     x_c7089780, x_c7089780, x_84d0a51b, x_d0d35cc6 };
u16 D_8004A1E0[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b,
                     x_c7089780, x_c7089780, x_37f8540c, x_d0d35cc6 };
u16 D_8004A1F4[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b,
                     x_c7089780, x_c7089780, x_b2ae561b, x_d0d35cc6 };
u16 D_8004A208[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b,
                     x_c7089780, x_c7089780, x_29dbff14, x_d0d35cc6 };
u16 D_8004A21C[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b,
                     x_c7089780, x_c7089780, x_c7089780, x_ffe9ce36, x_d0d35cc6 };
u16 D_8004A230[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b,
                     x_c7089780, x_c7089780, x_c7089780, x_84d0a51b, x_d0d35cc6 };
u16 D_8004A244[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b,
                     x_c7089780, x_c7089780, x_c7089780, x_37f8540c, x_d0d35cc6 };
u16 D_8004A258[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b, x_c7089780,
                     x_c7089780, x_c7089780, x_c7089780, x_b2ae561b, x_d0d35cc6 };
u16 D_8004A270[] = { x_c7089780, x_84d0a51b, x_64a28e7d, x_64a28e7d, x_84d0a51b, x_c7089780,
                     x_c7089780, x_c7089780, x_c7089780, x_29dbff14, x_d0d35cc6 };

x_64b038aa x_e521e2f2[] = { { D_8004A114, x_5b38dd2f, 0, 0 },
                            { x_872278ef, x_d74e99e0, TRUE, FALSE },
                            { x_af558c92, x_d74e99e0, TRUE, TRUE },
                            { x_da3e5ada, x_47955556, 0, 0 },
                            { x_2b6f9733, x_47955556, 2, 0 },
                            { x_7eaa6bad, x_47955556, 3, 0 },
                            { x_e694052f, x_47955556, 4, 0 },
                            { x_49a7f1c5, x_47955556, 6, 0 },
                            { x_0f81075a, x_47955556, 7, 0 },
                            { x_42d5a2ea, x_47955556, 8, 0 },
                            { x_b6970c24, x_47955556, 9, 0 },
                            { x_f9cc0201, x_47955556, 10, 0 },
                            { x_a8689ca4, x_47955556, 1, 0 },
                            { D_8004A13C, x_2cd57f74, 0, 0 },
                            { D_8004A14C, x_2cd57f74, 1, 0 },
                            { D_8004A15C, x_2cd57f74, 2, 0 },
                            { D_8004A16C, x_2cd57f74, 3, 0 },
                            { D_8004A17C, x_2cd57f74, 4, 0 },
                            { D_8004A18C, x_2cd57f74, 5, 0 },
                            { D_8004A19C, x_2cd57f74, 6, 0 },
                            { D_8004A1AC, x_2cd57f74, 7, 0 },
                            { D_8004A1BC, x_d8d91897, x_c4ddde6d, x_a98e3fb7 },
                            { D_8004A1CC, x_d8d91897, x_ff5073d4, x_1a4de9e0 },
                            { D_8004A1E0, x_d8d91897, x_73cf9ceb, x_3b539526 },
                            { D_8004A1F4, x_d8d91897, x_6a049984, x_8774b75f },
                            { D_8004A208, x_d8d91897, x_537ef8a7, x_04d94c4d },
                            { D_8004A21C, x_d8d91897, x_b52da315, x_2a9c0615 },
                            { D_8004A230, x_d8d91897, x_13ed828f, x_9cb4f0a0 },
                            { D_8004A244, x_d8d91897, x_12e7e1dc, x_ed0b2237 },
                            { D_8004A258, x_d8d91897, x_968cc9a2, x_4ad48df4 },
                            { D_8004A270, x_d8d91897, x_379149a4, x_b2483e0d },
                            { D_8004A128, x_7caf7d71, 0, 0 },
                            { NULL, NULL, 0, 0 } };

s16 x_da6f2a83(u16 *x_2bb7a7fd, u16 *x_04faa85c) {
    s16 length = 0;

    while (*x_2bb7a7fd == *x_04faa85c) {
        if (*x_04faa85c == x_d0d35cc6 || *x_2bb7a7fd == x_d0d35cc6) {
            break;
        }
        x_2bb7a7fd++;
        x_04faa85c++;
        length++;
    }

    return length;
}

void x_81cbe10a(x_5aaa1a5b *state, s16 x_30bbe547) {
    x_64b038aa *x_3a1b45d4 = state->x_3a1b45d4;

    state->x_e4b35e9b++;
    if (x_3a1b45d4->sequence[state->x_e4b35e9b] == x_d0d35cc6) {
        x_7e194d55(2, 9);
        x_3a1b45d4->handler(x_30bbe547, x_3a1b45d4->x_273c58c6, x_3a1b45d4->x_08455b9a);
        state->x_3a1b45d4 = NULL;
        state->x_e4b35e9b = 0;
    }
}

void x_778bd81c(x_5aaa1a5b *state, s16 x_30bbe547) {
    u16 x_f3756179;
    x_64b038aa *x_9eaf6155;
    x_64b038aa *ptr;
    s32 unused;

    if (!x_59ce598c[x_30bbe547].x_c4397934) {
        return;
    }
    x_f3756179 = x_59ce598c[x_30bbe547].x_f3756179;
    if (!x_f3756179) {
        return;
    }

    if (x_f3756179 & (x_f7763ed8 | x_b8c91680 | x_ad1aebe6 | x_fc4a9735 | x_37f8540c)) {
        if (state->x_30f758ad == x_f3756179) {
            x_59ce598c[x_30bbe547].x_c4397934 = FALSE;
            return;
        }
        state->x_30f758ad = x_f3756179;
    }

    x_59ce598c[x_30bbe547].x_c4397934 = FALSE;
    x_9eaf6155 = state->x_3a1b45d4;
    if (x_9eaf6155 != NULL) {
        if (x_f3756179 == x_9eaf6155->sequence[state->x_e4b35e9b]) {
            x_81cbe10a(state, x_30bbe547);
            return;
        }

        for (ptr = x_9eaf6155 + 1; ptr->sequence != NULL; ptr++) {
            if (x_da6f2a83(x_9eaf6155->sequence, ptr->sequence) == state->x_e4b35e9b &&
                x_f3756179 == ptr->sequence[state->x_e4b35e9b]) {
                state->x_3a1b45d4 = ptr;
                x_81cbe10a(state, x_30bbe547);
                return;
            }
        }
        x_59ce598c[x_30bbe547].x_c4397934 = TRUE;
        if (0) {} // required to match

        state->x_3a1b45d4 = NULL;
        state->x_e4b35e9b = FALSE;
        state->x_30f758ad = 0;
        return;
    }

    for (x_9eaf6155 = x_e521e2f2; x_9eaf6155->sequence != NULL; x_9eaf6155++) {
        if (x_9eaf6155->sequence[0] == x_f3756179) {
            state->x_3a1b45d4 = x_9eaf6155;
            state->x_e4b35e9b = 1;
            return;
        }
    }
}

void x_8daf2444(Object *obj) {
    x_778bd81c((x_5aaa1a5b *) &obj->x_0f4167b4[0], x_83106b21);
    x_778bd81c((x_5aaa1a5b *) &obj->x_0f4167b4[8], x_6f0b3be3);
}
