#include "common.h"

const char D_800549C0[] = "bars.sp2";
const char D_800549CC[] = "bars.sp2";
const char D_800549D8[] = "bars.sp2";
const char D_800549E4[] = "grpp1.sp2";
const char D_800549F0[] = "grpp2.sp2";
const char D_800549FC[] = "options2.sp2";
const char D_80054A0C[] = "options2.sp2";
const char D_80054A1C[] = "bars.sp2";
const char D_80054A28[] = "bars.sp2";
const char D_80054A34[] = "bars.sp2";
const char D_80054A40[] = "options2.sp2";
const char D_80054A50[] = "practice.sp2";
const char D_80054A60[] = "practice.sp2";

typedef struct UnkSigma {
    /* 0x00 */ u16 *unk_00;
    /* 0x04 */ void (*unk_04)(s16, u16, u16);
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} UnkSigma; // size = 0xC

typedef struct UnkRho {
    /* 0x00 */ UnkSigma *unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 buttons;
} UnkRho;

void func_80020298(s16, u16, u16);
void func_800201A4(s16, u16, u16);
void func_8002025C(s16, u16, u16);
void func_800202D0(s16, u16, u16);
void func_800203A8(s16, u16, u16);
void func_800202F0(s16, u16, u16);

s32 D_8004A020[] = { 0xD9, 0, 0 };

u16 D_8004A02C[] = { INP_L, INP_R, INP_CUP, INP_CDOWN, INP_CLEFT, INP_CRIGHT, -1 };
u16 D_8004A03C[] = { INP_A, INP_B, INP_R, INP_L, INP_CDOWN, INP_CUP, -1 };

u16 D_8004A04C[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CLEFT, -1 };
u16 D_8004A060[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CUP, -1 };
u16 D_8004A074[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CRIGHT, -1 };
u16 D_8004A088[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CDOWN, -1 };
u16 D_8004A09C[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_B, -1 };
u16 D_8004A0B0[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_A, -1 };
u16 D_8004A0C4[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CLEFT, -1 };
u16 D_8004A0D8[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CUP, -1 };
u16 D_8004A0EC[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CRIGHT, -1 };
u16 D_8004A100[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CDOWN, -1 };

u16 D_8004A114[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_B, INP_B, INP_B, INP_CUP, -1 };

u16 D_8004A128[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_B, INP_B, INP_B, INP_B, -1 };
u16 D_8004A13C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CLEFT, -1 };
u16 D_8004A14C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CUP, -1 };
u16 D_8004A15C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CRIGHT, -1 };
u16 D_8004A16C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_CDOWN, -1 };
u16 D_8004A17C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CLEFT, -1 };
u16 D_8004A18C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CUP, -1 };
u16 D_8004A19C[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CRIGHT, -1 };
u16 D_8004A1AC[] = { INP_LEFT, INP_CUP, INP_CLEFT, INP_CUP, INP_A, INP_A, INP_CDOWN, -1 };

u16 D_8004A1BC[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_CLEFT, -1 };
u16 D_8004A1CC[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_CUP, -1 };
u16 D_8004A1E0[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_CRIGHT, -1 };
u16 D_8004A1F4[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_CDOWN, -1 };
u16 D_8004A208[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_A, -1 };
u16 D_8004A21C[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_CLEFT, -1 };
u16 D_8004A230[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_CUP, -1 };
u16 D_8004A244[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_CRIGHT, -1 };
u16 D_8004A258[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_B, INP_CDOWN, -1 };
u16 D_8004A270[] = { INP_B, INP_CUP, INP_R, INP_R, INP_CUP, INP_B, INP_B, INP_B, INP_B, INP_A, -1 };

UnkSigma D_8004A288[] = {
    { D_8004A114, func_80020298, 0, 0 },   { D_8004A02C, func_800201A4, 1, 0 },  { D_8004A03C, func_800201A4, 1, 1 },
    { D_8004A04C, func_8002025C, 0, 0 },   { D_8004A060, func_8002025C, 2, 0 },  { D_8004A074, func_8002025C, 3, 0 },
    { D_8004A088, func_8002025C, 4, 0 },   { D_8004A09C, func_8002025C, 6, 0 },  { D_8004A0B0, func_8002025C, 7, 0 },
    { D_8004A0C4, func_8002025C, 8, 0 },   { D_8004A0D8, func_8002025C, 9, 0 },  { D_8004A0EC, func_8002025C, 10, 0 },
    { D_8004A100, func_8002025C, 1, 0 },   { D_8004A13C, func_800202D0, 0, 0 },  { D_8004A14C, func_800202D0, 1, 0 },
    { D_8004A15C, func_800202D0, 2, 0 },   { D_8004A16C, func_800202D0, 3, 0 },  { D_8004A17C, func_800202D0, 4, 0 },
    { D_8004A18C, func_800202D0, 5, 0 },   { D_8004A19C, func_800202D0, 6, 0 },  { D_8004A1AC, func_800202D0, 7, 0 },
    { D_8004A1BC, func_800203A8, 0, 6 },   { D_8004A1CC, func_800203A8, 1, 7 },  { D_8004A1E0, func_800203A8, 2, 8 },
    { D_8004A1F4, func_800203A8, 3, 9 },   { D_8004A208, func_800203A8, 4, 10 }, { D_8004A21C, func_800203A8, 6, 12 },
    { D_8004A230, func_800203A8, 7, 13 },  { D_8004A244, func_800203A8, 8, 14 }, { D_8004A258, func_800203A8, 9, 15 },
    { D_8004A270, func_800203A8, 10, 16 }, { D_8004A128, func_800202F0, 0, 0 },  { NULL, NULL, 0, 0 }
};

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001DE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001DFE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E188.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E378.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E5D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E624.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E834.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001EA24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001EB58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001EF28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001F1D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001F450.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001F4E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001F6E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001F748.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/run_player_selection_mode.s")

void func_800201A4(s16 playerId, u16 arg0, u16 gameMode) {
    D_80049DF0 = arg0;
    D_80049DF4 = gameMode;
}

void func_800201C4(s16 arg0, s16 playerId) {
    D_8005BFC0 |= 1;
    gGameMode = GAME_MODE_34;

    D_800B6328[playerId].unk_00 = arg0;
    D_800B6328[playerId].unk_02 = 0;
    D_800B6328[playerId].unk_06 = 0;

    D_800B6328[1 - playerId].unk_00 = 1;
    D_800B6328[1 - playerId].unk_02 = 1;
    D_800B6328[1 - playerId].unk_06 = 1;

    func_800194E0(playerId + 10);
}

void func_8002025C(s16 playerId, u16 arg0, u16 gameMode) {
    func_800201C4(arg0, playerId);
}

void func_80020298(s16 playerId, u16 arg0, u16 gameMode) {
    func_800201C4(1, playerId);
    gGameMode = GAME_MODE_30;
}

void func_800202D0(s16 playerId, u16 arg0, u16 gameMode) {
    D_800B6328[0].unk_04 = D_800B6328[1].unk_04 = arg0;
}

void func_800202F0(s16 playerId, u16 arg0, u16 gameMode) {
    s16 i;

    D_800B6328[1 - playerId].unk_06 = 1;
    D_800B6328[playerId].unk_06 = 0;
    D_800B6328[playerId].unk_02 = 0;
    D_800B6328[1 - playerId].unk_02 = 1;
    D_800801F1 = 1;

    for (i = 0; i < 11; i++) {
        D_800B6350[0][i] = D_800B6350[1][i] = 0;
    }

    D_8005BFC0 |= 1;
    func_800194E0(playerId + 10);
}

void func_800203A8(s16 playerId, u16 arg0, u16 gameMode) {
    D_800B6328[1 - playerId].unk_00 = arg0;
    D_800B6328[1 - playerId].unk_02 = 1;
    gGameMode = gameMode;
}

s16 func_800203F0(u16 *arg0, u16 *arg1) {
    s16 v1 = 0;

    while (*arg0 == *arg1) {
        if (*arg1 == 0xFFFF || *arg0 == 0xFFFF) {
            break;
        }
        arg0++;
        arg1++;
        v1++;
    }

    return v1;
}

void func_80020438(UnkRho *arg0, s16 playerId) {
    UnkSigma *v0 = arg0->unk_00;

    arg0->unk_04++;
    if (v0->unk_00[arg0->unk_04] == 0xFFFF) {
        sound_play(2, 9);
        v0->unk_04(playerId, v0->unk_08, v0->unk_0A);
        arg0->unk_00 = NULL;
        arg0->unk_04 = 0;
    }
}

void func_800204C0(UnkRho *arg0, s16 playerId) {
    u16 v0;
    UnkSigma *s1;
    UnkSigma *ptr;
    s32 unused;

    if (!gPlayerInput[playerId].unk_08) {
        return;
    }
    v0 = gPlayerInput[playerId].unk_06;
    if (!v0) {
        return;
    }

    if (v0 & (INP_UP | INP_DOWN | INP_LEFT | INP_RIGHT | INP_CRIGHT)) {
        if (arg0->buttons == v0) {
            gPlayerInput[playerId].unk_08 = FALSE;
            return;
        }
        arg0->buttons = v0;
    }

    gPlayerInput[playerId].unk_08 = FALSE;
    s1 = arg0->unk_00;
    if (s1 != NULL) {
        if (v0 == s1->unk_00[arg0->unk_04]) {
            func_80020438(arg0, playerId);
            return;
        }

        for (ptr = s1 + 1; ptr->unk_00 != NULL; ptr++) {
            if (func_800203F0(s1->unk_00, ptr->unk_00) == arg0->unk_04 && v0 == ptr->unk_00[arg0->unk_04]) {
                arg0->unk_00 = ptr;
                func_80020438(arg0, playerId);
                return;
            }
        }
        gPlayerInput[playerId].unk_08 = TRUE;
        if (0) {} // required to match

        arg0->unk_00 = NULL;
        arg0->unk_04 = FALSE;
        arg0->buttons = 0;
        return;
    }

    for (s1 = D_8004A288; s1->unk_00 != NULL; s1++) {
        if (s1->unk_00[0] == v0) {
            arg0->unk_00 = s1;
            arg0->unk_04 = 1;
            return;
        }
    }
}

void func_80020670(Object *obj) {
    func_800204C0((UnkRho *) &obj->unk_090[0], 0);
    func_800204C0((UnkRho *) &obj->unk_090[8], 1);
}
