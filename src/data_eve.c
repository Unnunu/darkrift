#include "common.h"

HitZonesSetup D_80052580 = {
    9,
    13,
    3,
    24,
    21,
    23,
    20,
    13,
    3,
    52500,
    80000,
    { 0, 200, 0, 0 },
    { 0, 200, 0, 0 },
    { 0, 100, -100, 0 },
    { 0, 100, -100, 0 },
    9,
    { 0, 0, 0, 0 },
};

s16 D_80052600[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_BS_COMBO_1_P3, 0 };
s16 D_80052608[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_1_P3,  0 };
s16 D_80052614[] = { MOVE_ID_BS_COMBO_1_P1, MOVE_ID_BS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_2_P1,  MOVE_ID_COCOMBO_2_P2,
                     MOVE_ID_COCOMBO_2_P3,  MOVE_ID_COCOMBO_2_P4,  0 };
s16 D_80052628[] = { MOVE_ID_HS_COMBO_1_P1,
                     MOVE_ID_HS_COMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,
                     MOVE_ID_COCOMBO_1_P3,
                     MOVE_ID_COCOMBO_1_P4,
                     0 };
s16 D_80052638[] = { MOVE_ID_HS_COMBO_1_P1, MOVE_ID_HS_COMBO_1_P2, MOVE_ID_COCOMBO_1_P1,
                     MOVE_ID_COCOMBO_1_P2,  MOVE_ID_COCOMBO_2_P1,  MOVE_ID_COCOMBO_2_P2,
                     MOVE_ID_COCOMBO_2_P3,  MOVE_ID_COCOMBO_2_P4,  0 };
s16 *D_8005264C[] = {
    D_80052600, D_80052608, D_80052614, D_80052628, D_80052638, NULL,
};

Unk_8004BA6C D_80052664[] = {
    { 154, 6, 0 }, { 164, 5, 0 }, { 180, 6, 0 }, { 198, 5, 0 }, { 212, 6, 0 }, { 0, 0, 0 },
};

Unk_8004BA6C D_80052688[] = {
    { 22, 2, 1 }, { 58, 2, 1 }, { 72, 2, 1 }, { 96, 2, 1 }, { 0, 0, 0 },
};