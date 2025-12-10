#include "common.h"

// R_CBUTTONS, L_CBUTTONS, D_CBUTTONS, U_CBUTTONS
s32 D_8004A4F0[] = {
    0,
    0x20, // R_CBUTTONS
    0x80, // L_CBUTTONS
    0xA0, // R_CBUTTONS + L_CBUTTONS
    0x40, // D_CBUTTONS
    0x60, // D_CBUTTONS + R_CBUTTONS
    0xC0, // D_CBUTTONS + L_CBUTTONS
    0xE0, // D_CBUTTONS + L_CBUTTONS + R_CBUTTONS
    0x10, // U_CBUTTONS
    0x30, // U_CBUTTONS + R_CBUTTONS
    0x90, // U_CBUTTONS + L_CBUTTONS
    0xB0, // U_CBUTTONS + L_CBUTTONS + R_CBUTTONS
    0x50, // U_CBUTTONS + D_CBUTTONS
    0x70, // U_CBUTTONS + D_CBUTTONS + R_CBUTTONS
    0xD0, // U_CBUTTONS + D_CBUTTONS + L_CBUTTONS
    0xF0  // U_CBUTTONS + D_CBUTTONS + L_CBUTTONS + R_CBUTTONS
};

// R_TRIG, L_TRIG
s32 D_8004A530[] = { 0,
                     INP_R,         // R_TRIG
                     INP_L,         // L_TRIG
                     INP_L | INP_R, // R_TRIG + L_TRIG
                     0,
                     0,
                     0,
                     0,
                     0 };

// R_JPAD, L_JPAD, D_JPAD, U_JPAD
s32 D_8004A554[] = {
    0,
    INP_RIGHT,                       // R_JPAD
    INP_LEFT,                        // L_JPAD
    INP_RIGHT | INP_LEFT,            // R_JPAD + L_JPAD
    INP_DOWN,                        // D_JPAD
    INP_RIGHT | INP_DOWN,            // R_JPAD + D_JPAD
    INP_DOWN | INP_LEFT,             // L_JPAD + D_JPAD
    INP_RIGHT | INP_DOWN | INP_LEFT, // R_JPAD + L_JPAD + D_JPAD
    INP_UP,                          // U_JPAD
    INP_UP | INP_RIGHT,              // R_JPAD + U_JPAD
    INP_UP | INP_LEFT                // L_JPAD + U_JPAD
};
// START_BUTTON, Z_TRIG, B_BUTTON, A_BUTTON
s32 D_8004A580[] = {
    0,
    INP_START,             // START_BUTTON
    INP_L,                 // Z_TRIG
    INP_ZTRIG | INP_START, // START_BUTTON + Z_TRIG
    INP_B,                 // B_BUTTON
    0,                     // START_BUTTON + B_BUTTON
    INP_ZTRIG | INP_B,     // Z_TRIG + B_BUTTON
    0,                     // START_BUTTON + Z_TRIG + B_BUTTON
    INP_A,                 // A_BUTTON
    0,                     // START_BUTTON + A_BUTTON
    INP_ZTRIG | INP_A,     // Z_TRIG + A_BUTTON
    0,                     // START_BUTTON + Z_TRIG + A_BUTTON
    INP_B | INP_A,         // B_BUTTON + A_BUTTON
    0,                     // START_BUTTON + B_BUTTON + A_BUTTON
    0,                     // Z_TRIG + B_BUTTON + A_BUTTON
    0                      // START_BUTTON + Z_TRIG + B_BUTTON + A_BUTTON
};

PlayerInput gPlayerInput[2];

u16 func_800249B0(u16 contId, u16 buttons) {
    u16 i;
    u16 mask;
    u16 v1;
    u16 *ptr = D_800AA450[contId];

    mask = 1;
    v1 = 0;

    for (i = 0; i < 8; i++) {
        if (mask & buttons) {
            v1 |= ptr[i];
        }
        mask <<= 1;
    }

    return v1 | (buttons & 0xFF00);
}

void func_80024A38(u16 contId) {
    s32 i;
    s32 mask;
    u16 *ptr = D_800AA450[contId];

    mask = 1;
    for (i = 0; i < 8; i++) {
        ptr[i] = mask;
        mask <<= 1;
    }
}

#ifdef NON_EQUIVALENT
void func_80024A90(s16 contId) {
    OSContPad *contData;
    u16 v1;
    u16 buttons;
    u16 v0;
    PlayerInput *ua;

    contData = gContData[contId];
    v1 = contData->button;

    buttons = D_8004A4F0[v1 & 0xF];
    buttons |= D_8004A530[(v1 >> 4) & 0xF] | D_8004A554[(v1 >> 8) & 0xF] | D_8004A580[(v1 >> 12) & 0xF];

    if (!gPlayerInput[contId].unk_0D && !(buttons & 0xF000)) {
        if (contData->stick_x > 40) {
            buttons |= INP_RIGHT;
        } else if (contData->stick_x < -40) {
            buttons |= INP_LEFT;
        }

        if (contData->stick_y > 40) {
            buttons |= INP_UP;
        } else if (contData->stick_y < -40) {
            buttons |= INP_DOWN;
        }
    }

    gPlayerInput[contId].raw_buttons = buttons;

    if (gPlayerInput[contId].unk_0C) {
        buttons = func_800249B0(contId, buttons);
    }

    if (gPlayerInput[contId].mirrored) {
        v0 = buttons;
        buttons &= 0x5FFF;
        if (v0 & INP_LEFT) {
            buttons |= INP_RIGHT;
        }
        if (v0 & INP_RIGHT) {
            buttons |= INP_LEFT;
        }
    }

    if (!gPlayerInput[contId].accumulated) {
        gPlayerInput[contId].held_buttons = gPlayerInput[contId].prev_buttons;
    } else {
        gPlayerInput[contId].held_buttons &= gPlayerInput[contId].prev_buttons;
    }

    gPlayerInput[contId].buttons =
        buttons & (~gPlayerInput[contId].prev_buttons | ~0x9FF | ~gPlayerInput[contId].held_buttons);

    if (buttons != gPlayerInput[contId].prev_buttons || (buttons & 0xE020) && !(buttons & 0xD0)) {
        gPlayerInput[contId].accumulated = TRUE;
    }

    gPlayerInput[contId].prev_buttons = buttons;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/input/func_80024A90.s")
void func_80024A90(s16 arg0);
#endif

void input_update(void) {
    gFrameCounter++;
    cont_read();

    if (gPlayerInput[PLAYER_1].enabled && gPlayerInput[PLAYER_1].connected) {
        func_80024A90(PLAYER_1);
    } else {
        gPlayerInput[PLAYER_1].buttons = 0;
    }

    if (gPlayerInput[PLAYER_2].enabled && gPlayerInput[PLAYER_2].connected) {
        func_80024A90(PLAYER_2);
    } else {
        gPlayerInput[PLAYER_2].buttons = 0;
    }
}

void func_80024D2C(void) {
    gPlayerInput[0].accumulated = gPlayerInput[1].accumulated = FALSE;
    gPlayerInput[0].buttons = gPlayerInput[1].buttons = 0;
    gPlayerInput[0].mirrored = gPlayerInput[1].mirrored = FALSE;
    gPlayerInput[1].enabled = gPlayerInput[0].enabled = TRUE;
    gPlayerInput[1].prev_buttons = gPlayerInput[0].prev_buttons = 0;
    gPlayerInput[1].unk_0C = gPlayerInput[0].unk_0C = TRUE;
    gPlayerInput[0].unk_0D = gPlayerInput[1].unk_0D = FALSE;
}
