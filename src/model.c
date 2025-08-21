#include "common.h"
#include "task.h"
#include "camera.h"
#include "string.h"
#include "PR/gt.h"

typedef struct GlobalObjD {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ char unk_0C[0x1C];
    /* 0x2C */ Object *unk_28;
    /* 0x2C */ struct GlobalObjD *unk_2C;
    /* 0x30 */ struct GlobalObjD *unk_30;
} GlobalObjD; // size = 0x34

extern ModelNodeRenderInfo *D_8013C4E8;
extern u32 D_8013C540;
extern K2Def D_80053010;
extern Vec4i D_8004934C;
extern Batch **D_8013C4E0;
extern GlobalObjD *D_8013C4EC;
extern ItemPool D_8013C4F0;
extern AssetGmdSub4 *D_8013C500[];

Object *func_8002BC84(Vec4i *, s32, K2Def *, s32);
void func_800028E0(s32 arg0, s32 arg1);

void func_80034090(AssetGmdSub4 *arg0) {
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
    AssetGmdSub4 *v1;
    u32 tmp;
    u32 a3;
    u32 *ptr;
    u32 q;

    for (i = 0; i < D_8013C540; i++) {
        v1 = D_8013C500[i];
        tmp = (v1->unk_00 * v1->unk_04) / 8;
        ptr = v1->unk_10;
        a3 = v1->unk_10[0];

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
    AssetGmdSub4 *v1;
    u32 tmp;
    u32 a3;
    u32 *ptr;
    u32 q;

    if (gFrameCounter & 1) {
        return 1;
    }

    for (i = 0; i < D_8013C540; i++) {
        v1 = D_8013C500[i];
        tmp = v1->unk_00 / 8;
        ptr = v1->unk_10;

        for (j = 0; j < v1->unk_04; j++) {
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
    Model *model = obj->model;
    UnkSam *sam = model->unk_A28;
    s32 numNodes = model->numNodes;
    u32 i, j;
    AssetGmdSub2 *s1;
    s32 s2;
    AssetGmdSub1 *sub1;

    if (D_8013C540 == 0) {
        if (arg1) {
            func_800028E0(func_800340E8, 0);
        } else {
            func_800028E0(func_8003424C, 0);
        }
    }

    for (i = 0; i < numNodes; i++) {
        s1 = &sam->unk_04->unk_04[i];
        s2 = s1->unk_18;
        for (j = 0; j < s2; j++) {
            sub1 = s1->unk_1C + j;
            if ((u8) (sub1->unk_00 >= 0)) {
                func_80034090(sub1->unk_0C);
            }
        }
    }

    obj->flags |= 0x2000;
}

void func_80034508(void) {
    D_8013C4EC = NULL;
    func_8002A8C0(&D_8013C4F0, 5, sizeof(GlobalObjD));
}

void func_8003453C(Object *obj, u8 *arg1) {
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
    objD->unk_00 = arg1[0];
    objD->unk_04 = arg1[1];
    objD->unk_08 = arg1[2];
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
    Gfx *gfx = &arg0->header.unk_10;

    func_80000E0C(gfx, 0, sizeof(Gfx));

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
    Gfx *gfx = &arg0->header.unk_10;

    func_80000E0C(gfx, 0, sizeof(Gfx));
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
    Model *model;
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
    model = obj->model;
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

        array = s4->unk_2A8[i];
        for (j = 1; j < s4->unk_238[i]; j++) {
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
    Model *model = obj->model;
    s32 count = model->numNodes;
    u8 *buffer = model->unk_1F6E;

    for (i = 0; i < count; i++) {
        buffer[i] = 1;
    }
}

void func_80034A58(Object *obj) {
    Model *model = obj->model;
    u32 i;
    s32 a2 = model->numNodes;
    u8 *ptr2 = model->unk_1F6E;

    for (i = 0; i < a2; i++) {
        ptr2[i] = 0;
    }
}

void func_80034AB8(Object *obj) {
    Model *model = obj->model;
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
    Model *model = obj->model;
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
    Model *model = obj->model;
    ColorRGBA *color;
    u8 v1 = obj->unk_088.a;
    u32 i;
    u32 count = model->numNodes;
    UnkSam *sam = model->unk_A28;
    Batch *disp;
    Gfx *gfx;

    for (i = 0; i < count; i++) {
        disp = sam->unk_154[i];
        gfx = disp->info->header.unk_0C;
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

void func_80034FC8(Model *model, s32 arg1, Vec4i *arg2) {
    AssetGmdSub2 *a1;
    s32 a, b, c;
    s32 i, count;
    AssetGmdSub3 *array;

    a = 0;
    b = 0;
    c = 0;

    if (model->unk_A24 != NULL) {
        a1 = &model->unk_A24->sam.unk_04->unk_04[arg1];
    } else {
        a1 = &model->unk_A28->unk_04->unk_04[arg1];
    }

    count = a1->unk_00;
    array = a1->unk_08;

    for (i = 0; i < count; i++) {
        a += array[i].unk_00.x;
        b += array[i].unk_00.y;
        c += array[i].unk_00.z;
    }

    arg2->x = a / count;
    arg2->y = b / count;
    arg2->z = c / count;
}

void func_8003517C(UnkSam *sam, s32 arg1, Vec4i *arg2) {
    AssetGmdSub2 *a1;
    s32 a, b, c;
    s32 i, count;
    AssetGmdSub3 *array;

    a = 0;
    b = 0;
    c = 0;

    a1 = &sam->unk_04->unk_04[arg1];

    count = a1->unk_00;
    array = a1->unk_08;

    for (i = 0; i < count; i++) {
        a += array[i].unk_00.x;
        b += array[i].unk_00.y;
        c += array[i].unk_00.z;
    }

    arg2->x = a / count;
    arg2->y = b / count;
    arg2->z = c / count;
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/D_800551D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800352FC.s")

void func_8003561C(Object *obj, s32 arg1) {
    Model *model;
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

    model = obj->model;
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

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800359E4.s")

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
    var1 = arg0->unk_154;
    for (i = 0; i < count; i++, s1++) {
        s1->unk_00 = temp;

        func_8003517C(arg0, i, &sp58);
        s1->unk_14.x = sp58.x;
        s1->unk_14.y = sp58.y;
        s1->unk_14.z = sp58.z;

        s1->unk_04[0] = i;
        s1->unk_08 = -1;
        s1->unk_20 = i;
        s1->unk_24 = temp;

        temp2 = 1; // required to match
        for (j = 0; j < temp2; j++) {
            s32 v0 = s1->unk_04[j];
            s1->unk_28[j] = var1[v0];
            s1->unk_38[j] = arg0->unk_238[v0];
        }
    }
}

void func_80035DF8(UnkSam *arg0, s32 arg1) {
    u32 i;
    s32 a2;
    Batch *v0;

    v0 = arg0->unk_154[arg1];
    a2 = arg0->unk_238[arg1];

    for (i = 0; i < a2; i++) {
        gSPTriBatch(gMainBatchPos, NULL, v0->info, v0->vertices, v0->triangles);
        v0++;
    }
}

void func_80035F5C(Object *obj) {
    Model *model;
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

    model = obj->model;
    trans = model->transforms;
    parent = (Object *) obj->vars[1];
    newvar = &obj->transform.local_matrix;
    sub3 = model->unk_A28->unk_154;

    if (parent->flags & 0x4) {
        return;
    }

    D_8013C4E0 = model->unk_A24->sam.unk_154;
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

void func_80036194(Object *arg0, char *arg1, s32 arg2) {
    Object *v0;

    str_copy(D_80053010.unk_00, arg1);
    v0 = func_8002BC84(&D_8004934C, 0, &D_80053010, arg2);

    v0->vars[0] = v0->model->transforms;
    v0->vars[1] = arg0;
    v0->model->transforms = arg0->model->transforms;
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

    s0 = &arg1->unk_00[D_8005BFCE];
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
    Model *model = obj->model;
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
    Model *model;

    nodeId = arg0[2];
    model = obj->model;

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
    Model *model;

    nodeId = script[2];
    model = obj->model;

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
    Model *model;
    Vec4s *temp;

    nodeId = arg0[2];
    model = obj->model;
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
    Model *model = obj->model;
    s32 lerp = FALSE;

    if (obj->spriteId & 1) {
        lerp = TRUE;
    }
    animFrame = (obj->spriteId + 1) >> 1;

    script = model->unk_A14;
    while (*(s32 *) script != -1) {
        s32 frameStart = script[0];
        s32 frameEnd = script[1];

        if (animFrame > frameEnd || animFrame < frameStart) {
            if (script[3] & 0xF) {
                script += frameEnd * 2 - frameStart * 2 + 6;
                if ((s32) script & 3) {
                    script += 2;
                }
            } else {
                script += frameEnd - frameStart + 5;
                while ((s32) script & 3) {
                    script++;
                }
            }
        } else {
            if (script[3] & 0xF) {
                if (lerp) {
                    model_anim_param_lerp(script, script + 4 + animFrame * 2 - frameStart * 2, obj);
                } else {
                    model_anim_param_set(script, script + 4 + animFrame * 2 - frameStart * 2, obj);
                }
                script += frameEnd * 2 - frameStart * 2 + 6;
                if ((s32) script & 3) {
                    script += 2;
                }
            } else {
                model_anim_param_add(script, script + 4 + animFrame - frameStart, obj);
                script += frameEnd - frameStart + 5;
                while ((s32) script & 3) {
                    script++;
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037394.s")
/*
u16 func_80037394(Model *model, s16 arg1) {
    u8 v1;

    v1 = *(model->unk_12C[arg1] + 1);

    if ((v1 & 0xF0) != 0 && (v1 & 0x0F) != 0) {
        model->unk_A08 = (u8) (*model->unk_12C[arg1]) * ((v1 & 0xF0) >> 4);
    } else {
        model->unk_A08 = (u8) (*model->unk_12C[arg1]) * 2;
    }

    return model->unk_A08;
}
    */

void func_800373FC(Object *obj) {
    Model *model = obj->model;
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
    Model *model = obj->model;
    s32 v1;
    u32 i;
    u32 j;
    s32 v12;

    model->unk_00C = 0;
    model->unk_A14 = model->unk_12C[model->unk_A0C] + 1;
    v1 = model->unk_A14[3];
    if ((v1 & 0xF0) != 0 && (v1 & 0x0F) != 0) {
        model->unk_A08 = ((u8 *) (model->unk_12C[model->unk_A0C]))[3] * ((v1 & 0xF0) >> 4);
    } else {
        model->unk_A08 = ((u8 *) (model->unk_12C[model->unk_A0C]))[3] * 2;
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

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003795C.s")

void func_80037CE4(Object *obj) {
    Model *model;
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
    model = obj->model;
    sub2 = model->unk_A28;
    newvar = sub2->unk_154[index];
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
    nv2 = sub2->unk_238[index];
    model->unk_A30.unk_08[0] = sub;

    sub6->unk_28[0] = newvar;
    sub6->unk_38[0] = nv2;
    model->unk_A30.next = D_8013C4E8;
    D_8013C4E8 = &model->unk_A30;
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037E28.s")

void func_800386E8(Object *obj) {
    Batch **s2;
    Model *model;
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

    model = obj->model;
    spAC = model->transforms;
    s2 = model->unk_A28->unk_154;
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

    if (model->unk_12C != NULL) {
        if (model->unk_A0C != model->unk_A0E) {
            func_80037500(obj);
            model->unk_A0E = model->unk_A0C;
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
