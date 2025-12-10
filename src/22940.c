#include "common.h"

void func_80022428(Object *obj, Object *obj2);
void func_80022EC0(Object *);

void func_80021D40(Object *obj) {
    if (++obj->frameIndex >= obj->modInst->numAnimFrames) {
        obj->currentTask->flags |= 0x80;
        obj->flags |= 0x10;
    }

    if (obj->unk_088.a >= obj->vars[0]) {
        obj->unk_088.a -= obj->vars[0];
    } else {
        obj->unk_088.a = 0;
        obj->currentTask->flags |= 0x80;
        obj->flags |= 0x10;
    }
}

void func_80021DC4(Object *obj) {
    Player *player = (Player *) obj->vars[0];
    Struct9C *s0;

    ;
    for (s0 = player->unk_9C->unk_00; s0->unk_00 != 255; s0++) {
        if (obj->frameIndex == s0->unk_01) {
            func_800226E8(obj, s0->unk_00);
        }
    }
}

void func_80021E34(Object *obj) {
    Player *player = (Player *) obj->vars[0];
    PlayerState *state;

    state = &player->states[player->stateId];
    if (state->unk_28 >= 0) {
        player->unk_9C = &player->unk_4C[state->unk_28];
        player->unk_194 = NULL;
        obj->currentTask->func = func_80021DC4;
    } else {
        obj->currentTask->flags |= 0x80;
    }
}

void func_80021EA0(Object *obj) {
}

void func_80021EA8(Object *obj, Object *obj2) {
    if (obj->unk_078 == 8) {
        func_80021EA0(obj);
    } else {
        func_80022428(obj, obj2);
    }
}

void func_80021EE8(Object *obj, PlayerSubG *arg1) {
    Player *player = (Player *) obj->vars[0];

    player->flags &= ~PLAYER_FLAG_2000000;

    switch (player->characterId) {
        case AARON:
            obj->vars[1] = 0;
            if (obj->vars[3] == 1) {
                obj->currentTask->func = func_8002A870;
            } else {
                obj->currentTask->flags |= 0x80;
                obj->flags |= OBJ_FLAG_10;
                D_8008012C &= ~GFX_FLAG_10;
            }
            return;
        case GORE:
            obj->currentTask->flags |= 0x80;
            obj->flags |= OBJ_FLAG_10;
            D_8008012C &= ~GFX_FLAG_10;
            return;
    }

    D_8008012C &= ~GFX_FLAG_10;
    obj->currentTask->flags |= 0x80;
    obj->flags |= OBJ_FLAG_10;
}

void func_80021FEC(Object *obj) {
    u8 *t0;
    PlayerSubG *s0;
    s32 temp2;
    Player *player;
    u8 v1;
    s16 temp;
    Object *playerObj;
    Vec4i sp28;

    s0 = (PlayerSubG *) obj->vars[7];
    t0 = (u8 *) obj->vars[1];
    player = (Player *) obj->vars[0];
    playerObj = player->obj;

    if ((s0->unk_2C & 2) && s0->unk_02 >= 0) {
        func_80028120(playerObj, s0, &sp28);
        obj->pos.x = sp28.x;
        obj->pos.y = sp28.y;
        obj->pos.z = sp28.z;
    }

    if (--obj->unk_08C <= 0) {
        temp = obj->vars[2]++;
        obj->unk_08C = obj->vars[4];
        v1 = t0[temp];

        if (v1 == 0xFF) {
            obj->vars[2] = 1;
            v1 = t0[0];
        } else if (v1 == 0xFE) {
            func_80021EE8(obj, s0);
            return;
        }

        obj->frameIndex = v1;
        if ((s0->unk_2C & 1) && obj->frameIndex >= s0->unk_36) {
            if (obj->unk_088.a >= obj->vars[9]) {
                obj->unk_088.a -= obj->vars[9];
            } else {
                obj->unk_088.a = 0;
                obj->currentTask->flags |= 0x80;
                obj->flags |= 0x10;
            }
        }
    }

    obj->flags &= ~OBJ_FLAG_HIDDEN;

    if (((s0->unk_2C & 0x10) && --obj->vars[5] < 0) || obj->pos.y > 0) { // @bug probably
        func_80021EE8(obj, s0);
        return;
    }

    if (s0->unk_2C & 4) {
        func_80022EC0(obj);
    }

    obj->pos.x += obj->velocity.x;
    obj->pos.y += obj->velocity.y;
    obj->pos.z += obj->velocity.z;

    temp2 = s0->unk_30;
    if (temp2 >= 0 && --obj->vars[8] < 0) {
        obj->vars[8] = s0->unk_34;
        func_800226E8(obj, temp2 ^ 0); // required to match
    }
}

void func_80022218(Object *obj) {
    PlayerSubG *s0;
    s32 temp2;
    Player *player;
    u8 v1;
    s16 temp;
    Object *playerObj;
    Vec4i sp2C;

    s0 = (PlayerSubG *) obj->vars[7];
    player = (Player *) obj->vars[0];
    playerObj = player->obj;

    D_8008012C |= GFX_FLAG_10;

    if ((s0->unk_2C & 2) && s0->unk_02 >= 0) {
        func_80028120(playerObj, s0, &sp2C);
        obj->pos.x = sp2C.x;
        obj->pos.y = sp2C.y;
        obj->pos.z = sp2C.z;
    }

    obj->flags &= ~OBJ_FLAG_HIDDEN;
    obj->frameIndex++;

    if (s0->unk_2C & 0x10) {
        if (--obj->vars[5] < 0 || obj->pos.y > 0) {
            func_80021EE8(obj, s0);
            return;
        }
        if (obj->frameIndex >= obj->modInst->numAnimFrames) {
            obj->frameIndex = s0->unk_24;
        }
    }

    if (obj->frameIndex >= obj->modInst->numAnimFrames) {
        func_80021EE8(obj, s0);
        return;
    }

    if (s0->unk_2C & 4) {
        func_80022EC0(obj);
    }

    obj->pos.x += obj->velocity.x;
    obj->pos.y += obj->velocity.y;
    obj->pos.z += obj->velocity.z;

    if ((s0->unk_2C & 1) && obj->frameIndex >= s0->unk_36) {
        if (obj->unk_088.a >= obj->vars[9]) {
            obj->unk_088.a -= obj->vars[9];
        } else {
            obj->unk_088.a = 0;
            func_80021EE8(obj, s0);
            return;
        }
    }

    temp2 = s0->unk_30;
    if (temp2 >= 0 && --obj->vars[8] < 0) {
        obj->vars[8] = s0->unk_34;
        func_800226E8(obj, temp2 ^ 0); // required to match
    }
}

void func_80022428(Object *obj, Object *obj2) {
    Player *player;
    Object *v0;
    PlayerSubG *v2;
    PlayerSubG *v1;

    player = (Player *) obj->vars[0];
    v1 = (PlayerSubG *) obj->vars[7];
    v2 = player->unk_48 + v1->unk_42;

    obj->unk_07C = obj->unk_07A = 0;
    obj->flags |= OBJ_FLAG_10;
    obj->currentTask->flags |= 0x80;

    v2->unk_00 = 0x10;
    v2->unk_2C |= 0x10;
    v2->unk_36 = 0;
    v2->unk_38 = 0x10;

    v0 = func_800226E8(obj, v1->unk_42);
    if (v0 != NULL) {
        obj->unk_076 |= 8;
        v0->unk_076 &= ~2;
        if (player->playerId != PLAYER_1) {
            v0->unk_07A = 2;
        } else {
            v0->unk_07C = 2;
        }
        v0->unk_1FC = 300;
    }
}

void func_8002250C(Object *obj, Object *arg1) {
    Player *player = (Player *) obj->vars[0];
    Object *v0;
    Vec4i sp30;
    PlayerSubG *v1 = (PlayerSubG *) obj->vars[7];
    ColorRGBA sp24[2] = { { 215, 180, 45, 0 }, { 250, 190, 55, 0 } };

    if ((obj->unk_078 & 8) && (obj->unk_076 & 8)) {
        func_80021EA0(obj);
        return;
    }

    obj->unk_07C = obj->unk_07A = 0;
    obj->flags |= OBJ_FLAG_10;
    obj->currentTask->flags |= 0x80;

    sp30.x = 0;
    sp30.y = 0;
    sp30.z = -obj->unk_1FC;
    func_8001370C(&sp30, &obj->rotation);
    sp30.x += obj->pos.x;
    sp30.z += obj->pos.z;
    obj->unk_1FC = 0;

    v0 = create_model_instance(&sp30, 0x1000, func_80021D40, player->unk_DCC[v1->unk_42]);
    if (v0 == NULL) {
        return;
    }

    v0->unk_088.a = 255;
    v0->vars[0] = 5;
    v0->flags |= OBJ_FLAG_2000;
    v0->unk_076 &= ~2;
    if (player->playerId != PLAYER_1) {
        v0->unk_07A = 2;
    } else {
        v0->unk_07C = 2;
    }
    v0->unk_1FC = 300;
    func_8003453C(v0, &sp24[player->playerId]);
}

ObjFunc D_8004A4C8[2] = { func_80022218, func_80021FEC }; // unused

void func_80022694(Object *obj, s32 arg1, Object *arg2) {
    Player *player = (Player *) obj->vars[0];
    Object *v0;

    if (player->characterId == GORE && arg1 == 0) {
        arg2->unk_1E8 = func_8002250C;
        v0 = func_80030908();
        if (v0 != NULL) {
            v0->vars[1] = 50;
            v0->vars[0] = 30;
        }
    }
}

Object *func_800226E8(Object *obj, s32 arg1) {
    Vec4i sp40;
    Object *a2;
    Player *player = (Player *) obj->vars[0];
    PlayerSubG *s0 = player->unk_48 + arg1;
    s32 pad[2];

    if (s0->unk_02 >= 0) {
        func_80028120(obj, s0, &sp40);
    } else {
        sp40.x = s0->unk_04;
        sp40.y = s0->unk_08;
        sp40.z = s0->unk_0C;
        func_8001370C(&sp40, &obj->rotation);
        sp40.x += obj->pos.x;
        sp40.y += obj->pos.y;
        sp40.z += obj->pos.z;
    }

    if (s0->unk_20 >= 0) {
        a2 = create_3dsprite(&sp40, 0x1100, func_80021FEC, player->unk_DC0[s0->unk_20]);
        if (a2 == NULL) {
            return a2;
        }

        a2->frameIndex = player->unk_44[s0->unk_1C];
        a2->unk_08C = a2->vars[4] = s0->unk_1E;
    } else {
        a2 = create_model_instance(&sp40, 0x1000, func_80022218, player->unk_DCC[s0->unk_22]);
        if (a2 == NULL) {
            return a2;
        }

        a2->flags |= OBJ_FLAG_HIDDEN;
        a2->currentTask->counter = s0->unk_1E;
        player->unk_194 = a2;
    }

    if (a2->modInst == NULL) {
        return NULL;
    }

    if (a2 != NULL) {
        if (s0->unk_2C & 4) {
            if (player->playerId != PLAYER_1) {
                a2->unk_07A = 2;
            } else {
                a2->unk_07C = 2;
            }
            a2->unk_1FC = 300;
            a2->unk_076 |= 2;
            a2->unk_076 |= 8;
            a2->unk_1E8 = func_80021EA8;
            player->flags |= PLAYER_FLAG_2000000;
        }

        if (s0->unk_2C & 0x40) {
            func_8003453C(a2, &s0->unk_44[player->playerId]);
        }

        a2->vars[0] = player;
        a2->vars[1] = player->unk_44 + s0->unk_1C;
        a2->vars[2] = 0;
        a2->vars[5] = s0->unk_00;
        a2->vars[6] = player->currentState;
        a2->vars[7] = s0;
        a2->vars[3] = arg1;
        a2->velocity.x = s0->unk_10;
        a2->velocity.y = s0->unk_14;
        a2->velocity.z = s0->unk_18;
        a2->unk_040.x = 0xF00000;
        a2->unk_040.y = 0xF00000;
        a2->unk_040.z = 0xF00000;

        func_8001370C(&a2->velocity, &obj->rotation);

        a2->vars[8] = s0->unk_32;
        a2->rotation.y = player->obj->rotation.y;
        s0->unk_40 = 0;

        if (s0->unk_2C & 9) {
            a2->flags |= OBJ_FLAG_2000;
            a2->unk_088.a = 255;

            if (s0->unk_38 > 0) {
                a2->vars[9] = 255 / s0->unk_38;
            } else if (s0->unk_20 < 0 && a2->modInst->numAnimFrames != 0) {
                a2->vars[9] = 255 / a2->modInst->numAnimFrames;
            } else {
                a2->vars[9] = 255 / a2->modInst->numNodes; // ?????????
            }

            if (player->characterId == DEMITRON && s0->unk_22 == 0) {

                a2->vars[9] = 128 / a2->modInst->numAnimFrames;
                a2->unk_088.a = 128;
            }
        }

        func_80022694(obj, arg1, a2);
    }

    return a2;
}

u8 func_80022B44(Player *arg0, Player *arg1, Object *arg2) {
    s16 v0;
    PlayerState *a2;
    u8 isBlock;

    a2 = (PlayerState *) arg2->vars[6];

    if (D_800801F0 && !D_8013C250) {
        return FALSE;
    }

    v0 = func_8000F074(arg0, arg1, a2);
    isBlock = (v0 == 270 || v0 == 271);
    return isBlock;
}

void func_80022BB0(Object *obj, Player *arg1, PlayerSubG *arg2, u8 arg3) {
    Player *player = (Player *) obj->vars[0];
    PlayerSubG *sp18 = player->unk_48 + arg2->unk_42;
    Object *v00;

    if (func_80022B44(arg1, player, obj)) {
        sp18->unk_00 = 0x10;
        sp18->unk_2C |= 0x10;
        sp18->unk_36 = 0;
        sp18->unk_38 = 0x10;
    } else {
        sp18->unk_00 = 0;
        sp18->unk_2C &= ~0x10;
        sp18->unk_38 = -1;
    }

    if (arg3) {
        v00 = func_800226E8(obj, arg2->unk_42);
        if (v00 != NULL) {
            v00->unk_088.a = 128;
            if (v00->modInst->numAnimFrames != 0) {
                v00->vars[9] = 255 / v00->modInst->numAnimFrames;
            }
        }
    }

    func_80021EE8(obj, arg2);
}

#ifdef NON_EQUIVALENT
u8 func_80022CD0(Object *obj) {
    Player *player;
    Vec4i *playerPos;
    Vec4i *oppPos;
    PlayerSubG *a2;
    Object *v0;
    Vec4i sp44;
    Player *sp20;
    s16 q;
    u32 dx, dz;
    s32 pad[2];

    player = (Player *) obj->vars[0];
    sp20 = gPlayers + (player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2);
    a2 = (PlayerSubG *) obj->vars[7];

    playerPos = &obj->pos;
    oppPos = &sp20->obj->pos;

    q = obj->vars[3];
    if (player->characterId == GORE) {
        if (q == 0) {
            if (1) {
                dx = ABS(playerPos->x - oppPos->x);
            }
            dz = ABS(playerPos->z - oppPos->z);

            // a2->unk_40 += 22;
            // obj->unk_1FC = a2->unk_40;
            if (FAST_HYPOT(dx, dz) < (obj->unk_1FC = a2->unk_40 += 22) && !(sp20->currentState->flags & 0xA)) {
                func_80022BB0(obj, sp20, a2, FALSE);

                sp44.x = playerPos->x;
                sp44.z = playerPos->z;
                sp44.y = 0;
                v0 = create_model_instance(&sp44, 0x1000, func_80021D40, player->unk_DCC[a2->unk_42]);
                if (v0 != NULL) {
                    v0->unk_088.a = 255;
                    v0->vars[0] = 255 / v0->modInst->numAnimFrames;
                    v0->flags |= OBJ_FLAG_2000;
                }
            }

            return TRUE;
        }
        return FALSE;
    }

    return FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022CD0.s")
u8 func_80022CD0(Object *obj);
#endif

void func_80022EC0(Object *obj) {
    Player *player;
    Player *s0;
    s32 pad[2];
    Vec4s sp40;
    Vec4s sp38;
    Object *v00;
    PlayerSubG *sp30;
    PlayerSubG *sp2C;
    s32 pad2;

    sp2C = (PlayerSubG *) obj->vars[7];
    player = (Player *) obj->vars[0];
    s0 = gPlayers + (player->playerId != PLAYER_1 ? PLAYER_1 : PLAYER_2);

    if (s0->currentState->flags & 0x40000) {
        return;
    }
    if (func_80022CD0(obj)) {
        return;
    }

    sp40.x = s0->unk_198.unk_08->x;
    sp40.y = s0->unk_198.unk_08->y;
    sp40.z = s0->unk_198.unk_08->z;

    sp38.x = obj->pos.x;
    sp38.y = obj->pos.y;
    sp38.z = obj->pos.z;

    if (func_8000EC70(&sp40, &s0->obj->pos, s0->unk_198.unk_2C + 80000, &sp38)) {
        if (!(sp2C->unk_2C & 0x20) && !(player->flags & PLAYER_FLAG_2000)) {
            sp30 = player->unk_48 + sp2C->unk_42;
            if (func_80022B44(s0, player, obj)) {
                sp30->unk_00 = 0x10;
                sp30->unk_2C |= 0x10;
                sp30->unk_36 = 0;
                sp30->unk_38 = 0x10;
            } else {
                sp30->unk_00 = 0;
                sp30->unk_2C &= ~0x10;
                sp30->unk_38 = -1;
            }

            v00 = func_800226E8(obj, sp2C->unk_42);
            if (v00 != NULL) {
                v00->unk_076 &= ~2;
                if (player->playerId != PLAYER_1) {
                    v00->unk_07A = 2;
                } else {
                    v00->unk_07C = 2;
                }
                v00->unk_1FC = 300;
            }

            func_80021EE8(obj, sp2C);
        } else {
            func_80021EE8(obj, sp2C);
        }

        player->unk_194 = NULL;
    }
}
