#include "common.h"
#include "task.h"
#include "camera.h"
#include "string.h"
#include "PR/gt.h"

// .data
x_aece7675 sShadowDesc = { "xxxxxxxxx", NULL, 0, 0xF9C, NULL };

// .bss
Mtx sUnusedMatrix;
Gfx **sDisplayList;
s32 sModelUnused;
x_f752bb53 *sSortListHead;
x_a8b4b5ce *sLightListHead;
x_b57dc591 sLightFreeList;
x_3b6b80ec *sFurTextures[16];
u32 sFurTextureCount;

void model_texture_register(x_3b6b80ec *texture) {
    u32 i;

    for (i = 0; i < sFurTextureCount; i++) {
        if (sFurTextures[i] == texture) {
            return;
        }
    }

    sFurTextures[sFurTextureCount++] = texture;
}

s32 texture_shift_full(void *unused) {
    u32 i, j;
    x_3b6b80ec *texture;
    u32 x_70b0b43c;
    u32 x_b16b10e1;
    u32 *x_eb7790f7;
    u32 x_5b96ee3f;

    for (i = 0; i < sFurTextureCount; i++) {
        texture = sFurTextures[i];
        x_70b0b43c = (texture->width * texture->height) / 8;
        x_eb7790f7 = texture->data;
        x_b16b10e1 = ((u32 *) texture->data)[0];

        for (j = 0; j < x_70b0b43c - 1; j++, x_eb7790f7++) {
            *x_eb7790f7 <<= 4;
            x_5b96ee3f = x_eb7790f7[1];
            x_5b96ee3f = (x_5b96ee3f & 0xF0000000) >> 28;
            *x_eb7790f7 |= x_5b96ee3f;
        }

        *x_eb7790f7 <<= 4;
        x_b16b10e1 = (x_b16b10e1 & 0xF0000000) >> 28;
        *x_eb7790f7 |= x_b16b10e1;
    }

    return 1;
}

s32 texture_shift_line(void *unused) {
    u32 i, j, k;
    x_3b6b80ec *v1;
    u32 x_92cb1df0;
    u32 x_021bc5e0;
    u32 *x_eb7790f7;
    u32 x_5b96ee3f;

    if (gFrameCounter & 1) {
        return 1;
    }

    for (i = 0; i < sFurTextureCount; i++) {
        v1 = sFurTextures[i];
        x_92cb1df0 = v1->width / 8;
        x_eb7790f7 = v1->data;

        for (j = 0; j < v1->height; j++) {
            x_021bc5e0 = *x_eb7790f7;
            for (k = 0; k < x_92cb1df0 - 1; k++, x_eb7790f7++) {
                *x_eb7790f7 <<= 4;
                x_5b96ee3f = x_eb7790f7[1];
                x_5b96ee3f = (x_5b96ee3f & 0xF0000000) >> 28;
                *x_eb7790f7 |= x_5b96ee3f;
            }
            *x_eb7790f7 <<= 4;
            x_021bc5e0 = (x_021bc5e0 & 0xF0000000) >> 28;
            *x_eb7790f7 |= x_021bc5e0;
        }
    }

    return 1;
}

void model_texture_reset(void) {
    sFurTextureCount = 0;
}

void model_collect_textures(Object *obj, u8 x_44c2855d) {
    x_6fcfcf46 *x_b802b7b5 = obj->x_20d20338;
    Model *model = x_b802b7b5->model;
    s32 x_6dcce206 = x_b802b7b5->x_6dcce206;
    u32 i, j;
    x_c3c252eb *node;
    s32 x_5a8a4e18;
    x_36123519 *x_e44b1739;

    if (sFurTextureCount == 0) {
        if (x_44c2855d) {
            rsp_register_callback(texture_shift_full, NULL);
        } else {
            rsp_register_callback(texture_shift_line, NULL);
        }
    }

    for (i = 0; i < x_6dcce206; i++) {
        node = &model->x_3bfb7219->x_45978ecb[i];
        x_5a8a4e18 = node->x_5a8a4e18;
        for (j = 0; j < x_5a8a4e18; j++) {
            x_e44b1739 = node->x_063bc6a1 + j;
            if ((u8) (x_e44b1739->x_cb2a5131 >= 0)) {
                model_texture_register(x_e44b1739->texture);
            }
        }
    }

    obj->flags |= x_b6789b80;
}

void model_light_pool_init(void) {
    sLightListHead = NULL;
    pool_init(&sLightFreeList, 5, sizeof(x_a8b4b5ce));
}

void model_light_attach(Object *obj, x_6751d717 *x_84ff873b) {
    x_a8b4b5ce *x_8413ad49;

    if (sLightFreeList.count == 0) {
        return;
    }

    x_8413ad49 = (x_a8b4b5ce *) x_6d619dce(sLightFreeList);
    obj->flags |= x_28b57b50;

    x_8413ad49->next = sLightListHead;
    x_8413ad49->previous = NULL;
    if (sLightListHead != NULL) {
        sLightListHead->previous = x_8413ad49;
    }
    sLightListHead = x_8413ad49;

    x_8413ad49->object = obj;
    x_8413ad49->red = x_84ff873b->r;
    x_8413ad49->green = x_84ff873b->g;
    x_8413ad49->blue = x_84ff873b->b;
    obj->light = x_8413ad49;
}

void model_light_detach(x_a8b4b5ce *x_cc1d0de5) {
    if (x_cc1d0de5->previous != NULL) {
        x_cc1d0de5->previous->next = x_cc1d0de5->next;
    } else {
        sLightListHead = x_cc1d0de5->next;
    }
    if (x_cc1d0de5->next != NULL) {
        x_cc1d0de5->next->previous = x_cc1d0de5->previous;
    }

    x_48825d30(sLightFreeList, x_cc1d0de5);
}

void model_render_mode_zbuf(x_c1cedf06 *x_cc1d0de5, s32 transparent) {
    Gfx *gfx = &x_cc1d0de5->header.otherMode;

    mem_set(gfx, 0, sizeof(Gfx));

    gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2);
    gtStateSetOthermode(gfx, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(gfx, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(gfx, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(gfx, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(gfx, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(gfx, GT_PIPELINE, G_PM_NPRIMITIVE);

    x_cc1d0de5->header.x_09cf7a45 |= G_RDP_TRI_ZBUFF_MASK;
}

void model_render_mode_standard(x_c1cedf06 *x_cc1d0de5, s32 x_3af6d8f2, s32 transparent) {
    Gfx *gfx = &x_cc1d0de5->header.otherMode;

    mem_set(gfx, 0, sizeof(Gfx));
    if (x_3af6d8f2 && !transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_OPA_SURF | G_RM_OPA_SURF2);
    } else if (!x_3af6d8f2 && !transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2);
    } else if (x_3af6d8f2 && transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    } else if (!x_3af6d8f2 && transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2);
    }

    gtStateSetOthermode(gfx, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(gfx, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(gfx, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(gfx, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(gfx, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(gfx, GT_PIPELINE, G_PM_NPRIMITIVE);

    x_cc1d0de5->header.x_09cf7a45 &= ~G_RDP_TRI_ZBUFF_MASK;
}

s32 model_render_mode_setup(Object *obj) {
    x_6fcfcf46 *x_20d20338;
    u32 j;
    x_c1cedf06 *x_3ab7202f;
    Model *model;
    u32 i;
    s32 count;
    x_c1cedf06 *x_67f2cdea;
    x_c1cedf06 *x_cc6990d0;
    s32 flags;
    s32 x_1652bbb1;
    s32 transparent;
    u8 *x_c8099ad6;

    flags = obj->flags;
    x_20d20338 = obj->x_20d20338;
    model = x_20d20338->model;
    count = x_20d20338->x_6dcce206;
    x_67f2cdea = x_20d20338->x_78526b81;
    x_cc6990d0 = x_20d20338->x_78526b81 + 30;
    x_1652bbb1 = obj->flags & x_0488a75b;
    transparent = flags & x_b6789b80;
    x_c8099ad6 = x_20d20338->x_c8099ad6;

    for (i = 0; i < count; x_67f2cdea++, x_cc6990d0++, i++) {
        s32 x_773702e7 = x_c8099ad6[i];

        if (x_773702e7 && !sZbufFillSkipped) {
            model_render_mode_zbuf(x_67f2cdea, transparent);
            model_render_mode_zbuf(x_cc6990d0, transparent);
        } else {
            model_render_mode_standard(x_67f2cdea, x_1652bbb1, transparent);
            model_render_mode_standard(x_cc6990d0, x_1652bbb1, transparent);
        }

        x_3ab7202f = model->x_d6eac39a[i];
        for (j = 1; j < model->x_c246f31f[i]; j++) {
            if (x_773702e7 && !sZbufFillSkipped) {
                model_render_mode_zbuf(&x_3ab7202f[j], transparent);
            } else {
                model_render_mode_standard(&x_3ab7202f[j], x_1652bbb1, transparent);
            }
        }
    }

    return 0;
}

void model_parts_enable_all(Object *obj) {
    u32 i;
    x_6fcfcf46 *model = obj->x_20d20338;
    s32 x_6dcce206 = model->x_6dcce206;
    u8 *x_c8099ad6 = model->x_c8099ad6;

    for (i = 0; i < x_6dcce206; i++) {
        x_c8099ad6[i] = TRUE;
    }
}

void model_parts_disable_all(Object *obj) {
    x_6fcfcf46 *model = obj->x_20d20338;
    u32 i;
    s32 x_6dcce206 = model->x_6dcce206;
    u8 *x_c8099ad6 = model->x_c8099ad6;

    for (i = 0; i < x_6dcce206; i++) {
        x_c8099ad6[i] = FALSE;
    }
}

void model_visibility_sync(Object *obj) {
    x_6fcfcf46 *model = obj->x_20d20338;
    u32 i;
    s32 x_6dcce206 = model->x_6dcce206;
    u8 *x_d8f5cfb2;
    u8 *x_4cf2fcb6;

    x_4cf2fcb6 = model->x_c8099ad6;
    x_d8f5cfb2 = model->x_8f151cd3;

    if (gGfxFlags & GFX_SHADOW_MODE) {
        if (!(obj->flags & x_0488a75b)) {
            memcpy(x_d8f5cfb2, x_4cf2fcb6, x_6dcce206);
            model_parts_disable_all(obj);
            rsp_register_callback(model_render_mode_setup, obj);
            obj->flags |= x_0488a75b;
            gGfxFlags |= GFX_NO_ZCLEAR;
        }
        return;
    }

    if (!(gGfxFlags & GFX_SHADOW_MODE) && (obj->flags & x_0488a75b)) {
        if (sZbufFillSkipped) {
            gGfxFlags &= ~GFX_NO_ZCLEAR;
        } else {
            memcpy(x_4cf2fcb6, x_d8f5cfb2, x_6dcce206);
            rsp_register_callback(model_render_mode_setup, obj);
            obj->flags &= ~x_0488a75b;
        }
        return;
    }

    for (i = 0; i < x_6dcce206; i++) {
        if (x_d8f5cfb2[i] != x_4cf2fcb6[i]) {
            memcpy(x_d8f5cfb2, x_4cf2fcb6, x_6dcce206);
            rsp_register_callback(model_render_mode_setup, obj);
            break;
        }
    }
}

void model_visibility_set(Object *obj, u8 *x_84ff873b) {
    x_6fcfcf46 *model = obj->x_20d20338;
    s32 count = model->x_6dcce206;
    u32 i;
    u8 *x_d8f5cfb2 = model->x_8f151cd3;
    u8 *x_4cf2fcb6 = model->x_c8099ad6;

    if (gGfxFlags & GFX_SHADOW_MODE) {
        for (i = 0; i < count; i++) {
            x_d8f5cfb2[i] = x_4cf2fcb6[i] = x_84ff873b[i];
        }
    } else {
        for (i = 0; i < count; i++) {
            x_4cf2fcb6[i] = x_84ff873b[i];
        }
    }
}

s32 model_prim_color_update(Object *obj) {
    x_6fcfcf46 *x_20d20338 = obj->x_20d20338;
    x_6751d717 *color;
    u8 v1 = obj->color.a;
    u32 i;
    u32 count = x_20d20338->x_6dcce206;
    Model *model = x_20d20338->model;
    x_320b5d80 *x_53a2c1d5;
    Gfx *gfx;

    for (i = 0; i < count; i++) {
        x_53a2c1d5 = model->x_467629e6[i];
        gfx = x_53a2c1d5->info->header.x_b7ba6d35;
        color = &obj->x_47e6a04c;
        if (gfx->words.w0 == _SHIFTL(G_SETPRIMCOLOR, 24, 8)) {
            gDPSetPrimColor(gfx, 0, 0, color->r, color->g, color->b, v1);
        }
    }

    return 0;
}

void model_prim_color_check(Object *obj) {
    x_6751d717 *x_5086c3f0 = &obj->x_47e6a04c;
    x_6751d717 *x_bd706c81 = &obj->x_da940449;

    x_5086c3f0->a = obj->color.a;

    if (x_bd706c81->r != x_5086c3f0->r || x_bd706c81->g != x_5086c3f0->g || x_bd706c81->b != x_5086c3f0->b ||
        x_bd706c81->a != x_5086c3f0->a) {
        rsp_register_callback(model_prim_color_update, obj);
        memcpy(&obj->x_da940449, &obj->x_47e6a04c, sizeof(x_6751d717));
    }
}

void model_node_centroid(x_6fcfcf46 *x_20d20338, s32 x_7b79be4b, x_88f11482 *x_b6669964) {
    x_c3c252eb *node;
    s32 x, y, z;
    s32 i, x_9d9b2b65;
    Vtx *vertices;

    x = 0;
    y = 0;
    z = 0;

    if (x_20d20338->x_305a60f8 != NULL) {
        node = &x_20d20338->x_305a60f8->model.x_3bfb7219->x_45978ecb[x_7b79be4b];
    } else {
        node = &x_20d20338->model->x_3bfb7219->x_45978ecb[x_7b79be4b];
    }

    x_9d9b2b65 = node->x_9d9b2b65;
    vertices = node->vertices;

    for (i = 0; i < x_9d9b2b65; i++) {
        x += vertices[i].v.ob[0];
        y += vertices[i].v.ob[1];
        z += vertices[i].v.ob[2];
    }

    x_b6669964->x = x / x_9d9b2b65;
    x_b6669964->y = y / x_9d9b2b65;
    x_b6669964->z = z / x_9d9b2b65;
}

void model_node_centroid_direct(Model *model, s32 x_7b79be4b, x_88f11482 *x_b6669964) {
    x_c3c252eb *node;
    s32 x, y, z;
    s32 i, x_9d9b2b65;
    Vtx *vertices;

    x = 0;
    y = 0;
    z = 0;

    node = &model->x_3bfb7219->x_45978ecb[x_7b79be4b];

    x_9d9b2b65 = node->x_9d9b2b65;
    vertices = node->vertices;

    for (i = 0; i < x_9d9b2b65; i++) {
        x += vertices[i].v.ob[0];
        y += vertices[i].v.ob[1];
        z += vertices[i].v.ob[2];
    }

    x_b6669964->x = x / x_9d9b2b65;
    x_b6669964->y = y / x_9d9b2b65;
    x_b6669964->z = z / x_9d9b2b65;
}

void model_anim_setup_transforms(x_6fcfcf46 *x_20d20338, x_40f23fab *x_a092cc8e) {
    u32 j;
    s32 z, y, x;
    u32 count;
    u32 i;
    s32 k;
    s32 x_7b79be4b;
    s32 x_37d63f99;
    x_40f23fab *ptr;
    x_88f11482 x_b6669964;
    x_257b53b4 *s7;
    Transform *transforms;
    Gfx **x_1aae351f;

    transforms = x_20d20338->transforms;
    x_1aae351f = x_20d20338->x_305a60f8->model.x_467629e6;

    if (s7) {}

    count = 0;
    ptr = x_a092cc8e;
    while (ptr->x_67091bea[0] >= 0) {
        ptr++;
        count++;
    }
    x_20d20338->x_88c9004e = count;

    x_20d20338->x_9a3e80ff = s7 = mem_alloc_debug(count * sizeof(x_257b53b4), "model.c", 0x21C);

    for (i = 0; i < count; i++) {
        if (x_a092cc8e->x_0c9f73ee >= 0) {
            model_node_centroid(x_20d20338, x_7b79be4b = x_a092cc8e->x_0c9f73ee, &x_b6669964);
            s7->x_b6669964.x = x_b6669964.x;
            s7->x_b6669964.y = x_b6669964.y;
            s7->x_b6669964.z = x_b6669964.z;
        } else {
            x = y = z = 0;
            for (j = 0; j < 4; j++) {
                if (x_a092cc8e->x_67091bea[j] >= 0) {
                    model_node_centroid(x_20d20338, x_7b79be4b = x_a092cc8e->x_67091bea[j], &x_b6669964);
                    x += x_b6669964.x;
                    y += x_b6669964.y;
                    z += x_b6669964.z;
                } else {
                    break;
                }
            }
            s7->x_b6669964.x = x / (s32) j;
            s7->x_b6669964.y = y / (s32) j;
            s7->x_b6669964.z = z / (s32) j;
        }

        for (j = 0; j < 4; j++) {
            x_7b79be4b = s7->group[j] = x_a092cc8e->x_67091bea[j];
            if (x_7b79be4b < 0) {
                break;
            }
        }

        s7->x_0c9f73ee = x_a092cc8e->x_0c9f73ee;
        s7->x_ceaf196d = j;

        for (k = 0; k < j; k++) {
            x_37d63f99 = s7->group[k];
            s7->transforms[k] = transforms[x_37d63f99].mtx + 0;
            s7->transforms[j + k] = transforms[x_37d63f99].mtx + 1;
            s7->x_1aae351f[k] = x_1aae351f[x_37d63f99];
        }

        s7->x_af0aa1f8 = 0;
        s7++;
        x_a092cc8e++;
    }

    for (j = 0; j < x_20d20338->x_88c9004e; j++) {
        x_20d20338->x_61b49b7b[j].x_164cf1ca = x_20d20338->x_9a3e80ff + j;
    }
}

void model_anim_sort(Object *obj, s32 x_84ff873b) {
    x_6fcfcf46 *model;
    x_f9704fd6 *x_bf6199df;
    u32 i;
    x_f752bb53 *s6;
    s32 x_8a9089b3;
    Transform *transforms;
    x_257b53b4 *s1;
    f32 x, y, z, w;
    u32 a00;
    s32 a1, a3;
    x_257b53b4 *a2;
    u32 flags;

    model = obj->x_20d20338;
    s6 = model->x_61b49b7b;
    x_8a9089b3 = model->x_88c9004e;
    transforms = model->transforms;

    if (obj->flags & x_a816b63b) {
        x_bf6199df = &D_8013C6B0;
    } else {
        x_bf6199df = &x_7eefcd11;
    }

    for (i = 0; i < x_8a9089b3; i++) {
        s1 = s6[i].x_164cf1ca;
        if (transforms != NULL) {
            x_f9704fd6 *mtx =
                (s1->x_0c9f73ee >= 0) ? &transforms[s1->x_0c9f73ee].x_0c1a9bdd : &transforms[s1->group[0]].x_0c1a9bdd;
            mat4_mul_general(mtx, x_bf6199df, &gMat4Temp);
        } else {
            mat4_mul_general(&model->x_abd7b3c4.x_0c1a9bdd, x_bf6199df, &gMat4Temp);
        }

        x = gMat4Temp.x.x * s1->x_b6669964.x + gMat4Temp.y.x * s1->x_b6669964.y + gMat4Temp.z.x * s1->x_b6669964.z +
            gMat4Temp.w.x;
        y = gMat4Temp.x.y * s1->x_b6669964.x + gMat4Temp.y.y * s1->x_b6669964.y + gMat4Temp.z.y * s1->x_b6669964.z +
            gMat4Temp.w.y;
        z = gMat4Temp.x.z * s1->x_b6669964.x + gMat4Temp.y.z * s1->x_b6669964.y + gMat4Temp.z.z * s1->x_b6669964.z +
            gMat4Temp.w.z;
        w = gMat4Temp.x.w * s1->x_b6669964.x + gMat4Temp.y.w * s1->x_b6669964.y + gMat4Temp.z.w * s1->x_b6669964.z +
            gMat4Temp.w.w;

        if (w != 0.0f) {
            x /= w;
            y /= w;
        } else {
            x = y = z = 2.0f;
        }

        if (!(obj->flags & x_060adf1c)) {
            s6[i].flags = (x > 1.2 || x < -1.2 || y > 1.2 || y < -1.2);
        } else {
            s6[i].flags &= ~1;
        }

        s6[i].x_9dca29cd = x_84ff873b + z;
    }

    for (i = 1; i < x_8a9089b3; i++) {
        a2 = s6[i].x_164cf1ca;
        a1 = s6[i].x_9dca29cd;
        a3 = s6[i].flags;
        a00 = i;
        for (a00 = i; a00 != 0 && s6[a00 - 1].x_9dca29cd < a1; a00--) {
            s6[a00].x_164cf1ca = s6[a00 - 1].x_164cf1ca;
            s6[a00].x_9dca29cd = s6[a00 - 1].x_9dca29cd;
            s6[a00].flags = s6[a00 - 1].flags;
        }

        s6[a00].x_164cf1ca = a2;
        s6[a00].x_9dca29cd = a1;
        s6[a00].flags = a3;
    }
}

void model_anim_setup_dl(x_6fcfcf46 *x_20d20338, x_40f23fab *x_84ff873b) {
    u32 s1;
    s32 s2, s3, s4;
    u32 x_5c787447;
    u32 x_dcab8ab0;
    s32 s5;
    s32 x_cf10d3eb;
    s32 x_6e3cc34e;
    s32 pad3;
    x_88f11482 x_fd09f53e;
    x_40f23fab *ptr;
    x_257b53b4 *s7;
    x_320b5d80 **x_467629e6;
    u32 pad2;

    x_467629e6 = x_20d20338->model->x_467629e6;

    x_5c787447 = 0;
    ptr = x_84ff873b;
    while (ptr->x_67091bea[0] >= 0) {
        ptr++;
        x_5c787447++;
    }
    x_20d20338->x_88c9004e = x_5c787447;

    x_20d20338->x_9a3e80ff = s7 = mem_alloc_debug(x_5c787447 * sizeof(x_257b53b4), "model.c", 693);

    for (x_dcab8ab0 = 0; x_dcab8ab0 < x_5c787447; x_dcab8ab0++) {
        s7->x_af0aa1f8 = 1;
        if (x_84ff873b->x_0c9f73ee >= 0) {
            model_node_centroid(x_20d20338, x_cf10d3eb = x_84ff873b->x_0c9f73ee, &x_fd09f53e);
            s7->x_b6669964.x = x_fd09f53e.x;
            s7->x_b6669964.y = x_fd09f53e.y;
            s7->x_b6669964.z = x_fd09f53e.z;
        } else {
            s4 = s3 = s2 = 0;
            for (s1 = 0; s1 < 4; s1++) {
                if (x_84ff873b->x_67091bea[s1] >= 0) {
                    model_node_centroid(x_20d20338, x_6e3cc34e = x_84ff873b->x_67091bea[s1], &x_fd09f53e);
                    s4 += x_fd09f53e.x;
                    s3 += x_fd09f53e.y;
                    s2 += x_fd09f53e.z;
                } else {
                    break;
                }
            }
            s7->x_b6669964.x = s4 / (s32) s1;
            s7->x_b6669964.y = s3 / (s32) s1;
            s7->x_b6669964.z = s2 / (s32) s1;
        }

        for (s1 = 0; s1 < 4; s1++) {
            if ((s7->group[s1] = x_84ff873b->x_67091bea[s1]) < 0) {
                break;
            }
        }

        s7->x_0c9f73ee = x_84ff873b->x_0c9f73ee;
        s7->x_ceaf196d = s1;

        pad2 = s1;
        for (s5 = 0; s5 < pad2; s5++) {
            s32 x_6e3cc34e = s7->group[s5];
            s7->transforms[s5] = x_467629e6[x_6e3cc34e];
            s7->x_c246f31f[s5] = x_20d20338->model->x_c246f31f[x_6e3cc34e];
        }

        x_84ff873b++;
        s7++;
    }

    for (s1 = 0; s1 < x_20d20338->x_88c9004e; s1++) {
        x_20d20338->x_61b49b7b[s1].x_164cf1ca = x_20d20338->x_9a3e80ff + s1;
    }
}

void model_bone_setup(Model *x_cc1d0de5) {
    s32 count;
    u32 i;
    x_257b53b4 *s1;
    s32 unused[4];
    u32 j;
    x_320b5d80 **x_4c3c4684;
    s32 temp;
    x_88f11482 x_fd09f53e;
    s32 x_df21a243;

    count = x_cc1d0de5->x_6dcce206;
    s1 = x_cc1d0de5->x_761a0268 = (x_257b53b4 *) mem_alloc_debug(count * sizeof(x_257b53b4), "model.c", 766);
    temp = 1; // required to match
    x_4c3c4684 = x_cc1d0de5->x_467629e6;
    for (i = 0; i < count; i++, s1++) {
        s1->x_af0aa1f8 = temp;

        model_node_centroid_direct(x_cc1d0de5, i, &x_fd09f53e);
        s1->x_b6669964.x = x_fd09f53e.x;
        s1->x_b6669964.y = x_fd09f53e.y;
        s1->x_b6669964.z = x_fd09f53e.z;

        s1->group[0] = i;
        s1->group[1] = -1;
        s1->x_0c9f73ee = i;
        s1->x_ceaf196d = temp;

        x_df21a243 = 1; // required to match
        for (j = 0; j < x_df21a243; j++) {
            s32 v0 = s1->group[j];
            s1->transforms[j] = x_4c3c4684[v0];
            s1->x_c246f31f[j] = x_cc1d0de5->x_c246f31f[v0];
        }
    }
}

void model_part_draw(Model *x_cc1d0de5, s32 x_a1c9c44b) {
    u32 i;
    s32 count;
    x_320b5d80 *x_4bb24efc;

    x_4bb24efc = x_cc1d0de5->x_467629e6[x_a1c9c44b];
    count = x_cc1d0de5->x_c246f31f[x_a1c9c44b];

    for (i = 0; i < count; i++) {
        x_50746900(gDrBatchPtr, NULL, x_4bb24efc->info, x_4bb24efc->vertices, x_4bb24efc->triangles);
        x_4bb24efc++;
    }
}

void model_shadow_render(Object *obj) {
    x_6fcfcf46 *x_20d20338;
    Object *x_e4712596;
    s16 j;
    s16 i;
    s16 s6;
    x_f9704fd6 x_d753d975;
    f32 v1, a0;
    x_c1cedf06 *x_3ab7202f;
    Transform *transforms;
    s32 unused[4];
    x_320b5d80 **x_467629e6;
    x_f9704fd6 *x_3fde9cd9;

    x_20d20338 = obj->x_20d20338;
    transforms = x_20d20338->transforms;
    x_e4712596 = (Object *) obj->x_0f4167b4[1];
    x_3fde9cd9 = &obj->transform.x_3fde9cd9;
    x_467629e6 = x_20d20338->model->x_467629e6;

    if (x_e4712596->flags & x_c537cafa) {
        return;
    }

    sDisplayList = x_20d20338->x_305a60f8->model.x_bde24317;
    mat4_ident(&x_d753d975);
    s6 = D_8005BFCE * 30;

    for (i = 0; i < x_20d20338->x_6dcce206; i++) {
        mat4_mul3(&x_d753d975, &transforms[i].x_0c1a9bdd, x_3fde9cd9);
        mat4_mul_general(&x_d753d975, &x_7eefcd11, &gMat4Temp);

        if (gMat4Temp.w.w != 0.0f) {
            v1 = gMat4Temp.w.x / gMat4Temp.w.w;
            a0 = gMat4Temp.w.y / gMat4Temp.w.w;
        } else {
            v1 = a0 = 2.0f;
        }

        if (v1 > 1.0 || v1 < -1.0 || a0 > 1.0 || a0 < -1.0) {
            continue;
        }

        j = i + s6;

        x_3ab7202f = j + x_20d20338->x_78526b81;
        if (&gMat4Temp && &gMat4Temp) {} // required to match

        mat4_to_mtx(&x_3ab7202f->transform, &gMat4Temp);
        x_467629e6[i]->info = x_3ab7202f;
        model_part_draw(x_20d20338->model, i);
    }
}

void model_shadow_spawn(Object *x_4a65b74c, char *x_15887b2b, u32 context) {
    Object *shadow;

    x_dab0846a(sShadowDesc.name, x_15887b2b);
    shadow = obj_create_with_model(&sZeroPosition, NULL, &sShadowDesc, context);

    shadow->x_0f4167b4[0] = shadow->x_20d20338->transforms;
    shadow->x_0f4167b4[1] = x_4a65b74c;
    shadow->x_20d20338->transforms = x_4a65b74c->x_20d20338->transforms;
    shadow->x_0232396f = model_shadow_render;

    shadow->transform.x_3fde9cd9.y.x = 0.0f;
    shadow->transform.x_3fde9cd9.x.y = 0.0f;
    shadow->transform.x_3fde9cd9.y.y = 0.0f;
    shadow->transform.x_3fde9cd9.z.y = 0.0f;
    shadow->transform.x_3fde9cd9.y.z = -1.5f;
}

void model_traverse_transforms(Transform *x_cc1d0de5, Transform *x_84ff873b) {
    Mtx *s0;
    Transform *x_82439cbe;

    s0 = &x_84ff873b->mtx[D_8005BFCE];
    mat4_to_mtx(s0, &x_84ff873b->x_0c1a9bdd);
    x_84ff873b->x_834cdf4f = &s0->m[1][2];

    if (x_cc1d0de5 != NULL) {
        gSPMatrix(gF3dDisplayListPtr++, x_c485761a(s0), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    } else {
        gSPMatrix(gF3dDisplayListPtr++, x_c485761a(s0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    for (x_82439cbe = x_84ff873b->x_171183e4; x_82439cbe != NULL; x_82439cbe = x_82439cbe->x_fda6b96a) {
        model_traverse_transforms(x_84ff873b, x_82439cbe);
    }

    if (x_84ff873b->id >= 0) {
        gSPDisplayList(gF3dDisplayListPtr++, x_c485761a(sDisplayList[x_84ff873b->id]));
    }

    gSPPopMatrix(gF3dDisplayListPtr++, G_MTX_MODELVIEW);
}

void model_transforms_update(Object *obj) {
    x_6fcfcf46 *model = obj->x_20d20338;
    s32 count;
    s32 i;
    s16 delta;
    u8 *x_07bd45a3;
    Transform *transforms;
    x_88f11482 x_dcd2d24e;
    s32 unused[5];
    x_88f11482 *x_5d0e77f6;
    x_2758cdab *x_b3db7eeb;
    x_43bd08ed *x_3930e671;
    x_88f11482 *x_d6354d00;

    x_d6354d00 = model->x_d6354d00;
    x_07bd45a3 = model->x_07bd45a3;
    x_3930e671 = model->x_0094fc88;
    x_5d0e77f6 = model->x_5d0e77f6;
    x_b3db7eeb = model->x_b3db7eeb;
    count = model->x_6dcce206;
    transforms = model->transforms;

    for (i = 0; i < count; i++) {
        if (x_07bd45a3[i]) {
            mat4_from_euler(&transforms[i].x_3fde9cd9, &x_b3db7eeb[i]);
            mat4_apply_scale(&transforms[i].x_3fde9cd9, &x_d6354d00[i]);

            transforms[i].x_3fde9cd9.w.x = x_3930e671[i].x + x_5d0e77f6[i].x;
            transforms[i].x_3fde9cd9.w.y = x_3930e671[i].y + x_5d0e77f6[i].y;
            transforms[i].x_3fde9cd9.w.z = x_3930e671[i].z + x_5d0e77f6[i].z;
            x_07bd45a3[i] = FALSE;
        }
    }

    if (model->x_898495c5 || model->x_766c2c4d != 0) {
        mat4_from_euler(&model->x_abd7b3c4.x_3fde9cd9, &model->x_08d6ba0b);
        mat4_apply_scale(&model->x_abd7b3c4.x_3fde9cd9, &model->x_4e599cb3);
        model->x_898495c5 = FALSE;
    }

    if (obj->flags & x_9ee447da) {
        model->x_abd7b3c4.x_3fde9cd9.w.y = model->x_6689336b.y;
        x_dcd2d24e.y = 0;

        if (obj->flags & x_03ae0e9e) {
            x_dcd2d24e.x = model->x_6689336b.x - model->x_9cfd7bb4.x - model->x_3aefae96;
            delta = x_dcd2d24e.x - model->velocity.x;
            model->velocity.x = x_dcd2d24e.x;
            x_dcd2d24e.x = delta;
            model->x_abd7b3c4.x_3fde9cd9.w.x = model->x_9cfd7bb4.x;
        } else {
            x_dcd2d24e.x = 0;
        }

        x_dcd2d24e.z = model->x_6689336b.z - model->x_9cfd7bb4.z;

        if (x_dcd2d24e.z != 0 || x_dcd2d24e.x != 0) {
            delta = 0;
            if (obj->flags & x_d645b406) {
                obj->flags &= ~x_d645b406;
            } else {
                delta = x_dcd2d24e.z - model->velocity.z;
            }
            model->velocity.z = x_dcd2d24e.z;
            x_dcd2d24e.z = delta;

            model->x_abd7b3c4.x_3fde9cd9.w.z = model->x_9cfd7bb4.z;
            vec_rotate_by_euler(&x_dcd2d24e, &obj->x_224610f1);
            if (!(obj->flags & x_56bbd9b2)) {
                obj->pos.x += x_dcd2d24e.x;
                obj->pos.z += x_dcd2d24e.z;
            }
        }
    } else {
        model->x_abd7b3c4.x_3fde9cd9.w.x = model->x_6689336b.x;
        model->x_abd7b3c4.x_3fde9cd9.w.y = model->x_6689336b.y;
        model->x_abd7b3c4.x_3fde9cd9.w.z = model->x_6689336b.z;

        if (model->x_6786034d.z != 0) {
            x_dcd2d24e.x = 0;
            x_dcd2d24e.z = model->x_6786034d.z - model->velocity.z;
            model->velocity.z = model->x_6786034d.z;
            vec_rotate_by_euler(&x_dcd2d24e, &obj->x_224610f1); // @bug sp88.y undefined
            obj->pos.x += x_dcd2d24e.x;
            obj->pos.z += x_dcd2d24e.z;
        }

        if (obj->flags & x_da021b29) {
            if (obj->flags & x_da584e3c) {
                obj->x_224610f1.y = 0x400 - ((0xC00 - obj->x_224610f1.y) & 0xFFF);
                obj->flags &= ~x_da584e3c;
            }

            obj->flags &= ~x_da021b29;

            x_dcd2d24e.y = 0;
            x_dcd2d24e.x = model->x_6689336b.x;
            x_dcd2d24e.z = model->x_6689336b.z;

            vec_rotate_by_euler(&x_dcd2d24e, &obj->x_224610f1);
            obj->pos.x -= x_dcd2d24e.x;
            obj->pos.z -= x_dcd2d24e.z;
        }
    }
}

void model_anim_blend_weighted(u8 *x_21a0270b, s16 *value, Object *obj) {
    s32 x_7b79be4b;
    x_6fcfcf46 *model;

    x_7b79be4b = x_21a0270b[2];
    model = obj->x_20d20338;

    if (x_7b79be4b == 0xFF) {
        switch (x_21a0270b[3] & 0xF) {
            case 1:
                model->x_08d6ba0b.x = (*value + model->x_08d6ba0b.x) >> 1;
                model->x_898495c5 = TRUE;
                break;
            case 2:
                model->x_08d6ba0b.y = (*value + model->x_08d6ba0b.y) >> 1;
                model->x_898495c5 = TRUE;
                break;
            case 3:
                model->x_08d6ba0b.z = (*value + model->x_08d6ba0b.z) >> 1;
                model->x_898495c5 = TRUE;
                break;
            case 4:
                model->x_6689336b.x = ((*value + model->x_6689336b.x - model->x_9cfd7bb4.x) >> 1) + model->x_9cfd7bb4.x;
                break;
            case 5:
                model->x_6689336b.y = ((*value + model->x_6689336b.y - model->x_9cfd7bb4.y) >> 1) + model->x_9cfd7bb4.y;
                break;
            case 6:
                model->x_6689336b.z = ((*value + model->x_6689336b.z - model->x_9cfd7bb4.z) >> 1) + model->x_9cfd7bb4.z;
                break;
            case 7:
                model->x_4e599cb3.x = (*value + model->x_4e599cb3.x) >> 1;
                model->x_898495c5 = TRUE;
                break;
            case 8:
                model->x_4e599cb3.y = (*value + model->x_4e599cb3.y) >> 1;
                model->x_898495c5 = TRUE;
                break;
            case 9:
                model->x_4e599cb3.z = (*value + model->x_4e599cb3.z) >> 1;
                model->x_898495c5 = TRUE;
                break;
        }
    } else if (x_7b79be4b == 0xFE) {
        switch (x_21a0270b[3] & 0xF) {
            case 5:
                obj->pos.y = (*value + obj->pos.y) >> 1;
                break;
            case 6:
                model->x_6786034d.z = (*value * obj->velocity.z + model->x_6786034d.z) >> 1;
                break;
            case 2:
                model->x_766c2c4d = (*value + model->x_766c2c4d) >> 1;
                break;
        }
    } else {
        x_2758cdab *temp = &model->x_b3db7eeb[x_7b79be4b];
        switch (x_21a0270b[3] & 0xF) {
            case 1:
                temp->x = (*value + temp->x) >> 1;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 2:
                temp->y = (*value + temp->y) >> 1;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 3:
                temp->z = (*value + temp->z) >> 1;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 4:
                model->x_5d0e77f6[x_7b79be4b].x = (f32) ((model->x_5d0e77f6[x_7b79be4b].x + *value) >> 1);
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 5:
                model->x_5d0e77f6[x_7b79be4b].y = (f32) ((model->x_5d0e77f6[x_7b79be4b].y + *value) >> 1);
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 6:
                model->x_5d0e77f6[x_7b79be4b].z = (f32) ((model->x_5d0e77f6[x_7b79be4b].z + *value) >> 1);
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 7:
                model->x_d6354d00[x_7b79be4b].x = (*value + model->x_d6354d00[x_7b79be4b].x) >> 1;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 8:
                model->x_d6354d00[x_7b79be4b].y = (*value + model->x_d6354d00[x_7b79be4b].y) >> 1;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 9:
                model->x_d6354d00[x_7b79be4b].z = (*value + model->x_d6354d00[x_7b79be4b].z) >> 1;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
        }
    }
}

void model_anim_blend_absolute(u8 *x_21a0270b, s16 *value, Object *obj) {
    s32 x_7b79be4b;
    x_6fcfcf46 *model;

    x_7b79be4b = x_21a0270b[2];
    model = obj->x_20d20338;

    if (x_7b79be4b == 0xFF) {
        switch (x_21a0270b[3] & 0xF) {
            case 1:
                model->x_08d6ba0b.x = *value;
                model->x_898495c5 = TRUE;
                break;
            case 2:
                model->x_08d6ba0b.y = *value;
                model->x_898495c5 = TRUE;
                break;
            case 3:
                model->x_08d6ba0b.z = *value;
                model->x_898495c5 = TRUE;
                break;
            case 4:
                model->x_6689336b.x = *value + model->x_9cfd7bb4.x;
                break;
            case 5:
                model->x_6689336b.y = *value + model->x_9cfd7bb4.y;
                break;
            case 6:
                model->x_6689336b.z = *value + model->x_9cfd7bb4.z;
                break;
            case 7:
                model->x_4e599cb3.x = *value;
                model->x_898495c5 = TRUE;
                break;
            case 8:
                model->x_4e599cb3.y = *value;
                model->x_898495c5 = TRUE;
                break;
            case 9:
                model->x_4e599cb3.z = *value;
                model->x_898495c5 = TRUE;
                break;
        }
    } else if (x_7b79be4b == 0xFE) {
        switch (x_21a0270b[3] & 0xF) {
            case 5:
                obj->pos.y = *value;
                break;
            case 6:
                model->x_6786034d.z = *value * obj->velocity.z;
                break;
            case 2:
                model->x_766c2c4d = *value;
                break;
        }
    } else {
        switch (x_21a0270b[3] & 0xF) {
            case 1:
                model->x_b3db7eeb[x_7b79be4b].x = *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 2:
                model->x_b3db7eeb[x_7b79be4b].y = *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 3:
                model->x_b3db7eeb[x_7b79be4b].z = *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 4:
                model->x_5d0e77f6[x_7b79be4b].x = (f32) *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 5:
                model->x_5d0e77f6[x_7b79be4b].y = (f32) *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 6:
                model->x_5d0e77f6[x_7b79be4b].z = (f32) *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 7:
                model->x_d6354d00[x_7b79be4b].x = *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 8:
                model->x_d6354d00[x_7b79be4b].y = *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 9:
                model->x_d6354d00[x_7b79be4b].z = *value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
        }
    }
}

void model_anim_blend_additive(u8 *x_cc1d0de5, u8 *x_84ff873b, Object *obj) {
    s32 value;
    s32 x_7b79be4b;
    x_6fcfcf46 *model;
    x_2758cdab *temp;

    x_7b79be4b = x_cc1d0de5[2];
    model = obj->x_20d20338;
    value = *x_84ff873b;

    if (value & 0x80) {
        value |= 0xFFFFFF00; // sign extend
    }

    if (x_7b79be4b == 0xFF) {
        switch ((x_cc1d0de5[3] & 0xF0) >> 4) {
            case 1:
                model->x_08d6ba0b.x += value;
                model->x_898495c5 = TRUE;
                break;
            case 2:
                model->x_08d6ba0b.y += value;
                model->x_898495c5 = TRUE;
                break;
            case 3:
                model->x_08d6ba0b.z += value;
                model->x_898495c5 = TRUE;
                break;
            case 4:
                model->x_6689336b.x += value;
                break;
            case 5:
                model->x_6689336b.y += value;
                break;
            case 6:
                model->x_6689336b.z += value;
                break;
            case 7:
                model->x_4e599cb3.x += value;
                model->x_898495c5 = TRUE;
                break;
            case 8:
                model->x_4e599cb3.y += value;
                model->x_898495c5 = TRUE;
                break;
            case 9:
                model->x_4e599cb3.z += value;
                model->x_898495c5 = TRUE;
                break;
        }
    } else if (x_7b79be4b == 0xFE) {
        switch ((x_cc1d0de5[3] & 0xF0) >> 4) {
            case 5:
                obj->pos.y += value;
                break;
            case 6:
                model->x_6786034d.z += value * obj->velocity.z;
                break;
            case 2:
                model->x_766c2c4d += value;
                break;
        }
    } else {
        temp = model->x_b3db7eeb + x_7b79be4b;
        switch ((x_cc1d0de5[3] & 0xF0) >> 4) {
            case 1:
                temp->x += value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 2:
                temp->y += value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 3:
                temp->z += value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 4:
                model->x_5d0e77f6[x_7b79be4b].x += (f32) value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 5:
                model->x_5d0e77f6[x_7b79be4b].y += (f32) value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 6:
                model->x_5d0e77f6[x_7b79be4b].z += (f32) value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 7:
                model->x_d6354d00[x_7b79be4b].x += value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 8:
                model->x_d6354d00[x_7b79be4b].y += value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
            case 9:
                model->x_d6354d00[x_7b79be4b].z += value;
                model->x_07bd45a3[x_7b79be4b] = 1;
                break;
        }
    }
}

void model_anim_tick(Object *obj) {
    u8 *x_21a0270b;
    s16 x_14f49e74;
    x_6fcfcf46 *model = obj->x_20d20338;
    s32 x_9ef67445 = FALSE;

    if (obj->frameCounter & 1) {
        x_9ef67445 = TRUE;
    }
    x_14f49e74 = (obj->frameCounter + 1) >> 1;

    x_21a0270b = model->x_924433d2;
    while (*(s32 *) x_21a0270b != -1) {
        s32 x_a6aa2fc2 = x_21a0270b[0];
        s32 x_c4562d54 = x_21a0270b[1];

        if (x_14f49e74 > x_c4562d54 || x_14f49e74 < x_a6aa2fc2) {
            if (x_21a0270b[3] & 0xF) {
                x_21a0270b += x_c4562d54 * 2 - x_a6aa2fc2 * 2 + 6;
                if ((s32) x_21a0270b & 3) {
                    x_21a0270b += 2;
                }
            } else {
                x_21a0270b += x_c4562d54 - x_a6aa2fc2 + 5;
                while ((s32) x_21a0270b & 3) {
                    x_21a0270b++;
                }
            }
        } else {
            if (x_21a0270b[3] & 0xF) {
                if (x_9ef67445) {
                    model_anim_blend_weighted(x_21a0270b, x_21a0270b + 4 + x_14f49e74 * 2 - x_a6aa2fc2 * 2, obj);
                } else {
                    model_anim_blend_absolute(x_21a0270b, x_21a0270b + 4 + x_14f49e74 * 2 - x_a6aa2fc2 * 2, obj);
                }
                x_21a0270b += x_c4562d54 * 2 - x_a6aa2fc2 * 2 + 6;
                if ((s32) x_21a0270b & 3) {
                    x_21a0270b += 2;
                }
            } else {
                model_anim_blend_additive(x_21a0270b, x_21a0270b + 4 + x_14f49e74 - x_a6aa2fc2, obj);
                x_21a0270b += x_c4562d54 - x_a6aa2fc2 + 5;
                while ((s32) x_21a0270b & 3) {
                    x_21a0270b++;
                }
            }
        }
    }
}

u16 model_anim_duration(x_6fcfcf46 *model, s16 x_84ff873b) {
    x_4aeb64bb *x_533c59a1;

    x_533c59a1 = model->x_50771dcd[x_84ff873b]->entries;

    if ((x_533c59a1->b3 & 0xF0) != 0 && (x_533c59a1->b3 & 0x0F) != 0) {
        model->x_8e601526 = model->x_50771dcd[x_84ff873b]->b3 * ((x_533c59a1->b3 & 0xF0) >> 4);
    } else {
        model->x_8e601526 = model->x_50771dcd[x_84ff873b]->b3 * 2;
    }

    return model->x_8e601526;
}

void model_bones_reset(Object *obj) {
    x_6fcfcf46 *model = obj->x_20d20338;
    x_88f11482 *temp = model->x_5d0e77f6;
    Transform *transforms = model->transforms;
    s16 i;

    if (transforms != NULL) {
        for (i = 0; i < model->x_6dcce206; i++) {
            mat4_ident_partial(&transforms[i].x_3fde9cd9);
            temp[i].x = 0;
            temp[i].y = 0;
            temp[i].z = 0;
        }
    }

    for (i = 0; i < model->x_6dcce206; i++) {
        model->x_b3db7eeb[i].x = model->x_b3db7eeb[i].y = model->x_b3db7eeb[i].z = model->x_07bd45a3[i] = 0;
        model->x_d6354d00[i].x = model->x_d6354d00[i].y = model->x_d6354d00[i].z = 0x100;
    }
}

void model_anim_load(Object *obj) {
    x_6fcfcf46 *model = obj->x_20d20338;
    s32 v1;
    u32 i;
    u32 j;
    s32 v12;

    model->x_6786034d.z = 0;
    model->x_924433d2 = model->x_50771dcd[model->x_ee205ef9]->entries;
    v1 = model->x_924433d2->b3;
    if ((v1 & 0xF0) != 0 && (v1 & 0x0F) != 0) {
        model->x_8e601526 = model->x_50771dcd[model->x_ee205ef9]->b3 * ((v1 & 0xF0) >> 4);
    } else {
        model->x_8e601526 = model->x_50771dcd[model->x_ee205ef9]->b3 * 2;
    }

    if (model->transforms != NULL) {
        x_88f11482 *temp = model->x_5d0e77f6;
        Transform *transforms = model->transforms;
        for (i = 0; i < model->x_6dcce206; i++) {
            mat4_ident_partial(&transforms[i].x_3fde9cd9);
            temp[i].x = 0;
            temp[i].y = 0;
            temp[i].z = 0;
        }
    }

    for (i = 0; i < model->x_6dcce206; i++) {
        model->x_b3db7eeb[i].x = model->x_b3db7eeb[i].y = model->x_b3db7eeb[i].z = model->x_07bd45a3[i] = 0;
        model->x_d6354d00[i].x = 0x100;
        model->x_d6354d00[i].y = 0x100;
        model->x_d6354d00[i].z = 0x100;
    }

    mat4_ident_partial(&model->x_abd7b3c4.x_3fde9cd9);

    obj->x_2b06a023 = -1;
    model->velocity.x = model->velocity.z = 0;
    model->x_85b6be0b = model->x_766c2c4d = 0;
    model->x_6689336b.x = model->x_9cfd7bb4.x;
    model->x_6689336b.y = model->x_9cfd7bb4.y;
    model->x_6689336b.z = model->x_9cfd7bb4.z;

    if (obj->flags & x_9ee447da) {
        if (obj->flags & x_da584e3c) {
            obj->x_224610f1.y = 0x400 - ((0xC00 - obj->x_224610f1.y) & 0xFFF);
            obj->flags &= ~x_da584e3c;
        }
        obj->flags |= x_da021b29;
    }

    if (obj->flags & x_977143b5) {
        obj->flags &= ~x_977143b5;
        obj->flags |= x_da584e3c;
    }

    model->x_08d6ba0b.x = model->x_08d6ba0b.y = model->x_08d6ba0b.z = 0;
    model->x_4e599cb3.x = model->x_4e599cb3.y = model->x_4e599cb3.z = 0x100;
    obj->flags &= ~x_56bbd9b2;

    if (obj->frameCounter != 0) {
        v12 = obj->frameCounter;
        for (j = 0; j < v12; j++) {
            obj->frameCounter = j;
            model_anim_tick(obj);
            if (j == 0) {
                model_anim_tick(obj);
            }
        }
        obj->frameCounter = v12;
    } else {
        model_anim_tick(obj);
    }
}

void model_sort_entries(x_f752bb53 *x_e3226490, s32 x_6dcce206) {
    u32 i, j;
    x_f752bb53 *v1;
    x_f752bb53 *a1;

    if (sSortListHead != NULL) {
        v1 = sSortListHead;

        if (sSortListHead->x_9dca29cd < x_e3226490->x_9dca29cd) {
            i = 1;
            a1 = sSortListHead = x_e3226490;
        } else {
            i = 0;
            a1 = sSortListHead = v1;
            v1 = v1->next;
        }

        while (v1 != NULL && i < x_6dcce206) {
            if (v1->x_9dca29cd < x_e3226490[i].x_9dca29cd) {
                a1->next = &x_e3226490[i];
                a1 = &x_e3226490[i];
                i++;
            } else {
                a1->next = v1;
                a1 = v1;
                v1 = v1->next;
            }
        }

        while (v1 != NULL) {
            a1->next = v1;
            a1 = v1;
            v1 = v1->next;
        }

        for (j = i; j < x_6dcce206; j++) {
            a1->next = &x_e3226490[j];
            a1 = &x_e3226490[j];
        }

        a1->next = NULL;
    } else {
        a1 = sSortListHead = x_e3226490;
        for (j = 1; j < x_6dcce206; j++) {
            a1->next = &x_e3226490[j];
            a1 = &x_e3226490[j];
        }
        a1->next = NULL;
    }
}

void model_anim_render(Object *obj) {
    x_6fcfcf46 *x_20d20338;
    Transform *s5;
    Transform *s1;
    u32 i;
    Mtx *s6;
    s32 pad2;
    s32 x_af0e6490;
    s32 pad[3];

    x_20d20338 = obj->x_20d20338;
    x_af0e6490 = x_20d20338->x_6dcce206;
    s5 = x_20d20338->transforms;
    s1 = &obj->transform;

    task_execute(obj);

    mat4_from_euler(&s1->x_3fde9cd9, &obj->x_224610f1);
    mat4_set_translation(&s1->x_3fde9cd9, &obj->pos);
    transform_calc_world(s1);

    sDisplayList = x_20d20338->x_305a60f8->model.x_bde24317;

    if (x_20d20338->x_50771dcd != NULL) {
        if (x_20d20338->x_ee205ef9 != x_20d20338->x_2f4c4ce1) {
            model_anim_load(obj);
            x_20d20338->x_2f4c4ce1 = x_20d20338->x_ee205ef9;
        }

        if (obj->frameCounter != obj->x_2b06a023) {
            model_anim_tick(obj);
            model_transforms_update(obj);
            obj->x_2b06a023 = obj->frameCounter;
        }

        if (x_20d20338->x_9a3e80ff != NULL) {
            model_anim_sort(obj, 0);

            for (i = 0; i < x_af0e6490; i++) {
                mat4_to_mtx(&s5[i].mtx[D_8005BFCE], &s5[i].x_0c1a9bdd);
            }

            model_sort_entries(x_20d20338->x_61b49b7b, x_20d20338->x_88c9004e);
        } else {
            for (i = 0; i < x_af0e6490; i++) {
                s6 = &s5[i].mtx[D_8005BFCE];
                mat4_to_mtx(s6, &s5[i].x_0c1a9bdd);
                gSPMatrix(gF3dDisplayListPtr++, x_c485761a(s6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gF3dDisplayListPtr++, x_c485761a(sDisplayList[i]));
            }
        }
    } else {
        s6 = &s1->mtx[D_8005BFCE];
        mat4_to_mtx(s6, &s1->x_0c1a9bdd);
        gSPMatrix(gF3dDisplayListPtr++, x_c485761a(s6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        for (i = 0; i < x_af0e6490; i++) {
            gSPDisplayList(gF3dDisplayListPtr++, x_c485761a(sDisplayList[i]));
        }
    }
}

void model_frame_render(Object *obj) {
    x_6fcfcf46 *x_20d20338;
    Transform *x_19503ea6;
    Model *x_94b671c9;
    s32 index;
    x_257b53b4 *x_b3b1a6c0;
    x_320b5d80 *x_24aca5c4;
    s32 x_a1c9c44b;
    s32 x_82a08606;
    x_c1cedf06 *sub;
    s32 unused[5];
    x_c1cedf06 *x_78526b81;
    int temp;

    temp = obj->flags & x_c537cafa; // required to match

    index = obj->frameCounter;
    x_20d20338 = obj->x_20d20338;
    x_94b671c9 = x_20d20338->model;
    x_24aca5c4 = x_94b671c9->x_467629e6[index];
    x_a1c9c44b = D_8005BFCE * 30 + index;

    task_execute(obj);

    if (obj->flags & x_c537cafa) {
        return;
    }

    x_19503ea6 = &obj->transform;
    x_78526b81 = x_20d20338->x_78526b81;

    if (obj->flags & x_b6789b80) {
        model_prim_color_check(obj);
    }

    if (!(obj->flags & x_f25de720)) {
        obj->x_224610f1.x = D_8013C668.x;
        obj->x_224610f1.y = D_8013C668.y;
    }

    mat4_from_euler(&x_19503ea6->x_3fde9cd9, &obj->x_224610f1);
    mat4_set_translation(&x_19503ea6->x_3fde9cd9, &obj->pos);
    mat4_mul_general(&x_19503ea6->x_3fde9cd9, &x_7eefcd11, &gMat4Temp);

    sub = x_78526b81 + x_a1c9c44b;
    x_b3b1a6c0 = &x_20d20338->x_8b36595a;
    mat4_to_mtx(&sub->transform, &gMat4Temp);
    x_82a08606 = x_94b671c9->x_c246f31f[index];
    x_20d20338->x_da66be9b.x_415ed9d6[0] = sub;

    x_b3b1a6c0->transforms[0] = x_24aca5c4;
    x_b3b1a6c0->x_c246f31f[0] = x_82a08606;
    x_20d20338->x_da66be9b.next = sSortListHead;
    sSortListHead = &x_20d20338->x_da66be9b;
}

#ifdef NON_EQUIVALENT
void model_lighting_apply(Object *obj) {
    ScreenProfile *a2;
    x_6fcfcf46 *v1;
    x_2bb4cf6f *v0;
    u32 t6;    // sp160
    Model *t0; // sp168
    u32 t2;    // sp158
    s32 x_959ea381;
    x_a8b4b5ce *a1;
    x_81d7569b *s0;
    x_f9704fd6 *t4;
    u32 s7;
    s32 x_2bef91d9, x_86fee161, x_2dffbf44;
    s32 x_f5463fa4, x_e31ee89a, x_98e2dc09;
    s32 a22;
    s32 x_9b6a774b;
    s32 x_65cbb149, x_568db421, x_f4f7b3d7;
    s32 x_4b500ba0;
    x_6751d717 *x_389f2997;
    s32 a33, x_3d164c28, x_7f7ef9c9;
    s32 x_8c5f8c03;
    s32 x_1cc81ccd, x_f534bdd3, x_a822276e;
    s32 x_0dd5e275;
    s32 padding[12];
    s32 x_b25f9b0d;
    s32 x_3c1df98f;
    s32 x_b794385f;
    x_6751d717 *col;
    u8 a;
    x_88f11482 *pos;
    s32 v12;
    s32 v02;
    Vtx *x_6a103aec;
    s32 x_c188a78e;
    s32 x_5b215acc;
    s32 x_3def65ec;
    s32 x_81bfdb41;
    s32 x_dcccc364;
    s32 x_5c787447;
    s32 x_dcab8ab0;
    s32 x_8a9089b3;
    s32 x_4a1fd4d1;
    s32 x_af0e6490;
    s32 x_20b9213f;
    s32 x_7d0aaee0;
    s32 x_331089fa;
    s32 x_840385a0;
    s32 x_fd09f53e;
    s32 x_de61763c;
    s32 x_2a89e429;
    s32 x_54406eae;
    s32 x_f10a928a;
    s32 x_fc517ba8;
    s32 x_081c4eef;

    v1 = obj->x_20d20338;
    t6 = gFrameCounter & 7;
    a2 = &gScreenProfiles[gCurrentScreenId];

    t2 = v1->x_6dcce206;
    t0 = v1->model;
    x_389f2997 = &a2->ambientColor;

    v0 = a2->cameraBounds;
    x_af0e6490 = v0->lights[0].color.r;
    x_20b9213f = v0->lights[0].color.g;
    x_7d0aaee0 = v0->lights[0].color.b;
    x_de61763c = v0->lights[0].x_5962f1cd;
    x_2a89e429 = v0->lights[0].x_f9f5d537;
    x_54406eae = v0->lights[0].x_a18bc2e0;
    x_331089fa = v0->lights[1].color.r;
    x_840385a0 = v0->lights[1].color.g;
    x_fd09f53e = v0->lights[1].color.b;
    x_f10a928a = v0->lights[1].x_5962f1cd;
    x_fc517ba8 = v0->lights[1].x_f9f5d537;
    x_081c4eef = v0->lights[1].x_a18bc2e0;

    for (a1 = sLightListHead; a1 != NULL; a1 = a1->next) {
        a = a1->object->color.a;
        a1->x_2c79259e = (a1->red * a) / 256;
        a1->x_034f3eb1 = (a1->green * a) / 256;
        a1->x_817784f2 = (a1->blue * a) / 256;
    }

    for (; t6 < t2; t6 += 8) {
        x_959ea381 = t0->x_810b9a68[t6];
        s0 = t0->x_5b386c41[t6];
        t4 = &v1->transforms[t6].x_0c1a9bdd;

        x_c188a78e = (s32) (v1->transforms[t6].x_0c1a9bdd.x.x * 1024.0f);
        x_5b215acc = (s32) (v1->transforms[t6].x_0c1a9bdd.x.y * 1024.0f);
        x_3def65ec = (s32) (v1->transforms[t6].x_0c1a9bdd.x.z * 1024.0f);
        x_81bfdb41 = (s32) (v1->transforms[t6].x_0c1a9bdd.y.x * 1024.0f);
        x_dcccc364 = (s32) (v1->transforms[t6].x_0c1a9bdd.y.y * 1024.0f);
        x_5c787447 = (s32) (v1->transforms[t6].x_0c1a9bdd.y.z * 1024.0f);
        x_dcab8ab0 = (s32) (v1->transforms[t6].x_0c1a9bdd.z.x * 1024.0f);
        x_8a9089b3 = (s32) (v1->transforms[t6].x_0c1a9bdd.z.y * 1024.0f);
        x_4a1fd4d1 = (s32) (v1->transforms[t6].x_0c1a9bdd.z.z * 1024.0f);

        for (a1 = sLightListHead; a1 != NULL; a1 = a1->next) {
            pos = &a1->object->pos;
            x_f5463fa4 = x_2bef91d9 = pos->x - t4->w.x;
            x_e31ee89a = x_86fee161 = pos->y - t4->w.y;
            x_98e2dc09 = x_2dffbf44 = pos->z - t4->w.z;

            if (x_2bef91d9 < 0) {
                x_f5463fa4 = -x_2bef91d9;
            }
            if (x_86fee161 < 0) {
                x_e31ee89a = -x_86fee161;
            }
            if (x_2dffbf44 < 0) {
                x_98e2dc09 = -x_2dffbf44;
            }

            x_9b6a774b = x_4a9e7834(x_f5463fa4, x_98e2dc09);
            x_8c5f8c03 = x_4a9e7834(x_9b6a774b, x_e31ee89a) * 128;

            a1->x_b8173ab8 = x_2bef91d9;
            a1->x_60c27ea9 = x_86fee161;
            a1->x_d23de2ad = x_2dffbf44;
            a1->x_08b62e4f = x_8c5f8c03;
        }

        for (s7 = 0; s7 < x_959ea381; s7++) {
            x_1cc81ccd = s0[s7].x_fb9d51cc;
            x_f534bdd3 = s0[s7].x_c7f5b137;
            x_a822276e = s0[s7].x_a546469c;

            a33 = x_389f2997->r;
            x_3d164c28 = x_389f2997->g;
            x_7f7ef9c9 = x_389f2997->b;

            if (x_1cc81ccd & 0x80) {
                x_1cc81ccd |= ~0xFF;
            }
            if (x_f534bdd3 & 0x80) {
                x_f534bdd3 |= ~0xFF;
            }
            if (x_a822276e & 0x80) {
                x_a822276e |= ~0xFF;
            }

            x_65cbb149 = ((x_c188a78e * x_1cc81ccd) >> 10) + ((x_81bfdb41 * x_f534bdd3) >> 10) +
                         ((x_dcab8ab0 * x_a822276e) >> 10);
            x_568db421 = ((x_5b215acc * x_1cc81ccd) >> 10) + ((x_dcccc364 * x_f534bdd3) >> 10) +
                         ((x_8a9089b3 * x_a822276e) >> 10);
            x_f4f7b3d7 = ((x_3def65ec * x_1cc81ccd) >> 10) + ((x_5c787447 * x_f534bdd3) >> 10) +
                         ((x_4a1fd4d1 * x_a822276e) >> 10);

            x_4b500ba0 = x_de61763c * x_65cbb149 + x_2a89e429 * x_568db421 + x_54406eae * x_f4f7b3d7;
            if (x_4b500ba0 > 0) {
                a33 += (x_af0e6490 * x_4b500ba0) >> 14;
                x_3d164c28 += (x_20b9213f * x_4b500ba0) >> 14;
                x_7f7ef9c9 += (x_7d0aaee0 * x_4b500ba0) >> 14;
            }

            x_4b500ba0 = x_f10a928a * x_65cbb149 + x_fc517ba8 * x_568db421 + x_081c4eef * x_f4f7b3d7;
            if (x_4b500ba0 > 0) {
                a33 += (x_331089fa * x_4b500ba0) >> 14;
                x_3d164c28 += (x_840385a0 * x_4b500ba0) >> 14;
                x_7f7ef9c9 += (x_fd09f53e * x_4b500ba0) >> 14;
            }

            for (a1 = sLightListHead; a1 != NULL; a1 = a1->next) {
                v12 = a1->x_08b62e4f;
                x_4b500ba0 = a1->x_b8173ab8 * x_65cbb149 + a1->x_60c27ea9 * x_568db421 + a1->x_d23de2ad * x_f4f7b3d7;
                if (x_4b500ba0 > 0) {
                    a33 += (a1->x_2c79259e * x_4b500ba0) / v12 * 2;
                    x_3d164c28 += (a1->x_034f3eb1 * x_4b500ba0) / v12 * 2;
                    x_7f7ef9c9 += (a1->x_817784f2 * x_4b500ba0) / v12 * 2;
                }
            }

            if (a33 > 255 || x_3d164c28 > 255 || x_7f7ef9c9 > 255) {
                v02 = 0;
                if (v02 < a33) {
                    v02 = a33;
                }
                if (v02 < x_3d164c28) {
                    v02 = x_3d164c28;
                }
                if (v02 < x_7f7ef9c9) {
                    v02 = x_7f7ef9c9;
                }

                a33 = a33 * 255 / v02;
                x_3d164c28 = x_3d164c28 * 255 / v02;
                x_7f7ef9c9 = x_7f7ef9c9 * 255 / v02;
            }
            a22 = 0;
            while ((x_b794385f = s0[s7].x_d0dadb00[a22]) >= 0) {
                x_6a103aec = &t0->x_3bfb7219->x_45978ecb[t6].vertices[x_b794385f];
                col = &s0[s7].x_b21a405e[a22];
                if (col->r != 255 || col->g != 255 || col->b != 255) {
                    a22++;
                } else {
                    x_6a103aec->v.cn[0] = a33;
                    x_6a103aec->v.cn[1] = x_3d164c28;
                    x_6a103aec->v.cn[2] = x_7f7ef9c9;
                    a22++;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/model/model_lighting_apply.s")
#endif

void model_render(Object *obj) {
    x_320b5d80 **s2;
    x_6fcfcf46 *x_20d20338;
    Transform *x_30a44af1;
    s32 j;
    u32 i;
    x_257b53b4 *x_23b71842;
    x_f9704fd6 *a1;
    x_c1cedf06 *s0;
    s32 x_dd9604d9;
    x_f752bb53 *x_dfa11b27;
    s32 s6;
    Transform *x_7642845a;
    x_f9704fd6 *x_3086cf46;
    x_c1cedf06 *s7;
    s32 unused[8];

    x_20d20338 = obj->x_20d20338;
    x_30a44af1 = x_20d20338->transforms;
    s2 = x_20d20338->model->x_467629e6;
    x_dd9604d9 = 30 * D_8005BFCE;

    task_execute(obj);

    if (obj->flags & x_c537cafa) {
        return;
    }

    x_7642845a = &obj->transform;

    if (obj->flags & x_3e24eba7) {
        model_parts_enable_all(obj);
    }

    if ((!(obj->flags & x_215d3747)) || (obj->flags & x_3e24eba7)) {
        model_visibility_sync(obj);
    }

    model_prim_color_check(obj);

    if (obj->flags & x_f465a0fc) {
        obj->x_224610f1.y = D_8013C668.y;
        obj->x_224610f1.x = D_8013C668.x;
    }

    if (x_20d20338->x_50771dcd != NULL) {
        if (x_20d20338->x_ee205ef9 != x_20d20338->x_2f4c4ce1) {
            model_anim_load(obj);
            x_20d20338->x_2f4c4ce1 = x_20d20338->x_ee205ef9;
        }

        if (obj->frameCounter != obj->x_2b06a023) {
            model_anim_tick(obj);
            model_transforms_update(obj);
            obj->x_2b06a023 = obj->frameCounter;
        }

        mat4_from_euler(&x_7642845a->x_3fde9cd9, &obj->x_224610f1);
        mat4_set_translation(&x_7642845a->x_3fde9cd9, &obj->pos);
        transform_calc_world(x_7642845a);

        if (x_20d20338->x_9a3e80ff != NULL) {
            if (obj->flags & x_d13a68b5) {
                model_anim_sort(obj, -10000);
            } else {
                model_anim_sort(obj, 0);
            }

            x_dfa11b27 = x_20d20338->x_61b49b7b;
            for (i = 0; i < x_20d20338->x_88c9004e; i++) {
                x_23b71842 = x_dfa11b27[i].x_164cf1ca;
                if (obj->flags & x_e411fefb) {
                    x_dfa11b27[i].flags |= 2;
                }

                s6 = x_23b71842->x_ceaf196d;
                s7 = x_20d20338->x_78526b81;

                for (j = 0; j < s6; j++) {
                    s32 s1 = x_23b71842->group[j];

                    if (obj->flags & x_a816b63b) {
                        a1 = &D_8013C6B0;
                    } else {
                        a1 = &x_7eefcd11;
                    }

                    if (x_30a44af1 != NULL) {
                        mat4_mul_general(&x_30a44af1[s1].x_0c1a9bdd, a1, &gMat4Temp);
                    } else {
                        mat4_mul_general(&x_20d20338->x_abd7b3c4.x_0c1a9bdd, a1, &gMat4Temp);
                    }

                    s0 = &s7[s1 + x_dd9604d9];
                    mat4_to_mtx(&s0->transform, &gMat4Temp);
                    x_dfa11b27[i].x_415ed9d6[j] = s0;
                }
            }

            model_sort_entries(x_dfa11b27, x_20d20338->x_88c9004e);
        }
    } else {
        s0 = x_20d20338->x_78526b81;
        mat4_from_euler(&x_7642845a->x_3fde9cd9, &obj->x_224610f1);
        mat4_set_translation(&x_7642845a->x_3fde9cd9, &obj->pos);
        transform_calc_world(x_7642845a);
        mat4_mul_general(&x_7642845a->x_3fde9cd9, &x_7eefcd11, &gMat4Temp);
        mat4_to_mtx(&(s0 + x_dd9604d9)->transform, &gMat4Temp);
        model_part_draw(x_20d20338->model, 0);
        (*s2)->info = s0 + x_dd9604d9;
    }
}
