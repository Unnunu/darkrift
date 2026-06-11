#include "common.h"
#include "sprite_ids.h"
#include "task.h"

#define x_0140ad12 0
#define x_82e2e1db 1
#define x_a44625a6 2

#define x_d0d35cc6 0xFFFF

typedef struct CheatEntry {
    /* 0x00 */ u16 *sequence;
    /* 0x04 */ void (*handler)(s16, u16, u16);
    /* 0x08 */ s16 param1;
    /* 0x0A */ s16 param2;
} CheatEntry; // size = 0xC

typedef struct CheatState {
    /* 0x00 */ CheatEntry *currentEntry;
    /* 0x04 */ s32 stepIndex;
    /* 0x08 */ s32 lastButton;
} CheatState;

extern s16 x_5e4e2788;
extern s16 D_80049390;
extern x_425d6ed3 *sHealthPartL;
extern x_425d6ed3 *sHealthPartR;

u8 sSonorkUnlocked = FALSE;
u8 sDemitronUnlocked = FALSE;

Object *sPlayerCursorObj[2];
u32 sLastWinnerIdx;

void char_select_confirm(Object *obj, Object *x_84ff873b);

void debug_model_edit(Object *obj) {
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
s32 char_select_count_avail(s32 x_30bbe547) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/pregame/char_select_count_avail.s")
s32 char_select_count_avail(s32 x_30bbe547);
#endif

#ifdef NON_EQUIVALENT
u8 char_select_random(u8 x_30bbe547) {
    u8 x_1be999e5[x_edb381f3];
    s32 pad;
    u8 x_eb1fe45b;
    u8 v1;
    u8 i;

    v1 = 0;
    x_eb1fe45b = gWadCondLoad[1 - x_30bbe547].x_eb1fe45b;

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
#pragma GLOBAL_ASM("asm/nonmatchings/pregame/char_select_random.s")
u8 char_select_random(u8 x_30bbe547);
#endif

void char_select_countdown2(Object *obj) {
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
        x_d16311d7[x_83106b21] = sPlayerCursorObj[x_83106b21]->x_e2f64c57[4];
        x_d16311d7[x_6f0b3be3] = sPlayerCursorObj[x_6f0b3be3]->x_e2f64c57[4];
        x_49781937 = sPlayerCursorObj[x_83106b21]->x_e2f64c57[5];

        if (x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) {
            x_93463df6 = (x_5e4e2788 == x_557d3dd6);
            TASK_END(sPlayerCursorObj[x_93463df6]->currentTask);
            x_d16311d7[x_93463df6]->x_0f4167b4[7] = 20;
            char_select_confirm(sPlayerCursorObj[x_93463df6], x_49781937);
            sPlayerCursorObj[1 - x_93463df6]->x_0f4167b4[6] = char_select_random(1 - x_93463df6);
        } else {
            TASK_END(sPlayerCursorObj[x_83106b21]->currentTask);
            TASK_END(sPlayerCursorObj[x_6f0b3be3]->currentTask);
            x_d16311d7[x_83106b21]->x_0f4167b4[7] = 20;
            x_d16311d7[x_6f0b3be3]->x_0f4167b4[7] = 20;
            char_select_confirm(sPlayerCursorObj[x_83106b21], x_49781937);
            char_select_confirm(sPlayerCursorObj[x_6f0b3be3], x_49781937);
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

void char_select_confirm(Object *obj, Object *x_84ff873b) {
    s16 x_30bbe547;

    x_30bbe547 = obj->x_0f4167b4[0];
    x_84ff873b->x_0f4167b4[8]++;

    if (obj->frameCounter >= 5) {
        x_84ff873b->x_0f4167b4[9 + x_30bbe547] = gWadCondLoad[x_30bbe547].x_eb1fe45b = obj->frameCounter + 1;
    } else {
        x_84ff873b->x_0f4167b4[9 + x_30bbe547] = gWadCondLoad[x_30bbe547].x_eb1fe45b = obj->frameCounter;
    }

    if (x_84ff873b->x_0f4167b4[11] == -1) {
        x_84ff873b->x_0f4167b4[11] = x_30bbe547;
    }
}

s16 handicap_health_to_width(s16 x_30bbe547) {
    return (u32) (gWadCondLoad[x_30bbe547].x_c35c64af * 80 * 0x10000) / 400 / 0x10000;
}

void handicap_input(Object *obj) {
    s16 x_30bbe547;
    s16 buttons;
    Object *a0;
    s16 x_464d68e5;

    x_30bbe547 = obj->x_0f4167b4[0];
    obj->x_0f4167b4[1] = buttons = x_59ce598c[x_30bbe547].buttons;

    if (buttons & x_9cefe76c) {
        audio_sfx_play(2, sAudioMuted != 0 ? 0 : x_30bbe547 + 4);
        char_select_confirm(obj, obj->x_e2f64c57[5]);
        TASK_END(obj->currentTask);
    } else if (buttons & (x_ad1aebe6 | x_fc4a9735)) {
        a0 = obj->x_e2f64c57[9];
        if (x_30bbe547 == x_83106b21 && (buttons & x_ad1aebe6) || x_30bbe547 == x_6f0b3be3 && (buttons & x_fc4a9735)) {
            gWadCondLoad[x_30bbe547].x_c35c64af += obj->x_0f4167b4[7];
            if (gWadCondLoad[x_30bbe547].x_c35c64af > 400) {
                gWadCondLoad[x_30bbe547].x_c35c64af = 400;
                a0->x_0f4167b4[2] = 15;
            }
        } else {
            gWadCondLoad[x_30bbe547].x_c35c64af -= obj->x_0f4167b4[7];
            if (gWadCondLoad[x_30bbe547].x_c35c64af < 40) {
                gWadCondLoad[x_30bbe547].x_c35c64af = 40;
                a0->x_0f4167b4[2] = 15;
            }
        }

        x_464d68e5 = handicap_health_to_width(x_30bbe547);
        if (x_30bbe547 == x_83106b21) {
            sHealthPartL->x_e7f1952a =
                sHealthPartL->x_e7f1952a - sHealthPartL->x_b88b3756 + sHealthPartL->rightS - x_464d68e5 - 8;
            sHealthPartL->x_b88b3756 = sHealthPartL->rightS - x_464d68e5 - 8;
        } else {
            sHealthPartR->rightS = sHealthPartR->x_b88b3756 + x_464d68e5;
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

void handicap_digit_render(Object *obj, Object *x_84ff873b, Object *x_2092f891) {
    s16 v0;
    s16 x_cf10d3eb;
    u8 x_a8677df7;
    u8 x_523c079f;
    u8 x_d413f652;
    s32 x_6e3cc34e;

    v0 = obj->x_0f4167b4[0];

    if (obj->x_0f4167b4[2] > 0) {
        obj->x_0f4167b4[2]--;
        obj->frameCounter = 0x29 + (gWadCondLoad[v0].x_c35c64af == 400);
        x_2092f891->flags |= x_c537cafa;
        x_84ff873b->flags |= x_c537cafa;
        obj->flags &= ~x_c537cafa;
        return;
    }

    x_cf10d3eb = gWadCondLoad[v0].x_c35c64af * 100 / 400;
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

void handicap_refresh(Object *obj) {
    s16 x_b2bb447b;
    Object *v0;
    Object *x_32f1d6e2;
    Object *x_5aee6615;
    Object *x_5bbba600;
    s32 v02;

    x_32f1d6e2 = obj->x_e2f64c57[5];
    x_5aee6615 = obj->x_e2f64c57[6];
    x_5bbba600 = obj->x_e2f64c57[7];
    handicap_digit_render(x_32f1d6e2, x_5aee6615, x_5bbba600);

    x_b2bb447b = obj->x_0f4167b4[0];
    v02 = obj->x_0f4167b4[2]--; // reuse required to match
    if (v02 < 0) {
        obj->x_0f4167b4[2] = 15;
        obj->frameCounter = 0x4f - obj->frameCounter;
    }

    if (sPlayerCursorObj[x_b2bb447b]->x_0f4167b4[1] & x_9cefe76c) {
        v0 = obj->x_e2f64c57[3];
        v0->flags |= x_f51cb721;
        v0 = obj->x_e2f64c57[4];
        v0->flags |= x_f51cb721;
        x_32f1d6e2->flags |= x_f51cb721;
        x_5aee6615->flags |= x_f51cb721;
        x_5bbba600->flags |= x_f51cb721;
        obj->flags |= x_f51cb721;
    }

    v02 = handicap_health_to_width(x_b2bb447b);
    if (x_b2bb447b == x_83106b21) {
        obj->pos.x = obj->x_0f4167b4[1] - v02;
    } else {
        obj->pos.x = obj->x_0f4167b4[1] + v02;
    }
}

void handicap_init(Object *obj) {
    s16 s1;
    s16 x_464d68e5;
    x_f0d7e70f x_d65a2f4e = { 11, NULL, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_15702e8a = { 39, handicap_refresh, 0, 0x1000, "bars.sp2" };
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

    s3 = obj_create_from_def(&x_522f451d[s1], &x_d65a2f4e, x_24b231d4);
    v0 = obj_create_from_def(&x_dcab8ab0[s1], &x_15702e8a, x_24b231d4);
    v0->x_0f4167b4[0] = s1;
    v0->x_0f4167b4[3] = s3;
    s3 = obj_create_from_def(&x_d753d975[s1], &x_d65a2f4e, x_24b231d4);
    s3->frameCounter = 15 - s1;
    v0->x_0f4167b4[4] = s3;

    x_464d68e5 = handicap_health_to_width(s1);
    if (s1 == 0) {
        sHealthPartL = s3->x_904eaf67->x_a34b89cc[15].parts;
        sHealthPartL->x_e7f1952a =
            sHealthPartL->x_e7f1952a - sHealthPartL->x_b88b3756 + sHealthPartL->rightS - x_464d68e5 - 8;
        sHealthPartL->x_b88b3756 = sHealthPartL->rightS - x_464d68e5 - 8;
        v0->x_0f4167b4[1] = 119;
        v0->pos.x = 119 - x_464d68e5;
    } else {
        sHealthPartR = s3->x_904eaf67->x_a34b89cc[14].parts;
        sHealthPartR->rightS = sHealthPartR->x_b88b3756 + x_464d68e5;
        v0->x_0f4167b4[1] = 0xD1;
        v0->pos.x = 0xD1 + x_464d68e5;
    }

    s2 = obj_create_from_def(&x_fd09f53e[s1], &x_f4254db5, x_24b231d4);
    x_fd09f53e[s1].x += 10;
    x_2bf9ce78 = obj_create_from_def(&x_fd09f53e[s1], &x_f4254db5, x_24b231d4);
    x_fd09f53e[s1].x += 10;
    x_7f4af95e = obj_create_from_def(&x_fd09f53e[s1], &x_f4254db5, x_24b231d4);
    x_7f4af95e->x_0f4167b4[0] = s1;

    handicap_digit_render(x_7f4af95e, x_2bf9ce78, s2);

    v0->x_0f4167b4[5] = x_7f4af95e;
    v0->x_0f4167b4[6] = x_2bf9ce78;
    v0->x_0f4167b4[7] = s2;

    obj->x_0f4167b4[1] = 0;
    obj->x_0f4167b4[9] = x_7f4af95e;
    obj->currentTask->callback = handicap_input;
    obj->currentTask->delay = 20;
}

void char_select_cpu_scroll(Object *obj) {
    Object *x_aaadc3e8;
    s16 v1;
    s16 x_30bbe547;

    if (!(x_e30d50d2 & x_e3ff543d)) {
        return;
    }

    x_30bbe547 = obj->x_0f4167b4[0];
    x_aaadc3e8 = obj->x_e2f64c57[5];

    if (!gWadCondLoad[1 - x_30bbe547].x_03604d94 && x_aaadc3e8->x_0f4167b4[8] == 0) {
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
        audio_sfx_play(2, sAudioMuted != 0 ? 0 : x_30bbe547 + 4);
        char_select_confirm(obj, x_aaadc3e8);
        x_aaadc3e8 = obj->x_e2f64c57[4];
        x_aaadc3e8->x_0f4167b4[7] = 20;
        TASK_END(obj->currentTask);
        return;
    }

    audio_sfx_play(2, 6 + x_30bbe547);

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

void char_select_cursor(Object *obj) {
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
            audio_sfx_play(2, sAudioMuted != 0 ? 0 : a3 + 4);
            x_aaadc3e8 = obj->x_e2f64c57[4];
            x_aaadc3e8->x_0f4167b4[7] = 20;

            if (x_5e4e2788 == x_96f25e0a) {
                handicap_init(obj);
            } else {
                char_select_confirm(obj, obj->x_e2f64c57[5]);
                if (x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) {
                    sPlayerCursorObj[1 - a3]->x_0f4167b4[6] = char_select_random(1 - a3);
                }
                TASK_END(obj->currentTask);
            }
        } else if (v1 & (x_ad1aebe6 | x_fc4a9735)) {
            audio_sfx_play(2, 6 + a3);

            v0 = obj->frameCounter;
            if (v1 & x_ad1aebe6) {
                v0--;
            } else {
                v0++;
            }

            if (!sSonorkUnlocked && v0 == 8 || !sDemitronUnlocked && v0 == 1) {
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

void pregame_model_flash(Object *obj) {
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

void pregame_start_seq(Object *obj) {
    if (obj->x_0f4167b4[8] < 2) {
        return;
    }

    if (obj->x_0f4167b4[8] == 2) {
        obj->x_0f4167b4[8] = 3;
        obj->currentTask->delay = 10;
        sPlayerCursorObj[0]->flags |= x_5a44854c;
        sPlayerCursorObj[1]->flags |= x_5a44854c;
        return;
    }

    if (obj->x_0f4167b4[8] == 3) {
        obj->x_0f4167b4[8] = 4;
        sPlayerCursorObj[0]->flags |= x_5a44854c;
        sPlayerCursorObj[1]->flags |= x_5a44854c;
        obj->flags &= ~x_c537cafa;
        obj->currentTask->delay = 20;
        return;
    }

    gWadCondLoad[x_83106b21].x_fb21ca8c = gWadCondLoad[x_6f0b3be3].x_fb21ca8c = 0;
    gWadCondLoad[x_83106b21].x_eb1fe45b = obj->x_0f4167b4[9];
    gWadCondLoad[x_6f0b3be3].x_eb1fe45b = obj->x_0f4167b4[10];
    gWadCondLoad[x_83106b21].x_b2b764b3 = gWadCondLoad[x_6f0b3be3].x_b2b764b3 = 0;
    gWadCondLoad[x_83106b21].x_c35c64af &= ~3;
    gWadCondLoad[x_6f0b3be3].x_c35c64af &= ~3;
    if (0) {} // required to match
    x_e30d50d2 |= x_bee364e0;

    if (x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) {
        x_e38a6e19 = gWadCondLoad[sLastWinnerIdx].x_eb1fe45b + SCREEN_CHAR_SELECT_OFFSET;
        if (gWadCondLoad[x_83106b21].x_7d8e7a6f + gWadCondLoad[x_6f0b3be3].x_7d8e7a6f == 0) {
            x_e38a6e19 = gWadCondLoad[1 - sLastWinnerIdx].x_eb1fe45b + x_d61e86e9;
            gWadCondLoad[1 - sLastWinnerIdx].x_fb21ca8c = 1;
        } else {
            gWadCondLoad[sLastWinnerIdx].x_fb21ca8c = 1;
        }
        if (gWadCondLoad[sLastWinnerIdx].x_eb1fe45b == x_ff5073d4) {
            x_e38a6e19 = x_3509e8f6;
        }
    } else {
        x_e38a6e19 = gWadCondLoad[obj->x_0f4167b4[11]].x_eb1fe45b + SCREEN_CHAR_SELECT_OFFSET;
        gWadCondLoad[obj->x_0f4167b4[11]].x_fb21ca8c++;
    }

    TASK_END(obj->currentTask);
}

void practice_transition(Object *obj) {
    s16 x_30bbe547;
    Object *x_e9508efc;

    if (obj->x_0f4167b4[2]-- < 0) {
        obj->x_0f4167b4[2] = 15;
        obj->frameCounter = obj->x_0f4167b4[1] - obj->frameCounter;
    }

    x_30bbe547 = obj->x_0f4167b4[0];
    x_e9508efc = sPlayerCursorObj[x_30bbe547]->x_e2f64c57[4];
    if (x_e9508efc->x_0f4167b4[7]) {
        obj->flags |= x_f51cb721;
    }
}

void practice_input(Object *obj) {
    if (obj->x_0f4167b4[x_a44625a6]-- < 0) {
        obj->x_0f4167b4[x_a44625a6] = 15;
        obj->frameCounter = obj->x_0f4167b4[x_82e2e1db] - obj->frameCounter;
    }

    if (x_59ce598c[obj->x_0f4167b4[x_0140ad12]].buttons & x_9cefe76c) {
        obj->frameCounter = x_aaa2c518 - 2 * obj->x_0f4167b4[0];
        obj->x_0f4167b4[x_82e2e1db] = obj->frameCounter * 2 + 1;
        obj->pos.x = 245 - obj->x_0f4167b4[x_0140ad12] * 167;

        obj->x_0f4167b4[x_0140ad12] = 1 - obj->x_0f4167b4[x_0140ad12];
        obj->currentTask->callback = practice_transition;
    }
}

void char_select_init(void) {
    Object *x_523933cc[2];
    Object *x_fd096fa8;
    Object *obj;
    s16 x_13d65ace;
    Object *x_994c79b3;
    x_f0d7e70f x_c3be5f96 = { x_0857a6f7, char_select_cursor, 0, 0x1000, "grpp1.sp2" };
    x_f0d7e70f x_a8ee65ba = { x_fa2a4086, char_select_cursor, 0, 0x1000, "grpp2.sp2" };
    x_f0d7e70f x_37539a8c = { x_bdf6d812, pregame_model_flash, 0, 0x1000, "options2.sp2" };
    x_f0d7e70f x_b610af55 = { x_76b8b516, pregame_model_flash, 0, 0x1000, "options2.sp2" };
    x_f0d7e70f x_5601faec = { 26, pregame_start_seq, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_652f5000 = { 0, char_select_countdown2, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_4fea1147 = { 6, NULL, 0, 0x1000, "bars.sp2" };
    x_f0d7e70f x_8fcab22c = { x_35414b8d, practice_transition, 0, 0x1000, "options2.sp2" };
    x_f0d7e70f x_3bfdbaa4 = { x_b4568ba1, practice_input, 0, 0x1000, "practice.sp2" };
    x_f0d7e70f x_93121a84 = { x_823ba8a7, practice_input, 0, 0x1000, "practice.sp2" };
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

    x_c16a42f3 = gWadCondLoad[x_83106b21].x_eb1fe45b;
    x_fb97b65c = gWadCondLoad[x_6f0b3be3].x_eb1fe45b;

    if (x_c16a42f3 == x_ff5073d4 && sDemitronUnlocked == 0) {
        x_c16a42f3 = x_537ef8a7;
    }
    if (x_fb97b65c == x_ff5073d4 && sDemitronUnlocked == 0) {
        x_fb97b65c = x_537ef8a7;
    }
    if (x_c16a42f3 == x_968cc9a2 && !sSonorkUnlocked) {
        x_c16a42f3 = x_c4ddde6d;
    }
    if (x_fb97b65c == x_968cc9a2 && !sSonorkUnlocked) {
        x_fb97b65c = x_c4ddde6d;
    }

    if (x_c16a42f3 >= x_e235676f) {
        x_c16a42f3--;
    }
    if (x_fb97b65c >= x_e235676f) {
        x_fb97b65c--;
    }

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    gGfxFlags |= GFX_MENU_OVERLAY;
    x_e30d50d2 |= x_86c5bc33;

    wad_load_path("/plyrsel/plyrsel", x_24b231d4);
    wad_load_path("/plyrsel/music", x_24b231d4);

    x_e30d50d2 |= x_3b812e44;

    switch (x_5e4e2788) {
        case x_e483bf48:
            obj = obj_create_from_def(&x_4a1fd4d1, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = x_83106b21;
            obj->x_0f4167b4[1] = 167;
            wad_load_path("/plyrsel/select", x_24b231d4);
            break;
        case x_557d3dd6:
            obj = obj_create_from_def(&x_331089fa, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = x_6f0b3be3;
            obj->x_0f4167b4[1] = 167;
            wad_load_path("/plyrsel/select", x_24b231d4);
            break;
        case x_96f25e0a:
        case x_3658fb97:
        case x_a5f164ca:
            obj = obj_create_from_def(&x_4a1fd4d1, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = 0;
            obj->x_0f4167b4[1] = 167;
            obj = obj_create_from_def(&x_331089fa, &x_8fcab22c, x_24b231d4);
            obj->x_0f4167b4[0] = 1;
            obj->x_0f4167b4[1] = 167;
            wad_load_path("/plyrsel/select2", x_24b231d4);
            break;
        case x_79c2dc5b:
            if (x_08051143 == x_83106b21) {
                obj = obj_create_from_def(&x_2a89e429, &x_3bfdbaa4, x_24b231d4);
                obj->x_0f4167b4[x_0140ad12] = x_83106b21;
                obj->x_0f4167b4[x_82e2e1db] = x_b4568ba1 * 2 + 1;
            } else {
                obj = obj_create_from_def(&x_081c4eef, &x_93121a84, x_24b231d4);
                obj->x_0f4167b4[x_0140ad12] = x_6f0b3be3;
                obj->x_0f4167b4[x_82e2e1db] = x_823ba8a7 * 2 + 1;
            }
            wad_load_path("/plyrsel/select3", x_24b231d4);
            break;
    }

    x_a0e73601("select", 0, 8, 0, 0, x_96186256, x_24b231d4);

    sPlayerCursorObj[0] = obj_create_from_def(&x_5c2a3a42, &x_c3be5f96, x_24b231d4);
    sPlayerCursorObj[0]->x_0f4167b4[0] = x_83106b21;
    sPlayerCursorObj[0]->frameCounter = x_c16a42f3;
    sPlayerCursorObj[0]->currentTask->delay = 20;

    sPlayerCursorObj[1] = obj_create_from_def(&x_0cbc7c1c, &x_a8ee65ba, x_24b231d4);
    sPlayerCursorObj[1]->x_0f4167b4[0] = x_6f0b3be3;
    sPlayerCursorObj[1]->frameCounter = x_fb97b65c;
    sPlayerCursorObj[1]->currentTask->delay = 20;

    x_523933cc[0] = obj_create_from_def(&x_a3f0c785, &x_37539a8c, x_24b231d4);
    x_523933cc[0]->x_0f4167b4[0] = x_83106b21;

    x_523933cc[1] = obj_create_from_def(&x_3dfff383, &x_b610af55, x_24b231d4);
    x_523933cc[1]->x_0f4167b4[0] = x_6f0b3be3;

    x_fd096fa8 = obj_create_from_def(&x_3eeec712, &x_5601faec, x_24b231d4);
    x_fd096fa8->flags |= x_c537cafa;
    x_fd096fa8->x_0f4167b4[11] = -1;
    x_fd096fa8->flags |= x_5a44854c;

    x_994c79b3 = obj_create_from_def(&x_9e7fdb6b, &x_4fea1147, x_24b231d4);
    obj = obj_create_from_def(&x_9d69f44f, &x_652f5000, x_24b231d4);
    obj->x_0f4167b4[2] = 60;
    obj->x_e2f64c57[1] = x_994c79b3;
    obj->x_e2f64c57[5] = x_fd096fa8;

    sPlayerCursorObj[0]->x_e2f64c57[4] = x_523933cc[0];
    sPlayerCursorObj[0]->x_e2f64c57[5] = x_fd096fa8;
    sPlayerCursorObj[1]->x_e2f64c57[4] = x_523933cc[1];
    sPlayerCursorObj[1]->x_e2f64c57[5] = x_fd096fa8;

    switch (x_5e4e2788) {
        case x_e483bf48:
        case x_557d3dd6:
            x_13d65ace = (x_5e4e2788 == x_557d3dd6);
            sPlayerCursorObj[1 - x_13d65ace]->currentTask->callback = char_select_cpu_scroll;
            sPlayerCursorObj[1 - x_13d65ace]->currentTask->delay = 0;
            sPlayerCursorObj[1 - x_13d65ace]->currentTask->flags = TASK_RUNNABLE;

            if (gWadCondLoad[x_13d65ace].x_b2b764b3 != 0) {
                sPlayerCursorObj[1 - x_13d65ace]->x_0f4167b4[6] = char_select_random(1 - x_13d65ace);
                TASK_END(sPlayerCursorObj[x_13d65ace]->currentTask);
                x_523933cc[x_13d65ace]->x_0f4167b4[7] = 20;
                x_fd096fa8->x_0f4167b4[8] = 1;
                x_fd096fa8->x_0f4167b4[9 + x_13d65ace] = gWadCondLoad[x_13d65ace].x_eb1fe45b;
            }
            break;
        case x_3658fb97:
            sPlayerCursorObj[0]->currentTask->callback = char_select_cpu_scroll;
            sPlayerCursorObj[0]->currentTask->delay = 0;
            sPlayerCursorObj[0]->currentTask->flags = TASK_RUNNABLE;
            sPlayerCursorObj[0]->x_0f4167b4[6] = char_select_random(0);

            sPlayerCursorObj[1]->currentTask->callback = char_select_cpu_scroll;
            sPlayerCursorObj[1]->currentTask->delay = 0;
            sPlayerCursorObj[1]->currentTask->flags = TASK_RUNNABLE;
            sPlayerCursorObj[1]->x_0f4167b4[6] = char_select_random(1);
            break;
        case x_96f25e0a:
        case x_79c2dc5b:
        case x_a5f164ca:
            break;
    }

    tr_scene_loop();
    wad_unload_context(x_24b231d4);
}

void cheat_set_flags(s16 x_30bbe547, u16 x_1819574a, u16 x_6388adb6) {
    sSonorkUnlocked = x_1819574a;
    sDemitronUnlocked = x_6388adb6;
}

void cheat_goto_stage(s16 x_05e00b01, s16 x_30bbe547) {
    x_e30d50d2 |= x_bee364e0;
    x_e38a6e19 = x_fa31c524;

    gWadCondLoad[x_30bbe547].x_eb1fe45b = x_05e00b01;
    gWadCondLoad[x_30bbe547].x_03604d94 = FALSE;
    gWadCondLoad[x_30bbe547].x_fb21ca8c = 0;

    gWadCondLoad[1 - x_30bbe547].x_eb1fe45b = x_ff5073d4;
    gWadCondLoad[1 - x_30bbe547].x_03604d94 = TRUE;
    gWadCondLoad[1 - x_30bbe547].x_fb21ca8c = 1;

    present_set_screen(x_30bbe547 + x_e483bf48);
}

void cheat_switch_char(s16 x_30bbe547, u16 x_05e00b01, u16 x_2092f891) {
    cheat_goto_stage(x_05e00b01, x_30bbe547);
}

void cheat_practice_mode(s16 x_30bbe547, u16 x_84ff873b, u16 x_2092f891) {
    cheat_goto_stage(x_ff5073d4, x_30bbe547);
    x_e38a6e19 = x_3509e8f6;
}

void cheat_set_difficulty(s16 x_30bbe547, u16 x_84ff873b, u16 x_2092f891) {
    gWadCondLoad[x_83106b21].x_cc57155e = gWadCondLoad[x_6f0b3be3].x_cc57155e = x_84ff873b;
}

void cheat_switch_side(s16 x_30bbe547, u16 x_84ff873b, u16 x_2092f891) {
    s16 i;

    gWadCondLoad[1 - x_30bbe547].x_fb21ca8c = 1;
    gWadCondLoad[x_30bbe547].x_fb21ca8c = 0;
    gWadCondLoad[x_30bbe547].x_03604d94 = FALSE;
    gWadCondLoad[1 - x_30bbe547].x_03604d94 = TRUE;
    sFirstFight = TRUE;

    for (i = 0; i < 11; i++) {
        D_800B6350[0][i] = D_800B6350[1][i] = 0;
    }

    x_e30d50d2 |= x_bee364e0;
    present_set_screen(x_30bbe547 + x_e483bf48);
}

void cheat_navigate(s16 x_30bbe547, u16 x_05e00b01, u16 x_7cedc3fb) {
    gWadCondLoad[1 - x_30bbe547].x_eb1fe45b = x_05e00b01;
    gWadCondLoad[1 - x_30bbe547].x_03604d94 = TRUE;
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

CheatEntry sCheatTable[] = { { D_8004A114, cheat_practice_mode, 0, 0 },
                             { x_872278ef, cheat_set_flags, TRUE, FALSE },
                             { x_af558c92, cheat_set_flags, TRUE, TRUE },
                             { x_da3e5ada, cheat_switch_char, 0, 0 },
                             { x_2b6f9733, cheat_switch_char, 2, 0 },
                             { x_7eaa6bad, cheat_switch_char, 3, 0 },
                             { x_e694052f, cheat_switch_char, 4, 0 },
                             { x_49a7f1c5, cheat_switch_char, 6, 0 },
                             { x_0f81075a, cheat_switch_char, 7, 0 },
                             { x_42d5a2ea, cheat_switch_char, 8, 0 },
                             { x_b6970c24, cheat_switch_char, 9, 0 },
                             { x_f9cc0201, cheat_switch_char, 10, 0 },
                             { x_a8689ca4, cheat_switch_char, 1, 0 },
                             { D_8004A13C, cheat_set_difficulty, 0, 0 },
                             { D_8004A14C, cheat_set_difficulty, 1, 0 },
                             { D_8004A15C, cheat_set_difficulty, 2, 0 },
                             { D_8004A16C, cheat_set_difficulty, 3, 0 },
                             { D_8004A17C, cheat_set_difficulty, 4, 0 },
                             { D_8004A18C, cheat_set_difficulty, 5, 0 },
                             { D_8004A19C, cheat_set_difficulty, 6, 0 },
                             { D_8004A1AC, cheat_set_difficulty, 7, 0 },
                             { D_8004A1BC, cheat_navigate, x_c4ddde6d, SCREEN_CHAR_SELECT_OFFSET },
                             { D_8004A1CC, cheat_navigate, x_ff5073d4, SCREEN_PRACTICE },
                             { D_8004A1E0, cheat_navigate, x_73cf9ceb, x_3b539526 },
                             { D_8004A1F4, cheat_navigate, x_6a049984, x_8774b75f },
                             { D_8004A208, cheat_navigate, x_537ef8a7, x_04d94c4d },
                             { D_8004A21C, cheat_navigate, x_b52da315, x_2a9c0615 },
                             { D_8004A230, cheat_navigate, x_13ed828f, x_9cb4f0a0 },
                             { D_8004A244, cheat_navigate, x_12e7e1dc, x_ed0b2237 },
                             { D_8004A258, cheat_navigate, x_968cc9a2, x_4ad48df4 },
                             { D_8004A270, cheat_navigate, x_379149a4, x_b2483e0d },
                             { D_8004A128, cheat_switch_side, 0, 0 },
                             { NULL, NULL, 0, 0 } };

s16 cheat_sequence_cmp(u16 *x_2bb7a7fd, u16 *x_04faa85c) {
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

void cheat_advance(CheatState *state, s16 x_30bbe547) {
    CheatEntry *x_3a1b45d4 = state->currentEntry;

    state->stepIndex++;
    if (x_3a1b45d4->sequence[state->stepIndex] == x_d0d35cc6) {
        audio_sfx_play(2, 9);
        x_3a1b45d4->handler(x_30bbe547, x_3a1b45d4->param1, x_3a1b45d4->param2);
        state->currentEntry = NULL;
        state->stepIndex = 0;
    }
}

void cheat_process(CheatState *state, s16 x_30bbe547) {
    u16 x_f3756179;
    CheatEntry *x_9eaf6155;
    CheatEntry *ptr;
    s32 unused;

    if (!x_59ce598c[x_30bbe547].x_c4397934) {
        return;
    }
    x_f3756179 = x_59ce598c[x_30bbe547].x_f3756179;
    if (!x_f3756179) {
        return;
    }

    if (x_f3756179 & (x_f7763ed8 | x_b8c91680 | x_ad1aebe6 | x_fc4a9735 | x_37f8540c)) {
        if (state->lastButton == x_f3756179) {
            x_59ce598c[x_30bbe547].x_c4397934 = FALSE;
            return;
        }
        state->lastButton = x_f3756179;
    }

    x_59ce598c[x_30bbe547].x_c4397934 = FALSE;
    x_9eaf6155 = state->currentEntry;
    if (x_9eaf6155 != NULL) {
        if (x_f3756179 == x_9eaf6155->sequence[state->stepIndex]) {
            cheat_advance(state, x_30bbe547);
            return;
        }

        for (ptr = x_9eaf6155 + 1; ptr->sequence != NULL; ptr++) {
            if (cheat_sequence_cmp(x_9eaf6155->sequence, ptr->sequence) == state->stepIndex &&
                x_f3756179 == ptr->sequence[state->stepIndex]) {
                state->currentEntry = ptr;
                cheat_advance(state, x_30bbe547);
                return;
            }
        }
        x_59ce598c[x_30bbe547].x_c4397934 = TRUE;
        if (0) {} // required to match

        state->currentEntry = NULL;
        state->stepIndex = FALSE;
        state->lastButton = 0;
        return;
    }

    for (x_9eaf6155 = sCheatTable; x_9eaf6155->sequence != NULL; x_9eaf6155++) {
        if (x_9eaf6155->sequence[0] == x_f3756179) {
            state->currentEntry = x_9eaf6155;
            state->stepIndex = 1;
            return;
        }
    }
}

void cheat_update(Object *obj) {
    cheat_process((CheatState *) &obj->x_0f4167b4[0], x_83106b21);
    cheat_process((CheatState *) &obj->x_0f4167b4[8], x_6f0b3be3);
}
