#include "common.h"
#include "camera.h"
#include "task.h"

extern s16 D_80049390;
extern HudMessage gWinMessages[];
extern u8 D_8004A42C;
extern s16 gMaxRounds;

extern Object *D_8013C23C;

extern s32 gTournamentOpponentId;

/* .bss */

Object *D_80081440;
Object *D_80081444;
Object *D_80081448;
Object *D_8008144C;
Object *D_80081450;
Object *D_80081454;

void func_80016A00(Object *);
void func_800177C0(Object *);

void func_80015BC0(Object *obj) {
    gGlobalFlags |= GAME_FLAG_80 | GAME_FLAG_40 | GAME_FLAG_MODE_DONE;
    gNextGameMode = GAME_MODE_PLAYER_SELECTION;
    func_800194E0(PLAY_MODE_50);
    if (gBattleSettings[PLAYER_1].isCpu) {
        D_80049390 = gBattleSettings[PLAYER_1].characterId;
    } else {
        D_80049390 = gBattleSettings[PLAYER_2].characterId;
    }

    gBattleSettings[PLAYER_1].isCpu = gBattleSettings[PLAYER_2].isCpu = FALSE;
    gBattleSettings[PLAYER_1].roundsWon = gBattleSettings[PLAYER_2].roundsWon = 0;
    obj->flags |= OBJ_FLAG_DELETE;
}

void func_80015C58(Object *obj) {
    if (obj->frameIndex >= obj->modInst->numAnimFrames) {
        if (--obj->vars[1] <= 0) {
            if (obj->vars[0] < obj->color.a) {
                obj->color.a -= obj->vars[0];
            } else {
                obj->color.a = 0;
                obj->fn_render = func_80015BC0;
            }
        }
    } else {
        obj->frameIndex++;
    }

    model_update(obj);
}

void func_80015CD8(Object *obj) {
    if (--obj->vars[1] <= 0) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if (obj->frameIndex == 0 && obj->vars[2] != -1) {
            sound_play(2, obj->vars[2]);
        }

        if (obj->frameIndex < obj->modInst->numAnimFrames - 1) {
            obj->frameIndex++;
        }
    }
}

void func_80015D60(Object *obj) {
    obj->flags &= ~OBJ_FLAG_HIDDEN;
    if (obj->frameIndex == 0 && obj->vars[2] != -1) {
        sound_play(2, obj->vars[2]);
    }

    if (obj->frameIndex >= obj->modInst->numAnimFrames) {
        if (--obj->vars[1] <= 0) {
            if (obj->color.a > obj->vars[0]) {
                obj->color.a -= obj->vars[0];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= OBJ_FLAG_DELETE;
            }
        }
    } else {
        obj->frameIndex++;
    }
}

void func_80015E24(Object *obj) {
    if (--obj->vars[1] <= 0) {
        if (obj->vars[0] < obj->color.a) {
            obj->color.a -= obj->vars[0];
        } else {
            TASK_END(obj->currentTask);
            obj->flags |= OBJ_FLAG_DELETE;
        }
    }
}

Object *create_hud_message(HudMessage *msg, s32 context) {
    Object *obj;
    Vec4i pos;
    Model *a3;
    char filename[80];

    sound_stop(2);
    str_copy(filename, msg->name);
    str_concat(filename, ".k2");

    a3 = gAssets[asset_find(filename, context)].aux_data;
    pos.x = pos.y = pos.z = 0;
    obj = create_model_instance(&pos, 0x1000, msg->fn_update, a3);

    if (obj != NULL) {
        obj->flags |= OBJ_FLAG_1000000;

        obj->vars[1] = msg->duration;
        obj->flags |= OBJ_FLAG_800;
        if (msg->fadeRate != 0) {
            obj->color.a = 128;
            obj->vars[0] = msg->fadeRate;
            obj->flags |= OBJ_FLAG_TRANSPARENT;
        }
        obj->vars[2] = msg->soundId;
        obj->currentTask->start_delay = 2;
    }

    return obj;
}

void func_80015F60(Object *arg0, Object *arg1) {
    D_8013C23C->currentTask->func = func_80016A00;
    D_8013C23C->currentTask->start_delay = 0;
    D_8013C23C->currentTask->flags = TASK_FLAG_ENABLED;
    D_8013C23C->currentTask->start_delay = 30;
}

Object *func_80015FB4(s16 msgId) {
    Object *obj;

    obj = create_hud_message(gGeneralMessages + msgId, CONTEXT_ABAB);
    if (obj != NULL && msgId == MESSAGE_ID_CTDOWN) {
        obj->unk_1E8 = func_80015F60;
        obj->unk_076 |= 8;
    }

    return obj;
}

Object *draw_win_message(s32 characterId, s32 arg1, u32 playerId) {
    s32 unused;
    Object *obj;

    obj = create_hud_message(gWinMessages + characterId, playerId);

    if (obj != NULL) {
        obj->currentTask->start_delay = arg1;
        obj->flags |= OBJ_FLAG_HIDDEN;
        if (gBattleSettings[playerId].isCpu) {
            obj->vars[2] = 7;
        }
    }

    sound_set_pan(0, 64);
    sound_set_pan(1, 64);
    D_8004A42C = TRUE;
    return obj;
}

u16 draw_round_number(s32 roundNumber) {
    HudMessage *a0;
    Object *obj;

    if (gBattleSettings[PLAYER_1].roundsWon == gMaxRounds - 1 &&
        gBattleSettings[PLAYER_2].roundsWon == gMaxRounds - 1) {
        a0 = &gGeneralMessages[MESSAGE_ID_FINALRD];
    } else {
        a0 = &gGeneralMessages[MESSAGE_ID_ROUND];
    }
    obj = create_hud_message(a0, CONTEXT_ABAB);
    if (obj != NULL) {
        obj->frameIndex = roundNumber * 2;
    }
    return a0->duration;
}

void func_80016144(Object *obj) {
    Object *unkObj;

    obj->flags &= ~OBJ_FLAG_HIDDEN;
    if ((gPlayerInput[1 - D_8013C24C].buttons & INP_DIRECTION) && obj->vars[1] == 0) {
        if (obj->frameIndex < obj->modInst->numAnimFrames) {
            obj->frameIndex += 30;
        }
        unkObj = D_8013C23C->varObj[5];
        unkObj->vars[1] -= 30;
    }

    obj->vars[1] = gPlayerInput[1 - D_8013C24C].buttons; // probably @bug

    if (obj->frameIndex >= obj->modInst->numAnimFrames) {
        if (--obj->vars[1] <= 0) {
            if (obj->vars[0] < obj->color.a) {
                obj->color.a -= obj->vars[0];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= OBJ_FLAG_DELETE;
            }
        }
    } else {
        obj->frameIndex++;
    }
}

void func_80016264(void) {
    Object *obj;

    for (obj = gObjectList; obj != NULL; obj = obj->nextObject) {
        if ((obj->flags & OBJ_FLAG_4000) || (obj->flags & OBJ_FLAG_3DSPRITE)) {
            obj->flags |= OBJ_FLAG_DELETE;
        }
    }
}

void func_800162A4(Object *obj) {
    Object *v0;
    Object *v1;
    u32 i;

    gPlayers[PLAYER_1].combatStateId = 0;
    gPlayers[PLAYER_2].combatStateId = 0;

    create_player_obj(PLAYER_1);
    create_player_obj(PLAYER_2);

    obj->flags |= OBJ_FLAG_DELETE;
    sCutsceneVariant = gFrameCounter % 5;
    D_8013C226 = 0;

    func_80016264();
    battle_round_init();
    func_80021D30();

    v0 = obj->varObj[4];
    if (v0 != NULL) {
        v0->flags |= OBJ_FLAG_DELETE;
    }
    if (D_80081440 != NULL) {
        D_80081440->flags |= OBJ_FLAG_DELETE;
    }
    if (D_80081448 != NULL) {
        D_80081448->flags |= OBJ_FLAG_DELETE;
    }
    if (D_8008144C != NULL) {
        D_8008144C->flags |= OBJ_FLAG_DELETE;
    }
    if (D_80081450 != NULL) {
        D_80081450->flags |= OBJ_FLAG_DELETE;
    }
    if (D_80081444 != NULL) {
        D_80081444->flags |= OBJ_FLAG_DELETE;
    }
    if (D_80081454 != NULL) {
        D_80081454->flags |= OBJ_FLAG_DELETE;
    }

    gCamera->currentTask->func = camera_outro_start;
    gCamera->currentTask->start_delay = 0;
    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -400;
    sCutsceneAnimDone = FALSE;

    if (gBattleDuration != 0) {
        D_8013C240->frameIndex = 3 + gBattleDuration * 3;
        v1 = D_8013C240->varObj[0];
        v1->frameIndex = 0;
        D_8013C240->currentTask->func = task_default_func;
    }

    D_8013C234->offsetX = D_8013C234->offsetX - D_8013C234->leftS + D_8013C234->rightS - 88;
    D_8013C234->leftS = D_8013C234->rightS - 88;
    D_8013C238->rightS = D_8013C238->leftS + 80;

    D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
    D_8013C232 = D_8013C230 = 80;

    D_80052D64[0] = D_80052D64[1] = D_80052D68[0] = D_80052D68[1] = D_80052D6C[0] = D_80052D6C[1] = D_8013C3C0[0] =
        D_8013C3C0[1] = D_80052D70[0] = D_80052D70[1] = D_80052D74[0] = D_80052D74[1] = 0;
    D_80052D78[0] = D_80052D78[1] = 2;

    if (!D_8013C24E && gBattleSettings[D_8013C24C].roundsWon != 0) {
        D_8013C258[D_8013C24C][gBattleSettings[D_8013C24C].roundsWon - 1]->frameIndex = 13;
    } else if (D_8013C24E && gBattleSettings[PLAYER_1].roundsWon != 0 && gBattleSettings[PLAYER_2].roundsWon != 0) {
        D_8013C258[PLAYER_1][gBattleSettings[PLAYER_1].roundsWon - 1]->frameIndex = 13;
        D_8013C258[PLAYER_2][gBattleSettings[PLAYER_2].roundsWon - 1]->frameIndex = 13;
    } else {
        for (i = 0; i < gMaxRounds; i++) {
            D_8013C258[PLAYER_1][i]->frameIndex = D_8013C258[PLAYER_2][i]->frameIndex = 12;
        }
    }

    gPlayers[PLAYER_1].obj->frameIndex = 2;
    gPlayers[PLAYER_2].obj->frameIndex = 2;
    model_change_animation(gPlayers[PLAYER_1].obj);
    model_change_animation(gPlayers[PLAYER_2].obj);

    func_80012AF4(&gPlayers[PLAYER_1].unk_750.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_1].unk_868.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_2].unk_750.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_2].unk_868.local_matrix);

    model_update_animated_params(gPlayers[PLAYER_1].obj);
    model_update_animated_params(gPlayers[PLAYER_2].obj);
    gPlayers[PLAYER_1].obj->previousFrameIndex = gPlayers[PLAYER_1].obj->frameIndex;
    gPlayers[PLAYER_2].obj->previousFrameIndex = gPlayers[PLAYER_2].obj->frameIndex;
    gPlayers[PLAYER_1].animTask->flags &= ~TASK_FLAG_TRIGGER_FRAME;
    gPlayers[PLAYER_2].animTask->flags &= ~TASK_FLAG_TRIGGER_FRAME;

    gPlayerAngle = 0x800;
    func_80029130();
}

u32 func_8001675C(Player *player, s32 arg1, u32 arg2) {
    s32 temp;
    u32 res;

    player_apply_move(player, arg1, TRUE);

    temp = player->animTask->params[1];
    if (arg2 < player->combatStateTable[temp].maxFrame + 120) {
        res = player->combatStateTable[temp].maxFrame + 120;
    } else {
        res = arg2;
    }
    return res;
}

u8 func_800167D4(void) {

    if ((gPlayMode == PLAY_MODE_TOURNAMENT_P1 || gPlayMode == PLAY_MODE_TOURNAMENT_P2) &&
        gBattleSettings[D_8013C24C].isCpu) {
        gPlayerInput[1 - D_8013C24C].enabled = TRUE;
        return (gPlayerInput[1 - D_8013C24C].buttons & INP_START) != 0;
    } else {
        return (gPlayerInput[D_8013C24C].buttons & INP_START) != 0;
    }
}

void func_80016880(Object *obj) {
    gPlayers[PLAYER_1].autoTransitionTimer = gPlayers[PLAYER_2].autoTransitionTimer = 0;

    if (--obj->vars[1] < 0 && func_800167D4()) {
        func_800162A4(obj);
    }

    if (--obj->vars[0] < 0) {
        func_800162A4(obj);
    }
}

void func_800168F0(Object *obj) {
    gPlayers[PLAYER_1].autoTransitionTimer = gPlayers[PLAYER_2].autoTransitionTimer = 0;

    if (--obj->vars[1] < 0 && func_800167D4()) {
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        TASK_END(obj->currentTask);
        gGlobalFlags |= GAME_FLAG_20;
        obj->flags |= OBJ_FLAG_DELETE;
    }

    if (--obj->vars[0] < 0) {
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        TASK_END(obj->currentTask);
        gGlobalFlags |= GAME_FLAG_20;
        obj->flags |= OBJ_FLAG_DELETE;
    }
}

void func_800169C4(Object *obj) {
    gNextGameMode = gDifficulty >= DIFFICULTY_NORMAL ? GAME_MODE_34 : GAME_MODE_37; // not real mode? @bug?
    obj->currentTask->func = func_800168F0;
}

void func_80016A00(Object *obj) {
    Object *a2;
    s16 i;
    s16 a3;

    if (gBattleSettings[PLAYER_1].isCpu || gBattleSettings[PLAYER_2].isCpu) {
        a2 = func_80015FB4(MESSAGE_ID_GAME_OVER);
        gNextGameMode = GAME_MODE_MAIN_MENU;
        gBattleSettings[PLAYER_1].consecutiveWins = gBattleSettings[PLAYER_2].consecutiveWins = 0;
    } else {
        a2 = func_80015FB4(MESSAGE_ID_GAME_OVER);
        gNextGameMode = GAME_MODE_PLAYER_SELECTION;

        if (gPlayMode == PLAY_MODE_50) {
            a3 = gMaxRounds == gBattleSettings[PLAYER_2].roundsWon;
            func_800194E0(PLAY_MODE_TOURNAMENT_P1 + a3);

            gBattleSettings[1 - a3].isCpu = TRUE;
            gTournamentOpponentId = 1 - a3;

            for (i = 0; i < NUM_CHARACTERS; i++) {
                D_800B6350[a3][i] = FALSE;
            }
        }
    }

    obj->currentTask->func = func_800168F0;

    if (a2 != NULL) {
        a2->vars[1] = 10;
        a2->vars[0] = a2->modInst->numAnimFrames;
    } else {
        obj->vars[1] = 0;
        obj->vars[0] = 0;
    }
}

void func_80016B6C(Object *obj) {
    Object *v0;

    if (gPlayerInput[1 - D_8013C24C].buttons & INP_START) {
        battle_match_init();

        if (gPlayMode == PLAY_MODE_TOURNAMENT_P1) {
            D_800B6350[PLAYER_2][gPlayers[PLAYER_2].characterId] = FALSE;
        } else if (gPlayMode == PLAY_MODE_TOURNAMENT_P2) {
            D_800B6350[PLAYER_1][gPlayers[PLAYER_1].characterId] = FALSE;
        }

        v0 = obj->varObj[3];
        if (v0 != NULL) {
            v0->flags |= OBJ_FLAG_HIDDEN;
            v0->currentTask->func = task_default_func;
        }

        func_800162A4(obj);
    }
}

void func_80016C34(Object *obj) {
    Object *a1;

    gGlobalFlags |= GAME_FLAG_4;

    if (--obj->vars[2] == 0 || (--obj->vars[1] < 0 && func_800167D4())) {
        if (gBattleSettings[PLAYER_1].isCpu || gBattleSettings[PLAYER_2].isCpu) {
            obj->varObj[5] = D_8008144C = func_80015FB4(MESSAGE_ID_CONT);
        } else {
            obj->varObj[5] = D_8008144C = func_80015FB4(MESSAGE_ID_CONT2);
        }
        obj->varObj[3] = D_80081450 = func_80015FB4(MESSAGE_ID_CTDOWN);

        gPlayerInput[1 - D_8013C24C].enabled = TRUE;
        obj->currentTask->func = func_80016B6C;
        a1 = obj->varObj[4];
        if (a1 != NULL) {
            a1->flags |= OBJ_FLAG_DELETE;
        }
        gPlayerInput[D_8013C24C].pendingInput = FALSE;
        obj->varObj[4] = obj->varObj[5];
    }
}

ObjFunc handle_player_win(u32 playerId, u8 arg1) {
    ObjFunc a3;

    a3 = func_80016880;

    gBattleSettings[playerId].roundsWon++;
    if (gBattleSettings[playerId].roundsWon == gMaxRounds) {
        if (!arg1) {
            gBattleSettings[D_8013C24C].consecutiveWins++;
            gBattleSettings[1 - D_8013C24C].consecutiveWins = 0;
        }

        D_800B6368[gBattleSettings[playerId].characterId].wins++;
        D_800B6368[gBattleSettings[1 - playerId].characterId].loses++;
        D_800801F1 = TRUE;

        switch (gPlayMode) {
            case PLAY_MODE_TOURNAMENT_P1:
            case PLAY_MODE_TOURNAMENT_P2:
                if (!gBattleSettings[playerId].isCpu) {
                    D_800B6350[1 - playerId][gPlayers[1 - playerId].characterId] = TRUE;

                    if (func_8001E188(1 - playerId) == -1) {
                        a3 = func_800169C4;
                    } else {
                        gNextGameMode = GAME_MODE_PLAYER_SELECTION;
                        a3 = func_800168F0;
                    }
                } else {
                    a3 = func_80016C34;
                }
                break;
            case PLAY_MODE_2_PLAYERS:
            case PLAY_MODE_50:
                a3 = func_80016C34;
                break;
            case PLAY_MODE_30:
                gNextGameMode = GAME_MODE_MAIN_MENU;
                break;
        }
    }

    return a3;
}

void func_80016F6C(Object *obj) {
    s32 sp2C;
    ObjFunc v02;

    sp2C = func_8001675C(&gPlayers[D_8013C24C], (gFrameCounter & 1) ? MOVE_ID_VICTORY_132 : MOVE_ID_VICTORY_2, 0x78);
    func_80016264();
    obj->varObj[4] = D_80081440 = draw_win_message(gPlayers[D_8013C24C].characterId, 6, D_8013C24C);
    v02 = handle_player_win(D_8013C24C, FALSE);

    obj->vars[0] = sp2C + 120;
    obj->vars[1] = 10;
    obj->vars[2] = 190;
    obj->currentTask->func = v02;

    gGlobalFlags &= ~GAME_FLAG_BATTLE_FINISHED;
    gPlayers[1 - D_8013C24C].obj->flags |= OBJ_FLAG_HIDDEN;
    gPlayers[D_8013C24C].obj->pos.x = gPlayers[D_8013C24C].obj->pos.y = gPlayers[D_8013C24C].obj->pos.z = 0;
    gPlayers[1 - D_8013C24C].obj->pos.x = gPlayers[1 - D_8013C24C].obj->pos.y = gPlayers[1 - D_8013C24C].obj->pos.z = 0;

    gPlayers[PLAYER_1].obj->rotation.y = 0;
    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_400000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_400000;

    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -400;

    if (gBattleSettings[D_8013C24C].characterId != MORPHIX) {
        gPlayers[D_8013C24C].obj->flags |= OBJ_FLAG_10000000;
    }

    gPlayers[D_8013C24C].obj->flags &= ~(OBJ_FLAG_8000000 | OBJ_FLAG_800000);
}

void func_800171EC(Object *obj) {
    s32 pad;
    Object *v0;
    ObjFunc a3;

    v0 = func_80015FB4(MESSAGE_ID_DRAW);
    a3 = func_80016880;

    if (v0 != NULL) {
        v0->currentTask->start_delay = 5;
    }

    D_80081444 = v0;

    func_8001675C(&gPlayers[PLAYER_2], MOVE_ID_DEFEAT_INTRO,
                  func_8001675C(&gPlayers[PLAYER_1], MOVE_ID_DEFEAT_INTRO, 0x78));

    if (gMaxRounds == gBattleSettings[PLAYER_1].roundsWon + 1) {
        a3 = handle_player_win(PLAYER_1, TRUE);
    } else {
        gBattleSettings[PLAYER_1].roundsWon++;
    }

    if (gMaxRounds == gBattleSettings[PLAYER_2].roundsWon + 1) {
        a3 = handle_player_win(PLAYER_2, TRUE);
    } else {
        gBattleSettings[PLAYER_2].roundsWon++;
    }

    obj->vars[0] = 245;
    obj->vars[1] = 10;
    obj->vars[2] = 190;
    obj->varObj[4] = v0;

    obj->currentTask->func = a3;
}

void func_80017304(Object *obj) {
    Object *a0;

    if (--obj->vars[0] > 0) {
        if ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START)) {
            a0 = obj->varObj[4];
            a0->flags |= OBJ_FLAG_DELETE;

            if (gPlayerInput[PLAYER_1].buttons & INP_START) {
                gPlayerInput[PLAYER_1].pendingInput = FALSE;
            }
            if (gPlayerInput[PLAYER_2].buttons & INP_START) {
                gPlayerInput[PLAYER_2].pendingInput = FALSE;
            }
        } else {
            return;
        }
    }

    if (D_8013C24E) {
        obj->currentTask->func = func_800171EC;
    } else {
        gPlayerInput[1 - D_8013C24C].enabled = FALSE;
        gPlayerInput[1 - D_8013C24C].buttons = 0;
        obj->currentTask->func = func_80016F6C;
    }
}

void func_800173DC(Object *obj) {
    if (gPlayers[PLAYER_1].flags & PLAYER_FLAG_80) {
        if (--gPlayers[PLAYER_1].autoTransitionTimer > 20) {
            gPlayers[PLAYER_1].autoTransitionTimer = 20;
        } else {
            player_select_transition(&gPlayers[PLAYER_1], TRUE);
        }
    } else if (gPlayers[PLAYER_2].flags & PLAYER_FLAG_80) {
        if (--gPlayers[PLAYER_2].autoTransitionTimer > 20) {
            gPlayers[PLAYER_2].autoTransitionTimer = 20;
        } else {
            player_select_transition(&gPlayers[PLAYER_2], TRUE);
        }
    } else if ((gPlayers[PLAYER_1].flags & PLAYER_FLAG_40000) && (gPlayers[PLAYER_2].flags & PLAYER_FLAG_40000)) {
        if ((gPlayers[PLAYER_1].combatState->flags & CSF_CROUCH) && gPlayers[PLAYER_1].combatStateId != 4) {
            player_apply_move(&gPlayers[PLAYER_1], MOVE_ID_CROUCH_IDLE, FALSE);
        } else if (gPlayers[PLAYER_1].combatStateId != 17) {
            player_apply_move(&gPlayers[PLAYER_1], MOVE_ID_IDLE_068, FALSE);
        }

        if ((gPlayers[PLAYER_2].combatState->flags & CSF_CROUCH) && gPlayers[PLAYER_2].combatStateId != 4) {
            player_apply_move(&gPlayers[PLAYER_2], MOVE_ID_CROUCH_IDLE, FALSE);
        } else if (gPlayers[PLAYER_2].combatStateId != 17) {
            player_apply_move(&gPlayers[PLAYER_2], MOVE_ID_IDLE_068, FALSE);
        }

        gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;

        obj->currentTask->func = func_80017304;
        obj->currentTask->start_delay = 10;
        obj->vars[0] = 80;
        D_80080234 = TRUE;
    }
}

void func_800175B0(Object *obj) {
    if (D_80080234) {
        obj->currentTask->func = func_800177C0;
    }
}

void func_800175D8(Object *obj) {
    if (++obj->vars[0] & 8) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void func_80017614(Object *obj) {
    if (D_80080234) {
        obj->flags |= OBJ_FLAG_DELETE;
    }
    func_800175D8(obj);
}

void func_80017650(Object *obj) {
    UIElement sp60 = { 0x26, func_80017614, 0x4000000, 0x1001, "bars.sp2" };
    Vec4i sp50 = { 250, 220, 0, 0 };

    gPlayerInput[D_8013C24C].enabled = TRUE;
    gGlobalFlags &= ~GAME_FLAG_BATTLE_FINISHED;
    if (TRUE) {
        D_80080234 = TRUE;
    }
    obj->currentTask->func = func_800177C0;
    obj->currentTask->start_delay = 45;
    func_80016264();
}

void func_80017728(Object *obj) {
    Object *a0;

    if (--obj->vars[0] > 0) {
        if (gPlayerInput[D_8013C24C].buttons & INP_START) {
            a0 = obj->varObj[4];
            if (a0 != NULL) {
                a0->flags |= OBJ_FLAG_DELETE;
            }

            if (gPlayerInput[PLAYER_1].buttons & INP_START) {
                gPlayerInput[PLAYER_1].pendingInput = FALSE;
            }
            if (gPlayerInput[PLAYER_2].buttons & INP_START) {
                gPlayerInput[PLAYER_2].pendingInput = FALSE;
            }
        } else {
            return;
        }
    }

    obj->currentTask->func = func_80017650;
}

void func_800177C0(Object *obj) {
    gGlobalFlags &= ~GAME_FLAG_BATTLE_FINISHED;

    if (!D_80080234) {
        if (gPlayers[PLAYER_1].obj->playerHp == gBattleSettings[PLAYER_1].initialHp &&
                gPlayers[PLAYER_2].obj->playerHp == 0 ||
            gPlayers[PLAYER_1].obj->playerHp == 0 &&
                gPlayers[PLAYER_2].obj->playerHp == gBattleSettings[PLAYER_2].initialHp) {
            obj->varObj[4] = D_80081448 = func_80015FB4(MESSAGE_ID_PAUSE2);
            obj->vars[0] = 90;
            gPlayerInput[D_8013C24C].enabled = TRUE;
            obj->currentTask->func = func_80017728;
        } else {
            obj->currentTask->func = func_80017650;
        }
    } else {
        gPlayerInput[D_8013C24C].enabled = TRUE;
        if (D_8013C24E) {
            gPlayerInput[1 - D_8013C24C].enabled = TRUE;
            obj->currentTask->func = func_800171EC;
        } else {
            obj->currentTask->func = func_80016F6C;
        }
    }
}

void func_8001792C(Object *obj) {
    Object *newObj;

    if (gRoundOver || gPlayers[PLAYER_1].obj->playerHp <= 0 || gPlayers[PLAYER_2].obj->playerHp <= 0) {
        func_80029044();
        gRoundOver = TRUE;
        if (!(gGlobalFlags & GAME_FLAG_4)) {
            gGlobalFlags |= GAME_FLAG_4;
            return;
        }

        gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = FALSE;
        if (gPlayers[PLAYER_1].obj->playerHp > gPlayers[PLAYER_2].obj->playerHp) {
            D_8013C24C = PLAYER_1;
        } else {
            D_8013C24C = PLAYER_2;
        }

        D_8013C24E = (gPlayers[PLAYER_1].obj->playerHp == gPlayers[PLAYER_2].obj->playerHp);

        if (gRoundOver && gPlayers[PLAYER_1].obj->playerHp != 0 && gPlayers[PLAYER_2].obj->playerHp != 0) {
            newObj = func_80015FB4(MESSAGE_ID_TIME_OVER);
            D_80081454 = newObj;
            obj->varObj[4] = newObj;
            obj->currentTask->func = func_800173DC;
        } else {
            obj->currentTask->func = func_800177C0;
        }

        D_80080234 = FALSE;
        obj->currentTask->start_delay = 45;
    }
}

void func_80017A90(Object *obj) {
    gGlobalFlags |= GAME_FLAG_4;
    gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;

    if (++obj->vars[0] > 900) {
        gNextGameMode = GAME_MODE_29;
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        obj->flags |= OBJ_FLAG_DELETE;
    } else if ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START)) {
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        gNextGameMode = GAME_MODE_MAIN_MENU;
        obj->flags |= OBJ_FLAG_DELETE;
    }
}

void func_80017B3C(Object *obj) {
    if (gPlayMode == PLAY_MODE_30) {
        obj->currentTask->func = func_80017A90;
        obj->vars[0] = 0;
        gGlobalFlags |= GAME_FLAG_4;
    } else {
        obj->currentTask->func = func_8001792C;
        gGlobalFlags &= ~GAME_FLAG_4;
    }

    gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;
    gPlayers[PLAYER_1].flags &= ~PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags &= ~PLAYER_FLAG_100000;

    if (gBattleSettings[PLAYER_1].isCpu) {
        gPlayers[PLAYER_1].aiState.aiFlags &= ~AIF_AI_DISABLED;
    }
    if (gBattleSettings[PLAYER_2].isCpu) {
        gPlayers[PLAYER_2].aiState.aiFlags &= ~AIF_AI_DISABLED;
    }

    func_80028FCC();
}

void func_80017C3C(Object *obj) {
    Object *v0;
    obj->currentTask->func = func_80017B3C;
    v0 = func_80015FB4(MESSAGE_ID_BATTLE);
    obj->currentTask->start_delay = v0->modInst->numAnimFrames + 20;
}

void func_80017C88(Object *obj) {
    task_execute(obj);
}

void func_80017CA8(void) {
    D_8013C23C = create_worker(func_80017C88, 1);
    gRoundOver = FALSE;
    sCutsceneAnimDone = 0;

    gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = FALSE;
    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_100000;
    gReplayActive = FALSE;
    D_80080234 = FALSE;

    if (gBattleSettings[PLAYER_1].isCpu) {
        gPlayers[PLAYER_1].aiState.aiFlags |= AIF_AI_DISABLED;
    }
    if (gBattleSettings[PLAYER_2].isCpu) {
        gPlayers[PLAYER_2].aiState.aiFlags |= AIF_AI_DISABLED;
    }

    D_8013C23C->currentTask->func = func_80017C3C;
    D_8013C23C->currentTask->start_delay = 0;
    D_8013C23C->currentTask->flags = TASK_FLAG_ENABLED;
    D_8013C23C->currentTask->start_delay =
        draw_round_number(gBattleSettings[PLAYER_1].roundsWon + gBattleSettings[PLAYER_2].roundsWon);
    D_80081440 = D_80081448 = D_8008144C = D_80081450 = D_80081454 = D_80081444 = NULL;
}
