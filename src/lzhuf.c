#include "common.h"

extern u8 D_8004C760[];
extern u8 D_8004C860[];
extern u16 D_8004C960;
extern u8 D_8004C964;
extern s16 D_8004C968[];
extern s16 D_8004C98C[];
extern OSMesgQueue gSchedDMAQueue;

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
extern u8 D_800B6440[];
extern u16 gHuffmanFreq[];
extern s16 gHuffmanParent[];
extern s16 gHuffmanSon[];

extern s32 D_8013C208;
extern s32 D_8013C218;

#define N 4096 /* buffer size */
#define F 60   /* lookahead buffer size */
#define THRESHOLD 2

#define N_CHAR (256 - THRESHOLD + F)
/* kinds of characters (character code = 0..N_CHAR-1) */
#define T (N_CHAR * 2 - 1) /* size of table */
#define R (T - 1)          /* position of root */
#define MAX_FREQ 0x8000    /* updates tree when the */

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
    u16* ptr;

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
        if (k > gHuffmanFreq[m & 0xFFFFFFFF]) {
            ptr = &gHuffmanFreq[m + 2];
            
            while (n = k > ptr[-1]) { // i = (k > ptr[-1]);
                ptr++;
            }
            l = ptr - gHuffmanFreq - 2;

            // Swap frequencies
            gHuffmanFreq[c] = ptr[-2];
            ptr[-2] = k;

            // Update parent and child relationships
            i = gHuffmanSon[c];
            gHuffmanParent[i] = l;
            if (i < T) gHuffmanParent[i + 1] = l;

            j = gHuffmanSon[l];
            gHuffmanSon[l] = i;

            gHuffmanParent[j] = c;
            if (j < T) gHuffmanParent[j + 1] = c;

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
