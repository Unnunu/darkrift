#include "common.h"

x_87049dce D_80052220 = {
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

s16 D_800522A0[] = { x_89bd7f51, x_0259aa31, x_acdca834, 0 };
s16 D_800522A8[] = { x_89bd7f51, x_0259aa31, x_6a3715eb, x_9efec86a, x_afcef681, x_da8c2fe3, 0 };
s16 D_800522B8[] = { x_89bd7f51, x_0259aa31, x_6a3715eb, x_9efec86a, x_a1422c65, x_618f64b1, x_55e6a23a, 0 };
s16 D_800522C8[] = { x_2d2ae732, x_84625073, x_dbd7fb68, x_6a3715eb, x_9efec86a, x_afcef681, x_da8c2fe3, 0 };
s16 D_800522D8[] = {
    x_2d2ae732, x_84625073, x_dbd7fb68, x_6a3715eb, x_9efec86a, x_a1422c65, x_618f64b1, x_55e6a23a, 0
};
s16 *x_e88b7c93[] = {
    D_800522A0, D_800522A8, D_800522B8, D_800522C8, D_800522D8, NULL,
};

// What is this ??
void results_portrait_flicker(Object *obj);

s32 D_80052304 = 0;
void (*D_80052308)(Object *) = results_portrait_flicker;
s32 D_8005230C = 0x2800;
