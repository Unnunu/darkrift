#include "common.h"
#include "PR/gt.h"
#include "task.h"

extern x_88f11482 D_8004A5D0[];
extern x_88f11482 D_8004A680[];

extern s32 D_80081434;
extern s32 D_80081438;

void hud_dust_sp3_init(Object *obj);

x_8b39d614 sDustHitObjDef = { "dusthit.sp3", hud_dust_sp3_init, 0, 0x1100, 0, 0x2800, 0 };
s16 sRoundWinCount = 0;
s16 sHealthBarSlideL = 0;
s16 sHealthBarSlideR = 0;
Vtx sHealthBarVtxL[2][4] = { { { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } },
                             { { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } } };
Vtx sHealthBarVtxR[2][4] = { { { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } },
                             { { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                               { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } } };
x_88f11482 sDigitPos1 = { 63, 220, 0, 0 };
x_88f11482 sDigitPos2 = { 72, 220, 0, 0 };
x_88f11482 sDigitPos3 = { 81, 220, 0, 0 };
x_88f11482 sDigitPos4 = { 268, 220, 0, 0 };
x_88f11482 sDigitPos5 = { 277, 220, 0, 0 };
x_88f11482 sDigitPos6 = { 286, 220, 0, 0 };
x_88f11482 *sDigitPosPtr[] = { &sDigitPos1, &sDigitPos2, &sDigitPos3, &sDigitPos4, &sDigitPos5, &sDigitPos6 };

s16 sCachedHealthL;
s16 sCachedHealthR;
x_425d6ed3 *sHealthPartL;
x_425d6ed3 *sHealthPartR;
Object *sHudRootObj;
Object *sTimerObj;
Object *sHealthBarTask;
Object *sScoreObj;
u16 sWinnerIdx;
u16 sIsDraw;
u16 sHudActive;
s32 sHudUnused;
Object *sRoundIndicators[2][10];
s16 sHealthFlashL;
s16 sHealthFlashR;

void results_p1_controls_hint(Object *obj);
void results_p1_pause(Object *obj);
void results_p1_control_continue(Object *obj);
void hud_round_win_anim(void);

void hud_dust_fade_cb(Object *obj) {
    obj->flags &= ~x_c537cafa;
    if (obj->frameCounter <= 12) {
        obj->frameCounter++;
        if (obj->color.a > 100) {
            obj->color.a -= 8;
        } else if (obj->color.a > 3) {
            obj->color.a -= 3;
        }
        obj->currentTask->delay = 2;
    } else {
        obj->flags |= x_c537cafa | x_f51cb721;
        TASK_END(obj->currentTask);
    }
}

void hud_dust_fast_fade_cb(Object *obj) {
    if (--obj->x_0f4167b4[1] <= 0) {
        obj->flags &= ~x_c537cafa;
        if (obj->frameCounter <= 8) {
            obj->frameCounter++;
            if (obj->color.a > 100) {
                obj->color.a -= 8;
            } else if (obj->color.a > 4) {
                obj->color.a -= 2;
            }
            obj->currentTask->delay = 2;
        } else {
            obj->flags |= x_c537cafa | x_f51cb721;
            TASK_END(obj->currentTask);
        }
    }
}

void hud_bone_to_world(Object *obj, x_6fc0b62f *x_84ff873b, x_88f11482 *x_b35af211) {
    x_88f11482 pos;

    pos.x = x_84ff873b->x_1422e8f9;
    pos.y = x_84ff873b->x_6f7546e4;
    pos.z = x_84ff873b->x_95b3e972;

    mat4_ident_partial(&gMat4Temp);
    mat4_set_translation(&gMat4Temp, &pos);
    mat4_mul(&gMat4Temp, &obj->x_20d20338->transforms[x_84ff873b->x_32485e13].x_0c1a9bdd);

    x_b35af211->x = gMat4Temp.w.x;
    x_b35af211->y = gMat4Temp.w.y;
    x_b35af211->z = gMat4Temp.w.z;
}

void hud_circular_offset(s16 x_cc1d0de5, x_88f11482 *x_84ff873b, x_88f11482 *x_2092f891) {
    s32 x_32f1d6e2;
    s32 x_5aee6615;
    s32 x_5bbba600;
    s32 x_dd7ffac5;
    s32 x_4346f5cb;

    x_5aee6615 = x_84ff873b->x;
    x_5bbba600 = x_84ff873b->z;
    x_32f1d6e2 = (u32) (sqrtf(x_84ce1cfb(x_5aee6615) + x_84ce1cfb(x_5bbba600)) + 0.5);
    x_dd7ffac5 = x_cc1d0de5 + x_32f1d6e2;
    x_4346f5cb = atan2_lut(x_5bbba600, x_5aee6615);

    x_2092f891->x = (sin_fixed(x_4346f5cb) * x_dd7ffac5) >> 12;
    x_2092f891->z = (-sin_fixed(x_4346f5cb + 0x400) * x_dd7ffac5) >> 12;
    x_2092f891->y = x_84ff873b->y;
}

void hud_dust_spawn_cb(Object *obj) {
    Object *v0;
    Object *v1;

    if (--obj->x_f9866d50 <= 0) {
        obj->x_f9866d50 = obj->x_0f4167b4[2];
        v1 = obj->x_e2f64c57[3];
        v0 = obj_create_from_props(&v1->pos, &sDustHitObjDef, x_2587f84f);
        if (v0 == NULL) {
            return;
        } else {
            v0->currentTask->callback = hud_dust_fade_cb;
            v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
            if (--obj->x_0f4167b4[1] < 0) {
                obj->flags |= x_f51cb721;
            }
        }
    }
}

void hud_dust_spawner(Object *obj) {
    Object *v0;
    Player *player = (Player *) obj->x_e2f64c57[0];

    v0 = obj_create_task(hud_dust_spawn_cb, 0x1000);
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

void hud_dust_follow_player(Object *obj) {
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
        hud_circular_offset(obj->x_0f4167b4[2], &x_dd7ffac5, &obj->pos);
    } else {
        obj->pos.x = x_dd7ffac5.x;
        obj->pos.z = x_dd7ffac5.z;
    }

    obj->pos.y = 0;
    obj->currentTask->callback = hud_dust_fast_fade_cb;
}

void hud_dust_sp3_init(Object *obj) {
    obj->currentTask->callback = hud_dust_follow_player;
}

void hud_dust_ring_spawn(Object *obj) {
    Object *v0;
    s16 s0 = ((Player *) obj->x_e2f64c57[0])->x_30bbe547;

    v0 = obj_create_from_props(&sZeroPosition, &sDustHitObjDef, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->currentTask->delay = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 0;
        v0->x_0f4167b4[2] = 150;
        v0->color.a = 60;
        v0->flags |= x_c537cafa;
    }

    v0 = obj_create_from_props(&sZeroPosition, &sDustHitObjDef, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->currentTask->delay = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 3;
        v0->x_0f4167b4[2] = 50;
        v0->color.a = 60;
        v0->flags |= x_c537cafa;
    }

    v0 = obj_create_from_props(&sZeroPosition, &sDustHitObjDef, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->currentTask->delay = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 5;
        v0->x_0f4167b4[2] = -200;
        v0->color.a = 40;
        v0->flags |= x_c537cafa;
    }

    v0 = obj_create_from_props(&sZeroPosition, &sDustHitObjDef, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->currentTask->delay = 10;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 7;
        v0->x_0f4167b4[2] = 100;
        v0->color.a = 40;
        v0->flags |= x_c537cafa;
    }

    v0 = obj_create_from_props(&sZeroPosition, &sDustHitObjDef, x_2587f84f);
    if (v0 == NULL) {
        return;
    } else {
        v0->currentTask->delay = 10;
        v0->x_860b579a = v0->x_2fa0bbed = v0->x_3e400065 = 0x64000;
        v0->x_f9866d50 = 1;
        v0->x_0f4167b4[0] = s0;
        v0->x_0f4167b4[1] = 9;
        v0->x_0f4167b4[2] = -250;
        v0->color.a = 30;
        v0->flags |= x_c537cafa;
    }
}

void hud_dust_line_spawn(Object *obj) {
    u32 i;
    Object *v0;
    s16 s4 = ((Player *) obj->x_e2f64c57[0])->x_30bbe547;
    s32 a, b;

    a = 0;
    b = -250;
    for (i = 0; i < 13; i++) {
        v0 = obj_create_from_props(&sZeroPosition, &sDustHitObjDef, x_2587f84f);
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

void hud_ko_countdown(Object *obj) {
    x_59ce598c[x_83106b21].enabled = FALSE;
    x_59ce598c[x_6f0b3be3].enabled = FALSE;

    if (obj->x_0f4167b4[0] == 0) {
        if (x_824b9544[x_83106b21].x_a4b33e43 == 0 && x_824b9544[x_6f0b3be3].x_a4b33e43 == 0) {
            hud_round_win_anim();
            obj->x_0f4167b4[0] = 240;
        }
    } else {
        obj->x_0f4167b4[0]--;
        if (obj->x_0f4167b4[0] == 0) {
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
        }
    }
}

s16 hud_health_width(s16 x_30bbe547) {
    return (u32) (x_824b9544[x_30bbe547].obj->x_9200c538 * 80 * 0x10000) / 400 / 0x10000;
}

void hud_quad_submit(Vtx *vtx) {
    Gfx *gfx = sQuadDl;

    if (gGfxFlags & GFX_SKIP_SCENE) {
        return;
    }

    sQuadBatch.header.x_09cf7a45 = 0;
    sQuadBatch.header.x_1256da71 = 0;
    sQuadBatch.header.x_4c5e05f8 = 4;
    sQuadBatch.header.x_ed66866b = 0;
    sQuadBatch.header.x_8a54e96a = 2;
    sQuadBatch.header.x_70b508ea = 2;
    sQuadBatch.header.x_b7ba6d35 = sQuadDl;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&sQuadBatch.header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);

    x_50746900(gExtraBatchPtr, NULL, &sQuadBatch, vtx, sQuadTri);
}

void hud_health_bar_update(Object *obj) {
    s32 unused;
    s16 x_6913166b;
    s16 a2;
    s16 x_f6289181;
    s16 x_4346f5cb;

    x_6913166b = D_8005BFCE;

    if (sFightLocked) {
        sHealthBarSlideL = sHealthBarSlideR = sHealthFlashL = sHealthFlashR = 0;
    }

    if (sHealthFlashL != 0) {
        hud_quad_submit(sHealthBarVtxL[x_6913166b]);
        sHealthFlashL--;
    } else if (sHealthBarSlideL > 0) {
        sHealthBarSlideL--;
        sHealthBarVtxL[x_6913166b][0].v.ob[0] = sHealthBarVtxL[x_6913166b][2].v.ob[0] =
            sHealthBarVtxL[x_6913166b][1].v.ob[0] - 4 * sHealthBarSlideL;
        hud_quad_submit(sHealthBarVtxL[x_6913166b]);
    }

    x_4346f5cb = hud_health_width(x_83106b21);
    if (x_4346f5cb != sCachedHealthL) {
        a2 = sCachedHealthL - x_4346f5cb;
        sHealthFlashL = 30 - sHealthFlashL - sHealthBarSlideL;
        if (sHealthFlashL < 0) {
            sHealthFlashL = 0;
        }

        sHealthBarSlideL += a2;
        sHealthPartL->x_b88b3756 += a2;
        sHealthPartL->x_e7f1952a += a2;
        if (sHealthPartL->x_b88b3756 >= sHealthPartL->rightS) {
            sHealthPartL->x_b88b3756 = sHealthPartL->rightS;
        }

        sHealthBarVtxL[0][1].v.ob[0] = sHealthBarVtxL[1][1].v.ob[0] = sHealthBarVtxL[0][3].v.ob[0] =
            sHealthBarVtxL[1][3].v.ob[0] = (35 + sHealthPartL->x_b88b3756) << 2;
        sHealthBarVtxL[0][0].v.ob[0] = sHealthBarVtxL[1][0].v.ob[0] = sHealthBarVtxL[0][2].v.ob[0] =
            sHealthBarVtxL[1][2].v.ob[0] = sHealthBarVtxL[0][1].v.ob[0] - 4 * sHealthBarSlideL;

        hud_quad_submit(sHealthBarVtxL[x_6913166b]);
        sCachedHealthL = x_4346f5cb;
    }

    if (sHealthFlashR != 0) {
        hud_quad_submit(sHealthBarVtxR[x_6913166b]);
        sHealthFlashR--;
    } else if (sHealthBarSlideR > 0) {
        sHealthBarSlideR--;
        sHealthBarVtxR[x_6913166b][1].v.ob[0] = sHealthBarVtxR[x_6913166b][3].v.ob[0] =
            sHealthBarVtxR[x_6913166b][0].v.ob[0] + 4 * sHealthBarSlideR;
        hud_quad_submit(sHealthBarVtxR[x_6913166b]);
    }

    x_f6289181 = hud_health_width(x_6f0b3be3);
    if (x_f6289181 != sCachedHealthR) {
        a2 = sCachedHealthR - x_f6289181;
        // clang-format off
        sHealthFlashR = 30 - sHealthFlashR - sHealthBarSlideR;\
        if (sHealthFlashR < 0) {
            sHealthFlashR = 0;
        }
        // clang-format on

        sHealthBarSlideR += a2;
        sHealthPartR->rightS -= a2;
        if (sHealthPartR->x_b88b3756 >= sHealthPartR->rightS) {
            sHealthPartR->x_b88b3756 = sHealthPartR->rightS;
        }

        sHealthBarVtxR[0][0].v.ob[0] = sHealthBarVtxR[1][0].v.ob[0] = sHealthBarVtxR[0][2].v.ob[0] =
            sHealthBarVtxR[1][2].v.ob[0] = (217 + sHealthPartR->rightS) << 2;
        sHealthBarVtxR[0][1].v.ob[0] = sHealthBarVtxR[1][1].v.ob[0] = sHealthBarVtxR[0][3].v.ob[0] =
            sHealthBarVtxR[1][3].v.ob[0] = sHealthBarVtxR[0][0].v.ob[0] + 4 * sHealthBarSlideR;

        hud_quad_submit(sHealthBarVtxR[x_6913166b]);
        sCachedHealthR = x_f6289181;
    }
}

void hud_round_win_anim(void) {
    s16 v0, v1;

    v0 = x_824b9544[x_83106b21].obj->x_9200c538;
    v1 = x_824b9544[x_6f0b3be3].obj->x_9200c538;
    if (v0 > v1) {
        player_exec_move(&x_824b9544[x_83106b21], x_fefa7415, 1);
        player_exec_move(&x_824b9544[x_6f0b3be3], x_f6ac8484, 1);
    } else if (v0 < v1) {
        player_exec_move(&x_824b9544[x_83106b21], x_f6ac8484, 1);
        player_exec_move(&x_824b9544[x_6f0b3be3], x_fefa7415, 1);
    } else {
        player_exec_move(&x_824b9544[x_83106b21], x_f6ac8484, 1);
        player_exec_move(&x_824b9544[x_6f0b3be3], x_f6ac8484, 1);
    }
}

void hud_timer_cb(Object *obj) {
    Object *v1;

    if (sFightLocked) {
        TASK_END(obj->currentTask);
    }

    obj->currentTask->delay = 60;

    v1 = obj->x_e2f64c57[0];
    if (--v1->frameCounter < 0) {
        v1->frameCounter = 9;
        if (--obj->frameCounter < 0) {
            obj->frameCounter = 0;
            sFightLocked = TRUE;
            v1->frameCounter = 0;
            TASK_END(obj->currentTask);
        }
    }
}

void hud_timer_start(void) {
    if (x_5e4e2788 != x_79c2dc5b && x_c8356c60 != 0) {
        sTimerObj->currentTask->callback = hud_timer_cb;
        sTimerObj->currentTask->delay = 0;
        sTimerObj->currentTask->flags = TASK_RUNNABLE;
        sHudRootObj->currentTask->delay = 120;
    }
}

void hud_score_cleanup(void) {
    s16 i = 0;
    Object *a0;

    if (sScoreObj != NULL) {
        sScoreObj->flags |= x_f51cb721;
        sScoreObj->flags &= ~x_5a44854c;
        D_80081438++;
        D_80081434++;

        while (sScoreObj->x_e2f64c57[i] != NULL) {
            D_80081438++;
            D_80081434++;
            sScoreObj->x_e2f64c57[i]->flags |= x_f51cb721;
            sScoreObj->x_e2f64c57[i]->flags &= ~x_5a44854c;
            i++;
        }

        sScoreObj = NULL;
    }
}

void hud_score_create(void) {
    x_f0d7e70f x_8a9089b3 = { 28, NULL, x_5a44854c, 0x1001, "bars.sp2" };
    x_f0d7e70f x_331089fa = { 27, NULL, x_5a44854c, 0x1001, "bars.sp2" };
    x_88f11482 x_2a89e429 = { 32, 220, 0, 0 };
    x_88f11482 x_081c4eef = { 236, 220, 0, 0 };
    s16 s0;
    s16 s3;
    s16 s2;
    Object *v0;

    sScoreObj = NULL;
    s0 = gWadCondLoad[x_83106b21].x_7d8e7a6f;
    if (s0 != 0) {
        sScoreObj = obj_create_from_def(&x_2a89e429, &x_331089fa, x_2587f84f);
        D_80081438--;
        D_80081434--;
        s3 = 0;
        s2 = 0;

        if (s0 >= 1000) {
            s0 = 1;
            gWadCondLoad[x_83106b21].x_7d8e7a6f = 1;
        }

        if (s0 >= 100) {
            v0 = obj_create_from_def(sDigitPosPtr[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->frameCounter = 28 + (s0 / 100);
            sScoreObj->x_e2f64c57[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 100;
            task_free_list(v0->taskListHead);
            v0->taskListHead = NULL;
        }

        if (gWadCondLoad[x_83106b21].x_7d8e7a6f >= 10) {
            v0 = obj_create_from_def(sDigitPosPtr[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->frameCounter = 28 + (s0 / 10);
            sScoreObj->x_e2f64c57[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 10;
            task_free_list(v0->taskListHead);
            v0->taskListHead = NULL;
        }

        v0 = obj_create_from_def(sDigitPosPtr[s3], &x_8a9089b3, x_2587f84f);
        D_80081438--;
        v0->frameCounter = 28 + s0;
        sScoreObj->x_e2f64c57[s2] = v0;
        s2++;
        sScoreObj->x_e2f64c57[s2] = NULL;
        task_free_list(v0->taskListHead);
        v0->taskListHead = NULL;

        task_free_list(sScoreObj->taskListHead);
        sScoreObj->taskListHead = NULL;
    }

    s0 = gWadCondLoad[x_6f0b3be3].x_7d8e7a6f;
    if (s0 != 0) {
        sScoreObj = obj_create_from_def(&x_081c4eef, &x_331089fa, x_2587f84f);
        D_80081438--;
        s3 = 3;
        s2 = 0;

        if (s0 >= 1000) {
            s0 = 1;
            gWadCondLoad[x_6f0b3be3].x_7d8e7a6f = 1;
        }

        if (s0 >= 100) {
            v0 = obj_create_from_def(sDigitPosPtr[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->frameCounter = 28 + (s0 / 100);
            sScoreObj->x_e2f64c57[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 100;
            task_free_list(v0->taskListHead);
            v0->taskListHead = NULL;
        }

        if (gWadCondLoad[x_6f0b3be3].x_7d8e7a6f >= 10) {
            v0 = obj_create_from_def(sDigitPosPtr[s3], &x_8a9089b3, x_2587f84f);
            D_80081438--;
            v0->frameCounter = 28 + (s0 / 10);
            sScoreObj->x_e2f64c57[s2] = v0;
            s2++;

            s0 = s0 % 10;
            s3++;
            task_free_list(v0->taskListHead);
            v0->taskListHead = NULL;
        }

        v0 = obj_create_from_def(sDigitPosPtr[s3], &x_8a9089b3, x_2587f84f);
        D_80081438--;
        v0->frameCounter = 28 + s0;
        sScoreObj->x_e2f64c57[s2] = v0;
        s2++;
        sScoreObj->x_e2f64c57[s2] = NULL;
        task_free_list(v0->taskListHead);
        v0->taskListHead = NULL;

        task_free_list(sScoreObj->taskListHead);
        sScoreObj->taskListHead = NULL;
    }
}

void hud_setup(void) {
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

    obj_create_from_def(&x_6b913371, &x_24cd786b, x_2587f84f);

    switch (x_c8356c60) {
        case 0:
            break;
        case 1:
        case 2:
            x_65cbb149 = obj_create_from_def(&x_30a44af1, &x_fd599243, x_2587f84f);
            v0 = obj_create_from_def(&x_4a496b1d, &x_cadba9e3, x_2587f84f);
            v0->frameCounter = x_c8356c60 * 3 + 3;
            v0->x_e2f64c57[0] = x_65cbb149;
            sTimerObj = v0;
            break;
    }

    v0 = obj_create_from_def(&x_a438747c, &x_4fc490a9, x_2587f84f);
    v0->frameCounter = 11;
    task_free_list(v0->taskListHead);
    v0->taskListHead = NULL;

    v0 = obj_create_from_def(&x_5b215acc, &x_4fc490a9, x_2587f84f);
    v0->frameCounter = 11;
    task_free_list(v0->taskListHead);
    v0->taskListHead = NULL;

    s0 = 0;
    for (s1 = 0; s1 < gWadCondLoad[x_83106b21].x_b2b764b3; s1++) {
        sRoundIndicators[x_83106b21][s1] = v0 = obj_create_from_def(&x_5c787447, &x_4fc490a9, x_2587f84f);
        v0->frameCounter = 13;
        x_5c787447.x -= 8;
        s0++;
        task_free_list(v0->taskListHead);
        v0->taskListHead = NULL;
    }

    for (; s0 < x_adcfd05c; s0++) {
        sRoundIndicators[x_83106b21][s0] = v0 = obj_create_from_def(&x_5c787447, &x_4fc490a9, x_2587f84f);
        v0->frameCounter = 12;
        x_5c787447.x -= 8;
        task_free_list(v0->taskListHead);
        v0->taskListHead = NULL;
    }

    s0 = 0;
    for (s1 = 0; s1 < gWadCondLoad[x_6f0b3be3].x_b2b764b3; s1++) {
        sRoundIndicators[x_6f0b3be3][s1] = v0 = obj_create_from_def(&x_af0e6490, &x_4fc490a9, x_2587f84f);
        v0->frameCounter = 13;
        x_af0e6490.x += 8;
        s0++;
        task_free_list(v0->taskListHead);
        v0->taskListHead = NULL;
    }

    for (; s0 < x_adcfd05c; s0++) {
        sRoundIndicators[x_6f0b3be3][s0] = v0 = obj_create_from_def(&x_af0e6490, &x_4fc490a9, x_2587f84f);
        v0->frameCounter = 12;
        x_af0e6490.x += 8;
        task_free_list(v0->taskListHead);
        v0->taskListHead = NULL;
    }

    v0 = obj_create_from_def(&x_840385a0, &x_4fc490a9, x_2587f84f);
    v0->frameCounter = 15;
    sHealthPartL = v0->x_904eaf67->x_a34b89cc[15].parts;
    sHealthPartL->x_e7f1952a = sHealthPartL->x_e7f1952a - sHealthPartL->x_b88b3756 + sHealthPartL->rightS - 88;
    sHealthPartL->x_b88b3756 = sHealthPartL->rightS - 88;

    v0 = obj_create_from_def(&x_54406eae, &x_4fc490a9, x_2587f84f);
    v0->frameCounter = 14;
    sHealthPartR = v0->x_904eaf67->x_a34b89cc[14].parts;
    sHealthPartR->rightS = sHealthPartR->x_b88b3756 + 80;

    v0 = obj_create_from_def(&D_8004A5D0[gWadCondLoad[x_83106b21].x_eb1fe45b], &x_4fc490a9, x_2587f84f);
    if (gWadCondLoad[x_83106b21].x_eb1fe45b < x_e235676f) {
        v0->frameCounter = 16 + gWadCondLoad[x_83106b21].x_eb1fe45b;
    } else {
        v0->frameCounter = 16 + gWadCondLoad[x_83106b21].x_eb1fe45b - 1;
    }
    task_free_list(v0->taskListHead);
    v0->taskListHead = NULL;

    v0 = obj_create_from_def(&D_8004A680[gWadCondLoad[x_6f0b3be3].x_eb1fe45b], &x_4fc490a9, x_2587f84f);
    if (gWadCondLoad[x_6f0b3be3].x_eb1fe45b < x_e235676f) {
        v0->frameCounter = 16 + gWadCondLoad[x_6f0b3be3].x_eb1fe45b;
    } else {
        v0->frameCounter = 16 + gWadCondLoad[x_6f0b3be3].x_eb1fe45b - 1;
    }
    task_free_list(v0->taskListHead);
    v0->taskListHead = NULL;

    sCachedHealthR = sCachedHealthL = 80;
    sHealthBarTask = obj_create_task(hud_health_bar_update, 0x1000);
    hud_score_create();
}

// TODO split files, so D_80052220 (52E20) is in another file

void results_ko_fade(Object *obj) {
    if (--obj->frameCounter < 2) {
        x_e30d50d2 |= x_700de048;
        obj->flags |= x_f51cb721;
    }

    sFadeAlpha -= 2;
    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_final_fade(Object *obj) {
    tr_quad_xlu(sFadeAlpha, NULL);
    obj->flags |= x_f51cb721;
}

void results_attract_skip(Object *obj) {
    if (++obj->frameCounter >= 130) {
        x_e30d50d2 |= x_700de048 | x_bee364e0;
        x_e38a6e19 = SCREEN_ATTRACT;
        x_e30d50d2 |= x_ecbcd14e;
        obj->flags &= ~x_e411fefb;
        obj->x_0232396f = results_final_fade;
    }

    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_wait_timer(Object *obj) {
    if (--obj->frameCounter <= 60) {
        obj->x_0232396f = results_p1_controls_hint;
    }

    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_p1_control_skip(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = results_attract_skip;
    } else if (buttons & x_fc4a9735) {
        obj->frameCounter = 118;
        obj->x_0232396f = results_p1_control_continue;
    }

    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_p1_control_continue(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = results_wait_timer;
    } else if (buttons & x_ad1aebe6) {
        obj->frameCounter = 120;
        obj->x_0232396f = results_p1_control_skip;
    }

    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_show_controls(Object *obj) {
    if (obj->frameCounter >= 118) {
        obj->x_0232396f = results_p1_control_continue;
    } else {
        obj->frameCounter++;
    }

    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_p1_controls_hint(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = results_show_controls;
    } else if (buttons & x_f7763ed8) {
        obj->x_0232396f = results_p1_pause;
        obj->frameCounter = 58;
    }

    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_p1_pause(Object *obj) {
    u16 buttons;
    s16 x_30bbe547;

    buttons = 0;
    x_30bbe547 = obj->x_0f4167b4[0];

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].buttons;
    }

    if (buttons & x_9cefe76c) {
        obj->x_0232396f = results_ko_fade;
    } else if (buttons & x_b8c91680) {
        obj->x_0232396f = results_p1_controls_hint;
        obj->frameCounter = 60;
    }

    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_fade_in(Object *obj) {
    if (obj->frameCounter >= 58) {
        obj->x_0232396f = results_p1_pause;
    } else {
        obj->frameCounter++;
    }
    sFadeAlpha += 2;
    tr_quad_xlu(sFadeAlpha, NULL);
    model_render(obj);
}

void results_init(Object *obj) {
    obj->x_0232396f = results_fade_in;
    obj->flags &= ~x_c537cafa;
    obj->frameCounter++;
    obj->currentTask->callback = task_remove_current;
    gTaskLock = TRUE;
    obj->flags |= x_e411fefb;
    sFadeAlpha = 0;
}

void results_portrait_flicker(Object *obj) {
    if (obj->frameCounter++ > 16) {
        obj->flags |= x_f51cb721;
    }
    obj->currentTask->delay = 2;
}
