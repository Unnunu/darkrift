#include "common.h"

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

extern u16 D_8013C494;
extern Object *D_80081660[2];
extern s16 D_80080230;
extern u32 D_80081668;
extern u8 D_8004A428;
extern AssetSP2Sub3 *D_8013C234;
extern AssetSP2Sub3 *D_8013C238;

u8 D_80049DF0 = 0;
u8 D_80049DF4 = 0;

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001DE10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001DFE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E188.s")
u8 func_8001E188(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E378.s")
void func_8001E378(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E540.s")
void func_8001E540(Object *, Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E5D8.s")
s16 func_8001E5D8(s16 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E624.s")
void func_8001E624(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001E834.s")
void func_8001E834(Object *, Object *, Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001EA24.s")
void func_8001EA24(Object *);

#ifdef NON_MATCHING
void func_8001EB58(Object *obj) {
    s16 s1;
    UIElement sp100 = { 11, NULL, 0, 0x1000, "bars.sp2" };
    UIElement spEC = { 39, func_8001EA24, 0, 0x1000, "bars.sp2" };
    UIElement spD8 = { 28, NULL, 0, 0x1000, "bars.sp2" };
    Vec4i spB8[] = { { 78, 220, 0, 0 }, { 248, 220, 0, 0 } };
    Vec4i sp98[] = { { 77, 220, 0, 0 }, { 248, 220, 0, 0 } };
    Vec4i sp78[] = { { 39, 216, 0, 0 }, { 289, 216, 0, 0 } };
    Vec4i sp58[] = { { 60, 203, 0, 0 }, { 229, 203, 0, 0 } };
    Object *s2;
    Object *s2a;
    Object *s2b;
    Object *s3;
    Object *v0;
    s16 v03;

    s1 = obj->vars[0];

    s3 = create_ui_element(&spB8[s1], &sp100, CONTEXT_EEFF);
    v0 = create_ui_element(&sp78[s1], &spEC, CONTEXT_EEFF);
    v0->vars[0] = s1;
    v0->vars[3] = s3;
    s3 = create_ui_element(&sp98[s1], &sp100, CONTEXT_EEFF);
    s3->unk_084 = 15 - s1;
    v0->vars[4] = s3;

    v03 = func_8001E5D8(s1);
    if (s1 == 0) {
        D_8013C234 = s3->sprite_map->sprites[15].unk_04;
        D_8013C234->unk_10 = D_8013C234->unk_10 - D_8013C234->unk_04 + D_8013C234->unk_08 - v03 - 8;
        D_8013C234->unk_04 = D_8013C234->unk_08 - v03 - 8;
        v0->vars[1] = 119;
        v0->pos.x = 119 - v03;
    } else {
        D_8013C238 = s3->sprite_map->sprites[14].unk_04;
        D_8013C238->unk_08 = D_8013C238->unk_04 + v03;
        v0->vars[1] = 0xD1;
        v0->pos.x = 0xD1 + v03;
    }

    s2 = create_ui_element(&sp58[s1], &spD8, CONTEXT_EEFF);
    sp58[s1].x += 10;
    s2a = create_ui_element(&sp58[s1], &spD8, CONTEXT_EEFF);
    sp58[s1].x += 10;
    s2b = create_ui_element(&sp58[s1], &spD8, CONTEXT_EEFF);
    s2b->vars[0] = s1;

    func_8001E834(s2b, s2a, s2);

    v0->vars[5] = s2b;
    v0->vars[6] = s2a;
    v0->vars[7] = s2;

    obj->vars[1] = 0;
    obj->vars[9] = s2b;
    obj->currentTask->func = func_8001E624;
    obj->currentTask->counter = 20;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/1EA10/func_8001EB58.s")
void func_8001EB58(Object *obj);
UIElement D_80049DF8 = { 11, NULL, 0, 0x1000, "bars.sp2" };
UIElement D_80049E0C = { 39, func_8001EA24, 0, 0x1000, "bars.sp2" };
UIElement D_80049E20 = { 28, NULL, 0, 0x1000, "bars.sp2" };
Vec4i D_80049E34[] = { { 0x4E, 0xDC, 0, 0 }, { 0xF8, 0xDC, 0, 0 } };
Vec4i D_80049E54[] = { { 0x4D, 0xDC, 0, 0 }, { 0xF8, 0xDC, 0, 0 } };
Vec4i D_80049E74[] = { { 0x27, 0xD8, 0, 0 }, { 0x121, 0xD8, 0, 0 } };
Vec4i D_80049E94[] = { { 0x3C, 0xCB, 0, 0 }, { 0xE5, 0xCB, 0, 0 } };
#endif

void func_8001EF28(Object *obj) {
    Object *unkObj;
    s16 v1;
    s16 charId;

    if (!(D_8005BFC0 & 0x1000)) {
        return;
    }

    charId = obj->vars[0];
    unkObj = obj->vars[5];

    if (D_800B6328[1 - charId].unk_02 == 0 && unkObj->vars[8] == 0) {
        return;
    }

    if (obj->vars[2]-- > 0) {
        return;
    }

    obj->vars[2] = 15;
    if (obj->unk_084 >= 5) {
        v1 = obj->unk_084 + 1;
    } else {
        v1 = obj->unk_084;
    }

    if (obj->vars[6] == 9 || obj->vars[6] == 1) {
        v1 = obj->vars[6];
        obj->unk_084 = v1 - (v1 == SONORK);
    }

    if (v1 == obj->vars[6]) {
        sound_play(2, D_8004A428 != 0 ? 0 : charId + 4);
        func_8001E540(obj, unkObj);
        unkObj = obj->vars[4];
        unkObj->vars[7] = 20;
        obj->currentTask->flags |= 0x80;
        return;
    }

    sound_play(2, 6 + charId);

    if (func_8002C310(v1 - obj->vars[6]) <= 5) {
        if (v1 < obj->vars[6]) {
            v1++;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1++;
            }
        } else {
            v1--;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1--;
            }
        }
    } else {
        if (v1 < obj->vars[6]) {
            v1--;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1--;
            }
        } else {
            v1++;
            if (v1 == CHARACTER_5 || v1 == SONORK || v1 == DEMITRON) {
                v1++;
            }
        }
    }

    if (v1 < AARON) {
        v1 = ZENMURON;
    } else if (v1 > ZENMURON) {
        v1 = AARON;
    }

    if (v1 >= CHARACTER_5) {
        obj->unk_084 = v1 - 1;
    } else {
        obj->unk_084 = v1;
    }
}

void func_8001F1D4(Object *obj) {
    s16 a1;
    s16 v0;
    s16 v1;
    s32 tmp2;
    s16 a3;
    s16 tmp;

    a3 = obj->vars[0];
    a1 = obj->vars[1];

    if (D_80080230 == 40) {
        Object *unkObj = obj->vars[5];
        if (a3 != D_8013C494) {
            if (unkObj->vars[8] == 0) {
                obj->vars[1] = 0x800;
                obj->vars[2] = 60;
                return;
            }
        }
        tmp2 = D_8013C494;
        obj->vars[1] = v1 = gPlayerInput[tmp2].unk_00;
    } else {
        obj->vars[1] = v1 = gPlayerInput[a3].unk_00;
    }

    tmp = obj->vars[2]--;
    if (tmp <= 0 || v1 != a1) {
        obj->vars[2] = 15;
        if (v1 & INP_START) {
            Object *unkObj;
            sound_play(2, D_8004A428 != 0 ? 0 : a3 + 4);
            unkObj = obj->vars[4];
            unkObj->vars[7] = 20;

            if (D_80080230 == 20) {
                func_8001EB58(obj);
            } else {
                func_8001E540(obj, obj->vars[5]);
                if (D_80080230 == 10 || D_80080230 == 11) {
                    D_80081660[1 - a3]->vars[6] = func_8001E188((u8) (1 - a3));
                }
                obj->currentTask->flags |= 0x80;
            }
        } else if (v1 & (INP_LEFT | INP_RIGHT)) {
            sound_play(2, 6 + a3);

            v0 = obj->unk_084;
            if (v1 & INP_LEFT) {
                v0--;
            } else {
                v0++;
            }

            if (D_80049DF0 == 0 && v0 == 8 || D_80049DF4 == 0 && v0 == 1) {
                if (v1 & INP_LEFT) {
                    v0--;
                } else {
                    v0++;
                }
            }

            if (v0 < 0) {
                v0 = 9;
            } else if (v0 > 9) {
                v0 = 0;
            }

            obj->unk_084 = v0;
        }
    }
}

void func_8001F450(Object *obj) {
    if (obj->vars[7] != 0) {
        if (obj->vars[8]-- == 0) {
            obj->unk_084 = obj->vars[0] * 4 - obj->unk_084 + 171;
            obj->vars[8] = -254 - (obj->vars[0] * 2 - obj->unk_084) * 3;
        }

        if (--obj->vars[7] == 0) {
            obj->unk_084 = obj->vars[0] * 2 + 86;
            obj->currentTask->flags |= 0x80;
        }
    }
}

void func_8001F4E0(Object *obj) {
    if (obj->vars[8] < 2) {
        return;
    }

    if (obj->vars[8] == 2) {
        obj->vars[8] = 3;
        obj->currentTask->counter = 10;
        D_80081660[0]->flags |= 0x4000000;
        D_80081660[1]->flags |= 0x4000000;
        return;
    }

    if (obj->vars[8] == 3) {
        obj->vars[8] = 4;
        D_80081660[0]->flags |= 0x4000000;
        D_80081660[1]->flags |= 0x4000000;
        obj->flags &= ~4;
        obj->currentTask->counter = 20;
        return;
    }

    D_800B6328[0].unk_06 = D_800B6328[1].unk_06 = 0;
    D_800B6328[0].characterId = obj->vars[9];
    D_800B6328[1].characterId = obj->vars[10];
    D_800B6328[0].unk_08 = D_800B6328[1].unk_08 = 0;
    D_800B6328[0].unk_0C &= ~3;
    D_800B6328[1].unk_0C &= ~3;
    if (0) {} // required to match
    D_8005BFC0 |= 1;

    if (D_80080230 == 10 || D_80080230 == 11) {
        gGameMode = D_800B6328[D_80081668].characterId + GAME_MODE_6;
        if (D_800B6328[0].unk_0A + D_800B6328[1].unk_0A == 0) {

            gGameMode = D_800B6328[1 - D_80081668].characterId + GAME_MODE_18;
            D_800B6328[1 - D_80081668].unk_06 = 1;
        } else {
            D_800B6328[D_80081668].unk_06 = 1;
        }
        if (D_800B6328[D_80081668].characterId == DEMITRON) {
            gGameMode = GAME_MODE_30;
        }
    } else {
        gGameMode = D_800B6328[obj->vars[11]].characterId + GAME_MODE_6;
        D_800B6328[obj->vars[11]].unk_06++;
    }

    obj->currentTask->flags |= 0x80;
}

void func_8001F6E8(Object *obj) {
    s16 playerId;
    Object *unkObj;

    if (obj->vars[2]-- < 0) {
        obj->vars[2] = 15;
        obj->unk_084 = obj->vars[1] - obj->unk_084;
    }

    playerId = obj->vars[0];
    unkObj = D_80081660[playerId]->vars[4];
    if (unkObj->vars[7]) {
        obj->flags |= 0x10;
    }
}

void func_8001F748(Object *obj) {
    if (obj->vars[2]-- < 0) {
        obj->vars[2] = 15;
        obj->unk_084 = obj->vars[1] - obj->unk_084;
    }

    if (gPlayerInput[obj->vars[0]].unk_00 & INP_START) {
        obj->unk_084 = 26 - 2 * obj->vars[0];
        obj->vars[1] = obj->unk_084 * 2 + 1;
        obj->pos.x = 245 - obj->vars[0] * 167;
        obj->vars[0] = 1 - obj->vars[0];
        obj->currentTask->func = func_8001F6E8;
    }
}

void run_player_selection_mode(void) {
    Object *sp1CC[2];
    Object *sp1C4;
    Object *obj;
    s16 player1;
    Object *sp1B8;
    UIElement portrait_p1 = { 0, func_8001F1D4, 0, 0x1000, "grpp1.sp2" };
    UIElement portrait_p2 = { 0, func_8001F1D4, 0, 0x1000, "grpp2.sp2" };
    UIElement sp17C = { 85, func_8001F450, 0, 0x1000, "options2.sp2" };
    UIElement sp168 = { 87, func_8001F450, 0, 0x1000, "options2.sp2" };
    UIElement sp154 = { 26, func_8001F4E0, 0, 0x1000, "bars.sp2" };
    UIElement sp140 = { 0, func_8001E378, 0, 0x1000, "bars.sp2" };
    UIElement sp12C = { 6, NULL, 0, 0x1000, "bars.sp2" };
    UIElement sp118 = { 83, func_8001F6E8, 0, 0x1000, "options2.sp2" };
    UIElement sp104 = { 20, func_8001F748, 0, 0x1000, "practice.sp2" };
    UIElement spF0 = { 22, func_8001F748, 0, 0x1000, "practice.sp2" };
    Vec4i portrait_p1_pos = { 84, 129, 0, 0 };
    Vec4i portrait_p2_pos = { 252, 129, 0, 0 };
    Vec4i spC0 = { 56, 60, 0, 0 };
    Vec4i spB0 = { 224, 60, 0, 0 };
    Vec4i spA0 = { 162, 130, 0, 0 };
    Vec4i sp90 = { 171, 75, 0, 0 };
    Vec4i sp80 = { 158, 75, 0, 0 };
    Vec4i sp70 = { 82, 217, 0, 0 };
    Vec4i sp60 = { 251, 217, 0, 0 };
    Vec4i sp50 = { 78, 217, 0, 0 };
    Vec4i sp40 = { 245, 217, 0, 0 };
    s16 char_p1, char_p2;
    s32 unused;

    char_p1 = D_800B6328[0].characterId;
    char_p2 = D_800B6328[1].characterId;

    if (char_p1 == DEMITRON && D_80049DF4 == 0) {
        char_p1 = GORE;
    }
    if (char_p2 == DEMITRON && D_80049DF4 == 0) {
        char_p2 = GORE;
    }
    if (char_p1 == SONORK && D_80049DF0 == 0) {
        char_p1 = AARON;
    }
    if (char_p2 == SONORK && D_80049DF0 == 0) {
        char_p2 = AARON;
    }

    if (char_p1 >= CHARACTER_5) {
        char_p1--;
    }
    if (char_p2 >= CHARACTER_5) {
        char_p2--;
    }

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;

    asset_open_folder("/plyrsel/plyrsel", CONTEXT_EEFF);
    asset_open_folder("/plyrsel/music", CONTEXT_EEFF);

    D_8005BFC0 |= 0x800;

    switch (D_80080230) {
        case 10:
            obj = create_ui_element(&sp70, &sp118, CONTEXT_EEFF);
            obj->vars[0] = 0;
            obj->vars[1] = 0xA7;
            asset_open_folder("/plyrsel/select", CONTEXT_EEFF);
            break;
        case 11:
            obj = create_ui_element(&sp60, &sp118, CONTEXT_EEFF);
            obj->vars[0] = 1;
            obj->vars[1] = 0xA7;
            asset_open_folder("/plyrsel/select", CONTEXT_EEFF);
            break;
        case 20:
        case 30:
        case 50:
            obj = create_ui_element(&sp70, &sp118, CONTEXT_EEFF);
            obj->vars[0] = 0;
            obj->vars[1] = 0xA7;
            obj = create_ui_element(&sp60, &sp118, CONTEXT_EEFF);
            obj->vars[0] = 1;
            obj->vars[1] = 0xA7;
            asset_open_folder("/plyrsel/select2", CONTEXT_EEFF);
            break;
        case 40:
            if (D_8013C494 == 0) {
                obj = create_ui_element(&sp50, &sp104, CONTEXT_EEFF);
                obj->vars[0] = 0;
                obj->vars[1] = 0x29;
            } else {
                obj = create_ui_element(&sp40, &spF0, CONTEXT_EEFF);
                obj->vars[0] = 1;
                obj->vars[1] = 0x2D;
            }
            asset_open_folder("/plyrsel/select3", CONTEXT_EEFF);
            break;
    }

    load_background("select", 0, 8, 0, 0, 1, CONTEXT_EEFF);

    D_80081660[0] = create_ui_element(&portrait_p1_pos, &portrait_p1, CONTEXT_EEFF);
    D_80081660[0]->vars[0] = 0;
    D_80081660[0]->unk_084 = char_p1;
    D_80081660[0]->currentTask->counter = 20;

    D_80081660[1] = create_ui_element(&portrait_p2_pos, &portrait_p2, CONTEXT_EEFF);
    D_80081660[1]->vars[0] = 1;
    D_80081660[1]->unk_084 = char_p2;
    D_80081660[1]->currentTask->counter = 20;

    sp1CC[0] = create_ui_element(&spC0, &sp17C, CONTEXT_EEFF);
    sp1CC[0]->vars[0] = 0;

    sp1CC[1] = create_ui_element(&spB0, &sp168, CONTEXT_EEFF);
    sp1CC[1]->vars[0] = 1;

    sp1C4 = create_ui_element(&spA0, &sp154, CONTEXT_EEFF);
    sp1C4->flags |= 4;
    sp1C4->vars[11] = -1;
    sp1C4->flags |= 0x4000000;

    sp1B8 = create_ui_element(&sp80, &sp12C, CONTEXT_EEFF);

    obj = create_ui_element(&sp90, &sp140, CONTEXT_EEFF);
    obj->vars[2] = 60;
    obj->vars[1] = sp1B8;
    obj->vars[5] = sp1C4;

    D_80081660[0]->vars[4] = sp1CC[0];
    D_80081660[0]->vars[5] = sp1C4;
    D_80081660[1]->vars[4] = sp1CC[1];
    D_80081660[1]->vars[5] = sp1C4;

    switch (D_80080230) {
        case 10:
        case 11:
            player1 = (D_80080230 == 11);
            D_80081660[1 - player1]->currentTask->func = func_8001EF28;
            D_80081660[1 - player1]->currentTask->counter = 0;
            D_80081660[1 - player1]->currentTask->flags = 1;

            if (D_800B6328[player1].unk_08 != 0) {
                D_80081660[1 - player1]->vars[6] = func_8001E188((u8) (1 - (u32) player1));
                D_80081660[player1]->currentTask->flags |= 0x80;
                sp1CC[player1]->vars[7] = 20;
                sp1C4->vars[8] = 1;
                sp1C4->vars[9 + player1] = D_800B6328[player1].characterId;
            }
            break;
        case 30:
            D_80081660[0]->currentTask->func = func_8001EF28;
            D_80081660[0]->currentTask->counter = 0;
            D_80081660[0]->currentTask->flags = 1;
            D_80081660[0]->vars[6] = func_8001E188(0);

            D_80081660[1]->currentTask->func = func_8001EF28;
            D_80081660[1]->currentTask->counter = 0;
            D_80081660[1]->currentTask->flags = 1;
            D_80081660[1]->vars[6] = func_8001E188(1);
            break;
        case 20:
        case 40:
        case 50:
            break;
    }

    func_80001D88();
    func_8002630C(CONTEXT_EEFF);

    // TODO .data start
}

void func_800201A4(s16 playerId, u16 arg1, u16 arg2) {
    D_80049DF0 = arg1;
    D_80049DF4 = arg2;
}

void func_800201C4(s16 charId, s16 playerId) {
    D_8005BFC0 |= 1;
    gGameMode = GAME_MODE_34;

    D_800B6328[playerId].characterId = charId;
    D_800B6328[playerId].unk_02 = 0;
    D_800B6328[playerId].unk_06 = 0;

    D_800B6328[1 - playerId].characterId = DEMITRON;
    D_800B6328[1 - playerId].unk_02 = 1;
    D_800B6328[1 - playerId].unk_06 = 1;

    func_800194E0(playerId + 10);
}

void cheat_character_ending(s16 playerId, u16 charId, u16 arg2) {
    func_800201C4(charId, playerId);
}

void func_80020298(s16 playerId, u16 arg1, u16 arg2) {
    func_800201C4(DEMITRON, playerId);
    gGameMode = GAME_MODE_30;
}

void func_800202D0(s16 playerId, u16 arg1, u16 arg2) {
    D_800B6328[0].unk_04 = D_800B6328[1].unk_04 = arg1;
}

void func_800202F0(s16 playerId, u16 arg1, u16 arg2) {
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

void func_800203A8(s16 playerId, u16 charId, u16 gameMode) {
    D_800B6328[1 - playerId].characterId = charId;
    D_800B6328[1 - playerId].unk_02 = 1;
    gGameMode = gameMode;
}

u16 cheat_code_play_as_sonork[] = { INP_L, INP_R, INP_CUP, INP_CDOWN, INP_CLEFT, INP_CRIGHT, -1 };
u16 cheat_code_play_as_sonork_or_demitron[] = { INP_A, INP_B, INP_R, INP_L, INP_CDOWN, INP_CUP, -1 };

u16 cheat_code_ending_aaron[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CLEFT, -1 };
u16 cheat_code_ending_demonica[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CUP, -1 };
u16 cheat_code_ending_eve[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CRIGHT, -1 };
u16 cheat_code_ending_gore[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_CDOWN, -1 };
u16 cheat_code_ending_morphix[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_B, -1 };
u16 cheat_code_ending_niiki[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_R, INP_R, INP_A, -1 };
u16 cheat_code_ending_scarlet[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CLEFT, -1 };
u16 cheat_code_ending_sonork[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CUP, -1 };
u16 cheat_code_ending_zenmuron[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CRIGHT, -1 };
u16 cheat_code_ending_demitron[] = { INP_UP, INP_CLEFT, INP_R, INP_RIGHT, INP_DOWN, INP_L, INP_L, INP_CDOWN, -1 };

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

UnkSigma D_8004A288[] = { { D_8004A114, func_80020298, 0, 0 },
                          { cheat_code_play_as_sonork, func_800201A4, 1, 0 },
                          { cheat_code_play_as_sonork_or_demitron, func_800201A4, 1, 1 },
                          { cheat_code_ending_aaron, cheat_character_ending, 0, 0 },
                          { cheat_code_ending_demonica, cheat_character_ending, 2, 0 },
                          { cheat_code_ending_eve, cheat_character_ending, 3, 0 },
                          { cheat_code_ending_gore, cheat_character_ending, 4, 0 },
                          { cheat_code_ending_morphix, cheat_character_ending, 6, 0 },
                          { cheat_code_ending_niiki, cheat_character_ending, 7, 0 },
                          { cheat_code_ending_scarlet, cheat_character_ending, 8, 0 },
                          { cheat_code_ending_sonork, cheat_character_ending, 9, 0 },
                          { cheat_code_ending_zenmuron, cheat_character_ending, 10, 0 },
                          { cheat_code_ending_demitron, cheat_character_ending, 1, 0 },
                          { D_8004A13C, func_800202D0, 0, 0 },
                          { D_8004A14C, func_800202D0, 1, 0 },
                          { D_8004A15C, func_800202D0, 2, 0 },
                          { D_8004A16C, func_800202D0, 3, 0 },
                          { D_8004A17C, func_800202D0, 4, 0 },
                          { D_8004A18C, func_800202D0, 5, 0 },
                          { D_8004A19C, func_800202D0, 6, 0 },
                          { D_8004A1AC, func_800202D0, 7, 0 },
                          { D_8004A1BC, func_800203A8, AARON, GAME_MODE_6 },
                          { D_8004A1CC, func_800203A8, DEMITRON, GAME_MODE_7 },
                          { D_8004A1E0, func_800203A8, DEMONICA, GAME_MODE_8 },
                          { D_8004A1F4, func_800203A8, EVE, GAME_MODE_9 },
                          { D_8004A208, func_800203A8, GORE, GAME_MODE_10 },
                          { D_8004A21C, func_800203A8, MORPHIX, GAME_MODE_12 },
                          { D_8004A230, func_800203A8, NIIKI, GAME_MODE_13 },
                          { D_8004A244, func_800203A8, SCARLET, GAME_MODE_14 },
                          { D_8004A258, func_800203A8, SONORK, GAME_MODE_15 },
                          { D_8004A270, func_800203A8, ZENMURON, GAME_MODE_16 },
                          { D_8004A128, func_800202F0, 0, 0 },
                          { NULL, NULL, 0, 0 } };

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
    func_800204C0((UnkRho *) &obj->vars[0], 0);
    func_800204C0((UnkRho *) &obj->vars[8], 1);
}
