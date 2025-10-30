#include "common.h"

Object *D_80081460;
char D_80081464[4];
Object *D_80081468[10];
s16 D_80081490;
s32 D_80081494;
s16 D_80081498[11];
s16 D_800814B0[11];
Vec4i D_800814C8;

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017E10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017F00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017F60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80017FF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018088.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800181C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800182E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800183FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800184A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800186AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018820.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018974.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_800189CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018AD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_80018D64.s")

void func_80018DD4(s16 number, s16 posX, s16 posY) {
    UIElement spC = { 0, NULL, 0, 0x1000, "options2.sp2" };
    s16 hundreds;
    s16 tens;
    s16 ones;
    Object *v1;

    if (number > 999) {
        number = 999;
    }

    hundreds = number / 100;
    number -= hundreds * 100;
    tens = number / 10;
    ones = number - tens * 10;

    if (hundreds != 0) {
        v1 = D_80081468[D_80081490++];
        v1->pos.x = posX;
        v1->pos.y = posY;
        v1->frameIndex = 21 + hundreds;
        v1->flags &= ~OBJ_FLAG_HIDDEN;
    }

    posX += 7;

    if (hundreds != 0 || hundreds == 0 && tens != 0) {
        v1 = D_80081468[D_80081490++];
        v1->pos.x = posX;
        v1->pos.y = posY;
        v1->frameIndex = 21 + tens;
        v1->flags &= ~OBJ_FLAG_HIDDEN;
    }

    posX += 7;

    v1 = D_80081468[D_80081490++];
    v1->pos.x = posX;
    v1->pos.y = posY;
    v1->frameIndex = 21 + ones;
    v1->flags &= ~OBJ_FLAG_HIDDEN;
}

#pragma GLOBAL_ASM("asm/nonmatchings/18A10/func_8001905C.s")

void func_80019278(void) {
    UIElement sp3C = { 0, NULL, 0, 0x1000, "options2.sp2" };
    s16 i, j, k;
    s16 p1;
    s16 p2;
    s16 a0;

    D_800814C8.x = 75;
    D_800814C8.y = 71;

    for (i = 0; i < 10; i++) {
        D_80081468[i] = create_ui_element(&D_800814C8, &sp3C, CONTEXT_2000);
        D_80081468[i]->flags |= OBJ_FLAG_HIDDEN;
    }

    for (i = 0; i < 11; i++) {
        D_80081498[i] = i;
    }

    for (j = 0; j < 11; j++) {
        p1 = D_800B6368[j][0];
        p2 = D_800B6368[j][1];
        a0 = p1 + p2;
        if (a0 != 0) {
            D_800814B0[j] = (p1 * 200 + a0) / (2 * a0);
        } else {
            D_800814B0[j] = 0;
        }
    }

    for (j = 1; j < 11; j++) {
        for (i = 0; i < j; i++) {
            if (D_800814B0[D_80081498[i]] < D_800814B0[j]) {
                for (k = j - 1; k >= i; k--) {
                    D_80081498[k + 1] = D_80081498[k];
                }
                D_80081498[i] = j;
                break;
            }
        }
    }
}
