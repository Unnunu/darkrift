#include "common.h"

HitZonesSetup D_80052B30 = {
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
    { 0, 30, 500, 0 },
    { 0, 150, 0, 0 },
    { 0, 150, 0, 0 },
    -1,
    { 0, 0, 0, 0 },
};

s16 D_80052BB0[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_BS_COMBO_1_P3, 0 };
s16 D_80052BB8[] = { MOVE_ID_HS_COMBO_1_P1, MOVE_ID_HS_COMBO_1_P2, MOVE_ID_HS_COMBO_1_P3, 0 };
s16 D_80052BC0[] = { MOVE_ID_RK_COMBO_1_P1, MOVE_ID_RK_COMBO_1_P2, MOVE_ID_RK_COMBO_1_P3, 0 };
s16 D_80052BC8[] = { MOVE_ID_BS_COMBO_1_P1,
                     MOVE_ID_BS_COMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P3,
                     MOVE_ID_COCOMBO_1_P4,
                     0 };
s16 D_80052BD8[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_2_P1,  MOVE_ID_COCOMBO_2_P2,
                     MOVE_ID_COCOMBO_2_P3,  MOVE_ID_COCOMBO_2_P4,  0 };
s16 D_80052BEC[] = { MOVE_ID_HS_COMBO_1_P1, MOVE_ID_HS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_1_P3,  0 };
s16 D_80052BF8[] = { MOVE_ID_HS_COMBO_1_P1, MOVE_ID_HS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1, MOVE_ID_COCOMBO_1_P2,
                     MOVE_ID_COCOMBO_2_P1,  MOVE_ID_COCOMBO_2_P2,  MOVE_ID_COCOMBO_2_P3, 0 };
s16 D_80052C08[] = { MOVE_ID_RK_COMBO_1_P1,
                     MOVE_ID_RK_COMBO_1_P2,
                     MOVE_ID_RK_FOREVER,
                     MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P3,
                     0 };
s16 *D_80052C18[] = {
    D_80052BB0, D_80052BB8, D_80052BC0, D_80052BC8, D_80052BD8, D_80052BEC, D_80052BF8, D_80052C08, NULL,
};

Unk_8004BA6C D_80052C3C[] = {
    { 15, 0, 0 },
    { 0, 0, 0 },
};
