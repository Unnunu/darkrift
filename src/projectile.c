#include "common.h"
#include "task.h"

void projectile_hit_effect(Object *obj, Object *x_71d00f40);
void projectile_impact_check(Object *);

void projectile_fade_cb(Object *obj) {
    if (++obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        TASK_END(obj->currentTask);
        obj->flags |= x_f51cb721;
    }

    if (obj->color.a >= obj->x_0f4167b4[0]) {
        obj->color.a -= obj->x_0f4167b4[0];
    } else {
        obj->color.a = 0;
        TASK_END(obj->currentTask);
        obj->flags |= x_f51cb721;
    }
}

void projectile_frame_update(Object *obj) {
    Player *player = (Player *) obj->x_0f4167b4[0];
    x_b842de24 *s0;

    ;
    for (s0 = player->x_0b88f58e->x_af0aa1f8; s0->x_d7ce6b8d != 255; s0++) {
        if (obj->frameCounter == s0->frameCounter) {
            projectile_spawn(obj, s0->x_d7ce6b8d);
        }
    }
}

void projectile_init(Object *obj) {
    Player *player = (Player *) obj->x_0f4167b4[0];
    x_388306ba *state;

    state = &player->x_68a6b5cd[player->x_cd14c741];
    if (state->x_fc1da284 >= 0) {
        player->x_0b88f58e = &player->x_38b3091d[state->x_fc1da284];
        player->x_66350762 = NULL;
        obj->currentTask->callback = projectile_frame_update;
    } else {
        TASK_END(obj->currentTask);
    }
}

void projectile_null_cb(Object *obj) {
}

void projectile_hit_dispatch(Object *obj, Object *x_71d00f40) {
    if (obj->x_1b0e7aa2 == 8) {
        projectile_null_cb(obj);
    } else {
        projectile_hit_effect(obj, x_71d00f40);
    }
}

void projectile_end(Object *obj, x_6fc0b62f *effect) {
    Player *player = (Player *) obj->x_0f4167b4[0];

    player->flags &= ~x_c15491f2;

    switch (player->x_eb1fe45b) {
        case x_c4ddde6d:
            obj->x_0f4167b4[1] = 0;
            if (obj->x_0f4167b4[3] == 1) {
                obj->currentTask->callback = fire_wave_init_cb;
            } else {
                TASK_END(obj->currentTask);
                obj->flags |= x_f51cb721;
                gGfxFlags &= ~GFX_SHADOW_MODE;
            }
            return;
        case x_537ef8a7:
            TASK_END(obj->currentTask);
            obj->flags |= x_f51cb721;
            gGfxFlags &= ~GFX_SHADOW_MODE;
            return;
    }

    gGfxFlags &= ~GFX_SHADOW_MODE;
    TASK_END(obj->currentTask);
    obj->flags |= x_f51cb721;
}

void projectile_ring_update(Object *obj) {
    u8 *t0;
    x_6fc0b62f *s0;
    s32 x_df21a243;
    Player *player;
    u8 v1;
    s16 temp;
    Object *x_b3c3622a;
    x_88f11482 x_5aee6615;

    s0 = (x_6fc0b62f *) obj->x_0f4167b4[7];
    t0 = (u8 *) obj->x_0f4167b4[1];
    player = (Player *) obj->x_0f4167b4[0];
    x_b3c3622a = player->obj;

    if ((s0->flags & 2) && s0->x_32485e13 >= 0) {
        x_342a32f9(x_b3c3622a, s0, &x_5aee6615);
        obj->pos.x = x_5aee6615.x;
        obj->pos.y = x_5aee6615.y;
        obj->pos.z = x_5aee6615.z;
    }

    if (--obj->x_f9866d50 <= 0) {
        temp = obj->x_0f4167b4[2]++;
        obj->x_f9866d50 = obj->x_0f4167b4[4];
        v1 = t0[temp];

        if (v1 == 0xFF) {
            obj->x_0f4167b4[2] = 1;
            v1 = t0[0];
        } else if (v1 == 0xFE) {
            projectile_end(obj, s0);
            return;
        }

        obj->frameCounter = v1;
        if ((s0->flags & 1) && obj->frameCounter >= s0->x_1adc8f8a) {
            if (obj->color.a >= obj->x_0f4167b4[9]) {
                obj->color.a -= obj->x_0f4167b4[9];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= x_f51cb721;
            }
        }
    }

    obj->flags &= ~x_c537cafa;

    if (((s0->flags & 0x10) && --obj->x_0f4167b4[5] < 0) || obj->pos.y > 0) { // @bug probably
        projectile_end(obj, s0);
        return;
    }

    if (s0->flags & 4) {
        projectile_impact_check(obj);
    }

    obj->pos.x += obj->velocity.x;
    obj->pos.y += obj->velocity.y;
    obj->pos.z += obj->velocity.z;

    x_df21a243 = s0->x_49e4c93e;
    if (x_df21a243 >= 0 && --obj->x_0f4167b4[8] < 0) {
        obj->x_0f4167b4[8] = s0->x_8cd129ed;
        projectile_spawn(obj, x_df21a243 ^ 0); // required to match
    }
}

void projectile_homing_update(Object *obj) {
    x_6fc0b62f *effect;
    s32 x_df21a243;
    Player *player;
    u8 v1;
    s16 temp;
    Object *x_b3c3622a;
    x_88f11482 x_32f1d6e2;

    effect = (x_6fc0b62f *) obj->x_0f4167b4[7];
    player = (Player *) obj->x_0f4167b4[0];
    x_b3c3622a = player->obj;

    gGfxFlags |= GFX_SHADOW_MODE;

    if ((effect->flags & 2) && effect->x_32485e13 >= 0) {
        x_342a32f9(x_b3c3622a, effect, &x_32f1d6e2);
        obj->pos.x = x_32f1d6e2.x;
        obj->pos.y = x_32f1d6e2.y;
        obj->pos.z = x_32f1d6e2.z;
    }

    obj->flags &= ~x_c537cafa;
    obj->frameCounter++;

    if (effect->flags & 0x10) {
        if (--obj->x_0f4167b4[5] < 0 || obj->pos.y > 0) {
            projectile_end(obj, effect);
            return;
        }
        if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
            obj->frameCounter = effect->x_817784f2;
        }
    }

    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        projectile_end(obj, effect);
        return;
    }

    if (effect->flags & 4) {
        projectile_impact_check(obj);
    }

    obj->pos.x += obj->velocity.x;
    obj->pos.y += obj->velocity.y;
    obj->pos.z += obj->velocity.z;

    if ((effect->flags & 1) && obj->frameCounter >= effect->x_1adc8f8a) {
        if (obj->color.a >= obj->x_0f4167b4[9]) {
            obj->color.a -= obj->x_0f4167b4[9];
        } else {
            obj->color.a = 0;
            projectile_end(obj, effect);
            return;
        }
    }

    x_df21a243 = effect->x_49e4c93e;
    if (x_df21a243 >= 0 && --obj->x_0f4167b4[8] < 0) {
        obj->x_0f4167b4[8] = effect->x_8cd129ed;
        projectile_spawn(obj, x_df21a243 ^ 0); // required to match
    }
}

void projectile_hit_effect(Object *obj, Object *x_71d00f40) {
    Player *player;
    Object *v0;
    x_6fc0b62f *v2;
    x_6fc0b62f *v1;

    player = (Player *) obj->x_0f4167b4[0];
    v1 = (x_6fc0b62f *) obj->x_0f4167b4[7];
    v2 = player->x_e4ca14d3 + v1->x_350c85ef;

    obj->x_b1e624ba = obj->x_e4466eca = 0;
    obj->flags |= x_f51cb721;
    TASK_END(obj->currentTask);

    v2->x_6f6a6d94 = 0x10;
    v2->flags |= 0x10;
    v2->x_1adc8f8a = 0;
    v2->x_251abb64 = 0x10;

    v0 = projectile_spawn(obj, v1->x_350c85ef);
    if (v0 != NULL) {
        obj->x_61f772e7 |= 8;
        v0->x_61f772e7 &= ~2;
        if (player->x_30bbe547 != x_83106b21) {
            v0->x_e4466eca = 2;
        } else {
            v0->x_b1e624ba = 2;
        }
        v0->x_de73d1d5 = 300;
    }
}

void projectile_guard_spawn(Object *obj, Object *x_84ff873b) {
    Player *player = (Player *) obj->x_0f4167b4[0];
    Object *v0;
    x_88f11482 x_c9614940;
    x_6fc0b62f *v1 = (x_6fc0b62f *) obj->x_0f4167b4[7];
    x_6751d717 x_5bbba600[2] = { { 215, 180, 45, 0 }, { 250, 190, 55, 0 } };

    if ((obj->x_1b0e7aa2 & 8) && (obj->x_61f772e7 & 8)) {
        projectile_null_cb(obj);
        return;
    }

    obj->x_b1e624ba = obj->x_e4466eca = 0;
    obj->flags |= x_f51cb721;
    TASK_END(obj->currentTask);

    x_c9614940.x = 0;
    x_c9614940.y = 0;
    x_c9614940.z = -obj->x_de73d1d5;
    vec_rotate_by_euler(&x_c9614940, &obj->x_224610f1);
    x_c9614940.x += obj->pos.x;
    x_c9614940.z += obj->pos.z;
    obj->x_de73d1d5 = 0;

    v0 = obj_create_with_model_ptr(&x_c9614940, 0x1000, projectile_fade_cb, player->x_dd32bc14[v1->x_350c85ef]);
    if (v0 == NULL) {
        return;
    }

    v0->color.a = 255;
    v0->x_0f4167b4[0] = 5;
    v0->flags |= x_b6789b80;
    v0->x_61f772e7 &= ~2;
    if (player->x_30bbe547 != x_83106b21) {
        v0->x_e4466eca = 2;
    } else {
        v0->x_b1e624ba = 2;
    }
    v0->x_de73d1d5 = 300;
    model_light_attach(v0, &x_5bbba600[player->x_30bbe547]);
}

x_09d6a3c8 sProjectileTypeTable[2] = { projectile_homing_update, projectile_ring_update }; // unused

void projectile_guard_ring(Object *obj, s32 x_84ff873b, Object *x_2092f891) {
    Player *player = (Player *) obj->x_0f4167b4[0];
    Object *v0;

    if (player->x_eb1fe45b == x_537ef8a7 && x_84ff873b == 0) {
        x_2092f891->x_450fdcd0 = projectile_guard_spawn;
        v0 = hit_effect_get();
        if (v0 != NULL) {
            v0->x_0f4167b4[1] = 50;
            v0->x_0f4167b4[0] = 30;
        }
    }
}

Object *projectile_spawn(Object *obj, s32 x_d7ce6b8d) {
    x_88f11482 pos;
    Object *x_02f7ef06;
    Player *player = (Player *) obj->x_0f4167b4[0];
    x_6fc0b62f *effect = player->x_e4ca14d3 + x_d7ce6b8d;
    s32 pad[2];

    if (effect->x_32485e13 >= 0) {
        x_342a32f9(obj, effect, &pos);
    } else {
        pos.x = effect->x_1422e8f9;
        pos.y = effect->x_6f7546e4;
        pos.z = effect->x_95b3e972;
        vec_rotate_by_euler(&pos, &obj->x_224610f1);
        pos.x += obj->pos.x;
        pos.y += obj->pos.y;
        pos.z += obj->pos.z;
    }

    if (effect->x_e2f3aa2a >= 0) {
        x_02f7ef06 =
            obj_create_frame_render(&pos, 0x1100, projectile_ring_update, player->x_a1dcdb62[effect->x_e2f3aa2a]);
        if (x_02f7ef06 == NULL) {
            return x_02f7ef06;
        }

        x_02f7ef06->frameCounter = player->x_8b00beac[effect->x_bc085e56];
        x_02f7ef06->x_f9866d50 = x_02f7ef06->x_0f4167b4[4] = effect->x_fbb09ed1;
    } else {
        x_02f7ef06 =
            obj_create_with_model_ptr(&pos, 0x1000, projectile_homing_update, player->x_dd32bc14[effect->x_1d88fb18]);
        if (x_02f7ef06 == NULL) {
            return x_02f7ef06;
        }

        x_02f7ef06->flags |= x_c537cafa;
        x_02f7ef06->currentTask->delay = effect->x_fbb09ed1;
        player->x_66350762 = x_02f7ef06;
    }

    if (x_02f7ef06->x_20d20338 == NULL) {
        return NULL;
    }

    if (x_02f7ef06 != NULL) {
        if (effect->flags & 4) {
            if (player->x_30bbe547 != x_83106b21) {
                x_02f7ef06->x_e4466eca = 2;
            } else {
                x_02f7ef06->x_b1e624ba = 2;
            }
            x_02f7ef06->x_de73d1d5 = 300;
            x_02f7ef06->x_61f772e7 |= 2;
            x_02f7ef06->x_61f772e7 |= 8;
            x_02f7ef06->x_450fdcd0 = projectile_hit_dispatch;
            player->flags |= x_c15491f2;
        }

        if (effect->flags & 0x40) {
            model_light_attach(x_02f7ef06, &effect->x_c3357d6a[player->x_30bbe547]);
        }

        x_02f7ef06->x_0f4167b4[0] = player;
        x_02f7ef06->x_0f4167b4[1] = player->x_8b00beac + effect->x_bc085e56;
        x_02f7ef06->x_0f4167b4[2] = 0;
        x_02f7ef06->x_0f4167b4[5] = effect->x_6f6a6d94;
        x_02f7ef06->x_0f4167b4[6] = player->x_7f68c36b;
        x_02f7ef06->x_0f4167b4[7] = effect;
        x_02f7ef06->x_0f4167b4[3] = x_d7ce6b8d;
        x_02f7ef06->velocity.x = effect->x_52756e64;
        x_02f7ef06->velocity.y = effect->x_4615af37;
        x_02f7ef06->velocity.z = effect->x_2c9fb9af;
        x_02f7ef06->x_d7f6e5d2.x = 0xF00000;
        x_02f7ef06->x_d7f6e5d2.y = 0xF00000;
        x_02f7ef06->x_d7f6e5d2.z = 0xF00000;

        vec_rotate_by_euler(&x_02f7ef06->velocity, &obj->x_224610f1);

        x_02f7ef06->x_0f4167b4[8] = effect->x_c3bc2262;
        x_02f7ef06->x_224610f1.y = player->obj->x_224610f1.y;
        effect->x_a484ea08 = 0;

        if (effect->flags & 9) {
            x_02f7ef06->flags |= x_b6789b80;
            x_02f7ef06->color.a = 255;

            if (effect->x_251abb64 > 0) {
                x_02f7ef06->x_0f4167b4[9] = 255 / effect->x_251abb64;
            } else if (effect->x_e2f3aa2a < 0 && x_02f7ef06->x_20d20338->x_8e601526 != 0) {
                x_02f7ef06->x_0f4167b4[9] = 255 / x_02f7ef06->x_20d20338->x_8e601526;
            } else {
                x_02f7ef06->x_0f4167b4[9] = 255 / x_02f7ef06->x_20d20338->x_6dcce206; // ?????????
            }

            if (player->x_eb1fe45b == x_ff5073d4 && effect->x_1d88fb18 == 0) {

                x_02f7ef06->x_0f4167b4[9] = 128 / x_02f7ef06->x_20d20338->x_8e601526;
                x_02f7ef06->color.a = 128;
            }
        }

        projectile_guard_ring(obj, x_d7ce6b8d, x_02f7ef06);
    }

    return x_02f7ef06;
}

u8 guard_prediction_check(Player *x_cc1d0de5, Player *x_84ff873b, Object *x_2092f891) {
    s16 v0;
    x_388306ba *a2;
    u8 x_2a9ef16e;

    a2 = (x_388306ba *) x_2092f891->x_0f4167b4[6];

    if (x_9df63a90 && !x_33abac12) {
        return FALSE;
    }

    v0 = hit_outcome(x_cc1d0de5, x_84ff873b, a2);
    x_2a9ef16e = (v0 == 270 || v0 == 271);
    return x_2a9ef16e;
}

void projectile_homing_setup(Object *obj, Player *x_84ff873b, x_6fc0b62f *x_2092f891, u8 x_ee71e5cb) {
    Player *player = (Player *) obj->x_0f4167b4[0];
    x_6fc0b62f *x_a1fcc259 = player->x_e4ca14d3 + x_2092f891->x_350c85ef;
    Object *v00;

    if (guard_prediction_check(x_84ff873b, player, obj)) {
        x_a1fcc259->x_6f6a6d94 = 0x10;
        x_a1fcc259->flags |= 0x10;
        x_a1fcc259->x_1adc8f8a = 0;
        x_a1fcc259->x_251abb64 = 0x10;
    } else {
        x_a1fcc259->x_6f6a6d94 = 0;
        x_a1fcc259->flags &= ~0x10;
        x_a1fcc259->x_251abb64 = -1;
    }

    if (x_ee71e5cb) {
        v00 = projectile_spawn(obj, x_2092f891->x_350c85ef);
        if (v00 != NULL) {
            v00->color.a = 128;
            if (v00->x_20d20338->x_8e601526 != 0) {
                v00->x_0f4167b4[9] = 255 / v00->x_20d20338->x_8e601526;
            }
        }
    }

    projectile_end(obj, x_2092f891);
}

#ifdef NON_EQUIVALENT
u8 projectile_guard_homing(Object *obj) {
    Player *player;
    x_88f11482 *x_7f6ea7e4;
    x_88f11482 *x_9b380833;
    x_6fc0b62f *a2;
    Object *v0;
    x_88f11482 x_fc517ba8;
    Player *x_dd7ffac5;
    s16 q;
    u32 x_720f6ac9, dz;
    s32 pad[2];

    player = (Player *) obj->x_0f4167b4[0];
    x_dd7ffac5 = x_824b9544 + (player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3);
    a2 = (x_6fc0b62f *) obj->x_0f4167b4[7];

    x_7f6ea7e4 = &obj->pos;
    x_9b380833 = &x_dd7ffac5->obj->pos;

    q = obj->x_0f4167b4[3];
    if (player->x_eb1fe45b == x_537ef8a7) {
        if (q == 0) {
            if (1) {
                x_720f6ac9 = ABS(x_7f6ea7e4->x - x_9b380833->x);
            }
            dz = ABS(x_7f6ea7e4->z - x_9b380833->z);

            // a2->unk_40 += 22;
            // obj->unk_1FC = a2->unk_40;
            if (x_4a9e7834(x_720f6ac9, dz) < (obj->x_de73d1d5 = a2->x_a484ea08 += 22) &&
                !(x_dd7ffac5->x_7f68c36b->flags & (x_025a12b8 | x_36377d70))) {
                projectile_homing_setup(obj, x_dd7ffac5, a2, FALSE);

                x_fc517ba8.x = x_7f6ea7e4->x;
                x_fc517ba8.z = x_7f6ea7e4->z;
                x_fc517ba8.y = 0;
                v0 = obj_create_with_model_ptr(&x_fc517ba8, 0x1000, projectile_fade_cb,
                                               player->x_dd32bc14[a2->x_350c85ef]);
                if (v0 != NULL) {
                    v0->color.a = 255;
                    v0->x_0f4167b4[0] = 255 / v0->x_20d20338->x_8e601526;
                    v0->flags |= x_b6789b80;
                }
            }

            return TRUE;
        }
        return FALSE;
    }

    return FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/projectile/projectile_guard_homing.s")
u8 projectile_guard_homing(Object *obj);
#endif

void projectile_impact_check(Object *obj) {
    Player *player;
    Player *x_98c4e5a5;
    s32 pad[2];
    x_2758cdab x_081c4eef;
    x_2758cdab x_49781937;
    Object *v00;
    x_6fc0b62f *x_c9614940;
    x_6fc0b62f *x_32f1d6e2;
    s32 pad2;

    x_32f1d6e2 = (x_6fc0b62f *) obj->x_0f4167b4[7];
    player = (Player *) obj->x_0f4167b4[0];
    x_98c4e5a5 = x_824b9544 + (player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3);

    if (x_98c4e5a5->x_7f68c36b->flags & x_7b8f7fad) {
        return;
    }
    if (projectile_guard_homing(obj)) {
        return;
    }

    x_081c4eef.x = x_98c4e5a5->x_5c5b1d93.x_b7552092->x;
    x_081c4eef.y = x_98c4e5a5->x_5c5b1d93.x_b7552092->y;
    x_081c4eef.z = x_98c4e5a5->x_5c5b1d93.x_b7552092->z;

    x_49781937.x = obj->pos.x;
    x_49781937.y = obj->pos.y;
    x_49781937.z = obj->pos.z;

    if (point_in_hit_range(&x_081c4eef, &x_98c4e5a5->obj->pos, x_98c4e5a5->x_5c5b1d93.x_62706fff + 80000,
                           &x_49781937)) {
        if (!(x_32f1d6e2->flags & 0x20) && !(player->flags & x_d8a402c3)) {
            x_c9614940 = player->x_e4ca14d3 + x_32f1d6e2->x_350c85ef;
            if (guard_prediction_check(x_98c4e5a5, player, obj)) {
                x_c9614940->x_6f6a6d94 = 0x10;
                x_c9614940->flags |= 0x10;
                x_c9614940->x_1adc8f8a = 0;
                x_c9614940->x_251abb64 = 0x10;
            } else {
                x_c9614940->x_6f6a6d94 = 0;
                x_c9614940->flags &= ~0x10;
                x_c9614940->x_251abb64 = -1;
            }

            v00 = projectile_spawn(obj, x_32f1d6e2->x_350c85ef);
            if (v00 != NULL) {
                v00->x_61f772e7 &= ~2;
                if (player->x_30bbe547 != x_83106b21) {
                    v00->x_e4466eca = 2;
                } else {
                    v00->x_b1e624ba = 2;
                }
                v00->x_de73d1d5 = 300;
            }

            projectile_end(obj, x_32f1d6e2);
        } else {
            projectile_end(obj, x_32f1d6e2);
        }

        player->x_66350762 = NULL;
    }
}
