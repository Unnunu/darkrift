#include "common.h"
#include "camera.h"

typedef struct UnkVec2s {
    s16 unk_00;
    s16 unk_02;
} UnkVec2s;

const char D_80055050[] = "dusthit.sp3";

extern UnkVec2s D_8004B920[];
extern Unk_8004BA6C *D_8004BA6C[];
extern u32 D_8004C1A4[];

extern Object *D_80052D60;

void func_80031DCC(Object *);
void func_80030DA8(Object *);
void func_800310C8(Object *);
void func_800309B4(Object *);
void func_8003088C(Object *);

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

void func_800305FC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 characterId;
    s16 oppId;
    s32 unused[3];

    if (obj->spriteId == player->unk_90->unk_04) {
        characterId = player->characterId;
        oppId = 1 - player->playerId;
        func_800063C4(&gPlayers[oppId], D_8004B920[characterId].unk_02, 1);

        if (player->characterId == AARON) {
            obj->currentTask->func = func_80021E34;
        } else if (D_8004BA6C[characterId] != NULL) {
            obj->currentTask->func = func_80031DCC;
        } else {
            obj->currentTask->flags |= 0x80;
        }
    }
}

void func_800306FC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (player->characterId == SONORK) {
        obj->currentTask->func = func_80021E34;
    } else if (D_8004BA6C[player->characterId] != NULL) {
        obj->currentTask->func = func_80031DCC;
    } else {
        obj->currentTask->flags |= 0x80;
    }
}

u8 func_80030764(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[1 - player->playerId];

    if (opponent->unk_80 & 0x10000) {
        return TRUE;
    } else {
        return FALSE;
    }
}

u8 func_800307C4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[1 - player->playerId];

    if (opponent->unk_80 & 0x2000) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void func_80030824(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] > 60) {
        obj->flags |= 0x10;
        D_8013C830 = 0;
        D_80052D60 = 0;
    } else if (D_8013C830 > 0) {
        D_8013C830 -= 10;
    } else {
        obj->fn_render = func_8003088C;
    }
}

void func_8003088C(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] > 60) {
        obj->flags |= 0x10;
        D_8013C830 = 0;
        D_80052D60 = 0;
    } else if (D_8013C830 < obj->vars[1]) {
        D_8013C830 += 10;
    } else {
        obj->fn_render = func_80030824;
        obj->vars[1] -= 15;
    }
}

Object *func_80030908(void) {
    if (D_80052D60 != NULL) {
        D_80052D60->flags |= 0x10;
    }

    D_80052D60 = create_worker(func_8003088C, 0x1000);
    return D_80052D60;
}

void func_80030954(Object *obj) {
    if (obj->modInst->unk_010.local_matrix.w.y > -200.0f) {
        func_800287AC(obj);
        obj->currentTask->func = func_800309B4;
        obj->currentTask->counter = 20;
    }
}

void func_800309B4(Object *obj) {
    if (obj->modInst->unk_010.local_matrix.w.y > -200.0f) {
        return;
    }

    obj->currentTask->func = func_80030954;
}

void func_800309EC(Object *obj) {
    Object *v0;

    if (obj->modInst->unk_010.local_matrix.w.y > -200.0f) {
        func_800287AC(obj);
        v0 = func_80030908();
        if (v0 != NULL) {
            v0->vars[1] = 50;
        }

        obj->currentTask->func = func_800309B4;
        obj->currentTask->counter = 20;
    }
}

void func_80030A60(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->spriteId > (player->unk_90->unk_02 >> 1)) {
        player->unk_0C->func = func_80024078;
        player->unk_0C->counter = 0;
        player->unk_0C->flags = 1;
    } else {
        player->unk_0C->func = func_80023ED0;
        player->unk_0C->counter = 0;
        player->unk_0C->flags = 1;
        obj->flags |= 0x8000;
    }

    player->unk_80 &= ~0x10;
    obj->currentTask->flags |= 0x80;
}

void func_80030AFC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    obj->unk_010.y += obj->unk_000.y;
    obj->pos.y += obj->unk_010.y >> 16;

    if (obj->pos.y >= 0) {
        obj->pos.y = 0;
        if (player->unk_80 & 0x8) {
            func_800063C4(player, 117, 1);
        } else {
            func_800063C4(player, 83, 1);
        }
    }
}

void func_80030B74(Object *obj) {
    obj->unk_010.y = 0xFFEC0000;
    obj->unk_000.y = 0x20000;
    obj->currentTask->func = func_80030AFC;
    func_800310C8(obj);
}

u8 func_80030BB0(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u8 sp1B;
    s32 t8;

    sp1B = FALSE;
    t8 = (0xC00 - obj->rotation.y) & 0xFFF;

    if (obj->flags & 0x800000) {
        return FALSE;
    }

    if (player->playerId != PLAYER_1) {
        if (abs(func_8002CDFC(D_8008020C, t8)) > 0x400) {
            sp1B = TRUE;
        }
    } else {
        if (abs(func_8002CDFC(D_8008020C, t8)) < 0x400) {
            sp1B = TRUE;
        }
    }

    return sp1B;
}

void func_80030C68(Object *obj) {
    s16 v0;

    v0 = (0xC00 - obj->rotation.y) & 0xFFF;
    obj->rotation.y = 0x400 - v0;
}

u8 func_80030C88(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    if (((opponent->unk_90->unk_34 & 0x30600) && !(opponent->unk_90->unk_34 & 0x40000)) > 0) {
        if (player->playerId != PLAYER_1) {
            player->unk_00->rotation.y = 0xC00 - D_8008020C;
        } else {
            player->unk_00->rotation.y = 0x1400 - D_8008020C;
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

void func_80030D60(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    obj->currentTask->counter = player->unk_20[player->unk_7E].unk_00 - obj->spriteId + 2;
    obj->currentTask->func = func_80030DA8;
}

void func_80030DA8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    s32 a1 = 97;

    if ((opponent->unk_80 & 0x30400) && D_80080210 < 400 && obj->spriteId >= player->unk_90->unk_04) {
        if (opponent->unk_90->unk_34 & 0x200) {
            a1 = 206;
        }
        func_800063C4(opponent, a1, 1);
        obj->currentTask->flags |= 0x80;
    }
}

void func_80030E88(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (D_80080210 < D_8004C1A4[player->characterId] && player->unk_7E != 17) {
        func_800063C4(player, 110, 1);
        obj->currentTask->flags |= 0x80;
    }
}

void func_80030F00(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (player->characterId == MORPHIX) {
        obj->currentTask->counter = 2;
    } else {
        obj->currentTask->counter = 6;
    }
    obj->currentTask->func = func_80030E88;
}

u8 func_80030F40(s32 arg0) {
    return D_80080210 > 550;
}

void func_80030F5C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    s16 sp26;
    s16 sp1A;

    sp26 = (0xC00 - opponent->unk_00->rotation.y) & 0xFFF;
    sp1A = func_8002CDFC(D_8008020C, sp26);

    if (sp1A < 0) {
        sp1A -= 0x800;
    } else {
        sp1A += 0x800;
    }
    opponent->unk_00->rotation.y = 0xC00 - (sp26 + sp1A);
}

void func_8003102C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    opponent->unk_80 |= 0x10;
}

void func_80031088(Object *obj) {
    if (obj->pos.y == 0) {
        func_8002856C(obj);
    }

    obj->currentTask->func = func_8003102C;
}

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
