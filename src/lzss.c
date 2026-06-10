#include "common.h"

#define N 4096 /* buffer size */
#define F 60   /* lookahead buffer size */
#define x_b7847da5 2

#define x_a0981260 (256 - x_b7847da5 + F)
/* kinds of characters (character code = 0..N_CHAR-1) */
#define T (x_a0981260 * 2 - 1) /* size of table */
#define R (T - 1)          /* position of root */
#define x_c02b3433 0x8000    /* updates tree when the */

extern u8 D_8004C760[];
extern u8 D_8004C860[];
extern s16 x_e9b1c821[628];
extern u8 *D_800B6410[2];
extern u8 *D_800B6418;
extern u8 *D_800B641C;
extern s32 D_800B6420;
extern s32 D_800B6424;
extern s32 D_800B6428;
extern s32 D_800B642C;
extern s32 D_800B6430;
extern u8 D_800B6434;
extern x_80d298c9 *D_800B6438;
extern u8 D_800B6440[4160];

void x_42b39ea8(void);
s16 x_13af1d38(void);

s16 x_679a6854(void) {
    u16 c;

    c = x_e9b1c821[R];
    while (c < T) {
        c += x_dbb46089();
        c = x_e9b1c821[c];
    }

    c -= T;
    x_a8ae0481(c);
    return c;
}

s16 x_1f8f58cf(void) {
    u16 i, j, c;

    i = x_13af1d38();
    c = D_8004C760[i] << 6;
    j = D_8004C860[i];

    j -= 2;

    return c | (((i << j) | x_472e02c2(j)) & 0x3f);
}

void x_66cc7af3(void) {
    s16 i;
    s16 r;
    s32 count;
    s16 c;
    s16 k;
    s16 v1;
    s16 j;

    x_42b39ea8();
    for (i = 0; i < N - F; i++) {
        D_800B6440[i] = ' ';
    }

    r = N - F;
    for (count = 0; count < D_800B6438->x_f33d7764;) {
        c = x_679a6854();
        if (c < 256) {
            *D_800B641C++ = c;
            D_800B6440[r++] = c;
            r &= (N - 1);
            count++;
        } else {
            i = (r - x_1f8f58cf() - 1) & (N - 1);
            j = c - 255 + x_b7847da5;
            for (k = 0; k < j; k++) {
                c = D_800B6440[(i + k) & (N - 1)];
                *D_800B641C++ = c;
                D_800B6440[r++] = c;
                r &= (N - 1);
                count++;
            }
        }
    }
}

void x_69c2895e(x_80d298c9 *x_cc1d0de5) {
    D_800B641C = x_cc1d0de5->data;
    D_800B6438 = x_cc1d0de5;
    D_800B6420 = x_cc1d0de5->size;
    D_800B6430 = (u32) D_8013C218 >> 1;

    D_800B6410[0] = D_8013C208;
    D_800B6418 = D_8013C208;
    D_800B6410[1] = D_8013C208 + D_800B6430;

    D_800B642C = 0;
    D_800B6428 = 0;

    if ((u32) D_8013C218 < (u32) x_cc1d0de5->size) {
        dma_read_sync(D_800B6438->romAddr, D_8013C208, D_800B6430);
        dma_read_async(D_800B6438->romAddr + D_800B6430, D_800B6410[1], D_800B6430);
        D_800B6424 = 2;
        D_800B6434 = 0;
    } else {
        dma_read_sync(D_800B6438->romAddr, D_8013C208, x_cc1d0de5->size);
        D_800B6430 = x_cc1d0de5->size;
        D_800B6434 = 1;
    }

    x_66cc7af3();
}
