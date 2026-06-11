#include "common.h"
#include "camera.h"
#include "task.h"

extern s16 sRoundWinCount;
extern s16 x_1acf99bf;
extern u32 x_6db66fc3;

void present_title_task(Object *);

s16 sCharRotTable[8][2] = {
    { x_b52da315, x_13ed828f }, { x_13ed828f, x_12e7e1dc }, { x_12e7e1dc, x_379149a4 }, { x_379149a4, x_c4ddde6d },
    { x_c4ddde6d, x_73cf9ceb }, { x_73cf9ceb, x_6a049984 }, { x_6a049984, x_537ef8a7 }, { x_537ef8a7, x_13ed828f },
};
s16 sAttractCycleIdx = 0;

/* .bss */
s16 D_80081250;
x_4a7d6dd4 *D_80081254;

void present_set_screen(u16 x_cc1d0de5) {
    x_1acf99bf = x_5e4e2788;
    x_5e4e2788 = x_cc1d0de5;
}

void attract_blink_cb(Object *obj) {
    if (++obj->frameCounter >= obj->x_0f4167b4[4]) {
        obj->frameCounter = obj->x_0f4167b4[6] * 20;
        obj->currentTask->callback = present_title_task;
    }
}

void attract_menu_input(Object *obj, s16 buttons, s16 x_30bbe547) {
    s16 i;
    s16 temp;
    s16 x_df21a243;

    x_df21a243 = obj->x_0f4167b4[1];
    temp = obj->x_0f4167b4[2];
    obj->x_0f4167b4[1] = buttons;
    obj->x_0f4167b4[2]--;
    obj->x_0f4167b4[7] = 0;

    if (temp <= 0 || buttons != x_df21a243) {
        obj->x_0f4167b4[2] = 15;
        if (buttons & x_9cefe76c) {
            switch (obj->x_0f4167b4[6]) {
                case 0:
                    x_e38a6e19 = SCREEN_WAIT;
                    gWadCondLoad[x_30bbe547].x_03604d94 = FALSE;
                    gWadCondLoad[1 - x_30bbe547].x_03604d94 = TRUE;
                    sFirstFight = TRUE;
                    x_6db66fc3 = 1 - x_30bbe547;
                    present_set_screen(x_e483bf48 + x_30bbe547);
                    gWadCondLoad[x_83106b21].x_b2b764b3 = gWadCondLoad[x_6f0b3be3].x_b2b764b3 = FALSE;
                    for (i = 0; i < x_edb381f3; i++) {
                        D_800B6350[x_83106b21][i] = D_800B6350[x_6f0b3be3][i] = FALSE;
                    }
                    break;
                case 1:
                    x_e38a6e19 = SCREEN_WAIT;
                    gWadCondLoad[x_83106b21].x_03604d94 = gWadCondLoad[x_6f0b3be3].x_03604d94 = FALSE;
                    sFirstFight = TRUE;
                    present_set_screen(x_96f25e0a);
                    break;
                case 2:
                    x_e38a6e19 = SCREEN_TITLE;
                    break;
                case 3:
                    gWadCondLoad[x_30bbe547].x_03604d94 = FALSE;
                    gWadCondLoad[1 - x_30bbe547].x_03604d94 = FALSE;
                    x_e38a6e19 = SCREEN_WAIT;
                    sFirstFight = TRUE;
                    present_set_screen(x_79c2dc5b);
                    x_08051143 = x_30bbe547;
                    break;
            }

            audio_sfx_play(2, 0);
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
        } else if (buttons & x_ad1aebe6) {
            obj->x_0f4167b4[4] = obj->x_0f4167b4[6] * 20 + 20;
            obj->x_0f4167b4[6] = (obj->x_0f4167b4[6] + 3) % 4;
            if (!x_59ce598c[x_83106b21].x_12a7bd86 || !x_59ce598c[x_6f0b3be3].x_12a7bd86) {
                if (obj->x_0f4167b4[6] == 1) {
                    obj->x_0f4167b4[6] = (obj->x_0f4167b4[6] + 3) % 4;
                }
            }
            obj->currentTask->callback = attract_blink_cb;
            audio_sfx_play(2, 1);
        } else if (buttons & x_fc4a9735) {
            obj->x_0f4167b4[4] = obj->x_0f4167b4[6] * 20 + 20;
            obj->x_0f4167b4[6] = (obj->x_0f4167b4[6] + 1) % 4;
            if (!x_59ce598c[x_83106b21].x_12a7bd86 || !x_59ce598c[x_6f0b3be3].x_12a7bd86) {
                if (obj->x_0f4167b4[6] == 1) {
                    obj->x_0f4167b4[6] = (obj->x_0f4167b4[6] + 1) % 4;
                }
            }
            obj->currentTask->callback = attract_blink_cb;
            audio_sfx_play(2, 1);
        }
    }
}

void present_single_win(void) {
    x_5e4e2788 = x_3658fb97;
    x_e30d50d2 |= x_bee364e0;

    gWadCondLoad[x_83106b21].x_eb1fe45b = gWadCondLoad[x_6f0b3be3].x_eb1fe45b = x_968cc9a2;
    gWadCondLoad[x_83106b21].x_fb21ca8c = TRUE;
    gWadCondLoad[x_6f0b3be3].x_fb21ca8c = FALSE;
    gWadCondLoad[x_83106b21].x_03604d94 = FALSE;
    gWadCondLoad[x_6f0b3be3].x_03604d94 = TRUE;

    x_e38a6e19 = SCREEN_OPTIONS;
    sRoundWinCount++;
}

void present_attract_cycle(void) {
    x_5e4e2788 = x_3658fb97;

    x_e30d50d2 |= x_bee364e0;
    sAttractCycleIdx &= 7;

    gWadCondLoad[x_83106b21].x_eb1fe45b = sCharRotTable[sAttractCycleIdx][x_83106b21];
    gWadCondLoad[x_83106b21].x_fb21ca8c = TRUE;
    gWadCondLoad[x_6f0b3be3].x_fb21ca8c = FALSE;
    gWadCondLoad[x_83106b21].x_03604d94 = FALSE;
    gWadCondLoad[x_6f0b3be3].x_03604d94 = TRUE;

    gWadCondLoad[x_6f0b3be3].x_eb1fe45b = sCharRotTable[sAttractCycleIdx][x_6f0b3be3];
    x_e38a6e19 = x_d61e86e9 + gWadCondLoad[x_83106b21].x_eb1fe45b;

    sRoundWinCount = sAttractCycleIdx++;
    x_6db66fc3 = x_6f0b3be3;
}

void present_title_task(Object *obj) {
    s16 x_48ca1589, x_a6a94456;

    x_48ca1589 = x_59ce598c[x_83106b21].buttons;
    x_a6a94456 = x_59ce598c[x_6f0b3be3].buttons;

    if (obj->x_0f4167b4[3]-- <= 0) {
        obj->x_0f4167b4[3] = 4;
        obj->frameCounter = obj->x_0f4167b4[6] * 40 + 2 - obj->frameCounter;
    }

    if (x_48ca1589 != 0) {
        attract_menu_input(obj, x_48ca1589, x_83106b21);
    } else if (x_a6a94456 != 0) {
        attract_menu_input(obj, x_a6a94456, x_6f0b3be3);
    } else {
        obj->x_0f4167b4[1] = 0;
    }

    if (++obj->x_0f4167b4[7] > 2400) {
        present_attract_cycle();
    }
}

void present_attract_loop(Object *obj) {
    Model *x_3f551491;
    x_88f11482 x_32f1d6e2 = { 160, 120, 0, 0 };
    Object *x_7e485fc0;

    if (obj->x_0f4167b4[2]-- < 0) {
        obj->x_0f4167b4[2] = 15;
        obj->frameCounter = 0xA7 - obj->frameCounter;
    }

    if ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
        audio_sfx_play(2, 0);
        x_3f551491 = sWadEntries[wad_entry_find("title.k2", 0x2000)].x_4962fc73;
        x_7e485fc0 = obj_create_with_model_ptr(&sZeroPosition, 0x1000, present_title_task, x_3f551491);
        x_7e485fc0->currentTask->delay = 30;
        x_7e485fc0->frameCounter = 0;
        x_7e485fc0->flags |= x_a816b63b;
        obj->flags |= x_f51cb721;
    }

    if (++obj->x_0f4167b4[7] > 900) {
        present_attract_cycle();
    }
}

void present_skip_to_attract(Object *obj) {
    if (x_5e4e2788 == x_3658fb97 &&
        ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c))) {
        x_e30d50d2 |= x_bee364e0;
        x_e38a6e19 = SCREEN_ATTRACT;
        obj->flags |= x_f51cb721;
        TASK_END(obj->currentTask);
    }
}

void present_digi_element(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] > 180) {
        sFadeAlpha = 0;
        x_e30d50d2 |= x_bee364e0;
        x_e38a6e19 = SCREEN_CREDITS;
        obj->flags |= x_f51cb721;
        TASK_END(obj->currentTask);
    }
    present_skip_to_attract(obj);
}

Vtx sFadeQuadVtx[2][4] = { { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                             { { { x_56e08f29 << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                             { { { 0, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                             { { { x_56e08f29 << 2, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } },
                           { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                             { { { x_56e08f29 << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                             { { { 0, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                             { { { x_56e08f29 << 2, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } } };

void present_kronos_fade_out(Object *obj) {
    if (sFadeAlpha - 8 < sFadeThreshold) {
        obj->x_0232396f = present_digi_element;
    } else {
        sFadeAlpha -= 8;
    }

    tr_quad_xlu(sFadeAlpha, sFadeQuadVtx[D_8005BFCE]);
}

void present_kronos_fade_in(Object *obj) {
    if (sFadeAlpha + 8 < 255) {
        sFadeAlpha += 8;
    } else {
        mem_free(x_3b49183f);
        x_3b49183f = NULL;
        x_a0e73601("kronos", 0, 60, 0, 180, x_96186256, x_35b88489);
        obj->x_0232396f = present_kronos_fade_out;
    }

    tr_quad_xlu(sFadeAlpha, sFadeQuadVtx[D_8005BFCE]);
}

void present_kronos_logo(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] > 180) {
        obj->x_0f4167b4[0] = 0;
        obj->x_0232396f = present_kronos_fade_in;
    }
    present_skip_to_attract(obj);
}

s16 sTitleSfxFrameTbl[] = { 14, 28, 40, 52, 64, 76, 88, 100, 0 };

void present_title_open_anim(Object *obj) {
    s16 i;

    for (i = 0; sTitleSfxFrameTbl[i] != 0; i++) {
        if (obj->frameCounter == sTitleSfxFrameTbl[i]) {
            audio_sfx_play(0x2000, 2);
        }
    }

    if (++obj->frameCounter >= obj->x_20d20338->x_8e601526 - 4) {
        obj->flags |= x_f51cb721;
        obj_create_task(fade_in_cb, 0x1000);
        sFadeAlpha = 0;
        audio_sfx_play(0x2000, 3);
    }
}

void present_title_sfx(Object *obj) {
    audio_sfx_play(0x2000, 8);
    obj->flags |= x_f51cb721;
}

void present_title_open(Object *obj) {
    Object *v1;
    Model *m;

    if (D_80081250 + x_6c647b3a + x_84e8ddf2 >= 0 &&
        ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c))) {
        D_80081254->flags |= x_607c80f4;
        obj->x_0232396f = fade_in_cb;

        v1 = obj->x_e2f64c57[0];
        v1->flags |= x_f51cb721;
        v1 = obj->x_e2f64c57[1];
        v1->flags |= x_f51cb721;

        audio_sfx_stop(0x2000, 8);
        audio_sfx_play(0x2000, 3);
        return;
    }

    if (++obj->x_0f4167b4[2] == 4) {
        obj->x_0f4167b4[2] = 0;
        if (D_80081250 + x_6c647b3a + x_84e8ddf2 >= 0) {
            x_6c647b3a--;
            return;
        }

        v1 = obj->x_e2f64c57[0];
        D_80081254->flags |= x_607c80f4;
        if (v1->color.a >= 6) {
            v1->color.a -= 6;
            v1->pos.z -= 160;

            v1 = obj->x_e2f64c57[1];
            v1->pos.z += 450;
        } else {
            v1->flags |= x_f51cb721;
            obj->flags |= x_f51cb721;

            v1 = obj->x_e2f64c57[1];
            v1->flags |= x_f51cb721;

            m = (Model *) sWadEntries[wad_entry_find("titopen.k2", x_35b88489)].x_4962fc73;
            v1 = obj_create_with_model_ptr(&sZeroPosition, 0x1000, present_title_open_anim, m);
            v1->flags |= x_a816b63b | x_b6789b80 | x_d13a68b5;
            v1->color.a = 128;
            obj->x_0f4167b4[2] = 3;
            audio_sfx_stop(0x2000, 8);
        }
    }
}

void present_haze_anim(Object *obj) {
    if (++obj->frameCounter > 118) {
        obj->frameCounter = 0;
    }
}

void present_haze_init(Object *obj, s16 x_84ff873b) {
    Object *v0;
    x_88f11482 x_5bbba600 = { 0, -550, 0, 0 };
    Model *m;

    m = (Model *) sWadEntries[wad_entry_find("haze.k2", x_84ff873b)].x_4962fc73;
    v0 = obj_create_with_model_ptr(&sZeroPosition, 0x1000, present_haze_anim, m);
    v0->flags |= x_a816b63b | x_b6789b80 | x_d13a68b5;
    v0->color.a = 75;
    if (obj != NULL) {
        obj->x_e2f64c57[0] = v0;
    }

    m = (Model *) sWadEntries[wad_entry_find("haze1.k2", x_84ff873b)].x_4962fc73;
    v0 = obj_create_with_model_ptr(&x_5bbba600, 0x1000, NULL, m);
    v0->flags |= x_a816b63b | x_b6789b80 | x_d13a68b5;
    v0->color.a = 75;
    if (obj != NULL) {
        obj->x_e2f64c57[1] = v0;
    }
    model_collect_textures(v0, FALSE);

    obj_create_task(present_title_sfx, 0x1000);
}

void present_theend_skip(Object *obj) {
    if (x_59ce598c[sWinnerIdx].buttons & x_9cefe76c) {
        x_e30d50d2 |= x_bee364e0;
        x_e38a6e19 = SCREEN_EASY_WIN;
        obj->flags |= x_f51cb721;
    }
}

void present_theend_anim_end(Object *obj) {
    if (++obj->frameCounter >= obj->x_20d20338->x_8e601526 - 1) {
        obj->currentTask->callback = task_remove_current;
    }
}

void present_theend_init(Object *obj) {
    Object *v0;
    Model *m;
    x_88f11482 x_dd7ffac5 = { 0, -40, 0, 0 };

    if (--obj->x_0f4167b4[0] < 0) {
        obj->x_0232396f = present_theend_skip;
        obj->x_0f4167b4[0] = 0;
        obj->x_0f4167b4[1] = 0;
        m = (Model *) sWadEntries[wad_entry_find("theend.k2", 0x4000)].x_4962fc73;
        v0 = obj_create_with_model_ptr(&x_dd7ffac5, 0x1000, present_theend_anim_end, m);
        v0->flags |= x_a816b63b | x_b6789b80 | x_d13a68b5;
    }
}

void present_transition_screen(Object *obj) {
    x_e30d50d2 |= x_bee364e0;

    switch (gCurrentScreenId) {
        case SCREEN_EASY_WIN:
            x_e38a6e19 = SCREEN_BOOT;
            break;
        case SCREEN_PRACTICE:
            x_e38a6e19 = SCREEN_EASY_WIN;
            break;
        case SCREEN_ATTRACT_AGAIN:
            x_e38a6e19 = x_b804ecb4;
            break;
        default:
            if (1) {}
            x_e38a6e19 = SCREEN_EASY_WIN;
            break;
    }

    obj->flags |= x_f51cb721;
    x_25025961(D_80081254);
}

void present_win_fade_out(Object *obj) {
    Object *v0 = obj->x_e2f64c57[0];
    Object *v1 = obj->x_e2f64c57[1];

    if (v0 != NULL && v0->color.a >= 6) {
        v0->color.a -= 6;
        v0->pos.z -= 150;
        v1->pos.z += 450;
        return;
    }

    v0->flags |= x_f51cb721;
    present_transition_screen(obj);
}

void present_win_result_loop(Object *obj) {
    if (++obj->x_0f4167b4[3] == obj->x_0f4167b4[2]) {
        obj->x_0f4167b4[3] = 0;
        if (D_80081250 + D_80081254->x_64a8566c + 40) {
            D_80081254->x_64a8566c--;
        }
    }

    if (!(D_80081250 + D_80081254->x_64a8566c + 40)) {
        if (gCurrentScreenId != SCREEN_EASY_WIN) {
            present_transition_screen(obj);
        } else {
            obj->x_0232396f = present_win_fade_out;
        }
    }

    if ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
        present_transition_screen(obj);
    }
}

void present_winner_wait(Object *obj) {
    if (x_f4bce728->x_20d20338->x_50771dcd[0] == NULL) {
        cam_ko_init(x_f4bce728, obj->x_0f4167b4[1]);
        TASK_END(obj->currentTask);
        obj->flags |= x_f51cb721;
    }
}

void present_result_timer(Object *obj) {
    if (--obj->x_0f4167b4[0] < 0) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
    }
}

typedef struct PresentSfxEntry {
    /* 0x00 */ s16 x_af0aa1f8;
    /* 0x02 */ s16 x_cd679b4c;
} PresentSfxEntry; // size = 0x4

PresentSfxEntry sPresentsSfxTbl[] = { { 231, 17 }, { 281, 9 },  { 297, 9 },  { 313, 12 }, { 335, 11 },
                                      { 425, 10 }, { 447, 14 }, { 484, 16 }, { 0, 0 } };
PresentSfxEntry sDemoSfxTbl[] = { { 166, 15 }, { 194, 16 }, { 214, 9 }, { 228, 10 }, { 242, 12 },
                                  { 256, 13 }, { 270, 9 },  { 276, 8 }, { 278, 20 }, { 0, 0 } };
s16 sDemoDustFrameTbl[] = { 175, 180, 190, 200, 210, 215, 220, 225, 230, 240, 250, 260, 265, 275, 0 };
PresentSfxEntry sDemoCharSfxTbl[] = { { 172, 10 }, { 190, 11 }, { 204, 10 }, { 220, 11 }, { 264, 14 }, { 0, 0 } };
PresentSfxEntry sDemoBossSfxTbl[] = { { 214, 21 }, { 250, 20 }, { 208, 15 }, { 0, 0 } };

void present_intro_presents(Object *obj) {
    u8 s3 = gWadCondLoad[x_6f0b3be3].x_03604d94;
    Player *s2 = &x_824b9544[s3];
    s16 i = 0;

    if (s2->obj->frameCounter == s2->x_7f68c36b->x_bab9966d - 2) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
        x_e38a6e19 = SCREEN_PRACTICE;
        x_25025961(D_80081254);
    }

    if (s2->obj->frameCounter == 260) {
        D_80081254 = x_a0e73601("demispk", 0, 160, 0, 0, x_8ce7ef70, 0x3000);
    }

    while (sPresentsSfxTbl[i].x_af0aa1f8 != 0) {
        if (sPresentsSfxTbl[i].x_af0aa1f8 == s2->obj->frameCounter) {
            audio_sfx_play(s3, sPresentsSfxTbl[i].x_cd679b4c);
        }
        i++;
    }
}

void present_demo_action(Object *obj) {
    u8 s4 = gWadCondLoad[x_6f0b3be3].x_03604d94;
    Player *s = x_824b9544 + s4;
    Player *s1 = x_824b9544 + 1 - s4;
    s16 i = 0;
    s16 *x_489cd5db;

    if (s1->obj->frameCounter == s1->x_7f68c36b->x_bab9966d - 2) {
        obj->x_0f4167b4[0] = 10;
        obj->x_0232396f = present_result_timer;
    }

    if (s1->x_eb1fe45b != x_968cc9a2 && s1->x_eb1fe45b != x_73cf9ceb) {
        while (sDemoSfxTbl[i].x_af0aa1f8 != 0) {
            if (sDemoSfxTbl[i].x_af0aa1f8 == s1->obj->frameCounter) {
                audio_sfx_play(s4, sPresentsSfxTbl[i].x_cd679b4c);
            }
            i++;
        }

        i = 0;
        while (sDemoDustFrameTbl[i] != 0) {
            if (s1->obj->frameCounter == sDemoDustFrameTbl[i]) {
                hud_dust_line_spawn(s->obj);
            }
            i++;
        }

        if (s1->obj->frameCounter == 278) {
            projectile_spawn(s->obj, 9);
        }
    }
}

void present_demo_sfx(Object *obj) {
    u8 s4 = gWadCondLoad[x_6f0b3be3].x_03604d94;
    Player *s = x_824b9544 + s4;
    Player *s1 = x_824b9544 + 1 - s4;
    s16 i = 0;

    if (s1->x_eb1fe45b == x_968cc9a2) {
        while (sDemoBossSfxTbl[i].x_af0aa1f8 != 0) {
            if (sDemoBossSfxTbl[i].x_af0aa1f8 == s1->obj->frameCounter) {
                audio_sfx_play(s1->x_30bbe547, sDemoBossSfxTbl[i].x_cd679b4c);
            }
            i++;
        }
    } else {
        while (sDemoCharSfxTbl[i].x_af0aa1f8 != 0) {
            if (s1->obj->frameCounter == sDemoCharSfxTbl[i].x_af0aa1f8) {
                audio_sfx_play(s1->x_30bbe547, sDemoCharSfxTbl[i].x_cd679b4c);
            }
            i++;
        }
    }
}
