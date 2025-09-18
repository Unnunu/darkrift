#include "common.h"
#include "sprite_ids.h"

#define VAR_PLAYER_ID 0
#define VAR_SPRITE_ID_SUM 1
#define VAR_COUNTER 2

#define CHEAT_END 0xFFFF

typedef struct CheatCode {
    /* 0x00 */ u16 *sequence;
    /* 0x04 */ void (*handler)(s16, u16, u16);
    /* 0x08 */ s16 param1;
    /* 0x0A */ s16 param2;
} CheatCode; // size = 0xC

typedef struct CheatCodeState {
    /* 0x00 */ CheatCode *cheat;
    /* 0x04 */ s32 numValid;
    /* 0x08 */ s32 current_buttons;
} CheatCodeState;

extern s16 D_80080230;

extern u8 D_8004A428;
extern AssetSP2Sub3 *D_8013C234;
extern AssetSP2Sub3 *D_8013C238;

u8 D_80049DF0 = 0;
u8 D_80049DF4 = 0;

Object *gCharacterPortrait[2];
u32 D_80081668;

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001DE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001DFE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001E188.s")
u8 func_8001E188(u8 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001E378.s")
void func_8001E378(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001E540.s")
void func_8001E540(Object *, Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001E5D8.s")
s16 func_8001E5D8(s16 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001E624.s")
void func_8001E624(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001E834.s")
void func_8001E834(Object *, Object *, Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001EA24.s")
void func_8001EA24(Object *);

#ifdef NON_MATCHING
void func_8001EB58(Object *obj) {
    s16 s1;
    UIElement empty_bar = { 11, NULL, 0, 0x1000, "bars.sp2" };
    UIElement two_triangles = { 39, func_8001EA24, 0, 0x1000, "bars.sp2" };
    UIElement digit_zero = { 28, NULL, 0, 0x1000, "bars.sp2" };
    Vec4i spB8[] = { { 78, 220, 0, 0 }, { 248, 220, 0, 0 } };
    Vec4i sp98[] = { { 77, 220, 0, 0 }, { 248, 220, 0, 0 } };
    Vec4i sp78[] = { { 39, 216, 0, 0 }, { 289, 216, 0, 0 } };
    Vec4i sp58[] = { { 60, 203, 0, 0 }, { 229, 203, 0, 0 } };
    Object *s2;
    Object *s2a;
    Object *s2b;
    Object *s3;
    Object *v0;
    s16 v03;

    s1 = obj->vars[0];

    s3 = create_ui_element(&spB8[s1], &empty_bar, CONTEXT_EEFF);
    v0 = create_ui_element(&sp78[s1], &two_triangles, CONTEXT_EEFF);
    v0->vars[0] = s1;
    v0->vars[3] = s3;
    s3 = create_ui_element(&sp98[s1], &empty_bar, CONTEXT_EEFF);
    s3->spriteId = 15 - s1;
    v0->vars[4] = s3;

    v03 = func_8001E5D8(s1);
    if (s1 == 0) {
        D_8013C234 = s3->sprite_map->sprites[15].parts;
        D_8013C234->unk_10 = D_8013C234->unk_10 - D_8013C234->unk_04 + D_8013C234->unk_08 - v03 - 8;
        D_8013C234->unk_04 = D_8013C234->unk_08 - v03 - 8;
        v0->vars[1] = 119;
        v0->pos.x = 119 - v03;
    } else {
        D_8013C238 = s3->sprite_map->sprites[14].parts;
        D_8013C238->unk_08 = D_8013C238->unk_04 + v03;
        v0->vars[1] = 0xD1;
        v0->pos.x = 0xD1 + v03;
    }

    s2 = create_ui_element(&sp58[s1], &digit_zero, CONTEXT_EEFF);
    sp58[s1].x += 10;
    s2a = create_ui_element(&sp58[s1], &digit_zero, CONTEXT_EEFF);
    sp58[s1].x += 10;
    s2b = create_ui_element(&sp58[s1], &digit_zero, CONTEXT_EEFF);
    s2b->vars[0] = s1;

    func_8001E834(s2b, s2a, s2);

    v0->vars[5] = s2b;
    v0->vars[6] = s2a;
    v0->vars[7] = s2;

    obj->vars[1] = 0;
    obj->vars[9] = s2b;
    obj->currentTask->func = func_8001E624;
    obj->currentTask->counter = 20;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/plyrsel/func_8001EB58.s")
void func_8001EB58(Object *obj);
UIElement D_80049DF8 = { 11, NULL, 0, 0x1000, "bars.sp2" };
UIElement D_80049E0C = { 39, func_8001EA24, 0, 0x1000, "bars.sp2" };
UIElement D_80049E20 = { 28, NULL, 0, 0x1000, "bars.sp2" };
Vec4i D_80049E34[] = { { 0x4E, 0xDC, 0, 0 }, { 0xF8, 0xDC, 0, 0 } };
Vec4i D_80049E54[] = { { 0x4D, 0xDC, 0, 0 }, { 0xF8, 0xDC, 0, 0 } };
Vec4i D_80049E74[] = { { 0x27, 0xD8, 0, 0 }, { 0x121, 0xD8, 0, 0 } };
Vec4i D_80049E94[] = { { 0x3C, 0xCB, 0, 0 }, { 0xE5, 0xCB, 0, 0 } };
#endif

void plyrsel_portrait_update_2(Object *obj) {
    Object *unkObj;
    s16 v1;
    s16 playerId;

    if (!(D_8005BFC0 & 0x1000)) {
        return;
    }

    playerId = obj->vars[0];
    unkObj = obj->varObj[5];

    if (D_800B6328[1 - playerId].unk_02 == 0 && unkObj->vars[8] == 0) {
        return;
    }

    if (obj->vars[2]-- > 0) {
        return;
    }

    obj->vars[2] = 15;
    if (obj->spriteId >= 5) {
        v1 = obj->spriteId + 1;
    } else {
        v1 = obj->spriteId;
    }

    if (obj->vars[6] == 9 || obj->vars[6] == 1) {
        v1 = obj->vars[6];
        obj->spriteId = v1 - (v1 == SONORK);
    }

    if (v1 == obj->vars[6]) {
        sound_play(2, D_8004A428 != 0 ? 0 : playerId + 4);
        func_8001E540(obj, unkObj);
        unkObj = obj->varObj[4];
        unkObj->vars[7] = 20;
        obj->currentTask->flags |= 0x80;
        return;
    }

    sound_play(2, 6 + playerId);

    if (abs(v1 - obj->vars[6]) <= 5) {
        if (v1 < obj->vars[6]) {
            v1++;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1++;
            }
        } else {
            v1--;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1--;
            }
        }
    } else {
        if (v1 < obj->vars[6]) {
            v1--;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1--;
            }
        } else {
            v1++;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1++;
            }
        }
    }

    if (v1 < AARON) {
        v1 = ZENMURON;
    } else if (v1 > ZENMURON) {
        v1 = AARON;
    }

    if (v1 >= CHARACTER_5) {
        obj->spriteId = v1 - 1;
    } else {
        obj->spriteId = v1;
    }
}

void plyrsel_portrait_update(Object *obj) {
    s16 a1;
    s16 v0;
    s16 v1;
    s32 tmp2;
    s16 a3;
    s16 tmp;

    a3 = obj->vars[0];
    a1 = obj->vars[1];

    if (D_80080230 == 40) {
        Object *unkObj = obj->varObj[5];
        if (a3 != gPracticingPlayer) {
            if (unkObj->vars[8] == 0) {
                obj->vars[1] = 0x800;
                obj->vars[2] = 60;
                return;
            }
        }
        tmp2 = gPracticingPlayer;
        obj->vars[1] = v1 = gPlayerInput[tmp2].buttons;
    } else {
        obj->vars[1] = v1 = gPlayerInput[a3].buttons;
    }

    tmp = obj->vars[2]--;
    if (tmp <= 0 || v1 != a1) {
        obj->vars[2] = 15;
        if (v1 & INP_START) {
            Object *unkObj;
            sound_play(2, D_8004A428 != 0 ? 0 : a3 + 4);
            unkObj = obj->varObj[4];
            unkObj->vars[7] = 20;

            if (D_80080230 == 20) {
                func_8001EB58(obj);
            } else {
                func_8001E540(obj, obj->varObj[5]);
                if (D_80080230 == 10 || D_80080230 == 11) {
                    gCharacterPortrait[1 - a3]->vars[6] = func_8001E188(1 - a3);
                }
                obj->currentTask->flags |= 0x80;
            }
        } else if (v1 & (INP_LEFT | INP_RIGHT)) {
            sound_play(2, 6 + a3);

            v0 = obj->spriteId;
            if (v1 & INP_LEFT) {
                v0--;
            } else {
                v0++;
            }

            if (D_80049DF0 == 0 && v0 == 8 || D_80049DF4 == 0 && v0 == 1) {
                if (v1 & INP_LEFT) {
                    v0--;
                } else {
                    v0++;
                }
            }

            if (v0 < 0) {
                v0 = 9;
            } else if (v0 > 9) {
                v0 = 0;
            }

            obj->spriteId = v0;
        }
    }
}

void plyrsel_player_label_update(Object *obj) {
    if (obj->vars[7] != 0) {
        if (obj->vars[8]-- == 0) {
            obj->spriteId = obj->vars[0] * 4 - obj->spriteId + 171;
            obj->vars[8] = -254 - (obj->vars[0] * 2 - obj->spriteId) * 3;
        }

        if (--obj->vars[7] == 0) {
            obj->spriteId = obj->vars[0] * 2 + 86;
            obj->currentTask->flags |= 0x80;
        }
    }
}

void plyrsel_image_vs_update(Object *obj) {
    if (obj->vars[8] < 2) {
        return;
    }

    if (obj->vars[8] == 2) {
        obj->vars[8] = 3;
        obj->currentTask->counter = 10;
        gCharacterPortrait[0]->flags |= OBJ_FLAG_4000000;
        gCharacterPortrait[1]->flags |= OBJ_FLAG_4000000;
        return;
    }

    if (obj->vars[8] == 3) {
        obj->vars[8] = 4;
        gCharacterPortrait[0]->flags |= OBJ_FLAG_4000000;
        gCharacterPortrait[1]->flags |= OBJ_FLAG_4000000;
        obj->flags &= ~4;
        obj->currentTask->counter = 20;
        return;
    }

    D_800B6328[0].unk_06 = D_800B6328[1].unk_06 = 0;
    D_800B6328[0].characterId = obj->vars[9];
    D_800B6328[1].characterId = obj->vars[10];
    D_800B6328[0].unk_08 = D_800B6328[1].unk_08 = 0;
    D_800B6328[0].unk_0C &= ~3;
    D_800B6328[1].unk_0C &= ~3;
    if (0) {} // required to match
    D_8005BFC0 |= 1;

    if (D_80080230 == 10 || D_80080230 == 11) {
        gGameMode = D_800B6328[D_80081668].characterId + GAME_MODE_BATTLE_AARON;
        if (D_800B6328[0].unk_0A + D_800B6328[1].unk_0A == 0) {
            gGameMode = D_800B6328[1 - D_80081668].characterId + GAME_MODE_18;
            D_800B6328[1 - D_80081668].unk_06 = 1;
        } else {
            D_800B6328[D_80081668].unk_06 = 1;
        }
        if (D_800B6328[D_80081668].characterId == DEMITRON) {
            gGameMode = GAME_MODE_30;
        }
    } else {
        gGameMode = D_800B6328[obj->vars[11]].characterId + GAME_MODE_BATTLE_AARON;
        D_800B6328[obj->vars[11]].unk_06++;
    }

    obj->currentTask->flags |= 0x80;
}

void plyrsel_practice_cpu_update(Object *obj) {
    s16 playerId;
    Object *playerLabel;

    if (obj->vars[2]-- < 0) {
        obj->vars[2] = 15;
        obj->spriteId = obj->vars[1] - obj->spriteId;
    }

    playerId = obj->vars[0];
    playerLabel = gCharacterPortrait[playerId]->varObj[4];
    if (playerLabel->vars[7]) {
        obj->flags |= 0x10;
    }
}

void plyrsel_practice_user_update(Object *obj) {
    if (obj->vars[VAR_COUNTER]-- < 0) {
        obj->vars[VAR_COUNTER] = 15;
        obj->spriteId = obj->vars[VAR_SPRITE_ID_SUM] - obj->spriteId;
    }

    if (gPlayerInput[obj->vars[VAR_PLAYER_ID]].buttons & INP_START) {
        obj->spriteId = SPR_PRA_P2_CPU - 2 * obj->vars[0];
        obj->vars[VAR_SPRITE_ID_SUM] = obj->spriteId * 2 + 1;
        obj->pos.x = 245 - obj->vars[VAR_PLAYER_ID] * 167;

        obj->vars[VAR_PLAYER_ID] = 1 - obj->vars[VAR_PLAYER_ID];
        obj->currentTask->func = plyrsel_practice_cpu_update;
    }
}

void run_player_selection_mode(void) {
    Object *player_labels[2];
    Object *image_vs_obj;
    Object *obj;
    s16 player1;
    Object *tens_obj;
    UIElement portrait_p1 = { GROUP1_AARON, plyrsel_portrait_update, 0, 0x1000, "grpp1.sp2" };
    UIElement portrait_p2 = { GROUP2_AARON, plyrsel_portrait_update, 0, 0x1000, "grpp2.sp2" };
    UIElement label_player1 = { OPTIONS_PLAYER_1, plyrsel_player_label_update, 0, 0x1000, "options2.sp2" };
    UIElement label_player2 = { OPTIONS_PLAYER_2, plyrsel_player_label_update, 0, 0x1000, "options2.sp2" };
    UIElement image_vs = { 26, plyrsel_image_vs_update, 0, 0x1000, "bars.sp2" };
    UIElement counter_ones = { 0, func_8001E378, 0, 0x1000, "bars.sp2" };
    UIElement counter_tens = { 6, NULL, 0, 0x1000, "bars.sp2" };
    UIElement label_press_start = { OPTIONS_PRESS_START, plyrsel_practice_cpu_update, 0, 0x1000, "options2.sp2" };
    UIElement p1_user = { SPR_PRA_P1_USER, plyrsel_practice_user_update, 0, 0x1000, "practice.sp2" };
    UIElement p2_user = { SPR_PRA_P2_USER, plyrsel_practice_user_update, 0, 0x1000, "practice.sp2" };
    Vec4i portrait_p1_pos = { 84, 129, 0, 0 };
    Vec4i portrait_p2_pos = { 252, 129, 0, 0 };
    Vec4i label_player1_pos = { 56, 60, 0, 0 };
    Vec4i label_player2_pos = { 224, 60, 0, 0 };
    Vec4i image_vs_pos = { 162, 130, 0, 0 };
    Vec4i counter_ones_pos = { 171, 75, 0, 0 };
    Vec4i counter_tens_pos = { 158, 75, 0, 0 };
    Vec4i sp70 = { 82, 217, 0, 0 };
    Vec4i sp60 = { 251, 217, 0, 0 };
    Vec4i sp50 = { 78, 217, 0, 0 };
    Vec4i sp40 = { 245, 217, 0, 0 };
    s16 char_p1, char_p2;
    s32 unused;

    char_p1 = D_800B6328[PLAYER_1].characterId;
    char_p2 = D_800B6328[PLAYER_2].characterId;

    if (char_p1 == DEMITRON && D_80049DF4 == 0) {
        char_p1 = GORE;
    }
    if (char_p2 == DEMITRON && D_80049DF4 == 0) {
        char_p2 = GORE;
    }
    if (char_p1 == SONORK && D_80049DF0 == 0) {
        char_p1 = AARON;
    }
    if (char_p2 == SONORK && D_80049DF0 == 0) {
        char_p2 = AARON;
    }

    if (char_p1 >= CHARACTER_5) {
        char_p1--;
    }
    if (char_p2 >= CHARACTER_5) {
        char_p2--;
    }

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;

    asset_open_folder("/plyrsel/plyrsel", CONTEXT_EEFF);
    asset_open_folder("/plyrsel/music", CONTEXT_EEFF);

    D_8005BFC0 |= 0x800;

    switch (D_80080230) {
        case 10:
            obj = create_ui_element(&sp70, &label_press_start, CONTEXT_EEFF);
            obj->vars[0] = PLAYER_1;
            obj->vars[1] = 167;
            asset_open_folder("/plyrsel/select", CONTEXT_EEFF);
            break;
        case 11:
            obj = create_ui_element(&sp60, &label_press_start, CONTEXT_EEFF);
            obj->vars[0] = PLAYER_2;
            obj->vars[1] = 167;
            asset_open_folder("/plyrsel/select", CONTEXT_EEFF);
            break;
        case 20:
        case 30:
        case 50:
            obj = create_ui_element(&sp70, &label_press_start, CONTEXT_EEFF);
            obj->vars[0] = 0;
            obj->vars[1] = 167;
            obj = create_ui_element(&sp60, &label_press_start, CONTEXT_EEFF);
            obj->vars[0] = 1;
            obj->vars[1] = 167;
            asset_open_folder("/plyrsel/select2", CONTEXT_EEFF);
            break;
        case 40:
            if (gPracticingPlayer == PLAYER_1) {
                obj = create_ui_element(&sp50, &p1_user, CONTEXT_EEFF);
                obj->vars[VAR_PLAYER_ID] = PLAYER_1;
                obj->vars[VAR_SPRITE_ID_SUM] = SPR_PRA_P1_USER * 2 + 1;
            } else {
                obj = create_ui_element(&sp40, &p2_user, CONTEXT_EEFF);
                obj->vars[VAR_PLAYER_ID] = PLAYER_2;
                obj->vars[VAR_SPRITE_ID_SUM] = SPR_PRA_P2_USER * 2 + 1;
            }
            asset_open_folder("/plyrsel/select3", CONTEXT_EEFF);
            break;
    }

    load_background("select", 0, 8, 0, 0, 1, CONTEXT_EEFF);

    gCharacterPortrait[0] = create_ui_element(&portrait_p1_pos, &portrait_p1, CONTEXT_EEFF);
    gCharacterPortrait[0]->vars[0] = PLAYER_1;
    gCharacterPortrait[0]->spriteId = char_p1;
    gCharacterPortrait[0]->currentTask->counter = 20;

    gCharacterPortrait[1] = create_ui_element(&portrait_p2_pos, &portrait_p2, CONTEXT_EEFF);
    gCharacterPortrait[1]->vars[0] = PLAYER_2;
    gCharacterPortrait[1]->spriteId = char_p2;
    gCharacterPortrait[1]->currentTask->counter = 20;

    player_labels[0] = create_ui_element(&label_player1_pos, &label_player1, CONTEXT_EEFF);
    player_labels[0]->vars[0] = PLAYER_1;

    player_labels[1] = create_ui_element(&label_player2_pos, &label_player2, CONTEXT_EEFF);
    player_labels[1]->vars[0] = PLAYER_2;

    image_vs_obj = create_ui_element(&image_vs_pos, &image_vs, CONTEXT_EEFF);
    image_vs_obj->flags |= 4;
    image_vs_obj->vars[11] = -1;
    image_vs_obj->flags |= 0x4000000;

    tens_obj = create_ui_element(&counter_tens_pos, &counter_tens, CONTEXT_EEFF);
    obj = create_ui_element(&counter_ones_pos, &counter_ones, CONTEXT_EEFF);
    obj->vars[2] = 60;
    obj->varObj[1] = tens_obj;
    obj->varObj[5] = image_vs_obj;

    gCharacterPortrait[0]->varObj[4] = player_labels[0];
    gCharacterPortrait[0]->varObj[5] = image_vs_obj;
    gCharacterPortrait[1]->varObj[4] = player_labels[1];
    gCharacterPortrait[1]->varObj[5] = image_vs_obj;

    switch (D_80080230) {
        case 10:
        case 11:
            player1 = (D_80080230 == 11);
            gCharacterPortrait[1 - player1]->currentTask->func = plyrsel_portrait_update_2;
            gCharacterPortrait[1 - player1]->currentTask->counter = 0;
            gCharacterPortrait[1 - player1]->currentTask->flags = 1;

            if (D_800B6328[player1].unk_08 != 0) {
                gCharacterPortrait[1 - player1]->vars[6] = func_8001E188(1 - (u32) player1);
                gCharacterPortrait[player1]->currentTask->flags |= 0x80;
                player_labels[player1]->vars[7] = 20;
                image_vs_obj->vars[8] = 1;
                image_vs_obj->vars[9 + player1] = D_800B6328[player1].characterId;
            }
            break;
        case 30:
            gCharacterPortrait[0]->currentTask->func = plyrsel_portrait_update_2;
            gCharacterPortrait[0]->currentTask->counter = 0;
            gCharacterPortrait[0]->currentTask->flags = 1;
            gCharacterPortrait[0]->vars[6] = func_8001E188(0);

            gCharacterPortrait[1]->currentTask->func = plyrsel_portrait_update_2;
            gCharacterPortrait[1]->currentTask->counter = 0;
            gCharacterPortrait[1]->currentTask->flags = 1;
            gCharacterPortrait[1]->vars[6] = func_8001E188(1);
            break;
        case 20:
        case 40:
        case 50:
            break;
    }

    func_80001D88();
    func_8002630C(CONTEXT_EEFF);
}

void func_800201A4(s16 playerId, u16 arg1, u16 arg2) {
    D_80049DF0 = arg1;
    D_80049DF4 = arg2;
}

void func_800201C4(s16 charId, s16 playerId) {
    D_8005BFC0 |= 1;
    gGameMode = GAME_MODE_34;

    D_800B6328[playerId].characterId = charId;
    D_800B6328[playerId].unk_02 = 0;
    D_800B6328[playerId].unk_06 = 0;

    D_800B6328[1 - playerId].characterId = DEMITRON;
    D_800B6328[1 - playerId].unk_02 = 1;
    D_800B6328[1 - playerId].unk_06 = 1;

    func_800194E0(playerId + 10);
}

void cheat_character_ending(s16 playerId, u16 charId, u16 arg2) {
    func_800201C4(charId, playerId);
}

void func_80020298(s16 playerId, u16 arg1, u16 arg2) {
    func_800201C4(DEMITRON, playerId);
    gGameMode = GAME_MODE_30;
}

void func_800202D0(s16 playerId, u16 arg1, u16 arg2) {
    D_800B6328[0].unk_04 = D_800B6328[1].unk_04 = arg1;
}

void func_800202F0(s16 playerId, u16 arg1, u16 arg2) {
    s16 i;

    D_800B6328[1 - playerId].unk_06 = 1;
    D_800B6328[playerId].unk_06 = 0;
    D_800B6328[playerId].unk_02 = 0;
    D_800B6328[1 - playerId].unk_02 = 1;
    D_800801F1 = 1;

    for (i = 0; i < 11; i++) {
        D_800B6350[0][i] = D_800B6350[1][i] = 0;
    }

    D_8005BFC0 |= 1;
    func_800194E0(playerId + 10);
}

void func_800203A8(s16 playerId, u16 charId, u16 gameMode) {
    D_800B6328[1 - playerId].characterId = charId;
    D_800B6328[1 - playerId].unk_02 = 1;
    gGameMode = gameMode;
}

u16 cheat_code_play_as_sonork[] = { INP_L, INP_R, INP_CUP, INP_CDOWN, INP_CLEFT, INP_CRIGHT, CHEAT_END };
u16 cheat_code_play_as_sonork_or_demitron[] = { INP_A, INP_B, INP_R, INP_L, INP_CDOWN, INP_CUP, CHEAT_END };

u16 cheat_code_ending_aaron[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CLEFT, CHEAT_END };
u16 cheat_code_ending_demonica[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CUP, CHEAT_END };
u16 cheat_code_ending_eve[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CRIGHT, CHEAT_END };
u16 cheat_code_ending_gore[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CDOWN, CHEAT_END };
u16 cheat_code_ending_morphix[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_B, CHEAT_END };
u16 cheat_code_ending_niiki[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_A, CHEAT_END };
u16 cheat_code_ending_scarlet[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CLEFT, CHEAT_END };
u16 cheat_code_ending_sonork[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CUP, CHEAT_END };
u16 cheat_code_ending_zenmuron[] = {
    INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CRIGHT, CHEAT_END
};
u16 cheat_code_ending_demitron[] = {
    INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CDOWN, CHEAT_END
};

u16 D_8004A114[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_B, INP_B, INP_B, INP_CUP, CHEAT_END };

u16 D_8004A128[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_B, INP_B, INP_B, INP_B, CHEAT_END };
u16 D_8004A13C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CLEFT, CHEAT_END };
u16 D_8004A14C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CUP, CHEAT_END };
u16 D_8004A15C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CRIGHT, CHEAT_END };
u16 D_8004A16C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CDOWN, CHEAT_END };
u16 D_8004A17C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CLEFT, CHEAT_END };
u16 D_8004A18C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CUP, CHEAT_END };
u16 D_8004A19C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CRIGHT, CHEAT_END };
u16 D_8004A1AC[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CDOWN, CHEAT_END };

u16 D_8004A1BC[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_CLEFT, CHEAT_END };
u16 D_8004A1CC[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_CUP, CHEAT_END };
u16 D_8004A1E0[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_CRIGHT, CHEAT_END };
u16 D_8004A1F4[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_CDOWN, CHEAT_END };
u16 D_8004A208[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_A, CHEAT_END };
u16 D_8004A21C[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_CLEFT, CHEAT_END };
u16 D_8004A230[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_CUP, CHEAT_END };
u16 D_8004A244[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_CRIGHT, CHEAT_END };
u16 D_8004A258[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_B, INP_CDOWN, CHEAT_END };
u16 D_8004A270[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_B, INP_A, CHEAT_END };

CheatCode gCheatCodes[] = { { D_8004A114, func_80020298, 0, 0 },
                            { cheat_code_play_as_sonork, func_800201A4, 1, 0 },
                            { cheat_code_play_as_sonork_or_demitron, func_800201A4, 1, 1 },
                            { cheat_code_ending_aaron, cheat_character_ending, 0, 0 },
                            { cheat_code_ending_demonica, cheat_character_ending, 2, 0 },
                            { cheat_code_ending_eve, cheat_character_ending, 3, 0 },
                            { cheat_code_ending_gore, cheat_character_ending, 4, 0 },
                            { cheat_code_ending_morphix, cheat_character_ending, 6, 0 },
                            { cheat_code_ending_niiki, cheat_character_ending, 7, 0 },
                            { cheat_code_ending_scarlet, cheat_character_ending, 8, 0 },
                            { cheat_code_ending_sonork, cheat_character_ending, 9, 0 },
                            { cheat_code_ending_zenmuron, cheat_character_ending, 10, 0 },
                            { cheat_code_ending_demitron, cheat_character_ending, 1, 0 },
                            { D_8004A13C, func_800202D0, 0, 0 },
                            { D_8004A14C, func_800202D0, 1, 0 },
                            { D_8004A15C, func_800202D0, 2, 0 },
                            { D_8004A16C, func_800202D0, 3, 0 },
                            { D_8004A17C, func_800202D0, 4, 0 },
                            { D_8004A18C, func_800202D0, 5, 0 },
                            { D_8004A19C, func_800202D0, 6, 0 },
                            { D_8004A1AC, func_800202D0, 7, 0 },
                            { D_8004A1BC, func_800203A8, AARON, GAME_MODE_BATTLE_AARON },
                            { D_8004A1CC, func_800203A8, DEMITRON, GAME_MODE_BATTLE_DEMITRON },
                            { D_8004A1E0, func_800203A8, DEMONICA, GAME_MODE_BATTLE_DEMONICA },
                            { D_8004A1F4, func_800203A8, EVE, GAME_MODE_BATTLE_EVE },
                            { D_8004A208, func_800203A8, GORE, GAME_MODE_BATTLE_GORE },
                            { D_8004A21C, func_800203A8, MORPHIX, GAME_MODE_BATTLE_MORHIX },
                            { D_8004A230, func_800203A8, NIIKI, GAME_MODE_BATTLE_NIIKI },
                            { D_8004A244, func_800203A8, SCARLET, GAME_MODE_BATTLE_SCARLET },
                            { D_8004A258, func_800203A8, SONORK, GAME_MODE_BATTLE_SONORK },
                            { D_8004A270, func_800203A8, ZENMURON, GAME_MODE_BATTLE_ZENMURON },
                            { D_8004A128, func_800202F0, 0, 0 },
                            { NULL, NULL, 0, 0 } };

s16 cheat_common_length(u16 *seq1, u16 *seq2) {
    s16 length = 0;

    while (*seq1 == *seq2) {
        if (*seq2 == CHEAT_END || *seq1 == CHEAT_END) {
            break;
        }
        seq1++;
        seq2++;
        length++;
    }

    return length;
}

void func_80020438(CheatCodeState *state, s16 playerId) {
    CheatCode *cheat = state->cheat;

    state->numValid++;
    if (cheat->sequence[state->numValid] == CHEAT_END) {
        sound_play(2, 9);
        cheat->handler(playerId, cheat->param1, cheat->param2);
        state->cheat = NULL;
        state->numValid = 0;
    }
}

void func_800204C0(CheatCodeState *state, s16 playerId) {
    u16 raw_buttons;
    CheatCode *current_cheat;
    CheatCode *ptr;
    s32 unused;

    if (!gPlayerInput[playerId].unk_08) {
        return;
    }
    raw_buttons = gPlayerInput[playerId].raw_buttons;
    if (!raw_buttons) {
        return;
    }

    if (raw_buttons & (INP_UP | INP_DOWN | INP_LEFT | INP_RIGHT | INP_CRIGHT)) {
        if (state->current_buttons == raw_buttons) {
            gPlayerInput[playerId].unk_08 = FALSE;
            return;
        }
        state->current_buttons = raw_buttons;
    }

    gPlayerInput[playerId].unk_08 = FALSE;
    current_cheat = state->cheat;
    if (current_cheat != NULL) {
        if (raw_buttons == current_cheat->sequence[state->numValid]) {
            func_80020438(state, playerId);
            return;
        }

        for (ptr = current_cheat + 1; ptr->sequence != NULL; ptr++) {
            if (cheat_common_length(current_cheat->sequence, ptr->sequence) == state->numValid &&
                raw_buttons == ptr->sequence[state->numValid]) {
                state->cheat = ptr;
                func_80020438(state, playerId);
                return;
            }
        }
        gPlayerInput[playerId].unk_08 = TRUE;
        if (0) {} // required to match

        state->cheat = NULL;
        state->numValid = FALSE;
        state->current_buttons = 0;
        return;
    }

    for (current_cheat = gCheatCodes; current_cheat->sequence != NULL; current_cheat++) {
        if (current_cheat->sequence[0] == raw_buttons) {
            state->cheat = current_cheat;
            state->numValid = 1;
            return;
        }
    }
}

void func_80020670(Object *obj) {
    func_800204C0((CheatCodeState *) &obj->vars[0], PLAYER_1);
    func_800204C0((CheatCodeState *) &obj->vars[8], PLAYER_2);
}
