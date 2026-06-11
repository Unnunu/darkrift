#include "common.h"
#include "camera.h"
#include "sprite_ids.h"
#include "task.h"

extern s16 sRoundWinCount;

extern s32 gGfxFlags;
extern Object *sScoreTitleObj;
extern s16 sCharButtonTbl[];

extern u8 sAudioMuted;
extern s32 sMusicVolumeSetting;
extern s32 gSfxVolumeSetting;
extern u8 sClearZbuffer;
extern s16 D_80081250;
extern x_4a7d6dd4 *D_80081254;
extern s16 sOverlayBrightness;
extern s16 sPrevScreenId;
extern s16 sWadUnk1;
extern s16 sWadUnk2;
extern s8 D_80081430;
extern s32 D_800AA480;
extern s16 x_1acf99bf;

extern u32 x_6db66fc3;
extern u16 sHudActive;

void present_intro_presents(Object *);
void present_theend_init(Object *);
void cam_ko_init(Object *, s32);
Object *obj_create_with_model_ptr(x_88f11482 *, s32, void (*)(Object *), Model *);
void present_title_task(Object *);
void x_8daf2444(Object *);
void present_title_open(Object *);
void present_haze_init(Object *, s16);
// s32 menu_rank_init(void);
void player_init(s16 x_cc1d0de5);
void ground_load(char *, s32);
void hud_setup(void);
void cam_intro_start(Object *);
void task_remove_current(Object *);
void select_score_display(Object *);
void select_char_task(Object *);
void select_char_update(Object *);
void select_stage_task(Object *);
void options_menu_task(Object *);
void option_game_mode(Object *);
void option_round_count(Object *);
void option_rounds_win(Object *);
void option_sound_mute(Object *);
void option_bgm_volume(Object *);
void option_sfx_volume(Object *);
void option_controller_setup(Object *);
void option_char_config(Object *);
void option_stage_select(Object *);
void option_back_attract(Object *);
void present_attract_loop(Object *);
void present_win_result_loop(Object *);
void present_demo_sfx(Object *);
void present_demo_action(Object *);

s32 D_800493F0[] = { 0, -783, -2453, 0 };

/* .bss */
u8 sFightLocked;
u8 sFirstFight;
s32 D_800801F4;
s32 D_800801F8;
s32 D_800801FC;
s32 D_80080200;
s32 D_80080204;
s32 D_80080208;
s32 sMenuState;
s32 gFighterDistance;
s32 D_80080214;
s32 D_80080218;
s32 D_8008021C;
x_88f11482 *sCharSelectSpriteA;
x_88f11482 *sCharSelectSpriteB;
Object *sIntroPlayerObjs[2];

void fight_init(void) {
    sHitModelRegular = sWadEntries[wad_entry_find("comhit.k5", x_2587f84f)].x_4962fc73;
    sHitModelGrab = sWadEntries[wad_entry_find("comblock.k5", x_2587f84f)].x_4962fc73;

    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    if (x_5e4e2788 == x_79c2dc5b) {
        x_59ce598c[1 - x_08051143].enabled = FALSE;
    } else {
        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    }

    sFightLocked = FALSE;
    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    sHealthBarSlideL = sHealthBarSlideR = sHealthFlashL = sHealthFlashR = 0;
    sHudActive = 0;
}

void fight_reset(void) {
    gWadCondLoad[x_83106b21].x_b2b764b3 = gWadCondLoad[x_6f0b3be3].x_b2b764b3 = 0;
    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;

    if (x_5e4e2788 == x_79c2dc5b) {
        x_59ce598c[1 - x_08051143].enabled = FALSE;
    } else {
        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    }

    sFightLocked = FALSE;
    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    sFirstFight = FALSE;
    sHealthBarSlideL = sHealthBarSlideR = sHealthFlashL = sHealthFlashR = 0;
}

void game_init(void) {
    u8 i, j;

    D_800AA480 = 0;

    gWadCondLoad[x_83106b21].x_eb1fe45b = x_537ef8a7;
    gWadCondLoad[x_83106b21].x_fb21ca8c = TRUE;
    gWadCondLoad[x_83106b21].x_03604d94 = FALSE;
    gWadCondLoad[x_83106b21].x_b2b764b3 = 0;
    gWadCondLoad[x_6f0b3be3].x_eb1fe45b = x_c4ddde6d;
    gWadCondLoad[x_6f0b3be3].x_fb21ca8c = FALSE;
    gWadCondLoad[x_6f0b3be3].x_03604d94 = FALSE;
    gWadCondLoad[x_6f0b3be3].x_b2b764b3 = 0;
    gWadCondLoad[x_83106b21].x_6128220f = FALSE;
    gWadCondLoad[x_6f0b3be3].x_6128220f = FALSE;
    gWadCondLoad[x_83106b21].x_c35c64af = 400;
    gWadCondLoad[x_6f0b3be3].x_c35c64af = 400;
    gWadCondLoad[x_83106b21].x_8a8d66c9 = gWadCondLoad[x_6f0b3be3].x_8a8d66c9 = TRUE;
    gWadCondLoad[x_83106b21].x_178eafa6 = gWadCondLoad[x_6f0b3be3].x_178eafa6 = 0;

    x_1acf99bf = x_5e4e2788 = x_96f25e0a;
    sFirstFight = TRUE;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            D_800B6350[i][j] = 0;
        }
    }

    for (j = 0; j < 11; j++) {
        D_800B6368[j].x_a962826d = D_800B6368[j].x_3f3ac621 = 0;
    }

    gWadCondLoad[x_83106b21].x_cc57155e = 7;
    gWadCondLoad[x_6f0b3be3].x_cc57155e = 7;
    x_08051143 = 0;
}

void fade_to_black_cb(Object *obj) {
    if (--obj->x_0f4167b4[0] < 0) {
        obj->flags |= x_f51cb721;
        x_e30d50d2 |= x_bee364e0;
        TASK_END(obj->currentTask);
        osViBlack(0);
    }
}

void load_wait_screen(void) {
    Object *obj;
    x_4a7d6dd4 *x_c9614940;
    u16 x_18643961;
    u16 x_32f1d6e2;
    u16 x_1c32c793;

    x_18643961 = sClearColorR;
    x_1c32c793 = sClearColorB;
    x_32f1d6e2 = sClearColorG;

    sClearColorR = sClearColorG = sClearColorB = 0;
    x_6c647b3a = 0;

    wad_load_path("/title/wait", x_30af3448);
    x_c9614940 = x_a0e73601("wait", 0, 0, 0, 0, x_96186256, 0x6000);
    x_e30d50d2 |= x_23ebd6b0 | x_d4c59644;
    gGfxFlags |= GFX_MENU_OVERLAY;

    obj = obj_create_task(&fade_to_black_cb, 0x1000);
    obj->x_0f4167b4[0] = 6;
    tr_scene_loop();

    sClearColorR = x_18643961;
    sClearColorG = x_32f1d6e2;
    sClearColorB = x_1c32c793;
    x_e30d50d2 &= ~(x_23ebd6b0 | x_d4c59644 | x_bee364e0);
    gGfxFlags &= ~GFX_MENU_OVERLAY;
    wad_unload_context(0x6000);
    x_25025961(x_c9614940);
}

void arena_pre_setup(void) {
    sWadUnk1 = gFrameCounter % 5;
    sWadUnk2 = 0;
    D_80081430 = 0;
    gWadCondLoad[x_83106b21].x_178eafa6 = gWadCondLoad[x_6f0b3be3].x_178eafa6 = 0;

    if (sPrevScreenId != SCREEN_WAIT) {
        load_wait_screen();
    }

    if (x_5e4e2788 != x_79c2dc5b) {
        wad_load_path("/bars/bars", x_2587f84f);
    } else {
        wad_load_path("/bars/bars2", x_2587f84f);
    }

    player_init(0);
    player_init(1);

    if (sFirstFight) {
        fight_reset();
    } else {
        fight_init();
    }
    osViBlack(1);
}

void arena_cleanup(void) {
    wad_unload_context(x_2587f84f);
    wad_unload_context(0x5000);
    wad_unload_context(0x5001);
}

void arena_stage_01(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg3", 0, 74, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();

    arena_cleanup();
}

void lighting_input_update(Object *obj) {
    if (x_59ce598c[x_6f0b3be3].x_33260da8 & x_ffe9ce36) {
        obj->x_224610f1.y -= 10;
    } else if (x_59ce598c[x_6f0b3be3].x_33260da8 & x_37f8540c) {
        obj->x_224610f1.y += 10;
    }
    model_lighting_apply(obj);
}

// unknown data
s32 D_80049400[] = { 0x40000, task_remove_current, 0x2800, 0x10000000, 0, "tc", lighting_input_update, 0x1000, 0 };

void arena_stage_02(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_88f11482 x_4346f5cb = { 0, -500, 0, 0 };
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, 74, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_03(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, -20, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_04(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, 40, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_05(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, 52, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 0, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_06(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, 96, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_07(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    arena_pre_setup();
    x_a0e73601("bg2", 0, 94, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_a0e73601("bg0", 0, -8, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_08(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, -7, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, -64, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_09(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, 20, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void arena_stage_10(void) {
    s32 x_32f1d6e2 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_4a7d6dd4 *x_3f14db6e;

    arena_pre_setup();
    x_3f14db6e = x_a0e73601("bg2", 0, -6, 0x2000, 0x10000, 0, x_32f1d6e2);
    x_3f14db6e->height -= 16;

    x_a0e73601("bg0", 0, 4, 0x1000, 0x10000, x_96186256, x_32f1d6e2);

    ground_load("arena", x_32f1d6e2);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    fight_init();
    tr_scene_loop();
    arena_cleanup();
}

void char_select_countdown(Object *obj) {
    s16 a3;

    a3 = 1 - gWadCondLoad[x_6f0b3be3].x_03604d94; // @bug maybe
    sFadeThreshold = 100;

    if (x_e30d50d2 & x_80ca0761) {
        obj->x_0f4167b4[1]++;
        if (obj->x_0f4167b4[1] == 4) {
            obj->x_0f4167b4[1] = 0;
            if (D_80081250 + D_80081254->x_64a8566c + 40) {
                D_80081254->x_64a8566c--;
            } else {
                if (x_5e4e2788 != x_3658fb97) {
                    gWadCondLoad[x_6db66fc3].x_fb21ca8c = TRUE;
                    gWadCondLoad[1 - x_6db66fc3].x_fb21ca8c = FALSE;
                    x_e38a6e19 = gWadCondLoad[x_6db66fc3].x_eb1fe45b + SCREEN_CHAR_SELECT_OFFSET;
                } else {
                    x_e38a6e19 = gWadCondLoad[1 - x_6db66fc3].x_eb1fe45b + SCREEN_CHAR_SELECT_OFFSET;
                    gWadCondLoad[x_83106b21].x_03604d94 = TRUE;
                }
                x_e30d50d2 |= x_ecbcd14e | x_bee364e0;
                obj->flags |= x_f51cb721;
            }
        }

        x_59ce598c[a3].x_c4397934 = TRUE;
        if ((x_59ce598c[a3].buttons & x_9cefe76c) ||
            x_5e4e2788 == x_3658fb97 && (x_59ce598c[1 - a3].buttons & x_9cefe76c)) {
            x_25025961(D_80081254);
            if (x_5e4e2788 != x_3658fb97) {
                x_e38a6e19 = gWadCondLoad[x_6db66fc3].x_eb1fe45b + SCREEN_CHAR_SELECT_OFFSET;
                gWadCondLoad[x_6db66fc3].x_fb21ca8c = TRUE;
                gWadCondLoad[1 - x_6db66fc3].x_fb21ca8c = FALSE;
            } else {
                x_e38a6e19 = SCREEN_ATTRACT;
            }
            x_e30d50d2 |= x_ecbcd14e | x_bee364e0;
            obj->flags |= x_f51cb721;
            D_80081254->flags &= ~x_8ce7ef70;
        }
    }
}

u16 D_80049434[] = { 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 298, 314, 330, 315, 316, 298, 331, 0 };

void intro_movies_load(Player *x_cc1d0de5, Object *x_84ff873b, s32 x_2092f891) {
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

        if ((v0 = wad_entry_find(name, x_2092f891)) >= 0) {
            a1 = x_cc1d0de5->x_68a6b5cd[D_80049434[i]].x_43d35340;
            x_84ff873b->x_20d20338->x_50771dcd[a1] = sWadEntries[v0].data;
            s4++;
            x_cc1d0de5->x_68a6b5cd[D_80049434[i]].x_bab9966d = model_anim_duration(x_84ff873b->x_20d20338, a1);
        }
    }
}

void fight_intro_setup(u8 x_cc1d0de5, s16 x_84ff873b, s32 x_2092f891) {
    s32 s0;
    Object *obj;
    Object *a1;
    Object *v1;

    s0 = gWadCondLoad[x_6f0b3be3].x_03604d94; // @bug maybe
    wad_unload_context(x_2587f84f);
    gWadCondLoad[s0].x_178eafa6 = 1;
    gWadCondLoad[1 - s0].x_178eafa6 = 0;

    if (sPrevScreenId != SCREEN_WAIT && gCurrentScreenId != SCREEN_OPTIONS) {
        load_wait_screen();
    }

    if (x_cc1d0de5) {
        obj = obj_create_task(char_select_countdown, 0x1000);
        obj->x_0f4167b4[0] = 480;
    }

    player_init(0);
    player_init(1);

    gWadCondLoad[x_83106b21].x_8a8d66c9 = gWadCondLoad[x_6f0b3be3].x_8a8d66c9 = TRUE;

    a1 = sIntroPlayerObjs[1 - s0];
    a1->pos.x = 0;
    a1->pos.z = 0;
    a1->x_224610f1.y = 0x400;

    sIntroPlayerObjs[s0]->pos.x = -5000;
    sIntroPlayerObjs[s0]->pos.z = -5000;
    sIntroPlayerObjs[s0]->flags |= x_c537cafa;

    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    if (gWadCondLoad[1 - s0].x_eb1fe45b != x_b52da315) {
        a1->flags |= x_3e24eba7;
    }

    x_e30d50d2 |= x_86c5bc33;

    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

    sFightLocked = FALSE;

    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;

    TASK_END(x_824b9544[x_83106b21].x_08b62e4f);
    TASK_END(x_824b9544[x_6f0b3be3].x_08b62e4f);

    intro_movies_load(x_824b9544 + 1 - s0, a1, x_2092f891);
    cam_battle_init(x_f4bce728);
    player_exec_move(x_824b9544 + 1 - s0, x_84ff873b, 1);
    gGfxFlags |= GFX_FLAG_4;
}

void intro_gore(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/gore/goreint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("goreint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg3", 0, 74, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();

    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_aaro(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/aaro/aaroint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("aaroint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 74, 0x10000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 15, 0x8000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();

    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_demi(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/demi/demiint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("demiint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, -8, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_demo(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/demo/demoint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("demoint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 32, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_eve(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/eve/eveint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("eveint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 52, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 0, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_morp(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/morp/morpint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("morpint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 96, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_niik(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/niik/niikint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("niikint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 94, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -8, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_scar(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/scar/scarint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("scarint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 0, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -64, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_sono(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/sono/sonoint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("sonoint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, 26, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void intro_zenm(void) {
    s32 x_a7710cd7 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;

    wad_load_path("/zenm/zenmint", x_46bec5bf);
    fight_intro_setup(TRUE, 0x70, 0x3000);
    D_80081254 = x_a0e73601("zenmint", 0, 250, 0, 0, x_8ce7ef70, 0x3000);
    D_80081250 = D_80081254->height;
    x_a0e73601("bg2", 0, -6, 0x2000, 0x10000, 0, x_a7710cd7);
    x_a0e73601("bg0", 0, 4, 0x1000, 0x10000, x_96186256, x_a7710cd7);
    ground_load("arena", x_a7710cd7);
    tr_scene_loop();
    wad_unload_context(0x3000);
    arena_cleanup();
    if (x_5e4e2788 != x_3658fb97) {
        wad_unload_context(x_a7710cd7);
    }
}

void boss_sono_end_check(Object *obj) {
    if (x_824b9544[x_83106b21].x_7f68c36b->x_bab9966d - 2 == x_824b9544[x_83106b21].obj->frameCounter) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
        x_e38a6e19 = SCREEN_BOOT;
    }
}

void anim_loop(Object *obj) {
    obj->frameCounter++;
    if (obj->frameCounter >= obj->x_20d20338->x_8e601526 - 1) {
        obj->frameCounter = 0;
    }
}

void boss_sono(void) {
    Object *obj;
    Object *x_942c59c7;
    void *a3;
    x_88f11482 x_93463df6 = { -200, 0, 0, 0 };
    x_4a7d6dd4 *x_3f14db6e;

    gWadCondLoad[x_83106b21].x_eb1fe45b = x_968cc9a2;
    gWadCondLoad[x_83106b21].x_fb21ca8c = TRUE;
    gWadCondLoad[x_6f0b3be3].x_fb21ca8c = FALSE;
    gWadCondLoad[x_83106b21].x_03604d94 = FALSE;
    gWadCondLoad[x_6f0b3be3].x_03604d94 = TRUE;

    wad_unload_context(0);
    x_e30d50d2 |= x_23ebd6b0 | x_d4c59644;
    gGfxFlags |= GFX_MENU_OVERLAY;

    wad_load_path("/sono/prize", x_46bec5bf);
    x_3f14db6e = x_a0e73601("prize", 0, 100, 0, 0, x_8ce7ef70, 0x3000);
    obj = obj_create_task(fade_to_black_cb, 0x1000);
    obj->x_0f4167b4[0] = 6;
    tr_scene_loop();

    x_e30d50d2 &= ~(x_d4c59644 | x_bee364e0);
    gGfxFlags &= ~GFX_MENU_OVERLAY;
    wad_load_path("/sono/sonoboss", x_46bec5bf);
    fight_intro_setup(FALSE, 346, 0x3000);
    x_a0e73601("bg2", 0, 26, 0x2000, 0x10000, 0, 0);
    x_a0e73601("bg0", 0, -24, 0x1000, 0x10000, x_96186256, 0);
    ground_load("arena", 0);
    a3 = sWadEntries[wad_entry_find("relic.k2", 0x3000)].x_4962fc73;
    x_942c59c7 = obj_create_with_model_ptr(&x_93463df6, 0x1000, anim_loop, a3);
    x_942c59c7->x_224610f1.y = 0x400;
    x_942c59c7->color.a = 80;
    obj_create_task(boss_sono_end_check, 0x1000);
    x_25025961(x_3f14db6e);
    tr_scene_loop();

    wad_unload_context(0x3000);
    wad_unload_context(0);
    wad_unload_context(1);
    if (sRoundWinCount == 0) {
        x_e38a6e19 = SCREEN_CREDITS;
    }
}

void boss_demi(void) {
    Object *obj;
    x_88f11482 x_54406eae = { -800, -100, 0, 0 };
    Object *a1;
    s32 x_fc517ba8;
    s16 x_ea78ab9e;
    void *a3;
    s32 padding;

    x_fc517ba8 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_ea78ab9e = gWadCondLoad[x_6f0b3be3].x_03604d94;

    wad_unload_context(x_2587f84f);
    wad_load_path("/demi/demiboss", x_46bec5bf);
    player_init(0);
    player_init(1);

    a1 = x_824b9544[x_ea78ab9e].obj;
    a1->pos.x = a1->pos.z = 0;
    a1->x_224610f1.y = 0x400;

    sIntroPlayerObjs[1 - x_ea78ab9e]->pos.x = -5000;
    sIntroPlayerObjs[1 - x_ea78ab9e]->pos.z = -5000;
    sIntroPlayerObjs[1 - x_ea78ab9e]->flags |= x_c537cafa;

    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    a1->flags |= x_3e24eba7;
    x_e30d50d2 |= x_86c5bc33;

    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

    sFightLocked = FALSE;

    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    TASK_END(x_824b9544[x_83106b21].x_08b62e4f);
    TASK_END(x_824b9544[x_6f0b3be3].x_08b62e4f);

    intro_movies_load(&x_824b9544[x_ea78ab9e], a1, 0x3000);
    cam_battle_init(x_f4bce728);
    player_exec_move(&x_824b9544[x_ea78ab9e], x_467d52ce, 1);
    gGfxFlags |= GFX_FLAG_4;
    obj_create_task(present_intro_presents, 0x1000);
    fight_init();

    a3 = sWadEntries[wad_entry_find("relic.k5", 0x3000)].x_4962fc73;
    obj = obj_create_with_model_ptr(&x_54406eae, 0x1000, anim_loop, a3);
    obj->x_224610f1.y = 0x400;
    obj->color.a = 80;

    x_a0e73601("bg2", 0, -32, 0x2000, 0x10000, 0, x_fc517ba8);
    x_a0e73601("bg0", 0, 8, 0x1000, 0x10000, x_96186256, x_fc517ba8);
    ground_load("arena", x_fc517ba8);
    sFightLocked = TRUE;
    tr_scene_loop();
    wad_unload_context(0x3000);
    x_e38a6e19 = SCREEN_PRACTICE;
}

void ending_char(void) {
    u16 x_4c3c4684;
    u16 x_de61763c;
    Object *obj;
    char x_fc517ba8[12];
    char x_49781937[12];

    x_4c3c4684 = 1 - gWadCondLoad[x_6f0b3be3].x_03604d94;
    x_de61763c = x_824b9544[x_4c3c4684].x_eb1fe45b;
    wad_unload_all();
    wad_load_path("/title/ending", x_f238a878);

    wad_strcpy(x_fc517ba8, "/");
    wad_strcat(x_fc517ba8, D_8004B844[x_de61763c].x_1256da71->name);
    wad_strcat(x_fc517ba8, "/");
    wad_strcat(x_fc517ba8, D_8004B844[x_de61763c].x_1256da71->name);
    wad_strcat(x_fc517ba8, "end");
    wad_load_path(x_fc517ba8, x_f238a878);

    obj = obj_create_task(present_theend_init, 0x1000);
    obj->x_0f4167b4[0] = 60;

    wad_strcpy(x_49781937, D_8004B844[x_de61763c].x_1256da71->name);
    wad_strcat(x_49781937, "end1");

    D_80081254 = x_a0e73601(x_49781937, 0, 40, 0, 0, x_96186256, 0x4000);
    D_80081254 = x_a0e73601("passwd", 0, 205, 0, 0, x_96186256, 0x4000);
    x_e30d50d2 |= x_86c5bc33;
    gGfxFlags |= GFX_MENU_OVERLAY;
    tr_scene_loop();
    wad_unload_context(0x4000);
}

void credits_screen(void) {
    Object *x_87eba76e;

    wad_unload_all();
    wad_load_path("/title/credit", x_f238a878);
    D_80081254 = x_a0e73601("credit", 0, 250, 0, 0, x_8ce7ef70, 0x4000);
    D_80081250 = D_80081254->height;
    x_87eba76e = obj_create_task(present_win_result_loop, 0x1000);
    x_87eba76e->x_0f4167b4[2] = 4;
    present_haze_init(x_87eba76e, 0x4000);
    sClearZbuffer = FALSE;
    x_e30d50d2 |= x_86c5bc33;
    gGfxFlags |= GFX_MENU_OVERLAY;
    tr_scene_loop();
    wad_unload_context(0x4000);
}

void ending_easywin_input(Object *obj) {
    if (x_59ce598c[sWinnerIdx].buttons & x_9cefe76c) {
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
    }
}

void ending_easywin(void) {
    wad_unload_all();
    wad_load_path("/title/easywin", x_f238a878);
    x_a0e73601("easyimg", 0, 0, 0, 0, x_96186256, 0x4000);
    obj_create_task(ending_easywin_input, 0x1000);
    sClearZbuffer = TRUE;
    x_e30d50d2 |= x_86c5bc33;
    gGfxFlags |= GFX_MENU_OVERLAY;
    tr_scene_loop();
    wad_unload_context(0x4000);
    x_e38a6e19 = SCREEN_EASY_WIN;
}

void screen_profile_apply(s32 x_cc1d0de5) {
    sFogMin = gScreenProfiles[x_cc1d0de5].fogMin;
    sFogMax = gScreenProfiles[x_cc1d0de5].fogMax;
    sFogColorR = gScreenProfiles[x_cc1d0de5].fogColorR;
    sFogColorG = gScreenProfiles[x_cc1d0de5].fogColorG;
    sFogColorB = gScreenProfiles[x_cc1d0de5].fogColorB;
    sClearColorR = gScreenProfiles[x_cc1d0de5].clearColorR;
    sClearColorG = gScreenProfiles[x_cc1d0de5].clearColorG;
    sClearColorB = gScreenProfiles[x_cc1d0de5].clearColorB;
}

void demo_fight_setup(u8 x_cc1d0de5) {
    x_88f11482 x_fd09f53e[] = { { -1152, 0, 0, 0 }, { 0, 0, 0, 0 } };
    u32 x_b3c51f8a;
    s32 s1;
    s16 x_05e00b01;
    u16 t9;
    Object *s0;
    Object *a3;

    s1 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    t9 = 1 - s1;
    x_b3c51f8a = s1;
    player_init(0);
    player_init(1);

    s0 = x_824b9544[t9].obj;
    a3 = x_824b9544[x_b3c51f8a].obj;

    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    s0->pos.x = x_fd09f53e[1].x;
    s0->pos.y = x_fd09f53e[1].y;
    s0->pos.z = x_fd09f53e[1].z;
    a3->pos.x = x_fd09f53e[0].x;
    a3->pos.y = x_fd09f53e[0].y;
    a3->pos.z = x_fd09f53e[0].z;

    if (!x_cc1d0de5) {
        if (gWadCondLoad[t9].x_eb1fe45b == x_968cc9a2) {
            x_824b9544[t9].obj->pos.x -= 400;
        } else if (gWadCondLoad[t9].x_eb1fe45b == x_73cf9ceb) {
            x_824b9544[t9].obj->pos.x += 1200;
            if (x_824b9544[x_b3c51f8a].obj) {} // required to match
        }
    }

    s0->x_224610f1.y = 0x400;

    x_05e00b01 = gWadCondLoad[t9].x_eb1fe45b; // required to match
    if ((x_05e00b01 == x_968cc9a2 || x_05e00b01 == x_73cf9ceb) && !x_cc1d0de5) {
        a3->x_224610f1.y = 0x400;
    } else {
        a3->x_224610f1.y = 0xC00;
    }

    if (gWadCondLoad[t9].x_eb1fe45b != x_b52da315) {
        s0->flags |= x_3e24eba7;
    }
    a3->flags |= x_3e24eba7;

    x_e30d50d2 |= x_86c5bc33;
    x_59ce598c[x_83106b21].x_33260da8 = x_59ce598c[x_6f0b3be3].x_33260da8 = 0;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    sFightLocked = FALSE;

    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    TASK_END(x_824b9544[x_83106b21].x_08b62e4f);
    TASK_END(x_824b9544[x_6f0b3be3].x_08b62e4f);

    cam_battle_init(x_f4bce728);
    intro_movies_load(&x_824b9544[x_b3c51f8a], a3, 0x4000);
    intro_movies_load(&x_824b9544[t9], s0, 0x4000);
    gGfxFlags |= GFX_FLAG_4;
    x_a0e73601("bg2", 0, -27, 0x2000, 0x10000, 0, x_b3c51f8a);
    x_a0e73601("bg0", x_b3c51f8a * 0, 8, 0x1000, 0x10000, x_96186256, x_b3c51f8a);
    screen_profile_apply(SCREEN_PRACTICE);
    ground_load("arena", x_b3c51f8a);
    sFightLocked = TRUE;
}

void ending_generic(void) {
    u16 x_21e2fc34;
    u16 x_5bbba600;
    char x_32f1d6e2[80];

    x_21e2fc34 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_5bbba600 = 1 - x_21e2fc34;
    gWadCondLoad[x_83106b21].x_178eafa6 = gWadCondLoad[x_6f0b3be3].x_178eafa6 = 0;
    sFightLocked = TRUE;
    D_80080234 = 1;

    switch (gWadCondLoad[x_5bbba600].x_eb1fe45b) {
        case x_c4ddde6d:
            wad_strcpy(x_32f1d6e2, "/aaro/aarogend");
            break;
        case x_ff5073d4:
            wad_strcpy(x_32f1d6e2, "/demi/demigend");
            break;
        case x_73cf9ceb:
            wad_strcpy(x_32f1d6e2, "/demo/demogend");
            break;
        case x_6a049984:
            wad_strcpy(x_32f1d6e2, "/eve/evegend");
            break;
        case x_537ef8a7:
            wad_strcpy(x_32f1d6e2, "/gore/goregend");
            break;
        case x_b52da315:
            wad_strcpy(x_32f1d6e2, "/morp/morpgend");
            break;
        case x_13ed828f:
            wad_strcpy(x_32f1d6e2, "/niik/niikgend");
            break;
        case x_12e7e1dc:
            wad_strcpy(x_32f1d6e2, "/scar/scargend");
            break;
        case x_968cc9a2:
            wad_strcpy(x_32f1d6e2, "/sono/sonogend");
            break;
        case x_379149a4:
            wad_strcpy(x_32f1d6e2, "/zenm/zenmgend");
            break;
    }

    wad_load_path(x_32f1d6e2, x_f238a878);
    if (wad_streq(x_32f1d6e2, "/demi/demigend") != 0) {
        if (gWadCondLoad[x_5bbba600].x_eb1fe45b != x_968cc9a2 && gWadCondLoad[x_5bbba600].x_eb1fe45b != x_73cf9ceb) {
            wad_load_path("/demi/demigend", x_f238a878);
        }
    }

    switch (gWadCondLoad[x_5bbba600].x_eb1fe45b) {
        case x_73cf9ceb:
            wad_load_path("/demi/demigen3", x_f238a878);
            obj_create_task(present_demo_sfx, 0x1000);
            break;
        case x_968cc9a2:
            wad_load_path("/demi/demigen2", x_f238a878);
            obj_create_task(present_demo_sfx, 0x1000);
            break;
    }

    demo_fight_setup(FALSE);
    wad_load_path("/demi/demidust", x_2587f84f);
    player_exec_move(&x_824b9544[x_21e2fc34], x_9b1bc46c, 1);
    player_exec_move(&x_824b9544[x_5bbba600], x_41323a8a, 1);
    obj_create_task(present_demo_action, 0x1000);
    tr_scene_loop();
    wad_unload_context(0x4000);
    wad_unload_context(x_2587f84f);
    x_e38a6e19 = SCREEN_ATTRACT_AGAIN;
}

void ending_open(void) {
    u16 x_1a071863;
    u16 x_de61763c;
    char x_f10a928a[12];
    char x_d16311d7[12];
    Object *obj;

    x_1a071863 = 1 - gWadCondLoad[x_6f0b3be3].x_03604d94;
    x_de61763c = x_824b9544[x_1a071863].x_eb1fe45b;

    wad_load_path("/title/ending", x_f238a878);

    wad_strcpy(x_f10a928a, "/");
    wad_strcat(x_f10a928a, D_8004B844[x_de61763c].x_1256da71->name);
    wad_strcat(x_f10a928a, "/");
    wad_strcat(x_f10a928a, D_8004B844[x_de61763c].x_1256da71->name);
    wad_strcat(x_f10a928a, "end");
    wad_load_path(x_f10a928a, x_f238a878);

    wad_strcpy(x_d16311d7, D_8004B844[x_de61763c].x_1256da71->name);
    wad_strcat(x_d16311d7, "end");
    D_80081254 = x_a0e73601(x_d16311d7, 0, 250, 0, 0, x_8ce7ef70, 0x4000);
    D_80081250 = D_80081254->height;

    obj = obj_create_task(present_win_result_loop, 0x1000);
    obj->x_0f4167b4[2] = 5;
    obj->x_0f4167b4[1] = 0;
    obj->x_0f4167b4[0] = 0;

    sClearZbuffer = FALSE;
    x_e30d50d2 |= x_86c5bc33;
    cam_ko_init(x_f4bce728, x_1a071863);
}

void closing_cutscene(void) {
    Object *obj;
    Model *a3;
    x_88f11482 x_048c1e73 = { -600, 0, -30, 0 };
    x_88f11482 x_c188a78e = { -400, 0, 200, 0 };
    x_88f11482 x_dcccc364 = { -400, 0, 0, 0 };
    u16 x_21e2fc34;
    u16 x_5bbba600;
    Player *x_13d65ace;
    Player *x_c48d15e0;
    char x_32f1d6e2[72];

    x_21e2fc34 = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_5bbba600 = 1 - x_21e2fc34;

    x_c48d15e0 = &x_824b9544[x_5bbba600];
    x_13d65ace = &x_824b9544[x_21e2fc34];

    sFightLocked = TRUE;
    D_80080234 = 1;
    gWadCondLoad[x_21e2fc34].x_178eafa6 = gWadCondLoad[x_5bbba600].x_178eafa6 = 0;

    switch (gWadCondLoad[x_5bbba600].x_eb1fe45b) {
        case x_c4ddde6d:
            wad_strcpy(x_32f1d6e2, "/aaro/aaroclos");
            break;
        case x_ff5073d4:
            wad_strcpy(x_32f1d6e2, "/demi/demiclos");
            break;
        case x_73cf9ceb:
            wad_strcpy(x_32f1d6e2, "/demo/democlos");
            break;
        case x_6a049984:
            wad_strcpy(x_32f1d6e2, "/eve/eveclos");
            break;
        case x_537ef8a7:
            wad_strcpy(x_32f1d6e2, "/gore/goreclos");
            break;
        case x_b52da315:
            wad_strcpy(x_32f1d6e2, "/morp/morpclos");
            break;
        case x_13ed828f:
            wad_strcpy(x_32f1d6e2, "/niik/niikclos");
            break;
        case x_12e7e1dc:
            wad_strcpy(x_32f1d6e2, "/scar/scarclos");
            break;
        case x_968cc9a2:
            wad_strcpy(x_32f1d6e2, "/sono/sonoclos");
            break;
        case x_379149a4:
            wad_strcpy(x_32f1d6e2, "/zenm/zenmclos");
            break;
    }
    wad_load_path(x_32f1d6e2, x_f238a878);

    if (gWadCondLoad[x_5bbba600].x_eb1fe45b == x_73cf9ceb) {
        wad_strcpy(x_32f1d6e2, "/demi/demigen3");
    } else {
        wad_strcpy(x_32f1d6e2, "/demi/demigen2");
    }
    wad_load_path(x_32f1d6e2, x_f238a878);

    demo_fight_setup(TRUE);
    player_exec_move(x_13d65ace, x_dd751953, 1);
    player_exec_move(x_c48d15e0, x_c8c943ae, 1);
    x_13d65ace->obj->flags |= x_c537cafa;
    ending_open();

    wad_load_path("/demi/relic", x_f238a878);
    a3 = sWadEntries[wad_entry_find("relic.k5", 0x4000)].x_4962fc73;
    obj = obj_create_with_model_ptr(&x_dcccc364, 0x1000, anim_loop, a3);
    obj->color.a = 80;

    if (gWadCondLoad[x_5bbba600].x_eb1fe45b == x_968cc9a2 || gWadCondLoad[x_5bbba600].x_eb1fe45b == x_73cf9ceb) {
        if (x_5bbba600 != 0) {
            a3 = sWadEntries[wad_entry_find("dheadp2.k2", 0x4000)].x_4962fc73;
        } else {
            a3 = sWadEntries[wad_entry_find("dheadp1.k2", 0x4000)].x_4962fc73;
        }
        obj = obj_create_with_model_ptr(&x_dcccc364, 0x1000, NULL, a3);
        obj->x_224610f1.y = -1179;
        obj->color.a = 255;
        obj->flags |= x_3e24eba7;
    }

    tr_scene_loop();
    wad_unload_all();
}

void title_pre_init(void) {
    s32 i;

    sFirstFight = TRUE;
    gWadCondLoad[x_83106b21].x_7d8e7a6f = gWadCondLoad[x_6f0b3be3].x_7d8e7a6f = 0;

    for (i = 0; i < 11; i++) {
        D_800B6350[x_6f0b3be3][i] = 0;
        D_800B6350[x_83106b21][i] = 0;
    }

    gWadCondLoad[x_83106b21].x_8a8d66c9 = gWadCondLoad[x_6f0b3be3].x_8a8d66c9 = TRUE;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    gWadCondLoad[x_83106b21].x_c35c64af = gWadCondLoad[x_6f0b3be3].x_c35c64af = 400;
    gWadCondLoad[x_83106b21].x_cc57155e = gWadCondLoad[x_6f0b3be3].x_cc57155e = 0;
}

void title_screen(void) {
    Object *x_a7ef4a30;
    x_f0d7e70f x_081c4eef = { x_35414b8d, present_attract_loop, 0, 0x1000, "options2.sp2" };
    x_88f11482 x_c9614940 = { 164, 155, 0, 0 };

    wad_unload_all();
    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    wad_load_path("/title", x_35b88489);
    x_a0e73601("dr_title", 0, 0, 0, 0, x_96186256, x_35b88489);
    gGfxFlags |= GFX_MENU_OVERLAY;
    x_e30d50d2 |= x_86c5bc33;

    if (sPrevScreenId == SCREEN_TITLE) {
        Model *x_2ac4abbe = sWadEntries[wad_entry_find("title.k2", x_35b88489)].x_4962fc73;
        x_a7ef4a30 = obj_create_with_model_ptr(&sZeroPosition, 0x1000, present_title_task, x_2ac4abbe);
        x_a7ef4a30->flags |= x_a816b63b;
    } else {
        x_a7ef4a30 = obj_create_from_def(&x_c9614940, &x_081c4eef, x_35b88489);
    }

    x_a7ef4a30->currentTask->delay = 30;

    obj_create_task(x_8daf2444, 0x1000);
    title_pre_init();
    tr_scene_loop();

    wad_unload_context(0x2000);
    if (x_e38a6e19 != SCREEN_WAIT) {
        wad_unload_context(x_24b231d4);
    }
}

void fade_out_cb(Object *obj) {
    tr_quad_xlu(sFadeAlpha, 0);

    if (sFadeAlpha - 2 > 0) {
        sFadeAlpha -= 2;
        return;
    }

    obj->flags |= x_f51cb721;
    sOverlayBrightness = 0;
}

void fade_in_cb(Object *obj) {
    x_f0d7e70f x_fc517ba8 = { 83, present_attract_loop, 0, 0x1000, "options2.sp2" };
    x_88f11482 x_93463df6 = { 160, 155, 0, 0 };
    Object *v0;

    sOverlayBrightness = 200;
    tr_quad_xlu(sFadeAlpha, NULL);

    if (sFadeAlpha + 32 < 255) {
        sFadeAlpha += 32;
        return;
    }

    audio_sfx_stop(0x2000, 8);
    obj->x_0232396f = fade_out_cb;
    x_a0e73601("dr_title", 0, 0, 0, 0, x_96186256, x_35b88489);
    v0 = obj_create_from_def(&x_93463df6, &x_fc517ba8, 0x2000);
    v0->currentTask->delay = 60;
    x_f4bce728->pos.z = -2200;
    obj_create_task(x_8daf2444, 0x1000);
}

void title_intro(void) {
    s32 unused;
    Object *v0;
    x_f0d7e70f x_d16311d7 = { 83, present_attract_loop, 0, 0x1000, "options2.sp2" };
    x_88f11482 x_32f1d6e2 = { 160, 155, 0, 0 };

    sClearZbuffer = FALSE;
    gGfxFlags |= GFX_MENU_OVERLAY;
    x_e30d50d2 |= x_86c5bc33;
    wad_load_path("/title/tit_int", x_35b88489);
    wad_load_path("/plyrsel/plyrsel", x_24b231d4);
    v0 = obj_create_task(present_title_open, 0x1000);
    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    present_haze_init(v0, 0x2000);

    D_80081254 = x_a0e73601("oplog", 0, 250, 0, 0x10000, x_8ce7ef70, x_35b88489);
    D_80081250 = D_80081254->height;

    title_pre_init();
    tr_scene_loop();
    wad_unload_context(0x2000);
    if (x_e38a6e19 != SCREEN_WAIT) {
        wad_unload_context(x_24b231d4);
    }
}

void title_error(void) {
    wad_load_path("/title/error", x_35b88489);
    x_a0e73601("messpg", 0, 90, 0, 180, x_96186256, x_35b88489);
    tr_scene_loop();
}

void title_logo(void) {
    wad_unload_all();
    x_e30d50d2 |= x_86c5bc33;
    gGfxFlags |= GFX_MENU_OVERLAY;
    gGfxFlags |= GFX_BORDER_AROUND;
    if (!x_59ce598c[x_83106b21].x_12a7bd86 && !x_59ce598c[x_6f0b3be3].x_12a7bd86) {
        title_error();
    }

    wad_load_path("/title/logo", x_35b88489);
    x_a0e73601("vic", 0, 30, 0, 180, x_96186256, x_35b88489);
    x_a0e73601("n64lic", 0, 190, 0, 240, x_96186256, x_35b88489);
    obj_create_task(present_kronos_logo, 0x1000);
    tr_scene_loop();
    wad_unload_context(0x2000);
}

void options_menu(void) {
    Object *controller;
    Object *obj;
    x_f0d7e70f x_910f3493 = { x_e7beedae, options_menu_task, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_dfcbab92 = { x_edf70307, option_game_mode, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_3d280011 = { x_adc09931, option_round_count, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_f2490cb2 = { x_0357f149, option_rounds_win, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_4b76305b = { x_4b8a6796, option_sound_mute, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_d252ddf2 = { x_86be64ca, option_bgm_volume, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_7b5eb252 = { x_86be64ca, option_sfx_volume, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_6a701386 = { x_51d9e266, option_controller_setup, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_4ae9ab69 = { x_273c3512, option_char_config, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_f4b84c7c = { x_9b5ea511, option_stage_select, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_e8326674 = { x_8bab2f3e, option_back_attract, 0, x_9d442987, "options2.sp2" };
    x_88f11482 x_7b3384f3 = { 130, 130, 0, 0 };
    x_88f11482 x_98eec76d = { 181, 74, 0, 0 };
    x_88f11482 x_39a42620 = { 181, 91, 0, 0 };
    x_88f11482 x_4ff52ceb = { 181, 105, 0, 0 };
    x_88f11482 x_867609ad = { 181, 121, 0, 0 };
    x_88f11482 x_49ea79b4 = { 181, 136, 0, 0 };
    x_88f11482 x_eeea4d36 = { 181, 151, 0, 0 };
    x_88f11482 x_375e794a = { 118, 166, 0, 0 };
    x_88f11482 x_ac1eaa4d = { 117, 181, 0, 0 };
    x_88f11482 x_5a64842d = { 135, 198, 0, 0 };
    x_88f11482 x_cdcf9ce9 = { 146, 228, 0, 0 };

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    wad_load_path("/title/option", x_35b88489);
    x_a0e73601("bgopt", 0, 0, 0, 0, x_96186256, x_35b88489);
    gGfxFlags |= GFX_MENU_OVERLAY;
    x_e30d50d2 |= x_86c5bc33;

    controller = obj_create_from_def(&x_7b3384f3, &x_910f3493, x_35b88489);

    obj = obj_create_from_def(&x_98eec76d, &x_dfcbab92, x_35b88489);
    obj->frameCounter = x_028e5846 + x_be30259d;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_39a42620, &x_3d280011, x_35b88489);
    obj->frameCounter = x_c8356c60 + x_336693df;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_4ff52ceb, &x_f2490cb2, x_35b88489);
    obj->frameCounter = x_adcfd05c + x_afcff1b4;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_867609ad, &x_4b76305b, x_35b88489);
    obj->frameCounter = sAudioMuted + x_4b8a6796;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_49ea79b4, &x_d252ddf2, x_35b88489);
    obj->frameCounter = sMusicVolumeSetting / (0x8000 / 9) + x_afcff1b4;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_eeea4d36, &x_7b5eb252, x_35b88489);
    obj->frameCounter = gSfxVolumeSetting / (0x8000 / 9) + x_afcff1b4;
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_375e794a, &x_6a701386, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_ac1eaa4d, &x_4ae9ab69, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_5a64842d, &x_f4b84c7c, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    obj = obj_create_from_def(&x_cdcf9ce9, &x_e8326674, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = controller;

    tr_scene_loop();
    wad_unload_context(x_35b88489);
}

void button_icon_update(Object *obj, s16 x_30bbe547) {
    s16 i;
    s16 button;

    button = sCharButtonTbl[obj->x_0f4167b4[x_13266785]];
    for (i = 0; i < 8; i++) {
        if (gRemapTable[x_30bbe547][i] == button) {
            break;
        }
    }

    switch (i) {
        case 0:
            obj->frameCounter = x_729a61e6;
            break;
        case 1:
            obj->frameCounter = x_a9cd5d36;
            break;
        case 2:
            obj->frameCounter = x_6dce29db;
            break;
        case 3:
            obj->frameCounter = x_23d505ec;
            break;
        case 4:
            obj->frameCounter = x_810a8a6e;
            break;
        case 5:
            obj->frameCounter = x_acee1321;
            break;
        case 6:
            obj->frameCounter = x_a4344608;
            break;
        case 7:
            obj->frameCounter = x_ab3153db;
            break;
    }
}

void options_controller(void) {
    Object *x_6dc41566;
    Object *x_abfe8d41;
    Object *obj;
    x_f0d7e70f x_d772ebb4 = { x_42fcfcea, NULL, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_43f9ca3f = { x_7eb4b3f4, select_char_task, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_fa93fe6a = { x_ab3153db, select_char_update, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_c592c457 = { x_a4344608, select_char_update, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_f13e2bec = { x_acee1321, select_char_update, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_1ccec23b = { x_23d505ec, select_char_update, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_23c4e7d3 = { x_729a61e6, select_char_update, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_c1e64f43 = { x_6dce29db, select_char_update, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_1c7346b1 = { x_a9cd5d36, select_char_update, 0, x_9d442987, "options2.sp2" };
    x_f0d7e70f x_cc88bd06 = { x_8bab2f3e, select_stage_task, 0, x_9d442987, "options2.sp2" };
    x_88f11482 x_0bef2693 = { 133, 126, 0, 0 };
    x_88f11482 x_bf23db74 = { 40, 82, 0, 0 };
    x_88f11482 x_7e4f6c9d = { 179, 82, 0, 0 };
    x_88f11482 x_e725bb19 = { 40, 96, 0, 0 };
    x_88f11482 x_fef76a74 = { 179, 96, 0, 0 };
    x_88f11482 x_77027484 = { 40, 110, 0, 0 };
    x_88f11482 x_e0e052f7 = { 179, 110, 0, 0 };
    x_88f11482 x_ebe59286 = { 40, 124, 0, 0 };
    x_88f11482 x_b42630db = { 179, 124, 0, 0 };
    x_88f11482 x_c9b06339 = { 40, 138, 0, 0 };
    x_88f11482 x_2a8bc04d = { 179, 138, 0, 0 };
    x_88f11482 x_887b975c = { 40, 152, 0, 0 };
    x_88f11482 x_03f0364f = { 179, 152, 0, 0 };
    x_88f11482 x_aa4f74c9 = { 40, 166, 0, 0 };
    x_88f11482 x_48fb41dd = { 179, 166, 0, 0 };
    x_88f11482 x_fde88f40 = { 40, 180, 0, 0 };
    x_88f11482 x_09ae4a39 = { 179, 180, 0, 0 };
    x_88f11482 x_20652c2f = { 149, 224, 0, 0 };

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    wad_load_path("/title/control", x_35b88489);
    x_a0e73601("bgcont", 0, 0, 0, 0, x_96186256, x_35b88489);
    gGfxFlags |= GFX_MENU_OVERLAY;
    x_e30d50d2 |= x_86c5bc33;

    obj_create_from_def(&x_0bef2693, &x_d772ebb4, x_35b88489);

    x_6dc41566 = obj_create_from_def(&x_bf23db74, &x_43f9ca3f, x_35b88489);
    x_6dc41566->x_0f4167b4[x_0371940a] = x_6dc41566;
    x_6dc41566->x_0f4167b4[x_13266785] = 0;
    button_icon_update(x_6dc41566, 0);

    obj = obj_create_from_def(&x_e725bb19, &x_fa93fe6a, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 1;
    button_icon_update(obj, 0);

    obj = obj_create_from_def(&x_77027484, &x_c592c457, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 2;
    button_icon_update(obj, 0);

    obj = obj_create_from_def(&x_ebe59286, &x_f13e2bec, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 3;
    button_icon_update(obj, 0);

    obj = obj_create_from_def(&x_c9b06339, &x_1ccec23b, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 4;
    button_icon_update(obj, 0);

    obj = obj_create_from_def(&x_887b975c, &x_23c4e7d3, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 5;
    button_icon_update(obj, 0);

    obj = obj_create_from_def(&x_aa4f74c9, &x_c1e64f43, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 6;
    button_icon_update(obj, 0);

    obj = obj_create_from_def(&x_fde88f40, &x_1c7346b1, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_6dc41566;
    obj->x_0f4167b4[x_13266785] = 7;
    button_icon_update(obj, 0);

    x_abfe8d41 = obj_create_from_def(&x_7e4f6c9d, &x_43f9ca3f, x_35b88489);
    x_abfe8d41->x_0f4167b4[x_0371940a] = x_abfe8d41;
    x_abfe8d41->x_0f4167b4[x_13266785] = 0;
    x_abfe8d41->x_0f4167b4[x_283009b1] = x_6f0b3be3;
    button_icon_update(x_abfe8d41, 1);

    obj = obj_create_from_def(&x_fef76a74, &x_fa93fe6a, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 1;
    button_icon_update(obj, 1);

    obj = obj_create_from_def(&x_e0e052f7, &x_c592c457, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 2;
    button_icon_update(obj, 1);

    obj = obj_create_from_def(&x_b42630db, &x_f13e2bec, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 3;
    button_icon_update(obj, 1);

    obj = obj_create_from_def(&x_2a8bc04d, &x_1ccec23b, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 4;
    button_icon_update(obj, 1);

    obj = obj_create_from_def(&x_03f0364f, &x_23c4e7d3, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 5;
    button_icon_update(obj, 1);

    obj = obj_create_from_def(&x_48fb41dd, &x_c1e64f43, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 6;
    button_icon_update(obj, 1);

    obj = obj_create_from_def(&x_09ae4a39, &x_1c7346b1, x_35b88489);
    obj->x_0f4167b4[x_0371940a] = x_abfe8d41;
    obj->x_0f4167b4[x_13266785] = 7;
    button_icon_update(obj, 1);

    obj = obj_create_from_def(&x_20652c2f, &x_cc88bd06, x_35b88489);
    obj->x_0f4167b4[x_f2901470] = x_6dc41566;
    obj->x_0f4167b4[x_88d435fa] = x_abfe8d41;

    tr_scene_loop();
    wad_unload_context(x_35b88489);
}

void options_score(void) {
    x_f0d7e70f x_b97c1d15 = { x_87664290, select_score_display, 0, x_9d442987, "options2.sp2" };
    x_88f11482 x_b0e0e2fc = { 133, 126, 0, 0 };

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    wad_load_path("/title/rank", x_35b88489);
    x_a0e73601("bgrank", 0, 4, 0, 0, x_96186256, x_35b88489);
    sScoreTitleObj = obj_create_from_def(&x_b0e0e2fc, &x_b97c1d15, x_35b88489);
    select_score_init();
    gGfxFlags |= GFX_MENU_OVERLAY;
    x_e30d50d2 |= x_86c5bc33;
    tr_scene_loop();
    wad_unload_context(x_35b88489);
}

void options_stage(void) {
    wad_unload_context(0);
    wad_unload_context(1);
    wad_unload_context(x_2587f84f);

    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = TRUE;
    wad_load_path("/title/stats", x_35b88489);
    x_a0e73601("aarost", 0, 13, 0, 0, x_96186256, x_35b88489);
    gGfxFlags |= GFX_MENU_OVERLAY;
    x_e30d50d2 |= x_86c5bc33;
    obj_create_task(select_stage_screen, x_9d442987);
    tr_scene_loop();
    wad_unload_context(x_35b88489);
}

static void null_func(void) {
}

void arena_stage_default(void) {
    s32 unused;
    x_2758cdab x_8a9089b3 = { 0, -400, 0, 0 };
    x_88f11482 x_7d0aaee0 = { -400, 0, 0, 0 };
    x_88f11482 x_de61763c = { 400, 0, 0, 0 };
    s32 x_f0d1d935;
    s32 x_54406eae = gWadCondLoad[x_6f0b3be3].x_fb21ca8c;
    x_aece7675 x_d16311d7 = { "gore", task_remove_current, 0, 0x1000, 0 };
    x_aece7675 x_32f1d6e2 = { "arena", task_remove_current, 0, 0x1000, 0 };

    wad_load_path("/bars", x_2587f84f);
    player_init(0);
    player_init(1);
    x_a0e73601("bg2", 0, 74, 0x2000, 0x10000, 0, x_54406eae);
    x_a0e73601("bg0", 0, 15, 0x1000, 0x10000, x_96186256, x_54406eae);
    ground_load("arena", x_54406eae);
    hud_setup();

    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->callback = cam_intro_start;
    x_f4bce728->currentTask->stackPtr = 0;

    tr_scene_loop();
}
