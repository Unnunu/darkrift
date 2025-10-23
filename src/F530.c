#include "common.h"

extern ColorRGBA D_800499A0;
extern ColorRGBA D_800499A4;

extern Vec4s D_80081268;

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

void func_8000EA80(Vec3s *arg0, u8 arg1, Object *arg2, ColorRGBA *arg3) {
    Object *v0;
    Vec4i sp24;
    Player *sp20;
    Player *sp1C;

    sp20 = (Player *) arg2->varObj[0];
    sp1C = gPlayers + (1 - sp20->playerId);

    sp24.x = arg0->x;
    sp24.y = arg0->y;
    sp24.z = arg0->z;

    if (arg1) {
        v0 = func_8002BFF0(&sp24, 0x1000, func_8000E9D8, D_80081278);
        if (v0 != NULL) {
            v0->vars[0] = 255 / (v0->modInst->numAnimFrames - 2);
            v0->flags |= 0x2000;
            func_8003453C(v0, &D_800499A4);
            v0->unk_088.a = 255;
        }

        if (arg3 == NULL) {
            arg3 = &D_8004B844[sp1C->characterId].unk_08[sp1C->playerId];
        }
        func_80023BE4(arg0, arg2, arg3);
    } else {
        v0 = func_8002BFF0(&sp24, 0x1000, func_8000E930, D_80081274);
        if (v0 != NULL) {
            v0->vars[0] = 255 / (v0->modInst->numAnimFrames - 12);
            v0->flags |= 0x2000;
            func_8003453C(v0, &D_800499A0);
            v0->unk_088.a = 255;
        }
    }
}

u8 func_8000EC70(Vec4s *arg0, Vec4i *arg1, u32 arg2, Vec4s *arg3) {
    s16 x1, z1;

    if (arg3->y < arg0->y - 200 || arg1->y < arg3->y) {
        return FALSE;
    }

    x1 = (arg0->x + arg1->x) * 0.5f;
    z1 = (arg0->z + arg1->z) * 0.5f;

    if (SQ(x1 - arg3->x) + SQ(z1 - arg3->z) < arg2) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Vec4s *func_8000ED50(Vec4s *arg0, Vec4i *arg1, u32 arg2, Vec4s *arg3, Vec4s *arg4) {
    s16 x1, z1;
    s32 dx, dz;
    s32 pad[4];
    s16 x2, y2, z2;

    x1 = (arg0->x + arg1->x) >> 1;
    z1 = (arg0->z + arg1->z) >> 1;

    if (arg3->y > arg0->y - 200 && arg1->y > arg3->y) {
        dx = x1 - arg3->x;
        dz = z1 - arg3->z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return arg3;
        }
    }

    if (arg4->y > arg0->y - 200 && arg1->y > arg4->y) {
        dx = x1 - arg4->x;
        dz = z1 - arg4->z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return arg4;
        }
    }

    x2 = D_80081268.x = (arg3->x + arg4->x) >> 1;
    y2 = D_80081268.y = (arg3->y + arg4->y) >> 1;
    z2 = D_80081268.z = (arg3->z + arg4->z) >> 1;

    if (D_80081268.y > arg0->y - 200 && arg1->y > D_80081268.y) {
        dx = x1 - D_80081268.x;
        dz = z1 - D_80081268.z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return &D_80081268;
        }
    }

    D_80081268.x = (x2 + arg4->x) >> 1;
    D_80081268.y = (y2 + arg4->y) >> 1;
    D_80081268.z = (z2 + arg4->z) >> 1;

    if (D_80081268.y > arg0->y - 200 && arg1->y > D_80081268.y) {
        dx = x1 - D_80081268.x;
        dz = z1 - D_80081268.z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return &D_80081268;
        }
    }

    D_80081268.x = (x2 + arg3->x) >> 1;
    D_80081268.y = (y2 + arg3->y) >> 1;
    D_80081268.z = (z2 + arg3->z) >> 1;

    if (D_80081268.y > arg0->y - 200 && arg1->y > D_80081268.y) {
        dx = x1 - D_80081268.x;
        dz = z1 - D_80081268.z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return &D_80081268;
        }
    }

    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000F074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000F3FC.s")
void func_8000F3FC(Player *, Player *, Vec4s *);

// #pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000F494.s")
void func_8000F494(Player *arg0, Player *arg1) {
    Vec4i *s1;
    Vec4s sp194;
    Vec4s sp18C;
    Vec4s sp184;
    Vec4s sp17C;
    Vec4s sp174;
    Vec4s *sp170;
    s32 pad[70];
    Transform *sp54;
    PlayerSub9 *arg09;
    PlayerSub9 *arg19;
    s32 pad2[6];

    s1 = &arg0->unk_00->pos;

    arg09 = &arg0->unk_198;
    arg19 = &arg1->unk_198;

    sp184.x = arg09->unk_08->x;
    sp184.y = arg09->unk_08->y;
    sp184.z = arg09->unk_08->z;

    sp17C.x = arg19->unk_10->x;
    sp17C.y = arg19->unk_10->y;
    sp17C.z = arg19->unk_10->z;

    if (arg19->unk_01) {
        sp194.x = arg19->unk_2E8.wolrd_matrix.w.x;
        sp194.y = arg19->unk_2E8.wolrd_matrix.w.y;
        sp194.z = arg19->unk_2E8.wolrd_matrix.w.z;

        sp170 = func_8000ED50(&sp184, s1, arg09->unk_2C + 55000, &sp17C, &sp194);
        if (sp170 != NULL) {
            if (sp170->y < sp184.y) {
                sp170->y = sp184.y;
            }

            sp170->x = ((func_80012854((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
            sp170->z = ((-func_80012854(((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
            func_8000F3FC(arg0, arg1, sp170);
            return;
        }
    } else if (func_8000EC70(&sp184, s1, arg09->unk_2C, &sp17C)) {
        if (sp17C.y < sp184.y) {
            sp17C.y = sp184.y;
        }
        sp17C.x = ((func_80012854((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
        sp17C.z = ((-func_80012854(((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
        func_8000F3FC(arg0, arg1, &sp17C);
        return;
    }

    sp174.x = arg19->unk_0C->x;
    sp174.y = arg19->unk_0C->y;
    sp174.z = arg19->unk_0C->z;

    if (arg19->unk_00) {
        sp54 = &arg19->unk_1D0;
        sp18C.x = arg19->unk_1D0.wolrd_matrix.w.x;
        sp18C.y = arg19->unk_1D0.wolrd_matrix.w.y;
        sp18C.z = arg19->unk_1D0.wolrd_matrix.w.z;

        sp170 = func_8000ED50(&sp184, s1, arg09->unk_2C + 55000, &sp174, &sp18C);
        if (sp170 != NULL) {
            if (sp170->y < sp184.y) {
                sp170->y = sp184.y;
            }

            sp170->x = ((func_80012854((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
            sp170->z = ((-func_80012854(((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
            func_8000F3FC(arg0, arg1, sp170);
            return;
        }
    } else if (func_8000EC70(&sp184, s1, arg09->unk_2C, &sp174)) {
        if (sp174.y < sp184.y) {
            sp174.y = sp184.y;
        }
        sp174.x = ((func_80012854((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
        sp174.z = ((-func_80012854(((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
        func_8000F3FC(arg0, arg1, &sp174);
        return;
    }

    if (arg19->unk_02) {
        if (arg19->unk_03) {
            // @bug sp54 could be uninitialized?
            sp18C.x = sp54->wolrd_matrix.w.x;
            sp18C.y = sp54->wolrd_matrix.w.y;
            sp18C.z = sp54->wolrd_matrix.w.z;
        } else {
            sp18C.x = arg19->unk_24->x;
            sp18C.y = arg19->unk_24->y;
            sp18C.z = arg19->unk_24->z;
        }

        if (func_8000EC70(&sp184, s1, arg09->unk_30, &sp18C)) {
            if (sp18C.y < sp184.y) {
                sp18C.y = sp184.y;
            }
            sp18C.x = ((func_80012854((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
            sp18C.z = ((-func_80012854(((0xC00 - arg0->unk_00->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
            func_8000F3FC(arg0, arg1, &sp18C);
        }
    }
}

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
