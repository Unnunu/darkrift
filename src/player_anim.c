#include "common.h"
#include "camera.h"
#include "task.h"

u8 ai_select_transition(Player *);

void anim_pingpong_forward(Object *);

void action_animation_end(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    s32 stateFlags;

    if (gBattleSettings[playerId].isCpu && !gRoundOver) {
        if (ai_advance_step(player) || ai_decide(player, TRUE)) {
            return;
        }

        ai_end_tactic(player);

        if (player->lookupLogicTable >= 0 && (player->flags & PLAYER_FLAG_1000)) {
            if (ai_select_transition(player)) {
                player->aiState.aiFlags |= AIF_ACTION_IN_PROGRESS;
                return;
            }
        }
    } else if (!(player->flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
               (gPlayerInput[playerId].pendingInput || (player->flags & PLAYER_FLAG_1000)) &&
               player->lookupLogicTable >= 0 && !(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME)) {
        if (player_select_transition(player, TRUE)) {
            return;
        }
    }

    D_80080236 = TRUE;
    stateFlags = player->combatState->flags;
    if (player->flags & PLAYER_FLAG_8000000) {
        player->flags &= ~PLAYER_FLAG_8000000;
        stateFlags ^= CSF_CROUCH | CSF_STANDING;
    }

    if (stateFlags & CSF_CROUCH) {
        player_apply_move(player, MOVE_ID_CROUCH_IDLE, FALSE);
    } else {
        player_apply_move(player, MOVE_ID_IDLE_068, FALSE);
    }

    D_80080236 = FALSE;
    player->flags |= PLAYER_FLAG_TRANSITION_LOCKED;
}

void anim_reverse(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex > player->combatState->minFrame + 1) {
        obj->frameIndex--;
    } else {
        obj->frameIndex--;
        action_animation_end(obj);
    }
}

void anim_pingpong_backward(Object *obj) {
    if (obj->frameIndex != 0) {
        obj->frameIndex--;
    } else {
        obj->frameIndex++;
        obj->currentTask->func = anim_pingpong_forward;
    }
}

void anim_pingpong_forward(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames - 1) {
        obj->frameIndex++;
    } else {
        obj->frameIndex--;
        obj->currentTask->func = anim_pingpong_backward;
    }
}

void anim_play_once(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames - 1) {
        obj->frameIndex++;
    } else {
        TASK_END(obj->currentTask);
    }
}

void anim_loop(Object *obj) {
    Player *player;
    s16 characterId;

    if (obj->frameIndex < ((Player *) obj->varObj[0])->combatState->maxFrame) {
        obj->frameIndex++;
        return;
    } else {
        obj->frameIndex = 0;
        player = (Player *) obj->varObj[0];
        characterId = player->characterId;

        if (obj->modInst->velocity.z != 0) {
            if (player->combatState->flags & CSF_STANDING) {
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

void anim_advance(Object *obj) {
    if (obj->frameIndex < ((Player *) obj->varObj[0])->combatState->maxFrame - 1) {
        obj->frameIndex++;
    } else {
        obj->frameIndex++;
        action_animation_end(obj);
    }
}

void player_anim_func_3_sub(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Vec4i sp2C;

    if (player->combatState->cutsceneId < 0) {
        TASK_END(obj->currentTask);
    } else if (obj->frameIndex >= player->combatState->custsceneDelay) {
        camera_save_state();

        sp2C.x = (gPlayers[PLAYER_1].obj->pos.x + gPlayers[PLAYER_2].obj->pos.x) >> 1;
        sp2C.z = (gPlayers[PLAYER_1].obj->pos.z + gPlayers[PLAYER_2].obj->pos.z) >> 1;
        sp2C.y = 0;
        func_80038E8C(gCamera, &sp2C, obj->rotation.y,
                      obj->modInst->animations[player->combatStateTable[player->combatState->cutsceneId].animationId]);

        gCamera->currentTask->func = camera_cutscene_playback;
        gCamera->currentTask->start_delay = 0;
        gCamera->currentTask->flags = TASK_FLAG_ENABLED;
        gCamera->currentTask->start_delay = 1;
        TASK_END(obj->currentTask);
    }
}

void player_anim_func_3(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 unused[2];
    CombatState *targetState;

    targetState = player->combatStateTable + player->combatStateId;
    player->combatState = targetState;

    if (targetState->cutsceneId >= 0 && targetState->custsceneDelay != -1) {
        player->cameraTask->func = player_anim_func_3_sub;
        player->cameraTask->start_delay = 0;
        player->cameraTask->flags = TASK_FLAG_ENABLED;
    }

    if (targetState->unk_30 != -1) {
        func_80034C18(obj, player->unk_68 + targetState->unk_30 * obj->modInst->numNodes);
    } else {
        func_80034A58(obj);
    }

    obj->currentTask->func = anim_advance;
    obj->frameIndex++;

    if (targetState->flags & CSF_ROOT_MOTION) {
        obj->flags |= OBJ_FLAG_ROOT_MOTION;
        if (targetState->flags & CSF_8000) {
            obj->flags |= OBJ_FLAG_20000;
        }
    } else {
        obj->flags &= ~OBJ_FLAG_ROOT_MOTION;
    }

    if (targetState->flags & CSF_80) {
        obj->flags |= OBJ_FLAG_800000;
    }

    if (targetState->flags & CSF_200000) {
        obj->flags |= OBJ_FLAG_100000;
    }
}

void anim_change_combat_state(Object *obj) {
    s32 *params;
    Player *player = (Player *) obj->varObj[0];
    CombatState *targetState;

    targetState = player->combatState;
    params = obj->currentTask->params;

    if (player->combatStateId >= 0) {
        targetState = player->combatStateTable + player->combatStateId;

        if (targetState->animationId == obj->modInst->currentAnimId && obj->frameIndex + 1 < targetState->minFrame) {
            obj->frameIndex++;
            player->animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
            player->animTask->triggerAt = targetState->minFrame - 2;
            player->animTask->triggerSlot.flags = TASK_FLAG_ENABLED;
            player->animTask->triggerSlot.func = player_anim_func_3;
            obj->currentTask->func = anim_advance;
            return;
        }

        if (targetState->animationId == obj->modInst->currentAnimId && obj->frameIndex == targetState->minFrame - 1) {
            player_anim_func_3(obj);
            return;
        }

        if (targetState->cutsceneId >= 0 && targetState->custsceneDelay != -1) {
            player->cameraTask->func = player_anim_func_3_sub;
            player->cameraTask->start_delay = 0;
            player->cameraTask->flags = TASK_FLAG_ENABLED;
        }

        if (targetState->unk_30 != -1) {
            func_80034C18(obj, player->unk_68 + targetState->unk_30 * obj->modInst->numNodes);
        } else {
            func_80034A58(obj);
        }

        player->combatState = targetState;

        if (player->flags & PLAYER_FLAG_800) {
            obj->frameIndex = targetState->maxFrame;
        } else {
            obj->frameIndex = MAX(targetState->minFrame, params[2]);
        }

        obj->modInst->currentAnimId = targetState->animationId;
        // trigger animation change code in model_update
        obj->modInst->previousAnimId = -1;
    }

    obj->currentTask->func = params[0];

    if (targetState->flags & CSF_ROOT_MOTION) {
        obj->flags |= OBJ_FLAG_ROOT_MOTION;
        if (targetState->flags & CSF_8000) {
            obj->flags |= OBJ_FLAG_20000;
        } else {
            obj->flags &= ~OBJ_FLAG_20000;
        }
    } else {
        obj->flags &= ~OBJ_FLAG_ROOT_MOTION;
    }

    if (targetState->flags & CSF_80) {
        obj->flags |= OBJ_FLAG_400000;
    }

    if (targetState->flags & CSF_200000) {
        obj->flags |= OBJ_FLAG_100000;
    }
}

void func_80024640(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 i;
    s32 s2;
    s32 *v0;

    if (obj->frameIndex < player->combatState->maxFrame) {
        obj->frameIndex++;
        return;
    }

    player->flags &= ~PLAYER_FLAG_TRANSITION_LOCKED;
    v0 = obj->currentTask->params;
    player->actionTask->func = v0[4];
    player->actionTask->start_delay = 0;
    player->actionTask->flags = TASK_FLAG_ENABLED;
    anim_change_combat_state(obj);

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

    player->aiState.aiFlags &= ~AIF_AI_DISABLED;
}

void func_80024764(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    CombatState *temp;

    obj->currentTask->func = func_80024640;
    obj->frameIndex = 1;
    temp = obj->currentTask->params[3] + player->combatStateTable; // required to match
    player->combatState = temp;
    obj->modInst->currentAnimId = temp->animationId;
    player->flags |= PLAYER_FLAG_TRANSITION_LOCKED;
    player->aiState.aiFlags |= AIF_AI_DISABLED;
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
    transitionTable = player->logicStateTable;
    currentTask = obj->currentTask;
    obj->frameIndex++;

    if (player_make_transition(player, TRUE, moveId)) {
        player->lookupLogicTable = transitionTable[moveId + 1];
        player->allowTransition = FALSE;
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
    s16 soundTableIndex = player->combatState->soundTableIndex;
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
