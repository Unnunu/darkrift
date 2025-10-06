#include "common.h"
#include "task.h"
#include "camera.h"
#include "string.h"
#include "PR/gt.h"

typedef struct GlobalObjD {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x2C */ Object *unk_28;
    /* 0x2C */ struct GlobalObjD *unk_2C;
    /* 0x30 */ struct GlobalObjD *unk_30;
} GlobalObjD; // size = 0x34

extern Vec4i D_8004934C;

// .data
K2Def D_80053010 = { "xxxxxxxxx", NULL, 0, 0xF9C, NULL };

// .bss
Gfx **D_8013C4E0;
s32 D_8013C4E4_unused;
ModelNodeRenderInfo *D_8013C4E8;
GlobalObjD *D_8013C4EC;
ItemPool D_8013C4F0;
TextureAsset *D_8013C500[16];
u32 D_8013C540;

void func_80034090(TextureAsset *arg0) {
    u32 i;

    for (i = 0; i < D_8013C540; i++) {
        if (D_8013C500[i] == arg0) {
            return;
        }
    }

    D_8013C500[D_8013C540++] = arg0;
}

s32 func_800340E8(void *arg0) {
    u32 i, j;
    TextureAsset *v1;
    u32 tmp;
    u32 a3;
    u32 *ptr;
    u32 q;

    for (i = 0; i < D_8013C540; i++) {
        v1 = D_8013C500[i];
        tmp = (v1->width * v1->height) / 8;
        ptr = v1->data;
        a3 = ((u32 *) v1->data)[0];

        for (j = 0; j < tmp - 1; j++, ptr++) {
            *ptr <<= 4;
            q = ptr[1];
            q = (q & 0xF0000000) >> 28;
            *ptr |= q;
        }

        *ptr <<= 4;
        a3 = (a3 & 0xF0000000) >> 28;
        *ptr |= a3;
    }

    return 1;
}

s32 func_8003424C(void *arg0) {
    u32 i, j, k;
    TextureAsset *v1;
    u32 tmp;
    u32 a3;
    u32 *ptr;
    u32 q;

    if (gFrameCounter & 1) {
        return 1;
    }

    for (i = 0; i < D_8013C540; i++) {
        v1 = D_8013C500[i];
        tmp = v1->width / 8;
        ptr = v1->data;

        for (j = 0; j < v1->height; j++) {
            a3 = *ptr;
            for (k = 0; k < tmp - 1; k++, ptr++) {
                *ptr <<= 4;
                q = ptr[1];
                q = (q & 0xF0000000) >> 28;
                *ptr |= q;
            }
            *ptr <<= 4;
            a3 = (a3 & 0xF0000000) >> 28;
            *ptr |= a3;
        }
    }

    return 1;
}

void func_800343EC(void) {
    D_8013C540 = 0;
}

void func_800343F8(Object *obj, u8 arg1) {
    ModelInstance *model = obj->modInst;
    UnkSam *sam = model->unk_A28;
    s32 numNodes = model->numNodes;
    u32 i, j;
    ModelNodeAsset *s1;
    s32 s2;
    BatchAsset *sub1;

    if (D_8013C540 == 0) {
        if (arg1) {
            func_800028E0(func_800340E8, 0);
        } else {
            func_800028E0(func_8003424C, 0);
        }
    }

    for (i = 0; i < numNodes; i++) {
        s1 = &sam->unk_04->nodes[i];
        s2 = s1->numParts;
        for (j = 0; j < s2; j++) {
            sub1 = s1->batchAssets + j;
            if ((u8) (sub1->unk_00 >= 0)) {
                func_80034090(sub1->texture);
            }
        }
    }

    obj->flags |= 0x2000;
}

void func_80034508(void) {
    D_8013C4EC = NULL;
    func_8002A8C0(&D_8013C4F0, 5, sizeof(GlobalObjD));
}

void func_8003453C(Object *obj, ColorRGBA *arg1) {
    GlobalObjD *objD;

    if (D_8013C4F0.count == 0) {
        return;
    }

    objD = (GlobalObjD *) GET_ITEM(D_8013C4F0);
    obj->flags |= 0x20000000;

    objD->unk_2C = D_8013C4EC;
    objD->unk_30 = NULL;
    if (D_8013C4EC != NULL) {
        D_8013C4EC->unk_30 = objD;
    }
    D_8013C4EC = objD;

    objD->unk_28 = obj;
    objD->unk_00 = arg1->r;
    objD->unk_04 = arg1->g;
    objD->unk_08 = arg1->b;
    obj->unk_208 = objD;
}

void func_800345D8(GlobalObjD *arg0) {
    if (arg0->unk_30 != NULL) {
        arg0->unk_30->unk_2C = arg0->unk_2C;
    } else {
        D_8013C4EC = arg0->unk_2C;
    }
    if (arg0->unk_2C != NULL) {
        arg0->unk_2C->unk_30 = arg0->unk_30;
    }

    RELEASE_ITEM(D_8013C4F0, arg0);
}

void func_80034648(BatchInfo *arg0, s32 transparent) {
    Gfx *gfx = &arg0->header.otherMode;

    mem_fill(gfx, 0, sizeof(Gfx));

    gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2);
    gtStateSetOthermode(gfx, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(gfx, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(gfx, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(gfx, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(gfx, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(gfx, GT_PIPELINE, G_PM_NPRIMITIVE);

    arg0->header.unk_00 |= 1;
}

void func_80034708(BatchInfo *arg0, s32 arg1, s32 transparent) {
    Gfx *gfx = &arg0->header.otherMode;

    mem_fill(gfx, 0, sizeof(Gfx));
    if (arg1 && !transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_OPA_SURF | G_RM_OPA_SURF2);
    } else if (!arg1 && !transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2);
    } else if (arg1 && transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    } else if (!arg1 && transparent) {
        gtStateSetOthermode(gfx, GT_RENDERMODE, G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2);
    }

    gtStateSetOthermode(gfx, GT_CYCLETYPE, G_CYC_1CYCLE);
    gtStateSetOthermode(gfx, GT_TEXTFILT, G_TF_BILERP);
    gtStateSetOthermode(gfx, GT_TEXTCONV, G_TC_FILT);
    gtStateSetOthermode(gfx, GT_TEXTPERSP, G_TP_PERSP);
    gtStateSetOthermode(gfx, GT_TEXTLUT, G_TT_RGBA16);
    gtStateSetOthermode(gfx, GT_PIPELINE, G_PM_NPRIMITIVE);

    arg0->header.unk_00 &= ~1;
}

s32 func_80034860(Object *obj) {
    ModelInstance *model;
    u32 j;
    BatchInfo *array;
    UnkSam *s4;
    u32 i;
    s32 count;
    BatchInfo *s7;
    BatchInfo *fp;
    s32 flags;
    s32 s5;
    s32 transparent;
    u8 *ptr;

    flags = obj->flags;
    model = obj->modInst;
    s4 = model->unk_A28;
    count = model->numNodes;
    s7 = model->unk_AB0;
    fp = model->unk_AB0 + 30;
    s5 = obj->flags & 0x40000000;
    transparent = flags & 0x2000;
    ptr = model->unk_1F6E;

    for (i = 0; i < count; s7++, fp++, i++) {
        s32 s3 = ptr[i];

        if (s3 && !D_800801E2) {
            func_80034648(s7, transparent);
            func_80034648(fp, transparent);
        } else {
            func_80034708(s7, s5, transparent);
            func_80034708(fp, s5, transparent);
        }

        array = s4->batchInfos[i];
        for (j = 1; j < s4->batchCounts[i]; j++) {
            if (s3 && !D_800801E2) {
                func_80034648(&array[j], transparent);
            } else {
                func_80034708(&array[j], s5, transparent);
            }
        }
    }

    return 0;
}

void func_800349F0(Object *obj) {
    u32 i;
    ModelInstance *model = obj->modInst;
    s32 count = model->numNodes;
    u8 *buffer = model->unk_1F6E;

    for (i = 0; i < count; i++) {
        buffer[i] = 1;
    }
}

void func_80034A58(Object *obj) {
    ModelInstance *model = obj->modInst;
    u32 i;
    s32 a2 = model->numNodes;
    u8 *ptr2 = model->unk_1F6E;

    for (i = 0; i < a2; i++) {
        ptr2[i] = 0;
    }
}

void func_80034AB8(Object *obj) {
    ModelInstance *model = obj->modInst;
    u32 i;
    s32 a2 = model->numNodes;
    u8 *ptr1;
    u8 *ptr2;

    ptr2 = model->unk_1F6E;
    ptr1 = model->unk_1F50;

    if (D_8008012C & 0x10) {
        if (!(obj->flags & 0x40000000)) {
            memcpy(ptr1, ptr2, a2);
            func_80034A58(obj);
            func_800028E0(func_80034860, obj);
            obj->flags |= 0x40000000;
            D_8008012C |= 8;
        }
        return;
    }

    if (!(D_8008012C & 0x10) && (obj->flags & 0x40000000)) {
        if (D_800801E2) {
            D_8008012C &= ~8;
        } else {
            memcpy(ptr2, ptr1, a2);
            func_800028E0(func_80034860, obj);
            obj->flags &= ~0x40000000;
        }
        return;
    }

    for (i = 0; i < a2; i++) {
        if (ptr1[i] != ptr2[i]) {
            memcpy(ptr1, ptr2, a2);
            func_800028E0(func_80034860, obj);
            break;
        }
    }
}

void func_80034C18(Object *obj, u8 *arg1) {
    ModelInstance *model = obj->modInst;
    s32 count = model->numNodes;
    u32 i;
    u8 *ptr1 = model->unk_1F50;
    u8 *ptr2 = model->unk_1F6E;

    if (D_8008012C & 0x10) {
        for (i = 0; i < count; i++) {
            ptr1[i] = ptr2[i] = arg1[i];
        }
    } else {
        for (i = 0; i < count; i++) {
            ptr2[i] = arg1[i];
        }
    }
}

s32 func_80034D54(Object *obj) {
    ModelInstance *model = obj->modInst;
    ColorRGBA *color;
    u8 v1 = obj->unk_088.a;
    u32 i;
    u32 count = model->numNodes;
    UnkSam *sam = model->unk_A28;
    Batch *disp;
    Gfx *gfx;

    for (i = 0; i < count; i++) {
        disp = sam->batches[i];
        gfx = disp->info->header.texGfx;
        color = &obj->unk_200;
        if (gfx->words.w0 == 0xFA000000) {
            gDPSetPrimColor(gfx, 0, 0, color->r, color->g, color->b, v1);
        }
    }

    return 0;
}

void func_80034F34(Object *obj) {
    ColorRGBA *color1 = &obj->unk_200;
    ColorRGBA *color2 = &obj->unk_204;

    color1->a = obj->unk_088.a;

    if (color2->r != color1->r || color2->g != color1->g || color2->b != color1->b || color2->a != color1->a) {
        func_800028E0(func_80034D54, obj);
        memcpy(&obj->unk_204, &obj->unk_200, sizeof(ColorRGBA));
    }
}

void func_80034FC8(ModelInstance *model, s32 arg1, Vec4i *arg2) {
    ModelNodeAsset *a1;
    s32 a, b, c;
    s32 i, count;
    Vtx *array;

    a = 0;
    b = 0;
    c = 0;

    if (model->unk_A24 != NULL) {
        a1 = &model->unk_A24->sam.unk_04->nodes[arg1];
    } else {
        a1 = &model->unk_A28->unk_04->nodes[arg1];
    }

    count = a1->numVertices;
    array = a1->vertices;

    for (i = 0; i < count; i++) {
        a += array[i].v.ob[0];
        b += array[i].v.ob[1];
        c += array[i].v.ob[2];
    }

    arg2->x = a / count;
    arg2->y = b / count;
    arg2->z = c / count;
}

void func_8003517C(UnkSam *sam, s32 arg1, Vec4i *arg2) {
    ModelNodeAsset *a1;
    s32 a, b, c;
    s32 i, count;
    Vtx *vertices;

    a = 0;
    b = 0;
    c = 0;

    a1 = &sam->unk_04->nodes[arg1];

    count = a1->numVertices;
    vertices = a1->vertices;

    for (i = 0; i < count; i++) {
        a += vertices[i].v.ob[0];
        b += vertices[i].v.ob[1];
        c += vertices[i].v.ob[2];
    }

    arg2->x = a / count;
    arg2->y = b / count;
    arg2->z = c / count;
}

void func_800352FC(ModelInstance *arg0, K2DefSub *arg1) {
    u32 s1;
    s32 s2, s3, s4;
    u32 sp7C;
    u32 sp78;
    s32 s5;
    s32 tmp;
    s32 tmp2;
    K2DefSub *ptr;
    Vec4i sp58;
    ModelNode *s7;
    Transform *sp50;
    Gfx **sp4C;

    sp50 = arg0->transforms;
    sp4C = arg0->unk_A24->sam.batches;
    if (s7) {}
    sp7C = 0;
    ptr = arg1;
    while (ptr->unk_00[0] >= 0) {
        ptr++;
        sp7C++;
    }
    arg0->unk_9C8 = sp7C;

    arg0->unk_604 = s7 = mem_alloc(sp7C * sizeof(ModelNode), "model.c", 0x21C);

    for (sp78 = 0; sp78 < sp7C; sp78++) {
        if (arg1->unk_10 >= 0) {
            func_80034FC8(arg0, tmp = arg1->unk_10, &sp58);
            s7->unk_14.x = sp58.x;
            s7->unk_14.y = sp58.y;
            s7->unk_14.z = sp58.z;
        } else {
            s4 = s3 = s2 = 0;
            for (s1 = 0; s1 < 4; s1++) {
                if (arg1->unk_00[s1] >= 0) {
                    func_80034FC8(arg0, tmp = arg1->unk_00[s1], &sp58);
                    s4 += sp58.x;
                    s3 += sp58.y;
                    s2 += sp58.z;
                } else {
                    break;
                }
            }
            s7->unk_14.x = s4 / (s32) s1;
            s7->unk_14.y = s3 / (s32) s1;
            s7->unk_14.z = s2 / (s32) s1;
        }

        for (s1 = 0; s1 < 4; s1++) {
            tmp = s7->unk_04[s1] = arg1->unk_00[s1];
            if (tmp < 0) {
                break;
            }
        }

        s7->unk_20 = arg1->unk_10;
        s7->unk_24 = s1;

        for (s5 = 0; s5 < s1; s5++) {
            tmp2 = s7->unk_04[s5];
            s7->unk_28[s5] = sp50[tmp2].mtx + 0;
            s7->unk_28[s1 + s5] = sp50[tmp2].mtx + 1;
            s7->unk_48[s5] = sp4C[tmp2];
        }

        s7->unk_00 = 0;
        s7++;
        arg1++;
    }

    for (s1 = 0; s1 < arg0->unk_9C8; s1++) {
        arg0->unk_608[s1].unk_04 = arg0->unk_604 + s1;
    }
}

void func_8003561C(Object *obj, s32 arg1) {
    ModelInstance *model;
    Matrix4f *fp;
    u32 i;
    ModelNodeRenderInfo *s6;
    s32 sp74;
    Transform *s5;
    ModelNode *s1;
    f32 x, y, z, w;
    u32 a00;
    s32 a1, a3;
    ModelNode *a2;
    u32 flags;

    model = obj->modInst;
    s6 = model->unk_608;
    sp74 = model->unk_9C8;
    s5 = model->transforms;

    if (obj->flags & 0x01000000) {
        fp = &D_8013C6B0;
    } else {
        fp = &gCameraProjectionMatrix;
    }

    for (i = 0; i < sp74; i++) {
        s1 = s6[i].unk_04;
        if (s5 != NULL) {
            Matrix4f *mtx = (s1->unk_20 >= 0) ? &s5[s1->unk_20].wolrd_matrix : &s5[s1->unk_04[0]].wolrd_matrix;
            math_mtxf_mul(mtx, fp, &D_800813E0);
        } else {
            math_mtxf_mul(&model->unk_010.wolrd_matrix, fp, &D_800813E0);
        }

        x = D_800813E0.x.x * s1->unk_14.x + D_800813E0.y.x * s1->unk_14.y + D_800813E0.z.x * s1->unk_14.z +
            D_800813E0.w.x;
        y = D_800813E0.x.y * s1->unk_14.x + D_800813E0.y.y * s1->unk_14.y + D_800813E0.z.y * s1->unk_14.z +
            D_800813E0.w.y;
        z = D_800813E0.x.z * s1->unk_14.x + D_800813E0.y.z * s1->unk_14.y + D_800813E0.z.z * s1->unk_14.z +
            D_800813E0.w.z;
        w = D_800813E0.x.w * s1->unk_14.x + D_800813E0.y.w * s1->unk_14.y + D_800813E0.z.w * s1->unk_14.z +
            D_800813E0.w.w;

        if (w != 0.0f) {
            x /= w;
            y /= w;
        } else {
            x = y = z = 2.0f;
        }

        if (!(obj->flags & 0x200000)) {
            s6[i].flags = (x > 1.2 || x < -1.2 || y > 1.2 || y < -1.2);
        } else {
            s6[i].flags &= ~1;
        }

        s6[i].zOrder = arg1 + z;
    }

    for (i = 1; i < sp74; i++) {
        a2 = s6[i].unk_04;
        a1 = s6[i].zOrder;
        a3 = s6[i].flags;
        a00 = i;
        for (a00 = i; a00 != 0 && s6[a00 - 1].zOrder < a1; a00--) {
            s6[a00].unk_04 = s6[a00 - 1].unk_04;
            s6[a00].zOrder = s6[a00 - 1].zOrder;
            s6[a00].flags = s6[a00 - 1].flags;
        }

        s6[a00].unk_04 = a2;
        s6[a00].zOrder = a1;
        s6[a00].flags = a3;
    }
}

void func_800359E4(ModelInstance *arg0, K2DefSub *arg1) {
    u32 s1;
    s32 s2, s3, s4;
    u32 sp7C;
    u32 sp78;
    s32 s5;
    s32 tmp;
    s32 tmp2;
    s32 pad3;
    Vec4i sp58;
    K2DefSub *ptr;
    ModelNode *s7;
    Batch **sp54;
    u32 pad2;

    sp54 = arg0->unk_A28->batches;

    sp7C = 0;
    ptr = arg1;
    while (ptr->unk_00[0] >= 0) {
        ptr++;
        sp7C++;
    }
    arg0->unk_9C8 = sp7C;

    arg0->unk_604 = s7 = mem_alloc(sp7C * sizeof(ModelNode), "model.c", 0x2B5);

    for (sp78 = 0; sp78 < sp7C; sp78++) {
        s7->unk_00 = 1;
        if (arg1->unk_10 >= 0) {
            func_80034FC8(arg0, tmp = arg1->unk_10, &sp58);
            s7->unk_14.x = sp58.x;
            s7->unk_14.y = sp58.y;
            s7->unk_14.z = sp58.z;
        } else {
            s4 = s3 = s2 = 0;
            for (s1 = 0; s1 < 4; s1++) {
                if (arg1->unk_00[s1] >= 0) {
                    func_80034FC8(arg0, tmp2 = arg1->unk_00[s1], &sp58);
                    s4 += sp58.x;
                    s3 += sp58.y;
                    s2 += sp58.z;
                } else {
                    break;
                }
            }
            s7->unk_14.x = s4 / (s32) s1;
            s7->unk_14.y = s3 / (s32) s1;
            s7->unk_14.z = s2 / (s32) s1;
        }

        for (s1 = 0; s1 < 4; s1++) {
            if ((s7->unk_04[s1] = arg1->unk_00[s1]) < 0) {
                break;
            }
        }

        s7->unk_20 = arg1->unk_10;
        s7->unk_24 = s1;

        pad2 = s1;
        for (s5 = 0; s5 < pad2; s5++) {
            s32 tmp2 = s7->unk_04[s5];
            s7->unk_28[s5] = sp54[tmp2];
            s7->unk_38[s5] = arg0->unk_A28->batchCounts[tmp2];
        }

        arg1++;
        s7++;
    }

    for (s1 = 0; s1 < arg0->unk_9C8; s1++) {
        arg0->unk_608[s1].unk_04 = arg0->unk_604 + s1;
    }
}

void func_80035CCC(UnkSam *arg0) {
    s32 count;
    u32 i;
    ModelNode *s1;
    s32 unused[4];
    u32 j;
    Batch **var1;
    s32 temp;
    Vec4i sp58;
    s32 temp2;

    count = arg0->unk_128;
    s1 = arg0->unk_31C = (ModelNode *) mem_alloc(count * sizeof(ModelNode), "model.c", 766);
    temp = 1; // required to match
    var1 = arg0->batches;
    for (i = 0; i < count; i++, s1++) {
        s1->unk_00 = temp;

        func_8003517C(arg0, i, &sp58);
        s1->unk_14.x = sp58.x;
        s1->unk_14.y = sp58.y;
        s1->unk_14.z = sp58.z;

        s1->unk_04[0] = i;
        s1->unk_04[1] = -1;
        s1->unk_20 = i;
        s1->unk_24 = temp;

        temp2 = 1; // required to match
        for (j = 0; j < temp2; j++) {
            s32 v0 = s1->unk_04[j];
            s1->unk_28[j] = var1[v0];
            s1->unk_38[j] = arg0->batchCounts[v0];
        }
    }
}

void func_80035DF8(UnkSam *arg0, s32 arg1) {
    u32 i;
    s32 a2;
    Batch *v0;

    v0 = arg0->batches[arg1];
    a2 = arg0->batchCounts[arg1];

    for (i = 0; i < a2; i++) {
        gSPTriBatch(gMainBatchPos, NULL, v0->info, v0->vertices, v0->triangles);
        v0++;
    }
}

void func_80035F5C(Object *obj) {
    ModelInstance *model;
    Object *parent;
    s16 j;
    s16 i;
    s16 s6;
    Matrix4f sp98;
    f32 v1, a0;
    BatchInfo *sub;
    Transform *trans;
    s32 unused[4];
    Batch **sub3;
    Matrix4f *newvar;

    model = obj->modInst;
    trans = model->transforms;
    parent = (Object *) obj->vars[1];
    newvar = &obj->transform.local_matrix;
    sub3 = model->unk_A28->batches;

    if (parent->flags & 0x4) {
        return;
    }

    D_8013C4E0 = model->unk_A24->sam.dlist;
    func_80012AA8(&sp98);
    s6 = D_8005BFCE * 30;

    for (i = 0; i < model->numNodes; i++) {
        func_80014718(&sp98, &trans[i].wolrd_matrix, newvar);
        math_mtxf_mul(&sp98, &gCameraProjectionMatrix, &D_800813E0);

        if (D_800813E0.w.w != 0.0f) {
            v1 = D_800813E0.w.x / D_800813E0.w.w;
            a0 = D_800813E0.w.y / D_800813E0.w.w;
        } else {
            v1 = a0 = 2.0f;
        }

        if (v1 > 1.0 || v1 < -1.0 || a0 > 1.0 || a0 < -1.0) {
            continue;
        }

        j = i + s6;

        sub = j + model->unk_AB0;
        if (&D_800813E0 && &D_800813E0) {} // required to match

        math_mtxf2mtx(&sub->transform, &D_800813E0);
        sub3[i]->info = sub;
        func_80035DF8(model->unk_A28, i);
    }
}

void func_80036194(Object *arg0, char *arg1, u32 arg2) {
    Object *v0;

    str_copy(D_80053010.unk_00, arg1);
    v0 = func_8002BC84(&D_8004934C, NULL, &D_80053010, arg2);

    v0->vars[0] = v0->modInst->transforms;
    v0->vars[1] = arg0;
    v0->modInst->transforms = arg0->modInst->transforms;
    v0->fn_render = func_80035F5C;

    v0->transform.local_matrix.y.x = 0.0f;
    v0->transform.local_matrix.x.y = 0.0f;
    v0->transform.local_matrix.y.y = 0.0f;
    v0->transform.local_matrix.z.y = 0.0f;
    v0->transform.local_matrix.y.z = -1.5f;
}

void func_80036228(Transform *arg0, Transform *arg1) {
    Mtx *s0;
    Transform *iter;

    s0 = &arg1->mtx[D_8005BFCE];
    math_mtxf2mtx(s0, &arg1->wolrd_matrix);
    arg1->unk_94 = &s0->m[1][2];

    if (arg0 != NULL) {
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(s0), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    } else {
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(s0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    for (iter = arg1->firstChild; iter != NULL; iter = iter->nextSibling) {
        func_80036228(arg1, iter);
    }

    if (arg1->unk_8C >= 0) {
        gSPDisplayList(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(D_8013C4E0[arg1->unk_8C]));
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}

void func_8003635C(Object *obj) {
    ModelInstance *model = obj->modInst;
    s32 count;
    s32 i;
    s16 v1;
    u8 *ptr;
    Transform *trans;
    Vec4i sp88;
    s32 unused[5];
    Vec4i *nodePosition;
    Vec4s *nodeRotation;
    StructAA8 *vec2;
    Vec4i *nodeScale;

    nodeScale = model->nodeScale;
    ptr = model->unk_5E4;
    vec2 = model->unk_AA8;
    nodePosition = model->nodePosition;
    nodeRotation = model->nodeRotation;
    count = model->numNodes;
    trans = model->transforms;

    for (i = 0; i < count; i++) {
        if (ptr[i]) {
            math_rotate(&trans[i].local_matrix, &nodeRotation[i]);
            func_800139A0(&trans[i].local_matrix, &nodeScale[i]);

            trans[i].local_matrix.w.x = vec2[i].x + nodePosition[i].x;
            trans[i].local_matrix.w.y = vec2[i].y + nodePosition[i].y;
            trans[i].local_matrix.w.z = vec2[i].z + nodePosition[i].z;
            ptr[i] = FALSE;
        }
    }

    if (model->unk_9F4 || model->unk_132 != 0) {
        math_rotate(&model->unk_010.local_matrix, &model->unk_9CC);
        func_800139A0(&model->unk_010.local_matrix, &model->unk_9F8);
        model->unk_9F4 = FALSE;
    }

    if (obj->flags & 0x400) {
        model->unk_010.local_matrix.w.y = model->unk_9D4.y;
        sp88.y = 0;
        if (obj->flags & 0x20000) {
            sp88.x = model->unk_9D4.x - model->unk_9E4.x - model->unk_A1C;
            v1 = sp88.x - model->unk_002;
            model->unk_002 = sp88.x;
            sp88.x = v1;
            model->unk_010.local_matrix.w.x = model->unk_9E4.x;
        } else {
            sp88.x = 0;
        }
        sp88.z = model->unk_9D4.z - model->unk_9E4.z;

        if (sp88.z != 0 || sp88.x != 0) {
            v1 = 0;
            if (obj->flags & 0x100000) {
                obj->flags &= ~0x100000;
            } else {
                v1 = sp88.z - model->unk_006;
            }
            model->unk_006 = sp88.z;
            sp88.z = v1;

            model->unk_010.local_matrix.w.z = model->unk_9E4.z;
            func_8001370C(&sp88, &obj->rotation);
            if (!(obj->flags & 0x8000)) {
                obj->pos.x += sp88.x;
                obj->pos.z += sp88.z;
            }
        }
    } else {
        model->unk_010.local_matrix.w.x = model->unk_9D4.x;
        model->unk_010.local_matrix.w.y = model->unk_9D4.y;
        model->unk_010.local_matrix.w.z = model->unk_9D4.z;

        if (model->unk_00C != 0) {
            sp88.x = 0;
            sp88.z = model->unk_00C - model->unk_006;
            model->unk_006 = model->unk_00C;
            func_8001370C(&sp88, &obj->rotation); // @bug sp88.y undefined
            obj->pos.x += sp88.x;
            obj->pos.z += sp88.z;
        }

        if (obj->flags & 0x8000000) {
            if (obj->flags & 0x800000) {
                obj->rotation.y = 0x400 - ((0xC00 - obj->rotation.y) & 0xFFF);
                obj->flags &= ~0x800000;
            }

            obj->flags &= ~0x8000000;

            sp88.y = 0;
            sp88.x = model->unk_9D4.x;
            sp88.z = model->unk_9D4.z;

            func_8001370C(&sp88, &obj->rotation);
            obj->pos.x -= sp88.x;
            obj->pos.z -= sp88.z;
        }
    }
}

void model_anim_param_lerp(u8 *arg0, s16 *arg1, Object *obj) {
    s32 nodeId;
    ModelInstance *model;

    nodeId = arg0[2];
    model = obj->modInst;

    if (nodeId == 0xFF) {
        switch (arg0[3] & 0xF) {
            case 1:
                model->unk_9CC.x = (*arg1 + model->unk_9CC.x) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 2:
                model->unk_9CC.y = (*arg1 + model->unk_9CC.y) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 3:
                model->unk_9CC.z = (*arg1 + model->unk_9CC.z) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 4:
                model->unk_9D4.x = ((*arg1 + model->unk_9D4.x - model->unk_9E4.x) >> 1) + model->unk_9E4.x;
                break;
            case 5:
                model->unk_9D4.y = ((*arg1 + model->unk_9D4.y - model->unk_9E4.y) >> 1) + model->unk_9E4.y;
                break;
            case 6:
                model->unk_9D4.z = ((*arg1 + model->unk_9D4.z - model->unk_9E4.z) >> 1) + model->unk_9E4.z;
                break;
            case 7:
                model->unk_9F8.x = (*arg1 + model->unk_9F8.x) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 8:
                model->unk_9F8.y = (*arg1 + model->unk_9F8.y) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 9:
                model->unk_9F8.z = (*arg1 + model->unk_9F8.z) >> 1;
                model->unk_9F4 = TRUE;
                break;
        }
    } else if (nodeId == 0xFE) {
        switch (arg0[3] & 0xF) {
            case 5:
                obj->pos.y = (*arg1 + obj->pos.y) >> 1;
                break;
            case 6:
                model->unk_00C = (*arg1 * obj->unk_010.z + model->unk_00C) >> 1;
                break;
            case 2:
                model->unk_132 = (*arg1 + model->unk_132) >> 1;
                break;
        }
    } else {
        Vec4s *temp = &model->nodeRotation[nodeId];
        switch (arg0[3] & 0xF) {
            case 1:
                temp->x = (*arg1 + temp->x) >> 1;
                model->unk_5E4[nodeId] = 1;
                break;
            case 2:
                temp->y = (*arg1 + temp->y) >> 1;
                model->unk_5E4[nodeId] = 1;
                break;
            case 3:
                temp->z = (*arg1 + temp->z) >> 1;
                model->unk_5E4[nodeId] = 1;
                break;
            case 4:
                model->nodePosition[nodeId].x = (f32) ((model->nodePosition[nodeId].x + *arg1) >> 1);
                model->unk_5E4[nodeId] = 1;
                break;
            case 5:
                model->nodePosition[nodeId].y = (f32) ((model->nodePosition[nodeId].y + *arg1) >> 1);
                model->unk_5E4[nodeId] = 1;
                break;
            case 6:
                model->nodePosition[nodeId].z = (f32) ((model->nodePosition[nodeId].z + *arg1) >> 1);
                model->unk_5E4[nodeId] = 1;
                break;
            case 7:
                model->nodeScale[nodeId].x = (*arg1 + model->nodeScale[nodeId].x) >> 1;
                model->unk_5E4[nodeId] = 1;
                break;
            case 8:
                model->nodeScale[nodeId].y = (*arg1 + model->nodeScale[nodeId].y) >> 1;
                model->unk_5E4[nodeId] = 1;
                break;
            case 9:
                model->nodeScale[nodeId].z = (*arg1 + model->nodeScale[nodeId].z) >> 1;
                model->unk_5E4[nodeId] = 1;
                break;
        }
    }
}

void model_anim_param_set(u8 *script, s16 *value, Object *obj) {
    s32 nodeId;
    ModelInstance *model;

    nodeId = script[2];
    model = obj->modInst;

    if (nodeId == 0xFF) {
        switch (script[3] & 0xF) {
            case 1:
                model->unk_9CC.x = *value;
                model->unk_9F4 = TRUE;
                break;
            case 2:
                model->unk_9CC.y = *value;
                model->unk_9F4 = TRUE;
                break;
            case 3:
                model->unk_9CC.z = *value;
                model->unk_9F4 = TRUE;
                break;
            case 4:
                model->unk_9D4.x = *value + model->unk_9E4.x;
                break;
            case 5:
                model->unk_9D4.y = *value + model->unk_9E4.y;
                break;
            case 6:
                model->unk_9D4.z = *value + model->unk_9E4.z;
                break;
            case 7:
                model->unk_9F8.x = *value;
                model->unk_9F4 = TRUE;
                break;
            case 8:
                model->unk_9F8.y = *value;
                model->unk_9F4 = TRUE;
                break;
            case 9:
                model->unk_9F8.z = *value;
                model->unk_9F4 = TRUE;
                break;
        }
    } else if (nodeId == 0xFE) {
        switch (script[3] & 0xF) {
            case 5:
                obj->pos.y = *value;
                break;
            case 6:
                model->unk_00C = *value * obj->unk_010.z;
                break;
            case 2:
                model->unk_132 = *value;
                break;
        }
    } else {
        switch (script[3] & 0xF) {
            case 1:
                model->nodeRotation[nodeId].x = *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 2:
                model->nodeRotation[nodeId].y = *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 3:
                model->nodeRotation[nodeId].z = *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 4:
                model->nodePosition[nodeId].x = (f32) *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 5:
                model->nodePosition[nodeId].y = (f32) *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 6:
                model->nodePosition[nodeId].z = (f32) *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 7:
                model->nodeScale[nodeId].x = *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 8:
                model->nodeScale[nodeId].y = *value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 9:
                model->nodeScale[nodeId].z = *value;
                model->unk_5E4[nodeId] = 1;
                break;
        }
    }
}

void model_anim_param_add(u8 *arg0, u8 *arg1, Object *obj) {
    s32 value;
    s32 nodeId;
    ModelInstance *model;
    Vec4s *temp;

    nodeId = arg0[2];
    model = obj->modInst;
    value = *arg1;

    if (value & 0x80) {
        value |= 0xFFFFFF00; // sign extend
    }

    if (nodeId == 0xFF) {
        switch ((arg0[3] & 0xF0) >> 4) {
            case 1:
                model->unk_9CC.x += value;
                model->unk_9F4 = TRUE;
                break;
            case 2:
                model->unk_9CC.y += value;
                model->unk_9F4 = TRUE;
                break;
            case 3:
                model->unk_9CC.z += value;
                model->unk_9F4 = TRUE;
                break;
            case 4:
                model->unk_9D4.x += value;
                break;
            case 5:
                model->unk_9D4.y += value;
                break;
            case 6:
                model->unk_9D4.z += value;
                break;
            case 7:
                model->unk_9F8.x += value;
                model->unk_9F4 = TRUE;
                break;
            case 8:
                model->unk_9F8.y += value;
                model->unk_9F4 = TRUE;
                break;
            case 9:
                model->unk_9F8.z += value;
                model->unk_9F4 = TRUE;
                break;
        }
    } else if (nodeId == 0xFE) {
        switch ((arg0[3] & 0xF0) >> 4) {
            case 5:
                obj->pos.y += value;
                break;
            case 6:
                model->unk_00C += value * obj->unk_010.z;
                break;
            case 2:
                model->unk_132 += value;
                break;
        }
    } else {
        temp = model->nodeRotation + nodeId;
        switch ((arg0[3] & 0xF0) >> 4) {
            case 1:
                temp->x += value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 2:
                temp->y += value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 3:
                temp->z += value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 4:
                model->nodePosition[nodeId].x += (f32) value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 5:
                model->nodePosition[nodeId].y += (f32) value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 6:
                model->nodePosition[nodeId].z += (f32) value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 7:
                model->nodeScale[nodeId].x += value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 8:
                model->nodeScale[nodeId].y += value;
                model->unk_5E4[nodeId] = 1;
                break;
            case 9:
                model->nodeScale[nodeId].z += value;
                model->unk_5E4[nodeId] = 1;
                break;
        }
    }
}

void func_800371C0(Object *obj) {
    u8 *script;
    s16 animFrame;
    ModelInstance *model = obj->modInst;
    s32 lerp = FALSE;

    if (obj->spriteId & 1) {
        lerp = TRUE;
    }
    animFrame = (obj->spriteId + 1) >> 1;

    script = model->unk_A14;
    while (*(s32 *) script != -1) {
        s32 firstFrame = script[0];
        s32 lastFrame = script[1];

        if (animFrame > lastFrame || animFrame < firstFrame) {
            if (script[3] & 0xF) {
                script += lastFrame * 2 - firstFrame * 2 + 6;
                if ((s32) script & 3) {
                    script += 2;
                }
            } else {
                script += lastFrame - firstFrame + 5;
                while ((s32) script & 3) {
                    script++;
                }
            }
        } else {
            if (script[3] & 0xF) {
                if (lerp) {
                    model_anim_param_lerp(script, script + 4 + animFrame * 2 - firstFrame * 2, obj);
                } else {
                    model_anim_param_set(script, script + 4 + animFrame * 2 - firstFrame * 2, obj);
                }
                script += lastFrame * 2 - firstFrame * 2 + 6;
                if ((s32) script & 3) {
                    script += 2;
                }
            } else {
                model_anim_param_add(script, script + 4 + animFrame - firstFrame, obj);
                script += lastFrame - firstFrame + 5;
                while ((s32) script & 3) {
                    script++;
                }
            }
        }
    }
}

u16 func_80037394(ModelInstance *model, s16 arg1) {
    AnimEntry *firstEntry;

    firstEntry = model->animations[arg1]->entries;

    if ((firstEntry->b3 & 0xF0) != 0 && (firstEntry->b3 & 0x0F) != 0) {
        model->numAnimFrames = model->animations[arg1]->b3 * ((firstEntry->b3 & 0xF0) >> 4);
    } else {
        model->numAnimFrames = model->animations[arg1]->b3 * 2;
    }

    return model->numAnimFrames;
}

void func_800373FC(Object *obj) {
    ModelInstance *model = obj->modInst;
    Vec4i *temp = model->nodePosition;
    Transform *transforms = model->transforms;
    s16 i;

    if (transforms != NULL) {
        for (i = 0; i < model->numNodes; i++) {
            func_80012AF4(&transforms[i].local_matrix);
            temp[i].x = 0;
            temp[i].y = 0;
            temp[i].z = 0;
        }
    }

    for (i = 0; i < model->numNodes; i++) {
        model->nodeRotation[i].x = model->nodeRotation[i].y = model->nodeRotation[i].z = model->unk_5E4[i] = 0;
        model->nodeScale[i].x = model->nodeScale[i].y = model->nodeScale[i].z = 0x100;
    }
}

void func_80037500(Object *obj) {
    ModelInstance *model = obj->modInst;
    s32 v1;
    u32 i;
    u32 j;
    s32 v12;

    model->unk_00C = 0;
    model->unk_A14 = model->animations[model->currentAnimId]->entries;
    v1 = model->unk_A14->b3;
    if ((v1 & 0xF0) != 0 && (v1 & 0x0F) != 0) {
        model->numAnimFrames = model->animations[model->currentAnimId]->b3 * ((v1 & 0xF0) >> 4);
    } else {
        model->numAnimFrames = model->animations[model->currentAnimId]->b3 * 2;
    }

    if (model->transforms != NULL) {
        Vec4i *temp = model->nodePosition;
        Transform *transforms = model->transforms;
        for (i = 0; i < model->numNodes; i++) {
            func_80012AF4(&transforms[i].local_matrix);
            temp[i].x = 0;
            temp[i].y = 0;
            temp[i].z = 0;
        }
    }

    for (i = 0; i < model->numNodes; i++) {
        model->nodeRotation[i].x = model->nodeRotation[i].y = model->nodeRotation[i].z = model->unk_5E4[i] = 0;
        model->nodeScale[i].x = 0x100;
        model->nodeScale[i].y = 0x100;
        model->nodeScale[i].z = 0x100;
    }

    func_80012AF4(&model->unk_010.local_matrix);

    obj->unk_086 = -1;
    model->unk_002 = model->unk_006 = 0;
    model->unk_130 = model->unk_132 = 0;
    model->unk_9D4.x = model->unk_9E4.x;
    model->unk_9D4.y = model->unk_9E4.y;
    model->unk_9D4.z = model->unk_9E4.z;

    if (obj->flags & 0x400) {
        if (obj->flags & 0x800000) {
            obj->rotation.y = 0x400 - ((0xC00 - obj->rotation.y) & 0xFFF);
            obj->flags &= ~0x800000;
        }
        obj->flags |= 0x08000000;
    }

    if (obj->flags & 0x400000) {
        obj->flags &= ~0x400000;
        obj->flags |= 0x800000;
    }

    model->unk_9CC.x = model->unk_9CC.y = model->unk_9CC.z = 0;
    model->unk_9F8.x = model->unk_9F8.y = model->unk_9F8.z = 0x100;
    obj->flags &= ~0x8000;

    if (obj->spriteId != 0) {
        v12 = obj->spriteId;
        for (j = 0; j < v12; j++) {
            obj->spriteId = j;
            func_800371C0(obj);
            if (j == 0) {
                func_800371C0(obj);
            }
        }
        obj->spriteId = v12;
    } else {
        func_800371C0(obj);
    }
}

void func_80037788(ModelNodeRenderInfo *nodeList, s32 numNodes) {
    u32 i, j;
    ModelNodeRenderInfo *v1;
    ModelNodeRenderInfo *a1;

    if (D_8013C4E8 != NULL) {
        v1 = D_8013C4E8;

        if (D_8013C4E8->zOrder < nodeList->zOrder) {
            i = 1;
            a1 = D_8013C4E8 = nodeList;
        } else {
            i = 0;
            a1 = D_8013C4E8 = v1;
            v1 = v1->next;
        }

        while (v1 != NULL && i < numNodes) {
            if (v1->zOrder < nodeList[i].zOrder) {
                a1->next = &nodeList[i];
                a1 = &nodeList[i];
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

        for (j = i; j < numNodes; j++) {
            a1->next = &nodeList[j];
            a1 = &nodeList[j];
        }

        a1->next = NULL;
    } else {
        a1 = D_8013C4E8 = nodeList;
        for (j = 1; j < numNodes; j++) {
            a1->next = &nodeList[j];
            a1 = &nodeList[j];
        }
        a1->next = NULL;
    }
}

void func_8003795C(Object *obj) {
    ModelInstance *model;
    Transform *s5;
    Transform *s1;
    u32 i;
    Mtx *s6;
    s32 pad2;
    s32 sp6C;
    s32 pad[3];

    model = obj->modInst;
    sp6C = model->numNodes;
    s5 = model->transforms;
    s1 = &obj->transform;

    task_execute(obj);

    math_rotate(&s1->local_matrix, &obj->rotation);
    math_translate(&s1->local_matrix, &obj->pos);
    func_80014974(s1);

    D_8013C4E0 = model->unk_A24->sam.dlist;

    if (model->animations != NULL) {
        if (model->currentAnimId != model->unk_A0E) {
            func_80037500(obj);
            model->unk_A0E = model->currentAnimId;
        }

        if (obj->spriteId != obj->unk_086) {
            func_800371C0(obj);
            func_8003635C(obj);
            obj->unk_086 = obj->spriteId;
        }

        if (model->unk_604 != NULL) {
            func_8003561C(obj, 0);

            for (i = 0; i < sp6C; i++) {
                math_mtxf2mtx(&s5[i].mtx[D_8005BFCE], &s5[i].wolrd_matrix);
            }

            func_80037788(model->unk_608, model->unk_9C8);
        } else {
            for (i = 0; i < sp6C; i++) {
                s6 = &s5[i].mtx[D_8005BFCE];
                math_mtxf2mtx(s6, &s5[i].wolrd_matrix);
                gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(s6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(D_8013C4E0[i]));
            }
        }
    } else {
        s6 = &s1->mtx[D_8005BFCE];
        math_mtxf2mtx(s6, &s1->wolrd_matrix);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(s6), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        for (i = 0; i < sp6C; i++) {
            gSPDisplayList(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(D_8013C4E0[i]));
        }
    }
}

void func_80037CE4(Object *obj) {
    ModelInstance *model;
    Transform *mu;
    UnkSam *sub2;
    s32 index;
    ModelNode *sub6;
    Batch *newvar;
    s32 sp4C;
    s32 nv2;
    BatchInfo *sub;
    s32 unused[5];
    BatchInfo *AB0;
    int temp;

    temp = obj->flags & 4; // required to match

    index = obj->spriteId;
    model = obj->modInst;
    sub2 = model->unk_A28;
    newvar = sub2->batches[index];
    sp4C = D_8005BFCE * 30 + index;

    task_execute(obj);

    if (obj->flags & 4) {
        return;
    }

    mu = &obj->transform;
    AB0 = model->unk_AB0;

    if (obj->flags & 0x2000) {
        func_80034F34(obj);
    }

    if (!(obj->flags & 0x80000)) {
        obj->rotation.x = D_8013C668.x;
        obj->rotation.y = D_8013C668.y;
    }

    math_rotate(&mu->local_matrix, &obj->rotation);
    math_translate(&mu->local_matrix, &obj->pos);
    math_mtxf_mul(&mu->local_matrix, &gCameraProjectionMatrix, &D_800813E0);

    sub = AB0 + sp4C;
    sub6 = &model->unk_A50;
    math_mtxf2mtx(&sub->transform, &D_800813E0);
    nv2 = sub2->batchCounts[index];
    model->unk_A30.unk_08[0] = sub;

    sub6->unk_28[0] = newvar;
    sub6->unk_38[0] = nv2;
    model->unk_A30.next = D_8013C4E8;
    D_8013C4E8 = &model->unk_A30;
}

#ifdef NON_EQUIVALENT
void func_80037E28(Object *obj) {
    GameMode *a2;
    ModelInstance *v1;
    UnkKappa *v0;
    u32 t6;     // sp160
    UnkSam *t0; // sp168
    u32 t2;     // sp158
    s32 sp154;
    GlobalObjD *a1;
    UnkSamSub *s0;
    Matrix4f *t4;
    u32 s7;
    s32 deltaX, deltaY, deltaZ;
    s32 absDeltaX, absDeltaY, absDeltaZ;
    s32 a22;
    s32 v05;
    s32 s00, s11, s22;
    s32 v06;
    ColorRGBA *ra;
    s32 a33, t00, t11;
    s32 temp1;
    s32 vv0, vv1, tt4;
    s32 vertId;
    s32 padding[12];
    s32 v07;
    s32 v08;
    s32 kek;
    ColorRGBA *col;
    u8 a;
    Vec4i *pos;
    s32 v12;
    s32 v02;
    Vtx *vert;
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;

    v1 = obj->modInst;
    t6 = gFrameCounter & 7;
    a2 = &gGameModes[D_8005BED0];

    t2 = v1->numNodes;
    t0 = v1->unk_A28;
    ra = &a2->unk_1C; // TODO make ColorRGBA

    v0 = a2->unk_18;
    sp6C = v0->unk_0;
    sp68 = v0->unk_1;
    sp64 = v0->unk_2;
    sp54 = v0->unk_4;
    sp50 = v0->unk_8;
    sp4C = v0->unk_C;
    sp60 = v0->unk_10;
    sp5C = v0->unk_11;
    sp58 = v0->unk_12;
    sp48 = v0->unk_14;
    sp44 = v0->unk_18;
    sp40 = v0->unk_1C;

    for (a1 = D_8013C4EC; a1 != NULL; a1 = a1->unk_2C) {
        a = a1->unk_28->unk_088.a;
        a1->unk_1C = (a1->unk_00 * a) / 256;
        a1->unk_20 = (a1->unk_04 * a) / 256;
        a1->unk_24 = (a1->unk_08 * a) / 256;
    }

    for (; t6 < t2; t6 += 8) {
        sp154 = t0->unk_394[t6];
        s0 = t0->unk_324[t6];
        t4 = &v1->transforms[t6].wolrd_matrix;

        sp90 = (s32) (v1->transforms[t6].wolrd_matrix.x.x * 1024.0f);
        sp8C = (s32) (v1->transforms[t6].wolrd_matrix.x.y * 1024.0f);
        sp88 = (s32) (v1->transforms[t6].wolrd_matrix.x.z * 1024.0f);
        sp84 = (s32) (v1->transforms[t6].wolrd_matrix.y.x * 1024.0f);
        sp80 = (s32) (v1->transforms[t6].wolrd_matrix.y.y * 1024.0f);
        sp7C = (s32) (v1->transforms[t6].wolrd_matrix.y.z * 1024.0f);
        sp78 = (s32) (v1->transforms[t6].wolrd_matrix.z.x * 1024.0f);
        sp74 = (s32) (v1->transforms[t6].wolrd_matrix.z.y * 1024.0f);
        sp70 = (s32) (v1->transforms[t6].wolrd_matrix.z.z * 1024.0f);

        for (a1 = D_8013C4EC; a1 != NULL; a1 = a1->unk_2C) {
            pos = &a1->unk_28->pos;
            absDeltaX = deltaX = pos->x - t4->w.x;
            absDeltaY = deltaY = pos->y - t4->w.y;
            absDeltaZ = deltaZ = pos->z - t4->w.z;

            if (deltaX < 0) {
                absDeltaX = -deltaX;
            }
            if (deltaY < 0) {
                absDeltaY = -deltaY;
            }
            if (deltaZ < 0) {
                absDeltaZ = -deltaZ;
            }

            v05 = DISTANCE(absDeltaX, absDeltaZ);
            temp1 = DISTANCE(v05, absDeltaY) * 128;

            a1->unk_0C = deltaX;
            a1->unk_10 = deltaY;
            a1->unk_14 = deltaZ;
            a1->unk_18 = temp1;
        }

        for (s7 = 0; s7 < sp154; s7++) {
            vv0 = s0[s7].unk_00;
            vv1 = s0[s7].unk_01;
            tt4 = s0[s7].unk_02;

            a33 = ra->r;
            t00 = ra->g;
            t11 = ra->b;

            if (vv0 & 0x80) {
                vv0 |= ~0xFF;
            }
            if (vv1 & 0x80) {
                vv1 |= ~0xFF;
            }
            if (tt4 & 0x80) {
                tt4 |= ~0xFF;
            }

            s00 = ((sp90 * vv0) >> 10) + ((sp84 * vv1) >> 10) + ((sp78 * tt4) >> 10);
            s11 = ((sp8C * vv0) >> 10) + ((sp80 * vv1) >> 10) + ((sp74 * tt4) >> 10);
            s22 = ((sp88 * vv0) >> 10) + ((sp7C * vv1) >> 10) + ((sp70 * tt4) >> 10);

            v06 = sp54 * s00 + sp50 * s11 + sp4C * s22;
            if (v06 > 0) {
                a33 += (sp6C * v06) >> 14;
                t00 += (sp68 * v06) >> 14;
                t11 += (sp64 * v06) >> 14;
            }

            v06 = sp48 * s00 + sp44 * s11 + sp40 * s22;
            if (v06 > 0) {
                a33 += (sp60 * v06) >> 14;
                t00 += (sp5C * v06) >> 14;
                t11 += (sp58 * v06) >> 14;
            }

            for (a1 = D_8013C4EC; a1 != NULL; a1 = a1->unk_2C) {
                v12 = a1->unk_18;
                v06 = a1->unk_0C * s00 + a1->unk_10 * s11 + a1->unk_14 * s22;
                if (v06 > 0) {
                    a33 += (a1->unk_1C * v06) / v12 * 2;
                    t00 += (a1->unk_20 * v06) / v12 * 2;
                    t11 += (a1->unk_24 * v06) / v12 * 2;
                }
            }

            if (a33 > 255 || t00 > 255 || t11 > 255) {
                v02 = 0;
                if (v02 < a33) {
                    v02 = a33;
                }
                if (v02 < t00) {
                    v02 = t00;
                }
                if (v02 < t11) {
                    v02 = t11;
                }

                a33 = a33 * 255 / v02;
                t00 = t00 * 255 / v02;
                t11 = t11 * 255 / v02;
            }
            a22 = 0;
            while ((kek = s0[s7].unk_44[a22]) >= 0) {
                vert = &t0->unk_04->nodes[t6].vertices[kek];
                col = &s0[s7].unk_04[a22];
                if (col->r != 255 || col->g != 255 || col->b != 255) {
                    a22++;
                } else {
                    vert->v.cn[0] = a33;
                    vert->v.cn[1] = t00;
                    vert->v.cn[2] = t11;
                    a22++;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037E28.s")
#endif

void func_800386E8(Object *obj) {
    Batch **s2;
    ModelInstance *model;
    Transform *spAC;
    s32 j;
    u32 i;
    ModelNode *new_var;
    Matrix4f *a1;
    BatchInfo *s0;
    s32 sp94;
    ModelNodeRenderInfo *renderInfo;
    s32 s6;
    Transform *objTransform;
    Matrix4f *nu;
    BatchInfo *s7;
    s32 unused[8];

    model = obj->modInst;
    spAC = model->transforms;
    s2 = model->unk_A28->batches;
    sp94 = 30 * D_8005BFCE;

    task_execute(obj);
    if (obj->flags & 4) {
        return;
    }

    objTransform = &obj->transform;

    if (obj->flags & 0x10000000) {
        func_800349F0(obj);
    }

    if ((!(obj->flags & 0x4000)) || (obj->flags & 0x10000000)) {
        func_80034AB8(obj);
    }

    func_80034F34(obj);

    if (obj->flags & 0x80000000) {
        obj->rotation.y = D_8013C668.y;
        obj->rotation.x = D_8013C668.x;
    }

    if (model->animations != NULL) {
        if (model->currentAnimId != model->unk_A0E) {
            func_80037500(obj);
            model->unk_A0E = model->currentAnimId;
        }

        if (obj->spriteId != obj->unk_086) {
            func_800371C0(obj);
            func_8003635C(obj);
            obj->unk_086 = obj->spriteId;
        }

        math_rotate(&objTransform->local_matrix, &obj->rotation);
        math_translate(&objTransform->local_matrix, &obj->pos);
        func_80014974(objTransform);

        if (model->unk_604 != NULL) {
            if (obj->flags & 0x800) {
                func_8003561C(obj, -10000);
            } else {
                func_8003561C(obj, 0);
            }

            renderInfo = model->unk_608;
            for (i = 0; i < model->unk_9C8; i++) {
                new_var = renderInfo[i].unk_04;
                if (obj->flags & 0x02000000) {
                    renderInfo[i].flags |= 2;
                }

                s6 = new_var->unk_24;
                s7 = model->unk_AB0;

                for (j = 0; j < s6; j++) {
                    s32 s1 = new_var->unk_04[j];

                    if (obj->flags & 0x01000000) {
                        a1 = &D_8013C6B0;
                    } else {
                        a1 = &gCameraProjectionMatrix;
                    }

                    if (spAC != NULL) {
                        math_mtxf_mul(&spAC[s1].wolrd_matrix, a1, &D_800813E0);
                    } else {
                        math_mtxf_mul(&model->unk_010.wolrd_matrix, a1, &D_800813E0);
                    }

                    s0 = &s7[s1 + sp94];
                    math_mtxf2mtx(&s0->transform, &D_800813E0);
                    renderInfo[i].unk_08[j] = s0;
                }
            }

            func_80037788(renderInfo, model->unk_9C8);
        }
    } else {
        s0 = model->unk_AB0;
        math_rotate(&objTransform->local_matrix, &obj->rotation);
        math_translate(&objTransform->local_matrix, &obj->pos);
        func_80014974(objTransform);
        math_mtxf_mul(&objTransform->local_matrix, &gCameraProjectionMatrix, &D_800813E0);
        math_mtxf2mtx(&(s0 + sp94)->transform, &D_800813E0);
        func_80035DF8(model->unk_A28, 0);
        (*s2)->info = s0 + sp94;
    }
}
