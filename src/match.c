#include "common.h"
#include "camera.h"
#include "task.h"

extern s16 D_80049390;
extern x_3da8fdd8 x_c2354b9b[];
extern u8 D_8004A42C;
extern s16 x_adcfd05c;

extern Object *D_8013C23C;

extern s32 x_6db66fc3;

/* .bss */

Object *D_80081440;
Object *D_80081444;
Object *D_80081448;
Object *D_8008144C;
Object *D_80081450;
Object *D_80081454;

void x_ae7ca939(Object *);
void x_3da93607(Object *);

void x_97edc3db(Object *obj) {
    x_e30d50d2 |= x_ecbcd14e | x_700de048 | x_bee364e0;
    x_e38a6e19 = x_802d9c2e;
    x_49d7310c(x_a5f164ca);
    if (x_77831b2c[x_83106b21].x_03604d94) {
        D_80049390 = x_77831b2c[x_83106b21].x_eb1fe45b;
    } else {
        D_80049390 = x_77831b2c[x_6f0b3be3].x_eb1fe45b;
    }

    x_77831b2c[x_83106b21].x_03604d94 = x_77831b2c[x_6f0b3be3].x_03604d94 = FALSE;
    x_77831b2c[x_83106b21].x_b2b764b3 = x_77831b2c[x_6f0b3be3].x_b2b764b3 = 0;
    obj->flags |= x_f51cb721;
}

void x_a1821d40(Object *obj) {
    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        if (--obj->x_0f4167b4[1] <= 0) {
            if (obj->x_0f4167b4[0] < obj->color.a) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
                obj->x_0232396f = x_97edc3db;
            }
        }
    } else {
        obj->frameCounter++;
    }

    model_render(obj);
}

void x_a08bfaa4(Object *obj) {
    if (--obj->x_0f4167b4[1] <= 0) {
        obj->flags &= ~x_c537cafa;
        if (obj->frameCounter == 0 && obj->x_0f4167b4[2] != -1) {
            x_7e194d55(2, obj->x_0f4167b4[2]);
        }

        if (obj->frameCounter < obj->x_20d20338->x_8e601526 - 1) {
            obj->frameCounter++;
        }
    }
}

void x_ebf8a1b0(Object *obj) {
    obj->flags &= ~x_c537cafa;
    if (obj->frameCounter == 0 && obj->x_0f4167b4[2] != -1) {
        x_7e194d55(2, obj->x_0f4167b4[2]);
    }

    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        if (--obj->x_0f4167b4[1] <= 0) {
            if (obj->color.a > obj->x_0f4167b4[0]) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= x_f51cb721;
            }
        }
    } else {
        obj->frameCounter++;
    }
}

void x_7705be49(Object *obj) {
    if (--obj->x_0f4167b4[1] <= 0) {
        if (obj->x_0f4167b4[0] < obj->color.a) {
            obj->color.a -= obj->x_0f4167b4[0];
        } else {
            TASK_END(obj->currentTask);
            obj->flags |= x_f51cb721;
        }
    }
}

Object *x_1bb3ac04(x_3da8fdd8 *msg, s32 context) {
    Object *obj;
    x_88f11482 pos;
    Model *a3;
    char x_f974a07e[80];

    x_14d52001(2);
    x_dab0846a(x_f974a07e, msg->name);
    x_8c518b47(x_f974a07e, ".k2");

    a3 = x_b717ed65[x_e720f37d(x_f974a07e, context)].x_4962fc73;
    pos.x = pos.y = pos.z = 0;
    obj = obj_create_with_model_ptr(&pos, 0x1000, msg->x_5cb18fd3, a3);

    if (obj != NULL) {
        obj->flags |= x_a816b63b;

        obj->x_0f4167b4[1] = msg->duration;
        obj->flags |= x_d13a68b5;
        if (msg->x_ba814dc8 != 0) {
            obj->color.a = 128;
            obj->x_0f4167b4[0] = msg->x_ba814dc8;
            obj->flags |= x_b6789b80;
        }
        obj->x_0f4167b4[2] = msg->x_1dc13257;
        obj->currentTask->delay = 2;
    }

    return obj;
}

void x_7c50d2d4(Object *x_cc1d0de5, Object *x_84ff873b) {
    D_8013C23C->currentTask->callback = x_ae7ca939;
    D_8013C23C->currentTask->delay = 0;
    D_8013C23C->currentTask->flags = TASK_RUNNABLE;
    D_8013C23C->currentTask->delay = 30;
}

Object *x_68289eaa(s16 x_31ee45bf) {
    Object *obj;

    obj = x_1bb3ac04(x_dd2c4e91 + x_31ee45bf, x_2587f84f);
    if (obj != NULL && x_31ee45bf == x_3d992fcd) {
        obj->x_450fdcd0 = x_7c50d2d4;
        obj->x_61f772e7 |= 8;
    }

    return obj;
}

Object *x_22ac1eb3(s32 x_eb1fe45b, s32 x_84ff873b, u32 x_30bbe547) {
    s32 unused;
    Object *obj;

    obj = x_1bb3ac04(x_c2354b9b + x_eb1fe45b, x_30bbe547);

    if (obj != NULL) {
        obj->currentTask->delay = x_84ff873b;
        obj->flags |= x_c537cafa;
        if (x_77831b2c[x_30bbe547].x_03604d94) {
            obj->x_0f4167b4[2] = 7;
        }
    }

    x_84221e64(0, 64);
    x_84221e64(1, 64);
    D_8004A42C = TRUE;
    return obj;
}

u16 x_357cdf67(s32 x_9591016d) {
    x_3da8fdd8 *a0;
    Object *obj;

    if (x_77831b2c[x_83106b21].x_b2b764b3 == x_adcfd05c - 1 && x_77831b2c[x_6f0b3be3].x_b2b764b3 == x_adcfd05c - 1) {
        a0 = &x_dd2c4e91[x_cd54037c];
    } else {
        a0 = &x_dd2c4e91[x_3ead7ac2];
    }
    obj = x_1bb3ac04(a0, x_2587f84f);
    if (obj != NULL) {
        obj->frameCounter = x_9591016d * 2;
    }
    return a0->duration;
}

void x_fb6f79b0(Object *obj) {
    Object *x_aaadc3e8;

    obj->flags &= ~x_c537cafa;
    if ((x_59ce598c[1 - D_8013C24C].buttons & x_0684c746) && obj->x_0f4167b4[1] == 0) {
        if (obj->frameCounter < obj->x_20d20338->x_8e601526) {
            obj->frameCounter += 30;
        }
        x_aaadc3e8 = D_8013C23C->x_e2f64c57[5];
        x_aaadc3e8->x_0f4167b4[1] -= 30;
    }

    obj->x_0f4167b4[1] = x_59ce598c[1 - D_8013C24C].buttons; // probably @bug

    if (obj->frameCounter >= obj->x_20d20338->x_8e601526) {
        if (--obj->x_0f4167b4[1] <= 0) {
            if (obj->x_0f4167b4[0] < obj->color.a) {
                obj->color.a -= obj->x_0f4167b4[0];
            } else {
                obj->color.a = 0;
                TASK_END(obj->currentTask);
                obj->flags |= x_f51cb721;
            }
        }
    } else {
        obj->frameCounter++;
    }
}

void x_943bfef8(void) {
    Object *obj;

    for (obj = gObjectList; obj != NULL; obj = obj->x_2d5f3fbd) {
        if ((obj->flags & x_215d3747) || (obj->flags & x_0b94e8d0)) {
            obj->flags |= x_f51cb721;
        }
    }
}

void x_1240eb8e(Object *obj) {
    Object *v0;
    Object *v1;
    u32 i;

    x_824b9544[x_83106b21].x_cd14c741 = 0;
    x_824b9544[x_6f0b3be3].x_cd14c741 = 0;

    player_reinit(x_83106b21);
    player_reinit(x_6f0b3be3);

    obj->flags |= x_f51cb721;
    x_2615d8ad = gFrameCounter % 5;
    D_8013C226 = 0;

    x_943bfef8();
    x_7bc4ef6e();
    x_073e79bc();

    v0 = obj->x_e2f64c57[4];
    if (v0 != NULL) {
        v0->flags |= x_f51cb721;
    }
    if (D_80081440 != NULL) {
        D_80081440->flags |= x_f51cb721;
    }
    if (D_80081448 != NULL) {
        D_80081448->flags |= x_f51cb721;
    }
    if (D_8008144C != NULL) {
        D_8008144C->flags |= x_f51cb721;
    }
    if (D_80081450 != NULL) {
        D_80081450->flags |= x_f51cb721;
    }
    if (D_80081444 != NULL) {
        D_80081444->flags |= x_f51cb721;
    }
    if (D_80081454 != NULL) {
        D_80081454->flags |= x_f51cb721;
    }

    x_f4bce728->currentTask->callback = cam_intro_start_inverse;
    x_f4bce728->currentTask->delay = 0;
    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -400;
    x_6f8aa7af = FALSE;

    if (x_c8356c60 != 0) {
        D_8013C240->frameCounter = 3 + x_c8356c60 * 3;
        v1 = D_8013C240->x_e2f64c57[0];
        v1->frameCounter = 0;
        D_8013C240->currentTask->callback = task_remove_current;
    }

    D_8013C234->x_e7f1952a = D_8013C234->x_e7f1952a - D_8013C234->x_b88b3756 + D_8013C234->rightS - 88;
    D_8013C234->x_b88b3756 = D_8013C234->rightS - 88;
    D_8013C238->rightS = D_8013C238->x_b88b3756 + 80;

    D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
    D_8013C232 = D_8013C230 = 80;

    D_80052D64[0] = D_80052D64[1] = D_80052D68[0] = D_80052D68[1] = D_80052D6C[0] = D_80052D6C[1] = D_8013C3C0[0] =
        D_8013C3C0[1] = D_80052D70[0] = D_80052D70[1] = D_80052D74[0] = D_80052D74[1] = 0;
    D_80052D78[0] = D_80052D78[1] = 2;

    if (!D_8013C24E && x_77831b2c[D_8013C24C].x_b2b764b3 != 0) {
        D_8013C258[D_8013C24C][x_77831b2c[D_8013C24C].x_b2b764b3 - 1]->frameCounter = 13;
    } else if (D_8013C24E && x_77831b2c[x_83106b21].x_b2b764b3 != 0 && x_77831b2c[x_6f0b3be3].x_b2b764b3 != 0) {
        D_8013C258[x_83106b21][x_77831b2c[x_83106b21].x_b2b764b3 - 1]->frameCounter = 13;
        D_8013C258[x_6f0b3be3][x_77831b2c[x_6f0b3be3].x_b2b764b3 - 1]->frameCounter = 13;
    } else {
        for (i = 0; i < x_adcfd05c; i++) {
            D_8013C258[x_83106b21][i]->frameCounter = D_8013C258[x_6f0b3be3][i]->frameCounter = 12;
        }
    }

    x_824b9544[x_83106b21].obj->frameCounter = 2;
    x_824b9544[x_6f0b3be3].obj->frameCounter = 2;
    model_anim_load(x_824b9544[x_83106b21].obj);
    model_anim_load(x_824b9544[x_6f0b3be3].obj);

    mat4_ident_partial(&x_824b9544[x_83106b21].x_a4d7c80d.x_3fde9cd9);
    mat4_ident_partial(&x_824b9544[x_83106b21].x_022dff72.x_3fde9cd9);
    mat4_ident_partial(&x_824b9544[x_6f0b3be3].x_a4d7c80d.x_3fde9cd9);
    mat4_ident_partial(&x_824b9544[x_6f0b3be3].x_022dff72.x_3fde9cd9);

    model_transforms_update(x_824b9544[x_83106b21].obj);
    model_transforms_update(x_824b9544[x_6f0b3be3].obj);
    x_824b9544[x_83106b21].obj->x_2b06a023 = x_824b9544[x_83106b21].obj->frameCounter;
    x_824b9544[x_6f0b3be3].obj->x_2b06a023 = x_824b9544[x_6f0b3be3].obj->frameCounter;
    x_824b9544[x_83106b21].x_b9252303->flags &= ~TASK_TIME_BASED;
    x_824b9544[x_6f0b3be3].x_b9252303->flags &= ~TASK_TIME_BASED;

    x_09a33777 = 0x800;
    x_ea2a7987();
}

u32 x_bd5da599(Player *player, s32 x_84ff873b, u32 x_2092f891) {
    s32 temp;
    u32 res;

    player_exec_move(player, x_84ff873b, TRUE);

    temp = player->x_b9252303->params[1];
    if (x_2092f891 < player->x_68a6b5cd[temp].x_bab9966d + 120) {
        res = player->x_68a6b5cd[temp].x_bab9966d + 120;
    } else {
        res = x_2092f891;
    }
    return res;
}

u8 x_10a92dc1(void) {

    if ((x_5e4e2788 == x_e483bf48 || x_5e4e2788 == x_557d3dd6) && x_77831b2c[D_8013C24C].x_03604d94) {
        x_59ce598c[1 - D_8013C24C].enabled = TRUE;
        return (x_59ce598c[1 - D_8013C24C].buttons & x_9cefe76c) != 0;
    } else {
        return (x_59ce598c[D_8013C24C].buttons & x_9cefe76c) != 0;
    }
}

void x_0290e665(Object *obj) {
    x_824b9544[x_83106b21].x_448f0851 = x_824b9544[x_6f0b3be3].x_448f0851 = 0;

    if (--obj->x_0f4167b4[1] < 0 && x_10a92dc1()) {
        x_1240eb8e(obj);
    }

    if (--obj->x_0f4167b4[0] < 0) {
        x_1240eb8e(obj);
    }
}

void x_3aac9858(Object *obj) {
    x_824b9544[x_83106b21].x_448f0851 = x_824b9544[x_6f0b3be3].x_448f0851 = 0;

    if (--obj->x_0f4167b4[1] < 0 && x_10a92dc1()) {
        x_e30d50d2 |= x_bee364e0;
        TASK_END(obj->currentTask);
        x_e30d50d2 |= x_b9be821f;
        obj->flags |= x_f51cb721;
    }

    if (--obj->x_0f4167b4[0] < 0) {
        x_e30d50d2 |= x_bee364e0;
        TASK_END(obj->currentTask);
        x_e30d50d2 |= x_b9be821f;
        obj->flags |= x_f51cb721;
    }
}

void x_0907749d(Object *obj) {
    x_e38a6e19 = x_028e5846 >= x_c74743bd ? x_fa31c524 : x_ef3ab4fe; // not real mode? @bug?
    obj->currentTask->callback = x_3aac9858;
}

void x_ae7ca939(Object *obj) {
    Object *a2;
    s16 i;
    s16 a3;

    if (x_77831b2c[x_83106b21].x_03604d94 || x_77831b2c[x_6f0b3be3].x_03604d94) {
        a2 = x_68289eaa(x_692a98c7);
        x_e38a6e19 = SCREEN_ATTRACT;
        x_77831b2c[x_83106b21].x_7d8e7a6f = x_77831b2c[x_6f0b3be3].x_7d8e7a6f = 0;
    } else {
        a2 = x_68289eaa(x_692a98c7);
        x_e38a6e19 = x_802d9c2e;

        if (x_5e4e2788 == x_a5f164ca) {
            a3 = x_adcfd05c == x_77831b2c[x_6f0b3be3].x_b2b764b3;
            x_49d7310c(x_e483bf48 + a3);

            x_77831b2c[1 - a3].x_03604d94 = TRUE;
            x_6db66fc3 = 1 - a3;

            for (i = 0; i < x_edb381f3; i++) {
                D_800B6350[a3][i] = FALSE;
            }
        }
    }

    obj->currentTask->callback = x_3aac9858;

    if (a2 != NULL) {
        a2->x_0f4167b4[1] = 10;
        a2->x_0f4167b4[0] = a2->x_20d20338->x_8e601526;
    } else {
        obj->x_0f4167b4[1] = 0;
        obj->x_0f4167b4[0] = 0;
    }
}

void x_8afd5019(Object *obj) {
    Object *v0;

    if (x_59ce598c[1 - D_8013C24C].buttons & x_9cefe76c) {
        x_91192da2();

        if (x_5e4e2788 == x_e483bf48) {
            D_800B6350[x_6f0b3be3][x_824b9544[x_6f0b3be3].x_eb1fe45b] = FALSE;
        } else if (x_5e4e2788 == x_557d3dd6) {
            D_800B6350[x_83106b21][x_824b9544[x_83106b21].x_eb1fe45b] = FALSE;
        }

        v0 = obj->x_e2f64c57[3];
        if (v0 != NULL) {
            v0->flags |= x_c537cafa;
            v0->currentTask->callback = task_remove_current;
        }

        x_1240eb8e(obj);
    }
}

void x_be1ae884(Object *obj) {
    Object *a1;

    x_e30d50d2 |= x_86c5bc33;

    if (--obj->x_0f4167b4[2] == 0 || (--obj->x_0f4167b4[1] < 0 && x_10a92dc1())) {
        if (x_77831b2c[x_83106b21].x_03604d94 || x_77831b2c[x_6f0b3be3].x_03604d94) {
            obj->x_e2f64c57[5] = D_8008144C = x_68289eaa(x_eab09ee3);
        } else {
            obj->x_e2f64c57[5] = D_8008144C = x_68289eaa(x_b74cb64b);
        }
        obj->x_e2f64c57[3] = D_80081450 = x_68289eaa(x_3d992fcd);

        x_59ce598c[1 - D_8013C24C].enabled = TRUE;
        obj->currentTask->callback = x_8afd5019;
        a1 = obj->x_e2f64c57[4];
        if (a1 != NULL) {
            a1->flags |= x_f51cb721;
        }
        x_59ce598c[D_8013C24C].x_c4397934 = FALSE;
        obj->x_e2f64c57[4] = obj->x_e2f64c57[5];
    }
}

x_09d6a3c8 x_9503a93c(u32 x_30bbe547, u8 x_84ff873b) {
    x_09d6a3c8 a3;

    a3 = x_0290e665;

    x_77831b2c[x_30bbe547].x_b2b764b3++;
    if (x_77831b2c[x_30bbe547].x_b2b764b3 == x_adcfd05c) {
        if (!x_84ff873b) {
            x_77831b2c[D_8013C24C].x_7d8e7a6f++;
            x_77831b2c[1 - D_8013C24C].x_7d8e7a6f = 0;
        }

        D_800B6368[x_77831b2c[x_30bbe547].x_eb1fe45b].x_a962826d++;
        D_800B6368[x_77831b2c[1 - x_30bbe547].x_eb1fe45b].x_3f3ac621++;
        D_800801F1 = TRUE;

        switch (x_5e4e2788) {
            case x_e483bf48:
            case x_557d3dd6:
                if (!x_77831b2c[x_30bbe547].x_03604d94) {
                    D_800B6350[1 - x_30bbe547][x_824b9544[1 - x_30bbe547].x_eb1fe45b] = TRUE;

                    if (x_7dc12b61(1 - x_30bbe547) == -1) {
                        a3 = x_0907749d;
                    } else {
                        x_e38a6e19 = x_802d9c2e;
                        a3 = x_3aac9858;
                    }
                } else {
                    a3 = x_be1ae884;
                }
                break;
            case x_96f25e0a:
            case x_a5f164ca:
                a3 = x_be1ae884;
                break;
            case x_3658fb97:
                x_e38a6e19 = SCREEN_ATTRACT;
                break;
        }
    }

    return a3;
}

void x_67392d1b(Object *obj) {
    s32 x_32f1d6e2;
    x_09d6a3c8 v02;

    x_32f1d6e2 = x_bd5da599(&x_824b9544[D_8013C24C], (gFrameCounter & 1) ? x_fefa7415 : x_f4d3471e, 0x78);
    x_943bfef8();
    obj->x_e2f64c57[4] = D_80081440 = x_22ac1eb3(x_824b9544[D_8013C24C].x_eb1fe45b, 6, D_8013C24C);
    v02 = x_9503a93c(D_8013C24C, FALSE);

    obj->x_0f4167b4[0] = x_32f1d6e2 + 120;
    obj->x_0f4167b4[1] = 10;
    obj->x_0f4167b4[2] = 190;
    obj->currentTask->callback = v02;

    x_e30d50d2 &= ~x_dd99cbfb;
    x_824b9544[1 - D_8013C24C].obj->flags |= x_c537cafa;
    x_824b9544[D_8013C24C].obj->pos.x = x_824b9544[D_8013C24C].obj->pos.y = x_824b9544[D_8013C24C].obj->pos.z = 0;
    x_824b9544[1 - D_8013C24C].obj->pos.x = x_824b9544[1 - D_8013C24C].obj->pos.y =
        x_824b9544[1 - D_8013C24C].obj->pos.z = 0;

    x_824b9544[x_83106b21].obj->x_224610f1.y = 0;
    x_824b9544[x_83106b21].flags |= x_c865be3f;
    x_824b9544[x_6f0b3be3].flags |= x_c865be3f;

    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -400;

    if (x_77831b2c[D_8013C24C].x_eb1fe45b != x_b52da315) {
        x_824b9544[D_8013C24C].obj->flags |= x_3e24eba7;
    }

    x_824b9544[D_8013C24C].obj->flags &= ~(x_da021b29 | x_da584e3c);
}

void x_72432500(Object *obj) {
    s32 pad;
    Object *v0;
    x_09d6a3c8 a3;

    v0 = x_68289eaa(x_baa70474);
    a3 = x_0290e665;

    if (v0 != NULL) {
        v0->currentTask->delay = 5;
    }

    D_80081444 = v0;

    x_bd5da599(&x_824b9544[x_6f0b3be3], x_f6ac8484, x_bd5da599(&x_824b9544[x_83106b21], x_f6ac8484, 0x78));

    if (x_adcfd05c == x_77831b2c[x_83106b21].x_b2b764b3 + 1) {
        a3 = x_9503a93c(x_83106b21, TRUE);
    } else {
        x_77831b2c[x_83106b21].x_b2b764b3++;
    }

    if (x_adcfd05c == x_77831b2c[x_6f0b3be3].x_b2b764b3 + 1) {
        a3 = x_9503a93c(x_6f0b3be3, TRUE);
    } else {
        x_77831b2c[x_6f0b3be3].x_b2b764b3++;
    }

    obj->x_0f4167b4[0] = 245;
    obj->x_0f4167b4[1] = 10;
    obj->x_0f4167b4[2] = 190;
    obj->x_e2f64c57[4] = v0;

    obj->currentTask->callback = a3;
}

void x_553d0c7f(Object *obj) {
    Object *a0;

    if (--obj->x_0f4167b4[0] > 0) {
        if ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
            a0 = obj->x_e2f64c57[4];
            a0->flags |= x_f51cb721;

            if (x_59ce598c[x_83106b21].buttons & x_9cefe76c) {
                x_59ce598c[x_83106b21].x_c4397934 = FALSE;
            }
            if (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c) {
                x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE;
            }
        } else {
            return;
        }
    }

    if (D_8013C24E) {
        obj->currentTask->callback = x_72432500;
    } else {
        x_59ce598c[1 - D_8013C24C].enabled = FALSE;
        x_59ce598c[1 - D_8013C24C].buttons = 0;
        obj->currentTask->callback = x_67392d1b;
    }
}

void x_4eb395f9(Object *obj) {
    if (x_824b9544[x_83106b21].flags & x_22ebc053) {
        if (--x_824b9544[x_83106b21].x_448f0851 > 20) {
            x_824b9544[x_83106b21].x_448f0851 = 20;
        } else {
            player_select_move(&x_824b9544[x_83106b21], TRUE);
        }
    } else if (x_824b9544[x_6f0b3be3].flags & x_22ebc053) {
        if (--x_824b9544[x_6f0b3be3].x_448f0851 > 20) {
            x_824b9544[x_6f0b3be3].x_448f0851 = 20;
        } else {
            player_select_move(&x_824b9544[x_6f0b3be3], TRUE);
        }
    } else if ((x_824b9544[x_83106b21].flags & x_a45101c0) && (x_824b9544[x_6f0b3be3].flags & x_a45101c0)) {
        if ((x_824b9544[x_83106b21].x_7f68c36b->flags & x_037894c1) && x_824b9544[x_83106b21].x_cd14c741 != 4) {
            player_exec_move(&x_824b9544[x_83106b21], x_26778114, FALSE);
        } else if (x_824b9544[x_83106b21].x_cd14c741 != 17) {
            player_exec_move(&x_824b9544[x_83106b21], x_ee946ac0, FALSE);
        }

        if ((x_824b9544[x_6f0b3be3].x_7f68c36b->flags & x_037894c1) && x_824b9544[x_6f0b3be3].x_cd14c741 != 4) {
            player_exec_move(&x_824b9544[x_6f0b3be3], x_26778114, FALSE);
        } else if (x_824b9544[x_6f0b3be3].x_cd14c741 != 17) {
            player_exec_move(&x_824b9544[x_6f0b3be3], x_ee946ac0, FALSE);
        }

        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

        obj->currentTask->callback = x_553d0c7f;
        obj->currentTask->delay = 10;
        obj->x_0f4167b4[0] = 80;
        D_80080234 = TRUE;
    }
}

void x_ccb0cf31(Object *obj) {
    if (D_80080234) {
        obj->currentTask->callback = x_3da93607;
    }
}

void x_fac2190d(Object *obj) {
    if (++obj->x_0f4167b4[0] & 8) {
        obj->flags &= ~x_c537cafa;
    } else {
        obj->flags |= x_c537cafa;
    }
}

void x_544fc7e7(Object *obj) {
    if (D_80080234) {
        obj->flags |= x_f51cb721;
    }
    x_fac2190d(obj);
}

void x_3651e6a0(Object *obj) {
    x_f0d7e70f x_331089fa = { 0x26, x_544fc7e7, 0x4000000, 0x1001, "bars.sp2" };
    x_88f11482 x_2a89e429 = { 250, 220, 0, 0 };

    x_59ce598c[D_8013C24C].enabled = TRUE;
    x_e30d50d2 &= ~x_dd99cbfb;
    if (TRUE) {
        D_80080234 = TRUE;
    }
    obj->currentTask->callback = x_3da93607;
    obj->currentTask->delay = 45;
    x_943bfef8();
}

void x_e99883b2(Object *obj) {
    Object *a0;

    if (--obj->x_0f4167b4[0] > 0) {
        if (x_59ce598c[D_8013C24C].buttons & x_9cefe76c) {
            a0 = obj->x_e2f64c57[4];
            if (a0 != NULL) {
                a0->flags |= x_f51cb721;
            }

            if (x_59ce598c[x_83106b21].buttons & x_9cefe76c) {
                x_59ce598c[x_83106b21].x_c4397934 = FALSE;
            }
            if (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c) {
                x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE;
            }
        } else {
            return;
        }
    }

    obj->currentTask->callback = x_3651e6a0;
}

void x_3da93607(Object *obj) {
    x_e30d50d2 &= ~x_dd99cbfb;

    if (!D_80080234) {
        if (x_824b9544[x_83106b21].obj->x_9200c538 == x_77831b2c[x_83106b21].x_c35c64af &&
                x_824b9544[x_6f0b3be3].obj->x_9200c538 == 0 ||
            x_824b9544[x_83106b21].obj->x_9200c538 == 0 &&
                x_824b9544[x_6f0b3be3].obj->x_9200c538 == x_77831b2c[x_6f0b3be3].x_c35c64af) {
            obj->x_e2f64c57[4] = D_80081448 = x_68289eaa(x_25af9d6d);
            obj->x_0f4167b4[0] = 90;
            x_59ce598c[D_8013C24C].enabled = TRUE;
            obj->currentTask->callback = x_e99883b2;
        } else {
            obj->currentTask->callback = x_3651e6a0;
        }
    } else {
        x_59ce598c[D_8013C24C].enabled = TRUE;
        if (D_8013C24E) {
            x_59ce598c[1 - D_8013C24C].enabled = TRUE;
            obj->currentTask->callback = x_72432500;
        } else {
            obj->currentTask->callback = x_67392d1b;
        }
    }
}

void x_76daaaf5(Object *obj) {
    Object *x_1b70419e;

    if (x_9df63a90 || x_824b9544[x_83106b21].obj->x_9200c538 <= 0 || x_824b9544[x_6f0b3be3].obj->x_9200c538 <= 0) {
        x_d265c713();
        x_9df63a90 = TRUE;
        if (!(x_e30d50d2 & x_86c5bc33)) {
            x_e30d50d2 |= x_86c5bc33;
            return;
        }

        x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = FALSE;
        if (x_824b9544[x_83106b21].obj->x_9200c538 > x_824b9544[x_6f0b3be3].obj->x_9200c538) {
            D_8013C24C = x_83106b21;
        } else {
            D_8013C24C = x_6f0b3be3;
        }

        D_8013C24E = (x_824b9544[x_83106b21].obj->x_9200c538 == x_824b9544[x_6f0b3be3].obj->x_9200c538);

        if (x_9df63a90 && x_824b9544[x_83106b21].obj->x_9200c538 != 0 && x_824b9544[x_6f0b3be3].obj->x_9200c538 != 0) {
            x_1b70419e = x_68289eaa(x_7dab12f3);
            D_80081454 = x_1b70419e;
            obj->x_e2f64c57[4] = x_1b70419e;
            obj->currentTask->callback = x_4eb395f9;
        } else {
            obj->currentTask->callback = x_3da93607;
        }

        D_80080234 = FALSE;
        obj->currentTask->delay = 45;
    }
}

void x_8f307638(Object *obj) {
    x_e30d50d2 |= x_86c5bc33;
    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;

    if (++obj->x_0f4167b4[0] > 900) {
        x_e38a6e19 = x_2a3e474b;
        x_e30d50d2 |= x_bee364e0;
        obj->flags |= x_f51cb721;
    } else if ((x_59ce598c[x_83106b21].buttons & x_9cefe76c) || (x_59ce598c[x_6f0b3be3].buttons & x_9cefe76c)) {
        x_e30d50d2 |= x_bee364e0;
        x_e38a6e19 = SCREEN_ATTRACT;
        obj->flags |= x_f51cb721;
    }
}

void x_a471eef4(Object *obj) {
    if (x_5e4e2788 == x_3658fb97) {
        obj->currentTask->callback = x_8f307638;
        obj->x_0f4167b4[0] = 0;
        x_e30d50d2 |= x_86c5bc33;
    } else {
        obj->currentTask->callback = x_76daaaf5;
        x_e30d50d2 &= ~x_86c5bc33;
    }

    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = TRUE;
    x_824b9544[x_83106b21].flags &= ~x_4d950171;
    x_824b9544[x_6f0b3be3].flags &= ~x_4d950171;

    if (x_77831b2c[x_83106b21].x_03604d94) {
        x_824b9544[x_83106b21].x_81570fde.x_b2c79d6e &= ~x_c74d666c;
    }
    if (x_77831b2c[x_6f0b3be3].x_03604d94) {
        x_824b9544[x_6f0b3be3].x_81570fde.x_b2c79d6e &= ~x_c74d666c;
    }

    x_fd44eb65();
}

void x_f0ad9b18(Object *obj) {
    Object *v0;
    obj->currentTask->callback = x_a471eef4;
    v0 = x_68289eaa(x_0f44231b);
    obj->currentTask->delay = v0->x_20d20338->x_8e601526 + 20;
}

void x_a21936ef(Object *obj) {
    task_execute(obj);
}

void x_b372f4dd(void) {
    D_8013C23C = obj_create_task(x_a21936ef, 1);
    x_9df63a90 = FALSE;
    x_6f8aa7af = 0;

    x_59ce598c[x_83106b21].enabled = x_59ce598c[x_6f0b3be3].enabled = FALSE;
    x_824b9544[x_83106b21].flags |= x_4d950171;
    x_824b9544[x_6f0b3be3].flags |= x_4d950171;
    x_33abac12 = FALSE;
    D_80080234 = FALSE;

    if (x_77831b2c[x_83106b21].x_03604d94) {
        x_824b9544[x_83106b21].x_81570fde.x_b2c79d6e |= x_c74d666c;
    }
    if (x_77831b2c[x_6f0b3be3].x_03604d94) {
        x_824b9544[x_6f0b3be3].x_81570fde.x_b2c79d6e |= x_c74d666c;
    }

    D_8013C23C->currentTask->callback = x_f0ad9b18;
    D_8013C23C->currentTask->delay = 0;
    D_8013C23C->currentTask->flags = TASK_RUNNABLE;
    D_8013C23C->currentTask->delay = x_357cdf67(x_77831b2c[x_83106b21].x_b2b764b3 + x_77831b2c[x_6f0b3be3].x_b2b764b3);
    D_80081440 = D_80081448 = D_8008144C = D_80081450 = D_80081454 = D_80081444 = NULL;
}
