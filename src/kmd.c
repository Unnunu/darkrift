#include "common.h"
#include "string.h"
#include "PR/gt.h"

x_d8e0705d x_fd763f4f = {
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2,
    0x2200,
    { 192, 192, 192, 255 },
    1,
};
x_d8e0705d x_bb5426b0 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_OPA_SURF | G_RM_OPA_SURF2,
    0x2000,
    { 255, 255, 255, 255 },
    1,
};
x_d8e0705d x_fc23f083 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_XLU_SURF | G_RM_XLU_SURF2,
    0,
    { 255, 255, 255, 128 },
    0,
};
x_d8e0705d x_eec8b086 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2,
    0x2000,
    { 192, 192, 192, 255 },
    0,
};
x_d8e0705d D_80049988 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_XLU_SURF | G_RM_XLU_SURF2,
    0x2000,
    { 255, 255, 255, 255 },
    0,
};

void x_09e9cd94(x_13162abc *, u8);

void x_af5b689f(x_c3c252eb *node, x_76f6b32b *x_84ff873b, u32 format) {
    node->x_9d9b2b65 = x_84ff873b->x_9d9b2b65;
    node->x_8a54e96a = x_84ff873b->x_8a54e96a;
    node->vertices = x_84ff873b->x_009cb3fe + (s32) x_84ff873b;
    node->triangles = x_84ff873b->x_3a1206c9 + (s32) x_84ff873b;

    if (format >= x_08e65f0c) {
        node->x_5a8a4e18 = *(s32 *) (x_84ff873b->x_9cc3894f + (s32) x_84ff873b);
    }
}

s32 x_0241ddfa(x_13162abc *x_3bfb7219) {
    s32 sum = 0;
    u32 i;

    for (i = 0; i < x_3bfb7219->x_6dcce206; i++) {
        sum += x_3bfb7219->x_45978ecb[i].x_9d9b2b65;
    }
    return sum;
}

s32 x_8f162ff1(x_13162abc *x_3bfb7219) {
    s32 sum = 0;
    u32 i;

    for (i = 0; i < x_3bfb7219->x_6dcce206; i++) {
        sum += x_3bfb7219->x_45978ecb[i].x_8a54e96a;
    }
    return sum;
}

void x_1b3761fc(s32 x_cc1d0de5) {
}

void x_2fd2846e(x_13162abc *x_3bfb7219, x_36123519 *x_e44b1739) {
    if (x_e44b1739->x_cb2a5131 >= 0) {
        if ((u8) (x_3bfb7219->x_8d36349d == x_7138a497)) {
            x_e44b1739->texture = (s32) x_3bfb7219->header + x_e44b1739->x_cb2a5131;
        } else {
            x_e44b1739->texture = (s32) x_3bfb7219->header +
                                  x_3bfb7219->header->offsets[x_3bfb7219->x_6dcce206 + x_e44b1739->x_cb2a5131 + 1];
        }
    } else {
        x_e44b1739->texture = NULL;
    }
}

void anim_buffer_relocate(x_13162abc *x_3bfb7219) {
    x_291fbc91 *header;
    s32 x_2caca85b;
    u32 i;
    x_c3c252eb *node;
    s32 x_5a8a4e18;
    u32 j;

    header = (x_291fbc91 *) sDmaSlots[x_3bfb7219->x_7d9f29c8].data;
    x_3bfb7219->x_45978ecb =
        (x_c3c252eb *) ((s32) x_3bfb7219 + sizeof(x_13162abc) + x_3bfb7219->x_6dcce206 * sizeof(x_36123519));
    x_3bfb7219->header = header;

    if (!((u8) (x_3bfb7219->x_8d36349d == x_7138a497))) {
        x_2caca85b = header->offsets[x_3bfb7219->x_6dcce206];
    }
    x_3bfb7219->x_2caca85b = x_2caca85b;

    for (i = 0; i < x_3bfb7219->x_6dcce206; i++) {
        node = x_3bfb7219->x_45978ecb + i;
        x_af5b689f(node, (x_76f6b32b *) ((s32) header + header->offsets[i]), x_3bfb7219->x_8d36349d);
        if ((u8) (x_3bfb7219->x_8d36349d == x_7138a497)) {
            node->x_063bc6a1 = &x_3bfb7219->x_8e7d60e8[i];
        } else {
            node->x_063bc6a1 =
                (x_36123519 *) ((s32) header + header->offsets[x_3bfb7219->x_6dcce206 + x_2caca85b + i + 2]);
        }

        x_5a8a4e18 = node->x_5a8a4e18;
        for (j = 0; j < x_5a8a4e18; j++) {
            x_2fd2846e(x_3bfb7219, &node->x_063bc6a1[j]);
        }
    }

    if (!((u8) (x_3bfb7219->x_8d36349d == x_7138a497))) {
        x_3bfb7219->x_1dbd7f4a =
            (s32) header + header->offsets[x_3bfb7219->x_6dcce206 + x_2caca85b + x_3bfb7219->x_6dcce206 + 2];
        x_3bfb7219->x_d38574ae =
            (s32) header + header->offsets[x_3bfb7219->x_6dcce206 + x_2caca85b + x_3bfb7219->x_6dcce206 + 3];
    }

    if ((u8) (x_3bfb7219->x_8d36349d == x_7138a497)) {
        if (header->offsets[2 * x_3bfb7219->x_6dcce206] != -1) {
            x_3bfb7219->x_e7962160 = (s32) header + header->offsets[2 * x_3bfb7219->x_6dcce206];
        } else {
            x_3bfb7219->x_e7962160 = NULL;
        }
    } else {
        if (header->offsets[x_3bfb7219->x_6dcce206 + x_3bfb7219->x_2caca85b + 1] != -1) {
            x_3bfb7219->x_e7962160 =
                (s32) header + header->offsets[x_3bfb7219->x_6dcce206 + x_3bfb7219->x_2caca85b + 1];
        } else {
            x_3bfb7219->x_e7962160 = NULL;
        }
    }
}

void x_1bb1665c(x_13162abc *x_3bfb7219, x_291fbc91 *header) {
    u32 i;
    s32 x_9d9b2b65, x_8a54e96a;

    x_3bfb7219->x_45978ecb =
        (x_c3c252eb *) ((s32) x_3bfb7219 + sizeof(x_13162abc) + x_3bfb7219->x_6dcce206 * sizeof(x_36123519));

    for (i = 0; i < x_3bfb7219->x_6dcce206; i++) {
        x_c3c252eb *node = x_3bfb7219->x_45978ecb + i;
        node->x_5a8a4e18 = 1;

        x_9d9b2b65 = ((x_76f6b32b *) ((s32) header + header->offsets[i]))->x_9d9b2b65;
        x_8a54e96a = ((x_76f6b32b *) ((s32) header + header->offsets[i]))->x_8a54e96a;

        x_3bfb7219->x_8e7d60e8[i].x_cb2a5131 = header->offsets[x_3bfb7219->x_6dcce206 + i];
        x_3bfb7219->x_8e7d60e8[i].x_5ab6332d = 0;
        x_3bfb7219->x_8e7d60e8[i].x_146f3cd6 = 0;
        x_3bfb7219->x_8e7d60e8[i].x_9d9b2b65 = x_9d9b2b65;
        x_3bfb7219->x_8e7d60e8[i].x_8a54e96a = x_8a54e96a;
    }
}

void anim_buffer_resolve(x_13162abc *x_3bfb7219, s32 x_7d9f29c8) {
    x_291fbc91 *x_0fc71c4e;

    x_3bfb7219->x_7d9f29c8 = x_7d9f29c8;
    x_0fc71c4e = sDmaSlots[x_7d9f29c8].data;
    x_09e9cd94(x_3bfb7219, x_0fc71c4e->x_1a2fc26d[0]);

    if ((u8) (x_3bfb7219->x_8d36349d == x_7138a497)) {
        x_1bb1665c(x_3bfb7219, x_0fc71c4e);
    }

    anim_buffer_relocate(x_3bfb7219);
}

void x_09e9cd94(x_13162abc *x_3bfb7219, u8 x_78066990) {
    switch (x_78066990) {
        case '@':
            x_3bfb7219->x_8d36349d = x_7138a497;
            break;
        case '2':
            x_3bfb7219->x_8d36349d = x_08e65f0c;
            break;
    }
}

void x_ced731f1(s32 *x_50f1dbff, s32 *x_2d9bafcb, void *x_3b9aa142) {
    s32 i;
    u32 size = (u32) x_3b9aa142;
    s32 delta = (u32) x_50f1dbff - (u32) x_2d9bafcb;

    for (i = 0; i < size; i++) {
        x_50f1dbff[i] += delta;
    }
}

void x_0dfb8a26(x_82e80914 *x_cc1d0de5, s32 x_84ff873b) {
    x_c3c252eb *v0 = &x_cc1d0de5->model.x_3bfb7219->x_45978ecb[x_84ff873b];
    u32 x_fa21689f = v0->x_5a8a4e18;
    u32 x_9d9b2b65 = v0->x_9d9b2b65;
    u32 x_1256da71 = v0->x_8a54e96a;
    s32 size;

    size = x_fa21689f * sizeof(Gfx) * 21 + (x_9d9b2b65 / 8) * sizeof(Gfx) + x_1256da71 * sizeof(Gfx); // TODO constant
    x_cc1d0de5->model.x_bde24317[x_84ff873b] = mem_alloc_debug(size, "kmd.c", 297);
    x_cc1d0de5->x_2640873a = size;
}

s32 x_fab6b1db(u16 *x_982aca1c, u32 x_a77898a9, s32 x_8a54e96a) {
    u32 i;

    for (i = 0; i < x_8a54e96a * 3; i++) {
        if (x_a77898a9 > x_982aca1c[i]) {
            x_a77898a9 = x_982aca1c[i];
        }
        if (x_982aca1c[i] * 0) {} // @fake
    }

    return x_a77898a9;
}

void x_7997e274(x_61d6ae0d *x_cc1d0de5, u32 x_84ff873b, u32 x_2092f891, s32 *x_ee71e5cb, s32 *x_a0e63e9c) {
    u32 v0;

    *x_ee71e5cb = *x_a0e63e9c = 0;
    v0 = x_84ff873b;

    while (x_2092f891) {
        if (x_cc1d0de5->vi[0] > x_84ff873b + 15 || x_cc1d0de5->vi[1] > x_84ff873b + 15 ||
            x_cc1d0de5->vi[2] > x_84ff873b + 15) {
            break;
        }
        if (v0 < x_cc1d0de5->vi[0]) {
            v0 = x_cc1d0de5->vi[0];
        }
        if (v0 < x_cc1d0de5->vi[1]) {
            v0 = x_cc1d0de5->vi[1];
        }
        if (v0 < x_cc1d0de5->vi[2]) {
            v0 = x_cc1d0de5->vi[2];
        }

        x_2092f891--;
        x_cc1d0de5++;
        (*x_ee71e5cb)++;
    }

    *x_a0e63e9c = v0 - x_84ff873b + 1;
}

void x_4126a1e6(Model *model, s32 x_7b79be4b, u8 x_6363ad21, x_d8e0705d *x_028ab561) {
    u32 x_a1c9c44b;
    s32 x_3e1f0641;
    x_562d2a02 *triangle;
    u32 x_fa21689f;
    Gfx *gfx;
    s32 x_17f3af4d;
    s32 x_746b0863;
    s32 x_f74d0791;
    s32 x_a3bc0d9d;
    s32 x_8a54e96a;
    x_c1cedf06 *x_d6eac39a;
    u8 x_2401efb1;
    u8 x_6db2862c;
    s32 v02;
    x_61d6ae0d *triangles;
    s32 padding[4];
    Vtx *vertices;
    Vtx *a11;
    s32 x_09c4f96c;
    s32 x_5ab6332d;
    x_61d6ae0d *x_9380a502;
    s32 size;
    x_562d2a02 *x_5aeb5894[100];
    s32 x_3016b79d[100];
    s32 x_2c95097b[100];
    u32 x_5a8a4e18;
    Vtx *x_ea5456e4[100];
    s32 x_90fe6b5a;
    u32 i;
    x_36123519 *x_c2df68e4;
    x_3b6b80ec *x_a0b04eac;
    s32 x_35a8bfd5[100];
    x_320b5d80 *x_2e8898dd;
    s32 x_b8a119a1[2];
    u8 *x_400cba8a;
    u8 *x_568d4efe;
    x_c3c252eb *node;

    x_2401efb1 = FALSE;
    x_6db2862c = FALSE;
    x_5a8a4e18 = 0;

    node = &model->x_3bfb7219->x_45978ecb[x_7b79be4b];
    x_fa21689f = node->x_5a8a4e18;
    x_3e1f0641 = node->x_9d9b2b65;
    vertices = node->vertices;
    triangles = node->triangles;

    if (model->x_1d24de6a) {
        for (i = 0; i < x_3e1f0641; i++) {
            vertices[i].v.tc[0] >>= 1;
            vertices[i].v.tc[1] >>= 1;
        }
    }

    for (x_a1c9c44b = 0; x_a1c9c44b < x_fa21689f; x_a1c9c44b++) {
        x_c2df68e4 = node->x_063bc6a1 + x_a1c9c44b;
        x_8a54e96a = x_c2df68e4->x_8a54e96a;
        x_5ab6332d = x_c2df68e4->x_5ab6332d;
        x_3e1f0641 = x_c2df68e4->x_9d9b2b65;
        x_9380a502 = triangles;
        x_9380a502 += x_c2df68e4->x_146f3cd6;

        x_35a8bfd5[x_a1c9c44b] = x_5a8a4e18;

        if (x_3e1f0641 <= 16U) {
            triangle = x_5aeb5894[x_5a8a4e18] = mem_alloc_debug(x_8a54e96a * sizeof(x_562d2a02), "kmd.c", 421);
            for (i = 0; i < x_8a54e96a; x_9380a502++, i++) {
                triangle[i].x_091f00cd = x_9380a502->vi[0] - x_5ab6332d;
                triangle[i].x_83f352dd = x_9380a502->vi[1] - x_5ab6332d;
                triangle[i].x_6bf9e1d5 = x_9380a502->vi[2] - x_5ab6332d;
                triangle[i].d = 0;
            }
            x_3016b79d[x_5a8a4e18] = x_8a54e96a;
            x_ea5456e4[x_5a8a4e18] = vertices;
            x_ea5456e4[x_5a8a4e18] += x_5ab6332d;
            x_2c95097b[x_5a8a4e18] = x_3e1f0641;
            x_5a8a4e18++;
        } else {
            do {
                x_5ab6332d = x_fab6b1db(x_9380a502, x_5ab6332d, x_8a54e96a);
                x_ea5456e4[x_5a8a4e18] = vertices;
                x_ea5456e4[x_5a8a4e18] += x_5ab6332d;
                x_7997e274(x_9380a502, x_5ab6332d, x_8a54e96a, &x_a3bc0d9d, &x_f74d0791);
                x_8a54e96a -= x_a3bc0d9d;
                x_3016b79d[x_5a8a4e18] = x_a3bc0d9d;
                x_2c95097b[x_5a8a4e18] = x_f74d0791;
                triangle = x_5aeb5894[x_5a8a4e18] = mem_alloc_debug(x_a3bc0d9d * sizeof(x_562d2a02), "kmd.c", 449);
                x_5a8a4e18++;

                for (i = 0; i < x_a3bc0d9d; i++, x_9380a502++) {
                    triangle[i].x_091f00cd = x_9380a502->vi[0] - x_5ab6332d;
                    triangle[i].x_83f352dd = x_9380a502->vi[1] - x_5ab6332d;
                    triangle[i].x_6bf9e1d5 = x_9380a502->vi[2] - x_5ab6332d;
                    triangle[i].d = 0;
                }
                x_5ab6332d += x_f74d0791;
            } while (x_8a54e96a != 0);
        }
    }

    x_2e8898dd = model->x_467629e6[x_7b79be4b] =
        (x_320b5d80 *) mem_alloc_debug(x_5a8a4e18 * sizeof(x_320b5d80), "kmd.c", 469);
    x_d6eac39a = model->x_d6eac39a[x_7b79be4b] =
        (x_c1cedf06 *) mem_alloc_debug(x_5a8a4e18 * sizeof(x_c1cedf06), "kmd.c", 470);

    for (i = 0; i < x_5a8a4e18; i++) {
        x_2e8898dd[i].context = NULL;
        x_2e8898dd[i].vertices = x_ea5456e4[i];
        x_2e8898dd[i].triangles = x_5aeb5894[i];
        x_90fe6b5a += x_3016b79d[i] * 4; // ??
        x_2e8898dd[i].info = x_d6eac39a + i;

        mem_set(x_d6eac39a + i, 0, sizeof(x_c1cedf06));
        (x_d6eac39a + i)->header.x_09cf7a45 = x_028ab561->x_09cf7a45;
        (x_d6eac39a + i)->header.x_1256da71 = 0;
        (x_d6eac39a + i)->header.x_4c5e05f8 = x_2c95097b[i];
        (x_d6eac39a + i)->header.x_ed66866b = 0;
        (x_d6eac39a + i)->header.x_8a54e96a = x_3016b79d[i];
        (x_d6eac39a + i)->header.x_70b508ea = (i != 0) ? 1 : 0;
        (x_d6eac39a + i)->header.x_b7ba6d35 = NULL;
        gtStateSetOthermode(&(x_d6eac39a + i)->header.otherMode, GT_RENDERMODE, x_028ab561->x_e5c5ede4);
        gtStateSetOthermode(&(x_d6eac39a + i)->header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
        gtStateSetOthermode(&(x_d6eac39a + i)->header.otherMode, GT_TEXTFILT, G_TF_BILERP);
        gtStateSetOthermode(&(x_d6eac39a + i)->header.otherMode, GT_TEXTCONV, G_TC_FILT);
        gtStateSetOthermode(&(x_d6eac39a + i)->header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
        gtStateSetOthermode(&(x_d6eac39a + i)->header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
        gtStateSetOthermode(&(x_d6eac39a + i)->header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);
    }
    model->x_c246f31f[x_7b79be4b] = x_5a8a4e18;

    size = 22 * sizeof(Gfx) * x_fa21689f; // TODO: make constant
    gfx = (Gfx *) mem_alloc_debug(size, "kmd.c", 501);
    mem_set(gfx, 0, size);
    for (x_a1c9c44b = 0; x_a1c9c44b < x_fa21689f; x_a1c9c44b++) {
        x_c2df68e4 = node->x_063bc6a1 + x_a1c9c44b;
        x_746b0863 = x_35a8bfd5[x_a1c9c44b];
        x_17f3af4d = (x_a1c9c44b + 1 < x_fa21689f) ? x_35a8bfd5[x_a1c9c44b + 1] : x_5a8a4e18;

        x_2e8898dd[x_746b0863].info->header.x_b7ba6d35 = gfx;
        if (x_a1c9c44b == 0 && !(x_028ab561->flags & 1)) {
            gDPSetPrimColor(gfx++, 0, 0, x_028ab561->primColor.r, x_028ab561->primColor.g, x_028ab561->primColor.b,
                            x_028ab561->primColor.a);
        }
        if (!x_2401efb1 && !((u8) (x_c2df68e4->x_cb2a5131 >= 0))) {
            gDPPipeSync(gfx++);
            gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
            x_2401efb1 = TRUE;
            x_6db2862c = FALSE;
        } else if (!x_6db2862c && (u8) (x_c2df68e4->x_cb2a5131 >= 0)) {
            gDPPipeSync(gfx++);
            gfx->words.w0 = x_028ab561->x_25501148.words.w0;
            gfx->words.w1 = x_028ab561->x_25501148.words.w1;
            gfx++;
            x_2401efb1 = FALSE;
            x_6db2862c = TRUE;
        }

        if (x_6db2862c) {
            for (i = x_746b0863; i < x_17f3af4d; i++) {
                x_2e8898dd[i].info->header.x_09cf7a45 |= G_RDP_TRI_TXTR_MASK;
            }

            x_3e1f0641 = x_c2df68e4->x_9d9b2b65;
            a11 = vertices;
            a11 += x_c2df68e4->x_5ab6332d;
            for (i = 0; i < x_3e1f0641; i++) {
                a11[i].v.cn[0] = a11[i].v.cn[1] = a11[i].v.cn[2] = 255;
            }

            x_a0b04eac = x_c2df68e4->texture;
            if (x_a0b04eac->format == 4) {
                if (!x_6363ad21) {
                    x_400cba8a = model->x_3bfb7219->x_1dbd7f4a + x_a0b04eac->x_3f981ea3 * 0x20;
                    x_400cba8a[1] &= ~1;
                    gDPLoadTLUT_pal16(gfx++, 0, x_c485761a(x_400cba8a));
                }
                gDPLoadTextureBlock_4b(gfx++, x_a0b04eac->data, G_IM_FMT_CI, x_a0b04eac->width, x_a0b04eac->height, 0,
                                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                if (!x_6363ad21) {
                    x_568d4efe = model->x_3bfb7219->x_d38574ae + x_a0b04eac->x_3f981ea3 * 0x200;
                    x_568d4efe[1] &= ~1;
                    gDPLoadTLUT_pal256(gfx++, x_c485761a(x_568d4efe));
                }
                gDPLoadTextureBlock(gfx++, x_a0b04eac->data, G_IM_FMT_CI, G_IM_SIZ_8b, x_a0b04eac->width,
                                    x_a0b04eac->height, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            }
        }
        gSPNoOp(gfx++);
    }
}

void x_2ff3b46b(x_82e80914 *x_cc1d0de5, s32 x_84ff873b, u8 x_2092f891) {
    u32 x_959ea381;
    Vtx *fp;
    Vtx *s7;
    s32 x_b51df1e3;
    x_61d6ae0d *s1;
    Gfx *s3;
    u32 s0;
    s32 x_148a0a2d;
    u32 x_39da5279;
    x_36123519 *a1;
    s32 s2;
    u8 x_953efa58;
    u8 x_a77fc173;
    s32 s6;
    x_61d6ae0d *x_4fc490a9;
    s32 t3;
    x_3b6b80ec *a2;
    u8 *x_400cba8a;
    u8 *x_568d4efe;
    s32 padding[3];
    u16 *x_56639221;
    u16 *x_b0cfd471;
    x_c3c252eb *v0;

    x_953efa58 = FALSE;
    x_a77fc173 = FALSE;
    s3 = x_cc1d0de5->model.x_bde24317[x_84ff873b];
    v0 = &x_cc1d0de5->model.x_3bfb7219->x_45978ecb[x_84ff873b];
    x_b51df1e3 = v0->x_5a8a4e18;
    fp = v0->vertices;
    x_4fc490a9 = v0->triangles;

    for (x_959ea381 = 0; x_959ea381 < x_b51df1e3; x_959ea381++) {
        a1 = &v0->x_063bc6a1[x_959ea381];

        s6 = a1->x_8a54e96a;
        t3 = a1->x_9d9b2b65;
        s1 = x_4fc490a9;
        s1 += a1->x_146f3cd6;

        s2 = a1->x_5ab6332d;
        s7 = fp;
        s7 += a1->x_5ab6332d;

        if (!x_953efa58 && !((u8) (a1->x_cb2a5131 >= 0))) {
            gDPPipeSync(s3++);
            gSPTexture(s3++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
            gDPSetCombineMode(s3++, G_CC_SHADE, G_CC_SHADE);
            x_953efa58 = TRUE;
            x_a77fc173 = FALSE;
        } else if (!x_a77fc173 && ((u8) (a1->x_cb2a5131 >= 0))) {
            gDPPipeSync(s3++);
            gSPTexture(s3++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
            gDPSetCombineMode(s3++, G_CC_DECALRGB, G_CC_DECALRGB);
            x_a77fc173 = TRUE;
            x_953efa58 = FALSE;
        }

        if (x_a77fc173) {
            a2 = a1->texture;
            if (a2->format == 4) {
                if (!x_2092f891) {
                    x_400cba8a = x_cc1d0de5->model.x_3bfb7219->x_1dbd7f4a + a2->x_3f981ea3 * 0x20;
                    gDPLoadTLUT_pal16(s3++, 0, x_c485761a(x_400cba8a));
                }
                gDPLoadTextureBlock_4b(s3++, a2->data, G_IM_FMT_CI, a2->width, a2->height, 0,
                                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                if (!x_2092f891) {
                    x_568d4efe = x_cc1d0de5->model.x_3bfb7219->x_d38574ae + a2->x_3f981ea3 * 0x200;
                    gDPLoadTLUT_pal256(s3++, x_c485761a(x_568d4efe));
                }
                gDPLoadTextureBlock(s3++, a2->data, G_IM_FMT_CI, G_IM_SIZ_8b, a2->width, a2->height, 0,
                                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
            }
        }

        if (t3 <= 0x10U) {

            gSPVertex(s3++, s7, t3, 0);
            for (s0 = 0; s0 < s6; s0++) {
                gSP1Triangle(s3++, s1->vi[0] - s2, s1->vi[1] - s2, s1->vi[2] - s2, 0);
                s1++;
            }
        } else {
            do {
                s2 = x_fab6b1db(s1, s2, s6);
                s7 = fp;
                s7 += s2;
                x_7997e274(s1, s2, s6, &x_39da5279, &x_148a0a2d);
                gSPVertex(s3++, s7, x_148a0a2d, 0);
                s6 -= x_39da5279;
                for (s0 = 0; s0 < x_39da5279; s0++) {
                    gSP1Triangle(s3++, s1->vi[0] - s2, s1->vi[1] - s2, s1->vi[2] - s2, 0);
                    s1++;
                }
                s2 += x_148a0a2d;
            } while (s6 != 0);
        }
    }

    gSPEndDisplayList(s3++);
}

void model_scaffold_register(x_82e80914 *x_cc1d0de5, x_13162abc *x_84ff873b, char *name, u8 x_ee71e5cb,
                             s32 x_a0e63e9c) {
    u32 i;
    x_80d298c9 *x_d59386e0;
    char x_c9614940[16];
    s32 v0;

    x_cc1d0de5->model.x_3bfb7219 = x_84ff873b;
    x_cc1d0de5->model.x_6dcce206 = x_84ff873b->x_6dcce206;

    for (i = 0; i < x_cc1d0de5->model.x_6dcce206; i++) {
        x_0dfb8a26(x_cc1d0de5, i);
        x_2ff3b46b(x_cc1d0de5, i, x_ee71e5cb);
    }

    x_cc1d0de5->model.x_e7962160 = v0 = x_cc1d0de5->model.x_3bfb7219->x_e7962160;

    if (v0 != 0) {
        wad_strcpy(x_c9614940, name);
        x_c9614940[3] = '\0';
        wad_strcat(x_c9614940, "_anm.anm");
        x_d59386e0 = &sWadEntries[wad_entry_find(x_c9614940, x_a0e63e9c)];
        x_cc1d0de5->model.x_50771dcd = sDmaSlots[x_d59386e0->x_d5b87ce9].data;
        x_cc1d0de5->model.x_c4306fe5 = x_d59386e0->x_4962fc73;
        mem_dma_set_callback(x_d59386e0->x_d5b87ce9, x_ced731f1, x_cc1d0de5->model.x_c4306fe5);
    } else {
        x_cc1d0de5->model.x_50771dcd = NULL;
    }
}

s32 x_f2461a47(Model *model, s32 x_906a6dc7, s16 *x_c941fcac) {
    x_c3c252eb *node;
    s32 x_44140223;
    u32 i;
    u32 j;
    u32 x_3ec0209e;
    Vtx *x_abd59dde;
    x_81d7569b *x_5b386c41;
    s16 x_adb12607;

    x_44140223 = 0;
    node = &model->x_3bfb7219->x_45978ecb[x_906a6dc7];
    x_3ec0209e = node->x_9d9b2b65;

    for (i = 0; i < x_3ec0209e; i++) {
        x_c941fcac[i] = i;
    }

    x_abd59dde = node->vertices;

    for (i = 0; i < x_3ec0209e - 1; i++) {
        if (x_c941fcac[i] == i) {
            x_44140223++;
            for (j = 1; j < x_3ec0209e; j++) {
                if (x_abd59dde[i].v.ob[0] == x_abd59dde[j].v.ob[0] && x_abd59dde[i].v.ob[1] == x_abd59dde[j].v.ob[1] &&
                    x_abd59dde[i].v.ob[2] == x_abd59dde[j].v.ob[2]) {
                    x_c941fcac[j] = x_44140223 - 1;
                }
            }
        }
    }

    x_5b386c41 = mem_alloc_debug(x_44140223 * sizeof(x_81d7569b), "kmd.c", 761);
    model->x_5b386c41[x_906a6dc7] = x_5b386c41;
    model->x_810b9a68[x_906a6dc7] = x_44140223;

    for (i = 0; i < x_44140223; i++) {
        x_adb12607 = 0;
        for (j = 0; j < x_3ec0209e; j++) {
            if (x_c941fcac[j] == i) {
                x_5b386c41[i].x_b21a405e[x_adb12607].r = x_abd59dde[j].v.cn[0];
                x_5b386c41[i].x_b21a405e[x_adb12607].g = x_abd59dde[j].v.cn[1];
                x_5b386c41[i].x_b21a405e[x_adb12607].b = x_abd59dde[j].v.cn[2];
                x_5b386c41[i].x_d0dadb00[x_adb12607++] = j;
                x_5b386c41[i].x_d0dadb00[x_adb12607] = -1;
            }
        }
    }

    return x_44140223;
}

void x_84fb7400(f32 *x_cc1d0de5) {
    f32 x_f8685538;

    x_f8685538 = sqrtf(x_84ce1cfb(x_cc1d0de5[0]) + x_84ce1cfb(x_cc1d0de5[1]) + x_84ce1cfb(x_cc1d0de5[2]));
    if (x_f8685538 != 0.0f) {
        x_cc1d0de5[0] /= x_f8685538;
        x_cc1d0de5[1] /= x_f8685538;
        x_cc1d0de5[2] /= x_f8685538;
    } else {
        x_cc1d0de5[0] = x_cc1d0de5[2] = 0.0f;
        x_cc1d0de5[1] = -1.0f;
    }
}

s32 x_1d609ba6(u32 x_cc1d0de5, u32 x_84ff873b, u16 *x_2092f891, x_625bda2c *x_ee71e5cb, u32 x_a0e63e9c,
               u16 *x_1011f751) {
    u32 i;
    s32 j;
    x_625bda2c *x_c9bcbd0a = &x_ee71e5cb[x_84ff873b];

    x_2092f891 += 3 * x_84ff873b + 3;
    for (i = x_84ff873b + 1; i < x_a0e63e9c; i++, x_2092f891 += 3) {
        for (j = 0; j < 3; j++) {
            if (x_cc1d0de5 == x_1011f751[x_2092f891[j]]) {
                if (x_c9bcbd0a->x == x_ee71e5cb[i].x && x_c9bcbd0a->y == x_ee71e5cb[i].y &&
                    x_c9bcbd0a->z == x_ee71e5cb[i].z) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

void model_anim_setup(Model *model) {
    u32 i;
    u32 x_adb12607;
    u32 s0;
    u32 s1;
    x_c3c252eb *node;
    Vtx *vertices;
    x_61d6ae0d *triangles;
    u16 j;
    u16 k;
    u16 l;
    x_acccb624 *x_1f43ddc1;
    x_81d7569b *x_705ea89d;
    x_625bda2c *x_ef3c3ef7;
    x_625bda2c *x_c4ba5114;
    s32 x_b8a119a1[2];
    x_625bda2c *x_21d228f6;
    f32 x, y, z;
    s16 x_44140223;
    s16 *x_74b56be1;
    x_acccb624 x_4a496b1d;
    s32 x_09c4f96c;
    u16 x_f4703079;
    s16 temp;
    f32 fv0;
    Vtx *v0;
    Vtx *v1;
    Vtx *a1;
    f32 x_78ae8cac[3];

    s0 = 0;
    s1 = 0;
    for (i = 0; i < model->x_6dcce206; i++) {
        node = &model->x_3bfb7219->x_45978ecb[i];
        if (s0 < node->x_9d9b2b65) {
            s0 = node->x_9d9b2b65;
        }
        if (s1 < node->x_8a54e96a) {
            s1 = node->x_8a54e96a;
        }
    }

    x_ef3c3ef7 = mem_alloc_debug(s0 * 12, "kmd.c", 854);
    x_c4ba5114 = mem_alloc_debug(s1 * 12, "kmd.c", 855);
    x_74b56be1 = mem_alloc_debug(s0 * 2, "kmd.c", 856);
    mem_set(x_ef3c3ef7, 0, s0 * 12);
    mem_set(x_c4ba5114, 0, s1 * 12);

    for (i = 0; i < model->x_6dcce206; i++) {
        x_44140223 = x_f2461a47(model, i, x_74b56be1);
        node = &model->x_3bfb7219->x_45978ecb[i];
        x_f4703079 = node->x_8a54e96a;
        vertices = node->vertices;
        triangles = node->triangles;

        for (j = 0; j < x_f4703079; j++, triangles++) {
            a1 = vertices;
            a1 += triangles->vi[0];
            v0 = vertices;
            v0 += triangles->vi[1];
            v1 = vertices;
            v1 += triangles->vi[2];

            x_78ae8cac[0] = a1->v.ob[1] * (v0->v.ob[2] - v1->v.ob[2]) + v0->v.ob[1] * (v1->v.ob[2] - a1->v.ob[2]) +
                            v1->v.ob[1] * (a1->v.ob[2] - v0->v.ob[2]);
            x_78ae8cac[1] = a1->v.ob[2] * (v0->v.ob[0] - v1->v.ob[0]) + v0->v.ob[2] * (v1->v.ob[0] - a1->v.ob[0]) +
                            v1->v.ob[2] * (a1->v.ob[0] - v0->v.ob[0]);
            x_78ae8cac[2] = a1->v.ob[0] * (v0->v.ob[1] - v1->v.ob[1]) + v0->v.ob[0] * (v1->v.ob[1] - a1->v.ob[1]) +
                            v1->v.ob[0] * (a1->v.ob[1] - v0->v.ob[1]);
            x_84fb7400(x_78ae8cac);
            x_c4ba5114[j].x = x_78ae8cac[0];
            x_c4ba5114[j].y = x_78ae8cac[1];
            x_c4ba5114[j].z = x_78ae8cac[2];
        }

        for (k = 0; k < x_44140223; k++) {
            triangles = node->triangles;
            for (j = 0; j < x_f4703079; j++, triangles++) {
                x_21d228f6 = x_c4ba5114;
                x_21d228f6 += j;
                for (l = 0; l < 3; l++) {
                    if (k == x_74b56be1[triangles->vi[l]] &&
                        x_1d609ba6(k, j, node->triangles, x_c4ba5114, x_f4703079, x_74b56be1) == 0) {
                        x_ef3c3ef7[k].x += x_21d228f6->x;
                        x_ef3c3ef7[k].y += x_21d228f6->y;
                        x_ef3c3ef7[k].z += x_21d228f6->z;
                    }
                }
            }
        }

        x_705ea89d = model->x_5b386c41[i];
        x_1f43ddc1 = &x_4a496b1d;
        for (x_adb12607 = 0; x_adb12607 < x_44140223; x_adb12607++) {
            x = x_ef3c3ef7[x_adb12607].x;
            y = x_ef3c3ef7[x_adb12607].y;
            z = x_ef3c3ef7[x_adb12607].z;
            fv0 = sqrtf(x_84ce1cfb(x) + x_84ce1cfb(y) + x_84ce1cfb(z));
            if (fv0 != 0) {
                x_ef3c3ef7[x_adb12607].x /= fv0;
                x_ef3c3ef7[x_adb12607].y /= fv0;
                x_ef3c3ef7[x_adb12607].z /= fv0;
            } else {
                x_ef3c3ef7[x_adb12607].x = x_ef3c3ef7[x_adb12607].y = x_ef3c3ef7[x_adb12607].z = 0.0;
            }

            x_1f43ddc1->x = temp = ROUND(x_ef3c3ef7[x_adb12607].x * 128.0f);
            if (temp > 127) {
                x_1f43ddc1->x = 127;
            }
            x_1f43ddc1->y = temp = ROUND(x_ef3c3ef7[x_adb12607].y * 128.0f);
            if (temp > 127) {
                x_1f43ddc1->y = 127;
            }
            x_1f43ddc1->z = temp = ROUND(x_ef3c3ef7[x_adb12607].z * 128.0f);
            if (temp > 127) {
                x_1f43ddc1->z = 127;
            }

            x_705ea89d[x_adb12607].x_fb9d51cc = x_1f43ddc1->x;
            x_705ea89d[x_adb12607].x_c7f5b137 = x_1f43ddc1->y;
            x_705ea89d[x_adb12607].x_a546469c = x_1f43ddc1->z;
        }
    }

    mem_free(x_ef3c3ef7);
    mem_free(x_c4ba5114);
    mem_free(x_74b56be1);
}

void model_create_from_kmd(Model *model, x_13162abc *x_6d416e72, char *name, u8 x_6363ad21, x_d8e0705d *x_e06fd284,
                           s32 x_010b4265) {
    u32 i;
    s32 x_80737ea7;
    s32 j;
    s32 x_09c4f96c;
    char x_1edacbe7[16];
    char padding[16];

    model->x_3bfb7219 = x_6d416e72;
    model->x_6dcce206 = x_6d416e72->x_6dcce206;
    model->x_1d24de6a = x_6d416e72->x_14bc93c1;
    model->x_5e8d7fdd = 0;
    model->x_70d4cd21 = 0;
    model->x_ca98492d = 0;

    for (i = 0; i < model->x_6dcce206; i++) {
        x_4126a1e6(model, i, x_6363ad21, x_e06fd284);
    }

    if (model->x_3bfb7219->x_e7962160 != NULL) {
        model->x_e7962160 = mem_alloc_debug((model->x_6dcce206 + 1) * sizeof(x_43bd08ed), "kmd.c", 983);
        memcpy(model->x_e7962160, model->x_3bfb7219->x_e7962160, (model->x_6dcce206 + 1) * sizeof(x_43bd08ed));
    } else {
        model->x_e7962160 = NULL;
    }

    wad_strcpy(x_1edacbe7, name);
    for (j = 0; x_1edacbe7[j] != '\0' && j < 16;) {
        if (x_1edacbe7[j++] == '.') {
            x_1edacbe7[j - 1] = '\0';
            break;
        }
    }

    wad_strcat(x_1edacbe7, "_anm.anm");
    x_80737ea7 = wad_entry_find(x_1edacbe7, x_010b4265);

    if (x_80737ea7 < 0) {
        wad_strcpy(x_1edacbe7, name);
        x_1edacbe7[3] = '\0';
        wad_strcat(x_1edacbe7, "_anm.anm");
        x_80737ea7 = wad_entry_find(x_1edacbe7, x_010b4265);
    }

    if (x_80737ea7 >= 0) {
        model->x_50771dcd = sDmaSlots[sWadEntries[x_80737ea7].x_d5b87ce9].data;
        model->x_c4306fe5 = sWadEntries[x_80737ea7].x_4962fc73;
        mem_dma_set_callback(sWadEntries[x_80737ea7].x_d5b87ce9, x_ced731f1, model->x_c4306fe5);
    } else {
        model->x_50771dcd = NULL;
    }
}
