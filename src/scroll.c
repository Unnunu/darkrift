#include "common.h"
#include "task.h"

extern s32 D_8008012C;
extern s32 x_6c647b3a;
extern u8 D_80080129;
extern Gfx *x_9a3c07b8;
extern Gfx *D_8005BFDC;
extern Gfx *x_d8cbce84;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;

x_4a7d6dd4 *x_3b49183f = NULL;
s32 x_e74df613 = 0;
s32 x_6c647b3a = 0;

/* .bss */
s32 D_80081420;
s32 D_80081424;
s32 D_80081428;
s32 D_8008142C;
s32 D_80081430;
s32 D_80081434;
s32 D_80081438;

x_4a7d6dd4 *x_a0e73601(char *x_2b0c3984, s32 x_84ff873b, s32 x_64a8566c, s32 x_afebb108, s32 x_86f38745, s32 flags,
                       s32 x_fb21ca8c) {
    x_4a7d6dd4 *head;
    s32 pad;
    x_3b6b80ec *x_d59386e0;
    x_4a7d6dd4 *x_8dddde0e;
    char x_7244b466[20];

    x_8dddde0e = x_56c3086a(sizeof(x_4a7d6dd4), "scroll.c", 21);

    x_dab0846a(x_7244b466, x_2b0c3984);
    x_8c518b47(x_7244b466, ".tex");

    x_d59386e0 = (x_3b6b80ec *) x_b717ed65[x_e720f37d(x_7244b466, x_fb21ca8c)].data;

    x_8dddde0e->width = x_d59386e0->width;
    x_8dddde0e->height = x_d59386e0->height;
    x_8dddde0e->x_519855f8 = x_d59386e0->format;
    x_8dddde0e->flags = flags;
    x_8dddde0e->x_afebb108 = x_afebb108;
    x_8dddde0e->x_86f38745 = x_86f38745;
    x_8dddde0e->x_08b62e4f = x_84ff873b;
    x_8dddde0e->x_64a8566c = x_64a8566c;
    x_8dddde0e->x_925c481a = x_d59386e0->data;

    if (x_8dddde0e->x_519855f8 == TRUE) {
        x_8dddde0e->palette = x_d59386e0->data + x_8dddde0e->width * x_8dddde0e->height;
    } else {
        x_8dddde0e->palette = NULL;
    }

    head = x_3b49183f;
    x_3b49183f = x_8dddde0e;
    x_8dddde0e->next = head;

    if (!(flags & x_96186256)) {
        s16 temp = x_8dddde0e->x_925c481a[0] * 2;
        x_8dddde0e->palette[temp] = 0;
        x_8dddde0e->palette[temp + 1] = 0;
    }
    if (flags & x_8ce7ef70) {
        D_8008012C |= x_48752861;
    }

    return x_8dddde0e;
}

void x_25025961(x_4a7d6dd4 *x_a0b04eac) {
    x_4a7d6dd4 *it;
    x_4a7d6dd4 *prev;

    it = x_3b49183f;

    if (x_a0b04eac == it) {
        x_3b49183f = x_3b49183f->next;
        x_86715543(x_a0b04eac);
        return;
    }

    while (it != NULL) {
        if (it == x_a0b04eac) {
            prev->next = it->next;
            x_86715543(x_a0b04eac);
            return;
        }
        prev = it;
        it = it->next;
    }
}

void x_fde7a84d(x_4a7d6dd4 *x_8dddde0e, s32 x_ace80dba, s32 x_64a8566c, u32 height, u32 x_c2580ba5, u32 texT) {
    Gfx **x_bde24317;
    s32 x_9dc253a1;
    u8 *image;
    u32 x_9bdb24e2;
    s32 x_54670c5d;
    s32 padding[6];

    image = x_8dddde0e->x_925c481a;
    image += x_ace80dba * x_8dddde0e->width;
    x_9dc253a1 = x_8dddde0e->width;
    x_bde24317 = (x_8dddde0e->flags & x_8ce7ef70) ? &x_d8cbce84 : &x_9a3c07b8;

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

void x_77751af8(void) {
    x_4a7d6dd4 *x_8dddde0e;
    s32 x_c9084644;
    s32 x_16201079;
    s32 x_64a8566c;
    s32 x_ace80dba;
    s32 height;
    s32 x_e97c45db;
    u32 x_c2580ba5;

    x_16201079 = 0;

    for (x_8dddde0e = x_3b49183f; x_8dddde0e != NULL;) {
        if (!(x_8dddde0e->flags & x_607c80f4)) {
            if (!(x_8dddde0e->flags & x_8ce7ef70)) {
                x_c9084644 = ((x_8dddde0e->x_afebb108 * x_e74df613) >> 16) + D_80081428;
            } else {
                x_c9084644 = 0;
            }

            x_e97c45db = (x_8dddde0e->x_86f38745 * x_6c647b3a) >> 16;
            x_e97c45db += x_8dddde0e->x_64a8566c;

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
            x_c2580ba5 = (x_8dddde0e->x_08b62e4f + x_c9084644) % x_8dddde0e->width;
            x_fde7a84d(x_8dddde0e, x_ace80dba, x_64a8566c, height, x_c2580ba5, 0);

            if (!(x_8dddde0e->flags & x_8ce7ef70) && x_16201079 < x_64a8566c + height &&
                x_64a8566c + height < x_84e8ddf2) {
                x_16201079 = x_64a8566c + height;
            }
        }
        x_8dddde0e = x_8dddde0e->next;
    }

    if (x_16201079 > 0 && D_80080129 && !(D_8008012C & x_bbfa9667)) {
        s32 t3 = MIN(64, x_84e8ddf2 - x_16201079);

        gDPPipeSync(x_9a3c07b8++);
        gDPSetCycleType(x_9a3c07b8++, G_CYC_FILL);
        gDPSetFillColor(x_9a3c07b8++, (GPACK_RGBA5551(D_80080130, D_80080132, D_80080134, 1) << 16) |
                                          GPACK_RGBA5551(D_80080130, D_80080132, D_80080134, 1));
        gDPFillRectangle(x_9a3c07b8++, 0, x_16201079, x_c84980f9 - 1, x_16201079 + t3 - 1);
        gDPPipeSync(x_9a3c07b8++);
        gDPSetCycleType(x_9a3c07b8++, G_CYC_COPY);
    }
}

void x_08216b8b(x_8ab35fe5 *x_cc1d0de5) {
    u32 i, j;
    s32 pad[2];
    u32 x_4346f5cb;
    x_7cc7ad58 *sprite;
    s32 x_5b30c492;

    x_33b084c7();
    sprite = x_cc1d0de5->x_a34b89cc;
    x_5b30c492 = x_cc1d0de5->x_5b30c492;
    for (i = 0; i < x_5b30c492; i++, sprite++) {
        for (j = 0; j < x_4346f5cb; j++) {}
    }
    if (sprite) {}
}

#ifdef NON_MATCHING
void x_23e3afdf(Object *obj) {
    x_7cc7ad58 *v1;
    u8 *pad;
    s32 width;
    x_425d6ed3 *part;
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
    x_8ab35fe5 *x_904eaf67;
    Gfx **x_bde24317;

    x_904eaf67 = obj->x_904eaf67;
    v1 = &x_904eaf67->x_a34b89cc[obj->frameCounter];

    x_925c481a = v1->texture->data;
    part = v1->parts;
    x_fa21689f = v1->x_fa21689f;
    width = v1->texture->width;
    palette = (u16 *) (v1->texture->data + width * v1->texture->height);

    if (obj->flags & x_5a44854c) {
        x_bde24317 = &x_d8cbce84;
        D_8008012C |= x_48752861;
    } else {
        x_bde24317 = &D_8005BFDC;
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
#pragma GLOBAL_ASM("asm/nonmatchings/scroll/x_23e3afdf.s")
void x_23e3afdf(Object *);
#endif
