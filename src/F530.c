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

void func_8000EA80(Vec4s *arg0, u8 arg1, Object *arg2, ColorRGBA *arg3) {
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

#ifdef NON_MATCHING
s16 func_8000F074(Player *arg0, Player *arg1, PlayerSub3 *arg2) {
    PlayerSub3 *sub3;
    s32 v13;
    s32 pad;
    s16 pad2;
    s16 a3;
    u8 v1;
    u8 v12;
    s32 t0;

    a3 = 0;
    sub3 = arg0->unk_90;
    t0 = sub3->unk_34;

    if ((t0 & 0xA) && arg0->unk_00->pos.y + arg0->unk_00->modInst->unk_010.local_matrix.w.y > -400.0f &&
        arg0->unk_198.unk_14->y - arg0->unk_198.unk_08->y > 200.0f) {
        t0 &= ~0xA;
        t0 |= 4;
    }

    v1 = (t0 & 0x80) && (arg0->unk_00->spriteId >= 12);

    if (t0 & 0x4000) {
        if (t0 & 4) {
            a3 = arg2->unk_0E;
        } else {
            a3 = arg2->unk_10;
        }
    } else if (t0 & 0x10000) {
        a3 = arg2->unk_1C;
    } else if (t0 & 0x20000) {
        a3 = arg2->unk_14;
    } else if ((t0 & 0x400) && arg2->unk_1E != 0) {
        if (t0 & 0x200) {
            a3 = 206;
        } else {
            a3 = 97;
        }
    } else if (func_80030BB0(arg0->unk_00) && !v1) {
        if (t0 & 0xE) {
            a3 = arg2->unk_16;
        } else if (t0 & 1) {
            a3 = arg2->unk_18;
        }

        if (t0 & 0xA) {
            a3 = arg2->unk_1A;
        } else {
            arg0->unk_00->pos.y = 0;
        }

        arg0->unk_00->flags &= ~0x800000;
    } else {
        if (t0 & 0xE) {
            a3 = arg2->unk_0A;
        } else if (t0 & 1) {
            a3 = arg2->unk_0C;
        }

        if (t0 & 0xA) {
            a3 = arg2->unk_12;
        } else {
            arg0->unk_00->pos.y = 0;
        }
    }

    v12 = (a3 == 270) || (a3 == 271);

    if (a3 != 0 && !D_8013C250) {
        arg1->damage = arg2->unk_20;
        if (arg1->unk_00->vars[3] < 0) {
            arg1->total_damage += arg1->damage;
        } else {
            arg1->total_damage = arg1->damage;
            arg1->unk_00->vars[3] = -1;
        }

        if (a3 >= 236 && a3 <= 245) {
            arg0->unk_00->vars[2] = arg2->unk_20;
        } else if (!v12 && D_80080230 != 40) {
            arg0->unk_00->unk_070 -= arg2->unk_20;
        }

        v13 = arg0->unk_00->unk_070;
        if (v13 < 0) {
            v13 = arg0->unk_00->unk_070 = 0;
        }

        if (v13 == 0) {
            D_8005BFC0 |= 0x200;
            if (arg0->unk_80 & 8) {
                if (t0 & 4) {
                    a3 = 118;
                } else if (t0 & 1) {
                    a3 = 81;
                }
            } else {
                if (t0 & 4) {
                    a3 = 70;
                } else if (t0 & 1) {
                    a3 = 73;
                }
            }
        }

        func_800063C4(arg0, a3, TRUE);
    }

    return a3;
}
#else
s16 func_8000F074(Player *arg0, Player *arg1, PlayerSub3 *arg2);
#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_8000F074.s")
#endif

void func_8000F3FC(Player *arg0, Player *arg1, Vec4s *arg2) {
    s16 v0;
    s16 t0;
    PlayerSub3 *q;

    q = arg1->unk_90;

    if (!D_800801F0 || D_8013C250) {
        v0 = func_8000F074(arg0, arg1, q);
        t0 = v0 == 270 || v0 == 271;
        if (v0 != 0) {
            func_8000EA80(arg2, t0, arg0->unk_00, NULL);
            arg0->unk_5F48 = 13;
            arg1->unk_5F48 = 2;
        }
    }
}

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
        sp194.x = arg19->unk_150.wolrd_matrix.w.x;
        sp194.y = arg19->unk_150.wolrd_matrix.w.y;
        sp194.z = arg19->unk_150.wolrd_matrix.w.z;

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
        sp54 = &arg19->unk_38;
        sp18C.x = arg19->unk_38.wolrd_matrix.w.x;
        sp18C.y = arg19->unk_38.wolrd_matrix.w.y;
        sp18C.z = arg19->unk_38.wolrd_matrix.w.z;

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

void func_8000FB30(Player *arg0, Player *arg1) {
    Vec4i *sp5C;
    Vec4s sp54;
    Vec4s sp4C;
    Vec4s sp44;
    PlayerSub9 *arg19;
    PlayerSub9 *arg09;
    u32 a2;
    Vec4s *v02;
    u8 v0;

    sp5C = &arg0->unk_00->pos;

    arg19 = &arg1->unk_198;
    arg09 = &arg0->unk_198;

    sp54.x = arg09->unk_08->x;
    sp54.y = arg09->unk_08->y;
    sp54.z = arg09->unk_08->z;

    if (arg19->unk_05) {
        sp4C.x = arg19->unk_380.wolrd_matrix.w.x;
        sp4C.y = arg19->unk_380.wolrd_matrix.w.y;
        sp4C.z = arg19->unk_380.wolrd_matrix.w.z;
    } else {
        sp4C.x = arg19->unk_18->x;
        sp4C.y = arg19->unk_18->y;
        sp4C.z = arg19->unk_18->z;
    }

    sp44.x = arg19->unk_20->x;
    sp44.y = arg19->unk_20->y;
    sp44.z = arg19->unk_20->z;

    v0 = (arg1->unk_90->unk_34 & 0x1000) || (sp4C.y < -200);

    if (sp4C.y < arg09->unk_20->y) {
        a2 = arg09->unk_2C;
    } else {
        a2 = arg09->unk_30;
    }

    if (v0) {
        v02 = func_8000ED50(&sp54, sp5C, a2, &sp44, &sp4C);
        if (v02 != NULL) {
            func_8000F3FC(arg0, arg1, v02);
            return;
        }
    }

    if (arg19->unk_04) {
        sp4C.x = arg19->unk_268.wolrd_matrix.w.x;
        sp4C.y = arg19->unk_268.wolrd_matrix.w.y;
        sp4C.z = arg19->unk_268.wolrd_matrix.w.z;
    } else {
        sp4C.x = arg19->unk_14->x;
        sp4C.y = arg19->unk_14->y;
        sp4C.z = arg19->unk_14->z;
    }

    sp44.x = arg19->unk_1C->x;
    sp44.y = arg19->unk_1C->y;
    sp44.z = arg19->unk_1C->z;

    if (sp4C.y < arg09->unk_1C->y) {
        a2 = arg09->unk_2C;
    } else {
        a2 = arg09->unk_30;
    }

    v0 = (arg1->unk_90->unk_34 & 0x800) || (sp4C.y < -200);

    if (v0) {
        v02 = func_8000ED50(&sp54, sp5C, a2, &sp44, &sp4C);
        if (v02 != NULL) {
            func_8000F3FC(arg0, arg1, v02);
        }
    }
}

void func_8000FE9C(Player *arg0, Player *arg1) {
    PlayerSub9 *arg09;
    PlayerSub9 *arg19;
    Vec4s sp50;
    Vec4s sp48;
    Vec4s sp40;
    Vec4i sp30;
    Vec4s *v03;
    s32 pad;

    arg09 = &arg0->unk_198;
    arg19 = &arg1->unk_198;

    if (arg1->unk_00->pos.y < -20 ||
        arg1->unk_00->modInst->unk_010.local_matrix.w.y < arg1->unk_00->modInst->unk_9E4.y) {
        return;
    }

    sp50.x = arg09->unk_08->x;
    sp50.y = arg09->unk_08->y;
    sp50.z = arg09->unk_08->z;

    sp48.x = arg09->unk_18->x;
    sp48.y = arg09->unk_18->y;
    sp48.z = arg09->unk_18->z;

    sp40.x = arg19->unk_28->x;
    sp40.z = arg19->unk_28->z;
    sp40.y = arg19->unk_28->y - 100.0f;

    sp30.x = arg19->unk_28->x;
    sp30.z = arg19->unk_28->z;
    sp30.y = arg19->unk_28->y;

    v03 = func_8000ED50(&sp40, &sp30, 80000, &sp50, &sp48);
    if (v03 != NULL) {
        func_8000F3FC(arg0, arg1, v03);
        return;
    }

    if (arg19->unk_01) {
        sp40.x = arg19->unk_150.wolrd_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->unk_150.wolrd_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->unk_10->x;
        sp40.y = -100;
        sp40.z = arg19->unk_10->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    }

    if (arg19->unk_00) {
        sp40.x = arg19->unk_38.wolrd_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->unk_38.wolrd_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->unk_0C->x;
        sp40.y = -100;
        sp40.z = arg19->unk_0C->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    }
}

void func_80010280(Player *arg0, Player *arg1) {
    PlayerSub9 *arg09;
    PlayerSub9 *arg19;
    Vec4s sp50;
    Vec4s sp48;
    Vec4s sp40;
    Vec4i sp30;
    Vec4s *v03;

    arg09 = &arg0->unk_198;
    arg19 = &arg1->unk_198;

    if (arg1->unk_00->pos.y < -20 ||
        arg1->unk_00->modInst->unk_010.local_matrix.w.y < arg1->unk_00->modInst->unk_9E4.y) {
        return;
    }

    sp50.x = arg09->unk_08->x;
    sp50.y = arg09->unk_08->y;
    sp50.z = arg09->unk_08->z;

    sp48.x = arg09->unk_18->x;
    sp48.y = arg09->unk_18->y;
    sp48.z = arg09->unk_18->z;

    sp40.x = arg19->unk_28->x;
    sp40.z = arg19->unk_28->z;
    sp40.y = arg19->unk_28->y - 100.0f;

    sp30.x = arg19->unk_28->x;
    sp30.z = arg19->unk_28->z;
    sp30.y = arg19->unk_28->y;

    v03 = func_8000ED50(&sp40, &sp30, 80000, &sp50, &sp48);
    if (v03 != NULL) {
        func_8000F3FC(arg0, arg1, v03);
        return;
    }

    if (arg19->unk_04) {
        sp40.x = arg19->unk_268.wolrd_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->unk_268.wolrd_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->unk_14->x;
        sp40.y = -100;
        sp40.z = arg19->unk_14->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    }

    if (arg19->unk_05) {
        sp40.x = arg19->unk_380.wolrd_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->unk_380.wolrd_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->unk_18->x;
        sp40.y = -100;
        sp40.z = arg19->unk_18->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = func_8000ED50(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            func_8000F3FC(arg0, arg1, v03);
            return;
        }
    }
}

void func_80010664(Player *arg0, UnkTauSub *arg1) {
    arg0->unk_198.unk_08 = &arg0->unk_00->modInst->transforms[arg1->unk_00].wolrd_matrix.w;
    arg0->unk_198.unk_0C = &arg0->unk_00->modInst->transforms[arg1->unk_04].wolrd_matrix.w;
    arg0->unk_198.unk_10 = &arg0->unk_00->modInst->transforms[arg1->unk_08].wolrd_matrix.w;
    arg0->unk_198.unk_14 = &arg0->unk_00->modInst->transforms[arg1->unk_0C].wolrd_matrix.w;
    arg0->unk_198.unk_18 = &arg0->unk_00->modInst->transforms[arg1->unk_10].wolrd_matrix.w;
    arg0->unk_198.unk_1C = &arg0->unk_00->modInst->transforms[arg1->unk_14].wolrd_matrix.w;
    arg0->unk_198.unk_20 = &arg0->unk_00->modInst->transforms[arg1->unk_18].wolrd_matrix.w;
    arg0->unk_198.unk_28 = &arg0->unk_00->modInst->transforms[0].wolrd_matrix.w;

    if (arg1->unk_6C > 0) {
        arg0->unk_198.unk_24 = &arg0->unk_00->modInst->transforms[arg1->unk_6C].wolrd_matrix.w;
        arg0->unk_198.unk_02 = TRUE;
    } else {
        arg0->unk_198.unk_02 = FALSE;
    }

    arg0->unk_198.unk_2C = arg1->unk_24;
    arg0->unk_198.unk_30 = arg1->unk_28;

    if (arg1->unk_3C.x != 0 || arg1->unk_3C.y != 0 || arg1->unk_3C.z != 0) {
        arg0->unk_198.unk_01 = TRUE;
        func_80012A20(&arg0->unk_00->modInst->transforms[arg1->unk_20], &arg0->unk_198.unk_150, -3, -3);
        arg0->unk_198.unk_150.local_matrix.w.x = arg1->unk_3C.x;
        arg0->unk_198.unk_150.local_matrix.w.y = arg1->unk_3C.y;
        arg0->unk_198.unk_150.local_matrix.w.z = arg1->unk_3C.z;
    } else {
        arg0->unk_198.unk_01 = FALSE;
    }

    if (arg1->unk_2C.x != 0 || arg1->unk_2C.y != 0 || arg1->unk_2C.z != 0) {
        arg0->unk_198.unk_00 = TRUE;
        func_80012A20(&arg0->unk_00->modInst->transforms[arg1->unk_1C], &arg0->unk_198.unk_38, -3, -3);
        arg0->unk_198.unk_38.local_matrix.w.x = arg1->unk_2C.x;
        arg0->unk_198.unk_38.local_matrix.w.y = arg1->unk_2C.y;
        arg0->unk_198.unk_38.local_matrix.w.z = arg1->unk_2C.z;
    } else {
        arg0->unk_198.unk_00 = FALSE;
    }

    if (arg1->unk_70.x != 0 || arg1->unk_70.y != 0 || arg1->unk_70.z != 0) {
        arg0->unk_198.unk_03 = TRUE;
        func_80012A20(&arg0->unk_00->modInst->transforms[arg1->unk_6C], &arg0->unk_198.unk_498, -3, -3);
        arg0->unk_198.unk_498.local_matrix.w.x = arg1->unk_70.x;
        arg0->unk_198.unk_498.local_matrix.w.y = arg1->unk_70.y;
        arg0->unk_198.unk_498.local_matrix.w.z = arg1->unk_70.z;
    } else {
        arg0->unk_198.unk_03 = FALSE;
    }

    if (arg1->unk_5C.x != 0 || arg1->unk_5C.y != 0 || arg1->unk_5C.z != 0) {
        arg0->unk_198.unk_05 = TRUE;
        func_80012A20(&arg0->unk_00->modInst->transforms[arg1->unk_10], &arg0->unk_198.unk_380, -3, -3);
        arg0->unk_198.unk_380.local_matrix.w.x = arg1->unk_5C.x;
        arg0->unk_198.unk_380.local_matrix.w.y = arg1->unk_5C.y;
        arg0->unk_198.unk_380.local_matrix.w.z = arg1->unk_5C.z;
    } else {
        arg0->unk_198.unk_05 = FALSE;
    }

    if (arg1->unk_4C.x != 0 || arg1->unk_4C.y != 0 || arg1->unk_4C.z != 0) {
        arg0->unk_198.unk_04 = TRUE;
        func_80012A20(&arg0->unk_00->modInst->transforms[arg1->unk_0C], &arg0->unk_198.unk_268, -3, -3);
        arg0->unk_198.unk_268.local_matrix.w.x = arg1->unk_4C.x;
        arg0->unk_198.unk_268.local_matrix.w.y = arg1->unk_4C.y;
        arg0->unk_198.unk_268.local_matrix.w.z = arg1->unk_4C.z;
    } else {
        arg0->unk_198.unk_04 = FALSE;
    }
}

// split ??

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010B00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010B14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010B84.s")

void func_80010BE4(PlayerSub6Sub1 *arg0) {
    func_80010B00(arg0->unk_00, 3);
    func_80010B00(arg0->unk_50, 3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80010C18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80011258.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_800114BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_800114DC.s")
void func_800114DC(BatchInfo *);

#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_800115A0.s")

extern Gfx D_80081280[];

#ifdef NON_EQUIVALENT
void func_80012150(PlayerSub6 *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4,
                   ColorRGBA *arg5) {
    u32 i, j;
    Gfx *gfx;
    u32 a;
    PlayerSub6Sub2 *s6;
    BatchInfo *bi;

    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->unk_08 = arg3;

    func_80010BE4(&arg0->unk_0C);
    func_80010BE4(&arg0->unk_EC);

    arg0->unk_1CC = 0;
    arg0->unk_1D0 = 0;
    arg0->unk_1450 = arg4;

    gfx = D_80081280;
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
    gSPNoOp(gfx++);

    for (i = 0, bi = arg0->unk_12D8; i < 4; i++, bi++) {
        func_800114DC(bi);
        bi->header.texGfx = D_80081280;
        bi->header.unk_0B = 0;
    }

    for (i = 0; i < 16; i++) {
        s6 = &arg0->unk_1D8[i];
        func_800114DC(&s6->unk_00);
        mem_fill(s6->unk_58, 0, sizeof(s6->unk_58));

        if (i == 0) {
            a = 200;
            for (j = 0; j < 4; j++) {
                s6->unk_58[j].unk_00.r = arg5->r;
                s6->unk_58[j].unk_00.g = arg5->g;
                s6->unk_58[j].unk_00.b = arg5->b;
                s6->unk_58[j].unk_00.a = a;
                s6->unk_58[j].unk_04.r = arg5->r;
                s6->unk_58[j].unk_04.g = arg5->g;
                s6->unk_58[j].unk_04.b = arg5->b;
                s6->unk_58[j].unk_04.a = a;
                a += 4;
            }
        } else {
            a = 204;
            for (j = 0; j < 4; j++) {
                s6->unk_58[j].unk_00.r = arg5->r;
                s6->unk_58[j].unk_00.g = arg5->g;
                s6->unk_58[j].unk_00.b = arg5->b;
                s6->unk_58[j].unk_00.a = a;
                s6->unk_58[j].unk_04.r = arg5->r;
                s6->unk_58[j].unk_04.g = arg5->g;
                s6->unk_58[j].unk_04.b = arg5->b;
                s6->unk_58[j].unk_04.a = a;
                a += 4;
                if (a > 255) {
                    a = 255;
                }
            }
        }

        s6->unk_F8 = -1;
    }

    arg0->unk_1438 = arg0->unk_143C = arg0->unk_1440 = 0.0f;
    arg0->unk_1444 = arg0->unk_1448 = arg0->unk_144C = 0.0f;

    arg0->unk_1454.r = arg5->r;
    arg0->unk_1454.g = arg5->g;
    arg0->unk_1454.b = arg5->b;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/F530/func_80012150.s")
#endif
