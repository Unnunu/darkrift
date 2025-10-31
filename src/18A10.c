#include "common.h"

extern s16 D_80049B20[];
extern s16 D_80049B30[];

Object *D_80081460;
char D_80081464[4];
Object *D_80081468[10];
s16 D_80081490;
s32 D_80081494;
s16 D_80081498[11];
s16 D_800814B0[11];
Vec4i D_800814C8;

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017E10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017F00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017F60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017FF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018088.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800181C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800182E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800183FC.s")

void func_800184A8(Object *obj) {
    Object *obj1;

    obj1 = obj->varObj[3];
    if (obj1->vars[4] == 7) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if ((gPlayerInput[PLAYER_1].buttons == INP_START) || gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_3;
            D_8005BFC0 |= GAME_FLAG_MODE_DONE;
            obj->currentTask->flags |= 0x80;
            sound_play(2, 0);
        }
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void func_80018554(Object *obj) {
    Object *obj1;

    obj1 = obj->varObj[3];
    if (obj1->vars[4] == 8) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if ((gPlayerInput[PLAYER_1].buttons == INP_START) || gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_4;
            D_8005BFC0 |= GAME_FLAG_MODE_DONE;
            obj->currentTask->flags |= 0x80;
            sound_play(2, 0);
        }
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void func_80018600(Object *obj) {
    Object *obj1;

    obj1 = obj->varObj[3];
    if (obj1->vars[4] == 9) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if ((gPlayerInput[PLAYER_1].buttons == INP_START) || gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_MAIN_MENU;
            D_8005BFC0 |= GAME_FLAG_MODE_DONE;
            obj->currentTask->flags |= 0x80;
            sound_play(2, 0);
        }
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void func_800186AC(Object *obj, s16 buttons, s16 playerId) {
    s16 prevButtons;
    s16 counter;
    s32 a2;

    a2 = 0;
    prevButtons = obj->vars[1];
    obj->vars[1] = buttons;
    counter = obj->vars[2]--;

    if (counter > 0 && buttons == prevButtons) {
        return;
    }

    obj->vars[2] = 15;
    if (buttons & INP_UP) {
        obj->vars[5] = 0;
        obj->vars[4] = (obj->vars[4] + 8) % 9;
        obj->vars[8] = 0;
        a2 = TRUE;
    } else if (buttons & INP_DOWN) {
        obj->vars[5] = 0;
        obj->vars[4] = (obj->vars[4] + 1) % 9;
        obj->vars[8] = 0;
        a2 = TRUE;
    } else if (buttons & INP_MASK_FF) {
        a2 = TRUE;

        if (buttons & INP_CUP) {
            obj->vars[5] = 61;
        } else if (buttons & INP_CLEFT) {
            obj->vars[5] = 62;
        } else if (buttons & INP_CDOWN) {
            obj->vars[5] = 63;
        } else if (buttons & INP_CRIGHT) {
            obj->vars[5] = 64;
        } else if (buttons & INP_A) {
            obj->vars[5] = 65;
        } else if (buttons & INP_B) {
            obj->vars[5] = 66;
        } else if (buttons & INP_L) {
            obj->vars[5] = 67;
        } else if (buttons & INP_R) {
            obj->vars[5] = 68;
        }
    }
    if (prevButtons) {} // @fake
    if (a2) {
        sound_play(2, 1);
    }
}

void func_80018820(Object *obj) {
    Object *obj1;
    s16 v1;
    s16 contId;
    s16 i;
    s16 q;
    s16 w;

    obj1 = obj->varObj[3];
    if (obj1->vars[4] == obj->vars[6]) {
        if (obj->frameIndex >= 61 && obj->frameIndex <= 69) {
            obj->frameIndex += 9;
        }

        v1 = obj1->vars[5];
        if (v1 != 0) {
            obj1->vars[7] = obj->frameIndex;
            obj1->vars[8] = obj->frameIndex = v1;
            obj1->vars[5] = 0;

            contId = obj1->vars[0];
            w = D_80049B30[obj->vars[6]];
            q = D_80049B20[obj1->vars[8] - 61];

            D_800AA450[contId][q] = w;
            for (i = 0; i < 8; i++) {}
        }
    } else {
        if (obj->frameIndex >= 70 && obj->frameIndex <= 78) {
            obj->frameIndex -= 9;
        }

        if (obj->frameIndex == obj1->vars[8]) {
            obj->frameIndex = obj1->vars[7];

            contId = obj1->vars[0];
            w = D_80049B30[obj->vars[6]];
            q = D_80049B20[obj1->vars[7] - 70];
            D_800AA450[contId][q] = w;
            for (i = 0; i < 8; i++) {}
        }
    }
}

void func_80018974(Object *obj) {
    s16 rawButtons;
    s16 playerId;

    playerId = obj->vars[0];
    rawButtons = gPlayerInput[playerId].raw_buttons;

    if (rawButtons != 0) {
        func_800186AC(obj, rawButtons, playerId);
    } else {
        obj->vars[1] = 0;
    }

    func_80018820(obj);
}

void func_800189CC(Object *obj) {
    u8 v1;
    Object *obj1;
    Object *obj2;

    obj->flags |= OBJ_FLAG_HIDDEN;

    obj1 = obj->varObj[0];
    obj2 = obj->varObj[1];

    v1 = 0;
    if (obj1->vars[4] == 8) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if (gPlayerInput[PLAYER_1].buttons == INP_START) {
            gNextGameMode = GAME_MODE_OPTIONS;
            D_8005BFC0 |= GAME_FLAG_MODE_DONE;
            obj->currentTask->flags |= 0x80;
            v1++;
        }
    }
    if (obj2->vars[4] == 8) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if (gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_OPTIONS;
            D_8005BFC0 |= GAME_FLAG_MODE_DONE;
            obj->currentTask->flags |= 0x80;
            v1++;
        }
    }

    if (v1 != 0) {
        sound_play(2, 0);
    }
}

void func_80018AD0(Object *obj) {
    s16 prevButtons;
    s16 buttons;
    char sp38[20];
    s16 characterId;
    s16 counter;

    prevButtons = obj->vars[1];
    obj->vars[1] = buttons = gPlayerInput[PLAYER_1].buttons | gPlayerInput[PLAYER_2].buttons;
    counter = obj->vars[2]--;

    if (counter > 0 && buttons == prevButtons) {
        return;
    }

    obj->vars[2] = 15;
    if (buttons & INP_LEFT) {
        characterId = obj->vars[0] = (obj->vars[0] + 10) % 11;
        if (characterId == CHARACTER_5 || characterId == SONORK && !D_80049DF0 ||
            characterId == DEMITRON && !D_80049DF4) {
            obj->vars[0]--;
        }

        mem_free(D_80049AE0);
        D_80049AE0 = NULL;
        str_copy(sp38, D_8004B844[obj->vars[0]].unk_04->name);
        str_concat(sp38, "st");
        load_background(sp38, 0, 13, 0, 0, 1, 0x2000);
        sound_play(2, 1);
    } else if (buttons & INP_RIGHT) {
        characterId = obj->vars[0] = (obj->vars[0] + 1) % 11;
        if (characterId == CHARACTER_5 || characterId == SONORK && !D_80049DF0 ||
            characterId == DEMITRON && !D_80049DF4) {
            obj->vars[0]++;
        }

        mem_free(D_80049AE0);
        D_80049AE0 = NULL;
        str_copy(sp38, D_8004B844[obj->vars[0]].unk_04->name);
        str_concat(sp38, "st");
        load_background(sp38, 0, 13, 0, 0, 1, 0x2000);
        sound_play(2, 1);
    } else if (buttons & INP_START) {
        gNextGameMode = GAME_MODE_OPTIONS;
        D_8005BFC0 |= GAME_FLAG_MODE_DONE;
        obj->currentTask->flags |= 0x80;
        sound_play(2, 0);
    }
}

void func_80018D64(Object *obj) {
    s16 buttons;

    buttons = gPlayerInput[PLAYER_1].buttons | gPlayerInput[PLAYER_2].buttons;
    if (buttons & INP_START) {
        gNextGameMode = GAME_MODE_OPTIONS;
        D_8005BFC0 |= GAME_FLAG_MODE_DONE;
        obj->currentTask->flags |= 0x80;
        sound_play(2, 0);
    }
}

void func_80018DD4(s16 number, s16 posX, s16 posY) {
    UIElement spC = { 0, NULL, 0, 0x1000, "options2.sp2" };
    s16 hundreds;
    s16 tens;
    s16 ones;
    Object *v1;

    if (number > 999) {
        number = 999;
    }

    hundreds = number / 100;
    number -= hundreds * 100;
    tens = number / 10;
    ones = number - tens * 10;

    if (hundreds != 0) {
        v1 = D_80081468[D_80081490++];
        v1->pos.x = posX;
        v1->pos.y = posY;
        v1->frameIndex = 21 + hundreds;
        v1->flags &= ~OBJ_FLAG_HIDDEN;
    }

    posX += 7;

    if (hundreds != 0 || hundreds == 0 && tens != 0) {
        v1 = D_80081468[D_80081490++];
        v1->pos.x = posX;
        v1->pos.y = posY;
        v1->frameIndex = 21 + tens;
        v1->flags &= ~OBJ_FLAG_HIDDEN;
    }

    posX += 7;

    v1 = D_80081468[D_80081490++];
    v1->pos.x = posX;
    v1->pos.y = posY;
    v1->frameIndex = 21 + ones;
    v1->flags &= ~OBJ_FLAG_HIDDEN;
}

void func_8001905C(Object *obj) {
    s16 i;
    s16 v0;
    s16 sp32;
    Object *v03;
    s32 pad;

    if (!(D_8005BFC0 & GAME_FLAG_1000)) {
        return;
    }
    v0 = obj->vars[0]++;
    if (v0 == 0) {
        func_80014CB4(D_80049AE0);
    }

    for (i = 0; i < 10; i++) {
        D_80081468[i]->flags |= OBJ_FLAG_HIDDEN;
    }

    if (v0 > 10) {
        obj->currentTask->func = func_80018D64;
        D_80081460->flags |= OBJ_FLAG_HIDDEN;
        return;
    }

    sp32 = D_80081498[v0];
    if (sp32 == CHARACTER_5 || sp32 == SONORK && !D_80049DF0 || sp32 == DEMITRON && !D_80049DF4) {
        return;
    }

    sound_play(2, 0);
    D_80081490 = 0;

    v03 = D_80081468[D_80081490++];
    v03->pos.x = D_800814C8.x;
    v03->pos.y = D_800814C8.y;
    v03->frameIndex = 0xBC + (sp32 - (sp32 > CHARACTER_5));
    v03->flags &= ~OBJ_FLAG_HIDDEN;

    func_80018DD4(D_800814B0[sp32], D_800814C8.x + 0x44, D_800814C8.y);
    func_80018DD4(D_800B6368[sp32][0], D_800814C8.x + 0x7B, D_800814C8.y);
    func_80018DD4(D_800B6368[sp32][1], D_800814C8.x + 0xA5, D_800814C8.y);
    D_800814C8.y += 16;
    obj->currentTask->counter = 10;
}

void func_80019278(void) {
    UIElement sp3C = { 0, NULL, 0, 0x1000, "options2.sp2" };
    s16 i, j, k;
    s16 p1;
    s16 p2;
    s16 a0;

    D_800814C8.x = 75;
    D_800814C8.y = 71;

    for (i = 0; i < 10; i++) {
        D_80081468[i] = create_ui_element(&D_800814C8, &sp3C, CONTEXT_2000);
        D_80081468[i]->flags |= OBJ_FLAG_HIDDEN;
    }

    for (i = 0; i < 11; i++) {
        D_80081498[i] = i;
    }

    for (j = 0; j < 11; j++) {
        p1 = D_800B6368[j][0];
        p2 = D_800B6368[j][1];
        a0 = p1 + p2;
        if (a0 != 0) {
            D_800814B0[j] = (p1 * 200 + a0) / (2 * a0);
        } else {
            D_800814B0[j] = 0;
        }
    }

    for (j = 1; j < 11; j++) {
        for (i = 0; i < j; i++) {
            if (D_800814B0[D_80081498[i]] < D_800814B0[j]) {
                for (k = j - 1; k >= i; k--) {
                    D_80081498[k + 1] = D_80081498[k];
                }
                D_80081498[i] = j;
                break;
            }
        }
    }
}
