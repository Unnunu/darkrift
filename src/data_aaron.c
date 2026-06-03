#include "common.h"

HitZonesSetup D_80052220 = {
    6,
    9,
    3,
    17,
    14,
    16,
    13,
    -1,
    4,
    80000,
    80000,
    { 0, 0, 0, 0 },
    { 0, 470, 0, 0 },
    { 0, 150, 0, 0 },
    { 0, 50, 0, 0 },
    -1,
    { 0, 0, 0, 0 },
};

s16 D_800522A0[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_BS_COMBO_2_P1, 0 };
s16 D_800522A8[] = { MOVE_ID_BS_COMBO_1_P1,
                     MOVE_ID_BS_COMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P3,
                     MOVE_ID_COCOMBO_1_P4,
                     0 };
s16 D_800522B8[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1, MOVE_ID_COCOMBO_1_P2,
                     MOVE_ID_COCOMBO_2_P1,  MOVE_ID_COCOMBO_2_P2,  MOVE_ID_COCOMBO_2_P3, 0 };
s16 D_800522C8[] = { MOVE_ID_HS_COMBO_1_P1, MOVE_ID_HS_COMBO_1_P2, MOVE_ID_HS_COMBO_1_P3, MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_1_P3,  MOVE_ID_COCOMBO_1_P4,  0 };
s16 D_800522D8[] = { MOVE_ID_HS_COMBO_1_P1, MOVE_ID_HS_COMBO_1_P2, MOVE_ID_HS_COMBO_1_P3,
                     MOVE_ID_COCOMBO_1_P1,  MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_2_P1,
                     MOVE_ID_COCOMBO_2_P2,  MOVE_ID_COCOMBO_2_P3,  0 };
s16 *gCombosAaron[] = {
    D_800522A0, D_800522A8, D_800522B8, D_800522C8, D_800522D8, NULL,
};

// What is this ??
void func_8002A250(Object *obj);

s32 D_80052304 = 0;
void (*D_80052308)(Object *) = func_8002A250;
s32 D_8005230C = 0x2800;
