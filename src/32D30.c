#include "common.h"
#include "task.h"

const char D_80055120[] = "practice.sp2";
const char D_80055130[] = "practice.sp2";
const char D_80055140[] = "practice.sp2";
const char D_80055150[] = "practice.sp2";
const char D_80055160[] = "practice.sp2";
const char D_80055170[] = "practice.sp2";
const char D_80055180[] = "practice.sp2";
const char D_80055190[] = "practice.sp2";
const char D_800551A0[] = "practice.sp2";

typedef struct UnkVec2su {
    u16 x, y;
} UnkVec2su; // size = 0x4

extern UIElement D_80052DAC;
extern UIElement D_80052E38;
extern s16 **D_80052F30[];
extern UnkVec2su D_80052F58[];
extern UnkVec2su D_80052FBC[];
extern UnkVec2su D_80052F7C[];

extern u16 D_8013C3D0;
extern Object *D_8013C3D8[];
extern u16 D_8013C408;
extern u16 D_8013C40A;
extern s16 D_8013C410[];
extern s16 D_8013C428;
extern s16 D_8013C42A;
extern s16 D_8013C42C;
extern s32 D_8013C430;
extern s32 D_8013C434;
extern s32 D_8013C43C;
extern s32 D_8013C440;
extern s32 D_8013C444;
extern u8 D_8013C45E;
extern u8 D_8013C45F;
extern Object *D_8013C460;
extern Object *D_8013C480;
extern Object *D_8013C484;
extern Object *D_8013C488;
extern Object *D_8013C48C;
extern Object *D_8013C490;

void func_80033FB0(Object *obj);
void func_80033E94(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800321C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032434.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_800327D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032CEC.s")
void func_80032CEC(void);

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032E00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/32D30/func_80032EDC.s")

void func_8003307C(Object *obj) {
    s16 v0;

    if (D_8013C430 == 18) {
        v0 = D_800AA488[gPracticingPlayer].characterId;
        if (v0 >= CHARACTER_5) {
            v0--;
        }
        obj->spriteId = v0 + 66;
        obj->flags &= ~4;
    } else {
        obj->flags |= 4;
    }

    func_80032CEC();
}

void func_80033124(Object *obj) {
    s16 v0;

    if (D_8013C434 == 66) {
        v0 = D_800AA488[1 - gPracticingPlayer].characterId;
        if (v0 >= CHARACTER_5) {
            v0--;
        }
        obj->spriteId = v0 + 66;
        obj->flags &= ~4;
    } else {
        obj->flags |= 4;
    }

    func_80032CEC();
}

void func_800331D0(Object *obj) {
    if (D_8013C430 == 18) {
        obj->flags &= ~4;
        obj->spriteId = D_8013C43C + 1;
    } else {
        obj->flags |= 4;
    }

    if (D_8013C45E) {
        obj->spriteId = D_8013C43C + 11;
    }
    func_80032CEC();
}

void func_80033250(Object *obj) {
    if (D_8013C434 == 66) {
        obj->flags &= ~4;
        obj->spriteId = D_8013C440 + 1;
    } else {
        obj->flags |= 4;
    }

    if (D_8013C45F) {
        obj->spriteId = D_8013C440 + 11;
    }
    func_80032CEC();
}

void func_800332D0(Object *obj) {
    Player *player;
    u32 v1;
    s16 a0;
    s16 v0;
    u32 a00;
    s16 a1;
    u32 nv = 100U;
    u32 nv2 = 10;

    player = &D_800AA488[gPracticingPlayer];

    v1 = player->unk_5F4E;
    if (v1 > 99) {
        v1 = 99;
    }
    a0 = v1 / nv2;
    D_8013C484->spriteId = a0;
    D_8013C480->spriteId = v1 - a0 * nv2;

    v1 = player->unk_5F4C;
    if (v1 > 999) {
        v1 = 999;
    }
    v0 = v1 / nv;
    a00 = v1 - v0 * nv;
    a1 = a00 / nv2;
    D_8013C490->spriteId = v0;
    D_8013C48C->spriteId = a1;
    D_8013C488->spriteId = a00 - a1 * nv2;
}

void func_800333F4(void) {
    s32 i;
    Vec4i sp4C = { 32, 186, 0, 0 };
    Vec4i sp3C = { 24, 177, 0, 0 };

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i] = create_ui_element(&sp4C, &D_80052E38, 0xABAB);
        D_8013C3D8[i]->flags |= 4;
        task_clear(D_8013C3D8[i]->taskList);
        D_8013C3D8[i]->taskList = NULL;
        sp4C.x += 20;
        D_8013C3D8[i]->vars[0] = i;
        D_8013C3D8[i]->fn_render = func_80033FB0;
    }

    D_8013C408 = 0;
    sp4C.y -= 20;
    D_8013C460 = create_ui_element(&sp3C, &D_80052DAC, 0xABAB);
    D_8013C460->spriteId = 76;
    D_8013C460->currentTask->func = func_80033E94;
}

void func_8003355C(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i]->flags |= 0x10;
    }
}

void func_800335BC(void) {
    s16 i;

    for (i = 0; i < 12; i++) {
        D_8013C3D8[i]->flags |= 4;
    }

    D_8013C408 = D_8013C40A = 0;
}

void func_8003360C(u16 arg0) {
    Object *v0;
    s16 i;

    if (arg0) {
        if (D_8013C40A > 45) {
            func_800335BC();
        } else {
            D_8013C40A = 0;
        }

        if (D_8013C408 < 12) {
            v0 = D_8013C3D8[D_8013C408++];
        } else {
            for (i = 0; i < 11; i++) {
                D_8013C3D8[i]->spriteId = D_8013C3D8[i + 1]->spriteId;
            }
            v0 = D_8013C3D8[11];
        }

        v0->spriteId = arg0;
        v0->flags &= ~4;
        v0->vars[2] = arg0;
    }
}

void func_800336E4(u16 arg0) {
    if (((arg0 >> 12) & 0xF) != 0) {
        func_8003360C(D_80052FBC[(arg0 >> 12) & 0xF].y);
    }

    if ((arg0 & 0xF) != 0) {
        func_8003360C(D_80052F58[arg0 & 0xF].y);
    }

    if (((arg0 >> 4) & 0xF) != 0) {
        func_8003360C(D_80052F7C[(arg0 >> 4) & 0xF].y);
    }
}

void func_80033774(u16 arg0) {
    Object *a0;

    if (arg0) {
        a0 = D_8013C3D8[D_8013C408++];
        a0->spriteId = arg0 + 1;
        func_80033FB0(a0);
    }
}

void func_800337C8(u16 arg0) {
    if (D_8013C430 != 16) {
        if (((arg0 >> 12) & 0xF) != 0) {
            func_80033774(D_80052FBC[(arg0 >> 12) & 0xF].y);
        }

        if ((arg0 & 0xF) != 0) {
            func_80033774(D_80052F58[arg0 & 0xF].y);
        }

        if (((arg0 >> 4) & 0xF) != 0) {
            func_80033774(D_80052F7C[(arg0 >> 4) & 0xF].y);
        }
    }
}

void func_80033868(void) {
    u32 i;

    if (D_8013C430 != 16) {
        for (i = 0; i < D_8013C408; i++) {
            D_8013C3D8[i]->spriteId = D_8013C3D8[i]->vars[2];
        }
    }

    D_8013C408 = 0;
    D_8013C42A = 0;
}

void func_800338D0(void) {
    u16 a0;

    a0 = gPlayerInput[gPracticingPlayer].raw_buttons;
    a0 &= ~D_8013C3D0;
    D_8013C3D0 = gPlayerInput[gPracticingPlayer].raw_buttons;

    if (!D_8013C3D0) {
        D_8013C40A++;
    }
    if (a0) {
        func_800336E4(a0);
    }
}

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
