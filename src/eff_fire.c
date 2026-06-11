#include "common.h"
#include "task.h"

s32 D_80052310 = 0x10000000;
s32 D_80052314 = 0;

void fire_null_cb(Object *obj) {
}

void fire_ring_update_cb(Object *obj) {
    s32 pad[1];
    u32 x_720f6ac9, dz;
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = x_824b9544 + 1 - player->x_30bbe547;
    x_88f11482 x_fc517ba8;
    x_88f11482 *x_7f6ea7e4 = &obj->pos;
    x_88f11482 *x_9b380833 = &x_98c4e5a5->obj->pos;
    Object *x_49781937;
    x_6751d717 x_c9614940[] = { { 255, 225, 175, 0 }, { 255, 200, 0, 0 } };

    obj->frameCounter++;
    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        TASK_END(obj->currentTask);
        obj->flags |= x_f51cb721;
        gGfxFlags &= ~GFX_SHADOW_MODE;
    }

    if (obj->color.a >= 4) {
        obj->color.a -= 4;
    }

    x_720f6ac9 = ABS(x_7f6ea7e4->x - x_9b380833->x);
    dz = ABS(x_7f6ea7e4->z - x_9b380833->z);
    if (x_4a9e7834(x_720f6ac9, dz) < obj->x_de73d1d5) {
        obj->x_0f4167b4[2] = 0;

        x_fc517ba8.x = x_9b380833->x;
        x_fc517ba8.z = x_9b380833->z;
        x_fc517ba8.y = 0;
        x_49781937 = obj_create_with_model_ptr(&x_fc517ba8, 0x1000, projectile_fade_cb, player->x_dd32bc14[6]);
        if (x_49781937 != NULL) {
            model_light_attach(x_49781937, &x_c9614940[player->x_30bbe547]);
            x_49781937->color.a = 160;
            if (guard_prediction_check(x_98c4e5a5, player, obj)) {
                x_49781937->x_0f4167b4[0] = 32;
            } else {
                x_49781937->x_0f4167b4[0] = 160 / x_49781937->x_20d20338->x_8e601526;
            }
            x_49781937->flags |= x_b6789b80;
        }
        TASK_END(obj->currentTask);
        obj->flags |= x_f51cb721;
    }

    obj->x_de73d1d5 += 16;
}

void fire_wave_spawn_cb(Object *obj) {
    x_88f11482 x_49781937;
    Object *v0;
    Player *player = (Player *) obj->x_e2f64c57[0];
    x_6751d717 x_5aee6615[] = { { 255, 225, 175, 0 }, { 255, 200, 0, 0 } };

    if (obj->x_0f4167b4[1] == 0) {
        x_49781937.x = obj->x_20d20338->transforms[0].x_0c1a9bdd.w.x;
        x_49781937.y = obj->x_20d20338->transforms[0].x_0c1a9bdd.w.y;
        x_49781937.z = obj->x_20d20338->transforms[0].x_0c1a9bdd.w.z;
        v0 = obj_create_with_model_ptr(&x_49781937, 0x1000, fire_ring_update_cb, player->x_dd32bc14[4]);
        if (v0 != NULL) {
            v0->color.a = 160;
            v0->x_0f4167b4[1] = 160 / v0->x_20d20338->x_8e601526;
            v0->flags |= x_b6789b80;
            v0->x_e2f64c57[0] = player;
            v0->x_0f4167b4[6] = obj->x_0f4167b4[6];
            model_light_attach(v0, &x_5aee6615[player->x_30bbe547]);
            audio_sfx_play(player->x_30bbe547, 10);
            v0 = hit_effect_get();
            if (v0 != NULL) {
                v0->x_0f4167b4[0] = v0->x_0f4167b4[1] = 40;
            }
        }
    } else if (obj->x_0f4167b4[1] == 8) {
        x_49781937.x = obj->x_20d20338->transforms[1].x_0c1a9bdd.w.x;
        x_49781937.y = obj->x_20d20338->transforms[1].x_0c1a9bdd.w.y;
        x_49781937.z = obj->x_20d20338->transforms[1].x_0c1a9bdd.w.z;
        v0 = obj_create_with_model_ptr(&x_49781937, 0x1000, fire_ring_update_cb, player->x_dd32bc14[4]);
        if (v0 != NULL) {
            v0->color.a = 160;
            v0->x_0f4167b4[1] = 160 / v0->x_20d20338->x_8e601526;
            v0->flags |= x_b6789b80;
            v0->x_e2f64c57[0] = player;
            v0->x_0f4167b4[6] = obj->x_0f4167b4[6];
            model_light_attach(v0, &x_5aee6615[player->x_30bbe547]);
            audio_sfx_play(player->x_30bbe547, 10);
        }
    } else if (obj->x_0f4167b4[1] == 16) {
        x_49781937.x = obj->x_20d20338->transforms[2].x_0c1a9bdd.w.x;
        x_49781937.y = obj->x_20d20338->transforms[2].x_0c1a9bdd.w.y;
        x_49781937.z = obj->x_20d20338->transforms[2].x_0c1a9bdd.w.z;
        v0 = obj_create_with_model_ptr(&x_49781937, 0x1000, fire_ring_update_cb, player->x_dd32bc14[4]);
        if (v0 != NULL) {
            v0->color.a = 160;
            v0->x_0f4167b4[1] = 160 / v0->x_20d20338->x_8e601526;
            v0->flags |= x_b6789b80;
            v0->x_e2f64c57[0] = player;
            v0->x_0f4167b4[6] = obj->x_0f4167b4[6];
            model_light_attach(v0, &x_5aee6615[player->x_30bbe547]);
            audio_sfx_play(player->x_30bbe547, 10);
        }
    } else if (obj->x_0f4167b4[1] == 24) {
        obj->flags |= x_f51cb721;
    }

    obj->x_0f4167b4[1]++;
}

void fire_wave_init_cb(Object *obj) {
    obj->x_0f4167b4[1] = 0;
    obj->currentTask->callback = fire_wave_spawn_cb;
}
