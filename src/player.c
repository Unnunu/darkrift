#include "common.h"
#include "task.h"
#include "camera.h"

typedef struct x_30c860fe {
    /* 0x00 */ s16 x_9200c538[2];
    /* 0x04 */ s16 x_a6423339;
    /* 0x06 */ u8 x_30bbe547;
    /* 0x07 */ u8 x_4deaa42c;
} x_30c860fe; // size=0x8

typedef struct x_64923535 {
    /* 0x0000 */ x_30c860fe x_af0aa1f8[512];
    /* 0x1000 */ u16 x_d0d13a9c;
    /* 0x1002 */ u16 x_ffd925e9;
    /* 0x1004 */ s32 x_69d9d5da;
    /* 0x1008 */ s32 x_77f7a44f;
} x_64923535; // size = 0x100C

extern s16 D_8004A730[];
extern s16 D_8004A748[];
extern x_2bb4cf6f D_8004B644;
extern x_2bb4cf6f D_8004B664;
extern x_2bb4cf6f D_8004B764;
extern x_2bb4cf6f D_8004B784;
extern x_6dac5499 D_8004B94C[];
extern x_edf8d3f1 D_8004C1E8[];

extern s32 D_80080218;
extern x_64923535 D_80080238;

/* .bss */
s16 x_5e4e2788;
s16 x_1acf99bf;
u16 D_80080234;
u16 D_80080236;
x_64923535 D_80080238;

void x_ed9e2514(x_056d4f07 *x_cc1d0de5, x_6fcfcf46 *x_84ff873b, x_f9704fd6 *x_2092f891, x_f9704fd6 *x_ee71e5cb,
                x_88f11482 *x_a0e63e9c, x_6751d717 *x_1011f751);

void x_84aa5a13(s16 x_30bbe547);
void x_252b14e4(Object *obj);

typedef struct x_4a3b281c {
    /* 0x00 */ s32 x_af0aa1f8;
    /* 0x04 */ s32 x_554ac37d;
    /* 0x08 */ s32 x_6e32552b;
    /* 0x0C */ s32 x_b8173ab8;
    /* 0x10 */ s32 x_60c27ea9;
    /* 0x14 */ s32 x_8ebab1d0;
    /* 0x18 */ s32 x_429c730a;
    /* 0x1C */ s32 x_2c79259e;
    /* 0x20 */ s32 x_59f97427;
    /* 0x24 */ s32 x_817784f2;
    /* 0x28 */ s32 x_e4ca14d3;
    /* 0x2C */ s32 x_38b3091d;
    /* 0x30 */ s32 x_49e4c93e;
    /* 0x34 */ s32 x_8cd129ed;
    /* 0x38 */ s32 x_251abb64;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 x_a484ea08;
} x_4a3b281c; // size = 0x44

extern s16 D_8004B9FC[];

#ifdef NON_MATCHING
/**
 * player_replay_record - Record current player state into replay buffer.
 * Captures player index, action ID, opponent state, and timestamps into circular buffer (512 entries).
 * Increments buffer head, tracks frame delta, sets overflow flag when head catches tail.
 * Params: player - Player to record
 */
void x_5f34c321(Player *player) {
    x_30c860fe *a1;
    u16 t8;
    u16 a2;
    Object *v0;
    s32 v1;
    s32 x_b3c51f8a;
    s32 temp;

    v0 = player->obj;

    if (D_80080236 || x_9df63a90) {
        return;
    }
    v1 = D_80080238.x_ffd925e9;
    a1 = D_80080238.x_af0aa1f8 + v1;
    a1->x_a6423339 = player->x_a6423339;
    a1->x_30bbe547 = player->x_30bbe547;
    a1->x_4deaa42c = 255;

    t8 = 1 - player->x_30bbe547;
    a2 = player->x_30bbe547;
    a1->x_9200c538[a2] = v0->x_9200c538;
    a1->x_9200c538[t8] = x_824b9544[t8].obj->x_9200c538;

    x_b3c51f8a = D_80080238.x_ffd925e9;
    D_80080238.x_af0aa1f8[((x_b3c51f8a - 1) & 0x1FF)].x_4deaa42c = gFrameCounter - D_80080238.x_69d9d5da;

    x_b3c51f8a = (x_b3c51f8a + 1) & 0x1FF;
    D_80080238.x_ffd925e9 = x_b3c51f8a;
    D_80080238.x_69d9d5da = gFrameCounter;

    if (x_b3c51f8a == D_80080238.x_d0d13a9c) {
        D_80080234 = 1;
        D_80080238.x_d0d13a9c = (D_80080238.x_d0d13a9c + 1) & 0x1FF;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/player/x_5f34c321.s")
void x_5f34c321(Player *player);
#endif

/**
 * player_replay_set_overflow - Mark replay buffer as overflowed and set object flag.
 * Called when replay buffer wraps around.
 * Params: obj - Object to flag
 */
void x_6c813c97(Object *obj) {
    obj->flags |= x_f51cb721;
    D_80080234 = 1;
}

/**
 * player_replay_check_timeout - Check if replay playback should end.
 * Ends replay if opponent health <= 0 or replay timer expires.
 * Sets next task to overflow handler with 55-frame delay.
 * Params: obj - replay Object
 */
void x_e3e68cfd(Object *obj) {
    if (x_824b9544[1 - D_8013C24C].obj->x_9200c538 <= 0 || --obj->x_0f4167b4[0] <= 0) {
        obj->currentTask->delay = 55;
        obj->currentTask->callback = x_6c813c97;
    }
}

#ifdef NON_MATCHING
void x_394387b3(Object *obj) {
    s32 s0;
    x_30c860fe *s1;
    s32 s3;
    s16 v0;
    s32 temp;
    Player *s2;

    while (TRUE) {
        s0 = D_80080238.x_d0d13a9c;
        s1 = D_80080238.x_af0aa1f8 + s0;
        s3 = s1->x_30bbe547;

        x_824b9544[s3].flags |= x_cf6c9b89;
        x_9d4a1d61(x_824b9544 + s3, TRUE, s1->x_a6423339);
        v0 = s1->x_9200c538[s3];
        x_824b9544[s3].obj->x_9200c538 = v0;
        if (v0 == 0) {
            x_e30d50d2 |= x_dd99cbfb;
        }

        if (s1->x_4deaa42c == 255) {
            break;
        }

        s0++;
        D_80080238.x_d0d13a9c = s0 & ~0x200;

        temp = s1->x_4deaa42c;

        if (obj && obj && obj) {} // @fake

        if (temp != 0) {
            obj->currentTask->delay = temp - 1;
            return;
        }
    }

    if (s1) {} // @fake
    obj->currentTask->callback = x_e3e68cfd;
    obj->x_0f4167b4[0] = 260;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/player/x_394387b3.s")
void x_394387b3(Object *obj);
#endif

void x_33a76c83(Object *obj) {
    task_execute(obj);

    if (x_59ce598c[D_8013C24C].buttons & x_9cefe76c) {
        obj->flags |= x_f51cb721;
        D_80080234 = 1;
        D_8013C23C->currentTask->delay = 0;
        D_8013C23C->currentTask->callback = x_3da93607;
        x_59ce598c[D_8013C24C].x_c4397934 = FALSE;
    }
}

s32 x_5d1cb2ec(void *x_cc1d0de5) {
    s32 s3;
    Object *v0;
    u32 i;
    s32 temp;

    s3 = gFrameCounter - D_80080238.x_77f7a44f;

    D_80080238.x_d0d13a9c = 0;
    x_33abac12 = 1;
    x_824b9544[x_83106b21].x_cd14c741 = 0;
    x_824b9544[x_6f0b3be3].x_cd14c741 = 0;

    x_84aa5a13(x_83106b21);
    x_84aa5a13(x_6f0b3be3);
    x_824b9544[x_83106b21].obj->frameCounter = 2;
    x_824b9544[x_6f0b3be3].obj->frameCounter = 2;
    x_0f2c2c2a(x_824b9544[x_83106b21].obj);
    x_0f2c2c2a(x_824b9544[x_6f0b3be3].obj);

    x_e5c4361f(&x_824b9544[x_83106b21].x_a4d7c80d.x_3fde9cd9);
    x_e5c4361f(&x_824b9544[x_83106b21].x_022dff72.x_3fde9cd9);
    x_e5c4361f(&x_824b9544[x_6f0b3be3].x_a4d7c80d.x_3fde9cd9);
    x_e5c4361f(&x_824b9544[x_6f0b3be3].x_022dff72.x_3fde9cd9);

    x_2a8d0730(x_824b9544[x_83106b21].obj);
    x_2a8d0730(x_824b9544[x_6f0b3be3].obj);
    x_824b9544[x_83106b21].obj->x_2b06a023 = x_824b9544[x_83106b21].obj->frameCounter;
    x_824b9544[x_6f0b3be3].obj->x_2b06a023 = x_824b9544[x_6f0b3be3].obj->frameCounter;
    x_824b9544[x_83106b21].x_b9252303->flags &= ~TASK_TIME_BASED;
    x_824b9544[x_6f0b3be3].x_b9252303->flags &= ~TASK_TIME_BASED;

    x_09a33777 = 0x800;
    x_70e8be1f(x_f4bce728);
    x_f4bce728->currentTask->callback = x_31bdfdc5;
    x_f4bce728->currentTask->delay = 0;
    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -400;
    x_6f8aa7af = FALSE;

    temp = guRandom() % 2;

    if (temp) {}

    v0 = x_4495b42c(x_33a76c83, -0x7001 + temp * 0);
    v0->currentTask->callback = x_394387b3;
    v0->currentTask->delay = 0;
    v0->currentTask->flags = TASK_RUNNABLE;

    D_8008012C |= x_f846a903;
    x_e30d50d2 &= ~x_dd99cbfb;

    if (s3 > 960) {
        s3 -= 960;
        for (i = 0; i < s3; i++) {
            x_252b14e4(x_824b9544[x_83106b21].obj);
            x_252b14e4(x_824b9544[x_6f0b3be3].obj);
            x_33a76c83(v0);
        }

        x_076ece50(x_f4bce728, TRUE);
    }

    return 0;
}

s32 x_b89e43c0(void) {
    s32 x_df087996 = gFrameCounter - D_80080238.x_77f7a44f;

    if (x_df087996 < 60) {
        return FALSE;
    } else {
        x_71257e81(x_5d1cb2ec, NULL);
        return TRUE;
    }
}

void x_252b14e4(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    u16 x_30bbe547 = player->x_30bbe547;
    s32 unused[7];
    x_6fcfcf46 *x_3bae2428 = obj->x_20d20338;

    if (x_af5ccc8a(obj)) {
        player->flags |= x_9298c772;
    } else {
        player->flags &= ~x_9298c772;
    }

    task_execute(obj);

    if (x_3bae2428->x_ee205ef9 != x_3bae2428->x_2f4c4ce1) {
        x_0f2c2c2a(obj);
        x_3bae2428->x_2f4c4ce1 = x_3bae2428->x_ee205ef9;
    }

    if (obj->frameCounter != obj->x_2b06a023) {
        x_b6e96a17(obj);
        x_2a8d0730(obj);
        obj->x_2b06a023 = obj->frameCounter;
    }

    if (x_af5ccc8a(obj)) {
        player->flags |= x_9298c772;
    } else {
        player->flags &= ~x_9298c772;
    }

    if (player->x_cadf184a) {
        if (player->x_448f0851 != 0 && --player->x_448f0851 == 0) {
            x_253cc396(player, TRUE);
        } else if (!(player->flags & (x_030d2322 | x_4d950171)) && x_59ce598c[x_30bbe547].x_c4397934 &&
                   player->x_0a8e33d7 >= 0 && !(player->x_b9252303->flags & TASK_TIME_BASED)) {
            x_253cc396(player, FALSE);
        }
    }

    player->x_cadf184a = TRUE;
}

void x_86740bd7(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    u16 x_30bbe547 = player->x_30bbe547;
    u16 x_de68d2a6;
    Player *x_98c4e5a5;
    x_388306ba *x_8cc4f7df;
    x_388306ba *x_0efa5bb1;
    s32 pad[2];
    Object *x_44d73ae1;
    u8 pad2;
    u8 x_36512335;

    x_8cc4f7df = player->x_7f68c36b;
    x_de68d2a6 = 1 - x_30bbe547;
    x_98c4e5a5 = &x_824b9544[x_de68d2a6];
    x_0efa5bb1 = x_98c4e5a5->x_7f68c36b;
    x_44d73ae1 = x_98c4e5a5->obj;

    if (x_af5ccc8a(obj)) {
        player->flags |= x_9298c772;
    } else {
        player->flags &= ~x_9298c772;
    }

    x_0022bfc3(obj);

    if (x_af5ccc8a(obj)) {
        player->flags |= x_9298c772;
    } else {
        player->flags &= ~x_9298c772;
    }

    x_36512335 = (x_8cc4f7df->x_6f5a5c61 != 0) && (obj->frameCounter >= x_8cc4f7df->x_946f41d3) &&
                 (obj->frameCounter < x_8cc4f7df->x_79b8e870);

    x_f7a1a468(&player->x_d8a19723, (x_8cc4f7df->flags & x_74a8ee84) && x_36512335);
    if (player->x_8bc5a2ac) {
        x_f7a1a468(&player->x_238ba16f, (x_8cc4f7df->flags & x_3e0e6012) && x_36512335);
    }
    x_f7a1a468(&player->x_29c9094f, (x_8cc4f7df->flags & x_0fe9e7f2) && x_36512335);
    x_f7a1a468(&player->x_a241ea2a, (x_8cc4f7df->flags & (x_a83332f6 | x_bd969186)) && x_36512335);

    if (player->x_eb1fe45b != x_b52da315) {
        x_5ff12555(obj);
    }

    if (gTaskLock) {
        return;
    }

    if (x_5e4e2788 == x_79c2dc5b) {
        if (D_8013C430 == 16) {
            x_75afee1a();
        } else if (D_8013C430 == 18) {
            x_65b38a11();
        }
        if (D_8013C434 == 66) {
            x_65b38a11();
        }
    }

    if (x_77831b2c[x_30bbe547].x_03604d94 && !x_9df63a90 && !(player->flags & x_4d950171)) {
        if (!(player->x_81570fde.x_b2c79d6e & x_c74d666c)) {
            x_da66d1d5(player);
        }
        if (D_8013C444 && x_59ce598c[x_30bbe547].x_c4397934 && player->x_0a8e33d7 >= 0 &&
            !(player->x_b9252303->flags & TASK_TIME_BASED) && !(player->flags & x_d8a402c3)) {
            x_253cc396(player, FALSE);
        }
    } else if (player->x_cadf184a && !x_9df63a90) {
        if (player->x_448f0851 != 0 && --player->x_448f0851 == 0) {
            x_253cc396(player, TRUE);
        } else if (!(player->flags & (x_030d2322 | x_4d950171)) && x_59ce598c[x_30bbe547].x_c4397934 &&
                   player->x_0a8e33d7 >= 0 && !(player->x_b9252303->flags & TASK_TIME_BASED)) {
            x_253cc396(player, FALSE);
        }
    }

    if (player->x_381817ae > 0) {
        player->x_381817ae--;
    }

    if (x_9a96200f <= D_80080218 && !(player->x_7f68c36b->flags & x_7b8f7fad) && player->x_381817ae == 0 &&
        x_44d73ae1->frameCounter >= x_0efa5bb1->x_c53ac2df && x_44d73ae1->frameCounter <= x_0efa5bb1->x_fedecf5c) {

        if (x_0efa5bb1->flags & (x_74a8ee84 | x_3e0e6012)) {
            if ((player->x_7f68c36b->flags & (x_eac5209f | x_8b64a078 | x_c1df43e1)) &&
                obj->x_20d20338->x_abd7b3c4.x_0c1a9bdd.w.y > -100.0f) {
                x_3fe0a5ec(player, x_98c4e5a5);
            } else {
                x_a617fc50(player, x_98c4e5a5);
            }
        }

        if (player->x_381817ae == 0 && (x_0efa5bb1->flags & (x_a83332f6 | x_0fe9e7f2 | x_bd969186))) {
            if ((player->x_7f68c36b->flags & (x_eac5209f | x_8b64a078 | x_c1df43e1)) &&
                obj->x_20d20338->x_abd7b3c4.x_0c1a9bdd.w.y > -100.0f) {
                x_5a643f96(player, x_98c4e5a5);
            } else {
                x_ec2ec20a(player, x_98c4e5a5);
            }
        }
    }

    player->x_cadf184a = TRUE;
}

void x_4bd2b75c(char *x_cc1d0de5, char *x_84ff873b, char *x_2092f891) {
    x_dab0846a(x_cc1d0de5, x_84ff873b);
    x_8c518b47(x_cc1d0de5, x_2092f891);
}

typedef struct x_c92407e7 {
    /* 0x00 */ char x_af0aa1f8[12];
} x_c92407e7; // size = 0xC

typedef struct x_47670d66 {
    /* 0x00 */ s32 x_af0aa1f8;
    /* 0x04 */ x_c92407e7 x_1256da71[1];
} x_47670d66;

typedef struct x_04bc5bf5 {
    /* 0x00 */ s32 x_af0aa1f8;
    /* 0x04 */ s16 x_1256da71[1];
} x_04bc5bf5;

s16 D_80049390 = -1;
s16 D_80049394 = -1;

void x_5ca8f576(Player *);
void x_c94a154b(Player *);
s32 x_a2f41f91(s32 x_cc1d0de5);

void x_0e475fbe(x_4a3b281c *x_cc1d0de5, s16 x_30bbe547) {
    x_47670d66 *v1;
    x_04bc5bf5 *a2;
    s32 s2;
    s32 i;
    s32 pad;

    x_824b9544[x_30bbe547].x_994b73a7 = x_cc1d0de5->x_49e4c93e + (u32) x_cc1d0de5;
    x_824b9544[x_30bbe547].x_4ec7bbf8 = x_cc1d0de5->x_8cd129ed + (u32) x_cc1d0de5;

    v1 = x_cc1d0de5->x_251abb64 + (u32) x_cc1d0de5;
    x_824b9544[x_30bbe547].x_81ca4eb2 = v1->x_af0aa1f8;
    x_824b9544[x_30bbe547].x_ad9d3e42 = v1->x_1256da71;
    x_824b9544[x_30bbe547].x_d908b580 = v1->x_af0aa1f8 + v1->x_1256da71; // required to match

    a2 = x_cc1d0de5->unk_3C + (u32) x_cc1d0de5;
    x_824b9544[x_30bbe547].x_261980db = a2->x_af0aa1f8;
    x_824b9544[x_30bbe547].x_78242925 = a2->x_1256da71;
    x_824b9544[x_30bbe547].x_0bc74042 =
        (((a2->x_af0aa1f8 & 1) + a2->x_af0aa1f8) & 0xFFFFFFFF) + a2->x_1256da71; // required to match

    x_824b9544[x_30bbe547].x_81570fde.x_b2c79d6e = x_c74d666c;
    x_824b9544[x_30bbe547].x_81570fde.x_14906c66[0] = NULL;
    x_824b9544[x_30bbe547].x_81570fde.x_9daba480 = &D_80049394;
    x_824b9544[x_30bbe547].x_81570fde.x_76cf2d04 = &D_80049394;
    x_824b9544[x_30bbe547].x_81570fde.x_ca75ac5d = 0;
    x_824b9544[x_30bbe547].x_81570fde.x_5a6554ba = 0;
    x_824b9544[x_30bbe547].x_81570fde.x_5c398490 = 0;

    x_59ce598c[x_30bbe547].enabled = FALSE;

    if (x_5e4e2788 == x_3658fb97) {
        if (x_30bbe547 != x_83106b21) {
            x_9308b483(x_824b9544 + x_30bbe547);
        } else {
            x_5ca8f576(x_824b9544 + x_83106b21);
        }
    } else if (x_77831b2c[x_30bbe547].x_8a8d66c9) {
        if (x_028e5846 == x_d286d6eb && x_77831b2c[x_30bbe547].x_cc57155e == 0) {
            x_77831b2c[x_30bbe547].x_cc57155e = 2;
        }
        s2 = x_77831b2c[x_30bbe547].x_cc57155e;

        x_9308b483(x_824b9544 + x_30bbe547);
        x_77831b2c[x_30bbe547].x_8a8d66c9 = FALSE;
        for (i = 0; i < s2; i++) {
            x_c94a154b(x_824b9544 + x_30bbe547);
        }
    } else {
        switch (x_028e5846) {
            case x_c74743bd:
            case x_d286d6eb:
                x_c94a154b(x_824b9544 + x_30bbe547);
                break;
            case x_8bfc1f62:
                switch (x_a2f41f91(x_30bbe547)) {
                    case 0:
                        x_5ca8f576(x_824b9544 + x_30bbe547);
                        break;
                    default:
                        x_c94a154b(x_824b9544 + x_30bbe547);
                        break;
                    case 4:
                    case 7:
                        break;
                }
                break;
        }
    }
}

void x_8ec7508a(s16 x_30bbe547, s16 x_eb1fe45b) {
    char x_dd9604d9[20];
    char x_dcccc364[20];
    x_388306ba *s0;
    s32 *pad3;
    s32 *x_8a9089b3;
    Player *player;
    x_6fcfcf46 *x_20d20338;
    s16 a12;
    x_7bac7836 *x_fc517ba8;
    x_4a3b281c *s3;
    s32 i;
    s32 pad;
    s16 q;
    s16 x_464d68e5; // sp54?
    s16 pad2;
    s16 x_2a89e429;

    player = &x_824b9544[x_30bbe547];
    x_20d20338 = player->obj->x_20d20338;
    x_fc517ba8 = &x_77831b2c[x_30bbe547];
    x_2a89e429 = x_77831b2c[1 - x_30bbe547].x_eb1fe45b;

    if (x_fc517ba8->x_178eafa6) {
        x_dab0846a(x_dcccc364, "dum.db");
    } else {
        x_4bd2b75c(x_dcccc364, D_8004B844[x_eb1fe45b].x_1256da71->name, ".db");
    }

    s3 = (x_4a3b281c *) x_b717ed65[x_e720f37d(x_dcccc364, x_30bbe547)].data;
    player->x_cfd37298 = s3->x_af0aa1f8 + (u32) s3;
    player->x_1af5b64c = pad = s3->x_554ac37d + 4 + (u32) s3;
    player->x_b8b27276 = s3->x_6e32552b + (u32) s3;
    player->x_a1696a6b = s3->x_b8173ab8 + (u32) s3;
    player->x_ae3aa7af = s3->x_60c27ea9 + (u32) s3;

    x_8a9089b3 = s3->x_8ebab1d0 + (u32) s3;
    if (x_fc517ba8->x_178eafa6) {
        *x_8a9089b3 = 0;
    }
    player->x_68a6b5cd = s0 = (u32) s3 + s3->x_8ebab1d0 + 4;

    player->x_429c730a = pad = s3->x_429c730a + (u32) s3 + 4;
    pad3 = s3->x_2c79259e + (u32) s3;
    player->x_ea8ec382 = *pad3;
    if (((!player->obj) && (!player->obj)) & 0xFFFFFFFFu) {} // @fake
    player->x_59f97427 = s3->x_59f97427 + (u32) s3;
    player->x_8b00beac = s3->x_817784f2 + (u32) s3;
    player->x_e4ca14d3 = s3->x_e4ca14d3 + (u32) s3;
    player->x_38b3091d = s3->x_38b3091d + (u32) s3;
    player->x_c42e3970 = s3->x_a484ea08 + (u32) s3;

    x_dab0846a(x_dd9604d9, D_8004B94C[x_2a89e429].x_1256da71);
    x_8c518b47(x_dd9604d9, ".MOV");
    if ((x_464d68e5 = x_e720f37d(x_dd9604d9, 0x5000 + x_30bbe547)) > 0) {
        q = D_8004B94C[x_2a89e429].x_af0aa1f8;
        a12 = s0[q].x_43d35340;
        x_20d20338->x_50771dcd[a12] = x_b717ed65[x_464d68e5].data;
        s0[q].x_bab9966d = x_d8998bf6(x_20d20338, a12) - 1;
    }

    x_dab0846a(x_dd9604d9, D_8004B94C[11 + x_2a89e429].x_1256da71);
    x_8c518b47(x_dd9604d9, ".MOV");
    if ((x_464d68e5 = x_e720f37d(x_dd9604d9, 0x5000 + x_30bbe547)) > 0) {
        q = D_8004B94C[11 + x_2a89e429].x_af0aa1f8;
        a12 = s0[q].x_43d35340;
        x_20d20338->x_50771dcd[a12] = x_b717ed65[x_464d68e5].data;
        if (x_2a89e429 != x_c4ddde6d) {
            s0[q].x_bab9966d = x_d8998bf6(x_20d20338, a12) - 1;
        }

        q = D_8004B9FC[x_2a89e429];
        a12 = s0[q].x_43d35340;
        x_20d20338->x_50771dcd[a12] = x_b717ed65[x_464d68e5].data;
        s0[q].x_bab9966d = x_d8998bf6(x_20d20338, a12) - 1;
    }

    player->x_cd14c741 = 0;

    for (i = 0; i < *x_8a9089b3; i++, s0++) {
        if (s0->x_bab9966d == -1) {
            s0->x_bab9966d = x_d8998bf6(x_20d20338, s0->x_43d35340) - 1;
        } else if (x_d8998bf6(x_20d20338, s0->x_43d35340) < s0->x_bab9966d) {
            s0->x_bab9966d = x_d8998bf6(x_20d20338, s0->x_43d35340) - 1;
        }

        if (s0->x_946f41d3 == -1 || s0->x_79b8e870 == -1) {
            s0->x_946f41d3 = s0->x_c53ac2df + 3;
            s0->x_79b8e870 = s0->x_fedecf5c - 1;
        }
    }

    if (x_fc517ba8->x_03604d94) {
        x_0e475fbe(s3, x_30bbe547);
    }

    if (x_fc517ba8->x_6128220f) {
        if (x_fc517ba8->x_178eafa6) {
            x_dab0846a(x_dcccc364, "dum.sym");
        } else {
            x_4bd2b75c(x_dcccc364, D_8004B844[x_eb1fe45b].x_1256da71->name, ".sym");
        }
        // TODO wrong structure
        s3 = (x_4a3b281c *) x_b717ed65[x_e720f37d(x_dcccc364, x_30bbe547)].data;
        player->x_b10c1d88 = s3->x_af0aa1f8 + (u32) s3;
        player->x_bfd481b9 = s3->x_554ac37d + (u32) s3;
        player->x_71560fc1 = s3->x_6e32552b + (u32) s3;
        player->x_be67e057 = s3->x_b8173ab8 + (u32) s3;
    }
}

void x_6dd7460b(Transform *x_cc1d0de5) {
    Transform *next;
    Transform *prev;

    prev = x_cc1d0de5->x_e4712596->x_171183e4;

    if (prev == x_cc1d0de5) {
        x_cc1d0de5->x_e4712596->x_171183e4 = x_cc1d0de5->x_fda6b96a;
        x_cc1d0de5->x_fda6b96a = NULL;
        return;
    }

    next = prev->x_fda6b96a;
    while (x_cc1d0de5 != next) {
        prev = next;
        next = next->x_fda6b96a;
    }

    prev->x_fda6b96a = x_cc1d0de5->x_fda6b96a;
    x_cc1d0de5->x_fda6b96a = NULL;
}

void x_a846a72a(Object *obj, s16 x_30bbe547, s16 x_2092f891) {
    Transform *s1;
    Transform *x_49781937;
    Transform *s0;
    x_43bd08ed *x_e7962160 = obj->x_20d20338->x_0094fc88;

    x_e7962160[D_8004C1D8[x_2092f891]].x = 0;
    x_e7962160[D_8004C1D8[x_2092f891]].y = 0;
    x_e7962160[D_8004C1D8[x_2092f891]].z = 0;

    s0 = &obj->x_20d20338->transforms[D_8004C1D8[x_2092f891]];
    s1 = &x_824b9544[x_30bbe547].x_a4d7c80d;
    x_f2c7456d(s0->x_e4712596, s1, -3, -3);
    s1->x_3fde9cd9.w.x = s0->x_3fde9cd9.w.x;
    s1->x_3fde9cd9.w.y = s0->x_3fde9cd9.w.y;
    s1->x_3fde9cd9.w.z = s0->x_3fde9cd9.w.z;
    x_6dd7460b(s0);
    x_49781937 = s0->x_171183e4;
    x_f2c7456d(s1, s0, -3, -3);
    s0->x_171183e4 = x_49781937;

    x_e7962160[0].x = 0;
    x_e7962160[0].y = 0;
    x_e7962160[0].z = 0;

    s0 = &obj->x_20d20338->transforms[0];
    s1 = &x_824b9544[x_30bbe547].x_022dff72;
    x_f2c7456d(s0->x_e4712596, s1, -3, -3);
    s1->x_3fde9cd9.w.x = s0->x_3fde9cd9.w.x;
    s1->x_3fde9cd9.w.y = s0->x_3fde9cd9.w.y;
    s1->x_3fde9cd9.w.z = s0->x_3fde9cd9.w.z;
    x_6dd7460b(s0);
    x_49781937 = s0->x_171183e4;
    x_f2c7456d(s1, s0, -3, -3);
    s0->x_171183e4 = x_49781937;

    D_80052D64[x_30bbe547] = D_80052D68[x_30bbe547] = D_80052D6C[x_30bbe547] = D_80052D70[x_30bbe547] =
        D_80052D74[x_30bbe547] = 0;
    D_80052D78[x_30bbe547] = 2;
}

void x_bee056cc(x_80d298c9 *x_d59386e0) {
    s16 v1;
    s16 v2;
    u8 x_42353189;

    v1 = x_77831b2c[1 - x_d59386e0->context].x_eb1fe45b;
    x_42353189 = x_d59386e0->name[6];
    x_d59386e0->name[6] = '\0';

    if (x_6b61a084(x_d59386e0->name, D_8004B94C[v1].x_1256da71) != 0) {
        v1 += 11;
        if (x_6b61a084(x_d59386e0->name, D_8004B94C[v1].x_1256da71) != 0) {
            x_d59386e0->name[0] = '\0';
            x_d59386e0->flags |= 1;
            return;
        }
    }
    x_d59386e0->name[6] = x_42353189;
    x_09120adb(x_d59386e0);
    x_d59386e0->context += 0x5000;
}

void x_16c5d7a5(s16 x_30bbe547) {
    char x_49781937[40];
    char x_32f1d6e2[12];
    u8 x_eb1fe45b = x_77831b2c[x_30bbe547].x_eb1fe45b;

    if (x_77831b2c[x_30bbe547].x_178eafa6) {
        x_dab0846a(x_49781937, "/aaro/dummy");
    } else {
        x_dab0846a(x_32f1d6e2, D_8004B844[x_eb1fe45b].x_1256da71->name);
        x_dab0846a(x_49781937, "/");
        x_8c518b47(x_49781937, x_32f1d6e2);
        x_8c518b47(x_49781937, "/");
        x_8c518b47(x_49781937, x_32f1d6e2);
        if (x_30bbe547 != x_83106b21) {
            x_8c518b47(x_49781937, "2");
        } else {
            x_8c518b47(x_49781937, "1");
        }
        if (x_77831b2c[x_30bbe547].x_fb21ca8c) {
            x_8c518b47(x_49781937, "_h");
        } else {
            x_8c518b47(x_49781937, "_v");
        }
    }

    if (x_6b61a084(x_49781937, x_824b9544[x_30bbe547].x_b920f376)) {
        x_ad9889cf(x_30bbe547);
        x_dab0846a(x_824b9544[x_30bbe547].x_b920f376, x_49781937);
    }
    D_8013C228 = x_bee056cc;
    x_0928eec2(x_49781937, x_929f65dc + x_30bbe547);
}

void x_8ba5e67e(Object *obj) {
    x_6751d717 *x_4346f5cb = obj->x_e2f64c57[0];
    x_6751d717 *x_a1fcc259 = obj->x_e2f64c57[1];
    u32 v1;

    if (--obj->x_0f4167b4[2] <= 0) {
        v1 = (guRandom() % 192) + 64;
        x_a1fcc259->r = x_4346f5cb->r * v1 / 256;
        x_a1fcc259->g = x_4346f5cb->g * v1 / 256;
        x_a1fcc259->b = x_4346f5cb->b * v1 / 256;
        obj->x_0f4167b4[2] = 8;
    }
}

void x_31116106(Object *obj) {
    Player *player = obj->x_e2f64c57[0];
    x_f9704fd6 *m = &player->obj->x_20d20338->transforms[5].x_0c1a9bdd;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

void x_04905798(Object *obj) {
    Player *player = obj->x_e2f64c57[0];
    x_f9704fd6 *m = &player->obj->x_20d20338->x_abd7b3c4.x_0c1a9bdd;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

void x_823fd126(u16 x_cc1d0de5, u16 x_84ff873b) {
    x_6751d717 x_49781937[] = { { 0, 200, 0, 0 }, { 200, 0, 0, 0 } };
    x_6751d717 x_c9614940[] = { { 0, 0, 255, 0 }, { 200, 50, 0, 0 } };
    Object *x_32f1d6e2;

    switch (x_84ff873b) {
        case x_6a049984:
            x_32f1d6e2 = x_4495b42c(x_31116106, 0x1000);
            x_371376ba(x_32f1d6e2, &x_49781937[x_cc1d0de5]);
            x_32f1d6e2->x_e2f64c57[0] = &x_824b9544[x_cc1d0de5];
            break;
        case x_b52da315:
            x_32f1d6e2 = x_4495b42c(x_04905798, 0x1000);
            x_371376ba(x_32f1d6e2, &x_c9614940[x_cc1d0de5]);
            x_32f1d6e2->x_e2f64c57[0] = &x_824b9544[x_cc1d0de5];
            break;
        case x_ff5073d4:
            if (x_77831b2c[x_cc1d0de5].x_fb21ca8c) {
                x_32f1d6e2 = x_4495b42c(x_8ba5e67e, 0x1000);
                x_32f1d6e2->x_e2f64c57[0] = &D_8004B764.lights[1].color;
                x_32f1d6e2->x_e2f64c57[1] = &D_8004B644.lights[1].color;
            }
            break;
        case x_73cf9ceb:
            if (x_77831b2c[x_cc1d0de5].x_fb21ca8c) {
                x_32f1d6e2 = x_4495b42c(x_8ba5e67e, 0x1000);
                x_32f1d6e2->x_e2f64c57[0] = &D_8004B784.lights[1].color;
                x_32f1d6e2->x_e2f64c57[1] = &D_8004B664.lights[1].color;
            }
            break;
    }
}

void x_6ed74c52(s16 x_30bbe547) {
    Object *obj;
    s16 v00;
    s16 i;
    s16 x_eb1fe45b;
    x_88f11482 x_70eb54d5[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 x_4cec9290[] = { 0, 0x800 };
    char x_5d45b0f8[12];
    char x_8a9089b3[48];
    char *x_a9ddf02d = "mod0.k2";
    char *x_24febb7e = "spr0.sp3";
    char x_331089fa[12];

    x_16c5d7a5(x_30bbe547);

    x_824b9544[x_30bbe547].x_30bbe547 = x_30bbe547;
    x_824b9544[x_30bbe547].flags = 0;
    x_eb1fe45b = x_824b9544[x_30bbe547].x_eb1fe45b = x_77831b2c[x_30bbe547].x_eb1fe45b;

    if (x_77831b2c[x_30bbe547].x_178eafa6) {
        x_eb1fe45b = x_c4ddde6d;
        x_dab0846a(x_5d45b0f8, "dum.tmd");
    } else {
        x_dab0846a(x_5d45b0f8, D_8004B844[x_eb1fe45b].x_1256da71->name);
        if (x_eb1fe45b != x_b52da315) {
            if (x_30bbe547 != 0) {
                x_8c518b47(x_5d45b0f8, "2.tmd");
            } else {
                x_8c518b47(x_5d45b0f8, ".tmd");
            }
        } else {
            if (x_30bbe547 != 0) {
                x_8c518b47(x_5d45b0f8, "2.k3");
            } else {
                x_8c518b47(x_5d45b0f8, ".k3");
            }
        }
    }

    obj = x_824b9544[x_30bbe547].obj =
        x_8e3c7e83(&x_70eb54d5[x_30bbe547], x_5d45b0f8, D_8004B844[x_eb1fe45b].x_1256da71, x_30bbe547);
    obj->flags |= x_dd6fc445;

    if (x_eb1fe45b == x_b52da315 && !x_77831b2c[x_30bbe547].x_178eafa6) {
        x_43d30ad8(x_824b9544 + x_30bbe547);
    }

    if (x_77831b2c[x_30bbe547].x_178eafa6) {
        x_dab0846a(x_5d45b0f8, "dumshad.k4");
    } else {
        x_dab0846a(x_5d45b0f8, D_8004B844[x_eb1fe45b].x_1256da71->name);
        x_5d45b0f8[3] = '\0';
        if (x_30bbe547 != 0) {
            do {
            } while (0);
            x_8c518b47(x_5d45b0f8, "shad2.k4");
        } else {
            x_8c518b47(x_5d45b0f8, "shad.k4");
        }
    }

    x_77cc77b6(obj, x_5d45b0f8, x_30bbe547);

    obj->x_224610f1.y = 0xC00 - x_4cec9290[x_30bbe547];
    obj->x_0232396f = x_86740bd7;
    if (obj->currentTask && obj->currentTask) {} // @fake
    obj->x_e2f64c57[0] = x_824b9544 + x_30bbe547;

    i = 0;
    x_dab0846a(x_8a9089b3, x_24febb7e);
    while (TRUE) {
        v00 = x_e720f37d(x_8a9089b3, x_30bbe547);
        if (v00 >= 0) {
            x_824b9544[x_30bbe547].x_a1dcdb62[i++] = x_b717ed65[v00].x_4962fc73;
        } else {
            break;
        }
        x_8a9089b3[3]++;
    }

    i = 0;
    x_dab0846a(x_8a9089b3, x_a9ddf02d);
    x_dab0846a(x_331089fa, x_a9ddf02d);
    x_331089fa[6] = '5';
    while (TRUE) {
        v00 = x_e720f37d(x_8a9089b3, x_30bbe547);
        if (v00 >= 0) {
            x_824b9544[x_30bbe547].x_dd32bc14[i++] = x_b717ed65[v00].x_4962fc73;
        } else {
            v00 = x_e720f37d(x_331089fa, x_30bbe547);
            if (v00 >= 0) {
                x_824b9544[x_30bbe547].x_dd32bc14[i++] = x_b717ed65[v00].x_4962fc73;
            } else {
                break;
            }
        }

        x_8a9089b3[3]++;
        x_331089fa[3]++;
    }

    x_8ec7508a(x_30bbe547, x_eb1fe45b);

    x_824b9544[x_30bbe547].x_147ade82 = obj->currentTask;
    x_824b9544[x_30bbe547].x_b9252303 = task_append(obj, task_remove_current, TASK_RUNNABLE);
    x_824b9544[x_30bbe547].x_50a9ff14 = task_append(obj, x_9a2e218f, TASK_RUNNABLE);
    x_824b9544[x_30bbe547].x_cdb23d89 = task_append(obj, task_remove_current, TASK_RUNNABLE);
    x_824b9544[x_30bbe547].x_08b62e4f = task_append(obj, x_340c2137, TASK_RUNNABLE);
    x_824b9544[x_30bbe547].x_f003fafb = D_8004C1E8;

    D_80080214 = D_8004A730[x_77831b2c[x_83106b21].x_eb1fe45b] + D_8004A730[x_77831b2c[x_6f0b3be3].x_eb1fe45b];
    D_80080218 = D_8004A748[x_77831b2c[x_83106b21].x_eb1fe45b] + D_8004A748[x_77831b2c[x_6f0b3be3].x_eb1fe45b];
    x_09a33777 = 0x800;
    x_9a96200f = 1600;

    x_3ac11521[x_30bbe547] = obj;
    D_80080238.x_d0d13a9c = D_80080238.x_ffd925e9 = 0;
    D_80080238.x_77f7a44f = gFrameCounter;

    D_80080236 = TRUE;

    if (x_77831b2c[x_30bbe547].x_03604d94) {
        x_e914de48(x_824b9544 + x_30bbe547, x_b55947d5, 0);
    } else {
        x_e914de48(x_824b9544 + x_30bbe547, x_ee946ac0, 0);
    }

    if (x_30bbe547 != 0) {
        D_80080236 = FALSE;
    }

    x_824b9544[x_30bbe547].x_7f68c36b = x_824b9544[x_30bbe547].x_68a6b5cd + x_824b9544[x_30bbe547].x_cd14c741;
    x_4f2b827a(&x_824b9544[x_30bbe547], D_8004B844[x_eb1fe45b].x_46ce35c8);

    obj->x_9200c538 = x_77831b2c[x_30bbe547].x_c35c64af;
    x_a846a72a(obj, x_30bbe547, x_eb1fe45b);

    if (x_30bbe547 == x_83106b21) {
        x_59ce598c[x_30bbe547].x_d93bcabf = TRUE;
    }

    x_ed9e2514(&x_824b9544[x_30bbe547].x_d8a19723, obj->x_20d20338,
               &obj->x_20d20338->transforms[D_8004B844[x_eb1fe45b].x_46ce35c8->x_8680658c].x_0c1a9bdd,
               &x_824b9544[x_30bbe547].x_5c5b1d93.x_cc2c17a6.x_0c1a9bdd, &obj->pos,
               &D_8004B844[x_eb1fe45b].x_732aef72[x_30bbe547]);

    if (D_8004B844[x_eb1fe45b].x_46ce35c8->x_1ffa33d9 >= 0) {
        x_ed9e2514(&x_824b9544[x_30bbe547].x_238ba16f, obj->x_20d20338,
                   &obj->x_20d20338->transforms[D_8004B844[x_eb1fe45b].x_46ce35c8->x_41b5ccd6].x_0c1a9bdd,
                   &x_824b9544[x_30bbe547].x_5c5b1d93.x_0548cec6.x_0c1a9bdd, &obj->pos,
                   &D_8004B844[x_eb1fe45b].x_732aef72[x_30bbe547]);
        x_824b9544[x_30bbe547].x_8bc5a2ac = TRUE;
    } else {
        x_824b9544[x_30bbe547].x_8bc5a2ac = FALSE;
    }

    x_ed9e2514(&x_824b9544[x_30bbe547].x_29c9094f, obj->x_20d20338,
               &obj->x_20d20338->transforms[D_8004B844[x_eb1fe45b].x_46ce35c8->x_35b6f6e0].x_0c1a9bdd,
               &obj->x_20d20338->transforms[D_8004B844[x_eb1fe45b].x_46ce35c8->x_cc509e17].x_0c1a9bdd, &obj->pos,
               &D_8004B844[x_eb1fe45b].x_732aef72[x_30bbe547]);
    x_ed9e2514(&x_824b9544[x_30bbe547].x_a241ea2a, obj->x_20d20338,
               &obj->x_20d20338->transforms[D_8004B844[x_eb1fe45b].x_46ce35c8->x_71801879].x_0c1a9bdd,
               &obj->x_20d20338->transforms[D_8004B844[x_eb1fe45b].x_46ce35c8->x_df4167c9].x_0c1a9bdd, &obj->pos,
               &D_8004B844[x_eb1fe45b].x_732aef72[x_30bbe547]);

    x_824b9544[x_30bbe547].x_cadf184a = FALSE;

    if (x_5e4e2788 == x_79c2dc5b) {
        if (x_30bbe547 == x_08051143) {
            x_78e49744();
        } else {
            x_824b9544[x_30bbe547].flags |= x_20efa43e;
        }
    }

    x_823fd126(x_30bbe547, x_eb1fe45b);
}

void x_84aa5a13(s16 x_30bbe547) {
    Object *obj = x_824b9544[x_30bbe547].obj;
    s16 x_eb1fe45b;
    x_88f11482 x_70eb54d5[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 x_4cec9290[] = { 0, 0x800 };
    s32 zero = 0;

    x_824b9544[x_30bbe547].x_30bbe547 = x_30bbe547;
    x_824b9544[x_30bbe547].flags = 0;
    x_824b9544[x_30bbe547].x_81570fde.x_b2c79d6e = 0;
    x_824b9544[x_30bbe547].x_eb1fe45b = x_eb1fe45b = x_77831b2c[x_30bbe547].x_eb1fe45b;

    obj->x_224610f1.y = 0xC00 - x_4cec9290[x_30bbe547];
    obj->pos.x = x_70eb54d5[x_30bbe547].x;
    obj->pos.y = x_70eb54d5[x_30bbe547].y;
    obj->pos.z = x_70eb54d5[x_30bbe547].z;
    obj->x_0232396f = x_86740bd7;
    obj->x_e2f64c57[0] = x_824b9544 + x_30bbe547;

    x_824b9544[x_30bbe547].x_147ade82->delay = 0;
    x_824b9544[x_30bbe547].x_147ade82->flags = TASK_RUNNABLE;
    x_824b9544[x_30bbe547].x_147ade82->callback = task_remove_current;
    x_824b9544[x_30bbe547].x_147ade82->stackPtr = zero; // required to match
    x_824b9544[x_30bbe547].x_b9252303->delay = 0;
    x_824b9544[x_30bbe547].x_b9252303->flags = TASK_RUNNABLE;
    x_824b9544[x_30bbe547].x_b9252303->callback = task_remove_current;
    x_824b9544[x_30bbe547].x_b9252303->stackPtr = 0;
    x_824b9544[x_30bbe547].x_50a9ff14->delay = 0;
    x_824b9544[x_30bbe547].x_50a9ff14->flags = TASK_RUNNABLE;
    x_824b9544[x_30bbe547].x_50a9ff14->callback = x_9a2e218f;
    x_824b9544[x_30bbe547].x_50a9ff14->stackPtr = 0;
    x_824b9544[x_30bbe547].x_cdb23d89->delay = 0;
    x_824b9544[x_30bbe547].x_cdb23d89->flags = TASK_RUNNABLE;
    x_824b9544[x_30bbe547].x_cdb23d89->callback = task_remove_current;
    x_824b9544[x_30bbe547].x_cdb23d89->stackPtr = 0;
    x_824b9544[x_30bbe547].x_08b62e4f->delay = 0;
    x_824b9544[x_30bbe547].x_08b62e4f->flags = TASK_RUNNABLE;
    x_824b9544[x_30bbe547].x_08b62e4f->callback = x_340c2137;
    x_824b9544[x_30bbe547].x_08b62e4f->stackPtr = 0;

    D_80080214 = D_8004A730[x_77831b2c[x_83106b21].x_eb1fe45b] + D_8004A730[x_77831b2c[x_6f0b3be3].x_eb1fe45b];
    D_80080218 = D_8004A748[x_77831b2c[x_83106b21].x_eb1fe45b] + D_8004A748[x_77831b2c[x_6f0b3be3].x_eb1fe45b];
    x_09a33777 = 0x800;
    D_80080238.x_d0d13a9c = D_80080238.x_ffd925e9 = 0;
    D_80080236 = TRUE;
    D_80080238.x_77f7a44f = gFrameCounter;
    obj->x_224610f1.y = 0xC00 - x_4cec9290[x_30bbe547];
    x_9a96200f = 1600;
    obj->flags = (obj->flags & x_b6789b80) | x_3434f870;
    D_80080238.x_d0d13a9c = D_80080238.x_ffd925e9 = 0;
    D_80080236 = TRUE;

    if (x_77831b2c[x_30bbe547].x_03604d94) {
        x_e914de48(x_824b9544 + x_30bbe547, x_b55947d5, 0);
    } else {
        x_e914de48(x_824b9544 + x_30bbe547, x_ee946ac0, 0);
    }

    if (x_30bbe547 != x_83106b21) {
        D_80080236 = FALSE;
    }

    x_824b9544[x_30bbe547].x_7f68c36b = x_824b9544[x_30bbe547].x_68a6b5cd + x_824b9544[x_30bbe547].x_cd14c741;
    obj->x_9200c538 = x_77831b2c[x_30bbe547].x_c35c64af;

    if (x_30bbe547 == x_83106b21) {
        x_59ce598c[x_30bbe547].x_d93bcabf = TRUE;
    }

    x_824b9544[x_30bbe547].x_cadf184a = FALSE;
}

u8 x_9d4a1d61(Player *player, u8 x_84ff873b, u16 x_1e30fe60) {
    u16 x_a4b33e43;
    u16 x_54406eae;
    TaskNode *x_b9252303;
    x_58fcf07a *x_fc517ba8;
    u16 x_ea78ab9e;
    x_edf8d3f1 *x_08bf2418;
    s32 pad1;
    s32 *x_4e8001a8;
    x_5d25c43c *pad3;
    x_388306ba *x_5b695729;
    u16 x_6cbdf667;
    x_e0b9a726 *x_8cc0b4a6;
    s16 x_cd14c741;
    u16 i;

    x_6cbdf667 = player->x_b8b27276[x_1e30fe60];
    x_8cc0b4a6 = &player->x_1af5b64c[x_6cbdf667];
    x_54406eae = x_8cc0b4a6->x_4f311d1d;
    x_a4b33e43 = x_8cc0b4a6->x_a4b33e43;
    // clang-format off
    x_cd14c741 = x_8cc0b4a6->x_86977b23; \
    if (x_cd14c741 == player->x_cd14c741 && !x_84ff873b) {
        x_cd14c741 = -1;
    }
    // clang-format on

    x_08bf2418 = player->x_f003fafb + x_a4b33e43;
    pad3 = player->x_a1696a6b + player->x_cd14c741;

    x_fc517ba8 = pad3->x_7f6512f9 + player->x_ae3aa7af;
    x_ea78ab9e = pad3->x_7e85e5f1;

    if (x_08bf2418->x_9cba3528 != NULL && !x_08bf2418->x_9cba3528(player->obj)) {
        return FALSE;
    }

    player->x_eaf4e410 = player->transition;
    player->transition = x_8cc0b4a6;

    x_b9252303 = player->x_b9252303;
    x_4e8001a8 = &x_b9252303->params;
    x_4e8001a8[2] = 0;

    for (i = 0; i < x_ea78ab9e; x_fc517ba8++, i++) {
        if (x_fc517ba8->x_9d8a9022 == x_cd14c741) {
            if (player->obj->frameCounter < x_fc517ba8->frameCounter) {
                x_b9252303->flags |= TASK_TIME_BASED;
                x_b9252303->triggerTime = x_fc517ba8->frameCounter;
                x_b9252303->pushState.callback = x_46bebbb5;
                x_b9252303->pushState.flags = TASK_RUNNABLE;

                player->x_147ade82->callback = task_remove_current;
                player->x_147ade82->delay = 0;
                player->x_147ade82->flags = TASK_RUNNABLE;

                x_4e8001a8[2] = x_fc517ba8->x_7028ad92;
                x_4e8001a8[3] = x_fc517ba8->x_300600ea;
                x_4e8001a8[4] = x_08bf2418->x_9ac0a1c4;
            } else {
                x_b9252303->callback = x_46bebbb5;
                x_b9252303->delay = 0;
                x_b9252303->flags = 1;

                player->x_147ade82->callback = task_remove_current;
                player->x_147ade82->delay = 0;
                player->x_147ade82->flags = TASK_RUNNABLE;

                x_4e8001a8[2] = x_fc517ba8->x_7028ad92;
                x_4e8001a8[3] = x_fc517ba8->x_300600ea;
                x_4e8001a8[4] = x_08bf2418->x_9ac0a1c4;

                player->x_81570fde.x_b2c79d6e |= x_c74d666c;
            }
            goto label;
        }
    }

    player->x_147ade82->callback = x_08bf2418->x_9ac0a1c4;
    player->x_147ade82->delay = 0;
    player->x_147ade82->flags = TASK_RUNNABLE;
    if (x_cd14c741 >= 0) {
        x_b9252303->callback = x_73e8f926;
        x_b9252303->delay = 0;
        x_b9252303->flags = TASK_RUNNABLE;
    }

label:

    if (x_cd14c741 >= 0) {
        x_4e8001a8[1] = x_cd14c741;
        x_4e8001a8[0] = x_08bf2418->x_9ed41890;
        player->x_45f71fd9 = player->x_cd14c741;
        player->x_cd14c741 = x_cd14c741;

        x_5b695729 = player->x_68a6b5cd + x_cd14c741;
        if (x_5b695729->x_016911c1 >= 0 && x_5b695729->x_71e17346 == -1) {
            x_7d4d6609();
            x_7bb27e6e(x_f4bce728,
                       player->obj->x_20d20338->x_50771dcd[player->x_68a6b5cd[x_5b695729->x_016911c1].x_43d35340]);
            x_f4bce728->currentTask->callback = x_e5f3a418;
            x_f4bce728->currentTask->delay = 0;
            x_f4bce728->currentTask->flags = TASK_RUNNABLE;
        }
    } else {
        x_b9252303->callback = x_08bf2418->x_9ed41890;
        x_b9252303->flags = TASK_RUNNABLE;
        x_b9252303->delay = 0;
    }

    player->x_81828f2f = player->x_a4b33e43;
    player->x_1a6e9e97 = player->flags;
    player->x_a4b33e43 = x_a4b33e43;
    player->x_b544b169 = player->x_cfd37298 + x_54406eae;

    player->flags = x_08bf2418->x_bb8c769c | (player->flags & x_08bf2418->x_8dd1ed1c);
    player->x_08bf2418 = x_08bf2418;
    player->x_6cbdf667 = x_6cbdf667;
    player->x_a6423339 = x_1e30fe60;

    x_5f34c321(player);

    if (x_824b9544[1 - player->x_30bbe547].x_381817ae < 3) {
        x_824b9544[1 - player->x_30bbe547].x_381817ae = 3;
    }

    player->x_965e5473 = gFrameCounter;
    if (player->x_b544b169->x_b8173ab8 != 0) {
        player->x_147ade82->delay = player->x_b544b169->x_b8173ab8;
    }
    player->x_448f0851 = player->x_b544b169->x_6785159a;
    player->obj->velocity.z = player->x_b544b169->x_415ed9d6;
    player->obj->flags &= ~x_d13a68b5;
    player->x_0a8e33d7 = player->x_b8b27276[x_1e30fe60 + 1];

    return TRUE;
}

u8 x_e914de48(Player *player, s16 x_0f12118c, u8 x_2092f891) {
    s16 x_1e30fe60;

    x_1e30fe60 = player->x_59f97427[x_0f12118c];
    player->x_b9252303->flags &= ~TASK_TIME_BASED;
    return x_9d4a1d61(player, x_2092f891, x_1e30fe60);
}

u8 x_c05bfb58(Player *player, s16 x_0f12118c, u8 x_2092f891) {
    if (x_77831b2c[player->x_30bbe547].x_03604d94) {
        player->x_448f0851 = 0;
        return x_96d3a31b(player, x_0f12118c);
    } else {
        return x_e914de48(player, x_0f12118c, x_2092f891);
    }
}

u8 x_253cc396(Player *player, u8 x_84ff873b) {
    TaskNode *x_b9252303;
    void *x_20b9213f;
    x_e0b9a726 *x_a8d41374;
    x_e0b9a726 *x_1af5b64c;
    s16 x_975f6a2d;
    s16 x_bc492774;
    s16 *x_6e32552b;
    s32 pad[2];
    s32 x_54406eae;
    u16 x_0433d04f;
    u16 x_958ae7d2;
    s32 pad2[2];
    u16 buttons;

    x_bc492774 = player->x_0a8e33d7;
    x_20b9213f = NULL;
    x_1af5b64c = player->x_1af5b64c;
    x_6e32552b = player->x_b8b27276;
    x_54406eae = gFrameCounter - player->x_965e5473;

    if (x_9df63a90) {
        buttons = 0;
    } else if (player->flags & x_f6191783) {
        buttons = x_59ce598c[player->x_30bbe547].x_33260da8;
    } else {
        buttons = x_59ce598c[player->x_30bbe547].buttons;
    }

    while (x_6e32552b[x_bc492774] >= 0) {
        x_a8d41374 = x_1af5b64c + x_6e32552b[x_bc492774];
        x_0433d04f = x_a8d41374->flags;
        x_958ae7d2 = buttons & x_a8d41374->x_b2075a91;

        // make this move only when no condition for other moves
        if (x_0433d04f & x_34c72c0e) {
            if ((x_0433d04f & x_ba1de1bc) && (!(x_0433d04f & x_14e00522) || !(player->flags & x_9298c772))) {
                x_bc492774 += 2;
                continue;
            } else {
                x_975f6a2d = x_bc492774;
                x_20b9213f = x_a8d41374;
                x_bc492774 += 2;
                continue;
            }
        }

        // triggers only on timeout, no input check
        if ((x_0433d04f & x_98f25ad6) && player->x_448f0851 <= 0) {
            x_59ce598c[player->x_30bbe547].x_c4397934 = FALSE;
            D_80080236 = TRUE;
            if (x_9d4a1d61(player, TRUE, x_bc492774)) {
                D_80080236 = FALSE;
                return TRUE;
            }

            D_80080236 = FALSE;
            x_bc492774 += 2;
            continue;
        }

        // move to turn around
        if (buttons && (x_0433d04f & x_ba1de1bc) && (x_0433d04f & x_14e00522) && (player->flags & x_9298c772)) {
            if (x_a8d41374->x_5512bb4f == 0 || (x_a8d41374->x_5512bb4f != 0 && x_958ae7d2 == x_a8d41374->x_5512bb4f) ||
                (x_a8d41374->x_5512bb4f == 0xFFFF && x_958ae7d2 != 0)) {

                if ((x_0433d04f & x_274c53f9) && player->x_7f68c36b == player->x_68a6b5cd + player->x_cd14c741 &&
                    player->x_7f68c36b->x_bab9966d != player->obj->frameCounter &&
                    !(player->flags & (x_d7755e38 | x_a2274a43))) {
                    x_b9252303 = player->x_b9252303;
                    x_b9252303->params[0] = x_bc492774;
                    x_b9252303->params[1] = x_a8d41374;
                    x_b9252303->flags |= TASK_TIME_BASED;
                    x_b9252303->triggerTime = player->x_7f68c36b->x_bab9966d - 1;
                    x_b9252303->pushState.callback = x_8126b2af;
                    x_b9252303->pushState.flags = TASK_SAVE_STACK | TASK_RUNNABLE;

                    return TRUE;
                }

                if (x_9d4a1d61(player, TRUE, x_bc492774)) {
                    x_59ce598c[player->x_30bbe547].x_c4397934 = TRUE;
                    return TRUE;
                }

                x_bc492774 += 2;
                continue;
            }
        }

        if (x_a8d41374->x_5512bb4f == x_958ae7d2 &&
            ((x_0433d04f & x_e888c0db) ||
             ((x_0433d04f & x_274c53f9) && player->x_7f68c36b == player->x_68a6b5cd + player->x_cd14c741))) {

            x_59ce598c[player->x_30bbe547].x_c4397934 = FALSE;

            if (x_0433d04f & x_502b7c2c) {
                if (player->x_7f68c36b->x_bab9966d != player->obj->frameCounter &&
                    (!(player->flags & (x_d7755e38 | x_a2274a43)) ||
                     player->x_7f68c36b->x_887b6be9 != player->obj->frameCounter)) {
                    x_bc492774 += 2;
                    continue;
                } else if (x_9d4a1d61(player, TRUE, x_bc492774)) {
                    return TRUE;
                } else {
                    x_bc492774 += 2;
                    continue;
                }
            }

            if ((x_0433d04f & x_274c53f9) && player->x_7f68c36b->x_bab9966d != player->obj->frameCounter &&
                !(player->flags & (x_d7755e38 | x_a2274a43))) {
                x_b9252303 = player->x_b9252303;
                x_b9252303->params[0] = x_bc492774;
                x_b9252303->params[1] = x_a8d41374;
                x_b9252303->flags |= TASK_TIME_BASED;
                x_b9252303->triggerTime = player->x_7f68c36b->x_bab9966d - 1;
                x_b9252303->pushState.callback = x_8126b2af;
                x_b9252303->pushState.flags = TASK_SAVE_STACK | TASK_RUNNABLE;
                return TRUE;
            }

            if ((x_0433d04f & x_0b97c4c4)) {
                if (x_54406eae <= player->x_cfd37298[x_a8d41374->x_4f311d1d].x_8b47d6ce) {
                    if (x_9d4a1d61(player, TRUE, x_bc492774)) {
                        return TRUE;
                    } else {
                        x_bc492774 += 2;
                        continue;
                    }
                } else {
                    x_bc492774 += 2;
                    continue;
                }
            }

            if (x_9d4a1d61(player, TRUE, x_bc492774)) {
                return TRUE;
            }
        }

        x_bc492774 += 2;
    }

    if (x_20b9213f != NULL && x_84ff873b) {
        x_59ce598c[player->x_30bbe547].x_c4397934 = FALSE;
        D_80080236 = TRUE;
        if (x_9d4a1d61(player, TRUE, x_975f6a2d)) {
            player->x_0a8e33d7 = x_6e32552b[x_975f6a2d + 1];
            D_80080236 = FALSE;
            return TRUE;
        }
        D_80080236 = FALSE;
    }

    return FALSE;
}

u8 x_fb0d2e6c(Player *player) {
    s16 x_7bfa285a;
    u16 x_560beae1;
    x_e0b9a726 *t2;
    x_e0b9a726 *x_554ac37d;
    x_e0b9a726 *x_09c24fd5;
    s16 x_434431dd;
    s16 *x_6e32552b;

    x_7bfa285a = player->x_0a8e33d7;
    x_554ac37d = player->x_1af5b64c;
    x_6e32552b = player->x_b8b27276;
    t2 = NULL;

    while (x_6e32552b[x_7bfa285a] >= 0) {
        x_09c24fd5 = x_554ac37d + x_6e32552b[x_7bfa285a];
        x_560beae1 = x_09c24fd5->flags;
        if (x_560beae1 & x_34c72c0e) {
            if (((x_560beae1 & x_ba1de1bc) && (!(x_560beae1 & x_14e00522) || !(player->flags & x_9298c772)))) {
                x_7bfa285a += 2;
                continue;
            }
            t2 = x_09c24fd5;
            x_434431dd = x_7bfa285a;
            break;
        }
        x_7bfa285a += 2;
    }

    if (t2 != NULL) {
        D_80080236 = TRUE;
        if (x_9d4a1d61(player, TRUE, x_434431dd)) {
            player->x_0a8e33d7 = x_6e32552b[x_434431dd + 1];
            D_80080236 = FALSE;
            return TRUE;
        }
        D_80080236 = FALSE;
    }

    return FALSE;
}
