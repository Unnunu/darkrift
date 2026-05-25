#include "common.h"
#include "task.h"

typedef struct AiCandidate {
    /* 0x00 */ s16 index;
    /* 0x04 */ AiAction *entry;
} AiCandidate; // size = 0x8

u8 ai_get_opponent_response(Player *, s16 **);
u8 ai_execute_action(Player *);
u8 ai_parse_action(Player *, AiState *);
s16 func_8001DA90(Player *);

s16 ai_cond_approach(Player *);
s16 func_8001CC8C(Player *);
s16 func_8001CD28(Player *);
s16 func_8001CD34(Player *);
s16 func_8001CDAC(Player *);
s16 func_8001CE18(Player *);
s16 func_8001CE0C(Player *);
s16 func_8001D070(Player *);
s16 func_8001D9B0(Player *);
s16 func_8001D660(Player *);
s16 func_8001DA10(Player *);
s16 func_8001CC18(Player *);
s16 func_8001DB2C(Player *);
s16 func_8001DC68(Player *);
s16 func_8001DDA4(Player *);
s16 func_8001DDEC(Player *);

s16 D_80049D10[] = { 30, 20, 20, 10, 10, 10, 0, 0, 0, 0 };
s16 D_80049D24[] = { 30, 30, 10, 6, 5, 2, 2, 0 };
s16 D_80049D34[] = { 1, 2, 3, 4, 8, 10, 20, 1000 };
s16 D_80049D44[] = { 70, 60, 60, 55, 50, 45, 40, 40 };
s16 D_80049D54[] = { 8, 6, 4, 2, 0, 0, 0, 0 };
s16 D_80049D64[] = { 2, 2, 2, 1, 1, 1, 1, 1 };
s16 (*D_80049D74[])(struct Player *) = {
    ai_cond_approach, func_8001CC8C, func_8001CD28, func_8001CD34, func_8001CDAC, func_8001CE18,
    func_8001CE0C,    func_8001D070, func_8001D9B0, func_8001D660, func_8001DA10, func_8001CC18,
    func_8001DB2C,    func_8001DC68, func_8001DDA4, func_8001DDEC,
};
s16 D_80049DB4[] = { 13, 13, 13, 10, 19, 19, 10, 10, 19, 10, 10, 0 };
s16 D_80049DCC[] = { 10, 10, 10, 7, 12, 12, 10, 10, 12, 10, 10, 0, 0, 0, 0, 0, 0, 0 };

u8 ai_force_transition(Player *player, s16 arg1) {
    ai_reset(player);
    player->aiState.aiFlags |= 0x8000;
    return player_apply_move(player, arg1, 1);
}

void ai_update(Player *player) {
    u8 v04;
    s16 *sp30;
    AiState *v1;
    u16 sp2A;
    s16 v02;

    sp2A = gBattleSettings[player->playerId].unk_04;
    if (player->obj->playerHp == 0) {
        return;
    }

    if (!(player->currentStateDef->flags & STATE_FLAG_4000)) {
        player->aiState.hitCount = 0;
    }

    if (player->aiState.aiFlags & 0x8000) {
        v1 = &player->aiState;
        if (player->autoTransitionTimer != 0 && --player->autoTransitionTimer == 0) {
            ai_reset(player);
            if (player->nextLogicState >= 0 && (player->flags & PLAYER_FLAG_1000)) {
                if (ai_select_transition(player)) {
                    player->aiState.aiFlags |= 0x8000;
                }
            }
        } else if (v1->stateCallback != NULL) {
            v02 = v1->stateCallback(player);
            if (v02 > 0) {
                return;
            }

            v1->stateCallback = NULL;
            player->aiState.aiFlags &= ~0x8000;
            if (v02 < 0) {
                ai_reset(player);
            } else {
                ai_advance_sequence(player);
            }
        } else if (player->autoTransitionTimer == 0 && player->obj->frameIndex >= player->currentStateDef->unk_02 - 1) {
            player->autoTransitionTimer = 512;
        }
    } else if (!(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME) &&
               !(player->flags & PLAYER_FLAG_TRANSITION_LOCKED)) {
        if (func_80030BB0(player->obj) && !(player->currentStateDef->flags & STATE_FLAG_80) &&
            !(player->obj->flags & OBJ_FLAG_800000)) {
            if (player->currentStateDef->flags & STATE_FLAG_1) {
                ai_force_transition(player, 0x62);
                return;
            }
            if (player->currentStateDef->flags & STATE_FLAG_4) {
                ai_force_transition(player, 0x5F);
                return;
            }
        }

        v04 = ai_get_opponent_response(player, &sp30);
        if ((player->obj->flags & OBJ_FLAG_800000) || (player->flags & PLAYER_FLAG_2000)) {
            return;
        }

        if ((--player->unk_DBE <= 0 || v04 && !(*sp30 & 2)) &&
                (player->currentStateDef->flags & (STATE_FLAG_1 | STATE_FLAG_4)) ||
            player->currentTransition->unk_19 != 0xFF) {
            player->unk_DBE = D_80049D10[sp2A];
            player->unk_DBE += guRandom() & D_80049D24[sp2A];

            if (!ai_decide(player, (player->flags & PLAYER_FLAG_200000) != 0)) {
                player->unk_DBE = 0;
            }
        }
    }
}

void ai_reset(Player *player) {
    player->aiState.recentActions[2] = player->aiState.recentActions[1];
    player->aiState.recentActions[1] = player->aiState.recentActions[0];
    player->aiState.recentActions[0] = NULL;

    player->aiState.stateCallback = NULL;
    player->aiState.sequencePtr = player->aiState.actionPtr = NULL;
    player->aiState.aiFlags &= ~0x3C000;
    player->autoTransitionTimer = 0;

    if (player->flags & PLAYER_FLAG_2000) {
        player->aiState.aiFlags |= 0x4000;
    }
}

u8 ai_advance_sequence(Player *player) {
    AiState *subH = &player->aiState;

    if (player->flags & PLAYER_FLAG_2000 || (player->unk_DBC > 0x100 && !(subH->actionFlags & 0x1000)) ||
        player->currentTransition->targetStateId != player->currentStateId) {
        ai_reset(player);
        return FALSE;
    }

    if (ai_execute_action(player)) {
        return TRUE;
    }

    if (subH->sequencePtr == NULL || *subH->sequencePtr == -1 || (player->aiState.aiFlags & 0x10000)) {
        ai_reset(player);
        return FALSE;
    }

    subH->sequencePtr++;

    if (subH->sequencePtr == NULL || *subH->sequencePtr == -1) {
        ai_reset(player);
        return FALSE;
    }

    ai_parse_action(player, subH);
    return ai_execute_action(player);
}

u8 ai_execute_action(Player *player) {
    AiState *subH = &player->aiState;
    s16 oppId = (player->playerId != PLAYER_1) ? PLAYER_1 : PLAYER_2;

    if (subH->actionPtr != NULL && (s16) *subH->actionPtr != -1) {
        if (player_apply_move(player, *subH->actionPtr, 1)) {
            subH->opponentHpAtAction = gPlayers[oppId].obj->playerHp;
            player->aiState.aiFlags |= 0x8000;
            subH->actionPtr++;
            return TRUE;
        }

        ai_reset(player);
        return FALSE;
    }
    return FALSE;
}

#ifdef NON_MATCHING
u8 ai_parse_action(Player *player, AiState *subH) {
    s32 a2;
    s32 pf;
    u8 a3;

    do {
        subH++; // @fake
        subH--; // @fake
        pf = player->flags;
        a2 = player->currentStateDef->flags;

        subH->actionPtr = player->aiActionTable + player->aiActionIndexMap[*subH->sequencePtr];
        subH->stateCallback = ((s16) *subH->actionPtr == -1) ? NULL : D_80049D74[*subH->actionPtr];
        subH->actionPtr++;
        subH->actionParam = *subH->actionPtr++;
        subH->conditionFlags = *subH->actionPtr++;

        a3 = (subH->conditionFlags & a2 & 0x400) && !((subH->conditionFlags & 0x200) ^ (a2 & 0x200));
        if (a3 && (subH->conditionFlags & 8) && ((subH->conditionFlags & 8) ^ (pf & PLAYER_FLAG_NOT_FACING_OPP))) {
            a3 = FALSE;
        }

        if ((subH->conditionFlags & 0x1000) || a3 ||
            ((!(subH->conditionFlags & 0x4000)) || ((subH->conditionFlags & 0x4000) ^ (a2 & 0x4000))) &&
                !((subH->conditionFlags & 8) ^ (pf & PLAYER_FLAG_NOT_FACING_OPP)) && (subH->conditionFlags & a2 & 5)) {
            subH->opponentHpAtAction = gPlayers[1 - player->playerId].obj->playerHp;
            player->aiState.aiFlags &= ~0x3C000;
            player->aiState.aiFlags |= 0x8000;
            if (subH->conditionFlags & 0x8000) {
                player->aiState.aiFlags |= 0x10000;
            }
            return TRUE;
        }

        subH->sequencePtr++;
    } while (*subH->sequencePtr >= 0);

    ai_reset(player);
    return FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ai/ai_parse_action.s")
#endif

void ai_increase_difficulty(Player *player) {
    s16 a1;
    s16 i;
    s16 a3;
    s16 *ptr;

    a1 = player->unk_DBA;

    gBattleSettings[player->playerId].unk_04++;
    if (gBattleSettings[player->playerId].unk_04 > 7) {
        gBattleSettings[player->playerId].unk_04 = 7;
    }
    a3 = gBattleSettings[player->playerId].unk_04;

    for (i = 0; i < a1; i++) {
        ptr = player->aiResponseTable + player->aiResponseIndexMap[i];
        ptr[3] = a3;
        ptr[2] = ptr[1];
    }

    ai_reset(player);
    player->aiState.aiFlags = 0x20000;
}

void ai_reset_diffculty(Player *player) {
    s16 a1;
    s16 i;
    s16 *ptr;
    s16 a3;

    a1 = player->unk_DBA;
    for (i = 0; i < a1; i++) {
        ptr = player->aiResponseTable + player->aiResponseIndexMap[i];
        ptr[3] = 0;
        ptr[2] = ptr[1];
    }

    ai_reset(player);

    a3 = gBattleSettings[player->playerId].unk_04;
    if (a3 == 0x7FFF) {
        a3 = 0;
    }
    gBattleSettings[player->playerId].unk_04 = 0;

    for (i = 0; i < a3; i++) {
        ai_increase_difficulty(player);
    }

    player->aiState.aiFlags = 0x20000;
}

void ai_reset_difficulty_hard(Player *player) {
    s16 a1;
    s16 i;
    s16 *ptr;

    a1 = player->unk_DBA;
    for (i = 0; i < a1; i++) {
        ptr = player->aiResponseTable + player->aiResponseIndexMap[i];
        ptr[3] = 0;
        ptr[2] = ptr[1];
    }

    ai_reset(player);
    gBattleSettings[player->playerId].unk_04 = 0;
    gBattleSettings[player->playerId].unk_04 = 0;
    player->aiState.aiFlags = 0x20000;
}

void ai_set_temp_max_difficulty(Player *player) {
    s16 a1;
    s16 i;
    s16 *ptr;
    s16 a3;

    a1 = player->unk_DBA;
    for (i = 0; i < a1; i++) {
        ptr = player->aiResponseTable + player->aiResponseIndexMap[i];
        ptr[3] = 0;
        ptr[2] = ptr[1];
    }

    ai_reset(player);

    gBattleSettings[player->playerId].unk_04 = 8;
    a3 = gBattleSettings[player->playerId].unk_04;
    gBattleSettings[player->playerId].unk_04 = 0;

    for (i = 0; i < a3; i++) {
        ai_increase_difficulty(player);
    }

    player->aiState.aiFlags = 0x20000;
}

u8 ai_get_transition_rule(Player *player, s16 **arg1, u8 arg2) {
    s32 v1;
    s16 a3;
    s16 *ptr;
    Player *opp;
    s16 a1;
    s16 a2;

    opp = gPlayers + 1 - player->playerId;

    if (arg2) {
        v1 = (gPlayers[1 - player->playerId].currentStateDef->flags & STATE_FLAG_1) ? 320 : 68;
        a1 = opp->moveToLogicStateMap[v1];
        a2 = opp->logicStates[a1];
        a3 = opp->transitionRules[a2].unk_0E[player->characterId];
    } else {
        a3 = gPlayers[1 - player->playerId].currentTransition->unk_0E[player->characterId];
        if (a3 == 0xFF) {
            return FALSE;
        }
    }

    ptr = player->aiResponseTable + player->aiResponseIndexMap[a3];
    if (!(ptr[0] & 1)) {
        a3 += ptr[3];
        ptr = player->aiResponseTable + player->aiResponseIndexMap[a3];
    }
    *arg1 = ptr;
    return TRUE;
}

u8 ai_get_opponent_response(Player *player, s16 **arg1) {
    s16 a3;
    s16 *ptr;

    a3 = gPlayers[1 - player->playerId].currentTransition->unk_0E[player->characterId];
    if (a3 == 0xFF) {
        return FALSE;
    }

    ptr = player->aiResponseTable + player->aiResponseIndexMap[a3];
    *arg1 = ptr;
    return TRUE;
}

u8 ai_get_self_response(Player *player, s16 **arg1) {
    s16 a3;
    s16 *ptr;

    a3 = gPlayers[player->playerId].currentTransition->unk_19;
    if (a3 == 0xFF) {
        return FALSE;
    }

    ptr = player->aiResponseTable + player->aiResponseIndexMap[a3];
    if (!(ptr[0] & 1)) {
        a3 += ptr[3];
        ptr = player->aiResponseTable + player->aiResponseIndexMap[a3];
    }

    *arg1 = ptr;
    return TRUE;
}

u8 ai_decide(Player *player, u8 arg1) {
    s16 *sp38C;
    s32 s0;
    s16 a3;
    AiState *subH;
    s16 *ptr;
    AiCandidate sp5C[100];
    u8 s2;
    AiAction *v1;
    s32 pad;
    s16 pad2;
    u16 sp4C;
    s32 sp48;
    s32 sp44;
    s16 v2;

    s0 = (player->playerId != PLAYER_1) ? PLAYER_1 : PLAYER_2;

    if (!(player->flags & PLAYER_FLAG_2000) && (player->currentStateId == 216 || player->currentStateId == 42) &&
        ai_get_transition_rule(player, &sp38C, TRUE)) {
        s2 = FALSE;
    } else if (ai_get_self_response(player, &sp38C)) {
        s2 = TRUE;
    } else if (ai_get_transition_rule(player, &sp38C, FALSE)) {
        s2 = FALSE;
    } else {
        ai_reset(player);
        return FALSE;
    }

    if (s2 && (*sp38C & 2) && (gPlayers[s0].currentStateDef->flags & (STATE_FLAG_200 | STATE_FLAG_400)) &&
        !gBattleSettings[s0].isCpu && !(gPlayers[s0].flags & PLAYER_FLAG_10000)) {
        return FALSE;
    }

    if (!s2 && arg1) {
        return FALSE;
    }

    if (s2 & arg1) { // typo ??
        s2 = FALSE;
    }

    a3 = 0;

    sp4C = 1 << gBattleSettings[player->playerId].unk_04;
    sp48 = player->currentStateDef->flags;
    sp44 = player->flags;

    do {
        ptr = sp38C + 4;
        while (*ptr != -1) {
            v1 = &player->aiCandidateTable[*ptr & 0xFF];
            ptr++;

            if (v1->distanceMax <= gPlayerDistance + 200 && v1->distanceMin >= gPlayerDistance - 200) {
                subH = &player->aiState;
                if (v1->difficultyMask & sp4C) {
                    if (v1 != subH->recentActions[1] && v1 != subH->recentActions[2] || !(v1->conditionFlags & 0x800)) {
                        if ((v1->conditionFlags & 0x1000) || ((v1->conditionFlags & sp48) & 0x600) ||
                            (sp44 & PLAYER_FLAG_NOT_FACING_OPP) == (v1->conditionFlags & 8) &&
                                ((u8) (v1->conditionFlags & sp48) & 5)) {
                            // clang-format off
                            sp5C[a3].index = ptr[-1];\
                            sp5C[a3].entry = v1;\
                            a3++;
                            // clang-format on
                        }
                    }
                }
            }
        }

        if (a3 == 0) {
            if (!s2) {
                if (arg1) {
                    return FALSE;
                }

                player->aiState.recentActions[0] = NULL;

                if (gPlayerDistance > 800 && !(player->aiState.aiFlags & 0x40000)) {
                    if (gBattleSettings[player->playerId].unk_04 < 4) {
                        player_apply_move(player, 45, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss fwd");
                        player->aiState.stateCallback = func_8001DA90;
                    } else {
                        player_apply_move(player, 33, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default dash fwd");
                    }

                    player->aiState.aiFlags &= ~0x180000;
                    player->aiState.aiFlags |= 0x40000;
                } else if (gPlayerDistance < 800 && !(player->aiState.aiFlags << 19)) { // ???
                    if (gBattleSettings[player->playerId].unk_04 < 4) {
                        player_apply_move(player, 300, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss bak");
                        player->aiState.stateCallback = func_8001DA90;
                    } else {
                        player_apply_move(player, 32, TRUE);
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default dash bak");
                    }

                    player->aiState.aiFlags &= ~0x140000;
                    player->aiState.aiFlags |= 0x80000;
                } else {
                    if (guRandom() & 1 & gFrameCounter) {
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss in");
                        if (!player_apply_move(player, 293, TRUE)) {
                            return FALSE;
                        }
                        player->aiState.stateCallback = NULL;
                    } else {
                        str_copy(gPlayers[PLAYER_2].aiState.aiDebugName, "Default ss out");
                        if (!player_apply_move(player, 292, TRUE)) {
                            return FALSE;
                        }
                        player->aiState.stateCallback = NULL;
                    }

                    player->aiState.aiFlags &= ~0xC0000;
                    player->aiState.aiFlags |= 0x100000;
                }

                player->aiState.actionPtr = NULL;
                player->aiState.aiFlags |= 0x8000;
                return TRUE;
            }

            if (ai_get_transition_rule(player, &sp38C, FALSE)) {
                s2 = FALSE;
            } else {
                player->aiState.recentActions[0] = NULL;
                return FALSE;
            }
        }
    } while (a3 == 0);

    subH = &player->aiState;

    v2 = guRandom() % a3;
    subH->recentActions[0] = sp5C[v2].entry;
    pad2 = subH->recentActions[0]->actionIndex;
    subH->sequencePtr = player->aiSequenceTable + pad2;
    subH->actionFlags = subH->recentActions[0]->conditionFlags;
    subH->tableRow = sp38C;

    return ai_parse_action(player, subH) && ai_execute_action(player);
}

s16 ai_cond_approach(Player *player) {
    s16 *sp24;
    u8 v0;

    if (player->obj->frameIndex < (player->currentStateDef->unk_02 >> 1)) {
        return TRUE;
    }

    v0 = ai_get_opponent_response(player, &sp24);
    return (player->aiState.actionParam < gPlayerDistance) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
           (!v0 || (*sp24 & 2));
}

s16 func_8001CC18(Player *player) {
    s16 *sp24;
    u8 v0;

    v0 = ai_get_opponent_response(player, &sp24);
    return (player->aiState.actionParam < gPlayerDistance) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
           (!v0 || (*sp24 & 2));
}

s16 func_8001CC8C(Player *player) {
    s16 *sp24;
    u8 v0;

    v0 = ai_get_opponent_response(player, &sp24);

    if (player->obj->frameIndex < (player->currentStateDef->unk_02 >> 1)) {
        return 1;
    }

    return (player->aiState.actionParam > gPlayerDistance) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
           (!v0 || (*sp24 & 2));
}

s16 func_8001CD28(Player *player) {
    return 0;
}

s16 func_8001CD34(Player *player) {
    s16 *sp24;
    u8 v0;

    v0 = ai_get_opponent_response(player, &sp24);

    if (player->aiState.actionParam) {
        player->aiState.actionParam--;
    }

    return (player->aiState.actionParam) && !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) && (!v0 || (*sp24 & 2));
}

s16 func_8001CDAC(Player *player) {
    if (player->obj->frameIndex < (player->currentStateDef->unk_02 >> 1)) {
        return 1;
    }

    return 0;
}

s16 func_8001CDE0(Player *player) {
    player->aiState.actionParam--;

    if (player->aiState.actionParam > 0) {
        return 1;
    } else {
        return -1;
    }
}

s16 func_8001CE0C(Player *player) {
    return -1;
}

s16 func_8001CE18(Player *player) {
    s16 *sp34;
    s16 oppId;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    Player *opponent;

    oppId = 1 - player->playerId;
    sp30 = gPlayers[oppId].obj->frameIndex;
    sp2E = gPlayers[oppId].currentStateDef->hitboxActiveEnd;
    sp2C = gPlayers[oppId].currentStateDef->hitboxActiveStart;

    if (player->flags & PLAYER_FLAG_2000) {
        return 1;
    }
    if (player->aiState.hitCount >= D_80049D34[gBattleSettings[player->playerId].unk_04] &&
        !(gPlayers[1 - player->playerId].flags & PLAYER_FLAG_2000000)) {
        return 0;
    }

    player->aiState.actionParam--;

    if (ai_get_opponent_response(player, &sp34)) {
        if (!(*sp34 & 2)) {
            if (*sp34 & 4) {
                player_force_move(player, 57, TRUE);
            }
            return 1;
        }
    }

    opponent = gPlayers + oppId;
    if ((gPlayers[oppId].flags & PLAYER_FLAG_NOT_FACING_OPP) ||
        !(opponent->flags & PLAYER_FLAG_2000000) && player->aiState.actionParam < 20 &&
            ((sp30 < sp2C && D_80049DB4[opponent->characterId] < sp2C - sp30) ||
             (sp2E < sp30 && D_80049DCC[opponent->characterId] < gPlayers[oppId].currentStateDef->unk_02 - sp2E) ||
             ((gPlayers[1 - player->playerId].flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
              gPlayers[1 - player->playerId].obj->frameIndex < 6))) {
        player->currentStateId = 216;
        return -1;
    }

    return player->aiState.actionParam > 0 || !(*sp34 & 2);
}

s16 func_8001D070(Player *player) {
    s16 oppId = 1 - player->playerId;
    s32 pad;
    s16 *sp24;
    u8 v0;

    if (player->flags & PLAYER_FLAG_2000) {
        return TRUE;
    }

    if (player->aiState.hitCount >= D_80049D34[gBattleSettings[player->playerId].unk_04] &&
        !(gPlayers[1 - player->playerId].flags & PLAYER_FLAG_2000000)) {
        return FALSE;
    }

    player->aiState.actionParam--;
    v0 = ai_get_opponent_response(player, &sp24);
    if (v0 && !(*sp24 & 2)) {
        if (!(*sp24 & 4)) {
            player_force_move(player, 56, TRUE);
        }
        return TRUE;
    }

    if (gPlayers[oppId].flags & PLAYER_FLAG_NOT_FACING_OPP) {
        player->currentStateId = 0x2a;
        return -1;
    }

    return (player->aiState.actionParam > 0) || !(*sp24 & 2);
}

u8 func_8001D1F8(Player *player) {
    switch (gDifficulty) {
        case DIFFICULTY_EASY:
            switch (gBattleSettings[player->playerId].unk_04) {
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
            switch (gBattleSettings[player->playerId].unk_04) {
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

s16 func_8001D3A8(Player *player) {
    s16 *sp24;
    s32 pad[2];
    u8 v0;
    s16 playerId = player->playerId;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[playerId].unk_04]) {
        v0 = ai_get_opponent_response(player, &sp24);
        if (v0 && !(*sp24 & 2) && !(*sp24 & 4)) {
            player_force_move(player, 56, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 func_8001D44C(Player *player) {
    s16 *sp34;
    s16 oppId;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    Player *opponent;

    oppId = 1 - player->playerId;
    sp30 = gPlayers[oppId].obj->frameIndex;
    sp2E = gPlayers[oppId].currentStateDef->hitboxActiveEnd;
    sp2C = gPlayers[oppId].currentStateDef->hitboxActiveStart;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[player->playerId].unk_04]) {
        if (ai_get_opponent_response(player, &sp34)) {
            if (!(*sp34 & 2) && !(*sp34 & 4)) {
                player_force_move(player, 56, TRUE);
                return 1;
            }
        }
    }

    opponent = gPlayers + oppId;
    if (!(opponent->flags & PLAYER_FLAG_2000000)) {
        if ((sp30 < sp2C && D_80049DB4[opponent->characterId] < sp2C - sp30) ||
            (sp2E < sp30 && D_80049DCC[opponent->characterId] < gPlayers[oppId].currentStateDef->unk_02 - sp2E) ||
            ((gPlayers[1 - player->playerId].flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
             gPlayers[1 - player->playerId].obj->frameIndex < 6)) {
            player->flags &= ~PLAYER_FLAG_2000;
            return -1;
        }
    }

    return 1;
}

s16 func_8001D660(Player *player) {
    player->aiState.delayCount = 0;
    player->aiState.hitCount++;

    if (func_8001D1F8(player)) {
        player->aiState.stateCallback = func_8001D44C;
        return func_8001D44C(player);
    } else {
        player->aiState.stateCallback = func_8001D3A8;
        return func_8001D3A8(player);
    }
}

s16 func_8001D6C0(Player *player) {
    s32 pad[2];
    s16 *sp24;
    u8 v0;
    s16 playerId = player->playerId;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[playerId].unk_04]) {
        v0 = ai_get_opponent_response(player, &sp24);
        if (v0 && !(*sp24 & 2) && (*sp24 & 4)) {
            player_force_move(player, 57, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 func_8001D764(Player *player) {
    s16 oppId;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    s16 *sp34;
    Player *opponent;

    oppId = 1 - player->playerId;
    sp30 = gPlayers[oppId].obj->frameIndex;
    sp2E = gPlayers[oppId].currentStateDef->hitboxActiveEnd;
    sp2C = gPlayers[oppId].currentStateDef->hitboxActiveStart;

    player->aiState.actionParam--;

    if (player->aiState.hitCount < D_80049D34[gBattleSettings[player->playerId].unk_04]) {
        if (ai_get_opponent_response(player, &sp34)) {
            if (!(*sp34 & 2) && (*sp34 & 4)) {
                player_force_move(player, 57, TRUE);
                return 1;
            }
        }
    }

    opponent = gPlayers + oppId;
    if (!(opponent->flags & PLAYER_FLAG_2000000) && func_8001D1F8(player)) {
        if ((sp30 < sp2C && D_80049DB4[opponent->characterId] < sp2C - sp30) ||
            (sp2E < sp30 && D_80049DCC[opponent->characterId] < gPlayers[oppId].currentStateDef->unk_02 - sp2E) ||
            ((gPlayers[1 - player->playerId].flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
             gPlayers[1 - player->playerId].obj->frameIndex < 6)) {
            player->flags &= ~PLAYER_FLAG_2000;
            return -1;
        }
    }

    return 1;
}

s16 func_8001D9B0(Player *player) {
    player->aiState.delayCount = 0;
    player->aiState.hitCount++;

    if (func_8001D1F8(player)) {
        player->aiState.stateCallback = func_8001D764;
        return func_8001D764(player);
    } else {
        player->aiState.stateCallback = func_8001D6C0;
        return func_8001D6C0(player);
    }
}

s16 func_8001DA10(Player *player) {
    s16 sp1E;

    sp1E = gBattleSettings[player->playerId].unk_04;
    player->aiState.actionParam = D_80049D44[sp1E] + (guRandom() & D_80049D24[sp1E]); // @BUG ??
    player->aiState.stateCallback = func_8001CDE0;
    return 1;
}

s16 func_8001DA90(Player *player) {
    s16 *sp24;
    s32 v0;

    v0 = ai_get_opponent_response(player, &sp24);

    if (player->obj->frameIndex < (player->currentStateDef->unk_02 >> 1) &&
        !(player->flags & PLAYER_FLAG_NOT_FACING_OPP)) {
        return 1;
    }

    if (player->obj->frameIndex < player->currentStateDef->unk_02 - 1 &&
        !(player->flags & PLAYER_FLAG_NOT_FACING_OPP) && (!v0 || (*sp24 & 2))) {
        return 1;
    }

    return 0;
}

s16 func_8001DB2C(Player *player) {
    s16 sp24;
    s32 pad;
    s16 pad2;
    s16 sp2C;

    sp24 = gBattleSettings[player->playerId].unk_04;
    sp2C = D_80049D54[sp24];
    sp2C += guRandom() % D_80049D64[sp24];
    player->aiState.delayCount++;

    if (sp2C < player->aiState.delayCount || (gPlayers[1 - player->playerId].flags & PLAYER_FLAG_100000)) {
        player->aiState.sequencePtr++;
        ai_parse_action(player, &player->aiState);
        ai_execute_action(player);
        player->aiState.actionParam = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 func_8001DC68(Player *player) {
    s16 sp24;
    s32 pad;
    s16 pad2;
    s16 sp2C;

    sp24 = gBattleSettings[player->playerId].unk_04;
    sp2C = D_80049D54[sp24];
    sp2C += guRandom() % D_80049D64[sp24];
    player->aiState.delayCount++;

    if (sp2C < player->aiState.delayCount || (gPlayers[1 - player->playerId].flags & PLAYER_FLAG_100000)) {
        player->aiState.sequencePtr++;
        ai_parse_action(player, &player->aiState);
        ai_execute_action(player);
        player->aiState.actionParam = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 func_8001DDA4(Player *player) {
    s16 *sp1C;

    if (ai_get_opponent_response(player, &sp1C) != 0) {
        if (!(*sp1C & 2)) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}

s16 func_8001DDEC(Player *player) {
    player->aiState.stateCallback = NULL;
    player->aiState.sequencePtr -= 2;
    return 1;
}
