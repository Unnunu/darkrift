#include "common.h"
#include "PR/gt.h"
#include "task.h"

extern Vec4i D_8004A5D0[];
extern Vec4i D_8004A680[];

extern s32 D_80081434;
extern s32 D_80081438;

void func_80028558(Object *obj);

UnkK2Def D_80051F50 = { "dusthit.sp3", func_80028558, 0, 0x1100, 0, 0x2800, 0 };
s16 D_80051F68 = 0;
s16 D_80051F6C = 0;
s16 D_80051F70 = 0;
Vtx D_80051F78[2][4] = { { { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } },
                         { { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 140, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } } };
Vtx D_80051FF8[2][4] = { { { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } },
                         { { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 112, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } },
                           { { { 1188, 152, 0 }, 0, { 0, 0 }, { 255, 255, 255, 255 } } } } };
Vec4i D_80052078 = { 63, 220, 0, 0 };
Vec4i D_80052088 = { 72, 220, 0, 0 };
Vec4i D_80052098 = { 81, 220, 0, 0 };
Vec4i D_800520A8 = { 268, 220, 0, 0 };
Vec4i D_800520B8 = { 277, 220, 0, 0 };
Vec4i D_800520C8 = { 286, 220, 0, 0 };
Vec4i *D_800520D8[] = { &D_80052078, &D_80052088, &D_80052098, &D_800520A8, &D_800520B8, &D_800520C8 };

s16 D_8013C230;
s16 D_8013C232;
AssetSP2Sub3 *D_8013C234;
AssetSP2Sub3 *D_8013C238;
Object *D_8013C23C;
Object *D_8013C240;
Object *D_8013C244;
Object *D_8013C248;
s16 D_8013C24C;
s16 D_8013C24E;
u16 D_8013C250;
s32 D_8013C254_unused;
Object *D_8013C258[2][10];
s16 D_8013C2A8;
s16 D_8013C2AA;

void func_8002A050(Object *obj);
void func_8002A0EC(Object *obj);
void func_80029F58(Object *obj);
void func_80028E84(void);

void func_8000636C(Player *, s32, s32);

void func_80028010(Object *obj) {
    obj->flags &= ~4;
    if (obj->spriteId <= 12) {
        obj->spriteId++;
        if (obj->unk_088.a > 100) {
            obj->unk_088.a -= 8;
        } else if (obj->unk_088.a > 3) {
            obj->unk_088.a -= 3;
        }
        obj->currentTask->counter = 2;
    } else {
        obj->flags |= 0x14;
        obj->currentTask->flags |= 0x80;
    }
}

void func_80028090(Object *obj) {
    if (--obj->vars[1] <= 0) {
        obj->flags &= ~4;
        if (obj->spriteId <= 8) {
            obj->spriteId++;
            if (obj->unk_088.a > 100) {
                obj->unk_088.a -= 8;
            } else if (obj->unk_088.a > 4) {
                obj->unk_088.a -= 2;
            }
            obj->currentTask->counter = 2;
        } else {
            obj->flags |= 0x14;
            obj->currentTask->flags |= 0x80;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028120.s")

void func_800281F8(s16 arg0, Vec4i *arg1, Vec4i *arg2) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    sp28 = arg1->x;
    sp24 = arg1->z;
    sp2C = (u32) (sqrtf(SQ(sp28) + SQ(sp24)) + 0.5);
    sp20 = arg0 + sp2C;
    sp1C = func_80012518(sp24, sp28);

    arg2->x = (func_80012854(sp1C) * sp20) >> 12;
    arg2->z = (-func_80012854(sp1C + 0x400) * sp20) >> 12;
    arg2->y = arg1->y;
}

void func_80028360(Object *obj) {
    Object *v0;
    Object *v1;

    if (--obj->unk_08C <= 0) {
        obj->unk_08C = obj->vars[2];
        v1 = obj->varObj[3];
        v0 = func_8002BF1C(&v1->pos, &D_80051F50, 0xABAB);
        if (v0 == NULL) {
            return;
        } else {
            v0->currentTask->func = func_80028010;
            v0->unk_058 = v0->unk_05C = v0->unk_060 = 0x64000;
            if (--obj->vars[1] < 0) {
                obj->flags |= 0x10;
            }
        }
    }
}

void func_80028400(Object *obj) {
    Object *v0;
    Player *player = (Player *) obj->varObj[0];

    v0 = create_worker(func_80028360, 0x1000);
    if (v0 == NULL) {
        return;
    }

    v0->varObj[0] = player;
    v0->vars[1] = 4;
    v0->vars[2] = 3;
    v0->varObj[3] = obj;
    v0->unk_088.a = 100;
    v0->unk_08C = 0;
}

void func_80028464(Object *obj) {
    s16 playerId = obj->vars[0];
    Object *v0 = gPlayers[playerId].unk_00;
    Vec4i sp20;

    if (v0->pos.y != 0) {
        return;
    }
    sp20.x = v0->modInst->unk_010.wolrd_matrix.w.x;
    sp20.y = v0->modInst->unk_010.wolrd_matrix.w.y;
    sp20.z = v0->modInst->unk_010.wolrd_matrix.w.z;

    if (obj) {} // @fake

    if (obj->vars[2] != 0) {
        func_800281F8(obj->vars[2], &sp20, &obj->pos);
    } else {
        obj->pos.x = sp20.x;
        obj->pos.z = sp20.z;
    }

    obj->pos.y = 0;
    obj->currentTask->func = func_80028090;
}

void func_80028558(Object *obj) {
    obj->currentTask->func = func_80028464;
}

void func_8002856C(Object *obj) {
    Object *v0;
    s16 s0 = ((Player *) obj->varObj[0])->playerId;

    v0 = func_8002BF1C(&D_8004934C, &D_80051F50, 0xABAB);
    if (v0 == NULL) {
        return;
    } else {
        v0->unk_058 = v0->unk_05C = v0->unk_060 = 0x64000;
        v0->currentTask->counter = 10;
        v0->unk_08C = 1;
        v0->vars[0] = s0;
        v0->vars[1] = 0;
        v0->vars[2] = 150;
        v0->unk_088.a = 60;
        v0->flags |= 4;
    }

    v0 = func_8002BF1C(&D_8004934C, &D_80051F50, 0xABAB);
    if (v0 == NULL) {
        return;
    } else {
        v0->unk_058 = v0->unk_05C = v0->unk_060 = 0x64000;
        v0->currentTask->counter = 10;
        v0->unk_08C = 1;
        v0->vars[0] = s0;
        v0->vars[1] = 3;
        v0->vars[2] = 50;
        v0->unk_088.a = 60;
        v0->flags |= 4;
    }

    v0 = func_8002BF1C(&D_8004934C, &D_80051F50, 0xABAB);
    if (v0 == NULL) {
        return;
    } else {
        v0->unk_058 = v0->unk_05C = v0->unk_060 = 0x64000;
        v0->currentTask->counter = 10;
        v0->unk_08C = 1;
        v0->vars[0] = s0;
        v0->vars[1] = 5;
        v0->vars[2] = -200;
        v0->unk_088.a = 40;
        v0->flags |= 4;
    }

    v0 = func_8002BF1C(&D_8004934C, &D_80051F50, 0xABAB);
    if (v0 == NULL) {
        return;
    } else {
        v0->unk_058 = v0->unk_05C = v0->unk_060 = 0x64000;
        v0->currentTask->counter = 10;
        v0->unk_08C = 1;
        v0->vars[0] = s0;
        v0->vars[1] = 7;
        v0->vars[2] = 100;
        v0->unk_088.a = 40;
        v0->flags |= 4;
    }

    v0 = func_8002BF1C(&D_8004934C, &D_80051F50, 0xABAB);
    if (v0 == NULL) {
        return;
    } else {
        v0->currentTask->counter = 10;
        v0->unk_058 = v0->unk_05C = v0->unk_060 = 0x64000;
        v0->unk_08C = 1;
        v0->vars[0] = s0;
        v0->vars[1] = 9;
        v0->vars[2] = -250;
        v0->unk_088.a = 30;
        v0->flags |= 4;
    }
}

void func_800287AC(Object *obj) {
    u32 i;
    Object *v0;
    s16 s4 = ((Player *) obj->varObj[0])->playerId;
    s32 a, b;

    a = 0;
    b = -250;
    for (i = 0; i < 13; i++) {
        v0 = func_8002BF1C(&D_8004934C, &D_80051F50, 0xABAB);
        if (v0 == NULL) {
            return;
        }

        v0->vars[1] = a;
        v0->vars[2] = b;
        v0->unk_058 = v0->unk_05C = v0->unk_060 = 0x64000;
        v0->unk_08C = 1;
        v0->vars[0] = s4;
        v0->unk_088.a = 40;
        v0->flags |= 4;

        b += 50;
        a += 3;
    }
}

void func_80028890(Object *obj) {
    gPlayerInput[PLAYER_1].unk_0A = FALSE;
    gPlayerInput[PLAYER_2].unk_0A = FALSE;

    if (obj->vars[0] == 0) {
        if (gPlayers[PLAYER_1].unk_7C == 0 && gPlayers[PLAYER_2].unk_7C == 0) {
            func_80028E84();
            obj->vars[0] = 240;
        }
    } else {
        obj->vars[0]--;
        if (obj->vars[0] == 0) {
            D_8005BFC0 |= 1;
            obj->currentTask->flags |= 0x80;
        }
    }
}

#ifdef NON_EQUIVALENT
s16 func_80028928(s16 playerId) {
    return (u32) (gPlayers[playerId].unk_70 * 80 * 0x10000) / 400 / 0x10000;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028928.s")
s16 func_80028928(s16 playerId);
#endif

void func_80028990(Vtx *vtx) {
    Gfx *gfx = D_8005BF58;

    if (D_8008012C & 1) {
        return;
    }

    D_8005BF00.header.unk_00 = 0;
    D_8005BF00.header.unk_04 = 0;
    D_8005BF00.header.numVertices = 4;
    D_8005BF00.header.unk_09 = 0;
    D_8005BF00.header.numTriangles = 2;
    D_8005BF00.header.unk_0B = 2;
    D_8005BF00.header.texGfx = D_8005BF58;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);

    gtStateSetOthermode(&D_8005BF10, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gtStateSetOthermode(&D_8005BF10, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(&D_8005BF10, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(&D_8005BF10, GT_PIPELINE, G_PM_NPRIMITIVE);

    gSPTriBatch(gOverlayBatchPos, NULL, &D_8005BF00, vtx, D_80049330);
}

void func_80028AE4(Object *obj) {
    s32 unused;
    s16 sp22;
    s16 a2;
    s16 sp1E;
    s16 sp1C;

    sp22 = D_8005BFCE;

    if (D_800801F0) {
        D_80051F6C = D_80051F70 = D_8013C2A8 = D_8013C2AA = 0;
    }

    if (D_8013C2A8 != 0) {
        func_80028990(D_80051F78[sp22]);
        D_8013C2A8--;
    } else if (D_80051F6C > 0) {
        D_80051F6C--;
        D_80051F78[sp22][0].v.ob[0] = D_80051F78[sp22][2].v.ob[0] = D_80051F78[sp22][1].v.ob[0] - 4 * D_80051F6C;
        func_80028990(D_80051F78[sp22]);
    }

    sp1C = func_80028928(PLAYER_1);
    if (sp1C != D_8013C230) {
        a2 = D_8013C230 - sp1C;
        D_8013C2A8 = 30 - D_8013C2A8 - D_80051F6C;
        if (D_8013C2A8 < 0) {
            D_8013C2A8 = 0;
        }

        D_80051F6C += a2;
        D_8013C234->unk_04 += a2;
        D_8013C234->unk_10 += a2;
        if (D_8013C234->unk_04 >= D_8013C234->unk_08) {
            D_8013C234->unk_04 = D_8013C234->unk_08;
        }

        D_80051F78[0][1].v.ob[0] = D_80051F78[1][1].v.ob[0] = D_80051F78[0][3].v.ob[0] = D_80051F78[1][3].v.ob[0] =
            (35 + D_8013C234->unk_04) << 2;
        D_80051F78[0][0].v.ob[0] = D_80051F78[1][0].v.ob[0] = D_80051F78[0][2].v.ob[0] = D_80051F78[1][2].v.ob[0] =
            D_80051F78[0][1].v.ob[0] - 4 * D_80051F6C;

        func_80028990(D_80051F78[sp22]);
        D_8013C230 = sp1C;
    }

    if (D_8013C2AA != 0) {
        func_80028990(D_80051FF8[sp22]);
        D_8013C2AA--;
    } else if (D_80051F70 > 0) {
        D_80051F70--;
        D_80051FF8[sp22][1].v.ob[0] = D_80051FF8[sp22][3].v.ob[0] = D_80051FF8[sp22][0].v.ob[0] + 4 * D_80051F70;
        func_80028990(D_80051FF8[sp22]);
    }

    sp1E = func_80028928(PLAYER_2);
    if (sp1E != D_8013C232) {
        a2 = D_8013C232 - sp1E;
        // clang-format off
        D_8013C2AA = 30 - D_8013C2AA - D_80051F70;\
        if (D_8013C2AA < 0) {
            D_8013C2AA = 0;
        }
        // clang-format on

        D_80051F70 += a2;
        D_8013C238->unk_08 -= a2;
        if (D_8013C238->unk_04 >= D_8013C238->unk_08) {
            D_8013C238->unk_04 = D_8013C238->unk_08;
        }

        D_80051FF8[0][0].v.ob[0] = D_80051FF8[1][0].v.ob[0] = D_80051FF8[0][2].v.ob[0] = D_80051FF8[1][2].v.ob[0] =
            (217 + D_8013C238->unk_08) << 2;
        D_80051FF8[0][1].v.ob[0] = D_80051FF8[1][1].v.ob[0] = D_80051FF8[0][3].v.ob[0] = D_80051FF8[1][3].v.ob[0] =
            D_80051FF8[0][0].v.ob[0] + 4 * D_80051F70;

        func_80028990(D_80051FF8[sp22]);
        D_8013C232 = sp1E;
    }
}

void func_80028E84(void) {
    s16 v0, v1;

    v0 = gPlayers[PLAYER_1].unk_00->unk_070;
    v1 = gPlayers[PLAYER_2].unk_00->unk_070;
    if (v0 > v1) {
        func_8000636C(&gPlayers[PLAYER_1], 132, 1);
        func_8000636C(&gPlayers[PLAYER_2], 384, 1);
    } else if (v0 < v1) {
        func_8000636C(&gPlayers[PLAYER_1], 384, 1);
        func_8000636C(&gPlayers[PLAYER_2], 132, 1);
    } else {
        func_8000636C(&gPlayers[PLAYER_1], 384, 1);
        func_8000636C(&gPlayers[PLAYER_2], 384, 1);
    }
}

void func_80028F38(Object *obj) {
    Object *v1;

    if (D_800801F0) {
        obj->currentTask->flags |= 0x80;
    }

    obj->currentTask->counter = 60;

    v1 = obj->varObj[0];
    if (--v1->spriteId < 0) {
        v1->spriteId = 9;
        if (--obj->spriteId < 0) {
            obj->spriteId = 0;
            D_800801F0 = TRUE;
            v1->spriteId = 0;
            obj->currentTask->flags |= 0x80;
        }
    }
}

void func_80028FCC(void) {
    if (D_80080230 != 40 && D_8004C1D4 != 0) {
        D_8013C240->currentTask->func = func_80028F38;
        D_8013C240->currentTask->counter = 0;
        D_8013C240->currentTask->flags = 1;
        D_8013C23C->currentTask->counter = 120;
    }
}

void func_80029044(void) {
    s16 i = 0;
    Object *a0;

    if (D_8013C248 != NULL) {
        D_8013C248->flags |= 0x10;
        D_8013C248->flags &= ~0x4000000;
        D_80081438++;
        D_80081434++;

        while (D_8013C248->varObj[i] != NULL) {
            D_80081438++;
            D_80081434++;
            D_8013C248->varObj[i]->flags |= 0x10;
            D_8013C248->varObj[i]->flags &= ~0x4000000;
            i++;
        }

        D_8013C248 = NULL;
    }
}

void func_80029130(void) {
    UIElement sp74 = { 28, NULL, 0x4000000, 0x1001, "bars.sp2" };
    UIElement sp60 = { 27, NULL, 0x4000000, 0x1001, "bars.sp2" };
    Vec4i sp50 = { 32, 220, 0, 0 };
    Vec4i sp40 = { 236, 220, 0, 0 };
    s16 s0;
    s16 s3;
    s16 s2;
    Object *v0;

    D_8013C248 = NULL;
    s0 = D_800B6328[PLAYER_1].unk_0A;
    if (s0 != 0) {
        D_8013C248 = create_ui_element(&sp50, &sp60, 0xABAB);
        D_80081438--;
        D_80081434--;
        s3 = 0;
        s2 = 0;

        if (s0 >= 1000) {
            s0 = 1;
            D_800B6328[PLAYER_1].unk_0A = 1;
        }

        if (s0 >= 100) {
            v0 = create_ui_element(D_800520D8[s3], &sp74, 0xABAB);
            D_80081438--;
            v0->spriteId = 28 + (s0 / 100);
            D_8013C248->varObj[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 100;
            task_clear(v0->taskList);
            v0->taskList = NULL;
        }

        if (D_800B6328[PLAYER_1].unk_0A >= 10) {
            v0 = create_ui_element(D_800520D8[s3], &sp74, 0xABAB);
            D_80081438--;
            v0->spriteId = 28 + (s0 / 10);
            D_8013C248->varObj[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 10;
            task_clear(v0->taskList);
            v0->taskList = NULL;
        }

        v0 = create_ui_element(D_800520D8[s3], &sp74, 0xABAB);
        D_80081438--;
        v0->spriteId = 28 + s0;
        D_8013C248->varObj[s2] = v0;
        s2++;
        D_8013C248->varObj[s2] = NULL;
        task_clear(v0->taskList);
        v0->taskList = NULL;

        task_clear(D_8013C248->taskList);
        D_8013C248->taskList = NULL;
    }

    s0 = D_800B6328[PLAYER_2].unk_0A;
    if (s0 != 0) {
        D_8013C248 = create_ui_element(&sp40, &sp60, 0xABAB);
        D_80081438--;
        s3 = 3;
        s2 = 0;

        if (s0 >= 1000) {
            s0 = 1;
            D_800B6328[PLAYER_2].unk_0A = 1;
        }

        if (s0 >= 100) {
            v0 = create_ui_element(D_800520D8[s3], &sp74, 0xABAB);
            D_80081438--;
            v0->spriteId = 28 + (s0 / 100);
            D_8013C248->varObj[s2] = v0;
            s2++;
            s3++;
            s0 = s0 % 100;
            task_clear(v0->taskList);
            v0->taskList = NULL;
        }

        if (D_800B6328[PLAYER_2].unk_0A >= 10) {
            v0 = create_ui_element(D_800520D8[s3], &sp74, 0xABAB);
            D_80081438--;
            v0->spriteId = 28 + (s0 / 10);
            D_8013C248->varObj[s2] = v0;
            s2++;

            s0 = s0 % 10;
            s3++;
            task_clear(v0->taskList);
            v0->taskList = NULL;
        }

        v0 = create_ui_element(D_800520D8[s3], &sp74, 0xABAB);
        D_80081438--;
        v0->spriteId = 28 + s0;
        D_8013C248->varObj[s2] = v0;
        s2++;
        D_8013C248->varObj[s2] = NULL;
        task_clear(v0->taskList);
        v0->taskList = NULL;

        task_clear(D_8013C248->taskList);
        D_8013C248->taskList = NULL;
    }
}

void func_80029630(void) {
    Object *v0;
    Object *s00;
    s16 s0;
    s16 s1;
    UIElement sp120 = { 10, NULL, 0, 0x1000, "bars.sp2" };
    UIElement sp10C = { 10, NULL, 0, 0x1000, "bars.sp2" };
    UIElement spF8 = { 0, NULL, 0, 0x1001, "bars.sp2" };
    UIElement spE4 = { 0, NULL, 0, 0x1001, "bars.sp2" };
    s32 pad[2];
    Vec4i spCC = { 167, 49, 0, 0 };
    Vec4i spBC = { 160, 75, 0, 0 };
    Vec4i spAC = { 173, 75, 0, 0 };
    Vec4i sp9C = { 75, 39, 0, 0 };
    Vec4i sp8C = { 257, 39, 0, 0 };
    Vec4i sp7C = { 146, 64, 0, 0 };
    Vec4i sp6C = { 187, 64, 0, 0 };
    Vec4i sp5C = { 74, 39, 0, 0 };
    Vec4i sp4C = { 257, 39, 0, 0 };

    if (D_80080230 == 40) {
        return;
    }

    create_ui_element(&spCC, &sp10C, 0xABAB);

    switch (D_8004C1D4) {
        case 0:
            break;
        case 1:
        case 2:
            s00 = create_ui_element(&spAC, &spF8, 0xABAB);
            v0 = create_ui_element(&spBC, &spE4, 0xABAB);
            v0->spriteId = D_8004C1D4 * 3 + 3;
            v0->varObj[0] = s00;
            D_8013C240 = v0;
            break;
    }

    v0 = create_ui_element(&sp9C, &sp120, 0xABAB);
    v0->spriteId = 11;
    task_clear(v0->taskList);
    v0->taskList = NULL;

    v0 = create_ui_element(&sp8C, &sp120, 0xABAB);
    v0->spriteId = 11;
    task_clear(v0->taskList);
    v0->taskList = NULL;

    s0 = 0;
    for (s1 = 0; s1 < D_800B6328[PLAYER_1].unk_08; s1++) {
        D_8013C258[PLAYER_1][s1] = v0 = create_ui_element(&sp7C, &sp120, 0xABAB);
        v0->spriteId = 13;
        sp7C.x -= 8;
        s0++;
        task_clear(v0->taskList);
        v0->taskList = NULL;
    }

    for (; s0 < D_8004C1D0; s0++) {
        D_8013C258[PLAYER_1][s0] = v0 = create_ui_element(&sp7C, &sp120, 0xABAB);
        v0->spriteId = 12;
        sp7C.x -= 8;
        task_clear(v0->taskList);
        v0->taskList = NULL;
    }

    s0 = 0;
    for (s1 = 0; s1 < D_800B6328[PLAYER_2].unk_08; s1++) {
        D_8013C258[PLAYER_2][s1] = v0 = create_ui_element(&sp6C, &sp120, 0xABAB);
        v0->spriteId = 13;
        sp6C.x += 8;
        s0++;
        task_clear(v0->taskList);
        v0->taskList = NULL;
    }

    for (; s0 < D_8004C1D0; s0++) {
        D_8013C258[PLAYER_2][s0] = v0 = create_ui_element(&sp6C, &sp120, 0xABAB);
        v0->spriteId = 12;
        sp6C.x += 8;
        task_clear(v0->taskList);
        v0->taskList = NULL;
    }

    v0 = create_ui_element(&sp5C, &sp120, 0xABAB);
    v0->spriteId = 15;
    D_8013C234 = v0->sprite_map->sprites[15].parts;
    D_8013C234->unk_10 = D_8013C234->unk_10 - D_8013C234->unk_04 + D_8013C234->unk_08 - 88;
    D_8013C234->unk_04 = D_8013C234->unk_08 - 88;

    v0 = create_ui_element(&sp4C, &sp120, 0xABAB);
    v0->spriteId = 14;
    D_8013C238 = v0->sprite_map->sprites[14].parts;
    D_8013C238->unk_08 = D_8013C238->unk_04 + 80;

    v0 = create_ui_element(&D_8004A5D0[D_800B6328[PLAYER_1].characterId], &sp120, 0xABAB);
    if (D_800B6328[PLAYER_1].characterId < CHARACTER_5) {
        v0->spriteId = 16 + D_800B6328[PLAYER_1].characterId;
    } else {
        v0->spriteId = 16 + D_800B6328[PLAYER_1].characterId - 1;
    }
    task_clear(v0->taskList);
    v0->taskList = NULL;

    v0 = create_ui_element(&D_8004A680[D_800B6328[PLAYER_2].characterId], &sp120, 0xABAB);
    if (D_800B6328[PLAYER_2].characterId < CHARACTER_5) {
        v0->spriteId = 16 + D_800B6328[PLAYER_2].characterId;
    } else {
        v0->spriteId = 16 + D_800B6328[PLAYER_2].characterId - 1;
    }
    task_clear(v0->taskList);
    v0->taskList = NULL;

    D_8013C232 = D_8013C230 = 80;
    D_8013C244 = create_worker(func_80028AE4, 0x1000);
    func_80029130();
}

// TODO split files, so D_80052220 (52E20) is in another file

void func_80029D04(Object *obj) {
    if (--obj->spriteId < 2) {
        D_8005BFC0 |= 0x40;
        obj->flags |= 0x10;
    }

    D_8005BEFC -= 2;
    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_80029D84(Object *obj) {
    func_80002178(D_8005BEFC, NULL);
    obj->flags |= 0x10;
}

void func_80029DC0(Object *obj) {
    if (++obj->spriteId >= 130) {
        D_8005BFC0 |= 0x41;
        gGameMode = GAME_MODE_0;
        D_8005BFC0 |= 0x80;
        obj->flags &= ~0x2000000;
        obj->fn_render = func_80029D84;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_80029E5C(Object *obj) {
    if (--obj->spriteId <= 60) {
        obj->fn_render = func_8002A050;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_80029EBC(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029DC0;
    } else if (buttons & INP_RIGHT) {
        obj->spriteId = 118;
        obj->fn_render = func_80029F58;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_80029F58(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029E5C;
    } else if (buttons & INP_LEFT) {
        obj->spriteId = 120;
        obj->fn_render = func_80029EBC;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_80029FF4(Object *obj) {
    if (obj->spriteId >= 118) {
        obj->fn_render = func_80029F58;
    } else {
        obj->spriteId++;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A050(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029FF4;
    } else if (buttons & INP_UP) {
        obj->fn_render = func_8002A0EC;
        obj->spriteId = 58;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A0EC(Object *obj) {
    u16 buttons;
    s16 playerId;

    buttons = 0;
    playerId = obj->vars[0];

    if (gPlayerInput[playerId].unk_08) {
        buttons = gPlayerInput[playerId].buttons;
    }

    if (buttons & INP_START) {
        obj->fn_render = func_80029D04;
    } else if (buttons & INP_DOWN) {
        obj->fn_render = func_8002A050;
        obj->spriteId = 60;
    }

    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A188(Object *obj) {
    if (obj->spriteId >= 58) {
        obj->fn_render = func_8002A0EC;
    } else {
        obj->spriteId++;
    }
    D_8005BEFC += 2;
    func_80002178(D_8005BEFC, NULL);
    func_800386E8(obj);
}

void func_8002A1F0(Object *obj) {
    obj->fn_render = func_8002A188;
    obj->flags &= ~4;
    obj->spriteId++;
    obj->currentTask->func = task_default_func;
    gTasksDisabled = TRUE;
    obj->flags |= 0x2000000;
    D_8005BEFC = 0;
}

void func_8002A250(Object *obj) {
    if (obj->spriteId++ > 16) {
        obj->flags |= 0x10;
    }
    obj->currentTask->counter = 2;
}
