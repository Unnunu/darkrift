#include "common.h"
#include "PR/gt.h"
#include "task.h"

const char D_80054F70[] = "dusthit.sp3";

extern Vec4i D_8004A5D0[];
extern Vec4i D_8004A680[];
extern Vtx D_80051F78[2][4];
extern Vtx D_80051FF8[2][4];
extern Vec4i *D_800520D8[];

extern s32 D_80081434;
extern s32 D_80081438;

extern s16 D_8013C230;
extern s16 D_8013C232;
extern AssetSP2Sub3 *D_8013C234;
extern AssetSP2Sub3 *D_8013C238;
extern Object *D_8013C240;
extern Object *D_8013C244;
extern Object *D_8013C248;
extern Object *D_8013C258[2][10];

void func_8002A050(Object *obj);
void func_8002A0EC(Object *obj);
void func_80029F58(Object *obj);
void func_80028E84(void);

void func_8000636C(Player *, s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028010.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_800281F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028400.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_80028558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_8002856C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/28C10/func_800287AC.s")

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
