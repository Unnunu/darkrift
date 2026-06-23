#include "common.h"

/* Input subsystem: per-frame controller reading, button decoding from raw
   hardware format, remapping, mirroring, and edge/level-triggered dispatch. */

/* Decode raw C-button nibble (bits 0-3) → INP_* flags.  The raw controller
   packs one group of buttons per nibble; these four tables unpack them. */
s32 sCButtonDecode[] = {
    0,
    INP_CRIGHT,                                  // R_CBUTTONS
    INP_CLEFT,                                   // L_CBUTTONS
    INP_CRIGHT | INP_CLEFT,                      // R_CBUTTONS + L_CBUTTONS
    INP_CDOWN,                                   // D_CBUTTONS
    INP_CDOWN | INP_CRIGHT,                      // D_CBUTTONS + R_CBUTTONS
    INP_CDOWN | INP_CLEFT,                       // D_CBUTTONS + L_CBUTTONS
    INP_CDOWN | INP_CLEFT | INP_CRIGHT,          // D_CBUTTONS + L_CBUTTONS + R_CBUTTONS
    INP_CUP,                                     // U_CBUTTONS
    INP_CUP | INP_CRIGHT,                        // U_CBUTTONS + R_CBUTTONS
    INP_CUP | INP_CLEFT,                         // U_CBUTTONS + L_CBUTTONS
    INP_CUP | INP_CRIGHT | INP_CLEFT,            // U_CBUTTONS + L_CBUTTONS + R_CBUTTONS
    INP_CUP | INP_CDOWN,                         // U_CBUTTONS + D_CBUTTONS
    INP_CUP | INP_CDOWN | INP_CRIGHT,            // U_CBUTTONS + D_CBUTTONS + R_CBUTTONS
    INP_CUP | INP_CDOWN | INP_CLEFT,             // U_CBUTTONS + D_CBUTTONS + L_CBUTTONS
    INP_CUP | INP_CDOWN | INP_CRIGHT | INP_CLEFT // U_CBUTTONS + D_CBUTTONS + L_CBUTTONS + R_CBUTTONS
};

/* Decode raw trigger nibble (bits 4-7) → L/R_INP flags. */
s32 sTriggerDecode[] = { 0,
                         INP_R,         // R_TRIG
                         INP_L,         // L_TRIG
                         INP_L | INP_R, // R_TRIG + L_TRIG
                         0,
                         0,
                         0,
                         0,
                         0 };

/* Decode raw D-pad nibble (bits 8-11) → INP_* direction flags. */
s32 sDPadDecode[] = {
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
/* Decode raw action-button nibble (bits 12-15) → START/Z/B/A flags. */
s32 sActionDecode[] = {
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
u16 gButtonsMap[2][8];

/* Remap already-decoded INP_* buttons through the per-controller
   gButtonsMap.  Low byte (bits 0-7: L, A, R, B, CUP, CRIGHT, CDOWN, CLEFT)
   is remappable — gButtonsMap[bit] → remapped INP_* value.  High byte
   (bits 8-15: Z, START, D-pad directions) passes through unchanged. */
u16 remap_buttons(u16 contId, u16 buttons) {
    u16 i;
    u16 mask;
    u16 v1;
    u16 *ptr = gButtonsMap[contId];

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

/* Initialise gButtonsMap for a controller to identity mapping
   (bit 0→bit 0, bit 1→bit 1, etc.).  Called at startup before
   the user's custom mapping is loaded. */
void init_button_map(u16 contId) {
    s32 i;
    s32 mask;
    u16 *ptr = gButtonsMap[contId];

    mask = 1;
    for (i = 0; i < 8; i++) {
        ptr[i] = mask;
        mask <<= 1;
    }
}

/*
 * Per-player, per-frame input processing pipeline:
 *
 *   1. Raw decode  — the N64 controller packs buttons into a 16-bit word
 *      organised as four 4-bit nibbles (C-buttons, triggers, D-pad, action).
 *      Each nibble is expanded through a lookup table into INP_* flags.
 *
 *   2. Analog stick  — if stick is enabled and no D-pad direction is held,
 *      read the stick axes (threshold ±40) and synthesise D-pad INP_* flags.
 *
 *   3. Remapping   — if this controller has a custom button map, translate
 *      the low byte (bits 0-7: L, A, R, B, all C-buttons) through
 *      gButtonsMap[].  High byte (Z, START, D-pad directions) is fixed.
 *
 *   4. Mirroring   — if the player is on the right (P2) side, swap LEFT↔RIGHT
 *      so that "toward opponent" / "away from opponent" is consistent.
 *
 *   5. Background mask — «what was already held before this press sequence».
 *      When pendingInput is FALSE (new sequence starting), background is
 *      snapshotted from fullState.  When pendingInput is TRUE (ongoing
 *      sequence), background is ANDed with fullState each frame so that
 *      released buttons drop out — but NEWLY pressed buttons are NOT added
 *      (background = snapshot of what came BEFORE, not what's new).
 *
 *   6. Edge detect — the output buttons field combines:
 *      - Level-triggered pass-through for directions, A, and CRIGHT (always
 *        appear in output regardless of previous state).
 *      - Edge-triggered detection for all other buttons: a button is
 *        reported only if it's NOT in fullState (wasn't held last frame)
 *        AND NOT in background (wasn't already held before this sequence).
 *        This prevents buttons that were held before the current action
 *        started from re-triggering every frame.
 *
 *   7. pendingInput  — set TRUE whenever the button state changes OR when
 *      a D-pad direction (or CRIGHT) is actively held (except when C-left,
 *      C-down, or C-up are also held — those exclude the repeat).  This
 *      signal tells the rest of the engine to re-evaluate transitions.
 */
#ifdef NON_MATCHING
void process_player_input(s16 contId) {
    s32 newPressMask;
    u16 rawButtons;
    u16 buttons;
    u16 prevFullState;

    // 1. Decode raw controller nibbles into INP_* flags
    rawButtons = gContData[contId]->button;
    buttons = sCButtonDecode[rawButtons & 0xF];
    buttons |= sTriggerDecode[(rawButtons >> 4) & 0xF];
    buttons |= sDPadDecode[(rawButtons >> 8) & 0xF];
    buttons |= sActionDecode[(rawButtons >> 12) & 0xF];

    // 2. Analog stick → D-pad (only when no D-pad direction is held)
    if (!(gPlayerInput + contId)->stickDisabled && !(buttons & INP_DIRECTION)) {
        if (gContData[contId]->stick_x > 40) {
            buttons |= INP_RIGHT;
        } else if (gContData[contId]->stick_x < -40) {
            buttons |= INP_LEFT;
        }

        if (gContData[contId]->stick_y > 40) {
            buttons |= INP_UP;
        } else if (gContData[contId]->stick_y < -40) {
            buttons |= INP_DOWN;
        }
    }

    // 3. Store raw (un-remapped) snapshot for reference
    (gPlayerInput + contId)->rawButtons = buttons;

    // 4. Apply user button remapping
    if ((gPlayerInput + contId)->remapped) {
        buttons = remap_buttons(contId, buttons);
    }

    // 5. Mirror LEFT ↔ RIGHT so P2's "toward opponent" is always RIGHT
    if (gPlayerInput[contId].mirrored) {
        prevFullState = buttons;
        buttons = buttons & 0x5FFF;
        if (buttons) {}
        if (prevFullState & INP_LEFT) {
            buttons |= INP_RIGHT;
        }
        if (prevFullState & INP_RIGHT) {
            buttons |= INP_LEFT;
        }
    }

    // 6. Background mask: snapshot of what was held BEFORE this sequence
    if (!gPlayerInput[contId].pendingInput) {
        // new sequence starts — freeze the background
        gPlayerInput[contId].background = gPlayerInput[contId].fullState;
    } else {
        // ongoing sequence — drop released buttons, do NOT add new ones
        gPlayerInput[contId].background = gPlayerInput[contId].background & gPlayerInput[contId].fullState;
    }

    // 7. Edge-detect new presses.
    // BUG (original code): `|= ~fullState` and `|= ~background` should be
    // `&= ~fullState` / `&= ~background`.  With `|` the mask can only gain
    // set bits, never lose them, so fullState and background are dead code:
    // all non-level-triggered buttons are reported as new presses every frame.
    // Correct: newPressMask = ~(levelTriggers | fullState | background).
    newPressMask = ~(INP_START | INP_ZTRIG | INP_CLEFT | INP_CDOWN | INP_CUP | INP_B | INP_R | INP_L);
    newPressMask |= (u16) ~gPlayerInput[contId].fullState;
    newPressMask |= (u16) ~gPlayerInput[contId].background;

    gPlayerInput[contId].buttons = newPressMask & buttons;
    prevFullState = gPlayerInput[contId].fullState;

    // Signal pendingInput when button state changes, or when a directional
    // button (D-pad + CRIGHT) is held without interfering C-buttons.
    // D-pad directions repeat each frame so they can drive running/dashing
    // without the player releasing and re-pressing every frame.
    if (buttons != prevFullState ||
        (buttons & (INP_CRIGHT | INP_LEFT | INP_DOWN | INP_RIGHT)) && !(buttons & (INP_CLEFT | INP_CDOWN | INP_CUP))) {
        gPlayerInput[contId].pendingInput = TRUE;
    }

    gPlayerInput[contId].fullState = buttons;
    do { } while (0); }
#else
#pragma GLOBAL_ASM("asm/nonmatchings/input/process_player_input.s")
void process_player_input(s16 contId);
#endif

/* Called once per frame: advance the frame counter, read raw controller
   data, and run the input pipeline for both players. */
void input_update(void) {
    gFrameCounter++;
    cont_read();

    if (gPlayerInput[PLAYER_1].enabled && gPlayerInput[PLAYER_1].connected) {
        process_player_input(PLAYER_1);
    } else {
        gPlayerInput[PLAYER_1].buttons = 0;
    }

    if (gPlayerInput[PLAYER_2].enabled && gPlayerInput[PLAYER_2].connected) {
        process_player_input(PLAYER_2);
    } else {
        gPlayerInput[PLAYER_2].buttons = 0;
    }
}

/* Reset all player input state to defaults at battle start. */
void input_init(void) {
    gPlayerInput[PLAYER_1].pendingInput = gPlayerInput[PLAYER_2].pendingInput = FALSE;
    gPlayerInput[PLAYER_1].buttons = gPlayerInput[PLAYER_2].buttons = 0;
    gPlayerInput[PLAYER_1].mirrored = gPlayerInput[PLAYER_2].mirrored = FALSE;
    gPlayerInput[PLAYER_2].enabled = gPlayerInput[PLAYER_1].enabled = TRUE;
    gPlayerInput[PLAYER_2].fullState = gPlayerInput[PLAYER_1].fullState = 0;
    gPlayerInput[PLAYER_2].remapped = gPlayerInput[PLAYER_1].remapped = TRUE;
    gPlayerInput[PLAYER_1].stickDisabled = gPlayerInput[PLAYER_2].stickDisabled = FALSE;
}
