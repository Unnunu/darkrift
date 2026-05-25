#include "common.h"
#include "camera.h"
#include "task.h"

u8 ai_select_transition(Player *);

void player_anim_pingpong_forward(Object *);

void player_anim_next_transition(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    s32 stateFlags;

    if (gBattleSettings[playerId].isCpu && !gRoundOver) {
        if (ai_advance_sequence(player) || ai_decide(player, TRUE)) {
            return;
        }

        ai_reset(player);

        if (player->nextLogicState >= 0 && (player->flags & PLAYER_FLAG_1000)) {
            if (ai_select_transition(player)) {
                player->aiState.aiFlags |= 0x8000;
                return;
            }
        }
    } else if (!(player->flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
               (gPlayerInput[playerId].accumulated || (player->flags & PLAYER_FLAG_1000)) &&
               player->nextLogicState >= 0 && !(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME)) {
        if (player_select_transition(player, TRUE)) {
            return;
        }
    }

    D_80080236 = TRUE;
    stateFlags = player->currentStateDef->flags;
    if (player->flags & PLAYER_FLAG_8000000) {
        player->flags &= ~PLAYER_FLAG_8000000;
        stateFlags ^= STATE_FLAG_1 | STATE_FLAG_4;
    }

    if (stateFlags & STATE_FLAG_1) {
        player_apply_move(player, 320, FALSE);
    } else {
        player_apply_move(player, 68, FALSE);
    }

    D_80080236 = FALSE;
    player->flags |= PLAYER_FLAG_TRANSITION_LOCKED;
}

void func_80023ED0(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex > player->currentStateDef->duration + 1) {
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

void player_anim_loop(Object *obj) {
    Player *player;
    s16 characterId;

    if (obj->frameIndex < ((Player *) obj->varObj[0])->currentStateDef->unk_02) {
        obj->frameIndex++;
        return;
    } else {
        obj->frameIndex = 0;
        player = (Player *) obj->varObj[0];
        characterId = player->characterId;

        if (obj->modInst->velocity.z != 0) {
            if (player->currentStateDef->flags & STATE_FLAG_4) {
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
    if (obj->frameIndex < ((Player *) obj->varObj[0])->currentStateDef->unk_02 - 1) {
        obj->frameIndex++;
    } else {
        obj->frameIndex++;
        player_anim_next_transition(obj);
    }
}

void func_800240C8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Vec4i sp2C;

    if (player->currentStateDef->cameraStateIndex < 0) {
        TASK_END(obj->currentTask);
    } else if (obj->frameIndex >= player->currentStateDef->cameraAnimIndex) {
        camera_save_state();

        sp2C.x = (gPlayers[PLAYER_1].obj->pos.x + gPlayers[PLAYER_2].obj->pos.x) >> 1;
        sp2C.z = (gPlayers[PLAYER_1].obj->pos.z + gPlayers[PLAYER_2].obj->pos.z) >> 1;
        sp2C.y = 0;
        func_80038E8C(
            gCamera, &sp2C, obj->rotation.y,
            obj->modInst->animations[player->stateDefs[player->currentStateDef->cameraStateIndex].animationId]);

        gCamera->currentTask->func = camera_cutscene_playback;
        gCamera->currentTask->start_delay = 0;
        gCamera->currentTask->flags = TASK_FLAG_ENABLED;
        gCamera->currentTask->start_delay = 1;
        TASK_END(obj->currentTask);
    }
}

void func_80024214(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 unused[2];
    PlayerStateDef *currentState;

    currentState = player->stateDefs + player->currentStateId;
    player->currentStateDef = currentState;

    if (currentState->cameraStateIndex >= 0 && currentState->cameraAnimIndex != -1) {
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
    s32 *sp24;
    Player *player = (Player *) obj->varObj[0];
    PlayerStateDef *currentState;

    currentState = player->currentStateDef;
    sp24 = obj->currentTask->params;

    if (player->currentStateId >= 0) {
        currentState = player->stateDefs + player->currentStateId;
        if (currentState->animationId == obj->modInst->currentAnimId && obj->frameIndex + 1 < currentState->duration) {
            obj->frameIndex++;
            player->animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
            player->animTask->triggerAt = currentState->duration - 2;
            player->animTask->triggerSlot.flags = TASK_FLAG_ENABLED;
            player->animTask->triggerSlot.func = func_80024214;
            obj->currentTask->func = func_80024078;
            return;
        }

        if (currentState->animationId == obj->modInst->currentAnimId && obj->frameIndex == currentState->duration - 1) {
            func_80024214(obj);
            return;
        }

        if (currentState->cameraStateIndex >= 0 && currentState->cameraAnimIndex != -1) {
            player->cameraTask->func = func_800240C8;
            player->cameraTask->start_delay = 0;
            player->cameraTask->flags = TASK_FLAG_ENABLED;
        }

        if (currentState->unk_30 != -1) {
            func_80034C18(obj, player->unk_68 + currentState->unk_30 * obj->modInst->numNodes);
        } else {
            func_80034A58(obj);
        }

        player->currentStateDef = currentState;

        if (player->flags & PLAYER_FLAG_800) {
            obj->frameIndex = currentState->unk_02;
        } else {
            obj->frameIndex = MAX(currentState->duration, sp24[2]);
        }

        obj->modInst->currentAnimId = currentState->animationId;
        obj->modInst->previousAnimId = -1;
    }

    obj->currentTask->func = sp24[0]; // ????

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
    s32 *v0;

    if (obj->frameIndex < player->currentStateDef->unk_02) {
        obj->frameIndex++;
        return;
    }

    player->flags &= ~PLAYER_FLAG_TRANSITION_LOCKED;
    v0 = obj->currentTask->params;
    player->unk_08->func = v0[4];
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

    player->aiState.aiFlags &= ~0x20000;
}

void func_80024764(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    PlayerStateDef *temp;

    obj->currentTask->func = func_80024640;
    obj->frameIndex = 1;
    temp = obj->currentTask->params[3] + player->stateDefs; // required to match
    player->currentStateDef = temp;
    obj->modInst->currentAnimId = temp->animationId;
    player->flags |= PLAYER_FLAG_TRANSITION_LOCKED;
    player->aiState.aiFlags |= 0x20000;
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
    moveId = v0->params[0];
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
    s16 soundTableIndex = player->currentStateDef->soundTableIndex;
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
