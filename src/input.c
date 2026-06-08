#include "common.h"

// R_CBUTTONS, L_CBUTTONS, D_CBUTTONS, U_CBUTTONS
s32 D_8004A4F0[] = {
    0,
    x_37f8540c,                                       // R_CBUTTONS
    x_ffe9ce36,                                       // L_CBUTTONS
    x_37f8540c | x_ffe9ce36,                          // R_CBUTTONS + L_CBUTTONS
    x_b2ae561b,                                       // D_CBUTTONS
    x_b2ae561b | x_37f8540c,                          // D_CBUTTONS + R_CBUTTONS
    x_b2ae561b | x_ffe9ce36,                          // D_CBUTTONS + L_CBUTTONS
    x_b2ae561b | x_ffe9ce36 | x_37f8540c,             // D_CBUTTONS + L_CBUTTONS + R_CBUTTONS
    x_84d0a51b,                                       // U_CBUTTONS
    x_84d0a51b | x_37f8540c,                          // U_CBUTTONS + R_CBUTTONS
    x_84d0a51b | x_ffe9ce36,                          // U_CBUTTONS + L_CBUTTONS
    x_84d0a51b | x_37f8540c | x_ffe9ce36,             // U_CBUTTONS + L_CBUTTONS + R_CBUTTONS
    x_84d0a51b | x_b2ae561b,                          // U_CBUTTONS + D_CBUTTONS
    x_84d0a51b | x_b2ae561b | x_37f8540c,             // U_CBUTTONS + D_CBUTTONS + R_CBUTTONS
    x_84d0a51b | x_b2ae561b | x_ffe9ce36,             // U_CBUTTONS + D_CBUTTONS + L_CBUTTONS
    x_84d0a51b | x_b2ae561b | x_37f8540c | x_ffe9ce36 // U_CBUTTONS + D_CBUTTONS + L_CBUTTONS + R_CBUTTONS
};

// R_TRIG, L_TRIG
s32 D_8004A530[] = { 0,
                     x_64a28e7d,              // R_TRIG
                     x_af0e0a9f,              // L_TRIG
                     x_af0e0a9f | x_64a28e7d, // R_TRIG + L_TRIG
                     0,
                     0,
                     0,
                     0,
                     0 };

// R_JPAD, L_JPAD, D_JPAD, U_JPAD
s32 D_8004A554[] = {
    0,
    x_fc4a9735,                           // R_JPAD
    x_ad1aebe6,                           // L_JPAD
    x_fc4a9735 | x_ad1aebe6,              // R_JPAD + L_JPAD
    x_b8c91680,                           // D_JPAD
    x_fc4a9735 | x_b8c91680,              // R_JPAD + D_JPAD
    x_b8c91680 | x_ad1aebe6,              // L_JPAD + D_JPAD
    x_fc4a9735 | x_b8c91680 | x_ad1aebe6, // R_JPAD + L_JPAD + D_JPAD
    x_f7763ed8,                           // U_JPAD
    x_f7763ed8 | x_fc4a9735,              // R_JPAD + U_JPAD
    x_f7763ed8 | x_ad1aebe6               // L_JPAD + U_JPAD
};
// START_BUTTON, Z_TRIG, B_BUTTON, A_BUTTON
s32 D_8004A580[] = {
    0,
    x_9cefe76c,              // START_BUTTON
    x_af0e0a9f,              // Z_TRIG
    x_1c9950cc | x_9cefe76c, // START_BUTTON + Z_TRIG
    x_c7089780,              // B_BUTTON
    0,                       // START_BUTTON + B_BUTTON
    x_1c9950cc | x_c7089780, // Z_TRIG + B_BUTTON
    0,                       // START_BUTTON + Z_TRIG + B_BUTTON
    x_29dbff14,              // A_BUTTON
    0,                       // START_BUTTON + A_BUTTON
    x_1c9950cc | x_29dbff14, // Z_TRIG + A_BUTTON
    0,                       // START_BUTTON + Z_TRIG + A_BUTTON
    x_c7089780 | x_29dbff14, // B_BUTTON + A_BUTTON
    0,                       // START_BUTTON + B_BUTTON + A_BUTTON
    0,                       // Z_TRIG + B_BUTTON + A_BUTTON
    0                        // START_BUTTON + Z_TRIG + B_BUTTON + A_BUTTON
};

x_23580eef x_59ce598c[2];
u16 x_013307ec[2][8];

u16 x_90d8784d(u16 x_1b94c75c, u16 buttons) {
    u16 i;
    u16 mask;
    u16 v1;
    u16 *ptr = x_013307ec[x_1b94c75c];

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

void x_15468514(u16 x_1b94c75c) {
    s32 i;
    s32 mask;
    u16 *ptr = x_013307ec[x_1b94c75c];

    mask = 1;
    for (i = 0; i < 8; i++) {
        ptr[i] = mask;
        mask <<= 1;
    }
}

#ifdef NON_MATCHING
void x_d523d906(s16 x_1b94c75c) {
    s32 temp;
    u16 v1;
    u16 buttons;
    u16 v0;

    v1 = x_f72c20e6[x_1b94c75c]->button;
    buttons = D_8004A4F0[v1 & 0xF];
    buttons |= D_8004A530[(v1 >> 4) & 0xF];
    buttons |= D_8004A554[(v1 >> 8) & 0xF];
    buttons |= D_8004A580[(v1 >> 12) & 0xF];

    if (!(x_59ce598c + x_1b94c75c)->x_40ccbb76 && !(buttons & x_0684c746)) {
        if (x_f72c20e6[x_1b94c75c]->stick_x > 40) {
            buttons |= x_fc4a9735;
        } else if (x_f72c20e6[x_1b94c75c]->stick_x < -40) {
            buttons |= x_ad1aebe6;
        }

        if (x_f72c20e6[x_1b94c75c]->stick_y > 40) {
            buttons |= x_f7763ed8;
        } else if (x_f72c20e6[x_1b94c75c]->stick_y < -40) {
            buttons |= x_b8c91680;
        }
    }

    (x_59ce598c + x_1b94c75c)->x_f3756179 = buttons;

    if ((x_59ce598c + x_1b94c75c)->x_3fb684fe) {
        buttons = x_90d8784d(x_1b94c75c, buttons);
    }

    if (x_59ce598c[x_1b94c75c].x_d93bcabf) {
        v0 = buttons;
        buttons = buttons & 0x5FFF;
        if (buttons) {}
        if (v0 & x_ad1aebe6) {
            buttons |= x_fc4a9735;
        }
        if (v0 & x_fc4a9735) {
            buttons |= x_ad1aebe6;
        }
    }

    if (!x_59ce598c[x_1b94c75c].x_c4397934) {
        x_59ce598c[x_1b94c75c].x_245d87f4 = x_59ce598c[x_1b94c75c].x_33260da8;
    } else {
        x_59ce598c[x_1b94c75c].x_245d87f4 = x_59ce598c[x_1b94c75c].x_245d87f4 & x_59ce598c[x_1b94c75c].x_33260da8;
    }

    temp = ~(x_9cefe76c | x_1c9950cc | x_ffe9ce36 | x_b2ae561b | x_84d0a51b | x_c7089780 | x_64a28e7d | x_af0e0a9f);
    temp |= (u16) ~x_59ce598c[x_1b94c75c].x_33260da8;
    temp |= (u16) ~x_59ce598c[x_1b94c75c].x_245d87f4;

    x_59ce598c[x_1b94c75c].buttons = temp & buttons;
    v0 = x_59ce598c[x_1b94c75c].x_33260da8;
    if (buttons != v0 || (buttons & (x_37f8540c | x_ad1aebe6 | x_b8c91680 | x_fc4a9735)) &&
                             !(buttons & (x_ffe9ce36 | x_b2ae561b | x_84d0a51b))) {
        x_59ce598c[x_1b94c75c].x_c4397934 = TRUE;
    }

    x_59ce598c[x_1b94c75c].x_33260da8 = buttons;
    do { } while (0); }
#else
#pragma GLOBAL_ASM("asm/nonmatchings/input/x_d523d906.s")
void x_d523d906(s16 x_cc1d0de5);
#endif

void x_0dd43bb1(void) {
    x_e3a9f332++;
    x_bb61051c();

    if (x_59ce598c[x_83106b21].enabled && x_59ce598c[x_83106b21].x_12a7bd86) {
        x_d523d906(x_83106b21);
    } else {
        x_59ce598c[x_83106b21].buttons = 0;
    }

    if (x_59ce598c[x_6f0b3be3].enabled && x_59ce598c[x_6f0b3be3].x_12a7bd86) {
        x_d523d906(x_6f0b3be3);
    } else {
        x_59ce598c[x_6f0b3be3].buttons = 0;
    }
}

void x_14384217(void) {
    x_59ce598c[x_83106b21].x_c4397934 = x_59ce598c[x_6f0b3be3].x_c4397934 = FALSE;
    x_59ce598c[x_83106b21].buttons = x_59ce598c[x_6f0b3be3].buttons = 0;
    x_59ce598c[x_83106b21].x_d93bcabf = x_59ce598c[x_6f0b3be3].x_d93bcabf = FALSE;
    x_59ce598c[x_6f0b3be3].enabled = x_59ce598c[x_83106b21].enabled = TRUE;
    x_59ce598c[x_6f0b3be3].x_33260da8 = x_59ce598c[x_83106b21].x_33260da8 = 0;
    x_59ce598c[x_6f0b3be3].x_3fb684fe = x_59ce598c[x_83106b21].x_3fb684fe = TRUE;
    x_59ce598c[x_83106b21].x_40ccbb76 = x_59ce598c[x_6f0b3be3].x_40ccbb76 = FALSE;
}
