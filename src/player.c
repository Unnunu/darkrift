#include "common.h"
#include "task.h"
#include "camera.h"

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

extern s16 D_8004A730[];
extern s16 D_8004A748[];
extern GlobalLighting D_8004B644;
extern GlobalLighting D_8004B664;
extern GlobalLighting D_8004B764;
extern GlobalLighting D_8004B784;
extern UnkQwe D_8004B94C[];
extern Behavior D_8004C1E8[];

extern s32 D_80080218;
extern TransitionRingBuffer D_80080238;

/* .bss */
s16 gPlayMode;
s16 gPreviousPlayMode;
u16 D_80080234;
u16 D_80080236;
TransitionRingBuffer D_80080238;

void hitbox_render_init(PlayerHitbox *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4,
                        ColorRGBA *arg5);

void create_player_obj(s16 playerId);
void func_80003C04_unused(Object *obj);

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

extern s16 D_8004B9FC[];

#ifdef NON_MATCHING
void func_800035D0(Player *player) {
    TransitionSnapshot *a1;
    u16 t8;
    u16 a2;
    Object *v0;
    s32 v1;
    s32 nv;
    s32 temp;

    v0 = player->obj;

    if (D_80080236 || gRoundOver) {
        return;
    }
    v1 = D_80080238.tailIndex;
    a1 = D_80080238.unk_00 + v1;
    a1->currentLogicState = player->currentLogicState;
    a1->playerId = player->playerId;
    a1->delayUntilNext = 255;

    t8 = 1 - player->playerId;
    a2 = player->playerId;
    a1->playerHp[a2] = v0->playerHp;
    a1->playerHp[t8] = gPlayers[t8].obj->playerHp;

    nv = D_80080238.tailIndex;
    D_80080238.unk_00[((nv - 1) & 0x1FF)].delayUntilNext = gFrameCounter - D_80080238.lastFrameCounter;

    nv = (nv + 1) & 0x1FF;
    D_80080238.tailIndex = nv;
    D_80080238.lastFrameCounter = gFrameCounter;

    if (nv == D_80080238.headIndex) {
        D_80080234 = 1;
        D_80080238.headIndex = (D_80080238.headIndex + 1) & 0x1FF;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/player/func_800035D0.s")
void func_800035D0(Player *player);
#endif

void func_800036E8(Object *obj) {
    obj->flags |= OBJ_FLAG_DELETE;
    D_80080234 = 1;
}

void func_80003704(Object *obj) {
    if (gPlayers[1 - D_8013C24C].obj->playerHp <= 0 || --obj->vars[0] <= 0) {
        obj->currentTask->start_delay = 55;
        obj->currentTask->func = func_800036E8;
    }
}

#ifdef NON_MATCHING
void func_80003780(Object *obj) {
    s32 s0;
    TransitionSnapshot *s1;
    s32 s3;
    s16 v0;
    s32 temp;
    Player *s2;

    while (TRUE) {
        s0 = D_80080238.headIndex;
        s1 = D_80080238.unk_00 + s0;
        s3 = s1->playerId;

        gPlayers[s3].flags |= PLAYER_FLAG_800000;
        player_make_transition(gPlayers + s3, TRUE, s1->currentLogicState);
        v0 = s1->playerHp[s3];
        gPlayers[s3].obj->playerHp = v0;
        if (v0 == 0) {
            gGlobalFlags |= GAME_FLAG_BATTLE_FINISHED;
        }

        if (s1->delayUntilNext == 255) {
            break;
        }

        s0++;
        D_80080238.headIndex = s0 & ~0x200;

        temp = s1->delayUntilNext;

        if (obj && obj && obj) {} // @fake

        if (temp != 0) {
            obj->currentTask->start_delay = temp - 1;
            return;
        }
    }

    if (s1) {} // @fake
    obj->currentTask->func = func_80003704;
    obj->vars[0] = 260;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/player/func_80003780.s")
void func_80003780(Object *obj);
#endif

void func_800038C8(Object *obj) {
    task_execute(obj);

    if (gPlayerInput[D_8013C24C].buttons & INP_START) {
        obj->flags |= OBJ_FLAG_DELETE;
        D_80080234 = 1;
        D_8013C23C->currentTask->start_delay = 0;
        D_8013C23C->currentTask->func = func_800177C0;
        gPlayerInput[D_8013C24C].pendingInput = FALSE;
    }
}

s32 func_80003974_unused(void *arg0) {
    s32 s3;
    Object *v0;
    u32 i;
    s32 temp;

    s3 = gFrameCounter - D_80080238.startFrameCounter;

    D_80080238.headIndex = 0;
    gReplayActive = 1;
    gPlayers[PLAYER_1].combatStateId = 0;
    gPlayers[PLAYER_2].combatStateId = 0;

    create_player_obj(PLAYER_1);
    create_player_obj(PLAYER_2);
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
    camera_orbit_init(gCamera);
    gCamera->currentTask->func = camera_battle_update;
    gCamera->currentTask->start_delay = 0;
    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -400;
    sCutsceneAnimDone = FALSE;

    temp = guRandom() % 2;

    if (temp) {}

    v0 = create_worker(func_800038C8, -0x7001 + temp * 0);
    v0->currentTask->func = func_80003780;
    v0->currentTask->start_delay = 0;
    v0->currentTask->flags = TASK_FLAG_ENABLED;

    D_8008012C |= GFX_FLAG_1;
    gGlobalFlags &= ~GAME_FLAG_BATTLE_FINISHED;

    if (s3 > 960) {
        s3 -= 960;
        for (i = 0; i < s3; i++) {
            func_80003C04_unused(gPlayers[PLAYER_1].obj);
            func_80003C04_unused(gPlayers[PLAYER_2].obj);
            func_800038C8(v0);
        }

        camera_orbit_update(gCamera, TRUE);
    }

    return 0;
}

s32 func_80003BB4_unused(void) {
    s32 diff = gFrameCounter - D_80080238.startFrameCounter;

    if (diff < 60) {
        return FALSE;
    } else {
        set_post_render_hook(func_80003974_unused, NULL);
        return TRUE;
    }
}

void func_80003C04_unused(Object *obj) {
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
        if (player->autoTransitionTimer != 0 && --player->autoTransitionTimer == 0) {
            player_select_transition(player, TRUE);
        } else if (!(player->flags & (PLAYER_FLAG_TRANSITION_LOCKED | PLAYER_FLAG_100000)) &&
                   gPlayerInput[playerId].pendingInput && player->lookupLogicTable >= 0 &&
                   !(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME)) {
            player_select_transition(player, FALSE);
        }
    }

    player->allowTransition = TRUE;
}

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
    u8 sp2E;

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

    model_update(obj);

    if (player_check_func_2(obj)) {
        player->flags |= PLAYER_FLAG_NOT_FACING_OPP;
    } else {
        player->flags &= ~PLAYER_FLAG_NOT_FACING_OPP;
    }

    sp2E = (currentState->damage != 0) && (obj->frameIndex >= currentState->bodyHitboxStart) &&
           (obj->frameIndex < currentState->bodyHitboxEnd);

    hitbox_render_update(&player->unk_DE8, (currentState->flags & CSF_40) && sp2E);
    if (player->unk_5F4A) {
        hitbox_render_update(&player->unk_2240, (currentState->flags & CSF_2000) && sp2E);
    }
    hitbox_render_update(&player->unk_3698, (currentState->flags & CSF_800) && sp2E);
    hitbox_render_update(&player->unk_4AF0, (currentState->flags & (CSF_20 | CSF_1000)) && sp2E);

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

    if (gBattleSettings[playerId].isCpu && !gRoundOver && !(player->flags & PLAYER_FLAG_100000)) {
        if (!(player->aiState.aiFlags & AIF_20000)) {
            ai_update(player);
        }
        if (D_8013C444 && gPlayerInput[playerId].pendingInput && player->lookupLogicTable >= 0 &&
            !(player->animTask->flags & TASK_FLAG_TRIGGER_FRAME) && !(player->flags & PLAYER_FLAG_2000)) {
            player_select_transition(player, FALSE);
        }
    } else if (player->allowTransition && !gRoundOver) {
        if (player->autoTransitionTimer != 0 && --player->autoTransitionTimer == 0) {
            player_select_transition(player, TRUE);
        } else if (!(player->flags & (PLAYER_FLAG_TRANSITION_LOCKED | PLAYER_FLAG_100000)) &&
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

        if (oppState->flags & (CSF_40 | CSF_2000)) {
            if ((player->combatState->flags & (CSF_400 | CSF_10000 | CSF_JUGGLED)) &&
                obj->modInst->rootTransform.world_matrix.w.y > -100.0f) {
                check_ground_hit_1(player, opponent);
            } else {
                check_air_hit_1(player, opponent);
            }
        }

        if (player->hitCooldown == 0 && (oppState->flags & (CSF_20 | CSF_800 | CSF_1000))) {
            if ((player->combatState->flags & (CSF_400 | CSF_10000 | CSF_JUGGLED)) &&
                obj->modInst->rootTransform.world_matrix.w.y > -100.0f) {
                check_ground_hit_2(player, opponent);
            } else {
                check_air_hit_2(player, opponent);
            }
        }
    }

    player->allowTransition = TRUE;
}

void func_80004304(char *arg0, char *arg1, char *arg2) {
    str_copy(arg0, arg1);
    str_concat(arg0, arg2);
}

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

s16 D_80049390 = -1;
s16 D_80049394 = -1;

void ai_set_temp_max_difficulty(Player *);
void ai_increase_difficulty(Player *);
s32 func_8001DFE4(s32 arg0);

void func_80004334(CharacterDefinition *arg0, s16 playerId) {
    AssetDB1 *v1;
    AssetDB3 *a2;
    s32 s2;
    s32 i;
    s32 pad;

    gPlayers[playerId].aiActionTable = arg0->unk_30 + (u32) arg0;
    gPlayers[playerId].aiActionIndexMap = arg0->unk_34 + (u32) arg0;

    v1 = arg0->unk_38 + (u32) arg0;
    gPlayers[playerId].unk_DB8 = v1->unk_00;
    gPlayers[playerId].aiCandidateTable = v1->unk_04;
    gPlayers[playerId].aiSequenceTable = v1->unk_00 + v1->unk_04; // required to match

    a2 = arg0->unk_3C + (u32) arg0;
    gPlayers[playerId].unk_DBA = a2->unk_00;
    gPlayers[playerId].aiResponseIndexMap = a2->unk_04;
    gPlayers[playerId].aiResponseTable =
        (((a2->unk_00 & 1) + a2->unk_00) & 0xFFFFFFFF) + a2->unk_04; // required to match

    gPlayers[playerId].aiState.aiFlags = AIF_20000;
    gPlayers[playerId].aiState.recentActions[0] = NULL;
    gPlayers[playerId].aiState.sequencePtr = &D_80049394;
    gPlayers[playerId].aiState.actionPtr = &D_80049394;
    gPlayers[playerId].aiState.stateCallback = 0;
    gPlayers[playerId].aiState.actionParam = 0;
    gPlayers[playerId].aiState.conditionFlags = 0;

    gPlayerInput[playerId].enabled = FALSE;

    if (gPlayMode == PLAY_MODE_30) {
        if (playerId != PLAYER_1) {
            ai_reset_difficulty_hard(gPlayers + playerId);
        } else {
            ai_set_temp_max_difficulty(gPlayers + PLAYER_1);
        }
    } else if (gBattleSettings[playerId].unk_0F) {
        if (gDifficulty == DIFFICULTY_HARD && gBattleSettings[playerId].aiDifficulty == 0) {
            gBattleSettings[playerId].aiDifficulty = 2;
        }
        s2 = gBattleSettings[playerId].aiDifficulty;

        ai_reset_difficulty_hard(gPlayers + playerId);
        gBattleSettings[playerId].unk_0F = FALSE;
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
                        ai_set_temp_max_difficulty(gPlayers + playerId);
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

void func_800045B4(s16 playerId, s16 characterId) {
    char sp94[20];
    char sp80[20];
    CombatState *s0;
    s32 *pad3;
    s32 *sp74;
    Player *player;
    ModelInstance *modInst;
    s16 a12;
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
        func_80004304(sp80, D_8004B844[characterId].unk_04->name, ".db");
    }

    s3 = (CharacterDefinition *) gAssets[asset_find(sp80, playerId)].data;
    player->transitionTimingTable = s3->unk_00 + (u32) s3;
    player->transitionRuleTable = pad = s3->transitionTable + 4 + (u32) s3;
    player->logicStateTable = s3->logicStates + (u32) s3;
    player->stateOverrideIndices = s3->unk_0C + (u32) s3;
    player->frameTriggerOverrideTable = s3->unk_10 + (u32) s3;

    sp74 = s3->stateTable + (u32) s3;
    if (sp44->isDummy) {
        *sp74 = 0;
    }
    player->combatStateTable = s0 = (u32) s3 + s3->stateTable + 4;

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
    if ((v03 = asset_find(sp94, 0x5000 + playerId)) > 0) {
        q = D_8004B94C[sp50].unk_00;
        a12 = s0[q].animationId;
        modInst->animations[a12] = gAssets[v03].data;
        s0[q].maxFrame = func_80037394(modInst, a12) - 1;
    }

    str_copy(sp94, D_8004B94C[11 + sp50].unk_04);
    str_concat(sp94, ".MOV");
    if ((v03 = asset_find(sp94, 0x5000 + playerId)) > 0) {
        q = D_8004B94C[11 + sp50].unk_00;
        a12 = s0[q].animationId;
        modInst->animations[a12] = gAssets[v03].data;
        if (sp50 != AARON) {
            s0[q].maxFrame = func_80037394(modInst, a12) - 1;
        }

        q = D_8004B9FC[sp50];
        a12 = s0[q].animationId;
        modInst->animations[a12] = gAssets[v03].data;
        s0[q].maxFrame = func_80037394(modInst, a12) - 1;
    }

    player->combatStateId = 0;

    for (i = 0; i < *sp74; i++, s0++) {
        if (s0->maxFrame == -1) {
            s0->maxFrame = func_80037394(modInst, s0->animationId) - 1;
        } else if (func_80037394(modInst, s0->animationId) < s0->maxFrame) {
            s0->maxFrame = func_80037394(modInst, s0->animationId) - 1;
        }

        if (s0->bodyHitboxStart == -1 || s0->bodyHitboxEnd == -1) {
            s0->bodyHitboxStart = s0->hitboxActiveStart + 3;
            s0->bodyHitboxEnd = s0->hitboxActiveEnd - 1;
        }
    }

    if (sp44->isCpu) {
        func_80004334(s3, playerId);
    }

    if (sp44->isDebug) {
        if (sp44->isDummy) {
            str_copy(sp80, "dum.sym");
        } else {
            func_80004304(sp80, D_8004B844[characterId].unk_04->name, ".sym");
        }
        // TODO wrong structure
        s3 = (CharacterDefinition *) gAssets[asset_find(sp80, playerId)].data;
        player->unk_9A8 = s3->unk_00 + (u32) s3;
        player->unk_9AC = s3->transitionTable + (u32) s3;
        player->unk_9B0 = s3->logicStates + (u32) s3;
        player->unk_9B4 = s3->unk_0C + (u32) s3;
    }
}

void func_80004AE0(Transform *arg0) {
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

void func_80004B30(Object *obj, s16 playerId, s16 arg2) {
    Transform *s1;
    Transform *sp38;
    Transform *s0;
    NodeAttachment *nodeHierarchy = obj->modInst->nodeAttachments;

    nodeHierarchy[D_8004C1D8[arg2]].x = 0;
    nodeHierarchy[D_8004C1D8[arg2]].y = 0;
    nodeHierarchy[D_8004C1D8[arg2]].z = 0;

    s0 = &obj->modInst->transforms[D_8004C1D8[arg2]];
    s1 = &gPlayers[playerId].unk_750;
    func_80012A20(s0->parent, s1, -3, -3);
    s1->local_matrix.w.x = s0->local_matrix.w.x;
    s1->local_matrix.w.y = s0->local_matrix.w.y;
    s1->local_matrix.w.z = s0->local_matrix.w.z;
    func_80004AE0(s0);
    sp38 = s0->firstChild;
    func_80012A20(s1, s0, -3, -3);
    s0->firstChild = sp38;

    nodeHierarchy[0].x = 0;
    nodeHierarchy[0].y = 0;
    nodeHierarchy[0].z = 0;

    s0 = &obj->modInst->transforms[0];
    s1 = &gPlayers[playerId].unk_868;
    func_80012A20(s0->parent, s1, -3, -3);
    s1->local_matrix.w.x = s0->local_matrix.w.x;
    s1->local_matrix.w.y = s0->local_matrix.w.y;
    s1->local_matrix.w.z = s0->local_matrix.w.z;
    func_80004AE0(s0);
    sp38 = s0->firstChild;
    func_80012A20(s1, s0, -3, -3);
    s0->firstChild = sp38;

    D_80052D64[playerId] = D_80052D68[playerId] = D_80052D6C[playerId] = D_80052D70[playerId] = D_80052D74[playerId] =
        0;
    D_80052D78[playerId] = 2;
}

void func_80004D40(Asset *asset) {
    s16 v1;
    s16 v2;
    u8 sp2B;

    v1 = gBattleSettings[1 - asset->context].characterId;
    sp2B = asset->name[6];
    asset->name[6] = '\0';

    if (str_compare(asset->name, D_8004B94C[v1].unk_04) != 0) {
        v1 += 11;
        if (str_compare(asset->name, D_8004B94C[v1].unk_04) != 0) {
            asset->name[0] = '\0';
            asset->flags |= 1;
            return;
        }
    }
    asset->name[6] = sp2B;
    asset_read(asset);
    asset->context += 0x5000;
}

void func_80004E14(s16 playerId) {
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
        if (gBattleSettings[playerId].assetContext) {
            str_concat(sp38, "_h");
        } else {
            str_concat(sp38, "_v");
        }
    }

    if (str_compare(sp38, gPlayers[playerId].unk_980)) {
        func_8002630C(playerId);
        str_copy(gPlayers[playerId].unk_980, sp38);
    }
    D_8013C228 = func_80004D40;
    asset_open_folder(sp38, CONTEXT_0000 + playerId);
}

void func_80004FC0(Object *obj) {
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

void func_80005060(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->obj->modInst->transforms[5].world_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

void func_800050B0(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->obj->modInst->rootTransform.world_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

void func_800050FC(u16 arg0, u16 arg1) {
    ColorRGBA sp38[] = { { 0, 200, 0, 0 }, { 200, 0, 0, 0 } };
    ColorRGBA sp30[] = { { 0, 0, 255, 0 }, { 200, 50, 0, 0 } };
    Object *sp2C;

    switch (arg1) {
        case EVE:
            sp2C = create_worker(func_80005060, 0x1000);
            create_light(sp2C, &sp38[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case MORPHIX:
            sp2C = create_worker(func_800050B0, 0x1000);
            create_light(sp2C, &sp30[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case DEMITRON:
            if (gBattleSettings[arg0].assetContext) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = &D_8004B764.lights[1].color;
                sp2C->varObj[1] = &D_8004B644.lights[1].color;
            }
            break;
        case DEMONICA:
            if (gBattleSettings[arg0].assetContext) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = &D_8004B784.lights[1].color;
                sp2C->varObj[1] = &D_8004B664.lights[1].color;
            }
            break;
    }
}

void func_800052EC(s16 playerId) {
    Object *spDC;
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

    func_80004E14(playerId);

    gPlayers[playerId].playerId = playerId;
    gPlayers[playerId].flags = 0;
    characterId = gPlayers[playerId].characterId = gBattleSettings[playerId].characterId;

    if (gBattleSettings[playerId].isDummy) {
        characterId = AARON;
        str_copy(spA4, "dum.tmd");
    } else {
        str_copy(spA4, D_8004B844[characterId].unk_04->name);
        if (characterId != MORPHIX) {
            if (playerId != 0) {
                str_concat(spA4, "2.tmd");
            } else {
                str_concat(spA4, ".tmd");
            }
        } else {
            if (playerId != 0) {
                str_concat(spA4, "2.k3");
            } else {
                str_concat(spA4, ".k3");
            }
        }
    }

    spDC = gPlayers[playerId].obj =
        create_model_instance_with_properties(&spB4[playerId], spA4, D_8004B844[characterId].unk_04, playerId);
    spDC->flags |= OBJ_FLAG_PLAYER;

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

    create_shadow(spDC, spA4, playerId);

    spDC->rotation.y = 0xC00 - spB0[playerId];
    spDC->fn_render = player_update;
    if (spDC->currentTask && spDC->currentTask) {} // @fake
    spDC->varObj[0] = gPlayers + playerId;

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

    func_800045B4(playerId, characterId);

    gPlayers[playerId].actionTask = spDC->currentTask;
    gPlayers[playerId].animTask = task_add(spDC, task_default_func, TASK_FLAG_ENABLED);
    gPlayers[playerId].audioTask = task_add(spDC, player_play_sounds, TASK_FLAG_ENABLED);
    gPlayers[playerId].cameraTask = task_add(spDC, task_default_func, TASK_FLAG_ENABLED);
    gPlayers[playerId].unk_18 = task_add(spDC, func_8003184C, TASK_FLAG_ENABLED);
    gPlayers[playerId].behaviorTable = D_8004C1E8;

    D_80080214 = D_8004A730[gBattleSettings[PLAYER_1].characterId] + D_8004A730[gBattleSettings[PLAYER_2].characterId];
    D_80080218 = D_8004A748[gBattleSettings[PLAYER_1].characterId] + D_8004A748[gBattleSettings[PLAYER_2].characterId];
    gPlayerAngle = 0x800;
    gPlayerDistance = 1600;

    gPlayerObjects[playerId] = spDC;
    D_80080238.headIndex = D_80080238.tailIndex = 0;
    D_80080238.startFrameCounter = gFrameCounter;

    D_80080236 = TRUE;

    if (gBattleSettings[playerId].isCpu) {
        player_apply_move(gPlayers + playerId, MOVE_ID_AI_OPENING_MOVE, 0);
    } else {
        player_apply_move(gPlayers + playerId, MOVE_ID_IDLE_068, 0);
    }

    if (playerId != 0) {
        D_80080236 = FALSE;
    }

    gPlayers[playerId].combatState = gPlayers[playerId].combatStateTable + gPlayers[playerId].combatStateId;
    init_player_hitboxes(&gPlayers[playerId], D_8004B844[characterId].unk_00);

    spDC->playerHp = gBattleSettings[playerId].initialHp;
    func_80004B30(spDC, playerId, characterId);

    if (playerId == PLAYER_1) {
        gPlayerInput[playerId].mirrored = TRUE;
    }

    hitbox_render_init(&gPlayers[playerId].unk_DE8, spDC->modInst,
                       &spDC->modInst->transforms[D_8004B844[characterId].unk_00->boneId3].world_matrix,
                       &gPlayers[playerId].hitboxBones.grabTransform.world_matrix, &spDC->pos,
                       &D_8004B844[characterId].unk_08[playerId]);

    if (D_8004B844[characterId].unk_00->torsoParentBoneId >= 0) {
        hitbox_render_init(&gPlayers[playerId].unk_2240, spDC->modInst,
                           &spDC->modInst->transforms[D_8004B844[characterId].unk_00->boneId2].world_matrix,
                           &gPlayers[playerId].hitboxBones.torsoTransform.world_matrix, &spDC->pos,
                           &D_8004B844[characterId].unk_08[playerId]);
        gPlayers[playerId].unk_5F4A = 1;
    } else {
        gPlayers[playerId].unk_5F4A = 0;
    }

    hitbox_render_init(&gPlayers[playerId].unk_3698, spDC->modInst,
                       &spDC->modInst->transforms[D_8004B844[characterId].unk_00->boneId6].world_matrix,
                       &spDC->modInst->transforms[D_8004B844[characterId].unk_00->boneId4].world_matrix, &spDC->pos,
                       &D_8004B844[characterId].unk_08[playerId]);
    hitbox_render_init(&gPlayers[playerId].unk_4AF0, spDC->modInst,
                       &spDC->modInst->transforms[D_8004B844[characterId].unk_00->boneId7].world_matrix,
                       &spDC->modInst->transforms[D_8004B844[characterId].unk_00->boneId5].world_matrix, &spDC->pos,
                       &D_8004B844[characterId].unk_08[playerId]);

    gPlayers[playerId].allowTransition = FALSE;
    if (gPlayMode == PLAY_MODE_PRACTICE) {
        if (playerId == gPracticingPlayer) {
            practice_init_hud();
        } else {
            gPlayers[playerId].flags |= PLAYER_FLAG_200000;
        }
    }

    func_800050FC(playerId, characterId);
}

void create_player_obj(s16 playerId) {
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

    gPlayers[playerId].actionTask->start_delay = 0;
    gPlayers[playerId].actionTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].actionTask->func = task_default_func;
    gPlayers[playerId].actionTask->stackPos = zero; // required to match
    gPlayers[playerId].animTask->start_delay = 0;
    gPlayers[playerId].animTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].animTask->func = task_default_func;
    gPlayers[playerId].animTask->stackPos = 0;
    gPlayers[playerId].audioTask->start_delay = 0;
    gPlayers[playerId].audioTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].audioTask->func = player_play_sounds;
    gPlayers[playerId].audioTask->stackPos = 0;
    gPlayers[playerId].cameraTask->start_delay = 0;
    gPlayers[playerId].cameraTask->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].cameraTask->func = task_default_func;
    gPlayers[playerId].cameraTask->stackPos = 0;
    gPlayers[playerId].unk_18->start_delay = 0;
    gPlayers[playerId].unk_18->flags = TASK_FLAG_ENABLED;
    gPlayers[playerId].unk_18->func = func_8003184C;
    gPlayers[playerId].unk_18->stackPos = 0;

    D_80080214 = D_8004A730[gBattleSettings[PLAYER_1].characterId] + D_8004A730[gBattleSettings[PLAYER_2].characterId];
    D_80080218 = D_8004A748[gBattleSettings[PLAYER_1].characterId] + D_8004A748[gBattleSettings[PLAYER_2].characterId];
    gPlayerAngle = 0x800;
    D_80080238.headIndex = D_80080238.tailIndex = 0;
    D_80080236 = TRUE;
    D_80080238.startFrameCounter = gFrameCounter;
    obj->rotation.y = 0xC00 - spB0[playerId];
    gPlayerDistance = 1600;
    obj->flags = (obj->flags & OBJ_FLAG_TRANSPARENT) | OBJ_FLAG_MODEL;
    D_80080238.headIndex = D_80080238.tailIndex = 0;
    D_80080236 = TRUE;

    if (gBattleSettings[playerId].isCpu) {
        player_apply_move(gPlayers + playerId, MOVE_ID_AI_OPENING_MOVE, 0);
    } else {
        player_apply_move(gPlayers + playerId, MOVE_ID_IDLE_068, 0);
    }

    if (playerId != PLAYER_1) {
        D_80080236 = FALSE;
    }

    gPlayers[playerId].combatState = gPlayers[playerId].combatStateTable + gPlayers[playerId].combatStateId;
    obj->playerHp = gBattleSettings[playerId].initialHp;

    if (playerId == PLAYER_1) {
        gPlayerInput[playerId].mirrored = TRUE;
    }

    gPlayers[playerId].allowTransition = FALSE;
}

u8 player_make_transition(Player *player, u8 arg1, u16 logicState) {
    u16 behaviorId;
    u16 sp4C;
    ObjectTask *animTask;
    FrameTriggerOverride *sp44;
    u16 sp42;
    Behavior *behavior;
    s32 pad1;
    s32 *animTaskParams;
    StateOverrideIndex *pad3;
    CombatState *nextState;
    u16 transitionId;
    TransitionRule *transitionRule;
    s16 combatStateId;
    u16 i;

    transitionId = player->logicStateTable[logicState];
    transitionRule = &player->transitionRuleTable[transitionId];
    sp4C = transitionRule->timingIndex;
    behaviorId = transitionRule->behaviorId;
    // clang-format off
    combatStateId = transitionRule->targetStateId; \
    if (combatStateId == player->combatStateId && !arg1) {
        combatStateId = -1;
    }
    // clang-format on

    behavior = player->behaviorTable + behaviorId;
    pad3 = player->stateOverrideIndices + player->combatStateId;

    sp44 = pad3->overrideTableOffset + player->frameTriggerOverrideTable;
    sp42 = pad3->numOverrides;

    if (behavior->transitionAllowedFunc != NULL && !behavior->transitionAllowedFunc(player->obj)) {
        return FALSE;
    }

    player->previousTransition = player->transition;
    player->transition = transitionRule;

    animTask = player->animTask;
    animTaskParams = &animTask->params;
    animTaskParams[2] = 0;

    for (i = 0; i < sp42; sp44++, i++) {
        if (sp44->stateId == combatStateId) {
            if (player->obj->frameIndex < sp44->frameIndex) {
                animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
                animTask->triggerAt = sp44->frameIndex;
                animTask->triggerSlot.func = func_80024764;
                animTask->triggerSlot.flags = TASK_FLAG_ENABLED;

                player->actionTask->func = task_default_func;
                player->actionTask->start_delay = 0;
                player->actionTask->flags = TASK_FLAG_ENABLED;

                animTaskParams[2] = sp44->transitionActionOverride;
                animTaskParams[3] = sp44->stateIdOverride;
                animTaskParams[4] = behavior->actionFunc;
            } else {
                animTask->func = func_80024764;
                animTask->start_delay = 0;
                animTask->flags = 1;

                player->actionTask->func = task_default_func;
                player->actionTask->start_delay = 0;
                player->actionTask->flags = TASK_FLAG_ENABLED;

                animTaskParams[2] = sp44->transitionActionOverride;
                animTaskParams[3] = sp44->stateIdOverride;
                animTaskParams[4] = behavior->actionFunc;

                player->aiState.aiFlags |= AIF_20000;
            }
            goto label;
        }
    }

    player->actionTask->func = behavior->actionFunc;
    player->actionTask->start_delay = 0;
    player->actionTask->flags = TASK_FLAG_ENABLED;
    if (combatStateId >= 0) {
        animTask->func = anim_change_combat_state;
        animTask->start_delay = 0;
        animTask->flags = TASK_FLAG_ENABLED;
    }

label:

    if (combatStateId >= 0) {
        animTaskParams[1] = combatStateId;
        animTaskParams[0] = behavior->animFunc;
        player->previousCombatStateId = player->combatStateId;
        player->combatStateId = combatStateId;

        nextState = player->combatStateTable + combatStateId;
        if (nextState->cutsceneId >= 0 && nextState->custsceneDelay == -1) {
            camera_save_state();
            camera_set_animation(
                gCamera, player->obj->modInst->animations[player->combatStateTable[nextState->cutsceneId].animationId]);
            gCamera->currentTask->func = camera_cutscene_playback;
            gCamera->currentTask->start_delay = 0;
            gCamera->currentTask->flags = TASK_FLAG_ENABLED;
        }
    } else {
        animTask->func = behavior->animFunc;
        animTask->flags = TASK_FLAG_ENABLED;
        animTask->start_delay = 0;
    }

    player->previousBehaviorId = player->behaviorId;
    player->previousFlags = player->flags;
    player->behaviorId = behaviorId;
    player->currentTiming = player->transitionTimingTable + sp4C;

    player->flags = behavior->newFlags | (player->flags & behavior->preserveFlags);
    player->behavior = behavior;
    player->transitionId = transitionId;
    player->currentLogicState = logicState;

    func_800035D0(player);

    if (gPlayers[1 - player->playerId].hitCooldown < 3) {
        gPlayers[1 - player->playerId].hitCooldown = 3;
    }

    player->transitionTimeStamp = gFrameCounter;
    if (player->currentTiming->unk_0C != 0) {
        player->actionTask->start_delay = player->currentTiming->unk_0C;
    }
    player->autoTransitionTimer = player->currentTiming->moveTimeout;
    player->obj->velocity.z = player->currentTiming->unk_08;
    player->obj->flags &= ~OBJ_FLAG_800;
    player->lookupLogicTable = player->logicStateTable[logicState + 1];

    return TRUE;
}

u8 player_apply_move(Player *player, s16 moveId, u8 arg2) {
    s16 logicState;

    logicState = player->moveToLogicStateMap[moveId];
    player->animTask->flags &= ~TASK_FLAG_TRIGGER_FRAME;
    return player_make_transition(player, arg2, logicState);
}

u8 player_force_move(Player *player, s16 moveId, u8 arg2) {
    if (gBattleSettings[player->playerId].isCpu) {
        player->autoTransitionTimer = 0;
        return ai_force_transition(player, moveId);
    } else {
        return player_apply_move(player, moveId, arg2);
    }
}

u8 player_select_transition(Player *player, u8 arg1) {
    ObjectTask *animTask;
    void *sp68;
    TransitionRule *possibleMove;
    TransitionRule *transitionRuleTable;
    s16 sp5E;
    s16 transitionIndex;
    s16 *logicStates;
    s32 pad[2];
    s32 sp4C;
    u16 moveFlags;
    u16 masked_buttons;
    s32 pad2[2];
    u16 buttons;

    transitionIndex = player->lookupLogicTable;
    sp68 = NULL;
    transitionRuleTable = player->transitionRuleTable;
    logicStates = player->logicStateTable;
    sp4C = gFrameCounter - player->transitionTimeStamp;

    if (gRoundOver) {
        buttons = 0;
    } else if (player->flags & PLAYER_FLAG_1000) {
        buttons = gPlayerInput[player->playerId].prev_buttons;
    } else {
        buttons = gPlayerInput[player->playerId].buttons;
    }

    while (logicStates[transitionIndex] >= 0) {
        possibleMove = transitionRuleTable + logicStates[transitionIndex];
        moveFlags = possibleMove->flags;
        masked_buttons = buttons & possibleMove->button_mask;

        // make this move only when no condition for other moves
        if (moveFlags & TRANSITION_FLAG_FALLBACK) {
            if ((moveFlags & TRANSITION_FLAG_TURN) &&
                (!(moveFlags & TRANSITION_FLAG_TURN_AWAY) || !(player->flags & PLAYER_FLAG_NOT_FACING_OPP))) {
                transitionIndex += 2;
                continue;
            } else {
                sp5E = transitionIndex;
                sp68 = possibleMove;
                transitionIndex += 2;
                continue;
            }
        }

        // triggers only on timeout, no input check
        if ((moveFlags & TRANSITION_FLAG_TIMEOUT) && player->autoTransitionTimer <= 0) {
            gPlayerInput[player->playerId].pendingInput = FALSE;
            D_80080236 = TRUE;
            if (player_make_transition(player, TRUE, transitionIndex)) {
                D_80080236 = FALSE;
                return TRUE;
            }

            D_80080236 = FALSE;
            transitionIndex += 2;
            continue;
        }

        // move to turn around
        if (buttons && (moveFlags & TRANSITION_FLAG_TURN) && (moveFlags & TRANSITION_FLAG_TURN_AWAY) &&
            (player->flags & PLAYER_FLAG_NOT_FACING_OPP)) {
            if (possibleMove->requiredButtons == 0 ||
                (possibleMove->requiredButtons != 0 && masked_buttons == possibleMove->requiredButtons) ||
                (possibleMove->requiredButtons == 0xFFFF && masked_buttons != 0)) {

                if ((moveFlags & TRANSITION_FLAG_HELD) &&
                    player->combatState == player->combatStateTable + player->combatStateId &&
                    player->combatState->maxFrame != player->obj->frameIndex &&
                    !(player->flags & (PLAYER_FLAG_800 | PLAYER_FLAG_4000))) {
                    animTask = player->animTask;
                    animTask->params[0] = transitionIndex;
                    animTask->params[1] = possibleMove;
                    animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
                    animTask->triggerAt = player->combatState->maxFrame - 1;
                    animTask->triggerSlot.func = func_800247CC;
                    animTask->triggerSlot.flags = TASK_FLAG_PREEMPT | TASK_FLAG_ENABLED;

                    return TRUE;
                }

                if (player_make_transition(player, TRUE, transitionIndex)) {
                    gPlayerInput[player->playerId].pendingInput = TRUE;
                    return TRUE;
                }

                transitionIndex += 2;
                continue;
            }
        }

        if (possibleMove->requiredButtons == masked_buttons &&
            ((moveFlags & TRANSITION_FLAG_IMMEDIATE) ||
             ((moveFlags & TRANSITION_FLAG_HELD) &&
              player->combatState == player->combatStateTable + player->combatStateId))) {

            gPlayerInput[player->playerId].pendingInput = FALSE;

            if (moveFlags & TRANSITION_FLAG_BUFFER) {
                if (player->combatState->maxFrame != player->obj->frameIndex &&
                    (!(player->flags & (PLAYER_FLAG_800 | PLAYER_FLAG_4000)) ||
                     player->combatState->minFrame != player->obj->frameIndex)) {
                    transitionIndex += 2;
                    continue;
                } else if (player_make_transition(player, TRUE, transitionIndex)) {
                    return TRUE;
                } else {
                    transitionIndex += 2;
                    continue;
                }
            }

            if ((moveFlags & TRANSITION_FLAG_HELD) && player->combatState->maxFrame != player->obj->frameIndex &&
                !(player->flags & (PLAYER_FLAG_800 | PLAYER_FLAG_4000))) {
                animTask = player->animTask;
                animTask->params[0] = transitionIndex;
                animTask->params[1] = possibleMove;
                animTask->flags |= TASK_FLAG_TRIGGER_FRAME;
                animTask->triggerAt = player->combatState->maxFrame - 1;
                animTask->triggerSlot.func = func_800247CC;
                animTask->triggerSlot.flags = TASK_FLAG_PREEMPT | TASK_FLAG_ENABLED;
                return TRUE;
            }

            if ((moveFlags & TRANSITION_FLAG_TIMED)) {
                if (sp4C <= player->transitionTimingTable[possibleMove->timingIndex].unk_06) {
                    if (player_make_transition(player, TRUE, transitionIndex)) {
                        return TRUE;
                    } else {
                        transitionIndex += 2;
                        continue;
                    }
                } else {
                    transitionIndex += 2;
                    continue;
                }
            }

            if (player_make_transition(player, TRUE, transitionIndex)) {
                return TRUE;
            }
        }

        transitionIndex += 2;
    }

    if (sp68 != NULL && arg1) {
        gPlayerInput[player->playerId].pendingInput = FALSE;
        D_80080236 = TRUE;
        if (player_make_transition(player, TRUE, sp5E)) {
            player->lookupLogicTable = logicStates[sp5E + 1];
            D_80080236 = FALSE;
            return TRUE;
        }
        D_80080236 = FALSE;
    }

    return FALSE;
}

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
        if (transitionFlags & TRANSITION_FLAG_FALLBACK) {
            if (((transitionFlags & TRANSITION_FLAG_TURN) &&
                 (!(transitionFlags & TRANSITION_FLAG_TURN_AWAY) || !(player->flags & PLAYER_FLAG_NOT_FACING_OPP)))) {
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
        D_80080236 = TRUE;
        if (player_make_transition(player, TRUE, sp26)) {
            player->lookupLogicTable = logicStates[sp26 + 1];
            D_80080236 = FALSE;
            return TRUE;
        }
        D_80080236 = FALSE;
    }

    return FALSE;
}
