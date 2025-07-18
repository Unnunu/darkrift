#include "common.h"

extern Vec3s D_8013C568;
extern Vec3s D_8013C818;
extern s32 D_8013C584;

void func_80038E00(Object *arg0, s32 arg1) {
    GlobalObjC *camera = arg0->unk_0C8;

    camera->unk_A0C = 0;
    arg0->unk_086 = camera->unk_A0E = -1;
    arg0->unk_084 = 0;

    *camera->unk_12C = arg1;

    D_8013C568.x = D_8013C568.z = 0;
    D_8013C568.y = -480;

    arg0->unk_024 = 0;
    arg0->unk_028 = 0;
    arg0->unk_020 = 0;

    arg0->unk_052 = 0x400;

    camera->unk_414 = 0;
    camera->unk_418 = 0;
    camera->unk_41C = 0;

    D_8013C818.x = D_8013C818.y = D_8013C818.z = 0;

    arg0->unk_0C8->unk_A08 = 0x7FFF;
    D_8013C584 = 11000;
}

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80038E8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80038F34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80039118.s")

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_8003950C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_800395D4.s")
