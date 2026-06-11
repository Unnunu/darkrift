#include "common.h"
#include "camera.h"
#include "task.h"

s16 ai_tactic_retreat(Player *);
s16 ai_tactic_aggressive(Player *);

void dust_spawn_cb(Object *obj);
void dust_wait_cb(Object *);
void dust_speed_cb(Object *);
void hit_sync_attacked_flag(Object *);
void hit_rebound_above_ground(Object *);
void hit_effect_fade_in(Object *);
void hit_rebound_spawn(Object *);
void hit_effect_iter_hitboxes(Object *);
void hit_effect_spawn_from_frame(x_448872e8 *, x_998ccc48 *, Object *);

x_8b39d614 sHitDustSpriteDef = { "dusthit.sp3", dust_spawn_cb, 0, 0x1100, 0, 0x2800, 0 };
s32 sHitDustFrameTable[] = { 14, 17, 18, 21, 21, 24, 12, 15, 11, 14, 0, 0, 14, 17, 18, 21, 11, 14, 14, 17, 11, 14 };
Object *sHitEffectObj = NULL;
s16 D_80052D64[] = { 0, 0 };
s16 D_80052D68[] = { 0, 0 };
s16 D_80052D6C[] = { 0, 0 };
s16 D_80052D70[] = { 0, 0 };
s16 D_80052D74[] = { 0, 0 };
s16 D_80052D78[] = { 2, 2 };

x_88f11482 D_8013C3A0[2];
s16 D_8013C3C0[2];
s32 D_8013C3C8[2];

u8 x_82bfe825(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    return (player->flags & x_cf6c9b89) || gWadCondLoad[player->x_30bbe547].x_03604d94;
}

void x_19fed2ac(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->frameCounter > 5 && (player->flags & x_188f9cec)) {
        player->flags &= ~x_188f9cec;
        TASK_END(obj->currentTask);
    }
}

void x_f95cb1c9(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    player->flags &= ~x_cf6c9b89;
    if (!(player->x_7f68c36b->flags & x_037894c1)) {
        player->flags &= ~x_188f9cec;
    }
    obj->currentTask->callback = task_remove_current;
}

void x_56d15e8a(Object *obj) {
    obj->currentTask->delay = 10;
    obj->currentTask->callback = x_f95cb1c9;
}

void dust_spawn_cb(Object *obj) {
    obj->color.a -= 5;
    obj->frameCounter++;
    if (obj->frameCounter > 9) {
        obj->flags |= x_f51cb721;
    }
    obj->currentTask->delay = 2;
}

void hit_dust_trail(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_30bbe547 = player->x_30bbe547;
    x_88f11482 *s1;
    Object *v0;
    x_88f11482 x_5aee6615;

    s1 = &D_8013C3A0[x_30bbe547];

    if ((abs(s1->x - obj->pos.x) > 20 || abs(s1->z - obj->pos.z) > 20) && !(player->flags & x_c865be3f)) {
        x_5aee6615.x = obj->pos.x;
        x_5aee6615.z = obj->pos.z;
        x_5aee6615.y = 0;
        v0 = obj_create_from_props(&x_5aee6615, &sHitDustSpriteDef, x_2587f84f);
        if (v0 != NULL) {
            v0->color.a = 60;
        }
    }

    s1->x = obj->pos.x;
    s1->z = obj->pos.z;
    if (--obj->x_0f4167b4[3] < 0) {
        player->x_95a50856 = 0;
    }
}

void hit_dust_set_radius(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 v0;
    s32 x_720f6ac9, dz;

    v0 = 0;
    x_720f6ac9 = player->x_5c5b1d93.x_6e7f4fd8->x - player->x_5c5b1d93.x_1b148bc2->x;
    dz = player->x_5c5b1d93.x_6e7f4fd8->z - player->x_5c5b1d93.x_1b148bc2->z;

    if (x_720f6ac9 != 0 || dz != 0) {
        v0 = (u32) (sqrtf(x_84ce1cfb(x_720f6ac9) + x_84ce1cfb(dz)) + 0.5) >> 1;
    }
    if (v0 < 150) {
        v0 = 150;
    }

    player->x_5c5b1d93.x_38ae036c = x_84ce1cfb(v0);
    v0 = (v0 * 0xE000) >> 16;
    player->x_5c5b1d93.x_62706fff = x_84ce1cfb(v0);

    if (player->x_7f68c36b->flags & x_ff05097f) {
        obj->currentTask->callback = hit_dust_trail;
    } else {
        x_56d15e8a(obj);
    }
    obj->x_0f4167b4[3] = 50;
}

void hit_dust_skid_init(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_30bbe547 = player->x_30bbe547;

    player->flags &= ~x_030d2322;
    obj->x_20d20338->x_3aefae96 = D_8004BA98[player->x_eb1fe45b].x;
    obj->x_20d20338->x_713417ac = D_8004BA98[player->x_eb1fe45b].z;
    obj->currentTask->delay = 2;
    obj->currentTask->callback = hit_dust_set_radius;
    obj->currentTask->delay = 2;
    D_8013C3A0[x_30bbe547].x = obj->pos.x;
    D_8013C3A0[x_30bbe547].z = obj->pos.z;
}

void hit_dust_skid_alt_init(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_30bbe547 = player->x_30bbe547;

    player->flags &= ~x_030d2322;
    obj->x_20d20338->x_713417ac = D_8004BAF0[player->x_eb1fe45b].z;
    obj->x_20d20338->x_3aefae96 = D_8004BAF0[player->x_eb1fe45b].x;
    obj->currentTask->delay = 2;
    obj->currentTask->callback = hit_dust_set_radius;
    D_8013C3A0[x_30bbe547].x = obj->pos.x;
    D_8013C3A0[x_30bbe547].z = obj->pos.z;
}

void hit_combo_break_1(Object *obj) {
    TASK_END(obj->currentTask);
}

void hit_combo_break_2(Object *obj) {
    TASK_END(obj->currentTask);
}

void hit_cam_rotate_to_opponent(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_7d3ef158;
    s32 temp;
    s16 v1;

    x_7d3ef158 = (0xC00 - obj->x_224610f1.y) & 0xFFF;

    temp = angle_diff(sMenuState - (player->x_30bbe547 != x_83106b21 ? 0 : 0x800), x_7d3ef158);
    if (temp < 0) {
        v1 = temp + 0x800;
    } else {
        v1 = temp - 0x800;
    }

    obj->x_224610f1.y = 0xC00 - x_7d3ef158 - v1;
    TASK_END(obj->currentTask);
}

u8 hit_push_opponent_away(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 pad[3];
    s16 x_eb1fe45b;
    s16 x_de68d2a6 = 1 - player->x_30bbe547;
    s16 temp;
    x_88f11482 x_93463df6;

    x_eb1fe45b = x_824b9544[x_de68d2a6].x_eb1fe45b;
    temp = D_8004B920[x_eb1fe45b].x_af0aa1f8;

    x_93463df6.x = 0;
    x_93463df6.y = 0;
    x_93463df6.z = -temp;
    vec_rotate_by_euler(&x_93463df6, &obj->x_224610f1);
    (x_824b9544 + x_de68d2a6)->obj->pos.x = obj->pos.x + x_93463df6.x;
    (x_824b9544 + x_de68d2a6)->obj->pos.z = obj->pos.z + x_93463df6.z;
    (x_824b9544 + x_de68d2a6)->obj->x_224610f1.y = 0x400 - ((0xC00 - obj->x_224610f1.y) & 0xFFF);

    return TRUE;
}

void hit_combo_damage_vfx(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = x_824b9544 + 1 - player->x_30bbe547;
    s16 x_eb1fe45b = player->x_eb1fe45b;

    if (obj->frameCounter == player->x_7f68c36b->x_bab9966d - 1) {
        player->x_6f5a5c61 = obj->x_0f4167b4[2];
        if (obj->x_0f4167b4[3] < 0) {
            player->x_95a50856 += player->x_6f5a5c61;
        } else {
            player->x_95a50856 = player->x_6f5a5c61;
            obj->x_0f4167b4[3] = -1;
        }

        if (x_5e4e2788 != x_79c2dc5b) {
            x_98c4e5a5->obj->x_9200c538 -= obj->x_0f4167b4[2];
        }
        if (x_98c4e5a5->obj->x_9200c538 < 0) {
            x_98c4e5a5->obj->x_9200c538 = 0;
        }
    }

    switch (x_eb1fe45b) {
        case x_c4ddde6d:
            projectile_frame_update(obj);
            break;
        case x_73cf9ceb:
            if (gWadCondLoad[1 - player->x_30bbe547].x_eb1fe45b == x_13ed828f &&
                obj->frameCounter < player->x_7f68c36b->x_bab9966d - 1) {
                obj->pos.y = 100;
            } else {
                obj->pos.y = 0;
            }
            hit_effect_iter_hitboxes(obj);
            break;
        default:
            if (D_8004BA40[x_eb1fe45b] != NULL) {
                hit_effect_iter_hitboxes(obj);
            }
            break;
    }
}

void hit_combo_damage_accum(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->frameCounter >= player->x_7f68c36b->x_bab9966d - 2) {
        player->x_6f5a5c61 = obj->x_0f4167b4[2];
        if (obj->x_0f4167b4[3] < 0) {
            player->x_95a50856 += player->x_6f5a5c61;
        } else {
            player->x_95a50856 = player->x_6f5a5c61;
            obj->x_0f4167b4[3] = -1;
        }

        if (x_5e4e2788 != x_79c2dc5b) {
            player->obj->x_9200c538 -= obj->x_0f4167b4[2];
        }
        if (player->obj->x_9200c538 < 0) {
            player->obj->x_9200c538 = 0;
        }

        player->x_08b62e4f->callback = hit_effect_angle_anim;
    }
}

void hit_combo_init(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_de68d2a6 = 1 - player->x_30bbe547;

    player->x_08b62e4f->callback = hit_combo_damage_accum;

    if (x_824b9544[x_de68d2a6].x_eb1fe45b != x_c4ddde6d) {
        obj->currentTask->callback = hit_rebound_spawn;
    } else {
        TASK_END(obj->currentTask);
    }
}

void hit_combo_routing(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 pad[2];
    s16 x_eb1fe45b;
    s16 x_de68d2a6;
    s32 pad2;
    s16 temp;
    x_388306ba *x_fc517ba8;
    x_88f11482 x_93463df6;

    if (sFightLocked && sHudActive == 0) {
        TASK_END(obj->currentTask);
        return;
    }

    if (obj->frameCounter != player->x_7f68c36b->x_bab9966d - 1) {
        return;
    }

    x_eb1fe45b = player->x_eb1fe45b;
    x_de68d2a6 = 1 - player->x_30bbe547;
    player->x_381817ae = 2;

    if (!(player->flags & x_9298c772) && gFighterDistance < D_8004C178[player->x_eb1fe45b] &&
        (x_824b9544[x_de68d2a6].x_7f68c36b->flags & x_ff05097f) &&
        !(x_824b9544[x_de68d2a6].x_7f68c36b->flags & x_7b8f7fad)) {
        TASK_END(obj->currentTask);

        if (x_824b9544[x_de68d2a6].flags & x_9298c772) {
            if (!(x_824b9544[x_de68d2a6].x_7f68c36b->flags & x_cdcff2e1)) {
                player_exec_move_ai(&x_824b9544[x_de68d2a6], x_e7a14975, 1);
            }
            return;
        }

        player->flags |= x_a45101c0;

        D_80080236 = TRUE;
        player_exec_move_ai(&x_824b9544[x_de68d2a6], D_8004B8F4[x_eb1fe45b].x_cd679b4c, 1);
        player_exec_move_ai(player, x_67148cc8, 1);
        D_80080236 = FALSE;
        x_fc517ba8 = &player->x_68a6b5cd[player->x_cd14c741];
        player->obj->x_e2f64c57[2] = x_fc517ba8->x_6f5a5c61;

        temp = D_8004B8F4[x_eb1fe45b].x_af0aa1f8;
        x_93463df6.x = 0;
        x_93463df6.y = 0;
        x_93463df6.z = -temp;
        vec_rotate_by_euler(&x_93463df6, &obj->x_224610f1);
        (x_824b9544 + x_de68d2a6)->obj->pos.x = obj->pos.x + x_93463df6.x;
        (x_824b9544 + x_de68d2a6)->obj->pos.z = obj->pos.z + x_93463df6.z;
        (x_824b9544 + x_de68d2a6)->obj->x_224610f1.y = 0x400 - ((0xC00 - obj->x_224610f1.y) & 0xFFF);

        gGfxFlags &= ~GFX_SHADOW_MODE;
        match_kill_fighters();

        switch (x_eb1fe45b) {
            case x_537ef8a7:
                obj->flags |= x_d13a68b5;
                break;
            case x_c4ddde6d:
                if (x_fc517ba8->x_fc1da284 >= 0) {
                    player->x_0b88f58e = &player->x_38b3091d[x_fc517ba8->x_fc1da284];
                    player->x_66350762 = NULL;
                }
                break;
        }
    }
}

void hit_combo_startup_projectile(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 x_eb1fe45b;
    s16 x_de68d2a6;
    s32 unused[3];

    if (obj->frameCounter == player->x_7f68c36b->x_c53ac2df) {
        x_eb1fe45b = player->x_eb1fe45b;
        x_de68d2a6 = 1 - player->x_30bbe547;
        player_exec_move_ai(&x_824b9544[x_de68d2a6], D_8004B920[x_eb1fe45b].x_cd679b4c, 1);

        if (player->x_eb1fe45b == x_c4ddde6d) {
            obj->currentTask->callback = projectile_init;
        } else if (D_8004BA6C[x_eb1fe45b] != NULL) {
            obj->currentTask->callback = dust_wait_cb;
        } else {
            TASK_END(obj->currentTask);
        }
    }
}

void hit_combo_startup_alt(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (player->x_eb1fe45b == x_968cc9a2) {
        obj->currentTask->callback = projectile_init;
    } else if (D_8004BA6C[player->x_eb1fe45b] != NULL) {
        obj->currentTask->callback = dust_wait_cb;
    } else {
        TASK_END(obj->currentTask);
    }
}

u8 hit_check_opp_grabbing(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[1 - player->x_30bbe547];

    if (x_98c4e5a5->flags & x_6de2d515) {
        return TRUE;
    } else {
        return FALSE;
    }
}

u8 hit_check_opp_falling(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[1 - player->x_30bbe547];

    if (x_98c4e5a5->flags & x_d8a402c3) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void hit_effect_fade_out(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] > 60) {
        obj->flags |= x_f51cb721;
        sCamHeightOffs = 0;
        sHitEffectObj = 0;
    } else if (sCamHeightOffs > 0) {
        sCamHeightOffs -= 10;
    } else {
        obj->x_0232396f = hit_effect_fade_in;
    }
}

void hit_effect_fade_in(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] > 60) {
        obj->flags |= x_f51cb721;
        sCamHeightOffs = 0;
        sHitEffectObj = 0;
    } else if (sCamHeightOffs < obj->x_0f4167b4[1]) {
        sCamHeightOffs += 10;
    } else {
        obj->x_0232396f = hit_effect_fade_out;
        obj->x_0f4167b4[1] -= 15;
    }
}

Object *hit_effect_get(void) {
    if (sHitEffectObj != NULL) {
        sHitEffectObj->flags |= x_f51cb721;
    }

    sHitEffectObj = obj_create_task(hit_effect_fade_in, 0x1000);
    return sHitEffectObj;
}

void hit_rebound_check(Object *obj) {
    if (obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y > -200.0f) {
        hud_dust_line_spawn(obj);
        obj->currentTask->callback = hit_rebound_above_ground;
        obj->currentTask->delay = 20;
    }
}

void hit_rebound_above_ground(Object *obj) {
    if (obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y > -200.0f) {
        return;
    }

    obj->currentTask->callback = hit_rebound_check;
}

void hit_rebound_spawn(Object *obj) {
    Object *v0;

    if (obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y > -200.0f) {
        hud_dust_line_spawn(obj);
        v0 = hit_effect_get();
        if (v0 != NULL) {
            v0->x_0f4167b4[1] = 50;
        }

        obj->currentTask->callback = hit_rebound_above_ground;
        obj->currentTask->delay = 20;
    }
}

void hit_combo_mid_startup(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->frameCounter > (player->x_7f68c36b->x_bab9966d >> 1)) {
        player->x_b9252303->callback = move_to_next;
        player->x_b9252303->delay = 0;
        player->x_b9252303->flags = TASK_RUNNABLE;
    } else {
        player->x_b9252303->callback = move_delay_cb;
        player->x_b9252303->delay = 0;
        player->x_b9252303->flags = TASK_RUNNABLE;
        obj->flags |= x_56bbd9b2;
    }

    player->flags &= ~x_188f9cec;
    TASK_END(obj->currentTask);
}

void hit_knockback_gravity(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    obj->velocity.y += obj->x_8da078cc.y;
    obj->pos.y += obj->velocity.y >> 16;

    if (obj->pos.y >= 0) {
        obj->pos.y = 0;
        if (player->flags & x_9298c772) {
            player_exec_move_ai(player, x_98df8f9f, 1);
        } else {
            player_exec_move_ai(player, x_37718e57, 1);
        }
    }
}

void hit_knockback_launch(Object *obj) {
    obj->velocity.y = 0xFFEC0000;
    obj->x_8da078cc.y = 0x20000;
    obj->currentTask->callback = hit_knockback_gravity;
    hit_sync_attacked_flag(obj);
}

u8 hit_check_facing_away(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    u8 x_cd986d3c;
    s32 t8;

    x_cd986d3c = FALSE;
    t8 = (0xC00 - obj->x_224610f1.y) & 0xFFF;

    if (obj->flags & x_da584e3c) {
        return FALSE;
    }

    if (player->x_30bbe547 != x_83106b21) {
        if (abs(angle_diff(sMenuState, t8)) > 0x400) {
            x_cd986d3c = TRUE;
        }
    } else {
        if (abs(angle_diff(sMenuState, t8)) < 0x400) {
            x_cd986d3c = TRUE;
        }
    }

    return x_cd986d3c;
}

void hit_flip_rotation(Object *obj) {
    s16 v0;

    v0 = (0xC00 - obj->x_224610f1.y) & 0xFFF;
    obj->x_224610f1.y = 0x400 - v0;
}

u8 hit_check_opp_blockstun(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    if (((x_98c4e5a5->x_7f68c36b->flags & (x_7507aa4b | x_eac5209f | x_8b64a078 | x_c1df43e1)) &&
         !(x_98c4e5a5->x_7f68c36b->flags & x_7b8f7fad)) > 0) {
        if (player->x_30bbe547 != x_83106b21) {
            player->obj->x_224610f1.y = 0xC00 - sMenuState;
        } else {
            player->obj->x_224610f1.y = 0x1400 - sMenuState;
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

void hit_delay_then_check_hitstun(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    obj->currentTask->delay = player->x_68a6b5cd[player->x_cd14c741].x_887b6be9 - obj->frameCounter + 2;
    obj->currentTask->callback = dust_speed_cb;
}

void dust_speed_cb(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    s16 a1 = x_dba71d7e;

    if ((x_98c4e5a5->flags & (x_030d2322 | x_6de2d515 | x_faf494e7)) && gFighterDistance < 400 &&
        obj->frameCounter >= player->x_7f68c36b->x_c53ac2df) {
        if (x_98c4e5a5->x_7f68c36b->flags & x_7507aa4b) {
            a1 = x_caa30513;
        }
        player_exec_move_ai(x_98c4e5a5, a1, 1);
        TASK_END(obj->currentTask);
    }
}

void hit_ai_counter_check(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (gFighterDistance < D_8004C1A4[player->x_eb1fe45b] && player->x_cd14c741 != 17) {
        player_exec_move_ai(player, x_e5ca67a6, 1);
        TASK_END(obj->currentTask);
    }
}

void hit_delay_ai_counter(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (player->x_eb1fe45b == x_b52da315) {
        obj->currentTask->delay = 2;
    } else {
        obj->currentTask->delay = 6;
    }
    obj->currentTask->callback = hit_ai_counter_check;
}

u8 hit_check_late_round(s32 x_cc1d0de5) {
    return gFighterDistance > 550;
}

void hit_face_opponent_immediate(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    s16 x_434431dd;
    s16 x_7d3ef158;

    x_434431dd = (0xC00 - x_98c4e5a5->obj->x_224610f1.y) & 0xFFF;
    x_7d3ef158 = angle_diff(sMenuState, x_434431dd);

    if (x_7d3ef158 < 0) {
        x_7d3ef158 -= 0x800;
    } else {
        x_7d3ef158 += 0x800;
    }
    x_98c4e5a5->obj->x_224610f1.y = 0xC00 - (x_434431dd + x_7d3ef158);
}

void hit_set_attacked_flag(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    x_98c4e5a5->flags |= x_188f9cec;
}

void hit_land_set_flag(Object *obj) {
    if (obj->pos.y == 0) {
        hud_dust_ring_spawn(obj);
    }

    obj->currentTask->callback = hit_set_attacked_flag;
}

void hit_sync_attacked_flag(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    if ((x_98c4e5a5->x_7f68c36b->flags & x_6f3569a1) || (x_98c4e5a5->x_08bf2418->x_bb8c769c & x_188f9cec)) {
        x_98c4e5a5->flags |= x_188f9cec;
    } else {
        x_98c4e5a5->flags &= ~x_188f9cec;
    }
}

void hit_set_flag_on_frame(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->frameCounter == player->x_7f68c36b->x_bab9966d - 1) {
        hit_sync_attacked_flag(obj);
    }
}

void hit_clear_flag_delayed(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    if (x_98c4e5a5->x_7f68c36b->flags & x_6f3569a1) {
        x_98c4e5a5->flags |= x_188f9cec;
    }

    if (obj->frameCounter >= 24) {
        player->flags &= ~x_188f9cec;
    }
}

void hit_combo_spin_opponent(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    Object *x_5bbba600 = sIntroPlayerObjs[x_83106b21];
    Object *x_dd7ffac5 = sIntroPlayerObjs[x_6f0b3be3];
    s16 x_f6289181;
    s16 x_4346f5cb;
    s16 x_7d3ef158;

    if (x_98c4e5a5->x_7f68c36b->x_6f5a5c61 != 0) {
        x_98c4e5a5->flags |= x_188f9cec;
    }

    if (!(player->flags & x_188f9cec) && (player->flags & x_9298c772) &&
        (player->x_cd14c741 == 39 || player->x_cd14c741 == 84)) {
        if (player->x_30bbe547 != x_83106b21) {
            x_4346f5cb = (0xC00 - x_dd7ffac5->x_224610f1.y) & 0xFFF;
            x_7d3ef158 = angle_diff(sMenuState - 0x800, x_4346f5cb);

            if (abs(x_7d3ef158) > 140) {
                if (x_7d3ef158 < 0) {
                    x_7d3ef158 = -140;
                } else {
                    x_7d3ef158 = 140;
                }
            }
            x_dd7ffac5->x_224610f1.y = 0xC00 - (x_4346f5cb + x_7d3ef158);
        } else {
            x_f6289181 = (0xC00 - x_5bbba600->x_224610f1.y) & 0xFFF;
            x_7d3ef158 = angle_diff(sMenuState, x_f6289181);

            if (abs(x_7d3ef158) > 140) {
                if (x_7d3ef158 < 0) {
                    x_7d3ef158 = -140;
                } else {
                    x_7d3ef158 = 140;
                }
            }
            x_5bbba600->x_224610f1.y = 0xC00 - (x_f6289181 + x_7d3ef158);
        }
    }
}

void hit_face_opponent_late(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Object *x_13d65ace = sIntroPlayerObjs[x_83106b21];
    Object *x_c48d15e0 = sIntroPlayerObjs[x_6f0b3be3];

    if (!(player->flags & x_9298c772) && obj->frameCounter >= player->x_7f68c36b->x_bab9966d - 1) {
        if (player->x_30bbe547 != x_83106b21) {
            x_c48d15e0->x_224610f1.y = 0xC00 - sMenuState;
        } else {
            x_13d65ace->x_224610f1.y = 0x1400 - sMenuState;
        }
    }
}

void hit_combo_unblockable_check(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5;
    s32 v12;
    s16 a3;

    x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    a3 = x_98c4e5a5->x_cd14c741;
    switch (a3) {
        case 36:
        case 48:
        case 81:
        case 82:
        case 88:
        case 89:
        case 94:
        case 118:
        case 119:
        case 120:
        case 121:
            v12 = TRUE;
            break;
        default:
            v12 = FALSE;
            break;
    }

    if (a3 == 52) {
        v12 = TRUE;
        if (x_98c4e5a5->flags & x_188f9cec) {
            if (x_98c4e5a5->x_30bbe547 != x_83106b21) {
                x_98c4e5a5->obj->x_224610f1.y = 0x1400 - sMenuState;
            } else {
                x_98c4e5a5->obj->x_224610f1.y = 0xC00 - sMenuState;
            }
        } else {
            if (x_98c4e5a5->x_30bbe547 != x_83106b21) {
                x_98c4e5a5->obj->x_224610f1.y = 0xC00 - sMenuState;
            } else {
                x_98c4e5a5->obj->x_224610f1.y = 0x1400 - sMenuState;
            }
        }
    }

    if (player->x_101ebc50 > 0x100 || (x_98c4e5a5->x_7f68c36b->flags & x_025a12b8) || v12) {
        player->flags |= x_188f9cec;
        TASK_END(obj->currentTask);
    }
}

u8 hit_check_button_same(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (gWadCondLoad[player->x_30bbe547].x_03604d94) {
        return TRUE;
    }

    return x_59ce598c[player->x_30bbe547].x_d93bcabf;
}

u8 hit_check_button_opposite(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (gWadCondLoad[player->x_30bbe547].x_03604d94) {
        return TRUE;
    }

    return ~x_59ce598c[player->x_30bbe547].x_d93bcabf;
}

u8 hit_check_opp_punishable(Object *obj) {
    Player *player;
    Player *v1;
    s32 a1;

    player = (Player *) obj->x_e2f64c57[0];
    v1 = x_824b9544 + (1 - player->x_30bbe547);

    a1 = (v1->x_7f68c36b->flags & x_01e3e146) &&
         (v1->x_7f68c36b->x_fedecf5c < v1->obj->frameCounter || v1->x_7f68c36b->x_c53ac2df > v1->obj->frameCounter);
    return a1 > 0;
}

void hit_combo_counter_attack(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *v0;
    x_388306ba *v1;

    v0 = x_824b9544 + (1 - player->x_30bbe547);
    v1 = &player->x_68a6b5cd[player->x_cd14c741];

    if (!(v1->flags & x_f79587cb) && gWadCondLoad[player->x_30bbe547].x_03604d94 &&
        (v0->x_7f68c36b->flags & x_01e3e146) && v0->obj->frameCounter < v0->x_7f68c36b->x_c53ac2df) {
        if (v0->flags & x_ed8e51a2) {
            player_exec_move_ai(player, x_e2a42ecd, 1);
            player->x_81570fde.x_ca75ac5d = ai_tactic_retreat;
            player->x_81570fde.x_5a6554ba = 60;
        } else {
            player_exec_move_ai(player, x_8a9cd4d8, 1);
            player->x_81570fde.x_ca75ac5d = ai_tactic_aggressive;
            player->x_81570fde.x_5a6554ba = 60;
        }
    }
}

#ifdef NON_EQUIVALENT
void hit_effect_angle_anim(Object *x_cc1d0de5) {
    x_2758cdab x_331089fa;
    x_2758cdab x_fd09f53e;
    Player *x_3be4fcf3;
    u8 x_e9fc447d;
    u8 x_3f615590;
    s16 x_ccb8eae3;
    s32 x_7be1f4c5;
    s16 x_e22db69c;

    s16 x_8450963f;
    s16 x_e27567e2;
    s16 x_dab5f4cd;
    s16 x_201aee20;
    s16 x_e03d0d18;

    s16 x_cf297abc;

    s16 x_73c8560b;
    s16 x_c8532a08;

    x_3be4fcf3 = (Player *) x_cc1d0de5->x_e2f64c57[0];
    x_e9fc447d = x_3be4fcf3->x_30bbe547;
    x_3f615590 = 1 - x_e9fc447d;

    x_331089fa.z = 0;
    x_fd09f53e.x = 0;
    x_fd09f53e.z = 0;

    x_ccb8eae3 = x_3be4fcf3->x_a4b33e43;
    x_7be1f4c5 = sIntroPlayerObjs[x_3f615590]->x_20d20338->x_abd7b3c4.x_0c1a9bdd.y.y + 360.0f;
    if (x_ccb8eae3 == 0 || x_ccb8eae3 == 7 || (x_3be4fcf3->x_7f68c36b->flags & x_f79587cb)) {
        x_331089fa.x = atan2_lut(x_7be1f4c5, gFighterDistance);
        x_cf297abc =
            angle_diff((s16) ((0xC00 - x_cc1d0de5->x_224610f1.y) & 0xFFF), (s16) (sMenuState - (x_3f615590 << 0xB)));

        if (x_cf297abc > 1700) {
            x_cf297abc = 1700;
        } else if (x_cf297abc < -1100) {
            x_cf297abc = -1100;
        }

        x_c8532a08 = D_80052D64[x_e9fc447d];
        x_73c8560b = D_80052D68[x_e9fc447d];
        x_e22db69c = x_cf297abc - x_c8532a08 - x_73c8560b;
    } else {
        x_73c8560b = D_80052D68[x_e9fc447d];
        x_c8532a08 = D_80052D64[x_e9fc447d];
        x_cf297abc = 0;
        x_331089fa.x = 0;
        x_e22db69c = -(x_73c8560b + x_c8532a08);
    }

    if (x_e22db69c == 0) {
        D_80052D70[x_e9fc447d] = D_80052D74[x_e9fc447d] = 0;
        D_80052D78[x_e9fc447d] = 2;
        D_8013C3C0[x_e9fc447d] = x_73c8560b + x_c8532a08;
    }

    D_80052D6C[x_e9fc447d] = ((D_8013C3C0[x_e9fc447d] + x_cf297abc) >> 1);
    D_80052D74[x_e9fc447d] += D_80052D78[x_e9fc447d];
    D_80052D70[x_e9fc447d] += D_80052D74[x_e9fc447d];

    if (D_80052D70[x_e9fc447d] > 60) {
        D_80052D70[x_e9fc447d] = 60;
        D_80052D78[x_e9fc447d] = 0;
    } else if (D_80052D70[x_e9fc447d] <= 0) {
        D_80052D70[x_e9fc447d] = 2;
        D_80052D78[x_e9fc447d] = 2;
    }
    if (D_80052D70[x_e9fc447d] < x_e22db69c) {
        x_e22db69c = D_80052D70[x_e9fc447d];
    } else if (x_e22db69c < -D_80052D70[x_e9fc447d]) {
        x_e22db69c = -D_80052D70[x_e9fc447d];
    }
    if (x_73c8560b > 0) {
        x_e03d0d18 = x_c8532a08 + x_e22db69c;
        if (x_e22db69c >= 0) {
            x_8450963f = x_73c8560b + x_e22db69c;
            if (x_8450963f > 600) {
                x_e22db69c = x_8450963f - 600;
                x_e03d0d18 = x_c8532a08 + x_e22db69c;

                x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = 600;
                if (x_e03d0d18 > 1100) {
                    x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = 1100;
                } else {
                    x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
                }
            } else {
                x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_8450963f;
                x_331089fa.y = x_c8532a08;
            }
        } else {
            if (x_e03d0d18 < 0) {
                x_e27567e2 = x_73c8560b + x_e03d0d18;
                x_e22db69c = x_e03d0d18;

                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = 0;
                if (x_e27567e2 < 0) {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = 0;
                } else {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_e27567e2;
                }
            } else {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
                x_fd09f53e.y = x_73c8560b;
            }
        }
    } else if (x_73c8560b < 0) {
        x_dab5f4cd = x_73c8560b + x_e22db69c;
        if (x_e22db69c >= 0) {
            x_e03d0d18 = x_c8532a08 + x_e22db69c;
            if (x_e03d0d18 > 0) {
                x_201aee20 = x_73c8560b + x_e03d0d18;
                x_e22db69c = x_e03d0d18;

                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = 0;
                if (x_201aee20 > 0) {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = 0;
                } else {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_201aee20;
                }
            } else {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
                x_fd09f53e.y = x_73c8560b;
            }
        } else if (x_dab5f4cd < -600) {
            x_e22db69c = x_dab5f4cd + 600;
            x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = -600;
            x_e03d0d18 = x_c8532a08 + x_e22db69c;
            if (x_e03d0d18 < -500) {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = -500;
            } else {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
            }
        } else {
            x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_dab5f4cd;
            x_331089fa.y = x_c8532a08;
        }
    } else {
        x_331089fa.y = x_c8532a08;
        x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_73c8560b + x_e22db69c;
    }

    if (D_80052D74[x_e9fc447d] > 0) {
        if (x_e22db69c >= 0 && x_c8532a08 + x_73c8560b >= D_80052D6C[x_e9fc447d]) {
            D_80052D78[x_e9fc447d] = -2;
        } else if (D_80052D6C[x_e9fc447d] >= x_c8532a08 + x_73c8560b) {
            D_80052D78[x_e9fc447d] = -2;
        }
    }

    mat4_from_euler(&x_3be4fcf3->x_a4d7c80d.x_3fde9cd9, &x_331089fa);
    mat4_from_euler(&x_3be4fcf3->x_022dff72.x_3fde9cd9, &x_fd09f53e);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/eff_hit/hit_effect_angle_anim.s")
#endif

void hit_effect_iter_hitboxes(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    x_448872e8 *s0;

    for (s0 = D_8004BA40[v0->x_eb1fe45b]; s0->x_af0aa1f8 != 0; s0++) {
        if (obj->frameCounter == s0->x_af0aa1f8) {
            hit_effect_spawn_from_frame(s0, &v0->x_5c5b1d93, obj);
        }
    }
}

void dust_wait_cb(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    x_448872e8 *s0;

    for (s0 = D_8004BA6C[v0->x_eb1fe45b]; s0->x_af0aa1f8 != 0; s0++) {
        if (obj->frameCounter == s0->x_af0aa1f8) {
            hit_effect_spawn_from_frame(s0, &v0->x_5c5b1d93, obj);
        }
    }
}

void hit_effect_spawn_from_frame(x_448872e8 *x_cc1d0de5, x_998ccc48 *x_5c5b1d93, Object *x_2092f891) {
    Player *player = (Player *) x_2092f891->x_e2f64c57[0];
    x_123b8fa2 *v0;
    x_acccb624 x_a1fcc259;

    switch (x_cc1d0de5->x_cd679b4c) {
        case 0:
            v0 = x_5c5b1d93->x_1b148bc2;
            break;
        case 1:
            v0 = x_5c5b1d93->x_6e7f4fd8;
            break;
        case 2:
            v0 = x_5c5b1d93->x_b7552092;
            break;
        case 3:
            v0 = &x_5c5b1d93->x_0548cec6.x_0c1a9bdd.w;
            break;
        case 4:
            v0 = &x_5c5b1d93->x_cc2c17a6.x_0c1a9bdd.w;
            break;
        case 5:
            v0 = x_5c5b1d93->x_3b24b185;
            break;
        case 6:
        default:
            v0 = x_5c5b1d93->x_55f532bb;
            break;
    }

    x_a1fcc259.x = v0->x;
    x_a1fcc259.y = v0->y;
    x_a1fcc259.z = v0->z;
    spawn_hit_effect(&x_a1fcc259, x_cc1d0de5->x_1256da71, x_2092f891, &D_8004BA14[player->x_eb1fe45b]);
}

void hit_projectile_or_end(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (v0->x_eb1fe45b == x_c4ddde6d) {
        obj->currentTask->callback = projectile_init;
    } else {
        TASK_END(obj->currentTask);
    }
}

void hit_exec_ai_move(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    player_exec_move_ai(v0, x_dcbb43b9, 1);
}

void hit_delay_ai_move(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (obj->frameCounter == v0->x_7f68c36b->x_bab9966d - 2) {
        obj->currentTask->callback = hit_exec_ai_move;
    }
}

void hit_ai_juggle_dispatch(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (v0->flags & x_9298c772) {
        player_exec_move_ai(v0, x_9f2970bc, 1);
    } else {
        obj->currentTask->delay = 60;
        obj->currentTask->callback = hit_exec_ai_move;
    }
}

void hit_exec_crossup_move(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    player_exec_move_ai(v0, x_445015b3, 1);
}

void hit_delay_crossup_move(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (gWadCondLoad[x_83106b21].x_eb1fe45b == gWadCondLoad[x_6f0b3be3].x_eb1fe45b && v0->x_30bbe547 != 0) {
        obj->currentTask->delay = 15;
    }

    obj->currentTask->callback = hit_exec_crossup_move;
}

void hit_projectile_pushback(Object *obj) {
    x_88f11482 x_dd7ffac5;
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    s32 v1 = v0->x_30bbe547;

    if (obj->frameCounter == v0->x_7f68c36b->x_bab9966d - 1) {
        x_dd7ffac5.x = x_dd7ffac5.y = 0;
        x_dd7ffac5.z = -D_8013C3C8[v1];
        vec_rotate_by_euler(&x_dd7ffac5, &obj->x_224610f1);
        obj->pos.x += x_dd7ffac5.x;
        obj->pos.z += x_dd7ffac5.z;
        obj->currentTask->callback = projectile_frame_update;
    }

    projectile_frame_update(obj);
}

void hit_projectile_zenmuron(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    s32 v1 = v0->x_30bbe547;

    if (v0->x_eb1fe45b == x_ff5073d4 && obj->frameCounter > 50) {
        projectile_frame_update(obj);
        obj->currentTask->callback = projectile_frame_update;
    } else {
        D_8013C3C8[v1] = gFighterDistance;
        projectile_init(obj);
        obj->currentTask->callback = hit_projectile_pushback;
    }
}
