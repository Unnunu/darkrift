#include "common.h"
#include "task.h"

typedef struct UnkOmicron {
    /* 0x0 */ char unk_00[0x1000];
    /* 0x1000 */ u16 unk_1000;
    /* 0x1002 */ u16 unk_1002;
    /* 0x1004 */ s32 unk_1004;
    /* 0x1008 */ s32 unk_1008;
} UnkOmicron;

extern s16 D_8004A730[];
extern s16 D_8004A748[];
extern char D_8004B654[]; // TODO: type
extern char D_8004B674[]; // TODO: type
extern char D_8004B774[]; // TODO: type
extern char D_8004B794[]; // TODO: type
extern PlayerSub5 D_8004C1E8[];

extern UnkOmicron D_80080238;
extern s32 D_8008020C;
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

void func_80004FC0(Object *obj) {
    ColorRGBA *sp1C = obj->varObj[0];
    ColorRGBA *sp18 = obj->varObj[1];
    u32 v1;

    if (--obj->vars[2] <= 0) {
        v1 = (guRandom() % 192) + 64;
        sp18->r = sp1C->r * v1 / 256;
        sp18->g = sp1C->g * v1 / 256;
        sp18->b = sp1C->b * v1 / 256;
        obj->vars[2] = 8;
    }
}

void func_80005060(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->unk_00->modInst->transforms[5].wolrd_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

void func_800050B0(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->unk_00->modInst->unk_010.wolrd_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

s32 D_80049390 = 0xFFFF0000;
s32 D_80049394 = 0xFFFF0000;

void func_800050FC(u16 arg0, u16 arg1) {
    ColorRGBA sp38[] = { { 0, 200, 0, 0 }, { 200, 0, 0, 0 } };
    ColorRGBA sp30[] = { { 0, 0, 255, 0 }, { 200, 50, 0, 0 } };
    Object *sp2C;

    switch (arg1) {
        case EVE:
            sp2C = create_worker(func_80005060, 0x1000);
            func_8003453C(sp2C, &sp38[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case MORPHIX:
            sp2C = create_worker(func_800050B0, 0x1000);
            func_8003453C(sp2C, &sp30[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case DEMITRON:
            if (D_800B6328[arg0].unk_06) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = D_8004B774;
                sp2C->varObj[1] = D_8004B654;
            }
            break;
        case DEMONICA:
            if (D_800B6328[arg0].unk_06) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = D_8004B794;
                sp2C->varObj[1] = D_8004B674;
            }
            break;
    }
}

void func_800052EC(s16 playerId) {
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

    func_80004E14(playerId);

    gPlayers[playerId].unk_04 = playerId;
    gPlayers[playerId].unk_80 = 0;
    spD6 = gPlayers[playerId].characterId = D_800B6328[playerId].characterId;

    if (D_800B6328[playerId].unk_10) {
        spD6 = AARON;
        str_copy(spA4, "dum.tmd");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->unk_00);
        if (spD6 != MORPHIX) {
            if (playerId != 0) {
                str_concat(spA4, "2.tmd");
            } else {
                str_concat(spA4, ".tmd");
            }
        } else {
            if (playerId != 0) {
                str_concat(spA4, "2.k3");
            } else {
                str_concat(spA4, ".k3");
            }
        }
    }

    spDC = gPlayers[playerId].unk_00 = func_8002BC84(&spB4[playerId], spA4, D_8004B844[spD6].unk_04, playerId);
    spDC->flags |= 0x80;

    if (spD6 == MORPHIX && !D_800B6328[playerId].unk_10) {
        func_8002A890(gPlayers + playerId);
    }

    if (D_800B6328[playerId].unk_10) {
        str_copy(spA4, "dumshad.k4");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->unk_00);
        spA4[3] = '\0';
        if (playerId != 0) {
            do {
            } while (0);
            str_concat(spA4, "shad2.k4");
        } else {
            str_concat(spA4, "shad.k4");
        }
    }

    func_80036194(spDC, spA4, playerId);

    spDC->rotation.y = 0xC00 - spB0[playerId];
    spDC->fn_render = func_80003DA4;
    if (spDC->currentTask && spDC->currentTask) {} // @fake
    spDC->varObj[0] = gPlayers + playerId;

    i = 0;
    str_copy(sp74, str2);
    while (TRUE) {
        v00 = asset_find(sp74, playerId);
        if (v00 >= 0) {
            gPlayers[playerId].unk_DC0[i++] = gAssets[v00].aux_data;
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
        v00 = asset_find(sp74, playerId);
        if (v00 >= 0) {
            gPlayers[playerId].unk_DCC[i++] = gAssets[v00].aux_data;
        } else {
            v00 = asset_find(sp60, playerId);
            if (v00 >= 0) {
                gPlayers[playerId].unk_DCC[i++] = gAssets[v00].aux_data;
            } else {
                break;
            }
        }

        sp74[3]++;
        sp60[3]++;
    }

    func_800045B4(playerId, spD6);

    gPlayers[playerId].unk_08 = spDC->currentTask;
    gPlayers[playerId].unk_0C = task_add(spDC, task_default_func, 1);
    gPlayers[playerId].unk_10 = task_add(spDC, func_800248C4, 1);
    gPlayers[playerId].unk_14 = task_add(spDC, task_default_func, 1);
    gPlayers[playerId].unk_18 = task_add(spDC, func_8003184C, 1);
    gPlayers[playerId].unk_24 = D_8004C1E8;

    D_80080214 = D_8004A730[D_800B6328[PLAYER_1].characterId] + D_8004A730[D_800B6328[PLAYER_2].characterId];
    D_80080218 = D_8004A748[D_800B6328[PLAYER_1].characterId] + D_8004A748[D_800B6328[PLAYER_2].characterId];
    D_8008020C = 0x800;
    D_80080210 = 0x640;

    D_80080228[playerId] = spDC;
    D_80080238.unk_1000 = D_80080238.unk_1002 = 0;
    D_80080238.unk_1008 = gFrameCounter;

    D_80080236 = 1;

    if ((D_800B6328[playerId].unk_02) != 0) {
        func_8000636C(gPlayers + playerId, 282, 0, D_8004A748);
    } else {
        func_8000636C(gPlayers + playerId, 68, 0, D_8004A748);
    }

    if (playerId != 0) {
        D_80080236 = 0;
    }

    gPlayers[playerId].unk_90 = gPlayers[playerId].unk_20 + gPlayers[playerId].unk_7E;
    func_80010664(&gPlayers[playerId], D_8004B844[spD6].unk_00);

    spDC->unk_070 = D_800B6328[playerId].unk_0C;
    func_80004B30(spDC, playerId, spD6);

    if (playerId == 0) {
        gPlayerInput[playerId].unk_09 = TRUE;
    }

    func_80012150(&gPlayers[playerId].unk_DE8, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_08].wolrd_matrix,
                  &gPlayers[playerId].unk_2E8.wolrd_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[playerId]);

    if (D_8004B844[spD6].unk_00->unk_1C >= 0) {
        func_80012150(&gPlayers[playerId].unk_2240, spDC->modInst,
                      &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_04].wolrd_matrix,
                      &gPlayers[playerId].unk_1D0.wolrd_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[playerId]);
        gPlayers[playerId].unk_5F4A = 1;
    } else {
        gPlayers[playerId].unk_5F4A = 0;
    }

    func_80012150(&gPlayers[playerId].unk_3698, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_14].wolrd_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_0C].wolrd_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[playerId]);
    func_80012150(&gPlayers[playerId].unk_4AF0, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_18].wolrd_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_10].wolrd_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[playerId]);

    gPlayers[playerId].unk_184 = 0;
    if (D_80080230 == 40) {
        if (playerId == gPracticingPlayer) {
            practice_init_hud();
        } else {
            gPlayers[playerId].unk_80 |= 0x200000;
        }
    }

    func_800050FC(playerId, spD6);
}

s32 D_800493CC = 0xFFFFFE70;

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80005B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80005EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_8000636C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800063C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_8000642C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800069C0.s")
