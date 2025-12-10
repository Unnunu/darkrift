#include "common.h"
#include "camera.h"
#include "task.h"

void func_8002FA98(Object *obj);
void func_80031DCC(Object *);
void func_80030DA8(Object *);
void func_800310C8(Object *);
void func_800309B4(Object *);
void func_8003088C(Object *);
void func_800309EC(Object *);
void func_80031D4C(Object *);
void func_80031E4C(Unk_8004BA6C *, PlayerSub9 *, Object *);

UnkK2Def D_80052CF0 = { "dusthit.sp3", func_8002FA98, 0, 0x1100, 0, 0x2800, 0 };
s32 D_80052D08[] = { 14, 17, 18, 21, 21, 24, 12, 15, 11, 14, 0, 0, 14, 17, 18, 21, 11, 14, 14, 17, 11, 14 };
Object *D_80052D60 = NULL;
s16 D_80052D64[] = { 0, 0 };
s16 D_80052D68[] = { 0, 0 };
s16 D_80052D6C[] = { 0, 0 };
s16 D_80052D70[] = { 0, 0 };
s16 D_80052D74[] = { 0, 0 };
s16 D_80052D78[] = { 2, 2 };

Vec4i D_8013C3A0[2];
s16 D_8013C3C0[2];
s32 D_8013C3C8[2];

u8 func_8002F9A0(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    return (player->flags & PLAYER_FLAG_800000) || gBattleSettings[player->playerId].isCpu;
}

void func_8002F9E8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex > 5 && (player->flags & PLAYER_FLAG_10)) {
        player->flags &= ~0x10;
        obj->currentTask->flags |= 0x80;
    }
}

void func_8002FA2C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    player->flags &= ~PLAYER_FLAG_800000;
    if (!(player->currentState->flags & 1)) {
        player->flags &= ~PLAYER_FLAG_10;
    }
    obj->currentTask->func = task_default_func;
}

void func_8002FA78(Object *obj) {
    obj->currentTask->counter = 10;
    obj->currentTask->func = func_8002FA2C;
}

void func_8002FA98(Object *obj) {
    obj->unk_088.a -= 5;
    obj->frameIndex++;
    if (obj->frameIndex > 9) {
        obj->flags |= 0x10;
    }
    obj->currentTask->counter = 2;
}

void func_8002FADC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 playerId = player->playerId;
    Vec4i *s1;
    Object *v0;
    Vec4i sp28;

    s1 = &D_8013C3A0[playerId];

    if ((abs(s1->x - obj->pos.x) > 20 || abs(s1->z - obj->pos.z) > 20) && !(player->flags & PLAYER_FLAG_400000)) {
        sp28.x = obj->pos.x;
        sp28.z = obj->pos.z;
        sp28.y = 0;
        v0 = create_3dsprite_with_properties(&sp28, &D_80052CF0, 0xABAB);
        if (v0 != NULL) {
            v0->unk_088.a = 60;
        }
    }

    s1->x = obj->pos.x;
    s1->z = obj->pos.z;
    if (--obj->vars[3] < 0) {
        player->total_damage = 0;
    }
}

void func_8002FBC8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 v0;
    s32 dx, dz;

    v0 = 0;
    dx = player->unk_198.unk_14->x - player->unk_198.unk_18->x;
    dz = player->unk_198.unk_14->z - player->unk_198.unk_18->z;

    if (dx != 0 || dz != 0) {
        v0 = (u32) (sqrtf(SQ(dx) + SQ(dz)) + 0.5) >> 1;
    }
    if (v0 < 150) {
        v0 = 150;
    }

    player->unk_198.unk_30 = SQ(v0);
    v0 = (v0 * 0xE000) >> 16;
    player->unk_198.unk_2C = SQ(v0);

    if (player->currentState->flags & 4) {
        obj->currentTask->func = func_8002FADC;
    } else {
        func_8002FA78(obj);
    }
    obj->vars[3] = 50;
}

void func_8002FD78(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 playerId = player->playerId;

    player->flags &= ~PLAYER_FLAG_400;
    obj->modInst->unk_A1C = D_8004BA98[player->characterId].x;
    obj->modInst->unk_A20 = D_8004BA98[player->characterId].z;
    obj->currentTask->counter = 2;
    obj->currentTask->func = func_8002FBC8;
    obj->currentTask->counter = 2;
    D_8013C3A0[playerId].x = obj->pos.x;
    D_8013C3A0[playerId].z = obj->pos.z;
}

void func_8002FE10(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 playerId = player->playerId;

    player->flags &= ~PLAYER_FLAG_400;
    obj->modInst->unk_A20 = D_8004BAF0[player->characterId].z;
    obj->modInst->unk_A1C = D_8004BAF0[player->characterId].x;
    obj->currentTask->counter = 2;
    obj->currentTask->func = func_8002FBC8;
    D_8013C3A0[playerId].x = obj->pos.x;
    D_8013C3A0[playerId].z = obj->pos.z;
}

void func_8002FEA0(Object *obj) {
    obj->currentTask->flags |= 0x80;
}

void func_8002FEB4(Object *obj) {
    obj->currentTask->flags |= 0x80;
}

void func_8002FEC8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 sp1A;
    s32 temp;
    s16 v1;

    sp1A = (0xC00 - obj->rotation.y) & 0xFFF;

    temp = func_8002CDFC(D_8008020C - (player->playerId != PLAYER_1 ? 0 : 0x800), sp1A);
    if (temp < 0) {
        v1 = temp + 0x800;
    } else {
        v1 = temp - 0x800;
    }

    obj->rotation.y = 0xC00 - sp1A - v1;
    obj->currentTask->flags |= 0x80;
}

u8 func_8002FF7C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 pad[3];
    s16 characterId;
    s16 oppId = 1 - player->playerId;
    s16 temp;
    Vec4i sp34;

    characterId = gPlayers[oppId].characterId;
    temp = D_8004B920[characterId].unk_00;

    sp34.x = 0;
    sp34.y = 0;
    sp34.z = -temp;
    func_8001370C(&sp34, &obj->rotation);
    (gPlayers + oppId)->obj->pos.x = obj->pos.x + sp34.x;
    (gPlayers + oppId)->obj->pos.z = obj->pos.z + sp34.z;
    (gPlayers + oppId)->obj->rotation.y = 0x400 - ((0xC00 - obj->rotation.y) & 0xFFF);

    return TRUE;
}

void func_80030074(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = gPlayers + 1 - player->playerId;
    s16 characterId = player->characterId;

    if (obj->frameIndex == player->currentState->unk_02 - 1) {
        player->damage = obj->vars[2];
        if (obj->vars[3] < 0) {
            player->total_damage += player->damage;
        } else {
            player->total_damage = player->damage;
            obj->vars[3] = -1;
        }

        if (gPlayMode != PLAY_MODE_PRACTICE) {
            opponent->obj->playerHp -= obj->vars[2];
        }
        if (opponent->obj->playerHp < 0) {
            opponent->obj->playerHp = 0;
        }
    }

    switch (characterId) {
        case AARON:
            func_80021DC4(obj);
            break;
        case DEMONICA:
            if (gBattleSettings[1 - player->playerId].characterId == NIIKI &&
                obj->frameIndex < player->currentState->unk_02 - 1) {
                obj->pos.y = 100;
            } else {
                obj->pos.y = 0;
            }
            func_80031D4C(obj);
            break;
        default:
            if (D_8004BA40[characterId] != NULL) {
                func_80031D4C(obj);
            }
            break;
    }
}

void func_800301FC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex >= player->currentState->unk_02 - 2) {
        player->damage = obj->vars[2];
        if (obj->vars[3] < 0) {
            player->total_damage += player->damage;
        } else {
            player->total_damage = player->damage;
            obj->vars[3] = -1;
        }

        if (gPlayMode != PLAY_MODE_PRACTICE) {
            player->obj->playerHp -= obj->vars[2];
        }
        if (player->obj->playerHp < 0) {
            player->obj->playerHp = 0;
        }

        player->unk_18->func = func_8003184C;
    }
}

void func_800302A4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 oppId = 1 - player->playerId;

    player->unk_18->func = func_800301FC;

    if (gPlayers[oppId].characterId != AARON) {
        obj->currentTask->func = func_800309EC;
    } else {
        obj->currentTask->flags |= 0x80;
    }
}

void func_80030330(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 pad[2];
    s16 characterId;
    s16 oppId;
    s32 pad2;
    s16 temp;
    PlayerState *sp44;
    Vec4i sp34;

    if (D_800801F0 && D_8013C250 == 0) {
        obj->currentTask->flags |= 0x80;
        return;
    }

    if (obj->frameIndex != player->currentState->unk_02 - 1) {
        return;
    }

    characterId = player->characterId;
    oppId = 1 - player->playerId;
    player->unk_5F48 = 2;

    if (!(player->flags & PLAYER_FLAG_NOT_FACING_OPP) && D_80080210 < D_8004C178[player->characterId] &&
        (gPlayers[oppId].currentState->flags & 4) && !(gPlayers[oppId].currentState->flags & 0x40000)) {
        obj->currentTask->flags |= 0x80;

        if (gPlayers[oppId].flags & PLAYER_FLAG_NOT_FACING_OPP) {
            if (!(gPlayers[oppId].currentState->flags & 0x80)) {
                func_800063C4(&gPlayers[oppId], 116, 1);
            }
            return;
        }

        player->flags |= PLAYER_FLAG_40000;

        D_80080236 = TRUE;
        func_800063C4(&gPlayers[oppId], D_8004B8F4[characterId].unk_02, 1);
        func_800063C4(player, 84, 1);
        D_80080236 = FALSE;
        sp44 = &player->states[player->stateId];
        player->obj->varObj[2] = sp44->damage;

        temp = D_8004B8F4[characterId].unk_00;
        sp34.x = 0;
        sp34.y = 0;
        sp34.z = -temp;
        func_8001370C(&sp34, &obj->rotation);
        (gPlayers + oppId)->obj->pos.x = obj->pos.x + sp34.x;
        (gPlayers + oppId)->obj->pos.z = obj->pos.z + sp34.z;
        (gPlayers + oppId)->obj->rotation.y = 0x400 - ((0xC00 - obj->rotation.y) & 0xFFF);

        D_8008012C &= ~GFX_FLAG_10;
        func_80016264();

        switch (characterId) {
            case GORE:
                obj->flags |= 0x800;
                break;
            case AARON:
                if (sp44->unk_28 >= 0) {
                    player->unk_9C = &player->unk_4C[sp44->unk_28];
                    player->unk_194 = NULL;
                }
                break;
        }
    }
}

void func_800305FC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 characterId;
    s16 oppId;
    s32 unused[3];

    if (obj->frameIndex == player->currentState->unk_04) {
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

    if (opponent->flags & PLAYER_FLAG_10000) {
        return TRUE;
    } else {
        return FALSE;
    }
}

u8 func_800307C4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[1 - player->playerId];

    if (opponent->flags & PLAYER_FLAG_2000) {
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
    if (obj->modInst->rootTransform.local_matrix.w.y > -200.0f) {
        func_800287AC(obj);
        obj->currentTask->func = func_800309B4;
        obj->currentTask->counter = 20;
    }
}

void func_800309B4(Object *obj) {
    if (obj->modInst->rootTransform.local_matrix.w.y > -200.0f) {
        return;
    }

    obj->currentTask->func = func_80030954;
}

void func_800309EC(Object *obj) {
    Object *v0;

    if (obj->modInst->rootTransform.local_matrix.w.y > -200.0f) {
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

    if (obj->frameIndex > (player->currentState->unk_02 >> 1)) {
        player->unk_0C->func = func_80024078;
        player->unk_0C->counter = 0;
        player->unk_0C->flags = 1;
    } else {
        player->unk_0C->func = func_80023ED0;
        player->unk_0C->counter = 0;
        player->unk_0C->flags = 1;
        obj->flags |= 0x8000;
    }

    player->flags &= ~PLAYER_FLAG_10;
    obj->currentTask->flags |= 0x80;
}

void func_80030AFC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    obj->velocity.y += obj->acceleration.y;
    obj->pos.y += obj->velocity.y >> 16;

    if (obj->pos.y >= 0) {
        obj->pos.y = 0;
        if (player->flags & PLAYER_FLAG_NOT_FACING_OPP) {
            func_800063C4(player, 117, 1);
        } else {
            func_800063C4(player, 83, 1);
        }
    }
}

void func_80030B74(Object *obj) {
    obj->velocity.y = 0xFFEC0000;
    obj->acceleration.y = 0x20000;
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

    if (((opponent->currentState->flags & 0x30600) && !(opponent->currentState->flags & 0x40000)) > 0) {
        if (player->playerId != PLAYER_1) {
            player->obj->rotation.y = 0xC00 - D_8008020C;
        } else {
            player->obj->rotation.y = 0x1400 - D_8008020C;
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

void func_80030D60(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    obj->currentTask->counter = player->states[player->stateId].duration - obj->frameIndex + 2;
    obj->currentTask->func = func_80030DA8;
}

void func_80030DA8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];
    s16 a1 = 97;

    if ((opponent->flags & (PLAYER_FLAG_400 | PLAYER_FLAG_10000 | PLAYER_FLAG_20000)) && D_80080210 < 400 &&
        obj->frameIndex >= player->currentState->unk_04) {
        if (opponent->currentState->flags & 0x200) {
            a1 = 206;
        }
        func_800063C4(opponent, a1, 1);
        obj->currentTask->flags |= 0x80;
    }
}

void func_80030E88(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (D_80080210 < D_8004C1A4[player->characterId] && player->stateId != 17) {
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

    sp26 = (0xC00 - opponent->obj->rotation.y) & 0xFFF;
    sp1A = func_8002CDFC(D_8008020C, sp26);

    if (sp1A < 0) {
        sp1A -= 0x800;
    } else {
        sp1A += 0x800;
    }
    opponent->obj->rotation.y = 0xC00 - (sp26 + sp1A);
}

void func_8003102C(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    opponent->flags |= PLAYER_FLAG_10;
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

    if ((opponent->currentState->flags & 0x100) || (opponent->unk_98->unk_00 & 0x10)) {
        opponent->flags |= PLAYER_FLAG_10;
    } else {
        opponent->flags &= ~PLAYER_FLAG_10;
    }
}

void func_80031164(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex == player->currentState->unk_02 - 1) {
        func_800310C8(obj);
    }
}

void func_800311A0(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = &gPlayers[player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2];

    if (opponent->currentState->flags & 0x100) {
        opponent->flags |= PLAYER_FLAG_10;
    }

    if (obj->frameIndex >= 24) {
        player->flags &= ~PLAYER_FLAG_10;
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

    if (opponent->currentState->damage != 0) {
        opponent->flags |= PLAYER_FLAG_10;
    }

    if (!(player->flags & PLAYER_FLAG_10) && (player->flags & PLAYER_FLAG_NOT_FACING_OPP) &&
        (player->stateId == 39 || player->stateId == 84)) {
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

    if (!(player->flags & PLAYER_FLAG_NOT_FACING_OPP) && obj->frameIndex >= player->currentState->unk_02 - 1) {
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
    a3 = opponent->stateId;
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
        if (opponent->flags & PLAYER_FLAG_10) {
            if (opponent->playerId != PLAYER_1) {
                opponent->obj->rotation.y = 0x1400 - D_8008020C;
            } else {
                opponent->obj->rotation.y = 0xC00 - D_8008020C;
            }
        } else {
            if (opponent->playerId != PLAYER_1) {
                opponent->obj->rotation.y = 0xC00 - D_8008020C;
            } else {
                opponent->obj->rotation.y = 0x1400 - D_8008020C;
            }
        }
    }

    if (player->unk_DBC > 256 || (opponent->currentState->flags & 2) || v12) {
        player->flags |= PLAYER_FLAG_10;
        obj->currentTask->flags |= 0x80;
    }
}

u8 func_800315FC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (gBattleSettings[player->playerId].isCpu) {
        return TRUE;
    }

    return gPlayerInput[player->playerId].mirrored;
}

u8 func_80031648(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (gBattleSettings[player->playerId].isCpu) {
        return TRUE;
    }

    return ~gPlayerInput[player->playerId].mirrored;
}

u8 func_800316A0(Object *obj) {
    Player *player;
    Player *v1;
    s32 a1;

    player = (Player *) obj->varObj[0];
    v1 = gPlayers + (1 - player->playerId);

    a1 = (v1->currentState->flags & 0x100000) &&
         (v1->currentState->unk_06 < v1->obj->frameIndex || v1->currentState->unk_04 > v1->obj->frameIndex);
    return a1 > 0;
}

void func_80031724(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *v0;
    PlayerState *v1;

    v0 = gPlayers + (1 - player->playerId);
    v1 = &player->states[player->stateId];

    if (!(v1->flags & 0x4000) && gBattleSettings[player->playerId].isCpu && (v0->currentState->flags & 0x100000) &&
        v0->obj->frameIndex < v0->currentState->unk_04) {
        if (v0->flags & PLAYER_FLAG_1) {
            func_800063C4(player, 0x27, 1);
            player->unk_A8.unk_BC = func_8001D070;
            player->unk_C0 = 60;
        } else {
            func_800063C4(player, 0x3B, 1);
            player->unk_A8.unk_BC = func_8001CE18;
            player->unk_C0 = 60;
        }
    }
}

#ifdef NON_EQUIVALENT
void func_8003184C(Object *arg0) {
    Vec4s sp60;
    Vec4s sp58;
    Player *temp_ra;
    u8 temp_v1;
    u8 temp_t8;
    s16 temp_v0;
    s32 temp_ft3;
    s16 var_t3;

    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v1_3;

    s16 var_t2;

    s16 var_a2;
    s16 var_t0;

    temp_ra = (Player *) arg0->varObj[0];
    temp_v1 = temp_ra->playerId;
    temp_t8 = 1 - temp_v1;

    sp60.z = 0;
    sp58.x = 0;
    sp58.z = 0;

    temp_v0 = temp_ra->unk_7C;
    temp_ft3 = D_80080228[temp_t8]->modInst->rootTransform.world_matrix.y.y + 360.0f;
    if (temp_v0 == 0 || temp_v0 == 7 || (temp_ra->currentState->flags & 0x4000)) {
        sp60.x = func_80012518(temp_ft3, D_80080210);
        var_t2 = func_8002CDFC((s16) ((0xC00 - arg0->rotation.y) & 0xFFF), (s16) (D_8008020C - (temp_t8 << 0xB)));

        if (var_t2 > 1700) {
            var_t2 = 1700;
        } else if (var_t2 < -1100) {
            var_t2 = -1100;
        }

        var_t0 = D_80052D64[temp_v1];
        var_a2 = D_80052D68[temp_v1];
        var_t3 = var_t2 - var_t0 - var_a2;
    } else {
        var_a2 = D_80052D68[temp_v1];
        var_t0 = D_80052D64[temp_v1];
        var_t2 = 0;
        sp60.x = 0;
        var_t3 = -(var_a2 + var_t0);
    }

    if (var_t3 == 0) {
        D_80052D70[temp_v1] = D_80052D74[temp_v1] = 0;
        D_80052D78[temp_v1] = 2;
        D_8013C3C0[temp_v1] = var_a2 + var_t0;
    }

    D_80052D6C[temp_v1] = ((D_8013C3C0[temp_v1] + var_t2) >> 1);
    D_80052D74[temp_v1] += D_80052D78[temp_v1];
    D_80052D70[temp_v1] += D_80052D74[temp_v1];

    if (D_80052D70[temp_v1] > 60) {
        D_80052D70[temp_v1] = 60;
        D_80052D78[temp_v1] = 0;
    } else if (D_80052D70[temp_v1] <= 0) {
        D_80052D70[temp_v1] = 2;
        D_80052D78[temp_v1] = 2;
    }
    if (D_80052D70[temp_v1] < var_t3) {
        var_t3 = D_80052D70[temp_v1];
    } else if (var_t3 < -D_80052D70[temp_v1]) {
        var_t3 = -D_80052D70[temp_v1];
    }
    if (var_a2 > 0) {
        temp_v1_3 = var_t0 + var_t3;
        if (var_t3 >= 0) {
            temp_v0_3 = var_a2 + var_t3;
            if (temp_v0_3 > 600) {
                var_t3 = temp_v0_3 - 600;
                temp_v1_3 = var_t0 + var_t3;

                sp58.y = var_a2 = D_80052D68[temp_v1] = 600;
                if (temp_v1_3 > 1100) {
                    sp60.y = var_t0 = D_80052D64[temp_v1] = 1100;
                } else {
                    sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
                }
            } else {
                sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_3;
                sp60.y = var_t0;
            }
        } else {
            if (temp_v1_3 < 0) {
                temp_v0_4 = var_a2 + temp_v1_3;
                var_t3 = temp_v1_3;

                sp60.y = var_t0 = D_80052D64[temp_v1] = 0;
                if (temp_v0_4 < 0) {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = 0;
                } else {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_4;
                }
            } else {
                sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
                sp58.y = var_a2;
            }
        }
    } else if (var_a2 < 0) {
        temp_v0_5 = var_a2 + var_t3;
        if (var_t3 >= 0) {
            temp_v1_3 = var_t0 + var_t3;
            if (temp_v1_3 > 0) {
                temp_v0_6 = var_a2 + temp_v1_3;
                var_t3 = temp_v1_3;

                sp60.y = var_t0 = D_80052D64[temp_v1] = 0;
                if (temp_v0_6 > 0) {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = 0;
                } else {
                    sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_6;
                }
            } else {
                sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
                sp58.y = var_a2;
            }
        } else if (temp_v0_5 < -600) {
            var_t3 = temp_v0_5 + 600;
            sp58.y = var_a2 = D_80052D68[temp_v1] = -600;
            temp_v1_3 = var_t0 + var_t3;
            if (temp_v1_3 < -500) {
                sp60.y = var_t0 = D_80052D64[temp_v1] = -500;
            } else {
                sp60.y = var_t0 = D_80052D64[temp_v1] = temp_v1_3;
            }
        } else {
            sp58.y = var_a2 = D_80052D68[temp_v1] = temp_v0_5;
            sp60.y = var_t0;
        }
    } else {
        sp60.y = var_t0;
        sp58.y = var_a2 = D_80052D68[temp_v1] = var_a2 + var_t3;
    }

    if (D_80052D74[temp_v1] > 0) {
        if (var_t3 >= 0 && var_t0 + var_a2 >= D_80052D6C[temp_v1]) {
            D_80052D78[temp_v1] = -2;
        } else if (D_80052D6C[temp_v1] >= var_t0 + var_a2) {
            D_80052D78[temp_v1] = -2;
        }
    }

    math_rotate(&temp_ra->unk_750.local_matrix, &sp60);
    math_rotate(&temp_ra->unk_868.local_matrix, &sp58);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/305A0/func_8003184C.s")
#endif

void func_80031D4C(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA40[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->frameIndex == s0->unk_00) {
            func_80031E4C(s0, &v0->unk_198, obj);
        }
    }
}

void func_80031DCC(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA6C[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->frameIndex == s0->unk_00) {
            func_80031E4C(s0, &v0->unk_198, obj);
        }
    }
}

void func_80031E4C(Unk_8004BA6C *arg0, PlayerSub9 *arg1, Object *arg2) {
    Player *player = (Player *) arg2->varObj[0];
    Vec4f *v0;
    Vec3s sp18;

    switch (arg0->unk_02) {
        case 0:
            v0 = arg1->unk_18;
            break;
        case 1:
            v0 = arg1->unk_14;
            break;
        case 2:
            v0 = arg1->unk_08;
            break;
        case 3:
            v0 = &arg1->unk_38.world_matrix.w;
            break;
        case 4:
            v0 = &arg1->unk_150.world_matrix.w;
            break;
        case 5:
            v0 = arg1->unk_0C;
            break;
        case 6:
        default:
            v0 = arg1->unk_10;
            break;
    }

    sp18.x = v0->x;
    sp18.y = v0->y;
    sp18.z = v0->z;
    func_8000EA80(&sp18, arg0->unk_04, arg2, &D_8004BA14[player->characterId]);
}

void func_80031F24(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (v0->characterId == AARON) {
        obj->currentTask->func = func_80021E34;
    } else {
        obj->currentTask->flags |= 0x80;
    }
}

void func_80031F60(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    func_800063C4(v0, 382, 1);
}

void func_80031F88(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (obj->frameIndex == v0->currentState->unk_02 - 2) {
        obj->currentTask->func = func_80031F60;
    }
}

void func_80031FBC(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (v0->flags & PLAYER_FLAG_NOT_FACING_OPP) {
        func_800063C4(v0, 383, 1);
    } else {
        obj->currentTask->counter = 60;
        obj->currentTask->func = func_80031F60;
    }
}

void func_8003201C(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    func_800063C4(v0, 140, 1);
}

void func_80032044(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (gBattleSettings[PLAYER_1].characterId == gBattleSettings[PLAYER_2].characterId && v0->playerId != 0) {
        obj->currentTask->counter = 15;
    }

    obj->currentTask->func = func_8003201C;
}

void func_8003208C(Object *obj) {
    Vec4i sp20;
    Player *v0 = (Player *) obj->varObj[0];
    s32 v1 = v0->playerId;

    if (obj->frameIndex == v0->currentState->unk_02 - 1) {
        sp20.x = sp20.y = 0;
        sp20.z = -D_8013C3C8[v1];
        func_8001370C(&sp20, &obj->rotation);
        obj->pos.x += sp20.x;
        obj->pos.z += sp20.z;
        obj->currentTask->func = func_80021DC4;
    }

    func_80021DC4(obj);
}

void func_80032130(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    s32 v1 = v0->playerId;

    if (v0->characterId == DEMITRON && obj->frameIndex > 50) {
        func_80021DC4(obj);
        obj->currentTask->func = func_80021DC4;
    } else {
        D_8013C3C8[v1] = D_80080210;
        func_80021E34(obj);
        obj->currentTask->func = func_8003208C;
    }
}
