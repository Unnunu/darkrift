#include "common.h"
#include "task.h"

extern s32 gGfxFlags;
extern s32 gScreenScrollY;
extern u8 sClearZbuffer;
extern Gfx *gF3dDisplayListPtr;
extern Gfx *gOverlayDlPtr;
extern Gfx *gF3dExtraListPtr;
extern s16 sFogColorR;
extern s16 sFogColorG;
extern s16 sFogColorB;

ScrollLayer *sScrollList = NULL;
s32 sScrollAccumX = 0;
s32 gScreenScrollY = 0;

/* .bss */
s32 D_80081420;
s32 D_80081424;
s32 gScreenScrollX;
s32 D_8008142C;
s32 D_80081430;
s32 D_80081434;
s32 D_80081438;

ScrollLayer *scroll_add(char *x_2b0c3984, s32 x_84ff873b, s32 x_64a8566c, s32 x_afebb108, s32 x_86f38745, s32 flags,
                        s32 x_fb21ca8c) {
    ScrollLayer *head;
    s32 pad;
    WadTextureHeader *x_d59386e0;
    ScrollLayer *x_8dddde0e;
    char x_7244b466[20];

    x_8dddde0e = mem_alloc_debug(sizeof(ScrollLayer), "scroll.c", 21);

    wad_strcpy(x_7244b466, x_2b0c3984);
    wad_strcat(x_7244b466, ".tex");

    x_d59386e0 = (WadTextureHeader *) sWadEntries[wad_entry_find(x_7244b466, x_fb21ca8c)].data;

    x_8dddde0e->width = x_d59386e0->width;
    x_8dddde0e->height = x_d59386e0->height;
    x_8dddde0e->hasPalette = x_d59386e0->format;
    x_8dddde0e->flags = flags;
    x_8dddde0e->speedX = x_afebb108;
    x_8dddde0e->speedY = x_86f38745;
    x_8dddde0e->xOffs = x_84ff873b;
    x_8dddde0e->yOffs = x_64a8566c;
    x_8dddde0e->imageData = x_d59386e0->data;

    if (x_8dddde0e->hasPalette == TRUE) {
        x_8dddde0e->palette = x_d59386e0->data + x_8dddde0e->width * x_8dddde0e->height;
    } else {
        x_8dddde0e->palette = NULL;
    }

    head = sScrollList;
    sScrollList = x_8dddde0e;
    x_8dddde0e->next = head;

    if (!(flags & x_96186256)) {
        s16 temp = x_8dddde0e->imageData[0] * 2;
        x_8dddde0e->palette[temp] = 0;
        x_8dddde0e->palette[temp + 1] = 0;
    }
    if (flags & x_8ce7ef70) {
        gGfxFlags |= GFX_EXTRA_DL;
    }

    return x_8dddde0e;
}

void scroll_remove(ScrollLayer *x_a0b04eac) {
    ScrollLayer *it;
    ScrollLayer *prev;

    it = sScrollList;

    if (x_a0b04eac == it) {
        sScrollList = sScrollList->next;
        mem_free(x_a0b04eac);
        return;
    }

    while (it != NULL) {
        if (it == x_a0b04eac) {
            prev->next = it->next;
            mem_free(x_a0b04eac);
            return;
        }
        prev = it;
        it = it->next;
    }
}

void scroll_tile_render(ScrollLayer *x_8dddde0e, s32 x_ace80dba, s32 x_64a8566c, u32 height, u32 x_c2580ba5, u32 texT) {
    Gfx **x_bde24317;
    s32 x_9dc253a1;
    u8 *image;
    u32 x_9bdb24e2;
    s32 x_54670c5d;
    s32 padding[6];

    image = x_8dddde0e->imageData;
    image += x_ace80dba * x_8dddde0e->width;
    x_9dc253a1 = x_8dddde0e->width;
    x_bde24317 = (x_8dddde0e->flags & x_8ce7ef70) ? &gF3dExtraListPtr : &gF3dDisplayListPtr;

    gDPLoadTLUT_pal256((*x_bde24317)++, x_c485761a(x_8dddde0e->palette));

    if (x_9dc253a1 < x_c84980f9 + x_c2580ba5) {
        image -= x_9dc253a1;
        do {
            x_54670c5d = MIN(height, 5);
            x_9bdb24e2 = x_9dc253a1 - x_c2580ba5;
            gDPLoadTextureTile((*x_bde24317)++,            // pkt
                               x_c485761a(image),          // timg
                               G_IM_FMT_CI,                // fmt
                               G_IM_SIZ_8b,                // siz
                               x_9dc253a1,                 // width
                               0,                          // height
                               x_c2580ba5,                 // uls
                               texT,                       // ult
                               x_c2580ba5 + x_c84980f9,    // lrs
                               texT + x_54670c5d,          // lrt
                               0,                          // pal
                               G_TX_NOMIRROR | G_TX_CLAMP, // cms
                               G_TX_NOMIRROR | G_TX_CLAMP, // cmt
                               G_TX_NOMASK,                // masks
                               G_TX_NOMASK,                // maskt
                               G_TX_NOLOD,                 // shifts
                               G_TX_NOLOD                  // shiftt
            );
            gSPTextureRectangle((*x_bde24317)++,                    // pkt
                                0 << 2,                             // xl
                                x_64a8566c << 2,                    // yl
                                x_9bdb24e2 << 2,                    // xh
                                (x_64a8566c + x_54670c5d - 1) << 2, // yh
                                G_TX_RENDERTILE,                    // tile
                                x_c2580ba5 << 5,                    // s
                                (texT + 1) << 5,                    // t
                                4 << 10,                            // dsdx
                                1 << 10                             // dtdy
            );
            gSPTextureRectangle((*x_bde24317)++,                    // pkt
                                x_9bdb24e2 << 2,                    // xl
                                x_64a8566c << 2,                    // yl
                                (x_c84980f9 - 1) << 2,              // xh
                                (x_64a8566c + x_54670c5d - 1) << 2, // yh
                                G_TX_RENDERTILE,                    // tile
                                (x_c2580ba5 + x_9bdb24e2) << 5,     // s
                                texT << 5,                          // t
                                4 << 10,                            // dsdx
                                1 << 10                             // dtdy
            );
            texT += x_54670c5d;
            x_64a8566c += x_54670c5d;
            height -= x_54670c5d;
        } while (height != 0);
    } else {
        do {
            x_54670c5d = MIN(height, 6);
            gDPLoadTextureTile((*x_bde24317)++,            // pkt
                               x_c485761a(image),          // timg
                               G_IM_FMT_CI,                // fmt
                               G_IM_SIZ_8b,                // siz
                               x_9dc253a1,                 // width
                               0,                          // height
                               x_c2580ba5,                 // uls
                               texT,                       // ult
                               x_c2580ba5 + x_c84980f9,    // lrs
                               texT + x_54670c5d - 1,      // lrt
                               0,                          // pal
                               G_TX_NOMIRROR | G_TX_CLAMP, // cms
                               G_TX_NOMIRROR | G_TX_CLAMP, // cmt
                               G_TX_NOMASK,                // masks
                               G_TX_NOMASK,                // maskt
                               G_TX_NOLOD,                 // shifts
                               G_TX_NOLOD                  // shiftt
            );
            gSPTextureRectangle((*x_bde24317)++,                    // pkt
                                0 << 2,                             // xl
                                x_64a8566c << 2,                    // yl
                                (x_56e08f29 - 1) << 2,              // xh
                                (x_64a8566c + x_54670c5d - 1) << 2, // yh
                                G_TX_RENDERTILE,                    // tile
                                x_c2580ba5 << 5,                    // s
                                texT << 5,                          // t
                                4 << 10,                            // dsdx
                                1 << 10                             // dtdy
            );

            texT += x_54670c5d;
            x_64a8566c += x_54670c5d;
            height -= x_54670c5d;
        } while (height != 0);
    }
}

void scroll_render(void) {
    ScrollLayer *x_8dddde0e;
    s32 x_c9084644;
    s32 x_16201079;
    s32 x_64a8566c;
    s32 x_ace80dba;
    s32 height;
    s32 x_e97c45db;
    u32 x_c2580ba5;

    x_16201079 = 0;

    for (x_8dddde0e = sScrollList; x_8dddde0e != NULL;) {
        if (!(x_8dddde0e->flags & x_607c80f4)) {
            if (!(x_8dddde0e->flags & x_8ce7ef70)) {
                x_c9084644 = ((x_8dddde0e->speedX * sScrollAccumX) >> 16) + gScreenScrollX;
            } else {
                x_c9084644 = 0;
            }

            x_e97c45db = (x_8dddde0e->speedY * gScreenScrollY) >> 16;
            x_e97c45db += x_8dddde0e->yOffs;

            if (x_e97c45db >= x_84e8ddf2) {
                x_8dddde0e = x_8dddde0e->next;
                continue;
            }
            x_64a8566c = x_e97c45db;

            if (x_64a8566c < 0) {
                x_ace80dba = -x_e97c45db;
                x_64a8566c = 0;
                if (x_ace80dba >= x_8dddde0e->height) {
                    x_8dddde0e = x_8dddde0e->next;
                    continue;
                }
            } else {
                x_ace80dba = 0;
            }

            height = MIN(x_84e8ddf2 - x_64a8566c, x_8dddde0e->height - x_ace80dba);
            x_c2580ba5 = (x_8dddde0e->xOffs + x_c9084644) % x_8dddde0e->width;
            scroll_tile_render(x_8dddde0e, x_ace80dba, x_64a8566c, height, x_c2580ba5, 0);

            if (!(x_8dddde0e->flags & x_8ce7ef70) && x_16201079 < x_64a8566c + height &&
                x_64a8566c + height < x_84e8ddf2) {
                x_16201079 = x_64a8566c + height;
            }
        }
        x_8dddde0e = x_8dddde0e->next;
    }

    if (x_16201079 > 0 && sClearZbuffer && !(gGfxFlags & GFX_BORDER_AROUND)) {
        s32 t3 = MIN(64, x_84e8ddf2 - x_16201079);

        gDPPipeSync(gF3dDisplayListPtr++);
        gDPSetCycleType(gF3dDisplayListPtr++, G_CYC_FILL);
        gDPSetFillColor(gF3dDisplayListPtr++, (GPACK_RGBA5551(sFogColorR, sFogColorG, sFogColorB, 1) << 16) |
                                                  GPACK_RGBA5551(sFogColorR, sFogColorG, sFogColorB, 1));
        gDPFillRectangle(gF3dDisplayListPtr++, 0, x_16201079, x_c84980f9 - 1, x_16201079 + t3 - 1);
        gDPPipeSync(gF3dDisplayListPtr++);
        gDPSetCycleType(gF3dDisplayListPtr++, G_CYC_COPY);
    }
}

void scroll_debug_iter(SpriteDef *x_cc1d0de5) {
    u32 i, j;
    s32 pad[2];
    u32 x_4346f5cb;
    SpriteFrame *sprite;
    s32 x_5b30c492;

    wad_debug_loop();
    sprite = x_cc1d0de5->sprites;
    x_5b30c492 = x_cc1d0de5->count;
    for (i = 0; i < x_5b30c492; i++, sprite++) {
        for (j = 0; j < x_4346f5cb; j++) {}
    }
    if (sprite) {}
}

#ifdef NON_MATCHING
void sprite_draw(Object *obj) {
    SpriteFrame *v1;
    u8 *pad;
    s32 width;
    x_23e34e3e *part;
    u32 i;
    s32 x_fa21689f;
    s32 pad2;
    u32 x_4760dd99;
    u32 uls;
    s32 lrs;
    s32 ult;
    s32 x;
    s32 y;
    s32 x_0cb35e25;
    s32 x_5ded428c;
    s32 lrt;
    u8 *x_925c481a;
    u16 *palette;
    u32 x_0dbe0778;
    SpriteDef *x_904eaf67;
    Gfx **x_bde24317;

    x_904eaf67 = obj->x_904eaf67;
    v1 = &x_904eaf67->sprites[obj->frameCounter];

    x_925c481a = v1->texture->data;
    part = v1->parts;
    x_fa21689f = v1->partCount;
    width = v1->texture->width;
    palette = (u16 *) (v1->texture->data + width * v1->texture->height);

    if (obj->flags & x_5a44854c) {
        x_bde24317 = &gF3dExtraListPtr;
        gGfxFlags |= GFX_EXTRA_DL;
    } else {
        x_bde24317 = &gOverlayDlPtr;
    }
    gDPLoadTLUT_pal256((*x_bde24317)++, x_c485761a(palette));

    task_execute(obj);

    if (obj->flags & x_c537cafa) {
        return;
    }

    for (i = 0; i < x_fa21689f; i++) {
        ult = part->x_a2264414;
        uls = part->x_b88b3756;
        lrs = part->rightS;
        lrt = part->x_f2864eba;
        x = obj->pos.x + part->x_e7f1952a;
        y = obj->pos.y + part->x_67347149;

        x_0cb35e25 = lrs - uls + 1;
        x_5ded428c = lrt - ult;

        if (x < 0) {
            x = 0;
        }
        if (y < 0) {
            y = 0;
        }
        if (x + x_0cb35e25 > x_c84980f9) {
            x_0cb35e25 = x_c84980f9 - x;
        }
        if (y + x_5ded428c > x_a4f5fb93) {
            x_5ded428c = x_a4f5fb93 - y;
        }

        part++;

        x_4760dd99 = 0x800 / (u32) ((x_0cb35e25 + 7) & ~7);

        do {
            x_0dbe0778 = MIN(x_5ded428c, x_4760dd99);
            gDPLoadTextureTile((*x_bde24317)++,            // pkt
                               x_c485761a(x_925c481a),     // timg
                               G_IM_FMT_CI,                // fmt
                               G_IM_SIZ_8b,                // siz
                               width,                      // width
                               0,                          // height
                               uls,                        // uls
                               ult,                        // ult
                               lrs,                        // lrs
                               ult + x_0dbe0778 - 1,       // lrt
                               0,                          // pal
                               G_TX_NOMIRROR | G_TX_CLAMP, // cms
                               G_TX_NOMIRROR | G_TX_CLAMP, // cmt
                               G_TX_NOMASK,                // masks
                               G_TX_NOMASK,                // maskt
                               G_TX_NOLOD,                 // shifts
                               G_TX_NOLOD                  // shiftt
            );

            gSPTextureRectangle((*x_bde24317)++,           // pkt
                                x << 2,                    // xl
                                y << 2,                    // yl
                                (x + x_0cb35e25 - 2) << 2, // xh
                                (y + x_0dbe0778 - 1) << 2, // yh
                                G_TX_RENDERTILE,           // tile
                                uls << 5,                  // s
                                ult << 5,                  // t
                                4 << 10,                   // dsdx
                                1 << 10                    // dtdy
            );

            ult += x_0dbe0778;
            y += x_0dbe0778;
            x_5ded428c -= x_0dbe0778;
        } while (x_5ded428c != 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/scroll/sprite_draw.s")
void sprite_draw(Object *);
#endif
