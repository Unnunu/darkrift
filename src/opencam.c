#include "common.h"
#include "camera.h"

extern s32 D_80049AE4;

extern s32 D_80052C60;
extern s32 D_80052C64;
extern s32 D_80052C78;
extern s32 D_80052C7C;
extern s32 D_80052C80;
extern s32 D_80052C84;
extern s32 D_80052C88;
extern s32 D_80052C8C;
extern s32 D_80052C90;
extern s32 D_80052C94;
extern s32 D_80052C98;
extern s32 D_80052C9C;
extern s32 D_80052CA0;
extern s32 D_80052CA4;
extern s32 D_80052CAC;
extern s8 D_80052CB0;
extern u8 D_80052CB4;
extern s32 D_80052CB8;
extern s32 D_80052CBC;
extern s32 D_80052CC0;
extern s32 D_80052CC4;
extern s32 D_80052CC8;
extern u8 D_80052CE0;

extern s16 D_8008020E;
extern Vec4i *D_80080220;
extern Vec4i *D_80080224;
extern Object *D_80080228[];
extern s32 D_8013C344;
extern s32 D_8013C348;
extern s32 D_8013C34C;
extern s32 D_8013C350;
extern s32 D_8013C360;
extern s32 D_8013C354;
extern s32 D_8013C35C;
extern s32 D_8013C370;
extern s32 D_8013C37C;
extern s32 D_8013C380;
extern s32 D_8013C384;
extern s16 D_8013C38A;
extern s16 D_8013C38C;
extern s16 D_8013C38E;

const char D_80055010[] = "opencamX.oc";

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/abs.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C328.s")
s32 func_8002C328(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C340.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C3FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C6E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C9F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CAEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CB28.s")
void func_8002CB28(void);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CDE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CDFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CE58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CFD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002D160.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002D1A8.s")
void func_8002D1A8(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002D278.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002DA08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002DCC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002DE20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002DEFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002DFCC.s")
void func_8002DFCC(s32);

void func_8002E628(Vec4i *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 x, y, z;
    f32 temp;
    x = arg0->x;
    z = arg0->z;
    y = arg0->y;
    *arg2 = 0;
    *arg1 = 0;
    *arg3 = 0;

    if (*gCamera->modInst->animations == 0) {
        *arg1 = gCameraProjectionMatrix.x.x * x + gCameraProjectionMatrix.y.x * y + gCameraProjectionMatrix.z.x * z +
                gCameraProjectionMatrix.w.x;
        *arg2 = gCameraProjectionMatrix.x.y * x + gCameraProjectionMatrix.y.y * y + gCameraProjectionMatrix.z.y * z +
                gCameraProjectionMatrix.w.y;
        temp = gCameraProjectionMatrix.x.w * x + gCameraProjectionMatrix.y.w * y + gCameraProjectionMatrix.z.w * z +
               gCameraProjectionMatrix.w.w;
        if (temp != 0) {
            *arg1 /= temp;
            *arg2 /= temp;
            if (*arg1 < 0) {
                *arg3 = -*arg1;
            } else {
                *arg3 = *arg1;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002E750.s")
void func_8002E750(Object *);

void func_8002EA50(Object *arg0, s32 arg1) {
    s32 sp24;
    s32 sp20;

    sp24 = arg0->pos.x - gCameraTarget.x;
    sp20 = arg0->pos.z - gCameraTarget.z;
    D_8013C38A = (guRandom() % 2) + 2;
    D_8013C38C = -1;
    D_8013C38E = (guRandom() % 2) + 1;
    arg0->currentTask->func = func_8002E750;
    arg0->currentTask->counter = 0;
    arg0->vars[3] = arg1;
    arg0->vars[1] = func_80012518(sp20, sp24);
    func_8002E750(arg0);
}

void func_8002EB2C(Object *obj) {
    s32 sp10C;
    s32 sp108;
    s32 sp104;
    s32 sp100;
    s32 spFC;
    s32 pad_spF0[3];
    s32 spEC;
    s32 spE8;
    s32 spE4;
    s32 spE0;
    s32 pad_spDC;
    s32 spD8;
    s32 pad_spD4;
    s32 spD0;
    s32 spCC;
    s32 temp1;
    s32 pad_sp9C[11];
    s32 sp98;
    s32 pad_sp84[5];
    Vec4i sp74;
    Vec4s sp6C;
    u8 sp6B;
    u8 sp6A;
    s32 v02;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    Vec4i sp34;

    sp6A = FALSE;
    if (D_8013C250 == 0) {
        D_8008012C |= 0x20;
    } else {
        D_8008012C &= ~0x20;
    }

    func_8002DFCC(0);

    if (D_80080210 > 800) {
        spEC = ((D_80080210 - 800) * D_8013C354) >> 0x10;
    } else {
        spEC = 0;
    }
    if (spEC > D_8013C350) {
        spEC = D_8013C350;
    }

    spE0 = obj->vars[2];
    spD8 = spEC - spE0;
    sp104 = obj->vars[1];

    v02 = func_8002CDFC(D_8008020E, sp104);
    if (v02 < 0) {
        sp108 = v02 + D_80052CAC;
    } else {
        sp108 = v02 - D_80052CAC;
    }

    func_8002CB28();

    if (func_8002CDFC(D_8008020E, sp104) > 0) {
        D_80080228[PLAYER_1]->flags &= ~0x200;
        gPlayerInput[PLAYER_1].unk_09 = FALSE;
        D_80080228[PLAYER_2]->flags |= 0x200;
        gPlayerInput[PLAYER_2].unk_09 = TRUE;
    } else {
        D_80080228[PLAYER_1]->flags |= 0x200;
        gPlayerInput[PLAYER_1].unk_09 = TRUE;
        D_80080228[PLAYER_2]->flags &= ~0x200;
        gPlayerInput[PLAYER_2].unk_09 = FALSE;
    }

    if (func_8002C328(sp108) < 450 && D_8013C380 < 0x20000) {
        D_8013C384 = 30;
        D_8013C380 = 0;
        sp6A = 1;
        D_80052CB0 = 0;
        sp10C = sp104;
    } else if (func_8002C328(sp108) > 450 && D_8013C380 < 0xA0000) {
        D_8013C380 += 0x2000;
        D_8013C37C = D_8013C380 >> 16;
        if (sp108 < -D_8013C37C) {
            sp108 = -D_8013C37C;
        } else if (sp108 > D_8013C37C) {
            sp108 = D_8013C37C;
        }
        D_80052CB0 = sp108;
        sp10C = sp104 + sp108;
    } else {
        D_8013C380 -= 0x3000;
        D_8013C37C = D_8013C380 >> 16;
        if (sp108 < -D_8013C37C) {
            sp108 = -D_8013C37C;
        } else if (sp108 > D_8013C37C) {
            sp108 = D_8013C37C;
        }
        D_80052CB0 = sp108;
        sp10C = sp104 + sp108;
    }

    obj->vars[1] = sp10C;

    if (func_8002C328(spD8) < D_80052C64 && D_80052CB4 == 0) {
        spEC = spE0;
    } else {
        if (abs(spD8) < D_80052C78) {
            if (D_80052C88 < D_80052C8C - D_80052C80) {
                D_80052C8C -= D_80052C84;
            } else {
                D_80052C8C = D_80052C88;
            }
        } else if (D_80052C8C + D_80052C98 < D_80052C94) {
            D_80052C8C += D_80052C80;
        } else {
            D_80052C8C = D_80052C7C;
        }

        D_8013C370 = D_80052C8C >> 0x10;

        if (spD8 < -D_8013C370) {
            spD8 = -D_8013C370;
        } else if (spD8 > D_8013C370) {
            spD8 = D_8013C370;
        }
        D_80052CB4 = spD8;
        spEC = spE0 + spD8;
    }

    sp34.x = D_80080220->x;
    sp34.y = gPlayers[PLAYER_1].unk_198.unk_08->y;
    sp34.z = D_80080220->z;
    func_8002E628(&sp34, &sp60, &sp5C, &sp50);

    sp34.x = D_80080224->x;
    sp34.y = gPlayers[PLAYER_2].unk_198.unk_08->y;
    sp34.z = D_80080224->z;
    func_8002E628(&sp34, &sp58, &sp54, &sp4C);

    if (D_80052CB8 < 250 && (sp54 > 0.6 || sp5C > 0.6)) {
        sp5C = MAX(sp54, sp5C);
        sp5C -= 0.6;
        spEC = spE0 + sp5C * 700;
        D_80052CB8 += sp5C * 60;
        D_80052CBC -= sp5C * 30;
        D_80052CC8 += D_80052CC4;
        D_80052CC0 += sp5C * 2;
    } else if (sp54 <= 0.6 && sp5C <= 0.6) {
        if (D_80052CB8 > 8) {
            D_80052CB8 -= 8;
            D_80052CBC += 4;
        } else {
            D_80052CB8 = D_80052CBC = 0;
        }

        if (D_80052CC0 != 0) {
            D_80052CC0--;
        }

        if (sp50 > 0.65 || sp4C > 0.65) {
            sp50 = MAX(sp4C, sp50);
            sp50 -= 0.65;
            if (sp50 < 0.55) {
                spEC = spE0 + sp50 * 600;
            }
        }
    } else {
        spEC = spE0;
    }

    if (spEC > 6500) {
        spEC = 6500;
    }
    obj->vars[2] = spEC;

    D_80049AE8 = D_8013C82C + D_80052CC0 - (s32) (D_8013C830 * 0.2f);
    if (spEC > 1500 && D_80049AE8 < -24) {
        D_80049AE8 = -24;
    }

    gCameraTarget.y = ((D_8013C360 * spEC) >> 16) + D_80052CBC - 480;

    sp34.x = (D_80080224->x + D_80080220->x) >> 1;
    sp34.z = (D_80080224->z + D_80080220->z) >> 1;
    sp34.y = -480;
    func_8002E628(&sp34, &sp48, &sp44, &sp50);

    sp6B = sp50 > 0.2f;
    sp100 = ((D_80080224->x + D_80080220->x) >> 1) - gCameraTarget.x;
    spFC = ((D_80080224->z + D_80080220->z) >> 1) - gCameraTarget.z;

    if (func_8002C328(sp100) > D_80052C60 || func_8002C328(spFC) > D_80052C60 || D_80052CE0 != 0) {
        if (abs(sp100) < D_80052C90 && abs(spFC) < D_80052C90) {
            if (D_80052CA4 - D_80052C98 > D_80052CA0) {
                D_80052CA4 -= D_80052C9C; // @bug ??
            } else {
                D_80052CA4 = D_80052CA0;
            }
        } else {
            if (D_80052CA4 + D_80052C98 < D_80052C94) {
                D_80052CA4 += D_80052C98;
            } else {
                D_80052CA4 = D_80052C94;
            }
        }

        D_8013C370 = D_80052CA4 >> 16;

        if (sp100 < -D_8013C370) {
            sp100 = -D_8013C370;
        } else if (sp100 > D_8013C370) {
            sp100 = D_8013C370;
        }

        if (spFC < -D_8013C370) {
            spFC = -D_8013C370;
        } else if (spFC > D_8013C370) {
            spFC = D_8013C370;
        }

        D_80052CE0 = ((sp100 != 0) || (spFC != 0));

        gCameraTarget.x += sp100;
        gCameraTarget.z += spFC;

        if (sp6A && sp6B && (spFC != 0 || sp100 != 0)) {
            sp74.x = sp100;
            sp74.z = -spFC;

            sp6C.y = (0x400 - gCameraHeading) & 0xFFF;
            sp6C.x = sp6C.z = 0;
            func_8001370C(&sp74, &sp6C);

            if (sp74.x > 0) {
                sp98 = (u32) (sqrtf(sp100 * sp100 + spFC * spFC) + 0.5) >> 1;
            } else if (sp74.x < 0) {
                sp98 = -((u32) (sqrtf(sp100 * sp100 + spFC * spFC) + 0.5) >> 1);
            }

            if (sp98 > 2) {
                sp98 = 2;
            }
            if (sp98 < -2) {
                sp98 = -2;
            }
            D_80049AE4 += sp98;
        }
    }

    spE8 = ((func_80012854(sp10C) * D_8013C34C) >> 12) + gCameraTarget.x;
    spE4 = ((-func_80012854(sp10C + 0x400) * D_8013C34C) >> 12) + gCameraTarget.z;
    spD0 = (func_80012854(sp10C) * D_8013C348) >> 12;
    spCC = (-func_80012854(sp10C + 0x400) * D_8013C348) >> 12;
    temp1 = (spEC * D_8013C344) >> 12;

    obj->pos.x = ((spEC * spD0) >> 12) + spE8;
    obj->pos.z = ((spEC * spCC) >> 12) + spE4;
    obj->pos.y = D_8013C35C + D_80052CB8 - temp1;

    D_80081428 = D_8013C828;

    if (*gCamera->modInst->animations == 0 && !(gPlayers[PLAYER_1].unk_80 & 0x400000) &&
            !(gPlayers[PLAYER_2].unk_80 & 0x400000) ||
        D_8013C250 != 0) {
        func_8002D1A8(obj);
    }
}
