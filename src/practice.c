#include "common.h"
#include "task.h"
#include "sprite_ids.h"

u32 D_80052D80[] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };

UIElement D_80052DAC = { SPR_PRA_PAUSE_MENU_3, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052DC0 = { SPR_PRA_BLUE_ON, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052DD4 = { SPR_PRA_BLUE_OFF, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052DE8 = { SPR_PRA_AARON, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052DFC = { SPR_PRA_AARON, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052E10 = { SPR_PRA_RED_DIGIT_1, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052E24 = { SPR_PRA_RED_DIGIT_1, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052E38 = { SPR_PRA_RED_DIGIT_1, task_default_func, 0x04000000, 0x1000, "practice.sp2" };
UIElement D_80052E4C = { SPR_PRA_RED_DIGIT_0, task_default_func, 0, 0x1000, "practice.sp2" };

Vec4i D_80052E60 = { 164, 133, 0, 0 };
Vec4i D_80052E70 = { 177, 93, 0, 0 };
Vec4i D_80052E80 = { 181, 133, 0, 0 };
Vec4i D_80052E90 = { 165, 108, 0, 0 };
Vec4i D_80052EA0 = { 165, 147, 0, 0 };
Vec4i D_80052EB0 = { 172, 108, 0, 0 };
Vec4i D_80052EC0 = { 172, 147, 0, 0 };
Vec4i D_80052ED0 = { 33, 31, 0, 0 };
Vec4i D_80052EE0 = { 104, 39, 0, 0 };
Vec4i D_80052EF0 = { 95, 39, 0, 0 };
Vec4i D_80052F00 = { 104, 51, 0, 0 };
Vec4i D_80052F10 = { 95, 51, 0, 0 };
Vec4i D_80052F20 = { 86, 51, 0, 0 };

s16 **D_80052F30[] = { D_800522EC, D_80052524, D_8005264C, D_80052770, D_800523E4,
                       D_80052864, D_8005296C, D_80052A48, D_80052B18, D_80052C18 };

s32 D_80052F58[] = { 0, SPR_PRA_BUTTON_L, SPR_PRA_BUTTON_A, 0, SPR_PRA_BUTTON_R, 0, 0, 0, SPR_PRA_BUTTON_B };
s32 D_80052F7C[] = { 0,
                     SPR_PRA_BUTTON_C_UP,
                     SPR_PRA_BUTTON_C_RIGHT,
                     SPR_PRA_BUTTON_C_UP_RIGHT,
                     SPR_PRA_BUTTON_C_DOWN,
                     SPR_PRA_BUTTON_C_UP_DOWN,
                     SPR_PRA_BUTTON_C_DOWN_RIGHT,
                     SPR_PRA_BUTTON_C_UP_DOWN_RIGHT,
                     SPR_PRA_BUTTON_C_LEFT,
                     SPR_PRA_BUTTON_C_UP_LEFT,
                     SPR_PRA_BUTTON_C_LEFT_RIGHT,
                     SPR_PRA_BUTTON_C_UP_LEFT_RIGHT,
                     SPR_PRA_BUTTON_C_DOWN_LEFT,
                     SPR_PRA_BUTTON_C_UP_DOWN_LEFT,
                     SPR_PRA_BUTTON_C_DOWN_LEFT_RIGHT,
                     SPR_PRA_BUTTON_C_ALL };
s32 D_80052FBC[] = { 0,
                     SPR_PRA_ARROW_UP,
                     SPR_PRA_ARROW_RIGHT,
                     SPR_PRA_ARROW_UP_RIGHT,
                     SPR_PRA_ARROW_DOWN,
                     0,
                     SPR_PRA_ARROW_DOWN_RIGHT,
                     0,
                     SPR_PRA_ARROW_LEFT,
                     SPR_PRA_ARROW_UP_LEFT,
                     0,
                     0,
                     SPR_PRA_ARROW_DOWN_LEFT };

u16 D_8013C3D0;
s32 D_8013C3D4_unused;
Object *D_8013C3D8[12];
u16 D_8013C408;
u16 D_8013C40A;
s32 D_8013C40C_unused;
s16 D_8013C410[12];
s16 D_8013C428;
s16 D_8013C42A;
s16 D_8013C42C;
s32 D_8013C430;
s32 D_8013C434;
s32 gPracticePauseMenuSelection;
s32 D_8013C43C;
s32 D_8013C440;
s32 D_8013C444;
s32 D_8013C448;
s32 D_8013C44C;
s32 D_8013C450;
s32 D_8013C454;
s32 D_8013C458;
u8 D_8013C45C;
u8 D_8013C45D;
u8 D_8013C45E;
u8 D_8013C45F;
Object *D_8013C460;
Object *D_8013C464;
Object *D_8013C468;
Object *D_8013C46C;
Object *D_8013C470;
Object *D_8013C474;
Object *D_8013C478;
Object *D_8013C47C;
Object *D_8013C480;
Object *D_8013C484;
Object *D_8013C488;
Object *D_8013C48C;
Object *D_8013C490;
u16 gPracticingPlayer;

void func_800327D8(Object *);
void func_80032D2C(Object *);
void func_80032E00(Object *);
void func_80032EDC(Object *);
void func_8003307C(Object *);
void func_80033124(Object *);
void func_800331D0(Object *);
void func_80033250(Object *);
void func_800332D0(Object *);
void func_800333F4(void);
void func_80033E94(Object *);
void func_80033FB0(Object *);
void func_800335BC(void);
void func_80033958(void);
void func_80033AB0(void);

void practice_init_hud(void) {
    Object *temp_v0_2;

    gPracticePauseMenuSelection = 112;
    D_8013C430 = 16;
    D_8013C434 = 65;
    D_8013C43C = D_8013C440 = 0;
    func_800333F4();

    D_8013C40A = 0;
    D_8013C444 = 0;
    gPlayers[1 - gPracticingPlayer].unk_80 |= 0x200000;
    gBattleSettings[1 - gPracticingPlayer].isCpu = FALSE;

    temp_v0_2 = create_ui_element(&D_80052ED0, &D_80052E4C, 0xABAB);
    temp_v0_2->frameIndex = SPR_PRA_DAMAGE;
    temp_v0_2->currentTask->func = func_800332D0;

    D_8013C480 = create_ui_element(&D_80052EE0, &D_80052E4C, 0xABAB);
    D_8013C484 = create_ui_element(&D_80052EF0, &D_80052E4C, 0xABAB);
    D_8013C488 = create_ui_element(&D_80052F00, &D_80052E4C, 0xABAB);
    D_8013C48C = create_ui_element(&D_80052F10, &D_80052E4C, 0xABAB);
    D_8013C490 = create_ui_element(&D_80052F20, &D_80052E4C, 0xABAB);
    task_clear(D_8013C480->taskList);
    D_8013C480->taskList = NULL;
    task_clear(D_8013C484->taskList);
    D_8013C484->taskList = NULL;
    task_clear(D_8013C488->taskList);
    D_8013C488->taskList = NULL;
    task_clear(D_8013C48C->taskList);
    D_8013C48C->taskList = NULL;
    task_clear(D_8013C490->taskList);
    D_8013C490->taskList = NULL;

    gPlayerInput[gPracticingPlayer].unk_0C = FALSE;
    gPlayers[gPracticingPlayer].damage = gPlayers[gPracticingPlayer].total_damage = 0;
}

void practice_enter_pause(s32 playerId) {
    Object *v0;

    while (gTaskPool.count < 10 || D_8013C2B0.count < 10) {
        func_8000132C();
    }

    D_8013C464 = create_ui_element(&D_80052E60, &D_80052DAC, 0xABAB);
    D_8013C464->fn_render = func_80032D2C;
    task_clear(D_8013C464->taskList);
    D_8013C464->taskList = NULL;

    D_8013C468 = create_ui_element(&D_80052E70, &D_80052DC0, 0xABAB);
    D_8013C468->fn_render = func_80032E00;
    task_clear(D_8013C468->taskList);
    D_8013C468->taskList = NULL;

    D_8013C46C = create_ui_element(&D_80052E80, &D_80052DD4, 0xABAB);
    D_8013C46C->fn_render = func_80032EDC;
    task_clear(D_8013C46C->taskList);
    D_8013C46C->taskList = NULL;

    D_8013C470 = create_ui_element(&D_80052E90, &D_80052DE8, 0xABAB);
    D_8013C470->fn_render = func_8003307C;
    task_clear(D_8013C470->taskList);
    D_8013C470->taskList = NULL;

    D_8013C474 = create_ui_element(&D_80052EA0, &D_80052DFC, 0xABAB);
    D_8013C474->fn_render = func_80033124;
    task_clear(D_8013C474->taskList);
    D_8013C474->taskList = NULL;

    D_8013C478 = create_ui_element(&D_80052EB0, &D_80052E10, 0xABAB);
    D_8013C478->fn_render = func_800331D0;
    task_clear(D_8013C478->taskList);
    D_8013C478->taskList = NULL;

    D_8013C47C = create_ui_element(&D_80052EC0, &D_80052E24, 0xABAB);
    D_8013C47C->fn_render = func_80033250;
    task_clear(D_8013C47C->taskList);
    D_8013C47C->taskList = NULL;

    v0 = create_worker(func_800327D8, 0x1064);
    task_clear(v0->taskList);
    v0->taskList = NULL;
    v0->vars[0] = playerId;

    D_8013C450 = gPracticePauseMenuSelection;
    D_8013C448 = D_8013C430;
    D_8013C44C = D_8013C434;
    D_8013C454 = D_8013C43C;
    D_8013C458 = D_8013C458;
    D_8013C45C = D_8013C45D = D_8013C45E = D_8013C45F = FALSE;
    gIsPaused = TRUE;
    D_8013C460->flags |= 4;
}

void func_80032750(Object *obj) {
    if (gPlayerInput[PLAYER_1].buttons & INP_LEFT) {
        obj->pos.x++;
    }
    if (gPlayerInput[PLAYER_1].buttons & INP_RIGHT) {
        obj->pos.x--;
    }
    if (gPlayerInput[PLAYER_1].buttons & INP_UP) {
        obj->pos.y--;
    }
    if (gPlayerInput[PLAYER_1].buttons & INP_DOWN) {
        obj->pos.y++;
    }
}

void func_800327D8(Object *obj) {
    s16 playerId;
    u16 buttons;

    playerId = obj->vars[0];
    buttons = 0;

    func_80002178(160, NULL);

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].raw_buttons;
        gPlayerInput[playerId].unk_08 = FALSE;
    }

    if (!buttons) {
        obj->vars[1] = 0;
        return;
    }

    if (--obj->vars[1] > 0) {
        return;
    }
    obj->vars[1] = 10;

    if (buttons & INP_DOWN) {
        gPracticePauseMenuSelection++;
        if (gPracticePauseMenuSelection > 118) {
            gPracticePauseMenuSelection = 112;
        }

        if (gPracticePauseMenuSelection == 114 && D_8013C430 != 18) {
            gPracticePauseMenuSelection = 115;
        } else if (gPracticePauseMenuSelection == 116 && D_8013C434 != 66) {
            gPracticePauseMenuSelection = 117;
        }
    } else if (buttons & INP_UP) {
        gPracticePauseMenuSelection--;
        if (gPracticePauseMenuSelection < 112) {
            gPracticePauseMenuSelection = 118;
        }

        if (gPracticePauseMenuSelection == 114 && D_8013C430 != 18) {
            gPracticePauseMenuSelection = 113;
        } else if (gPracticePauseMenuSelection == 116 && D_8013C434 != 66) {
            gPracticePauseMenuSelection = 115;
        }
    } else if (buttons & INP_RIGHT) {
        switch (gPracticePauseMenuSelection) {
            case 113:
                D_8013C430++;
                if (D_8013C430 > 18) {
                    D_8013C430 = 16;
                }
                break;
            case 115:
                D_8013C434++;
                if (D_8013C434 > 66) {
                    D_8013C434 = 65;
                }
                break;
            case 114:
                D_8013C43C++;
                if (D_8013C43C >= D_80052D80[gPlayers[playerId].characterId]) {
                    D_8013C43C = 0;
                }
                break;
            case 116:
                D_8013C440++;
                if (D_8013C440 >= D_80052D80[gPlayers[1 - playerId].characterId]) {
                    D_8013C440 = 0;
                }
                break;
        }
    }

    if (buttons & INP_LEFT) {
        switch (gPracticePauseMenuSelection) {
            case 113:
                D_8013C430--;
                if (D_8013C430 < 16) {
                    D_8013C430 = 18;
                }
                break;
            case 115:
                D_8013C434--;
                if (D_8013C434 < 65) {
                    D_8013C434 = 66;
                }
                break;
            case 114:
                D_8013C43C--;
                if (D_8013C43C < 0) {
                    D_8013C43C = D_80052D80[gPlayers[playerId].characterId] - 1;
                }
                break;
            case 116:
                D_8013C440--;
                if (D_8013C440 < 0) {
                    D_8013C440 = D_80052D80[gPlayers[1 - playerId].characterId] - 1;
                }
                break;
        }
    }

    if (buttons & INP_START) {
        switch (gPracticePauseMenuSelection) {
            case 118:
                D_8005BFC0 |= GAME_FLAG_80 | GAME_FLAG_40 | GAME_FLAG_MODE_DONE;
                gNextGameMode = GAME_MODE_MAIN_MENU;
                obj->flags |= 0x10;
                return;
            case 112:
                D_8005BFC0 |= GAME_FLAG_40;
                obj->flags |= 0x10;
                gPracticePauseMenuSelection = D_8013C450;
                D_8013C430 = D_8013C448;
                D_8013C434 = D_8013C44C;
                D_8013C43C = D_8013C454;
                D_8013C440 = D_8013C458;
                return;
            case 117:
                D_8005BFC0 |= GAME_FLAG_40 | GAME_FLAG_MODE_DONE;
                obj->flags |= 0x10;
                gNextGameMode = GAME_MODE_PLAYER_SELECTION;
                return;
        }

        D_8005BFC0 |= GAME_FLAG_40;
        obj->flags |= 0x10;
    }
}

void func_80032CEC(Object *obj) {
    if (D_8005BFC0 & GAME_FLAG_40) {
        obj->flags |= 0x10;
    }
    func_80015724(obj);
}

void func_80032D2C(Object *obj) {
    D_8013C45C = D_8013C45D = D_8013C45E = D_8013C45F = FALSE;
    obj->frameIndex = SPR_PRA_PAUSE_MENU_4;

    switch (gPracticePauseMenuSelection) {
        case 112:
            obj->frameIndex = SPR_PRA_PAUSE_MENU_1;
            break;
        case 113:
            D_8013C45C = TRUE;
            break;
        case 115:
            D_8013C45D = TRUE;
            break;
        case 117:
            obj->frameIndex = SPR_PRA_PAUSE_MENU_2;
            break;
        case 114:
            D_8013C45E = TRUE;
            break;
        case 116:
            D_8013C45F = TRUE;
            break;
        case 118:
            obj->frameIndex = SPR_PRA_PAUSE_MENU_3;
            break;
    }
    func_80032CEC(obj);
}

void func_80032E00(Object *obj) {
    switch (D_8013C430) {
        case 16:
            obj->frameIndex = SPR_PRA_BLUE_ON;
            func_800335BC();
            break;
        case 17:
            obj->frameIndex = SPR_PRA_BLUE_OFF;
            func_800335BC();
            break;
        case 18:
            obj->frameIndex = SPR_PRA_BLUE_COMBOS;
            if (D_8013C434 == 66 && gPracticePauseMenuSelection != 115) {
                D_8013C434 = 65;
            }
            func_80033958();
            break;
    }

    if (D_8013C45C) {
        obj->frameIndex += 3;
    }
    func_80032CEC(obj);
}

void func_80032EDC(Object *obj) {
    switch (D_8013C434) {
        case 64:
            obj->frameIndex = SPR_PRA_BLUE_ON;
            gPlayers[1 - gPracticingPlayer].unk_DBE = 50;
            gPlayers[1 - gPracticingPlayer].unk_80 &= ~0x200000;
            break;
        case 66:
            if (D_8013C430 == 18) {
                D_8013C430 = 16;
            }
            obj->frameIndex = SPR_PRA_BLUE_COMBOS;
            func_80033AB0();
            gPlayers[1 - gPracticingPlayer].unk_80 |= 0x200000;
            break;
        case 65:
            obj->frameIndex = SPR_PRA_BLUE_OFF;
            gPlayers[1 - gPracticingPlayer].unk_80 |= 0x200000;
            break;
    }

    if (D_8013C45D) {
        obj->frameIndex += 3;
    }
    func_80032CEC(obj);
}

void func_8003307C(Object *obj) {
    s16 characterId;

    if (D_8013C430 == 18) {
        characterId = gPlayers[gPracticingPlayer].characterId;
        if (characterId >= CHARACTER_5) {
            characterId--;
        }
        obj->frameIndex = characterId + SPR_PRA_AARON;
        obj->flags &= ~4;
    } else {
        obj->flags |= 4;
    }

    func_80032CEC(obj);
}

void func_80033124(Object *obj) {
    s16 characterId;

    if (D_8013C434 == 66) {
        characterId = gPlayers[1 - gPracticingPlayer].characterId;
        if (characterId >= CHARACTER_5) {
            characterId--;
        }
        obj->frameIndex = characterId + SPR_PRA_AARON;
        obj->flags &= ~4;
    } else {
        obj->flags |= 4;
    }

    func_80032CEC(obj);
}

void func_800331D0(Object *obj) {
    if (D_8013C430 == 18) {
        obj->flags &= ~4;
        obj->frameIndex = D_8013C43C + SPR_PRA_RED_DIGIT_1;
    } else {
        obj->flags |= 4;
    }

    if (D_8013C45E) {
        obj->frameIndex = D_8013C43C + SPR_PRA_GREEN_DIGIT_1;
    }
    func_80032CEC(obj);
}

void func_80033250(Object *obj) {
    if (D_8013C434 == 66) {
        obj->flags &= ~4;
        obj->frameIndex = D_8013C440 + SPR_PRA_RED_DIGIT_1;
    } else {
        obj->flags |= 4;
    }

    if (D_8013C45F) {
        obj->frameIndex = D_8013C440 + SPR_PRA_GREEN_DIGIT_1;
    }
    func_80032CEC(obj);
}

void func_800332D0(Object *obj) {
    Player *player;
    u32 v1;
    s16 a0;
    s16 v0;
    u32 a00;
    s16 a1;
    u32 nv = 100U;
    u32 nv2 = 10;

    player = &gPlayers[gPracticingPlayer];

    v1 = player->damage;
    if (v1 > 99) {
        v1 = 99;
    }
    a0 = v1 / nv2;
    D_8013C484->frameIndex = a0;
    D_8013C480->frameIndex = v1 - a0 * nv2;

    v1 = player->total_damage;
    if (v1 > 999) {
        v1 = 999;
    }
    v0 = v1 / nv;
    a00 = v1 - v0 * nv;
    a1 = a00 / nv2;
    D_8013C490->frameIndex = v0;
    D_8013C48C->frameIndex = a1;
    D_8013C488->frameIndex = a00 - a1 * nv2;
}

void func_800333F4(void) {
    s32 i;
    Vec4i sp4C = { 32, 186, 0, 0 };
    Vec4i sp3C = { 24, 177, 0, 0 };

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i] = create_ui_element(&sp4C, &D_80052E38, 0xABAB);
        D_8013C3D8[i]->flags |= 4;
        task_clear(D_8013C3D8[i]->taskList);
        D_8013C3D8[i]->taskList = NULL;
        sp4C.x += 20;
        D_8013C3D8[i]->vars[0] = i;
        D_8013C3D8[i]->fn_render = func_80033FB0;
    }

    D_8013C408 = 0;
    sp4C.y -= 20;
    D_8013C460 = create_ui_element(&sp3C, &D_80052DAC, 0xABAB);
    D_8013C460->frameIndex = SPR_PRA_AUTO_PLAY;
    D_8013C460->currentTask->func = func_80033E94;
}

void func_8003355C(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i]->flags |= 0x10;
    }
}

void func_800335BC(void) {
    s16 i;

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i]->flags |= 4;
    }

    D_8013C408 = D_8013C40A = 0;
}

void func_8003360C(u16 arg0) {
    Object *v0;
    s16 i;

    if (arg0) {
        if (D_8013C40A > 45) {
            func_800335BC();
        } else {
            D_8013C40A = 0;
        }

        if (D_8013C408 < 12) {
            v0 = D_8013C3D8[D_8013C408++];
        } else {
            for (i = 0; i < 11; i++) {
                D_8013C3D8[i]->frameIndex = D_8013C3D8[i + 1]->frameIndex;
            }
            v0 = D_8013C3D8[11];
        }

        v0->frameIndex = arg0;
        v0->flags &= ~4;
        v0->vars[2] = arg0;
    }
}

void func_800336E4(u16 arg0) {
    if (((arg0 >> 12) & 0xF) != 0) {
        func_8003360C(D_80052FBC[(arg0 >> 12) & 0xF]);
    }

    if ((arg0 & 0xF) != 0) {
        func_8003360C(D_80052F58[arg0 & 0xF]);
    }

    if (((arg0 >> 4) & 0xF) != 0) {
        func_8003360C(D_80052F7C[(arg0 >> 4) & 0xF]);
    }
}

void func_80033774(u16 arg0) {
    Object *a0;

    if (arg0) {
        a0 = D_8013C3D8[D_8013C408++];
        a0->frameIndex = arg0 + 1;
        func_80033FB0(a0);
    }
}

void func_800337C8(u16 arg0) {
    if (D_8013C430 != 16) {
        if (((arg0 >> 12) & 0xF) != 0) {
            func_80033774(D_80052FBC[(arg0 >> 12) & 0xF]);
        }

        if ((arg0 & 0xF) != 0) {
            func_80033774(D_80052F58[arg0 & 0xF]);
        }

        if (((arg0 >> 4) & 0xF) != 0) {
            func_80033774(D_80052F7C[(arg0 >> 4) & 0xF]);
        }
    }
}

void func_80033868(void) {
    u32 i;

    if (D_8013C430 != 16) {
        for (i = 0; i < D_8013C408; i++) {
            D_8013C3D8[i]->frameIndex = D_8013C3D8[i]->vars[2];
        }
    }

    D_8013C408 = 0;
    D_8013C42A = 0;
}

void func_800338D0(void) {
    u16 a0;

    a0 = gPlayerInput[gPracticingPlayer].raw_buttons;
    a0 &= ~D_8013C3D0;
    D_8013C3D0 = gPlayerInput[gPracticingPlayer].raw_buttons;

    if (!D_8013C3D0) {
        D_8013C40A++;
    }
    if (a0) {
        func_800336E4(a0);
    }
}

void func_80033958(void) {
    s16 v1;
    Player *s2;
    s16 *s0;
    s16 s1;
    PlayerSub8 *new_var;
    s16 **q;
    s16 *tmp2;
    s16 t3;

    s2 = gPlayers + gPracticingPlayer;
    v1 = gPlayers[gPracticingPlayer].characterId;
    if (v1 >= CHARACTER_5) {
        v1--;
    }

    q = D_80052F30[v1];
    s0 = q[D_8013C43C];

    func_800335BC();
    D_8013C428 = D_8013C42A = 0;

    s1 = *s0;
    while (s1 != 0) {
        t3 = s2->unk_38[s1];
        tmp2 = s2->unk_34;
        new_var = &s2->unk_2C[tmp2[t3]];
        D_8013C410[D_8013C428++] = tmp2[t3];
        func_800336E4(new_var->unk_02);
        s0++;
        s1 = *s0;
    }

    D_8013C408 = 0;
}

void func_80033AB0(void) {
    s16 v1;
    Player *s2;
    s16 *s0;
    s16 s1;
    PlayerSub8 *new_var;
    s16 **q;
    s16 *tmp2;
    s16 t3;

    s2 = gPlayers + 1 - gPracticingPlayer;
    v1 = gPlayers[1 - gPracticingPlayer].characterId;
    if (v1 >= CHARACTER_5) {
        v1--;
    }

    q = D_80052F30[v1];
    s0 = q[D_8013C440];

    func_800335BC();
    D_8013C428 = D_8013C42A = 0;

    s1 = *s0;
    while (s1 != 0) {
        t3 = s2->unk_38[s1];
        tmp2 = s2->unk_34;
        new_var = &s2->unk_2C[tmp2[t3]];
        D_8013C410[D_8013C428++] = tmp2[t3];
        func_800336E4(new_var->unk_02);
        s0++;
        s1 = *s0;
    }

    D_8013C408 = 0;
}

void func_80033C38(void) {
    u16 a2;
    PlayerSub8 *new_var;

    if (--D_8013C42C <= 0) {
        a2 = (D_8013C430 == 18) ? gPracticingPlayer : 1 - gPracticingPlayer;

        if (D_8013C42A < D_8013C428) {
            new_var = &gPlayers[a2].unk_2C[D_8013C410[D_8013C42A]];
            gPlayerInput[a2].buttons = new_var->unk_02;
            gPlayerInput[a2].unk_08 = TRUE;
        } else {
            D_8013C444 = FALSE;
            gPlayerInput[gPracticingPlayer].enabled = TRUE;
            D_8005BFC0 &= ~GAME_FLAG_4;
        }
    }
}

void func_80033D64(void) {
    u16 a2;
    Player *player;

    if (D_8013C430 == 18) {
        a2 = gPracticingPlayer;
    } else {
        a2 = 1 - gPracticingPlayer;
    }
    player = &gPlayers[a2];

    if (D_8013C444 != 0) {
        func_80033C38();
    }

    if (player->unk_74 == D_8013C410[D_8013C42A]) {
        func_800337C8(player->unk_A0->unk_02);
        D_8013C42A++;
        if (D_8013C444) {
            func_80033C38();
        }
        D_8013C42C = 15;
    } else if (D_8013C42A != 0 && player->unk_74 != D_8013C410[D_8013C42A - 1]) {
        func_80033868();
        D_8013C444 = FALSE;
    }
}

void func_80033E94(Object *obj) {
    if (D_8013C430 != 18 && D_8013C434 != 66) {
        obj->flags |= 4;
        return;
    }

    if (--obj->vars[0] < 0 && D_8013C444 == 0) {
        obj->flags ^= 4;
        obj->vars[0] = 12;
    } else if (D_8013C444 != 0) {
        obj->flags &= ~4;
    }

    if (gPlayerInput[gPracticingPlayer].buttons == INP_A) {
        D_8013C444 = 1;
        D_8013C42C = 0;
        D_8005BFC0 |= GAME_FLAG_4;
        if (D_8013C430 == 18) {
            gPlayerInput[gPracticingPlayer].enabled = FALSE;
        } else {
            gPlayerInput[1 - gPracticingPlayer].enabled = FALSE;
        }
    }
}

void func_80033FB0(Object *obj) {
    s32 q;
    if (D_8013C430 != 18 || (obj->flags & 4)) {
        func_80015724(obj);
        return;
    }

    if (gPlayerInput[gPracticingPlayer].isMirrored) {
        if (obj->vars[2] != SPR_PRA_ARROW_LEFT) {
            if (obj->vars[2] == SPR_PRA_ARROW_RIGHT) {
                obj->frameIndex = (q = (obj->frameIndex & 1) == 0) + SPR_PRA_ARROW_LEFT;
            }
        } else {
            obj->frameIndex = (q = (obj->frameIndex & 1) == 0) + SPR_PRA_ARROW_RIGHT;
        }
    } else {
        obj->frameIndex = (q = (obj->frameIndex & 1) == 0) + obj->vars[2];
    }

    func_80015724(obj);
}
