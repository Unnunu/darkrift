#include "common.h"

void func_8000E930(Object *obj) {
    if (obj->spriteId < obj->modInst->numAnimFrames) {
        D_8008012C |= 0x10;
        obj->spriteId++;
        if (obj->spriteId > 12) {
            if (obj->unk_088.a > obj->vars[0]) {
                obj->unk_088.a -= obj->vars[0];
            } else {
                obj->unk_088.a = 0;
            }
        }
    } else {
        obj->flags |= 0x10;
        D_8008012C &= ~0x10;
        obj->currentTask->flags |= 0x80;
    }
}

void func_8000E9D8(Object *obj) {
    if (obj->spriteId < obj->modInst->numAnimFrames) {
        D_8008012C |= 0x10;
        obj->spriteId++;
        if (obj->spriteId > 2) {
            if (obj->unk_088.a > obj->vars[0]) {
                obj->unk_088.a -= obj->vars[0];
            } else {
                obj->unk_088.a = 0;
            }
        }
    } else {
        D_8008012C &= ~0x10;
        obj->flags |= 0x10;
        obj->currentTask->flags |= 0x80;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000EA80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000EC70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000ED50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000F074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000F3FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000F494.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000FB30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000FE9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010B00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010B14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010BE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010C18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80011258.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_800114BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_800114DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_800115A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80012150.s")
