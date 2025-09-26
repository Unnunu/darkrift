#include "common.h"

extern s32 D_8004BA14[];
extern Unk_8004BA6C *D_8004BA40[];
extern Unk_8004BA6C *D_8004BA6C[];

Object *D_80052D60 = NULL;
s16 D_80052D64[] = { 0, 0 };
s16 D_80052D68[] = { 0, 0 };
s16 D_80052D6C[] = { 0, 0 };
s16 D_80052D70[] = { 0, 0 };
s16 D_80052D74[] = { 0, 0 };
s16 D_80052D78[] = { 2, 2 };

s16 D_8013C3C0[2];
s32 D_8013C3C8[2];

void func_80031E4C(Unk_8004BA6C *, PlayerSub9 *, Object *);

u8 func_800316A0(Object *obj) {
    Player *player;
    Player *v1;
    s32 a1;

    player = (Player *) obj->varObj[0];
    v1 = gPlayers + (1 - player->playerId);

    a1 = (v1->unk_90->unk_34 & 0x100000) &&
         (v1->unk_90->unk_06 < v1->unk_00->spriteId || v1->unk_90->unk_04 > v1->unk_00->spriteId);
    return a1 > 0;
}

void func_80031724(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Player *v0;
    PlayerSub3 *v1;

    v0 = gPlayers + (1 - player->playerId);
    v1 = &player->unk_20[player->unk_7E];

    if (!(v1->unk_34 & 0x4000) && D_800B6328[player->playerId].unk_02 && (v0->unk_90->unk_34 & 0x100000) &&
        v0->unk_00->spriteId < v0->unk_90->unk_04) {
        if (v0->unk_80 & 1) {
            func_800063C4(player, 0x27, 1);
            player->unk_BC = func_8001D070;
            player->unk_C0 = 60;
        } else {
            func_800063C4(player, 0x3B, 1);
            player->unk_BC = func_8001CE18;
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
    temp_ft3 = D_80080228[temp_t8]->modInst->unk_010.wolrd_matrix.y.y + 360.0f;
    if (temp_v0 == 0 || temp_v0 == 7 || (temp_ra->unk_90->unk_34 & 0x4000)) {
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

    math_rotate(&temp_ra->unk_7E8, &sp60);
    math_rotate(&temp_ra->unk_900, &sp58);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/322A0/func_8003184C.s")
#endif

void func_80031D4C(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA40[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->spriteId == s0->unk_00) {
            func_80031E4C(s0, &v0->unk_198, obj);
        }
    }
}

void func_80031DCC(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA6C[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->spriteId == s0->unk_00) {
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
            v0 = &arg1->unk_1D0.wolrd_matrix.w;
            break;
        case 4:
            v0 = &arg1->unk_2E8.wolrd_matrix.w;
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

    if (obj->spriteId == v0->unk_90->unk_02 - 2) {
        obj->currentTask->func = func_80031F60;
    }
}

void func_80031FBC(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (v0->unk_80 & 8) {
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

    if (D_800B6328[PLAYER_1].characterId == D_800B6328[PLAYER_2].characterId && v0->playerId != 0) {
        obj->currentTask->counter = 15;
    }

    obj->currentTask->func = func_8003201C;
}

void func_8003208C(Object *obj) {
    Vec4i sp20;
    Player *v0 = (Player *) obj->varObj[0];
    s32 v1 = v0->playerId;

    if (obj->spriteId == v0->unk_90->unk_02 - 1) {
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

    if (v0->characterId == DEMITRON && obj->spriteId > 50) {
        func_80021DC4(obj);
        obj->currentTask->func = func_80021DC4;
    } else {
        D_8013C3C8[v1] = D_80080210;
        func_80021E34(obj);
        obj->currentTask->func = func_8003208C;
    }
}
