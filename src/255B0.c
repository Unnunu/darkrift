#include "common.h"

extern u16 D_800AA450[][8];
extern OSContPad *gContData[MAXCONTROLLERS];

extern s32 D_800492AC;
extern s32 D_8004A4F0[];
extern s32 D_8004A530[];
extern s32 D_8004A554[];
extern s32 D_8004A580[];

void cont_read(void);

u16 func_800249B0(u16 arg0, u16 arg1) {
    u16 i;
    u16 mask;
    u16 v1;
    u16 *ptr = D_800AA450[arg0];

    mask = 1;
    v1 = 0;

    for (i = 0; i < 8; i++) {
        if (mask & arg1) {
            v1 |= ptr[i];
        }
        mask <<= 1;
    }

    return v1 | (arg1 & 0xFF00);
}

void func_80024A38(u16 arg0) {
    s32 i;
    s32 mask;
    u16 *ptr = D_800AA450[arg0];

    mask = 1;
    for (i = 0; i < 8; i++) {
        ptr[i] = mask;
        mask <<= 1;
    }
}

#ifdef NON_EQUIVALENT
void func_80024A90(s16 arg0) {
    OSContPad *contData;
    u16 v1;
    u16 buttons;
    u16 v0;
    UnkAlpha *ua;
    s32 temp;

    contData = gContData[arg0];
    v1 = contData->button;
    temp = D_8004A4F0[v1 & 0xF];
    buttons = temp;
    buttons |= D_8004A530[(v1 >> 4) & 0xF] | D_8004A554[(v1 >> 8) & 0xF] | D_8004A580[(v1 >> 12) & 0xF];

    if (D_800AA430[arg0].unk_0D == 0 && !(buttons & 0xF000)) {
        if (contData->stick_x > 40) {
            buttons |= 0x2000;
        } else if (contData->stick_x < -40) {
            buttons |= 0x8000;
        }

        if (contData->stick_y > 40) {
            buttons |= 0x1000;
        } else if (contData->stick_y < -40) {
            buttons |= 0x4000;
        }
    }

    D_800AA430[arg0].unk_06 = buttons;

    if (D_800AA430[arg0].unk_0C != 0) {
        buttons = func_800249B0(arg0, buttons);
    }

    if (D_800AA430[arg0].unk_09) {
        v0 = buttons;
        buttons &= 0x5FFF;
        if (v0 & 0x8000) {
            buttons |= 0x2000;
        }
        if (v0 & 0x2000) {
            buttons |= 0x8000;
        }
    }

    if (D_800AA430[arg0].unk_08 == 0) {
        D_800AA430[arg0].unk_04 = D_800AA430[arg0].unk_02;
    } else {
        D_800AA430[arg0].unk_04 &= D_800AA430[arg0].unk_02;
    }

    D_800AA430[arg0].unk_00 = buttons & (~D_800AA430[arg0].unk_02 | ~0x9FF | ~D_800AA430[arg0].unk_04);

    if (buttons != D_800AA430[arg0].unk_02 || (buttons & 0xE020) && !(buttons & 0xD0)) {
        D_800AA430[arg0].unk_08 = TRUE;
    }

    D_800AA430[arg0].unk_02 = buttons;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/255B0/func_80024A90.s")
void func_80024A90(s16 arg0);
#endif

void func_80024C98(void) {
    D_800492AC++;
    cont_read();

    if (D_800AA430[0].unk_0A && D_800AA430[0].unk_0B) {
        func_80024A90(0);
    } else {
        D_800AA430[0].unk_00 = 0;
    }

    if (D_800AA430[1].unk_0A && D_800AA430[1].unk_0B) {
        func_80024A90(1);
    } else {
        D_800AA430[1].unk_00 = 0;
    }
}

void func_80024D2C(void) {
    D_800AA430[0].unk_08 = D_800AA430[1].unk_08 = 0;
    D_800AA430[0].unk_00 = D_800AA430[1].unk_00 = 0;
    D_800AA430[0].unk_09 = D_800AA430[1].unk_09 = 0;
    D_800AA430[1].unk_0A = D_800AA430[0].unk_0A = 1;
    D_800AA430[1].unk_02 = D_800AA430[0].unk_02 = 0;
    D_800AA430[1].unk_0C = D_800AA430[0].unk_0C = 1;
    D_800AA430[0].unk_0D = D_800AA430[1].unk_0D = 0;
}
