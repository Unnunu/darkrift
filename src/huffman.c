#include "common.h"

#define N 4096 /* buffer size */
#define F 60   /* lookahead buffer size */
#define x_b7847da5 2

#define x_a0981260 (256 - x_b7847da5 + F)
/* kinds of characters (character code = 0..N_CHAR-1) */
#define T (x_a0981260 * 2 - 1) /* size of table */
#define R (T - 1)              /* position of root */
#define x_c02b3433 0x8000      /* updates tree when the */

u8 D_8004C760[] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                    0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
                    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,
                    3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5,  5,  5,  5,  5,
                    6,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,  8,  8,  8,  8,  8,
                    9,  9,  9,  9,  9,  9,  9,  9,  10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11,
                    12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17,
                    18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23,
                    24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35,
                    36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47,
                    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63 };
u8 D_8004C860[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };
u16 D_8004C960 = 0;
u8 D_8004C964 = 0;
s16 D_8004C968[] = {
    0x0, 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0xFFF, 0xFFFF
}; // @bug 15-th element should be 0x7FFF, though it doesn't affect anything
s16 D_8004C98C[] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

s32 x_0930c581[4];
u8 *D_800B6410[2];
u8 *D_800B6418;
u8 *D_800B641C;
s32 D_800B6420;
s32 D_800B6424;
s32 D_800B6428;
s32 D_800B642C;
s32 D_800B6430;
u8 D_800B6434;
x_80d298c9 *D_800B6438;
u8 D_800B6440[4160];
u16 x_c50dcc97[628];
s16 x_18069a64[944];
s16 x_e9b1c821[628];

void x_1041b8d9(void) {
    if (D_800B6434 == 0) {
        D_800B6428 = 1 - D_800B6428;
        D_800B6418 = D_800B6410[D_800B6428];

        while (osRecvMesg(&gPiMessageQueue, NULL, OS_MESG_NOBLOCK)) {}

        if ((u32) D_800B6430 < (u32) D_800B6420) {
            dma_read_async(D_800B6438->romAddr + D_800B6424 * D_800B6430, D_800B6410[1 - D_800B6428], D_800B6430);
        } else {
            dma_read_async(D_800B6438->romAddr + D_800B6424 * D_800B6430, D_800B6410[1 - D_800B6428], D_800B6420);
        }
        D_800B6420 -= D_800B6430;
    }
}

u8 x_86fda831(void) {
    if ((u32) D_800B6430 <= (u32) D_800B642C) {
        x_1041b8d9();
        D_800B642C = 0;
        D_800B6424++;
    }

    return D_800B6418[D_800B642C++];
}

s16 x_dbb46089(void) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = D_8004C960;
    if (D_8004C964 < 9) {
        a0 = x_86fda831();
        if ((s16) a0 < 0) {
            a0 = 0;
        }

        bits |= a0 << (8 - D_8004C964);
        D_8004C964 += 8;
    }

    D_8004C960 = bits << 1;
    D_8004C964--;

    if (bits & 0x8000) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s16 x_13af1d38(void) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = D_8004C960;
    if (D_8004C964 < 9) {
        a0 = x_86fda831();
        if ((s16) a0 < 0) {
            a0 = 0;
        }

        bits |= a0 << (8 - D_8004C964);
        D_8004C964 += 8;
    }

    D_8004C960 = bits << 8;
    D_8004C964 -= 8;
    return (bits >> 8) & 0xFF;
}

s16 x_472e02c2(u16 x_cc1d0de5) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = D_8004C960;
    if (D_8004C964 < 9) {
        a0 = x_86fda831();
        if ((s16) a0 < 0) {
            a0 = 0;
        }

        bits |= a0 << (8 - D_8004C964);
        D_8004C964 += 8;
    }

    D_8004C960 = bits << x_cc1d0de5;
    D_8004C964 -= x_cc1d0de5;
    return (bits >> D_8004C98C[x_cc1d0de5]) & D_8004C968[x_cc1d0de5];
}

void x_42b39ea8(void) {
    s16 i, j;

    for (i = 0; i < x_a0981260; i++) {
        x_c50dcc97[i] = 1;
        x_e9b1c821[i] = i + T;
        x_18069a64[i + T] = i;
    }

    for (i = 0, j = x_a0981260; j <= R; i += 2, j++) { // why <= ??
        x_c50dcc97[j] = x_c50dcc97[i] + x_c50dcc97[i + 1];
        x_e9b1c821[j] = i;
        x_18069a64[i] = x_18069a64[i + 1] = j;
    }

    x_c50dcc97[T] = 0xFFFF;
    x_18069a64[R] = 0;

    D_8004C964 = 0;
    D_8004C960 = 0;
}

#ifdef NON_EQUIVALENT
void x_cbd0f8d7(void) {
    s16 i; // v0
    s16 j;
    s16 k;
    u16 f;
    u16 l;
    u16 m;

    j = 0;
    for (i = 0; i < T; i++) {
        if (x_e9b1c821[i] >= T) {
            x_c50dcc97[j] = (x_c50dcc97[i] + 1) / 2;
            x_e9b1c821[j] = x_e9b1c821[i];
            j++;
        }
    }

    for (i = 0, j = x_a0981260; j < T; i += 2, j++) {
        k = i + 1;
        f = x_c50dcc97[j] = x_c50dcc97[i] + x_c50dcc97[k];

        for (k = j - 1; f < x_c50dcc97[k]; k--)
            ;

        k++;
        l = (j - k) * 2;

        for (m = l; m > 0; m--) {
            x_c50dcc97[k + m] = x_c50dcc97[k + m - 1];
        }
        x_c50dcc97[k] = f;

        for (m = l; m > 0; m--) {
            x_e9b1c821[k + m] = x_e9b1c821[k + m - 1];
        }

        x_e9b1c821[k] = i;
    }

    for (i = 0; i < T; i++) {
        if ((k = x_e9b1c821[i]) >= T) {
            x_18069a64[k] = i;
        } else {
            x_18069a64[k] = x_18069a64[k + 1] = i;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/huffman/x_cbd0f8d7.s")
void x_cbd0f8d7(void);
#endif

void x_a8ae0481(u16 c) {
    s16 j, k, l;
    s32 n;
    s16 m;
    s32 i;
    u16 *ptr;

    // Check if frequency root reached max
    if (x_c50dcc97[R] == x_c02b3433) {
        x_cbd0f8d7();
    }

    // Get parent of the current node
    c = x_18069a64[c + T];

    do {
        // Increment frequency
        k = ++x_c50dcc97[c];
        m = c + 1;
        // If frequency order is disturbed, reorder nodes
        if (k > x_c50dcc97[(u32) m]) {
            ptr = &x_c50dcc97[m + 2];

            while (n = k > ptr[-1]) {
                ptr++;
            }
            l = ptr - x_c50dcc97 - 2;

            // Swap frequencies
            x_c50dcc97[c] = ptr[-2];
            ptr[-2] = k;

            // Update parent and child relationships
            i = x_e9b1c821[c];
            x_18069a64[i] = l;
            if (i < T)
                x_18069a64[i + 1] = l;

            j = x_e9b1c821[l];
            x_e9b1c821[l] = i;

            x_18069a64[j] = c;
            if (j < T)
                x_18069a64[j + 1] = c;

            x_e9b1c821[c] = j;

            c = l;
        }
    } while ((c = x_18069a64[c]) != 0); // Repeat until reaching the root
}
