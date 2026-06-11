#include "common.h"
#include "task.h"

x_6751d717 sColorRed = { 255, 0, 0, 0 };
x_6751d717 sColorBlue = { 0, 0, 255, 0 };

/* .bss */
s32 sCombatPad[2];
x_2758cdab sScratchPos;
s32 sCombatScratch;
Model *sHitModelRegular;
Model *sHitModelGrab;

void hit_effect_fade_slow(Object *obj) {
    if (obj->frameCounter < obj->x_20d20338->x_8e601526) {
        gGfxFlags |= GFX_SHADOW_MODE;
        obj->frameCounter++;
        if (obj->frameCounter > 12) {
            if (obj->color.a > obj->x_0f4167b4[0]) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
            }
        }
    } else {
        obj->flags |= x_f51cb721;
        gGfxFlags &= ~GFX_SHADOW_MODE;
        TASK_END(obj->currentTask);
    }
}

void hit_effect_fade_fast(Object *obj) {
    if (obj->frameCounter < obj->x_20d20338->x_8e601526) {
        gGfxFlags |= GFX_SHADOW_MODE;
        obj->frameCounter++;
        if (obj->frameCounter > 2) {
            if (obj->color.a > obj->x_0f4167b4[0]) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
            }
        }
    } else {
        gGfxFlags &= ~GFX_SHADOW_MODE;
        obj->flags |= x_f51cb721;
        TASK_END(obj->currentTask);
    }
}

void spawn_hit_effect(x_2758cdab *pos, u8 x_0328a4c8, Object *x_2092f891, x_6751d717 *x_ee71e5cb) {
    Object *v0;
    x_88f11482 x_5bbba600;
    Player *x_dd7ffac5;
    Player *x_4346f5cb;

    x_dd7ffac5 = (Player *) x_2092f891->x_e2f64c57[0];
    x_4346f5cb = x_824b9544 + (1 - x_dd7ffac5->x_30bbe547);

    x_5bbba600.x = pos->x;
    x_5bbba600.y = pos->y;
    x_5bbba600.z = pos->z;

    if (x_0328a4c8) {
        v0 = obj_create_with_model_ptr(&x_5bbba600, x_9d442987, hit_effect_fade_fast, sHitModelGrab);
        if (v0 != NULL) {
            v0->x_0f4167b4[0] = 255 / (v0->x_20d20338->x_8e601526 - 2);
            v0->flags |= x_b6789b80;
            model_light_attach(v0, &sColorBlue);
            v0->color.a = 255;
        }

        if (x_ee71e5cb == NULL) {
            x_ee71e5cb = &D_8004B844[x_4346f5cb->x_eb1fe45b].x_732aef72[x_4346f5cb->x_30bbe547];
        }
        spark_spawn(pos, x_2092f891, x_ee71e5cb);
    } else {
        v0 = obj_create_with_model_ptr(&x_5bbba600, x_9d442987, hit_effect_fade_slow, sHitModelRegular);
        if (v0 != NULL) {
            v0->x_0f4167b4[0] = 255 / (v0->x_20d20338->x_8e601526 - 12);
            v0->flags |= x_b6789b80;
            model_light_attach(v0, &sColorRed);
            v0->color.a = 255;
        }
    }
}

u8 point_in_hit_range(x_2758cdab *x_cc1d0de5, x_88f11482 *x_84ff873b, u32 x_72eb45b1, x_2758cdab *point) {
    s16 x1, z1;

    if (point->y < x_cc1d0de5->y - 200 || x_84ff873b->y < point->y) {
        return FALSE;
    }

    x1 = (x_cc1d0de5->x + x_84ff873b->x) * 0.5f;
    z1 = (x_cc1d0de5->z + x_84ff873b->z) * 0.5f;

    if (x_84ce1cfb(x1 - point->x) + x_84ce1cfb(z1 - point->z) < x_72eb45b1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

x_2758cdab *find_collision_point(x_2758cdab *x_65d81f5e, x_88f11482 *x_6530585f, u32 x_72eb45b1, x_2758cdab *x_c593269c,
                                 x_2758cdab *x_dedb5b95) {
    s16 x_2ec7c161, x_ef312970;
    s32 x_720f6ac9, dz;
    s32 pad[4];
    s16 x_b6150ad6, x_753494c4, x_71984ce4;

    x_2ec7c161 = (x_65d81f5e->x + x_6530585f->x) >> 1;
    x_ef312970 = (x_65d81f5e->z + x_6530585f->z) >> 1;

    if (x_c593269c->y > x_65d81f5e->y - 200 && x_c593269c->y < x_6530585f->y) {
        x_720f6ac9 = x_2ec7c161 - x_c593269c->x;
        dz = x_ef312970 - x_c593269c->z;
        if (x_84ce1cfb(x_720f6ac9) + x_84ce1cfb(dz) < x_72eb45b1) {
            return x_c593269c;
        }
    }

    if (x_dedb5b95->y > x_65d81f5e->y - 200 && x_dedb5b95->y < x_6530585f->y) {
        x_720f6ac9 = x_2ec7c161 - x_dedb5b95->x;
        dz = x_ef312970 - x_dedb5b95->z;
        if (x_84ce1cfb(x_720f6ac9) + x_84ce1cfb(dz) < x_72eb45b1) {
            return x_dedb5b95;
        }
    }

    x_b6150ad6 = sScratchPos.x = (x_c593269c->x + x_dedb5b95->x) >> 1;
    x_753494c4 = sScratchPos.y = (x_c593269c->y + x_dedb5b95->y) >> 1;
    x_71984ce4 = sScratchPos.z = (x_c593269c->z + x_dedb5b95->z) >> 1;

    if (sScratchPos.y > x_65d81f5e->y - 200 && sScratchPos.y < x_6530585f->y) {
        x_720f6ac9 = x_2ec7c161 - sScratchPos.x;
        dz = x_ef312970 - sScratchPos.z;
        if (x_84ce1cfb(x_720f6ac9) + x_84ce1cfb(dz) < x_72eb45b1) {
            return &sScratchPos;
        }
    }

    sScratchPos.x = (x_b6150ad6 + x_dedb5b95->x) >> 1;
    sScratchPos.y = (x_753494c4 + x_dedb5b95->y) >> 1;
    sScratchPos.z = (x_71984ce4 + x_dedb5b95->z) >> 1;

    if (sScratchPos.y > x_65d81f5e->y - 200 && sScratchPos.y < x_6530585f->y) {
        x_720f6ac9 = x_2ec7c161 - sScratchPos.x;
        dz = x_ef312970 - sScratchPos.z;
        if (x_84ce1cfb(x_720f6ac9) + x_84ce1cfb(dz) < x_72eb45b1) {
            return &sScratchPos;
        }
    }

    sScratchPos.x = (x_b6150ad6 + x_c593269c->x) >> 1;
    sScratchPos.y = (x_753494c4 + x_c593269c->y) >> 1;
    sScratchPos.z = (x_71984ce4 + x_c593269c->z) >> 1;

    if (sScratchPos.y > x_65d81f5e->y - 200 && sScratchPos.y < x_6530585f->y) {
        x_720f6ac9 = x_2ec7c161 - sScratchPos.x;
        dz = x_ef312970 - sScratchPos.z;
        if (x_84ce1cfb(x_720f6ac9) + x_84ce1cfb(dz) < x_72eb45b1) {
            return &sScratchPos;
        }
    }

    return NULL;
}

#ifdef NON_MATCHING
s32 hit_outcome(Player *x_7246d2b2, Player *x_e64ba38a, x_388306ba *x_0deedaaf) {
    x_388306ba *x_cd232430;
    s32 hp;
    s32 pad;
    s16 pad2;
    s16 x_0f12118c;
    u8 v1;
    u8 v12;
    s32 x_b0a612ba;

    x_0f12118c = 0;
    x_cd232430 = x_7246d2b2->x_7f68c36b;
    x_b0a612ba = x_cd232430->flags;

    if ((x_b0a612ba & (x_025a12b8 | x_36377d70)) &&
        x_7246d2b2->obj->pos.y + x_7246d2b2->obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y > -400.0f &&
        x_7246d2b2->x_5c5b1d93.x_6e7f4fd8->y - x_7246d2b2->x_5c5b1d93.x_b7552092->y > 200.0f) {
        x_b0a612ba &= ~(x_025a12b8 | x_36377d70);
        x_b0a612ba |= x_ff05097f;
    }

    v1 = (x_b0a612ba & x_cdcff2e1) && (x_7246d2b2->obj->frameCounter >= 12);

    if (x_b0a612ba & x_f79587cb) {
        if (x_b0a612ba & x_ff05097f) {
            x_0f12118c = x_0deedaaf->x_40be83c8;
        } else {
            x_0f12118c = x_0deedaaf->x_b033c680;
        }
    } else if (x_b0a612ba & x_8b64a078) {
        x_0f12118c = x_0deedaaf->x_6290ef5a;
    } else if (x_b0a612ba & x_c1df43e1) {
        x_0f12118c = x_0deedaaf->x_2955cef8;
    } else if ((x_b0a612ba & x_eac5209f) && x_0deedaaf->x_fbb09ed1 != 0) {
        if (x_b0a612ba & x_7507aa4b) {
            x_0f12118c = x_caa30513; // slammed face down
        } else {
            x_0f12118c = x_dba71d7e; // slammed face up
        }
    } else if (hit_check_facing_away(x_7246d2b2->obj) && !v1) {
        if (x_b0a612ba & (x_025a12b8 | x_ff05097f | x_36377d70)) {
            x_0f12118c = x_0deedaaf->x_c33946bb;
        } else if (x_b0a612ba & x_037894c1) {
            x_0f12118c = x_0deedaaf->x_cdc30d39;
        }

        if (x_b0a612ba & (x_025a12b8 | x_36377d70)) {
            x_0f12118c = x_0deedaaf->x_dc90c3b6;
        } else {
            x_7246d2b2->obj->pos.y = 0;
        }

        x_7246d2b2->obj->flags &= ~x_da584e3c;
    } else {
        if (x_b0a612ba & (x_025a12b8 | x_ff05097f | x_36377d70)) {
            x_0f12118c = x_0deedaaf->x_237b8772;
        } else if (x_b0a612ba & x_037894c1) {
            x_0f12118c = x_0deedaaf->x_71357e64;
        }

        if (x_b0a612ba & (x_025a12b8 | x_36377d70)) {
            x_0f12118c = x_0deedaaf->x_d3699524;
        } else {
            x_7246d2b2->obj->pos.y = 0;
        }
    }

    v12 = (x_0f12118c == x_3cc3613b) || (x_0f12118c == x_5a136108);

    if (x_0f12118c != 0 && !x_33abac12) {
        x_e64ba38a->x_6f5a5c61 = x_0deedaaf->x_6f5a5c61;
        if (x_e64ba38a->obj->x_0f4167b4[3] < 0) {
            x_e64ba38a->x_95a50856 += x_e64ba38a->x_6f5a5c61;
        } else {
            x_e64ba38a->x_95a50856 = x_e64ba38a->x_6f5a5c61;
            x_e64ba38a->obj->x_0f4167b4[3] = -1;
        }

        if (x_0f12118c >= x_fcce1abe && x_0f12118c <= x_0ba1d6d3) {
            // CoGrabbed
            x_7246d2b2->obj->x_0f4167b4[2] = x_0deedaaf->x_6f5a5c61;
        } else if (!v12 && x_5e4e2788 != x_79c2dc5b) {
            x_7246d2b2->obj->x_9200c538 -= x_0deedaaf->x_6f5a5c61;
        }

        hp = x_7246d2b2->obj->x_9200c538;
        if (hp < 0) {
            hp = x_7246d2b2->obj->x_9200c538 = 0;
        }

        if (hp == 0) {
            x_e30d50d2 |= x_dd99cbfb;
            if (x_7246d2b2->flags & x_9298c772) {
                if (x_b0a612ba & x_ff05097f) {
                    x_0f12118c = x_235050ce;
                } else if (x_b0a612ba & x_037894c1) {
                    x_0f12118c = x_f959531a;
                }
            } else {
                if (x_b0a612ba & x_ff05097f) {
                    x_0f12118c = x_8a72e76c;
                } else if (x_b0a612ba & x_037894c1) {
                    x_0f12118c = x_13b6becb;
                }
            }
        }

        player_exec_move_ai(x_7246d2b2, x_0f12118c, TRUE);
    }

    return x_0f12118c;
}
#else
s32 hit_outcome(Player *x_cc1d0de5, Player *x_84ff873b, x_388306ba *x_2092f891);
#pragma GLOBAL_ASM("asm/nonmatchings/combat/hit_outcome.s")
#endif

void apply_hit(Player *x_7246d2b2, Player *x_e64ba38a, x_2758cdab *x_c9d501a3) {
    s32 x_0f12118c;
    s16 x_2a9ef16e;
    x_388306ba *x_ed035b81;

    x_ed035b81 = x_e64ba38a->x_7f68c36b;

    if (!x_9df63a90 || x_33abac12) {
        x_0f12118c = hit_outcome(x_7246d2b2, x_e64ba38a, x_ed035b81);
        x_2a9ef16e = x_0f12118c == 270 || x_0f12118c == 271;
        if (x_0f12118c != 0) {
            spawn_hit_effect(x_c9d501a3, x_2a9ef16e, x_7246d2b2->obj, NULL);
            x_7246d2b2->x_381817ae = 13;
            x_e64ba38a->x_381817ae = 2;
        }
    }
}

void hit_detect_lower(Player *x_7246d2b2, Player *x_e64ba38a) {
    x_88f11482 *x_c593269c;
    x_2758cdab x_6530585f;
    x_2758cdab x_a76dcbae;
    x_2758cdab x_dedb5b95;
    x_2758cdab x_65d81f5e;
    x_2758cdab x_7bbf202d;
    x_2758cdab *x_c9d501a3;
    s32 pad[70];
    Transform *x_de61763c;
    x_998ccc48 *x_681b4659;
    x_998ccc48 *x_2972e837;
    s32 pad2[6];

    x_c593269c = &x_7246d2b2->obj->pos;

    x_681b4659 = &x_7246d2b2->x_5c5b1d93;
    x_2972e837 = &x_e64ba38a->x_5c5b1d93;

    x_dedb5b95.x = x_681b4659->x_b7552092->x;
    x_dedb5b95.y = x_681b4659->x_b7552092->y;
    x_dedb5b95.z = x_681b4659->x_b7552092->z;

    x_65d81f5e.x = x_2972e837->x_55f532bb->x;
    x_65d81f5e.y = x_2972e837->x_55f532bb->y;
    x_65d81f5e.z = x_2972e837->x_55f532bb->z;

    if (x_2972e837->x_c01445c3) {
        x_6530585f.x = x_2972e837->x_cc2c17a6.x_0c1a9bdd.w.x;
        x_6530585f.y = x_2972e837->x_cc2c17a6.x_0c1a9bdd.w.y;
        x_6530585f.z = x_2972e837->x_cc2c17a6.x_0c1a9bdd.w.z;

        x_c9d501a3 =
            find_collision_point(&x_dedb5b95, x_c593269c, x_681b4659->x_62706fff + 55000, &x_65d81f5e, &x_6530585f);
        if (x_c9d501a3 != NULL) {
            if (x_c9d501a3->y < x_dedb5b95.y) {
                x_c9d501a3->y = x_dedb5b95.y;
            }

            x_c9d501a3->x = ((sin_fixed((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) * 100) >> 12) + x_c593269c->x;
            x_c9d501a3->z =
                ((-sin_fixed(((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) + 0x400) * 100) >> 12) + x_c593269c->z;
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
            return;
        }
    } else if (point_in_hit_range(&x_dedb5b95, x_c593269c, x_681b4659->x_62706fff, &x_65d81f5e)) {
        if (x_65d81f5e.y < x_dedb5b95.y) {
            x_65d81f5e.y = x_dedb5b95.y;
        }
        x_65d81f5e.x = ((sin_fixed((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) * 100) >> 12) + x_c593269c->x;
        x_65d81f5e.z =
            ((-sin_fixed(((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) + 0x400) * 100) >> 12) + x_c593269c->z;
        apply_hit(x_7246d2b2, x_e64ba38a, &x_65d81f5e);
        return;
    }

    x_7bbf202d.x = x_2972e837->x_3b24b185->x;
    x_7bbf202d.y = x_2972e837->x_3b24b185->y;
    x_7bbf202d.z = x_2972e837->x_3b24b185->z;

    if (x_2972e837->x_a1c57a3b) {
        x_de61763c = &x_2972e837->x_0548cec6;
        x_a76dcbae.x = x_2972e837->x_0548cec6.x_0c1a9bdd.w.x;
        x_a76dcbae.y = x_2972e837->x_0548cec6.x_0c1a9bdd.w.y;
        x_a76dcbae.z = x_2972e837->x_0548cec6.x_0c1a9bdd.w.z;

        x_c9d501a3 =
            find_collision_point(&x_dedb5b95, x_c593269c, x_681b4659->x_62706fff + 55000, &x_7bbf202d, &x_a76dcbae);
        if (x_c9d501a3 != NULL) {
            if (x_c9d501a3->y < x_dedb5b95.y) {
                x_c9d501a3->y = x_dedb5b95.y;
            }

            x_c9d501a3->x = ((sin_fixed((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) * 100) >> 12) + x_c593269c->x;
            x_c9d501a3->z =
                ((-sin_fixed(((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) + 0x400) * 100) >> 12) + x_c593269c->z;
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
            return;
        }
    } else if (point_in_hit_range(&x_dedb5b95, x_c593269c, x_681b4659->x_62706fff, &x_7bbf202d)) {
        if (x_7bbf202d.y < x_dedb5b95.y) {
            x_7bbf202d.y = x_dedb5b95.y;
        }
        x_7bbf202d.x = ((sin_fixed((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) * 100) >> 12) + x_c593269c->x;
        x_7bbf202d.z =
            ((-sin_fixed(((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) + 0x400) * 100) >> 12) + x_c593269c->z;
        apply_hit(x_7246d2b2, x_e64ba38a, &x_7bbf202d);
        return;
    }

    if (x_2972e837->x_b7aa4e8a) {
        if (x_2972e837->x_d8ede1db) {
            // @bug sp54 could be uninitialized?
            x_a76dcbae.x = x_de61763c->x_0c1a9bdd.w.x;
            x_a76dcbae.y = x_de61763c->x_0c1a9bdd.w.y;
            x_a76dcbae.z = x_de61763c->x_0c1a9bdd.w.z;
        } else {
            x_a76dcbae.x = x_2972e837->x_9829da43->x;
            x_a76dcbae.y = x_2972e837->x_9829da43->y;
            x_a76dcbae.z = x_2972e837->x_9829da43->z;
        }

        if (point_in_hit_range(&x_dedb5b95, x_c593269c, x_681b4659->x_38ae036c, &x_a76dcbae)) {
            if (x_a76dcbae.y < x_dedb5b95.y) {
                x_a76dcbae.y = x_dedb5b95.y;
            }
            x_a76dcbae.x = ((sin_fixed((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) * 100) >> 12) + x_c593269c->x;
            x_a76dcbae.z =
                ((-sin_fixed(((0xC00 - x_7246d2b2->obj->x_224610f1.y) & 0xFFF) + 0x400) * 100) >> 12) + x_c593269c->z;
            apply_hit(x_7246d2b2, x_e64ba38a, &x_a76dcbae);
        }
    }
}

void hit_detect_upper(Player *x_7246d2b2, Player *x_e64ba38a) {
    x_88f11482 *x_c593269c;
    x_2758cdab x_319ebd5a;
    x_2758cdab x_65d81f5e;
    x_2758cdab x_6530585f;
    x_998ccc48 *x_2972e837;
    x_998ccc48 *x_681b4659;
    u32 radius;
    x_2758cdab *x_c9d501a3;
    u8 v0;

    x_c593269c = &x_7246d2b2->obj->pos;

    x_2972e837 = &x_e64ba38a->x_5c5b1d93;
    x_681b4659 = &x_7246d2b2->x_5c5b1d93;

    x_319ebd5a.x = x_681b4659->x_b7552092->x;
    x_319ebd5a.y = x_681b4659->x_b7552092->y;
    x_319ebd5a.z = x_681b4659->x_b7552092->z;

    if (x_2972e837->x_22014d8c) {
        x_65d81f5e.x = x_2972e837->x_45875993.x_0c1a9bdd.w.x;
        x_65d81f5e.y = x_2972e837->x_45875993.x_0c1a9bdd.w.y;
        x_65d81f5e.z = x_2972e837->x_45875993.x_0c1a9bdd.w.z;
    } else {
        x_65d81f5e.x = x_2972e837->x_1b148bc2->x;
        x_65d81f5e.y = x_2972e837->x_1b148bc2->y;
        x_65d81f5e.z = x_2972e837->x_1b148bc2->z;
    }

    x_6530585f.x = x_2972e837->x_ef41f475->x;
    x_6530585f.y = x_2972e837->x_ef41f475->y;
    x_6530585f.z = x_2972e837->x_ef41f475->z;

    v0 = (x_e64ba38a->x_7f68c36b->flags & x_bd969186) || (x_65d81f5e.y < -200);

    if (x_65d81f5e.y < x_681b4659->x_ef41f475->y) {
        radius = x_681b4659->x_62706fff;
    } else {
        radius = x_681b4659->x_38ae036c;
    }

    if (v0) {
        x_c9d501a3 = find_collision_point(&x_319ebd5a, x_c593269c, radius, &x_6530585f, &x_65d81f5e);
        if (x_c9d501a3 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
            return;
        }
    }

    if (x_2972e837->x_6216b7a1) {
        x_65d81f5e.x = x_2972e837->x_20d81af7.x_0c1a9bdd.w.x;
        x_65d81f5e.y = x_2972e837->x_20d81af7.x_0c1a9bdd.w.y;
        x_65d81f5e.z = x_2972e837->x_20d81af7.x_0c1a9bdd.w.z;
    } else {
        x_65d81f5e.x = x_2972e837->x_6e7f4fd8->x;
        x_65d81f5e.y = x_2972e837->x_6e7f4fd8->y;
        x_65d81f5e.z = x_2972e837->x_6e7f4fd8->z;
    }

    x_6530585f.x = x_2972e837->x_4c227952->x;
    x_6530585f.y = x_2972e837->x_4c227952->y;
    x_6530585f.z = x_2972e837->x_4c227952->z;

    if (x_65d81f5e.y < x_681b4659->x_4c227952->y) {
        radius = x_681b4659->x_62706fff;
    } else {
        radius = x_681b4659->x_38ae036c;
    }

    v0 = (x_e64ba38a->x_7f68c36b->flags & x_0fe9e7f2) || (x_65d81f5e.y < -200);

    if (v0) {
        x_c9d501a3 = find_collision_point(&x_319ebd5a, x_c593269c, radius, &x_6530585f, &x_65d81f5e);
        if (x_c9d501a3 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
        }
    }
}

void hit_detect_grounded_a(Player *x_7246d2b2, Player *x_e64ba38a) {
    x_998ccc48 *x_681b4659;
    x_998ccc48 *x_2972e837;
    x_2758cdab x_c593269c;
    x_2758cdab x_dedb5b95;
    x_2758cdab x_65d81f5e;
    x_88f11482 x_6530585f;
    x_2758cdab *x_c9d501a3;
    s32 pad;

    x_681b4659 = &x_7246d2b2->x_5c5b1d93;
    x_2972e837 = &x_e64ba38a->x_5c5b1d93;

    if (x_e64ba38a->obj->pos.y < -20 ||
        x_e64ba38a->obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y < x_e64ba38a->obj->x_20d20338->x_9cfd7bb4.y) {
        return;
    }

    x_c593269c.x = x_681b4659->x_b7552092->x;
    x_c593269c.y = x_681b4659->x_b7552092->y;
    x_c593269c.z = x_681b4659->x_b7552092->z;

    x_dedb5b95.x = x_681b4659->x_1b148bc2->x;
    x_dedb5b95.y = x_681b4659->x_1b148bc2->y;
    x_dedb5b95.z = x_681b4659->x_1b148bc2->z;

    x_65d81f5e.x = x_2972e837->x_82e589d5->x;
    x_65d81f5e.z = x_2972e837->x_82e589d5->z;
    x_65d81f5e.y = x_2972e837->x_82e589d5->y - 100.0f;

    x_6530585f.x = x_2972e837->x_82e589d5->x;
    x_6530585f.z = x_2972e837->x_82e589d5->z;
    x_6530585f.y = x_2972e837->x_82e589d5->y;

    x_c9d501a3 = find_collision_point(&x_65d81f5e, &x_6530585f, 80000, &x_c593269c, &x_dedb5b95);
    if (x_c9d501a3 != NULL) {
        apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
        return;
    }

    if (x_2972e837->x_c01445c3) {
        x_65d81f5e.x = x_2972e837->x_cc2c17a6.x_0c1a9bdd.w.x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_cc2c17a6.x_0c1a9bdd.w.z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c9d501a3 = find_collision_point(&x_65d81f5e, &x_6530585f, 15000, &x_c593269c, &x_dedb5b95);
        if (x_c9d501a3 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
            return;
        }
    } else {
        x_65d81f5e.x = x_2972e837->x_55f532bb->x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_55f532bb->z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c9d501a3 = find_collision_point(&x_65d81f5e, &x_6530585f, 15000, &x_c593269c, &x_dedb5b95);
        if (x_c9d501a3 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
            return;
        }
    }

    if (x_2972e837->x_a1c57a3b) {
        x_65d81f5e.x = x_2972e837->x_0548cec6.x_0c1a9bdd.w.x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_0548cec6.x_0c1a9bdd.w.z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c9d501a3 = find_collision_point(&x_65d81f5e, &x_6530585f, 15000, &x_c593269c, &x_dedb5b95);
        if (x_c9d501a3 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
            return;
        }
    } else {
        x_65d81f5e.x = x_2972e837->x_3b24b185->x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_3b24b185->z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c9d501a3 = find_collision_point(&x_65d81f5e, &x_6530585f, 15000, &x_c593269c, &x_dedb5b95);
        if (x_c9d501a3 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c9d501a3);
            return;
        }
    }
}

void hit_detect_grounded_b(Player *x_7246d2b2, Player *x_e64ba38a) {
    x_998ccc48 *x_681b4659;
    x_998ccc48 *x_2972e837;
    x_2758cdab x_c593269c;
    x_2758cdab x_dedb5b95;
    x_2758cdab x_65d81f5e;
    x_88f11482 x_6530585f;
    x_2758cdab *x_c3f1d391;

    x_681b4659 = &x_7246d2b2->x_5c5b1d93;
    x_2972e837 = &x_e64ba38a->x_5c5b1d93;

    if (x_e64ba38a->obj->pos.y < -20 ||
        x_e64ba38a->obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y < x_e64ba38a->obj->x_20d20338->x_9cfd7bb4.y) {
        return;
    }

    x_c593269c.x = x_681b4659->x_b7552092->x;
    x_c593269c.y = x_681b4659->x_b7552092->y;
    x_c593269c.z = x_681b4659->x_b7552092->z;

    x_dedb5b95.x = x_681b4659->x_1b148bc2->x;
    x_dedb5b95.y = x_681b4659->x_1b148bc2->y;
    x_dedb5b95.z = x_681b4659->x_1b148bc2->z;

    x_65d81f5e.x = x_2972e837->x_82e589d5->x;
    x_65d81f5e.z = x_2972e837->x_82e589d5->z;
    x_65d81f5e.y = x_2972e837->x_82e589d5->y - 100.0f;

    x_6530585f.x = x_2972e837->x_82e589d5->x;
    x_6530585f.z = x_2972e837->x_82e589d5->z;
    x_6530585f.y = x_2972e837->x_82e589d5->y;

    x_c3f1d391 = find_collision_point(&x_65d81f5e, &x_6530585f, 80000, &x_c593269c, &x_dedb5b95);
    if (x_c3f1d391 != NULL) {
        apply_hit(x_7246d2b2, x_e64ba38a, x_c3f1d391);
        return;
    }

    if (x_2972e837->x_6216b7a1) {
        x_65d81f5e.x = x_2972e837->x_20d81af7.x_0c1a9bdd.w.x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_20d81af7.x_0c1a9bdd.w.z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c3f1d391 = find_collision_point(&x_65d81f5e, &x_6530585f, 50000, &x_c593269c, &x_dedb5b95);
        if (x_c3f1d391 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c3f1d391);
            return;
        }
    } else {
        x_65d81f5e.x = x_2972e837->x_6e7f4fd8->x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_6e7f4fd8->z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c3f1d391 = find_collision_point(&x_65d81f5e, &x_6530585f, 50000, &x_c593269c, &x_dedb5b95);
        if (x_c3f1d391 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c3f1d391);
            return;
        }
    }

    if (x_2972e837->x_22014d8c) {
        x_65d81f5e.x = x_2972e837->x_45875993.x_0c1a9bdd.w.x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_45875993.x_0c1a9bdd.w.z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c3f1d391 = find_collision_point(&x_65d81f5e, &x_6530585f, 50000, &x_c593269c, &x_dedb5b95);
        if (x_c3f1d391 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c3f1d391);
            return;
        }
    } else {
        x_65d81f5e.x = x_2972e837->x_1b148bc2->x;
        x_65d81f5e.y = -100;
        x_65d81f5e.z = x_2972e837->x_1b148bc2->z;

        x_6530585f.x = x_65d81f5e.x;
        x_6530585f.y = 0;
        x_6530585f.z = x_65d81f5e.z;

        x_c3f1d391 = find_collision_point(&x_65d81f5e, &x_6530585f, 50000, &x_c593269c, &x_dedb5b95);
        if (x_c3f1d391 != NULL) {
            apply_hit(x_7246d2b2, x_e64ba38a, x_c3f1d391);
            return;
        }
    }
}

void coll_volume_setup(Player *player, x_87049dce *x_46ce35c8) {
    player->x_5c5b1d93.x_b7552092 = &player->obj->x_20d20338->transforms[x_46ce35c8->x_283c5e35].x_0c1a9bdd.w;
    player->x_5c5b1d93.x_3b24b185 = &player->obj->x_20d20338->transforms[x_46ce35c8->x_41b5ccd6].x_0c1a9bdd.w;
    player->x_5c5b1d93.x_55f532bb = &player->obj->x_20d20338->transforms[x_46ce35c8->x_8680658c].x_0c1a9bdd.w;
    player->x_5c5b1d93.x_6e7f4fd8 = &player->obj->x_20d20338->transforms[x_46ce35c8->x_cc509e17].x_0c1a9bdd.w;
    player->x_5c5b1d93.x_1b148bc2 = &player->obj->x_20d20338->transforms[x_46ce35c8->x_df4167c9].x_0c1a9bdd.w;
    player->x_5c5b1d93.x_4c227952 = &player->obj->x_20d20338->transforms[x_46ce35c8->x_35b6f6e0].x_0c1a9bdd.w;
    player->x_5c5b1d93.x_ef41f475 = &player->obj->x_20d20338->transforms[x_46ce35c8->x_71801879].x_0c1a9bdd.w;
    player->x_5c5b1d93.x_82e589d5 = &player->obj->x_20d20338->transforms[0].x_0c1a9bdd.w;

    if (x_46ce35c8->x_baea923a > 0) {
        player->x_5c5b1d93.x_9829da43 = &player->obj->x_20d20338->transforms[x_46ce35c8->x_baea923a].x_0c1a9bdd.w;
        player->x_5c5b1d93.x_b7aa4e8a = TRUE;
    } else {
        player->x_5c5b1d93.x_b7aa4e8a = FALSE;
    }

    player->x_5c5b1d93.x_62706fff = x_46ce35c8->x_62706fff;
    player->x_5c5b1d93.x_38ae036c = x_46ce35c8->x_38ae036c;

    if (x_46ce35c8->x_3bf3046a.x != 0 || x_46ce35c8->x_3bf3046a.y != 0 || x_46ce35c8->x_3bf3046a.z != 0) {
        player->x_5c5b1d93.x_c01445c3 = TRUE;
        transform_init_node(&player->obj->x_20d20338->transforms[x_46ce35c8->x_e888d5ae],
                            &player->x_5c5b1d93.x_cc2c17a6, -3, -3);
        player->x_5c5b1d93.x_cc2c17a6.x_3fde9cd9.w.x = x_46ce35c8->x_3bf3046a.x;
        player->x_5c5b1d93.x_cc2c17a6.x_3fde9cd9.w.y = x_46ce35c8->x_3bf3046a.y;
        player->x_5c5b1d93.x_cc2c17a6.x_3fde9cd9.w.z = x_46ce35c8->x_3bf3046a.z;
    } else {
        player->x_5c5b1d93.x_c01445c3 = FALSE;
    }

    if (x_46ce35c8->x_f95a218e.x != 0 || x_46ce35c8->x_f95a218e.y != 0 || x_46ce35c8->x_f95a218e.z != 0) {
        player->x_5c5b1d93.x_a1c57a3b = TRUE;
        transform_init_node(&player->obj->x_20d20338->transforms[x_46ce35c8->x_1ffa33d9],
                            &player->x_5c5b1d93.x_0548cec6, -3, -3);
        player->x_5c5b1d93.x_0548cec6.x_3fde9cd9.w.x = x_46ce35c8->x_f95a218e.x;
        player->x_5c5b1d93.x_0548cec6.x_3fde9cd9.w.y = x_46ce35c8->x_f95a218e.y;
        player->x_5c5b1d93.x_0548cec6.x_3fde9cd9.w.z = x_46ce35c8->x_f95a218e.z;
    } else {
        player->x_5c5b1d93.x_a1c57a3b = FALSE;
    }

    if (x_46ce35c8->x_8f7663b3.x != 0 || x_46ce35c8->x_8f7663b3.y != 0 || x_46ce35c8->x_8f7663b3.z != 0) {
        player->x_5c5b1d93.x_d8ede1db = TRUE;
        transform_init_node(&player->obj->x_20d20338->transforms[x_46ce35c8->x_baea923a],
                            &player->x_5c5b1d93.x_6057c67e, -3, -3);
        player->x_5c5b1d93.x_6057c67e.x_3fde9cd9.w.x = x_46ce35c8->x_8f7663b3.x;
        player->x_5c5b1d93.x_6057c67e.x_3fde9cd9.w.y = x_46ce35c8->x_8f7663b3.y;
        player->x_5c5b1d93.x_6057c67e.x_3fde9cd9.w.z = x_46ce35c8->x_8f7663b3.z;
    } else {
        player->x_5c5b1d93.x_d8ede1db = FALSE;
    }

    if (x_46ce35c8->x_150bdca9.x != 0 || x_46ce35c8->x_150bdca9.y != 0 || x_46ce35c8->x_150bdca9.z != 0) {
        player->x_5c5b1d93.x_22014d8c = TRUE;
        transform_init_node(&player->obj->x_20d20338->transforms[x_46ce35c8->x_df4167c9],
                            &player->x_5c5b1d93.x_45875993, -3, -3);
        player->x_5c5b1d93.x_45875993.x_3fde9cd9.w.x = x_46ce35c8->x_150bdca9.x;
        player->x_5c5b1d93.x_45875993.x_3fde9cd9.w.y = x_46ce35c8->x_150bdca9.y;
        player->x_5c5b1d93.x_45875993.x_3fde9cd9.w.z = x_46ce35c8->x_150bdca9.z;
    } else {
        player->x_5c5b1d93.x_22014d8c = FALSE;
    }

    if (x_46ce35c8->x_495dd749.x != 0 || x_46ce35c8->x_495dd749.y != 0 || x_46ce35c8->x_495dd749.z != 0) {
        player->x_5c5b1d93.x_6216b7a1 = TRUE;
        transform_init_node(&player->obj->x_20d20338->transforms[x_46ce35c8->x_cc509e17],
                            &player->x_5c5b1d93.x_20d81af7, -3, -3);
        player->x_5c5b1d93.x_20d81af7.x_3fde9cd9.w.x = x_46ce35c8->x_495dd749.x;
        player->x_5c5b1d93.x_20d81af7.x_3fde9cd9.w.y = x_46ce35c8->x_495dd749.y;
        player->x_5c5b1d93.x_20d81af7.x_3fde9cd9.w.z = x_46ce35c8->x_495dd749.z;
    } else {
        player->x_5c5b1d93.x_6216b7a1 = FALSE;
    }
}
