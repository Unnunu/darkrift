#include "common.h"

typedef struct UnkObjDef2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} UnkObjDef2; // size = 0x8

typedef struct UnkObjDef4 {
    /* 0x00 */ char *unk_00;
    /* 0x04 */ void (*unk_04)(Object *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkObjDef4; // size = 0x10

extern u8 D_800B6340;
extern Object *D_8013C560;
extern s32 D_8008012C;
extern Object *D_80081460;
extern s16 D_80049B30[];
extern s16 D_8004C1D0;
extern s16 D_8004C1D4;
extern s16 D_8004C1E4;
extern u8 D_8004A428;
extern s32 D_8004A448;
extern s32 D_8004A478;

s32 func_80019278(void); // TODO try to match if it returns void
void func_800052EC(s16 arg0);
void func_8001B5B0(char *, s32);
void func_80029630(void);
void func_8002DE20(Object *);
void func_80038DE0(Object *);
void func_8001905C(Object *);
void func_80018974(Object *);
void func_80018820(Object *);
void func_800189CC(Object *);

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

s32 D_80049530 = 0;

void func_80017F00(Object *);
void func_80017F60(Object *);
void func_80017FF4(Object *);
void func_80018088(Object *);
void func_80018120(Object *);
void func_800181C8(Object *);
void func_800182E0(Object *);
void func_800183FC(Object *);
void func_800184A8(Object *);
void func_80018554(Object *);
void func_80018600(Object *);

void func_8000A98C(void) {
    Object *s0;
    Object *v0;
    UnkObjectDef sp1AC = { 89, func_80017F00, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp198 = { 203, func_80017F60, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp184 = { 53, func_80017FF4, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp170 = { 14, func_80018088, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp15C = { 7, func_80018120, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp148 = { 20, func_800181C8, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp134 = { 20, func_800182E0, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp120 = { 57, func_800183FC, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp10C = { 58, func_800184A8, 0, 0x1000, "options2.sp2" };
    UnkObjectDef spF8 = { 59, func_80018554, 0, 0x1000, "options2.sp2" };
    UnkObjectDef spE4 = { 60, func_80018600, 0, 0x1000, "options2.sp2" };
    Vec4i spD4 = { 130, 130, 0, 0 };
    Vec4i spC4 = { 181, 74, 0, 0 };
    Vec4i spB4 = { 181, 91, 0, 0 };
    Vec4i spA4 = { 181, 105, 0, 0 };
    Vec4i sp94 = { 181, 121, 0, 0 };
    Vec4i sp84 = { 181, 136, 0, 0 };
    Vec4i sp74 = { 181, 151, 0, 0 };
    Vec4i sp64 = { 118, 166, 0, 0 };
    Vec4i sp54 = { 117, 181, 0, 0 };
    Vec4i sp44 = { 135, 198, 0, 0 };
    Vec4i sp34 = { 146, 228, 0, 0 };

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    asset_open_folder("/title/option", 0x2000);
    func_80014B60("bgopt", 0, 0, 0, 0, 1, 0x2000);
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;

    s0 = func_8002BBD4(&spD4, &sp1AC, 0x2000);

    v0 = func_8002BBD4(&spC4, &sp198, 0x2000);
    v0->unk_084 = D_8004C1E4 + 202;
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&spB4, &sp184, 0x2000);
    v0->unk_084 = D_8004C1D4 + 51;
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&spA4, &sp170, 0x2000);
    v0->unk_084 = D_8004C1D0 + 11;
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&sp94, &sp15C, 0x2000);
    v0->unk_084 = D_8004A428 + 7;
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&sp84, &sp148, 0x2000);
    v0->unk_084 = D_8004A448 / 3640 + 11;
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&sp74, &sp134, 0x2000);
    v0->unk_084 = D_8004A478 / 3640 + 11;
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&sp64, &sp120, 0x2000);
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&sp54, &sp10C, 0x2000);
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&sp44, &spF8, 0x2000);
    v0->unk_090[3] = s0;

    v0 = func_8002BBD4(&sp34, &spE4, 0x2000);
    v0->unk_090[3] = s0;

    func_80001D88();
    func_8002630C(0x2000);
}

void func_8000AFA4(Object *obj, s16 arg1) {
    s16 i;
    s16 q;

    q = D_80049B30[obj->unk_090[6]];
    for (i = 0; i < 8; i++) {
        if (D_800AA450[arg1][i] == q) {
            break;
        }
    }

    switch (i) {
        case 0:
            obj->unk_084 = 67;
            break;
        case 1:
            obj->unk_084 = 65;
            break;
        case 2:
            obj->unk_084 = 68;
            break;
        case 3:
            obj->unk_084 = 66;
            break;
        case 4:
            obj->unk_084 = 61;
            break;
        case 5:
            obj->unk_084 = 64;
            break;
        case 6:
            obj->unk_084 = 63;
            break;
        case 7:
            obj->unk_084 = 62;
            break;
    }
}

void func_8000B088(void) {
    Object *sp21C;
    Object *sp218;
    Object *v0;
    UnkObjectDef sp200 = { 90, NULL, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp1EC = { 70, func_80018974, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp1D8 = { 62, func_80018820, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp1C4 = { 63, func_80018820, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp1B0 = { 64, func_80018820, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp19C = { 66, func_80018820, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp188 = { 67, func_80018820, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp174 = { 68, func_80018820, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp160 = { 65, func_80018820, 0, 0x1000, "options2.sp2" };
    UnkObjectDef sp14C = { 60, func_800189CC, 0, 0x1000, "options2.sp2" };
    Vec4i sp13C = { 133, 126, 0, 0 };
    Vec4i sp12C = { 40, 82, 0, 0 };
    Vec4i sp11C = { 179, 82, 0, 0 };
    Vec4i sp10C = { 40, 96, 0, 0 };
    Vec4i spFC = { 179, 96, 0, 0 };
    Vec4i spEC = { 40, 110, 0, 0 };
    Vec4i spDC = { 179, 110, 0, 0 };
    Vec4i spCC = { 40, 124, 0, 0 };
    Vec4i spBC = { 179, 124, 0, 0 };
    Vec4i spAC = { 40, 138, 0, 0 };
    Vec4i sp9C = { 179, 138, 0, 0 };
    Vec4i sp8C = { 40, 152, 0, 0 };
    Vec4i sp7C = { 179, 152, 0, 0 };
    Vec4i sp6C = { 40, 166, 0, 0 };
    Vec4i sp5C = { 179, 166, 0, 0 };
    Vec4i sp4C = { 40, 180, 0, 0 };
    Vec4i sp3C = { 179, 180, 0, 0 };
    Vec4i sp2C = { 149, 224, 0, 0 };

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    asset_open_folder("/title/control", 0x2000);
    func_80014B60("bgcont", 0, 0, 0, 0, 1, 0x2000);
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;

    func_8002BBD4(&sp13C, &sp200, 0x2000);

    sp21C = func_8002BBD4(&sp12C, &sp1EC, 0x2000);
    sp21C->unk_090[3] = sp21C;
    sp21C->unk_090[6] = 0;
    func_8000AFA4(sp21C, 0);

    v0 = func_8002BBD4(&sp10C, &sp1D8, 0x2000);
    v0->unk_090[3] = sp21C;
    v0->unk_090[6] = 1;
    func_8000AFA4(v0, 0);

    v0 = func_8002BBD4(&spEC, &sp1C4, 0x2000);
    v0->unk_090[3] = sp21C;
    v0->unk_090[6] = 2;
    func_8000AFA4(v0, 0);

    v0 = func_8002BBD4(&spCC, &sp1B0, 0x2000);
    v0->unk_090[3] = sp21C;
    v0->unk_090[6] = 3;
    func_8000AFA4(v0, 0);

    v0 = func_8002BBD4(&spAC, &sp19C, 0x2000);
    v0->unk_090[3] = sp21C;
    v0->unk_090[6] = 4;
    func_8000AFA4(v0, 0);

    v0 = func_8002BBD4(&sp8C, &sp188, 0x2000);
    v0->unk_090[3] = sp21C;
    v0->unk_090[6] = 5;
    func_8000AFA4(v0, 0);

    v0 = func_8002BBD4(&sp6C, &sp174, 0x2000);
    v0->unk_090[3] = sp21C;
    v0->unk_090[6] = 6;
    func_8000AFA4(v0, 0);

    v0 = func_8002BBD4(&sp4C, &sp160, 0x2000);
    v0->unk_090[3] = sp21C;
    v0->unk_090[6] = 7;
    func_8000AFA4(v0, 0);

    sp218 = func_8002BBD4(&sp11C, &sp1EC, 0x2000);
    sp218->unk_090[3] = sp218;
    sp218->unk_090[6] = 0;
    sp218->unk_090[0] = 1;
    func_8000AFA4(sp218, 1);

    v0 = func_8002BBD4(&spFC, &sp1D8, 0x2000);
    v0->unk_090[3] = sp218;
    v0->unk_090[6] = 1;
    func_8000AFA4(v0, 1);

    v0 = func_8002BBD4(&spDC, &sp1C4, 0x2000);
    v0->unk_090[3] = sp218;
    v0->unk_090[6] = 2;
    func_8000AFA4(v0, 1);

    v0 = func_8002BBD4(&spBC, &sp1B0, 0x2000);
    v0->unk_090[3] = sp218;
    v0->unk_090[6] = 3;
    func_8000AFA4(v0, 1);

    v0 = func_8002BBD4(&sp9C, &sp19C, 0x2000);
    v0->unk_090[3] = sp218;
    v0->unk_090[6] = 4;
    func_8000AFA4(v0, 1);

    v0 = func_8002BBD4(&sp7C, &sp188, 0x2000);
    v0->unk_090[3] = sp218;
    v0->unk_090[6] = 5;
    func_8000AFA4(v0, 1);

    v0 = func_8002BBD4(&sp5C, &sp174, 0x2000);
    v0->unk_090[3] = sp218;
    v0->unk_090[6] = 6;
    func_8000AFA4(v0, 1);

    v0 = func_8002BBD4(&sp3C, &sp160, 0x2000);
    v0->unk_090[3] = sp218;
    v0->unk_090[6] = 7;
    func_8000AFA4(v0, 1);

    v0 = func_8002BBD4(&sp2C, &sp14C, 0x2000);
    v0->unk_090[0] = sp21C;
    v0->unk_090[1] = sp218;

    func_80001D88();
    func_8002630C(0x2000);
}

void func_8000B934(void) {
    UnkObjectDef sp3C = { 198, func_8001905C, 0, 0x1000, "options2.sp2" };
    Vec4i sp2C = { 133, 126, 0, 0 };

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    asset_open_folder("/title/rank", 0x2000);
    func_80014B60("bgrank", 0, 4, 0, 0, 1, 0x2000);
    D_80081460 = func_8002BBD4(&sp2C, &sp3C, 0x2000);
    func_80019278();
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;
    func_80001D88();
    func_8002630C(0x2000);
}

void func_8000BA4C(void) {
    func_8002630C(0);
    func_8002630C(1);
    func_8002630C(0xABAB);

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    asset_open_folder("/title/stats", 0x2000);
    func_80014B60("aarost", 0, 13, 0, 0, 1, 0x2000);
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;
    func_8002BB6C(func_80018AD0, 0x1000);
    func_80001D88();
    func_8002630C(0x2000);
}

static void nullsub(void) {
}

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
