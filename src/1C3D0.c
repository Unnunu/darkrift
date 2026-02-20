#include "common.h"
#include "task.h"

extern s16 D_80049D10[];
extern s16 D_80049D24[];
extern s16 (*D_80049D74[])(struct Player *);

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

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CC18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CC8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CD28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CDAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CDE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CE0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CE18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D070.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D1F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D44C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D660.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D6C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D9B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DA10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DA90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DB2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DC68.s")

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
