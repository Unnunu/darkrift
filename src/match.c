#include "common.h"
#include "camera.h"
#include "task.h"

extern s16 D_80049390;
extern x_3da8fdd8 x_c2354b9b[];
extern u8 sAudioForceMute;
extern s16 x_adcfd05c;

extern Object *sHudRootObj;

extern s32 sLastWinnerIdx;

/* .bss */

Object *sWinnerMsgObj;
Object *sDrawMsgObj;
Object *sKoMsgObj;
Object *sAfterKoMsgObj;
Object *sContinueMsgObj;
Object *sSuddenDeathMsgObj;

void match_post_ko_routing(Object *);
void match_ko_decision(Object *);

void match_goto_select(Object *obj) {
    x_e30d50d2 |= x_ecbcd14e | x_700de048 | x_bee364e0;
    x_e38a6e19 = SCREEN_WAIT;
    present_set_screen(x_a5f164ca);
    if (gWadCondLoad[x_83106b21].x_03604d94) {
        D_80049390 = gWadCondLoad[x_83106b21].x_eb1fe45b;
    } else {
        D_80049390 = gWadCondLoad[x_6f0b3be3].x_eb1fe45b;
    }

    gWadCondLoad[x_83106b21].x_03604d94 = gWadCondLoad[x_6f0b3be3].x_03604d94 = FALSE;
    gWadCondLoad[x_83106b21].x_b2b764b3 = gWadCondLoad[x_6f0b3be3].x_b2b764b3 = 0;
    obj->flags |= x_f51cb721;
}

void match_ko_fadeout(Object *obj) {
    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        if (--obj->x_0f4167b4[1] <= 0) {
            if (obj->x_0f4167b4[0] < obj->color.a) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
                obj->x_0232396f = match_goto_select;
            }
        }
    } else {
        obj->frameCounter++;
    }

    model_render(obj);
}

void match_anim_play_fade(Object *obj) {
    if (--obj->x_0f4167b4[1] <= 0) {
        obj->flags &= ~x_c537cafa;
        if (obj->frameCounter == 0 && obj->x_0f4167b4[2] != -1) {
            audio_sfx_play(2, obj->x_0f4167b4[2]);
        }

        if (obj->frameCounter < obj->x_20d20338->x_8e601526 - 1) {
            obj->frameCounter++;
        }
    }
}

void match_anim_play_fadeout(Object *obj) {
    obj->flags &= ~x_c537cafa;
    if (obj->frameCounter == 0 && obj->x_0f4167b4[2] != -1) {
        audio_sfx_play(2, obj->x_0f4167b4[2]);
    }

    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        if (--obj->x_0f4167b4[1] <= 0) {
            if (obj->color.a > obj->x_0f4167b4[0]) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= x_f51cb721;
            }
        }
    } else {
        obj->frameCounter++;
    }
}

void match_model_fadeout(Object *obj) {
    if (--obj->x_0f4167b4[1] <= 0) {
        if (obj->x_0f4167b4[0] < obj->color.a) {
            obj->color.a -= obj->x_0f4167b4[0];
        } else {
            TASK_END(obj->currentTask);
            obj->flags |= x_f51cb721;
        }
    }
}

Object *match_msg_model_create(x_3da8fdd8 *msg, s32 context) {
    Object *obj;
    x_88f11482 pos;
    Model *a3;
    char x_f974a07e[80];

    audio_sfx_stop_bank(2);
    wad_strcpy(x_f974a07e, msg->name);
    wad_strcat(x_f974a07e, ".k2");

    a3 = sWadEntries[wad_entry_find(x_f974a07e, context)].x_4962fc73;
    pos.x = pos.y = pos.z = 0;
    obj = obj_create_with_model_ptr(&pos, 0x1000, msg->x_5cb18fd3, a3);

    if (obj != NULL) {
        obj->flags |= x_a816b63b;

        obj->x_0f4167b4[1] = msg->duration;
        obj->flags |= x_d13a68b5;
        if (msg->x_ba814dc8 != 0) {
            obj->color.a = 128;
            obj->x_0f4167b4[0] = msg->x_ba814dc8;
            obj->flags |= x_b6789b80;
        }
        obj->x_0f4167b4[2] = msg->x_1dc13257;
        obj->currentTask->delay = 2;
    }

    return obj;
}

void match_set_continue_cb(Object *x_cc1d0de5, Object *x_84ff873b) {
    sHudRootObj->currentTask->callback = match_post_ko_routing;
    sHudRootObj->currentTask->delay = 0;
    sHudRootObj->currentTask->flags = TASK_RUNNABLE;
    sHudRootObj->currentTask->delay = 30;
}

Object *match_screen_msg(s16 x_31ee45bf) {
    Object *obj;

    obj = match_msg_model_create(x_dd2c4e91 + x_31ee45bf, x_2587f84f);
    if (obj != NULL && x_31ee45bf == x_3d992fcd) {
        obj->x_450fdcd0 = match_set_continue_cb;
        obj->x_61f772e7 |= 8;
    }

    return obj;
}

Object *match_msg_model_delayed(s32 x_eb1fe45b, s32 x_84ff873b, u32 x_30bbe547) {
    s32 unused;
    Object *obj;

    obj = match_msg_model_create(x_c2354b9b + x_eb1fe45b, x_30bbe547);

    if (obj != NULL) {
        obj->currentTask->delay = x_84ff873b;
        obj->flags |= x_c537cafa;
        if (gWadCondLoad[x_30bbe547].x_03604d94) {
            obj->x_0f4167b4[2] = 7;
        }
    }

    audio_sfx_set_pan(0, 64);
    audio_sfx_set_pan(1, 64);
    sAudioForceMute = TRUE;
    return obj;
}

u16 match_round_msg_show(s32 x_9591016d) {
    x_3da8fdd8 *a0;
    Object *obj;

    if (gWadCondLoad[x_83106b21].x_b2b764b3 == x_adcfd05c - 1 &&
        gWadCondLoad[x_6f0b3be3].x_b2b764b3 == x_adcfd05c - 1) {
        a0 = &x_dd2c4e91[x_cd54037c];
    } else {
        a0 = &x_dd2c4e91[x_3ead7ac2];
    }
    obj = match_msg_model_create(a0, x_2587f84f);
    if (obj != NULL) {
        obj->frameCounter = x_9591016d * 2;
    }
    return a0->duration;
}

void match_attract_anim(Object *obj) {
    Object *x_aaadc3e8;

    obj->flags &= ~x_c537cafa;
    if ((x_59ce598c[1 - sWinnerIdx].buttons & x_0684c746) && obj->x_0f4167b4[1] == 0) {
        if (obj->frameCounter < obj->x_20d20338->x_8e601526) {
            obj->frameCounter += 30;
        }
        x_aaadc3e8 = sHudRootObj->x_e2f64c57[5];
        x_aaadc3e8->x_0f4167b4[1] -= 30;
    }

    obj->x_0f4167b4[1] = x_59ce598c[1 - sWinnerIdx].buttons; // probably @bug

    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        if (--obj->x_0f4167b4[1] <= 0) {
            if (obj->x_0f4167b4[0] < obj->color.a) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= x_f51cb721;
            }
        }
    } else {
        obj->frameCounter++;
    }
}

void match_kill_fighters(void) {
    Object *obj;

    for (obj = gObjectList; obj != NULL; obj = obj->x_2d5f3fbd) {
        if ((obj->flags & x_215d3747) || (obj->flags & x_0b94e8d0)) {
            obj->flags |= x_f51cb721;
        }
    }
}

void match_round_reset(Object *obj) {
    Object *v0;
    Object *v1;
    u32 i;

    x_824b9544[x_83106b21].x_cd14c741 = 0;
    x_824b9544[x_6f0b3be3].x_cd14c741 = 0;

    player_reinit(x_83106b21);
    player_reinit(x_6f0b3be3);

    obj->flags |= x_f51cb721;
    sWadUnk1 = gFrameCounter % 5;
    sWadUnk2 = 0;

    match_kill_fighters();
    fight_init();
    audio_unmute();

    v0 = obj->x_e2f64c57[4];
    if (v0 != NULL) {
        v0->flags |= x_f51cb721;
    }
    if (sWinnerMsgObj != NULL) {
        sWinnerMsgObj->flags |= x_f51cb721;
    }
    if (sKoMsgObj != NULL) {
        sKoMsgObj->flags |= x_f51cb721;
    }
    if (sAfterKoMsgObj != NULL) {
        sAfterKoMsgObj->flags |= x_f51cb721;
    }
    if (sContinueMsgObj != NULL) {
        sContinueMsgObj->flags |= x_f51cb721;
    }
    if (sDrawMsgObj != NULL) {
        sDrawMsgObj->flags |= x_f51cb721;
    }
    if (sSuddenDeathMsgObj != NULL) {
        sSuddenDeathMsgObj->flags |= x_f51cb721;
    }

    x_f4bce728->currentTask->callback = cam_intro_start_inverse;
    x_f4bce728->currentTask->delay = 0;
    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -400;
    x_6f8aa7af = FALSE;

    if (x_c8356c60 != 0) {
        sTimerObj->frameCounter = 3 + x_c8356c60 * 3;
        v1 = sTimerObj->x_e2f64c57[0];
        v1->frameCounter = 0;
        sTimerObj->currentTask->callback = task_remove_current;
    }

    sHealthPartL->x_e7f1952a = sHealthPartL->x_e7f1952a - sHealthPartL->x_b88b3756 + sHealthPartL->rightS - 88;
    sHealthPartL->x_b88b3756 = sHealthPartL->rightS - 88;
    sHealthPartR->rightS = sHealthPartR->x_b88b3756 + 80;

    sHealthBarSlideL = sHealthBarSlideR = sHealthFlashL = sHealthFlashR = 0;
    sCachedHealthR = sCachedHealthL = 80;

    D_80052D64[0] = D_80052D64[1] = D_80052D68[0] = D_80052D68[1] = D_80052D6C[0] = D_80052D6C[1] = D_8013C3C0[0] =
        D_8013C3C0[1] = D_80052D70[0] = D_80052D70[1] = D_80052D74[0] = D_80052D74[1] = 0;
    D_80052D78[0] = D_80052D78[1] = 2;

    if (!sIsDraw && gWadCondLoad[sWinnerIdx].x_b2b764b3 != 0) {
        sRoundIndicators[sWinnerIdx][gWadCondLoad[sWinnerIdx].x_b2b764b3 - 1]->frameCounter = 13;
    } else if (sIsDraw && gWadCondLoad[x_83106b21].x_b2b764b3 != 0 && gWadCondLoad[x_6f0b3be3].x_b2b764b3 != 0) {
        sRoundIndicators[x_83106b21][gWadCondLoad[x_83106b21].x_b2b764b3 - 1]->frameCounter = 13;
        sRoundIndicators[x_6f0b3be3][gWadCondLoad[x_6f0b3be3].x_b2b764b3 - 1]->frameCounter = 13;
    } else {
        for (i = 0; i < x_adcfd05c; i++) {
            sRoundIndicators[x_83106b21][i]->frameCounter = sRoundIndicators[x_6f0b3be3][i]->frameCounter = 12;
        }
    }

    x_824b9544[x_83106b21].obj->frameCounter = 2;
    x_824b9544[x_6f0b3be3].obj->frameCounter = 2;
    model_anim_load(x_824b9544[x_83106b21].obj);
    model_anim_load(x_824b9544[x_6f0b3be3].obj);

    mat4_ident_partial(&x_824b9544[x_83106b21].x_a4d7c80d.x_3fde9cd9);
    mat4_ident_partial(&x_824b9544[x_83106b21].x_022dff72.x_3fde9cd9);
    mat4_ident_partial(&x_824b9544[x_6f0b3be3].x_a4d7c80d.x_3fde9cd9);
    mat4_ident_partial(&x_824b9544[x_6f0b3be3].x_022dff72.x_3fde9cd9);

    model_transforms_update(x_824b9544[x_83106b21].obj);
    model_transforms_update(x_824b9544[x_6f0b3be3].obj);
    x_824b9544[x_83106b21].obj->x_2b06a023 = x_824b9544[x_83106b21].obj->frameCounter;
    x_824b9544[x_6f0b3be3].obj->x_2b06a023 = x_824b9544[x_6f0b3be3].obj->frameCounter;
    x_824b9544[x_83106b21].x_b9252303->flags &= ~TASK_TIME_BASED;
    x_824b9544[x_6f0b3be3].x_b9252303->flags &= ~TASK_TIME_BASED;

    sMenuState = 0x800;
    hud_score_create();
}

u32 match_move_time(Player *player, s32 x_84ff873b, u32 x_2092f891) {
    s32 temp;
    u32 res;

    player_exec_move(player, x_84ff873b, TRUE);

    temp = player->x_b9252303->params[1];
    if (x_2092f891 < player->x_68a6b5cd[temp].x_bab9966d + 120) {
        res = player->x_68a6b5cd[temp].x_bab9966d + 120;
    } else {
        res = x_2092f891;
    }
    return res;
}

u8 match_continue_pressed(void) {

    if ((x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) && gWadCondLoad[sWinnerIdx].x_03604d94) {
        x_59ce598c[1 - sWinnerIdx].enabled = TRUE;
        return (x_59ce598c[1 - sWinnerIdx].buttons & x_9cefe76c) != 0;
    } else {
        return (x_59ce598c[sWinnerIdx].buttons & x_9cefe76c) != 0;
    }
}

void match_continue_wait(Object *obj) {
    x_824b9544[x_83106b21].x_448f0851 = x_824b9544[x_6f0b3be3].x_448f0851 = 0;

    if (--obj->x_0f4167b4[1] < 0 && match_continue_pressed()) {
        match_round_reset(obj);
    }

    if (--obj->x_0f4167b4[0] < 0) {
        match_round_reset(obj);
    }
}

void match_fade_to_next(Object *obj) {
    x_824b9544[x_83106b21].x_448f0851 = x_824b9544[x_6f0b3be3].x_448f0851 = 0;

    if (--obj->x_0f4167b4[1] < 0 && match_continue_pressed()) {
        x_e30d50d2 |= x_bee364e0;
        TASK_END(obj->currentTask);
        x_e30d50d2 |= x_b9be821f;
        obj->flags |= x_f51cb721;
    }

    if (--obj->x_0f4167b4[0] < 0) {
        x_e30d50d2 |= x_bee364e0;
        TASK_END(obj->currentTask);
        x_e30d50d2 |= x_b9be821f;
        obj->flags |= x_f51cb721;
    }
}

void match_end_screen_check(Object *obj) {
    x_e38a6e19 = x_028e5846 >= x_c74743bd ? x_fa31c524 : x_ef3ab4fe; // not real mode? @bug?
    obj->currentTask->callback = match_fade_to_next;
}

void match_post_ko_routing(Object *obj) {
    Object *a2;
    s16 i;
    s16 a3;

    if (gWadCondLoad[x_83106b21].x_03604d94 || gWadCondLoad[x_6f0b3be3].x_03604d94) {
        a2 = match_screen_msg(x_692a98c7);
        x_e38a6e19 = SCREEN_ATTRACT;
        gWadCondLoad[x_83106b21].x_7d8e7a6f = gWadCondLoad[x_6f0b3be3].x_7d8e7a6f = 0;
    } else {
        a2 = match_screen_msg(x_692a98c7);
        x_e38a6e19 = SCREEN_WAIT;

        if (x_5e4e2788 == x_a5f164ca) {
            a3 = x_adcfd05c == gWadCondLoad[x_6f0b3be3].x_b2b764b3;
            present_set_screen(x_e483bf48 + a3);

            gWadCondLoad[1 - a3].x_03604d94 = TRUE;
            sLastWinnerIdx = 1 - a3;

            for (i = 0; i < x_edb381f3; i++) {
                D_800B6350[a3][i] = FALSE;
            }
        }
    }

    obj->currentTask->callback = match_fade_to_next;

    if (a2 != NULL) {
        a2->x_0f4167b4[1] = 10;
        a2->x_0f4167b4[0] = a2->x_20d20338->x_8e601526;
    } else {
        obj->x_0f4167b4[1] = 0;
        obj->x_0f4167b4[0] = 0;
    }
}

void match_continue_handler(Object *obj) {
    Object *v0;

    if (x_59ce598c[1 - sWinnerIdx].buttons & x_9cefe76c) {
        fight_reset();

        if (x_5e4e2788 == x_e483bf48) {
            D_800B6350[x_6f0b3be3][x_824b9544[x_6f0b3be3].x_eb1fe45b] = FALSE;
        } else if (x_5e4e2788 == x_557d3dd6) {
            D_800B6350[x_83106b21][x_824b9544[x_83106b21].x_eb1fe45b] = FALSE;
        }

        v0 = obj->x_e2f64c57[3];
        if (v0 != NULL) {
            v0->flags |= x_c537cafa;
            v0->currentTask->callback = task_remove_current;
        }

        match_round_reset(obj);
    }
}

void match_rematch_setup(Object *obj) {
    Object *a1;

    x_e30d50d2 |= x_86c5bc33;

    if (--obj->x_0f4167b4[2] == 0 || (--obj->x_0f4167b4[1] < 0 && match_continue_pressed())) {
        if (gWadCondLoad[x_83106b21].x_03604d94 || gWadCondLoad[x_6f0b3be3].x_03604d94) {
            obj->x_e2f64c57[5] = sAfterKoMsgObj = match_screen_msg(x_eab09ee3);
        } else {
            obj->x_e2f64c57[5] = sAfterKoMsgObj = match_screen_msg(x_b74cb64b);
        }
        obj->x_e2f64c57[3] = sContinueMsgObj = match_screen_msg(x_3d992fcd);

        x_59ce598c[1 - sWinnerIdx].enabled = TRUE;
        obj->currentTask->callback = match_continue_handler;
        a1 = obj->x_e2f64c57[4];
        if (a1 != NULL) {
            a1->flags |= x_f51cb721;
        }
        x_59ce598c[sWinnerIdx].x_c4397934 = FALSE;
        obj->x_e2f64c57[4] = obj->x_e2f64c57[5];
    }
}

x_09d6a3c8 match_result_callback(u32 x_30bbe547, u8 x_84ff873b) {
    x_09d6a3c8 a3;

    a3 = match_continue_wait;

    gWadCondLoad[x_30bbe547].x_b2b764b3++;
    if (gWadCondLoad[x_30bbe547].x_b2b764b3 == x_adcfd05c) {
        if (!x_84ff873b) {
            gWadCondLoad[sWinnerIdx].x_7d8e7a6f++;
            gWadCondLoad[1 - sWinnerIdx].x_7d8e7a6f = 0;
        }

        D_800B6368[gWadCondLoad[x_30bbe547].x_eb1fe45b].x_a962826d++;
        D_800B6368[gWadCondLoad[1 - x_30bbe547].x_eb1fe45b].x_3f3ac621++;
        sFirstFight = TRUE;

        switch (x_5e4e2788) {
            case x_e483bf48:
            case x_557d3dd6:
                if (!gWadCondLoad[x_30bbe547].x_03604d94) {
                    D_800B6350[1 - x_30bbe547][x_824b9544[1 - x_30bbe547].x_eb1fe45b] = TRUE;

                    if (char_select_random(1 - x_30bbe547) == -1) {
                        a3 = match_end_screen_check;
                    } else {
                        x_e38a6e19 = SCREEN_WAIT;
                        a3 = match_fade_to_next;
                    }
                } else {
                    a3 = match_rematch_setup;
                }
                break;
            case x_96f25e0a:
            case x_a5f164ca:
                a3 = match_rematch_setup;
                break;
            case x_3658fb97:
                x_e38a6e19 = SCREEN_ATTRACT;
                break;
        }
    }

    return a3;
}

void match_winner_setup(Object *obj) {
    s32 x_32f1d6e2;
    x_09d6a3c8 v02;

    x_32f1d6e2 = match_move_time(&x_824b9544[sWinnerIdx], (gFrameCounter & 1) ? x_fefa7415 : x_f4d3471e, 0x78);
    match_kill_fighters();
    obj->x_e2f64c57[4] = sWinnerMsgObj = match_msg_model_delayed(x_824b9544[sWinnerIdx].x_eb1fe45b, 6, sWinnerIdx);
    v02 = match_result_callback(sWinnerIdx, FALSE);

    obj->x_0f4167b4[0] = x_32f1d6e2 + 120;
    obj->x_0f4167b4[1] = 10;
    obj->x_0f4167b4[2] = 190;
    obj->currentTask->callback = v02;

    x_e30d50d2 &= ~x_dd99cbfb;
    x_824b9544[1 - sWinnerIdx].obj->flags |= x_c537cafa;
    x_824b9544[sWinnerIdx].obj->pos.x = x_824b9544[sWinnerIdx].obj->pos.y = x_824b9544[sWinnerIdx].obj->pos.z = 0;
    x_824b9544[1 - sWinnerIdx].obj->pos.x = x_824b9544[1 - sWinnerIdx].obj->pos.y =
        x_824b9544[1 - sWinnerIdx].obj->pos.z = 0;

    x_824b9544[x_83106b21].obj->x_224610f1.y = 0;
    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -400;

    if (gWadCondLoad[sWinnerIdx].x_eb1fe45b != x_b52da315) {
        x_824b9544[sWinnerIdx].obj->flags |= x_3e24eba7;
    }

    x_824b9544[sWinnerIdx].obj->flags &= ~(x_da021b29 | x_da584e3c);
}

void match_draw_setup(Object *obj) {
    s32 pad;
    Object *v0;
    x_09d6a3c8 a3;

    v0 = match_screen_msg(x_baa70474);
    a3 = match_continue_wait;

    if (v0 != NULL) {
        v0->currentTask->delay = 5;
    }

    sDrawMsgObj = v0;

    match_move_time(&x_824b9544[x_6f0b3be3], x_f6ac8484, match_move_time(&x_824b9544[x_83106b21], x_f6ac8484, 0x78));

    if (x_adcfd05c == gWadCondLoad[x_83106b21].x_b2b764b3 + 1) {
        a3 = match_result_callback(x_83106b21, TRUE);
    } else {
        gWadCondLoad[x_83106b21].x_b2b764b3++;
    }

    if (x_adcfd05c == gWadCondLoad[x_6f0b3be3].x_b2b764b3 + 1) {
        a3 = match_result_callback(x_6f0b3be3, TRUE);
    } else {
        gWadCondLoad[x_6f0b3be3].x_b2b764b3++;
    }

    obj->x_0f4167b4[0] = 245;
    obj->x_0f4167b4[1] = 10;
    obj->x_0f4167b4[2] = 190;
    obj->x_e2f64c57[4] = v0;

    obj->currentTask->callback = a3;
}

void match_win_input_wait(Object *obj) {
    Object *a0;

    if (--obj->x_0f4167b4[0] > 0) {
        if ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
            a0 = obj->x_e2f64c57[4];
            a0->flags |= x_f51cb721;

            if (x_59ce598c[x_83106b21].buttons & x_9cefe76c) {
                x_59ce598c[x_83106b21].x_c4397934 = FALSE;
            }
            if (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c) {
                x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE;
            }
        } else {
            return;
        }
    }

    if (sIsDraw) {
        obj->currentTask->callback = match_draw_setup;
    } else {
        x_59ce598c[1 - sWinnerIdx].enabled = FALSE;
        x_59ce598c[1 - sWinnerIdx].buttons = 0;
        obj->currentTask->callback = match_winner_setup;
    }
}

void match_post_ko_transition(Object *obj) {
    if (x_824b9544[x_83106b21].flags & x_22ebc053) {
        if (--x_824b9544[x_83106b21].x_448f0851 > 20) {
            x_824b9544[x_83106b21].x_448f0851 = 20;
        } else {
            player_select_move(&x_824b9544[x_83106b21], TRUE);
        }
    } else if (x_824b9544[x_6f0b3be3].flags & x_22ebc053) {
        if (--x_824b9544[x_6f0b3be3].x_448f0851 > 20) {
            x_824b9544[x_6f0b3be3].x_448f0851 = 20;
        } else {
            player_select_move(&x_824b9544[x_6f0b3be3], TRUE);
        }
    } else if ((x_824b9544[x_83106b21].flags & x_a45101c0) && (x_824b9544[x_6f0b3be3].flags & x_a45101c0)) {
        if ((x_824b9544[x_83106b21].x_7f68c36b->flags & x_037894c1) && x_824b9544[x_83106b21].x_cd14c741 != 4) {
            player_exec_move(&x_824b9544[x_83106b21], x_26778114, FALSE);
        } else if (x_824b9544[x_83106b21].x_cd14c741 != 17) {
            player_exec_move(&x_824b9544[x_83106b21], x_ee946ac0, FALSE);
        }

        if ((x_824b9544[x_6f0b3be3].x_7f68c36b->flags & x_037894c1) && x_824b9544[x_6f0b3be3].x_cd14c741 != 4) {
            player_exec_move(&x_824b9544[x_6f0b3be3], x_26778114, FALSE);
        } else if (x_824b9544[x_6f0b3be3].x_cd14c741 != 17) {
            player_exec_move(&x_824b9544[x_6f0b3be3], x_ee946ac0, FALSE);
        }

        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

        obj->currentTask->callback = match_win_input_wait;
        obj->currentTask->delay = 10;
        obj->x_0f4167b4[0] = 80;
        D_80080234 = TRUE;
    }
}

void match_wait_flag(Object *obj) {
    if (D_80080234) {
        obj->currentTask->callback = match_ko_decision;
    }
}

void match_blink_cb(Object *obj) {
    if (++obj->x_0f4167b4[0] & 8) {
        obj->flags &= ~x_c537cafa;
    } else {
        obj->flags |= x_c537cafa;
    }
}

void match_blink_kill_cb(Object *obj) {
    if (D_80080234) {
        obj->flags |= x_f51cb721;
    }
    match_blink_cb(obj);
}

void match_ko_overlay(Object *obj) {
    x_f0d7e70f x_331089fa = { 0x26, match_blink_kill_cb, 0x4000000, 0x1001, "bars.sp2" };
    x_88f11482 x_2a89e429 = { 250, 220, 0, 0 };

    x_59ce598c[sWinnerIdx].enabled = TRUE;
    x_e30d50d2 &= ~x_dd99cbfb;
    if (TRUE) {
        D_80080234 = TRUE;
    }
    obj->currentTask->callback = match_ko_decision;
    obj->currentTask->delay = 45;
    match_kill_fighters();
}

void match_ko_overlay_wait(Object *obj) {
    Object *a0;

    if (--obj->x_0f4167b4[0] > 0) {
        if (x_59ce598c[sWinnerIdx].buttons & x_9cefe76c) {
            a0 = obj->x_e2f64c57[4];
            if (a0 != NULL) {
                a0->flags |= x_f51cb721;
            }

            if (x_59ce598c[x_83106b21].buttons & x_9cefe76c) {
                x_59ce598c[x_83106b21].x_c4397934 = FALSE;
            }
            if (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c) {
                x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE;
            }
        } else {
            return;
        }
    }

    obj->currentTask->callback = match_ko_overlay;
}

void match_ko_decision(Object *obj) {
    x_e30d50d2 &= ~x_dd99cbfb;

    if (!D_80080234) {
        if (x_824b9544[x_83106b21].obj->x_9200c538 == gWadCondLoad[x_83106b21].x_c35c64af &&
                x_824b9544[x_6f0b3be3].obj->x_9200c538 == 0 ||
            x_824b9544[x_83106b21].obj->x_9200c538 == 0 &&
                x_824b9544[x_6f0b3be3].obj->x_9200c538 == gWadCondLoad[x_6f0b3be3].x_c35c64af) {
            obj->x_e2f64c57[4] = sKoMsgObj = match_screen_msg(x_25af9d6d);
            obj->x_0f4167b4[0] = 90;
            x_59ce598c[sWinnerIdx].enabled = TRUE;
            obj->currentTask->callback = match_ko_overlay_wait;
        } else {
            obj->currentTask->callback = match_ko_overlay;
        }
    } else {
        x_59ce598c[sWinnerIdx].enabled = TRUE;
        if (sIsDraw) {
            x_59ce598c[1 - sWinnerIdx].enabled = TRUE;
            obj->currentTask->callback = match_draw_setup;
        } else {
            obj->currentTask->callback = match_winner_setup;
        }
    }
}

void match_ko_check(Object *obj) {
    Object *x_1b70419e;

    if (sFightLocked || x_824b9544[x_83106b21].obj->x_9200c538 <= 0 || x_824b9544[x_6f0b3be3].obj->x_9200c538 <= 0) {
        hud_score_cleanup();
        sFightLocked = TRUE;
        if (!(x_e30d50d2 & x_86c5bc33)) {
            x_e30d50d2 |= x_86c5bc33;
            return;
        }

        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = FALSE;
        if (x_824b9544[x_83106b21].obj->x_9200c538 > x_824b9544[x_6f0b3be3].obj->x_9200c538) {
            sWinnerIdx = x_83106b21;
        } else {
            sWinnerIdx = x_6f0b3be3;
        }

        sIsDraw = (x_824b9544[x_83106b21].obj->x_9200c538 == x_824b9544[x_6f0b3be3].obj->x_9200c538);

        if (sFightLocked && x_824b9544[x_83106b21].obj->x_9200c538 != 0 &&
            x_824b9544[x_6f0b3be3].obj->x_9200c538 != 0) {
            x_1b70419e = match_screen_msg(x_7dab12f3);
            sSuddenDeathMsgObj = x_1b70419e;
            obj->x_e2f64c57[4] = x_1b70419e;
            obj->currentTask->callback = match_post_ko_transition;
        } else {
            obj->currentTask->callback = match_ko_decision;
        }

        D_80080234 = FALSE;
        obj->currentTask->delay = 45;
    }
}

void match_attract_result(Object *obj) {
    x_e30d50d2 |= x_86c5bc33;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

    if (++obj->x_0f4167b4[0] > 900) {
        x_e38a6e19 = SCREEN_OPTIONS;
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
    } else if ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
        x_e30d50d2 |= x_bee364e0;
        x_e38a6e19 = SCREEN_ATTRACT;
        obj->flags |= x_f51cb721;
    }
}

void match_round_start_exec(Object *obj) {
    if (x_5e4e2788 == x_3658fb97) {
        obj->currentTask->callback = match_attract_result;
        obj->x_0f4167b4[0] = 0;
        x_e30d50d2 |= x_86c5bc33;
    } else {
        obj->currentTask->callback = match_ko_check;
        x_e30d50d2 &= ~x_86c5bc33;
    }

    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    x_824b9544[x_83106b21].flags &= ~x_4d950171;
    x_824b9544[x_6f0b3be3].flags &= ~x_4d950171;

    if (gWadCondLoad[x_83106b21].x_03604d94) {
        x_824b9544[x_83106b21].x_81570fde.x_b2c79d6e &= ~x_c74d666c;
    }
    if (gWadCondLoad[x_6f0b3be3].x_03604d94) {
        x_824b9544[x_6f0b3be3].x_81570fde.x_b2c79d6e &= ~x_c74d666c;
    }

    hud_timer_start();
}

void match_round_announce(Object *obj) {
    Object *v0;
    obj->currentTask->callback = match_round_start_exec;
    v0 = match_screen_msg(x_0f44231b);
    obj->currentTask->delay = v0->x_20d20338->x_8e601526 + 20;
}

void match_task_exec(Object *obj) {
    task_execute(obj);
}

void match_round_start(void) {
    sHudRootObj = obj_create_task(match_task_exec, 1);
    sFightLocked = FALSE;
    x_6f8aa7af = 0;

    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = FALSE;
    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    sHudActive = FALSE;
    D_80080234 = FALSE;

    if (gWadCondLoad[x_83106b21].x_03604d94) {
        x_824b9544[x_83106b21].x_81570fde.x_b2c79d6e |= x_c74d666c;
    }
    if (gWadCondLoad[x_6f0b3be3].x_03604d94) {
        x_824b9544[x_6f0b3be3].x_81570fde.x_b2c79d6e |= x_c74d666c;
    }

    sHudRootObj->currentTask->callback = match_round_announce;
    sHudRootObj->currentTask->delay = 0;
    sHudRootObj->currentTask->flags = TASK_RUNNABLE;
    sHudRootObj->currentTask->delay =
        match_round_msg_show(gWadCondLoad[x_83106b21].x_b2b764b3 + gWadCondLoad[x_6f0b3be3].x_b2b764b3);
    sWinnerMsgObj = sKoMsgObj = sAfterKoMsgObj = sContinueMsgObj = sSuddenDeathMsgObj = sDrawMsgObj = NULL;
}
