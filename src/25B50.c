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
extern u16 D_800B7480[];
extern s16 D_800B7968[];
extern s16 D_800B80C8[];

extern s32 D_8013C208;
extern s32 D_8013C218;

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

    for (i = 0; i < 314; i++) {
        D_800B7480[i] = 1;
        D_800B80C8[i] = 627 + i;
        D_800B7968[627 + i] = i;
    }

    for (i = 0, j = 314; j < 627; i += 2, j++) {
        D_800B7480[j] = D_800B7480[i] + D_800B7480[i + 1];
        D_800B80C8[j] = i;
        D_800B7968[i] = D_800B7968[i + 1] = j;
    }

    D_800B7480[627] = -1;
    D_800B7968[626] = 0;
    D_8004C964 = 0;
    D_8004C960 = 0;
}

#ifdef NON_EQUIVALENT
void func_8002541C(void) {
    s16 i;
    s16 j;
    s16 k;
    u32 l;
    u16 q;

    j = 0;
    for (i = 0; i < 627; i++) {
        if (D_800B80C8[i] >= 627) {
            D_800B7480[j] = (D_800B7480[i] + 1) / 2;
            D_800B80C8[j] = D_800B80C8[i];
            j++;
        }
    }

    for (i = 0, j = 314; j < 627; j++, i += 2) {
        q = D_800B7480[i] + D_800B7480[(s16) (i + 1)];
        D_800B7480[j] = q;

        for (k = j - 1; D_800B7480[k] > q; k--) {}

        for (l = j; l > k + 1; l--) {
            D_800B7480[l] = D_800B7480[l - 1];
        }
        D_800B7480[k + 1] = q;

        for (l = j; l > k + 1; l--) {
            D_800B80C8[l] = D_800B80C8[l - 1];
        }
        D_800B80C8[k + 1] = i;
    }

    for (i = 0; i < 627; i++) {
        if (D_800B80C8[i] >= 627) {
            D_800B7968[D_800B80C8[i]] = i;
        } else {
            D_800B7968[D_800B80C8[i]] = D_800B7968[D_800B80C8[i] + 1] = i;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/25B50/func_8002541C.s")
void func_8002541C(void);
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/25B50/func_80025624.s")
void func_80025624(s32);

s16 func_80025780(void) {
    u16 s0;

    s0 = D_800B80C8[626];
    while (s0 < 0x273) {
        s0 += func_80025120();
        s0 = D_800B80C8[s0];
    }

    s0 -= 0x273;
    func_80025624(s0);
    return s0;
}

#ifdef NON_MATCHING
s16 func_80025800(void) {
    u16 a;
    u16 b;
    u16 c;

    a = func_800251D4();
    b = D_8004C860[a];
    c = D_8004C760[a] << 6;

    return ((func_80025278(b - 2) | (a << (u16) (b - 2))) & 0x3F) | c;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/25B50/func_80025800.s")
s16 func_80025800(void);
#endif

#ifdef NON_MATCHING
void func_80025878(void) {
    s16 i;
    s16 s1;
    s32 s4;
    s16 v0;
    s16 s0;
    s16 v1;
    s16 j;

    func_80025344();
    for (i = 0; i < 4036; i++) {
        D_800B6440[i] = ' ';
    }

    s1 = 4036;
    for (s4 = 0; s4 < D_800B6438->unpacked_size;) {
        v0 = func_80025780();
        if (v0 <= 0xFF) {
            *D_800B641C++ = v0;
            D_800B6440[s1++] = v0;
            s1 &= 0xFFF;
            s4++;
        } else {
            v1 = (s1 - func_80025800() - 1) & 0xFFF;
            i = v0 - 0xFD;
            for (s0 = 0; s0 < i; s0++) {
                v0 = D_800B6440[(v1 + s0) & 0xFFF];
                *D_800B641C++ = v0;
                D_800B6440[s1++] = v0;
                s1 &= 0xFFF;
                s4++;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/25B50/func_80025878.s")
void func_80025878(void);
#endif

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

    func_80025878();
}
