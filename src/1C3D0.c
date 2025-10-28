#include "common.h"

u8 func_8001B7D0(Player *player, s16 arg1) {
    func_8001BB2C(player);
    player->unk_180 |= 0x8000;
    return func_8000636C(player, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001B810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BB2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BB80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BC7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BD5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001BF40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C02C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C1C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C2B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C404.s")
s32 func_8001C404(Object *, s16 **);

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C48C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001C53C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CB74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CC18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CC8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CD28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CDAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CDE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CE0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001CE18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D070.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D1F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D44C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D660.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D6C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001D9B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DA10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DA90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DB2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1C3D0/func_8001DC68.s")

s32 func_8001DDA4(Object *obj) {
    s16 *sp1C;

    if (func_8001C404(obj, &sp1C) != 0) {
        if (!(*sp1C & 2)) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}

s32 func_8001DDEC(Object *obj) {
    obj->vars[11] = 0;
    obj->vars[9] -= 4;
    return 1;
}
