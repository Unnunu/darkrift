#include "common.h"
#include "camera.h"
#include "sprite_ids.h"
#include "task.h"

extern s16 D_80051F68;

extern s32 D_8008012C;
extern Object *gRankTable;
extern s16 D_80049B30[];

extern u8 gAudioMono;
extern s32 gMusicVolume;
extern s32 gSoundVolume;
extern u8 D_80080129;
extern s16 D_80081250;
extern BackgroundLayer *D_80081254;
extern s16 D_80080116;
extern s16 gPreviousGameMode;
extern s16 D_8013C224;
extern s16 D_8013C226;
extern s8 D_80081430;
extern s32 D_800AA480;
extern s16 gPreviousPlayMode;

extern u32 gTournamentOpponentId;
extern u16 D_8013C250;

void func_8001A674(Object *);
void func_8001A334(Object *);
void func_8002EA50(Object *, s32);
Object *create_model_instance(Vec4i *, s32, void (*)(Object *), Model *);
void func_800199E0(Object *);
void func_80020670(Object *);
void func_80019F40(Object *);
void func_8001A158(Object *, s16);
// s32 menu_rank_init(void);
void func_800052EC(s16 arg0);
void func_8001B5B0(char *, s32);
void func_80029630(void);
void func_8002DE20(Object *);
void task_default_func(Object *);
void rank_table_update(Object *);
void controls_controller_update(Object *);
void controls_button_update(Object *);
void controls_exit_update(Object *);
void options_update(Object *);
void options_difficulty_update(Object *);
void options_timer_update(Object *);
void options_rounds_update(Object *);
void options_audio_update(Object *);
void options_music_update(Object *);
void options_sfx_update(Object *);
void options_controls_update(Object *);
void options_rankings_update(Object *);
void options_stats_update(Object *);
void options_exit_update(Object *);
void func_80019A9C(Object *);
void func_8001A4FC(Object *);
void func_8001A98C(Object *);
void func_8001A7DC(Object *);

s32 D_800493F0[] = { 0, -783, -2453, 0 };

/* .bss */
u8 D_800801F0;
u8 D_800801F1;
s32 D_800801F4;
s32 D_800801F8;
s32 D_800801FC;
s32 D_80080200;
s32 D_80080204;
s32 D_80080208;
s32 D_8008020C;
s32 D_80080210;
s32 D_80080214;
s32 D_80080218;
s32 D_8008021C;
Vec4i *D_80080220;
Vec4i *D_80080224;
Object *D_80080228[2];

void func_80006AE0(void) {
    D_80081274 = gAssets[asset_find("comhit.k5", CONTEXT_ABAB)].aux_data;
    D_80081278 = gAssets[asset_find("comblock.k5", CONTEXT_ABAB)].aux_data;

    gPlayerInput[PLAYER_1].prev_buttons = gPlayerInput[PLAYER_2].prev_buttons = 0;
    if (gPlayMode == PLAY_MODE_PRACTICE) {
        gPlayerInput[1 - gPracticingPlayer].enabled = FALSE;
    } else {
        gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;
    }

    D_800801F0 = FALSE;
    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_100000;
    D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
    D_8013C250 = 0;
}

void func_80006C14(void) {
    gBattleSettings[PLAYER_1].roundsWon = gBattleSettings[PLAYER_2].roundsWon = 0;
    gPlayerInput[PLAYER_1].prev_buttons = gPlayerInput[PLAYER_2].prev_buttons = 0;

    if (gPlayMode == PLAY_MODE_PRACTICE) {
        gPlayerInput[1 - gPracticingPlayer].enabled = FALSE;
    } else {
        gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;
    }

    D_800801F0 = FALSE;
    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_100000;
    D_800801F1 = FALSE;
    D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
}

void func_80006CEC(void) {
    u8 i, j;

    D_800AA480 = 0;

    gBattleSettings[PLAYER_1].characterId = GORE;
    gBattleSettings[PLAYER_1].assetContext = TRUE;
    gBattleSettings[PLAYER_1].isCpu = FALSE;
    gBattleSettings[PLAYER_1].roundsWon = 0;
    gBattleSettings[PLAYER_2].characterId = AARON;
    gBattleSettings[PLAYER_2].assetContext = FALSE;
    gBattleSettings[PLAYER_2].isCpu = FALSE;
    gBattleSettings[PLAYER_2].roundsWon = 0;
    gBattleSettings[PLAYER_1].isDebug = FALSE;
    gBattleSettings[PLAYER_2].isDebug = FALSE;
    gBattleSettings[PLAYER_1].initialHp = 400;
    gBattleSettings[PLAYER_2].initialHp = 400;
    gBattleSettings[PLAYER_1].unk_0F = gBattleSettings[PLAYER_2].unk_0F = TRUE;
    gBattleSettings[PLAYER_1].isDummy = gBattleSettings[PLAYER_2].isDummy = 0;

    gPreviousPlayMode = gPlayMode = PLAY_MODE_2_PLAYERS;
    D_800801F1 = TRUE;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            D_800B6350[i][j] = 0;
        }
    }

    for (j = 0; j < 11; j++) {
        D_800B6368[j].wins = D_800B6368[j].loses = 0;
    }

    gBattleSettings[PLAYER_1].unk_04 = 7;
    gBattleSettings[PLAYER_2].unk_04 = 7;
    gPracticingPlayer = 0;
}

void func_80006E0C(Object *obj) {
    if (--obj->vars[0] < 0) {
        obj->flags |= OBJ_FLAG_DELETE;
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        TASK_END(obj->currentTask);
        osViBlack(0);
    }
}

void func_80006E6C(void) {
    Object *obj;
    BackgroundLayer *sp30;
    u16 sp2E;
    u16 sp2C;
    u16 sp2A;

    sp2E = D_80080110;
    sp2A = D_80080114;
    sp2C = D_80080112;

    D_80080110 = D_80080112 = D_80080114 = 0;
    gBgScrollY = 0;

    asset_open_folder("/title/wait", CONTEXT_6000);
    sp30 = bg_layer_create("wait", 0, 0, 0, 0, TEX_FLAG_1, 0x6000);
    gGlobalFlags |= GAME_FLAG_400 | GAME_FLAG_10;
    D_8008012C |= GFX_FLAG_20;

    obj = create_worker(&func_80006E0C, 0x1000);
    obj->vars[0] = 6;
    main_loop();

    D_80080110 = sp2E;
    D_80080112 = sp2C;
    D_80080114 = sp2A;
    gGlobalFlags &= ~(GAME_FLAG_400 | GAME_FLAG_10 | GAME_FLAG_MODE_DONE);
    D_8008012C &= ~GFX_FLAG_20;
    func_8002630C(0x6000);
    bg_layer_delete(sp30);
}

void func_80006FB4(void) {
    D_8013C224 = gFrameCounter % 5;
    D_8013C226 = 0;
    D_80081430 = 0;
    gBattleSettings[PLAYER_1].isDummy = gBattleSettings[PLAYER_2].isDummy = 0;

    if (gPreviousGameMode != GAME_MODE_PLAYER_SELECTION) {
        func_80006E6C();
    }

    if (gPlayMode != PLAY_MODE_PRACTICE) {
        asset_open_folder("/bars/bars", CONTEXT_ABAB);
    } else {
        asset_open_folder("/bars/bars2", CONTEXT_ABAB);
    }

    func_800052EC(0);
    func_800052EC(1);

    if (D_800801F1) {
        func_80006C14();
    } else {
        func_80006AE0();
    }
    osViBlack(1);
}

void func_800070C0(void) {
    func_8002630C(CONTEXT_ABAB);
    func_8002630C(0x5000);
    func_8002630C(0x5001);
}

void run_battle_gore_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg3", 0, 74, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, 15, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();

    func_800070C0();
}

void func_800071F0(Object *obj) {
    if (gPlayerInput[PLAYER_2].prev_buttons & INP_CLEFT) {
        obj->rotation.y -= 10;
    } else if (gPlayerInput[PLAYER_2].prev_buttons & INP_CRIGHT) {
        obj->rotation.y += 10;
    }
    func_80037E28(obj);
}

// unknown data
s32 D_80049400[] = { 0x40000, task_default_func, 0x2800, 0x10000000, 0, "tc", func_800071F0, 0x1000, 0 };

void run_battle_aaron_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    Vec4i sp1C = { 0, -500, 0, 0 };
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, 74, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, 15, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_demitron_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, -20, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, 8, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_demonica_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, 40, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, -24, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_eve_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, 52, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, 0, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_morphix_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, 96, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;
    bg_layer_create("bg0", 0, 8, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_niiki_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;

    func_80006FB4();
    bg_layer_create("bg2", 0, 94, 0x2000, 0x10000, 0, sp2C);
    bg_layer_create("bg0", 0, -8, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_scarlet_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, -7, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, -64, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_sonork_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, 20, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, -24, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void run_battle_zenmuron_mode(void) {
    s32 sp2C = gBattleSettings[PLAYER_2].assetContext;
    BackgroundLayer *bg;

    func_80006FB4();
    bg = bg_layer_create("bg2", 0, -6, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    bg_layer_create("bg0", 0, 4, 0x1000, 0x10000, TEX_FLAG_1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    main_loop();
    func_800070C0();
}

void func_80007B68(Object *obj) {
    s16 a3;

    a3 = 1 - gBattleSettings[PLAYER_2].isCpu; // @bug maybe
    D_80080118 = 100;

    if (gGlobalFlags & GAME_FLAG_100) {
        obj->vars[1]++;
        if (obj->vars[1] == 4) {
            obj->vars[1] = 0;
            if (D_80081250 + D_80081254->posY + 40) {
                D_80081254->posY--;
            } else {
                if (gPlayMode != PLAY_MODE_30) {
                    gBattleSettings[gTournamentOpponentId].assetContext = TRUE;
                    gBattleSettings[1 - gTournamentOpponentId].assetContext = FALSE;
                    gNextGameMode = gBattleSettings[gTournamentOpponentId].characterId + GAME_MODE_BATTLE_AARON;
                } else {
                    gNextGameMode = gBattleSettings[1 - gTournamentOpponentId].characterId + GAME_MODE_BATTLE_AARON;
                    gBattleSettings[PLAYER_1].isCpu = TRUE;
                }
                gGlobalFlags |= GAME_FLAG_80 | GAME_FLAG_MODE_DONE;
                obj->flags |= OBJ_FLAG_DELETE;
            }
        }

        gPlayerInput[a3].accumulated = TRUE;
        if ((gPlayerInput[a3].buttons & INP_START) ||
            gPlayMode == PLAY_MODE_30 && (gPlayerInput[1 - a3].buttons & INP_START)) {
            bg_layer_delete(D_80081254);
            if (gPlayMode != PLAY_MODE_30) {
                gNextGameMode = gBattleSettings[gTournamentOpponentId].characterId + GAME_MODE_BATTLE_AARON;
                gBattleSettings[gTournamentOpponentId].assetContext = TRUE;
                gBattleSettings[1 - gTournamentOpponentId].assetContext = FALSE;
            } else {
                gNextGameMode = GAME_MODE_MAIN_MENU;
            }
            gGlobalFlags |= GAME_FLAG_80 | GAME_FLAG_MODE_DONE;
            obj->flags |= OBJ_FLAG_DELETE;
            D_80081254->flags &= ~BG_FLAG_OVERLAY;
        }
    }
}

u16 D_80049434[] = { 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 298, 314, 330, 315, 316, 298, 331, 0 };

void func_80007DB0(Player *arg0, Object *arg1, s32 arg2) {
    s16 i;
    s16 a1;
    s16 v0;
    s16 s4;
    char *name = "intXX.mov";

    s4 = 0;
    for (i = 0; D_80049434[i] != 0; i++) {
        // modifying string stored in .rodata section isn't good practice
        name[3] = (i / 10) + '0';
        name[4] = (i % 10) + '0';

        if ((v0 = asset_find(name, arg2)) >= 0) {
            a1 = arg0->stateTable[D_80049434[i]].animationId;
            arg1->modInst->animations[a1] = gAssets[v0].data;
            s4++;
            arg0->stateTable[D_80049434[i]].unk_02 = func_80037394(arg1->modInst, a1);
        }
    }
}

void func_80007F4C(u8 arg0, s16 arg1, s32 arg2) {
    s32 s0;
    Object *obj;
    Object *a1;
    Object *v1;

    s0 = gBattleSettings[PLAYER_2].isCpu; // @bug maybe
    func_8002630C(CONTEXT_ABAB);
    gBattleSettings[s0].isDummy = 1;
    gBattleSettings[1 - s0].isDummy = 0;

    if (gPreviousGameMode != GAME_MODE_PLAYER_SELECTION && gCurrentGameMode != GAME_MODE_29) {
        func_80006E6C();
    }

    if (arg0) {
        obj = create_worker(func_80007B68, 0x1000);
        obj->vars[0] = 480;
    }

    func_800052EC(0);
    func_800052EC(1);

    gBattleSettings[PLAYER_1].unk_0F = gBattleSettings[PLAYER_2].unk_0F = TRUE;

    a1 = D_80080228[1 - s0];
    a1->pos.x = 0;
    a1->pos.z = 0;
    a1->rotation.y = 0x400;

    D_80080228[s0]->pos.x = -5000;
    D_80080228[s0]->pos.z = -5000;
    D_80080228[s0]->flags |= OBJ_FLAG_HIDDEN;

    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_400000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_400000;

    if (gBattleSettings[1 - s0].characterId != MORPHIX) {
        a1->flags |= OBJ_FLAG_10000000;
    }

    gGlobalFlags |= GAME_FLAG_4;

    gPlayerInput[PLAYER_1].prev_buttons = gPlayerInput[PLAYER_2].prev_buttons = 0;
    gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;

    D_800801F0 = FALSE;

    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_100000;

    TASK_END(gPlayers[PLAYER_1].unk_18);
    TASK_END(gPlayers[PLAYER_2].unk_18);

    func_80007DB0(gPlayers + 1 - s0, a1, arg2);
    func_8002DA08(gCamera);
    func_8000636C(gPlayers + 1 - s0, arg1, 1);
    D_8008012C |= GFX_FLAG_4;
}

void run_intro_gore_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/gore/goreint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("goreint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg3", 0, 74, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, 15, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();

    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_aaron_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/aaro/aaroint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("aaroint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, 74, 0x10000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, 15, 0x8000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();

    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_demitron_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/demi/demiint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("demiint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, -8, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, 8, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_demonica_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/demo/demoint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("demoint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, 32, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, -24, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_eve_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/eve/eveint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("eveint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, 52, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, 0, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_morphix_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/morp/morpint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("morpint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, 96, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, 8, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_niiki_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/niik/niikint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("niikint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, 94, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, -8, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_scarlet_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/scar/scarint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("scarint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, 0, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, -64, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_sonork_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/sono/sonoint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("sonoint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, 26, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, -24, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void run_intro_zenmuron_mode(void) {
    s32 temp_s0 = gBattleSettings[PLAYER_2].assetContext;

    asset_open_folder("/zenm/zenmint", CONTEXT_3000);
    func_80007F4C(TRUE, 0x70, 0x3000);
    D_80081254 = bg_layer_create("zenmint", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    D_80081250 = D_80081254->height;
    bg_layer_create("bg2", 0, -6, 0x2000, 0x10000, 0, temp_s0);
    bg_layer_create("bg0", 0, 4, 0x1000, 0x10000, TEX_FLAG_1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    main_loop();
    func_8002630C(0x3000);
    func_800070C0();
    if (gPlayMode != PLAY_MODE_30) {
        func_8002630C(temp_s0);
    }
}

void func_80008D0C(Object *obj) {
    if (gPlayers[PLAYER_1].currentState->unk_02 - 2 == gPlayers[PLAYER_1].obj->frameIndex) {
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        obj->flags |= OBJ_FLAG_DELETE;
        gNextGameMode = GAME_MODE_LOGO;
    }
}

void func_80008D64(Object *obj) {
    obj->frameIndex++;
    if (obj->frameIndex >= obj->modInst->numAnimFrames - 1) {
        obj->frameIndex = 0;
    }
}

void run_29_mode(void) {
    Object *obj;
    Object *relic;
    void *a3;
    Vec4i sp34 = { -200, 0, 0, 0 };
    BackgroundLayer *bg;

    gBattleSettings[PLAYER_1].characterId = SONORK;
    gBattleSettings[PLAYER_1].assetContext = TRUE;
    gBattleSettings[PLAYER_2].assetContext = FALSE;
    gBattleSettings[PLAYER_1].isCpu = FALSE;
    gBattleSettings[PLAYER_2].isCpu = TRUE;

    func_8002630C(0);
    gGlobalFlags |= GAME_FLAG_400 | GAME_FLAG_10;
    D_8008012C |= GFX_FLAG_20;

    asset_open_folder("/sono/prize", CONTEXT_3000);
    bg = bg_layer_create("prize", 0, 100, 0, 0, BG_FLAG_OVERLAY, 0x3000);
    obj = create_worker(func_80006E0C, 0x1000);
    obj->vars[0] = 6;
    main_loop();

    gGlobalFlags &= ~(GAME_FLAG_10 | GAME_FLAG_MODE_DONE);
    D_8008012C &= ~GFX_FLAG_20;
    asset_open_folder("/sono/sonoboss", CONTEXT_3000);
    func_80007F4C(FALSE, 346, 0x3000);
    bg_layer_create("bg2", 0, 26, 0x2000, 0x10000, 0, 0);
    bg_layer_create("bg0", 0, -24, 0x1000, 0x10000, TEX_FLAG_1, 0);
    func_8001B5B0("arena", 0);
    a3 = gAssets[asset_find("relic.k2", 0x3000)].aux_data;
    relic = create_model_instance(&sp34, 0x1000, func_80008D64, a3);
    relic->rotation.y = 0x400;
    relic->unk_088.a = 80;
    create_worker(func_80008D0C, 0x1000);
    bg_layer_delete(bg);
    main_loop();

    func_8002630C(0x3000);
    func_8002630C(0);
    func_8002630C(1);
    if (D_80051F68 == 0) {
        gNextGameMode = GAME_MODE_32;
    }
}

void run_30_mode(void) {
    Object *obj;
    Vec4i sp4C = { -800, -100, 0, 0 };
    Object *a1;
    s32 sp44;
    s16 sp42;
    void *a3;
    s32 padding;

    sp44 = gBattleSettings[PLAYER_2].assetContext;
    sp42 = gBattleSettings[PLAYER_2].isCpu;

    func_8002630C(CONTEXT_ABAB);
    asset_open_folder("/demi/demiboss", CONTEXT_3000);
    func_800052EC(0);
    func_800052EC(1);

    a1 = gPlayers[sp42].obj;
    a1->pos.x = a1->pos.z = 0;
    a1->rotation.y = 0x400;

    D_80080228[1 - sp42]->pos.x = -5000;
    D_80080228[1 - sp42]->pos.z = -5000;
    D_80080228[1 - sp42]->flags |= OBJ_FLAG_HIDDEN;

    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_400000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_400000;

    a1->flags |= OBJ_FLAG_10000000;
    gGlobalFlags |= GAME_FLAG_4;

    gPlayerInput[PLAYER_1].prev_buttons = gPlayerInput[PLAYER_2].prev_buttons = 0;
    gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;

    D_800801F0 = FALSE;

    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_100000;
    TASK_END(gPlayers[PLAYER_1].unk_18);
    TASK_END(gPlayers[PLAYER_2].unk_18);

    func_80007DB0(&gPlayers[sp42], a1, 0x3000);
    func_8002DA08(gCamera);
    func_8000636C(&gPlayers[sp42], 346, 1);
    D_8008012C |= GFX_FLAG_4;
    create_worker(func_8001A674, 0x1000);
    func_80006AE0();

    a3 = gAssets[asset_find("relic.k5", 0x3000)].aux_data;
    obj = create_model_instance(&sp4C, 0x1000, func_80008D64, a3);
    obj->rotation.y = 0x400;
    obj->unk_088.a = 80;

    bg_layer_create("bg2", 0, -32, 0x2000, 0x10000, 0, sp44);
    bg_layer_create("bg0", 0, 8, 0x1000, 0x10000, TEX_FLAG_1, sp44);
    func_8001B5B0("arena", sp44);
    D_800801F0 = TRUE;
    main_loop();
    func_8002630C(0x3000);
    gNextGameMode = GAME_MODE_BATTLE_DEMITRON;
}

void run_31_mode(void) {
    u16 var1;
    u16 sp54;
    Object *obj;
    char sp44[12];
    char sp38[12];

    var1 = 1 - gBattleSettings[PLAYER_2].isCpu;
    sp54 = gPlayers[var1].characterId;
    func_800263A8();
    asset_open_folder("/title/ending", CONTEXT_4000);

    str_copy(sp44, "/");
    str_concat(sp44, D_8004B844[sp54].unk_04->name);
    str_concat(sp44, "/");
    str_concat(sp44, D_8004B844[sp54].unk_04->name);
    str_concat(sp44, "end");
    asset_open_folder(sp44, CONTEXT_4000);

    obj = create_worker(func_8001A334, 0x1000);
    obj->vars[0] = 60;

    str_copy(sp38, D_8004B844[sp54].unk_04->name);
    str_concat(sp38, "end1");

    D_80081254 = bg_layer_create(sp38, 0, 40, 0, 0, TEX_FLAG_1, 0x4000);
    D_80081254 = bg_layer_create("passwd", 0, 205, 0, 0, TEX_FLAG_1, 0x4000);
    gGlobalFlags |= GAME_FLAG_4;
    D_8008012C |= GFX_FLAG_20;
    main_loop();
    func_8002630C(0x4000);
}

void run_36_mode(void) {
    Object *worker;

    func_800263A8();
    asset_open_folder("/title/credit", CONTEXT_4000);
    D_80081254 = bg_layer_create("credit", 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x4000);
    D_80081250 = D_80081254->height;
    worker = create_worker(func_8001A4FC, 0x1000);
    worker->vars[2] = 4;
    func_8001A158(worker, 0x4000);
    D_80080129 = FALSE;
    gGlobalFlags |= GAME_FLAG_4;
    D_8008012C |= GFX_FLAG_20;
    main_loop();
    func_8002630C(0x4000);
}

void func_80009554(Object *obj) {
    if (gPlayerInput[D_8013C24C].buttons & INP_START) {
        gGlobalFlags |= GAME_FLAG_MODE_DONE;
        obj->flags |= OBJ_FLAG_DELETE;
    }
}

void run_37_mode(void) {
    func_800263A8();
    asset_open_folder("/title/easywin", CONTEXT_4000);
    bg_layer_create("easyimg", 0, 0, 0, 0, TEX_FLAG_1, 0x4000);
    create_worker(func_80009554, 0x1000);
    D_80080129 = TRUE;
    gGlobalFlags |= GAME_FLAG_4;
    D_8008012C |= GFX_FLAG_20;
    main_loop();
    func_8002630C(0x4000);
    gNextGameMode = GAME_MODE_36;
}

void func_8000965C(s32 arg0) {
    D_80080136 = gGameModes[arg0].unk_14;
    D_80080138 = gGameModes[arg0].unk_16;
    D_80080130 = gGameModes[arg0].unk_10;
    D_80080132 = gGameModes[arg0].unk_11;
    D_80080134 = gGameModes[arg0].unk_12;
    D_80080110 = gGameModes[arg0].unk_0C;
    D_80080112 = gGameModes[arg0].unk_0D;
    D_80080114 = gGameModes[arg0].unk_0E;
}

void func_800096D0(u8 arg0) {
    Vec4i sp58[] = { { -1152, 0, 0, 0 }, { 0, 0, 0, 0 } };
    u32 nv;
    s32 s1;
    s16 charId;
    u16 t9;
    Object *s0;
    Object *a3;

    s1 = gBattleSettings[PLAYER_2].assetContext;
    t9 = 1 - s1;
    nv = s1;
    func_800052EC(0);
    func_800052EC(1);

    s0 = gPlayers[t9].obj;
    a3 = gPlayers[nv].obj;

    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_400000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_400000;

    s0->pos.x = sp58[1].x;
    s0->pos.y = sp58[1].y;
    s0->pos.z = sp58[1].z;
    a3->pos.x = sp58[0].x;
    a3->pos.y = sp58[0].y;
    a3->pos.z = sp58[0].z;

    if (!arg0) {
        if (gBattleSettings[t9].characterId == SONORK) {
            gPlayers[t9].obj->pos.x -= 400;
        } else if (gBattleSettings[t9].characterId == DEMONICA) {
            gPlayers[t9].obj->pos.x += 1200;
            if (gPlayers[nv].obj) {} // required to match
        }
    }

    s0->rotation.y = 0x400;

    charId = gBattleSettings[t9].characterId; // required to match
    if ((charId == SONORK || charId == DEMONICA) && !arg0) {
        a3->rotation.y = 0x400;
    } else {
        a3->rotation.y = 0xC00;
    }

    if (gBattleSettings[t9].characterId != MORPHIX) {
        s0->flags |= OBJ_FLAG_10000000;
    }
    a3->flags |= OBJ_FLAG_10000000;

    gGlobalFlags |= GAME_FLAG_4;
    gPlayerInput[PLAYER_1].prev_buttons = gPlayerInput[PLAYER_2].prev_buttons = 0;
    gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;
    D_800801F0 = FALSE;

    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_100000;
    TASK_END(gPlayers[PLAYER_1].unk_18);
    TASK_END(gPlayers[PLAYER_2].unk_18);

    func_8002DA08(gCamera);
    func_80007DB0(&gPlayers[nv], a3, 0x4000);
    func_80007DB0(&gPlayers[t9], s0, 0x4000);
    D_8008012C |= GFX_FLAG_4;
    bg_layer_create("bg2", 0, -27, 0x2000, 0x10000, 0, nv);
    bg_layer_create("bg0", nv * 0, 8, 0x1000, 0x10000, TEX_FLAG_1, nv);
    func_8000965C(GAME_MODE_BATTLE_DEMITRON);
    func_8001B5B0("arena", nv);
    D_800801F0 = TRUE;
}

void run_34_mode(void) {
    u16 sp7E;
    u16 sp24;
    char sp2C[80];

    sp7E = gBattleSettings[PLAYER_2].assetContext;
    sp24 = 1 - sp7E;
    gBattleSettings[PLAYER_1].isDummy = gBattleSettings[PLAYER_2].isDummy = 0;
    D_800801F0 = TRUE;
    D_80080234 = 1;

    switch (gBattleSettings[sp24].characterId) {
        case AARON:
            str_copy(sp2C, "/aaro/aarogend");
            break;
        case DEMITRON:
            str_copy(sp2C, "/demi/demigend");
            break;
        case DEMONICA:
            str_copy(sp2C, "/demo/demogend");
            break;
        case EVE:
            str_copy(sp2C, "/eve/evegend");
            break;
        case GORE:
            str_copy(sp2C, "/gore/goregend");
            break;
        case MORPHIX:
            str_copy(sp2C, "/morp/morpgend");
            break;
        case NIIKI:
            str_copy(sp2C, "/niik/niikgend");
            break;
        case SCARLET:
            str_copy(sp2C, "/scar/scargend");
            break;
        case SONORK:
            str_copy(sp2C, "/sono/sonogend");
            break;
        case ZENMURON:
            str_copy(sp2C, "/zenm/zenmgend");
            break;
    }

    asset_open_folder(sp2C, CONTEXT_4000);
    if (str_compare(sp2C, "/demi/demigend") != 0) {
        if (gBattleSettings[sp24].characterId != SONORK && gBattleSettings[sp24].characterId != DEMONICA) {
            asset_open_folder("/demi/demigend", CONTEXT_4000);
        }
    }

    switch (gBattleSettings[sp24].characterId) {
        case DEMONICA:
            asset_open_folder("/demi/demigen3", CONTEXT_4000);
            create_worker(func_8001A98C, 0x1000);
            break;
        case SONORK:
            asset_open_folder("/demi/demigen2", CONTEXT_4000);
            create_worker(func_8001A98C, 0x1000);
            break;
    }

    func_800096D0(FALSE);
    asset_open_folder("/demi/demidust", CONTEXT_ABAB);
    func_8000636C(&gPlayers[sp7E], 365, 1);
    func_8000636C(&gPlayers[sp24], 366, 1);
    create_worker(func_8001A7DC, 0x1000);
    main_loop();
    func_8002630C(0x4000);
    func_8002630C(CONTEXT_ABAB);
    gNextGameMode = GAME_MODE_35;
}

void func_80009CE0(void) {
    u16 sp56;
    u16 sp54;
    char sp48[12];
    char sp3C[12];
    Object *obj;

    sp56 = 1 - gBattleSettings[PLAYER_2].isCpu;
    sp54 = gPlayers[sp56].characterId;

    asset_open_folder("/title/ending", CONTEXT_4000);

    str_copy(sp48, "/");
    str_concat(sp48, D_8004B844[sp54].unk_04->name);
    str_concat(sp48, "/");
    str_concat(sp48, D_8004B844[sp54].unk_04->name);
    str_concat(sp48, "end");
    asset_open_folder(sp48, CONTEXT_4000);

    str_copy(sp3C, D_8004B844[sp54].unk_04->name);
    str_concat(sp3C, "end");
    D_80081254 = bg_layer_create(sp3C, 0, 250, 0, 0, BG_FLAG_OVERLAY, 0x4000);
    D_80081250 = D_80081254->height;

    obj = create_worker(func_8001A4FC, 0x1000);
    obj->vars[2] = 5;
    obj->vars[1] = 0;
    obj->vars[0] = 0;

    D_80080129 = FALSE;
    gGlobalFlags |= GAME_FLAG_4;
    func_8002EA50(gCamera, sp56);
}

void run_35_mode(void) {
    Object *obj;
    Model *a3;
    Vec4i spA0 = { -600, 0, -30, 0 };
    Vec4i sp90 = { -400, 0, 200, 0 };
    Vec4i sp80 = { -400, 0, 0, 0 };
    u16 sp7E;
    u16 sp24;
    Player *player1;
    Player *player2;
    char sp2C[72];

    sp7E = gBattleSettings[PLAYER_2].assetContext;
    sp24 = 1 - sp7E;

    player2 = &gPlayers[sp24];
    player1 = &gPlayers[sp7E];

    D_800801F0 = TRUE;
    D_80080234 = 1;
    gBattleSettings[sp7E].isDummy = gBattleSettings[sp24].isDummy = 0;

    switch (gBattleSettings[sp24].characterId) {
        case AARON:
            str_copy(sp2C, "/aaro/aaroclos");
            break;
        case DEMITRON:
            str_copy(sp2C, "/demi/demiclos");
            break;
        case DEMONICA:
            str_copy(sp2C, "/demo/democlos");
            break;
        case EVE:
            str_copy(sp2C, "/eve/eveclos");
            break;
        case GORE:
            str_copy(sp2C, "/gore/goreclos");
            break;
        case MORPHIX:
            str_copy(sp2C, "/morp/morpclos");
            break;
        case NIIKI:
            str_copy(sp2C, "/niik/niikclos");
            break;
        case SCARLET:
            str_copy(sp2C, "/scar/scarclos");
            break;
        case SONORK:
            str_copy(sp2C, "/sono/sonoclos");
            break;
        case ZENMURON:
            str_copy(sp2C, "/zenm/zenmclos");
            break;
    }
    asset_open_folder(sp2C, CONTEXT_4000);

    if (gBattleSettings[sp24].characterId == DEMONICA) {
        str_copy(sp2C, "/demi/demigen3");
    } else {
        str_copy(sp2C, "/demi/demigen2");
    }
    asset_open_folder(sp2C, CONTEXT_4000);

    func_800096D0(TRUE);
    func_8000636C(player1, 252, 1);
    func_8000636C(player2, 367, 1);
    player1->obj->flags |= OBJ_FLAG_HIDDEN;
    func_80009CE0();

    asset_open_folder("/demi/relic", CONTEXT_4000);
    a3 = gAssets[asset_find("relic.k5", 0x4000)].aux_data;
    obj = create_model_instance(&sp80, 0x1000, func_80008D64, a3);
    obj->unk_088.a = 80;

    if (gBattleSettings[sp24].characterId == SONORK || gBattleSettings[sp24].characterId == DEMONICA) {
        if (sp24 != 0) {
            a3 = gAssets[asset_find("dheadp2.k2", 0x4000)].aux_data;
        } else {
            a3 = gAssets[asset_find("dheadp1.k2", 0x4000)].aux_data;
        }
        obj = create_model_instance(&sp80, 0x1000, NULL, a3);
        obj->rotation.y = -1179;
        obj->unk_088.a = 255;
        obj->flags |= OBJ_FLAG_10000000;
    }

    main_loop();
    func_800263A8();
}

void func_8000A298(void) {
    s32 i;

    D_800801F1 = TRUE;
    gBattleSettings[PLAYER_1].consecutiveWins = gBattleSettings[PLAYER_2].consecutiveWins = 0;

    for (i = 0; i < 11; i++) {
        D_800B6350[PLAYER_2][i] = 0;
        D_800B6350[PLAYER_1][i] = 0;
    }

    gBattleSettings[PLAYER_1].unk_0F = gBattleSettings[PLAYER_2].unk_0F = TRUE;
    gPlayerInput[PLAYER_1].enabled = gPlayerInput[PLAYER_2].enabled = TRUE;
    gBattleSettings[PLAYER_1].initialHp = gBattleSettings[PLAYER_2].initialHp = 400;
    gBattleSettings[PLAYER_1].unk_04 = gBattleSettings[PLAYER_2].unk_04 = 0;
}

void run_main_menu_mode(void) {
    Object *menuEntrySelector;
    UIElement sp40 = { OPTIONS_PRESS_START, func_80019A9C, 0, 0x1000, "options2.sp2" };
    Vec4i sp30 = { 164, 155, 0, 0 };

    func_800263A8();
    gPlayerInput[PLAYER_1].disableStick = gPlayerInput[PLAYER_2].disableStick = TRUE;
    asset_open_folder("/title", CONTEXT_2000);
    bg_layer_create("dr_title", 0, 0, 0, 0, TEX_FLAG_1, CONTEXT_2000);
    D_8008012C |= GFX_FLAG_20;
    gGlobalFlags |= GAME_FLAG_4;

    if (gPreviousGameMode == GAME_MODE_MENU_OPTIONS) {
        Model *menuEntrySelectorModel = gAssets[asset_find("title.k2", CONTEXT_2000)].aux_data;
        menuEntrySelector = create_model_instance(&gZeroPosition, 0x1000, func_800199E0, menuEntrySelectorModel);
        menuEntrySelector->flags |= OBJ_FLAG_1000000;
    } else {
        menuEntrySelector = create_ui_element(&sp30, &sp40, CONTEXT_2000);
    }

    menuEntrySelector->currentTask->start_delay = 30;

    create_worker(func_80020670, 0x1000);
    func_8000A298();
    main_loop();

    func_8002630C(0x2000);
    if (gNextGameMode != GAME_MODE_PLAYER_SELECTION) {
        func_8002630C(CONTEXT_EEFF);
    }
}

void func_8000A514(Object *obj) {
    func_80002178(D_8005BEFC, 0);

    if (D_8005BEFC - 2 > 0) {
        D_8005BEFC -= 2;
        return;
    }

    obj->flags |= OBJ_FLAG_DELETE;
    D_80080116 = 0;
}

void func_8000A578(Object *obj) {
    UIElement sp44 = { 83, func_80019A9C, 0, 0x1000, "options2.sp2" };
    Vec4i sp34 = { 160, 155, 0, 0 };
    Object *v0;

    D_80080116 = 200;
    func_80002178(D_8005BEFC, NULL);

    if (D_8005BEFC + 32 < 255) {
        D_8005BEFC += 32;
        return;
    }

    sound_stop_one(0x2000, 8);
    obj->fn_render = func_8000A514;
    bg_layer_create("dr_title", 0, 0, 0, 0, TEX_FLAG_1, CONTEXT_2000);
    v0 = create_ui_element(&sp34, &sp44, 0x2000);
    v0->currentTask->start_delay = 60;
    gCamera->pos.z = -2200;
    create_worker(func_80020670, 0x1000);
}

void run_intro_mode(void) {
    s32 unused;
    Object *v0;
    UIElement sp3C = { 83, func_80019A9C, 0, 0x1000, "options2.sp2" };
    Vec4i sp2C = { 160, 155, 0, 0 };

    D_80080129 = FALSE;
    D_8008012C |= GFX_FLAG_20;
    gGlobalFlags |= GAME_FLAG_4;
    asset_open_folder("/title/tit_int", CONTEXT_2000);
    asset_open_folder("/plyrsel/plyrsel", CONTEXT_EEFF);
    v0 = create_worker(func_80019F40, 0x1000);
    gPlayerInput[PLAYER_1].disableStick = gPlayerInput[PLAYER_2].disableStick = TRUE;
    func_8001A158(v0, 0x2000);

    D_80081254 = bg_layer_create("oplog", 0, 250, 0, 0x10000, BG_FLAG_OVERLAY, CONTEXT_2000);
    D_80081250 = D_80081254->height;

    func_8000A298();
    main_loop();
    func_8002630C(0x2000);
    if (gNextGameMode != GAME_MODE_PLAYER_SELECTION) {
        func_8002630C(CONTEXT_EEFF);
    }
}

void func_8000A828(void) {
    asset_open_folder("/title/error", CONTEXT_2000);
    bg_layer_create("messpg", 0, 90, 0, 180, TEX_FLAG_1, CONTEXT_2000);
    main_loop();
}

void run_logo_mode(void) {
    func_800263A8();
    gGlobalFlags |= GAME_FLAG_4;
    D_8008012C |= GFX_FLAG_20;
    D_8008012C |= GFX_FLAG_40;
    if (!gPlayerInput[PLAYER_1].connected && !gPlayerInput[PLAYER_2].connected) {
        func_8000A828();
    }

    asset_open_folder("/title/logo", CONTEXT_2000);
    bg_layer_create("vic", 0, 30, 0, 180, TEX_FLAG_1, CONTEXT_2000);
    bg_layer_create("n64lic", 0, 190, 0, 240, TEX_FLAG_1, CONTEXT_2000);
    create_worker(func_80019DE4, 0x1000);
    main_loop();
    func_8002630C(0x2000);
}

void run_options_mode(void) {
    Object *controller;
    Object *obj;
    UIElement ui_labels = { OPTIONS_OPTIONS_TEXT, options_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_difficulty = { OPTIONS_NORMAL_HL, options_difficulty_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_timer = { OPTIONS_90, options_timer_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_rounds = { OPTIONS_3, options_rounds_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_audio = { OPTIONS_STEREO, options_audio_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_music_volume = { OPTIONS_9, options_music_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_sfx_volume = { OPTIONS_9, options_sfx_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_controls = { OPTIONS_CONTROLS_HL, options_controls_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_rankings = { OPTIONS_RANKINGS_HL, options_rankings_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_stats = { OPTIONS_STATS_HL, options_stats_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement ui_exit = { OPTIONS_EXIT_HL, options_exit_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    Vec4i ui_labels_pos = { 130, 130, 0, 0 };
    Vec4i ui_difficulty_pos = { 181, 74, 0, 0 };
    Vec4i ui_timer_pos = { 181, 91, 0, 0 };
    Vec4i ui_rounds_pos = { 181, 105, 0, 0 };
    Vec4i ui_audio_pos = { 181, 121, 0, 0 };
    Vec4i ui_music_volume_pos = { 181, 136, 0, 0 };
    Vec4i ui_sfx_volume_pos = { 181, 151, 0, 0 };
    Vec4i ui_controls_pos = { 118, 166, 0, 0 };
    Vec4i ui_rankings_pos = { 117, 181, 0, 0 };
    Vec4i ui_stats_pos = { 135, 198, 0, 0 };
    Vec4i ui_exit_pos = { 146, 228, 0, 0 };

    gPlayerInput[PLAYER_1].disableStick = gPlayerInput[PLAYER_2].disableStick = TRUE;
    asset_open_folder("/title/option", CONTEXT_2000);
    bg_layer_create("bgopt", 0, 0, 0, 0, TEX_FLAG_1, CONTEXT_2000);
    D_8008012C |= GFX_FLAG_20;
    gGlobalFlags |= GAME_FLAG_4;

    controller = create_ui_element(&ui_labels_pos, &ui_labels, CONTEXT_2000);

    obj = create_ui_element(&ui_difficulty_pos, &ui_difficulty, CONTEXT_2000);
    obj->frameIndex = gDifficulty + OPTIONS_EASY_HL;
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_timer_pos, &ui_timer, CONTEXT_2000);
    obj->frameIndex = gBattleDuration + OPTIONS_00;
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_rounds_pos, &ui_rounds, CONTEXT_2000);
    obj->frameIndex = gMaxRounds + OPTIONS_0;
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_audio_pos, &ui_audio, CONTEXT_2000);
    obj->frameIndex = gAudioMono + OPTIONS_STEREO;
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_music_volume_pos, &ui_music_volume, CONTEXT_2000);
    obj->frameIndex = gMusicVolume / (0x8000 / 9) + OPTIONS_0;
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_sfx_volume_pos, &ui_sfx_volume, CONTEXT_2000);
    obj->frameIndex = gSoundVolume / (0x8000 / 9) + OPTIONS_0;
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_controls_pos, &ui_controls, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_rankings_pos, &ui_rankings, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_stats_pos, &ui_stats, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    obj = create_ui_element(&ui_exit_pos, &ui_exit, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller;

    main_loop();
    func_8002630C(CONTEXT_2000);
}

void func_8000AFA4(Object *obj, s16 playerId) {
    s16 i;
    s16 button;

    button = D_80049B30[obj->vars[VAR_OPT_CTRL_ROW]];
    for (i = 0; i < 8; i++) {
        if (gButtonsMap[playerId][i] == button) {
            break;
        }
    }

    switch (i) {
        case 0:
            obj->frameIndex = OPTIONS_BUTTON_L;
            break;
        case 1:
            obj->frameIndex = OPTIONS_BUTTON_A;
            break;
        case 2:
            obj->frameIndex = OPTIONS_BUTTON_R;
            break;
        case 3:
            obj->frameIndex = OPTIONS_BUTTON_B;
            break;
        case 4:
            obj->frameIndex = OPTIONS_BUTTON_C_UP;
            break;
        case 5:
            obj->frameIndex = OPTIONS_BUTTON_C_RIGHT;
            break;
        case 6:
            obj->frameIndex = OPTIONS_BUTTON_C_DOWN;
            break;
        case 7:
            obj->frameIndex = OPTIONS_BUTTON_C_LEFT;
            break;
    }
}

void run_menu_control_mode(void) {
    Object *controller_p1;
    Object *controller_p2;
    Object *obj;
    UIElement labels = { OPTIONS_CONTROLS_TEXT, NULL, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_c_up = { OPTIONS_BUTTON_C_UP_HL, controls_controller_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_c_left = { OPTIONS_BUTTON_C_LEFT, controls_button_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_c_down = { OPTIONS_BUTTON_C_DOWN, controls_button_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_c_right = { OPTIONS_BUTTON_C_RIGHT, controls_button_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_b = { OPTIONS_BUTTON_B, controls_button_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_l = { OPTIONS_BUTTON_L, controls_button_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_r = { OPTIONS_BUTTON_R, controls_button_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement button_a = { OPTIONS_BUTTON_A, controls_button_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    UIElement exit_menu = { OPTIONS_EXIT_HL, controls_exit_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    Vec4i labels_pos = { 133, 126, 0, 0 };
    Vec4i button_c_up_p1_pos = { 40, 82, 0, 0 };
    Vec4i button_c_up_p2_pos = { 179, 82, 0, 0 };
    Vec4i button_c_left_p1_pos = { 40, 96, 0, 0 };
    Vec4i button_c_left_p2_pos = { 179, 96, 0, 0 };
    Vec4i button_c_down_p1_pos = { 40, 110, 0, 0 };
    Vec4i button_c_down_p2_pos = { 179, 110, 0, 0 };
    Vec4i button_c_right_p1_pos = { 40, 124, 0, 0 };
    Vec4i button_c_right_p2_pos = { 179, 124, 0, 0 };
    Vec4i button_b_p1_pos = { 40, 138, 0, 0 };
    Vec4i button_b_p2_pos = { 179, 138, 0, 0 };
    Vec4i button_l_p1_pos = { 40, 152, 0, 0 };
    Vec4i button_l_p2_pos = { 179, 152, 0, 0 };
    Vec4i button_r_p1_pos = { 40, 166, 0, 0 };
    Vec4i button_r_p2_pos = { 179, 166, 0, 0 };
    Vec4i button_a_p1_pos = { 40, 180, 0, 0 };
    Vec4i button_a_p2_pos = { 179, 180, 0, 0 };
    Vec4i exit_menu_pos = { 149, 224, 0, 0 };

    gPlayerInput[PLAYER_1].disableStick = gPlayerInput[PLAYER_2].disableStick = TRUE;
    asset_open_folder("/title/control", CONTEXT_2000);
    bg_layer_create("bgcont", 0, 0, 0, 0, TEX_FLAG_1, CONTEXT_2000);
    D_8008012C |= GFX_FLAG_20;
    gGlobalFlags |= GAME_FLAG_4;

    create_ui_element(&labels_pos, &labels, CONTEXT_2000);

    controller_p1 = create_ui_element(&button_c_up_p1_pos, &button_c_up, CONTEXT_2000);
    controller_p1->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    controller_p1->vars[VAR_OPT_CTRL_ROW] = 0;
    func_8000AFA4(controller_p1, 0);

    obj = create_ui_element(&button_c_left_p1_pos, &button_c_left, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    obj->vars[VAR_OPT_CTRL_ROW] = 1;
    func_8000AFA4(obj, 0);

    obj = create_ui_element(&button_c_down_p1_pos, &button_c_down, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    obj->vars[VAR_OPT_CTRL_ROW] = 2;
    func_8000AFA4(obj, 0);

    obj = create_ui_element(&button_c_right_p1_pos, &button_c_right, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    obj->vars[VAR_OPT_CTRL_ROW] = 3;
    func_8000AFA4(obj, 0);

    obj = create_ui_element(&button_b_p1_pos, &button_b, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    obj->vars[VAR_OPT_CTRL_ROW] = 4;
    func_8000AFA4(obj, 0);

    obj = create_ui_element(&button_l_p1_pos, &button_l, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    obj->vars[VAR_OPT_CTRL_ROW] = 5;
    func_8000AFA4(obj, 0);

    obj = create_ui_element(&button_r_p1_pos, &button_r, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    obj->vars[VAR_OPT_CTRL_ROW] = 6;
    func_8000AFA4(obj, 0);

    obj = create_ui_element(&button_a_p1_pos, &button_a, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p1;
    obj->vars[VAR_OPT_CTRL_ROW] = 7;
    func_8000AFA4(obj, 0);

    controller_p2 = create_ui_element(&button_c_up_p2_pos, &button_c_up, CONTEXT_2000);
    controller_p2->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    controller_p2->vars[VAR_OPT_CTRL_ROW] = 0;
    controller_p2->vars[VAR_OPT_CTRL_PLAYER_ID] = PLAYER_2;
    func_8000AFA4(controller_p2, 1);

    obj = create_ui_element(&button_c_left_p2_pos, &button_c_left, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    obj->vars[VAR_OPT_CTRL_ROW] = 1;
    func_8000AFA4(obj, 1);

    obj = create_ui_element(&button_c_down_p2_pos, &button_c_down, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    obj->vars[VAR_OPT_CTRL_ROW] = 2;
    func_8000AFA4(obj, 1);

    obj = create_ui_element(&button_c_right_p2_pos, &button_c_right, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    obj->vars[VAR_OPT_CTRL_ROW] = 3;
    func_8000AFA4(obj, 1);

    obj = create_ui_element(&button_b_p2_pos, &button_b, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    obj->vars[VAR_OPT_CTRL_ROW] = 4;
    func_8000AFA4(obj, 1);

    obj = create_ui_element(&button_l_p2_pos, &button_l, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    obj->vars[VAR_OPT_CTRL_ROW] = 5;
    func_8000AFA4(obj, 1);

    obj = create_ui_element(&button_r_p2_pos, &button_r, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    obj->vars[VAR_OPT_CTRL_ROW] = 6;
    func_8000AFA4(obj, 1);

    obj = create_ui_element(&button_a_p2_pos, &button_a, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_CONTROLLER] = controller_p2;
    obj->vars[VAR_OPT_CTRL_ROW] = 7;
    func_8000AFA4(obj, 1);

    obj = create_ui_element(&exit_menu_pos, &exit_menu, CONTEXT_2000);
    obj->vars[VAR_OPT_CTRL_EXIT_0] = controller_p1;
    obj->vars[VAR_OPT_CTRL_EXIT_1] = controller_p2;

    main_loop();
    func_8002630C(CONTEXT_2000);
}

void run_menu_rank_mode(void) {
    UIElement rankTable = { OPTIONS_RANK_TABLE_TEMPLATE, rank_table_update, 0, OBJ_PRIO_DEFAULT, "options2.sp2" };
    Vec4i rankTablePos = { 133, 126, 0, 0 };

    gPlayerInput[PLAYER_1].disableStick = gPlayerInput[PLAYER_2].disableStick = TRUE;
    asset_open_folder("/title/rank", CONTEXT_2000);
    bg_layer_create("bgrank", 0, 4, 0, 0, TEX_FLAG_1, CONTEXT_2000);
    gRankTable = create_ui_element(&rankTablePos, &rankTable, CONTEXT_2000);
    menu_rank_init();
    D_8008012C |= GFX_FLAG_20;
    gGlobalFlags |= GAME_FLAG_4;
    main_loop();
    func_8002630C(CONTEXT_2000);
}

void run_menu_stats_mode(void) {
    func_8002630C(0);
    func_8002630C(1);
    func_8002630C(CONTEXT_ABAB);

    gPlayerInput[PLAYER_1].disableStick = gPlayerInput[PLAYER_2].disableStick = TRUE;
    asset_open_folder("/title/stats", CONTEXT_2000);
    bg_layer_create("aarost", 0, 13, 0, 0, TEX_FLAG_1, CONTEXT_2000);
    D_8008012C |= GFX_FLAG_20;
    gGlobalFlags |= GAME_FLAG_4;
    create_worker(stats_update, OBJ_PRIO_DEFAULT);
    main_loop();
    func_8002630C(CONTEXT_2000);
}

static void nullsub(void) {
}

void run_17_mode(void) {
    s32 unused;
    Vec4s sp74 = { 0, -400, 0, 0 };
    Vec4i sp64 = { -400, 0, 0, 0 };
    Vec4i sp54 = { 400, 0, 0, 0 };
    s32 unused2;
    s32 sp4C = gBattleSettings[PLAYER_2].assetContext;
    K2Def sp3C = { "gore", task_default_func, 0, 0x1000, 0 };
    K2Def sp2C = { "arena", task_default_func, 0, 0x1000, 0 };

    asset_open_folder("/bars", CONTEXT_ABAB);
    func_800052EC(0);
    func_800052EC(1);
    bg_layer_create("bg2", 0, 74, 0x2000, 0x10000, 0, sp4C);
    bg_layer_create("bg0", 0, 15, 0x1000, 0x10000, TEX_FLAG_1, sp4C);
    func_8001B5B0("arena", sp4C);
    func_80029630();

    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    main_loop();
}
