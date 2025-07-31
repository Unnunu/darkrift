#include "common.h"

extern Quad D_80049BA8[];

extern s16 D_80080230;
extern s16 D_80080232;

void func_800194E0(u16 arg0) {
    D_80080232 = D_80080230;
    D_80080230 = arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_80019500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001954C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_800198D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_80019940.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_800199E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_80019A9C.s")

void func_80019BD0(Object *obj) {
    if (D_80080230 == 30 && ((gPlayerInput[0].unk_00 & INP_START) || (gPlayerInput[1].unk_00 & INP_START))) {
        D_8005BFC0 |= 1;
        gGameMode = GAME_MODE_0;
        obj->flags |= 0x10;
        obj->currentTask->flags |= 0x80;
    }
}

void func_80019C48(Object *obj) {
    obj->unk_090[0]++;
    if (obj->unk_090[0] > 180) {
        D_8005BEFC = 0;
        D_8005BFC0 |= 1;
        gGameMode = GAME_MODE_32;
        obj->flags |= 0x10;
        obj->currentTask->flags |= 0x80;
    }
    func_80019BD0(obj);
}

void func_80019CC0(Object *obj) {
    if (D_8005BEFC - 8 < D_80080118) {
        obj->fn_update = func_80019C48;
    } else {
        D_8005BEFC -= 8;
    }

    func_80002178(D_8005BEFC, &D_80049BA8[D_8005BFCE]);
}

void func_80019D2C(Object *obj) {
    if (D_8005BEFC + 8 < 255) {
        D_8005BEFC += 8;
    } else {
        mem_free(D_80049AE0);
        D_80049AE0 = NULL;
        load_background("kronos", 0, 60, 0, 180, 1, CONTEXT_2000);
        obj->fn_update = func_80019CC0;
    }

    func_80002178(D_8005BEFC, &D_80049BA8[D_8005BFCE]);
}

void func_80019DE4(Object *obj) {
    obj->unk_090[0]++;
    if (obj->unk_090[0] > 180) {
        obj->unk_090[0] = 0;
        obj->fn_update = func_80019D2C;
    }
    func_80019BD0(obj);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_80019E28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_80019F08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_80019F40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A130.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A158.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A294.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A2F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A334.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A3EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A4FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A5D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A63C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A7DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1A0E0/func_8001A98C.s")
