#include "common.h"

void title_screen(void);
void options_menu(void);
void options_controller(void);
void options_score(void);
void options_stage(void);
void char_select_init(void);
void arena_stage_02(void);
void arena_stage_03(void);
void arena_stage_04(void);
void arena_stage_05(void);
void arena_stage_01(void);
void arena_stage_06(void);
void arena_stage_07(void);
void arena_stage_08(void);
void arena_stage_09(void);
void arena_stage_10(void);
void arena_stage_default(void);
void intro_aaro(void);
void intro_demi(void);
void intro_demo(void);
void intro_eve(void);
void intro_gore(void);
void intro_morp(void);
void intro_niik(void);
void intro_scar(void);
void intro_sono(void);
void intro_zenm(void);
void boss_sono(void);
void boss_demi(void);
void ending_char(void);
void title_intro(void);
void title_logo(void);
void ending_generic(void);
void closing_cutscene(void);
void credits_screen(void);
void ending_easywin(void);

void match_anim_play_fadeout(Object *obj);
void match_attract_anim(Object *obj);
void move_apply_vel(Object *);
void hit_dust_skid_init(Object *);
void hit_combo_mid_startup(Object *);
void x_19fed2ac(Object *);
void x_56d15e8a(Object *);
void hit_delay_ai_counter(Object *);
void hit_land_set_flag(Object *);
void hit_dust_skid_alt_init(Object *);
void move_state_change(Object *);
void hit_combo_routing(Object *);
void hit_rebound_spawn(Object *);
void hit_combo_break_1(Object *);
void hit_combo_counter_attack(Object *);
void move_count_up(Object *);
void move_osc_down(Object *);
void hit_knockback_launch(Object *);
void move_exec_current(Object *);
u8 hit_check_opp_blockstun(Object *);
void hit_clear_flag_delayed(Object *);
u8 hit_check_button_same(Object *);
u8 hit_check_button_opposite(Object *);
void hit_cam_rotate_to_opponent(Object *);
void hit_combo_startup_projectile(Object *);
u8 hit_check_opp_grabbing(Object *);
u8 hit_push_opponent_away(Object *);
void hit_combo_startup_alt(Object *);
void hit_projectile_or_end(Object *);
u8 hit_check_opp_punishable(Object *);
void hit_combo_init(Object *);
u8 x_82bfe825(Object *);
void hit_combo_damage_vfx(Object *);
void hit_projectile_zenmuron(Object *);
void hit_combo_spin_opponent(Object *);
void hit_combo_unblockable_check(Object *);
void hit_set_flag_on_frame(Object *);
void hit_ai_juggle_dispatch(Object *);
void hit_delay_crossup_move(Object *);
void hit_delay_ai_move(Object *);
void hit_face_opponent_late(Object *);
void match_anim_play_fade(Object *);
void match_model_fadeout(Object *);
void results_init(Object *);

extern x_448872e8 D_800523FC;
extern x_448872e8 D_8005254C;
extern x_448872e8 D_80052560;
extern x_448872e8 D_80052664;
extern x_448872e8 D_80052688;
extern x_448872e8 D_80052788;
extern x_448872e8 D_8005287C;
extern x_448872e8 D_80052890;
extern x_448872e8 D_80052C3C;

extern x_87049dce D_80052220;
extern x_87049dce D_80052420;
extern x_87049dce D_80052580;
extern x_87049dce D_800526B0;
extern x_87049dce D_80052330;
extern x_87049dce D_800527A0;
extern x_87049dce D_800528B0;
extern x_87049dce D_80052990;
extern x_87049dce D_80052A60;
extern x_87049dce D_80052B30;

extern x_2bb4cf6f sDefaultLights;

s32 D_8004A5C0[] = { 0, 0, 0, 0 };

x_88f11482 D_8004A5D0[] = {
    { 60, 51, 0, 0 }, { 69, 51, 0, 0 }, { 69, 51, 0, 0 }, { 42, 51, 0, 0 }, { 51, 51, 0, 0 }, { 51, 51, 0, 0 },
    { 65, 51, 0, 0 }, { 47, 51, 0, 0 }, { 60, 51, 0, 0 }, { 60, 51, 0, 0 }, { 70, 51, 0, 0 },
};

x_88f11482 D_8004A680[] = {
    { 274, 51, 0, 0 }, { 261, 51, 0, 0 }, { 261, 51, 0, 0 }, { 287, 51, 0, 0 }, { 282, 51, 0, 0 }, { 285, 51, 0, 0 },
    { 264, 51, 0, 0 }, { 285, 51, 0, 0 }, { 267, 51, 0, 0 }, { 271, 51, 0, 0 }, { 262, 51, 0, 0 },
};

s16 D_8004A730[] = {
    175, 175, 150, 170, 160, 175, 175, 130, 175, 175, 175,
};

s16 D_8004A748[] = {
    400, 400, 250, 480, 550, 400, 900, 400, 400, 1000, 400,
};

x_40f23fab D_8004A760[] = {
    { { 18, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004A8DC[] = {
    { { 22, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { 18, -1, 0, 0 }, 18 },   { { 19, -1, 0, 0 }, 19 },
    { { 20, -1, 0, 0 }, 20 }, { { 21, -1, 0, 0 }, 21 }, { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004AAA8[] = {
    { { 25, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },     { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },     { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },     { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 },   { { 14, -1, 0, 0 }, 14 }, { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 },   { { 18, -1, 0, 0 }, 18 }, { { 19, -1, 0, 0 }, 19 },
    { { 20, -1, 0, 0 }, 20 }, { { 21, -1, 0, 0 }, 21 },   { { 22, -1, 0, 0 }, 22 }, { { 23, -1, 0, 0 }, 23 },
    { { 24, -1, 0, 0 }, 24 }, { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004ACB0[] = {
    { { 16, 0, -1, 0 }, -1 },   { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },     { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },     { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 },   { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 }, { { 15, -1, 0, 0 }, 15 },
    { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004AE04[] = {
    { { 15, 0, -1, 0 }, -1 },  { { 1, -1, 0, 0 }, -1 },    { { 2, -1, 0, 0 }, -2 }, { { 4, 3, -1, 0 }, 3 },
    { { 5, -1, 0, 0 }, 5 },    { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },  { { 8, -1, 0, 0 }, 8 },
    { { 11, 10, 9, -1 }, 11 }, { { 14, 13, 12, -1 }, 14 }, { { -1, -1, 0, 0 }, 0 },
};

x_40f23fab D_8004AEE0[] = {
    { { 18, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004B05C[] = {
    { { 22, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { 18, -1, 0, 0 }, 18 },   { { 19, -1, 0, 0 }, 19 },
    { { 20, -1, 0, 0 }, 20 }, { { 21, -1, 0, 0 }, 21 }, { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004B228[] = {
    { { 15, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 }, { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004B368[] = {
    { { 18, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },     { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },     { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 },   { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 },   { { 15, -1, 0, 0 }, 15 },
    { { 16, -1, 0, 0 }, 16 }, { { 17, -1, 0, 0 }, 17 }, { { -1, -1, -1, -1 }, -1 },
};

x_40f23fab D_8004B4E4[] = {
    { { 15, 0, -1, 0 }, -1 }, { { 1, -1, 0, 0 }, 1 },   { { 2, -1, 0, 0 }, 2 },   { { 3, -1, 0, 0 }, 3 },
    { { 4, -1, 0, 0 }, 4 },   { { 5, -1, 0, 0 }, 5 },   { { 6, -1, 0, 0 }, 6 },   { { 7, -1, 0, 0 }, 7 },
    { { 8, -1, 0, 0 }, 8 },   { { 9, -1, 0, 0 }, 9 },   { { 10, -1, 0, 0 }, 10 }, { { 11, -1, 0, 0 }, 11 },
    { { 12, -1, 0, 0 }, 12 }, { { 13, -1, 0, 0 }, 13 }, { { 14, -1, 0, 0 }, 14 }, { { -1, -1, -1, -1 }, -1 },
};

x_2bb4cf6f D_8004B624 = { { { { 255, 255, 255, 255 }, 0, -101, -126 }, { { 0, 0, 0, 0 }, 73, -73, -73 } } };
x_2bb4cf6f D_8004B644 = { { { { 255, 254, 254, 255 }, 0, -126, -86 }, { { 255, 59, 27, 0 }, 20, 126, 0 } } };
x_2bb4cf6f D_8004B664 = { { { { 191, 112, 96, 255 }, -1, -126, -55 }, { { 30, 255, 132, 0 }, 5, 127, 191 } } };
x_2bb4cf6f D_8004B684 = { { { { 255, 255, 255, 255 }, -1, -127, -128 }, { { 91, 73, 112, 0 }, 0, 127, 63 } } };
x_2bb4cf6f D_8004B6A4 = { { { { 255, 255, 255, 255 }, 0, -123, -107 }, { { 76, 60, 98, 0 }, 16, 127, -32 } } };
x_2bb4cf6f D_8004B6C4 = { { { { 255, 210, 255, 0 }, 11, -115, 117 }, { { 100, 120, 150, 0 }, -126, -121, 88 } } };
x_2bb4cf6f D_8004B6E4 = { { { { 255, 228, 213, 0 }, 6, -125, -127 }, { { 33, 36, 68, 0 }, 44, 91, 98 } } };
x_2bb4cf6f D_8004B704 = { { { { 255, 213, 186, 0 }, 6, -125, -127 }, { { 51, 42, 83, 0 }, 44, 91, 98 } } };
x_2bb4cf6f D_8004B724 = { { { { 255, 255, 255, 0 }, 6, -127, -128 }, { { 82, 50, 40, 0 }, -107, 123, 53 } } };
x_2bb4cf6f D_8004B744 = { { { { 219, 228, 255, 0 }, 11, -115, -117 }, { { 231, 39, 22, 0 }, -126, -121, 88 } } };
x_2bb4cf6f D_8004B764 = { { { { 255, 254, 254, 255 }, 0, -126, -86 }, { { 255, 59, 27, 0 }, 20, 126, 0 } } };
x_2bb4cf6f D_8004B784 = { { { { 191, 112, 96, 255 }, -1, -126, -55 }, { { 30, 255, 132, 0 }, 5, 127, 191 } } };

x_aece7675 D_8004B7A4 = { "aaro", NULL, 0, x_9d442987, D_8004A760 };
x_aece7675 D_8004B7B4 = { "demi", NULL, 0, x_9d442987, D_8004A8DC };
x_aece7675 D_8004B7C4 = { "demo", NULL, 0, x_9d442987, D_8004AAA8 };
x_aece7675 D_8004B7D4 = { "eve", NULL, 0, x_9d442987, D_8004ACB0 };
x_aece7675 D_8004B7E4 = { "gore", NULL, 0, x_9d442987, D_8004AE04 };
x_aece7675 D_8004B7F4 = { "morp", NULL, 0, x_9d442987, D_8004AEE0 };
x_aece7675 D_8004B804 = { "niik", NULL, 0, x_9d442987, D_8004B05C };
x_aece7675 D_8004B814 = { "scar", NULL, 0, x_9d442987, D_8004B228 };
x_aece7675 D_8004B824 = { "sono", NULL, 0, x_9d442987, D_8004B368 };
x_aece7675 D_8004B834 = { "zenm", NULL, 0, x_9d442987, D_8004B4E4 };

x_e630c828 D_8004B844[] = {
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

x_f1ef2747 D_8004B8F4[] = {
    { 347, x_e63530c1 }, { 550, x_694e40b6 }, { 400, x_b2b1b96e }, { 430, x_3c7302ce },
    { 360, x_35aace93 }, { 430, x_ee946ac0 }, { 393, x_2b743d6c }, { 487, x_f756fc7a },
    { 430, x_e2a97731 }, { 400, x_386c4125 }, { 430, x_7d1ece0c },
};

x_f1ef2747 D_8004B920[] = { { 171, x_5e459866 }, { 250, x_43a34e27 }, { 369, x_6fb95bb3 }, { 400, x_d55dddfa },
                            { 488, x_df2f05e7 }, { 400, x_df2f05e7 }, { 483, x_03639beb }, { 400, x_3aacdec1 },
                            { 422, x_87d80e6c }, { 400, x_7408302b }, { 400, x_c55d4b86 } };

x_6dac5499 D_8004B94C[] = {
    { 167, "AR_GR1" }, { 168, "DM_GR1" }, { 169, "DO_GR1" }, { 170, "EV_GR1" }, { 171, "GE_GR1" }, { 171, "GO_GR1" },
    { 172, "MO_GR1" }, { 173, "NI_GR1" }, { 174, "SC_GR1" }, { 175, "SO_GR1" }, { 176, "ZE_GR1" }, { 177, "ARCGR1" },
    { 178, "DMCGR1" }, { 179, "DOCGR1" }, { 180, "EVCGR1" }, { 181, "GECGR1" }, { 181, "GOCGR1" }, { 182, "MOCGR1" },
    { 183, "NICGR1" }, { 184, "SCCGR1" }, { 185, "SOCGR1" }, { 186, "ZECGR1" },
};

s16 D_8004B9FC[] = { 187, 188, 189, 190, 191, 191, 192, 193, 194, 195, 196 };

x_6751d717 D_8004BA14[] = { { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 },
                            { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 },
                            { 255, 0, 0, 0 }, { 255, 0, 0, 0 }, { 255, 0, 0, 0 } };

x_448872e8 *D_8004BA40[] = { NULL,        &D_8005254C, &D_80052688, &D_80052788, NULL,       NULL,
                             &D_8005287C, NULL,        NULL,        NULL,        &D_80052C3C };

x_448872e8 *D_8004BA6C[] = { NULL,        &D_80052560, &D_80052664, NULL, &D_800523FC, NULL,
                             &D_80052890, NULL,        NULL,        NULL, NULL };

x_2758cdab D_8004BA98[] = {
    { 0, 0, 27 },  // Aaron
    { 0, 0, 58 },  // Demitron
    { 0, 0, 100 }, // Demonica
    { 0, 0, 50 },  // Eve
    { 0, 0, 18 },  // Gore
    { 0, 0, -1 },  // Character 5
    { 0, 0, 0 },   // Morphix
    { 26, 0, 44 }, // Niiki
    { 0, 0, 0 },   // Scarlet
    { 0, 0, 0 },   // Sonork
    { -3, 0, -3 }, // Zenmuron
};

x_2758cdab D_8004BAF0[] = {
    { 0, 0, 0 },    // Aaron
    { 0, 0, 21 },   // Demitron
    { 31, 0, 140 }, // Demonica
    { -38, 0, 4 },  // Eve
    { 26, 0, 85 },  // Gore
    { 0, 0, -1 },   // Character 5
    { -7, 0, -22 }, // Morphix
    { 26, 0, 16 },  // Niiki
    { 0, 0, -1 },   // Scarlet
    { 13, 0, 4 },   // Sonork
    { -3, 0, -3 },  // Zenmuron
};

ScreenProfile gScreenProfiles[] = {
    { title_screen, 9, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { options_menu, 9, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { options_controller, 9, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { options_score, 9, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { options_stage, 9, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { char_select_init, 2, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { arena_stage_02, 11, 0, 0, 0, 0, 0, 113, 108, 97, 0, 945, 1000, &D_8004B624, { 69, 55, 88, 0 } },
    { arena_stage_03, 11, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, { 84, 26, 25, 0 } },
    { arena_stage_04, 11, 0, 19, 32, 28, 0, 4, 4, 14, 0, 945, 1000, &D_8004B664, { 36, 77, 54, 0 } },
    { arena_stage_05, 11, 0, 84, 124, 190, 0, 27, 62, 21, 0, 945, 1000, &D_8004B684, { 23, 25, 27, 0 } },
    { arena_stage_01, 11, 0, 67, 107, 186, 0, 40, 32, 40, 0, 945, 1000, &D_8004B6A4, { 62, 52, 74, 0 } },
    { arena_stage_02, 11, 0, 61, 105, 194, 0, 40, 32, 40, 0, 945, 1000, &D_8004B624, { 50, 60, 70, 0 } },
    { arena_stage_06, 11, 0, 42, 31, 70, 0, 56, 43, 85, 0, 945, 1000, &D_8004B6C4, { 50, 60, 70, 0 } },
    { arena_stage_07, 11, 0, 13, 14, 14, 0, 26, 20, 18, 0, 850, 1000, &D_8004B6E4, { 63, 29, 33, 0 } },
    { arena_stage_08, 11, 0, 36, 32, 30, 0, 123, 94, 69, 0, 945, 1000, &D_8004B704, { 53, 43, 52, 0 } },
    { arena_stage_09, 11, 0, 112, 105, 109, 0, 114, 101, 81, 0, 945, 1000, &D_8004B724, { 56, 46, 34, 0 } },
    { arena_stage_10, 11, 0, 2, 7, 16, 0, 1, 6, 14, 0, 945, 1000, &D_8004B744, { 8, 16, 69, 0 } },
    { arena_stage_default, 11, 0, 61, 105, 194, 0, 40, 32, 40, 0, 945, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { intro_aaro, 11, 0, 0, 0, 0, 0, 113, 108, 97, 0, 945, 1000, &D_8004B624, { 69, 55, 88, 0 } },
    { intro_demi, 11, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, { 84, 26, 25, 0 } },
    { intro_demo, 11, 0, 19, 32, 28, 0, 4, 4, 14, 0, 945, 1000, &D_8004B664, { 36, 77, 54, 0 } },
    { intro_eve, 11, 0, 84, 124, 190, 0, 27, 62, 21, 0, 945, 1000, &D_8004B684, { 23, 25, 27, 0 } },
    { intro_gore, 11, 0, 61, 105, 194, 0, 40, 32, 40, 0, 945, 1000, &D_8004B6A4, { 62, 52, 74, 0 } },
    { intro_gore, 11, 0, 67, 107, 186, 0, 40, 32, 40, 0, 945, 1000, &D_8004B624, { 50, 60, 70, 0 } },
    { intro_morp, 11, 0, 42, 31, 70, 0, 56, 43, 85, 0, 945, 1000, &D_8004B6C4, { 50, 60, 70, 0 } },
    { intro_niik, 11, 0, 13, 14, 14, 0, 26, 20, 18, 0, 850, 1000, &D_8004B6E4, { 63, 29, 33, 0 } },
    { intro_scar, 11, 0, 36, 32, 30, 0, 123, 94, 69, 0, 945, 1000, &D_8004B704, { 53, 43, 52, 0 } },
    { intro_sono, 11, 0, 112, 105, 109, 0, 114, 101, 81, 0, 945, 1000, &D_8004B724, { 56, 46, 34, 0 } },
    { intro_zenm, 11, 0, 2, 7, 16, 0, 1, 6, 14, 0, 945, 1000, &D_8004B744, { 8, 16, 69, 0 } },
    { boss_sono, 11, 0, 112, 105, 109, 0, 114, 101, 81, 0, 945, 1000, &D_8004B724, { 56, 46, 34, 0 } },
    { boss_demi, 11, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, { 84, 26, 25, 0 } },
    { ending_char, 11, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { title_intro, 11, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { title_logo, 11, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { ending_generic, 11, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, { 84, 26, 25, 0 } },
    { closing_cutscene, 11, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, { 84, 26, 25, 0 } },
    { credits_screen, 11, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } },
    { ending_easywin, 11, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &sDefaultLights, { 192, 192, 192, 0 } }
};

x_3da8fdd8 x_dd2c4e91[] = {
    { "battle", 10, 20, match_anim_play_fadeout, 0 },   { "chal", 60, 20, match_anim_play_fadeout, 3 },
    { "cont", 240, 20, match_anim_play_fadeout, 1 },    { "ctdown", 0, 255, match_attract_anim, -1 },
    { "draw", 0, 20, match_anim_play_fade, 4 },         { "finalrd", 30, 20, match_anim_play_fadeout, -1 },
    { "round", 30, 20, match_model_fadeout, -1 },       { "gameover", 0, 20, match_anim_play_fade, 2 },
    { "cont", 240, 20, match_anim_play_fadeout, 1 },    { "pause", 0, 20, results_init, -1 },
    { "timeover", 0, 20, match_anim_play_fadeout, -1 }, { "perfect", 0, 80, match_anim_play_fadeout, 6 },
};

x_3da8fdd8 x_c2354b9b[] = {
    { "aarowin", 110, 20, match_anim_play_fade, 5 }, { "demiwin", 110, 20, match_anim_play_fade, 5 },
    { "demowin", 110, 20, match_anim_play_fade, 5 }, { "evewin", 110, 20, match_anim_play_fade, 5 },
    { "gorewin", 110, 20, match_anim_play_fade, 5 }, { "gorewin", 110, 20, match_anim_play_fade, 5 },
    { "morpwin", 100, 20, match_anim_play_fade, 5 }, { "niikwin", 110, 20, match_anim_play_fade, 5 },
    { "scarwin", 110, 20, match_anim_play_fade, 5 }, { "sonowin", 110, 20, match_anim_play_fade, 5 },
    { "zenmwin", 110, 20, match_anim_play_fade, 5 },
};

u32 D_8004C178[] = { 430, 430, 430, 430, 430, 430, 430, 530, 470, 430, 430 };
u32 D_8004C1A4[] = { 500, 450, 450, 450, 450, 450, 450, 370, 370, 450, 450 };

s16 x_adcfd05c = 3;
s16 x_c8356c60 = 2;

u8 D_8004C1D8[] = { 6, 7, 9, 6, 5, 5, 6, 8, 5, 8, 5 };

s16 x_028e5846 = x_c74743bd;

x_edf8d3f1 D_8004C1E8[] = {
    /* idle */ { 0x0040010, move_apply_vel, hit_dust_skid_init, NULL, 0x2700208 },
    /* unknown step */ { 0x0041010, task_remove_current, hit_combo_mid_startup, NULL, 0x2700208 },
    /* dash */ { 0x0001010, move_to_next, x_19fed2ac, NULL, 0x2700208 },
    /* step */ { 0x0040010, move_apply_vel, x_56d15e8a, NULL, 0x2F00208 },
    /* ----- */ { 0x0040000, move_apply_vel, task_remove_current, NULL, 0x2700208 },
    /* run */ { 0x0040000, move_apply_vel, hit_delay_ai_counter, NULL, 0x2700208 },
    /* jump */ { 0x0001010, move_to_next, hit_land_set_flag, NULL, 0x2700208 },
    /* crouch */ { 0x0040010, move_apply_vel, hit_dust_skid_alt_init, NULL, 0x2F00208 },
    /* crouch exit*/ { 0x0001810, move_delay_cb, task_remove_current, NULL, 0x2F00208 },
    /* crouch restart */ { 0x0001010, move_state_change, task_remove_current, NULL, 0x2700208 },
    /* stand block */ { 0x0801010, move_to_next, task_remove_current, NULL, 0x2700208 },
    /* crouch abort */ { 0x0005000, move_delay_cb, task_remove_current, NULL, 0x2F00208 },
    /* SB reabort */ { 0x0000000, move_state_change, task_remove_current, NULL, 0x2700208 },
    /* grab */ { 0x0000010, move_to_next, hit_combo_routing, NULL, 0x2700208 },
    /* grabbed */ { 0x1003090, move_to_next, hit_rebound_spawn, NULL, 0x2700208 },
    /* co-grabbed */ { 0x0000000, move_to_next, task_remove_current, NULL, 0x2700208 },
    /* intro */ { 0x0040000, move_apply_vel, task_remove_current, NULL, 0x2700208 },
    /* key up */ { 0x0040000, move_apply_vel, task_remove_current, NULL, 0x2700208 },
    /* various SP */ { 0x0000000, move_to_next, hit_combo_break_1, NULL, 0x2700208 },
    /* damaged */ { 0x0003010, move_to_next, hit_combo_counter_attack, NULL, 0x2700208 },
    /* end */ { 0x0041000, move_count_up, task_remove_current, NULL, 0x2700208 },
    /* lying down */ { 0x0040090, move_apply_vel, task_remove_current, NULL, 0x2700208 },
    { 0x0040000, move_osc_down, task_remove_current, NULL, 0x2700208 },
    /* dmg jump */ { 0x0003000, move_count_up, hit_knockback_launch, NULL, 0x2700208 },
    /* timeout to idle */ { 0x0000000, task_remove_current, move_exec_current, NULL, 0x2700208 },
    /* body slam */ { 0x0001000, move_to_next, task_remove_current, hit_check_opp_blockstun, 0x2700208 },
    { 0x0003000, move_to_next, task_remove_current, NULL, 0x2700208 },
    /* turn to opponent */ { 0x0001018, move_to_next, task_remove_current, hit_check_facing_away, 0x2700208 },
    { 0x0000010, move_to_next, projectile_init, NULL, 0x2700208 },
    /* intro projecti */ { 0x0001000, move_to_next, task_remove_current, NULL, 0x2700208 },
    /* various */ { 0x0001010, move_to_next, hit_clear_flag_delayed, hit_check_button_same, 0x2700208 },
    /* roll */ { 0x0001010, move_to_next, hit_clear_flag_delayed, hit_check_button_opposite, 0x2700208 },
    /* roll 2*/ { 0x0000010, move_to_next, hit_clear_flag_delayed, hit_check_button_same, 0x2700208 },
    /* side step */ { 0x0000010, move_to_next, hit_clear_flag_delayed, hit_check_button_opposite, 0x2700208 },
    /* side step 2 */ { 0x0000010, move_to_next, hit_cam_rotate_to_opponent, hit_check_facing_away, 0x2700208 },
    /* turn around */ { 0x0008010, move_to_next, hit_combo_break_1, NULL, 0x2700208 },
    { 0x0000010, move_to_next, task_remove_current, NULL, 0x2700208 },
    { 0x0040010, move_osc_down, task_remove_current, NULL, 0x2700208 },
    { 0x0040010, move_apply_vel, task_remove_current, NULL, 0x2700208 },
    { 0x0008010, move_to_next, hit_combo_startup_projectile, hit_check_opp_grabbing, 0x2700208 },
    /* Aaron specific */ { 0x1013090, move_to_next, hit_combo_init, hit_push_opponent_away, 0x2700208 },
    { 0x0000010, move_to_next, hit_combo_startup_alt, hit_check_opp_grabbing, 0x2700208 },
    { 0x0000080, move_to_next, task_remove_current, NULL, 0x2700208 },
    { 0x0003000, move_to_next, task_remove_current, NULL, 0x2700208 },
    { 0x0040090, move_count_up, task_remove_current, NULL, 0x2700208 },
    { 0x0008000, move_to_next, task_remove_current, NULL, 0x2700208 },
    { 0x0029010, move_to_next, task_remove_current, NULL, 0x2700208 },
    { 0x0068010, move_apply_vel, task_remove_current, NULL, 0x2700208 },
    { 0x0029010, move_to_next, hit_projectile_or_end, NULL, 0x2700208 },
    { 0x0003090, move_to_next, hit_rebound_spawn, NULL, 0x2700208 },
    { 0x0041000, move_count_up, task_remove_current, NULL, 0x2700208 },
    { 0x0000010, move_to_next, hit_clear_flag_delayed, NULL, 0x2700208 },
    { 0x0041010, move_to_next, task_remove_current, hit_check_opp_punishable, 0x2700208 },
    { 0x0001000, move_to_next, projectile_init, x_82bfe825, 0x2F00208 },
    { 0x1000010, move_to_next, hit_combo_damage_vfx, NULL, 0x2700208 },
    { 0x1021000, move_to_next, hit_projectile_zenmuron, NULL, 0x2700208 },
    { 0x0000010, move_count_up, projectile_init, NULL, 0x2700208 },
    { 0x0001000, move_to_next, hit_combo_spin_opponent, hit_check_button_same, 0x2700208 },
    { 0x0001000, move_to_next, hit_combo_spin_opponent, hit_check_button_opposite, 0x2700208 },
    { 0x1003090, move_to_next, hit_combo_init, NULL, 0x2700208 },
    { 0x1013090, move_to_next, task_remove_current, hit_push_opponent_away, 0x2700208 },
    { 0x0008010, move_to_next, hit_clear_flag_delayed, NULL, 0x2700208 },
    { 0x0000000, move_to_next, hit_combo_unblockable_check, NULL, 0x2700208 },
    { 0x0061010, move_to_next, hit_set_flag_on_frame, NULL, 0x2700208 },
    { 0x0008000, move_apply_vel, hit_ai_juggle_dispatch, NULL, 0x2700208 },
    { 0x0000000, move_count_up, hit_delay_ai_move, NULL, 0x2700208 },
    { 0x0000000, move_apply_vel, hit_delay_crossup_move, NULL, 0x2700208 },
    { 0x0001000, move_to_next, hit_face_opponent_late, NULL, 0x2700208 },
    { 0x8005000, move_delay_cb, task_remove_current, NULL, 0x2F00208 },
};

/* .bss */
s32 D_800AA470[4];
s32 D_800AA480;
Player x_824b9544[2];
x_7bac7836 gWadCondLoad[2];
u8 D_800B6350[2][11];
x_79eacfe1 D_800B6368[x_edb381f3];