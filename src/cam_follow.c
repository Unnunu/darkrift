#include "common.h"
#include "camera.h"
#include "task.h"

s32 x_e3ea1dcb = 170;
s32 x_e700b1a3 = 500;
s32 x_789112b4[] = { 0, 0xFFFFFE20, 0xFFFFF704, 0 };
s32 x_63e0d71b = 0x400;
s32 x_fef2140c = 0x480000;
s32 x_452e0082 = 0x1C000;
s32 x_c2f1d98b = 0x20000;
s32 x_15bf92fd = 0x100000;
s32 x_b8d38fc7 = 0;
s32 x_7eb21652 = 200;
s32 x_1c1ecf0d = 0x240000;
s32 x_79389416 = 0x2000;
s32 x_e21927eb = 0xE000;
s32 x_e4130b8b = 0x40000;
s32 x_08b122d8 = 0;
s32 x_824d63ed = 0;
s32 x_19369121 = 0x400;
s8 x_e1e12448 = 0;
u8 x_9991d607 = FALSE;
s32 x_b64f16b7 = 0;
s32 x_881ee8c3 = 0;
s32 x_1e5afea8 = 0;
s32 x_b221ddda = 0x8000;
s32 x_7450a2d3 = 0;
char *x_9f3b452d = "opencamX.oc";

x_88f11482 x_f8a5b34e;
x_88f11482 x_84e6adae;
s16 D_8013C300;
s16 D_8013C302;
s16 D_8013C304;
f32 D_8013C308;
s32 x_2c039205;
x_88f11482 D_8013C310;
x_88f11482 D_8013C320;
s16 x_c4fec3a7;
s16 D_8013C332;
s16 D_8013C334;
s16 D_8013C336;
f32 D_8013C338;
s16 D_8013C33C;
s16 D_8013C33E;
s32 x_987ae9dc;
s32 x_d86fab4d;
s32 x_49bdae1a;
s32 x_22f06603;
s32 x_6db70595;
s32 x_fb93483b;
s32 x_992054e2;
s32 x_d85eefcc;
s32 x_6d4a1d2c;
s32 x_143af627;
s32 x_4809c47c;
s32 x_aa9e3546;
s32 D_8013C370;
s32 x_93ff7118;
s32 x_7411f494;
s32 x_c7298ffb;
s32 x_f6ef18bf;
s32 x_db28d0d1;
s16 x_01fe5b5c;
s16 x_0525ed93;
s16 x_aba11848;
s16 x_b227e464;
s32 x_e5ea8fea;

s32 sin_fixed(s32 x_cc1d0de5);

void cam_battle_update(Object *obj);
void cam_update(Object *obj, u8 x_84ff873b);
void cam_distance_update(u8 x_cc1d0de5);

s32 abs(s32 x_cc1d0de5) {
    return x_cc1d0de5 < 0 ? -x_cc1d0de5 : x_cc1d0de5;
}

s32 iabs(s32 x_cc1d0de5) {
    return x_cc1d0de5 < 0 ? -x_cc1d0de5 : x_cc1d0de5;
}

void cam_save_state(void) {
    D_8013C320.x = x_435c561d.x;
    D_8013C320.y = x_435c561d.y;
    D_8013C320.z = x_435c561d.z;

    D_8013C310.x = x_f4bce728->pos.x;
    D_8013C310.y = x_f4bce728->pos.y;
    D_8013C310.z = x_f4bce728->pos.z;

    D_8013C332 = x_e74df613;
    D_8013C334 = x_6c647b3a;
    D_8013C336 = D_8013C828;
    D_8013C338 = D_8013C5A0;

    if (gCurrentScreenId <= x_cc464edc) {
        gGfxFlags |= GFX_SKIP_SCENE;
    }
}

void cam_save_state_alt(void) {
    D_8013C302 = x_e74df613;

    x_84e6adae.x = x_435c561d.x;
    x_84e6adae.y = x_435c561d.y;
    x_84e6adae.z = x_435c561d.z;

    x_f8a5b34e.x = x_f4bce728->pos.x;
    x_f8a5b34e.y = x_f4bce728->pos.y;
    x_f8a5b34e.z = x_f4bce728->pos.z;

    D_8013C300 = x_6c647b3a;
    D_8013C304 = D_8013C828;
    D_8013C308 = D_8013C5A0;
}

void cam_cinematic_update(Object *obj) {

    cam_save_state_alt();

    obj->pos.x = D_8013C310.x;
    obj->pos.y = D_8013C310.y;
    obj->pos.z = D_8013C310.z;

    x_435c561d.x = D_8013C320.x;
    x_435c561d.y = D_8013C320.y;
    x_435c561d.z = D_8013C320.z;

    x_e74df613 = D_8013C332;
    x_6c647b3a = D_8013C334;
    D_8013C828 = D_8013C336;
    D_8013C5A0 = D_8013C338;

    cam_update(obj, FALSE);
    cam_save_state();

    if (obj->x_20d20338->x_50771dcd[0] != NULL) {
        obj->frameCounter++;
        if (obj->frameCounter >= obj->x_20d20338->x_8e601526 - 1) {
            obj->x_20d20338->x_50771dcd[0] = NULL;
            if (!sFightLocked || D_80080234 == 0) {
                obj->currentTask->callback = cam_battle_update;
                obj->currentTask->delay = 1;
                gGfxFlags &= ~GFX_SKIP_SCENE;
                x_824b9544[x_83106b21].obj->flags &= ~x_060adf1c;
                x_824b9544[x_6f0b3be3].obj->flags &= ~x_060adf1c;
                return;
            }
            x_6f8aa7af = TRUE;
        }
    }

    gGfxFlags &= ~GFX_MENU_OVERLAY;

    obj->pos.x = x_f8a5b34e.x;
    obj->pos.y = x_f8a5b34e.y;
    obj->pos.z = x_f8a5b34e.z;

    x_435c561d.x = x_84e6adae.x;
    x_435c561d.y = x_84e6adae.y;
    x_435c561d.z = x_84e6adae.z;

    x_6c647b3a = D_8013C300 - (s32) (x_cf60a652 * 0.2f);
    x_e74df613 = 0;
    D_8013C828 = D_8013C304;
    D_8013C5A0 = D_8013C308;
}

void cam_intro_skip_check(Object *obj) {

    cam_cinematic_update(obj);

    if (obj->frameCounter >= obj->x_20d20338->x_8e601526 - 1 || (x_59ce598c[x_83106b21].buttons & x_9cefe76c) ||
        (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
        if (x_5e4e2788 != x_79c2dc5b) {
            x_b372f4dd();
        } else {
            x_824b9544[x_83106b21].flags &= ~x_4d950171;
            x_824b9544[x_6f0b3be3].flags &= ~x_4d950171;
            x_e30d50d2 &= ~x_86c5bc33;
        }

        x_e74df613 = 0;
        D_8013C828 = D_8013C304;
        D_8013C5A0 = D_8013C308;

        cam_update(obj, FALSE);

        obj->currentTask->callback = cam_battle_update;
        obj->x_20d20338->x_50771dcd[0] = NULL;
        x_59ce598c[x_83106b21].x_c4397934 = x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE;
        gGfxFlags &= ~(GFX_SKIP_SCENE | GFX_SHADOW_MODE);
    }

    x_824b9544[x_83106b21].obj->flags |= x_060adf1c;
    x_824b9544[x_6f0b3be3].obj->flags |= x_060adf1c;
}

void cam_debug_controls(Object *obj) {
    u32 v0;

    v0 = x_59ce598c[x_83106b21].buttons;

    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;

    if (v0 & x_64a28e7d) {
        D_8013C588 -= 10;
    } else if (v0 & x_84d0a51b) {
        x_435c561d.y -= 10;
    } else if (v0 & x_b2ae561b) {
        x_435c561d.y += 10;
    } else if (v0 & x_ffe9ce36) {
        obj->pos.z -= 10;
    } else if (v0 & x_37f8540c) {
        obj->pos.z += 10;
    } else if (v0 & x_af0e0a9f) {
        D_8013C588 += 10;
    } else if (v0 & x_f7763ed8) {
        obj->pos.y += 10;
    } else if (v0 & x_b8c91680) {
        obj->pos.y -= 10;
    } else if (v0 & x_c7089780) {
        obj->pos.z += 10;
    } else if (v0 & x_29dbff14) {
        obj->pos.z -= 10;
    } else if (v0 & x_64a28e7d) {
        x_824b9544[x_83106b21].obj->pos.x = -1600;
        x_824b9544[x_6f0b3be3].obj->pos.x = 1600;
    } else if (v0 & x_af0e0a9f) {
        x_824b9544[x_83106b21].obj->pos.x = -400;
        x_824b9544[x_6f0b3be3].obj->pos.x = 400;
    }
}

void cam_debug_scene_input(Object *obj) {
    u32 x_8c5f8c03;
    u32 v1;
    u32 a1;
    x_2bb4cf6f *v0;

    v0 = gScreenProfiles[gCurrentScreenId].cameraBounds;
    x_8c5f8c03 = x_59ce598c[x_83106b21].buttons;
    v1 = x_8c5f8c03 & 0xFFFF;
    a1 = x_8c5f8c03 >> 16;
    x_8c5f8c03 = v1;

    if (x_8c5f8c03 != 0 || a1 != 0) {
        switch (x_8c5f8c03) {
            case 0x80:
                obj->pos.x = -2000;
                obj->pos.z = 0;
                break;
            case 0x20:
                obj->pos.x = 2000;
                obj->pos.z = 0;
                break;
            case 0x10:
                obj->pos.x = 20;
                obj->pos.z = 20;
                obj->pos.y = -2000;
                break;
            case 0x40:
                obj->pos.x = 0;
                obj->pos.z = -2000;
                break;
        }

        switch (a1) {
            case 0x80:
                v0->lights[0].x_5962f1cd = -127;
                v0->lights[0].x_a18bc2e0 = 0;
                break;
            case 0x20:
                v0->lights[0].x_5962f1cd = 127;
                v0->lights[0].x_a18bc2e0 = 0;
                break;
            case 0x10:
                v0->lights[0].x_5962f1cd = 0;
                v0->lights[0].x_a18bc2e0 = 127;
                break;
            case 0x40:
                v0->lights[0].x_5962f1cd = 0;
                v0->lights[0].x_a18bc2e0 = -127;
                break;
        }
    }
}

void cam_debug_init(Object *obj) {
    obj->pos.x = 0;
    obj->pos.y = -480;
    obj->pos.z = -2300;
    x_435c561d.y = -480;
    D_8013C588 = 597;
    obj->currentTask->callback = cam_debug_controls;
}

void cam_face_players(void) {
    Object *x_13d65ace;
    Object *x_c48d15e0;
    s16 x_434431dd;

    x_13d65ace = sIntroPlayerObjs[x_83106b21];
    x_c48d15e0 = sIntroPlayerObjs[x_6f0b3be3];
    D_8013C33C = (0xC00 - x_13d65ace->x_224610f1.y) & 0xFFF;
    D_8013C33E = (0xC00 - x_c48d15e0->x_224610f1.y) & 0xFFF;

    if (abs(angle_diff(sMenuState, D_8013C33C)) < 0x400) {
        ((Player *) x_13d65ace->x_e2f64c57[0])->flags |= x_9298c772;
        ((Player *) x_13d65ace->x_e2f64c57[0])->flags &= ~x_67e702ae;
    } else {
        x_434431dd = angle_diff(sMenuState - 0x800, D_8013C33C);
        if (abs(x_434431dd) > 140) {
            if (x_434431dd < 0) {
                x_434431dd = -140;
            } else {
                x_434431dd = 140;
            }
        }

        if (!(((Player *) x_13d65ace->x_e2f64c57[0])->flags & (x_188f9cec | x_faf494e7 | x_c865be3f))) {
            x_13d65ace->x_224610f1.y = 0xC00 - D_8013C33C - x_434431dd;
        }

        if ((x_824b9544[x_83106b21].x_101ebc50 = abs(x_434431dd)) < 8) {
            ((Player *) x_13d65ace->x_e2f64c57[0])->flags |= x_67e702ae;
        } else {
            ((Player *) x_13d65ace->x_e2f64c57[0])->flags &= ~x_67e702ae;
        }
        ((Player *) x_13d65ace->x_e2f64c57[0])->flags &= ~x_9298c772;
    }

    if (abs(angle_diff(sMenuState, D_8013C33E)) < 0x400) {
        x_434431dd = angle_diff(sMenuState, D_8013C33E);
        if (abs(x_434431dd) > 140) {
            if (x_434431dd < 0) {
                x_434431dd = -140;
            } else {
                x_434431dd = 140;
            }
        }

        if (!(((Player *) x_c48d15e0->x_e2f64c57[0])->flags & (x_188f9cec | x_faf494e7 | x_c865be3f))) {
            x_c48d15e0->x_224610f1.y = 0xC00 - D_8013C33E - x_434431dd;
        }

        if ((x_824b9544[x_6f0b3be3].x_101ebc50 = abs(x_434431dd)) < 8) {
            ((Player *) x_c48d15e0->x_e2f64c57[0])->flags |= x_67e702ae;
        } else {
            ((Player *) x_c48d15e0->x_e2f64c57[0])->flags &= ~x_67e702ae;
        }
        ((Player *) x_c48d15e0->x_e2f64c57[0])->flags &= ~x_9298c772;
    } else {
        ((Player *) x_c48d15e0->x_e2f64c57[0])->flags |= x_9298c772;
        ((Player *) x_c48d15e0->x_e2f64c57[0])->flags &= ~x_67e702ae;
    }
}

s32 lerp_int(s32 x_cc1d0de5, s32 x_84ff873b, s32 x_2092f891, s32 x_ee71e5cb) {
    x_cc1d0de5 -= x_84ff873b;
    x_cc1d0de5 = (x_cc1d0de5 * x_ee71e5cb) >> 16;
    return x_2092f891 + x_cc1d0de5;
}

s16 angle_diff(s16 x_cc1d0de5, s16 x_84ff873b) {
    s16 v1;

    v1 = (x_cc1d0de5 & 0xFFF) - (x_84ff873b & 0xFFF);
    if (v1 > 0x800) {
        v1 -= 0x1000;
    }
    if (v1 < -0x800) {
        v1 += 0x1000;
    }
    return v1;
}

void cam_world_shift(s32 x_cc1d0de5, s32 x_84ff873b) {
    Object *obj;

    for (obj = gObjectList; obj != NULL; obj = obj->x_2d5f3fbd) {
        if (!(obj->flags & x_3d723236)) {
            obj->pos.x += x_cc1d0de5;
            obj->pos.z += x_84ff873b;
            transform_calc_world(&obj->transform);
        }
    }

    x_824b9544[x_83106b21].x_d8a19723.x_b1f57d55 = x_824b9544[x_83106b21].x_238ba16f.x_b1f57d55 =
        x_824b9544[x_83106b21].x_29c9094f.x_b1f57d55 = x_824b9544[x_83106b21].x_a241ea2a.x_b1f57d55 =
            x_824b9544[x_6f0b3be3].x_d8a19723.x_b1f57d55 = x_824b9544[x_6f0b3be3].x_238ba16f.x_b1f57d55 =
                x_824b9544[x_6f0b3be3].x_29c9094f.x_b1f57d55 = x_824b9544[x_6f0b3be3].x_a241ea2a.x_b1f57d55 = 0;

    spline_init(&x_824b9544[x_83106b21].x_d8a19723.x_1091fcc6);
    spline_init(&x_824b9544[x_83106b21].x_d8a19723.x_60635a2d);
    spline_init(&x_824b9544[x_83106b21].x_238ba16f.x_1091fcc6);
    spline_init(&x_824b9544[x_83106b21].x_238ba16f.x_60635a2d);
    spline_init(&x_824b9544[x_83106b21].x_29c9094f.x_1091fcc6);
    spline_init(&x_824b9544[x_83106b21].x_29c9094f.x_60635a2d);
    spline_init(&x_824b9544[x_83106b21].x_a241ea2a.x_1091fcc6);
    spline_init(&x_824b9544[x_83106b21].x_a241ea2a.x_60635a2d);
    spline_init(&x_824b9544[x_6f0b3be3].x_d8a19723.x_1091fcc6);
    spline_init(&x_824b9544[x_6f0b3be3].x_d8a19723.x_60635a2d);
    spline_init(&x_824b9544[x_6f0b3be3].x_238ba16f.x_1091fcc6);
    spline_init(&x_824b9544[x_6f0b3be3].x_238ba16f.x_60635a2d);
    spline_init(&x_824b9544[x_6f0b3be3].x_29c9094f.x_1091fcc6);
    spline_init(&x_824b9544[x_6f0b3be3].x_29c9094f.x_60635a2d);
    spline_init(&x_824b9544[x_6f0b3be3].x_a241ea2a.x_1091fcc6);
    spline_init(&x_824b9544[x_6f0b3be3].x_a241ea2a.x_60635a2d);
}

s32 cam_world_wrap(void *x_cc1d0de5) {
    s32 a3, a1;

    a3 = x_f4bce728->x_0f4167b4[3];
    a1 = x_f4bce728->x_0f4167b4[4];

    if (x_435c561d.x > 0x2300 || x_f4bce728->pos.x > 0x2300 || x_435c561d.x < -0x2300 || x_f4bce728->pos.x < -0x2300 ||
        x_435c561d.z > 0x2300 || x_f4bce728->pos.z > 0x2300 || x_435c561d.z < -0x2300 || x_f4bce728->pos.z < -0x2300) {

        x_435c561d.x += a3;
        x_435c561d.z += a1;
        cam_world_shift(a3, a1);
        if (x_f4bce728->pos.x != 0 || x_f4bce728->pos.z != 0 || x_435c561d.x != 0 || x_435c561d.z != 0) {
            guLookAtF(&x_b082fd90, x_f4bce728->pos.x, x_f4bce728->pos.y, x_f4bce728->pos.z, x_435c561d.x, x_435c561d.y,
                      x_435c561d.z, 0.0f, -1.0f, 0.0f);
            mat4_mul_general(&x_b082fd90, &x_e1751f31, &x_7eefcd11);
        }
    }
    return 0;
}

s32 cam_world_wrap_reset(s32 x_cc1d0de5) {
    cam_world_shift(-x_435c561d.x, -x_435c561d.z);
    x_435c561d.x = x_435c561d.z = 0;
    return 0;
}

void cam_boundary_check(Object *obj) {
    s32 a2, a3;

    a2 = 0;
    a3 = 0;

    if (x_435c561d.x > 0x2300 || obj->pos.x > 0x2300) {
        a2 = -0x2800;
    } else if (x_435c561d.x < -0x2300 || obj->pos.x < -0x2300) {
        a2 = 0x2800;
    }

    if (x_435c561d.z > 0x2300 || obj->pos.z > 0x2300) {
        a3 = -0x2800;
    } else if (x_435c561d.z < -0x2300 || obj->pos.z < -0x2300) {
        a3 = 0x2800;
    }

    if (a2 != 0 || a3 != 0) {
        obj->x_0f4167b4[3] = a2;
        obj->x_0f4167b4[4] = a3;
        rsp_register_callback(cam_world_wrap, NULL);
    }
}

void cam_update(Object *obj, u8 x_84ff873b) {
    s32 pad1[3];
    s32 x_5fd741dc;
    s32 x_d318cea9;
    s32 x_6e851264;
    s32 pad2[3];
    s32 x_024f6a8d;
    s32 x_4a496b1d;
    s32 x_522f451d;
    s32 pad3[4];
    s32 x_5d45b0f8;
    s32 x_048c1e73;
    s32 x_a438747c;
    s32 v02;
    s32 a0;
    s32 x_720f6ac9, x_aa1be933, dz;
    u32 x_5d21c78b, x_b7cc9533;
    s32 x_df21a243;
    s32 x_dcab8ab0;
    x_88f11482 x_20b9213f;
    x_2758cdab x_331089fa;
    s32 x_06630832[4];
    f32 ft5;
    s32 temp;

    if (sHudActive == 0) {
        gGfxFlags |= GFX_MENU_OVERLAY;
    } else {
        gGfxFlags &= ~GFX_MENU_OVERLAY;
    }

    cam_distance_update(FALSE);

    if (gFighterDistance > 800) {
        x_024f6a8d = ((gFighterDistance - 800) * x_fb93483b) >> 0x10;
    } else {
        x_024f6a8d = 0;
    }
    if (x_024f6a8d > x_6db70595) {
        x_024f6a8d = x_6db70595;
    }

    obj->x_0f4167b4[2] = x_024f6a8d = ((x_024f6a8d - obj->x_0f4167b4[2]) ^ 0) + obj->x_0f4167b4[2]; // @fake ^ 0
    x_5fd741dc = obj->x_0f4167b4[1];

    v02 = angle_diff(sMenuState, x_5fd741dc);
    if (v02 < 0) {
        a0 = v02 + x_19369121;
    } else {
        a0 = v02 - x_19369121;
    }
    obj->x_0f4167b4[1] = temp = x_5fd741dc + a0;

    cam_face_players();
    if (angle_diff(sMenuState, x_5fd741dc) > 0) {
        sIntroPlayerObjs[x_83106b21]->flags &= ~x_6c2d42ba;
        x_59ce598c[x_83106b21].x_d93bcabf = FALSE;
        sIntroPlayerObjs[x_6f0b3be3]->flags |= x_6c2d42ba;
        x_59ce598c[x_6f0b3be3].x_d93bcabf = TRUE;
    } else {
        sIntroPlayerObjs[x_83106b21]->flags |= x_6c2d42ba;
        x_59ce598c[x_83106b21].x_d93bcabf = TRUE;
        sIntroPlayerObjs[x_6f0b3be3]->flags &= ~x_6c2d42ba;
        x_59ce598c[x_6f0b3be3].x_d93bcabf = FALSE;
    }

    x_435c561d.y = ((x_6d4a1d2c * x_024f6a8d) >> 0x10) + x_881ee8c3 - 480;
    x_d318cea9 = ((sCharSelectSpriteB->x + sCharSelectSpriteA->x) >> 1) - x_435c561d.x;
    x_6e851264 = ((sCharSelectSpriteB->z + sCharSelectSpriteA->z) >> 1) - x_435c561d.z;
    x_435c561d.x += x_d318cea9;
    x_435c561d.z += x_6e851264;

    x_4a496b1d = ((sin_fixed(temp) * x_22f06603) >> 12) + x_435c561d.x;
    x_522f451d = ((-sin_fixed(temp + 0x400) * x_22f06603) >> 12) + x_435c561d.z;
    x_5d45b0f8 = (sin_fixed(temp) * x_49bdae1a) >> 12;
    x_048c1e73 = (-sin_fixed(temp + 0x400) * x_49bdae1a) >> 12;
    x_a438747c = (x_024f6a8d * x_d86fab4d) >> 12;

    obj->pos.x = ((x_024f6a8d * x_5d45b0f8) >> 12) + x_4a496b1d;
    obj->pos.z = ((x_024f6a8d * x_048c1e73) >> 12) + x_522f451d;
    obj->pos.y = x_d85eefcc + x_b64f16b7 - x_a438747c;

    if (x_d318cea9 != 0 || x_6e851264 != 0) {
        x_20b9213f.x = x_d318cea9;
        x_20b9213f.z = -x_6e851264;
        x_331089fa.y = (0x400 - x_4c17a2ba) & 0xFFF;
        x_331089fa.x = x_331089fa.z = 0;
        vec_rotate_by_euler(&x_20b9213f, &x_331089fa);
        if (x_20b9213f.x > 0) {
            x_dcab8ab0 = (u32) (sqrtf(x_84ce1cfb(x_d318cea9) + x_84ce1cfb(x_6e851264)) + 0.5) >> 1;
        } else if (x_20b9213f.x < 0) {
            x_dcab8ab0 = -((u32) (sqrtf(x_84ce1cfb(x_d318cea9) + x_84ce1cfb(x_6e851264)) + 0.5) >> 1);
        }
        x_e74df613 += x_dcab8ab0;
    }

    x_720f6ac9 = x_435c561d.x - x_f4bce728->pos.x;
    x_aa1be933 = x_435c561d.y - x_f4bce728->pos.y;
    dz = x_435c561d.z - x_f4bce728->pos.z;
    x_5d21c78b = ABS(x_720f6ac9);
    x_b7cc9533 = ABS(dz);
    ft5 = x_4a9e7834(x_5d21c78b, x_b7cc9533);
    D_8013C594 = x_aa1be933 / ft5;

    x_3f054879(x_720f6ac9, dz, x_5d21c78b, x_b7cc9533);

    x_6c647b3a = D_8013C82C;
    if (x_024f6a8d > 1500) {
        x_6c647b3a += (x_143af627 * (x_024f6a8d - 1500)) >> 0x10;
        if (obj->x_0f4167b4 || obj->x_0f4167b4) {} // @fake
    }
    D_80081428 = D_8013C828;

    if (x_84ff873b) {
        cam_boundary_check(obj);
        if (obj->pos.x != 0 || obj->pos.z != 0 || x_435c561d.x != 0 || x_435c561d.z != 0) {
            guLookAtF(&x_b082fd90, obj->pos.x, obj->pos.y, obj->pos.z, x_435c561d.x, x_435c561d.y, x_435c561d.z, 0.0f,
                      -1.0f, 0.0f);
            mat4_mul_general(&x_b082fd90, &x_e1751f31, &x_7eefcd11);
        }
    }
}

void cam_battle_init(Object *obj) {
    x_435c561d.y = -480;
    x_987ae9dc = atan2_lut(899, 5045);
    x_d86fab4d = -sin_fixed(x_987ae9dc + 0x400);
    x_49bdae1a = sin_fixed(x_987ae9dc);
    x_22f06603 = 2300;
    x_6db70595 = -5045;
    x_6db70595 = (u32) (sqrtf(x_84ce1cfb(x_6db70595) + x_84ce1cfb(1379)) + 0.5);
    x_fb93483b = (x_6db70595 << 16) / 2400;
    x_992054e2 = (-347 << 16) / x_6db70595;
    x_6d4a1d2c = (-400 << 16) / x_6db70595;
    x_143af627 = (12 << 16) / x_6db70595;
    x_aa9e3546 = 291271;
    x_d85eefcc = -480;
    sCharSelectSpriteA = &x_824b9544[x_83106b21].obj->pos;
    sCharSelectSpriteB = &x_824b9544[x_6f0b3be3].obj->pos;

    obj->x_0f4167b4[1] = 0xC00;
    obj->x_0f4167b4[2] = 0;
    cam_update(obj, FALSE);
    x_cf60a652 = 0;
    obj->pos.x = 0;
    obj->pos.z = -2300;
    obj->pos.y = -480;
    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -480;
    x_1e5afea8 = x_b64f16b7 = x_881ee8c3 = 0;
}

void cam_intro_wait_input(Object *obj) {
    x_6c647b3a = D_8013C82C;
    D_80081428 = D_8013C828;

    if ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
        if (x_5e4e2788 != x_79c2dc5b) {
            x_b372f4dd();
        } else {
            x_824b9544[x_83106b21].flags &= ~x_4d950171;
            x_824b9544[x_6f0b3be3].flags &= ~x_4d950171;
            x_e30d50d2 &= ~x_86c5bc33;
        }

        x_e74df613 = 0;
        D_8013C828 = D_8013C304;
        D_8013C5A0 = D_8013C308;

        cam_update(obj, FALSE);

        obj->currentTask->callback = cam_battle_update;
        obj->x_20d20338->x_50771dcd[0] = NULL;
        x_59ce598c[x_83106b21].x_c4397934 = x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE;
        gGfxFlags &= ~(GFX_SKIP_SCENE | GFX_SHADOW_MODE);
    } else {
        if (--obj->x_0f4167b4[10] <= 0) {
            obj->currentTask->callback = cam_intro_skip_check;
        }
    }
}

void cam_intro_start(Object *obj) {
    s32 x_7b42bed5;
    char x_a1fcc259[20];

    cam_battle_init(obj);
    cam_save_state();

    wad_strcpy(x_a1fcc259, x_9f3b452d);
    x_a1fcc259[7] = '1' + sWadUnk1;
    x_7b42bed5 = wad_entry_find(x_a1fcc259, x_2587f84f);
    x_7bb27e6e(x_f4bce728, (x_a05f18ad *) sWadEntries[x_7b42bed5].data);
    x_f4bce728->currentTask->callback = cam_intro_wait_input;
    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->delay = 1;
    x_f4bce728->x_0f4167b4[10] = 60;
    x_59ce598c[x_83106b21].x_c4397934 = x_7b42bed5 = x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE; // required to match
}

void cam_intro_start_inverse(Object *obj) {
    s32 x_7b42bed5;
    char x_a1fcc259[20];

    cam_battle_init(obj);
    cam_save_state();

    wad_strcpy(x_a1fcc259, x_9f3b452d);
    x_a1fcc259[7] = '1' + sWadUnk1;
    x_7b42bed5 = wad_entry_find(x_a1fcc259, x_2587f84f);
    x_7bb27e6e(x_f4bce728, (x_a05f18ad *) sWadEntries[x_7b42bed5].data);
    x_f4bce728->currentTask->callback = cam_intro_skip_check;
    x_f4bce728->currentTask->delay = 0;
    x_f4bce728->currentTask->flags = TASK_RUNNABLE;
    x_f4bce728->currentTask->delay = 1;
    x_59ce598c[x_83106b21].x_c4397934 = x_7b42bed5 = x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE; // required to match
}

#ifdef NON_EQUIVALENT
void cam_distance_update(u8 x_cc1d0de5) {
    s16 s6;
    s16 s1;
    s32 v1, v0;
    u8 s0;
    s16 s3;
    s16 lo;
    s16 s4;
    Player *temp = x_824b9544;

x_3ace60b0:
    D_800801F4 = D_80080200;
    D_800801F8 = D_80080204;

    D_80080200 = sCharSelectSpriteA->x - sCharSelectSpriteB->x;
    D_80080208 = -MIN(sCharSelectSpriteA->y, sCharSelectSpriteB->y);
    D_80080204 = sCharSelectSpriteA->z - sCharSelectSpriteB->z;

    s6 = atan2_lut(D_80080204, D_80080200);
    if (D_80080200 != 0 || D_80080204 != 0) {
        s1 = (u32) (sqrtf(x_84ce1cfb(D_80080200) + x_84ce1cfb(D_80080204)) + 0.5);
    } else {
        s1 = 0;
    }

    if ((x_824b9544[x_83106b21].flags & x_c865be3f) || (x_824b9544[x_6f0b3be3].flags & x_c865be3f) ||
        (x_824b9544[x_83106b21].flags & x_77ec809d) ||
        (x_824b9544[x_6f0b3be3].flags & x_77ec809d) && s1 < 3200) { // @bug?
        D_8008021C = sMenuState;
        sMenuState = s6;
        gFighterDistance = s1;
        return;
    }

    v1 = MIN(temp[x_83106b21].x_5c5b1d93.x_1b148bc2->y, temp[x_83106b21].x_5c5b1d93.x_6e7f4fd8->y);
    v0 = MIN(temp[x_6f0b3be3].x_5c5b1d93.x_1b148bc2->y, temp[x_6f0b3be3].x_5c5b1d93.x_6e7f4fd8->y);

    if (v1 < v0) {
        s0 = (temp[x_6f0b3be3].x_5c5b1d93.x_b7552092->y - 200.0f) < v1;
    } else {
        s0 = (temp[x_83106b21].x_5c5b1d93.x_b7552092->y - 200.0f) < v0;
    }

    if ((x_824b9544[x_83106b21].x_7f68c36b->flags & x_ceaa006e) ||
        (x_824b9544[x_6f0b3be3].x_7f68c36b->flags & x_ceaa006e)) {
        s0 = TRUE;
    }

    if (!x_cc1d0de5 && s0 && abs(angle_diff(s6, sMenuState)) > 0x200) {
        s4 = (s1 + 280) >> 1;

        s3 = (sin_fixed(s6) * s4) >> 12;
        lo = ((-sin_fixed(s6 + 0x400)) * s4) >> 12;
        sCharSelectSpriteA->x -= s3;
        sCharSelectSpriteA->z -= lo;

        s3 = (sin_fixed(s6) * s4) >> 12;
        lo = ((-sin_fixed(s6 + 0x400)) * s4) >> 12;
        sCharSelectSpriteB->x += s3;
        sCharSelectSpriteB->z += lo;

        x_cc1d0de5 = TRUE;
        goto x_3ace60b0;
    }

    if (s1 < D_80080214 &&
        (!(x_824b9544[x_83106b21].flags & x_77fae129) || (x_824b9544[x_6f0b3be3].flags & x_77fae129))) { // @bug ??
        s4 = D_80080214 - s1;
        if ((x_824b9544[x_83106b21].x_7f68c36b->flags & x_ceaa006e) ||
            (x_824b9544[x_6f0b3be3].x_7f68c36b->flags & x_ceaa006e) || (x_824b9544[x_83106b21].flags & x_7f7504b2) ||
            (x_824b9544[x_6f0b3be3].flags & x_7f7504b2)) {
            s4 >>= 1;
        }
    } else {
        if (s1 > 3200) {
            s4 = 3200 - s1;
        } else {
            s4 = 0;
        }
    }

    D_8008021C = sMenuState;
    sMenuState = s6;
    gFighterDistance = s1 + s4;

    if (s4 != 0 && (s0 || s1 > 3200)) {
        s4 >>= 1;
        s3 = (sin_fixed(sMenuState) * s4) >> 12;
        lo = (-sin_fixed(sMenuState + 0x400) * s4) >> 12;
        sCharSelectSpriteA->x += s3;
        sCharSelectSpriteA->z += lo;
        sCharSelectSpriteB->x -= s3;
        sCharSelectSpriteB->z -= lo;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/cam_follow/cam_distance_update.s")
void cam_distance_update(u8);
#endif

void cam_project_point(x_88f11482 *x_cc1d0de5, f32 *x_84ff873b, f32 *x_2092f891, f32 *x_ee71e5cb) {
    f32 x, y, z;
    f32 temp;
    x = x_cc1d0de5->x;
    z = x_cc1d0de5->z;
    y = x_cc1d0de5->y;
    *x_2092f891 = 0;
    *x_84ff873b = 0;
    *x_ee71e5cb = 0;

    if (*x_f4bce728->x_20d20338->x_50771dcd == 0) {
        *x_84ff873b = x_7eefcd11.x.x * x + x_7eefcd11.y.x * y + x_7eefcd11.z.x * z + x_7eefcd11.w.x;
        *x_2092f891 = x_7eefcd11.x.y * x + x_7eefcd11.y.y * y + x_7eefcd11.z.y * z + x_7eefcd11.w.y;
        temp = x_7eefcd11.x.w * x + x_7eefcd11.y.w * y + x_7eefcd11.z.w * z + x_7eefcd11.w.w;
        if (temp != 0) {
            *x_84ff873b /= temp;
            *x_2092f891 /= temp;
            if (*x_84ff873b < 0) {
                *x_ee71e5cb = -*x_84ff873b;
            } else {
                *x_ee71e5cb = *x_84ff873b;
            }
        }
    }
}

void cam_ko_orbit(Object *obj) {
    s32 pad[2];
    s32 x_fc517ba8;
    u32 ft4;
    s16 a1;
    s16 x_4ffe2260;
    x_88f11482 x_32f1d6e2 = { -200, 0, 0, 0 };

    x_6f8aa7af = FALSE;

    if (x_435c561d.x > x_32f1d6e2.x) {
        if (x_435c561d.x - 5 > x_32f1d6e2.x) {
            x_435c561d.x = x_435c561d.x - 5;
        } else {
            x_435c561d.x = x_32f1d6e2.x;
        }
    } else if (x_435c561d.x < x_32f1d6e2.x) {
        if (x_435c561d.x + 5 < x_32f1d6e2.x) {
            x_435c561d.x = x_435c561d.x + 5;
        } else {
            x_435c561d.x = x_32f1d6e2.x;
        }
    }

    if (x_435c561d.z > x_32f1d6e2.z) {
        if (x_435c561d.z - 5 > x_32f1d6e2.z) {
            x_435c561d.z = x_435c561d.z - 5;
        } else {
            x_435c561d.z = x_32f1d6e2.z;
        }
    } else if (x_435c561d.z < x_32f1d6e2.z) {
        if (x_435c561d.z + 5 < x_32f1d6e2.z) {
            x_435c561d.z = x_435c561d.z + 5;
        } else {
            x_435c561d.z = x_32f1d6e2.z;
        }
    }

    ft4 = sqrtf(x_84ce1cfb(obj->pos.x - x_435c561d.x) + x_84ce1cfb(obj->pos.z - x_435c561d.z)) + 0.5;
    a1 = obj->x_0f4167b4[1];
    a1 = (a1 + x_0525ed93) & 0xFFF;
    obj->x_0f4167b4[1] = x_4ffe2260 = a1;
    x_fc517ba8 = (s32) ft4 + x_b227e464;
    if (x_b227e464 > 0 && x_fc517ba8 > 1800) {
        x_b227e464 = -x_b227e464;
    }
    if (x_b227e464 < 0 && x_fc517ba8 < 1500) {
        x_b227e464 = -x_b227e464;
    }

    obj->pos.x = ((sin_fixed(x_4ffe2260) * x_fc517ba8) >> 12) + x_435c561d.x;
    obj->pos.z = (((-sin_fixed(x_4ffe2260 + 0x400)) * x_fc517ba8) >> 12) + x_435c561d.z;
    obj->pos.y += x_aba11848;
    if (x_aba11848 > 0 && obj->pos.y > -360) {
        x_aba11848 = -x_aba11848;
    }
    if (x_aba11848 < 0 && obj->pos.y < -1200) {
        x_aba11848 = -x_aba11848;
    }
}

void cam_ko_init(Object *obj, s32 x_84ff873b) {
    s32 x_5bbba600;
    s32 x_dd7ffac5;

    x_5bbba600 = obj->pos.x - x_435c561d.x;
    x_dd7ffac5 = obj->pos.z - x_435c561d.z;
    x_0525ed93 = (guRandom() % 2) + 2;
    x_aba11848 = -1;
    x_b227e464 = (guRandom() % 2) + 1;
    obj->currentTask->callback = cam_ko_orbit;
    obj->currentTask->delay = 0;
    obj->x_0f4167b4[3] = x_84ff873b;
    obj->x_0f4167b4[1] = atan2_lut(x_dd7ffac5, x_5bbba600);
    cam_ko_orbit(obj);
}

u8 x_04c83de3 = TRUE;

void cam_battle_update(Object *obj) {
    s32 x_24cd786b;
    s32 x_d27706a3;
    s32 x_f2d104c6;
    s32 x_8b060a59;
    s32 x_1e9ad2e0;
    s32 x_d090e95e[3];
    s32 spEC;
    s32 x_e6efd229;
    s32 x_cadba9e3;
    s32 x_e5752d05;
    s32 x_887ded02;
    s32 x_5fd741dc;
    s32 x_7513cd6a;
    s32 x_6e851264;
    s32 x_6b913371;
    s32 x_8c5f8c03;
    s32 x_13ac4811[11];
    s32 x_d753d975;
    s32 x_3ddc7998[5];
    x_88f11482 x_8a9089b3;
    x_2758cdab x_af0e6490;
    u8 x_3bbf0098;
    u8 x_91b5b40f;
    s32 v02;
    f32 x_331089fa;
    f32 x_840385a0;
    f32 x_fd09f53e;
    f32 x_de61763c;
    f32 x_2a89e429;
    f32 x_54406eae;
    f32 x_f10a928a;
    f32 x_fc517ba8;
    x_88f11482 x_93463df6;

    x_91b5b40f = FALSE;
    if (sHudActive == 0) {
        gGfxFlags |= GFX_MENU_OVERLAY;
    } else {
        gGfxFlags &= ~GFX_MENU_OVERLAY;
    }

    cam_distance_update(FALSE);

    if (gFighterDistance > 800) {
        spEC = ((gFighterDistance - 800) * x_fb93483b) >> 0x10;
    } else {
        spEC = 0;
    }
    if (spEC > x_6db70595) {
        spEC = x_6db70595;
    }

    x_e5752d05 = obj->x_0f4167b4[2];
    x_5fd741dc = spEC - x_e5752d05;
    x_f2d104c6 = obj->x_0f4167b4[1];

    v02 = angle_diff(sMenuState, x_f2d104c6);
    if (v02 < 0) {
        x_d27706a3 = v02 + x_19369121;
    } else {
        x_d27706a3 = v02 - x_19369121;
    }

    cam_face_players();

    if (angle_diff(sMenuState, x_f2d104c6) > 0) {
        sIntroPlayerObjs[x_83106b21]->flags &= ~x_6c2d42ba;
        x_59ce598c[x_83106b21].x_d93bcabf = FALSE;
        sIntroPlayerObjs[x_6f0b3be3]->flags |= x_6c2d42ba;
        x_59ce598c[x_6f0b3be3].x_d93bcabf = TRUE;
    } else {
        sIntroPlayerObjs[x_83106b21]->flags |= x_6c2d42ba;
        x_59ce598c[x_83106b21].x_d93bcabf = TRUE;
        sIntroPlayerObjs[x_6f0b3be3]->flags &= ~x_6c2d42ba;
        x_59ce598c[x_6f0b3be3].x_d93bcabf = FALSE;
    }

    if (iabs(x_d27706a3) < 450 && x_f6ef18bf < 0x20000) {
        x_db28d0d1 = 30;
        x_f6ef18bf = 0;
        x_91b5b40f = 1;
        x_e1e12448 = 0;
        x_24cd786b = x_f2d104c6;
    } else if (iabs(x_d27706a3) > 450 && x_f6ef18bf < 0xA0000) {
        x_f6ef18bf += 0x2000;
        x_c7298ffb = x_f6ef18bf >> 16;
        if (x_d27706a3 < -x_c7298ffb) {
            x_d27706a3 = -x_c7298ffb;
        } else if (x_d27706a3 > x_c7298ffb) {
            x_d27706a3 = x_c7298ffb;
        }
        x_e1e12448 = x_d27706a3;
        x_24cd786b = x_f2d104c6 + x_d27706a3;
    } else {
        x_f6ef18bf -= 0x3000;
        x_c7298ffb = x_f6ef18bf >> 16;
        if (x_d27706a3 < -x_c7298ffb) {
            x_d27706a3 = -x_c7298ffb;
        } else if (x_d27706a3 > x_c7298ffb) {
            x_d27706a3 = x_c7298ffb;
        }
        x_e1e12448 = x_d27706a3;
        x_24cd786b = x_f2d104c6 + x_d27706a3;
    }

    obj->x_0f4167b4[1] = x_24cd786b;

    if (iabs(x_5fd741dc) < x_e700b1a3 && x_9991d607 == 0) {
        spEC = x_e5752d05;
    } else {
        if (abs(x_5fd741dc) < x_63e0d71b) {
            if (x_15bf92fd < x_b8d38fc7 - x_452e0082) {
                x_b8d38fc7 -= x_c2f1d98b;
            } else {
                x_b8d38fc7 = x_15bf92fd;
            }
        } else if (x_b8d38fc7 + x_79389416 < x_1c1ecf0d) {
            x_b8d38fc7 += x_452e0082;
        } else {
            x_b8d38fc7 = x_fef2140c;
        }

        D_8013C370 = x_b8d38fc7 >> 0x10;

        if (x_5fd741dc < -D_8013C370) {
            x_5fd741dc = -D_8013C370;
        } else if (x_5fd741dc > D_8013C370) {
            x_5fd741dc = D_8013C370;
        }
        x_9991d607 = x_5fd741dc;
        spEC = x_e5752d05 + x_5fd741dc;
    }

    x_93463df6.x = sCharSelectSpriteA->x;
    x_93463df6.y = x_824b9544[x_83106b21].x_5c5b1d93.x_b7552092->y;
    x_93463df6.z = sCharSelectSpriteA->z;
    cam_project_point(&x_93463df6, &x_331089fa, &x_840385a0, &x_2a89e429);

    x_93463df6.x = sCharSelectSpriteB->x;
    x_93463df6.y = x_824b9544[x_6f0b3be3].x_5c5b1d93.x_b7552092->y;
    x_93463df6.z = sCharSelectSpriteB->z;
    cam_project_point(&x_93463df6, &x_fd09f53e, &x_de61763c, &x_54406eae);

    if (x_b64f16b7 < 250 && (x_de61763c > 0.6 || x_840385a0 > 0.6)) {
        x_840385a0 = MAX(x_de61763c, x_840385a0);
        x_840385a0 -= 0.6;
        spEC = x_e5752d05 + x_840385a0 * 700;
        x_b64f16b7 += x_840385a0 * 60;
        x_881ee8c3 -= x_840385a0 * 30;
        x_7450a2d3 += x_b221ddda;
        x_1e5afea8 += x_840385a0 * 2;
    } else if (x_de61763c <= 0.6 && x_840385a0 <= 0.6) {
        if (x_b64f16b7 > 8) {
            x_b64f16b7 -= 8;
            x_881ee8c3 += 4;
        } else {
            x_b64f16b7 = x_881ee8c3 = 0;
        }

        if (x_1e5afea8 != 0) {
            x_1e5afea8--;
        }

        if (x_2a89e429 > 0.65 || x_54406eae > 0.65) {
            x_2a89e429 = MAX(x_54406eae, x_2a89e429);
            x_2a89e429 -= 0.65;
            if (x_2a89e429 < 0.55) {
                spEC = x_e5752d05 + x_2a89e429 * 600;
            }
        }
    } else {
        spEC = x_e5752d05;
    }

    if (spEC > 6500) {
        spEC = 6500;
    }
    obj->x_0f4167b4[2] = spEC;

    x_6c647b3a = D_8013C82C + x_1e5afea8 - (s32) (x_cf60a652 * 0.2f);
    if (spEC > 1500 && x_6c647b3a < -24) {
        x_6c647b3a = -24;
    }

    x_435c561d.y = ((x_6d4a1d2c * spEC) >> 16) + x_881ee8c3 - 480;

    x_93463df6.x = (sCharSelectSpriteB->x + sCharSelectSpriteA->x) >> 1;
    x_93463df6.z = (sCharSelectSpriteB->z + sCharSelectSpriteA->z) >> 1;
    x_93463df6.y = -480;
    cam_project_point(&x_93463df6, &x_f10a928a, &x_fc517ba8, &x_2a89e429);

    x_3bbf0098 = x_2a89e429 > 0.2f;
    x_8b060a59 = ((sCharSelectSpriteB->x + sCharSelectSpriteA->x) >> 1) - x_435c561d.x;
    x_1e9ad2e0 = ((sCharSelectSpriteB->z + sCharSelectSpriteA->z) >> 1) - x_435c561d.z;

    if (iabs(x_8b060a59) > x_e3ea1dcb || iabs(x_1e9ad2e0) > x_e3ea1dcb || x_04c83de3) {
        if (abs(x_8b060a59) < x_7eb21652 && abs(x_1e9ad2e0) < x_7eb21652) {
            if (x_08b122d8 - x_79389416 > x_e4130b8b) {
                x_08b122d8 -= x_e21927eb; // @bug ??
            } else {
                x_08b122d8 = x_e4130b8b;
            }
        } else {
            if (x_08b122d8 + x_79389416 < x_1c1ecf0d) {
                x_08b122d8 += x_79389416;
            } else {
                x_08b122d8 = x_1c1ecf0d;
            }
        }

        D_8013C370 = x_08b122d8 >> 16;

        if (x_8b060a59 < -D_8013C370) {
            x_8b060a59 = -D_8013C370;
        } else if (x_8b060a59 > D_8013C370) {
            x_8b060a59 = D_8013C370;
        }

        if (x_1e9ad2e0 < -D_8013C370) {
            x_1e9ad2e0 = -D_8013C370;
        } else if (x_1e9ad2e0 > D_8013C370) {
            x_1e9ad2e0 = D_8013C370;
        }

        x_04c83de3 = ((x_8b060a59 != 0) || (x_1e9ad2e0 != 0));

        x_435c561d.x += x_8b060a59;
        x_435c561d.z += x_1e9ad2e0;

        if (x_91b5b40f && x_3bbf0098 && (x_1e9ad2e0 != 0 || x_8b060a59 != 0)) {
            x_8a9089b3.x = x_8b060a59;
            x_8a9089b3.z = -x_1e9ad2e0;

            x_af0e6490.y = (0x400 - x_4c17a2ba) & 0xFFF;
            x_af0e6490.x = x_af0e6490.z = 0;
            vec_rotate_by_euler(&x_8a9089b3, &x_af0e6490);

            if (x_8a9089b3.x > 0) {
                x_d753d975 = (u32) (sqrtf(x_8b060a59 * x_8b060a59 + x_1e9ad2e0 * x_1e9ad2e0) + 0.5) >> 1;
            } else if (x_8a9089b3.x < 0) {
                x_d753d975 = -((u32) (sqrtf(x_8b060a59 * x_8b060a59 + x_1e9ad2e0 * x_1e9ad2e0) + 0.5) >> 1);
            }

            if (x_d753d975 > 2) {
                x_d753d975 = 2;
            }
            if (x_d753d975 < -2) {
                x_d753d975 = -2;
            }
            x_e74df613 += x_d753d975;
        }
    }

    x_e6efd229 = ((sin_fixed(x_24cd786b) * x_22f06603) >> 12) + x_435c561d.x;
    x_cadba9e3 = ((-sin_fixed(x_24cd786b + 0x400) * x_22f06603) >> 12) + x_435c561d.z;
    x_6e851264 = (sin_fixed(x_24cd786b) * x_49bdae1a) >> 12;
    x_6b913371 = (-sin_fixed(x_24cd786b + 0x400) * x_49bdae1a) >> 12;
    x_8c5f8c03 = (spEC * x_d86fab4d) >> 12;

    obj->pos.x = ((spEC * x_6e851264) >> 12) + x_e6efd229;
    obj->pos.z = ((spEC * x_6b913371) >> 12) + x_cadba9e3;
    obj->pos.y = x_d85eefcc + x_b64f16b7 - x_8c5f8c03;

    D_80081428 = D_8013C828;

    if (*x_f4bce728->x_20d20338->x_50771dcd == NULL && !(x_824b9544[x_83106b21].flags & x_c865be3f) &&
            !(x_824b9544[x_6f0b3be3].flags & x_c865be3f) ||
        sHudActive != 0) {
        cam_boundary_check(obj);
    }
}
