#include "common.h"
#include "task.h"

s32 D_80052310 = 0x10000000;
s32 D_80052314 = 0;

void func_8002A280(Object *obj) {
}

void func_8002A288(Object *obj) {
    s32 pad[1];
    u32 dx, dz;
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = gPlayers + 1 - player->playerId;
    Vec4i sp44;
    Vec4i *playerPos = &obj->pos;
    Vec4i *oppPos = &opponent->obj->pos;
    Object *sp38;
    ColorRGBA sp30[] = { { 255, 225, 175, 0 }, { 255, 200, 0, 0 } };

    obj->frameIndex++;
    if (obj->frameIndex >= obj->modInst->numAnimFrames) {
        TASK_END(obj->currentTask);
        obj->flags |= OBJ_FLAG_DELETE;
        D_8008012C &= ~GFX_FLAG_10;
    }

    if (obj->color.a >= 4) {
        obj->color.a -= 4;
    }

    dx = ABS(playerPos->x - oppPos->x);
    dz = ABS(playerPos->z - oppPos->z);
    if (FAST_HYPOT(dx, dz) < obj->unk_1FC) {
        obj->vars[2] = 0;

        sp44.x = oppPos->x;
        sp44.z = oppPos->z;
        sp44.y = 0;
        sp38 = create_model_instance(&sp44, 0x1000, projectile_fade_away, player->effectModels[6]);
        if (sp38 != NULL) {
            create_light(sp38, &sp30[player->playerId]);
            sp38->color.a = 160;
            if (projectile_apply_damage(opponent, player, obj)) {
                sp38->vars[0] = 32;
            } else {
                sp38->vars[0] = 160 / sp38->modInst->numAnimFrames;
            }
            sp38->flags |= OBJ_FLAG_TRANSPARENT;
        }
        TASK_END(obj->currentTask);
        obj->flags |= OBJ_FLAG_DELETE;
    }

    obj->unk_1FC += 16;
}

void func_8002A4E0(Object *obj) {
    Vec4i sp38;
    Object *v0;
    Player *player = (Player *) obj->varObj[0];
    ColorRGBA sp28[] = { { 255, 225, 175, 0 }, { 255, 200, 0, 0 } };

    if (obj->vars[1] == 0) {
        sp38.x = obj->modInst->transforms[0].world_matrix.w.x;
        sp38.y = obj->modInst->transforms[0].world_matrix.w.y;
        sp38.z = obj->modInst->transforms[0].world_matrix.w.z;
        v0 = create_model_instance(&sp38, 0x1000, func_8002A288, player->effectModels[4]);
        if (v0 != NULL) {
            v0->color.a = 160;
            v0->vars[1] = 160 / v0->modInst->numAnimFrames;
            v0->flags |= OBJ_FLAG_TRANSPARENT;
            v0->varObj[0] = player;
            v0->vars[6] = obj->vars[6];
            create_light(v0, &sp28[player->playerId]);
            sound_play(player->playerId, 10);
            v0 = func_80030908();
            if (v0 != NULL) {
                v0->vars[0] = v0->vars[1] = 40;
            }
        }
    } else if (obj->vars[1] == 8) {
        sp38.x = obj->modInst->transforms[1].world_matrix.w.x;
        sp38.y = obj->modInst->transforms[1].world_matrix.w.y;
        sp38.z = obj->modInst->transforms[1].world_matrix.w.z;
        v0 = create_model_instance(&sp38, 0x1000, func_8002A288, player->effectModels[4]);
        if (v0 != NULL) {
            v0->color.a = 160;
            v0->vars[1] = 160 / v0->modInst->numAnimFrames;
            v0->flags |= OBJ_FLAG_TRANSPARENT;
            v0->varObj[0] = player;
            v0->vars[6] = obj->vars[6];
            create_light(v0, &sp28[player->playerId]);
            sound_play(player->playerId, 10);
        }
    } else if (obj->vars[1] == 16) {
        sp38.x = obj->modInst->transforms[2].world_matrix.w.x;
        sp38.y = obj->modInst->transforms[2].world_matrix.w.y;
        sp38.z = obj->modInst->transforms[2].world_matrix.w.z;
        v0 = create_model_instance(&sp38, 0x1000, func_8002A288, player->effectModels[4]);
        if (v0 != NULL) {
            v0->color.a = 160;
            v0->vars[1] = 160 / v0->modInst->numAnimFrames;
            v0->flags |= OBJ_FLAG_TRANSPARENT;
            v0->varObj[0] = player;
            v0->vars[6] = obj->vars[6];
            create_light(v0, &sp28[player->playerId]);
            sound_play(player->playerId, 10);
        }
    } else if (obj->vars[1] == 24) {
        obj->flags |= OBJ_FLAG_DELETE;
    }

    obj->vars[1]++;
}

void func_8002A870(Object *obj) {
    obj->vars[1] = 0;
    obj->currentTask->func = func_8002A4E0;
}
