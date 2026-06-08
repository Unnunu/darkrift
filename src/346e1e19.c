#include "common.h"
#include "task.h"
#include "string.h"

Object *x_8cdb365e = NULL;
s32 D_80052C54 = 0;

x_b57dc591 x_11f3efb0;
x_b57dc591 x_5c163218;
s32 x_f1d278c5;

void x_7824740c(x_b57dc591 *x_cc1d0de5, u32 count, u32 x_52f03926) {
    s16 i;
    u8 *buffer;

    x_cc1d0de5->elements = (u8 **) x_56c3086a(count * 4, "item.c", 23);
    x_cc1d0de5->buffer = (u8 *) x_56c3086a(x_52f03926 * count, "item.c", 24);
    x_ad92c136(x_cc1d0de5->buffer, 0, count * x_52f03926);
    x_cc1d0de5->count = count;
    x_cc1d0de5->x_b8173ab8 = count - 1;

    buffer = x_cc1d0de5->buffer;
    for (i = 0; i < count; i++) {
        x_cc1d0de5->elements[i] = buffer + i * x_52f03926;
    }
}

void x_24bc1a84(x_b57dc591 *x_cc1d0de5, u32 count, u32 x_52f03926) {
    u32 i;
    u32 j;
    u32 x_9d95bf71;
    u32 x_55e411ea;
    void *buffer;
    u8 **x_ed0d2d7a;

    x_9d95bf71 = x_cc1d0de5->count;
    x_55e411ea = x_9d95bf71 + count;

    x_ed0d2d7a = (u8 **) x_56c3086a(x_55e411ea * 4, "item.c", 45);
    buffer = x_56c3086a(count * x_52f03926, "item.c", 46);

    for (i = 0; i < x_9d95bf71; i++) {
        x_ed0d2d7a[i] = x_cc1d0de5->elements[i];
    }

    for (j = i; j < x_55e411ea; j++) {
        x_ed0d2d7a[j] = (u8 *) buffer + (j - i) * x_52f03926;
    }

    x_86715543(x_cc1d0de5->elements);

    x_cc1d0de5->elements = x_ed0d2d7a;
    x_cc1d0de5->count = x_55e411ea;
    x_cc1d0de5->x_b8173ab8 = x_55e411ea - 1;
}

void x_8e6b5db0(s32 count) {
    x_24bc1a84(&x_11f3efb0, count, sizeof(Object));
    x_24bc1a84(&x_30839b82, count, sizeof(x_41a0e1e6));
}

void x_3c16ed51(void) {
    x_7824740c(&x_11f3efb0, 50, sizeof(Object));
    x_7824740c(&x_5c163218, 16, sizeof(x_6fcfcf46));
    x_8cdb365e = NULL;
    D_80052C54 = 0;
}

Object *x_5283664d(s16 priority) {
    Object *obj;
    Object *x_5ad2b76c;

    D_80052C54++;
    if (x_11f3efb0.x_b8173ab8 <= 0) {
        return NULL;
    }

    if (x_8cdb365e == NULL) {
        obj = x_8cdb365e = (Object *) x_6d619dce(x_11f3efb0);

        obj->x_d0268c0d = NULL;
        obj->x_2d5f3fbd = NULL;
    } else {
        obj = x_8cdb365e;

        while (obj != NULL && obj->priority >= priority) {
            x_5ad2b76c = obj;
            obj = obj->x_2d5f3fbd;
        }

        if (obj == NULL) {
            x_5ad2b76c->x_2d5f3fbd = (Object *) x_6d619dce(x_11f3efb0);

            obj = x_5ad2b76c->x_2d5f3fbd;
            obj->x_d0268c0d = x_5ad2b76c;
            obj->x_2d5f3fbd = NULL;
        } else if (obj->x_d0268c0d == NULL) {
            obj = (Object *) x_6d619dce(x_11f3efb0);

            obj->x_2d5f3fbd = x_8cdb365e;
            x_8cdb365e->x_d0268c0d = obj;
            x_8cdb365e = obj;
            obj->x_d0268c0d = NULL;
        } else {
            if ((!obj->x_2d5f3fbd) != 0) {} // required to match
            x_5ad2b76c = (Object *) x_6d619dce(x_11f3efb0);

            obj->x_d0268c0d->x_2d5f3fbd = x_5ad2b76c;
            x_5ad2b76c->x_2d5f3fbd = obj;
            x_5ad2b76c->x_d0268c0d = obj->x_d0268c0d;
            obj->x_d0268c0d = x_5ad2b76c;
            obj = x_5ad2b76c;
        }
    }

    obj->priority = priority;
    return obj;
}

void x_63b616bf(Object *obj) {
    D_80052C54--;
    if (obj->x_d0268c0d == NULL) {
        obj->x_2d5f3fbd->x_d0268c0d = NULL;
        x_8cdb365e = obj->x_2d5f3fbd;
    } else if (obj->x_2d5f3fbd == NULL) {
        obj->x_d0268c0d->x_2d5f3fbd = NULL;
    } else {
        obj->x_d0268c0d->x_2d5f3fbd = obj->x_2d5f3fbd;
        obj->x_2d5f3fbd->x_d0268c0d = obj->x_d0268c0d;
    }

    if (obj->flags & x_3434f870) {
        x_5c163218.x_b8173ab8++;
        x_5c163218.elements[x_5c163218.x_b8173ab8] = obj->x_20d20338;
        x_5c163218.count++;

        if (obj->x_20d20338->transforms != NULL) {
            x_86715543(obj->x_20d20338->transforms);
        }
    }

    x_11f3efb0.x_b8173ab8++;
    x_11f3efb0.elements[x_11f3efb0.x_b8173ab8] = obj;
    x_11f3efb0.count++;
}

// unused
void x_f8781320(x_c1cedf06 *x_cc1d0de5) {
    x_9b85c792(&x_cc1d0de5->transform);
}

// unused
void x_454a13ef(x_320b5d80 *x_cc1d0de5) {
    u32 i;

    x_f8781320(x_cc1d0de5->info);

    for (i = 0; i < x_cc1d0de5->info->header.x_4c5e05f8; i++) {}
    for (i = 0; i < x_cc1d0de5->info->header.x_8a54e96a; i++) {}
}

void x_581070ad(Object *obj) {
    u32 x_5d21c78b, x_b7cc9533;
    s32 x_df21a243;
    Object *x_7cdc2f34;

    for (x_7cdc2f34 = x_8cdb365e; x_7cdc2f34 != NULL; x_7cdc2f34 = x_7cdc2f34->x_2d5f3fbd) {
        if (x_7cdc2f34 != obj && (obj->x_b1e624ba & x_7cdc2f34->x_e4466eca)) {
            x_5d21c78b = ABS(obj->pos.x - x_7cdc2f34->pos.x);
            x_b7cc9533 = ABS(obj->pos.z - x_7cdc2f34->pos.z);
            x_df21a243 = x_4a9e7834(x_5d21c78b, x_b7cc9533) - obj->x_de73d1d5 - x_7cdc2f34->x_de73d1d5;
            if (x_df21a243 <= 0) {
                if (obj->x_61f772e7 & 2) {
                    obj->x_450fdcd0(obj, x_7cdc2f34);
                }
                if (x_7cdc2f34->x_61f772e7 & 2) {
                    x_7cdc2f34->x_450fdcd0(x_7cdc2f34, obj);
                }
                break;
            }
        }
    }
}

void x_efb29a7d(void) {
    Object *obj;
    Object *x_a58b9b64;
    x_f752bb53 *x_dfa11b27;
    s32 s1;
    u32 i;
    u32 j;
    x_320b5d80 *v0;
    u32 t2;
    s32 x_df21a243;

    D_8013C4E8 = NULL;
    obj = x_8cdb365e;
    while (obj != NULL) {
        if (obj->x_b1e624ba != 0) {
            x_581070ad(obj);
        }

        if ((obj->flags & x_f51cb721) && !(obj->flags & x_c537cafa)) {
            obj->flags |= x_c537cafa;
        } else if (obj->flags & x_f51cb721) {
            if (obj->x_61f772e7 & 8) {
                obj->x_1b0e7aa2 |= 8;
                obj->x_450fdcd0(obj, NULL);
            }
            if (obj->flags & x_28b57b50) {
                x_1760d24f(obj->light);
            }
            x_bbe35044(obj->x_d178c88f);
            obj->x_d178c88f = NULL;
            x_a58b9b64 = obj;
            obj = obj->x_2d5f3fbd;
            x_63b616bf(x_a58b9b64);
        } else {
            obj->x_0232396f(obj);
            obj = obj->x_2d5f3fbd;
        }
    }

    for (x_dfa11b27 = D_8013C4E8; x_dfa11b27 != NULL; x_dfa11b27 = x_dfa11b27->next) {
        s1 = x_dfa11b27->x_164cf1ca->x_ceaf196d;
        if (x_dfa11b27->x_164cf1ca->x_af0aa1f8) {
            for (i = 0; i < s1; i++) {
                if (x_dfa11b27->flags & 1) {
                    continue;
                }
                v0 = x_dfa11b27->x_164cf1ca->transforms[i];
                t2 = x_dfa11b27->x_164cf1ca->x_c246f31f[i];
                for (j = 0; j < t2; j++) {
                    if (x_dfa11b27->flags & 2) {
                        x_50746900(x_ee137e39, NULL, (j != 0) ? v0->info : x_dfa11b27->x_415ed9d6[i], v0->vertices,
                                   v0->triangles);
                        v0++;
                    } else {
                        x_50746900(x_8a79b283, NULL, (j != 0) ? v0->info : x_dfa11b27->x_415ed9d6[i], v0->vertices,
                                   v0->triangles);
                        v0++;
                    }
                }
            }
        } else {
            s32 temp = D_8005BFCE * s1;
            for (i = 0; i < s1; i++) {
                gSPMatrix(x_9a3c07b8++, x_c485761a(x_dfa11b27->x_164cf1ca->transforms[i + temp]),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(x_9a3c07b8++, x_c485761a(x_dfa11b27->x_164cf1ca->x_1aae351f[i]));
            }
        }
    }
}

#ifdef NON_EQUIVALENT
void x_6d41c91d(Object *x_cc1d0de5, x_88f11482 *x_84ff873b, x_acccb624 *x_2092f891, Transform *x_ee71e5cb,
                void (*x_08ae3bb4)(Object *)) {
    s16 i;
    s32 temp;

    x_f2c7456d(x_ee71e5cb, &x_cc1d0de5->transform, -2, -3);

    x_cc1d0de5->x_61f772e7 = 0;
    x_cc1d0de5->color.r = x_cc1d0de5->color.g = x_cc1d0de5->color.b = 160;

    x_cc1d0de5->x_8da078cc.x = 0;
    x_cc1d0de5->x_8da078cc.y = 0;
    x_cc1d0de5->x_8da078cc.z = 0;

    x_cc1d0de5->velocity.x = 0;
    x_cc1d0de5->velocity.y = 0;
    x_cc1d0de5->velocity.z = 0;

    x_cc1d0de5->x_f9866d50 = x_cc1d0de5->x_61f772e7;

    x_cc1d0de5->pos.x = x_84ff873b->x;
    x_cc1d0de5->pos.y = x_84ff873b->y;
    x_cc1d0de5->pos.z = x_84ff873b->z;

    x_cc1d0de5->x_224610f1.x = x_2092f891->x;
    x_cc1d0de5->x_224610f1.y = x_2092f891->y;
    x_cc1d0de5->x_224610f1.z = x_2092f891->z;

    x_cc1d0de5->x_e4466eca = 0;
    x_cc1d0de5->x_b1e624ba = 0;
    x_cc1d0de5->x_de73d1d5 = 0;

    x_cc1d0de5->x_860b579a = 0x100;
    x_cc1d0de5->x_2fa0bbed = 0x100;
    x_cc1d0de5->x_3e400065 = 0x100;

    x_cc1d0de5->x_1b0e7aa2 = 0;
    x_cc1d0de5->x_5fcb1654 = 0;
    x_cc1d0de5->x_2b06a023 = -1;
    x_cc1d0de5->color.a = 128;
    x_cc1d0de5->x_8f6ab396 = 0;
    x_cc1d0de5->x_9112b8b9 = 0;

    x_cc1d0de5->x_d178c88f = (x_41a0e1e6 *) x_6d619dce(x_30839b82);
    x_cc1d0de5->x_64946db0 = x_cc1d0de5->x_d178c88f;
    if (x_08ae3bb4 != NULL) {
        x_cc1d0de5->x_64946db0->x_c7f843c2 = 0;
        x_cc1d0de5->x_64946db0->flags = x_0fb55613;
        x_cc1d0de5->x_64946db0->x_f6382727 = x_08ae3bb4;
        x_cc1d0de5->x_64946db0->x_116c9ff3 = 0;
    } else {
        x_cc1d0de5->x_64946db0->x_c7f843c2 = 0;
        x_cc1d0de5->x_64946db0->flags = x_0fb55613;
        x_cc1d0de5->x_64946db0->x_f6382727 = x_0ae6735d;
        x_cc1d0de5->x_64946db0->x_116c9ff3 = 0;
    }

    x_cc1d0de5->x_64946db0->next = NULL;
    x_cc1d0de5->x_64946db0->x_116c9ff3 = 0;

    x_948f0b9f(&x_cc1d0de5->transform.x_3fde9cd9, x_2092f891);
    x_fc6adb04(&x_cc1d0de5->transform.x_3fde9cd9, x_84ff873b);

    for (i = 0; i < 13; i++) {
        x_cc1d0de5->x_0f4167b4[i] = 0;
    }

    x_cc1d0de5->x_47e6a04c.r = x_cc1d0de5->x_47e6a04c.g = x_cc1d0de5->x_47e6a04c.b = 255;
    x_cc1d0de5->x_da940449.r = x_cc1d0de5->x_da940449.g = x_cc1d0de5->x_da940449.b = x_cc1d0de5->x_da940449.a = 0;
    x_cc1d0de5->light = NULL;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/346e1e19/x_6d41c91d.s")
void x_6d41c91d(Object *x_cc1d0de5, x_88f11482 *x_84ff873b, x_acccb624 *x_2092f891, Transform *x_ee71e5cb,
                void (*x_a0e63e9c)(Object *));
#endif

void x_9c540986(Object *obj, Model *model) {
    x_6fcfcf46 *x_20d20338;
    u32 x_6dcce206;
    Transform *x_abd7b3c4;
    Transform *transforms;
    x_43bd08ed *x_529cbc8f;
    u32 i;
    s32 x_eb290249;

    x_20d20338 = obj->x_20d20338;
    x_6dcce206 = model->x_6dcce206;
    x_abd7b3c4 = &x_20d20338->x_abd7b3c4;

    x_f2c7456d(&obj->transform, x_abd7b3c4, -1, -2);
    x_20d20338->transforms = transforms = x_56c3086a(x_6dcce206 * sizeof(Transform), "item.c", 453);

    x_529cbc8f = model->x_e7962160;
    x_20d20338->x_0094fc88 = &x_529cbc8f[1];
    x_20d20338->x_9cfd7bb4.x = x_529cbc8f->x;
    x_20d20338->x_9cfd7bb4.y = x_529cbc8f->y;
    x_20d20338->x_9cfd7bb4.z = x_529cbc8f->z;
    x_fc6adb04(&x_20d20338->x_abd7b3c4.x_3fde9cd9, &x_20d20338->x_9cfd7bb4);

    for (i = 0; i < x_6dcce206; i++) {
        x_529cbc8f = model->x_e7962160 + i + 1;
        x_eb290249 = x_529cbc8f->x_e4712596;
        if (x_eb290249 >= 0) {
            x_f2c7456d(&transforms[x_eb290249], &transforms[i], i, x_eb290249);
        } else {
            x_f2c7456d(x_abd7b3c4, &transforms[i], i, x_eb290249);
        }
        x_fc6adb04(&transforms[i].x_3fde9cd9, &x_529cbc8f->x);
    }
}

Object *x_745c5ce2(x_88f11482 *x_cc1d0de5, char *x_84ff873b, x_aece7675 *properties, s32 x_ee71e5cb) {
    Object *obj;
    char x_dcab8ab0[20];
    x_6fcfcf46 *x_20d20338;
    x_82e80914 *s5;

    if (x_84ff873b == NULL) {
        obj = x_5283664d(properties->x_95ee18a8);
        x_dab0846a(x_dcab8ab0, properties->name);
        x_6d41c91d(obj, x_cc1d0de5, &x_acab9952, NULL, properties->x_08ae3bb4);
    } else {
        x_dab0846a(x_dcab8ab0, x_84ff873b);
        if (properties != NULL) {
            obj = x_5283664d(properties->x_95ee18a8);
            x_6d41c91d(obj, x_cc1d0de5, &x_acab9952, NULL, properties->x_08ae3bb4);
        } else {
            obj = x_5283664d(0x1000);
            x_6d41c91d(obj, x_cc1d0de5, &x_acab9952, NULL, NULL);
        }
    }

    obj->x_0232396f = x_9f1f8050;
    obj->flags = x_3434f870;
    x_20d20338 = obj->x_20d20338 = x_56c3086a(sizeof(x_6fcfcf46), "item.c", 523);

    x_8c518b47(x_dcab8ab0, ".kmd");
    s5 = x_20d20338->x_305a60f8 = x_b717ed65[x_e720f37d(x_dcab8ab0, x_ee71e5cb)].x_4962fc73;
    x_20d20338->model = NULL;
    x_20d20338->x_6dcce206 = s5->model.x_6dcce206;

    if (s5->model.x_e7962160 != NULL) {
        x_9c540986(obj, &s5->model);
    } else {
        obj->x_20d20338->transforms = NULL;
    }

    x_20d20338->x_50771dcd = s5->model.x_50771dcd;
    x_20d20338->x_1d0c1660 = s5->x_2640873a;

    if (properties != NULL && properties->x_b8173ab8 != NULL) {
        x_549030bf(x_20d20338, properties->x_b8173ab8);
    } else {
        x_20d20338->x_9a3e80ff = NULL;
    }

    return obj;
}

Object *x_4495b42c(void (*x_0232396f)(Object *), s16 x_84ff873b) {
    Object *obj;

    obj = x_5283664d(x_84ff873b);
    x_6d41c91d(obj, &x_c787d34b, &x_acab9952, NULL, NULL);
    obj->x_0232396f = x_0232396f;
    obj->flags = x_f2c38774;
    return obj;
}

Object *x_12014163(x_88f11482 *pos, x_f0d7e70f *def, s32 context) {
    Object *obj;

    obj = x_5283664d(def->x_95ee18a8);
    x_6d41c91d(obj, pos, &x_acab9952, NULL, def->x_f6382727);
    obj->x_0232396f = x_23e3afdf;
    obj->flags = def->flags;
    obj->flags |= x_3d723236;
    obj->x_5fcb1654 = def->x_f85f1359;
    obj->x_904eaf67 = x_b717ed65[x_e720f37d(def->x_6870fa4a, context)].data;

    return obj;
}

Object *x_8e3c7e83(x_88f11482 *pos, char *name, x_aece7675 *properties, u32 context) {
    Object *obj;
    char x_c02b5734[20];
    x_6fcfcf46 *x_20d20338;
    Model *model;
    u32 x_6dcce206;
    s32 i;

    if (name == NULL) {
        obj = x_5283664d(properties->x_95ee18a8);
        x_dab0846a(x_c02b5734, properties->name);
        x_6d41c91d(obj, pos, &x_acab9952, NULL, properties->x_08ae3bb4);
    } else {
        x_dab0846a(x_c02b5734, name);
        if (properties != NULL) {
            obj = x_5283664d(properties->x_95ee18a8);
            x_6d41c91d(obj, pos, &x_acab9952, NULL, properties->x_08ae3bb4);
        } else {
            obj = x_5283664d(x_9d442987);
            x_6d41c91d(obj, pos, &x_acab9952, NULL, NULL);
        }
    }

    obj->x_0232396f = x_0022bfc3;
    obj->flags = x_3434f870;
    obj->x_20d20338 = (x_6fcfcf46 *) x_6d619dce(x_5c163218);

    x_20d20338 = obj->x_20d20338;
    model = x_20d20338->model = x_b717ed65[x_e720f37d(x_c02b5734, context)].x_4962fc73;
    x_20d20338->x_305a60f8 = NULL;
    x_6dcce206 = x_20d20338->x_6dcce206 = model->x_6dcce206;

    for (i = 0; i < x_6dcce206; i++) {
        memcpy(&x_20d20338->x_78526b81[i].header, model->x_d6eac39a[i], sizeof(x_c32f9ed9));
        memcpy(&x_20d20338->x_78526b81[30 + i].header, model->x_d6eac39a[i], sizeof(x_c32f9ed9));
        x_20d20338->x_c8099ad6[i] = x_20d20338->x_8f151cd3[i] = FALSE;
    }

    if (model->x_e7962160 != NULL) {
        x_9c540986(obj, model);
    } else {
        obj->x_20d20338->transforms = NULL;
    }

    x_20d20338->x_50771dcd = model->x_50771dcd;
    x_20d20338->x_1d0c1660 = model->x_cb6af9da;
    x_20d20338->x_2f4c4ce1 = -1;

    if (properties != NULL && properties->x_b8173ab8 != NULL) {
        x_5ff45842(x_20d20338, properties->x_b8173ab8);
    } else {
        x_20d20338->x_9a3e80ff = NULL;
    }

    obj->flags |= x_dd3a53e4;
    x_20d20338->x_3aefae96 = x_20d20338->x_713417ac = 0;
    return obj;
}

Object *x_1d5cf6e2(x_88f11482 *pos, x_8b39d614 *properties, s32 context) {
    Object *obj;
    x_257b53b4 *x_23b71842;

    if (x_5c163218.count >= 2) {
        obj = x_8e3c7e83(pos, NULL, &properties->base, context);
        obj->x_0232396f = x_3a85c5a8;
        obj->x_5fcb1654 = properties->x_14033586;
        obj->flags |= properties->flags | x_0b94e8d0;
        obj->color.a = 128;

        x_23b71842 = &obj->x_20d20338->x_8b36595a;
        x_23b71842->x_af0aa1f8 = 1;
        x_23b71842->x_ceaf196d = 1;
        obj->x_20d20338->x_da66be9b.x_164cf1ca = x_23b71842;
        if (obj->flags & x_d13a68b5) {
            obj->x_20d20338->x_da66be9b.x_9dca29cd = -0x80000000;
        } else {
            obj->x_20d20338->x_da66be9b.x_9dca29cd = 0x7FFFFFFF;
        }
        obj->x_20d20338->x_da66be9b.flags = 0;
        return obj;
    } else {
        return NULL;
    }
}

Object *x_572f827d(x_88f11482 *pos, s32 x_95ee18a8, void (*x_08ae3bb4)(Object *), Model *model) {
    u32 x_6dcce206;
    Object *obj;
    x_6fcfcf46 *x_20d20338;
    u32 i;
    s32 unused[5];

    obj = x_5283664d(x_95ee18a8);
    x_6d41c91d(obj, pos, &x_acab9952, NULL, x_08ae3bb4);

    obj->x_0232396f = x_0022bfc3;
    obj->flags = x_3434f870;

    if (x_5c163218.count == 0) {
        obj->x_0232396f = x_0ae6735d;
        obj->flags = x_f51cb721;
        obj->x_20d20338 = NULL;
        return NULL;
    }

    obj->x_20d20338 = (x_6fcfcf46 *) x_6d619dce(x_5c163218);

    x_20d20338 = obj->x_20d20338;
    x_20d20338->model = model;
    x_20d20338->x_305a60f8 = NULL;
    x_6dcce206 = x_20d20338->x_6dcce206 = model->x_6dcce206;

    for (i = 0; i < x_6dcce206; i++) {
        memcpy(&x_20d20338->x_78526b81[i].header, model->x_d6eac39a[i], sizeof(x_c32f9ed9));
        memcpy(&x_20d20338->x_78526b81[30 + i].header, model->x_d6eac39a[i], sizeof(x_c32f9ed9));
        x_20d20338->x_8f151cd3[i] = x_20d20338->x_07bd45a3[i] = FALSE;
        x_20d20338->x_c8099ad6[i] = FALSE;
    }

    if (model->x_e7962160 != NULL) {
        x_9c540986(obj, model);
    } else {
        obj->x_20d20338->transforms = NULL;
        x_f2c7456d(&obj->transform, &x_20d20338->x_abd7b3c4, -1, -2);
        x_20d20338->x_9cfd7bb4.x = 0;
        x_20d20338->x_9cfd7bb4.y = 0;
        x_20d20338->x_9cfd7bb4.z = 0;
        x_fc6adb04(&x_20d20338->x_abd7b3c4.x_3fde9cd9, &x_20d20338->x_9cfd7bb4);
    }

    x_20d20338->x_50771dcd = model->x_50771dcd;
    x_20d20338->x_1d0c1660 = model->x_cb6af9da;
    obj->flags |= x_dd3a53e4 | x_215d3747;
    x_20d20338->x_88c9004e = x_6dcce206;
    x_20d20338->x_9a3e80ff = model->x_761a0268;

    for (i = 0; i < x_20d20338->x_88c9004e; i++) {
        x_20d20338->x_61b49b7b[i].x_164cf1ca = &model->x_761a0268[i];
    }

    x_20d20338->x_ee205ef9 = 0;
    x_20d20338->x_3aefae96 = x_20d20338->x_713417ac = 0;

    if (x_20d20338->x_50771dcd != NULL) {
        x_0f2c2c2a(obj);
    }

    if (model->x_8ac8f967 & 1) {
        obj->flags |= x_f465a0fc;
    }

    return obj;
}

Object *x_6f2f6fab(x_88f11482 *pos, s32 x_95ee18a8, void (*x_08ae3bb4)(Object *), Model *model) {
    Object *obj;
    x_257b53b4 *x_23b71842;

    if (x_5c163218.count == 0) {
        return NULL;
    }

    obj = x_572f827d(pos, x_95ee18a8, x_08ae3bb4, model);
    obj->x_0232396f = x_3a85c5a8;
    obj->x_5fcb1654 = 0;
    obj->flags |= x_215d3747 | x_b6789b80 | x_0b94e8d0;
    obj->color.a = 128;

    x_23b71842 = &obj->x_20d20338->x_8b36595a;
    x_23b71842->x_af0aa1f8 = 1;
    x_23b71842->x_ceaf196d = 1;
    obj->x_20d20338->x_da66be9b.x_164cf1ca = x_23b71842;
    obj->x_20d20338->x_da66be9b.x_9dca29cd = -9000;
    obj->x_20d20338->x_da66be9b.flags = 0;
    return obj;
}
