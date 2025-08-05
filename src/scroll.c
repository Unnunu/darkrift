#include "common.h"

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

Texture *load_background(char *name, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 flags, s32 context) {
    Texture *head;
    s32 pad;
    TextureAsset *asset;
    Texture *tex;
    char fullname[20];

    tex = mem_alloc(sizeof(Texture), "scroll.c", 21);

    str_copy(fullname, name);
    str_concat(fullname, ".tex");

    asset = (TextureAsset *) gAssets[asset_find(fullname, context)].data;

    tex->width = asset->width;
    tex->height = asset->height;
    tex->colorIndexed = asset->unk_08;
    tex->flags = flags;
    tex->unk_20 = arg3;
    tex->unk_24 = arg4;
    tex->unk_18 = arg1;
    tex->unk_1C = arg2;
    tex->raster = asset->data;

    if (tex->colorIndexed == TRUE) {
        tex->palette = asset->data + tex->width * tex->height;
    } else {
        tex->palette = NULL;
    }

    head = D_80049AE0;
    D_80049AE0 = tex;
    tex->next = head;

    if (!(flags & 1)) {
        s16 temp = tex->raster[0] * 2;
        tex->palette[temp] = 0;
        tex->palette[temp + 1] = 0;
    }
    if (flags & 2) {
        D_8008012C |= 2;
    }

    return tex;
}

void func_80014CB4(Texture *tex) {
    Texture *it;
    Texture *prev;

    it = D_80049AE0;

    if (tex == it) {
        D_80049AE0 = D_80049AE0->next;
        mem_free(tex);
        return;
    }

    while (it != NULL) {
        if (it == tex) {
            prev->next = it->next;
            mem_free(tex);
            return;
        }
        prev = it;
        it = it->next;
    }
}

void func_80014D2C(Texture *tex, s32 texYOffset, s32 screenY, u32 height, u32 scrollS, u32 scrollT) {
    Gfx **dlist;
    s32 texWidth;
    u8 *image;
    u32 a1;
    s32 vart0;
    s32 var1;
    s32 padding[5];

    image = tex->raster;
    image += texYOffset * tex->width;
    texWidth = tex->width;
    dlist = (tex->flags & 2) ? &D_8005BFE0 : &D_8005BFD8;

    gDPLoadTLUT_pal256((*dlist)++, VIRTUAL_TO_PHYSICAL(tex->palette));

    if (texWidth < D_8005BFC8 + scrollS) {
        image -= texWidth;
        do {
            vart0 = MIN(height, 5);
            a1 = texWidth - scrollS;
            gDPLoadTextureTile((*dlist)++, VIRTUAL_TO_PHYSICAL(image), G_IM_FMT_CI, G_IM_SIZ_8b, texWidth, 0, scrollS,
                               scrollT, scrollS + D_8005BFC8, scrollT + vart0, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle((*dlist)++, 0, screenY << 2, a1 << 2, (screenY + vart0 - 1) << 2, 0, scrollS << 5,
                                (scrollT + 1) << 5, 0x1000, 0x400);
            gSPTextureRectangle((*dlist)++, a1 << 2, screenY << 2, (D_8005BFC8 - 1) << 2, (screenY + vart0 - 1) << 2, 0,
                                (scrollS + a1) << 5, scrollT << 5, 0x1000, 0x400);
            scrollT += vart0;
            screenY += vart0;
            height -= vart0;
        } while (height != 0);
    } else {
        do {
            vart0 = MIN(height, 6);
            gDPLoadTextureTile((*dlist)++, VIRTUAL_TO_PHYSICAL(image), G_IM_FMT_CI, G_IM_SIZ_8b, texWidth, 0, scrollS,
                               scrollT, scrollS + D_8005BFC8, scrollT + vart0 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle((*dlist)++, 0, screenY << 2, (SCREEN_WIDTH - 1) << 2, (screenY + vart0 - 1) << 2, 0,
                                scrollS << 5, scrollT << 5, 0x1000, 0x400);

            scrollT += vart0;
            screenY += vart0;
            height -= vart0;
        } while (height != 0);
    }
}

void func_800153C4(void) {
    Texture *tex;
    s32 t0;
    s32 s3;
    s32 screenY;
    s32 texYBase;
    s32 height;
    s32 v0;
    s32 scrollS;

    s3 = 0;

    for (tex = D_80049AE0; tex != NULL;) {
        if (!(tex->flags & 4)) {
            if (!(tex->flags & 2)) {
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
            screenY = v0;

            if (screenY < 0) {
                texYBase = -v0;
                screenY = 0;
                if (texYBase >= tex->height) {
                    tex = tex->next;
                    continue;
                }
            } else {
                texYBase = 0;
            }

            height = MIN(SCREEN_HEIGHT - screenY, tex->height - texYBase);
            scrollS = (tex->unk_18 + t0) % tex->width;
            func_80014D2C(tex, texYBase, screenY, height, scrollS, 0);

            if (!(tex->flags & 2) && s3 < screenY + height && screenY + height < SCREEN_HEIGHT) {
                s3 = screenY + height;
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
/*
void func_80015724(Object *obj) {
    UnkObjectSub2 *v1;

    v1 = obj->sprite_map->unk_48[obj->unk_084];
}
    */
