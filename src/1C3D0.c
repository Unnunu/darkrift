#include "common.h"
#include "task.h"

extern s16 D_80049D10[];
extern s16 D_80049D24[];
extern s16 D_80049D34[];
extern s16 D_80049D44[];
extern s16 D_80049D54[];
extern s16 D_80049D64[];
extern s16 (*D_80049D74[])(struct Player *);
extern s16 D_80049DB4[];
extern s16 D_80049DCC[];

u8 func_8001C404(Player *, s16 **);
u8 func_8001BC7C(Player *);
u8 func_8001BD5C(Player *, PlayerSubH *);

u8 func_8001B7D0(Player *player, s16 arg1) {
    func_8001BB2C(player);
    player->unk_180 |= 0x8000;
    return func_8000636C(player, arg1, 1);
}

void func_8001B810(Player *player) {
    s32 v04;
    s16 *sp30;
    PlayerSubH *v1;
    u16 sp2A;
    s16 v02;

    sp2A = gBattleSettings[player->playerId].unk_04;
    if (player->obj->playerHp == 0) {
        return;
    }

    if (!(player->currentState->flags & STATE_FLAG_4000)) {
        player->unk_DC = 0;
    }

    if (player->unk_180 & 0x8000) {
        v1 = &player->unk_A8;
        if (player->moveTimeout != 0 && --player->moveTimeout == 0) {
            func_8001BB2C(player);
            if (player->nextLogicState >= 0 && (player->flags & PLAYER_FLAG_1000)) {
                if (ai_select_transition(player)) {
                    player->unk_180 |= 0x8000;
                }
            }
        } else if (v1->unk_BC != NULL) {
            v02 = v1->unk_BC(player);
            if (v02 > 0) {
                return;
            }

            v1->unk_BC = NULL;
            player->unk_180 &= ~0x8000;
            if (v02 < 0) {
                func_8001BB2C(player);
            } else {
                func_8001BB80(player);
            }
        } else if (player->moveTimeout == 0 && player->obj->frameIndex >= player->currentState->unk_02 - 1) {
            player->moveTimeout = 512;
        }
    } else if (!(player->animTask->flags & TASK_FLAG_FRAME_TRIGGER) &&
               !(player->flags & PLAYER_FLAG_TRANSITION_LOCKED)) {
        if (func_80030BB0(player->obj) && !(player->currentState->flags & STATE_FLAG_80) &&
            !(player->obj->flags & OBJ_FLAG_800000)) {
            if (player->currentState->flags & STATE_FLAG_1) {
                func_8001B7D0(player, 0x62);
                return;
            }
            if (player->currentState->flags & STATE_FLAG_4) {
                func_8001B7D0(player, 0x5F);
                return;
            }
        }

        v04 = func_8001C404(player, &sp30);
        if ((player->obj->flags & OBJ_FLAG_800000) || (player->flags & PLAYER_FLAG_2000)) {
            return;
        }

        if ((--player->unk_DBE <= 0 || (v04 & 0xFF) && !(*sp30 & 2)) &&
                (player->currentState->flags & (STATE_FLAG_1 | STATE_FLAG_4)) ||
            player->currentTransition->unk_19 != 0xFF) {
            player->unk_DBE = D_80049D10[sp2A];
            player->unk_DBE += guRandom() & D_80049D24[sp2A];

            if (!func_8001C53C(player, (player->flags & PLAYER_FLAG_200000) != 0)) {
                player->unk_DBE = 0;
            }
        }
    }
}

void func_8001BB2C(Player *player) {
    player->unk_A8.unk_B0 = player->unk_A8.unk_AC;
    player->unk_A8.unk_AC = player->unk_A8.unk_A8;
    player->unk_A8.unk_A8 = 0;

    player->unk_A8.unk_BC = NULL;
    player->unk_A8.unk_B4 = player->unk_A8.unk_B8 = NULL;
    player->unk_180 &= ~0x3C000;
    player->moveTimeout = 0;

    if (player->flags & PLAYER_FLAG_2000) {
        player->unk_180 |= 0x4000;
    }
}

u8 func_8001BB80(Player *player) {
    PlayerSubH *subH = &player->unk_A8;

    if (player->flags & PLAYER_FLAG_2000 || (player->unk_DBC > 0x100 && !(subH->unk_C8 & 0x1000)) ||
        player->currentTransition->stateId != player->stateId) {
        func_8001BB2C(player);
        return FALSE;
    }

    if (func_8001BC7C(player)) {
        return TRUE;
    }

    if (subH->unk_B4 == NULL || *subH->unk_B4 == -1 || (player->unk_180 & 0x10000)) {
        func_8001BB2C(player);
        return FALSE;
    }

    subH->unk_B4++;

    if (subH->unk_B4 == NULL || *subH->unk_B4 == -1) {
        func_8001BB2C(player);
        return FALSE;
    }

    func_8001BD5C(player, subH);
    return func_8001BC7C(player);
}

u8 func_8001BC7C(Player *player) {
    PlayerSubH *subH = &player->unk_A8;
    s16 sp22 = (player->playerId != PLAYER_1) ? PLAYER_1 : PLAYER_2;

    if (subH->unk_B8 != NULL && *subH->unk_B8 != -1) {
        if (func_8000636C(player, *subH->unk_B8, 1)) {
            subH->unk_CE = gPlayers[sp22].obj->playerHp;
            player->unk_180 |= 0x8000;
            subH->unk_B8++;
            return TRUE;
        }

        func_8001BB2C(player);
        return FALSE;
    }
    return FALSE;
}

#ifdef NON_EQUIVALENT
u8 func_8001BD5C(Player *player, PlayerSubH *subH) {
    s32 a2;
    s32 pf;
    u8 a3;

    while (TRUE) {
        a2 = player->currentState->flags;
        pf = player->flags;
        subH->unk_B8 = player->unk_50 + player->unk_54[*subH->unk_B4];
        subH->unk_BC = ((s16) (*subH->unk_B8) == -1) ? NULL : D_80049D74[*subH->unk_B8];
        subH->unk_B8++;

        subH->unk_C0 = *subH->unk_B8++;
        subH->unk_C4 = *subH->unk_B8++;

        a3 = (subH->unk_C4 & a2 & 0x400) && ((a2 & 0x200) == (subH->unk_C4 & 0x200));
        if (a3 && (subH->unk_C4 & 8) && (pf & 8) != (subH->unk_C4 & 8)) {
            a3 = FALSE;
        }

        if ((subH->unk_C4 & 0x1000) || a3 ||
            (!(subH->unk_C4 & 0x4000) || (a2 & 0x4000) != (subH->unk_C4 & 0x4000)) && (pf & 8) == (subH->unk_C4 & 8) &&
                (subH->unk_C4 & a2 & 5)) {
            subH->unk_CE = gPlayers[1 - player->playerId].obj->playerHp;
            player->unk_180 &= ~0x3C000;
            player->unk_180 |= 0x8000;
            if (subH->unk_C4 & 0x8000) {
                player->unk_180 |= 0x10000;
            }
            return TRUE;
        }

        // subH->unk_B4++;
        if (++*subH->unk_B4 < 0) {
            func_8001BB2C(player);
            return FALSE;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BD5C.s")
#endif

void func_8001BF40(Player *player) {
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
        ptr = player->unk_60 + player->unk_64[i];
        ptr[3] = a3;
        ptr[2] = ptr[1];
    }

    func_8001BB2C(player);
    player->unk_180 = 0x20000;
}

void func_8001C02C(Player *player) {
    s16 a1;
    s16 i;
    s16 *ptr;
    s16 a3;

    a1 = player->unk_DBA;
    for (i = 0; i < a1; i++) {
        ptr = player->unk_60 + player->unk_64[i];
        ptr[3] = 0;
        ptr[2] = ptr[1];
    }

    func_8001BB2C(player);

    a3 = gBattleSettings[player->playerId].unk_04;
    if (a3 == 0x7FFF) {
        a3 = 0;
    }
    gBattleSettings[player->playerId].unk_04 = 0;

    for (i = 0; i < a3; i++) {
        func_8001BF40(player);
    }

    player->unk_180 = 0x20000;
}

void func_8001C114(Player *player) {
    s16 a1;
    s16 i;
    s16 *ptr;

    a1 = player->unk_DBA;
    for (i = 0; i < a1; i++) {
        ptr = player->unk_60 + player->unk_64[i];
        ptr[3] = 0;
        ptr[2] = ptr[1];
    }

    func_8001BB2C(player);
    gBattleSettings[player->playerId].unk_04 = 0;
    gBattleSettings[player->playerId].unk_04 = 0;
    player->unk_180 = 0x20000;
}

void func_8001C1C0(Player *player) {
    s16 a1;
    s16 i;
    s16 *ptr;
    s16 a3;

    a1 = player->unk_DBA;
    for (i = 0; i < a1; i++) {
        ptr = player->unk_60 + player->unk_64[i];
        ptr[3] = 0;
        ptr[2] = ptr[1];
    }

    func_8001BB2C(player);

    gBattleSettings[player->playerId].unk_04 = 8;
    a3 = gBattleSettings[player->playerId].unk_04;
    gBattleSettings[player->playerId].unk_04 = 0;

    for (i = 0; i < a3; i++) {
        func_8001BF40(player);
    }

    player->unk_180 = 0x20000;
}

u8 func_8001C2B4(Player *player, s16 **arg1, u8 arg2) {
    s32 v1;
    s16 a3;
    s16 *ptr;
    Player *opp;
    s16 a1;
    s16 a2;

    opp = gPlayers + 1 - player->playerId;

    if (arg2) {
        v1 = (gPlayers[1 - player->playerId].currentState->flags & 1) ? 320 : 68;
        a1 = opp->unk_38[v1];
        a2 = opp->logicStates[a1];
        a3 = opp->transitionTable[a2].unk_0E[player->characterId];
    } else {
        a3 = gPlayers[1 - player->playerId].currentTransition->unk_0E[player->characterId];
        if (a3 == 0xFF) {
            return FALSE;
        }
    }

    ptr = player->unk_60 + player->unk_64[a3];
    if (!(ptr[0] & 1)) {
        a3 += ptr[3];
        ptr = player->unk_60 + player->unk_64[a3];
    }
    *arg1 = ptr;
    return TRUE;
}

u8 func_8001C404(Player *player, s16 **arg1) {
    s16 a3;
    s16 *ptr;

    a3 = gPlayers[1 - player->playerId].currentTransition->unk_0E[player->characterId];
    if (a3 == 0xFF) {
        return FALSE;
    }

    ptr = player->unk_60 + player->unk_64[a3];
    *arg1 = ptr;
    return TRUE;
}

u8 func_8001C48C(Player *player, s16 **arg1) {
    s16 a3;
    s16 *ptr;

    a3 = gPlayers[player->playerId].currentTransition->unk_19;
    if (a3 == 0xFF) {
        return FALSE;
    }

    ptr = player->unk_60 + player->unk_64[a3];
    if (!(ptr[0] & 1)) {
        a3 += ptr[3];
        ptr = player->unk_60 + player->unk_64[a3];
    }

    *arg1 = ptr;
    return TRUE;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C53C.s")

s16 func_8001CB74(Player *player) {
    s16 *sp24;
    u8 v0;

    if (player->obj->frameIndex < (player->currentState->unk_02 >> 1)) {
        return TRUE;
    }

    v0 = func_8001C404(player, &sp24);
    return (player->unk_A8.unk_C0 < D_80080210) && !(player->flags & 8) && (!v0 || (*sp24 & 2));
}

s16 func_8001CC18(Player *player) {
    s16 *sp24;
    u8 v0;

    v0 = func_8001C404(player, &sp24);
    return (player->unk_A8.unk_C0 < D_80080210) && !(player->flags & 8) && (!v0 || (*sp24 & 2));
}

s16 func_8001CC8C(Player *player) {
    s16 *sp24;
    u8 v0;

    v0 = func_8001C404(player, &sp24);

    if (player->obj->frameIndex < (player->currentState->unk_02 >> 1)) {
        return TRUE;
    }

    return (player->unk_A8.unk_C0 > D_80080210) && !(player->flags & 8) && (!v0 || (*sp24 & 2));
}

s16 func_8001CD28(Player *player) {
    return FALSE;
}

s16 func_8001CD34(Player *player) {
    s16 *sp24;
    u8 v0;

    v0 = func_8001C404(player, &sp24);

    if (player->unk_A8.unk_C0) {
        player->unk_A8.unk_C0--;
    }

    return (player->unk_A8.unk_C0) && !(player->flags & 8) && (!v0 || (*sp24 & 2));
}

s16 func_8001CDAC(Player *player) {
    if (player->obj->frameIndex < (player->currentState->unk_02 >> 1)) {
        return TRUE;
    }

    return FALSE;
}

s16 func_8001CDE0(Player *player) {
    player->unk_A8.unk_C0--;

    if (player->unk_A8.unk_C0 > 0) {
        return TRUE;
    } else {
        return -1;
    }
}

s16 func_8001CE0C(Player *player) {
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CE18.s")

s16 func_8001D070(Player *player) {
    s16 oppId = 1 - player->playerId;
    s32 pad;
    s16 *sp24;
    u8 v0;

    if (player->flags & 0x2000) {
        return TRUE;
    }

    if (player->unk_DC >= D_80049D34[gBattleSettings[player->playerId].unk_04] &&
        !(gPlayers[1 - player->playerId].flags & 0x02000000)) {
        return FALSE;
    }

    player->unk_A8.unk_C0--;
    v0 = func_8001C404(player, &sp24);
    if (v0 && !(*sp24 & 2)) {
        if (!(*sp24 & 4)) {
            func_800063C4(player, 56, TRUE);
        }
        return TRUE;
    }

    if (gPlayers[oppId].flags & 8) {
        player->stateId = 0x2a;
        return -1;
    }

    return (player->unk_A8.unk_C0 > 0) || !(*sp24 & 2);
}

u8 func_8001D1F8(Player *player) {
    switch (gDifficulty) {
        case 0:
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
        case 1:
        case 2:
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

    player->unk_A8.unk_C0--;

    if (player->unk_DC < D_80049D34[gBattleSettings[playerId].unk_04]) {
        v0 = func_8001C404(player, &sp24);
        if (v0 && !(*sp24 & 2) && !(*sp24 & 4)) {
            func_800063C4(player, 56, TRUE);
            return TRUE;
        }
    }

    return TRUE;
}

s32 func_8001D44C(Player *player) {
    s16 *sp34;
    s16 oppId;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    Player *opponent;

    oppId = 1 - player->playerId;
    sp30 = gPlayers[oppId].obj->frameIndex;
    sp2E = gPlayers[oppId].currentState->unk_06;
    sp2C = gPlayers[oppId].currentState->unk_04;

    player->unk_A8.unk_C0--;

    if (player->unk_DC < D_80049D34[gBattleSettings[player->playerId].unk_04]) {
        if (func_8001C404(player, &sp34)) {
            if (!(*sp34 & 2) && !(*sp34 & 4)) {
                func_800063C4(player, 56, TRUE);
                return 1;
            }
        }
    }

    opponent = gPlayers + oppId;
    if (!(opponent->flags & PLAYER_FLAG_2000000)) {
        if ((sp30 < sp2C && D_80049DB4[opponent->characterId] < sp2C - sp30) ||
            (sp2E < sp30 && D_80049DCC[opponent->characterId] < gPlayers[oppId].currentState->unk_02 - sp2E) ||
            ((gPlayers[1 - player->playerId].flags & PLAYER_FLAG_TRANSITION_LOCKED) &&
             gPlayers[1 - player->playerId].obj->frameIndex < 6)) {
            player->flags &= ~0x2000;
            return -1;
        }
    }

    return 1;
}

void func_8001D660(Player *player) {
    player->unk_DE = 0;
    player->unk_DC++;

    if (func_8001D1F8(player)) {
        player->unk_A8.unk_BC = func_8001D44C;
        func_8001D44C(player);
    } else {
        player->unk_A8.unk_BC = func_8001D3A8;
        func_8001D3A8(player);
    }
}

s16 func_8001D6C0(Player *player) {
    s32 pad[2];
    s16 *sp24;
    u8 v0;
    s16 playerId = player->playerId;

    player->unk_A8.unk_C0--;

    if (player->unk_DC < D_80049D34[gBattleSettings[playerId].unk_04]) {
        v0 = func_8001C404(player, &sp24);
        if (v0 && !(*sp24 & 2) && (*sp24 & 4)) {
            func_800063C4(player, 57, TRUE);
            return TRUE;
        }
    }

    return TRUE;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D764.s")
void func_8001D764(Player *player);

void func_8001D9B0(Player *player) {
    player->unk_DE = 0;
    player->unk_DC++;

    if (func_8001D1F8(player)) {
        player->unk_A8.unk_BC = func_8001D764;
        func_8001D764(player);
    } else {
        player->unk_A8.unk_BC = func_8001D6C0;
        func_8001D6C0(player);
    }
}

u8 func_8001DA10(Player *player) {
    s16 sp1E;

    sp1E = gBattleSettings[player->playerId].unk_04;
    player->unk_A8.unk_C0 = D_80049D44[sp1E] + (guRandom() & D_80049D24[sp1E]); // @BUG ??
    player->unk_A8.unk_BC = func_8001CDE0;
    return TRUE;
}

u8 func_8001DA90(Player *player) {
    s16 *sp24;
    s32 v0;

    v0 = func_8001C404(player, &sp24);

    if (player->obj->frameIndex < (player->currentState->unk_02 >> 1) && !(player->flags & 8)) {
        return TRUE;
    }

    if (player->obj->frameIndex < player->currentState->unk_02 - 1 && !(player->flags & 8) && (!v0 || (*sp24 & 2))) {
        return TRUE;
    }

    return FALSE;
}

s32 func_8001DB2C(Player *player) {
    s16 sp24;
    s32 pad;
    s16 pad2;
    s16 sp2C;

    sp24 = gBattleSettings[player->playerId].unk_04;
    sp2C = D_80049D54[sp24];
    sp2C += guRandom() % D_80049D64[sp24];
    player->unk_DE++;

    if (sp2C < player->unk_DE || (gPlayers[1 - player->playerId].flags & PLAYER_FLAG_100000)) {
        player->unk_A8.unk_B4++;
        func_8001BD5C(player, &player->unk_A8);
        func_8001BC7C(player);
        player->unk_A8.unk_C0 = 90;
        return 1;
    } else {
        return -1;
    }
}

s32 func_8001DC68(Player *player) {
    s16 sp24;
    s32 pad;
    s16 pad2;
    s16 sp2C;

    sp24 = gBattleSettings[player->playerId].unk_04;
    sp2C = D_80049D54[sp24];
    sp2C += guRandom() % D_80049D64[sp24];
    player->unk_DE++;

    if (sp2C < player->unk_DE || (gPlayers[1 - player->playerId].flags & PLAYER_FLAG_100000)) {
        player->unk_A8.unk_B4++;
        func_8001BD5C(player, &player->unk_A8);
        func_8001BC7C(player);
        player->unk_A8.unk_C0 = 90;
        return 1;
    } else {
        return -1;
    }
}

s32 func_8001DDA4(Player *player) {
    s16 *sp1C;

    if (func_8001C404(player, &sp1C) != 0) {
        if (!(*sp1C & 2)) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}

s32 func_8001DDEC(Object *obj) {
    obj->vars[11] = 0;
    obj->vars[9] -= 4;
    return 1;
}
