#include "common.h"

#define N 4096 /* buffer size */
#define F 60   /* lookahead buffer size */
#define THRESHOLD 2

#define N_CHAR (256 - THRESHOLD + F)
/* kinds of characters (character code = 0..N_CHAR-1) */
#define T (N_CHAR * 2 - 1) /* size of table */
#define R (T - 1)          /* position of root */
#define MAX_FREQ 0x8000    /* updates tree when the */

extern u8 D_8004C760[];
extern u8 D_8004C860[];
extern s16 gHuffmanSon[628];
extern u8 *D_800B6410[2];
extern u8 *D_800B6418;
extern u8 *D_800B641C;
extern s32 D_800B6420;
extern s32 D_800B6424;
extern s32 D_800B6428;
extern s32 D_800B642C;
extern s32 D_800B6430;
extern u8 D_800B6434;
extern Asset *D_800B6438;
extern u8 D_800B6440[4160];

void func_80025344(void);
s16 func_800251D4(void);

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

s16 lzhuf_decode_position(void) {
    u16 i, j, c;

    i = func_800251D4();
    c = D_8004C760[i] << 6;
    j = D_8004C860[i];

    j -= 2;

    return c | (((i << j) | func_80025278(j)) & 0x3f);
}

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
