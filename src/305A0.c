#include "common.h"
#include "camera.h"
#include "task.h"

void func_8002FA98(Object *obj);
void func_80031DCC(Object *);
void func_80030DA8(Object *);
void func_800310C8(Object *);
void func_800309B4(Object *);
void func_8003088C(Object *);
void player_trans_func_9(Object *);
void func_80031D4C(Object *);
void func_80031E4C(Unk_8004BA6C *, HitboxBones *, Object *);

UnkK2Def D_80052CF0 = { "dusthit.sp3", func_8002FA98, 0, 0x1100, 0, 0x2800, 0 };
s32 D_80052D08[] = { 14, 17, 18, 21, 21, 24, 12, 15, 11, 14, 0, 0, 14, 17, 18, 21, 11, 14, 14, 17, 11, 14 };
Object *D_80052D60 = NULL;
s16 D_80052D64[] = { 0, 0 };
s16 D_80052D68[] = { 0, 0 };
s16 D_80052D6C[] = { 0, 0 };
s16 D_80052D70[] = { 0, 0 };
s16 D_80052D74[] = { 0, 0 };
s16 D_80052D78[] = { 2, 2 };

Vec4i D_8013C3A0[2];
s16 D_8013C3C0[2];
s32 D_8013C3C8[2];

u8 player_check_func_8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    return (player->flags & PLAYER_FLAG_800000) || gBattleSettings[player->playerId].isCpu;
}

void player_trans_func_3(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex > 5 && (player->flags & PLAYER_FLAG_10)) {
        player->flags &= ~PLAYER_FLAG_10;
        TASK_END(obj->currentTask);
    }
}

void func_8002FA2C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    player->flags &= ~PLAYER_FLAG_800000;
    if (!(player->combatState->flags & CSF_CROUCH)) {
        player->flags &= ~PLAYER_FLAG_10;
    }
    obj->currentTask->func = task_default_func;
}

void player_trans_func_4(Object *obj) {
    obj->currentTask->start_delay = 10;
    obj->currentTask->func = func_8002FA2C;
}

void func_8002FA98(Object *obj) {
    obj->color.a -= 5;
    obj->frameIndex++;
    if (obj->frameIndex > 9) {
        obj->flags |= OBJ_FLAG_DELETE;
    }
    obj->currentTask->start_delay = 2;
}

void func_8002FADC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 playerId = player->playerId;
    Vec4i *s1;
    Object *v0;
    Vec4i sp28;

    s1 = &D_8013C3A0[playerId];

    if ((abs(s1->x - obj->pos.x) > 20 || abs(s1->z - obj->pos.z) > 20) && !(player->flags & PLAYER_FLAG_400000)) {
        sp28.x = obj->pos.x;
        sp28.z = obj->pos.z;
        sp28.y = 0;
        v0 = create_3dsprite_with_properties(&sp28, &D_80052CF0, CONTEXT_ABAB);
        if (v0 != NULL) {
            v0->color.a = 60;
        }
    }

    s1->x = obj->pos.x;
    s1->z = obj->pos.z;
    if (--obj->vars[3] < 0) {
        player->total_damage = 0;
    }
}

void func_8002FBC8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 v0;
    s32 dx, dz;

    v0 = 0;
    dx = player->hitboxBones.thighPos->x - player->hitboxBones.headPos->x;
    dz = player->hitboxBones.thighPos->z - player->hitboxBones.headPos->z;

    if (dx != 0 || dz != 0) {
        v0 = (u32) (sqrtf(SQ(dx) + SQ(dz)) + 0.5) >> 1;
    }
    if (v0 < 150) {
        v0 = 150;
    }

    player->hitboxBones.comboRadius = SQ(v0);
    v0 = (v0 * 0xE000) >> 16;
    player->hitboxBones.strikeRadius = SQ(v0);

    if (player->combatState->flags & CSF_STANDING) {
        obj->currentTask->func = func_8002FADC;
    } else {
        player_trans_func_4(obj);
    }
    obj->vars[3] = 50;
}

void player_trans_func_1(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 playerId = player->playerId;

    player->flags &= ~PLAYER_FLAG_TRANSITION_LOCKED;
    obj->modInst->unk_A1C = D_8004BA98[player->characterId].x;
    obj->modInst->unk_A20 = D_8004BA98[player->characterId].z;
    obj->currentTask->start_delay = 2;
    obj->currentTask->func = func_8002FBC8;
    obj->currentTask->start_delay = 2;
    D_8013C3A0[playerId].x = obj->pos.x;
    D_8013C3A0[playerId].z = obj->pos.z;
}

void player_trans_func_7(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 playerId = player->playerId;

    player->flags &= ~PLAYER_FLAG_TRANSITION_LOCKED;
    obj->modInst->unk_A20 = D_8004BAF0[player->characterId].z;
    obj->modInst->unk_A1C = D_8004BAF0[player->characterId].x;
    obj->currentTask->start_delay = 2;
    obj->currentTask->func = func_8002FBC8;
    D_8013C3A0[playerId].x = obj->pos.x;
    D_8013C3A0[playerId].z = obj->pos.z;
}

void player_trans_func_10(Object *obj) {
    TASK_END(obj->currentTask);
}

void func_8002FEB4(Object *obj) {
    TASK_END(obj->currentTask);
}

void player_trans_func_15(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 sp1A;
    s32 temp;
    s16 v1;

    sp1A = (0xC00 - obj->rotation.y) & 0xFFF;

    temp = angle_diff(gPlayerAngle - (player->playerId != PLAYER_1 ? 0 : 0x800), sp1A);
    if (temp < 0) {
        v1 = temp + 0x800;
    } else {
        v1 = temp - 0x800;
    }

    obj->rotation.y = 0xC00 - sp1A - v1;
    TASK_END(obj->currentTask);
}

u8 player_check_func_6(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 pad[3];
    s16 characterId;
    s16 oppId = 1 - player->playerId;
    s16 temp;
    Vec4i sp34;

    characterId = gPlayers[oppId].characterId;
    temp = D_8004B920[characterId].unk_00;

    sp34.x = 0;
    sp34.y = 0;
    sp34.z = -temp;
    func_8001370C(&sp34, &obj->rotation);
    (gPlayers + oppId)->obj->pos.x = obj->pos.x + sp34.x;
    (gPlayers + oppId)->obj->pos.z = obj->pos.z + sp34.z;
    (gPlayers + oppId)->obj->rotation.y = 0x400 - ((0xC00 - obj->rotation.y) & 0xFFF);

    return TRUE;
}

void player_trans_func_19(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = gPlayers + 1 - player->playerId;
    s16 characterId = player->characterId;

    if (obj->frameIndex == player->combatState->maxFrame - 1) {
        player->damage = obj->vars[2];
        if (obj->vars[3] < 0) {
            player->total_damage += player->damage;
        } else {
            player->total_damage = player->damage;
            obj->vars[3] = -1;
        }

        if (gPlayMode != PLAY_MODE_PRACTICE) {
            opponent->obj->playerHp -= obj->vars[2];
        }
        if (opponent->obj->playerHp < 0) {
            opponent->obj->playerHp = 0;
        }
    }

    switch (characterId) {
        case AARON:
            projectile_spawn_at_frame(obj);
            break;
        case DEMONICA:
            if (gBattleSettings[1 - player->playerId].characterId == NIIKI &&
                obj->frameIndex < player->combatState->maxFrame - 1) {
                obj->pos.y = 100;
            } else {
                obj->pos.y = 0;
            }
            func_80031D4C(obj);
            break;
        default:
            if (D_8004BA40[characterId] != NULL) {
                func_80031D4C(obj);
            }
            break;
    }
}

void func_800301FC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex >= player->combatState->maxFrame - 2) {
        player->damage = obj->vars[2];
        if (obj->vars[3] < 0) {
            player->total_damage += player->damage;
        } else {
            player->total_damage = player->damage;
            obj->vars[3] = -1;
        }

        if (gPlayMode != PLAY_MODE_PRACTICE) {
            player->obj->playerHp -= obj->vars[2];
        }
        if (player->obj->playerHp < 0) {
            player->obj->playerHp = 0;
        }

        player->unk_18->func = func_8003184C;
    }
}

void player_trans_func_22(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 oppId = 1 - player->playerId;

    player->unk_18->func = func_800301FC;

    if (gPlayers[oppId].characterId != AARON) {
        obj->currentTask->func = player_trans_func_9;
    } else {
        TASK_END(obj->currentTask);
    }
}

void player_trans_func_8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 pad[2];
    s16 characterId;
    s16 oppId;
    s32 pad2;
    s16 temp;
    CombatState *sp44;
    Vec4i sp34;

    if (gRoundOver && gReplayActive == 0) {
        TASK_END(obj->currentTask);
        return;
    }

    if (obj->frameIndex != player->combatState->maxFrame - 1) {
        return;
    }

    characterId = player->characterId;
    oppId = 1 - player->playerId;
    player->hitCooldown = 2;

    if (!(player->flags & PLAYER_FLAG_NOT_FACING_OPP) && gPlayerDistance < D_8004C178[player->characterId] &&
        (gPlayers[oppId].combatState->flags & CSF_STANDING) && !(gPlayers[oppId].combatState->flags & CSF_INVINSIBLE)) {
        TASK_END(obj->currentTask);

        if (gPlayers[oppId].flags & PLAYER_FLAG_NOT_FACING_OPP) {
            if (!(gPlayers[oppId].combatState->flags & CSF_80)) {
                player_force_move(&gPlayers[oppId], 116, 1);
            }
            return;
        }

        player->flags |= PLAYER_FLAG_40000;

        D_80080236 = TRUE;
        player_force_move(&gPlayers[oppId], D_8004B8F4[characterId].unk_02, 1);
        player_force_move(player, 84, 1);
        D_80080236 = FALSE;
        sp44 = &player->combatStateTable[player->combatStateId];
        player->obj->varObj[2] = sp44->damage;

        temp = D_8004B8F4[characterId].unk_00;
        sp34.x = 0;
        sp34.y = 0;
        sp34.z = -temp;
        func_8001370C(&sp34, &obj->rotation);
        (gPlayers + oppId)->obj->pos.x = obj->pos.x + sp34.x;
        (gPlayers + oppId)->obj->pos.z = obj->pos.z + sp34.z;
        (gPlayers + oppId)->obj->rotation.y = 0x400 - ((0xC00 - obj->rotation.y) & 0xFFF);

        D_8008012C &= ~GFX_FLAG_10;
        func_80016264();

        switch (characterId) {
            case GORE:
                obj->flags |= OBJ_FLAG_800;
                break;
            case AARON:
                if (sp44->projBarrage >= 0) {
                    player->barrage = &player->barrageTable[sp44->projBarrage];
                    player->projectileObj = NULL;
                }
                break;
        }
    }
}

void player_trans_func_16(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 characterId;
    s16 oppId;
    s32 unused[3];

    if (obj->frameIndex == player->combatState->hitboxActiveStart) {
        characterId = player->characterId;
        oppId = 1 - player->playerId;
        player_force_move(&gPlayers[oppId], D_8004B920[characterId].unk_02, 1);

        if (player->characterId == AARON) {
            obj->currentTask->func = player_action_init_projectiles;
        } else if (D_8004BA6C[characterId] != NULL) {
            obj->currentTask->func = func_80031DCC;
        } else {
            TASK_END(obj->currentTask);
        }
    }
}

void player_trans_func_17(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (player->characterId == SONORK) {
        obj->currentTask->func = player_action_init_projectiles;
    } else if (D_8004BA6C[player->characterId] != NULL) {
        obj->currentTask->func = func_80031DCC;
    } else {
        TASK_END(obj->currentTask);
    }
}

u8 player_check_func_5(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[1 - player->playerId];

    if (opponent->flags & PLAYER_FLAG_10000) {
        return TRUE;
    } else {
        return FALSE;
    }
}

u8 func_800307C4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[1 - player->playerId];

    if (opponent->flags & PLAYER_FLAG_2000) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void func_80030824(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] > 60) {
        obj->flags |= OBJ_FLAG_DELETE;
        sPostCutsceneZoom = 0;
        D_80052D60 = 0;
    } else if (sPostCutsceneZoom > 0) {
        sPostCutsceneZoom -= 10;
    } else {
        obj->fn_render = func_8003088C;
    }
}

void func_8003088C(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] > 60) {
        obj->flags |= OBJ_FLAG_DELETE;
        sPostCutsceneZoom = 0;
        D_80052D60 = 0;
    } else if (sPostCutsceneZoom < obj->vars[1]) {
        sPostCutsceneZoom += 10;
    } else {
        obj->fn_render = func_80030824;
        obj->vars[1] -= 15;
    }
}

Object *func_80030908(void) {
    if (D_80052D60 != NULL) {
        D_80052D60->flags |= OBJ_FLAG_DELETE;
    }

    D_80052D60 = create_worker(func_8003088C, 0x1000);
    return D_80052D60;
}

void func_80030954(Object *obj) {
    if (obj->modInst->rootTransform.local_matrix.w.y > -200.0f) {
        func_800287AC(obj);
        obj->currentTask->func = func_800309B4;
        obj->currentTask->start_delay = 20;
    }
}

void func_800309B4(Object *obj) {
    if (obj->modInst->rootTransform.local_matrix.w.y > -200.0f) {
        return;
    }

    obj->currentTask->func = func_80030954;
}

void player_trans_func_9(Object *obj) {
    Object *v0;

    if (obj->modInst->rootTransform.local_matrix.w.y > -200.0f) {
        func_800287AC(obj);
        v0 = func_80030908();
        if (v0 != NULL) {
            v0->vars[1] = 50;
        }

        obj->currentTask->func = func_800309B4;
        obj->currentTask->start_delay = 20;
    }
}

void player_trans_func_2(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex > (player->combatState->maxFrame >> 1)) {
        player->animTask->func = anim_advance;
        player->animTask->start_delay = 0;
        player->animTask->flags = TASK_FLAG_ENABLED;
    } else {
        player->animTask->func = anim_reverse;
        player->animTask->start_delay = 0;
        player->animTask->flags = TASK_FLAG_ENABLED;
        obj->flags |= OBJ_FLAG_8000;
    }

    player->flags &= ~PLAYER_FLAG_10;
    TASK_END(obj->currentTask);
}

void func_80030AFC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    obj->velocity.y += obj->acceleration.y;
    obj->pos.y += obj->velocity.y >> 16;

    if (obj->pos.y >= 0) {
        obj->pos.y = 0;
        if (player->flags & PLAYER_FLAG_NOT_FACING_OPP) {
            player_force_move(player, 117, 1);
        } else {
            player_force_move(player, 83, 1);
        }
    }
}

void player_trans_func_12(Object *obj) {
    obj->velocity.y = 0xFFEC0000;
    obj->acceleration.y = 0x20000;
    obj->currentTask->func = func_80030AFC;
    func_800310C8(obj);
}

u8 player_check_func_2(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u8 sp1B;
    s32 t8;

    sp1B = FALSE;
    t8 = (0xC00 - obj->rotation.y) & 0xFFF;

    if (obj->flags & OBJ_FLAG_800000) {
        return FALSE;
    }

    if (player->playerId != PLAYER_1) {
        if (abs(angle_diff(gPlayerAngle, t8)) > 0x400) {
            sp1B = TRUE;
        }
    } else {
        if (abs(angle_diff(gPlayerAngle, t8)) < 0x400) {
            sp1B = TRUE;
        }
    }

    return sp1B;
}

void func_80030C68(Object *obj) {
    s16 v0;

    v0 = (0xC00 - obj->rotation.y) & 0xFFF;
    obj->rotation.y = 0x400 - v0;
}

u8 player_check_func_1(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    if (((opponent->combatState->flags & (CSF_200 | CSF_400 | CSF_10000 | CSF_JUGGLED)) &&
         !(opponent->combatState->flags & CSF_INVINSIBLE)) > 0) {
        if (player->playerId != PLAYER_1) {
            player->obj->rotation.y = 0xC00 - gPlayerAngle;
        } else {
            player->obj->rotation.y = 0x1400 - gPlayerAngle;
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

void func_80030D60(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    obj->currentTask->start_delay = player->combatStateTable[player->combatStateId].minFrame - obj->frameIndex + 2;
    obj->currentTask->func = func_80030DA8;
}

void func_80030DA8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    s16 a1 = 97;

    if ((opponent->flags & (PLAYER_FLAG_TRANSITION_LOCKED | PLAYER_FLAG_10000 | PLAYER_FLAG_20000)) &&
        gPlayerDistance < 400 && obj->frameIndex >= player->combatState->hitboxActiveStart) {
        if (opponent->combatState->flags & CSF_200) {
            a1 = 206;
        }
        player_force_move(opponent, a1, 1);
        TASK_END(obj->currentTask);
    }
}

void func_80030E88(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (gPlayerDistance < D_8004C1A4[player->characterId] && player->combatStateId != 17) {
        player_force_move(player, 110, 1);
        TASK_END(obj->currentTask);
    }
}

void player_trans_func_5(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (player->characterId == MORPHIX) {
        obj->currentTask->start_delay = 2;
    } else {
        obj->currentTask->start_delay = 6;
    }
    obj->currentTask->func = func_80030E88;
}

u8 func_80030F40(s32 arg0) {
    return gPlayerDistance > 550;
}

void func_80030F5C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    s16 sp26;
    s16 sp1A;

    sp26 = (0xC00 - opponent->obj->rotation.y) & 0xFFF;
    sp1A = angle_diff(gPlayerAngle, sp26);

    if (sp1A < 0) {
        sp1A -= 0x800;
    } else {
        sp1A += 0x800;
    }
    opponent->obj->rotation.y = 0xC00 - (sp26 + sp1A);
}

void func_8003102C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    opponent->flags |= PLAYER_FLAG_10;
}

void player_trans_func_6(Object *obj) {
    if (obj->pos.y == 0) {
        func_8002856C(obj);
    }

    obj->currentTask->func = func_8003102C;
}

void func_800310C8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    if ((opponent->combatState->flags & CSF_100) || (opponent->behavior->newFlags & PLAYER_FLAG_10)) {
        opponent->flags |= PLAYER_FLAG_10;
    } else {
        opponent->flags &= ~PLAYER_FLAG_10;
    }
}

void player_trans_func_24(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex == player->combatState->maxFrame - 1) {
        func_800310C8(obj);
    }
}

void player_trans_func_14(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    if (opponent->combatState->flags & CSF_100) {
        opponent->flags |= PLAYER_FLAG_10;
    }

    if (obj->frameIndex >= 24) {
        player->flags &= ~PLAYER_FLAG_10;
    }
}

void player_trans_func_21(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    Object *sp24 = gPlayerObjects[PLAYER_1];
    Object *sp20 = gPlayerObjects[PLAYER_2];
    s16 sp1E;
    s16 sp1C;
    s16 sp1A;

    if (opponent->combatState->damage != 0) {
        opponent->flags |= PLAYER_FLAG_10;
    }

    if (!(player->flags & PLAYER_FLAG_10) && (player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
        (player->combatStateId == 39 || player->combatStateId == 84)) {
        if (player->playerId != PLAYER_1) {
            sp1C = (0xC00 - sp20->rotation.y) & 0xFFF;
            sp1A = angle_diff(gPlayerAngle - 0x800, sp1C);

            if (abs(sp1A) > 140) {
                if (sp1A < 0) {
                    sp1A = -140;
                } else {
                    sp1A = 140;
                }
            }
            sp20->rotation.y = 0xC00 - (sp1C + sp1A);
        } else {
            sp1E = (0xC00 - sp24->rotation.y) & 0xFFF;
            sp1A = angle_diff(gPlayerAngle, sp1E);

            if (abs(sp1A) > 140) {
                if (sp1A < 0) {
                    sp1A = -140;
                } else {
                    sp1A = 140;
                }
            }
            sp24->rotation.y = 0xC00 - (sp1E + sp1A);
        }
    }
}

void player_trans_func_28(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Object *player1 = gPlayerObjects[PLAYER_1];
    Object *player2 = gPlayerObjects[PLAYER_2];

    if (!(player->flags & PLAYER_FLAG_NOT_FACING_OPP) && obj->frameIndex >= player->combatState->maxFrame - 1) {
        if (player->playerId != PLAYER_1) {
            player2->rotation.y = 0xC00 - gPlayerAngle;
        } else {
            player1->rotation.y = 0x1400 - gPlayerAngle;
        }
    }
}

void player_trans_func_23(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent;
    s32 v12;
    s16 a3;

    opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    a3 = opponent->combatStateId;
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
        if (opponent->flags & PLAYER_FLAG_10) {
            if (opponent->playerId != PLAYER_1) {
                opponent->obj->rotation.y = 0x1400 - gPlayerAngle;
            } else {
                opponent->obj->rotation.y = 0xC00 - gPlayerAngle;
            }
        } else {
            if (opponent->playerId != PLAYER_1) {
                opponent->obj->rotation.y = 0xC00 - gPlayerAngle;
            } else {
                opponent->obj->rotation.y = 0x1400 - gPlayerAngle;
            }
        }
    }

    if (player->unk_DBC > 256 || (opponent->combatState->flags & CSF_JUMP) || v12) {
        player->flags |= PLAYER_FLAG_10;
        TASK_END(obj->currentTask);
    }
}

u8 player_check_func_3(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (gBattleSettings[player->playerId].isCpu) {
        return TRUE;
    }

    return gPlayerInput[player->playerId].mirrored;
}

u8 player_check_func_4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (gBattleSettings[player->playerId].isCpu) {
        return TRUE;
    }

    return ~gPlayerInput[player->playerId].mirrored;
}

u8 player_check_func_7(Object *obj) {
    Player *player;
    Player *v1;
    s32 a1;

    player = (Player *) obj->varObj[0];
    v1 = gPlayers + (1 - player->playerId);

    a1 = (v1->combatState->flags & CSF_100000) && (v1->combatState->hitboxActiveEnd < v1->obj->frameIndex ||
                                                   v1->combatState->hitboxActiveStart > v1->obj->frameIndex);
    return a1 > 0;
}

void player_trans_func_11(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *v0;
    CombatState *v1;

    v0 = gPlayers + (1 - player->playerId);
    v1 = &player->combatStateTable[player->combatStateId];

    if (!(v1->flags & CSF_BLOCK) && gBattleSettings[player->playerId].isCpu && (v0->combatState->flags & CSF_100000) &&
        v0->obj->frameIndex < v0->combatState->hitboxActiveStart) {
        if (v0->flags & PLAYER_FLAG_1) {
            player_force_move(player, 39, 1);
            player->aiState.stateCallback = func_8001D070;
            player->aiState.actionParam = 60;
        } else {
            player_force_move(player, 59, 1);
            player->aiState.stateCallback = func_8001CE18;
            player->aiState.actionParam = 60;
        }
    }
}

#ifdef NON_EQUIVALENT
void func_8003184C(Object *arg0) {
    Vec4s sp60;
    Vec4s sp58;
    Player *temp_ra;
    u8 temp_v1;
    u8 temp_t8;
    s16 temp_v0;
    s32 temp_ft3;
    s16 var_t3;

    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v1_3;

    s16 var_t2;

    s16 var_a2;
    s16 var_t0;

    temp_ra = (Player *) arg0->varObj[0];
    temp_v1 = temp_ra->playerId;
    temp_t8 = 1 - temp_v1;

    sp60.z = 0;
    sp58.x = 0;
    sp58.z = 0;

    temp_v0 = temp_ra->behaviorId;
    temp_ft3 = gPlayerObjects[temp_t8]->modInst->rootTransform.world_matrix.y.y + 360.0f;
    if (temp_v0 == 0 || temp_v0 == 7 || (temp_ra->combatState->flags & CSF_BLOCK)) {
        sp60.x = func_80012518(temp_ft3, gPlayerDistance);
        var_t2 = angle_diff((s16) ((0xC00 - arg0->rotation.y) & 0xFFF), (s16) (gPlayerAngle - (temp_t8 << 0xB)));

        if (var_t2 > 1700) {
            var_t2 = 1700;
        } else if (var_t2 < -1100) {
            var_t2 = -1100;
        }

        var_t0 = D_80052D64[temp_v1];
        var_a2 = D_80052D68[temp_v1];
        var_t3 = var_t2 - var_t0 - var_a2;
    } else {
        var_a2 = D_80052D68[temp_v1];
        var_t0 = D_80052D64[temp_v1];
        var_t2 = 0;
        sp60.x = 0;
        var_t3 = -(var_a2 + var_t0);
    }

    if (var_t3 == 0) {
        D_80052D70[temp_v1] = D_80052D74[temp_v1] = 0;
        D_80052D78[temp_v1] = 2;
        D_8013C3C0[temp_v1] = var_a2 + var_t0;
    }

    D_80052D6C[temp_v1] = ((D_8013C3C0[temp_v1] + var_t2) >> 1);
    D_80052D74[temp_v1] += D_80052D78[temp_v1];
    D_80052D70[temp_v1] += D_80052D74[temp_v1];

    if (D_80052D70[temp_v1] > 60) {
        D_80052D70[temp_v1] = 60;
        D_80052D78[temp_v1] = 0;
    } else if (D_80052D70[temp_v1] <= 0) {
        D_80052D70[temp_v1] = 2;
        D_80052D78[temp_v1] = 2;
    }
    if (D_80052D70[temp_v1] < var_t3) {
        var_t3 = D_80052D70[temp_v1];
    } else if (var_t3 < -D_80052D70[temp_v1]) {
        var_t3 = -D_80052D70[temp_v1];
    }
    if (var_a2 > 0) {
        temp_v1_3 = var_t0 + var_t3;
        if (var_t3 >= 0) {
            temp_v0_3 = var_a2 + var_t3;
            if (temp_v0_3 > 600) {
                var_t3 = temp_v0_3 - 600;
                temp_v1_3 = var_t0 + var_t3;

                sp58.y = var_a2 = D_80052D68[temp_v1] = 600;
                if (temp_v1_3 > 1100) {
                    sp60.y = var_t0 = D_80052D64[temp_v1] = 1100;
                } else {
                    sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
                }
            } else {
                sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_3;
                sp60.y = var_t0;
            }
        } else {
            if (temp_v1_3 < 0) {
                temp_v0_4 = var_a2 + temp_v1_3;
                var_t3 = temp_v1_3;

                sp60.y = var_t0 = D_80052D64[temp_v1] = 0;
                if (temp_v0_4 < 0) {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = 0;
                } else {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_4;
                }
            } else {
                sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
                sp58.y = var_a2;
            }
        }
    } else if (var_a2 < 0) {
        temp_v0_5 = var_a2 + var_t3;
        if (var_t3 >= 0) {
            temp_v1_3 = var_t0 + var_t3;
            if (temp_v1_3 > 0) {
                temp_v0_6 = var_a2 + temp_v1_3;
                var_t3 = temp_v1_3;

                sp60.y = var_t0 = D_80052D64[temp_v1] = 0;
                if (temp_v0_6 > 0) {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = 0;
                } else {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_6;
                }
            } else {
                sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
                sp58.y = var_a2;
            }
        } else if (temp_v0_5 < -600) {
            var_t3 = temp_v0_5 + 600;
            sp58.y = var_a2 = D_80052D68[temp_v1] = -600;
            temp_v1_3 = var_t0 + var_t3;
            if (temp_v1_3 < -500) {
                sp60.y = var_t0 = D_80052D64[temp_v1] = -500;
            } else {
                sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
            }
        } else {
            sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_5;
            sp60.y = var_t0;
        }
    } else {
        sp60.y = var_t0;
        sp58.y = var_a2 = D_80052D68[temp_v1] = var_a2 + var_t3;
    }

    if (D_80052D74[temp_v1] > 0) {
        if (var_t3 >= 0 && var_t0 + var_a2 >= D_80052D6C[temp_v1]) {
            D_80052D78[temp_v1] = -2;
        } else if (D_80052D6C[temp_v1] >= var_t0 + var_a2) {
            D_80052D78[temp_v1] = -2;
        }
    }

    math_rotate(&temp_ra->unk_750.local_matrix, &sp60);
    math_rotate(&temp_ra->unk_868.local_matrix, &sp58);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8003184C.s")
#endif

void func_80031D4C(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA40[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->frameIndex == s0->unk_00) {
            func_80031E4C(s0, &v0->hitboxBones, obj);
        }
    }
}

void func_80031DCC(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA6C[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->frameIndex == s0->unk_00) {
            func_80031E4C(s0, &v0->hitboxBones, obj);
        }
    }
}

void func_80031E4C(Unk_8004BA6C *arg0, HitboxBones *arg1, Object *arg2) {
    Player *player = (Player *) arg2->varObj[0];
    Vec4f *v0;
    Vec3s sp18;

    switch (arg0->unk_02) {
        case 0:
            v0 = arg1->headPos;
            break;
        case 1:
            v0 = arg1->thighPos;
            break;
        case 2:
            v0 = arg1->handPos;
            break;
        case 3:
            v0 = &arg1->torsoTransform.world_matrix.w;
            break;
        case 4:
            v0 = &arg1->grabTransform.world_matrix.w;
            break;
        case 5:
            v0 = arg1->footPos;
            break;
        case 6:
        default:
            v0 = arg1->torsoPos;
            break;
    }

    sp18.x = v0->x;
    sp18.y = v0->y;
    sp18.z = v0->z;
    spawn_hit_effect(&sp18, arg0->unk_04, arg2, &D_8004BA14[player->characterId]);
}

void player_trans_func_18(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (v0->characterId == AARON) {
        obj->currentTask->func = player_action_init_projectiles;
    } else {
        TASK_END(obj->currentTask);
    }
}

void func_80031F60(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    player_force_move(v0, 382, 1);
}

void player_trans_func_26(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (obj->frameIndex == v0->combatState->maxFrame - 2) {
        obj->currentTask->func = func_80031F60;
    }
}

void player_trans_func_25(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (v0->flags & PLAYER_FLAG_NOT_FACING_OPP) {
        player_force_move(v0, 383, 1);
    } else {
        obj->currentTask->start_delay = 60;
        obj->currentTask->func = func_80031F60;
    }
}

void func_8003201C(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    player_force_move(v0, 140, 1);
}

void player_trans_func_27(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (gBattleSettings[PLAYER_1].characterId == gBattleSettings[PLAYER_2].characterId && v0->playerId != 0) {
        obj->currentTask->start_delay = 15;
    }

    obj->currentTask->func = func_8003201C;
}

void func_8003208C(Object *obj) {
    Vec4i sp20;
    Player *v0 = (Player *) obj->varObj[0];
    s32 v1 = v0->playerId;

    if (obj->frameIndex == v0->combatState->maxFrame - 1) {
        sp20.x = sp20.y = 0;
        sp20.z = -D_8013C3C8[v1];
        func_8001370C(&sp20, &obj->rotation);
        obj->pos.x += sp20.x;
        obj->pos.z += sp20.z;
        obj->currentTask->func = projectile_spawn_at_frame;
    }

    projectile_spawn_at_frame(obj);
}

void player_trans_func_20(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    s32 v1 = v0->playerId;

    if (v0->characterId == DEMITRON && obj->frameIndex > 50) {
        projectile_spawn_at_frame(obj);
        obj->currentTask->func = projectile_spawn_at_frame;
    } else {
        D_8013C3C8[v1] = gPlayerDistance;
        player_action_init_projectiles(obj);
        obj->currentTask->func = func_8003208C;
    }
}
