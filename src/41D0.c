#include "common.h"
#include "task.h"
#include "camera.h"

typedef struct UnkOmicronSub {
    /* 0x00 */ s16 unk_00[2];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
} UnkOmicronSub; // size=0x8

typedef struct UnkOmicron {
    /* 0x0000 */ UnkOmicronSub unk_00[512];
    /* 0x1000 */ u16 unk_1000;
    /* 0x1002 */ u16 unk_1002;
    /* 0x1004 */ s32 unk_1004;
    /* 0x1008 */ s32 unk_1008;
} UnkOmicron;

typedef struct UnkQwe {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ char *unk_04;
} UnkQwe; // size = 8

extern s16 D_8004A730[];
extern s16 D_8004A748[];
extern char D_8004B654[]; // TODO: type
extern char D_8004B674[]; // TODO: type
extern char D_8004B774[]; // TODO: type
extern char D_8004B794[]; // TODO: type
extern UnkQwe D_8004B94C[];
extern PlayerSub5 D_8004C1E8[];

extern s32 D_80080218;
extern UnkOmicron D_80080238;
extern s32 D_80081240;

void func_80012150(PlayerSub6 *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4, ColorRGBA *arg5);

void func_80005B70(s16 playerId);
void func_80003C04(Object *obj);

typedef struct AssetDB {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
} AssetDB; // size = 0x44

extern s16 D_8004B9FC[];

#ifdef NON_MATCHING
void func_800035D0(Player *player) {
    UnkOmicronSub *a1;
    u16 t8;
    u16 a2;
    Object *v0;
    s32 v1;
    s32 nv, nv2, nv3;

    v0 = player->obj;

    if (D_80080236 || D_800801F0) {
        return;
    }
    v1 = D_80080238.unk_1002;
    a1 = D_80080238.unk_00 + v1;
    a1->unk_04 = player->unk_78;
    a1->unk_06 = player->playerId;
    a1->unk_07 = 255;

    a2 = player->playerId;
    t8 = 1 - player->playerId;
    a1->unk_00[a2] = v0->playerHp;
    a1->unk_00[t8] = gPlayers[t8].obj->playerHp;

    nv = D_80080238.unk_1002;
    nv2 = (nv - 1) & 0x1FF;
    D_80080238.unk_00[nv2].unk_07 = gFrameCounter - D_80080238.unk_1004;
    nv = (nv + 1) & 0x1FF;
    D_80080238.unk_1002 = nv;
    D_80080238.unk_1004 = gFrameCounter;

    if (D_80080238.unk_1000 == nv) {
        D_80080234 = 1;
        D_80080238.unk_1000 = (D_80080238.unk_1000 + 1) & 0x1FF;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800035D0.s")
void func_800035D0(Player *player);
#endif

void func_800036E8(Object *obj) {
    obj->flags |= 0x10;
    D_80080234 = 1;
}

void func_80003704(Object *obj) {
    if (gPlayers[1 - D_8013C24C].obj->playerHp <= 0 || --obj->vars[0] <= 0) {
        obj->currentTask->counter = 55;
        obj->currentTask->func = func_800036E8;
    }
}

#ifdef NON_EQUIVALENT
void func_80003780(Object *obj) {
    s32 s0;
    UnkOmicronSub *s1;
    s32 s3;

    while (TRUE) {
        s0 = D_80080238.unk_1000;
        s1 = &D_80080238.unk_00[s0];
        s3 = s1->unk_06;
        gPlayers[s3].unk_80 |= 0x800000;
        func_80005EE4(gPlayers + s1->unk_06, TRUE, s1->unk_04);
        gPlayers[s3].obj->playerHp = s1->unk_00[s3];
        if (s1->unk_00[s3] == 0) {
            D_8005BFC0 |= GAME_FLAG_200;
        }

        if (s1->unk_07 == 255) {
            break;
        }

        D_80080238.unk_1000 = (s0 + 1) & 0xFDFF; // ???
        if (s1->unk_07 != 0) {
            obj->currentTask->counter = s1->unk_07 - 1;
            return;
        }
    }

    obj->currentTask->func = func_80003704;
    obj->vars[0] = 260;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003780.s")
void func_80003780(Object *obj);
#endif

void func_800038C8(Object *obj) {
    task_execute(obj);

    if (gPlayerInput[D_8013C24C].buttons & INP_START) {
        obj->flags |= 0x10;
        D_80080234 = 1;
        D_8013C23C->currentTask->counter = 0;
        D_8013C23C->currentTask->func = func_800177C0;
        gPlayerInput[D_8013C24C].unk_08 = FALSE;
    }
}

#ifdef NON_MATCHING
s32 func_80003974(void *arg0) {
    s32 s3;
    Object *v0;
    u32 i;
    s32 temp;

    s3 = gFrameCounter - D_80080238.unk_1008;

    D_80080238.unk_1000 = 0;
    D_8013C250 = 1;
    gPlayers[PLAYER_1].stateId = 0;
    gPlayers[PLAYER_2].stateId = 0;

    func_80005B70(PLAYER_1);
    func_80005B70(PLAYER_2);
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
    gPlayers[PLAYER_1].unk_0C->flags &= ~4;
    gPlayers[PLAYER_2].unk_0C->flags &= ~4;

    D_8008020C = 0x800;
    func_8002DA08(gCamera);
    gCamera->currentTask->func = func_8002EB2C;
    gCamera->currentTask->counter = 0;
    gCameraTarget.x = 0;
    gCameraTarget.z = 0;
    gCameraTarget.y = -400;
    D_8013C834 = FALSE;

    temp = guRandom() % 2;

    if (temp) {}

    v0 = create_worker(func_800038C8, -0x7001 + temp * 0);
    v0->currentTask->func = func_80003780;
    v0->currentTask->counter = 0;
    v0->currentTask->flags = 1;

    D_8008012C |= GFX_FLAG_1;
    D_8005BFC0 &= ~GAME_FLAG_200;

    if (s3 > 960) {
        s3 -= 960;
        for (i = 0; i < s3; i++) {
            func_80003C04(gPlayers[PLAYER_1].obj);
            func_80003C04(gPlayers[PLAYER_2].obj);
            func_800038C8(v0);
        }

        func_8002D278(gCamera, TRUE);
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003974.s")
s32 func_80003974(void *arg0);
#endif

s32 func_80003BB4(void) {
    s32 diff = gFrameCounter - D_80081240;

    if (diff < 60) {
        return FALSE;
    } else {
        set_post_render_hook(func_80003974, NULL);
        return TRUE;
    }
}

void func_80003C04(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    s32 unused[7];
    ModelInstance *sp20 = obj->modInst;

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    task_execute(obj);

    if (sp20->currentAnimId != sp20->previousAnimId) {
        model_change_animation(obj);
        sp20->previousAnimId = sp20->currentAnimId;
    }

    if (obj->frameIndex != obj->previousFrameIndex) {
        model_process_animation(obj);
        model_update_animated_params(obj);
        obj->previousFrameIndex = obj->frameIndex;
    }

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    if (player->unk_184) {
        if (player->unk_94 != 0 && --player->unk_94 == 0) {
            func_8000642C(player, TRUE);
        } else if (!(player->unk_80 & 0x100400) && gPlayerInput[playerId].unk_08 && player->unk_76 >= 0 &&
                   !(player->unk_0C->flags & 4)) {
            func_8000642C(player, FALSE);
        }
    }

    player->unk_184 = TRUE;
}

void func_80003DA4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 sp4A = player->playerId;
    u16 oppId;
    Player *sp24;
    PlayerState *sp40;
    PlayerState *sp3C;
    s32 pad[2];
    Object *sp30;
    u8 pad2;
    u8 sp2E;

    sp40 = player->currentState;
    oppId = 1 - sp4A;
    sp24 = &gPlayers[oppId];
    sp3C = sp24->currentState;
    sp30 = sp24->obj;

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    model_update(obj);

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    sp2E = (sp40->damage != 0) && (obj->frameIndex >= sp40->unk_24) && (obj->frameIndex < sp40->unk_26);

    func_800115A0(&player->unk_DE8, (sp40->flags & 0x40) && sp2E);
    if (player->unk_5F4A) {
        func_800115A0(&player->unk_2240, (sp40->flags & 0x2000) && sp2E);
    }
    func_800115A0(&player->unk_3698, (sp40->flags & 0x800) && sp2E);
    func_800115A0(&player->unk_4AF0, (sp40->flags & 0x1020) && sp2E);

    if (player->characterId != MORPHIX) {
        func_80037E28(obj);
    }

    if (!gIsPaused) {
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

        if (gBattleSettings[sp4A].isCpu && !D_800801F0 && !(player->unk_80 & 0x100000)) {
            if (!(player->unk_180 & 0x20000)) {
                func_8001B810(player);
            }
            if (D_8013C444 && gPlayerInput[sp4A].unk_08 && player->unk_76 >= 0 && !(player->unk_0C->flags & 4) &&
                !(player->unk_80 & 0x2000)) {
                func_8000642C(player, FALSE);
            }
        } else if (player->unk_184 && !D_800801F0) {
            if (player->unk_94 != 0 && --player->unk_94 == 0) {
                func_8000642C(player, TRUE);
            } else if (!(player->unk_80 & 0x100400) && gPlayerInput[sp4A].unk_08 && player->unk_76 >= 0 &&
                       !(player->unk_0C->flags & 4)) {
                func_8000642C(player, FALSE);
            }
        }

        if (player->unk_5F48 > 0) {
            player->unk_5F48--;
        }

        if (D_80080218 >= D_80080210 && !(player->currentState->flags & 0x40000) && player->unk_5F48 == 0 &&
            sp30->frameIndex >= sp3C->unk_04 && sp30->frameIndex <= sp3C->unk_06) {
            if (sp3C->flags & 0x2040) {
                if ((player->currentState->flags & 0x30400) && obj->modInst->rootTransform.world_matrix.w.y > -100.0f) {
                    func_8000FE9C(player, sp24);
                } else {
                    func_8000F494(player, sp24);
                }
            }

            if (player->unk_5F48 == 0 && (sp3C->flags & 0x1820)) {
                if ((player->currentState->flags & 0x30400) && obj->modInst->rootTransform.world_matrix.w.y > -100.0f) {
                    func_80010280(player, sp24);
                } else {
                    func_8000FB30(player, sp24);
                }
            }
        }

        player->unk_184 = TRUE;
    }
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
s32 func_8001C114(Player *); // @fake signature
void func_8001C1C0(Player *);
void func_8001BF40(Player *);
s32 func_8001DFE4(s32 arg0);

void func_80004334(AssetDB *arg0, s16 playerId) {
    AssetDB1 *v1;
    AssetDB3 *a2;
    s32 s2;
    s32 i;
    s32 pad;

    gPlayers[playerId].unk_50 = arg0->unk_30 + (u32) arg0;
    gPlayers[playerId].unk_54 = arg0->unk_34 + (u32) arg0;

    v1 = arg0->unk_38 + (u32) arg0;
    gPlayers[playerId].unk_DB8 = v1->unk_00;
    gPlayers[playerId].unk_58 = v1->unk_04;
    gPlayers[playerId].unk_5C = v1->unk_00 + v1->unk_04; // required to match

    a2 = arg0->unk_3C + (u32) arg0;
    gPlayers[playerId].unk_DBA = a2->unk_00;
    gPlayers[playerId].unk_64 = a2->unk_04;
    gPlayers[playerId].unk_60 = (((a2->unk_00 & 1) + a2->unk_00) & 0xFFFFFFFF) + a2->unk_04; // required to match

    gPlayers[playerId].unk_180 = 0x20000;
    gPlayers[playerId].unk_A8.unk_A8 = 0;
    gPlayers[playerId].unk_A8.unk_B4 = &D_80049394;
    gPlayers[playerId].unk_A8.unk_B8 = &D_80049394;
    gPlayers[playerId].unk_A8.unk_BC = 0;
    gPlayers[playerId].unk_C0 = 0;
    gPlayers[playerId].unk_C4 = 0;

    gPlayerInput[playerId].enabled = FALSE;

    if (gPlayMode == PLAY_MODE_30) {
        if (playerId != PLAYER_1) {
            func_8001C114(gPlayers + playerId);
        } else {
            func_8001C1C0(gPlayers + PLAYER_1);
        }
    } else if (gBattleSettings[playerId].unk_0F) {
        if (gDifficulty == 2 && gBattleSettings[playerId].unk_04 == 0) {
            gBattleSettings[playerId].unk_04 = 2;
        }
        s2 = gBattleSettings[playerId].unk_04;

        func_8001C114(gPlayers + playerId);
        gBattleSettings[playerId].unk_0F = FALSE;
        for (i = 0; i < s2; i++) {
            func_8001BF40(gPlayers + playerId);
        }
    } else {
        switch (gDifficulty) {
            case 1:
            case 2:
                func_8001BF40(gPlayers + playerId);
                break;
            case 0:
                switch (func_8001DFE4(playerId)) {
                    case 0:
                        func_8001C1C0(gPlayers + playerId);
                        break;
                    default:
                        func_8001BF40(gPlayers + playerId);
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
    PlayerState *s0;
    s32 *pad3;
    s32 *sp74;
    Player *player;
    ModelInstance *modInst;
    s16 a12;
    Player12 *sp44;
    AssetDB *s3;
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

    s3 = (AssetDB *) gAssets[asset_find(sp80, playerId)].data;
    player->unk_28 = s3->unk_00 + (u32) s3;
    player->unk_2C = pad = s3->unk_04 + 4 + (u32) s3;
    player->unk_34 = s3->unk_08 + (u32) s3;
    player->unk_30 = s3->unk_0C + (u32) s3;
    player->unk_1C = s3->unk_10 + (u32) s3;

    sp74 = s3->unk_14 + (u32) s3;
    if (sp44->isDummy) {
        *sp74 = 0;
    }
    player->states = s0 = (u32) s3 + s3->unk_14 + 4;

    player->unk_40 = pad = s3->unk_18 + (u32) s3 + 4;
    pad3 = s3->unk_1C + (u32) s3;
    player->unk_6C = *pad3;
    if (((!player->obj) && (!player->obj)) & 0xFFFFFFFFu) {} // @fake
    player->unk_38 = s3->unk_20 + (u32) s3;
    player->unk_44 = s3->unk_24 + (u32) s3;
    player->unk_48 = s3->unk_28 + (u32) s3;
    player->unk_4C = s3->unk_2C + (u32) s3;
    player->unk_68 = s3->unk_40 + (u32) s3;

    str_copy(sp94, D_8004B94C[sp50].unk_04);
    str_concat(sp94, ".MOV");
    if ((v03 = asset_find(sp94, 0x5000 + playerId)) > 0) {
        q = D_8004B94C[sp50].unk_00;
        a12 = s0[q].animationId;
        modInst->animations[a12] = gAssets[v03].data;
        s0[q].unk_02 = func_80037394(modInst, a12) - 1;
    }

    str_copy(sp94, D_8004B94C[11 + sp50].unk_04);
    str_concat(sp94, ".MOV");
    if ((v03 = asset_find(sp94, 0x5000 + playerId)) > 0) {
        q = D_8004B94C[11 + sp50].unk_00;
        a12 = s0[q].animationId;
        modInst->animations[a12] = gAssets[v03].data;
        if (sp50 != AARON) {
            s0[q].unk_02 = func_80037394(modInst, a12) - 1;
        }

        q = D_8004B9FC[sp50];
        a12 = s0[q].animationId;
        modInst->animations[a12] = gAssets[v03].data;
        s0[q].unk_02 = func_80037394(modInst, a12) - 1;
    }

    player->stateId = 0;

    for (i = 0; i < *sp74; i++, s0++) {
        if (s0->unk_02 == -1) {
            s0->unk_02 = func_80037394(modInst, s0->animationId) - 1;
        } else if (func_80037394(modInst, s0->animationId) < s0->unk_02) {
            s0->unk_02 = func_80037394(modInst, s0->animationId) - 1;
        }

        if (s0->unk_24 == -1 || s0->unk_26 == -1) {
            s0->unk_24 = s0->unk_04 + 3;
            s0->unk_26 = s0->unk_06 - 1;
        }
    }

    if (sp44->isCpu) {
        func_80004334(s3, playerId);
    }

    if (sp44->unk_0E) {
        if (sp44->isDummy) {
            str_copy(sp80, "dum.sym");
        } else {
            func_80004304(sp80, D_8004B844[characterId].unk_04->name, ".sym");
        }
        s3 = (AssetDB *) gAssets[asset_find(sp80, playerId)].data;
        player->unk_9A8 = s3->unk_00 + (u32) s3;
        player->unk_9AC = s3->unk_04 + (u32) s3;
        player->unk_9B0 = s3->unk_08 + (u32) s3;
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
    NodeAttachment *v1 = obj->modInst->nodeAttachments;

    v1[D_8004C1D8[arg2]].x = 0;
    v1[D_8004C1D8[arg2]].y = 0;
    v1[D_8004C1D8[arg2]].z = 0;

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

    v1[0].x = 0;
    v1[0].y = 0;
    v1[0].z = 0;

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
    func_80026BE0(asset);
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
        if (gBattleSettings[playerId].unk_06) {
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
    asset_open_folder(sp38, playerId);
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
            func_8003453C(sp2C, &sp38[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case MORPHIX:
            sp2C = create_worker(func_800050B0, 0x1000);
            func_8003453C(sp2C, &sp30[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case DEMITRON:
            if (gBattleSettings[arg0].unk_06) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = D_8004B774;
                sp2C->varObj[1] = D_8004B654;
            }
            break;
        case DEMONICA:
            if (gBattleSettings[arg0].unk_06) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = D_8004B794;
                sp2C->varObj[1] = D_8004B674;
            }
            break;
    }
}

void func_800052EC(s16 playerId) {
    Object *spDC;
    s16 v00;
    s16 i;
    s16 spD6;
    Vec4i spB4[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 spB0[] = { 0, 0x800 };
    char spA4[12];
    char sp74[48];
    char *str1 = "mod0.k2";
    char *str2 = "spr0.sp3";
    char sp60[12];

    func_80004E14(playerId);

    gPlayers[playerId].playerId = playerId;
    gPlayers[playerId].unk_80 = 0;
    spD6 = gPlayers[playerId].characterId = gBattleSettings[playerId].characterId;

    if (gBattleSettings[playerId].isDummy) {
        spD6 = AARON;
        str_copy(spA4, "dum.tmd");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->name);
        if (spD6 != MORPHIX) {
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
        create_model_instance_with_properties(&spB4[playerId], spA4, D_8004B844[spD6].unk_04, playerId);
    spDC->flags |= 0x80;

    if (spD6 == MORPHIX && !gBattleSettings[playerId].isDummy) {
        func_8002A890(gPlayers + playerId);
    }

    if (gBattleSettings[playerId].isDummy) {
        str_copy(spA4, "dumshad.k4");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->name);
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
    spDC->fn_render = func_80003DA4;
    if (spDC->currentTask && spDC->currentTask) {} // @fake
    spDC->varObj[0] = gPlayers + playerId;

    i = 0;
    str_copy(sp74, str2);
    while (TRUE) {
        v00 = asset_find(sp74, playerId);
        if (v00 >= 0) {
            gPlayers[playerId].unk_DC0[i++] = gAssets[v00].aux_data;
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
            gPlayers[playerId].unk_DCC[i++] = gAssets[v00].aux_data;
        } else {
            v00 = asset_find(sp60, playerId);
            if (v00 >= 0) {
                gPlayers[playerId].unk_DCC[i++] = gAssets[v00].aux_data;
            } else {
                break;
            }
        }

        sp74[3]++;
        sp60[3]++;
    }

    func_800045B4(playerId, spD6);

    gPlayers[playerId].unk_08 = spDC->currentTask;
    gPlayers[playerId].unk_0C = task_add(spDC, task_default_func, 1);
    gPlayers[playerId].unk_10 = task_add(spDC, func_800248C4, 1);
    gPlayers[playerId].unk_14 = task_add(spDC, task_default_func, 1);
    gPlayers[playerId].unk_18 = task_add(spDC, func_8003184C, 1);
    gPlayers[playerId].unk_24 = D_8004C1E8;

    D_80080214 = D_8004A730[gBattleSettings[PLAYER_1].characterId] + D_8004A730[gBattleSettings[PLAYER_2].characterId];
    D_80080218 = D_8004A748[gBattleSettings[PLAYER_1].characterId] + D_8004A748[gBattleSettings[PLAYER_2].characterId];
    D_8008020C = 0x800;
    D_80080210 = 1600;

    D_80080228[playerId] = spDC;
    D_80080238.unk_1000 = D_80080238.unk_1002 = 0;
    D_80080238.unk_1008 = gFrameCounter;

    D_80080236 = 1;

    if (gBattleSettings[playerId].isCpu) {
        func_8000636C(gPlayers + playerId, 282, 0);
    } else {
        func_8000636C(gPlayers + playerId, 68, 0);
    }

    if (playerId != 0) {
        D_80080236 = 0;
    }

    gPlayers[playerId].currentState = gPlayers[playerId].states + gPlayers[playerId].stateId;
    func_80010664(&gPlayers[playerId], D_8004B844[spD6].unk_00);

    spDC->playerHp = gBattleSettings[playerId].unk_0C;
    func_80004B30(spDC, playerId, spD6);

    if (playerId == 0) {
        gPlayerInput[playerId].isMirrored = TRUE;
    }

    func_80012150(&gPlayers[playerId].unk_DE8, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_08].world_matrix,
                  &gPlayers[playerId].unk_198.unk_150.world_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[playerId]);

    if (D_8004B844[spD6].unk_00->unk_1C >= 0) {
        func_80012150(&gPlayers[playerId].unk_2240, spDC->modInst,
                      &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_04].world_matrix,
                      &gPlayers[playerId].unk_198.unk_38.world_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[playerId]);
        gPlayers[playerId].unk_5F4A = 1;
    } else {
        gPlayers[playerId].unk_5F4A = 0;
    }

    func_80012150(&gPlayers[playerId].unk_3698, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_14].world_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_0C].world_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[playerId]);
    func_80012150(&gPlayers[playerId].unk_4AF0, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_18].world_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_10].world_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[playerId]);

    gPlayers[playerId].unk_184 = 0;
    if (gPlayMode == PLAY_MODE_PRACTICE) {
        if (playerId == gPracticingPlayer) {
            practice_init_hud();
        } else {
            gPlayers[playerId].unk_80 |= 0x200000;
        }
    }

    func_800050FC(playerId, spD6);
}

void func_80005B70(s16 playerId) {
    Object *obj = gPlayers[playerId].obj;
    s16 characterId;
    Vec4i spB4[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 spB0[] = { 0, 0x800 };
    s32 zero = 0;

    gPlayers[playerId].playerId = playerId;
    gPlayers[playerId].unk_80 = 0;
    gPlayers[playerId].unk_180 = 0;
    gPlayers[playerId].characterId = characterId = gBattleSettings[playerId].characterId;

    obj->rotation.y = 0xC00 - spB0[playerId];
    obj->pos.x = spB4[playerId].x;
    obj->pos.y = spB4[playerId].y;
    obj->pos.z = spB4[playerId].z;
    obj->fn_render = func_80003DA4;
    obj->varObj[0] = gPlayers + playerId;

    gPlayers[playerId].unk_08->counter = 0;
    gPlayers[playerId].unk_08->flags = 1;
    gPlayers[playerId].unk_08->func = task_default_func;
    gPlayers[playerId].unk_08->stackPos = zero; // required to match
    gPlayers[playerId].unk_0C->counter = 0;
    gPlayers[playerId].unk_0C->flags = 1;
    gPlayers[playerId].unk_0C->func = task_default_func;
    gPlayers[playerId].unk_0C->stackPos = 0;
    gPlayers[playerId].unk_10->counter = 0;
    gPlayers[playerId].unk_10->flags = 1;
    gPlayers[playerId].unk_10->func = func_800248C4;
    gPlayers[playerId].unk_10->stackPos = 0;
    gPlayers[playerId].unk_14->counter = 0;
    gPlayers[playerId].unk_14->flags = 1;
    gPlayers[playerId].unk_14->func = task_default_func;
    gPlayers[playerId].unk_14->stackPos = 0;
    gPlayers[playerId].unk_18->counter = 0;
    gPlayers[playerId].unk_18->flags = 1;
    gPlayers[playerId].unk_18->func = func_8003184C;
    gPlayers[playerId].unk_18->stackPos = 0;

    D_80080214 = D_8004A730[gBattleSettings[PLAYER_1].characterId] + D_8004A730[gBattleSettings[PLAYER_2].characterId];
    D_80080218 = D_8004A748[gBattleSettings[PLAYER_1].characterId] + D_8004A748[gBattleSettings[PLAYER_2].characterId];
    D_8008020C = 0x800;
    D_80080238.unk_1000 = D_80080238.unk_1002 = 0;
    D_80080236 = 1;
    D_80080238.unk_1008 = gFrameCounter;
    obj->rotation.y = 0xC00 - spB0[playerId];
    D_80080210 = 1600;
    obj->flags = (obj->flags & 0x2000) | 1;
    D_80080238.unk_1000 = D_80080238.unk_1002 = 0;
    D_80080236 = 1;

    if (gBattleSettings[playerId].isCpu) {
        func_8000636C(gPlayers + playerId, 282, 0);
    } else {
        func_8000636C(gPlayers + playerId, 68, 0);
    }

    if (playerId != PLAYER_1) {
        D_80080236 = FALSE;
    }

    gPlayers[playerId].currentState = gPlayers[playerId].states + gPlayers[playerId].stateId;
    obj->playerHp = gBattleSettings[playerId].unk_0C;

    if (playerId == PLAYER_1) {
        gPlayerInput[playerId].isMirrored = TRUE;
    }

    gPlayers[playerId].unk_184 = FALSE;
}

u8 func_80005EE4(Player *player, u8 arg1, u16 arg2) {
    u16 sp4E;
    u16 sp4C;
    ObjectTask *unk_0C;
    PlayerSubE *sp44;
    u16 sp42;
    PlayerSub5 *sp3C;
    s32 pad1;
    ObjectTaskSub *pad2;
    PlayerSubD *pad3;
    PlayerState *sp2C;
    u16 sp2A;
    PlayerSub8 *sp24;
    s16 sp22;
    u16 i;

    sp2A = player->unk_34[arg2];
    sp24 = &player->unk_2C[sp2A];
    sp4C = sp24->index_in_field28;
    sp4E = sp24->index_in_field24;
    // clang-format off
    sp22 = sp24->index_in_field20; \
    if (sp22 == player->stateId && !arg1) {
        sp22 = -1;
    }
    // clang-format on

    sp3C = player->unk_24 + sp4E;
    pad3 = player->unk_30 + player->stateId;

    sp44 = pad3->unk_00 + player->unk_1C;
    sp42 = pad3->unk_02;

    if (sp3C->fn_check != NULL && !sp3C->fn_check(player->obj)) {
        return FALSE;
    }

    player->unk_A4 = player->unk_A0;
    player->unk_A0 = sp24;

    unk_0C = player->unk_0C;
    pad2 = &unk_0C->unk_08;
    pad2->unk_08 = 0;

    for (i = 0; i < sp42; sp44++, i++) {
        if (sp44->unk_04 == sp22) {
            if (player->obj->frameIndex < sp44->unk_02) {
                unk_0C->flags |= 4;
                unk_0C->unk_86 = sp44->unk_02;
                unk_0C->unk_90.func = func_80024764;
                unk_0C->unk_90.flags = 1;

                player->unk_08->func = task_default_func;
                player->unk_08->counter = 0;
                player->unk_08->flags = 1;

                pad2->unk_08 = sp44->unk_06;
                pad2->unk_0C = sp44->unk_00;
                pad2->unk_10 = sp3C->unk_08;
            } else {
                unk_0C->func = func_80024764;
                unk_0C->counter = 0;
                unk_0C->flags = 1;

                player->unk_08->func = task_default_func;
                player->unk_08->counter = 0;
                player->unk_08->flags = 1;

                pad2->unk_08 = sp44->unk_06;
                pad2->unk_0C = sp44->unk_00;
                pad2->unk_10 = sp3C->unk_08;

                player->unk_180 |= 0x20000;
            }
            goto label;
        }
    }

    player->unk_08->func = sp3C->unk_08;
    player->unk_08->counter = 0;
    player->unk_08->flags = 1;
    if (sp22 >= 0) {
        unk_0C->func = func_80024390;
        unk_0C->counter = 0;
        unk_0C->flags = 1;
    }

label:

    if (sp22 >= 0) {
        pad2->unk_04 = sp22;
        pad2->unk_00_f = sp3C->unk_04;
        player->unk_188 = player->stateId;
        player->stateId = sp22;

        sp2C = player->states + sp22;
        if (sp2C->unk_2C >= 0 && sp2C->unk_2E == -1) {
            func_8002C340();
            camera_set_animation(gCamera, player->obj->modInst->animations[player->states[sp2C->unk_2C].animationId]);
            gCamera->currentTask->func = func_8002C490;
            gCamera->currentTask->counter = 0;
            gCamera->currentTask->flags = 1;
        }
    } else {
        unk_0C->func = sp3C->unk_04;
        unk_0C->flags = 1;
        unk_0C->counter = 0;
    }

    player->unk_186 = player->unk_7C;
    player->unk_18C = player->unk_80;
    player->unk_7C = sp4E;
    player->unk_88 = player->unk_28 + sp4C;

    player->unk_80 = sp3C->unk_00 | (player->unk_80 & sp3C->unk_10);
    player->unk_98 = sp3C;
    player->unk_74 = sp2A;
    player->unk_78 = arg2;

    func_800035D0(player);

    if (gPlayers[1 - player->playerId].unk_5F48 < 3) {
        gPlayers[1 - player->playerId].unk_5F48 = 3;
    }

    player->unk_8C = gFrameCounter;
    if (player->unk_88->unk_0C != 0) {
        player->unk_08->counter = player->unk_88->unk_0C;
    }
    player->unk_94 = player->unk_88->unk_0E;
    player->obj->velocity.z = player->unk_88->unk_08;
    player->obj->flags &= ~0x800;
    player->unk_76 = player->unk_34[arg2 + 1];

    return TRUE;
}

u8 func_8000636C(Player *player, s16 arg1, u8 arg2) {
    s16 v1;

    v1 = player->unk_38[arg1];
    player->unk_0C->flags &= ~4;
    return func_80005EE4(player, arg2, v1);
}

u8 func_800063C4(Player *player, s16 arg1, u8 arg2) {
    if (gBattleSettings[player->playerId].isCpu) {
        player->unk_94 = 0;
        return func_8001B7D0(player, arg1);
    } else {
        return func_8000636C(player, arg1, arg2);
    }
}

u8 func_8000642C(Player *player, u8 arg1) {
    ObjectTask *unk_0C;
    void *sp68;
    PlayerSub8 *a2;
    PlayerSub8 *sp60;
    s16 sp5E;
    s16 s0;
    s16 *sp58;
    s32 pad[2];
    s32 sp4C;
    u16 v0;
    u16 masked_buttons;
    s32 pad2[2];
    u16 buttons;

    s0 = player->unk_76;
    sp68 = NULL;
    sp60 = player->unk_2C;
    sp58 = player->unk_34;
    sp4C = gFrameCounter - player->unk_8C;

    if (D_800801F0) {
        buttons = 0;
    } else if (player->unk_80 & 0x1000) {
        buttons = gPlayerInput[player->playerId].prev_buttons;
    } else {
        buttons = gPlayerInput[player->playerId].buttons;
    }

    while (sp58[s0] >= 0) {
        a2 = sp60 + sp58[s0];
        v0 = a2->flags;
        masked_buttons = buttons & a2->button_mask;

        if (v0 & 2) {
            if ((v0 & 0x10) && (!(v0 & 0x800) || !(player->unk_80 & 8))) {
                s0 += 2;
            } else {
                sp5E = s0;
                sp68 = a2;
                s0 += 2;
            }
            continue;
        }

        if ((v0 & 8) && player->unk_94 <= 0) {
            gPlayerInput[player->playerId].unk_08 = FALSE;
            D_80080236 = TRUE;
            if (func_80005EE4(player, TRUE, s0)) {
                D_80080236 = FALSE;
                return TRUE;
            }

            D_80080236 = FALSE;
            s0 += 2;
            continue;
        }

        if (buttons && (v0 & 0x10) && (v0 & 0x800) && (player->unk_80 & 8) &&
            (a2->buttons == 0 || (a2->buttons != 0 && masked_buttons == a2->buttons) ||
             (a2->buttons == 0xFFFF && masked_buttons != 0))) {
            if ((v0 & 4) && player->currentState == player->states + player->stateId &&
                player->currentState->unk_02 != player->obj->frameIndex && !(player->unk_80 & 0x4800)) {
                unk_0C = player->unk_0C;
                unk_0C->unk_08.unk_00_i = s0;
                unk_0C->unk_08.unk_04_ptr = a2;
                unk_0C->flags |= 4;
                unk_0C->unk_86 = player->currentState->unk_02 - 1;
                unk_0C->unk_90.func = func_800247CC;
                unk_0C->unk_90.flags = 0x41;

                return TRUE;
            }

            if (func_80005EE4(player, TRUE, s0)) {
                gPlayerInput[player->playerId].unk_08 = TRUE;
                return TRUE;
            }

            s0 += 2;
            continue;
        }

        if (a2->buttons == masked_buttons &&
            ((v0 & 1) || ((v0 & 4) && player->currentState == player->states + player->stateId))) {
            gPlayerInput[player->playerId].unk_08 = FALSE;

            if (v0 & 0x20) {
                if (player->currentState->unk_02 != player->obj->frameIndex &&
                    (!(player->unk_80 & 0x4800) || player->currentState->unk_00 != player->obj->frameIndex)) {
                    s0 += 2;
                } else if (func_80005EE4(player, TRUE, s0)) {
                    return TRUE;
                } else {
                    s0 += 2;
                }
                continue;
            }

            if ((v0 & 4) && player->currentState->unk_02 != player->obj->frameIndex && !(player->unk_80 & 0x4800)) {
                unk_0C = player->unk_0C;
                unk_0C->unk_08.unk_00_i = s0;
                unk_0C->unk_08.unk_04_ptr = a2;
                unk_0C->flags |= 4;
                unk_0C->unk_86 = player->currentState->unk_02 - 1;
                unk_0C->unk_90.func = func_800247CC;
                unk_0C->unk_90.flags = 0x41;
                return TRUE;
            }

            if ((v0 & 0x40)) {
                if (sp4C <= player->unk_28[a2->index_in_field28].unk_06) {
                    if (func_80005EE4(player, TRUE, s0)) {
                        return TRUE;
                    } else {
                        s0 += 2;
                        continue;
                    }
                } else {
                    s0 += 2;
                    continue;
                }
            }

            if (func_80005EE4(player, TRUE, s0)) {
                return TRUE;
            }
        }

        s0 += 2;
    }

    if (sp68 != NULL && arg1) {
        gPlayerInput[player->playerId].unk_08 = FALSE;
        D_80080236 = TRUE;
        if (func_80005EE4(player, TRUE, sp5E)) {
            player->unk_76 = sp58[sp5E + 1];
            D_80080236 = FALSE;
            return TRUE;
        }
        D_80080236 = FALSE;
    }

    return FALSE;
}

u8 func_800069C0(Player *player) {
    s16 a2;
    u16 v0;
    PlayerSub8 *t2;
    PlayerSub8 *unk_2C;
    PlayerSub8 *a0;
    s16 sp26;
    s16 *sp20;

    a2 = player->unk_76;
    unk_2C = player->unk_2C;
    sp20 = player->unk_34;
    t2 = NULL;

    while (sp20[a2] >= 0) {
        a0 = unk_2C + sp20[a2];
        v0 = a0->flags;
        if (v0 & 2) {
            if (((v0 & 0x10) && (!(v0 & 0x800) || !(player->unk_80 & 8)))) {
                a2 += 2;
                continue;
            }
            t2 = a0;
            sp26 = a2;
            break;
        }
        a2 += 2;
    }

    if (t2 != NULL) {
        D_80080236 = TRUE;
        if (func_80005EE4(player, TRUE, sp26)) {
            player->unk_76 = sp20[sp26 + 1];
            D_80080236 = FALSE;
            return TRUE;
        }
        D_80080236 = FALSE;
    }

    return FALSE;
}
