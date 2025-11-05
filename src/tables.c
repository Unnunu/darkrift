#include "common.h"

void run_main_menu_mode(void);
void run_1_mode(void);
void run_2_mode(void);
void run_3_mode(void);
void run_4_mode(void);
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
void func_80008D98(void);
void func_80008FDC(void);
void func_800092B0(void);
void run_intro_mode(void);
void run_logo_mode(void);
void func_800099F0(void);
void func_80009E8C(void);
void func_80009480(void);
void func_800095A8(void);

void func_80015D60(Object *obj);
void func_80016144(Object *obj);
void func_80023FDC(Object *);
void func_8002FD78(Object *);
void func_80030A60(Object *);
void func_8002F9E8(Object *);
void func_8002FA78(Object *);
void func_80030F00(Object *);
void func_80031088(Object *);
void func_8002FE10(Object *);
void func_80024214(Object *);
void func_80030330(Object *);
void func_800309EC(Object *);
void func_8002FEA0(Object *);
void func_80031724(Object *);
void func_80023F9C(Object *);
void func_80023F54(Object *);
void func_80030B74(Object *);
void func_80023D30(Object *);
u8 func_80030C88(Object *);
void func_800311A0(Object *);
u8 func_800315FC(Object *);
u8 func_80031648(Object *);
void func_8002FEC8(Object *);
void func_800305FC(Object *);
u8 func_80030764(Object *);
u8 func_8002FF7C(Object *);
void func_800306FC(Object *);
void func_80031F24(Object *);
u8 func_800316A0(Object *);
void func_800302A4(Object *);
u8 func_8002F9A0(Object *);
void func_80030074(Object *);
void func_80032130(Object *);
void func_80031234(Object *);
void func_8003146C(Object *);
void func_80031164(Object *);
void func_80031FBC(Object *);
void func_80032044(Object *);
void func_80031F88(Object *);
void func_800313EC(Object *);
void func_80015CD8(Object *);
void func_80015E24(Object *);
void func_8002A1F0(Object *);

extern UnkKappa D_8004935C;
extern UnkKappa D_8004B624;
extern UnkKappa D_8004B644;
extern UnkKappa D_8004B664;
extern UnkKappa D_8004B684;
extern UnkKappa D_8004B6A4;
extern UnkKappa D_8004B6C4;
extern UnkKappa D_8004B6E4;
extern UnkKappa D_8004B704;
extern UnkKappa D_8004B724;
extern UnkKappa D_8004B744;

const char D_80054C70[] = "aaro";
const char D_80054C78[] = "demi";
const char D_80054C80[] = "demo";
const char D_80054C88[] = "eve";
const char D_80054C8C[] = "gore";
const char D_80054C94[] = "morp";
const char D_80054C9C[] = "niik";
const char D_80054CA4[] = "scar";
const char D_80054CAC[] = "sono";
const char D_80054CB4[] = "zenm";

const char D_80054CBC[] = "AR_GR1";
const char D_80054CC4[] = "DM_GR1";
const char D_80054CCC[] = "DO_GR1";
const char D_80054CD4[] = "EV_GR1";
const char D_80054CDC[] = "GE_GR1";
const char D_80054CE4[] = "GO_GR1";
const char D_80054CEC[] = "MO_GR1";
const char D_80054CF4[] = "NI_GR1";
const char D_80054CFC[] = "SC_GR1";
const char D_80054D04[] = "SO_GR1";
const char D_80054D0C[] = "ZE_GR1";

const char D_80054D14[] = "ARCGR1";
const char D_80054D1C[] = "DMCGR1";
const char D_80054D24[] = "DOCGR1";
const char D_80054D2C[] = "EVCGR1";
const char D_80054D34[] = "GECGR1";
const char D_80054D3C[] = "GOCGR1";
const char D_80054D44[] = "MOCGR1";
const char D_80054D4C[] = "NICGR1";
const char D_80054D54[] = "SCCGR1";
const char D_80054D5C[] = "SOCGR1";
const char D_80054D64[] = "ZECGR1";

extern Unk_8004BA6C D_800523FC;
extern Unk_8004BA6C D_80052560;
extern Unk_8004BA6C D_80052664;
extern Unk_8004BA6C D_80052890;

s32 D_8004BA60[] = { 0, 0, 0x80052C3C }; // TODO

Unk_8004BA6C *D_8004BA6C[] = {
    NULL, &D_80052560, &D_80052664, NULL, &D_800523FC, NULL, &D_80052890, NULL, NULL, NULL, NULL,
};

Vec4s D_8004BA98[] = {
    { 0, 0, 27 }, { 0, 0, 58 },  { 0, 0, 100 }, { 0, 0, 50 }, { 0, 0, 18 },  { 0, 0, -1 },
    { 0, 0, 0 },  { 26, 0, 44 }, { 0, 0, 0 },   { 0, 0, 0 },  { -3, 0, -3 },
};

Vec4s D_8004BAF0[] = {
    { 0, 0, 0 },    { 0, 0, 21 },  { 31, 0, 140 }, { -38, 0, 4 }, { 26, 0, 85 }, { 0, 0, -1 },
    { -7, 0, -22 }, { 26, 0, 16 }, { 0, 0, -1 },   { 13, 0, 4 },  { -3, 0, -3 },
};

GameMode gGameModes[] = {
    { run_main_menu_mode, 0x90000, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_1_mode, 0x90000, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_2_mode, 0x90000, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_3_mode, 0x90000, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_4_mode, 0x90000, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_player_selection_mode, 0x20000, 0, 0, 0, 0, 0, 40, 32, 40, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_battle_aaron_mode, 0xB0000, 0, 0, 0, 0, 0, 113, 108, 97, 0, 945, 1000, &D_8004B624, 69, 55, 88, 0 },
    { run_battle_demitron_mode, 0xB0000, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, 84, 26, 25, 0 },
    { run_battle_demonica_mode, 0xB0000, 0, 19, 32, 28, 0, 4, 4, 14, 0, 945, 1000, &D_8004B664, 36, 77, 54, 0 },
    { run_battle_eve_mode, 0xB0000, 0, 84, 124, 190, 0, 27, 62, 21, 0, 945, 1000, &D_8004B684, 23, 25, 27, 0 },
    { run_battle_gore_mode, 0xB0000, 0, 67, 107, 186, 0, 40, 32, 40, 0, 945, 1000, &D_8004B6A4, 62, 52, 74, 0 },
    { run_battle_aaron_mode, 0xB0000, 0, 61, 105, 194, 0, 40, 32, 40, 0, 945, 1000, &D_8004B624, 50, 60, 70, 0 },
    { run_battle_morphix_mode, 0xB0000, 0, 42, 31, 70, 0, 56, 43, 85, 0, 945, 1000, &D_8004B6C4, 50, 60, 70, 0 },
    { run_battle_niiki_mode, 0xB0000, 0, 13, 14, 14, 0, 26, 20, 18, 0, 850, 1000, &D_8004B6E4, 63, 29, 33, 0 },
    { run_battle_scarlet_mode, 0xB0000, 0, 36, 32, 30, 0, 123, 94, 69, 0, 945, 1000, &D_8004B704, 53, 43, 52, 0 },
    { run_battle_sonork_mode, 0xB0000, 0, 112, 105, 109, 0, 114, 101, 81, 0, 945, 1000, &D_8004B724, 56, 46, 34, 0 },
    { run_battle_zenmuron_mode, 0xB0000, 0, 2, 7, 16, 0, 1, 6, 14, 0, 945, 1000, &D_8004B744, 8, 16, 69, 0 },
    { run_17_mode, 0xB0000, 0, 61, 105, 194, 0, 40, 32, 40, 0, 945, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_intro_aaron_mode, 0xB0000, 0, 0, 0, 0, 0, 113, 108, 97, 0, 945, 1000, &D_8004B624, 69, 55, 88, 0 },
    { run_intro_demitron_mode, 0xB0000, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, 84, 26, 25, 0 },
    { run_intro_demonica_mode, 0xB0000, 0, 19, 32, 28, 0, 4, 4, 14, 0, 945, 1000, &D_8004B664, 36, 77, 54, 0 },
    { run_intro_eve_mode, 0xB0000, 0, 84, 124, 190, 0, 27, 62, 21, 0, 945, 1000, &D_8004B684, 23, 25, 27, 0 },
    { run_intro_gore_mode, 0xB0000, 0, 61, 105, 194, 0, 40, 32, 40, 0, 945, 1000, &D_8004B6A4, 62, 52, 74, 0 },
    { run_intro_gore_mode, 0xB0000, 0, 67, 107, 186, 0, 40, 32, 40, 0, 945, 1000, &D_8004B624, 50, 60, 70, 0 },
    { run_intro_morphix_mode, 0xB0000, 0, 42, 31, 70, 0, 56, 43, 85, 0, 945, 1000, &D_8004B6C4, 50, 60, 70, 0 },
    { run_intro_niiki_mode, 0xB0000, 0, 13, 14, 14, 0, 26, 20, 18, 0, 850, 1000, &D_8004B6E4, 63, 29, 33, 0 },
    { run_intro_scarlet_mode, 0xB0000, 0, 36, 32, 30, 0, 123, 94, 69, 0, 945, 1000, &D_8004B704, 53, 43, 52, 0 },
    { run_intro_sonork_mode, 0xB0000, 0, 112, 105, 109, 0, 114, 101, 81, 0, 945, 1000, &D_8004B724, 56, 46, 34, 0 },
    { run_intro_zenmuron_mode, 0xB0000, 0, 2, 7, 16, 0, 1, 6, 14, 0, 945, 1000, &D_8004B744, 8, 16, 69, 0 },
    { func_80008D98, 0xB0000, 0, 112, 105, 109, 0, 114, 101, 81, 0, 945, 1000, &D_8004B724, 56, 46, 34, 0 },
    { func_80008FDC, 0xB0000, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, 84, 26, 25, 0 },
    { func_800092B0, 0xB0000, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_intro_mode, 0xB0000, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { run_logo_mode, 0xB0000, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { func_800099F0, 0xB0000, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, 84, 26, 25, 0 },
    { func_80009E8C, 0xB0000, 0, 113, 65, 59, 0, 234, 89, 69, 0, 850, 1000, &D_8004B644, 84, 26, 25, 0 },
    { func_80009480, 0xB0000, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 },
    { func_800095A8, 0xB0000, 0, 0, 0, 0, 0, 0, 4, 10, 0, 630, 1000, &D_8004935C, 192, 192, 192, 0 }
};

Unk80015E74 D_8004C008[] = {
    { "battle", 10, 20, func_80015D60, 0 },   { "chal", 60, 20, func_80015D60, 3 },
    { "cont", 240, 20, func_80015D60, 1 },    { "ctdown", 0, 255, func_80016144, -1 },
    { "draw", 0, 20, func_80015CD8, 4 },      { "finalrd", 30, 20, func_80015D60, -1 },
    { "round", 30, 20, func_80015E24, -1 },   { "gameover", 0, 20, func_80015CD8, 2 },
    { "cont", 240, 20, func_80015D60, 1 },    { "pause", 0, 20, func_8002A1F0, -1 },
    { "timeover", 0, 20, func_80015D60, -1 }, { "perfect", 0, 80, func_80015D60, 6 },
};

Unk80015E74 D_8004C0C8[] = {
    { "aarowin", 110, 20, func_80015CD8, 5 }, { "demiwin", 110, 20, func_80015CD8, 5 },
    { "demowin", 110, 20, func_80015CD8, 5 }, { "evewin", 110, 20, func_80015CD8, 5 },
    { "gorewin", 110, 20, func_80015CD8, 5 }, { "gorewin", 110, 20, func_80015CD8, 5 },
    { "morpwin", 100, 20, func_80015CD8, 5 }, { "niikwin", 110, 20, func_80015CD8, 5 },
    { "scarwin", 110, 20, func_80015CD8, 5 }, { "sonowin", 110, 20, func_80015CD8, 5 },
    { "zenmwin", 110, 20, func_80015CD8, 5 },
};

u32 D_8004C178[] = { 430, 430, 430, 430, 430, 430, 430, 530, 470, 430, 430 };
u32 D_8004C1A4[] = { 500, 450, 450, 450, 450, 450, 450, 370, 370, 450, 450 };

s16 gNumRounds = 3;
s16 gBattleDurationEnum = 2;

u8 D_8004C1D8[] = { 6, 7, 9, 6, 5, 5, 6, 8, 5, 8, 5 };

s16 gDifficulty = 1;

PlayerSub5 D_8004C1E8[] = {
    { 0x0040010, func_80023FDC, func_8002FD78, NULL, 0x2700208 },
    { 0x0041010, task_default_func, func_80030A60, NULL, 0x2700208 },
    { 0x0001010, func_80024078, func_8002F9E8, NULL, 0x2700208 },
    { 0x0040010, func_80023FDC, func_8002FA78, NULL, 0x2F00208 },
    { 0x0040000, func_80023FDC, task_default_func, NULL, 0x2700208 },
    { 0x0040000, func_80023FDC, func_80030F00, NULL, 0x2700208 },
    { 0x0001010, func_80024078, func_80031088, NULL, 0x2700208 },
    { 0x0040010, func_80023FDC, func_8002FE10, NULL, 0x2F00208 },
    { 0x0001810, func_80023ED0, task_default_func, NULL, 0x2F00208 },
    { 0x0001010, func_80024214, task_default_func, NULL, 0x2700208 },
    { 0x0801010, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0005000, func_80023ED0, task_default_func, NULL, 0x2F00208 },
    { 0x0000000, func_80024214, task_default_func, NULL, 0x2700208 },
    { 0x0000010, func_80024078, func_80030330, NULL, 0x2700208 },
    { 0x1003090, func_80024078, func_800309EC, NULL, 0x2700208 },
    { 0x0000000, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0040000, func_80023FDC, task_default_func, NULL, 0x2700208 },
    { 0x0040000, func_80023FDC, task_default_func, NULL, 0x2700208 },
    { 0x0000000, func_80024078, func_8002FEA0, NULL, 0x2700208 },
    { 0x0003010, func_80024078, func_80031724, NULL, 0x2700208 },
    { 0x0041000, func_80023F9C, task_default_func, NULL, 0x2700208 },
    { 0x0040090, func_80023FDC, task_default_func, NULL, 0x2700208 },
    { 0x0040000, func_80023F54, task_default_func, NULL, 0x2700208 },
    { 0x0003000, func_80023F9C, func_80030B74, NULL, 0x2700208 },
    { 0x0000000, task_default_func, func_80023D30, NULL, 0x2700208 },
    { 0x0001000, func_80024078, task_default_func, func_80030C88, 0x2700208 },
    { 0x0003000, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0001018, func_80024078, task_default_func, func_80030BB0, 0x2700208 },
    { 0x0000010, func_80024078, func_80021E34, NULL, 0x2700208 },
    { 0x0001000, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0001010, func_80024078, func_800311A0, func_800315FC, 0x2700208 },
    { 0x0001010, func_80024078, func_800311A0, func_80031648, 0x2700208 },
    { 0x0000010, func_80024078, func_800311A0, func_800315FC, 0x2700208 },
    { 0x0000010, func_80024078, func_800311A0, func_80031648, 0x2700208 },
    { 0x0000010, func_80024078, func_8002FEC8, func_80030BB0, 0x2700208 },
    { 0x0008010, func_80024078, func_8002FEA0, NULL, 0x2700208 },
    { 0x0000010, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0040010, func_80023F54, task_default_func, NULL, 0x2700208 },
    { 0x0040010, func_80023FDC, task_default_func, NULL, 0x2700208 },
    { 0x0008010, func_80024078, func_800305FC, func_80030764, 0x2700208 },
    { 0x1013090, func_80024078, func_800302A4, func_8002FF7C, 0x2700208 },
    { 0x0000010, func_80024078, func_800306FC, func_80030764, 0x2700208 },
    { 0x0000080, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0003000, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0040090, func_80023F9C, task_default_func, NULL, 0x2700208 },
    { 0x0008000, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0029010, func_80024078, task_default_func, NULL, 0x2700208 },
    { 0x0068010, func_80023FDC, task_default_func, NULL, 0x2700208 },
    { 0x0029010, func_80024078, func_80031F24, NULL, 0x2700208 },
    { 0x0003090, func_80024078, func_800309EC, NULL, 0x2700208 },
    { 0x0041000, func_80023F9C, task_default_func, NULL, 0x2700208 },
    { 0x0000010, func_80024078, func_800311A0, NULL, 0x2700208 },
    { 0x0041010, func_80024078, task_default_func, func_800316A0, 0x2700208 },
    { 0x0001000, func_80024078, func_80021E34, func_8002F9A0, 0x2F00208 },
    { 0x1000010, func_80024078, func_80030074, NULL, 0x2700208 },
    { 0x1021000, func_80024078, func_80032130, NULL, 0x2700208 },
    { 0x0000010, func_80023F9C, func_80021E34, NULL, 0x2700208 },
    { 0x0001000, func_80024078, func_80031234, func_800315FC, 0x2700208 },
    { 0x0001000, func_80024078, func_80031234, func_80031648, 0x2700208 },
    { 0x1003090, func_80024078, func_800302A4, NULL, 0x2700208 },
    { 0x1013090, func_80024078, task_default_func, func_8002FF7C, 0x2700208 },
    { 0x0008010, func_80024078, func_800311A0, NULL, 0x2700208 },
    { 0x0000000, func_80024078, func_8003146C, NULL, 0x2700208 },
    { 0x0061010, func_80024078, func_80031164, NULL, 0x2700208 },
    { 0x0008000, func_80023FDC, func_80031FBC, NULL, 0x2700208 },
    { 0x0000000, func_80023F9C, func_80031F88, NULL, 0x2700208 },
    { 0x0000000, func_80023FDC, func_80032044, NULL, 0x2700208 },
    { 0x0001000, func_80024078, func_800313EC, NULL, 0x2700208 },
    { 0x8005000, func_80023ED0, task_default_func, NULL, 0x2F00208 },
};