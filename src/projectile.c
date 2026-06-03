#include "common.h"
#include "task.h"

void projectile_impact_explosion(Object *obj, Object *obj2);
void func_80022EC0(Object *);

void projectile_fade_away(Object *obj) {
    if (++obj->frameIndex >= obj->modInst->numAnimFrames) {
        TASK_END(obj->currentTask);
        obj->flags |= OBJ_FLAG_DELETE;
    }

    if (obj->color.a >= obj->vars[0]) {
        obj->color.a -= obj->vars[0];
    } else {
        obj->color.a = 0;
        TASK_END(obj->currentTask);
        obj->flags |= OBJ_FLAG_DELETE;
    }
}

void projectile_spawn_at_frame(Object *obj) {
    Player *player = (Player *) obj->vars[0];
    ProjectileShot *s0;

    ;
    for (s0 = player->barrage->unk_00; s0->projectileId != 255; s0++) {
        if (obj->frameIndex == s0->frameIndex) {
            projectile_spawn(obj, s0->projectileId);
        }
    }
}

void player_action_init_projectiles(Object *obj) {
    Player *player = (Player *) obj->vars[0];
    CombatState *state;

    state = &player->combatStateTable[player->combatStateId];
    if (state->projBarrage >= 0) {
        player->barrage = &player->barrageTable[state->projBarrage];
        player->projectileObj = NULL;
        obj->currentTask->func = projectile_spawn_at_frame;
    } else {
        TASK_END(obj->currentTask);
    }
}

void projectile_noop(Object *obj) {
}

void projectile_on_impact(Object *obj, Object *obj2) {
    if (obj->unk_078 == 8) {
        projectile_noop(obj);
    } else {
        projectile_impact_explosion(obj, obj2);
    }
}

void projectile_cleanup(Object *obj, ProjectileDef *effect) {
    Player *player = (Player *) obj->vars[0];

    player->flags &= ~PLAYER_FLAG_SHOOTED;

    switch (player->characterId) {
        case AARON:
            obj->vars[1] = 0;
            if (obj->vars[3] == 1) {
                obj->currentTask->func = func_8002A870;
            } else {
                TASK_END(obj->currentTask);
                obj->flags |= OBJ_FLAG_DELETE;
                D_8008012C &= ~GFX_FLAG_10;
            }
            return;
        case GORE:
            TASK_END(obj->currentTask);
            obj->flags |= OBJ_FLAG_DELETE;
            D_8008012C &= ~GFX_FLAG_10;
            return;
    }

    D_8008012C &= ~GFX_FLAG_10;
    TASK_END(obj->currentTask);
    obj->flags |= OBJ_FLAG_DELETE;
}

void projectile_update_sprite(Object *obj) {
    u8 *t0;
    ProjectileDef *s0;
    s32 temp2;
    Player *player;
    u8 v1;
    s16 temp;
    Object *playerObj;
    Vec4i sp28;

    s0 = (ProjectileDef *) obj->vars[7];
    t0 = (u8 *) obj->vars[1];
    player = (Player *) obj->vars[0];
    playerObj = player->obj;

    if ((s0->flags & 2) && s0->boneId >= 0) {
        func_80028120(playerObj, s0, &sp28);
        obj->pos.x = sp28.x;
        obj->pos.y = sp28.y;
        obj->pos.z = sp28.z;
    }

    if (--obj->unk_08C <= 0) {
        temp = obj->vars[2]++;
        obj->unk_08C = obj->vars[4];
        v1 = t0[temp];

        if (v1 == 0xFF) {
            obj->vars[2] = 1;
            v1 = t0[0];
        } else if (v1 == 0xFE) {
            projectile_cleanup(obj, s0);
            return;
        }

        obj->frameIndex = v1;
        if ((s0->flags & 1) && obj->frameIndex >= s0->unk_36) {
            if (obj->color.a >= obj->vars[9]) {
                obj->color.a -= obj->vars[9];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= OBJ_FLAG_DELETE;
            }
        }
    }

    obj->flags &= ~OBJ_FLAG_HIDDEN;

    if (((s0->flags & 0x10) && --obj->vars[5] < 0) || obj->pos.y > 0) { // @bug probably
        projectile_cleanup(obj, s0);
        return;
    }

    if (s0->flags & 4) {
        func_80022EC0(obj);
    }

    obj->pos.x += obj->velocity.x;
    obj->pos.y += obj->velocity.y;
    obj->pos.z += obj->velocity.z;

    temp2 = s0->unk_30;
    if (temp2 >= 0 && --obj->vars[8] < 0) {
        obj->vars[8] = s0->unk_34;
        projectile_spawn(obj, temp2 ^ 0); // required to match
    }
}

void projectile_update_model(Object *obj) {
    ProjectileDef *effect;
    s32 temp2;
    Player *player;
    u8 v1;
    s16 temp;
    Object *playerObj;
    Vec4i sp2C;

    effect = (ProjectileDef *) obj->vars[7];
    player = (Player *) obj->vars[0];
    playerObj = player->obj;

    D_8008012C |= GFX_FLAG_10;

    if ((effect->flags & 2) && effect->boneId >= 0) {
        func_80028120(playerObj, effect, &sp2C);
        obj->pos.x = sp2C.x;
        obj->pos.y = sp2C.y;
        obj->pos.z = sp2C.z;
    }

    obj->flags &= ~OBJ_FLAG_HIDDEN;
    obj->frameIndex++;

    if (effect->flags & 0x10) {
        if (--obj->vars[5] < 0 || obj->pos.y > 0) {
            projectile_cleanup(obj, effect);
            return;
        }
        if (obj->frameIndex >= obj->modInst->numAnimFrames) {
            obj->frameIndex = effect->unk_24;
        }
    }

    if (obj->frameIndex >= obj->modInst->numAnimFrames) {
        projectile_cleanup(obj, effect);
        return;
    }

    if (effect->flags & 4) {
        func_80022EC0(obj);
    }

    obj->pos.x += obj->velocity.x;
    obj->pos.y += obj->velocity.y;
    obj->pos.z += obj->velocity.z;

    if ((effect->flags & 1) && obj->frameIndex >= effect->unk_36) {
        if (obj->color.a >= obj->vars[9]) {
            obj->color.a -= obj->vars[9];
        } else {
            obj->color.a = 0;
            projectile_cleanup(obj, effect);
            return;
        }
    }

    temp2 = effect->unk_30;
    if (temp2 >= 0 && --obj->vars[8] < 0) {
        obj->vars[8] = effect->unk_34;
        projectile_spawn(obj, temp2 ^ 0); // required to match
    }
}

void projectile_impact_explosion(Object *obj, Object *obj2) {
    Player *player;
    Object *v0;
    ProjectileDef *v2;
    ProjectileDef *v1;

    player = (Player *) obj->vars[0];
    v1 = (ProjectileDef *) obj->vars[7];
    v2 = player->projectileTable + v1->unk_42;

    obj->unk_07C = obj->unk_07A = 0;
    obj->flags |= OBJ_FLAG_DELETE;
    TASK_END(obj->currentTask);

    v2->lifetime = 0x10;
    v2->flags |= 0x10;
    v2->unk_36 = 0;
    v2->unk_38 = 0x10;

    v0 = projectile_spawn(obj, v1->unk_42);
    if (v0 != NULL) {
        obj->unk_076 |= 8;
        v0->unk_076 &= ~2;
        if (player->playerId != PLAYER_1) {
            v0->unk_07A = 2;
        } else {
            v0->unk_07C = 2;
        }
        v0->unk_1FC = 300;
    }
}

void projectile_impact_fade_model(Object *obj, Object *arg1) {
    Player *player = (Player *) obj->vars[0];
    Object *v0;
    Vec4i sp30;
    ProjectileDef *v1 = (ProjectileDef *) obj->vars[7];
    ColorRGBA sp24[2] = { { 215, 180, 45, 0 }, { 250, 190, 55, 0 } };

    if ((obj->unk_078 & 8) && (obj->unk_076 & 8)) {
        projectile_noop(obj);
        return;
    }

    obj->unk_07C = obj->unk_07A = 0;
    obj->flags |= OBJ_FLAG_DELETE;
    TASK_END(obj->currentTask);

    sp30.x = 0;
    sp30.y = 0;
    sp30.z = -obj->unk_1FC;
    math_rotate_vector(&sp30, &obj->rotation);
    sp30.x += obj->pos.x;
    sp30.z += obj->pos.z;
    obj->unk_1FC = 0;

    v0 = create_model_instance(&sp30, 0x1000, projectile_fade_away, player->effectModels[v1->unk_42]);
    if (v0 == NULL) {
        return;
    }

    v0->color.a = 255;
    v0->vars[0] = 5;
    v0->flags |= OBJ_FLAG_TRANSPARENT;
    v0->unk_076 &= ~2;
    if (player->playerId != PLAYER_1) {
        v0->unk_07A = 2;
    } else {
        v0->unk_07C = 2;
    }
    v0->unk_1FC = 300;
    create_light(v0, &sp24[player->playerId]);
}

ObjFunc D_8004A4C8[2] = { projectile_update_model, projectile_update_sprite }; // unused

void projectile_gore_homing_setup(Object *obj, s32 arg1, Object *arg2) {
    Player *player = (Player *) obj->vars[0];
    Object *v0;

    if (player->characterId == GORE && arg1 == 0) {
        arg2->unk_1E8 = projectile_impact_fade_model;
        v0 = func_80030908();
        if (v0 != NULL) {
            v0->vars[1] = 50;
            v0->vars[0] = 30;
        }
    }
}

Object *projectile_spawn(Object *obj, s32 projectileId) {
    Vec4i pos;
    Object *effectObj;
    Player *player = (Player *) obj->vars[0];
    ProjectileDef *effect = player->projectileTable + projectileId;
    s32 pad[2];

    if (effect->boneId >= 0) {
        func_80028120(obj, effect, &pos);
    } else {
        pos.x = effect->originX;
        pos.y = effect->originY;
        pos.z = effect->originZ;
        math_rotate_vector(&pos, &obj->rotation);
        pos.x += obj->pos.x;
        pos.y += obj->pos.y;
        pos.z += obj->pos.z;
    }

    if (effect->spriteIndex >= 0) {
        effectObj = create_3dsprite(&pos, 0x1100, projectile_update_sprite, player->effectSprites[effect->spriteIndex]);
        if (effectObj == NULL) {
            return effectObj;
        }

        effectObj->frameIndex = player->unk_44[effect->spriteFrame];
        effectObj->unk_08C = effectObj->vars[4] = effect->unk_1E;
    } else {
        effectObj =
            create_model_instance(&pos, 0x1000, projectile_update_model, player->effectModels[effect->modelIndex]);
        if (effectObj == NULL) {
            return effectObj;
        }

        effectObj->flags |= OBJ_FLAG_HIDDEN;
        effectObj->currentTask->start_delay = effect->unk_1E;
        player->projectileObj = effectObj;
    }

    if (effectObj->modInst == NULL) {
        return NULL;
    }

    if (effectObj != NULL) {
        if (effect->flags & 4) {
            if (player->playerId != PLAYER_1) {
                effectObj->unk_07A = 2;
            } else {
                effectObj->unk_07C = 2;
            }
            effectObj->unk_1FC = 300;
            effectObj->unk_076 |= 2;
            effectObj->unk_076 |= 8;
            effectObj->unk_1E8 = projectile_on_impact;
            player->flags |= PLAYER_FLAG_SHOOTED;
        }

        if (effect->flags & 0x40) {
            create_light(effectObj, &effect->lightColors[player->playerId]);
        }

        effectObj->vars[0] = player;
        effectObj->vars[1] = player->unk_44 + effect->spriteFrame;
        effectObj->vars[2] = 0;
        effectObj->vars[5] = effect->lifetime;
        effectObj->vars[6] = player->combatState;
        effectObj->vars[7] = effect;
        effectObj->vars[3] = projectileId;
        effectObj->velocity.x = effect->velocityX;
        effectObj->velocity.y = effect->velocityY;
        effectObj->velocity.z = effect->velocityZ;
        effectObj->unk_040.x = 0xF00000;
        effectObj->unk_040.y = 0xF00000;
        effectObj->unk_040.z = 0xF00000;

        math_rotate_vector(&effectObj->velocity, &obj->rotation);

        effectObj->vars[8] = effect->unk_32;
        effectObj->rotation.y = player->obj->rotation.y;
        effect->unk_40 = 0;

        if (effect->flags & 9) {
            effectObj->flags |= OBJ_FLAG_TRANSPARENT;
            effectObj->color.a = 255;

            if (effect->unk_38 > 0) {
                effectObj->vars[9] = 255 / effect->unk_38;
            } else if (effect->spriteIndex < 0 && effectObj->modInst->numAnimFrames != 0) {
                effectObj->vars[9] = 255 / effectObj->modInst->numAnimFrames;
            } else {
                effectObj->vars[9] = 255 / effectObj->modInst->numNodes; // ?????????
            }

            if (player->characterId == DEMITRON && effect->modelIndex == 0) {

                effectObj->vars[9] = 128 / effectObj->modInst->numAnimFrames;
                effectObj->color.a = 128;
            }
        }

        projectile_gore_homing_setup(obj, projectileId, effectObj);
    }

    return effectObj;
}

u8 projectile_apply_damage(Player *arg0, Player *arg1, Object *arg2) {
    s16 v0;
    CombatState *a2;
    u8 isBlock;

    a2 = (CombatState *) arg2->vars[6];

    if (gRoundOver && !gReplayActive) {
        return FALSE;
    }

    v0 = apply_damage_and_reaction(arg0, arg1, a2);
    isBlock = (v0 == 270 || v0 == 271);
    return isBlock;
}

void projectile_hit_opponent(Object *obj, Player *arg1, ProjectileDef *arg2, u8 arg3) {
    Player *player = (Player *) obj->vars[0];
    ProjectileDef *sp18 = player->projectileTable + arg2->unk_42;
    Object *v00;

    if (projectile_apply_damage(arg1, player, obj)) {
        sp18->lifetime = 0x10;
        sp18->flags |= 0x10;
        sp18->unk_36 = 0;
        sp18->unk_38 = 0x10;
    } else {
        sp18->lifetime = 0;
        sp18->flags &= ~0x10;
        sp18->unk_38 = -1;
    }

    if (arg3) {
        v00 = projectile_spawn(obj, arg2->unk_42);
        if (v00 != NULL) {
            v00->color.a = 128;
            if (v00->modInst->numAnimFrames != 0) {
                v00->vars[9] = 255 / v00->modInst->numAnimFrames;
            }
        }
    }

    projectile_cleanup(obj, arg2);
}

#ifdef NON_EQUIVALENT
u8 func_80022CD0(Object *obj) {
    Player *player;
    Vec4i *playerPos;
    Vec4i *oppPos;
    ProjectileDef *a2;
    Object *v0;
    Vec4i sp44;
    Player *sp20;
    s16 q;
    u32 dx, dz;
    s32 pad[2];

    player = (Player *) obj->vars[0];
    sp20 = gPlayers + (player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2);
    a2 = (ProjectileDef *) obj->vars[7];

    playerPos = &obj->pos;
    oppPos = &sp20->obj->pos;

    q = obj->vars[3];
    if (player->characterId == GORE) {
        if (q == 0) {
            if (1) {
                dx = ABS(playerPos->x - oppPos->x);
            }
            dz = ABS(playerPos->z - oppPos->z);

            // a2->unk_40 += 22;
            // obj->unk_1FC = a2->unk_40;
            if (FAST_HYPOT(dx, dz) < (obj->unk_1FC = a2->unk_40 += 22) &&
                !(sp20->combatState->flags & (CSF_JUMP | CSF_HOP))) {
                projectile_hit_opponent(obj, sp20, a2, FALSE);

                sp44.x = playerPos->x;
                sp44.z = playerPos->z;
                sp44.y = 0;
                v0 = create_model_instance(&sp44, 0x1000, projectile_fade_away, player->effectModels[a2->unk_42]);
                if (v0 != NULL) {
                    v0->color.a = 255;
                    v0->vars[0] = 255 / v0->modInst->numAnimFrames;
                    v0->flags |= OBJ_FLAG_TRANSPARENT;
                }
            }

            return TRUE;
        }
        return FALSE;
    }

    return FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/projectile/func_80022CD0.s")
u8 func_80022CD0(Object *obj);
#endif

void func_80022EC0(Object *obj) {
    Player *player;
    Player *opponent;
    s32 pad[2];
    Vec4s sp40;
    Vec4s sp38;
    Object *v00;
    ProjectileDef *sp30;
    ProjectileDef *sp2C;
    s32 pad2;

    sp2C = (ProjectileDef *) obj->vars[7];
    player = (Player *) obj->vars[0];
    opponent = gPlayers + (player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2);

    if (opponent->combatState->flags & CSF_INVINSIBLE) {
        return;
    }
    if (func_80022CD0(obj)) {
        return;
    }

    sp40.x = opponent->hitZones.headPos->x;
    sp40.y = opponent->hitZones.headPos->y;
    sp40.z = opponent->hitZones.headPos->z;

    sp38.x = obj->pos.x;
    sp38.y = obj->pos.y;
    sp38.z = obj->pos.z;

    if (is_point_in_hit_range(&sp40, &opponent->obj->pos, opponent->hitZones.radius1 + 80000, &sp38)) {
        if (!(sp2C->flags & 0x20) && !(player->flags & PLAYER_FLAG_2000)) {
            sp30 = player->projectileTable + sp2C->unk_42;
            if (projectile_apply_damage(opponent, player, obj)) {
                sp30->lifetime = 0x10;
                sp30->flags |= 0x10;
                sp30->unk_36 = 0;
                sp30->unk_38 = 0x10;
            } else {
                sp30->lifetime = 0;
                sp30->flags &= ~0x10;
                sp30->unk_38 = -1;
            }

            v00 = projectile_spawn(obj, sp2C->unk_42);
            if (v00 != NULL) {
                v00->unk_076 &= ~2;
                if (player->playerId != PLAYER_1) {
                    v00->unk_07A = 2;
                } else {
                    v00->unk_07C = 2;
                }
                v00->unk_1FC = 300;
            }

            projectile_cleanup(obj, sp2C);
        } else {
            projectile_cleanup(obj, sp2C);
        }

        player->projectileObj = NULL;
    }
}
