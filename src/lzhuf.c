#include "common.h"

#define N 4096 /* buffer size */
#define F 60   /* lookahead buffer size */
#define THRESHOLD 2

#define N_CHAR (256 - THRESHOLD + F)
/* kinds of characters (character code = 0..N_CHAR-1) */
#define T (N_CHAR * 2 - 1) /* size of table */
#define R (T - 1)          /* position of root */
#define MAX_FREQ 0x8000    /* updates tree when the */

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

s32 D_800B6400_unused[4];
u8 *D_800B6410[2];
u8 *D_800B6418;
u8 *D_800B641C;
s32 D_800B6420;
s32 D_800B6424;
s32 D_800B6428;
s32 D_800B642C;
s32 D_800B6430;
u8 D_800B6434;
Asset *D_800B6438;
u8 D_800B6440[4160];
u16 gHuffmanFreq[628];
s16 gHuffmanParent[944];
s16 gHuffmanSon[628];

void func_80024F50(void) {
    if (D_800B6434 == 0) {
        D_800B6428 = 1 - D_800B6428;
        D_800B6418 = D_800B6410[D_800B6428];

        while (osRecvMesg(&gSchedDMAQueue, NULL, OS_MESG_NOBLOCK)) {}

        if ((u32) D_800B6430 < (u32) D_800B6420) {
            dma_read_noblock(D_800B6438->romAddr + D_800B6424 * D_800B6430, D_800B6410[1 - D_800B6428], D_800B6430);
        } else {
            dma_read_noblock(D_800B6438->romAddr + D_800B6424 * D_800B6430, D_800B6410[1 - D_800B6428], D_800B6420);
        }
        D_800B6420 -= D_800B6430;
    }
}

u8 func_800250A8(void) {
    if ((u32) D_800B6430 <= (u32) D_800B642C) {
        func_80024F50();
        D_800B642C = 0;
        D_800B6424++;
    }

    return D_800B6418[D_800B642C++];
}

s16 func_80025120(void) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = D_8004C960;
    if (D_8004C964 < 9) {
        a0 = func_800250A8();
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

s16 func_800251D4(void) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = D_8004C960;
    if (D_8004C964 < 9) {
        a0 = func_800250A8();
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

s16 func_80025278(u16 arg0) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = D_8004C960;
    if (D_8004C964 < 9) {
        a0 = func_800250A8();
        if ((s16) a0 < 0) {
            a0 = 0;
        }

        bits |= a0 << (8 - D_8004C964);
        D_8004C964 += 8;
    }

    D_8004C960 = bits << arg0;
    D_8004C964 -= arg0;
    return (bits >> D_8004C98C[arg0]) & D_8004C968[arg0];
}

void func_80025344(void) {
    s16 i, j;

    for (i = 0; i < N_CHAR; i++) {
        gHuffmanFreq[i] = 1;
        gHuffmanSon[i] = i + T;
        gHuffmanParent[i + T] = i;
    }

    for (i = 0, j = N_CHAR; j <= R; i += 2, j++) { // why <= ??
        gHuffmanFreq[j] = gHuffmanFreq[i] + gHuffmanFreq[i + 1];
        gHuffmanSon[j] = i;
        gHuffmanParent[i] = gHuffmanParent[i + 1] = j;
    }

    gHuffmanFreq[T] = 0xFFFF;
    gHuffmanParent[R] = 0;

    D_8004C964 = 0;
    D_8004C960 = 0;
}

#ifdef NON_EQUIVALENT
void func_8002541C(void) {
    s16 i, j, k;
    u16 f;
    u16 l;
    u16 m;

    j = 0;
    for (i = 0; i < T; i++) {
        if (gHuffmanSon[i] >= T) {
            gHuffmanFreq[j] = (gHuffmanFreq[i] + 1) / 2;
            gHuffmanSon[j] = gHuffmanSon[i];
            j++;
        }
    }

    for (i = 0, j = N_CHAR; j < T; i += 2, j++) {
        k = i + 1;
        f = gHuffmanFreq[j] = gHuffmanFreq[i] + gHuffmanFreq[k];

        for (k = j - 1; f < gHuffmanFreq[k]; k--)
            ;

        k++;
        l = (j - k) * 2;

        for (m = l; m > 0; m--) {
            gHuffmanFreq[k + m] = gHuffmanFreq[k + m - 1];
        }
        gHuffmanFreq[k] = f;

        for (m = l; m > 0; m--) {
            gHuffmanSon[k + m] = gHuffmanSon[k + m - 1];
        }

        gHuffmanSon[k] = i;
    }

    for (i = 0; i < T; i++) {
        if ((k = gHuffmanSon[i]) >= T) {
            gHuffmanParent[k] = i;
        } else {
            gHuffmanParent[k] = gHuffmanParent[k + 1] = i;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/lzhuf/func_8002541C.s")
void func_8002541C(void);
#endif

void lzhuf_update(u16 c) {
    s16 j, k, l;
    s32 n;
    s16 m;
    s32 i;
    u16 *ptr;

    // Check if frequency root reached max
    if (gHuffmanFreq[R] == MAX_FREQ) {
        func_8002541C();
    }

    // Get parent of the current node
    c = gHuffmanParent[c + T];

    do {
        // Increment frequency
        k = ++gHuffmanFreq[c];
        m = c + 1;
        // If frequency order is disturbed, reorder nodes
        if (k > gHuffmanFreq[(u32) m]) {
            ptr = &gHuffmanFreq[m + 2];

            while (n = k > ptr[-1]) {
                ptr++;
            }
            l = ptr - gHuffmanFreq - 2;

            // Swap frequencies
            gHuffmanFreq[c] = ptr[-2];
            ptr[-2] = k;

            // Update parent and child relationships
            i = gHuffmanSon[c];
            gHuffmanParent[i] = l;
            if (i < T)
                gHuffmanParent[i + 1] = l;

            j = gHuffmanSon[l];
            gHuffmanSon[l] = i;

            gHuffmanParent[j] = c;
            if (j < T)
                gHuffmanParent[j + 1] = c;

            gHuffmanSon[c] = j;

            c = l;
        }
    } while ((c = gHuffmanParent[c]) != 0); // Repeat until reaching the root
}

#pragma GLOBAL_ASM("asm/nonmatchings/lzhuf/lzhuf_decode_char.s")
s16 lzhuf_decode_char(void);
/*
s16 lzhuf_decode_char(void) {
    u16 c;

    c = gHuffmanSon[R];
    while (c < T) {
        c += func_80025120();
        c = gHuffmanSon[c];
    }

    c -= T;
    lzhuf_update(c);
    return c;
}
*/

#ifdef NON_MATCHING
s16 lzhuf_decode_position(void) {
    u16 i, j, c;

    i = func_800251D4();
    c = D_8004C760[i] << 6;
    j = D_8004C860[i];

    j -= 2;

    i = (i << j) + func_80025278(j);

    return c | (i & 0x3f);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/lzhuf/lzhuf_decode_position.s")
s16 lzhuf_decode_position(void);
#endif

void lzhuf_decode(void) {
    s16 i;
    s16 r;
    s32 count;
    s16 c;
    s16 k;
    s16 v1;
    s16 j;

    func_80025344();
    for (i = 0; i < N - F; i++) {
        D_800B6440[i] = ' ';
    }

    r = N - F;
    for (count = 0; count < D_800B6438->unpacked_size;) {
        c = lzhuf_decode_char();
        if (c < 256) {
            *D_800B641C++ = c;
            D_800B6440[r++] = c;
            r &= (N - 1);
            count++;
        } else {
            i = (r - lzhuf_decode_position() - 1) & (N - 1);
            j = c - 255 + THRESHOLD;
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

void func_80025A0C(Asset *arg0) {
    D_800B641C = arg0->data;
    D_800B6438 = arg0;
    D_800B6420 = arg0->size;
    D_800B6430 = (u32) D_8013C218 >> 1;

    D_800B6410[0] = D_8013C208;
    D_800B6418 = D_8013C208;
    D_800B6410[1] = D_8013C208 + D_800B6430;

    D_800B642C = 0;
    D_800B6428 = 0;

    if ((u32) D_8013C218 < (u32) arg0->size) {
        dma_read(D_800B6438->romAddr, D_8013C208, D_800B6430);
        dma_read_noblock(D_800B6438->romAddr + D_800B6430, D_800B6410[1], D_800B6430);
        D_800B6424 = 2;
        D_800B6434 = 0;
    } else {
        dma_read(D_800B6438->romAddr, D_8013C208, arg0->size);
        D_800B6430 = arg0->size;
        D_800B6434 = 1;
    }

    lzhuf_decode();
}
