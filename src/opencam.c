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
const char D_80055010[] = "opencamX.oc";
extern char *D_80052CCC;

extern s32 D_800801F4;
extern s32 D_800801F8;
extern s32 D_80080200;
extern s32 D_80080204;
extern s32 D_80080208;
extern s16 D_8008020E;
extern Vec4i *D_80080220;
extern Vec4i *D_80080224;
extern Object *D_80080228[];

extern s16 D_8013C224;
extern s16 D_8013C304;
extern f32 D_8013C308;
extern s32 D_8013C340;
extern s32 D_8013C344;
extern s32 D_8013C348;
extern s32 D_8013C34C;
extern s32 D_8013C350;
extern s32 D_8013C354;
extern s32 D_8013C358;
extern s32 D_8013C35C;
extern s32 D_8013C360;
extern s32 D_8013C364;
extern s32 D_8013C36C;
extern s32 D_8013C370;
extern s32 D_8013C37C;
extern s32 D_8013C380;
extern s32 D_8013C384;
extern s16 D_8013C38A;
extern s16 D_8013C38C;
extern s16 D_8013C38E;
extern f32 D_8013C5A0;

void func_8002EB2C(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/abs.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C328.s")
s32 func_8002C328(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C340.s")
void func_8002C340(void);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C3FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C490.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C6E8.s")
void func_8002C6E8(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002C9F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CAEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CB28.s")
void func_8002CB28(void);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CDE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CDFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CE58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002CFD4.s")
s32 func_8002CFD4(void *arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002D160.s")

void func_8002D1A8(Object *obj) {
    s32 a2, a3;

    a2 = 0;
    a3 = 0;

    if (gCameraTarget.x > 0x2300 || obj->pos.x > 0x2300) {
        a2 = -0x2800;
    } else if (gCameraTarget.x < -0x2300 || obj->pos.x < -0x2300) {
        a2 = 0x2800;
    }

    if (gCameraTarget.z > 0x2300 || obj->pos.z > 0x2300) {
        a3 = -0x2800;
    } else if (gCameraTarget.z < -0x2300 || obj->pos.z < -0x2300) {
        a3 = 0x2800;
    }

    if (a2 != 0 || a3 != 0) {
        obj->vars[3] = a2;
        obj->vars[4] = a3;
        func_800028E0(func_8002CFD4, NULL);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002D278.s")
void func_8002D278(Object *obj, u8 arg1);

void func_8002DA08(Object *obj) {
    gCameraTarget.y = -480;
    D_8013C340 = func_80012518(899, 5045);
    D_8013C344 = -func_80012854(D_8013C340 + 0x400);
    D_8013C348 = func_80012854(D_8013C340);
    D_8013C34C = 2300;
    D_8013C350 = -5045;
    D_8013C350 = (u32) (sqrtf(SQ(D_8013C350) + SQ(1379)) + 0.5);
    D_8013C354 = (D_8013C350 << 16) / 2400;
    D_8013C358 = (-347 << 16) / D_8013C350;
    D_8013C360 = (-400 << 16) / D_8013C350;
    D_8013C364 = (12 << 16) / D_8013C350;
    D_8013C36C = 291271;
    D_8013C35C = -480;
    D_80080220 = &gPlayers[PLAYER_1].unk_00->pos;
    D_80080224 = &gPlayers[PLAYER_2].unk_00->pos;

    obj->vars[1] = 0xC00;
    obj->vars[2] = 0;
    func_8002D278(obj, FALSE);
    D_8013C830 = 0;
    obj->pos.x = 0;
    obj->pos.z = -2300;
    obj->pos.y = -480;
    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -480;
    D_80052CC0 = D_80052CB8 = D_80052CBC = 0;
}

void func_8002DCC8(Object *obj) {
    D_80049AE8 = D_8013C82C;
    D_80081428 = D_8013C828;

    if ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START)) {
        if (D_80080230 != 40) {
            func_80017CA8();
        } else {
            gPlayers[PLAYER_1].unk_80 &= ~0x100000;
            gPlayers[PLAYER_2].unk_80 &= ~0x100000;
            D_8005BFC0 &= ~4;
        }

        D_80049AE4 = 0;
        D_8013C828 = D_8013C304;
        D_8013C5A0 = D_8013C308;

        func_8002D278(obj, FALSE);

        obj->currentTask->func = func_8002EB2C;
        obj->modInst->animations[0] = NULL;
        gPlayerInput[PLAYER_1].unk_08 = gPlayerInput[PLAYER_2].unk_08 = FALSE;
        D_8008012C &= ~0x11;
    } else {
        if (--obj->vars[10] <= 0) {
            obj->currentTask->func = func_8002C6E8;
        }
    }
}

void func_8002DE20(Object *obj) {
    s32 assetId;
    char sp18[20];

    func_8002DA08(obj);
    func_8002C340();

    str_copy(sp18, D_80052CCC);
    sp18[7] = '1' + D_8013C224;
    assetId = asset_find(sp18, 0xABAB);
    func_80038E00(gCamera, (AnimHeader **) gAssets[assetId].data);
    gCamera->currentTask->func = func_8002DCC8;
    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->counter = 1;
    gCamera->vars[10] = 60;
    gPlayerInput[PLAYER_1].unk_08 = assetId = gPlayerInput[PLAYER_2].unk_08 = FALSE; // required to match
}

void func_8002DEFC(Object *obj) {
    s32 assetId;
    char sp18[20];

    func_8002DA08(obj);
    func_8002C340();

    str_copy(sp18, D_80052CCC);
    sp18[7] = '1' + D_8013C224;
    assetId = asset_find(sp18, 0xABAB);
    func_80038E00(gCamera, (AnimHeader **) gAssets[assetId].data);
    gCamera->currentTask->func = func_8002C6E8;
    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->counter = 1;
    gPlayerInput[PLAYER_1].unk_08 = assetId = gPlayerInput[PLAYER_2].unk_08 = FALSE; // required to match
}

#ifdef NON_EQUIVALENT
void func_8002DFCC(u8 arg0) {
    s16 s6;
    s16 s1;
    s32 v1, v0;
    u8 s0;
    s16 s3;
    s16 lo;
    s16 s4;

restart:
    D_800801F4 = D_80080200;
    D_800801F8 = D_80080204;

    D_80080200 = D_80080220->x - D_80080224->x;
    D_80080208 = -MIN(D_80080220->y, D_80080224->y);
    D_80080204 = D_80080220->z - D_80080224->z;

    s6 = func_80012518(D_80080204, D_80080200);
    if (D_80080200 != 0 || D_80080204 != 0) {
        s1 = (u32) (sqrtf(SQ(D_80080200) + SQ(D_80080204)) + 0.5);
    } else {
        s1 = 0;
    }

    if ((gPlayers[PLAYER_1].unk_80 & 0x400000) || (gPlayers[PLAYER_2].unk_80 & 0x400000) ||
        (gPlayers[PLAYER_1].unk_80 & 0x01000000) || (gPlayers[PLAYER_2].unk_80 & 0x01000000) && s1 < 3200) { // @bug?
        D_8008021C = D_8008020C;
        D_8008020C = s6;
        D_80080210 = s1;
        return;
    }

    v1 = MIN(gPlayers[PLAYER_1].unk_198.unk_18->y, gPlayers[PLAYER_1].unk_198.unk_14->y);
    v0 = MIN(gPlayers[PLAYER_2].unk_198.unk_18->y, gPlayers[PLAYER_2].unk_198.unk_14->y);

    if (v1 < v0) {
        s0 = (gPlayers[PLAYER_2].unk_198.unk_08->y - 200.0f) < v1;
    } else {
        s0 = (gPlayers[PLAYER_1].unk_198.unk_08->y - 200.0f) < v0;
    }

    if ((gPlayers[PLAYER_1].unk_90->unk_34 & 0x80000) || (gPlayers[PLAYER_2].unk_90->unk_34 & 0x80000)) {
        s0 = TRUE;
    }

    if (!arg0 && s0 && abs(func_8002CDFC(s6, D_8008020E)) > 0x200) {
        s4 = (s1 + 280) >> 1;

        s3 = (func_80012854(s6) * s4) >> 12;
        lo = ((-func_80012854(s6 + 0x400)) * s4) >> 12;
        D_80080220->x -= s3;
        D_80080220->z -= lo;

        s3 = (func_80012854(s6) * s4) >> 12;
        lo = ((-func_80012854(s6 + 0x400)) * s4) >> 12;
        D_80080224->x += s3;
        D_80080224->z += lo;

        arg0 = TRUE;
        goto restart;
    }

    if (s1 < D_80080214 && (!(gPlayers[PLAYER_1].unk_80 & 0x8000) || (gPlayers[PLAYER_2].unk_80 & 0x8000))) { // @bug ??
        s4 = D_80080214 - s1;
        if ((gPlayers[PLAYER_1].unk_90->unk_34 & 0x80000) || (gPlayers[PLAYER_2].unk_90->unk_34 & 0x80000) ||
            (gPlayers[PLAYER_1].unk_80 & 0x4000000) || (gPlayers[PLAYER_2].unk_80 & 0x4000000)) {
            s4 >>= 1;
        }
    } else {
        if (s1 > 3200) {
            s4 = 3200 - s1;
        } else {
            s4 = 0;
        }
    }

    D_8008021C = D_8008020C;
    D_8008020C = s6;
    D_80080210 = s1 + s4;

    if (s4 != 0 && (s0 || s1 > 3200)) {
        s4 >>= 1;
        s3 = (func_80012854(D_8008020C) * s4) >> 12;
        lo = (-func_80012854(D_8008020C + 0x400) * s4) >> 12;
        D_80080220->x += s3;
        D_80080220->z += lo;
        D_80080224->x -= s3;
        D_80080224->z -= lo;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/opencam/func_8002DFCC.s")
void func_8002DFCC(u8);
#endif

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

void func_8002E750(Object *obj) {
    s32 pad[2];
    s32 sp44;
    u32 ft4;
    s16 a1;
    s16 sp3E;
    Vec4i sp2C = { -200, 0, 0, 0 };

    D_8013C834 = FALSE;

    if (gCameraTarget.x > sp2C.x) {
        if (gCameraTarget.x - 5 > sp2C.x) {
            gCameraTarget.x = gCameraTarget.x - 5;
        } else {
            gCameraTarget.x = sp2C.x;
        }
    } else if (gCameraTarget.x < sp2C.x) {
        if (gCameraTarget.x + 5 < sp2C.x) {
            gCameraTarget.x = gCameraTarget.x + 5;
        } else {
            gCameraTarget.x = sp2C.x;
        }
    }

    if (gCameraTarget.z > sp2C.z) {
        if (gCameraTarget.z - 5 > sp2C.z) {
            gCameraTarget.z = gCameraTarget.z - 5;
        } else {
            gCameraTarget.z = sp2C.z;
        }
    } else if (gCameraTarget.z < sp2C.z) {
        if (gCameraTarget.z + 5 < sp2C.z) {
            gCameraTarget.z = gCameraTarget.z + 5;
        } else {
            gCameraTarget.z = sp2C.z;
        }
    }

    ft4 = sqrtf(SQ(obj->pos.x - gCameraTarget.x) + SQ(obj->pos.z - gCameraTarget.z)) + 0.5;
    a1 = obj->vars[1];
    a1 = (a1 + D_8013C38A) & 0xFFF;
    obj->vars[1] = sp3E = a1;
    sp44 = (s32) ft4 + D_8013C38E;
    if (D_8013C38E > 0 && sp44 > 1800) {
        D_8013C38E = -D_8013C38E;
    }
    if (D_8013C38E < 0 && sp44 < 1500) {
        D_8013C38E = -D_8013C38E;
    }

    obj->pos.x = ((func_80012854(sp3E) * sp44) >> 12) + gCameraTarget.x;
    obj->pos.z = (((-func_80012854(sp3E + 0x400)) * sp44) >> 12) + gCameraTarget.z;
    obj->pos.y += D_8013C38C;
    if (D_8013C38C > 0 && obj->pos.y > -360) {
        D_8013C38C = -D_8013C38C;
    }
    if (D_8013C38C < 0 && obj->pos.y < -1200) {
        D_8013C38C = -D_8013C38C;
    }
}

void func_8002EA50(Object *obj, s32 arg1) {
    s32 sp24;
    s32 sp20;

    sp24 = obj->pos.x - gCameraTarget.x;
    sp20 = obj->pos.z - gCameraTarget.z;
    D_8013C38A = (guRandom() % 2) + 2;
    D_8013C38C = -1;
    D_8013C38E = (guRandom() % 2) + 1;
    obj->currentTask->func = func_8002E750;
    obj->currentTask->counter = 0;
    obj->vars[3] = arg1;
    obj->vars[1] = func_80012518(sp20, sp24);
    func_8002E750(obj);
}

u8 D_80052CE0 = TRUE;

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

    func_8002DFCC(FALSE);

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

    if (func_8002C328(sp100) > D_80052C60 || func_8002C328(spFC) > D_80052C60 || D_80052CE0) {
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
