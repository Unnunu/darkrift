#include "common.h"

void func_80022428(Object *obj, Object *obj2);

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

    state = &player->states[player->unk_7E];
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

void func_80021EE8(Object *obj, s32 arg1) {
    Player *player = (Player *) obj->vars[0];

    player->unk_80 &= ~0x2000000;

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

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80021FEC.s")
void func_80021FEC(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022218.s")
void func_80022218(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022428.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_8002250C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022694.s")
void func_80022694(Object *, s32, Object *);

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
            player->unk_80 |= 0x2000000;
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

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022B44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022CD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022EC0.s")
