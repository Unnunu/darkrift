#include "common.h"

void run_main_menu_mode(void);
void run_options_mode(void);
void run_menu_control_mode(void);
void run_menu_rank_mode(void);
void run_menu_stats_mode(void);
void run_player_selection_mode(void);
void run_battle_aaron_mode(void);
void run_battle_demitron_mode(void);
void run_battle_demonica_mode(void);
void run_battle_eve_mode(void);
void run_battle_gore_mode(void);
void run_battle_morphix_mode(void);
void run_battle_niiki_mode(void);
void run_battle_scarlet_mode(void);
void run_battle_sonork_mode(void);
void run_battle_zenmuron_mode(void);
void run_17_mode(void);
void run_intro_aaron_mode(void);
void run_intro_demitron_mode(void);
void run_intro_demonica_mode(void);
void run_intro_eve_mode(void);
void run_intro_gore_mode(void);
void run_intro_morphix_mode(void);
void run_intro_niiki_mode(void);
void run_intro_scarlet_mode(void);
void run_intro_sonork_mode(void);
void run_intro_zenmuron_mode(void);
void run_29_mode(void);
void run_30_mode(void);
void run_31_mode(void);
void run_intro_mode(void);
void run_logo_mode(void);
void run_34_mode(void);
void run_35_mode(void);
void run_36_mode(void);
void run_37_mode(void);

void func_80015D60(Object *obj);
void func_80016144(Object *obj);
void anim_loop(Object *);
void action_idle(Object *);
void action_stop_walking(Object *);
void action_dash(Object *);
void action_walk(Object *);
void action_run(Object *);
void action_jump(Object *);
void action_crouch(Object *);
void player_anim_func_3(Object *);
void action_grab(Object *);
void action_grabbed(Object *);
void action_none(Object *);
void action_damaged(Object *);
void anim_play_once(Object *);
void anim_pingpong_forward(Object *);
void player_trans_func_12(Object *);
void action_animation_end(Object *);
u8 player_check_func_1(Object *);
void player_trans_func_14(Object *);
u8 player_check_func_3(Object *);
u8 player_check_func_4(Object *);
void player_trans_func_15(Object *);
void player_trans_func_16(Object *);
u8 player_check_func_5(Object *);
u8 player_check_func_6(Object *);
void player_trans_func_17(Object *);
void player_trans_func_18(Object *);
u8 player_check_func_7(Object *);
void player_trans_func_22(Object *);
u8 player_check_func_8(Object *);
void player_trans_func_19(Object *);
void player_trans_func_20(Object *);
void player_trans_func_21(Object *);
void player_trans_func_23(Object *);
void player_trans_func_24(Object *);
void player_trans_func_25(Object *);
void player_trans_func_27(Object *);
void player_trans_func_26(Object *);
void player_trans_func_28(Object *);
void func_80015CD8(Object *);
void func_80015E24(Object *);
void func_8002A1F0(Object *);

extern Unk_8004BA6C D_800523FC;
extern Unk_8004BA6C D_8005254C;
extern Unk_8004BA6C D_80052560;
extern Unk_8004BA6C D_80052664;
extern Unk_8004BA6C D_80052688;
extern Unk_8004BA6C D_80052788;
extern Unk_8004BA6C D_8005287C;
extern Unk_8004BA6C D_80052890;
extern Unk_8004BA6C D_80052C3C;

extern HitZonesSetup D_80052220;
extern HitZonesSetup D_80052420;
extern HitZonesSetup D_80052580;
extern HitZonesSetup D_800526B0;
extern HitZonesSetup D_80052330;
extern HitZonesSetup D_800527A0;
extern HitZonesSetup D_800528B0;
extern HitZonesSetup D_80052990;
extern HitZonesSetup D_80052A60;
extern HitZonesSetup D_80052B30;

extern CharLighting gDefaultLighting;

s32 D_8004A5C0[] = { 0, 0, 0, 0 };

Vec4i D_8004A5D0[] = {
    { 60, 51, 0, 0 }, { 69, 51, 0, 0 }, { 69, 51, 0, 0 }, { 42, 51, 0, 0 }, { 51, 51, 0, 0 }, { 51, 51, 0, 0 },
    { 65, 51, 0, 0 }, { 47, 51, 0, 0 }, { 60, 51, 0, 0 }, { 60, 51, 0, 0 }, { 70, 51, 0, 0 },
};

Vec4i D_8004A680[] = {
    { 274, 51, 0, 0 }, { 261, 51, 0, 0 }, { 261, 51, 0, 0 }, { 287, 51, 0, 0 }, { 282, 51, 0, 0 }, { 285, 51, 0, 0 },
    { 264, 51, 0, 0 }, { 285, 51, 0, 0 }, { 267, 51, 0, 0 }, { 271, 51, 0, 0 }, { 262, 51, 0, 0 },
};

s16 D_8004A730[] = {
    175, 175, 150, 170, 160, 175, 175, 130, 175, 175, 175,
};

s16 D_8004A748[] = {
    400, 400, 250, 480, 550, 400, 900, 400, 400, 1000, 400,
};

ModelNodeGroup D_8004A760[] = {
    { { 18, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004A8DC[] = {
    { { 22, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { 18, -1, 0, 0 }, 18 },   { { 19, -1, 0, 0 }, 19 },
    { { 20, -1, 0, 0 }, 20 }, { { 21, -1, 0, 0 }, 21 }, { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004AAA8[] = {
    { { 25, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },     { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },     { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },     { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 },   { { 14, -1, 0, 0 }, 14 }, { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 },   { { 18, -1, 0, 0 }, 18 }, { { 19, -1, 0, 0 }, 19 },
    { { 20, -1, 0, 0 }, 20 }, { { 21, -1, 0, 0 }, 21 },   { { 22, -1, 0, 0 }, 22 }, { { 23, -1, 0, 0 }, 23 },
    { { 24, -1, 0, 0 }, 24 }, { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004ACB0[] = {
    { { 16, 0, -1, 0 }, -1 },   { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },     { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },     { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 },   { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 }, { { 15, -1, 0, 0 }, 15 },
    { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004AE04[] = {
    { { 15, 0, -1, 0 }, -1 },  { { 1, -1, 0, 0 }, -1 },    { { 2, -1, 0, 0 }, -2 }, { { 4, 3, -1, 0 }, 3 },
    { { 5, -1, 0, 0 }, 5 },    { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },  { { 8, -1, 0, 0 }, 8 },
    { { 11, 10, 9, -1 }, 11 }, { { 14, 13, 12, -1 }, 14 }, { { -1, -1, 0, 0 }, 0 },
};

ModelNodeGroup D_8004AEE0[] = {
    { { 18, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004B05C[] = {
    { { 22, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { 18, -1, 0, 0 }, 18 },   { { 19, -1, 0, 0 }, 19 },
    { { 20, -1, 0, 0 }, 20 }, { { 21, -1, 0, 0 }, 21 }, { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004B228[] = {
    { { 15, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 }, { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004B368[] = {
    { { 18, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { -1, -1, -1, -1 }, -1 },
};

ModelNodeGroup D_8004B4E4[] = {
    { { 15, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 }, { { -1, -1, -1, -1 }, -1 },
};

CharLighting gBattleAaronLighting = { { { { 255, 255, 255, 255 }, 0, -101, -126 }, { { 0, 0, 0, 0 }, 73, -73, -73 } } };
CharLighting gBattleDemitronLighting = { { { { 255, 254, 254, 255 }, 0, -126, -86 },
                                           { { 255, 59, 27, 0 }, 20, 126, 0 } } };
CharLighting gBattleDemonicaLighting = { { { { 191, 112, 96, 255 }, -1, -126, -55 },
                                           { { 30, 255, 132, 0 }, 5, 127, 191 } } };
CharLighting gBattleEveLighting = { { { { 255, 255, 255, 255 }, -1, -127, -128 },
                                      { { 91, 73, 112, 0 }, 0, 127, 63 } } };
CharLighting gBattleGoreLighting = { { { { 255, 255, 255, 255 }, 0, -123, -107 },
                                       { { 76, 60, 98, 0 }, 16, 127, -32 } } };
CharLighting gBattleMorphixLighting = { { { { 255, 210, 255, 0 }, 11, -115, 117 },
                                          { { 100, 120, 150, 0 }, -126, -121, 88 } } };
CharLighting gBattleNiikiLighting = { { { { 255, 228, 213, 0 }, 6, -125, -127 }, { { 33, 36, 68, 0 }, 44, 91, 98 } } };
CharLighting gBattleScarletLighting = { { { { 255, 213, 186, 0 }, 6, -125, -127 },
                                          { { 51, 42, 83, 0 }, 44, 91, 98 } } };
CharLighting gBattleSonorkLighting = { { { { 255, 255, 255, 0 }, 6, -127, -128 },
                                         { { 82, 50, 40, 0 }, -107, 123, 53 } } };
CharLighting gBattleZenmuronLighting = { { { { 219, 228, 255, 0 }, 11, -115, -117 },
                                           { { 231, 39, 22, 0 }, -126, -121, 88 } } };
CharLighting gBattleDemitronAltLighting = { { { { 255, 254, 254, 255 }, 0, -126, -86 },
                                              { { 255, 59, 27, 0 }, 20, 126, 0 } } };
CharLighting gBattleDemonicaAltLighting = { { { { 191, 112, 96, 255 }, -1, -126, -55 },
                                              { { 30, 255, 132, 0 }, 5, 127, 191 } } };

K2Def D_8004B7A4 = { "aaro", NULL, 0, OBJ_PRIO_DEFAULT, D_8004A760 };
K2Def D_8004B7B4 = { "demi", NULL, 0, OBJ_PRIO_DEFAULT, D_8004A8DC };
K2Def D_8004B7C4 = { "demo", NULL, 0, OBJ_PRIO_DEFAULT, D_8004AAA8 };
K2Def D_8004B7D4 = { "eve", NULL, 0, OBJ_PRIO_DEFAULT, D_8004ACB0 };
K2Def D_8004B7E4 = { "gore", NULL, 0, OBJ_PRIO_DEFAULT, D_8004AE04 };
K2Def D_8004B7F4 = { "morp", NULL, 0, OBJ_PRIO_DEFAULT, D_8004AEE0 };
K2Def D_8004B804 = { "niik", NULL, 0, OBJ_PRIO_DEFAULT, D_8004B05C };
K2Def D_8004B814 = { "scar", NULL, 0, OBJ_PRIO_DEFAULT, D_8004B228 };
K2Def D_8004B824 = { "sono", NULL, 0, OBJ_PRIO_DEFAULT, D_8004B368 };
K2Def D_8004B834 = { "zenm", NULL, 0, OBJ_PRIO_DEFAULT, D_8004B4E4 };

UnkTau D_8004B844[] = {
    { &D_80052220, &D_8004B7A4, { { 99, 185, 255, 0 }, { 255, 124, 46, 0 } } },
    { &D_80052420, &D_8004B7B4, { { 21, 255, 193, 0 }, { 255, 112, 26, 0 } } },
    { &D_80052580, &D_8004B7C4, { { 255, 32, 0, 0 }, { 0, 197, 120, 0 } } },
    { &D_800526B0, &D_8004B7D4, { { 70, 255, 58, 0 }, { 255, 63, 63, 0 } } },
    { &D_80052330, &D_8004B7E4, { { 26, 216, 255, 0 }, { 255, 89, 120, 0 } } },
    { &D_80052330, &D_8004B7E4, { { 26, 255, 255, 0 }, { 255, 89, 120, 0 } } },
    { &D_800527A0, &D_8004B7F4, { { 0, 180, 255, 0 }, { 255, 79, 0, 0 } } },
    { &D_800528B0, &D_8004B804, { { 255, 70, 168, 0 }, { 173, 99, 255, 0 } } },
    { &D_80052990, &D_8004B814, { { 156, 255, 158, 0 }, { 183, 126, 255, 0 } } },
    { &D_80052A60, &D_8004B824, { { 58, 255, 148, 0 }, { 0, 116, 255, 0 } } },
    { &D_80052B30, &D_8004B834, { { 105, 255, 69, 0 }, { 255, 38, 106, 0 } } },
};

UnkVec2s D_8004B8F4[] = {
    { 347, MOVE_ID_GRABBED_BY_AAR_226 }, { 550, MOVE_ID_GRABBED_BY_DEM_227 }, { 400, MOVE_ID_GRABBED_BY_DEM_228 },
    { 430, MOVE_ID_GRABBED_BY_EVE },     { 360, MOVE_ID_GRABBED_BY_GOR },     { 430, MOVE_ID_IDLE_068 },
    { 393, MOVE_ID_GRABBED_BY_MOR },     { 487, MOVE_ID_GRABBED_BY_NII },     { 430, MOVE_ID_GRABBED_BY_SCA },
    { 400, MOVE_ID_GRABBED_BY_SON },     { 430, MOVE_ID_GRABBED_BY_ZEN },
};

UnkVec2s D_8004B920[] = { { 171, MOVE_ID_COGRABBED_BY_A_253 }, { 250, MOVE_ID_COGRABBED_BY_D_254 },
                          { 369, MOVE_ID_COGRABBED_BY_D_255 }, { 400, MOVE_ID_COGRABBED_BY_E_256 },
                          { 488, MOVE_ID_COGRABBED_BY_G_257 }, { 400, MOVE_ID_COGRABBED_BY_G_257 },
                          { 483, MOVE_ID_COGRABBED_BY_M_258 }, { 400, MOVE_ID_COGRABBED_BY_N_259 },
                          { 422, MOVE_ID_COGRABBED_BY_S_260 }, { 400, MOVE_ID_COGRABBED_BY_S_261 },
                          { 400, MOVE_ID_COGRABBED_BY_Z_262 } };

UnkQwe D_8004B94C[] = {
    { CS_ID_GRABBED_BY_AARON, "AR_GR1" },      { CS_ID_GRABBED_BY_DEMITRON, "DM_GR1" },
    { CS_ID_GRABBED_BY_DEMONICA, "DO_GR1" },   { CS_ID_GRABBED_BY_EVE, "EV_GR1" },
    { CS_ID_GRABBED_BY_GORE, "GE_GR1" },       { CS_ID_GRABBED_BY_GORE, "GO_GR1" },
    { CS_ID_GRABBED_BY_MORPHIX, "MO_GR1" },    { CS_ID_GRABBED_BY_NIIKI, "NI_GR1" },
    { CS_ID_GRABBED_BY_SCARLET, "SC_GR1" },    { CS_ID_GRABBED_BY_SONORK, "SO_GR1" },
    { CS_ID_GRABBED_BY_ZENMURON, "ZE_GR1" },   { CS_ID_COGRABBED_BY_AARON, "ARCGR1" },
    { CS_ID_COGRABBED_BY_DEMITRON, "DMCGR1" }, { CS_ID_COGRABBED_BY_DEMONICA, "DOCGR1" },
    { CS_ID_COGRABBED_BY_EVE, "EVCGR1" },      { CS_ID_COGRABBED_BY_GORE, "GECGR1" },
    { CS_ID_COGRABBED_BY_GORE, "GOCGR1" },     { CS_ID_COGRABBED_BY_MORPHIX, "MOCGR1" },
    { CS_ID_COGRABBED_BY_NIIKI, "NICGR1" },    { CS_ID_COGRABBED_BY_SCARLET, "SCCGR1" },
    { CS_ID_COGRABBED_BY_SONORK, "SOCGR1" },   { CS_ID_COGRABBED_BY_ZENMURON, "ZECGR1" },
};

s16 D_8004B9FC[] = { 187, 188, 189, 190, 191, 191, 192, 193, 194, 195, 196 };

ColorRGBA D_8004BA14[] = { { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 },
                           { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 },
                           { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 } };

Unk_8004BA6C *D_8004BA40[] = { NULL,        &D_8005254C, &D_80052688, &D_80052788, NULL,       NULL,
                               &D_8005287C, NULL,        NULL,        NULL,        &D_80052C3C };

Unk_8004BA6C *D_8004BA6C[] = { NULL,        &D_80052560, &D_80052664, NULL, &D_800523FC, NULL,
                               &D_80052890, NULL,        NULL,        NULL, NULL };

Vec4s D_8004BA98[] = {
    { 0, 0, 27 },  // Aaron
    { 0, 0, 58 },  // Demitron
    { 0, 0, 100 }, // Demonica
    { 0, 0, 50 },  // Eve
    { 0, 0, 18 },  // Gore
    { 0, 0, -1 },  // Gorm (CUT)
    { 0, 0, 0 },   // Morphix
    { 26, 0, 44 }, // Niiki
    { 0, 0, 0 },   // Scarlet
    { 0, 0, 0 },   // Sonork
    { -3, 0, -3 }, // Zenmuron
};

Vec4s D_8004BAF0[] = {
    { 0, 0, 0 },    // Aaron
    { 0, 0, 21 },   // Demitron
    { 31, 0, 140 }, // Demonica
    { -38, 0, 4 },  // Eve
    { 26, 0, 85 },  // Gore
    { 0, 0, -1 },   // Gorm (CUT)
    { -7, 0, -22 }, // Morphix
    { 26, 0, 16 },  // Niiki
    { 0, 0, -1 },   // Scarlet
    { 13, 0, 4 },   // Sonork
    { -3, 0, -3 },  // Zenmuron
};

GameMode gGameModes[] = {
    { run_main_menu_mode, 9, 0, { 0, 0, 0, 0 }, { 40, 32, 40, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_options_mode, 9, 0, { 0, 0, 0, 0 }, { 40, 32, 40, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_menu_control_mode,
      9,
      0,
      { 0, 0, 0, 0 },
      { 40, 32, 40, 0 },
      630,
      1000,
      &gDefaultLighting,
      { 192, 192, 192, 0 } },
    { run_menu_rank_mode, 9, 0, { 0, 0, 0, 0 }, { 40, 32, 40, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_menu_stats_mode,
      9,
      0,
      { 0, 0, 0, 0 },
      { 40, 32, 40, 0 },
      630,
      1000,
      &gDefaultLighting,
      { 192, 192, 192, 0 } },
    { run_player_selection_mode,
      2,
      0,
      { 0, 0, 0, 0 },
      { 40, 32, 40, 0 },
      630,
      1000,
      &gDefaultLighting,
      { 192, 192, 192, 0 } },
    { run_battle_aaron_mode,
      11,
      0,
      { 0, 0, 0, 0 },
      { 113, 108, 97, 0 },
      945,
      1000,
      &gBattleAaronLighting,
      { 69, 55, 88, 0 } },
    { run_battle_demitron_mode,
      11,
      0,
      { 113, 65, 59, 0 },
      { 234, 89, 69, 0 },
      850,
      1000,
      &gBattleDemitronLighting,
      { 84, 26, 25, 0 } },
    { run_battle_demonica_mode,
      11,
      0,
      { 19, 32, 28, 0 },
      { 4, 4, 14, 0 },
      945,
      1000,
      &gBattleDemonicaLighting,
      { 36, 77, 54, 0 } },
    { run_battle_eve_mode,
      11,
      0,
      { 84, 124, 190, 0 },
      { 27, 62, 21, 0 },
      945,
      1000,
      &gBattleEveLighting,
      { 23, 25, 27, 0 } },
    { run_battle_gore_mode,
      11,
      0,
      { 67, 107, 186, 0 },
      { 40, 32, 40, 0 },
      945,
      1000,
      &gBattleGoreLighting,
      { 62, 52, 74, 0 } },
    { run_battle_aaron_mode,
      11,
      0,
      { 61, 105, 194, 0 },
      { 40, 32, 40, 0 },
      945,
      1000,
      &gBattleAaronLighting,
      { 50, 60, 70, 0 } },
    { run_battle_morphix_mode,
      11,
      0,
      { 42, 31, 70, 0 },
      { 56, 43, 85, 0 },
      945,
      1000,
      &gBattleMorphixLighting,
      { 50, 60, 70, 0 } },
    { run_battle_niiki_mode,
      11,
      0,
      { 13, 14, 14, 0 },
      { 26, 20, 18, 0 },
      850,
      1000,
      &gBattleNiikiLighting,
      { 63, 29, 33, 0 } },
    { run_battle_scarlet_mode,
      11,
      0,
      { 36, 32, 30, 0 },
      { 123, 94, 69, 0 },
      945,
      1000,
      &gBattleScarletLighting,
      { 53, 43, 52, 0 } },
    { run_battle_sonork_mode,
      11,
      0,
      { 112, 105, 109, 0 },
      { 114, 101, 81, 0 },
      945,
      1000,
      &gBattleSonorkLighting,
      { 56, 46, 34, 0 } },
    { run_battle_zenmuron_mode,
      11,
      0,
      { 2, 7, 16, 0 },
      { 1, 6, 14, 0 },
      945,
      1000,
      &gBattleZenmuronLighting,
      { 8, 16, 69, 0 } },
    { run_17_mode, 11, 0, { 61, 105, 194, 0 }, { 40, 32, 40, 0 }, 945, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_intro_aaron_mode,
      11,
      0,
      { 0, 0, 0, 0 },
      { 113, 108, 97, 0 },
      945,
      1000,
      &gBattleAaronLighting,
      { 69, 55, 88, 0 } },
    { run_intro_demitron_mode,
      11,
      0,
      { 113, 65, 59, 0 },
      { 234, 89, 69, 0 },
      850,
      1000,
      &gBattleDemitronLighting,
      { 84, 26, 25, 0 } },
    { run_intro_demonica_mode,
      11,
      0,
      { 19, 32, 28, 0 },
      { 4, 4, 14, 0 },
      945,
      1000,
      &gBattleDemonicaLighting,
      { 36, 77, 54, 0 } },
    { run_intro_eve_mode,
      11,
      0,
      { 84, 124, 190, 0 },
      { 27, 62, 21, 0 },
      945,
      1000,
      &gBattleEveLighting,
      { 23, 25, 27, 0 } },
    { run_intro_gore_mode,
      11,
      0,
      { 61, 105, 194, 0 },
      { 40, 32, 40, 0 },
      945,
      1000,
      &gBattleGoreLighting,
      { 62, 52, 74, 0 } },
    { run_intro_gore_mode,
      11,
      0,
      { 67, 107, 186, 0 },
      { 40, 32, 40, 0 },
      945,
      1000,
      &gBattleAaronLighting,
      { 50, 60, 70, 0 } },
    { run_intro_morphix_mode,
      11,
      0,
      { 42, 31, 70, 0 },
      { 56, 43, 85, 0 },
      945,
      1000,
      &gBattleMorphixLighting,
      { 50, 60, 70, 0 } },
    { run_intro_niiki_mode,
      11,
      0,
      { 13, 14, 14, 0 },
      { 26, 20, 18, 0 },
      850,
      1000,
      &gBattleNiikiLighting,
      { 63, 29, 33, 0 } },
    { run_intro_scarlet_mode,
      11,
      0,
      { 36, 32, 30, 0 },
      { 123, 94, 69, 0 },
      945,
      1000,
      &gBattleScarletLighting,
      { 53, 43, 52, 0 } },
    { run_intro_sonork_mode,
      11,
      0,
      { 112, 105, 109, 0 },
      { 114, 101, 81, 0 },
      945,
      1000,
      &gBattleSonorkLighting,
      { 56, 46, 34, 0 } },
    { run_intro_zenmuron_mode,
      11,
      0,
      { 2, 7, 16, 0 },
      { 1, 6, 14, 0 },
      945,
      1000,
      &gBattleZenmuronLighting,
      { 8, 16, 69, 0 } },
    { run_29_mode,
      11,
      0,
      { 112, 105, 109, 0 },
      { 114, 101, 81, 0 },
      945,
      1000,
      &gBattleSonorkLighting,
      { 56, 46, 34, 0 } },
    { run_30_mode,
      11,
      0,
      { 113, 65, 59, 0 },
      { 234, 89, 69, 0 },
      850,
      1000,
      &gBattleDemitronLighting,
      { 84, 26, 25, 0 } },
    { run_31_mode, 11, 0, { 0, 0, 0, 0 }, { 0, 4, 10, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_intro_mode, 11, 0, { 0, 0, 0, 0 }, { 0, 4, 10, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_logo_mode, 11, 0, { 0, 0, 0, 0 }, { 0, 4, 10, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_34_mode,
      11,
      0,
      { 113, 65, 59, 0 },
      { 234, 89, 69, 0 },
      850,
      1000,
      &gBattleDemitronLighting,
      { 84, 26, 25, 0 } },
    { run_35_mode,
      11,
      0,
      { 113, 65, 59, 0 },
      { 234, 89, 69, 0 },
      850,
      1000,
      &gBattleDemitronLighting,
      { 84, 26, 25, 0 } },
    { run_36_mode, 11, 0, { 0, 0, 0, 0 }, { 0, 4, 10, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } },
    { run_37_mode, 11, 0, { 0, 0, 0, 0 }, { 0, 4, 10, 0 }, 630, 1000, &gDefaultLighting, { 192, 192, 192, 0 } }
};

HudMessage gGeneralMessages[] = {
    { "battle", 10, 20, func_80015D60, 0 },   { "chal", 60, 20, func_80015D60, 3 },
    { "cont", 240, 20, func_80015D60, 1 },    { "ctdown", 0, 255, func_80016144, -1 },
    { "draw", 0, 20, func_80015CD8, 4 },      { "finalrd", 30, 20, func_80015D60, -1 },
    { "round", 30, 20, func_80015E24, -1 },   { "gameover", 0, 20, func_80015CD8, 2 },
    { "cont", 240, 20, func_80015D60, 1 },    { "pause", 0, 20, func_8002A1F0, -1 },
    { "timeover", 0, 20, func_80015D60, -1 }, { "perfect", 0, 80, func_80015D60, 6 },
};

HudMessage gWinMessages[] = {
    { "aarowin", 110, 20, func_80015CD8, 5 }, { "demiwin", 110, 20, func_80015CD8, 5 },
    { "demowin", 110, 20, func_80015CD8, 5 }, { "evewin", 110, 20, func_80015CD8, 5 },
    { "gorewin", 110, 20, func_80015CD8, 5 }, { "gorewin", 110, 20, func_80015CD8, 5 },
    { "morpwin", 100, 20, func_80015CD8, 5 }, { "niikwin", 110, 20, func_80015CD8, 5 },
    { "scarwin", 110, 20, func_80015CD8, 5 }, { "sonowin", 110, 20, func_80015CD8, 5 },
    { "zenmwin", 110, 20, func_80015CD8, 5 },
};

u32 D_8004C178[] = { 430, 430, 430, 430, 430, 430, 430, 530, 470, 430, 430 };
u32 D_8004C1A4[] = { 500, 450, 450, 450, 450, 450, 450, 370, 370, 450, 450 };

s16 gMaxRounds = 3;
s16 gBattleDuration = 2;

u8 D_8004C1D8[] = { 6, 7, 9, 6, 5, 5, 6, 8, 5, 8, 5 };

s16 gDifficulty = DIFFICULTY_NORMAL;

#define BHV_KEEP                                                                                       \
    (PLAYER_FLAG_NOT_FACING_OPP | PLAYER_FLAG_200 | PLAYER_FLAG_GAMEPLAY_LOCKED | PLAYER_FLAG_200000 | \
     PLAYER_FLAG_400000 | PLAYER_FLAG_SHOOTED)
#define BHV_KEEP_2                                                                                     \
    (PLAYER_FLAG_NOT_FACING_OPP | PLAYER_FLAG_200 | PLAYER_FLAG_GAMEPLAY_LOCKED | PLAYER_FLAG_200000 | \
     PLAYER_FLAG_400000 | PLAYER_FLAG_800000 | PLAYER_FLAG_SHOOTED)

Behavior gBehaviorTable[] = {
    /* BHV_IDLE */ { PLAYER_FLAG_10 | PLAYER_FLAG_40000, anim_loop, action_idle, NULL, BHV_KEEP },
    /* BHV_STOP_WALK */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION | PLAYER_FLAG_40000, task_end, action_stop_walking, NULL, BHV_KEEP },
    /* BHV_DASH */ { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION, anim_advance, action_dash, NULL, BHV_KEEP },
    /* BHV_WALK */ { PLAYER_FLAG_10 | PLAYER_FLAG_40000, anim_loop, action_walk, NULL, BHV_KEEP_2 },
    /* BHV_UNUSED_4 */ { PLAYER_FLAG_40000, anim_loop, task_end, NULL, BHV_KEEP },
    /* BHV_RUN */ { PLAYER_FLAG_40000, anim_loop, action_run, NULL, BHV_KEEP },
    /* BHV_JUMP */ { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION, anim_advance, action_jump, NULL, BHV_KEEP },
    /* BHV_CROUCH */ { PLAYER_FLAG_10 | PLAYER_FLAG_40000, anim_loop, action_crouch, NULL, BHV_KEEP_2 },
    /* BHV_CROUCH_EXIT */
    { PLAYER_FLAG_10 | PLAYER_FLAG_REVERSE | PLAYER_FLAG_ACTION, anim_reverse, task_end, NULL, BHV_KEEP_2 },
    /* BHV_CROUCH_RESTART */ { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION, player_anim_func_3, task_end, NULL, BHV_KEEP },
    /* BHV_BLOCK */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION | PLAYER_FLAG_800000, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_CROUCH_ABORT */
    { PLAYER_FLAG_ACTION | PLAYER_FLAG_REVERSE_2, anim_reverse, task_end, NULL, BHV_KEEP_2 },
    /* BHV_SB_REABORT */ { 0, player_anim_func_3, task_end, NULL, BHV_KEEP },
    /* BHV_GRAB */ { PLAYER_FLAG_10, anim_advance, action_grab, NULL, BHV_KEEP },
    /* BHV_GRABBED */
    { PLAYER_FLAG_10 | PLAYER_FLAG_80 | PLAYER_FLAG_ACTION | PLAYER_FLAG_2000 | PLAYER_FLAG_1000000, anim_advance,
      action_grabbed, NULL, BHV_KEEP },
    /* BHV_CO_GRABBED */ { 0, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_CUTSCENE */ { PLAYER_FLAG_40000, anim_loop, task_end, NULL, BHV_KEEP },
    /* BHV_KEY_UP */ { PLAYER_FLAG_40000, anim_loop, task_end, NULL, BHV_KEEP },
    /* BHV_ATTACK */ { 0, anim_advance, action_none, NULL, BHV_KEEP },
    /* BHV_DAMAGED */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION | PLAYER_FLAG_2000, anim_advance, action_damaged, NULL, BHV_KEEP },
    /* BHV_END */ { PLAYER_FLAG_ACTION | PLAYER_FLAG_40000, anim_play_once, task_end, NULL, BHV_KEEP },
    /* BHV_LYING_DOWN */
    { PLAYER_FLAG_10 | PLAYER_FLAG_80 | PLAYER_FLAG_40000, anim_loop, task_end, NULL, BHV_KEEP },
    /* BHV_FALL_FORWARD */ { PLAYER_FLAG_40000, anim_pingpong_forward, task_end, NULL, BHV_KEEP },
    /* BHV_DMG_JUMP */ { PLAYER_FLAG_ACTION | PLAYER_FLAG_2000, anim_play_once, player_trans_func_12, NULL, BHV_KEEP },
    /* BHV_TIMEOUT_TO_IDLE */ { 0, task_end, action_animation_end, NULL, BHV_KEEP },
    /* BHV_BODY_SLAM */ { PLAYER_FLAG_ACTION, anim_advance, task_end, player_check_func_1, BHV_KEEP },
    /* BHV_KNOCKBACK */ { PLAYER_FLAG_ACTION | PLAYER_FLAG_2000, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_TURN_TO_OPPONENT */
    { PLAYER_FLAG_NOT_FACING_OPP | PLAYER_FLAG_10 | PLAYER_FLAG_ACTION, anim_advance, task_end, player_check_func_2,
      BHV_KEEP },
    /* BHV_PROJECTILE_INIT */ { PLAYER_FLAG_10, anim_advance, player_action_init_projectiles, NULL, BHV_KEEP },
    /* BHV_INTRO_PROJECTILE */ { PLAYER_FLAG_ACTION, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_ROLL_VARIOUS */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION, anim_advance, player_trans_func_14, player_check_func_3, BHV_KEEP },
    /* BHV_ROLL */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION, anim_advance, player_trans_func_14, player_check_func_4, BHV_KEEP },
    /* BHV_ROLL_2 */ { PLAYER_FLAG_10, anim_advance, player_trans_func_14, player_check_func_3, BHV_KEEP },
    /* BHV_SIDE_STEP */ { PLAYER_FLAG_10, anim_advance, player_trans_func_14, player_check_func_4, BHV_KEEP },
    /* BHV_SIDE_STEP_2 */ { PLAYER_FLAG_10, anim_advance, player_trans_func_15, player_check_func_2, BHV_KEEP },
    /* BHV_TURN_AROUND */ { PLAYER_FLAG_10 | PLAYER_FLAG_8000, anim_advance, action_none, NULL, BHV_KEEP },
    /* BHV_NEUTRAL_ADVANCE */
    { PLAYER_FLAG_10, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_NEUTRAL_PINGPONG */
    { PLAYER_FLAG_10 | PLAYER_FLAG_40000, anim_pingpong_forward, task_end, NULL, BHV_KEEP },
    /* BHV_NEUTRAL_LOOP_2 */
    { PLAYER_FLAG_10 | PLAYER_FLAG_40000, anim_loop, task_end, NULL, BHV_KEEP },
    /* BHV_COCOMBO_P4 */
    { PLAYER_FLAG_10 | PLAYER_FLAG_8000, anim_advance, player_trans_func_16, player_check_func_5, BHV_KEEP },
    /* BHV_COGRABBED */
    { PLAYER_FLAG_10 | PLAYER_FLAG_80 | PLAYER_FLAG_ACTION | PLAYER_FLAG_2000 | PLAYER_FLAG_10000 | PLAYER_FLAG_1000000,
      anim_advance, player_trans_func_22, player_check_func_6, BHV_KEEP },
    /* BHV_COCOMBO */
    { PLAYER_FLAG_10, anim_advance, player_trans_func_17, player_check_func_5, BHV_KEEP },
    /* BHV_GET_UP_STAND */
    { PLAYER_FLAG_80, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_GET_UP_ACT */
    { PLAYER_FLAG_ACTION | PLAYER_FLAG_2000, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_LYING_DOWN_FD */
    { PLAYER_FLAG_10 | PLAYER_FLAG_80 | PLAYER_FLAG_40000, anim_play_once, task_end, NULL, BHV_KEEP },
    /* BHV_CHARGE */
    { PLAYER_FLAG_8000, anim_advance, task_end, NULL, BHV_KEEP },
    /* BHV_VICTORY */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION | PLAYER_FLAG_8000 | PLAYER_FLAG_20000, anim_advance, task_end, NULL,
      BHV_KEEP },
    /* BHV_VICTORY_IDLE */
    { PLAYER_FLAG_10 | PLAYER_FLAG_8000 | PLAYER_FLAG_20000 | PLAYER_FLAG_40000, anim_loop, task_end, NULL, BHV_KEEP },
    /* BHV_VICTORY_UNIQUE */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION | PLAYER_FLAG_8000 | PLAYER_FLAG_20000, anim_advance, player_trans_func_18,
      NULL, BHV_KEEP },
    /* BHV_KNOCKDOWN_GETUP */
    { PLAYER_FLAG_10 | PLAYER_FLAG_80 | PLAYER_FLAG_ACTION | PLAYER_FLAG_2000, anim_advance, action_grabbed, NULL,
      BHV_KEEP },
    /* BHV_CROUCH_BLOCK */
    { PLAYER_FLAG_ACTION | PLAYER_FLAG_40000, anim_play_once, task_end, NULL, BHV_KEEP },
    /* BHV_SIDE_STEP_COMBAT */
    { PLAYER_FLAG_10, anim_advance, player_trans_func_14, NULL, BHV_KEEP },
    /* BHV_COMBO_BREAK */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION | PLAYER_FLAG_40000, anim_advance, task_end, player_check_func_7, BHV_KEEP },
    /* BHV_PROJECTILE */
    { PLAYER_FLAG_ACTION, anim_advance, player_action_init_projectiles, player_check_func_8, BHV_KEEP_2 },
    /* BHV_GRAB_EXTEND */
    { PLAYER_FLAG_10 | PLAYER_FLAG_1000000, anim_advance, player_trans_func_19, NULL, BHV_KEEP },
    /* BHV_DEMI_TRANSFORM */
    { PLAYER_FLAG_ACTION | PLAYER_FLAG_20000 | PLAYER_FLAG_1000000, anim_advance, player_trans_func_20, NULL,
      BHV_KEEP },
    /* BHV_DEMI_DEATH */
    { PLAYER_FLAG_10, anim_play_once, player_action_init_projectiles, NULL, BHV_KEEP },
    /* BHV_ROLL_BACKWARD */
    { PLAYER_FLAG_ACTION, anim_advance, player_trans_func_21, player_check_func_3, BHV_KEEP },
    /* BHV_ROLL_NO_FLAGS */
    { PLAYER_FLAG_ACTION, anim_advance, player_trans_func_21, player_check_func_4, BHV_KEEP },
    /* BHV_COGRABBED_A_FUNC22 */
    { PLAYER_FLAG_10 | PLAYER_FLAG_80 | PLAYER_FLAG_ACTION | PLAYER_FLAG_2000 | PLAYER_FLAG_1000000, anim_advance,
      player_trans_func_22, NULL, BHV_KEEP },
    /* BHV_COGRABBED_A_CHECK6 */
    { PLAYER_FLAG_10 | PLAYER_FLAG_80 | PLAYER_FLAG_ACTION | PLAYER_FLAG_2000 | PLAYER_FLAG_10000 | PLAYER_FLAG_1000000,
      anim_advance, task_end, player_check_func_6, BHV_KEEP },
    /* BHV_AI_ROLL */
    { PLAYER_FLAG_10 | PLAYER_FLAG_8000, anim_advance, player_trans_func_14, NULL, BHV_KEEP },
    /* BHV_RUNNING_SLIDE */
    { 0, anim_advance, player_trans_func_23, NULL, BHV_KEEP },
    /* BHV_JUMP_DOWN_ATTACK */
    { PLAYER_FLAG_10 | PLAYER_FLAG_ACTION | PLAYER_FLAG_20000 | PLAYER_FLAG_40000, anim_advance, player_trans_func_24,
      NULL, BHV_KEEP },
    /* BHV_DEFEAT */
    { PLAYER_FLAG_8000, anim_loop, player_trans_func_25, NULL, BHV_KEEP },
    /* BHV_DEFEAT_TAR */
    { 0, anim_play_once, player_trans_func_26, NULL, BHV_KEEP },
    /* BHV_DEFEAT_INTRO */
    { 0, anim_loop, player_trans_func_27, NULL, BHV_KEEP },
    /* BHV_HOP_PART_1 */
    { PLAYER_FLAG_ACTION, anim_advance, player_trans_func_28, NULL, BHV_KEEP },
    /* BHV_CROUCH_BLOCK_ABORT */
    { PLAYER_FLAG_ACTION | PLAYER_FLAG_REVERSE_2 | PLAYER_FLAG_8000000, anim_reverse, task_end, NULL, BHV_KEEP_2 },
};

/* .bss */
s32 D_800AA470[4];
s32 D_800AA480;
Player gPlayers[2];
Player12 gBattleSettings[2];
u8 D_800B6350[2][11];
CharacterStats D_800B6368[NUM_CHARACTERS];