#include "common.h"

const char D_80055050[] = "dusthit.sp3";

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002F9A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002F9E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FA2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FA78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FA98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FADC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FBC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FD78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FEA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FEB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FEC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8002FF7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_800301FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_800302A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030330.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_800305FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_800306FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_800307C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030824.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8003088C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030908.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030954.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_800309B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_800309EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030A60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030AFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030B74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030C68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030D60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030E88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030F00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030F40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80030F5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8003102C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_80031088.s")

void func_800310C8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    if ((opponent->unk_90->unk_34 & 0x100) || (opponent->unk_98->unk_00 & 0x10)) {
        opponent->unk_80 |= 0x10;
    } else {
        opponent->unk_80 &= ~0x10;
    }
}

void func_80031164(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->spriteId == player->unk_90->unk_02 - 1) {
        func_800310C8(obj);
    }
}

void func_800311A0(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    if (opponent->unk_90->unk_34 & 0x100) {
        opponent->unk_80 |= 0x10;
    }

    if (obj->spriteId >= 24) {
        player->unk_80 &= ~0x10;
    }
}

void func_80031234(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    Object *sp24 = D_80080228[PLAYER_1];
    Object *sp20 = D_80080228[PLAYER_2];
    s16 sp1E;
    s16 sp1C;
    s16 sp1A;

    if (opponent->unk_90->unk_20 != 0) {
        opponent->unk_80 |= 0x10;
    }

    if (!(player->unk_80 & 0x10) && (player->unk_80 & 0x8) && (player->unk_7E == 39 || player->unk_7E == 84)) {
        if (player->playerId != PLAYER_1) {
            sp1C = (0xC00 - sp20->rotation.y) & 0xFFF;
            sp1A = func_8002CDFC(D_8008020C - 0x800, sp1C);

            if (abs(sp1A) > 140) {
                if (sp1A < 0) {
                    sp1A = -140;
                } else {
                    sp1A = 140;
                }
            }
            sp20->rotation.y = 0xC00 - (sp1C + sp1A);
        } else {
            sp1E = (0xC00 - sp24->rotation.y) & 0xFFF;
            sp1A = func_8002CDFC(D_8008020C, sp1E);

            if (abs(sp1A) > 140) {
                if (sp1A < 0) {
                    sp1A = -140;
                } else {
                    sp1A = 140;
                }
            }
            sp24->rotation.y = 0xC00 - (sp1E + sp1A);
        }
    }
}

void func_800313EC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Object *player1 = D_80080228[PLAYER_1];
    Object *player2 = D_80080228[PLAYER_2];

    if (!(player->unk_80 & 8) && obj->spriteId >= player->unk_90->unk_02 - 1) {
        if (player->playerId != PLAYER_1) {
            player2->rotation.y = 0xC00 - D_8008020C;
        } else {
            player1->rotation.y = 0x1400 - D_8008020C;
        }
    }
}

void func_8003146C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent;
    s32 v12;
    s16 a3;

    opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    a3 = opponent->unk_7E;
    switch (a3) {
        case 36:
        case 48:
        case 81:
        case 82:
        case 88:
        case 89:
        case 94:
        case 118:
        case 119:
        case 120:
        case 121:
            v12 = TRUE;
            break;
        default:
            v12 = FALSE;
            break;
    }

    if (a3 == 52) {
        v12 = TRUE;
        if (opponent->unk_80 & 0x10) {
            if (opponent->playerId != PLAYER_1) {
                opponent->unk_00->rotation.y = 0x1400 - D_8008020C;
            } else {
                opponent->unk_00->rotation.y = 0xC00 - D_8008020C;
            }
        } else {
            if (opponent->playerId != PLAYER_1) {
                opponent->unk_00->rotation.y = 0xC00 - D_8008020C;
            } else {
                opponent->unk_00->rotation.y = 0x1400 - D_8008020C;
            }
        }
    }

    if (player->unk_DBC > 256 || (opponent->unk_90->unk_34 & 2) || v12) {
        player->unk_80 |= 0x10;
        obj->currentTask->flags |= 0x80;
    }
}

u8 func_800315FC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (D_800B6328[player->playerId].unk_02) {
        return TRUE;
    }

    return gPlayerInput[player->playerId].unk_09;
}

u8 func_80031648(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (D_800B6328[player->playerId].unk_02) {
        return TRUE;
    }

    return ~gPlayerInput[player->playerId].unk_09;
}
