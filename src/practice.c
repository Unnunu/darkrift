#include "common.h"
#include "task.h"
#include "sprite_ids.h"

u32 D_80052D80[] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };

x_f0d7e70f D_80052DAC = { x_36257901, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052DC0 = { x_f43d0063, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052DD4 = { x_f9ed5014, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052DE8 = { x_a6fea99d, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052DFC = { x_a6fea99d, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052E10 = { x_39a96277, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052E24 = { x_39a96277, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052E38 = { x_39a96277, task_remove_current, x_5a44854c, x_9d442987, "practice.sp2" };
x_f0d7e70f D_80052E4C = { x_40bffae3, task_remove_current, 0, x_9d442987, "practice.sp2" };

x_88f11482 D_80052E60 = { 164, 133, 0, 0 };
x_88f11482 D_80052E70 = { 177, 93, 0, 0 };
x_88f11482 D_80052E80 = { 181, 133, 0, 0 };
x_88f11482 D_80052E90 = { 165, 108, 0, 0 };
x_88f11482 D_80052EA0 = { 165, 147, 0, 0 };
x_88f11482 D_80052EB0 = { 172, 108, 0, 0 };
x_88f11482 D_80052EC0 = { 172, 147, 0, 0 };
x_88f11482 D_80052ED0 = { 33, 31, 0, 0 };
x_88f11482 D_80052EE0 = { 104, 39, 0, 0 };
x_88f11482 D_80052EF0 = { 95, 39, 0, 0 };
x_88f11482 D_80052F00 = { 104, 51, 0, 0 };
x_88f11482 D_80052F10 = { 95, 51, 0, 0 };
x_88f11482 D_80052F20 = { 86, 51, 0, 0 };

s16 **x_4cc02482[] = { x_e88b7c93, D_80052524, D_8005264C, D_80052770, D_800523E4,
                       D_80052864, D_8005296C, D_80052A48, D_80052B18, D_80052C18 };

s32 D_80052F58[] = { 0, x_180244ce, x_006c7f15, 0, x_f673c860, 0, 0, 0, x_5d19c520 };
s32 D_80052F7C[] = { 0,          x_17af68da, x_424fe5d4, x_129ae237, x_38df7c08, x_2c010cd1, x_2bfbcc72, x_f36e8a3f,
                     x_5bf01f04, x_7b59cc27, x_eed7d21f, x_6435fcb0, x_d3a9d418, x_fe280ff9, x_e9eb1900, x_ae495bd1 };
s32 D_80052FBC[] = { 0, x_398095e7, x_abbe237e, x_a0dfe4e1, x_2e55edff, 0,         x_ac50de44,
                     0, x_8963333b, x_b4acafdc, 0,          0,          x_98d881e5 };

u16 D_8013C3D0;
s32 x_4b48f8e2;
Object *D_8013C3D8[12];
u16 D_8013C408;
u16 D_8013C40A;
s32 x_7648d9aa;
s16 D_8013C410[12];
s16 D_8013C428;
s16 D_8013C42A;
s16 D_8013C42C;
s32 D_8013C430;
s32 D_8013C434;
s32 x_1de5ff40;
s32 D_8013C43C;
s32 D_8013C440;
s32 D_8013C444;
s32 D_8013C448;
s32 D_8013C44C;
s32 D_8013C450;
s32 D_8013C454;
s32 D_8013C458;
u8 D_8013C45C;
u8 D_8013C45D;
u8 D_8013C45E;
u8 D_8013C45F;
Object *D_8013C460;
Object *D_8013C464;
Object *D_8013C468;
Object *D_8013C46C;
Object *D_8013C470;
Object *D_8013C474;
Object *D_8013C478;
Object *D_8013C47C;
Object *D_8013C480;
Object *D_8013C484;
Object *D_8013C488;
Object *D_8013C48C;
Object *D_8013C490;
u16 x_08051143;

void x_5430cd84(Object *);
void x_5f59e443(Object *);
void x_49eeb523(Object *);
void x_44e15b24(Object *);
void x_9a37e70c(Object *);
void x_4b9731fd(Object *);
void x_05cf4b38(Object *);
void x_01c341c9(Object *);
void x_d361fcd2(Object *);
void x_39ab32e6(void);
void x_8a4def91(Object *);
void x_f291cff5(Object *);
void x_5ee2f850(void);
void x_8bc38ad7(void);
void x_1d62b1ef(void);

void x_78e49744(void) {
    Object *x_59e6d217;

    x_1de5ff40 = 112;
    D_8013C430 = 16;
    D_8013C434 = 65;
    D_8013C43C = D_8013C440 = 0;
    x_39ab32e6();

    D_8013C40A = 0;
    D_8013C444 = 0;
    x_824b9544[1 - x_08051143].flags |= x_20efa43e;
    gWadCondLoad[1 - x_08051143].x_03604d94 = FALSE;

    x_59e6d217 = obj_create_from_def(&D_80052ED0, &D_80052E4C, x_2587f84f);
    x_59e6d217->frameCounter = x_18e8de7c;
    x_59e6d217->currentTask->callback = x_d361fcd2;

    D_8013C480 = obj_create_from_def(&D_80052EE0, &D_80052E4C, x_2587f84f);
    D_8013C484 = obj_create_from_def(&D_80052EF0, &D_80052E4C, x_2587f84f);
    D_8013C488 = obj_create_from_def(&D_80052F00, &D_80052E4C, x_2587f84f);
    D_8013C48C = obj_create_from_def(&D_80052F10, &D_80052E4C, x_2587f84f);
    D_8013C490 = obj_create_from_def(&D_80052F20, &D_80052E4C, x_2587f84f);
    task_free_list(D_8013C480->taskListHead);
    D_8013C480->taskListHead = NULL;
    task_free_list(D_8013C484->taskListHead);
    D_8013C484->taskListHead = NULL;
    task_free_list(D_8013C488->taskListHead);
    D_8013C488->taskListHead = NULL;
    task_free_list(D_8013C48C->taskListHead);
    D_8013C48C->taskListHead = NULL;
    task_free_list(D_8013C490->taskListHead);
    D_8013C490->taskListHead = NULL;

    x_59ce598c[x_08051143].x_3fb684fe = FALSE;
    x_824b9544[x_08051143].x_6f5a5c61 = x_824b9544[x_08051143].x_95a50856 = 0;
}

void x_3c859f4e(s32 x_30bbe547) {
    Object *v0;

    while (gTaskPool.count < 10 || gObjectPool.count < 10) {
        gfx_render_frame();
    }

    D_8013C464 = obj_create_from_def(&D_80052E60, &D_80052DAC, x_2587f84f);
    D_8013C464->x_0232396f = x_5f59e443;
    task_free_list(D_8013C464->taskListHead);
    D_8013C464->taskListHead = NULL;

    D_8013C468 = obj_create_from_def(&D_80052E70, &D_80052DC0, x_2587f84f);
    D_8013C468->x_0232396f = x_49eeb523;
    task_free_list(D_8013C468->taskListHead);
    D_8013C468->taskListHead = NULL;

    D_8013C46C = obj_create_from_def(&D_80052E80, &D_80052DD4, x_2587f84f);
    D_8013C46C->x_0232396f = x_44e15b24;
    task_free_list(D_8013C46C->taskListHead);
    D_8013C46C->taskListHead = NULL;

    D_8013C470 = obj_create_from_def(&D_80052E90, &D_80052DE8, x_2587f84f);
    D_8013C470->x_0232396f = x_9a37e70c;
    task_free_list(D_8013C470->taskListHead);
    D_8013C470->taskListHead = NULL;

    D_8013C474 = obj_create_from_def(&D_80052EA0, &D_80052DFC, x_2587f84f);
    D_8013C474->x_0232396f = x_4b9731fd;
    task_free_list(D_8013C474->taskListHead);
    D_8013C474->taskListHead = NULL;

    D_8013C478 = obj_create_from_def(&D_80052EB0, &D_80052E10, x_2587f84f);
    D_8013C478->x_0232396f = x_05cf4b38;
    task_free_list(D_8013C478->taskListHead);
    D_8013C478->taskListHead = NULL;

    D_8013C47C = obj_create_from_def(&D_80052EC0, &D_80052E24, x_2587f84f);
    D_8013C47C->x_0232396f = x_01c341c9;
    task_free_list(D_8013C47C->taskListHead);
    D_8013C47C->taskListHead = NULL;

    v0 = obj_create_task(x_5430cd84, 0x1064);
    task_free_list(v0->taskListHead);
    v0->taskListHead = NULL;
    v0->x_0f4167b4[0] = x_30bbe547;

    D_8013C450 = x_1de5ff40;
    D_8013C448 = D_8013C430;
    D_8013C44C = D_8013C434;
    D_8013C454 = D_8013C43C;
    D_8013C458 = D_8013C458;
    D_8013C45C = D_8013C45D = D_8013C45E = D_8013C45F = FALSE;
    gTaskLock = TRUE;
    D_8013C460->flags |= x_c537cafa;
}

void x_d456b93e(Object *obj) {
    if (x_59ce598c[x_83106b21].buttons & x_ad1aebe6) {
        obj->pos.x++;
    }
    if (x_59ce598c[x_83106b21].buttons & x_fc4a9735) {
        obj->pos.x--;
    }
    if (x_59ce598c[x_83106b21].buttons & x_f7763ed8) {
        obj->pos.y--;
    }
    if (x_59ce598c[x_83106b21].buttons & x_b8c91680) {
        obj->pos.y++;
    }
}

void x_5430cd84(Object *obj) {
    s16 x_30bbe547;
    u16 buttons;

    x_30bbe547 = obj->x_0f4167b4[0];
    buttons = 0;

    tr_quad_xlu(160, NULL);

    if (x_59ce598c[x_30bbe547].x_c4397934) {
        buttons = x_59ce598c[x_30bbe547].x_f3756179;
        x_59ce598c[x_30bbe547].x_c4397934 = FALSE;
    }

    if (!buttons) {
        obj->x_0f4167b4[1] = 0;
        return;
    }

    if (--obj->x_0f4167b4[1] > 0) {
        return;
    }
    obj->x_0f4167b4[1] = 10;

    if (buttons & x_b8c91680) {
        x_1de5ff40++;
        if (x_1de5ff40 > 118) {
            x_1de5ff40 = 112;
        }

        if (x_1de5ff40 == 114 && D_8013C430 != 18) {
            x_1de5ff40 = 115;
        } else if (x_1de5ff40 == 116 && D_8013C434 != 66) {
            x_1de5ff40 = 117;
        }
    } else if (buttons & x_f7763ed8) {
        x_1de5ff40--;
        if (x_1de5ff40 < 112) {
            x_1de5ff40 = 118;
        }

        if (x_1de5ff40 == 114 && D_8013C430 != 18) {
            x_1de5ff40 = 113;
        } else if (x_1de5ff40 == 116 && D_8013C434 != 66) {
            x_1de5ff40 = 115;
        }
    } else if (buttons & x_fc4a9735) {
        switch (x_1de5ff40) {
            case 113:
                D_8013C430++;
                if (D_8013C430 > 18) {
                    D_8013C430 = 16;
                }
                break;
            case 115:
                D_8013C434++;
                if (D_8013C434 > 66) {
                    D_8013C434 = 65;
                }
                break;
            case 114:
                D_8013C43C++;
                if (D_8013C43C >= D_80052D80[x_824b9544[x_30bbe547].x_eb1fe45b]) {
                    D_8013C43C = 0;
                }
                break;
            case 116:
                D_8013C440++;
                if (D_8013C440 >= D_80052D80[x_824b9544[1 - x_30bbe547].x_eb1fe45b]) {
                    D_8013C440 = 0;
                }
                break;
        }
    }

    if (buttons & x_ad1aebe6) {
        switch (x_1de5ff40) {
            case 113:
                D_8013C430--;
                if (D_8013C430 < 16) {
                    D_8013C430 = 18;
                }
                break;
            case 115:
                D_8013C434--;
                if (D_8013C434 < 65) {
                    D_8013C434 = 66;
                }
                break;
            case 114:
                D_8013C43C--;
                if (D_8013C43C < 0) {
                    D_8013C43C = D_80052D80[x_824b9544[x_30bbe547].x_eb1fe45b] - 1;
                }
                break;
            case 116:
                D_8013C440--;
                if (D_8013C440 < 0) {
                    D_8013C440 = D_80052D80[x_824b9544[1 - x_30bbe547].x_eb1fe45b] - 1;
                }
                break;
        }
    }

    if (buttons & x_9cefe76c) {
        switch (x_1de5ff40) {
            case 118:
                x_e30d50d2 |= x_ecbcd14e | x_700de048 | x_bee364e0;
                x_e38a6e19 = SCREEN_ATTRACT;
                obj->flags |= x_f51cb721;
                return;
            case 112:
                x_e30d50d2 |= x_700de048;
                obj->flags |= x_f51cb721;
                x_1de5ff40 = D_8013C450;
                D_8013C430 = D_8013C448;
                D_8013C434 = D_8013C44C;
                D_8013C43C = D_8013C454;
                D_8013C440 = D_8013C458;
                return;
            case 117:
                x_e30d50d2 |= x_700de048 | x_bee364e0;
                obj->flags |= x_f51cb721;
                x_e38a6e19 = x_802d9c2e;
                return;
        }

        x_e30d50d2 |= x_700de048;
        obj->flags |= x_f51cb721;
    }
}

void x_8188d175(Object *obj) {
    if (x_e30d50d2 & x_700de048) {
        obj->flags |= x_f51cb721;
    }
    x_23e3afdf(obj);
}

void x_5f59e443(Object *obj) {
    D_8013C45C = D_8013C45D = D_8013C45E = D_8013C45F = FALSE;
    obj->frameCounter = x_61ca6c23;

    switch (x_1de5ff40) {
        case 112:
            obj->frameCounter = x_56755b1f;
            break;
        case 113:
            D_8013C45C = TRUE;
            break;
        case 115:
            D_8013C45D = TRUE;
            break;
        case 117:
            obj->frameCounter = x_de8c28e5;
            break;
        case 114:
            D_8013C45E = TRUE;
            break;
        case 116:
            D_8013C45F = TRUE;
            break;
        case 118:
            obj->frameCounter = x_36257901;
            break;
    }
    x_8188d175(obj);
}

void x_49eeb523(Object *obj) {
    switch (D_8013C430) {
        case 16:
            obj->frameCounter = x_f43d0063;
            x_5ee2f850();
            break;
        case 17:
            obj->frameCounter = x_f9ed5014;
            x_5ee2f850();
            break;
        case 18:
            obj->frameCounter = x_72058b30;
            if (D_8013C434 == 66 && x_1de5ff40 != 115) {
                D_8013C434 = 65;
            }
            x_8bc38ad7();
            break;
    }

    if (D_8013C45C) {
        obj->frameCounter += 3;
    }
    x_8188d175(obj);
}

void x_44e15b24(Object *obj) {
    switch (D_8013C434) {
        case 64:
            obj->frameCounter = x_f43d0063;
            x_824b9544[1 - x_08051143].x_0b34e01a = 50;
            x_824b9544[1 - x_08051143].flags &= ~x_20efa43e;
            break;
        case 66:
            if (D_8013C430 == 18) {
                D_8013C430 = 16;
            }
            obj->frameCounter = x_72058b30;
            x_1d62b1ef();
            x_824b9544[1 - x_08051143].flags |= x_20efa43e;
            break;
        case 65:
            obj->frameCounter = x_f9ed5014;
            x_824b9544[1 - x_08051143].flags |= x_20efa43e;
            break;
    }

    if (D_8013C45D) {
        obj->frameCounter += 3;
    }
    x_8188d175(obj);
}

void x_9a37e70c(Object *obj) {
    s16 x_eb1fe45b;

    if (D_8013C430 == 18) {
        x_eb1fe45b = x_824b9544[x_08051143].x_eb1fe45b;
        if (x_eb1fe45b >= x_e235676f) {
            x_eb1fe45b--;
        }
        obj->frameCounter = x_eb1fe45b + x_a6fea99d;
        obj->flags &= ~x_c537cafa;
    } else {
        obj->flags |= x_c537cafa;
    }

    x_8188d175(obj);
}

void x_4b9731fd(Object *obj) {
    s16 x_eb1fe45b;

    if (D_8013C434 == 66) {
        x_eb1fe45b = x_824b9544[1 - x_08051143].x_eb1fe45b;
        if (x_eb1fe45b >= x_e235676f) {
            x_eb1fe45b--;
        }
        obj->frameCounter = x_eb1fe45b + x_a6fea99d;
        obj->flags &= ~x_c537cafa;
    } else {
        obj->flags |= x_c537cafa;
    }

    x_8188d175(obj);
}

void x_05cf4b38(Object *obj) {
    if (D_8013C430 == 18) {
        obj->flags &= ~x_c537cafa;
        obj->frameCounter = D_8013C43C + x_39a96277;
    } else {
        obj->flags |= x_c537cafa;
    }

    if (D_8013C45E) {
        obj->frameCounter = D_8013C43C + x_61f28495;
    }
    x_8188d175(obj);
}

void x_01c341c9(Object *obj) {
    if (D_8013C434 == 66) {
        obj->flags &= ~x_c537cafa;
        obj->frameCounter = D_8013C440 + x_39a96277;
    } else {
        obj->flags |= x_c537cafa;
    }

    if (D_8013C45F) {
        obj->frameCounter = D_8013C440 + x_61f28495;
    }
    x_8188d175(obj);
}

void x_d361fcd2(Object *obj) {
    Player *player;
    u32 v1;
    s16 a0;
    s16 v0;
    u32 a00;
    s16 a1;
    u32 x_b3c51f8a = 100U;
    u32 x_82a08606 = 10;

    player = &x_824b9544[x_08051143];

    v1 = player->x_6f5a5c61;
    if (v1 > 99) {
        v1 = 99;
    }
    a0 = v1 / x_82a08606;
    D_8013C484->frameCounter = a0;
    D_8013C480->frameCounter = v1 - a0 * x_82a08606;

    v1 = player->x_95a50856;
    if (v1 > 999) {
        v1 = 999;
    }
    v0 = v1 / x_b3c51f8a;
    a00 = v1 - v0 * x_b3c51f8a;
    a1 = a00 / x_82a08606;
    D_8013C490->frameCounter = v0;
    D_8013C48C->frameCounter = a1;
    D_8013C488->frameCounter = a00 - a1 * x_82a08606;
}

void x_39ab32e6(void) {
    s32 i;
    x_88f11482 x_54406eae = { 32, 186, 0, 0 };
    x_88f11482 x_d16311d7 = { 24, 177, 0, 0 };

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i] = obj_create_from_def(&x_54406eae, &D_80052E38, x_2587f84f);
        D_8013C3D8[i]->flags |= x_c537cafa;
        task_free_list(D_8013C3D8[i]->taskListHead);
        D_8013C3D8[i]->taskListHead = NULL;
        x_54406eae.x += 20;
        D_8013C3D8[i]->x_0f4167b4[0] = i;
        D_8013C3D8[i]->x_0232396f = x_f291cff5;
    }

    D_8013C408 = 0;
    x_54406eae.y -= 20;
    D_8013C460 = obj_create_from_def(&x_d16311d7, &D_80052DAC, x_2587f84f);
    D_8013C460->frameCounter = x_fa3d736d;
    D_8013C460->currentTask->callback = x_8a4def91;
}

void x_02a93bc5(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i]->flags |= x_f51cb721;
    }
}

void x_5ee2f850(void) {
    s16 i;

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i]->flags |= x_c537cafa;
    }

    D_8013C408 = D_8013C40A = 0;
}

void x_b2930fd7(u16 x_cc1d0de5) {
    Object *v0;
    s16 i;

    if (x_cc1d0de5) {
        if (D_8013C40A > 45) {
            x_5ee2f850();
        } else {
            D_8013C40A = 0;
        }

        if (D_8013C408 < 12) {
            v0 = D_8013C3D8[D_8013C408++];
        } else {
            for (i = 0; i < 11; i++) {
                D_8013C3D8[i]->frameCounter = D_8013C3D8[i + 1]->frameCounter;
            }
            v0 = D_8013C3D8[11];
        }

        v0->frameCounter = x_cc1d0de5;
        v0->flags &= ~x_c537cafa;
        v0->x_0f4167b4[2] = x_cc1d0de5;
    }
}

void x_fc939beb(u16 x_cc1d0de5) {
    if (((x_cc1d0de5 >> 12) & 0xF) != 0) {
        x_b2930fd7(D_80052FBC[(x_cc1d0de5 >> 12) & 0xF]);
    }

    if ((x_cc1d0de5 & 0xF) != 0) {
        x_b2930fd7(D_80052F58[x_cc1d0de5 & 0xF]);
    }

    if (((x_cc1d0de5 >> 4) & 0xF) != 0) {
        x_b2930fd7(D_80052F7C[(x_cc1d0de5 >> 4) & 0xF]);
    }
}

void x_67bc7ac4(u16 x_cc1d0de5) {
    Object *a0;

    if (x_cc1d0de5) {
        a0 = D_8013C3D8[D_8013C408++];
        a0->frameCounter = x_cc1d0de5 + 1;
        x_f291cff5(a0);
    }
}

void x_71555a2e(u16 x_cc1d0de5) {
    if (D_8013C430 != 16) {
        if (((x_cc1d0de5 >> 12) & 0xF) != 0) {
            x_67bc7ac4(D_80052FBC[(x_cc1d0de5 >> 12) & 0xF]);
        }

        if ((x_cc1d0de5 & 0xF) != 0) {
            x_67bc7ac4(D_80052F58[x_cc1d0de5 & 0xF]);
        }

        if (((x_cc1d0de5 >> 4) & 0xF) != 0) {
            x_67bc7ac4(D_80052F7C[(x_cc1d0de5 >> 4) & 0xF]);
        }
    }
}

void x_d8010ff6(void) {
    u32 i;

    if (D_8013C430 != 16) {
        for (i = 0; i < D_8013C408; i++) {
            D_8013C3D8[i]->frameCounter = D_8013C3D8[i]->x_0f4167b4[2];
        }
    }

    D_8013C408 = 0;
    D_8013C42A = 0;
}

void x_75afee1a(void) {
    u16 a0;

    a0 = x_59ce598c[x_08051143].x_f3756179;
    a0 &= ~D_8013C3D0;
    D_8013C3D0 = x_59ce598c[x_08051143].x_f3756179;

    if (!D_8013C3D0) {
        D_8013C40A++;
    }
    if (a0) {
        x_fc939beb(a0);
    }
}

void x_8bc38ad7(void) {
    s16 x_11413d9b;
    Player *player;
    s16 *x_8fb32026;
    s16 s1;
    x_e0b9a726 *x_23b71842;
    s16 **x_9420af58;
    s16 *x_6e32552b;
    s16 t3;

    player = x_824b9544 + x_08051143;
    x_11413d9b = x_824b9544[x_08051143].x_eb1fe45b;
    if (x_11413d9b >= x_e235676f) {
        x_11413d9b--;
    }

    x_9420af58 = x_4cc02482[x_11413d9b];
    x_8fb32026 = x_9420af58[D_8013C43C];

    x_5ee2f850();
    D_8013C428 = D_8013C42A = 0;

    s1 = *x_8fb32026;
    while (s1 != 0) {
        t3 = player->x_59f97427[s1];
        x_6e32552b = player->x_b8b27276;
        x_23b71842 = &player->x_1af5b64c[x_6e32552b[t3]];
        D_8013C410[D_8013C428++] = x_6e32552b[t3];
        x_fc939beb(x_23b71842->x_5512bb4f);
        x_8fb32026++;
        s1 = *x_8fb32026;
    }

    D_8013C408 = 0;
}

void x_1d62b1ef(void) {
    s16 x_c8b456d0;
    Player *x_98c4e5a5;
    s16 *x_8fb32026;
    s16 s1;
    x_e0b9a726 *transition;
    s16 **x_4daef94b;
    s16 *x_6e32552b;
    s16 x_499fba40;

    x_98c4e5a5 = x_824b9544 + 1 - x_08051143;
    x_c8b456d0 = x_824b9544[1 - x_08051143].x_eb1fe45b;
    if (x_c8b456d0 >= x_e235676f) {
        x_c8b456d0--;
    }

    x_4daef94b = x_4cc02482[x_c8b456d0];
    x_8fb32026 = x_4daef94b[D_8013C440];

    x_5ee2f850();
    D_8013C428 = D_8013C42A = 0;

    s1 = *x_8fb32026;
    while (s1 != 0) {
        x_499fba40 = x_98c4e5a5->x_59f97427[s1];
        x_6e32552b = x_98c4e5a5->x_b8b27276;
        transition = &x_98c4e5a5->x_1af5b64c[x_6e32552b[x_499fba40]];
        D_8013C410[D_8013C428++] = x_6e32552b[x_499fba40];
        x_fc939beb(transition->x_5512bb4f);
        x_8fb32026++;
        s1 = *x_8fb32026;
    }

    D_8013C408 = 0;
}

void x_b3ce14e9(void) {
    u16 a2;
    x_e0b9a726 *x_23b71842;

    if (--D_8013C42C <= 0) {
        a2 = (D_8013C430 == 18) ? x_08051143 : 1 - x_08051143;

        if (D_8013C42A < D_8013C428) {
            x_23b71842 = &x_824b9544[a2].x_1af5b64c[D_8013C410[D_8013C42A]];
            x_59ce598c[a2].buttons = x_23b71842->x_5512bb4f;
            x_59ce598c[a2].x_c4397934 = TRUE;
        } else {
            D_8013C444 = FALSE;
            x_59ce598c[x_08051143].enabled = TRUE;
            x_e30d50d2 &= ~x_86c5bc33;
        }
    }
}

void x_65b38a11(void) {
    u16 a2;
    Player *player;

    if (D_8013C430 == 18) {
        a2 = x_08051143;
    } else {
        a2 = 1 - x_08051143;
    }
    player = &x_824b9544[a2];

    if (D_8013C444 != 0) {
        x_b3ce14e9();
    }

    if (player->x_6cbdf667 == D_8013C410[D_8013C42A]) {
        x_71555a2e(player->transition->x_5512bb4f);
        D_8013C42A++;
        if (D_8013C444) {
            x_b3ce14e9();
        }
        D_8013C42C = 15;
    } else if (D_8013C42A != 0 && player->x_6cbdf667 != D_8013C410[D_8013C42A - 1]) {
        x_d8010ff6();
        D_8013C444 = FALSE;
    }
}

void x_8a4def91(Object *obj) {
    if (D_8013C430 != 18 && D_8013C434 != 66) {
        obj->flags |= x_c537cafa;
        return;
    }

    if (--obj->x_0f4167b4[0] < 0 && D_8013C444 == 0) {
        obj->flags ^= x_c537cafa;
        obj->x_0f4167b4[0] = 12;
    } else if (D_8013C444 != 0) {
        obj->flags &= ~x_c537cafa;
    }

    if (x_59ce598c[x_08051143].buttons == x_29dbff14) {
        D_8013C444 = 1;
        D_8013C42C = 0;
        x_e30d50d2 |= x_86c5bc33;
        if (D_8013C430 == 18) {
            x_59ce598c[x_08051143].enabled = FALSE;
        } else {
            x_59ce598c[1 - x_08051143].enabled = FALSE;
        }
    }
}

void x_f291cff5(Object *obj) {
    s32 q;
    if (D_8013C430 != 18 || (obj->flags & x_c537cafa)) {
        x_23e3afdf(obj);
        return;
    }

    if (x_59ce598c[x_08051143].x_d93bcabf) {
        if (obj->x_0f4167b4[2] != x_8963333b) {
            if (obj->x_0f4167b4[2] == x_abbe237e) {
                obj->frameCounter = (q = (obj->frameCounter & 1) == 0) + x_8963333b;
            }
        } else {
            obj->frameCounter = (q = (obj->frameCounter & 1) == 0) + x_abbe237e;
        }
    } else {
        obj->frameCounter = (q = (obj->frameCounter & 1) == 0) + obj->x_0f4167b4[2];
    }

    x_23e3afdf(obj);
}
