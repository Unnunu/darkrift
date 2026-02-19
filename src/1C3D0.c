#include "common.h"
#include "task.h"

extern s16 D_80049D10[];
extern s16 D_80049D24[];

s32 func_8001C404(Player *, s16 **);

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

#ifdef NON_EQUIVALENT
void func_8001BB2C(Player *player) {
    s32 temp;
    s32 temp2;

    temp = player->unk_A8.unk_A8;
    temp2 = player->unk_A8.unk_AC;
    player->unk_A8.unk_A8 = 0;
    player->unk_A8.unk_B0 = temp2;
    player->unk_A8.unk_AC = temp;

    player->unk_A8.unk_BC = NULL;
    player->unk_A8.unk_B4 = player->unk_A8.unk_B8 = NULL;
    player->unk_180 &= ~0x3C000;
    player->moveTimeout = 0;

    if (player->flags & PLAYER_FLAG_2000) {
        player->unk_180 |= 0x4000;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BB2C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BB80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BC7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BD5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BF40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C02C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C1C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C2B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C404.s")
s32 func_8001C404(Player *, s16 **);

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C48C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C53C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CB74.s")

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
