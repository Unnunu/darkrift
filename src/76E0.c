#include "common.h"

typedef struct UnkObjDef2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} UnkObjDef2; // size = 0x8

typedef struct UnkObjDef3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkObjDef3; // size = 0x10

typedef struct UnkObjDef4 {
    /* 0x00 */ char *unk_00;
    /* 0x04 */ void (*unk_04)(Object *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkObjDef4; // size = 0x10

extern u8 D_800B6340;
extern Object *D_8013C560;
extern s32 D_8008012C;

void func_800052EC(s16 arg0);
void func_8001B5B0(char *, s32);
void func_80029630(void);
void func_8002DE20(Object *);
void func_80038DE0(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006C14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006CEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006E0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006E6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006FB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800070C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800070F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800071F0.s")

const char D_80053F14[] = "tc";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007248.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007374.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007474.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007574.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007774.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007868.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007968.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007B68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007DB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007F4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800081A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800082CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800083EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008510.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008634.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008758.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000887C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800089A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008AC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008BE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008D0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008D64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008D98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008FDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800092B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80009480.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80009554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800095A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000965C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800096D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800099F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80009CE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80009E8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000A298.s")

const char D_80054418[] = "options2.sp2";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000A354.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000A514.s")

const char D_80054448[] = "options2.sp2";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000A578.s")

const char D_80054464[] = "options2.sp2";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000A6B8.s")

void func_8000A828(void) {
    asset_open_folder("/title/error", 0x2000);
    func_80014B60("messpg", 0, 90, 0, 180, 1, 0x2000);
    func_80001D88();
}

void gamemode_33_run(void) {
    func_800263A8();
    D_8005BFC0 |= 4;
    D_8008012C |= 0x20;
    D_8008012C |= 0x40;
    if (!gPlayerInput[0].unk_0B && !gPlayerInput[1].unk_0B) {
        func_8000A828();
    }

    asset_open_folder("/title/logo", 0x2000);
    func_80014B60("vic", 0, 30, 0, 180, 1, 0x2000);
    func_80014B60("n64lic", 0, 190, 0, 240, 1, 0x2000);
    func_8002BB6C(func_80019DE4, 0x1000);
    func_80001D88();
    func_8002630C(0x2000);
}

const char D_800544D0[] = "options2.sp2";
const char D_800544E0[] = "options2.sp2";
const char D_800544F0[] = "options2.sp2";
const char D_80054500[] = "options2.sp2";
const char D_80054510[] = "options2.sp2";
const char D_80054520[] = "options2.sp2";
const char D_80054530[] = "options2.sp2";
const char D_80054540[] = "options2.sp2";
const char D_80054550[] = "options2.sp2";
const char D_80054560[] = "options2.sp2";
const char D_80054570[] = "options2.sp2";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000A98C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000AFA4.s")

const char D_80054598[] = "options2.sp2";
const char D_800545A8[] = "options2.sp2";
const char D_800545B8[] = "options2.sp2";
const char D_800545C8[] = "options2.sp2";
const char D_800545D8[] = "options2.sp2";
const char D_800545E8[] = "options2.sp2";
const char D_800545F8[] = "options2.sp2";
const char D_80054608[] = "options2.sp2";
const char D_80054618[] = "options2.sp2";
const char D_80054628[] = "options2.sp2";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000B088.s")

const char D_80054650[] = "options2.sp2";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000B934.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000BA4C.s")

// TODO expand .data
s32 D_800498C0[] = { 0x7E, 0, 0 };

void func_8000BB1C(void) {
    s32 unused;
    UnkObjDef2 sp74 = { 0x0000FE70, 0 };
    UnkObjDef3 sp64 = { 0xFFFFFE70, 0, 0, 0 };
    UnkObjDef3 sp54 = { 400, 0, 0, 0 };
    s32 unused2;
    s32 sp4C = D_800B6340;
    UnkObjDef4 sp3C = { "gore", func_80038DE0, 0x1000, 0 };
    UnkObjDef4 sp2C = { "arena", func_80038DE0, 0x1000, 0 };

    asset_open_folder("/bars", 0xABAB);
    func_800052EC(0);
    func_800052EC(1);
    func_80014B60("bg2", 0, 74, 0x2000, 0x10000, 0, sp4C);
    func_80014B60("bg0", 0, 15, 0x1000, 0x10000, 1, sp4C);
    func_8001B5B0("arena", sp4C);
    func_80029630();

    D_8013C560->unk_1F4->unk_84 = 0;
    D_8013C560->unk_1F4->unk_00 = 1;
    D_8013C560->unk_1F4->unk_04 = func_8002DE20;
    D_8013C560->unk_1F4->unk_20 = 0;

    func_80001D88();
}
