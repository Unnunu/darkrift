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
        D_8008012C |= GFX_FLAG_OVERLAY;
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

    if (maxY > 0 && D_80080129 && !(D_8008012C & GFX_FLAG_40)) {
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

void func_800156B0(AssetSP2 *arg0) {
    u32 i, j;
    s32 pad[2];
    u32 sp1C;
    AssetSP2Sub2 *sprite;
    s32 numSprites;

    func_80025B40();
    sprite = arg0->sprites;
    numSprites = arg0->numSprites;
    for (i = 0; i < numSprites; i++, sprite++) {
        for (j = 0; j < sp1C; j++) {}
    }
    if (sprite) {}
}

#ifdef NON_MATCHING
void func_80015724(Object *obj) {
    AssetSP2Sub2 *v1;
    u8 *pad;
    s32 width;
    AssetSP2Sub3 *part;
    u32 i;
    s32 numParts;
    s32 pad2;
    u32 maxHeight;
    u32 uls;
    s32 lrs;
    s32 ult;
    s32 x;
    s32 y;
    s32 tileWidth;
    s32 tileHeight;
    s32 lrt;
    u8 *raster;
    u16 *palette;
    u32 strip_height;
    AssetSP2 *sprite_map;
    Gfx **dlist;

    sprite_map = obj->sprite_map;
    v1 = &sprite_map->sprites[obj->frameIndex];
    raster = v1->texture->data;
    part = v1->parts;
    numParts = v1->numParts;
    width = v1->texture->width;
    palette = (u16 *) (v1->texture->data + width * v1->texture->height * 2);

    if (obj->flags & OBJ_FLAG_4000000) {
        dlist = &gOverlayGfxPos;
        D_8008012C |= GFX_FLAG_OVERLAY;
    } else {
        dlist = &D_8005BFDC;
    }

    gDPLoadTLUT_pal256((*dlist)++, VIRTUAL_TO_PHYSICAL(palette));

    task_execute(obj);

    if (obj->flags & OBJ_FLAG_HIDDEN) {
        return;
    }

    for (i = 0; i < numParts; i++) {
        ult = part->ult;
        uls = part->uls;
        lrs = part->lrs;
        lrt = part->lrt;
        x = obj->pos.x + part->offsetX;
        y = obj->pos.y + part->offsetY;

        tileWidth = lrs - uls + 1;
        tileHeight = lrt - ult;

        if (x < 0) {
            x = 0;
        }
        if (y < 0) {
            y = 0;
        }
        if (x + tileWidth > gScreenWidth) {
            tileWidth = gScreenWidth - x;
        }
        if (y + tileHeight > gScreenHeight) {
            tileHeight = gScreenHeight - y;
        }

        part++;

        maxHeight = 0x800 / (u32) ((tileWidth + 7) & ~7);

        do {
            strip_height = MIN(tileHeight, maxHeight);
            gDPLoadTextureTile((*dlist)++,                  // pkt
                               VIRTUAL_TO_PHYSICAL(raster), // timg
                               G_IM_FMT_CI,                 // fmt
                               G_IM_SIZ_8b,                 // siz
                               width,                       // width
                               0,                           // height
                               uls,                         // uls
                               ult,                         // ult
                               lrs,                         // lrs
                               ult + strip_height - 1,      // lrt
                               0,                           // pal
                               G_TX_NOMIRROR | G_TX_CLAMP,  // cms
                               G_TX_NOMIRROR | G_TX_CLAMP,  // cmt
                               G_TX_NOMASK,                 // masks
                               G_TX_NOMASK,                 // maskt
                               G_TX_NOLOD,                  // shifts
                               G_TX_NOLOD                   // shiftt
            );

            gSPTextureRectangle((*dlist)++,                  // pkt
                                x << 2,                      // xl
                                y << 2,                      // yl
                                (x + tileWidth - 2) << 2,    // xh
                                (y + strip_height - 1) << 2, // yh
                                G_TX_RENDERTILE,             // tile
                                uls << 5,                    // s
                                ult << 5,                    // t
                                4 << 10,                     // dsdx
                                1 << 10                      // dtdy
            );

            ult += strip_height;
            y += strip_height;
            tileHeight -= strip_height;
        } while (tileHeight != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/scroll/func_80015724.s")
void func_80015724(Object *);
#endif
