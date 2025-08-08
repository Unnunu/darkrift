#include "common.h"
#include "camera.h"

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

extern s32 D_8008012C;
extern Object *D_80081460;
extern s16 D_80049B30[];
extern s16 D_8004C1D0;
extern s16 D_8004C1D4;
extern s16 D_8004C1E4;
extern u8 D_8004A428;
extern s32 gMusicVolume;
extern s32 gSoundVolume;
extern s8 D_80080129;
extern s16 D_80081250;
extern Texture *D_80081254;
extern s16 D_80080116;
extern s16 D_8005BED2;
extern Vec4i D_8004934C;
extern u16 D_8013C24C;

Object *func_8002BFF0(Vec4i *, s16, void (*)(Object *), UnkSam *);
void func_800199E0(Object *);
void sound_stop_one(s32, s32);
void func_80020670(Object *);
void func_80019F40(Object *);
void func_8001A158(Object *, s16);
s32 func_80019278(void); // TODO try to match if it returns void
void func_800052EC(s16 arg0);
void func_8001B5B0(char *, s32);
void func_80029630(void);
void func_8002DE20(Object *);
void task_default_func(Object *);
void func_8001905C(Object *);
void func_80018974(Object *);
void func_80018820(Object *);
void func_800189CC(Object *);
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
void func_80019A9C(Object *);
void func_8001A4FC(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006AE0.s")
void func_80006AE0(void);

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006C14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006CEC.s")

void func_80006E0C(Object *obj) {
    obj->vars[0]--;
    if (obj->vars[0] < 0) {
        obj->flags |= 0x10;
        D_8005BFC0 |= 1;
        obj->currentTask->flags |= 0x80;
        osViBlack(0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006E6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80006FB4.s")
void func_80006FB4(void);

void func_800070C0(void) {
    func_8002630C(0xABAB);
    func_8002630C(0x5000);
    func_8002630C(0x5001);
}

void func_800070F0(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg3", 0, 74, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    load_background("bg0", 0, 15, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void func_800071F0(Object *obj) {
    if (gPlayerInput[1].unk_02 & INP_CLEFT) {
        obj->rotation.y -= 10;
    } else if (gPlayerInput[1].unk_02 & INP_CRIGHT) {
        obj->rotation.y += 10;
    }
    func_80037E28(obj);
}

const char D_80053F14[] = "tc";

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007248.s")

void func_80007374(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg2", 0, -20, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    load_background("bg0", 0, 8, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void func_80007474(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg2", 0, 40, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    load_background("bg0", 0, -24, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void run_battle_mode(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg2", 0, 52, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    load_background("bg0", 0, 0, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void func_80007674(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg2", 0, 96, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;
    load_background("bg0", 0, 8, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void func_80007774(void) {
    s32 sp2C = D_800B6328[1].unk_06;

    func_80006FB4();
    load_background("bg2", 0, 94, 0x2000, 0x10000, 0, sp2C);
    load_background("bg0", 0, -8, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void func_80007868(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg2", 0, -7, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    load_background("bg0", 0, -64, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void func_80007968(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg2", 0, 20, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    load_background("bg0", 0, -24, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

void func_80007A68(void) {
    s32 sp2C = D_800B6328[1].unk_06;
    Texture *bg;

    func_80006FB4();
    bg = load_background("bg2", 0, -6, 0x2000, 0x10000, 0, sp2C);
    bg->height -= 16;

    load_background("bg0", 0, 4, 0x1000, 0x10000, 1, sp2C);

    func_8001B5B0("arena", sp2C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80006AE0();
    func_80001D88();
    func_800070C0();
}

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007B68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007DB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80007F4C.s")
void func_80007F4C(s32, s32, s32);

void func_800081A8(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/gore/goreint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("goreint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg3", 0, 74, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, 15, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_800082CC(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/aaro/aaroint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("aaroint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, 74, 0x10000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, 15, 0x8000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_800083EC(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/demi/demiint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("demiint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, -8, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, 8, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_80008510(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/demo/demoint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("demoint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, 32, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, -24, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_80008634(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/eve/eveint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("eveint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, 52, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, 0, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_80008758(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/morp/morpint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("morpint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, 96, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, 8, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_8000887C(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/niik/niikint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("niikint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, 94, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, -8, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_800089A0(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/scar/scarint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("scarint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, 0, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, -64, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_80008AC4(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/sono/sonoint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("sonoint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, 26, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, -24, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_80008BE8(void) {
    s32 temp_s0 = D_800B6328[1].unk_06;

    asset_open_folder("/zenm/zenmint", 0x3000);
    func_80007F4C(1, 0x70, 0x3000);
    D_80081254 = load_background("zenmint", 0, 250, 0, 0, 2, 0x3000);
    D_80081250 = D_80081254->height;
    load_background("bg2", 0, -6, 0x2000, 0x10000, 0, temp_s0);
    load_background("bg0", 0, 4, 0x1000, 0x10000, 1, temp_s0);
    func_8001B5B0("arena", temp_s0);
    func_80001D88();
    func_8002630C(0x3000);
    func_800070C0();
    if (D_80080230 != 30) {
        func_8002630C(temp_s0);
    }
}

void func_80008D0C(Object *obj) {
    if (D_800AA488->unk_00->unk_084 + 2 == D_800AA488->unk_90->unk_02) {
        D_8005BFC0 |= 1;
        obj->flags |= 0x10;
        gGameMode = GAME_MODE_LOGO;
    }
}

void func_80008D64(Object *obj) {
    obj->unk_084++;
    if (obj->unk_084 >= obj->model->unk_A08 - 1) {
        obj->unk_084 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008D98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80008FDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800092B0.s")

void func_80009480(void) {
    Object *worker;

    func_800263A8();
    asset_open_folder("/title/credit", 0x4000);
    D_80081254 = load_background("credit", 0, 250, 0, 0, 2, 0x4000);
    D_80081250 = D_80081254->height;
    worker = create_worker(func_8001A4FC, 0x1000);
    worker->vars[2] = 4;
    func_8001A158(worker, 0x4000);
    D_80080129 = FALSE;
    D_8005BFC0 |= 4;
    D_8008012C |= 0x20;
    func_80001D88();
    func_8002630C(0x4000);
}

void func_80009554(Object *obj) {
    if (gPlayerInput[D_8013C24C].unk_00 & INP_START) {
        D_8005BFC0 |= 1;
        obj->flags |= 0x10;
    }
}

void func_800095A8(void) {
    func_800263A8();
    asset_open_folder("/title/easywin", 0x4000);
    load_background("easyimg", 0, 0, 0, 0, 1, 0x4000);
    create_worker(func_80009554, 0x1000);
    D_80080129 = TRUE;
    D_8005BFC0 |= 4;
    D_8008012C |= 0x20;
    func_80001D88();
    func_8002630C(0x4000);
    gGameMode = GAME_MODE_36;
}

void func_8000965C(s32 arg0) {
    D_80080136 = D_8004BB48[arg0].unk_14;
    D_80080138 = D_8004BB48[arg0].unk_16;
    D_80080130 = D_8004BB48[arg0].unk_10;
    D_80080132 = D_8004BB48[arg0].unk_11;
    D_80080134 = D_8004BB48[arg0].unk_12;
    D_80080110 = D_8004BB48[arg0].unk_0C;
    D_80080112 = D_8004BB48[arg0].unk_0D;
    D_80080114 = D_8004BB48[arg0].unk_0E;
}

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800096D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_800099F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80009CE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_80009E8C.s")
/*extern s32 D_800801F0;
extern s32 D_80080234;
void func_80009E8C(void) {
    D_800801F0 = 1;
    D_80080234 = 1;
}*/

#pragma GLOBAL_ASM("asm/nonmatchings/76E0/func_8000A298.s")
void func_8000A298(void);

s32 D_800494C0[] = { 0, 0 };

void run_0_mode(void) {
    Object *v1;
    UIElement sp40 = { 83, func_80019A9C, 0, 0x1000, "options2.sp2" };
    Vec4i sp30 = { 164, 155, 0, 0 };

    func_800263A8();
    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    asset_open_folder("/title", 0x2000);
    load_background("dr_title", 0, 0, 0, 0, 1, CONTEXT_2000);
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;

    if (D_8005BED2 == 1) {
        UnkSam *assetData = gAssets[asset_find("title.k2", 0x2000)].aux_data;
        v1 = func_8002BFF0(&D_8004934C, 0x1000, func_800199E0, assetData);
        v1->flags |= 0x01000000;
    } else {
        v1 = create_ui_element(&sp30, &sp40, 0x2000);
    }

    v1->currentTask->counter = 30;

    create_worker(func_80020670, 0x1000);
    func_8000A298();
    func_80001D88();
    func_8002630C(0x2000);
    if (gGameMode != GAME_MODE_PLAYER_SELECTION) {
        func_8002630C(0xEEFF);
    }
}

void func_8000A514(Object *obj) {
    func_80002178(D_8005BEFC, 0);

    if (D_8005BEFC - 2 > 0) {
        D_8005BEFC -= 2;
        return;
    }

    obj->flags |= 0x10;
    D_80080116 = 0;
}

void func_8000A578(Object *obj) {
    UIElement sp44 = { 83, func_80019A9C, 0, 0x1000, "options2.sp2" };
    Vec4i sp34 = { 160, 155, 0, 0 };
    Object *v0;

    D_80080116 = 200;
    func_80002178(D_8005BEFC, NULL);

    if (D_8005BEFC + 32 < 255) {
        D_8005BEFC += 32;
        return;
    }

    sound_stop_one(0x2000, 8); // @bug wrong player id
    obj->fn_update = func_8000A514;
    load_background("dr_title", 0, 0, 0, 0, 1, CONTEXT_2000);
    v0 = create_ui_element(&sp34, &sp44, 0x2000);
    v0->currentTask->counter = 60;
    gCamera->pos.z = -2200;
    create_worker(func_80020670, 0x1000);
}

void run_intro_mode(void) {
    s32 unused;
    Object *v0;
    UIElement sp3C = { 83, func_80019A9C, 0, 0x1000, "options2.sp2" };
    Vec4i sp2C = { 160, 155, 0, 0 };

    D_80080129 = FALSE;
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;
    asset_open_folder("/title/tit_int", CONTEXT_2000);
    asset_open_folder("/plyrsel/plyrsel", CONTEXT_EEFF);
    v0 = create_worker(func_80019F40, 0x1000);
    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    func_8001A158(v0, 0x2000);

    D_80081254 = load_background("oplog", 0, 250, 0, 0x10000, 2, CONTEXT_2000);
    D_80081250 = D_80081254->height;

    func_8000A298();
    func_80001D88();
    func_8002630C(0x2000);
    if (gGameMode != GAME_MODE_PLAYER_SELECTION) {
        func_8002630C(0xEEFF);
    }
}

void func_8000A828(void) {
    asset_open_folder("/title/error", 0x2000);
    load_background("messpg", 0, 90, 0, 180, 1, CONTEXT_2000);
    func_80001D88();
}

void run_logo_mode(void) {
    func_800263A8();
    D_8005BFC0 |= 4;
    D_8008012C |= 0x20;
    D_8008012C |= 0x40;
    if (!gPlayerInput[0].enabled && !gPlayerInput[1].enabled) {
        func_8000A828();
    }

    asset_open_folder("/title/logo", 0x2000);
    load_background("vic", 0, 30, 0, 180, 1, CONTEXT_2000);
    load_background("n64lic", 0, 190, 0, 240, 1, CONTEXT_2000);
    create_worker(func_80019DE4, 0x1000);
    func_80001D88();
    func_8002630C(0x2000);
}

void run_1_mode(void) {
    Object *s0;
    Object *v0;
    UIElement sp1AC = { 89, func_80017F00, 0, 0x1000, "options2.sp2" };
    UIElement sp198 = { 203, func_80017F60, 0, 0x1000, "options2.sp2" };
    UIElement sp184 = { 53, func_80017FF4, 0, 0x1000, "options2.sp2" };
    UIElement sp170 = { 14, func_80018088, 0, 0x1000, "options2.sp2" };
    UIElement sp15C = { 7, func_80018120, 0, 0x1000, "options2.sp2" };
    UIElement sp148 = { 20, func_800181C8, 0, 0x1000, "options2.sp2" };
    UIElement sp134 = { 20, func_800182E0, 0, 0x1000, "options2.sp2" };
    UIElement sp120 = { 57, func_800183FC, 0, 0x1000, "options2.sp2" };
    UIElement sp10C = { 58, func_800184A8, 0, 0x1000, "options2.sp2" };
    UIElement spF8 = { 59, func_80018554, 0, 0x1000, "options2.sp2" };
    UIElement spE4 = { 60, func_80018600, 0, 0x1000, "options2.sp2" };
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
    load_background("bgopt", 0, 0, 0, 0, 1, CONTEXT_2000);
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;

    s0 = create_ui_element(&spD4, &sp1AC, 0x2000);

    v0 = create_ui_element(&spC4, &sp198, 0x2000);
    v0->unk_084 = D_8004C1E4 + 202;
    v0->vars[3] = s0;

    v0 = create_ui_element(&spB4, &sp184, 0x2000);
    v0->unk_084 = D_8004C1D4 + 51;
    v0->vars[3] = s0;

    v0 = create_ui_element(&spA4, &sp170, 0x2000);
    v0->unk_084 = D_8004C1D0 + 11;
    v0->vars[3] = s0;

    v0 = create_ui_element(&sp94, &sp15C, 0x2000);
    v0->unk_084 = D_8004A428 + 7;
    v0->vars[3] = s0;

    v0 = create_ui_element(&sp84, &sp148, 0x2000);
    v0->unk_084 = gMusicVolume / (0x8000 / 9) + 11;
    v0->vars[3] = s0;

    v0 = create_ui_element(&sp74, &sp134, 0x2000);
    v0->unk_084 = gSoundVolume / (0x8000 / 9) + 11;
    v0->vars[3] = s0;

    v0 = create_ui_element(&sp64, &sp120, 0x2000);
    v0->vars[3] = s0;

    v0 = create_ui_element(&sp54, &sp10C, 0x2000);
    v0->vars[3] = s0;

    v0 = create_ui_element(&sp44, &spF8, 0x2000);
    v0->vars[3] = s0;

    v0 = create_ui_element(&sp34, &spE4, 0x2000);
    v0->vars[3] = s0;

    func_80001D88();
    func_8002630C(0x2000);
}

void func_8000AFA4(Object *obj, s16 arg1) {
    s16 i;
    s16 q;

    q = D_80049B30[obj->vars[6]];
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

void run_2_mode(void) {
    Object *sp21C;
    Object *sp218;
    Object *v0;
    UIElement sp200 = { 90, NULL, 0, 0x1000, "options2.sp2" };
    UIElement sp1EC = { 70, func_80018974, 0, 0x1000, "options2.sp2" };
    UIElement sp1D8 = { 62, func_80018820, 0, 0x1000, "options2.sp2" };
    UIElement sp1C4 = { 63, func_80018820, 0, 0x1000, "options2.sp2" };
    UIElement sp1B0 = { 64, func_80018820, 0, 0x1000, "options2.sp2" };
    UIElement sp19C = { 66, func_80018820, 0, 0x1000, "options2.sp2" };
    UIElement sp188 = { 67, func_80018820, 0, 0x1000, "options2.sp2" };
    UIElement sp174 = { 68, func_80018820, 0, 0x1000, "options2.sp2" };
    UIElement sp160 = { 65, func_80018820, 0, 0x1000, "options2.sp2" };
    UIElement sp14C = { 60, func_800189CC, 0, 0x1000, "options2.sp2" };
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
    load_background("bgcont", 0, 0, 0, 0, 1, CONTEXT_2000);
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;

    create_ui_element(&sp13C, &sp200, 0x2000);

    sp21C = create_ui_element(&sp12C, &sp1EC, 0x2000);
    sp21C->vars[3] = sp21C;
    sp21C->vars[6] = 0;
    func_8000AFA4(sp21C, 0);

    v0 = create_ui_element(&sp10C, &sp1D8, 0x2000);
    v0->vars[3] = sp21C;
    v0->vars[6] = 1;
    func_8000AFA4(v0, 0);

    v0 = create_ui_element(&spEC, &sp1C4, 0x2000);
    v0->vars[3] = sp21C;
    v0->vars[6] = 2;
    func_8000AFA4(v0, 0);

    v0 = create_ui_element(&spCC, &sp1B0, 0x2000);
    v0->vars[3] = sp21C;
    v0->vars[6] = 3;
    func_8000AFA4(v0, 0);

    v0 = create_ui_element(&spAC, &sp19C, 0x2000);
    v0->vars[3] = sp21C;
    v0->vars[6] = 4;
    func_8000AFA4(v0, 0);

    v0 = create_ui_element(&sp8C, &sp188, 0x2000);
    v0->vars[3] = sp21C;
    v0->vars[6] = 5;
    func_8000AFA4(v0, 0);

    v0 = create_ui_element(&sp6C, &sp174, 0x2000);
    v0->vars[3] = sp21C;
    v0->vars[6] = 6;
    func_8000AFA4(v0, 0);

    v0 = create_ui_element(&sp4C, &sp160, 0x2000);
    v0->vars[3] = sp21C;
    v0->vars[6] = 7;
    func_8000AFA4(v0, 0);

    sp218 = create_ui_element(&sp11C, &sp1EC, 0x2000);
    sp218->vars[3] = sp218;
    sp218->vars[6] = 0;
    sp218->vars[0] = 1;
    func_8000AFA4(sp218, 1);

    v0 = create_ui_element(&spFC, &sp1D8, 0x2000);
    v0->vars[3] = sp218;
    v0->vars[6] = 1;
    func_8000AFA4(v0, 1);

    v0 = create_ui_element(&spDC, &sp1C4, 0x2000);
    v0->vars[3] = sp218;
    v0->vars[6] = 2;
    func_8000AFA4(v0, 1);

    v0 = create_ui_element(&spBC, &sp1B0, 0x2000);
    v0->vars[3] = sp218;
    v0->vars[6] = 3;
    func_8000AFA4(v0, 1);

    v0 = create_ui_element(&sp9C, &sp19C, 0x2000);
    v0->vars[3] = sp218;
    v0->vars[6] = 4;
    func_8000AFA4(v0, 1);

    v0 = create_ui_element(&sp7C, &sp188, 0x2000);
    v0->vars[3] = sp218;
    v0->vars[6] = 5;
    func_8000AFA4(v0, 1);

    v0 = create_ui_element(&sp5C, &sp174, 0x2000);
    v0->vars[3] = sp218;
    v0->vars[6] = 6;
    func_8000AFA4(v0, 1);

    v0 = create_ui_element(&sp3C, &sp160, 0x2000);
    v0->vars[3] = sp218;
    v0->vars[6] = 7;
    func_8000AFA4(v0, 1);

    v0 = create_ui_element(&sp2C, &sp14C, 0x2000);
    v0->vars[0] = sp21C;
    v0->vars[1] = sp218;

    func_80001D88();
    func_8002630C(0x2000);
}

void run_3_mode(void) {
    UIElement sp3C = { 198, func_8001905C, 0, 0x1000, "options2.sp2" };
    Vec4i sp2C = { 133, 126, 0, 0 };

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    asset_open_folder("/title/rank", 0x2000);
    load_background("bgrank", 0, 4, 0, 0, 1, CONTEXT_2000);
    D_80081460 = create_ui_element(&sp2C, &sp3C, 0x2000);
    func_80019278();
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;
    func_80001D88();
    func_8002630C(0x2000);
}

void run_4_mode(void) {
    func_8002630C(0);
    func_8002630C(1);
    func_8002630C(0xABAB);

    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = TRUE;
    asset_open_folder("/title/stats", 0x2000);
    load_background("aarost", 0, 13, 0, 0, 1, CONTEXT_2000);
    D_8008012C |= 0x20;
    D_8005BFC0 |= 4;
    create_worker(func_80018AD0, 0x1000);
    func_80001D88();
    func_8002630C(0x2000);
}

static void nullsub(void) {
}

void run_17_mode(void) {
    s32 unused;
    UnkObjDef2 sp74 = { 0x0000FE70, 0 };
    UnkObjDef3 sp64 = { 0xFFFFFE70, 0, 0, 0 };
    UnkObjDef3 sp54 = { 400, 0, 0, 0 };
    s32 unused2;
    s32 sp4C = D_800B6328[1].unk_06;
    UnkObjDef4 sp3C = { "gore", task_default_func, 0x1000, 0 };
    UnkObjDef4 sp2C = { "arena", task_default_func, 0x1000, 0 };

    asset_open_folder("/bars", 0xABAB);
    func_800052EC(0);
    func_800052EC(1);
    load_background("bg2", 0, 74, 0x2000, 0x10000, 0, sp4C);
    load_background("bg0", 0, 15, 0x1000, 0x10000, 1, sp4C);
    func_8001B5B0("arena", sp4C);
    func_80029630();

    gCamera->currentTask->counter = 0;
    gCamera->currentTask->flags = 1;
    gCamera->currentTask->func = func_8002DE20;
    gCamera->currentTask->stackPos = 0;

    func_80001D88();
}
