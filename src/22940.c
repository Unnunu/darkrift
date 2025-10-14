#include "common.h"

void func_80021D40(Object *obj) {
    if (++obj->spriteId >= obj->modInst->numAnimFrames) {
        obj->currentTask->flags |= 0x80;
        obj->flags |= 0x10;
    }

    if (obj->unk_088.a >= obj->vars[0]) {
        obj->unk_088.a -= obj->vars[0];
    } else {
        obj->unk_088.a = 0;
        obj->currentTask->flags |= 0x80;
        obj->flags |= 0x10;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80021DC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80021E34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80021EA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80021EA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80021EE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80021FEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022218.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022428.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_8002250C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022694.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_800226E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022B44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022CD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/22940/func_80022EC0.s")
