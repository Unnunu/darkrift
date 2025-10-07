#include "common.h"
#include "task.h"

s32 D_80052310[] = { 0x10000000, 0 };

void func_8002A0EC(Object *obj);
void func_80029F58(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028010.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_800281F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028400.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_8002856C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_800287AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028890.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028AE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028E84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028F38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80029044.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80029130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80029630.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80029D04.s")
void func_80029D04(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80029D84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80029DC0.s")
void func_80029DC0(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80029E5C.s")
void func_80029E5C(Object *obj);

void func_80029EBC(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029DC0;
    } else if (buttons & INP_RIGHT) {
        obj->spriteId = 118;
        obj->fn_render = func_80029F58;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_80029F58(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029E5C;
    } else if (buttons & INP_LEFT) {
        obj->spriteId = 120;
        obj->fn_render = func_80029EBC;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_80029FF4(Object *obj) {
    if (obj->spriteId >= 118) {
        obj->fn_render = func_80029F58;
    } else {
        obj->spriteId++;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A050(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029FF4;
    } else if (buttons & INP_UP) {
        obj->fn_render = func_8002A0EC;
        obj->spriteId = 58;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A0EC(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029D04;
    } else if (buttons & INP_DOWN) {
        obj->fn_render = func_8002A050;
        obj->spriteId = 60;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A188(Object *obj) {
    if (obj->spriteId >= 58) {
        obj->fn_render = func_8002A0EC;
    } else {
        obj->spriteId++;
    }
    D_8005BEFC += 2;
    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A1F0(Object *obj) {
    obj->fn_render = func_8002A188;
    obj->flags &= ~4;
    obj->spriteId++;
    obj->currentTask->func = task_default_func;
    gTasksDisabled = TRUE;
    obj->flags |= 0x2000000;
    D_8005BEFC = 0;
}

void func_8002A250(Object *obj) {
    if (obj->spriteId++ > 16) {
        obj->flags |= 0x10;
    }
    obj->currentTask->counter = 2;
}

void func_8002A280(Object *obj) {
}

void func_8002A288(Object *obj) {
    s32 pad[1];
    u32 dx, dz;
    Player *player = (Player *) obj->varObj[0];
    Player *opponent = gPlayers + 1 - player->playerId;
    Vec4i sp44;
    Vec4i *playerPos = &obj->pos;
    Vec4i *oppPos = &opponent->unk_00->pos;
    Object *sp38;
    ColorRGBA sp30[] = { { 255, 225, 175, 0 }, { 255, 200, 0, 0 } };

    obj->spriteId++;
    if (obj->spriteId >= obj->modInst->numAnimFrames) {
        obj->currentTask->flags |= 0x80;
        obj->flags |= 0x10;
        D_8008012C &= ~0x10;
    }

    if (obj->unk_088.a >= 4) {
        obj->unk_088.a -= 4;
    }

    dx = ABS(playerPos->x - oppPos->x);
    dz = ABS(playerPos->z - oppPos->z);
    if (DISTANCE(dx, dz) < obj->unk_1FC) {
        obj->vars[2] = 0;

        sp44.x = oppPos->x;
        sp44.z = oppPos->z;
        sp44.y = 0;
        sp38 = func_8002BFF0(&sp44, 0x1000, func_80021D40, player->unk_DE4);
        if (sp38 != NULL) {
            func_8003453C(sp38, &sp30[player->playerId]);
            sp38->unk_088.a = 160;
            if (func_80022B44(opponent, player, obj)) {
                sp38->vars[0] = 32;
            } else {
                sp38->vars[0] = 160 / sp38->modInst->numAnimFrames;
            }
            sp38->flags |= 0x2000;
        }
        obj->currentTask->flags |= 0x80;
        obj->flags |= 0x10;
    }

    obj->unk_1FC += 16;
}

void func_8002A4E0(Object *obj) {
    Vec4i sp38;
    Object *v0;
    Player *player = (Player *) obj->varObj[0];
    ColorRGBA sp28[] = { { 255, 225, 175, 0 }, { 255, 200, 0, 0 } };

    if (obj->vars[1] == 0) {
        sp38.x = obj->modInst->transforms[0].wolrd_matrix.w.x;
        sp38.y = obj->modInst->transforms[0].wolrd_matrix.w.y;
        sp38.z = obj->modInst->transforms[0].wolrd_matrix.w.z;
        v0 = func_8002BFF0(&sp38, 0x1000, func_8002A288, player->unk_DDC);
        if (v0 != NULL) {
            v0->unk_088.a = 160;
            v0->vars[1] = 160 / v0->modInst->numAnimFrames;
            v0->flags |= 0x2000;
            v0->varObj[0] = player;
            v0->vars[6] = obj->vars[6];
            func_8003453C(v0, &sp28[player->playerId]);
            sound_play(player->playerId, 10);
            v0 = func_80030908();
            if (v0 != NULL) {
                v0->vars[0] = v0->vars[1] = 40;
            }
        }
    } else if (obj->vars[1] == 8) {
        sp38.x = obj->modInst->transforms[1].wolrd_matrix.w.x;
        sp38.y = obj->modInst->transforms[1].wolrd_matrix.w.y;
        sp38.z = obj->modInst->transforms[1].wolrd_matrix.w.z;
        v0 = func_8002BFF0(&sp38, 0x1000, func_8002A288, player->unk_DDC);
        if (v0 != NULL) {
            v0->unk_088.a = 160;
            v0->vars[1] = 160 / v0->modInst->numAnimFrames;
            v0->flags |= 0x2000;
            v0->varObj[0] = player;
            v0->vars[6] = obj->vars[6];
            func_8003453C(v0, &sp28[player->playerId]);
            sound_play(player->playerId, 10);
        }
    } else if (obj->vars[1] == 16) {
        sp38.x = obj->modInst->transforms[2].wolrd_matrix.w.x;
        sp38.y = obj->modInst->transforms[2].wolrd_matrix.w.y;
        sp38.z = obj->modInst->transforms[2].wolrd_matrix.w.z;
        v0 = func_8002BFF0(&sp38, 0x1000, func_8002A288, player->unk_DDC);
        if (v0 != NULL) {
            v0->unk_088.a = 160;
            v0->vars[1] = 160 / v0->modInst->numAnimFrames;
            v0->flags |= 0x2000;
            v0->varObj[0] = player;
            v0->vars[6] = obj->vars[6];
            func_8003453C(v0, &sp28[player->playerId]);
            sound_play(player->playerId, 10);
        }
    } else if (obj->vars[1] == 24) {
        obj->flags |= 0x10;
    }

    obj->vars[1]++;
}

void func_8002A870(Object *obj) {
    obj->vars[1] = 0;
    obj->currentTask->func = func_8002A4E0;
}
