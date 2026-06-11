#include "common.h"
#include "task.h"

enum x_997a3c36 { AI_REACT_ACTIVE = 1, AI_REACT_CHAIN_ONLY = 2, AI_REACT_SPECIAL = 4 };

typedef struct {
    s16 index;
    x_eea787ea *entry;
} AiCandidate; // wrapping for candidate selection

u8 ai_enemy_action_check(Player *, x_ccb3bba0 **);
u8 ai_execute_action(Player *);
u8 ai_select_action(Player *, x_1e5e42da *);
s16 ai_tactic_default_move(Player *);

s16 ai_tactic_guard_far(Player *);
s16 ai_tactic_approach(Player *);
s16 ai_tactic_reject(Player *);
s16 ai_tactic_delay(Player *);
s16 ai_tactic_mid_guard(Player *);
s16 ai_tactic_aggressive(Player *);
s16 ai_tactic_fail(Player *);
s16 ai_tactic_retreat(Player *);
s16 ai_tactic_special_decide(Player *);
s16 ai_tactic_aggressive_decide(Player *);
s16 ai_tactic_delay_reset(Player *);
s16 ai_tactic_guard(Player *);
s16 ai_tactic_wait_interrupt(Player *);
s16 ai_tactic_wait_interrupt2(Player *);
s16 ai_tactic_check_reaction(Player *);
s16 ai_tactic_rewind(Player *);

s16 sAiDelayTable[] = { 30, 20, 20, 10, 10, 10, 0, 0, 0, 0 };
s16 sAiRandDelayTable[] = { 30, 30, 10, 6, 5, 2, 2, 0 };
s16 sAiAttemptCapTable[] = { 1, 2, 3, 4, 8, 10, 20, 1000 };
s16 sAiTimerBaseTable[] = { 70, 60, 60, 55, 50, 45, 40, 40 };
s16 sAiInterruptBaseTable[] = { 8, 6, 4, 2, 0, 0, 0, 0 };
s16 sAiInterruptRandTable[] = { 2, 2, 2, 1, 1, 1, 1, 1 };
s16 (*sAiTacticTable[])(struct Player *) = {
    ai_tactic_guard_far,      ai_tactic_approach,          ai_tactic_reject,         ai_tactic_delay,
    ai_tactic_mid_guard,      ai_tactic_aggressive,        ai_tactic_fail,           ai_tactic_retreat,
    ai_tactic_special_decide, ai_tactic_aggressive_decide, ai_tactic_delay_reset,    ai_tactic_guard,
    ai_tactic_wait_interrupt, ai_tactic_wait_interrupt2,   ai_tactic_check_reaction, ai_tactic_rewind,
};
s16 sAiOpenWindowTable[] = { 13, 13, 13, 10, 19, 19, 10, 10, 19, 10, 10, 0 };
s16 sAiCloseWindowTable[] = { 10, 10, 10, 7, 12, 12, 10, 10, 12, 10, 10, 0, 0, 0, 0, 0, 0, 0 };

u8 ai_move_force(Player *player, s16 x_0f12118c) {
    ai_state_reset(player);
    player->x_81570fde.x_b2c79d6e |= x_096af79a;
    return player_exec_move(player, x_0f12118c, TRUE);
}

void ai_update(Player *player) {
    u8 x_4b1172f5;
    x_ccb3bba0 *x_73dff70e;
    x_1e5e42da *x_81570fde;
    u16 x_cc57155e;
    s16 x_300a844c;

    x_cc57155e = gWadCondLoad[player->x_30bbe547].x_cc57155e;

    if (player->obj->x_9200c538 == 0) {
        return;
    }

    if (!(player->x_7f68c36b->flags & x_f79587cb)) {
        player->x_81570fde.x_60227f92 = 0;
    }

    if (player->x_81570fde.x_b2c79d6e & x_096af79a) {
        x_81570fde = &player->x_81570fde;
        if (player->x_448f0851 != 0 && --player->x_448f0851 == 0) {
            ai_state_reset(player);
            if (player->x_0a8e33d7 >= 0 && (player->flags & x_f6191783)) {
                if (player_force_transition(player)) {
                    player->x_81570fde.x_b2c79d6e |= x_096af79a;
                }
            }
        } else if (x_81570fde->x_ca75ac5d != NULL) {
            x_300a844c = x_81570fde->x_ca75ac5d(player);
            if (x_300a844c > 0) {
                return;
            }

            x_81570fde->x_ca75ac5d = NULL;
            player->x_81570fde.x_b2c79d6e &= ~x_096af79a;
            if (x_300a844c < 0) {
                ai_state_reset(player);
            } else {
                ai_advance_action(player);
            }
        } else if (player->x_448f0851 == 0 && player->obj->frameCounter >= player->x_7f68c36b->x_bab9966d - 1) {
            player->x_448f0851 = 512;
        }
    } else if (!(player->x_b9252303->flags & TASK_TIME_BASED) && !(player->flags & x_030d2322)) {
        if (hit_check_facing_away(player->obj) && !(player->x_7f68c36b->flags & x_cdcff2e1) &&
            !(player->obj->flags & x_da584e3c)) {
            if (player->x_7f68c36b->flags & x_037894c1) {
                ai_move_force(player, x_1d1fc609);
                return;
            }
            if (player->x_7f68c36b->flags & x_ff05097f) {
                ai_move_force(player, x_1fed1650);
                return;
            }
        }

        x_4b1172f5 = ai_enemy_action_check(player, &x_73dff70e);
        if ((player->obj->flags & x_da584e3c) || (player->flags & x_d8a402c3)) {
            return;
        }

        if ((--player->x_0b34e01a <= 0 || x_4b1172f5 && !(x_73dff70e->flags & AI_REACT_CHAIN_ONLY)) &&
                (player->x_7f68c36b->flags & (x_037894c1 | x_ff05097f)) ||
            player->transition->x_18eb6c3d != 0xFF) {
            player->x_0b34e01a = sAiDelayTable[x_cc57155e];
            player->x_0b34e01a += guRandom() & sAiRandDelayTable[x_cc57155e];

            if (!ai_select_action_full(player, (player->flags & x_20efa43e) != 0)) {
                player->x_0b34e01a = 0;
            }
        }
    }
}

void ai_state_reset(Player *player) {
    player->x_81570fde.x_14906c66[2] = player->x_81570fde.x_14906c66[1];
    player->x_81570fde.x_14906c66[1] = player->x_81570fde.x_14906c66[0];
    player->x_81570fde.x_14906c66[0] = NULL;

    player->x_81570fde.x_ca75ac5d = NULL;
    player->x_81570fde.x_9daba480 = player->x_81570fde.x_76cf2d04 = NULL;
    player->x_81570fde.x_b2c79d6e &= ~(x_62247817 | x_096af79a | x_f90d2b7b | x_c74d666c);
    player->x_448f0851 = 0;

    if (player->flags & x_d8a402c3) {
        player->x_81570fde.x_b2c79d6e |= x_62247817;
    }
}

u8 ai_advance_action(Player *player) {
    x_1e5e42da *x_81570fde = &player->x_81570fde;

    if (player->flags & x_d8a402c3 || (player->x_101ebc50 > 0x100 && !(x_81570fde->x_d098505c & 0x1000)) ||
        player->transition->x_86977b23 != player->x_cd14c741) {
        ai_state_reset(player);
        return FALSE;
    }

    if (ai_execute_action(player)) {
        return TRUE;
    }

    if (x_81570fde->x_9daba480 == NULL || *x_81570fde->x_9daba480 == -1 ||
        (player->x_81570fde.x_b2c79d6e & x_f90d2b7b)) {
        ai_state_reset(player);
        return FALSE;
    }

    x_81570fde->x_9daba480++;

    if (x_81570fde->x_9daba480 == NULL || *x_81570fde->x_9daba480 == -1) {
        ai_state_reset(player);
        return FALSE;
    }

    ai_select_action(player, x_81570fde);
    return ai_execute_action(player);
}

u8 ai_execute_action(Player *player) {
    x_1e5e42da *x_81570fde = &player->x_81570fde;
    s16 x_de68d2a6 = (player->x_30bbe547 != x_83106b21) ? x_83106b21 : x_6f0b3be3;

    if (x_81570fde->x_76cf2d04 != NULL && (s16) *x_81570fde->x_76cf2d04 != -1) {
        if (player_exec_move(player, *x_81570fde->x_76cf2d04, TRUE)) {
            x_81570fde->x_ef647f03 = x_824b9544[x_de68d2a6].obj->x_9200c538;
            player->x_81570fde.x_b2c79d6e |= x_096af79a;
            x_81570fde->x_76cf2d04++;
            return TRUE;
        }

        ai_state_reset(player);
        return FALSE;
    }
    return FALSE;
}

#ifdef NON_MATCHING
u8 ai_select_action(Player *player, x_1e5e42da *x_81570fde) {
    s32 x_7d78dd2d;
    s32 x_d7f0204f;
    u8 a3;

    do {
        x_81570fde++; // @fake
        x_81570fde--; // @fake
        x_d7f0204f = player->flags;
        x_7d78dd2d = player->x_7f68c36b->flags;

        // read AiAction header
        x_81570fde->x_76cf2d04 = player->x_994b73a7 + player->x_4ec7bbf8[*x_81570fde->x_9daba480];
        x_81570fde->x_ca75ac5d = ((s16) *x_81570fde->x_76cf2d04 == -1) ? NULL : sAiTacticTable[*x_81570fde->x_76cf2d04];
        x_81570fde->x_76cf2d04++;
        x_81570fde->x_5a6554ba = *x_81570fde->x_76cf2d04++;
        x_81570fde->x_5c398490 = *x_81570fde->x_76cf2d04++;

        a3 =
            (x_81570fde->x_5c398490 & x_7d78dd2d & 0x400) && !((x_81570fde->x_5c398490 & 0x200) ^ (x_7d78dd2d & 0x200));
        if (a3 && (x_81570fde->x_5c398490 & 8) && ((x_81570fde->x_5c398490 & 8) ^ (x_d7f0204f & x_9298c772))) {
            a3 = FALSE;
        }

        if ((x_81570fde->x_5c398490 & 0x1000) || a3 ||
            ((!(x_81570fde->x_5c398490 & 0x4000)) || ((x_81570fde->x_5c398490 & 0x4000) ^ (x_7d78dd2d & 0x4000))) &&
                !((x_81570fde->x_5c398490 & 8) ^ (x_d7f0204f & x_9298c772)) &&
                (x_81570fde->x_5c398490 & x_7d78dd2d & 5)) {
            // selected action from sequence
            x_81570fde->x_ef647f03 = x_824b9544[1 - player->x_30bbe547].obj->x_9200c538;
            player->x_81570fde.x_b2c79d6e &= ~(x_62247817 | x_096af79a | x_f90d2b7b | x_c74d666c);
            player->x_81570fde.x_b2c79d6e |= x_096af79a;
            if (x_81570fde->x_5c398490 & 0x8000) {
                player->x_81570fde.x_b2c79d6e |= x_f90d2b7b;
            }
            return TRUE;
        }

        x_81570fde->x_9daba480++;
    } while (*x_81570fde->x_9daba480 >= 0);

    ai_state_reset(player);
    return FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/aibrain/ai_select_action.s")
#endif

void ai_difficulty_increase(Player *player) {
    s16 x_261980db;
    s16 i;
    s16 x_b129ae42;
    x_ccb3bba0 *x_73dff70e;

    x_261980db = player->x_261980db;

    gWadCondLoad[player->x_30bbe547].x_cc57155e++;
    if (gWadCondLoad[player->x_30bbe547].x_cc57155e > 7) {
        gWadCondLoad[player->x_30bbe547].x_cc57155e = 7;
    }
    x_b129ae42 = gWadCondLoad[player->x_30bbe547].x_cc57155e;

    for (i = 0; i < x_261980db; i++) {
        x_73dff70e = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[i]);
        x_73dff70e->x_b129ae42 = x_b129ae42;
        x_73dff70e->x_1256da71 = x_73dff70e->x_cd679b4c;
    }

    ai_state_reset(player);
    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

void ai_difficulty_reset(Player *player) {
    s16 x_261980db;
    s16 i;
    x_ccb3bba0 *x_73dff70e;
    s16 x_cc57155e;

    x_261980db = player->x_261980db;
    for (i = 0; i < x_261980db; i++) {
        x_73dff70e = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[i]);
        x_73dff70e->x_b129ae42 = 0;
        x_73dff70e->x_1256da71 = x_73dff70e->x_cd679b4c;
    }

    ai_state_reset(player);

    x_cc57155e = gWadCondLoad[player->x_30bbe547].x_cc57155e;
    if (x_cc57155e == 0x7FFF) {
        x_cc57155e = 0;
    }

    gWadCondLoad[player->x_30bbe547].x_cc57155e = 0;
    for (i = 0; i < x_cc57155e; i++) {
        ai_difficulty_increase(player);
    }

    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

void ai_tables_clear(Player *player) {
    s16 x_261980db;
    s16 i;
    x_ccb3bba0 *x_73dff70e;

    x_261980db = player->x_261980db;
    for (i = 0; i < x_261980db; i++) {
        x_73dff70e = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[i]);
        x_73dff70e->x_b129ae42 = 0;
        x_73dff70e->x_1256da71 = x_73dff70e->x_cd679b4c;
    }

    ai_state_reset(player);
    gWadCondLoad[player->x_30bbe547].x_cc57155e = 0;
    gWadCondLoad[player->x_30bbe547].x_cc57155e = 0;
    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

void ai_difficulty_max(Player *player) {
    s16 x_261980db;
    s16 i;
    x_ccb3bba0 *x_73dff70e;
    s16 x_cc57155e;

    x_261980db = player->x_261980db;
    for (i = 0; i < x_261980db; i++) {
        x_73dff70e = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[i]);
        x_73dff70e->x_b129ae42 = 0;
        x_73dff70e->x_1256da71 = x_73dff70e->x_cd679b4c;
    }

    ai_state_reset(player);

    gWadCondLoad[player->x_30bbe547].x_cc57155e = 8;
    x_cc57155e = gWadCondLoad[player->x_30bbe547].x_cc57155e;

    gWadCondLoad[player->x_30bbe547].x_cc57155e = 0;
    for (i = 0; i < x_cc57155e; i++) {
        ai_difficulty_increase(player);
    }

    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

u8 ai_reaction_lookup(Player *player, x_ccb3bba0 **x_73dff70e, u8 x_852d4cff) {
    s32 x_0475899f;
    s16 x_00e4973c;
    x_ccb3bba0 *x_621dd544;
    Player *x_98c4e5a5;
    s16 x_4c93e610;
    s16 x_549ac3de;

    x_98c4e5a5 = x_824b9544 + 1 - player->x_30bbe547;

    if (x_852d4cff) {
        x_0475899f = (x_824b9544[1 - player->x_30bbe547].x_7f68c36b->flags & x_037894c1) ? x_26778114 : x_ee946ac0;
        x_4c93e610 = x_98c4e5a5->x_59f97427[x_0475899f];
        x_549ac3de = x_98c4e5a5->x_b8b27276[x_4c93e610];
        x_00e4973c = x_98c4e5a5->x_1af5b64c[x_549ac3de].x_acda7e96[player->x_eb1fe45b];
    } else {
        // get response to enemy state
        x_00e4973c = x_824b9544[1 - player->x_30bbe547].transition->x_acda7e96[player->x_eb1fe45b];
        if (x_00e4973c == 0xFF) {
            // enemy action doesn't imply reaction, so return nothing
            return FALSE;
        }
    }

    x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    if (!(x_621dd544->flags & AI_REACT_ACTIVE)) {
        x_00e4973c += x_621dd544->x_b129ae42;
        x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    }
    *x_73dff70e = x_621dd544;
    return TRUE;
}

u8 ai_enemy_action_check(Player *player, x_ccb3bba0 **x_73dff70e) {
    s16 x_00e4973c;
    x_ccb3bba0 *x_621dd544;

    x_00e4973c = x_824b9544[1 - player->x_30bbe547].transition->x_acda7e96[player->x_eb1fe45b];
    if (x_00e4973c == 0xFF) {
        return FALSE;
    }

    x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    *x_73dff70e = x_621dd544;
    return TRUE;
}

u8 ai_self_action_reaction(Player *player, x_ccb3bba0 **x_73dff70e) {
    s16 x_00e4973c;
    x_ccb3bba0 *x_621dd544;

    x_00e4973c = x_824b9544[player->x_30bbe547].transition->x_18eb6c3d;
    if (x_00e4973c == 0xFF) {
        return FALSE;
    }

    x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    if (!(x_621dd544->flags & AI_REACT_ACTIVE)) {
        x_00e4973c += x_621dd544->x_b129ae42;
        x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    }

    *x_73dff70e = x_621dd544;
    return TRUE;
}

u8 ai_select_action_full(Player *player, u8 x_84ff873b) {
    x_ccb3bba0 *x_73dff70e;
    s32 x_de68d2a6;
    s16 x_35bfa5f2;
    x_1e5e42da *x_81570fde;
    s16 *x_cf2c3c6e;
    AiCandidate x_ba159dbf[100];
    u8 x_5ad6e307;
    x_eea787ea *x_1fd4d41c;
    s32 pad;
    s16 x_ad99dc68;
    u16 x_1e623531;
    s32 x_42126496;
    s32 x_d7f0204f;
    s16 x_c8766e1c;

    x_de68d2a6 = (player->x_30bbe547 != x_83106b21) ? x_83106b21 : x_6f0b3be3;

    if (!(player->flags & x_d8a402c3) && (player->x_cd14c741 == 216 || player->x_cd14c741 == 42) &&
        ai_reaction_lookup(player, &x_73dff70e, TRUE)) {
        x_5ad6e307 = FALSE;
    } else if (ai_self_action_reaction(player, &x_73dff70e)) {
        x_5ad6e307 = TRUE;
    } else if (ai_reaction_lookup(player, &x_73dff70e, FALSE)) {
        x_5ad6e307 = FALSE;
    } else {
        ai_state_reset(player);
        return FALSE;
    }

    if (x_5ad6e307 && (x_73dff70e->flags & AI_REACT_CHAIN_ONLY) &&
        (x_824b9544[x_de68d2a6].x_7f68c36b->flags & (x_7507aa4b | x_eac5209f)) &&
        !gWadCondLoad[x_de68d2a6].x_03604d94 && !(x_824b9544[x_de68d2a6].flags & x_6de2d515)) {
        return FALSE;
    }

    if (!x_5ad6e307 && x_84ff873b) {
        return FALSE;
    }

    if (x_5ad6e307 & x_84ff873b) { // typo ??
        x_5ad6e307 = FALSE;
    }

    x_35bfa5f2 = 0;

    x_1e623531 = 1 << gWadCondLoad[player->x_30bbe547].x_cc57155e;
    x_42126496 = player->x_7f68c36b->flags;
    x_d7f0204f = player->flags;

    do {
        x_cf2c3c6e = x_73dff70e->x_ba159dbf;
        while (*x_cf2c3c6e != -1) {
            x_1fd4d41c = &player->x_ad9d3e42[*x_cf2c3c6e & 0xFF];
            x_cf2c3c6e++;

            if (x_1fd4d41c->x_1350cb4d <= gFighterDistance + 200 && x_1fd4d41c->x_62addb22 >= gFighterDistance - 200) {
                x_81570fde = &player->x_81570fde;
                if (x_1fd4d41c->x_1e623531 & x_1e623531) {
                    if (x_1fd4d41c != x_81570fde->x_14906c66[1] && x_1fd4d41c != x_81570fde->x_14906c66[2] ||
                        !(x_1fd4d41c->x_c3afc384 & 0x800)) {
                        if ((x_1fd4d41c->x_c3afc384 & 0x1000) || ((x_1fd4d41c->x_c3afc384 & x_42126496) & 0x600) ||
                            (x_d7f0204f & x_9298c772) == (x_1fd4d41c->x_c3afc384 & 8) &&
                                ((u8) (x_1fd4d41c->x_c3afc384 & x_42126496) & 5)) {
                            // clang-format off
                            x_ba159dbf[x_35bfa5f2].index = x_cf2c3c6e[-1];\
                            x_ba159dbf[x_35bfa5f2].entry = x_1fd4d41c;\
                            x_35bfa5f2++;
                            // clang-format on
                        }
                    }
                }
            }
        }

        if (x_35bfa5f2 == 0) {
            if (!x_5ad6e307) {
                if (x_84ff873b) {
                    return FALSE;
                }

                player->x_81570fde.x_14906c66[0] = NULL;

                if (gFighterDistance > 800 && !(player->x_81570fde.x_b2c79d6e & x_c98846bd)) {
                    if (gWadCondLoad[player->x_30bbe547].x_cc57155e <= 3) {
                        player_exec_move(player, x_4a0f5c6c, TRUE);
                        wad_strcpy(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss fwd");
                        player->x_81570fde.x_ca75ac5d = ai_tactic_default_move;
                    } else {
                        player_exec_move(player, x_a8ddcce3, TRUE);
                        wad_strcpy(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default dash fwd");
                    }

                    player->x_81570fde.x_b2c79d6e &= ~(x_dc8d9492 | x_83011c23);
                    player->x_81570fde.x_b2c79d6e |= x_c98846bd;
                } else if (gFighterDistance < 800 && !(player->x_81570fde.x_b2c79d6e << 19)) { // ???
                    if (gWadCondLoad[player->x_30bbe547].x_cc57155e <= 3) {
                        player_exec_move(player, x_96d30734, TRUE);
                        wad_strcpy(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss bak");
                        player->x_81570fde.x_ca75ac5d = ai_tactic_default_move;
                    } else {
                        player_exec_move(player, x_6cd07703, TRUE);
                        wad_strcpy(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default dash bak");
                    }

                    player->x_81570fde.x_b2c79d6e &= ~(x_c98846bd | x_83011c23);
                    player->x_81570fde.x_b2c79d6e |= x_dc8d9492;
                } else {
                    if (guRandom() & 1 & gFrameCounter) {
                        wad_strcpy(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss in");
                        if (!player_exec_move(player, x_35f07eb8, TRUE)) {
                            return FALSE;
                        }
                        player->x_81570fde.x_ca75ac5d = NULL;
                    } else {
                        wad_strcpy(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss out");
                        if (!player_exec_move(player, x_98c27b4d, TRUE)) {
                            return FALSE;
                        }
                        player->x_81570fde.x_ca75ac5d = NULL;
                    }

                    player->x_81570fde.x_b2c79d6e &= ~(x_c98846bd | x_dc8d9492);
                    player->x_81570fde.x_b2c79d6e |= x_83011c23;
                }

                player->x_81570fde.x_76cf2d04 = NULL;
                player->x_81570fde.x_b2c79d6e |= x_096af79a;
                return TRUE;
            }

            if (ai_reaction_lookup(player, &x_73dff70e, FALSE)) {
                x_5ad6e307 = FALSE;
            } else {
                player->x_81570fde.x_14906c66[0] = NULL;
                return FALSE;
            }
        }
    } while (x_35bfa5f2 == 0);

    x_81570fde = &player->x_81570fde;

    x_c8766e1c = guRandom() % x_35bfa5f2;
    x_81570fde->x_14906c66[0] = x_ba159dbf[x_c8766e1c].entry;
    x_ad99dc68 = x_81570fde->x_14906c66[0]->x_d3e51cdb;
    x_81570fde->x_9daba480 = player->x_d908b580 + x_ad99dc68;
    x_81570fde->x_d098505c = x_81570fde->x_14906c66[0]->x_c3afc384;
    x_81570fde->x_011116d7 = x_73dff70e;

    return ai_select_action(player, x_81570fde) && ai_execute_action(player);
}

s16 ai_tactic_guard_far(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    if (player->obj->frameCounter < (player->x_7f68c36b->x_bab9966d >> 1)) {
        return TRUE;
    }

    x_4b1172f5 = ai_enemy_action_check(player, &x_73dff70e);
    return (gFighterDistance > player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & AI_REACT_CHAIN_ONLY));
}

s16 ai_tactic_guard(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    x_4b1172f5 = ai_enemy_action_check(player, &x_73dff70e);
    return (gFighterDistance > player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & AI_REACT_CHAIN_ONLY));
}

s16 ai_tactic_approach(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    x_4b1172f5 = ai_enemy_action_check(player, &x_73dff70e);

    if (player->obj->frameCounter < (player->x_7f68c36b->x_bab9966d >> 1)) {
        return TRUE;
    }

    return (gFighterDistance < player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & AI_REACT_CHAIN_ONLY));
}

s16 ai_tactic_reject(Player *player) {
    return 0;
}

s16 ai_tactic_delay(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    x_4b1172f5 = ai_enemy_action_check(player, &x_73dff70e);

    if (player->x_81570fde.x_5a6554ba) {
        player->x_81570fde.x_5a6554ba--;
    }

    return (player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & AI_REACT_CHAIN_ONLY));
}

s16 ai_tactic_mid_guard(Player *player) {
    if (player->obj->frameCounter < (player->x_7f68c36b->x_bab9966d >> 1)) {
        return TRUE;
    }

    return FALSE;
}

s16 ai_tactic_timer(Player *player) {
    if (--player->x_81570fde.x_5a6554ba > 0) {
        return TRUE;
    } else {
        return -1;
    }
}

s16 ai_tactic_fail(Player *player) {
    return -1;
}

s16 ai_tactic_aggressive(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s16 x_de68d2a6;
    s16 frameCounter;
    s16 x_fedecf5c;
    s16 x_c53ac2df;
    Player *x_98c4e5a5;

    x_de68d2a6 = 1 - player->x_30bbe547;
    frameCounter = x_824b9544[x_de68d2a6].obj->frameCounter;
    x_fedecf5c = x_824b9544[x_de68d2a6].x_7f68c36b->x_fedecf5c;
    x_c53ac2df = x_824b9544[x_de68d2a6].x_7f68c36b->x_c53ac2df;

    if (player->flags & x_d8a402c3) {
        return TRUE;
    }
    if (player->x_81570fde.x_60227f92 >= sAiAttemptCapTable[gWadCondLoad[player->x_30bbe547].x_cc57155e] &&
        !(x_824b9544[1 - player->x_30bbe547].flags & x_c15491f2)) {
        return FALSE;
    }

    player->x_81570fde.x_5a6554ba--;

    if (ai_enemy_action_check(player, &x_73dff70e) && !(x_73dff70e->flags & AI_REACT_CHAIN_ONLY)) {
        if (x_73dff70e->flags & AI_REACT_SPECIAL) {
            player_exec_move_ai(player, x_28ed5d80, TRUE);
        }
        return TRUE;
    }

    x_98c4e5a5 = x_824b9544 + x_de68d2a6;
    if ((x_824b9544[x_de68d2a6].flags & x_9298c772) ||
        !(x_98c4e5a5->flags & x_c15491f2) && player->x_81570fde.x_5a6554ba < 20 &&
            ((frameCounter < x_c53ac2df && sAiOpenWindowTable[x_98c4e5a5->x_eb1fe45b] < x_c53ac2df - frameCounter) ||
             (x_fedecf5c < frameCounter && sAiCloseWindowTable[x_98c4e5a5->x_eb1fe45b] <
                                               x_824b9544[x_de68d2a6].x_7f68c36b->x_bab9966d - x_fedecf5c) ||
             ((x_824b9544[1 - player->x_30bbe547].flags & x_030d2322) &&
              x_824b9544[1 - player->x_30bbe547].obj->frameCounter < 6))) {
        player->x_cd14c741 = 216;
        return -1;
    }

    return player->x_81570fde.x_5a6554ba > 0 || !(x_73dff70e->flags & AI_REACT_CHAIN_ONLY);
}

s16 ai_tactic_retreat(Player *player) {
    s16 x_de68d2a6 = 1 - player->x_30bbe547;
    s32 pad;
    x_ccb3bba0 *x_73dff70e;
    u8 v0;

    if (player->flags & x_d8a402c3) {
        return TRUE;
    }

    if (player->x_81570fde.x_60227f92 >= sAiAttemptCapTable[gWadCondLoad[player->x_30bbe547].x_cc57155e] &&
        !(x_824b9544[1 - player->x_30bbe547].flags & x_c15491f2)) {
        return FALSE;
    }

    player->x_81570fde.x_5a6554ba--;
    v0 = ai_enemy_action_check(player, &x_73dff70e);
    if (v0 && !(x_73dff70e->flags & AI_REACT_CHAIN_ONLY)) {
        if (!(x_73dff70e->flags & AI_REACT_SPECIAL)) {
            player_exec_move_ai(player, x_01ff67cd, TRUE);
        }
        return TRUE;
    }

    if (x_824b9544[x_de68d2a6].flags & x_9298c772) {
        player->x_cd14c741 = 42;
        return -1;
    }

    return (player->x_81570fde.x_5a6554ba > 0) || !(x_73dff70e->flags & AI_REACT_CHAIN_ONLY);
}

u8 ai_random_chance(Player *player) {
    switch (x_028e5846) {
        case x_8bfc1f62:
            switch (gWadCondLoad[player->x_30bbe547].x_cc57155e) {
                case 0:
                    return (guRandom() % 100) < 20;
                case 1:
                case 2:
                    return (guRandom() % 100) < 40;
                case 3:
                case 4:
                    return (guRandom() % 100) < 60;
                case 5:
                    return (guRandom() % 100) < 80;
                default:
                    return TRUE;
            }
            break;
        case x_c74743bd:
        case x_d286d6eb:
            switch (gWadCondLoad[player->x_30bbe547].x_cc57155e) {
                case 0:
                    return (guRandom() % 100) < 20;
                case 1:
                    return (guRandom() % 100) < 40;
                case 2:
                case 3:
                    return (guRandom() % 100) < 80;
                default:
                    return TRUE;
            }
            break;
    }

    return TRUE;
}

s16 ai_tactic_passive(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s32 pad[2];
    u8 v0;
    s16 x_30bbe547 = player->x_30bbe547;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < sAiAttemptCapTable[gWadCondLoad[x_30bbe547].x_cc57155e]) {
        v0 = ai_enemy_action_check(player, &x_73dff70e);
        if (v0 && !(x_73dff70e->flags & AI_REACT_CHAIN_ONLY) && !(x_73dff70e->flags & AI_REACT_SPECIAL)) {
            player_exec_move_ai(player, x_01ff67cd, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 ai_tactic_opener(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s16 x_de68d2a6;
    s16 x_c9614940;
    s16 x_18643961;
    s16 x_32f1d6e2;
    Player *x_98c4e5a5;

    x_de68d2a6 = 1 - player->x_30bbe547;
    x_c9614940 = x_824b9544[x_de68d2a6].obj->frameCounter;
    x_18643961 = x_824b9544[x_de68d2a6].x_7f68c36b->x_fedecf5c;
    x_32f1d6e2 = x_824b9544[x_de68d2a6].x_7f68c36b->x_c53ac2df;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < sAiAttemptCapTable[gWadCondLoad[player->x_30bbe547].x_cc57155e]) {
        if (ai_enemy_action_check(player, &x_73dff70e)) {
            if (!(x_73dff70e->flags & AI_REACT_CHAIN_ONLY) && !(x_73dff70e->flags & AI_REACT_SPECIAL)) {
                player_exec_move_ai(player, x_01ff67cd, TRUE);
                return 1;
            }
        }
    }

    x_98c4e5a5 = x_824b9544 + x_de68d2a6;
    if (!(x_98c4e5a5->flags & x_c15491f2)) {
        if ((x_c9614940 < x_32f1d6e2 && sAiOpenWindowTable[x_98c4e5a5->x_eb1fe45b] < x_32f1d6e2 - x_c9614940) ||
            (x_18643961 < x_c9614940 && sAiCloseWindowTable[x_98c4e5a5->x_eb1fe45b] <
                                            x_824b9544[x_de68d2a6].x_7f68c36b->x_bab9966d - x_18643961) ||
            ((x_824b9544[1 - player->x_30bbe547].flags & x_030d2322) &&
             x_824b9544[1 - player->x_30bbe547].obj->frameCounter < 6)) {
            player->flags &= ~x_d8a402c3;
            return -1;
        }
    }

    return 1;
}

s16 ai_tactic_aggressive_decide(Player *player) {
    player->x_81570fde.x_4390a1c3 = 0;
    player->x_81570fde.x_60227f92++;

    if (ai_random_chance(player)) {
        player->x_81570fde.x_ca75ac5d = ai_tactic_opener;
        return ai_tactic_opener(player);
    } else {
        player->x_81570fde.x_ca75ac5d = ai_tactic_passive;
        return ai_tactic_passive(player);
    }
}

s16 ai_tactic_special_delay(Player *player) {
    s32 pad[2];
    x_ccb3bba0 *x_73dff70e;
    u8 v0;
    s16 x_30bbe547 = player->x_30bbe547;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < sAiAttemptCapTable[gWadCondLoad[x_30bbe547].x_cc57155e]) {
        v0 = ai_enemy_action_check(player, &x_73dff70e);
        if (v0 && !(x_73dff70e->flags & AI_REACT_CHAIN_ONLY) && (x_73dff70e->flags & AI_REACT_SPECIAL)) {
            player_exec_move_ai(player, x_28ed5d80, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 ai_tactic_special_approach(Player *player) {
    s16 x_de68d2a6;
    s16 x_c9614940;
    s16 x_18643961;
    s16 x_32f1d6e2;
    x_ccb3bba0 *x_73dff70e;
    Player *x_98c4e5a5;

    x_de68d2a6 = 1 - player->x_30bbe547;
    x_c9614940 = x_824b9544[x_de68d2a6].obj->frameCounter;
    x_18643961 = x_824b9544[x_de68d2a6].x_7f68c36b->x_fedecf5c;
    x_32f1d6e2 = x_824b9544[x_de68d2a6].x_7f68c36b->x_c53ac2df;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < sAiAttemptCapTable[gWadCondLoad[player->x_30bbe547].x_cc57155e]) {
        if (ai_enemy_action_check(player, &x_73dff70e)) {
            if (!(x_73dff70e->flags & AI_REACT_CHAIN_ONLY) && (x_73dff70e->flags & AI_REACT_SPECIAL)) {
                player_exec_move_ai(player, x_28ed5d80, TRUE);
                return 1;
            }
        }
    }

    x_98c4e5a5 = x_824b9544 + x_de68d2a6;
    if (!(x_98c4e5a5->flags & x_c15491f2) && ai_random_chance(player)) {
        if ((x_c9614940 < x_32f1d6e2 && sAiOpenWindowTable[x_98c4e5a5->x_eb1fe45b] < x_32f1d6e2 - x_c9614940) ||
            (x_18643961 < x_c9614940 && sAiCloseWindowTable[x_98c4e5a5->x_eb1fe45b] <
                                            x_824b9544[x_de68d2a6].x_7f68c36b->x_bab9966d - x_18643961) ||
            ((x_824b9544[1 - player->x_30bbe547].flags & x_030d2322) &&
             x_824b9544[1 - player->x_30bbe547].obj->frameCounter < 6)) {
            player->flags &= ~x_d8a402c3;
            return -1;
        }
    }

    return 1;
}

s16 ai_tactic_special_decide(Player *player) {
    player->x_81570fde.x_4390a1c3 = 0;
    player->x_81570fde.x_60227f92++;

    if (ai_random_chance(player)) {
        player->x_81570fde.x_ca75ac5d = ai_tactic_special_approach;
        return ai_tactic_special_approach(player);
    } else {
        player->x_81570fde.x_ca75ac5d = ai_tactic_special_delay;
        return ai_tactic_special_delay(player);
    }
}

s16 ai_tactic_delay_reset(Player *player) {
    s16 x_f6289181;

    x_f6289181 = gWadCondLoad[player->x_30bbe547].x_cc57155e;
    player->x_81570fde.x_5a6554ba =
        sAiTimerBaseTable[x_f6289181] + (guRandom() & sAiRandDelayTable[x_f6289181]); // @BUG ??
    player->x_81570fde.x_ca75ac5d = ai_tactic_timer;
    return 1;
}

s16 ai_tactic_default_move(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s32 x_4b1172f5;

    x_4b1172f5 = ai_enemy_action_check(player, &x_73dff70e);

    if (player->obj->frameCounter < (player->x_7f68c36b->x_bab9966d >> 1) && !(player->flags & x_9298c772)) {
        return TRUE;
    }

    if (player->obj->frameCounter < player->x_7f68c36b->x_bab9966d - 1 && !(player->flags & x_9298c772) &&
        (!x_4b1172f5 || (x_73dff70e->flags & AI_REACT_CHAIN_ONLY))) {
        return TRUE;
    }

    return FALSE;
}

s16 ai_tactic_wait_interrupt(Player *player) {
    s16 x_5bbba600;
    s32 pad;
    s16 pad2;
    s16 x_32f1d6e2;

    x_5bbba600 = gWadCondLoad[player->x_30bbe547].x_cc57155e;
    x_32f1d6e2 = sAiInterruptBaseTable[x_5bbba600];
    x_32f1d6e2 += guRandom() % sAiInterruptRandTable[x_5bbba600];
    player->x_81570fde.x_4390a1c3++;

    if (x_32f1d6e2 < player->x_81570fde.x_4390a1c3 || (x_824b9544[1 - player->x_30bbe547].flags & x_4d950171)) {
        player->x_81570fde.x_9daba480++;
        ai_select_action(player, &player->x_81570fde);
        ai_execute_action(player);
        player->x_81570fde.x_5a6554ba = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 ai_tactic_wait_interrupt2(Player *player) {
    s16 x_cc57155e;
    s32 pad;
    s16 pad2;
    s16 x_32f1d6e2;

    x_cc57155e = gWadCondLoad[player->x_30bbe547].x_cc57155e;
    x_32f1d6e2 = sAiInterruptBaseTable[x_cc57155e];
    x_32f1d6e2 += guRandom() % sAiInterruptRandTable[x_cc57155e];
    player->x_81570fde.x_4390a1c3++;

    if (x_32f1d6e2 < player->x_81570fde.x_4390a1c3 || (x_824b9544[1 - player->x_30bbe547].flags & x_4d950171)) {
        player->x_81570fde.x_9daba480++;
        ai_select_action(player, &player->x_81570fde);
        ai_execute_action(player);
        player->x_81570fde.x_5a6554ba = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 ai_tactic_check_reaction(Player *player) {
    x_ccb3bba0 *x_73dff70e;

    if (ai_enemy_action_check(player, &x_73dff70e)) {
        if (!(x_73dff70e->flags & AI_REACT_CHAIN_ONLY)) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}

s16 ai_tactic_rewind(Player *player) {
    player->x_81570fde.x_ca75ac5d = NULL;
    player->x_81570fde.x_9daba480 -= 2;
    return 1;
}
