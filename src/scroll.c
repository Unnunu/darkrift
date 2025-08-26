#include "common.h"
#include "task.h"

extern s32 D_8008012C;
extern s32 D_80049AE4;
extern s32 D_80049AE8;
extern s32 D_80081428;
extern u8 D_80080129;
extern Gfx *gMainGfxPos;
extern Gfx *D_8005BFDC;
extern Gfx *gOverlayGfxPos;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;

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
    tex->colorIndexed = asset->format;
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

void texture_render(Texture *tex, s32 texYOffset, s32 posY, u32 height, u32 scrollS, u32 scrollT) {
    Gfx **dlist;
    s32 texWidth;
    u8 *image;
    u32 left_part_width;
    s32 strip_height;
    s32 var1;
    s32 padding[5];

    image = tex->raster;
    image += texYOffset * tex->width;
    texWidth = tex->width;
    dlist = (tex->flags & 2) ? &gOverlayGfxPos : &gMainGfxPos;

    gDPLoadTLUT_pal256((*dlist)++, VIRTUAL_TO_PHYSICAL(tex->palette));

    if (texWidth < gScreenWidth + scrollS) {
        image -= texWidth;
        do {
            strip_height = MIN(height, 5);
            left_part_width = texWidth - scrollS;
            gDPLoadTextureTile((*dlist)++,                 // pkt
                               VIRTUAL_TO_PHYSICAL(image), // timg
                               G_IM_FMT_CI,                // fmt
                               G_IM_SIZ_8b,                // siz
                               texWidth,                   // width
                               0,                          // height
                               scrollS,                    // uls
                               scrollT,                    // ult
                               scrollS + gScreenWidth,     // lrs
                               scrollT + strip_height,     // lrt
                               0,                          // pal
                               G_TX_NOMIRROR | G_TX_CLAMP, // cms
                               G_TX_NOMIRROR | G_TX_CLAMP, // cmt
                               G_TX_NOMASK,                // masks
                               G_TX_NOMASK,                // maskt
                               G_TX_NOLOD,                 // shifts
                               G_TX_NOLOD                  // shiftt
            );
            gSPTextureRectangle((*dlist)++,                     // pkt
                                0 << 2,                         // xl
                                posY << 2,                      // yl
                                left_part_width << 2,           // xh
                                (posY + strip_height - 1) << 2, // yh
                                G_TX_RENDERTILE,                // tile
                                scrollS << 5,                   // s
                                (scrollT + 1) << 5,             // t
                                4 << 10,                        // dsdx
                                1 << 10                         // dtdy
            );
            gSPTextureRectangle((*dlist)++,                       // pkt
                                left_part_width << 2,             // xl
                                posY << 2,                        // yl
                                (gScreenWidth - 1) << 2,          // xh
                                (posY + strip_height - 1) << 2,   // yh
                                G_TX_RENDERTILE,                  // tile
                                (scrollS + left_part_width) << 5, // s
                                scrollT << 5,                     // t
                                4 << 10,                          // dsdx
                                1 << 10                           // dtdy
            );
            scrollT += strip_height;
            posY += strip_height;
            height -= strip_height;
        } while (height != 0);
    } else {
        do {
            strip_height = MIN(height, 6);
            gDPLoadTextureTile((*dlist)++,                 // pkt
                               VIRTUAL_TO_PHYSICAL(image), // timg
                               G_IM_FMT_CI,                // fmt
                               G_IM_SIZ_8b,                // siz
                               texWidth,                   // width
                               0,                          // height
                               scrollS,                    // uls
                               scrollT,                    // ult
                               scrollS + gScreenWidth,     // lrs
                               scrollT + strip_height - 1, // lrt
                               0,                          // pal
                               G_TX_NOMIRROR | G_TX_CLAMP, // cms
                               G_TX_NOMIRROR | G_TX_CLAMP, // cmt
                               G_TX_NOMASK,                // masks
                               G_TX_NOMASK,                // maskt
                               G_TX_NOLOD,                 // shifts
                               G_TX_NOLOD                  // shiftt
            );
            gSPTextureRectangle((*dlist)++,                     // pkt
                                0 << 2,                         // xl
                                posY << 2,                      // yl
                                (SCREEN_WIDTH - 1) << 2,        // xh
                                (posY + strip_height - 1) << 2, // yh
                                G_TX_RENDERTILE,                // tile
                                scrollS << 5,                   // s
                                scrollT << 5,                   // t
                                4 << 10,                        // dsdx
                                1 << 10                         // dtdy
            );

            scrollT += strip_height;
            posY += strip_height;
            height -= strip_height;
        } while (height != 0);
    }
}

void bg_draw(void) {
    Texture *tex;
    s32 t0;
    s32 maxY;
    s32 posY;
    s32 texYBase;
    s32 height;
    s32 v0;
    u32 scrollS;

    maxY = 0;

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
            posY = v0;

            if (posY < 0) {
                texYBase = -v0;
                posY = 0;
                if (texYBase >= tex->height) {
                    tex = tex->next;
                    continue;
                }
            } else {
                texYBase = 0;
            }

            height = MIN(SCREEN_HEIGHT - posY, tex->height - texYBase);
            scrollS = (tex->unk_18 + t0) % tex->width;
            texture_render(tex, texYBase, posY, height, scrollS, 0);

            if (!(tex->flags & 2) && maxY < posY + height && posY + height < SCREEN_HEIGHT) {
                maxY = posY + height;
            }
        }
        tex = tex->next;
    }

    if (maxY > 0 && D_80080129 && !(D_8008012C & 0x40)) {
        s32 t3 = MIN(64, SCREEN_HEIGHT - maxY);

        gDPPipeSync(gMainGfxPos++);
        gDPSetCycleType(gMainGfxPos++, G_CYC_FILL);
        gDPSetFillColor(gMainGfxPos++, (GPACK_RGBA5551(D_80080130, D_80080132, D_80080134, 1) << 16) |
                                           GPACK_RGBA5551(D_80080130, D_80080132, D_80080134, 1));
        gDPFillRectangle(gMainGfxPos++, 0, maxY, gScreenWidth - 1, maxY + t3 - 1);
        gDPPipeSync(gMainGfxPos++);
        gDPSetCycleType(gMainGfxPos++, G_CYC_COPY);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/scroll/func_800156B0.s")

#ifdef NON_EQUIVALENT
void func_80015724(Object *obj) {
    AssetSP2Sub2 *v1;
    TextureAsset *texture;
    s32 s1;
    AssetSP2Sub3 *spE0;
    AssetSP2Sub3 *newvar;
    u32 lo;
    s32 i;
    s32 spD8;
    s32 a3;
    s32 t1;
    s32 t5;
    s32 v0;
    s32 ra;
    s32 t0;
    s32 t4;
    s32 var1;
    Gfx **dlist; // sp9C
    u8 *raster;
    u16 *palette;
    u32 strip_height;
    AssetSP2 *sprite_map;

    sprite_map = obj->sprite_map;
    v1 = &sprite_map->sprites[obj->spriteId];
    texture = v1->texture;
    spE0 = v1->parts;
    spD8 = v1->numParts;
    s1 = texture->width;
    raster = texture->data;
    palette = texture->data + texture->width * texture->height;

    if (obj->flags & 0x4000000) {
        dlist = &gOverlayGfxPos;
        D_8008012C |= 2;
    } else {
        dlist = &D_8005BFDC;
    }

    gDPLoadTLUT_pal256((*dlist)++, VIRTUAL_TO_PHYSICAL(palette));

    task_execute(obj);

    if (obj->flags & 4) {
        return;
    }

    for (i = 0; i != spD8; i++) {
        t5 = spE0->unk_00;
        a3 = spE0->unk_04;
        t1 = spE0->unk_08;
        var1 = spE0->unk_0C;
        v0 = obj->pos.x + spE0->unk_10;
        ra = obj->pos.y + spE0->unk_14;
        t0 = t1 - a3 + 1;
        t4 = var1 - t5;

        spE0++;

        if (v0 < 0) {
            v0 = 0;
        }
        if (ra < 0) {
            ra = 0;
        }
        if (v0 + t0 > gScreenWidth) {
            t0 = gScreenWidth - v0;
        }
        if (t4 + ra > gScreenHeight) {
            t4 = gScreenHeight - ra;
        }

        lo = 0x800 / (u32) ((t0 + 7) & ~7);

        do {
            strip_height = MIN(t4, lo);
            gDPLoadTextureTile((*dlist)++,                  // pkt
                               VIRTUAL_TO_PHYSICAL(raster), // timg
                               G_IM_FMT_CI,                 // fmt
                               G_IM_SIZ_8b,                 // siz
                               s1,                          // width
                               0,                           // height
                               a3,                          // uls
                               t5,                          // ult
                               t1,                          // lrs
                               t5 + strip_height - 1,       // lrt
                               0,                           // pal
                               G_TX_NOMIRROR | G_TX_CLAMP,  // cms
                               G_TX_NOMIRROR | G_TX_CLAMP,  // cmt
                               G_TX_NOMASK,                 // masks
                               G_TX_NOMASK,                 // maskt
                               G_TX_NOLOD,                  // shifts
                               G_TX_NOLOD                   // shiftt
            );

            gSPTextureRectangle((*dlist)++,                   // pkt
                                v0 << 2,                      // xl
                                ra << 2,                      // yl
                                (v0 + t0 - 2) << 2,           // xh
                                (ra + strip_height - 1) << 2, // yh
                                G_TX_RENDERTILE,              // tile
                                a3 << 5,                      // s
                                t5 << 5,                      // t
                                4 << 10,                      // dsdx
                                1 << 10                       // dtdy
            );

            t5 += strip_height;
            ra += strip_height;
            t4 -= strip_height;
        } while (t4 != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/scroll/func_80015724.s")
void func_80015724(Object *);
#endif
