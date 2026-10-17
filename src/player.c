#include "common.h"
#include "task.h"
#include "camera.h"

/* Player subsystem: character lifecycle, state machine transitions, replay,
   tracking transforms, and character-specific lighting.  Every function
   involved in creating, updating, and tearing down a player lives here. */

typedef struct TransitionSnapshot {
    /* 0x00 */ s16 playerHp[2];
    /* 0x04 */ s16 currentLogicState;
    /* 0x06 */ u8 playerId;
    /* 0x07 */ u8 delayUntilNext;
} TransitionSnapshot; // size=0x8

typedef struct TransitionRingBuffer {
    /* 0x0000 */ TransitionSnapshot unk_00[512];
    /* 0x1000 */ u16 headIndex;
    /* 0x1002 */ u16 tailIndex;
    /* 0x1004 */ s32 lastFrameCounter;
    /* 0x1008 */ s32 startFrameCounter;
} TransitionRingBuffer; // size = 0x100C

typedef struct AssetDB2 {
    /* 0x00 */ char unk_00[12];
} AssetDB2; // size = 0xC

typedef struct AssetDB1 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ AssetDB2 unk_04[1];
} AssetDB1;

typedef struct AssetDB3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04[1];
} AssetDB3;

typedef struct CharacterDefinition {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 transitionTable;
    /* 0x08 */ s32 logicStates;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 stateTable;
    /* 0x18 */ s32 soundTable;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 moveToLogicStateMap;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 projectileTable;
    /* 0x2C */ s32 barrageTable;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
} CharacterDefinition; // size = 0x44

typedef struct CharSymbols {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
}; // size = 0x10

extern s16 D_8004A730[];
extern s16 D_8004A748[];
extern CharLighting gBattleDemitronLighting;
extern CharLighting gBattleDemonicaLighting;
extern CharLighting gBattleDemitronAltLighting;
extern CharLighting gBattleDemonicaAltLighting;
extern UnkQwe D_8004B94C[];
extern Behavior gBehaviorTable[];

extern s32 D_80080218;
extern TransitionRingBuffer gTransitionReplayBuffer;

s16 gCharacterSelectResult = -1;
s16 sSentinelEmpty = -1;

/* .bss */
s16 gPlayMode;
s16 gPreviousPlayMode;
u16 gReplayOverflow;
u16 gReplayDisabled;
TransitionRingBuffer gTransitionReplayBuffer;

void motion_trail_init(MotionTrail *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4,
                       ColorRGBA *arg5);
void ai_max_difficulty(Player *);
void ai_increase_difficulty(Player *);
s32 func_8001DFE4(s32 arg0);
void replay_respawn_player(s16 playerId);
void replay_update_player(Object *obj);

extern s16 D_8004B9FC[];

/* Record the player's current state (HP, logic state, player ID) into the
   transition replay ring buffer so the match can be replayed later. */
#ifdef NON_MATCHING
void log_transition_state(Player *player) {
    TransitionSnapshot *a1;
    u16 t8;
    u16 a2;
    Object *v0;
    s32 v1;
    s32 nv;
    s32 temp;

    v0 = player->obj;

    if (gReplayDisabled || gRoundOver) {
        return;
    }
    v1 = gTransitionReplayBuffer.tailIndex;
    a1 = gTransitionReplayBuffer.unk_00 + v1;
    a1->currentLogicState = player->currentLogicState;
    a1->playerId = player->playerId;
    a1->delayUntilNext = 255;

    t8 = 1 - player->playerId;
    a2 = player->playerId;
    a1->playerHp[a2] = v0->playerHp;
    a1->playerHp[t8] = gPlayers[t8].obj->playerHp;

    nv = gTransitionReplayBuffer.tailIndex;
    gTransitionReplayBuffer.unk_00[((nv - 1) & 0x1FF)].delayUntilNext =
        gFrameCounter - gTransitionReplayBuffer.lastFrameCounter;

    nv = (nv + 1) & 0x1FF;
    gTransitionReplayBuffer.tailIndex = nv;
    gTransitionReplayBuffer.lastFrameCounter = gFrameCounter;

    if (nv == gTransitionReplayBuffer.headIndex) {
        gReplayOverflow = 1;
        gTransitionReplayBuffer.headIndex = (gTransitionReplayBuffer.headIndex + 1) & 0x1FF;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/player/log_transition_state.s")
void log_transition_state(Player *player);
#endif

/* Mark the replay object for deletion and signal overflow to stop playback. */
void end_replay(Object *obj) {
    obj->flags |= OBJ_FLAG_DELETE;
    gReplayOverflow = 1;
}

/* Wait for the replay to conclude (opponent KO'd or timeout), then schedule
   the end_replay task. */
void replay_await_end(Object *obj) {
    if (gPlayers[1 - D_8013C24C].obj->playerHp <= 0 || --obj->vars[0] <= 0) {
        obj->currentTask->startDelay = 55;
        obj->currentTask->func = end_replay;
    }
}

/* Replay: consume snapshots from the ring buffer, applying each saved
   transition state in sequence.  When delayUntilNext != 255, pause for that
   many frames before reading the next entry. */
void replay_restore_snapshot(Object *obj) {
    s32 s0;
    TransitionSnapshot *s1;
    s32 s3;
    s16 v0;
    s32 temp;

    s0 = gTransitionReplayBuffer.headIndex;
    s1 = gTransitionReplayBuffer.unk_00 + s0;
    s3 = s1->playerId;

    gPlayers[s3].flags |= PLAYER_FLAG_800000;
    player_make_transition(gPlayers + s3, TRUE, s1->currentLogicState);
    v0 = s1->playerHp[s3];
    gPlayers[s3].obj->playerHp = v0;
    if (v0 == 0) {
        gGlobalFlags |= GAME_FLAG_BATTLE_FINISHED;
    }

    if (s1->delayUntilNext != 255) {
        s0++;
        gTransitionReplayBuffer.headIndex = s0 & ~0x200;
        temp = s1->delayUntilNext;
        if (temp != s0 * 0) { // @fake
            obj->currentTask->startDelay = temp - 1;
        } else {
            replay_restore_snapshot(obj);
        }
    } else {
        obj->currentTask->func = replay_await_end;
        obj->vars[0] = 260;
    }
}

/* Replay: execute the current replay task each frame; if START is pressed,
   abort replay and return to normal gameplay. */
void replay_poll_skip(Object *obj) {
    task_execute(obj);

    if (gPlayerInput[D_8013C24C].buttons & INP_START) {
        obj->flags |= OBJ_FLAG_DELETE;
        gReplayOverflow = 1;
        D_8013C23C->currentTask->startDelay = 0;
        D_8013C23C->currentTask->func = func_800177C0;
        gPlayerInput[D_8013C24C].pendingInput = FALSE;
    }
}

/* Initialise replay playback: respawn both players at frame 2, reset camera,
   and create the replay worker chain (poll_skip → restore_snapshot → await_end). */
s32 replay_setup(void *arg0) {
    s32 s3;
    Object *v0;
    u32 i;
    s32 temp;

    s3 = gFrameCounter - gTransitionReplayBuffer.startFrameCounter;

    gTransitionReplayBuffer.headIndex = 0;
    gReplayActive = 1;
    gPlayers[PLAYER_1].combatStateId = CS_ID_0;
    gPlayers[PLAYER_2].combatStateId = CS_ID_0;

    replay_respawn_player(PLAYER_1);
    replay_respawn_player(PLAYER_2);
    gPlayers[PLAYER_1].obj->frameIndex = 2;
    gPlayers[PLAYER_2].obj->frameIndex = 2;
    model_change_animation(gPlayers[PLAYER_1].obj);
    model_change_animation(gPlayers[PLAYER_2].obj);

    func_80012AF4(&gPlayers[PLAYER_1].headTrack.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_1].bodyTurn.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_2].headTrack.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_2].bodyTurn.local_matrix);

    model_update_animated_params(gPlayers[PLAYER_1].obj);
    model_update_animated_params(gPlayers[PLAYER_2].obj);
    gPlayers[PLAYER_1].obj->previousFrameIndex = gPlayers[PLAYER_1].obj->frameIndex;
    gPlayers[PLAYER_2].obj->previousFrameIndex = gPlayers[PLAYER_2].obj->frameIndex;
    gPlayers[PLAYER_1].animTask->flags &= ~TASK_FLAG_TRIGGER_FRAME;
    gPlayers[PLAYER_2].animTask->flags &= ~TASK_FLAG_TRIGGER_FRAME;

    gPlayerAngle = 0x800;
    camera_orbit_init(gCamera);
    gCamera->currentTask->func = camera_battle_update;
    gCamera->currentTask->startDelay = 0;
    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -400;
    sCutsceneAnimDone = FALSE;

    temp = guRandom() % 2;

    if (temp) {}

    v0 = create_worker(replay_poll_skip, OBJ_PRIO_LOWEST + temp * 0);
    v0->currentTask->func = replay_restore_snapshot;
    v0->currentTask->startDelay = 0;
    v0->currentTask->flags = TASK_FLAG_ENABLED;

    gGfxFlags |= GFX_FLAG_CUTSCENE;
    gGlobalFlags &= ~GAME_FLAG_BATTLE_FINISHED;

    if (s3 > 960) {
        s3 -= 960;
        for (i = 0; i < s3; i++) {
            replay_update_player(gPlayers[PLAYER_1].obj);
            replay_update_player(gPlayers[PLAYER_2].obj);
            replay_poll_skip(v0);
        }

        camera_orbit_update(gCamera, TRUE);
    }

    return 0;
}

/* Called after the KO screen; if enough frames have passed, schedule replay
   setup as a post-render hook.  Returns TRUE when replay begins. */
s32 replay_schedule_start(void) {
    s32 diff = gFrameCounter - gTransitionReplayBuffer.startFrameCounter;

    if (diff < 60) {
        return FALSE;
    } else {
        set_post_render_hook(replay_setup, NULL);
        return TRUE;
    }
}

/* Per-frame update for a player during replay playback.  Executes the current
   task chain, syncs animation, and polls for transitions just like the normal
   update but without hit detection or AI. */
void replay_update_player(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    s32 unused[7];
    ModelInstance *mosInst = obj->modInst;

    if (player_check_func_2(obj)) {
        player->flags |= PLAYER_FLAG_NOT_FACING_OPP;
    } else {
        player->flags &= ~PLAYER_FLAG_NOT_FACING_OPP;
    }

    task_execute(obj);

    if (mosInst->currentAnimId != mosInst->previousAnimId) {
        model_change_animation(obj);
        mosInst->previousAnimId = mosInst->currentAnimId;
    }

    if (obj->frameIndex != obj->previousFrameIndex) {
        model_process_animation(obj);
        model_update_animated_params(obj);
        obj->previousFrameIndex = obj->frameIndex;
    }

    if (player_check_func_2(obj)) {
        player->flags |= PLAYER_FLAG_NOT_FACING_OPP;
    } else {
        player->flags &= ~PLAYER_FLAG_NOT_FACING_OPP;
    }

    if (player->allowTransition) {
        if (player->autoTimer != 0 && --player->autoTimer == 0) {
            player_select_transition(player, TRUE);
        } else if (!(player->flags & (PLAYER_FLAG_TRANSITION_GUARD | PLAYER_FLAG_GAMEPLAY_LOCKED)) &&
                   gPlayerInput[playerId].pendingInput && player->lookupLogicTable >= 0 &&
                   !(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME)) {
            player_select_transition(player, FALSE);
        }
    }

    player->allowTransition = TRUE;
}

/* Main per-frame player update: run model animation, render hit trails,
   apply software vertex lighting, poll AI or human input for transitions,
   and detect hit collisions with the opponent. */
void player_update(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    u16 oppId;
    Player *opponent;
    CombatState *currentState;
    CombatState *oppState;
    s32 pad[2];
    Object *oppObj;
    u8 pad2;
    u8 showTrail;

    currentState = player->combatState;
    oppId = 1 - playerId;
    opponent = &gPlayers[oppId];
    oppState = opponent->combatState;
    oppObj = opponent->obj;

    if (player_check_func_2(obj)) {
        player->flags |= PLAYER_FLAG_NOT_FACING_OPP;
    } else {
        player->flags &= ~PLAYER_FLAG_NOT_FACING_OPP;
    }

    model_update(obj); // also executes tasks

    if (player_check_func_2(obj)) {
        player->flags |= PLAYER_FLAG_NOT_FACING_OPP;
    } else {
        player->flags &= ~PLAYER_FLAG_NOT_FACING_OPP;
    }

    showTrail = (currentState->damage != 0) && (obj->frameIndex >= currentState->trailStart) &&
                (obj->frameIndex < currentState->trailEnd);

    hitbox_render_update(&player->rightHandTrail, (currentState->flags & CSF_ATTACK_RIGHT_HAND) && showTrail);
    if (player->hasLeftHandTrail) {
        hitbox_render_update(&player->leftHandTrail, (currentState->flags & CSF_ATTACK_LEFT_HAND) && showTrail);
    }
    hitbox_render_update(&player->leftLegTrail, (currentState->flags & CSF_ATTACK_LEFT_FOOT) && showTrail);
    hitbox_render_update(&player->rightLegTrail,
                         (currentState->flags & (CSF_ATTACK_RIGHT_FOOT_1 | CSF_ATTACK_RIGHT_FOOT_2)) && showTrail);

    if (player->characterId != MORPHIX) {
        func_80037E28(obj);
    }

    if (gIsPaused) {
        return;
    }

    if (gPlayMode == PLAY_MODE_PRACTICE) {
        if (D_8013C430 == 16) {
            func_800338D0();
        } else if (D_8013C430 == 18) {
            func_80033D64();
        }
        if (D_8013C434 == 66) {
            func_80033D64();
        }
    }

    if (gBattleSettings[playerId].isCpu && !gRoundOver && !(player->flags & PLAYER_FLAG_GAMEPLAY_LOCKED)) {
        if (!(player->aiState.aiFlags & AIF_AI_DISABLED)) {
            ai_update(player);
        }
        if (D_8013C444 && gPlayerInput[playerId].pendingInput && player->lookupLogicTable >= 0 &&
            !(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME) && !(player->flags & PLAYER_FLAG_2000)) {
            player_select_transition(player, FALSE);
        }
    } else if (player->allowTransition && !gRoundOver) {
        if (player->autoTimer != 0 && --player->autoTimer == 0) {
            player_select_transition(player, TRUE);
        } else if (!(player->flags & (PLAYER_FLAG_TRANSITION_GUARD | PLAYER_FLAG_GAMEPLAY_LOCKED)) &&
                   gPlayerInput[playerId].pendingInput && player->lookupLogicTable >= 0 &&
                   !(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME)) {
            player_select_transition(player, FALSE);
        }
    }

    if (player->hitCooldown > 0) {
        player->hitCooldown--;
    }

    if (gPlayerDistance <= D_80080218 && !(player->combatState->flags & CSF_INVINSIBLE) && player->hitCooldown == 0 &&
        oppObj->frameIndex >= oppState->hitboxActiveStart && oppObj->frameIndex <= oppState->hitboxActiveEnd) {

        if (oppState->flags & (CSF_ATTACK_RIGHT_HAND | CSF_ATTACK_LEFT_HAND)) {
            if ((player->combatState->flags & (CSF_400 | CSF_10000 | CSF_JUGGLED)) &&
                obj->modInst->rootTransform.world_matrix.w.y > -100.0f) {
                check_punch_ground(player, opponent);
            } else {
                check_punch_air(player, opponent);
            }
        }

        if (player->hitCooldown == 0 &&
            (oppState->flags & (CSF_ATTACK_RIGHT_FOOT_1 | CSF_ATTACK_LEFT_FOOT | CSF_ATTACK_RIGHT_FOOT_2))) {
            if ((player->combatState->flags & (CSF_400 | CSF_10000 | CSF_JUGGLED)) &&
                obj->modInst->rootTransform.world_matrix.w.y > -100.0f) {
                check_kick_ground(player, opponent);
            } else {
                check_kick_air(player, opponent);
            }
        }
    }

    player->allowTransition = TRUE;
}

/* Concatenate two strings into a destination buffer (str_copy + str_concat). */
void str_join(char *arg0, char *arg1, char *arg2) {
    str_copy(arg0, arg1);
    str_concat(arg0, arg2);
}

/* Parse AI tables from the character .db file: action table, candidate
   table, strategy table, etc.  Then initialise difficulty based on game mode
   and settings. */
void load_ai_tables(CharacterDefinition *arg0, s16 playerId) {
    AssetDB1 *v1;
    AssetDB3 *a2;
    s32 s2;
    s32 i;
    s32 pad;

    gPlayers[playerId].aiActionTable = arg0->unk_30 + (u32) arg0;
    gPlayers[playerId].aiActionIndexMap = arg0->unk_34 + (u32) arg0;

    v1 = arg0->unk_38 + (u32) arg0;
    gPlayers[playerId].numAiCandidates = v1->unk_00;
    gPlayers[playerId].aiCandidateTable = v1->unk_04;
    gPlayers[playerId].aiActionSequenceTable = v1->unk_00 + v1->unk_04; // required to match

    a2 = arg0->unk_3C + (u32) arg0;
    gPlayers[playerId].numAiStrategies = a2->unk_00;
    gPlayers[playerId].aiStrategyIndexMap = a2->unk_04;
    gPlayers[playerId].aiStrategyTable =
        (((a2->unk_00 & 1) + a2->unk_00) & 0xFFFFFFFF) + a2->unk_04; // required to match

    gPlayers[playerId].aiState.aiFlags = AIF_AI_DISABLED;
    gPlayers[playerId].aiState.recentTactics[0] = NULL;
    gPlayers[playerId].aiState.tacticActionsPtr = &sSentinelEmpty;
    gPlayers[playerId].aiState.moveSequence = &sSentinelEmpty;
    gPlayers[playerId].aiState.continueActionFunc = 0;
    gPlayers[playerId].aiState.actionParam = 0;
    gPlayers[playerId].aiState.actionFlags = 0;

    gPlayerInput[playerId].enabled = FALSE;

    if (gPlayMode == PLAY_MODE_30) {
        if (playerId != PLAYER_1) {
            ai_min_difficulty(gPlayers + playerId);
        } else {
            ai_max_difficulty(gPlayers + PLAYER_1);
        }
    } else if (gBattleSettings[playerId].initDifficulty) {
        if (gDifficulty == DIFFICULTY_HARD && gBattleSettings[playerId].aiDifficulty == 0) {
            gBattleSettings[playerId].aiDifficulty = 2;
        }
        s2 = gBattleSettings[playerId].aiDifficulty;

        ai_min_difficulty(gPlayers + playerId);
        gBattleSettings[playerId].initDifficulty = FALSE;
        for (i = 0; i < s2; i++) {
            ai_increase_difficulty(gPlayers + playerId);
        }
    } else {
        switch (gDifficulty) {
            case DIFFICULTY_NORMAL:
            case DIFFICULTY_HARD:
                ai_increase_difficulty(gPlayers + playerId);
                break;
            case DIFFICULTY_EASY:
                switch (func_8001DFE4(playerId)) {
                    case 0:
                        ai_max_difficulty(gPlayers + playerId);
                        break;
                    default:
                        ai_increase_difficulty(gPlayers + playerId);
                        break;
                    case 4:
                    case 7:
                        break;
                }
                break;
        }
    }
}

/* Load character data from a .db file: transition tables, combat states,
   sounds, animations, projectile/barrage tables, and optionally AI tables
   and debug symbols.  Also patches opponent-specific grab animations (GR1 MOV). */
void load_character_data(s16 playerId, s16 characterId) {
    char sp94[20];
    char sp80[20];
    CombatState *combatStateTable;
    s32 *pad3;
    s32 *sp74;
    Player *player;
    ModelInstance *modInst;
    s16 animId;
    Player12 *sp44;
    CharacterDefinition *s3;
    s32 i;
    s32 pad;
    s16 q;
    s16 v03; // sp54?
    s16 pad2;
    s16 sp50;

    player = &gPlayers[playerId];
    modInst = player->obj->modInst;
    sp44 = &gBattleSettings[playerId];
    sp50 = gBattleSettings[1 - playerId].characterId;

    if (sp44->isDummy) {
        str_copy(sp80, "dum.db");
    } else {
        str_join(sp80, D_8004B844[characterId].unk_04->name, ".db");
    }

    s3 = (CharacterDefinition *) gAssets[asset_find(sp80, playerId)].data;
    player->transitionTimingTable = s3->unk_00 + (u32) s3;
    player->transitionRuleTable = pad = s3->transitionTable + 4 + (u32) s3;
    player->logicStateTable = s3->logicStates + (u32) s3;
    player->frameTriggerGroupTable = s3->unk_0C + (u32) s3;
    player->frameOverrides = s3->unk_10 + (u32) s3;

    sp74 = s3->stateTable + (u32) s3;
    if (sp44->isDummy) {
        *sp74 = 0;
    }
    player->combatStateTable = combatStateTable = (u32) s3 + s3->stateTable + 4;

    player->soundTable = pad = s3->soundTable + (u32) s3 + 4;
    pad3 = s3->unk_1C + (u32) s3;
    player->unk_6C = *pad3;

    if (((!player->obj) && (!player->obj)) & 0xFFFFFFFFu) {} // @fake

    player->moveToLogicStateMap = s3->moveToLogicStateMap + (u32) s3;
    player->unk_44 = s3->unk_24 + (u32) s3;
    player->projectileTable = s3->projectileTable + (u32) s3;
    player->barrageTable = s3->barrageTable + (u32) s3;
    player->unk_68 = s3->unk_40 + (u32) s3;

    str_copy(sp94, D_8004B94C[sp50].unk_04);
    str_concat(sp94, ".MOV");
    if ((v03 = asset_find(sp94, CONTEXT_5000 + playerId)) > 0) {
        q = D_8004B94C[sp50].combatStateId;
        animId = combatStateTable[q].animationId;
        modInst->animations[animId] = gAssets[v03].data;
        combatStateTable[q].maxFrame = func_80037394(modInst, animId) - 1;
    }

    str_copy(sp94, D_8004B94C[11 + sp50].unk_04);
    str_concat(sp94, ".MOV");
    if ((v03 = asset_find(sp94, CONTEXT_5000 + playerId)) > 0) {
        q = D_8004B94C[11 + sp50].combatStateId;
        animId = combatStateTable[q].animationId;
        modInst->animations[animId] = gAssets[v03].data;
        if (sp50 != AARON) {
            combatStateTable[q].maxFrame = func_80037394(modInst, animId) - 1;
        }

        q = D_8004B9FC[sp50];
        animId = combatStateTable[q].animationId;
        modInst->animations[animId] = gAssets[v03].data;
        combatStateTable[q].maxFrame = func_80037394(modInst, animId) - 1;
    }

    player->combatStateId = CS_ID_0;

    for (i = 0; i < *sp74; i++, combatStateTable++) {
        if (combatStateTable->maxFrame == -1) {
            combatStateTable->maxFrame = func_80037394(modInst, combatStateTable->animationId) - 1;
        } else if (func_80037394(modInst, combatStateTable->animationId) < combatStateTable->maxFrame) {
            combatStateTable->maxFrame = func_80037394(modInst, combatStateTable->animationId) - 1;
        }

        if (combatStateTable->trailStart == -1 || combatStateTable->trailEnd == -1) {
            combatStateTable->trailStart = combatStateTable->hitboxActiveStart + 3;
            combatStateTable->trailEnd = combatStateTable->hitboxActiveEnd - 1;
        }
    }

    if (sp44->isCpu) {
        load_ai_tables(s3, playerId);
    }

    if (sp44->isDebug) {
        if (sp44->isDummy) {
            str_copy(sp80, "dum.sym");
        } else {
            str_join(sp80, D_8004B844[characterId].unk_04->name, ".sym");
        }
        // TODO wrong structure
        s3 = (CharacterDefinition *) gAssets[asset_find(sp80, playerId)].data;
        player->unk_9A8 = s3->unk_00 + (u32) s3;
        player->unk_9AC = s3->transitionTable + (u32) s3;
        player->unk_9B0 = s3->logicStates + (u32) s3;
        player->unk_9B4 = s3->unk_0C + (u32) s3;
    }
}

/* Remove a Transform node from its parent's child list. */
void transform_unlink(Transform *arg0) {
    Transform *next;
    Transform *prev;

    prev = arg0->parent->firstChild;

    if (prev == arg0) {
        arg0->parent->firstChild = arg0->nextSibling;
        arg0->nextSibling = NULL;
        return;
    }

    next = prev->nextSibling;
    while (arg0 != next) {
        prev = next;
        next = next->nextSibling;
    }

    prev->nextSibling = arg0->nextSibling;
    arg0->nextSibling = NULL;
}

/* Insert two extra transforms into the model hierarchy: headTrack (bone
   selected by D_8004C1D8[characterId]) and bodyTurn (root bone, index 0).
   These are used by aimingTask (func_8003184C) to rotate the character's
   head/body toward a target independently. */
void init_tracking_transforms(Object *obj, s16 playerId, s16 characterId) {
    Transform *s1;
    Transform *sp38;
    Transform *s0;
    NodeAttachment *nodeHierarchy = obj->modInst->nodeAttachments;

    nodeHierarchy[D_8004C1D8[characterId]].x = 0;
    nodeHierarchy[D_8004C1D8[characterId]].y = 0;
    nodeHierarchy[D_8004C1D8[characterId]].z = 0;

    s0 = &obj->modInst->transforms[D_8004C1D8[characterId]];
    s1 = &gPlayers[playerId].headTrack;
    init_transform(s0->parent, s1, -3, -3);
    s1->local_matrix.w.x = s0->local_matrix.w.x;
    s1->local_matrix.w.y = s0->local_matrix.w.y;
    s1->local_matrix.w.z = s0->local_matrix.w.z;
    transform_unlink(s0);
    sp38 = s0->firstChild;
    init_transform(s1, s0, -3, -3);
    s0->firstChild = sp38;

    nodeHierarchy[0].x = 0;
    nodeHierarchy[0].y = 0;
    nodeHierarchy[0].z = 0;

    s0 = &obj->modInst->transforms[0];
    s1 = &gPlayers[playerId].bodyTurn;
    init_transform(s0->parent, s1, -3, -3);
    s1->local_matrix.w.x = s0->local_matrix.w.x;
    s1->local_matrix.w.y = s0->local_matrix.w.y;
    s1->local_matrix.w.z = s0->local_matrix.w.z;
    transform_unlink(s0);
    sp38 = s0->firstChild;
    init_transform(s1, s0, -3, -3);
    s0->firstChild = sp38;

    D_80052D64[playerId] = D_80052D68[playerId] = D_80052D6C[playerId] = D_80052D70[playerId] = D_80052D74[playerId] =
        0;
    D_80052D78[playerId] = 2;
}

/* Asset callback: when loading a GR1 MOV file (opponent grab animation),
   redirect to the opponent character's folder so the correct character-
   specific grab reaction plays. */
void asset_redirect_opponent_grab(Asset *asset) {
    s16 characterId;
    s16 v2;
    u8 sp2B;

    characterId = gBattleSettings[1 - asset->context].characterId;
    sp2B = asset->name[6];
    asset->name[6] = '\0';

    if (str_compare(asset->name, D_8004B94C[characterId].unk_04) != 0) {
        characterId += 11;
        if (str_compare(asset->name, D_8004B94C[characterId].unk_04) != 0) {
            asset->name[0] = '\0';
            asset->flags |= 1;
            return;
        }
    }
    asset->name[6] = sp2B;
    asset_read(asset);
    asset->context += 0x5000;
}

/* Open the file-system folder for a player's assets (models, sprites, etc.)
   and register the opponent-grab redirect callback.  Folder path depends on
   character, player side (1/2), and costume variant (_v/_h). */
void open_player_asset_folder(s16 playerId) {
    char sp38[40];
    char sp2C[12];
    u8 characterId = gBattleSettings[playerId].characterId;

    if (gBattleSettings[playerId].isDummy) {
        str_copy(sp38, "/aaro/dummy");
    } else {
        str_copy(sp2C, D_8004B844[characterId].unk_04->name);
        str_copy(sp38, "/");
        str_concat(sp38, sp2C);
        str_concat(sp38, "/");
        str_concat(sp38, sp2C);
        if (playerId != PLAYER_1) {
            str_concat(sp38, "2");
        } else {
            str_concat(sp38, "1");
        }
        if (gBattleSettings[playerId].assetContext != CONTEXT_0000) {
            str_concat(sp38, "_h");
        } else {
            str_concat(sp38, "_v");
        }
    }

    if (str_compare(sp38, gPlayers[playerId].unk_980)) {
        func_8002630C(playerId);
        str_copy(gPlayers[playerId].unk_980, sp38);
    }
    D_8013C228 = asset_redirect_opponent_grab;
    asset_open_folder(sp38, CONTEXT_0000 + playerId);
}

/* Task callback: flickers a character light's color randomly every 8 frames.
   Used for Demitron/Demonica alternate costumes. */
void light_flicker_random_color(Object *obj) {
    ColorRGBA *sp1C = obj->varObj[0];
    ColorRGBA *sp18 = obj->varObj[1];
    u32 v1;

    if (--obj->vars[2] <= 0) {
        v1 = (guRandom() % 192) + 64;
        sp18->r = sp1C->r * v1 / 256;
        sp18->g = sp1C->g * v1 / 256;
        sp18->b = sp1C->b * v1 / 256;
        obj->vars[2] = 8;
    }
}

/* Task callback: attach Eve's point light to bone 5 (sword hand). */
void eve_light_update(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->obj->modInst->transforms[5].world_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

/* Task callback: attach Morphix's point light to the root transform. */
void morphix_light_update(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->obj->modInst->rootTransform.world_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

/* Spawn character-specific point lights (Eve sword, Morphix root) and set up
   colour flicker for Demitron/Demonica alternate costumes. */
void create_character_lights(u16 playerId, u16 characterId) {
    ColorRGBA sp38[] = { { 0, 200, 0, 0 }, { 200, 0, 0, 0 } };
    ColorRGBA sp30[] = { { 0, 0, 255, 0 }, { 200, 50, 0, 0 } };
    Object *sp2C;

    switch (characterId) {
        case EVE:
            sp2C = create_worker(eve_light_update, OBJ_PRIO_DEFAULT);
            create_light(sp2C, &sp38[playerId]);
            sp2C->varObj[0] = &gPlayers[playerId];
            break;
        case MORPHIX:
            sp2C = create_worker(morphix_light_update, OBJ_PRIO_DEFAULT);
            create_light(sp2C, &sp30[playerId]);
            sp2C->varObj[0] = &gPlayers[playerId];
            break;
        case DEMITRON:
            if (gBattleSettings[playerId].assetContext != CONTEXT_0000) {
                sp2C = create_worker(light_flicker_random_color, OBJ_PRIO_DEFAULT);
                sp2C->varObj[0] = &gBattleDemitronAltLighting.lights[1].color;
                sp2C->varObj[1] = &gBattleDemitronLighting.lights[1].color;
            }
            break;
        case DEMONICA:
            if (gBattleSettings[playerId].assetContext != CONTEXT_0000) {
                sp2C = create_worker(light_flicker_random_color, OBJ_PRIO_DEFAULT);
                sp2C->varObj[0] = &gBattleDemonicaAltLighting.lights[1].color;
                sp2C->varObj[1] = &gBattleDemonicaLighting.lights[1].color;
            }
            break;
    }
}

/* Full player creation: open asset folder, load model/shadow/sprites/effects,
   parse .db tables, create task slots, init hitboxes/trails/tracking, apply
   the opening move, and create character lights.  Called once per player per
   battle start. */
void spawn_player(s16 playerId) {
    Object *obj;
    s16 v00;
    s16 i;
    s16 characterId;
    Vec4i spB4[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 spB0[] = { 0, 0x800 };
    char spA4[12];
    char sp74[48];
    char *str1 = "mod0.k2";
    char *str2 = "spr0.sp3";
    char sp60[12];

    open_player_asset_folder(playerId);

    gPlayers[playerId].playerId = playerId;
    gPlayers[playerId].flags = 0;
    characterId = gPlayers[playerId].characterId = gBattleSettings[playerId].characterId;

    if (gBattleSettings[playerId].isDummy) {
        characterId = AARON;
        str_copy(spA4, "dum.tmd");
    } else {
        str_copy(spA4, D_8004B844[characterId].unk_04->name);
        if (characterId != MORPHIX) {
            if (playerId != PLAYER_1) {
                str_concat(spA4, "2.tmd");
            } else {
                str_concat(spA4, ".tmd");
            }
        } else {
            if (playerId != PLAYER_1) {
                str_concat(spA4, "2.k3");
            } else {
                str_concat(spA4, ".k3");
            }
        }
    }

    obj = gPlayers[playerId].obj =
        create_model_instance_with_properties(&spB4[playerId], spA4, D_8004B844[characterId].unk_04, playerId);
    obj->flags |= OBJ_FLAG_PLAYER;

    if (characterId == MORPHIX && !gBattleSettings[playerId].isDummy) {
        func_8002A890(gPlayers + playerId);
    }

    if (gBattleSettings[playerId].isDummy) {
        str_copy(spA4, "dumshad.k4");
    } else {
        str_copy(spA4, D_8004B844[characterId].unk_04->name);
        spA4[3] = '\0';
        if (playerId != 0) {
            do {
            } while (0);
            str_concat(spA4, "shad2.k4");
        } else {
            str_concat(spA4, "shad.k4");
        }
    }

    create_shadow(obj, spA4, playerId);

    obj->rotation.y = 0xC00 - spB0[playerId];
    obj->fn_render = player_update;
    if (obj->currentTask && obj->currentTask) {} // @fake
    obj->varObj[0] = gPlayers + playerId;

    i = 0;
    str_copy(sp74, str2);
    while (TRUE) {
        v00 = asset_find(sp74, playerId);
        if (v00 >= 0) {
            gPlayers[playerId].effectSprites[i++] = gAssets[v00].aux_data;
        } else {
            break;
        }
        sp74[3]++;
    }

    i = 0;
    str_copy(sp74, str1);
    str_copy(sp60, str1);
    sp60[6] = '5';
    while (TRUE) {
        v00 = asset_find(sp74, playerId);
        if (v00 >= 0) {
            gPlayers[playerId].effectModels[i++] = gAssets[v00].aux_data;
        } else {
            v00 = asset_find(sp60, playerId);
            if (v00 >= 0) {
                gPlayers[playerId].effectModels[i++] = gAssets[v00].aux_data;
            } else {
                break;
            }
        }

        sp74[3]++;
        sp60[3]++;
    }

    load_character_data(playerId, characterId);

    gPlayers[playerId].actionTask = obj->currentTask;
    gPlayers[playerId].animTask = task_add(obj, task_end, TASK_FLAG_ENABLED);
    gPlayers[playerId].audioTask = task_add(obj, player_play_sounds, TASK_FLAG_ENABLED);
    gPlayers[playerId].cameraTask = task_add(obj, task_end, TASK_FLAG_ENABLED);
    gPlayers[playerId].aimingTask = task_add(obj, func_8003184C, TASK_FLAG_ENABLED);
    gPlayers[playerId].behaviorTable = gBehaviorTable;

    D_80080214 = D_8004A730[gBattleSettings[PLAYER_1].characterId] + D_8004A730[gBattleSettings[PLAYER_2].characterId];
    D_80080218 = D_8004A748[gBattleSettings[PLAYER_1].characterId] + D_8004A748[gBattleSettings[PLAYER_2].characterId];
    gPlayerAngle = 0x800;
    gPlayerDistance = 1600;

    gPlayerObjects[playerId] = obj;
    gTransitionReplayBuffer.headIndex = gTransitionReplayBuffer.tailIndex = 0;
    gTransitionReplayBuffer.startFrameCounter = gFrameCounter;

    gReplayDisabled = TRUE;

    if (gBattleSettings[playerId].isCpu) {
        player_apply_move(gPlayers + playerId, MOVE_ID_AI_OPENING_MOVE, 0);
    } else {
        player_apply_move(gPlayers + playerId, MOVE_ID_IDLE_068, 0);
    }

    if (playerId != 0) {
        gReplayDisabled = FALSE;
    }

    gPlayers[playerId].combatState = gPlayers[playerId].combatStateTable + gPlayers[playerId].combatStateId;
    init_player_hitboxes(&gPlayers[playerId], D_8004B844[characterId].hitZonesSetup);

    obj->playerHp = gBattleSettings[playerId].initialHp;
    init_tracking_transforms(obj, playerId, characterId);

    if (playerId == PLAYER_1) {
        gPlayerInput[playerId].mirrored = TRUE;
    }

    motion_trail_init(&gPlayers[playerId].rightHandTrail, obj->modInst,
                      &obj->modInst->transforms[D_8004B844[characterId].hitZonesSetup->rightHandId].world_matrix,
                      &gPlayers[playerId].hitZones.rightPunchStrike.world_matrix, &obj->pos,
                      &D_8004B844[characterId].trailColors[playerId]);

    if (D_8004B844[characterId].hitZonesSetup->leftPunchBoneId >= 0) {
        motion_trail_init(&gPlayers[playerId].leftHandTrail, obj->modInst,
                          &obj->modInst->transforms[D_8004B844[characterId].hitZonesSetup->leftHandId].world_matrix,
                          &gPlayers[playerId].hitZones.leftPunchStrike.world_matrix, &obj->pos,
                          &D_8004B844[characterId].trailColors[playerId]);
        gPlayers[playerId].hasLeftHandTrail = TRUE;
    } else {
        gPlayers[playerId].hasLeftHandTrail = FALSE;
    }

    motion_trail_init(&gPlayers[playerId].leftLegTrail, obj->modInst,
                      &obj->modInst->transforms[D_8004B844[characterId].hitZonesSetup->leftCalfBoneId].world_matrix,
                      &obj->modInst->transforms[D_8004B844[characterId].hitZonesSetup->leftFootBoneId].world_matrix,
                      &obj->pos, &D_8004B844[characterId].trailColors[playerId]);
    motion_trail_init(&gPlayers[playerId].rightLegTrail, obj->modInst,
                      &obj->modInst->transforms[D_8004B844[characterId].hitZonesSetup->rightCalfBoneId].world_matrix,
                      &obj->modInst->transforms[D_8004B844[characterId].hitZonesSetup->rightFootBoneId].world_matrix,
                      &obj->pos, &D_8004B844[characterId].trailColors[playerId]);

    gPlayers[playerId].allowTransition = FALSE;

    if (gPlayMode == PLAY_MODE_PRACTICE) {
        if (playerId == gPracticingPlayer) {
            practice_init_hud();
        } else {
            gPlayers[playerId].flags |= PLAYER_FLAG_200000;
        }
    }

    create_character_lights(playerId, characterId);
}

/* Minimal replay-only respawn: repositions the existing object, resets tasks,
   and applies the opening move.  Skips asset loading, hitbox init, trails,
   and tracking since those were done at battle start. */
void replay_respawn_player(s16 playerId) {
    Object *obj = gPlayers[playerId].obj;
    s16 characterId;
    Vec4i spB4[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 spB0[] = { 0, 0x800 };
    s32 zero = 0;

    gPlayers[playerId].playerId = playerId;
    gPlayers[playerId].flags = 0;
    gPlayers[playerId].aiState.aiFlags = 0;
    gPlayers[playerId].characterId = characterId = gBattleSettings[playerId].characterId;

    obj->rotation.y = 0xC00 - spB0[playerId];
    obj->pos.x = spB4[playerId].x;
    obj->pos.y = spB4[playerId].y;
    obj->pos.z = spB4[playerId].z;
    obj->fn_render = player_update;
    obj->varObj[0] = gPlayers + playerId;

    gPlayers[playerId].actionTask->startDelay = 0;
    gPlayers[playerId].actionTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].actionTask->func = task_end;
    gPlayers[playerId].actionTask->stackPos = zero; // required to match
    gPlayers[playerId].animTask->startDelay = 0;
    gPlayers[playerId].animTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].animTask->func = task_end;
    gPlayers[playerId].animTask->stackPos = 0;
    gPlayers[playerId].audioTask->startDelay = 0;
    gPlayers[playerId].audioTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].audioTask->func = player_play_sounds;
    gPlayers[playerId].audioTask->stackPos = 0;
    gPlayers[playerId].cameraTask->startDelay = 0;
    gPlayers[playerId].cameraTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].cameraTask->func = task_end;
    gPlayers[playerId].cameraTask->stackPos = 0;
    gPlayers[playerId].aimingTask->startDelay = 0;
    gPlayers[playerId].aimingTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].aimingTask->func = func_8003184C;
    gPlayers[playerId].aimingTask->stackPos = 0;

    D_80080214 = D_8004A730[gBattleSettings[PLAYER_1].characterId] + D_8004A730[gBattleSettings[PLAYER_2].characterId];
    D_80080218 = D_8004A748[gBattleSettings[PLAYER_1].characterId] + D_8004A748[gBattleSettings[PLAYER_2].characterId];
    gPlayerAngle = 0x800;
    gTransitionReplayBuffer.headIndex = gTransitionReplayBuffer.tailIndex = 0;
    gReplayDisabled = TRUE;
    gTransitionReplayBuffer.startFrameCounter = gFrameCounter;
    obj->rotation.y = 0xC00 - spB0[playerId];
    gPlayerDistance = 1600;
    obj->flags = (obj->flags & OBJ_FLAG_TRANSPARENT) | OBJ_FLAG_MODEL;
    gTransitionReplayBuffer.headIndex = gTransitionReplayBuffer.tailIndex = 0;
    gReplayDisabled = TRUE;

    if (gBattleSettings[playerId].isCpu) {
        player_apply_move(gPlayers + playerId, MOVE_ID_AI_OPENING_MOVE, 0);
    } else {
        player_apply_move(gPlayers + playerId, MOVE_ID_IDLE_068, 0);
    }

    if (playerId != PLAYER_1) {
        gReplayDisabled = FALSE;
    }

    gPlayers[playerId].combatState = gPlayers[playerId].combatStateTable + gPlayers[playerId].combatStateId;
    obj->playerHp = gBattleSettings[playerId].initialHp;

    if (playerId == PLAYER_1) {
        gPlayerInput[playerId].mirrored = TRUE;
    }

    gPlayers[playerId].allowTransition = FALSE;
}

/* Core state machine transition: resolve a logicState → transitionRule →
   behavior → combatStateId, install the appropriate animation/action tasks,
   apply frame-trigger overrides, handle cutscene camera, update all player
   bookkeeping, and log the transition for replay. */
u8 player_make_transition(Player *player, u8 arg1, u16 logicState) {
    u16 behaviorId;
    u16 sp4C;
    ObjectTask *animTask;
    FrameTriggerOverride *overrideRule;
    u16 overrideCount;
    Behavior *behavior;
    s32 pad1;
    s32 *animTaskParams;
    FrameTriggerGroup *curStateGroup;
    CombatState *nextState;
    u16 transitionId;
    TransitionRule *transitionRule;
    s16 targetStateId;
    u16 i;

    transitionId = player->logicStateTable[logicState];
    transitionRule = &player->transitionRuleTable[transitionId];
    sp4C = transitionRule->timingIndex;
    behaviorId = transitionRule->behaviorId;
    // clang-format off
    targetStateId = transitionRule->targetStateId; \
    if (targetStateId == player->combatStateId && !arg1) {
        targetStateId = -1;
    }
    // clang-format on

    behavior = player->behaviorTable + behaviorId;
    curStateGroup = player->frameTriggerGroupTable + player->combatStateId;

    overrideRule = curStateGroup->firstOverride + player->frameOverrides;
    overrideCount = curStateGroup->overrideCount;

    if (behavior->transitionAllowedFunc != NULL && !behavior->transitionAllowedFunc(player->obj)) {
        return FALSE;
    }

    player->previousTransition = player->transition;
    player->transition = transitionRule;

    animTask = player->animTask;
    animTaskParams = &animTask->params;
    animTaskParams[2] = 0;

    for (i = 0; i < overrideCount; overrideRule++, i++) {
        if (overrideRule->matchTarget == targetStateId) {
            if (player->obj->frameIndex < overrideRule->triggerFrame) {
                animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
                animTask->triggerAt = overrideRule->triggerFrame;
                animTask->triggerSlot.func = anim_apply_diverted_combat_state;
                animTask->triggerSlot.flags = TASK_FLAG_ENABLED;

                player->actionTask->func = task_end;
                player->actionTask->startDelay = 0;
                player->actionTask->flags = TASK_FLAG_ENABLED;

                animTaskParams[2] = overrideRule->startFrame;
                animTaskParams[3] = overrideRule->redirectState;
                animTaskParams[4] = behavior->actionFunc;
            } else {
                animTask->func = anim_apply_diverted_combat_state;
                animTask->startDelay = 0;
                animTask->flags = TASK_FLAG_ENABLED;

                player->actionTask->func = task_end;
                player->actionTask->startDelay = 0;
                player->actionTask->flags = TASK_FLAG_ENABLED;

                animTaskParams[2] = overrideRule->startFrame;
                animTaskParams[3] = overrideRule->redirectState;
                animTaskParams[4] = behavior->actionFunc;

                player->aiState.aiFlags |= AIF_AI_DISABLED;
            }
            goto label;
        }
    }

    player->actionTask->func = behavior->actionFunc;
    player->actionTask->startDelay = 0;
    player->actionTask->flags = TASK_FLAG_ENABLED;
    if (targetStateId >= 0) {
        animTask->func = anim_change_combat_state;
        animTask->startDelay = 0;
        animTask->flags = TASK_FLAG_ENABLED;
    }

label:

    if (targetStateId >= 0) {
        animTaskParams[1] = targetStateId;
        animTaskParams[0] = behavior->animFunc;
        player->previousCombatStateId = player->combatStateId;
        player->combatStateId = targetStateId;

        nextState = player->combatStateTable + targetStateId;
        if (nextState->cutsceneId >= 0 && nextState->custsceneDelay == -1) {
            camera_save_state();
            camera_set_animation(
                gCamera, player->obj->modInst->animations[player->combatStateTable[nextState->cutsceneId].animationId]);
            gCamera->currentTask->func = camera_cutscene_playback;
            gCamera->currentTask->startDelay = 0;
            gCamera->currentTask->flags = TASK_FLAG_ENABLED;
        }
    } else {
        animTask->func = behavior->animFunc;
        animTask->flags = TASK_FLAG_ENABLED;
        animTask->startDelay = 0;
    }

    player->previousBehaviorId = player->behaviorId;
    player->previousFlags = player->flags;
    player->behaviorId = behaviorId;
    player->currentTiming = player->transitionTimingTable + sp4C;

    player->flags = behavior->newFlags | (player->flags & behavior->preserveFlags);
    player->behavior = behavior;
    player->transitionId = transitionId;
    player->currentLogicState = logicState;

    log_transition_state(player);

    if (gPlayers[1 - player->playerId].hitCooldown < 3) {
        gPlayers[1 - player->playerId].hitCooldown = 3;
    }

    player->transitionTimeStamp = gFrameCounter;
    if (player->currentTiming->actionDelay != 0) {
        player->actionTask->startDelay = player->currentTiming->actionDelay;
    }
    player->autoTimer = player->currentTiming->autoDelay;
    player->obj->velocity.z = player->currentTiming->initVelZ;
    player->obj->flags &= ~OBJ_FLAG_800;
    player->lookupLogicTable = player->logicStateTable[logicState + 1];

    return TRUE;
}

/* Look up a moveId in the move-to-logic-state map and execute the transition.
   Used to initiate moves from code (opening move, cutscenes, etc.). */
u8 player_apply_move(Player *player, s16 moveId, u8 arg2) {
    s16 logicState;

    logicState = player->moveToLogicStateMap[moveId];
    player->animTask->flags &= ~TASK_FLAG_TRIGGER_FRAME;
    return player_make_transition(player, arg2, logicState);
}

/* Force a move onto the player: if CPU, use the AI override; otherwise
   delegate to player_apply_move. */
u8 player_force_move(Player *player, s16 moveId, u8 arg2) {
    if (gBattleSettings[player->playerId].isCpu) {
        player->autoTimer = 0;
        return ai_force_move(player, moveId);
    } else {
        return player_apply_move(player, moveId, arg2);
    }
}

/*
 * Transition selection for human-controlled players.  Called every frame
 * when the player is in a state that allows input.
 *
 * lookupLogicTable is a flat array of (ruleId, nextLookup) pairs, terminated
 * by a negative ruleId.  E.g.:
 *   { MOVE_PUNCH, next_A }, { MOVE_KICK, next_B }, ..., { -1, ignore }
 *
 * On a successful transition, player->lookupLogicTable is advanced to the
 * stored nextLookup so the search resumes from a new sub-table for the next
 * frame (effectively a state-machine within the state machine).
 *
 * Transition flags act along two independent axes:
 *
 *   Timing:   NOW (0x1)  — fire immediately
 *             LATER (0x4) — defer to the end of current animation
 *
 *   Hold:     HELD (0x20) — button must be held until the last frame
 *             (no flag)   — one press is enough, the system remembers
 *
 * These combine into three practical modes:
 *   NOW              — immediate (one-press or held, doesn't matter)
 *   LATER            — deferred, one press is enough
 *   LATER | HELD     — deferred, must hold button until the end
 *
 * Checks are performed in priority order for each candidate pair:
 *
 *   1. FALLBACK (0x2) — No input required; stored as a last-resort move.
 *      Only used if nothing else matched during the entire walk (handled
 *      after the loop).  Moves with FACING|BEHIND are excluded from fallback
 *      if the player is already facing the opponent (they'd be redundant).
 *
 *   2. TIMEOUT (0x8) — autoTransitionTimer reached zero; force this
 *      transition regardless of input.  Still calls player_make_transition()
 *      which may decline (e.g. permission func blocks it).
 *
 *   3. FACING | BEHIND — Turn-around: player is facing away from opponent
 *      and presses any button; execute the move (which turns them to face).
 *      The button requirement can be: any button (requiredButtons == 0),
 *      a specific combo (masked_buttons == requiredButtons), or "not
 *      neutral" (0xFFFF).  Two sub-modes:
 *        a) LATER — defer the turn to the last frame via trigger slot.
 *        b) (no LATER) — turn right now.
 *
 *   4. Button match — requiredButtons matched the masked input.  Gate
 *      condition: must be NOW, or LATER while not inside a diverted
 *      animation (combatState must equal combatStateTable + combatStateId).
 *      Sub-checks within this group (applied in order):
 *        a) HELD — only allowed on boundary frames: the last frame of
 *           forward animation (maxFrame), or the first frame of a reversed
 *           animation (minFrame).  This is the "hold to the end" variant.
 *        b) LATER without HELD — schedule a trigger slot at maxFrame-1.
 *           One press is enough; it fires automatically.
 *        c) TIMED — must be within unk_06 frames since last transition.
 *        d) (no special flags) — make transition now.
 *
 *   5. If no candidate matched and allowFallback is set, apply the stored
 *      FALLBACK transition (only used on timeout-driven calls, not on
 *      initial pendingInput).
 *
 * Manages gReplayDisabled (disabled during TIMEOUT and FALLBACK to prevent
 * replay desync), and pendingInput to signal whether input is still buffered.
 *
 * When PLAYER_FLAG_ACTION is set, the previous frame's buttons are used
 * instead of the current frame's — prevents input from being consumed
 * by a just-performed transition.
 */
u8 player_select_transition(Player *player, u8 allowFallback) {
    ObjectTask *animTask;
    void *fallbackMove;
    TransitionRule *possibleMove;
    TransitionRule *transitionRuleTable;
    s16 fallbackIndex;
    s16 entryIndex;
    s16 *logicStates;
    s32 pad[2];
    s32 elapsedFrames;
    u16 moveFlags;
    u16 masked_buttons;
    s32 pad2[2];
    u16 buttons;

    entryIndex = player->lookupLogicTable;
    fallbackMove = NULL;
    transitionRuleTable = player->transitionRuleTable;
    logicStates = player->logicStateTable;
    elapsedFrames = gFrameCounter - player->transitionTimeStamp;

    if (gRoundOver) {
        buttons = 0;
    } else if (player->flags & PLAYER_FLAG_ACTION) {
        // previous frame's buttons — the current frame's input was
        // already consumed by a just-performed transition
        buttons = gPlayerInput[player->playerId].fullState;
    } else {
        buttons = gPlayerInput[player->playerId].buttons;
    }

    // walk the (ruleId, nextLookup) pairs until a negative terminator
    while (logicStates[entryIndex] >= 0) {
        possibleMove = transitionRuleTable + logicStates[entryIndex];
        moveFlags = possibleMove->flags;
        masked_buttons = buttons & possibleMove->button_mask;

        if (moveFlags & TRANSITION_FLAG_DEFAULT) {
            // fallback: remember this move as a last resort.  Skip if it
            // has FACING and the player is already facing the opponent
            // (the turn-around logic handles it; storing it as fallback
            // would be redundant).
            if ((moveFlags & TRANSITION_FLAG_FACING) &&
                (!(moveFlags & TRANSITION_FLAG_BEHIND) || !(player->flags & PLAYER_FLAG_NOT_FACING_OPP))) {
                entryIndex += 2;
                continue;
            } else {
                fallbackIndex = entryIndex;
                fallbackMove = possibleMove;
                entryIndex += 2;
                continue;
            }
        }

        // timeout: autoTransitionTimer expired — force this transition.
        // Used for automatic sequences (e.g. wakeup, combo follow-ups
        // driven by autoDelay).
        if ((moveFlags & TRANSITION_FLAG_TIMEOUT) && player->autoTimer <= 0) {
            gPlayerInput[player->playerId].pendingInput = FALSE;
            gReplayDisabled = TRUE;
            if (player_make_transition(player, TRUE, entryIndex)) {
                gReplayDisabled = FALSE;
                return TRUE;
            }
            gReplayDisabled = FALSE;
            entryIndex += 2;
            continue;
        }

        // turn-around: player faces away from opponent and presses a
        // direction button.  FACING|BEHIND marks moves that can reverse
        // the character's facing direction.
        if (buttons && (moveFlags & TRANSITION_FLAG_FACING) && (moveFlags & TRANSITION_FLAG_BEHIND) &&
            (player->flags & PLAYER_FLAG_NOT_FACING_OPP)) {
            if (possibleMove->requiredButtons == 0 ||
                (possibleMove->requiredButtons != 0 && masked_buttons == possibleMove->requiredButtons) ||
                (possibleMove->requiredButtons == 0xFFFF && masked_buttons != 0)) {

                if ((moveFlags & TRANSITION_FLAG_LATER) &&
                    player->combatState == player->combatStateTable + player->combatStateId &&
                    player->combatState->maxFrame != player->obj->frameIndex &&
                    !(player->flags & (PLAYER_FLAG_REVERSE | PLAYER_FLAG_REVERSE_2))) {
                    // defer turn-around to the last frame of current animation
                    animTask = player->animTask;
                    animTask->params[0] = entryIndex;
                    animTask->params[1] = possibleMove;
                    animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
                    animTask->triggerAt = player->combatState->maxFrame - 1;
                    animTask->triggerSlot.func = anim_apply_deferred_transition;
                    animTask->triggerSlot.flags = TASK_FLAG_PREEMPT | TASK_FLAG_ENABLED;
                    return TRUE;
                }

                if (player_make_transition(player, TRUE, entryIndex)) {
                    gPlayerInput[player->playerId].pendingInput = TRUE;
                    return TRUE;
                }
                entryIndex += 2;
                continue;
            }
        }

        // button-match: requiredButtons must match the masked input
        // Gate condition: NOW fires immediately; LATER only fires when
        // not inside a diverted animation (combatState must be in-sync
        // with combatStateId — see anim_apply_diverted_combat_state).
        if (possibleMove->requiredButtons == masked_buttons &&
            ((moveFlags & TRANSITION_FLAG_IMMEDIATE) ||
             ((moveFlags & TRANSITION_FLAG_LATER) &&
              player->combatState == player->combatStateTable + player->combatStateId))) {

            gPlayerInput[player->playerId].pendingInput = FALSE;

            // HELD: button must be held to the end — only fire on the
            // first or last frame of the combat state animation.
            if (moveFlags & TRANSITION_FLAG_HELD) {
                if (player->combatState->maxFrame != player->obj->frameIndex &&
                    (!(player->flags & (PLAYER_FLAG_REVERSE | PLAYER_FLAG_REVERSE_2)) ||
                     player->combatState->minFrame != player->obj->frameIndex)) {
                    entryIndex += 2;
                    continue;
                }
                if (player_make_transition(player, TRUE, entryIndex)) {
                    return TRUE;
                } else {
                    entryIndex += 2;
                    continue;
                }
            }

            // LATER without HELD: one press is enough — schedule the
            // transition on the last frame via a trigger slot.  It will
            // fire even if the player releases the button.
            if ((moveFlags & TRANSITION_FLAG_LATER) && player->combatState->maxFrame != player->obj->frameIndex &&
                !(player->flags & (PLAYER_FLAG_REVERSE | PLAYER_FLAG_REVERSE_2))) {
                animTask = player->animTask;
                animTask->params[0] = entryIndex;
                animTask->params[1] = possibleMove;
                animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
                animTask->triggerAt = player->combatState->maxFrame - 1;
                animTask->triggerSlot.func = anim_apply_deferred_transition;
                animTask->triggerSlot.flags = TASK_FLAG_PREEMPT | TASK_FLAG_ENABLED;
                return TRUE;
            }

            // timed: transition must occur within a fixed window (elapsed
            // <= timing->unk_06).  Used for chains with tight timing
            // windows where the button must be pressed promptly.
            if ((moveFlags & TRANSITION_FLAG_TIMED)) {
                if (elapsedFrames <= player->transitionTimingTable[possibleMove->timingIndex].timeWindow) {
                    if (player_make_transition(player, TRUE, entryIndex)) {
                        return TRUE;
                    } else {
                        entryIndex += 2;
                        continue;
                    }
                } else {
                    entryIndex += 2;
                    continue;
                }
            }

            // immediate match with no special flags
            if (player_make_transition(player, TRUE, entryIndex)) {
                return TRUE;
            }
        }

        entryIndex += 2;
    }

    /* No candidate matched: apply the stored fallback transition.
       allowFallback distinguishes timeout-driven calls (TRUE, from
       player_update when autoTransitionTimer hits 0) from the initial
       pendingInput-driven call (FALSE, right after a button press).
       Fallback is only used on timeout to give the player a default
       move (usually idle / crouch idle) when nothing else fits. */
    if (fallbackMove != NULL && allowFallback) {
        gPlayerInput[player->playerId].pendingInput = FALSE;
        gReplayDisabled = TRUE;
        if (player_make_transition(player, TRUE, fallbackIndex)) {
            player->lookupLogicTable = logicStates[fallbackIndex + 1];
            gReplayDisabled = FALSE;
            return TRUE;
        }
        gReplayDisabled = FALSE;
    }

    return FALSE;
}

/* Transition selection for AI: simplified version that just picks the first
   fallback transition from the lookup chain (the AI module has already
   decided which move group is active). */
u8 ai_select_transition(Player *player) {
    s16 nextLogicState;
    u16 transitionFlags;
    TransitionRule *t2;
    TransitionRule *transitionTable;
    TransitionRule *possibleTransition;
    s16 sp26;
    s16 *logicStates;

    nextLogicState = player->lookupLogicTable;
    transitionTable = player->transitionRuleTable;
    logicStates = player->logicStateTable;
    t2 = NULL;

    while (logicStates[nextLogicState] >= 0) {
        possibleTransition = transitionTable + logicStates[nextLogicState];
        transitionFlags = possibleTransition->flags;
        if (transitionFlags & TRANSITION_FLAG_DEFAULT) {
            if (((transitionFlags & TRANSITION_FLAG_FACING) &&
                 (!(transitionFlags & TRANSITION_FLAG_BEHIND) || !(player->flags & PLAYER_FLAG_NOT_FACING_OPP)))) {
                nextLogicState += 2;
                continue;
            }
            t2 = possibleTransition;
            sp26 = nextLogicState;
            break;
        }
        nextLogicState += 2;
    }

    if (t2 != NULL) {
        gReplayDisabled = TRUE;
        if (player_make_transition(player, TRUE, sp26)) {
            player->lookupLogicTable = logicStates[sp26 + 1];
            gReplayDisabled = FALSE;
            return TRUE;
        }
        gReplayDisabled = FALSE;
    }

    return FALSE;
}
