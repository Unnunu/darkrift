#include "common.h"

#define N 4096 /* buffer size */
#define F 60   /* lookahead buffer size */
#define THRESHOLD 2

#define NUM_SYMBOLS (256 - THRESHOLD + F)
/* kinds of characters (character code = 0..N_CHAR-1) */
#define T (NUM_SYMBOLS * 2 - 1) /* size of table */
#define R (T - 1)               /* position of root */
#define MAX_FREQ 0x8000         /* updates tree when the */

u8 sDistBase[] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
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
u8 sDistExtra[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };
u16 sBitBuf = 0;
u8 sBitCount = 0;
s16 sBitMask[] = {
    0x0, 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0xFFF, 0xFFFF
}; // @bug 15-th element should be 0x7FFF, though it doesn't affect anything
s16 sBitShift[] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

s32 sHufPad[4];
u8 *sDecompBufs[2];
u8 *sDecompReadPtr;
u8 *sDecompWritePtr;
s32 sDecompRemain;
s32 sDecompChunkIdx;
s32 sDecompBufIdx;
s32 sDecompBufPos;
s32 sDecompChunkSize;
u8 sDecompLastFlag;
x_80d298c9 *sDecompResCtx;
u8 sSlideWindow[4160];
u16 sHufFreq[628];
s16 sHufTree[944];
s16 sHufMap[628];

void lzhuf_dma_refill(void) {
    if (sDecompLastFlag == 0) {
        sDecompBufIdx = 1 - sDecompBufIdx;
        sDecompReadPtr = sDecompBufs[sDecompBufIdx];

        while (osRecvMesg(&gPiMessageQueue, NULL, OS_MESG_NOBLOCK)) {}

        if ((u32) sDecompChunkSize < (u32) sDecompRemain) {
            dma_read_async(sDecompResCtx->romAddr + sDecompChunkIdx * sDecompChunkSize, sDecompBufs[1 - sDecompBufIdx],
                           sDecompChunkSize);
        } else {
            dma_read_async(sDecompResCtx->romAddr + sDecompChunkIdx * sDecompChunkSize, sDecompBufs[1 - sDecompBufIdx],
                           sDecompRemain);
        }
        sDecompRemain -= sDecompChunkSize;
    }
}

u8 lzhuf_read_byte(void) {
    if ((u32) sDecompChunkSize <= (u32) sDecompBufPos) {
        lzhuf_dma_refill();
        sDecompBufPos = 0;
        sDecompChunkIdx++;
    }

    return sDecompReadPtr[sDecompBufPos++];
}

s16 lzhuf_read_bit(void) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = sBitBuf;
    if (sBitCount < 9) {
        a0 = lzhuf_read_byte();
        if ((s16) a0 < 0) {
            a0 = 0;
        }

        bits |= a0 << (8 - sBitCount);
        sBitCount += 8;
    }

    sBitBuf = bits << 1;
    sBitCount--;

    if (bits & 0x8000) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s16 lzhuf_read_byte_bits(void) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = sBitBuf;
    if (sBitCount < 9) {
        a0 = lzhuf_read_byte();
        if ((s16) a0 < 0) {
            a0 = 0;
        }

        bits |= a0 << (8 - sBitCount);
        sBitCount += 8;
    }

    sBitBuf = bits << 8;
    sBitCount -= 8;
    return (bits >> 8) & 0xFF;
}

s16 lzhuf_read_bits(u16 x_cc1d0de5) {
    u16 bits;
    u16 a0;
    s32 ret;

    bits = sBitBuf;
    if (sBitCount < 9) {
        a0 = lzhuf_read_byte();
        if ((s16) a0 < 0) {
            a0 = 0;
        }

        bits |= a0 << (8 - sBitCount);
        sBitCount += 8;
    }

    sBitBuf = bits << x_cc1d0de5;
    sBitCount -= x_cc1d0de5;
    return (bits >> sBitShift[x_cc1d0de5]) & sBitMask[x_cc1d0de5];
}

void lzhuf_tree_init(void) {
    s16 i, j;

    for (i = 0; i < NUM_SYMBOLS; i++) {
        sHufFreq[i] = 1;
        sHufMap[i] = i + T;
        sHufTree[i + T] = i;
    }

    for (i = 0, j = NUM_SYMBOLS; j <= R; i += 2, j++) { // why <= ??
        sHufFreq[j] = sHufFreq[i] + sHufFreq[i + 1];
        sHufMap[j] = i;
        sHufTree[i] = sHufTree[i + 1] = j;
    }

    sHufFreq[T] = 0xFFFF;
    sHufTree[R] = 0;

    sBitCount = 0;
    sBitBuf = 0;
}

#ifdef NON_EQUIVALENT
void lzhuf_tree_rebuild(void) {
    s16 i; // v0
    s16 j;
    s16 k;
    u16 f;
    u16 l;
    u16 m;

    j = 0;
    for (i = 0; i < T; i++) {
        if (sHufMap[i] >= T) {
            sHufFreq[j] = (sHufFreq[i] + 1) / 2;
            sHufMap[j] = sHufMap[i];
            j++;
        }
    }

    for (i = 0, j = NUM_SYMBOLS; j < T; i += 2, j++) {
        k = i + 1;
        f = sHufFreq[j] = sHufFreq[i] + sHufFreq[k];

        for (k = j - 1; f < sHufFreq[k]; k--)
            ;

        k++;
        l = (j - k) * 2;

        for (m = l; m > 0; m--) {
            sHufFreq[k + m] = sHufFreq[k + m - 1];
        }
        sHufFreq[k] = f;

        for (m = l; m > 0; m--) {
            sHufMap[k + m] = sHufMap[k + m - 1];
        }

        sHufMap[k] = i;
    }

    for (i = 0; i < T; i++) {
        if ((k = sHufMap[i]) >= T) {
            sHufTree[k] = i;
        } else {
            sHufTree[k] = sHufTree[k + 1] = i;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/huffman/lzhuf_tree_rebuild.s")
void lzhuf_tree_rebuild(void);
#endif

void lzhuf_tree_update(u16 c) {
    s16 j, k, l;
    s32 n;
    s16 m;
    s32 i;
    u16 *ptr;

    // Check if frequency root reached max
    if (sHufFreq[R] == MAX_FREQ) {
        lzhuf_tree_rebuild();
    }

    // Get parent of the current node
    c = sHufTree[c + T];

    do {
        // Increment frequency
        k = ++sHufFreq[c];
        m = c + 1;
        // If frequency order is disturbed, reorder nodes
        if (k > sHufFreq[(u32) m]) {
            ptr = &sHufFreq[m + 2];

            while (n = k > ptr[-1]) {
                ptr++;
            }
            l = ptr - sHufFreq - 2;

            // Swap frequencies
            sHufFreq[c] = ptr[-2];
            ptr[-2] = k;

            // Update parent and child relationships
            i = sHufMap[c];
            sHufTree[i] = l;
            if (i < T)
                sHufTree[i + 1] = l;

            j = sHufMap[l];
            sHufMap[l] = i;

            sHufTree[j] = c;
            if (j < T)
                sHufTree[j + 1] = c;

            sHufMap[c] = j;

            c = l;
        }
    } while ((c = sHufTree[c]) != 0); // Repeat until reaching the root
}
