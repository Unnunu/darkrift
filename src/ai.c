#include "common.h"
#include "task.h"

enum x_997a3c36 { x_79afbc9f = 1, x_42f9acb6 = 2, x_43a0d261 = 4 };

typedef struct {
    s16 index;
    x_eea787ea *entry;
} x_2559abd9; // wrapping for candidate selection

u8 x_99de1125(Player *, x_ccb3bba0 **);
u8 x_c41ec21f(Player *);
u8 x_9f09065b(Player *, x_1e5e42da *);
s16 x_c292dfa6(Player *);

s16 x_96d51072(Player *);
s16 x_456d0051(Player *);
s16 x_30f96d57(Player *);
s16 x_09f9ea13(Player *);
s16 x_02127c90(Player *);
s16 x_a92b640d(Player *);
s16 x_54e2b66c(Player *);
s16 x_8b270b48(Player *);
s16 x_8985d3ca(Player *);
s16 x_9aa019dc(Player *);
s16 x_b8c2dd87(Player *);
s16 x_96cd9330(Player *);
s16 x_f7322749(Player *);
s16 x_4f67a505(Player *);
s16 x_449f1966(Player *);
s16 x_61604a34(Player *);

s16 D_80049D10[] = { 30, 20, 20, 10, 10, 10, 0, 0, 0, 0 };
s16 D_80049D24[] = { 30, 30, 10, 6, 5, 2, 2, 0 };
s16 D_80049D34[] = { 1, 2, 3, 4, 8, 10, 20, 1000 };
s16 D_80049D44[] = { 70, 60, 60, 55, 50, 45, 40, 40 };
s16 D_80049D54[] = { 8, 6, 4, 2, 0, 0, 0, 0 };
s16 D_80049D64[] = { 2, 2, 2, 1, 1, 1, 1, 1 };
s16 (*x_0d580d2b[])(struct Player *) = {
    x_96d51072, x_456d0051, x_30f96d57, x_09f9ea13, x_02127c90, x_a92b640d, x_54e2b66c, x_8b270b48,
    x_8985d3ca, x_9aa019dc, x_b8c2dd87, x_96cd9330, x_f7322749, x_4f67a505, x_449f1966, x_61604a34,
};
s16 D_80049DB4[] = { 13, 13, 13, 10, 19, 19, 10, 10, 19, 10, 10, 0 };
s16 D_80049DCC[] = { 10, 10, 10, 7, 12, 12, 10, 10, 12, 10, 10, 0, 0, 0, 0, 0, 0, 0 };

u8 x_96d3a31b(Player *player, s16 x_0f12118c) {
    x_5587ad5e(player);
    player->x_81570fde.x_b2c79d6e |= x_096af79a;
    return x_e914de48(player, x_0f12118c, TRUE);
}

void x_da66d1d5(Player *player) {
    u8 x_4b1172f5;
    x_ccb3bba0 *x_73dff70e;
    x_1e5e42da *x_81570fde;
    u16 x_cc57155e;
    s16 x_300a844c;

    x_cc57155e = x_77831b2c[player->x_30bbe547].x_cc57155e;

    if (player->obj->x_9200c538 == 0) {
        return;
    }

    if (!(player->x_7f68c36b->flags & x_f79587cb)) {
        player->x_81570fde.x_60227f92 = 0;
    }

    if (player->x_81570fde.x_b2c79d6e & x_096af79a) {
        x_81570fde = &player->x_81570fde;
        if (player->x_448f0851 != 0 && --player->x_448f0851 == 0) {
            x_5587ad5e(player);
            if (player->x_0a8e33d7 >= 0 && (player->flags & x_f6191783)) {
                if (x_fb0d2e6c(player)) {
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
                x_5587ad5e(player);
            } else {
                x_12c88671(player);
            }
        } else if (player->x_448f0851 == 0 && player->obj->x_5fcb1654 >= player->x_7f68c36b->x_bab9966d - 1) {
            player->x_448f0851 = 512;
        }
    } else if (!(player->x_b9252303->flags & x_09809fad) && !(player->flags & x_030d2322)) {
        if (x_af5ccc8a(player->obj) && !(player->x_7f68c36b->flags & x_cdcff2e1) &&
            !(player->obj->flags & x_da584e3c)) {
            if (player->x_7f68c36b->flags & x_037894c1) {
                x_96d3a31b(player, x_1d1fc609);
                return;
            }
            if (player->x_7f68c36b->flags & x_ff05097f) {
                x_96d3a31b(player, x_1fed1650);
                return;
            }
        }

        x_4b1172f5 = x_99de1125(player, &x_73dff70e);
        if ((player->obj->flags & x_da584e3c) || (player->flags & x_d8a402c3)) {
            return;
        }

        if ((--player->x_0b34e01a <= 0 || x_4b1172f5 && !(x_73dff70e->flags & x_42f9acb6)) &&
                (player->x_7f68c36b->flags & (x_037894c1 | x_ff05097f)) ||
            player->transition->x_18eb6c3d != 0xFF) {
            player->x_0b34e01a = D_80049D10[x_cc57155e];
            player->x_0b34e01a += guRandom() & D_80049D24[x_cc57155e];

            if (!x_bed222e0(player, (player->flags & x_20efa43e) != 0)) {
                player->x_0b34e01a = 0;
            }
        }
    }
}

void x_5587ad5e(Player *player) {
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

u8 x_12c88671(Player *player) {
    x_1e5e42da *x_81570fde = &player->x_81570fde;

    if (player->flags & x_d8a402c3 || (player->x_101ebc50 > 0x100 && !(x_81570fde->x_d098505c & 0x1000)) ||
        player->transition->x_86977b23 != player->x_cd14c741) {
        x_5587ad5e(player);
        return FALSE;
    }

    if (x_c41ec21f(player)) {
        return TRUE;
    }

    if (x_81570fde->x_9daba480 == NULL || *x_81570fde->x_9daba480 == -1 ||
        (player->x_81570fde.x_b2c79d6e & x_f90d2b7b)) {
        x_5587ad5e(player);
        return FALSE;
    }

    x_81570fde->x_9daba480++;

    if (x_81570fde->x_9daba480 == NULL || *x_81570fde->x_9daba480 == -1) {
        x_5587ad5e(player);
        return FALSE;
    }

    x_9f09065b(player, x_81570fde);
    return x_c41ec21f(player);
}

u8 x_c41ec21f(Player *player) {
    x_1e5e42da *x_81570fde = &player->x_81570fde;
    s16 x_de68d2a6 = (player->x_30bbe547 != x_83106b21) ? x_83106b21 : x_6f0b3be3;

    if (x_81570fde->x_76cf2d04 != NULL && (s16) *x_81570fde->x_76cf2d04 != -1) {
        if (x_e914de48(player, *x_81570fde->x_76cf2d04, TRUE)) {
            x_81570fde->x_ef647f03 = x_824b9544[x_de68d2a6].obj->x_9200c538;
            player->x_81570fde.x_b2c79d6e |= x_096af79a;
            x_81570fde->x_76cf2d04++;
            return TRUE;
        }

        x_5587ad5e(player);
        return FALSE;
    }
    return FALSE;
}

#ifdef NON_MATCHING
u8 x_9f09065b(Player *player, x_1e5e42da *x_81570fde) {
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
        x_81570fde->x_ca75ac5d = ((s16) *x_81570fde->x_76cf2d04 == -1) ? NULL : x_0d580d2b[*x_81570fde->x_76cf2d04];
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

    x_5587ad5e(player);
    return FALSE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ai/x_9f09065b.s")
#endif

void x_c94a154b(Player *player) {
    s16 x_261980db;
    s16 i;
    s16 x_b129ae42;
    x_ccb3bba0 *x_73dff70e;

    x_261980db = player->x_261980db;

    x_77831b2c[player->x_30bbe547].x_cc57155e++;
    if (x_77831b2c[player->x_30bbe547].x_cc57155e > 7) {
        x_77831b2c[player->x_30bbe547].x_cc57155e = 7;
    }
    x_b129ae42 = x_77831b2c[player->x_30bbe547].x_cc57155e;

    for (i = 0; i < x_261980db; i++) {
        x_73dff70e = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[i]);
        x_73dff70e->x_b129ae42 = x_b129ae42;
        x_73dff70e->x_1256da71 = x_73dff70e->x_cd679b4c;
    }

    x_5587ad5e(player);
    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

void x_b5611eaf(Player *player) {
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

    x_5587ad5e(player);

    x_cc57155e = x_77831b2c[player->x_30bbe547].x_cc57155e;
    if (x_cc57155e == 0x7FFF) {
        x_cc57155e = 0;
    }

    x_77831b2c[player->x_30bbe547].x_cc57155e = 0;
    for (i = 0; i < x_cc57155e; i++) {
        x_c94a154b(player);
    }

    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

void x_9308b483(Player *player) {
    s16 x_261980db;
    s16 i;
    x_ccb3bba0 *x_73dff70e;

    x_261980db = player->x_261980db;
    for (i = 0; i < x_261980db; i++) {
        x_73dff70e = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[i]);
        x_73dff70e->x_b129ae42 = 0;
        x_73dff70e->x_1256da71 = x_73dff70e->x_cd679b4c;
    }

    x_5587ad5e(player);
    x_77831b2c[player->x_30bbe547].x_cc57155e = 0;
    x_77831b2c[player->x_30bbe547].x_cc57155e = 0;
    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

void x_5ca8f576(Player *player) {
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

    x_5587ad5e(player);

    x_77831b2c[player->x_30bbe547].x_cc57155e = 8;
    x_cc57155e = x_77831b2c[player->x_30bbe547].x_cc57155e;

    x_77831b2c[player->x_30bbe547].x_cc57155e = 0;
    for (i = 0; i < x_cc57155e; i++) {
        x_c94a154b(player);
    }

    player->x_81570fde.x_b2c79d6e = x_c74d666c;
}

u8 x_cb6a0d41(Player *player, x_ccb3bba0 **x_73dff70e, u8 x_852d4cff) {
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
    if (!(x_621dd544->flags & x_79afbc9f)) {
        x_00e4973c += x_621dd544->x_b129ae42;
        x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    }
    *x_73dff70e = x_621dd544;
    return TRUE;
}

u8 x_99de1125(Player *player, x_ccb3bba0 **x_73dff70e) {
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

u8 x_574aae97(Player *player, x_ccb3bba0 **x_73dff70e) {
    s16 x_00e4973c;
    x_ccb3bba0 *x_621dd544;

    x_00e4973c = x_824b9544[player->x_30bbe547].transition->x_18eb6c3d;
    if (x_00e4973c == 0xFF) {
        return FALSE;
    }

    x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    if (!(x_621dd544->flags & x_79afbc9f)) {
        x_00e4973c += x_621dd544->x_b129ae42;
        x_621dd544 = (x_ccb3bba0 *) (player->x_0bc74042 + player->x_78242925[x_00e4973c]);
    }

    *x_73dff70e = x_621dd544;
    return TRUE;
}

u8 x_bed222e0(Player *player, u8 x_84ff873b) {
    x_ccb3bba0 *x_73dff70e;
    s32 x_de68d2a6;
    s16 x_35bfa5f2;
    x_1e5e42da *x_81570fde;
    s16 *x_cf2c3c6e;
    x_2559abd9 x_ba159dbf[100];
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
        x_cb6a0d41(player, &x_73dff70e, TRUE)) {
        x_5ad6e307 = FALSE;
    } else if (x_574aae97(player, &x_73dff70e)) {
        x_5ad6e307 = TRUE;
    } else if (x_cb6a0d41(player, &x_73dff70e, FALSE)) {
        x_5ad6e307 = FALSE;
    } else {
        x_5587ad5e(player);
        return FALSE;
    }

    if (x_5ad6e307 && (x_73dff70e->flags & x_42f9acb6) &&
        (x_824b9544[x_de68d2a6].x_7f68c36b->flags & (x_7507aa4b | x_eac5209f)) && !x_77831b2c[x_de68d2a6].x_03604d94 &&
        !(x_824b9544[x_de68d2a6].flags & x_6de2d515)) {
        return FALSE;
    }

    if (!x_5ad6e307 && x_84ff873b) {
        return FALSE;
    }

    if (x_5ad6e307 & x_84ff873b) { // typo ??
        x_5ad6e307 = FALSE;
    }

    x_35bfa5f2 = 0;

    x_1e623531 = 1 << x_77831b2c[player->x_30bbe547].x_cc57155e;
    x_42126496 = player->x_7f68c36b->flags;
    x_d7f0204f = player->flags;

    do {
        x_cf2c3c6e = x_73dff70e->x_ba159dbf;
        while (*x_cf2c3c6e != -1) {
            x_1fd4d41c = &player->x_ad9d3e42[*x_cf2c3c6e & 0xFF];
            x_cf2c3c6e++;

            if (x_1fd4d41c->x_1350cb4d <= x_9a96200f + 200 && x_1fd4d41c->x_62addb22 >= x_9a96200f - 200) {
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

                if (x_9a96200f > 800 && !(player->x_81570fde.x_b2c79d6e & x_c98846bd)) {
                    if (x_77831b2c[player->x_30bbe547].x_cc57155e <= 3) {
                        x_e914de48(player, x_4a0f5c6c, TRUE);
                        x_dab0846a(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss fwd");
                        player->x_81570fde.x_ca75ac5d = x_c292dfa6;
                    } else {
                        x_e914de48(player, x_a8ddcce3, TRUE);
                        x_dab0846a(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default dash fwd");
                    }

                    player->x_81570fde.x_b2c79d6e &= ~(x_dc8d9492 | x_83011c23);
                    player->x_81570fde.x_b2c79d6e |= x_c98846bd;
                } else if (x_9a96200f < 800 && !(player->x_81570fde.x_b2c79d6e << 19)) { // ???
                    if (x_77831b2c[player->x_30bbe547].x_cc57155e <= 3) {
                        x_e914de48(player, x_96d30734, TRUE);
                        x_dab0846a(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss bak");
                        player->x_81570fde.x_ca75ac5d = x_c292dfa6;
                    } else {
                        x_e914de48(player, x_6cd07703, TRUE);
                        x_dab0846a(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default dash bak");
                    }

                    player->x_81570fde.x_b2c79d6e &= ~(x_c98846bd | x_83011c23);
                    player->x_81570fde.x_b2c79d6e |= x_dc8d9492;
                } else {
                    if (guRandom() & 1 & x_e3a9f332) {
                        x_dab0846a(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss in");
                        if (!x_e914de48(player, x_35f07eb8, TRUE)) {
                            return FALSE;
                        }
                        player->x_81570fde.x_ca75ac5d = NULL;
                    } else {
                        x_dab0846a(x_824b9544[x_6f0b3be3].x_81570fde.x_599a5202, "Default ss out");
                        if (!x_e914de48(player, x_98c27b4d, TRUE)) {
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

            if (x_cb6a0d41(player, &x_73dff70e, FALSE)) {
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

    return x_9f09065b(player, x_81570fde) && x_c41ec21f(player);
}

s16 x_96d51072(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    if (player->obj->x_5fcb1654 < (player->x_7f68c36b->x_bab9966d >> 1)) {
        return TRUE;
    }

    x_4b1172f5 = x_99de1125(player, &x_73dff70e);
    return (x_9a96200f > player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & x_42f9acb6));
}

s16 x_96cd9330(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    x_4b1172f5 = x_99de1125(player, &x_73dff70e);
    return (x_9a96200f > player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & x_42f9acb6));
}

s16 x_456d0051(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    x_4b1172f5 = x_99de1125(player, &x_73dff70e);

    if (player->obj->x_5fcb1654 < (player->x_7f68c36b->x_bab9966d >> 1)) {
        return TRUE;
    }

    return (x_9a96200f < player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & x_42f9acb6));
}

s16 x_30f96d57(Player *player) {
    return 0;
}

s16 x_09f9ea13(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    u8 x_4b1172f5;

    x_4b1172f5 = x_99de1125(player, &x_73dff70e);

    if (player->x_81570fde.x_5a6554ba) {
        player->x_81570fde.x_5a6554ba--;
    }

    return (player->x_81570fde.x_5a6554ba) && !(player->flags & x_9298c772) &&
           (!x_4b1172f5 || (x_73dff70e->flags & x_42f9acb6));
}

s16 x_02127c90(Player *player) {
    if (player->obj->x_5fcb1654 < (player->x_7f68c36b->x_bab9966d >> 1)) {
        return TRUE;
    }

    return FALSE;
}

s16 x_9b936c80(Player *player) {
    if (--player->x_81570fde.x_5a6554ba > 0) {
        return TRUE;
    } else {
        return -1;
    }
}

s16 x_54e2b66c(Player *player) {
    return -1;
}

s16 x_a92b640d(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s16 x_de68d2a6;
    s16 x_5fcb1654;
    s16 x_fedecf5c;
    s16 x_c53ac2df;
    Player *x_98c4e5a5;

    x_de68d2a6 = 1 - player->x_30bbe547;
    x_5fcb1654 = x_824b9544[x_de68d2a6].obj->x_5fcb1654;
    x_fedecf5c = x_824b9544[x_de68d2a6].x_7f68c36b->x_fedecf5c;
    x_c53ac2df = x_824b9544[x_de68d2a6].x_7f68c36b->x_c53ac2df;

    if (player->flags & x_d8a402c3) {
        return TRUE;
    }
    if (player->x_81570fde.x_60227f92 >= D_80049D34[x_77831b2c[player->x_30bbe547].x_cc57155e] &&
        !(x_824b9544[1 - player->x_30bbe547].flags & x_c15491f2)) {
        return FALSE;
    }

    player->x_81570fde.x_5a6554ba--;

    if (x_99de1125(player, &x_73dff70e) && !(x_73dff70e->flags & x_42f9acb6)) {
        if (x_73dff70e->flags & x_43a0d261) {
            x_c05bfb58(player, x_28ed5d80, TRUE);
        }
        return TRUE;
    }

    x_98c4e5a5 = x_824b9544 + x_de68d2a6;
    if ((x_824b9544[x_de68d2a6].flags & x_9298c772) ||
        !(x_98c4e5a5->flags & x_c15491f2) && player->x_81570fde.x_5a6554ba < 20 &&
            ((x_5fcb1654 < x_c53ac2df && D_80049DB4[x_98c4e5a5->x_eb1fe45b] < x_c53ac2df - x_5fcb1654) ||
             (x_fedecf5c < x_5fcb1654 &&
              D_80049DCC[x_98c4e5a5->x_eb1fe45b] < x_824b9544[x_de68d2a6].x_7f68c36b->x_bab9966d - x_fedecf5c) ||
             ((x_824b9544[1 - player->x_30bbe547].flags & x_030d2322) &&
              x_824b9544[1 - player->x_30bbe547].obj->x_5fcb1654 < 6))) {
        player->x_cd14c741 = 216;
        return -1;
    }

    return player->x_81570fde.x_5a6554ba > 0 || !(x_73dff70e->flags & x_42f9acb6);
}

s16 x_8b270b48(Player *player) {
    s16 x_de68d2a6 = 1 - player->x_30bbe547;
    s32 pad;
    x_ccb3bba0 *x_73dff70e;
    u8 v0;

    if (player->flags & x_d8a402c3) {
        return TRUE;
    }

    if (player->x_81570fde.x_60227f92 >= D_80049D34[x_77831b2c[player->x_30bbe547].x_cc57155e] &&
        !(x_824b9544[1 - player->x_30bbe547].flags & x_c15491f2)) {
        return FALSE;
    }

    player->x_81570fde.x_5a6554ba--;
    v0 = x_99de1125(player, &x_73dff70e);
    if (v0 && !(x_73dff70e->flags & x_42f9acb6)) {
        if (!(x_73dff70e->flags & x_43a0d261)) {
            x_c05bfb58(player, x_01ff67cd, TRUE);
        }
        return TRUE;
    }

    if (x_824b9544[x_de68d2a6].flags & x_9298c772) {
        player->x_cd14c741 = 42;
        return -1;
    }

    return (player->x_81570fde.x_5a6554ba > 0) || !(x_73dff70e->flags & x_42f9acb6);
}

u8 x_463aa1ee(Player *player) {
    switch (x_028e5846) {
        case x_8bfc1f62:
            switch (x_77831b2c[player->x_30bbe547].x_cc57155e) {
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
            switch (x_77831b2c[player->x_30bbe547].x_cc57155e) {
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

s16 x_92798f35(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s32 pad[2];
    u8 v0;
    s16 x_30bbe547 = player->x_30bbe547;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < D_80049D34[x_77831b2c[x_30bbe547].x_cc57155e]) {
        v0 = x_99de1125(player, &x_73dff70e);
        if (v0 && !(x_73dff70e->flags & x_42f9acb6) && !(x_73dff70e->flags & x_43a0d261)) {
            x_c05bfb58(player, x_01ff67cd, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 x_88a987a4(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s16 x_de68d2a6;
    s16 x_c9614940;
    s16 x_18643961;
    s16 x_32f1d6e2;
    Player *x_98c4e5a5;

    x_de68d2a6 = 1 - player->x_30bbe547;
    x_c9614940 = x_824b9544[x_de68d2a6].obj->x_5fcb1654;
    x_18643961 = x_824b9544[x_de68d2a6].x_7f68c36b->x_fedecf5c;
    x_32f1d6e2 = x_824b9544[x_de68d2a6].x_7f68c36b->x_c53ac2df;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < D_80049D34[x_77831b2c[player->x_30bbe547].x_cc57155e]) {
        if (x_99de1125(player, &x_73dff70e)) {
            if (!(x_73dff70e->flags & x_42f9acb6) && !(x_73dff70e->flags & x_43a0d261)) {
                x_c05bfb58(player, x_01ff67cd, TRUE);
                return 1;
            }
        }
    }

    x_98c4e5a5 = x_824b9544 + x_de68d2a6;
    if (!(x_98c4e5a5->flags & x_c15491f2)) {
        if ((x_c9614940 < x_32f1d6e2 && D_80049DB4[x_98c4e5a5->x_eb1fe45b] < x_32f1d6e2 - x_c9614940) ||
            (x_18643961 < x_c9614940 &&
             D_80049DCC[x_98c4e5a5->x_eb1fe45b] < x_824b9544[x_de68d2a6].x_7f68c36b->x_bab9966d - x_18643961) ||
            ((x_824b9544[1 - player->x_30bbe547].flags & x_030d2322) &&
             x_824b9544[1 - player->x_30bbe547].obj->x_5fcb1654 < 6)) {
            player->flags &= ~x_d8a402c3;
            return -1;
        }
    }

    return 1;
}

s16 x_9aa019dc(Player *player) {
    player->x_81570fde.x_4390a1c3 = 0;
    player->x_81570fde.x_60227f92++;

    if (x_463aa1ee(player)) {
        player->x_81570fde.x_ca75ac5d = x_88a987a4;
        return x_88a987a4(player);
    } else {
        player->x_81570fde.x_ca75ac5d = x_92798f35;
        return x_92798f35(player);
    }
}

s16 x_01906465(Player *player) {
    s32 pad[2];
    x_ccb3bba0 *x_73dff70e;
    u8 v0;
    s16 x_30bbe547 = player->x_30bbe547;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < D_80049D34[x_77831b2c[x_30bbe547].x_cc57155e]) {
        v0 = x_99de1125(player, &x_73dff70e);
        if (v0 && !(x_73dff70e->flags & x_42f9acb6) && (x_73dff70e->flags & x_43a0d261)) {
            x_c05bfb58(player, x_28ed5d80, TRUE);
            return 1;
        }
    }

    return 1;
}

s16 x_3f4966fe(Player *player) {
    s16 x_de68d2a6;
    s16 x_c9614940;
    s16 x_18643961;
    s16 x_32f1d6e2;
    x_ccb3bba0 *x_73dff70e;
    Player *x_98c4e5a5;

    x_de68d2a6 = 1 - player->x_30bbe547;
    x_c9614940 = x_824b9544[x_de68d2a6].obj->x_5fcb1654;
    x_18643961 = x_824b9544[x_de68d2a6].x_7f68c36b->x_fedecf5c;
    x_32f1d6e2 = x_824b9544[x_de68d2a6].x_7f68c36b->x_c53ac2df;

    player->x_81570fde.x_5a6554ba--;

    if (player->x_81570fde.x_60227f92 < D_80049D34[x_77831b2c[player->x_30bbe547].x_cc57155e]) {
        if (x_99de1125(player, &x_73dff70e)) {
            if (!(x_73dff70e->flags & x_42f9acb6) && (x_73dff70e->flags & x_43a0d261)) {
                x_c05bfb58(player, x_28ed5d80, TRUE);
                return 1;
            }
        }
    }

    x_98c4e5a5 = x_824b9544 + x_de68d2a6;
    if (!(x_98c4e5a5->flags & x_c15491f2) && x_463aa1ee(player)) {
        if ((x_c9614940 < x_32f1d6e2 && D_80049DB4[x_98c4e5a5->x_eb1fe45b] < x_32f1d6e2 - x_c9614940) ||
            (x_18643961 < x_c9614940 &&
             D_80049DCC[x_98c4e5a5->x_eb1fe45b] < x_824b9544[x_de68d2a6].x_7f68c36b->x_bab9966d - x_18643961) ||
            ((x_824b9544[1 - player->x_30bbe547].flags & x_030d2322) &&
             x_824b9544[1 - player->x_30bbe547].obj->x_5fcb1654 < 6)) {
            player->flags &= ~x_d8a402c3;
            return -1;
        }
    }

    return 1;
}

s16 x_8985d3ca(Player *player) {
    player->x_81570fde.x_4390a1c3 = 0;
    player->x_81570fde.x_60227f92++;

    if (x_463aa1ee(player)) {
        player->x_81570fde.x_ca75ac5d = x_3f4966fe;
        return x_3f4966fe(player);
    } else {
        player->x_81570fde.x_ca75ac5d = x_01906465;
        return x_01906465(player);
    }
}

s16 x_b8c2dd87(Player *player) {
    s16 x_f6289181;

    x_f6289181 = x_77831b2c[player->x_30bbe547].x_cc57155e;
    player->x_81570fde.x_5a6554ba = D_80049D44[x_f6289181] + (guRandom() & D_80049D24[x_f6289181]); // @BUG ??
    player->x_81570fde.x_ca75ac5d = x_9b936c80;
    return 1;
}

s16 x_c292dfa6(Player *player) {
    x_ccb3bba0 *x_73dff70e;
    s32 x_4b1172f5;

    x_4b1172f5 = x_99de1125(player, &x_73dff70e);

    if (player->obj->x_5fcb1654 < (player->x_7f68c36b->x_bab9966d >> 1) && !(player->flags & x_9298c772)) {
        return TRUE;
    }

    if (player->obj->x_5fcb1654 < player->x_7f68c36b->x_bab9966d - 1 && !(player->flags & x_9298c772) &&
        (!x_4b1172f5 || (x_73dff70e->flags & x_42f9acb6))) {
        return TRUE;
    }

    return FALSE;
}

s16 x_f7322749(Player *player) {
    s16 x_5bbba600;
    s32 pad;
    s16 pad2;
    s16 x_32f1d6e2;

    x_5bbba600 = x_77831b2c[player->x_30bbe547].x_cc57155e;
    x_32f1d6e2 = D_80049D54[x_5bbba600];
    x_32f1d6e2 += guRandom() % D_80049D64[x_5bbba600];
    player->x_81570fde.x_4390a1c3++;

    if (x_32f1d6e2 < player->x_81570fde.x_4390a1c3 || (x_824b9544[1 - player->x_30bbe547].flags & x_4d950171)) {
        player->x_81570fde.x_9daba480++;
        x_9f09065b(player, &player->x_81570fde);
        x_c41ec21f(player);
        player->x_81570fde.x_5a6554ba = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 x_4f67a505(Player *player) {
    s16 x_cc57155e;
    s32 pad;
    s16 pad2;
    s16 x_32f1d6e2;

    x_cc57155e = x_77831b2c[player->x_30bbe547].x_cc57155e;
    x_32f1d6e2 = D_80049D54[x_cc57155e];
    x_32f1d6e2 += guRandom() % D_80049D64[x_cc57155e];
    player->x_81570fde.x_4390a1c3++;

    if (x_32f1d6e2 < player->x_81570fde.x_4390a1c3 || (x_824b9544[1 - player->x_30bbe547].flags & x_4d950171)) {
        player->x_81570fde.x_9daba480++;
        x_9f09065b(player, &player->x_81570fde);
        x_c41ec21f(player);
        player->x_81570fde.x_5a6554ba = 90;
        return 1;
    } else {
        return -1;
    }
}

s16 x_449f1966(Player *player) {
    x_ccb3bba0 *x_73dff70e;

    if (x_99de1125(player, &x_73dff70e)) {
        if (!(x_73dff70e->flags & x_42f9acb6)) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}

s16 x_61604a34(Player *player) {
    player->x_81570fde.x_ca75ac5d = NULL;
    player->x_81570fde.x_9daba480 -= 2;
    return 1;
}
