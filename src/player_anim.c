#include "common.h"
#include "camera.h"
#include "task.h"

u8 ai_select_transition(Player *);

void player_anim_pingpong_forward(Object *);

void player_anim_next_transition(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    s32 stateFlags;

    if (gBattleSettings[playerId].isCpu && !D_800801F0) {
        if (func_8001BB80(player) || func_8001C53C(player, TRUE)) {
            return;
        }

        func_8001BB2C(player);

        if (player->nextLogicState >= 0 && (player->flags & PLAYER_FLAG_1000)) {
            if (ai_select_transition(player)) {
                player->unk_180 |= 0x8000;
                return;
            }
        }
    } else if (!(player->flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
               (gPlayerInput[playerId].accumulated || (player->flags & PLAYER_FLAG_1000)) &&
               player->nextLogicState >= 0 && !(player->animTask->flags & TASK_FLAG_FRAME_TRIGGER)) {
        if (player_select_transition(player, TRUE)) {
            return;
        }
    }

    D_80080236 = TRUE;
    stateFlags = player->currentState->flags;
    if (player->flags & PLAYER_FLAG_8000000) {
        player->flags &= ~PLAYER_FLAG_8000000;
        stateFlags ^= STATE_FLAG_1 | STATE_FLAG_4;
    }

    if (stateFlags & STATE_FLAG_1) {
        func_8000636C(player, 320, FALSE);
    } else {
        func_8000636C(player, 68, FALSE);
    }

    D_80080236 = FALSE;
    player->flags |= PLAYER_FLAG_TRANSITION_LOCKED;
}

void func_80023ED0(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex > player->currentState->duration + 1) {
        obj->frameIndex--;
    } else {
        obj->frameIndex--;
        player_anim_next_transition(obj);
    }
}

void player_anim_pingpong_backward(Object *obj) {
    if (obj->frameIndex != 0) {
        obj->frameIndex--;
    } else {
        obj->frameIndex++;
        obj->currentTask->func = player_anim_pingpong_forward;
    }
}

void player_anim_pingpong_forward(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames - 1) {
        obj->frameIndex++;
    } else {
        obj->frameIndex--;
        obj->currentTask->func = player_anim_pingpong_backward;
    }
}

void player_anim_step_once(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames - 1) {
        obj->frameIndex++;
    } else {
        TASK_END(obj->currentTask);
    }
}

void func_80023FDC(Object *obj) {
    Player *player;
    s16 characterId;

    if (obj->frameIndex < ((Player *) obj->varObj[0])->currentState->unk_02) {
        obj->frameIndex++;
        return;
    } else {
        obj->frameIndex = 0;
        player = (Player *) obj->varObj[0];
        characterId = player->characterId;

        if (obj->modInst->velocity.z != 0) {
            if (player->currentState->flags & STATE_FLAG_4) {
                obj->modInst->velocity.z = D_8004BA98[characterId].z;
            } else {
                obj->modInst->velocity.z = D_8004BAF0[characterId].z;
            }
            obj->modInst->currentRootPos.z = obj->modInst->baseRootPos.z;
        } else {
            obj->modInst->previousAnimId = -1;
        }
    }
}

void func_80024078(Object *obj) {
    if (obj->frameIndex < ((Player *) obj->varObj[0])->currentState->unk_02 - 1) {
        obj->frameIndex++;
    } else {
        obj->frameIndex++;
        player_anim_next_transition(obj);
    }
}

void func_800240C8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Vec4i sp2C;

    if (player->currentState->unk_2C < 0) {
        TASK_END(obj->currentTask);
    } else if (obj->frameIndex >= player->currentState->unk_2E) {
        func_8002C340();

        sp2C.x = (gPlayers[PLAYER_1].obj->pos.x + gPlayers[PLAYER_2].obj->pos.x) >> 1;
        sp2C.z = (gPlayers[PLAYER_1].obj->pos.z + gPlayers[PLAYER_2].obj->pos.z) >> 1;
        sp2C.y = 0;
        func_80038E8C(gCamera, &sp2C, obj->rotation.y,
                      obj->modInst->animations[player->stateTable[player->currentState->unk_2C].animationId]);

        gCamera->currentTask->func = func_8002C490;
        gCamera->currentTask->start_delay = 0;
        gCamera->currentTask->flags = TASK_FLAG_ENABLED;
        gCamera->currentTask->start_delay = 1;
        TASK_END(obj->currentTask);
    }
}

void func_80024214(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 unused[2];
    ActionState *currentState;

    currentState = player->stateTable + player->stateId;
    player->currentState = currentState;

    if (currentState->unk_2C >= 0 && currentState->unk_2E != -1) {
        player->cameraTask->func = func_800240C8;
        player->cameraTask->start_delay = 0;
        player->cameraTask->flags = TASK_FLAG_ENABLED;
    }

    if (currentState->unk_30 != -1) {
        func_80034C18(obj, player->unk_68 + currentState->unk_30 * obj->modInst->numNodes);
    } else {
        func_80034A58(obj);
    }

    obj->currentTask->func = func_80024078;
    obj->frameIndex++;

    if (currentState->flags & STATE_FLAG_10) {
        obj->flags |= OBJ_FLAG_400;
        if (currentState->flags & STATE_FLAG_8000) {
            obj->flags |= OBJ_FLAG_20000;
        }
    } else {
        obj->flags &= ~OBJ_FLAG_400;
    }

    if (currentState->flags & STATE_FLAG_80) {
        obj->flags |= OBJ_FLAG_800000;
    }

    if (currentState->flags & STATE_FLAG_200000) {
        obj->flags |= OBJ_FLAG_100000;
    }
}

void func_80024390(Object *obj) {
    ObjectTaskParams *sp24;
    Player *player = (Player *) obj->varObj[0];
    ActionState *currentState;

    currentState = player->currentState;
    sp24 = &obj->currentTask->params;

    if (player->stateId >= 0) {
        currentState = player->stateTable + player->stateId;
        if (currentState->animationId == obj->modInst->currentAnimId && obj->frameIndex + 1 < currentState->duration) {
            obj->frameIndex++;
            player->animTask->flags |= TASK_FLAG_FRAME_TRIGGER;
            player->animTask->unk_86 = currentState->duration - 2;
            player->animTask->conditional_context.flags = TASK_FLAG_ENABLED;
            player->animTask->conditional_context.func = func_80024214;
            obj->currentTask->func = func_80024078;
            return;
        }

        if (currentState->animationId == obj->modInst->currentAnimId && obj->frameIndex == currentState->duration - 1) {
            func_80024214(obj);
            return;
        }

        if (currentState->unk_2C >= 0 && currentState->unk_2E != -1) {
            player->cameraTask->func = func_800240C8;
            player->cameraTask->start_delay = 0;
            player->cameraTask->flags = TASK_FLAG_ENABLED;
        }

        if (currentState->unk_30 != -1) {
            func_80034C18(obj, player->unk_68 + currentState->unk_30 * obj->modInst->numNodes);
        } else {
            func_80034A58(obj);
        }

        player->currentState = currentState;

        if (player->flags & PLAYER_FLAG_800) {
            obj->frameIndex = currentState->unk_02;
        } else {
            obj->frameIndex = MAX(currentState->duration, sp24->unk_08);
        }

        obj->modInst->currentAnimId = currentState->animationId;
        obj->modInst->previousAnimId = -1;
    }

    obj->currentTask->func = sp24->unk_00_f; // ????

    if (currentState->flags & STATE_FLAG_10) {
        obj->flags |= OBJ_FLAG_400;
        if (currentState->flags & STATE_FLAG_8000) {
            obj->flags |= OBJ_FLAG_20000;
        } else {
            obj->flags &= ~OBJ_FLAG_20000;
        }
    } else {
        obj->flags &= ~OBJ_FLAG_400;
    }

    if (currentState->flags & STATE_FLAG_80) {
        obj->flags |= OBJ_FLAG_400000;
    }

    if (currentState->flags & STATE_FLAG_200000) {
        obj->flags |= OBJ_FLAG_100000;
    }
}

void func_80024640(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 i;
    s32 s2;
    ObjectTaskParams *v0;

    if (obj->frameIndex < player->currentState->unk_02) {
        obj->frameIndex++;
        return;
    }

    player->flags &= ~PLAYER_FLAG_TRANSITION_LOCKED;
    v0 = &obj->currentTask->params;
    player->unk_08->func = v0->unk_10;
    player->unk_08->start_delay = 0;
    player->unk_08->flags = TASK_FLAG_ENABLED;
    func_80024390(obj);

    if (obj->frameIndex >= 2) {
        model_change_animation(obj);
        obj->modInst->previousAnimId = obj->modInst->currentAnimId;
        obj->flags |= OBJ_FLAG_8000;

        s2 = obj->frameIndex;
        for (i = 0; i < s2; i += 2) {
            obj->frameIndex = i;
            model_process_animation(obj);
        }

        obj->flags &= ~OBJ_FLAG_8000;
        obj->frameIndex = s2;
    }

    player->unk_180 &= ~0x20000;
}

void func_80024764(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    ActionState *temp;

    obj->currentTask->func = func_80024640;
    obj->frameIndex = 1;
    temp = obj->currentTask->params.stateId + player->stateTable; // required to match
    player->currentState = temp;
    obj->modInst->currentAnimId = temp->animationId;
    player->flags |= PLAYER_FLAG_TRANSITION_LOCKED;
    player->unk_180 |= 0x20000;
}

void func_800247CC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    ObjectTask *v0;
    s32 pad2;
    s16 moveId;
    s16 *transitionTable;
    TaskContext *stack;
    ObjectTask *currentTask;

    v0 = player->animTask;
    moveId = v0->params.unk_00_i;
    transitionTable = player->logicStates;
    currentTask = obj->currentTask;
    obj->frameIndex++;

    if (player_make_transition(player, TRUE, moveId)) {
        player->nextLogicState = transitionTable[moveId + 1];
        player->unk_184 = FALSE;
        currentTask->stackPos--;
    } else {
        stack = currentTask->stack + (--currentTask->stackPos);
        currentTask->func = stack->func;
        currentTask->flags = stack->flags;
        currentTask->start_delay = stack->start_delay;

        if (currentTask->start_delay != 0) {
            currentTask->start_delay--;
        } else {
            currentTask->func(obj);
        }
    }
}

void player_play_sounds(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 soundTableIndex = player->currentState->soundTableIndex;
    AnimationSoundTriggers *soundTable = player->soundTable;
    s16 playerId = player->playerId;

    if (soundTableIndex != -1) {
        soundTable += soundTableIndex;
        if (obj->frameIndex != 0) {
            if (obj->frameIndex == soundTable->frame1) {
                sound_play(playerId, soundTable->soundId1);
            }
            if (obj->frameIndex == soundTable->frame2) {
                sound_play(playerId, soundTable->soundId2);
            }
            if (obj->frameIndex == soundTable->frame3) {
                sound_play(playerId, soundTable->soundId3);
            }
            if (obj->frameIndex == soundTable->frame4) {
                sound_play(playerId, soundTable->soundId4);
            }
        }
    }
}

void func_800249A4(Object *obj) {
}
