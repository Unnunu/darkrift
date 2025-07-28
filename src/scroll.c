#include "common.h"

typedef struct TextureAsset {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[1];
} TextureAsset;

extern s32 D_8008012C;
extern s32 D_80049AE4;
extern s32 D_80049AE8;
extern s32 D_80081428;
extern u8 D_80080129;
extern Gfx *D_8005BFD8;
extern Gfx *D_8005BFE0;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;
extern u16 D_8005BFC8;

Texture *func_80014B60(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Texture *head;
    s32 pad;
    TextureAsset *asset;
    Texture *tex;
    char fullname[20];

    tex = mem_alloc(sizeof(Texture), "scroll.c", 21);

    str_copy(fullname, arg0);
    str_concat(fullname, ".tex");

    asset = (TextureAsset *) gAssets[asset_find(fullname, arg6)].data;

    tex->unk_00 = asset->unk_00;
    tex->unk_04 = asset->unk_04;
    tex->unk_08 = asset->unk_08;
    tex->unk_0C = arg5;
    tex->unk_20 = arg3;
    tex->unk_24 = arg4;
    tex->unk_18 = arg1;
    tex->unk_1C = arg2;
    tex->unk_10 = asset->unk_10;

    if (tex->unk_08 == 1) {
        tex->unk_14 = asset->unk_10 + tex->unk_00 * tex->unk_04;
    } else {
        tex->unk_14 = NULL;
    }

    head = D_80049AE0;
    D_80049AE0 = tex;
    tex->next = head;

    if (!(arg5 & 1)) {
        s16 temp = tex->unk_10[0] * 2;
        tex->unk_14[temp] = 0;
        tex->unk_14[temp + 1] = 0;
    }
    if (arg5 & 2) {
        D_8008012C |= 2;
    }

    return tex;
}

#pragma GLOBAL_ASM("asm/nonmatchings/scroll/func_80014CB4.s")

void func_80014D2C(Texture *tex, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5) {
    Gfx *dlist;
    u32 t2;
    u8 *t0;
    u32 vart0;

    t2 = tex->unk_00;
    t0 = tex->unk_10 + arg1 * t2;

    if (tex->unk_0C & 2) {
        dlist = D_8005BFE0;
    } else {
        dlist = D_8005BFD8;
    }

    gDPLoadTLUT_pal256(dlist++, VIRTUAL_TO_PHYSICAL(tex->unk_14));

    if (t2 < D_8005BFC8 + arg4) {
        do {
            vart0 = MIN(arg3, 5);
            gDPLoadTextureTile(dlist++, VIRTUAL_TO_PHYSICAL(t0 - t2), G_IM_FMT_CI, G_IM_SIZ_8b, t2, 0, arg4, arg5,
                               D_8005BFC8 + arg4, arg5 + vart0, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(dlist++, (t2 - arg4) * 4, (arg2 + vart0 - 1) * 4, t2 * 4, arg2 * 4, 0, 0, 0, 0x1000, 0x400);
            gSPTextureRectangle(dlist++, (t2 - arg4) * 4, (arg2 + vart0 - 1) * 4, t2 * 4, arg2 * 4, 0, 0, 0, 0x1000, 0x400);
            arg5 += vart0;
            arg2 += vart0;
            arg3 -= vart0;
        } while (arg3 != 0);
    } else {
        do {
            vart0 = MIN(arg3, 5);
            gDPLoadTextureTile(dlist++, VIRTUAL_TO_PHYSICAL(t0), G_IM_FMT_CI, G_IM_SIZ_8b, t2, 0, arg4, arg5,
                               D_8005BFC8 + arg4, arg5 + vart0, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(dlist++, 0, arg2 * 4, 319 * 4, (arg2 + vart0) * 4, 0, arg4 << 5, arg5 << 5, 0x1000, 0x400);
            arg5 += vart0;
            arg2 += vart0;
            arg3 -= vart0;
        } while (arg3 != 0);
    }
}

void func_800153C4(void) {
    Texture *tex;
    s32 t0;
    s32 s3;
    s32 s2;
    s32 a1;
    s32 s1;
    s32 v0;
    s32 q;

    s3 = 0;

    for (tex = D_80049AE0; tex != NULL;) {
        if (!(tex->unk_0C & 4)) {

            if (!(tex->unk_0C & 2)) {
                t0 = ((tex->unk_20 * D_80049AE4) >> 16) + D_80081428;
            } else {
                t0 = 0;
            }

            v0 = ((tex->unk_24 * D_80049AE8) >> 16);
            v0 += tex->unk_1C;

            if (v0 >= SCREEN_HEIGHT) {
                tex = tex->next;
                continue;
            }
            s2 = v0;

            if (s2 < 0) {
                a1 = -v0;
                s2 = 0;
                if (a1 >= tex->unk_04) {
                    tex = tex->next;
                    continue;
                }
            } else {
                a1 = 0;
            }

            s1 = MIN(SCREEN_HEIGHT - s2, tex->unk_04 - a1);
            q = (tex->unk_18 + t0) % tex->unk_00;
            func_80014D2C(tex, a1, s2, s1, q, 0);

            if (!(tex->unk_0C & 2) && s3 < s2 + s1 && s2 + s1 < SCREEN_HEIGHT) {
                s3 = s2 + s1;
            }
        }
        tex = tex->next;
    }

    if (s3 > 0 && D_80080129 && !(D_8008012C & 0x40)) {
        s32 t3 = MIN(64, SCREEN_HEIGHT - s3);

        gDPPipeSync(D_8005BFD8++);
        gDPSetCycleType(D_8005BFD8++, G_CYC_FILL);
        gDPSetFillColor(D_8005BFD8++, (GPACK_RGBA5551(D_80080130, D_80080132, D_80080134, 1) << 16) |
                                          GPACK_RGBA5551(D_80080130, D_80080132, D_80080134, 1));
        gDPFillRectangle(D_8005BFD8++, 0, s3, D_8005BFC8 - 1, s3 + t3 - 1);
        gDPPipeSync(D_8005BFD8++);
        gDPSetCycleType(D_8005BFD8++, G_CYC_COPY);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/scroll/func_800156B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/scroll/func_80015724.s")
