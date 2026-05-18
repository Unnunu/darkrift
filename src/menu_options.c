#include "common.h"
#include "task.h"
#include "sprite_ids.h"

#define MAX_OBJECTS_IN_RANK_ROW 10

s16 D_80049B20[] = { 4, 7, 6, 5, 1, 3, 0, 2 };
s16 D_80049B30[] = { INP_CUP, INP_CLEFT, INP_CDOWN, INP_CRIGHT, INP_B, INP_L, INP_R, INP_A };

Object *gRankTable;
char D_80081464_unused[4];
Object *gRankRowObjects[MAX_OBJECTS_IN_RANK_ROW];
s16 gRankRowObjectIndex;
s32 D_80081494_unused;
s16 gRankOrder[NUM_CHARACTERS];
s16 gWinPercent[NUM_CHARACTERS];
Vec4i gRankRowPos;

void options_update_buttons(Object *obj, s16 buttons, s16 playerId) {
    s16 prevButtons;
    s16 counter;
    s32 pressed;

    pressed = FALSE;
    prevButtons = obj->vars[VAR_OPT_CTRL_BUTTONS];
    obj->vars[VAR_OPT_CTRL_BUTTONS] = buttons;
    counter = obj->vars[VAR_OPT_CTRL_COUNTER]--;

    if (counter > 0 && buttons == prevButtons) {
        return;
    }
    obj->vars[VAR_OPT_CTRL_COUNTER] = 15;

    if (buttons & INP_UP) {
        obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
        obj->vars[VAR_OPT_CTRL_CURRENT_ROW] = (obj->vars[VAR_OPT_CTRL_CURRENT_ROW] + 9) % 10;
        pressed = TRUE;
    } else if (buttons & INP_DOWN) {
        obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
        obj->vars[VAR_OPT_CTRL_CURRENT_ROW] = (obj->vars[VAR_OPT_CTRL_CURRENT_ROW] + 1) % 10;
        pressed = TRUE;
    } else if (buttons & INP_LEFT) {
        obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = -1;
        pressed = TRUE;
    } else if (buttons & INP_RIGHT) {
        obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 1;
        pressed = TRUE;
    }

    if (pressed) {
        sound_play(2, 1);
    }
}

void options_update(Object *obj) {
    s16 buttons;
    s16 buttons2;

    buttons = gPlayerInput[PLAYER_1].buttons;
    buttons2 = gPlayerInput[PLAYER_2].buttons;

    if (buttons != 0) {
        options_update_buttons(obj, buttons, PLAYER_1);
    } else if (buttons2 != 0) {
        options_update_buttons(obj, buttons2, PLAYER_2);
    } else {
        obj->vars[VAR_OPT_CTRL_BUTTONS] = 0;
    }
}

void options_difficulty_update(Object *obj) {
    Object *controller;
    s16 leftright;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 0) {
        if (obj->frameIndex >= OPTIONS_EASY && obj->frameIndex <= OPTIONS_HARD) {
            obj->frameIndex += 3;
        }

        leftright = controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON];
        if (leftright != 0) {
            obj->frameIndex = OPTIONS_EASY_HL + ((obj->frameIndex + leftright + 2) % 3);
            controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
            gDifficulty = obj->frameIndex - OPTIONS_EASY_HL;
        }
    } else {
        if (obj->frameIndex >= OPTIONS_EASY_HL && obj->frameIndex <= OPTIONS_HARD_HL) {
            obj->frameIndex -= 3;
        }
    }
}

void options_timer_update(Object *obj) {
    Object *controller;
    s16 leftright;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 1) {
        if (obj->frameIndex >= OPTIONS_00 && obj->frameIndex <= OPTIONS_90) {
            obj->frameIndex += 3;
        }

        leftright = controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON];
        if (leftright != 0) {
            obj->frameIndex = OPTIONS_00_HL + ((obj->frameIndex + leftright) % 3);
            controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
            gBattleDuration = obj->frameIndex - OPTIONS_00_HL;
        }
    } else {
        if (obj->frameIndex >= OPTIONS_00_HL && obj->frameIndex <= OPTIONS_90_HL) {
            obj->frameIndex -= 3;
        }
    }
}

void options_rounds_update(Object *obj) {
    Object *controller;
    s16 leftright;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 2) {
        if (obj->frameIndex >= OPTIONS_1 && obj->frameIndex <= OPTIONS_5) {
            obj->frameIndex += 10;
        }

        leftright = controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON];
        if (leftright != 0) {
            obj->frameIndex = OPTIONS_1_HL + ((obj->frameIndex + leftright + 3) % 5);
            controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
            gMaxRounds = obj->frameIndex - OPTIONS_0_HL;
        }
    } else {
        if (obj->frameIndex >= OPTIONS_1_HL && obj->frameIndex <= OPTIONS_5_HL) {
            obj->frameIndex -= 10;
        }
    }
}

void options_audio_update(Object *obj) {
    Object *controller;
    s16 leftright;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 3) {
        if (obj->frameIndex == OPTIONS_STEREO || obj->frameIndex == OPTIONS_MONO) {
            obj->frameIndex += 2;
        }

        leftright = controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON];
        if (leftright != 0) {
            obj->frameIndex = OPTIONS_STEREO_HL + ((obj->frameIndex + leftright + 1) % 2);
            controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
            gAudioMono = obj->frameIndex - OPTIONS_STEREO_HL;
        }
    } else {
        if (obj->frameIndex == OPTIONS_STEREO_HL || obj->frameIndex == OPTIONS_MONO_HL) {
            obj->frameIndex -= 2;
        }
    }
}

void options_music_update(Object *obj) {
    Object *controller;
    s16 leftright;
    s32 volume;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 4) {
        if (obj->frameIndex >= OPTIONS_0 && obj->frameIndex <= OPTIONS_9) {
            obj->frameIndex += 10;
        }

        leftright = controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON];
        if (leftright != 0) {
            obj->frameIndex = OPTIONS_0_HL + ((obj->frameIndex + leftright + 9) % 10);
            controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;

            volume = (obj->frameIndex - OPTIONS_0_HL) * (0x7FFF / 9);
            if (volume > 0x7FFF) {
                volume = 0x7FFF;
            }
            if (volume == 0) {
                volume = 1;
            }

            if (volume != gMusicVolume) {
                music_set_volume(volume);
            }
            gMusicVolumeFading = gMusicVolume = volume;
        }
    } else {
        if (obj->frameIndex >= OPTIONS_0_HL && obj->frameIndex <= OPTIONS_9_HL) {
            obj->frameIndex -= 10;
        }
    }
}

void options_sfx_update(Object *obj) {
    Object *controller;
    s16 leftright;
    s32 volume;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 5) {
        if (obj->frameIndex >= OPTIONS_0 && obj->frameIndex <= OPTIONS_9) {
            obj->frameIndex += 10;
        }

        leftright = controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON];
        if (leftright != 0) {
            obj->frameIndex = OPTIONS_0_HL + ((obj->frameIndex + leftright + 9) % 10);
            controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;

            volume = (obj->frameIndex - OPTIONS_0_HL) * (0x7FFF / 9);
            if (volume > 0x7FFF) {
                volume = 0x7FFF;
            }
            if (volume == 0) {
                volume = 1;
            }

            if (volume != gSoundVolume) {
                sound_set_volume(2, volume);
            }
            gSoundVolumeFading = gSoundVolume = volume;
        }
    } else {
        if (obj->frameIndex >= OPTIONS_0_HL && obj->frameIndex <= OPTIONS_9_HL) {
            obj->frameIndex -= 10;
        }
    }
}

void options_controls_update(Object *obj) {
    Object *controller;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 6) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if ((gPlayerInput[PLAYER_1].buttons == INP_START) || gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_MENU_CONTROLS;
            gGlobalFlags |= GAME_FLAG_MODE_DONE;
            TASK_END(obj->currentTask);
            sound_play(2, 0);
        }
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void options_rankings_update(Object *obj) {
    Object *controller;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 7) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if ((gPlayerInput[PLAYER_1].buttons == INP_START) || gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_MENU_RANKINGS;
            gGlobalFlags |= GAME_FLAG_MODE_DONE;
            TASK_END(obj->currentTask);
            sound_play(2, 0);
        }
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void options_stats_update(Object *obj) {
    Object *controller;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 8) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if ((gPlayerInput[PLAYER_1].buttons == INP_START) || gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_MENU_STATS;
            gGlobalFlags |= GAME_FLAG_MODE_DONE;
            TASK_END(obj->currentTask);
            sound_play(2, 0);
        }
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void options_exit_update(Object *obj) {
    Object *controller;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == 9) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if ((gPlayerInput[PLAYER_1].buttons == INP_START) || gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_MAIN_MENU;
            gGlobalFlags |= GAME_FLAG_MODE_DONE;
            TASK_END(obj->currentTask);
            sound_play(2, 0);
        }
    } else {
        obj->flags |= OBJ_FLAG_HIDDEN;
    }
}

void controls_handle_button_remap(Object *obj, s16 buttons, s16 playerId) {
    s16 prevButtons;
    s16 counter;
    s32 pressed;

    pressed = FALSE;
    prevButtons = obj->vars[VAR_OPT_CTRL_BUTTONS];
    obj->vars[VAR_OPT_CTRL_BUTTONS] = buttons;
    counter = obj->vars[VAR_OPT_CTRL_COUNTER]--;

    if (counter > 0 && buttons == prevButtons) {
        return;
    }
    obj->vars[VAR_OPT_CTRL_COUNTER] = 15;

    if (buttons & INP_UP) {
        obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
        obj->vars[VAR_OPT_CTRL_CURRENT_ROW] = (obj->vars[VAR_OPT_CTRL_CURRENT_ROW] + 8) % 9;
        obj->vars[VAR_OPT_CTRL_CURRENT_BUTTON] = 0;
        pressed = TRUE;
    } else if (buttons & INP_DOWN) {
        obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;
        obj->vars[VAR_OPT_CTRL_CURRENT_ROW] = (obj->vars[VAR_OPT_CTRL_CURRENT_ROW] + 1) % 9;
        obj->vars[VAR_OPT_CTRL_CURRENT_BUTTON] = 0;
        pressed = TRUE;
    } else if (buttons & INP_MASK_FF) {
        pressed = TRUE;

        if (buttons & INP_CUP) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_C_UP;
        } else if (buttons & INP_CLEFT) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_C_LEFT;
        } else if (buttons & INP_CDOWN) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_C_DOWN;
        } else if (buttons & INP_CRIGHT) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_C_RIGHT;
        } else if (buttons & INP_A) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_A;
        } else if (buttons & INP_B) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_B;
        } else if (buttons & INP_L) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_L;
        } else if (buttons & INP_R) {
            obj->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = OPTIONS_BUTTON_R;
        }
    }
    if (prevButtons) {} // @fake
    if (pressed) {
        sound_play(2, 1);
    }
}

void controls_button_update(Object *obj) {
    Object *controller;
    s16 newButton;
    s16 playerId;
    s16 i;
    s16 q;
    s16 w;

    controller = obj->varObj[VAR_OPT_CTRL_CONTROLLER];
    if (controller->vars[VAR_OPT_CTRL_CURRENT_ROW] == obj->vars[VAR_OPT_CTRL_ROW]) {
        if (obj->frameIndex >= OPTIONS_BUTTON_C_UP && obj->frameIndex <= OPTIONS_BUTTON_Z) {
            obj->frameIndex += 9;
        }

        newButton = controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON];
        if (newButton != 0) {
            controller->vars[VAR_OPT_CTRL_PREVIOUS_BUTTON] = obj->frameIndex;
            controller->vars[VAR_OPT_CTRL_CURRENT_BUTTON] = obj->frameIndex = newButton;
            controller->vars[VAR_OPT_CTRL_PRESSED_BUTTON] = 0;

            playerId = controller->vars[VAR_OPT_CTRL_PLAYER_ID];
            w = D_80049B30[obj->vars[VAR_OPT_CTRL_ROW]];
            q = D_80049B20[controller->vars[VAR_OPT_CTRL_CURRENT_BUTTON] - OPTIONS_BUTTON_C_UP];

            gButtonsMap[playerId][q] = w;
            for (i = 0; i < 8; i++) {}
        }
    } else {
        if (obj->frameIndex >= OPTIONS_BUTTON_C_UP_HL && obj->frameIndex <= OPTIONS_BUTTON_Z_HL) {
            obj->frameIndex -= 9;
        }

        if (obj->frameIndex == controller->vars[VAR_OPT_CTRL_CURRENT_BUTTON]) {
            obj->frameIndex = controller->vars[VAR_OPT_CTRL_PREVIOUS_BUTTON];

            playerId = controller->vars[VAR_OPT_CTRL_PLAYER_ID];
            w = D_80049B30[obj->vars[VAR_OPT_CTRL_ROW]];
            q = D_80049B20[controller->vars[VAR_OPT_CTRL_PREVIOUS_BUTTON] - OPTIONS_BUTTON_C_UP_HL];
            gButtonsMap[playerId][q] = w;
            for (i = 0; i < 8; i++) {}
        }
    }
}

void controls_controller_update(Object *obj) {
    s16 rawButtons;
    s16 playerId;

    playerId = obj->vars[VAR_OPT_CTRL_PLAYER_ID];
    rawButtons = gPlayerInput[playerId].raw_buttons;

    if (rawButtons != 0) {
        controls_handle_button_remap(obj, rawButtons, playerId);
    } else {
        obj->vars[VAR_OPT_CTRL_BUTTONS] = 0;
    }

    controls_button_update(obj);
}

void controls_exit_update(Object *obj) {
    u8 v1;
    Object *obj1;
    Object *obj2;

    obj->flags |= OBJ_FLAG_HIDDEN;

    obj1 = obj->varObj[VAR_OPT_CTRL_EXIT_0];
    obj2 = obj->varObj[VAR_OPT_CTRL_EXIT_1];

    v1 = 0;
    if (obj1->vars[VAR_OPT_CTRL_CURRENT_ROW] == 8) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if (gPlayerInput[PLAYER_1].buttons == INP_START) {
            gNextGameMode = GAME_MODE_MENU_OPTIONS;
            gGlobalFlags |= GAME_FLAG_MODE_DONE;
            TASK_END(obj->currentTask);
            v1++;
        }
    }
    if (obj2->vars[VAR_OPT_CTRL_CURRENT_ROW] == 8) {
        obj->flags &= ~OBJ_FLAG_HIDDEN;
        if (gPlayerInput[PLAYER_2].buttons == INP_START) {
            gNextGameMode = GAME_MODE_MENU_OPTIONS;
            gGlobalFlags |= GAME_FLAG_MODE_DONE;
            TASK_END(obj->currentTask);
            v1++;
        }
    }

    if (v1 != 0) {
        sound_play(2, 0);
    }
}

void stats_update(Object *obj) {
    s16 prevButtons;
    s16 buttons;
    char charName[20];
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
        characterId = obj->vars[0] = (obj->vars[0] + NUM_CHARACTERS - 1) % NUM_CHARACTERS;
        if (characterId == CHARACTER_5 || characterId == SONORK && !gSonorkUnlocked ||
            characterId == DEMITRON && !gDemitronUnlocked) {
            obj->vars[0]--;
        }

        mem_free(gBgLayerList);
        gBgLayerList = NULL;
        str_copy(charName, D_8004B844[obj->vars[0]].unk_04->name);
        str_concat(charName, "st");
        bg_layer_create(charName, 0, 13, 0, 0, TEX_FLAG_1, CONTEXT_2000);
        sound_play(2, 1);
    } else if (buttons & INP_RIGHT) {
        characterId = obj->vars[0] = (obj->vars[0] + 1) % NUM_CHARACTERS;
        if (characterId == CHARACTER_5 || characterId == SONORK && !gSonorkUnlocked ||
            characterId == DEMITRON && !gDemitronUnlocked) {
            obj->vars[0]++;
        }

        mem_free(gBgLayerList);
        gBgLayerList = NULL;
        str_copy(charName, D_8004B844[obj->vars[0]].unk_04->name);
        str_concat(charName, "st");
        bg_layer_create(charName, 0, 13, 0, 0, TEX_FLAG_1, CONTEXT_2000);
        sound_play(2, 1);
    } else if (buttons & INP_START) {
        gNextGameMode = GAME_MODE_MENU_OPTIONS;
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        TASK_END(obj->currentTask);
        sound_play(2, 0);
    }
}

void menu_rank_handle_input(Object *obj) {
    s16 buttons;

    buttons = gPlayerInput[PLAYER_1].buttons | gPlayerInput[PLAYER_2].buttons;
    if (buttons & INP_START) {
        gNextGameMode = GAME_MODE_MENU_OPTIONS;
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        TASK_END(obj->currentTask);
        sound_play(2, 0);
    }
}

void menu_rank_draw_number(s16 number, s16 posX, s16 posY) {
    UIElement ui_stub = { 0, NULL, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
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
        v1 = gRankRowObjects[gRankRowObjectIndex++];
        v1->pos.x = posX;
        v1->pos.y = posY;
        v1->frameIndex = 21 + hundreds;
        v1->flags &= ~OBJ_FLAG_HIDDEN;
    }

    posX += 7;

    if (hundreds != 0 || hundreds == 0 && tens != 0) {
        v1 = gRankRowObjects[gRankRowObjectIndex++];
        v1->pos.x = posX;
        v1->pos.y = posY;
        v1->frameIndex = 21 + tens;
        v1->flags &= ~OBJ_FLAG_HIDDEN;
    }

    posX += 7;

    v1 = gRankRowObjects[gRankRowObjectIndex++];
    v1->pos.x = posX;
    v1->pos.y = posY;
    v1->frameIndex = 21 + ones;
    v1->flags &= ~OBJ_FLAG_HIDDEN;
}

void rank_table_update(Object *obj) {
    s16 i;
    s16 row;
    s16 charId;
    Object *charName;
    s32 pad;

    if (!(gGlobalFlags & GAME_FLAG_1000)) {
        return;
    }
    row = obj->vars[0]++;
    if (row == 0) {
        bg_layer_delete(gBgLayerList);
    }

    for (i = 0; i < MAX_OBJECTS_IN_RANK_ROW; i++) {
        gRankRowObjects[i]->flags |= OBJ_FLAG_HIDDEN;
    }

    if (row > 10) {
        obj->currentTask->func = menu_rank_handle_input;
        gRankTable->flags |= OBJ_FLAG_HIDDEN;
        return;
    }

    charId = gRankOrder[row];
    if (charId == CHARACTER_5 || charId == SONORK && !gSonorkUnlocked || charId == DEMITRON && !gDemitronUnlocked) {
        return;
    }

    sound_play(2, 0);
    gRankRowObjectIndex = 0;

    charName = gRankRowObjects[gRankRowObjectIndex++];
    charName->pos.x = gRankRowPos.x;
    charName->pos.y = gRankRowPos.y;
    charName->frameIndex = 188 + (charId - (charId > CHARACTER_5));
    charName->flags &= ~OBJ_FLAG_HIDDEN;

    menu_rank_draw_number(gWinPercent[charId], gRankRowPos.x + 68, gRankRowPos.y);
    menu_rank_draw_number(D_800B6368[charId].wins, gRankRowPos.x + 123, gRankRowPos.y);
    menu_rank_draw_number(D_800B6368[charId].loses, gRankRowPos.x + 165, gRankRowPos.y);
    gRankRowPos.y += 16;
    obj->currentTask->start_delay = 10;
}

void menu_rank_init(void) {
    UIElement ui_stub = { 0, NULL, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    s16 i, j, k;
    s16 wins;
    s16 loses;
    s16 total;

    gRankRowPos.x = 75;
    gRankRowPos.y = 71;

    for (i = 0; i < MAX_OBJECTS_IN_RANK_ROW; i++) {
        gRankRowObjects[i] = create_ui_element(&gRankRowPos, &ui_stub, CONTEXT_2000);
        gRankRowObjects[i]->flags |= OBJ_FLAG_HIDDEN;
    }

    for (i = 0; i < NUM_CHARACTERS; i++) {
        gRankOrder[i] = i;
    }

    for (j = 0; j < NUM_CHARACTERS; j++) {
        wins = D_800B6368[j].wins;
        loses = D_800B6368[j].loses;
        total = wins + loses;
        if (total != 0) {
            gWinPercent[j] = (wins * 200 + total) / (2 * total);
        } else {
            gWinPercent[j] = 0;
        }
    }

    for (j = 1; j < NUM_CHARACTERS; j++) {
        for (i = 0; i < j; i++) {
            if (gWinPercent[gRankOrder[i]] < gWinPercent[j]) {
                for (k = j - 1; k >= i; k--) {
                    gRankOrder[k + 1] = gRankOrder[k];
                }
                gRankOrder[i] = j;
                break;
            }
        }
    }
}
