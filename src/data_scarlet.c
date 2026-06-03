#include "common.h"

HitZonesSetup D_80052990 = {
    5,
    8,
    3,
    14,
    11,
    13,
    10,
    -1,
    4,
    52500,
    80000,
    { 0, 0, 0, 0 },
    { 0, 20, -390, 0 },
    { 0, 100, 0, 0 },
    { 0, 100, 0, 0 },
    -1,
    { 0, 0, 0, 0 },
};

s16 D_80052A10[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_BS_COMBO_1_P3, MOVE_ID_BS_COMBO_1_P4, 0 };
s16 D_80052A1C[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_1_P3,  0 };
s16 D_80052A28[] = { MOVE_ID_HS_COMBO_1_P1, MOVE_ID_HS_COMBO_1_P2, MOVE_ID_HS_COMBO_2_P1, 0 };
s16 D_80052A30[] = { MOVE_ID_RK_COMBO_1_P1, MOVE_ID_RK_COMBO_1_P2, 0 };
s16 D_80052A38[] = { MOVE_ID_HS_COMBO_1_P1,
                     MOVE_ID_HS_COMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,
                     MOVE_ID_COCOMBO_2_P1,
                     MOVE_ID_COCOMBO_2_P2,
                     0 };
s16 *D_80052A48[] = {
    D_80052A10, D_80052A1C, D_80052A28, D_80052A30, D_80052A38, NULL,
};
