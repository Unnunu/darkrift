#include "common.h"

extern s16 D_80051F68;
extern s16 D_80080232;
extern u32 gTournamentOpponentId;

void func_800199E0(Object *);

s16 D_80049B70[8][2] = {
    { MORPHIX, NIIKI },  { NIIKI, SCARLET }, { SCARLET, ZENMURON }, { ZENMURON, AARON },
    { AARON, DEMONICA }, { DEMONICA, EVE },  { EVE, GORE },         { GORE, NIIKI },
};
s16 D_80049B90 = 0;

void func_800194E0(u16 arg0) {
    D_80080232 = gPlayMode;
    gPlayMode = arg0;
}

void func_80019500(Object *obj) {
    if (++obj->frameIndex >= obj->vars[4]) {
        obj->frameIndex = obj->vars[6] * 20;
        obj->currentTask->func = func_800199E0;
    }
}

void func_8001954C(Object *obj, s16 buttons, s16 playerId) {
    s16 i;
    s16 temp;
    s16 temp2;

    temp2 = obj->vars[1];
    temp = obj->vars[2];
    obj->vars[1] = buttons;
    obj->vars[2]--;
    obj->vars[7] = 0;

    if (temp <= 0 || buttons != temp2) {
        obj->vars[2] = 15;
        if (buttons & INP_START) {
            switch (obj->vars[6]) {
                case 0:
                    gNextGameMode = GAME_MODE_PLAYER_SELECTION;
                    gBattleSettings[playerId].isCpu = FALSE;
                    gBattleSettings[1 - playerId].isCpu = TRUE;
                    D_800801F1 = TRUE;
                    gTournamentOpponentId = 1 - playerId;
                    func_800194E0(PLAY_MODE_TOURNAMENT_P1 + playerId);
                    gBattleSettings[PLAYER_1].unk_08 = gBattleSettings[PLAYER_2].unk_08 = FALSE;
                    for (i = 0; i < NUM_CHARACTERS; i++) {
                        D_800B6350[PLAYER_1][i] = D_800B6350[PLAYER_2][i] = FALSE;
                    }
                    break;
                case 1:
                    gNextGameMode = GAME_MODE_PLAYER_SELECTION;
                    gBattleSettings[PLAYER_1].isCpu = gBattleSettings[PLAYER_2].isCpu = FALSE;
                    D_800801F1 = TRUE;
                    func_800194E0(PLAY_MODE_2_PLAYERS);
                    break;
                case 2:
                    gNextGameMode = GAME_MODE_OPTIONS;
                    break;
                case 3:
                    gBattleSettings[playerId].isCpu = FALSE;
                    gBattleSettings[1 - playerId].isCpu = FALSE;
                    gNextGameMode = GAME_MODE_PLAYER_SELECTION;
                    D_800801F1 = TRUE;
                    func_800194E0(PLAY_MODE_PRACTICE);
                    gPracticingPlayer = playerId;
                    break;
            }

            sound_play(2, 0);
            D_8005BFC0 |= GAME_FLAG_MODE_DONE;
            obj->currentTask->flags |= 0x80;
        } else if (buttons & INP_LEFT) {
            obj->vars[4] = obj->vars[6] * 20 + 20;
            obj->vars[6] = (obj->vars[6] + 3) % 4;
            if (!gPlayerInput[PLAYER_1].connected || !gPlayerInput[PLAYER_2].connected) {
                if (obj->vars[6] == 1) {
                    obj->vars[6] = (obj->vars[6] + 3) % 4;
                }
            }
            obj->currentTask->func = func_80019500;
            sound_play(2, 1);
        } else if (buttons & INP_RIGHT) {
            obj->vars[4] = obj->vars[6] * 20 + 20;
            obj->vars[6] = (obj->vars[6] + 1) % 4;
            if (!gPlayerInput[PLAYER_1].connected || !gPlayerInput[PLAYER_2].connected) {
                if (obj->vars[6] == 1) {
                    obj->vars[6] = (obj->vars[6] + 1) % 4;
                }
            }
            obj->currentTask->func = func_80019500;
            sound_play(2, 1);
        }
    }
}

void func_800198D0(void) {
    gPlayMode = PLAY_MODE_30;
    D_8005BFC0 |= GAME_FLAG_MODE_DONE;

    gBattleSettings[PLAYER_1].characterId = gBattleSettings[PLAYER_2].characterId = SONORK;
    gBattleSettings[PLAYER_1].unk_06 = TRUE;
    gBattleSettings[PLAYER_2].unk_06 = FALSE;
    gBattleSettings[PLAYER_1].isCpu = FALSE;
    gBattleSettings[PLAYER_2].isCpu = TRUE;

    gNextGameMode = GAME_MODE_29;
    D_80051F68++;
}

void func_80019940(void) {
    gPlayMode = PLAY_MODE_30;

    D_8005BFC0 |= GAME_FLAG_MODE_DONE;
    D_80049B90 &= 7;

    gBattleSettings[PLAYER_1].characterId = D_80049B70[D_80049B90][PLAYER_1];
    gBattleSettings[PLAYER_1].unk_06 = TRUE;
    gBattleSettings[PLAYER_2].unk_06 = FALSE;
    gBattleSettings[PLAYER_1].isCpu = FALSE;
    gBattleSettings[PLAYER_2].isCpu = TRUE;

    gBattleSettings[PLAYER_2].characterId = D_80049B70[D_80049B90][PLAYER_2];
    gNextGameMode = GAME_MODE_INTRO_AARON + gBattleSettings[PLAYER_1].characterId;

    D_80051F68 = D_80049B90++;
    gTournamentOpponentId = PLAYER_2;
}

void func_800199E0(Object *obj) {
    s16 buttons1, buttons2;

    buttons1 = gPlayerInput[PLAYER_1].buttons;
    buttons2 = gPlayerInput[PLAYER_2].buttons;

    if (obj->vars[3]-- <= 0) {
        obj->vars[3] = 4;
        obj->frameIndex = obj->vars[6] * 40 + 2 - obj->frameIndex;
    }

    if (buttons1 != 0) {
        func_8001954C(obj, buttons1, PLAYER_1);
    } else if (buttons2 != 0) {
        func_8001954C(obj, buttons2, PLAYER_2);
    } else {
        obj->vars[1] = 0;
    }

    if (++obj->vars[7] > 2400) {
        func_80019940();
    }
}

void func_80019A9C(Object *obj) {
    Model *assetData;
    Vec4i sp2C = { 160, 120, 0, 0 };
    Object *obj1;

    if (obj->vars[2]-- < 0) {
        obj->vars[2] = 15;
        obj->frameIndex = 0xA7 - obj->frameIndex;
    }

    if ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START)) {
        sound_play(2, 0);
        assetData = gAssets[asset_find("title.k2", 0x2000)].aux_data;
        obj1 = create_model_instance(&D_8004934C, 0x1000, func_800199E0, assetData);
        obj1->currentTask->counter = 30;
        obj1->frameIndex = 0;
        obj1->flags |= 0x01000000;
        obj->flags |= 0x10;
    }

    if (++obj->vars[7] > 900) {
        func_80019940();
    }
}

void func_80019BD0(Object *obj) {
    if (gPlayMode == PLAY_MODE_30 &&
        ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START))) {
        D_8005BFC0 |= GAME_FLAG_MODE_DONE;
        gNextGameMode = GAME_MODE_MAIN_MENU;
        obj->flags |= 0x10;
        obj->currentTask->flags |= 0x80;
    }
}

void func_80019C48(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] > 180) {
        D_8005BEFC = 0;
        D_8005BFC0 |= GAME_FLAG_MODE_DONE;
        gNextGameMode = GAME_MODE_32;
        obj->flags |= 0x10;
        obj->currentTask->flags |= 0x80;
    }
    func_80019BD0(obj);
}

Vtx D_80049BA8[2][4] = { { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { SCREEN_WIDTH << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { 0, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { SCREEN_WIDTH << 2, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } },
                         { { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { SCREEN_WIDTH << 2, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { 0, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
                           { { { SCREEN_WIDTH << 2, 180 << 2, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } } } };

void func_80019CC0(Object *obj) {
    if (D_8005BEFC - 8 < D_80080118) {
        obj->fn_render = func_80019C48;
    } else {
        D_8005BEFC -= 8;
    }

    func_80002178(D_8005BEFC, D_80049BA8[D_8005BFCE]);
}

void func_80019D2C(Object *obj) {
    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
    } else {
        mem_free(D_80049AE0);
        D_80049AE0 = NULL;
        load_background("kronos", 0, 60, 0, 180, 1, CONTEXT_2000);
        obj->fn_render = func_80019CC0;
    }

    func_80002178(D_8005BEFC, D_80049BA8[D_8005BFCE]);
}

void func_80019DE4(Object *obj) {
    obj->vars[0]++;
    if (obj->vars[0] > 180) {
        obj->vars[0] = 0;
        obj->fn_render = func_80019D2C;
    }
    func_80019BD0(obj);
}

s16 D_80049C28[] = { 14, 28, 40, 52, 64, 76, 88, 100, 0 };

void func_80019E28(Object *obj) {
    s16 i;

    for (i = 0; D_80049C28[i] != 0; i++) {
        if (obj->frameIndex == D_80049C28[i]) {
            sound_play(0x2000, 2);
        }
    }

    if (++obj->frameIndex >= obj->modInst->numAnimFrames - 4) {
        obj->flags |= 0x10;
        create_worker(func_8000A578, 0x1000);
        D_8005BEFC = 0;
        sound_play(0x2000, 3);
    }
}

void func_80019F08(Object *obj) {
    sound_play(0x2000, 8);
    obj->flags |= 0x10;
}

void func_80019F40(Object *obj) {
    Object *v1;
    Model *m;

    if (D_80081250 + D_80049AE8 + SCREEN_HEIGHT >= 0 &&
        ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START))) {
        D_80081254->flags |= 4;
        obj->fn_render = func_8000A578;

        v1 = obj->varObj[0];
        v1->flags |= 0x10;
        v1 = obj->varObj[1];
        v1->flags |= 0x10;

        sound_stop_one(0x2000, 8);
        sound_play(0x2000, 3);
        return;
    }

    if (++obj->vars[2] == 4) {
        obj->vars[2] = 0;
        if (D_80081250 + D_80049AE8 + SCREEN_HEIGHT >= 0) {
            D_80049AE8--;
            return;
        }

        v1 = obj->varObj[0];
        D_80081254->flags |= 4;
        if (v1->unk_088.a >= 6) {
            v1->unk_088.a -= 6;
            v1->pos.z -= 160;

            v1 = obj->varObj[1];
            v1->pos.z += 450;
        } else {
            v1->flags |= 0x10;
            obj->flags |= 0x10;

            v1 = obj->varObj[1];
            v1->flags |= 0x10;

            m = (Model *) gAssets[asset_find("titopen.k2", CONTEXT_2000)].aux_data;
            v1 = create_model_instance(&D_8004934C, 0x1000, func_80019E28, m);
            v1->flags |= 0x01002800;
            v1->unk_088.a = 128;
            obj->vars[2] = 3;
            sound_stop_one(0x2000, 8);
        }
    }
}

void func_8001A130(Object *obj) {
    if (++obj->frameIndex > 118) {
        obj->frameIndex = 0;
    }
}

void func_8001A158(Object *obj, s16 arg1) {
    Object *v0;
    Vec4i sp24 = { 0, -550, 0, 0 };
    Model *m;

    m = (Model *) gAssets[asset_find("haze.k2", arg1)].aux_data;
    v0 = create_model_instance(&D_8004934C, 0x1000, func_8001A130, m);
    v0->flags |= 0x01002800;
    v0->unk_088.a = 75;
    if (obj != NULL) {
        obj->varObj[0] = v0;
    }

    m = (Model *) gAssets[asset_find("haze1.k2", arg1)].aux_data;
    v0 = create_model_instance(&sp24, 0x1000, NULL, m);
    v0->flags |= 0x01002800;
    v0->unk_088.a = 75;
    if (obj != NULL) {
        obj->varObj[1] = v0;
    }
    func_800343F8(v0, FALSE);

    create_worker(func_80019F08, 0x1000);
}

void func_8001A294(Object *obj) {
    if (gPlayerInput[D_8013C24C].buttons & INP_START) {
        D_8005BFC0 |= GAME_FLAG_MODE_DONE;
        gNextGameMode = GAME_MODE_36;
        obj->flags |= 0x10;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A2F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A334.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A3EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A4FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A5D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A63C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A7DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main_menu/func_8001A98C.s")
