#include "common.h"
#include "task.h"

typedef struct UnkOmicron {
    /* 0x0 */ char unk_00[0x1000];
    /* 0x1000 */ u16 unk_1000;
    /* 0x1002 */ u16 unk_1002;
    /* 0x1004 */ s32 unk_1004;
    /* 0x1008 */ s32 unk_1008;
} UnkOmicron;

extern UnkOmicron D_80080238;
extern PlayerSub5 D_8004C1E8[];
extern s16 D_8004A730[];
extern s16 D_8004A748[];
extern s32 D_8008020C;
extern s32 D_80080210;
extern s32 D_80080214;
extern s32 D_80080218;
extern u16 D_80080236;

void func_8000636C(Player *, s32, s32, s16 *);
void func_80012150(PlayerSub6 *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4, s32 *arg5);

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800035D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800036E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800038C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003974.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003BB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003C04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003DA4.s")
void func_80003DA4(Object *);

void func_80004304(char *arg0, char *arg1, char *arg2) {
    str_copy(arg0, arg1);
    str_concat(arg0, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80004334.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800045B4.s")
void func_800045B4(s16 arg0, s16 arg1);

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80004AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80004B30.s")
void func_80004B30(Object *, s16, s16);

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80004D40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80004E14.s")
void func_80004E14(s16);

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80004FC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80005060.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800050B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800050FC.s")
void func_800050FC(u16 arg0, u16 arg1);

s32 D_800493A0[] = { 0x0000FF00, 0xC8320000 };

void func_800052EC(s16 arg0) {
    Object *spDC;
    s16 v00;
    s16 i;
    s16 spD6;
    Vec4i spB4[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 spB0[] = { 0, 0x800 };
    char spA4[12];
    char sp74[48];
    char *str1 = "mod0.k2";
    char *str2 = "spr0.sp3";
    char sp60[12];

    func_80004E14(arg0);

    D_800AA488[arg0].unk_04 = arg0;
    D_800AA488[arg0].unk_80 = 0;
    spD6 = D_800AA488[arg0].characterId = D_800B6328[arg0].characterId;

    if (D_800B6328[arg0].unk_10) {
        spD6 = AARON;
        str_copy(spA4, "dum.tmd");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->unk_00);
        if (spD6 != MORPHIX) {
            if (arg0 != 0) {
                str_concat(spA4, "2.tmd");
            } else {
                str_concat(spA4, ".tmd");
            }
        } else {
            if (arg0 != 0) {
                str_concat(spA4, "2.k3");
            } else {
                str_concat(spA4, ".k3");
            }
        }
    }

    spDC = D_800AA488[arg0].unk_00 = func_8002BC84(&spB4[arg0], spA4, D_8004B844[spD6].unk_04, arg0);
    spDC->flags |= 0x80;

    if (spD6 == MORPHIX && !D_800B6328[arg0].unk_10) {
        func_8002A890(D_800AA488 + arg0);
    }

    if (D_800B6328[arg0].unk_10) {
        str_copy(spA4, "dumshad.k4");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->unk_00);
        spA4[3] = '\0';
        if (arg0 != 0) {
            do {
            } while (0);
            str_concat(spA4, "shad2.k4");
        } else {
            str_concat(spA4, "shad.k4");
        }
    }

    func_80036194(spDC, spA4, arg0);

    spDC->rotation.y = 0xC00 - spB0[arg0];
    spDC->fn_render = func_80003DA4;
    if (spDC->currentTask && spDC->currentTask) {} // @fake
    spDC->varObj[0] = D_800AA488 + arg0;

    i = 0;
    str_copy(sp74, str2);
    while (TRUE) {
        v00 = asset_find(sp74, arg0);
        if (v00 >= 0) {
            D_800AA488[arg0].unk_DC0[i++] = gAssets[v00].aux_data;
        } else {
            break;
        }
        sp74[3]++;
    }

    i = 0;
    str_copy(sp74, str1);
    str_copy(sp60, str1);
    sp60[6] = '5';
    while (TRUE) {
        v00 = asset_find(sp74, arg0);
        if (v00 >= 0) {
            D_800AA488[arg0].unk_DCC[i++] = gAssets[v00].aux_data;
        } else {
            v00 = asset_find(sp60, arg0);
            if (v00 >= 0) {
                D_800AA488[arg0].unk_DCC[i++] = gAssets[v00].aux_data;
            } else {
                break;
            }
        }

        sp74[3]++;
        sp60[3]++;
    }

    func_800045B4(arg0, spD6);

    D_800AA488[arg0].unk_08 = spDC->currentTask;
    D_800AA488[arg0].unk_0C = task_add(spDC, task_default_func, 1);
    D_800AA488[arg0].unk_10 = task_add(spDC, func_800248C4, 1);
    D_800AA488[arg0].unk_14 = task_add(spDC, task_default_func, 1);
    D_800AA488[arg0].unk_18 = task_add(spDC, func_8003184C, 1);
    D_800AA488[arg0].unk_24 = D_8004C1E8;

    D_80080214 = D_8004A730[D_800B6328[PLAYER_1].characterId] + D_8004A730[D_800B6328[PLAYER_2].characterId];
    D_80080218 = D_8004A748[D_800B6328[PLAYER_1].characterId] + D_8004A748[D_800B6328[PLAYER_2].characterId];
    D_8008020C = 0x800;
    D_80080210 = 0x640;

    D_80080228[arg0] = spDC;
    D_80080238.unk_1000 = D_80080238.unk_1002 = 0;
    D_80080238.unk_1008 = gFrameCounter;

    D_80080236 = 1;

    if ((D_800B6328[arg0].unk_02) != 0) {
        func_8000636C(D_800AA488 + arg0, 282, 0, D_8004A748);
    } else {
        func_8000636C(D_800AA488 + arg0, 68, 0, D_8004A748);
    }

    if (arg0 != 0) {
        D_80080236 = 0;
    }

    D_800AA488[arg0].unk_90 = D_800AA488[arg0].unk_20 + D_800AA488[arg0].unk_7E;
    func_80010664(&D_800AA488[arg0], D_8004B844[spD6].unk_00);

    spDC->unk_070 = D_800B6328[arg0].unk_0C;
    func_80004B30(spDC, arg0, spD6);

    if (arg0 == 0) {
        gPlayerInput[arg0].unk_09 = TRUE;
    }

    func_80012150(&D_800AA488[arg0].unk_DE8, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_08].wolrd_matrix,
                  &D_800AA488[arg0].unk_2E8.wolrd_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[arg0]);

    if (D_8004B844[spD6].unk_00->unk_1C >= 0) {
        func_80012150(&D_800AA488[arg0].unk_2240, spDC->modInst,
                      &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_04].wolrd_matrix,
                      &D_800AA488[arg0].unk_1D0.wolrd_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[arg0]);
        D_800AA488[arg0].unk_5F4A = 1;
    } else {
        D_800AA488[arg0].unk_5F4A = 0;
    }

    func_80012150(&D_800AA488[arg0].unk_3698, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_14].wolrd_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_0C].wolrd_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[arg0]);
    func_80012150(&D_800AA488[arg0].unk_4AF0, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_18].wolrd_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_10].wolrd_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[arg0]);

    D_800AA488[arg0].unk_184 = 0;
    if (D_80080230 == 40) {
        if (arg0 == gPracticingPlayer) {
            func_800321C0();
        } else {
            D_800AA488[arg0].unk_80 |= 0x200000;
        }
    }

    func_800050FC(arg0, spD6);
}

s32 D_800493CC = 0xFFFFFE70;

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80005B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80005EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_8000636C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800063C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_8000642C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800069C0.s")
