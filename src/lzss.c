#include "common.h"

#define N 4096 /* buffer size */
#define F 60   /* lookahead buffer size */
#define THRESHOLD 2

#define NUM_SYMBOLS (256 - THRESHOLD + F)
/* kinds of characters (character code = 0..N_CHAR-1) */
#define T (NUM_SYMBOLS * 2 - 1) /* size of table */
#define R (T - 1)               /* position of root */
#define MAX_FREQ 0x8000         /* updates tree when the */

extern u8 sDistBase[];
extern u8 sDistExtra[];
extern s16 sHufMap[628];
extern u8 *sDecompBufs[2];
extern u8 *sDecompReadPtr;
extern u8 *sDecompWritePtr;
extern s32 sDecompRemain;
extern s32 sDecompChunkIdx;
extern s32 sDecompBufIdx;
extern s32 sDecompBufPos;
extern s32 sDecompChunkSize;
extern u8 sDecompLastFlag;
extern x_80d298c9 *sDecompResCtx;
extern u8 sSlideWindow[4160];

void lzhuf_tree_init(void);
s16 lzhuf_read_byte_bits(void);

s16 lzhuf_decode_symbol(void) {
    u16 c;

    c = sHufMap[R];
    while (c < T) {
        c += lzhuf_read_bit();
        c = sHufMap[c];
    }

    c -= T;
    lzhuf_tree_update(c);
    return c;
}

s16 lzhuf_decode_distance(void) {
    u16 i, j, c;

    i = lzhuf_read_byte_bits();
    c = sDistBase[i] << 6;
    j = sDistExtra[i];

    j -= 2;

    return c | (((i << j) | lzhuf_read_bits(j)) & 0x3f);
}

void lzhuf_decompress(void) {
    s16 i;
    s16 r;
    s32 count;
    s16 c;
    s16 k;
    s16 v1;
    s16 j;

    lzhuf_tree_init();
    for (i = 0; i < N - F; i++) {
        sSlideWindow[i] = ' ';
    }

    r = N - F;
    for (count = 0; count < sDecompResCtx->x_f33d7764;) {
        c = lzhuf_decode_symbol();
        if (c < 256) {
            *sDecompWritePtr++ = c;
            sSlideWindow[r++] = c;
            r &= (N - 1);
            count++;
        } else {
            i = (r - lzhuf_decode_distance() - 1) & (N - 1);
            j = c - 255 + THRESHOLD;
            for (k = 0; k < j; k++) {
                c = sSlideWindow[(i + k) & (N - 1)];
                *sDecompWritePtr++ = c;
                sSlideWindow[r++] = c;
                r &= (N - 1);
                count++;
            }
        }
    }
}

void lzhuf_start(x_80d298c9 *x_cc1d0de5) {
    sDecompWritePtr = x_cc1d0de5->data;
    sDecompResCtx = x_cc1d0de5;
    sDecompRemain = x_cc1d0de5->size;
    sDecompChunkSize = (u32) D_8013C218 >> 1;

    sDecompBufs[0] = D_8013C208;
    sDecompReadPtr = D_8013C208;
    sDecompBufs[1] = D_8013C208 + sDecompChunkSize;

    sDecompBufPos = 0;
    sDecompBufIdx = 0;

    if ((u32) D_8013C218 < (u32) x_cc1d0de5->size) {
        dma_read_sync(sDecompResCtx->romAddr, D_8013C208, sDecompChunkSize);
        dma_read_async(sDecompResCtx->romAddr + sDecompChunkSize, sDecompBufs[1], sDecompChunkSize);
        sDecompChunkIdx = 2;
        sDecompLastFlag = 0;
    } else {
        dma_read_sync(sDecompResCtx->romAddr, D_8013C208, x_cc1d0de5->size);
        sDecompChunkSize = x_cc1d0de5->size;
        sDecompLastFlag = 1;
    }

    lzhuf_decompress();
}
