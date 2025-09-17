#include "common.h"

const char D_80055120[] = "practice.sp2";
const char D_80055130[] = "practice.sp2";
const char D_80055140[] = "practice.sp2";
const char D_80055150[] = "practice.sp2";
const char D_80055160[] = "practice.sp2";
const char D_80055170[] = "practice.sp2";
const char D_80055180[] = "practice.sp2";
const char D_80055190[] = "practice.sp2";
const char D_800551A0[] = "practice.sp2";

extern s16 **D_80052F30[];

extern s16 D_8013C408;
extern s16 D_8013C410[];
extern s16 D_8013C428;
extern s16 D_8013C42A;
extern s16 D_8013C42C;
extern s32 D_8013C430;
extern s32 D_8013C434;
extern s32 D_8013C43C;
extern s32 D_8013C440;
extern s32 D_8013C444;

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800321C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032434.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800327D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032CEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032E00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032EDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_8003307C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80033124.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800331D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80033250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800332D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800333F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_8003355C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800335BC.s")
void func_800335BC(void);

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_8003360C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800336E4.s")
void func_800336E4(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80033774.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800337C8.s")
void func_800337C8(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80033868.s")
void func_80033868(void);

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800338D0.s")

void func_80033958(void) {
    s16 v1;
    Player *s2;
    s16 *s0;
    s16 s1;
    PlayerSub8 *new_var;
    s16 **q;
    s16 *tmp2;
    s16 t3;

    s2 = D_800AA488 + gPracticingPlayer;
    v1 = D_800AA488[gPracticingPlayer].characterId;
    if (v1 >= CHARACTER_5) {
        v1--;
    }

    q = D_80052F30[v1];
    s0 = q[D_8013C43C];

    func_800335BC();
    D_8013C428 = D_8013C42A = 0;

    s1 = *s0;
    while (s1 != 0) {
        t3 = s2->unk_38[s1];
        tmp2 = s2->unk_34;
        new_var = &s2->unk_2C[tmp2[t3]];
        D_8013C410[D_8013C428++] = tmp2[t3];
        func_800336E4(new_var->unk_02);
        s0++;
        s1 = *s0;
    }

    D_8013C408 = 0;
}

void func_80033AB0(void) {
    s16 v1;
    Player *s2;
    s16 *s0;
    s16 s1;
    PlayerSub8 *new_var;
    s16 **q;
    s16 *tmp2;
    s16 t3;

    s2 = D_800AA488 + 1 - gPracticingPlayer;
    v1 = D_800AA488[1 - gPracticingPlayer].characterId;
    if (v1 >= CHARACTER_5) {
        v1--;
    }

    q = D_80052F30[v1];
    s0 = q[D_8013C440];

    func_800335BC();
    D_8013C428 = D_8013C42A = 0;

    s1 = *s0;
    while (s1 != 0) {
        t3 = s2->unk_38[s1];
        tmp2 = s2->unk_34;
        new_var = &s2->unk_2C[tmp2[t3]];
        D_8013C410[D_8013C428++] = tmp2[t3];
        func_800336E4(new_var->unk_02);
        s0++;
        s1 = *s0;
    }

    D_8013C408 = 0;
}

void func_80033C38(void) {
    u16 a2;
    PlayerSub8 *new_var;

    if (--D_8013C42C <= 0) {
        a2 = (D_8013C430 == 18) ? gPracticingPlayer : 1 - gPracticingPlayer;

        if (D_8013C42A < D_8013C428) {
            new_var = &D_800AA488[a2].unk_2C[D_8013C410[D_8013C42A]];
            gPlayerInput[a2].buttons = new_var->unk_02;
            gPlayerInput[a2].unk_08 = TRUE;
        } else {
            D_8013C444 = FALSE;
            gPlayerInput[gPracticingPlayer].unk_0A = TRUE;
            D_8005BFC0 &= ~4;
        }
    }
}

void func_80033D64(void) {
    u16 a2;
    Player *player;

    if (D_8013C430 == 18) {
        a2 = gPracticingPlayer;
    } else {
        a2 = 1 - gPracticingPlayer;
    }
    player = &D_800AA488[a2];

    if (D_8013C444 != 0) {
        func_80033C38();
    }

    if (player->unk_74 == D_8013C410[D_8013C42A]) {
        func_800337C8(player->unk_A0->unk_02);
        D_8013C42A++;
        if (D_8013C444) {
            func_80033C38();
        }
        D_8013C42C = 15;
    } else if (D_8013C42A != 0 && player->unk_74 != D_8013C410[D_8013C42A - 1]) {
        func_80033868();
        D_8013C444 = FALSE;
    }
}

void func_80033E94(Object *obj) {
    if (D_8013C430 != 18 && D_8013C434 != 66) {
        obj->flags |= 4;
        return;
    }

    if (--obj->vars[0] < 0 && D_8013C444 == 0) {
        obj->flags ^= 4;
        obj->vars[0] = 12;
    } else if (D_8013C444 != 0) {
        obj->flags &= ~4;
    }

    if (gPlayerInput[gPracticingPlayer].buttons == INP_A) {
        D_8013C444 = 1;
        D_8013C42C = 0;
        D_8005BFC0 |= 4;
        if (D_8013C430 == 18) {
            gPlayerInput[gPracticingPlayer].unk_0A = FALSE;
        } else {
            gPlayerInput[1 - gPracticingPlayer].unk_0A = FALSE;
        }
    }
}

void func_80033FB0(Object *obj) {
    s32 q;
    if (D_8013C430 != 18 || (obj->flags & 4)) {
        func_80015724(obj);
        return;
    }

    if (gPlayerInput[gPracticingPlayer].unk_09) {
        if (obj->vars[2] != 0x29) {
            if (obj->vars[2] == 0x31) {
                obj->spriteId = (q = (obj->spriteId & 1) == 0) + 0x29;
            }
        } else {
            obj->spriteId = (q = (obj->spriteId & 1) == 0) + 0x31;
        }
    } else {
        obj->spriteId = (q = (obj->spriteId & 1) == 0) + obj->vars[2];
    }

    func_80015724(obj);
}
