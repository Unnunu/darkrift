#include "common.h"
#include "task.h"

enum AiStrategyFlags { AI_SF_DIFFICULTY_LOCKED = 1, AI_SF_DEFERRABLE = 2, AI_SF_BLOCK_LOW = 4 };

typedef struct {
    s16 index;
    AiTactic *entry;
} AiTacticChoice; // wrapping for candidate selection

u8 ai_peek_reaction_to_opponent(Player *, AiStrategy **);
u8 ai_step_move(Player *);
u8 ai_setup_action(Player *, AiState *);
s16 ai_step_move_wait(Player *);

s16 ai_step_approach(Player *);
s16 ai_step_retreat(Player *);
s16 ai_step_immediate(Player *);
s16 ai_step_timer(Player *);
s16 ai_step_anim_half(Player *);
s16 ai_step_stand_block_exit(Player *);
s16 ai_step_abort(Player *);
s16 ai_step_crouch_block_exit(Player *);
s16 ai_step_stand_impact(Player *);
s16 ai_step_crouch_impact(Player *);
s16 ai_step_lay_down(Player *);
s16 ai_step_run(Player *);
s16 ai_step_stand_block_try(Player *);
s16 ai_step_crouch_block_try(Player *);
s16 ai_step_block_release(Player *);
s16 ai_step_block_loop(Player *);

s16 D_80049D10[] = { 30, 20, 20, 10, 10, 10, 0, 0, 0, 0 };
s16 D_80049D24[] = { 30, 30, 10, 6, 5, 2, 2, 0 };
s16 D_80049D34[] = { 1, 2, 3, 4, 8, 10, 20, 1000 };
s16 D_80049D44[] = { 70, 60, 60, 55, 50, 45, 40, 40 };
s16 D_80049D54[] = { 8, 6, 4, 2, 0, 0, 0, 0 };
s16 D_80049D64[] = { 2, 2, 2, 1, 1, 1, 1, 1 };
s16 (*gAiStepFunctions[])(struct Player *) = {
    ai_step_approach,        ai_step_retreat,          ai_step_immediate,     ai_step_timer,
    ai_step_anim_half,       ai_step_stand_block_exit, ai_step_abort,         ai_step_crouch_block_exit,
    ai_step_stand_impact,    ai_step_crouch_impact,    ai_step_lay_down,      ai_step_run,
    ai_step_stand_block_try, ai_step_crouch_block_try, ai_step_block_release, ai_step_block_loop,
};
s16 D_80049DB4[] = { 13, 13, 13, 10, 19, 19, 10, 10, 19, 10, 10, 0 };
s16 D_80049DCC[] = { 10, 10, 10, 7, 12, 12, 10, 10, 12, 10, 10, 0, 0, 0, 0, 0, 0, 0 };

u8 ai_force_move(Player *player, s16 moveId) {
    ai_end_tactic(player);
    player->aiState.aiFlags |= AIF_ACTION_IN_PROGRESS;
    return player_apply_move(player, moveId, TRUE);
}

void ai_update(Player *player) {
    u8 hasStrategy;
    AiStrategy *strategy;
    AiState *aiState;
    u16 aiDifficulty;
    s16 cbResult;

    aiDifficulty = gBattleSettings[player->playerId].aiDifficulty;

    if (player->obj->playerHp == 0) {
        return;
    }

    if (!(player->combatState->flags & CSF_BLOCK)) {
        player->aiState.hitCount = 0;
    }

    if (player->aiState.aiFlags & AIF_ACTION_IN_PROGRESS) {
        aiState = &player->aiState;
        if (player->autoTransitionTimer != 0 && --player->autoTransitionTimer == 0) {
            ai_end_tactic(player);
            if (player->lookupLogicTable >= 0 && (player->flags & PLAYER_FLAG_1000)) {
                if (ai_select_transition(player)) {
                    player->aiState.aiFlags |= AIF_ACTION_IN_PROGRESS;
                }
            }
        } else if (aiState->continueActionFunc != NULL) {
            cbResult = aiState->continueActionFunc(player);
            if (cbResult > 0) {
                return;
            }

            aiState->continueActionFunc = NULL;
            player->aiState.aiFlags &= ~AIF_ACTION_IN_PROGRESS;
            if (cbResult < 0) {
                ai_end_tactic(player);
            } else {
                ai_advance_step(player);
            }
        } else if (player->autoTransitionTimer == 0 && player->obj->frameIndex >= player->combatState->maxFrame - 1) {
            player->autoTransitionTimer = 512;
        }
    } else if (!(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME) &&
               !(player->flags & PLAYER_FLAG_TRANSITION_LOCKED)) {
        if (player_check_func_2(player->obj) && !(player->combatState->flags & CSF_80) &&
            !(player->obj->flags & OBJ_FLAG_800000)) {
            if (player->combatState->flags & CSF_CROUCH) {
                ai_force_move(player, MOVE_ID_CROUCH_TURN_AR);
                return;
            }
            if (player->combatState->flags & CSF_STANDING) {
                ai_force_move(player, MOVE_ID_TURN_AROUND_NO);
                return;
            }
        }

        hasStrategy = ai_peek_reaction_to_opponent(player, &strategy);
        if ((player->obj->flags & OBJ_FLAG_800000) || (player->flags & PLAYER_FLAG_2000)) {
            return;
        }

        if ((--player->unk_DBE <= 0 || hasStrategy && !(strategy->flags & AI_SF_DEFERRABLE)) &&
                (player->combatState->flags & (CSF_CROUCH | CSF_STANDING)) ||
            player->transition->aiSelfStrategy != 0xFF) {
            player->unk_DBE = D_80049D10[aiDifficulty];
            player->unk_DBE += guRandom() & D_80049D24[aiDifficulty];

            if (!ai_decide(player, (player->flags & PLAYER_FLAG_200000) != 0)) {
                player->unk_DBE = 0;
            }
        }
    }
}

void ai_end_tactic(Player *player) {
    player->aiState.recentTactics[2] = player->aiState.recentTactics[1];
    player->aiState.recentTactics[1] = player->aiState.recentTactics[0];
    player->aiState.recentTactics[0] = NULL;

    player->aiState.continueActionFunc = NULL;
    player->aiState.tacticActionsPtr = player->aiState.moveSequence = NULL;
    player->aiState.aiFlags &= ~(AIF_4000 | AIF_ACTION_IN_PROGRESS | AIF_TERMINATE_TACTIC | AIF_AI_DISABLED);
    player->autoTransitionTimer = 0;

    if (player->flags & PLAYER_FLAG_2000) {
        player->aiState.aiFlags |= AIF_4000;
    }
}

u8 ai_advance_step(Player *player) {
    AiState *aiState = &player->aiState;

    if (player->flags & PLAYER_FLAG_2000 || (player->unk_DBC > 0x100 && !(aiState->tacticFlags & 0x1000)) ||
        player->transition->targetStateId != player->combatStateId) {
        ai_end_tactic(player);
        return FALSE;
    }

    if (ai_step_move(player)) {
        return TRUE;
    }

    if (aiState->tacticActionsPtr == NULL || *aiState->tacticActionsPtr == -1 ||
        (player->aiState.aiFlags & AIF_TERMINATE_TACTIC)) {
        ai_end_tactic(player);
        return FALSE;
    }

    aiState->tacticActionsPtr++;

    if (aiState->tacticActionsPtr == NULL || *aiState->tacticActionsPtr == -1) {
        ai_end_tactic(player);
        return FALSE;
    }

    ai_setup_action(player, aiState);
    return ai_step_move(player);
}

u8 ai_step_move(Player *player) {
    AiState *aiState = &player->aiState;
    s16 oppId = (player->playerId != PLAYER_1) ? PLAYER_1 : PLAYER_2;

    if (aiState->moveSequence != NULL && (s16) *aiState->moveSequence != -1) {
        if (player_apply_move(player, *aiState->moveSequence, TRUE)) {
            aiState->opponentHpAtAction = gPlayers[oppId].obj->playerHp;
            player->aiState.aiFlags |= AIF_ACTION_IN_PROGRESS;
            aiState->moveSequence++;
            return TRUE;
        }

        ai_end_tactic(player);
        return FALSE;
    }
    return FALSE;
}

#ifdef NON_MATCHING
u8 ai_setup_action(Player *player, AiState *aiState) {
    s32 combatStateFlags;
    s32 playerFlags;
    u8 a3;

    do {
        aiState++; // @fake
        aiState--; // @fake
        playerFlags = player->flags;
        combatStateFlags = player->combatState->flags;

        // read AiAction header
        aiState->moveSequence = player->aiActionTable + player->aiActionIndexMap[*aiState->tacticActionsPtr];
        aiState->continueActionFunc =
            ((s16) *aiState->moveSequence == -1) ? NULL : gAiStepFunctions[*aiState->moveSequence];
        aiState->moveSequence++;
        aiState->actionParam = *aiState->moveSequence++;
        aiState->actionFlags = *aiState->moveSequence++;

        a3 = (aiState->actionFlags & combatStateFlags & 0x400) &&
             !((aiState->actionFlags & 0x200) ^ (combatStateFlags & 0x200));
        if (a3 && (aiState->actionFlags & 8) &&
            ((aiState->actionFlags & 8) ^ (playerFlags & PLAYER_FLAG_NOT_FACING_OPP))) {
            a3 = FALSE;
        }

        if ((aiState->actionFlags & 0x1000) || a3 ||
            ((!(aiState->actionFlags & 0x4000)) || ((aiState->actionFlags & 0x4000) ^ (combatStateFlags & 0x4000))) &&
                !((aiState->actionFlags & 8) ^ (playerFlags & PLAYER_FLAG_NOT_FACING_OPP)) &&
                (aiState->actionFlags & combatStateFlags & 5)) {
            // selected action from sequence
            aiState->opponentHpAtAction = gPlayers[1 - player->playerId].obj->playerHp;
            player->aiState.aiFlags &= ~(AIF_4000 | AIF_ACTION_IN_PROGRESS | AIF_TERMINATE_TACTIC | AIF_AI_DISABLED);
            player->aiState.aiFlags |= AIF_ACTION_IN_PROGRESS;
            if (aiState->actionFlags & 0x8000) {
                player->aiState.aiFlags |= AIF_TERMINATE_TACTIC;
            }
            return TRUE;
        }

        aiState->tacticActionsPtr++;
    } while (*aiState->tacticActionsPtr >= 0);

    ai_end_tactic(player);
    return FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ai/ai_setup_action.s")
#endif

void ai_increase_difficulty(Player *player) {
    s16 numAiStrategies;
    s16 i;
    s16 difficulty;
    AiStrategy *strategy;

    numAiStrategies = player->numAiStrategies;

    gBattleSettings[player->playerId].aiDifficulty++;
    if (gBattleSettings[player->playerId].aiDifficulty > 7) {
        gBattleSettings[player->playerId].aiDifficulty = 7;
    }
    difficulty = gBattleSettings[player->playerId].aiDifficulty;

    for (i = 0; i < numAiStrategies; i++) {
        strategy = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[i]);
        strategy->difficulty = difficulty;
        strategy->unk_04 = strategy->unk_02;
    }

    ai_end_tactic(player);
    player->aiState.aiFlags = AIF_AI_DISABLED;
}

void ai_apply_difficulty(Player *player) {
    s16 numAiStrategies;
    s16 i;
    AiStrategy *strategy;
    s16 aiDifficulty;

    numAiStrategies = player->numAiStrategies;
    for (i = 0; i < numAiStrategies; i++) {
        strategy = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[i]);
        strategy->difficulty = 0;
        strategy->unk_04 = strategy->unk_02;
    }

    ai_end_tactic(player);

    aiDifficulty = gBattleSettings[player->playerId].aiDifficulty;
    if (aiDifficulty == 0x7FFF) {
        aiDifficulty = 0;
    }

    gBattleSettings[player->playerId].aiDifficulty = 0;
    for (i = 0; i < aiDifficulty; i++) {
        ai_increase_difficulty(player);
    }

    player->aiState.aiFlags = AIF_AI_DISABLED;
}

void ai_min_difficulty(Player *player) {
    s16 numAiStrategies;
    s16 i;
    AiStrategy *strategy;

    numAiStrategies = player->numAiStrategies;
    for (i = 0; i < numAiStrategies; i++) {
        strategy = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[i]);
        strategy->difficulty = 0;
        strategy->unk_04 = strategy->unk_02;
    }

    ai_end_tactic(player);
    gBattleSettings[player->playerId].aiDifficulty = 0;
    gBattleSettings[player->playerId].aiDifficulty = 0;
    player->aiState.aiFlags = AIF_AI_DISABLED;
}

void ai_max_difficulty(Player *player) {
    s16 numAiStrategies;
    s16 i;
    AiStrategy *strategy;
    s16 aiDifficulty;

    numAiStrategies = player->numAiStrategies;
    for (i = 0; i < numAiStrategies; i++) {
        strategy = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[i]);
        strategy->difficulty = 0;
        strategy->unk_04 = strategy->unk_02;
    }

    ai_end_tactic(player);

    gBattleSettings[player->playerId].aiDifficulty = 8;
    aiDifficulty = gBattleSettings[player->playerId].aiDifficulty;

    gBattleSettings[player->playerId].aiDifficulty = 0;
    for (i = 0; i < aiDifficulty; i++) {
        ai_increase_difficulty(player);
    }

    player->aiState.aiFlags = AIF_AI_DISABLED;
}

u8 ai_get_reaction_strategy(Player *player, AiStrategy **strategy, u8 useIdle) {
    s32 idleMove;
    s16 strategyId;
    AiStrategy *strat;
    Player *opponent;
    s16 idleFsmState;
    s16 idleTransitionId;

    opponent = gPlayers + 1 - player->playerId;

    if (useIdle) {
        idleMove =
            (gPlayers[1 - player->playerId].combatState->flags & CSF_CROUCH) ? MOVE_ID_CROUCH_IDLE : MOVE_ID_IDLE_068;
        idleFsmState = opponent->moveToLogicStateMap[idleMove];
        idleTransitionId = opponent->logicStateTable[idleFsmState];
        strategyId = opponent->transitionRuleTable[idleTransitionId].aiResponseForChar[player->characterId];
    } else {
        // get response to enemy state
        strategyId = gPlayers[1 - player->playerId].transition->aiResponseForChar[player->characterId];
        if (strategyId == 0xFF) {
            // enemy action doesn't imply reaction, so return nothing
            return FALSE;
        }
    }

    strat = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[strategyId]);
    if (!(strat->flags & AI_SF_DIFFICULTY_LOCKED)) {
        strategyId += strat->difficulty;
        strat = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[strategyId]);
    }
    *strategy = strat;
    return TRUE;
}

u8 ai_peek_reaction_to_opponent(Player *player, AiStrategy **strategy) {
    s16 strategyId;
    AiStrategy *strat;

    strategyId = gPlayers[1 - player->playerId].transition->aiResponseForChar[player->characterId];
    if (strategyId == 0xFF) {
        return FALSE;
    }

    strat = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[strategyId]);
    *strategy = strat;
    return TRUE;
}

u8 ai_get_self_strategy(Player *player, AiStrategy **strategy) {
    s16 strategyId;
    AiStrategy *strat;

    strategyId = gPlayers[player->playerId].transition->aiSelfStrategy;
    if (strategyId == 0xFF) {
        return FALSE;
    }

    strat = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[strategyId]);
    if (!(strat->flags & AI_SF_DIFFICULTY_LOCKED)) {
        strategyId += strat->difficulty;
        strat = (AiStrategy *) (player->aiStrategyTable + player->aiStrategyIndexMap[strategyId]);
    }

    *strategy = strat;
    return TRUE;
}

u8 ai_decide(Player *player, u8 arg1) {
    AiStrategy *strategy;
    s32 oppId;
    s16 numCandidates;
    AiState *aiState;
    s16 *candPtr;
    AiTacticChoice candidates[100];
    u8 isSelfTriggered;
    AiTactic *tactic;
    s32 pad;
    s16 actionSequenceIndex;
    u16 difficultyMask;
    s32 combatFlags;
    s32 playerFlags;
    s16 selectedTactic;

    oppId = (player->playerId != PLAYER_1) ? PLAYER_1 : PLAYER_2;

    if (!(player->flags & PLAYER_FLAG_2000) && (player->combatStateId == 216 || player->combatStateId == 42) &&
        ai_get_reaction_strategy(player, &strategy, TRUE)) {
        isSelfTriggered = FALSE;
    } else if (ai_get_self_strategy(player, &strategy)) {
        isSelfTriggered = TRUE;
    } else if (ai_get_reaction_strategy(player, &strategy, FALSE)) {
        isSelfTriggered = FALSE;
    } else {
        ai_end_tactic(player);
        return FALSE;
    }

    if (isSelfTriggered && (strategy->flags & AI_SF_DEFERRABLE) &&
        (gPlayers[oppId].combatState->flags & (CSF_200 | CSF_400)) && !gBattleSettings[oppId].isCpu &&
        !(gPlayers[oppId].flags & PLAYER_FLAG_10000)) {
        return FALSE;
    }

    if (!isSelfTriggered && arg1) {
        return FALSE;
    }

    if (isSelfTriggered & arg1) { // typo ??
        isSelfTriggered = FALSE;
    }

    numCandidates = 0;

    difficultyMask = 1 << gBattleSettings[player->playerId].aiDifficulty;
    combatFlags = player->combatState->flags;
    playerFlags = player->flags;

    do {
        candPtr = strategy->candidates;
        while (*candPtr != -1) {
            tactic = &player->aiCandidateTable[*candPtr & 0xFF];
            candPtr++;

            if (tactic->distanceMin <= gPlayerDistance + 200 && tactic->distanceMax >= gPlayerDistance - 200) {
                aiState = &player->aiState;
                if (tactic->difficultyMask & difficultyMask) {
                    if (tactic != aiState->recentTactics[1] && tactic != aiState->recentTactics[2] ||
                        !(tactic->conditionFlags & 0x800)) {
                        if ((tactic->conditionFlags & 0x1000) || ((tactic->conditionFlags & combatFlags) & 0x600) ||
                            (playerFlags & PLAYER_FLAG_NOT_FACING_OPP) == (tactic->conditionFlags & 8) &&
                                ((u8) (tactic->conditionFlags & combatFlags) & 5)) {
                            // clang-format off
                            candidates[numCandidates].index = candPtr[-1];\
                            candidates[numCandidates].entry = tactic;\
                            numCandidates++;
                            // clang-format on
                        }
                    }
                }
            }
        }

        if (numCandidates == 0) {
            if (!isSelfTriggered) {
                if (arg1) {
                    return FALSE;
                }

                player->aiState.recentTactics[0] = NULL;

                if (gPlayerDistance > 800 && !(player->aiState.aiFlags & AIF_MOVED_FORWARD)) {
                    if (gBattleSettings[player->playerId].aiDifficulty <= 3) {
                        player_apply_move(player, MOVE_ID_SHUFFLE_TOWARDS, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss fwd");
                        player->aiState.continueActionFunc = ai_step_move_wait;
                    } else {
                        player_apply_move(player, MOVE_ID_DASH, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default dash fwd");
                    }

                    player->aiState.aiFlags &= ~(AIF_MOVED_BACK | AIF_SIDE_STEPPED);
                    player->aiState.aiFlags |= AIF_MOVED_FORWARD;
                } else if (gPlayerDistance < 800 && !(player->aiState.aiFlags << 19)) { // ???
                    if (gBattleSettings[player->playerId].aiDifficulty <= 3) {
                        player_apply_move(player, MOVE_ID_SHUFFLE_BACK, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss bak");
                        player->aiState.continueActionFunc = ai_step_move_wait;
                    } else {
                        player_apply_move(player, MOVE_ID_DASH_BACK, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default dash bak");
                    }

                    player->aiState.aiFlags &= ~(AIF_MOVED_FORWARD | AIF_SIDE_STEPPED);
                    player->aiState.aiFlags |= AIF_MOVED_BACK;
                } else {
                    if (guRandom() & 1 & gFrameCounter) {
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss in");
                        if (!player_apply_move(player, MOVE_ID_AI_SIDE_STEP_IN, TRUE)) {
                            return FALSE;
                        }
                        player->aiState.continueActionFunc = NULL;
                    } else {
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss out");
                        if (!player_apply_move(player, MOVE_ID_AI_SIDE_STEP_OUT, TRUE)) {
                            return FALSE;
                        }
                        player->aiState.continueActionFunc = NULL;
                    }

                    player->aiState.aiFlags &= ~(AIF_MOVED_FORWARD | AIF_MOVED_BACK);
                    player->aiState.aiFlags |= AIF_SIDE_STEPPED;
                }

                player->aiState.moveSequence = NULL;
                player->aiState.aiFlags |= AIF_ACTION_IN_PROGRESS;
                return TRUE;
            }

            if (ai_get_reaction_strategy(player, &strategy, FALSE)) {
                isSelfTriggered = FALSE;
            } else {
                player->aiState.recentTactics[0] = NULL;
                return FALSE;
            }
        }
    } while (numCandidates == 0);

    aiState = &player->aiState;

    selectedTactic = guRandom() % numCandidates;
    aiState->recentTactics[0] = candidates[selectedTactic].entry;
    actionSequenceIndex = aiState->recentTactics[0]->actionSequence;
    aiState->tacticActionsPtr = player->aiActionSequenceTable + actionSequenceIndex;
    aiState->tacticFlags = aiState->recentTactics[0]->conditionFlags;
    aiState->currentStrategy = strategy;

    return ai_setup_action(player, aiState) && ai_step_move(player);
}

s16 ai_step_approach(Player *player) {
    AiStrategy *strategy;
    u8 hasStrategy;

    if (player->obj->frameIndex < (player->combatState->maxFrame >> 1)) {
        return TRUE;
    }

    hasStrategy = ai_peek_reaction_to_opponent(player, &strategy);
    return (gPlayerDistance > player->aiState.actionParam) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
           (!hasStrategy || (strategy->flags & AI_SF_DEFERRABLE));
}

s16 ai_step_run(Player *player) {
    AiStrategy *strategy;
    u8 hasStrategy;

    hasStrategy = ai_peek_reaction_to_opponent(player, &strategy);
    return (gPlayerDistance > player->aiState.actionParam) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
           (!hasStrategy || (strategy->flags & AI_SF_DEFERRABLE));
}

s16 ai_step_retreat(Player *player) {
    AiStrategy *strategy;
    u8 hasStrategy;

    hasStrategy = ai_peek_reaction_to_opponent(player, &strategy);

    if (player->obj->frameIndex < (player->combatState->maxFrame >> 1)) {
        return TRUE;
    }

    return (gPlayerDistance < player->aiState.actionParam) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
           (!hasStrategy || (strategy->flags & AI_SF_DEFERRABLE));
}

s16 ai_step_immediate(Player *player) {
    return 0;
}

s16 ai_step_timer(Player *player) {
    AiStrategy *strategy;
    u8 hasStrategy;

    hasStrategy = ai_peek_reaction_to_opponent(player, &strategy);

    if (player->aiState.actionParam) {
        player->aiState.actionParam--;
    }

    return (player->aiState.actionParam) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
           (!hasStrategy || (strategy->flags & AI_SF_DEFERRABLE));
}

s16 ai_step_anim_half(Player *player) {
    if (player->obj->frameIndex < (player->combatState->maxFrame >> 1)) {
        return TRUE;
    }

    return FALSE;
}

s16 ai_step_timer_abort(Player *player) {
    if (--player->aiState.actionParam > 0) {
        return TRUE;
    } else {
        return -1;
    }
}

s16 ai_step_abort(Player *player) {
    return -1;
}

s16 ai_step_stand_block_exit(Player *player) {
    AiStrategy *strategy;
    s16 oppId;
    s16 frameIndex;
    s16 hitboxActiveEnd;
    s16 hitboxActiveStart;
    Player *opponent;

    oppId = 1 - player->playerId;
    frameIndex = gPlayers[oppId].obj->frameIndex;
    hitboxActiveEnd = gPlayers[oppId].combatState->hitboxActiveEnd;
    hitboxActiveStart = gPlayers[oppId].combatState->hitboxActiveStart;

    if (player->flags & PLAYER_FLAG_2000) {
        return TRUE;
    }
    if (player->aiState.hitCount >= D_80049D34[gBattleSettings[player->playerId].aiDifficulty] &&
        !(gPlayers[1 - player->playerId].flags & PLAYER_FLAG_SHOOTED)) {
        return FALSE;
    }

    player->aiState.actionParam--;

    if (ai_peek_reaction_to_opponent(player, &strategy) && !(strategy->flags & AI_SF_DEFERRABLE)) {
        if (strategy->flags & AI_SF_BLOCK_LOW) {
            player_force_move(player, MOVE_ID_CROUCH_BLOCK_INTERRUPT, TRUE);
        }
        return TRUE;
    }

    opponent = gPlayers + oppId;
    if ((gPlayers[oppId].flags & PLAYER_FLAG_NOT_FACING_OPP) ||
        !(opponent->flags & PLAYER_FLAG_SHOOTED) && player->aiState.actionParam < 20 &&
            ((frameIndex < hitboxActiveStart && D_80049DB4[opponent->characterId] < hitboxActiveStart - frameIndex) ||
             (hitboxActiveEnd < frameIndex &&
              D_80049DCC[opponent->characterId] < gPlayers[oppId].combatState->maxFrame - hitboxActiveEnd) ||
             ((gPlayers[1 - player->playerId].flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
              gPlayers[1 - player->playerId].obj->frameIndex < 6))) {
        player->combatStateId = 216;
        return -1;
    }

    return player->aiState.actionParam > 0 || !(strategy->flags & AI_SF_DEFERRABLE);
}

s16 ai_step_crouch_block_exit(Player *player) {
    s16 oppId = 1 - player->playerId;
    s32 pad;
    AiStrategy *strategy;
    u8 v0;

    if (player->flags & PLAYER_FLAG_2000) {
        return TRUE;
    }

    if (player->aiState.hitCount >= D_80049D34[gBattleSettings[player->playerId].aiDifficulty] &&
        !(gPlayers[1 - player->playerId].flags & PLAYER_FLAG_SHOOTED)) {
        return FALSE;
    }

    player->aiState.actionParam--;
    v0 = ai_peek_reaction_to_opponent(player, &strategy);
    if (v0 && !(strategy->flags & AI_SF_DEFERRABLE)) {
        if (!(strategy->flags & AI_SF_BLOCK_LOW)) {
            player_force_move(player, MOVE_ID_CROUCH_BLOCK_2_STAND_BLOCK, TRUE);
        }
        return TRUE;
    }

    if (gPlayers[oppId].flags & PLAYER_FLAG_NOT_FACING_OPP) {
        player->combatStateId = 42;
        return -1;
    }

    return (player->aiState.actionParam > 0) || !(strategy->flags & AI_SF_DEFERRABLE);
}

u8 func_8001D1F8(Player *player) {
    switch (gDifficulty) {
        case DIFFICULTY_EASY:
            switch (gBattleSettings[player->playerId].aiDifficulty) {
                case 0:
                    return (guRandom() % 100) < 20;
                case 1:
                case 2:
                    return (guRandom() % 100) < 40;
                case 3:
                case 4:
                    return (guRandom() % 100) < 60;
                case 5:
                    return (guRandom() % 100) < 80;
                default:
                    return TRUE;
            }
            break;
        case DIFFICULTY_NORMAL:
        case DIFFICULTY_HARD:
            switch (gBattleSettings[player->playerId].aiDifficulty) {
                case 0:
                    return (guRandom() % 100) < 20;
                case 1:
                    return (guRandom() % 100) < 40;
                case 2:
                case 3:
                    return (guRandom() % 100) < 80;
                default:
                    return TRUE;
            }
            break;
    }

    return TRUE;
}

s16 ai_step_counter_def_stand(Player *player) {
    AiStrategy *strategy;
    s32 pad[2];
    u8 v0;
    s16 playerId = player->playerId;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[playerId].aiDifficulty]) {
        v0 = ai_peek_reaction_to_opponent(player, &strategy);
        if (v0 && !(strategy->flags & AI_SF_DEFERRABLE) && !(strategy->flags & AI_SF_BLOCK_LOW)) {
            player_force_move(player, MOVE_ID_CROUCH_BLOCK_2_STAND_BLOCK, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 ai_step_counter_agg_stand(Player *player) {
    AiStrategy *strategy;
    s16 oppId;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    Player *opponent;

    oppId = 1 - player->playerId;
    sp30 = gPlayers[oppId].obj->frameIndex;
    sp2E = gPlayers[oppId].combatState->hitboxActiveEnd;
    sp2C = gPlayers[oppId].combatState->hitboxActiveStart;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[player->playerId].aiDifficulty]) {
        if (ai_peek_reaction_to_opponent(player, &strategy)) {
            if (!(strategy->flags & AI_SF_DEFERRABLE) && !(strategy->flags & AI_SF_BLOCK_LOW)) {
                player_force_move(player, MOVE_ID_CROUCH_BLOCK_2_STAND_BLOCK, TRUE);
                return 1;
            }
        }
    }

    opponent = gPlayers + oppId;
    if (!(opponent->flags & PLAYER_FLAG_SHOOTED)) {
        if ((sp30 < sp2C && D_80049DB4[opponent->characterId] < sp2C - sp30) ||
            (sp2E < sp30 && D_80049DCC[opponent->characterId] < gPlayers[oppId].combatState->maxFrame - sp2E) ||
            ((gPlayers[1 - player->playerId].flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
             gPlayers[1 - player->playerId].obj->frameIndex < 6)) {
            player->flags &= ~PLAYER_FLAG_2000;
            return -1;
        }
    }

    return 1;
}

s16 ai_step_crouch_impact(Player *player) {
    player->aiState.delayCount = 0;
    player->aiState.hitCount++;

    if (func_8001D1F8(player)) {
        player->aiState.continueActionFunc = ai_step_counter_agg_stand;
        return ai_step_counter_agg_stand(player);
    } else {
        player->aiState.continueActionFunc = ai_step_counter_def_stand;
        return ai_step_counter_def_stand(player);
    }
}

s16 ai_step_counter_def_crouch(Player *player) {
    s32 pad[2];
    AiStrategy *strategy;
    u8 v0;
    s16 playerId = player->playerId;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[playerId].aiDifficulty]) {
        v0 = ai_peek_reaction_to_opponent(player, &strategy);
        if (v0 && !(strategy->flags & AI_SF_DEFERRABLE) && (strategy->flags & AI_SF_BLOCK_LOW)) {
            player_force_move(player, MOVE_ID_CROUCH_BLOCK_INTERRUPT, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 ai_step_counter_agg_crouch(Player *player) {
    s16 oppId;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    AiStrategy *strategy;
    Player *opponent;

    oppId = 1 - player->playerId;
    sp30 = gPlayers[oppId].obj->frameIndex;
    sp2E = gPlayers[oppId].combatState->hitboxActiveEnd;
    sp2C = gPlayers[oppId].combatState->hitboxActiveStart;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[player->playerId].aiDifficulty]) {
        if (ai_peek_reaction_to_opponent(player, &strategy)) {
            if (!(strategy->flags & AI_SF_DEFERRABLE) && (strategy->flags & AI_SF_BLOCK_LOW)) {
                player_force_move(player, MOVE_ID_CROUCH_BLOCK_INTERRUPT, TRUE);
                return 1;
            }
        }
    }

    opponent = gPlayers + oppId;
    if (!(opponent->flags & PLAYER_FLAG_SHOOTED) && func_8001D1F8(player)) {
        if ((sp30 < sp2C && D_80049DB4[opponent->characterId] < sp2C - sp30) ||
            (sp2E < sp30 && D_80049DCC[opponent->characterId] < gPlayers[oppId].combatState->maxFrame - sp2E) ||
            ((gPlayers[1 - player->playerId].flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
             gPlayers[1 - player->playerId].obj->frameIndex < 6)) {
            player->flags &= ~PLAYER_FLAG_2000;
            return -1;
        }
    }

    return 1;
}

s16 ai_step_stand_impact(Player *player) {
    player->aiState.delayCount = 0;
    player->aiState.hitCount++;

    if (func_8001D1F8(player)) {
        player->aiState.continueActionFunc = ai_step_counter_agg_crouch;
        return ai_step_counter_agg_crouch(player);
    } else {
        player->aiState.continueActionFunc = ai_step_counter_def_crouch;
        return ai_step_counter_def_crouch(player);
    }
}

s16 ai_step_lay_down(Player *player) {
    s16 sp1E;

    sp1E = gBattleSettings[player->playerId].aiDifficulty;
    player->aiState.actionParam = D_80049D44[sp1E] + (guRandom() & D_80049D24[sp1E]); // @BUG ??
    player->aiState.continueActionFunc = ai_step_timer_abort;
    return 1;
}

s16 ai_step_move_wait(Player *player) {
    AiStrategy *strategy;
    s32 hasStrategy;

    hasStrategy = ai_peek_reaction_to_opponent(player, &strategy);

    if (player->obj->frameIndex < (player->combatState->maxFrame >> 1) &&
        !(player->flags & PLAYER_FLAG_NOT_FACING_OPP)) {
        return TRUE;
    }

    if (player->obj->frameIndex < player->combatState->maxFrame - 1 && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
        (!hasStrategy || (strategy->flags & AI_SF_DEFERRABLE))) {
        return TRUE;
    }

    return FALSE;
}

s16 ai_step_stand_block_try(Player *player) {
    s16 sp24;
    s32 pad;
    s16 pad2;
    s16 sp2C;

    sp24 = gBattleSettings[player->playerId].aiDifficulty;
    sp2C = D_80049D54[sp24];
    sp2C += guRandom() % D_80049D64[sp24];
    player->aiState.delayCount++;

    if (sp2C < player->aiState.delayCount || (gPlayers[1 - player->playerId].flags & PLAYER_FLAG_100000)) {
        player->aiState.tacticActionsPtr++;
        ai_setup_action(player, &player->aiState);
        ai_step_move(player);
        player->aiState.actionParam = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 ai_step_crouch_block_try(Player *player) {
    s16 aiDifficulty;
    s32 pad;
    s16 pad2;
    s16 sp2C;

    aiDifficulty = gBattleSettings[player->playerId].aiDifficulty;
    sp2C = D_80049D54[aiDifficulty];
    sp2C += guRandom() % D_80049D64[aiDifficulty];
    player->aiState.delayCount++;

    if (sp2C < player->aiState.delayCount || (gPlayers[1 - player->playerId].flags & PLAYER_FLAG_100000)) {
        player->aiState.tacticActionsPtr++;
        ai_setup_action(player, &player->aiState);
        ai_step_move(player);
        player->aiState.actionParam = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 ai_step_block_release(Player *player) {
    AiStrategy *strategy;

    if (ai_peek_reaction_to_opponent(player, &strategy)) {
        if (!(strategy->flags & AI_SF_DEFERRABLE)) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}

s16 ai_step_block_loop(Player *player) {
    player->aiState.continueActionFunc = NULL;
    player->aiState.tacticActionsPtr -= 2;
    return 1;
}
