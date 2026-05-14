#include "common.h"
#include "task.h"

extern s32 D_8008012C;
extern s32 gBgScrollY;
extern u8 D_80080129;
extern Gfx *gMainGfxPos;
extern Gfx *D_8005BFDC;
extern Gfx *gOverlayGfxPos;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;

BackgroundLayer *gBgLayerList = NULL;
s32 gBgScrollX = 0;
s32 gBgScrollY = 0;

/* .bss */
s32 D_80081420;
s32 D_80081424;
s32 D_80081428;
s32 D_8008142C;
s32 D_80081430;
s32 D_80081434;
s32 D_80081438;

BackgroundLayer *bg_layer_create(char *assetName, s32 arg1, s32 posY, s32 parallaxX, s32 parallaxY, s32 flags,
                                 s32 assetContext) {
    BackgroundLayer *head;
    s32 pad;
    TextureAsset *asset;
    BackgroundLayer *bgLayer;
    char fullname[20];

    bgLayer = mem_alloc(sizeof(BackgroundLayer), "scroll.c", 21);

    str_copy(fullname, assetName);
    str_concat(fullname, ".tex");

    asset = (TextureAsset *) gAssets[asset_find(fullname, assetContext)].data;

    bgLayer->width = asset->width;
    bgLayer->height = asset->height;
    bgLayer->colorIndexed = asset->format;
    bgLayer->flags = flags;
    bgLayer->parallaxX = parallaxX;
    bgLayer->parallaxY = parallaxY;
    bgLayer->unk_18 = arg1;
    bgLayer->posY = posY;
    bgLayer->raster = asset->data;

    if (bgLayer->colorIndexed == TRUE) {
        bgLayer->palette = asset->data + bgLayer->width * bgLayer->height;
    } else {
        bgLayer->palette = NULL;
    }

    head = gBgLayerList;
    gBgLayerList = bgLayer;
    bgLayer->next = head;

    if (!(flags & TEX_FLAG_1)) {
        s16 temp = bgLayer->raster[0] * 2;
        bgLayer->palette[temp] = 0;
        bgLayer->palette[temp + 1] = 0;
    }
    if (flags & BG_FLAG_OVERLAY) {
        D_8008012C |= GFX_FLAG_OVERLAY;
    }

    return bgLayer;
}

void bg_layer_delete(BackgroundLayer *tex) {
    BackgroundLayer *it;
    BackgroundLayer *prev;

    it = gBgLayerList;

    if (tex == it) {
        gBgLayerList = gBgLayerList->next;
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

void bg_draw_one(BackgroundLayer *bgLayer, s32 srcY, s32 posY, u32 height, u32 texS, u32 texT) {
    Gfx **dlist;
    s32 texWidth;
    u8 *image;
    u32 leftWidth;
    s32 stripHeight;
    s32 padding[6];

    image = bgLayer->raster;
    image += srcY * bgLayer->width;
    texWidth = bgLayer->width;
    dlist = (bgLayer->flags & BG_FLAG_OVERLAY) ? &gOverlayGfxPos : &gMainGfxPos;

    gDPLoadTLUT_pal256((*dlist)++, VIRTUAL_TO_PHYSICAL(bgLayer->palette));

    if (texWidth < gScreenWidth + texS) {
        image -= texWidth;
        do {
            stripHeight = MIN(height, 5);
            leftWidth = texWidth - texS;
            gDPLoadTextureTile((*dlist)++,                 // pkt
                               VIRTUAL_TO_PHYSICAL(image), // timg
                               G_IM_FMT_CI,                // fmt
                               G_IM_SIZ_8b,                // siz
                               texWidth,                   // width
                               0,                          // height
                               texS,                       // uls
                               texT,                       // ult
                               texS + gScreenWidth,        // lrs
                               texT + stripHeight,         // lrt
                               0,                          // pal
                               G_TX_NOMIRROR | G_TX_CLAMP, // cms
                               G_TX_NOMIRROR | G_TX_CLAMP, // cmt
                               G_TX_NOMASK,                // masks
                               G_TX_NOMASK,                // maskt
                               G_TX_NOLOD,                 // shifts
                               G_TX_NOLOD                  // shiftt
            );
            gSPTextureRectangle((*dlist)++,                    // pkt
                                0 << 2,                        // xl
                                posY << 2,                     // yl
                                leftWidth << 2,                // xh
                                (posY + stripHeight - 1) << 2, // yh
                                G_TX_RENDERTILE,               // tile
                                texS << 5,                     // s
                                (texT + 1) << 5,               // t
                                4 << 10,                       // dsdx
                                1 << 10                        // dtdy
            );
            gSPTextureRectangle((*dlist)++,                    // pkt
                                leftWidth << 2,                // xl
                                posY << 2,                     // yl
                                (gScreenWidth - 1) << 2,       // xh
                                (posY + stripHeight - 1) << 2, // yh
                                G_TX_RENDERTILE,               // tile
                                (texS + leftWidth) << 5,       // s
                                texT << 5,                     // t
                                4 << 10,                       // dsdx
                                1 << 10                        // dtdy
            );
            texT += stripHeight;
            posY += stripHeight;
            height -= stripHeight;
        } while (height != 0);
    } else {
        do {
            stripHeight = MIN(height, 6);
            gDPLoadTextureTile((*dlist)++,                 // pkt
                               VIRTUAL_TO_PHYSICAL(image), // timg
                               G_IM_FMT_CI,                // fmt
                               G_IM_SIZ_8b,                // siz
                               texWidth,                   // width
                               0,                          // height
                               texS,                       // uls
                               texT,                       // ult
                               texS + gScreenWidth,        // lrs
                               texT + stripHeight - 1,     // lrt
                               0,                          // pal
                               G_TX_NOMIRROR | G_TX_CLAMP, // cms
                               G_TX_NOMIRROR | G_TX_CLAMP, // cmt
                               G_TX_NOMASK,                // masks
                               G_TX_NOMASK,                // maskt
                               G_TX_NOLOD,                 // shifts
                               G_TX_NOLOD                  // shiftt
            );
            gSPTextureRectangle((*dlist)++,                    // pkt
                                0 << 2,                        // xl
                                posY << 2,                     // yl
                                (SCREEN_WIDTH - 1) << 2,       // xh
                                (posY + stripHeight - 1) << 2, // yh
                                G_TX_RENDERTILE,               // tile
                                texS << 5,                     // s
                                texT << 5,                     // t
                                4 << 10,                       // dsdx
                                1 << 10                        // dtdy
            );

            texT += stripHeight;
            posY += stripHeight;
            height -= stripHeight;
        } while (height != 0);
    }
}

void bg_draw_all(void) {
    BackgroundLayer *bgLayer;
    s32 scrollX;
    s32 maxY;
    s32 posY;
    s32 srcY;
    s32 height;
    s32 screenY;
    u32 texS;

    maxY = 0;

    for (bgLayer = gBgLayerList; bgLayer != NULL;) {
        if (!(bgLayer->flags & BG_FLAG_HIDDEN)) {
            if (!(bgLayer->flags & BG_FLAG_OVERLAY)) {
                scrollX = ((bgLayer->parallaxX * gBgScrollX) >> 16) + D_80081428;
            } else {
                scrollX = 0;
            }

            screenY = (bgLayer->parallaxY * gBgScrollY) >> 16;
            screenY += bgLayer->posY;

            if (screenY >= SCREEN_HEIGHT) {
                bgLayer = bgLayer->next;
                continue;
            }
            posY = screenY;

            if (posY < 0) {
                srcY = -screenY;
                posY = 0;
                if (srcY >= bgLayer->height) {
                    bgLayer = bgLayer->next;
                    continue;
                }
            } else {
                srcY = 0;
            }

            height = MIN(SCREEN_HEIGHT - posY, bgLayer->height - srcY);
            texS = (bgLayer->unk_18 + scrollX) % bgLayer->width;
            bg_draw_one(bgLayer, srcY, posY, height, texS, 0);

            if (!(bgLayer->flags & BG_FLAG_OVERLAY) && maxY < posY + height && posY + height < SCREEN_HEIGHT) {
                maxY = posY + height;
            }
        }
        bgLayer = bgLayer->next;
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
    palette = (u16 *) (v1->texture->data + width * v1->texture->height);

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
        ult = part->topT;
        uls = part->leftS;
        lrs = part->rightS;
        lrt = part->bottomT;
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
