#include "common.h"
#include "string.h"
#include "PR/gt.h"

Unk8000C3CCArg3 D_80049920 = {
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2,
    0x2200,
    { 192, 192, 192, 255 },
    1,
};
Unk8000C3CCArg3 D_80049938 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_OPA_SURF | G_RM_OPA_SURF2,
    0x2000,
    { 255, 255, 255, 255 },
    1,
};
Unk8000C3CCArg3 D_80049950 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_XLU_SURF | G_RM_XLU_SURF2,
    0,
    { 255, 255, 255, 128 },
    0,
};
Unk8000C3CCArg3 D_80049968 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2,
    0x2000,
    { 192, 192, 192, 255 },
    0,
};
Unk8000C3CCArg3 D_80049988 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_XLU_SURF | G_RM_XLU_SURF2,
    0x2000,
    { 255, 255, 255, 255 },
    0,
};

void model_asset_detect_format(ModelAsset *, u8);

void model_node_asset_init_from_file(ModelNodeAsset *node, ModelNodeFileEntry *arg1, u32 format) {
    node->numVertices = arg1->numVertices;
    node->numTriangles = arg1->numTriangles;
    node->vertices = arg1->verticesOffset + (s32) arg1;
    node->triangles = arg1->trianglesOffset + (s32) arg1;

    if (format >= MODEL_FILE_FORMAT_V2) {
        node->numBatches = *(s32 *) (arg1->numBatchesOffset + (s32) arg1);
    }
}

s32 func_8000BD38(ModelAsset *modelAsset) {
    s32 sum = 0;
    u32 i;

    for (i = 0; i < modelAsset->numNodes; i++) {
        sum += modelAsset->nodes[i].numVertices;
    }
    return sum;
}

s32 func_8000BD70(ModelAsset *arg0) {
    s32 sum = 0;
    u32 i;

    for (i = 0; i < arg0->numNodes; i++) {
        sum += arg0->nodes[i].numTriangles;
    }
    return sum;
}

void func_8000BDA8(s32 arg0) {
}

void func_8000BDB0(ModelAsset *modelAsset, BatchAsset *batchAsset) {
    if (batchAsset->texIndex >= 0) {
        if ((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1)) {
            batchAsset->texture = (s32) modelAsset->header + batchAsset->texIndex;
        } else {
            batchAsset->texture =
                (s32) modelAsset->header + modelAsset->header->offsets[modelAsset->numNodes + batchAsset->texIndex + 1];
        }
    } else {
        batchAsset->texture = NULL;
    }
}

void model_asset_build_from_file(ModelAsset *modelAsset) {
    ModelFileHeader *header;
    s32 sp40;
    u32 i;
    ModelNodeAsset *node;
    s32 numBatches;
    u32 j;

    header = (ModelFileHeader *) D_8005AEB8[modelAsset->rawFileMemSlot].data;
    modelAsset->nodes =
        (ModelNodeAsset *) ((s32) modelAsset + sizeof(ModelAsset) + modelAsset->numNodes * sizeof(BatchAsset));
    modelAsset->header = header;

    if (!((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1))) {
        sp40 = header->offsets[modelAsset->numNodes];
    }
    modelAsset->unk_B4 = sp40;

    for (i = 0; i < modelAsset->numNodes; i++) {
        node = modelAsset->nodes + i;
        model_node_asset_init_from_file(node, (ModelNodeFileEntry *) ((s32) header + header->offsets[i]),
                                        modelAsset->fileFormat);
        if ((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1)) {
            node->batchAssets = &modelAsset->unk_CC[i];
        } else {
            node->batchAssets = (BatchAsset *) ((s32) header + header->offsets[modelAsset->numNodes + sp40 + i + 2]);
        }

        numBatches = node->numBatches;
        for (j = 0; j < numBatches; j++) {
            func_8000BDB0(modelAsset, &node->batchAssets[j]);
        }
    }

    if (!((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1))) {
        modelAsset->palettes16 = (s32) header + header->offsets[modelAsset->numNodes + sp40 + modelAsset->numNodes + 2];
        modelAsset->palettes256 =
            (s32) header + header->offsets[modelAsset->numNodes + sp40 + modelAsset->numNodes + 3];
    }

    if ((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1)) {
        if (header->offsets[2 * modelAsset->numNodes] != -1) {
            modelAsset->nodeHierarchy = (s32) header + header->offsets[2 * modelAsset->numNodes];
        } else {
            modelAsset->nodeHierarchy = NULL;
        }
    } else {
        if (header->offsets[modelAsset->numNodes + modelAsset->unk_B4 + 1] != -1) {
            modelAsset->nodeHierarchy = (s32) header + header->offsets[modelAsset->numNodes + modelAsset->unk_B4 + 1];
        } else {
            modelAsset->nodeHierarchy = NULL;
        }
    }
}

void model_asset_build_legacy_batches(ModelAsset *modelAsset, ModelFileHeader *header) {
    u32 i;
    s32 numVertices, numTriangles;

    modelAsset->nodes =
        (ModelNodeAsset *) ((s32) modelAsset + sizeof(ModelAsset) + modelAsset->numNodes * sizeof(BatchAsset));

    for (i = 0; i < modelAsset->numNodes; i++) {
        ModelNodeAsset *node = modelAsset->nodes + i;
        node->numBatches = 1;

        numVertices = ((ModelNodeFileEntry *) ((s32) header + header->offsets[i]))->numVertices;
        numTriangles = ((ModelNodeFileEntry *) ((s32) header + header->offsets[i]))->numTriangles;

        modelAsset->unk_CC[i].texIndex = header->offsets[modelAsset->numNodes + i];
        modelAsset->unk_CC[i].vertIndex = 0;
        modelAsset->unk_CC[i].triOffset = 0;
        modelAsset->unk_CC[i].numVertices = numVertices;
        modelAsset->unk_CC[i].numTriangles = numTriangles;
    }
}

void model_asset_load_from_memory_slot(ModelAsset *modelAsset, s32 rawFileMemSlot) {
    ModelFileHeader *rawFileHeader;

    modelAsset->rawFileMemSlot = rawFileMemSlot;
    rawFileHeader = D_8005AEB8[rawFileMemSlot].data;
    model_asset_detect_format(modelAsset, rawFileHeader->signature[0]);

    if ((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1)) {
        model_asset_build_legacy_batches(modelAsset, rawFileHeader);
    }

    model_asset_build_from_file(modelAsset);
}

void model_asset_detect_format(ModelAsset *modelAsset, u8 firstChar) {
    switch (firstChar) {
        case '@':
            modelAsset->fileFormat = MODEL_FILE_FORMAT_V1;
            break;
        case '2':
            modelAsset->fileFormat = MODEL_FILE_FORMAT_V2;
            break;
    }
}

void func_8000C18C(s32 *new_data, s32 *old_data, void *priv) {
    s32 i;
    u32 size = (u32) priv;
    s32 delta = (u32) new_data - (u32) old_data;

    for (i = 0; i < size; i++) {
        new_data[i] += delta;
    }
}

void func_8000C1C4(KModel *arg0, s32 arg1) {
    ModelNodeAsset *v0 = &arg0->model.unk_04->nodes[arg1];
    u32 numParts = v0->numBatches;
    u32 numVertices = v0->numVertices;
    u32 unk_04 = v0->numTriangles;
    s32 size;

    size = numParts * sizeof(Gfx) * 21 + (numVertices / 8) * sizeof(Gfx) + unk_04 * sizeof(Gfx); // TODO constant
    arg0->model.dlist[arg1] = mem_alloc(size, "kmd.c", 297);
    arg0->unk_A64 = size;
}

s32 func_8000C258(u16 *arg0, u32 arg1, s32 arg2) {
    u32 i;

    for (i = 0; i < arg2 * 3; i++) {
        if (arg1 > arg0[i]) {
            arg1 = arg0[i];
        }
        if (arg0[i] * 0) {} // @fake
    }

    return arg1;
}

void func_8000C328(Vec3su *arg0, u32 arg1, u32 arg2, s32 *arg3, s32 *arg4) {
    u32 v0;

    *arg3 = *arg4 = 0;
    v0 = arg1;

    while (arg2) {
        if (arg0->vi[0] > arg1 + 15 || arg0->vi[1] > arg1 + 15 || arg0->vi[2] > arg1 + 15) {
            break;
        }
        if (v0 < arg0->vi[0]) {
            v0 = arg0->vi[0];
        }
        if (v0 < arg0->vi[1]) {
            v0 = arg0->vi[1];
        }
        if (v0 < arg0->vi[2]) {
            v0 = arg0->vi[2];
        }

        arg2--;
        arg0++;
        (*arg3)++;
    }

    *arg4 = v0 - arg1 + 1;
}

void func_8000C3CC(Model *arg0, s32 nodeId, u8 arg2, Unk8000C3CCArg3 *arg3) {
    u32 partIndex;
    s32 numVerts;
    BatchTriangle *triangle;
    u32 numParts;
    Gfx *gfx;
    s32 partLastBatch;
    s32 partFirstBatch;
    s32 sp940;
    s32 sp93C;
    s32 numTriangles;
    BatchInfo *batchInfos;
    u8 sp933;
    u8 sp932;
    s32 v02;
    Vec3su *triangles;
    s32 padding[4];
    Vtx *vertices;
    Vtx *a11;
    s32 padding2;
    s32 vertIndex;
    Vec3su *triPtr;
    s32 size;
    BatchTriangle *triangleBuffer[100];
    s32 numTriBuffer[100];
    s32 numVertBuffer[100];
    u32 numBatches;
    Vtx *vertexBuffer[100];
    s32 sp2B8;
    u32 i;
    BatchAsset *nodeBatch;
    TextureAsset *tex;
    s32 sp11C[100];
    Batch *batchArray;
    s32 padding3[2];
    u8 *pal16;
    u8 *pal256;
    ModelNodeAsset *node;

    sp933 = FALSE;
    sp932 = FALSE;
    numBatches = 0;

    node = &arg0->unk_04->nodes[nodeId];
    numParts = node->numBatches;
    numVerts = node->numVertices;
    vertices = node->vertices;
    triangles = node->triangles;

    if (arg0->unk_318) {
        for (i = 0; i < numVerts; i++) {
            vertices[i].v.tc[0] >>= 1;
            vertices[i].v.tc[1] >>= 1;
        }
    }

    for (partIndex = 0; partIndex < numParts; partIndex++) {
        nodeBatch = node->batchAssets + partIndex;
        numTriangles = nodeBatch->numTriangles;
        vertIndex = nodeBatch->vertIndex;
        numVerts = nodeBatch->numVertices;
        triPtr = triangles;
        triPtr += nodeBatch->triOffset;

        sp11C[partIndex] = numBatches;

        if (numVerts <= 16U) {
            triangle = triangleBuffer[numBatches] = mem_alloc(numTriangles * sizeof(BatchTriangle), "kmd.c", 421);
            for (i = 0; i < numTriangles; triPtr++, i++) {
                triangle[i].vi0 = triPtr->vi[0] - vertIndex;
                triangle[i].vi1 = triPtr->vi[1] - vertIndex;
                triangle[i].vi2 = triPtr->vi[2] - vertIndex;
                triangle[i].d = 0;
            }
            numTriBuffer[numBatches] = numTriangles;
            vertexBuffer[numBatches] = vertices;
            vertexBuffer[numBatches] += vertIndex;
            numVertBuffer[numBatches] = numVerts;
            numBatches++;
        } else {
            do {
                vertIndex = func_8000C258(triPtr, vertIndex, numTriangles);
                vertexBuffer[numBatches] = vertices;
                vertexBuffer[numBatches] += vertIndex;
                func_8000C328(triPtr, vertIndex, numTriangles, &sp93C, &sp940);
                numTriangles -= sp93C;
                numTriBuffer[numBatches] = sp93C;
                numVertBuffer[numBatches] = sp940;
                triangle = triangleBuffer[numBatches] = mem_alloc(sp93C * sizeof(BatchTriangle), "kmd.c", 449);
                numBatches++;

                for (i = 0; i < sp93C; i++, triPtr++) {
                    triangle[i].vi0 = triPtr->vi[0] - vertIndex;
                    triangle[i].vi1 = triPtr->vi[1] - vertIndex;
                    triangle[i].vi2 = triPtr->vi[2] - vertIndex;
                    triangle[i].d = 0;
                }
                vertIndex += sp940;
            } while (numTriangles != 0);
        }
    }

    batchArray = arg0->batches[nodeId] = (Batch *) mem_alloc(numBatches * sizeof(Batch), "kmd.c", 469);
    batchInfos = arg0->batchInfos[nodeId] = (BatchInfo *) mem_alloc(numBatches * sizeof(BatchInfo), "kmd.c", 470);

    for (i = 0; i < numBatches; i++) {
        batchArray[i].context = NULL;
        batchArray[i].vertices = vertexBuffer[i];
        batchArray[i].triangles = triangleBuffer[i];
        sp2B8 += numTriBuffer[i] * 4; // ??
        batchArray[i].info = batchInfos + i;

        mem_fill(batchInfos + i, 0, sizeof(BatchInfo));
        (batchInfos + i)->header.triMask = arg3->triMask;
        (batchInfos + i)->header.unk_04 = 0;
        (batchInfos + i)->header.vtxNum = numVertBuffer[i];
        (batchInfos + i)->header.vtxOffset = 0;
        (batchInfos + i)->header.numTriangles = numTriBuffer[i];
        (batchInfos + i)->header.unk_0B = (i != 0) ? 1 : 0;
        (batchInfos + i)->header.texGfx = NULL;
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_RENDERMODE, arg3->renderMode);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTFILT, G_TF_BILERP);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTCONV, G_TC_FILT);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);
    }
    arg0->batchCounts[nodeId] = numBatches;

    size = 22 * sizeof(Gfx) * numParts; // TODO: make constant
    gfx = (Gfx *) mem_alloc(size, "kmd.c", 501);
    mem_fill(gfx, 0, size);
    for (partIndex = 0; partIndex < numParts; partIndex++) {
        nodeBatch = node->batchAssets + partIndex;
        partFirstBatch = sp11C[partIndex];
        partLastBatch = (partIndex + 1 < numParts) ? sp11C[partIndex + 1] : numBatches;

        batchArray[partFirstBatch].info->header.texGfx = gfx;
        if (partIndex == 0 && !(arg3->flags & 1)) {
            gDPSetPrimColor(gfx++, 0, 0, arg3->primColor.r, arg3->primColor.g, arg3->primColor.b, arg3->primColor.a);
        }
        if (!sp933 && !((u8) (nodeBatch->texIndex >= 0))) {
            gDPPipeSync(gfx++);
            gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
            sp933 = TRUE;
            sp932 = FALSE;
        } else if (!sp932 && (u8) (nodeBatch->texIndex >= 0)) {
            gDPPipeSync(gfx++);
            gfx->words.w0 = arg3->combineMode.words.w0;
            gfx->words.w1 = arg3->combineMode.words.w1;
            gfx++;
            sp933 = FALSE;
            sp932 = TRUE;
        }

        if (sp932) {
            for (i = partFirstBatch; i < partLastBatch; i++) {
                batchArray[i].info->header.triMask |= G_RDP_TRI_TXTR_MASK;
            }

            numVerts = nodeBatch->numVertices;
            a11 = vertices;
            a11 += nodeBatch->vertIndex;
            for (i = 0; i < numVerts; i++) {
                a11[i].v.cn[0] = a11[i].v.cn[1] = a11[i].v.cn[2] = 255;
            }

            tex = nodeBatch->texture;
            if (tex->format == 4) {
                if (!arg2) {
                    pal16 = arg0->unk_04->palettes16 + tex->palIndex * 0x20;
                    pal16[1] &= ~1;
                    gDPLoadTLUT_pal16(gfx++, 0, VIRTUAL_TO_PHYSICAL(pal16));
                }
                gDPLoadTextureBlock_4b(gfx++, tex->data, G_IM_FMT_CI, tex->width, tex->height, 0,
                                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                if (!arg2) {
                    pal256 = arg0->unk_04->palettes256 + tex->palIndex * 0x200;
                    pal256[1] &= ~1;
                    gDPLoadTLUT_pal256(gfx++, VIRTUAL_TO_PHYSICAL(pal256));
                }
                gDPLoadTextureBlock(gfx++, tex->data, G_IM_FMT_CI, G_IM_SIZ_8b, tex->width, tex->height, 0,
                                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
            }
        }
        gSPNoOp(gfx++);
    }
}

void func_8000D11C(KModel *arg0, s32 arg1, u8 arg2) {
    u32 sp154;
    Vtx *fp;
    Vtx *s7;
    s32 sp148;
    Vec3su *s1;
    Gfx *s3;
    u32 s0;
    s32 sp138;
    u32 sp134;
    BatchAsset *a1;
    s32 s2;
    u8 sp12B;
    u8 sp12A;
    s32 s6;
    Vec3su *sp120;
    s32 t3;
    TextureAsset *a2;
    u8 *pal16;
    u8 *pal256;
    s32 padding[3];
    u16 *pz1;
    u16 *pz2;
    ModelNodeAsset *v0;

    sp12B = FALSE;
    sp12A = FALSE;
    s3 = arg0->model.dlist[arg1];
    v0 = &arg0->model.unk_04->nodes[arg1];
    sp148 = v0->numBatches;
    fp = v0->vertices;
    sp120 = v0->triangles;

    for (sp154 = 0; sp154 < sp148; sp154++) {
        a1 = &v0->batchAssets[sp154];

        s6 = a1->numTriangles;
        t3 = a1->numVertices;
        s1 = sp120;
        s1 += a1->triOffset;

        s2 = a1->vertIndex;
        s7 = fp;
        s7 += a1->vertIndex;

        if (!sp12B && !((u8) (a1->texIndex >= 0))) {
            gDPPipeSync(s3++);
            gSPTexture(s3++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
            gDPSetCombineMode(s3++, G_CC_SHADE, G_CC_SHADE);
            sp12B = TRUE;
            sp12A = FALSE;
        } else if (!sp12A && ((u8) (a1->texIndex >= 0))) {
            gDPPipeSync(s3++);
            gSPTexture(s3++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
            gDPSetCombineMode(s3++, G_CC_DECALRGB, G_CC_DECALRGB);
            sp12A = TRUE;
            sp12B = FALSE;
        }

        if (sp12A) {
            a2 = a1->texture;
            if (a2->format == 4) {
                if (!arg2) {
                    pal16 = arg0->model.unk_04->palettes16 + a2->palIndex * 0x20;
                    gDPLoadTLUT_pal16(s3++, 0, VIRTUAL_TO_PHYSICAL(pal16));
                }
                gDPLoadTextureBlock_4b(s3++, a2->data, G_IM_FMT_CI, a2->width, a2->height, 0,
                                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                if (!arg2) {
                    pal256 = arg0->model.unk_04->palettes256 + a2->palIndex * 0x200;
                    gDPLoadTLUT_pal256(s3++, VIRTUAL_TO_PHYSICAL(pal256));
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
                s2 = func_8000C258(s1, s2, s6);
                s7 = fp;
                s7 += s2;
                func_8000C328(s1, s2, s6, &sp134, &sp138);
                gSPVertex(s3++, s7, sp138, 0);
                s6 -= sp134;
                for (s0 = 0; s0 < sp134; s0++) {
                    gSP1Triangle(s3++, s1->vi[0] - s2, s1->vi[1] - s2, s1->vi[2] - s2, 0);
                    s1++;
                }
                s2 += sp138;
            } while (s6 != 0);
        }
    }

    gSPEndDisplayList(s3++);
}

void func_8000DAB0(KModel *arg0, ModelAsset *arg1, char *name, u8 arg3, s32 arg4) {
    u32 i;
    Asset *asset;
    char sp30[16];
    s32 v0;

    arg0->model.unk_04 = arg1;
    arg0->model.numNodes = arg1->numNodes;

    for (i = 0; i < arg0->model.numNodes; i++) {
        func_8000C1C4(arg0, i);
        func_8000D11C(arg0, i, arg3);
    }

    arg0->model.nodeHierarchy = v0 = arg0->model.unk_04->nodeHierarchy;

    if (v0 != 0) {
        str_copy(sp30, name);
        sp30[3] = '\0';
        str_concat(sp30, "_anm.anm");
        asset = &gAssets[asset_find(sp30, arg4)];
        arg0->model.animations = D_8005AEB8[asset->memory_slot].data;
        arg0->model.unk_14C = asset->aux_data;
        heap_set_move_callback(asset->memory_slot, func_8000C18C, arg0->model.unk_14C);
    } else {
        arg0->model.animations = NULL;
    }
}

s32 func_8000DBC4(Model *arg0, s32 arg1, s16 *arg2) {
    ModelNodeAsset *a3;
    s32 t4;
    u32 i;
    u32 j;
    u32 t5;
    Vtx *t3;
    UnkSamSub *sub;
    s16 a2;

    t4 = 0;
    a3 = &arg0->unk_04->nodes[arg1];
    t5 = a3->numVertices;

    for (i = 0; i < t5; i++) {
        arg2[i] = i;
    }

    t3 = a3->vertices;

    for (i = 0; i < t5 - 1; i++) {
        if (arg2[i] == i) {
            t4++;
            for (j = 1; j < t5; j++) {
                if (t3[i].v.ob[0] == t3[j].v.ob[0] && t3[i].v.ob[1] == t3[j].v.ob[1] &&
                    t3[i].v.ob[2] == t3[j].v.ob[2]) {
                    arg2[j] = t4 - 1;
                }
            }
        }
    }

    sub = mem_alloc(t4 * sizeof(UnkSamSub), "kmd.c", 761);
    arg0->unk_324[arg1] = sub;
    arg0->unk_394[arg1] = t4;

    for (i = 0; i < t4; i++) {
        a2 = 0;
        for (j = 0; j < t5; j++) {
            if (arg2[j] == i) {
                sub[i].unk_04[a2].r = t3[j].v.cn[0];
                sub[i].unk_04[a2].g = t3[j].v.cn[1];
                sub[i].unk_04[a2].b = t3[j].v.cn[2];
                sub[i].unk_44[a2++] = j;
                sub[i].unk_44[a2] = -1;
            }
        }
    }

    return t4;
}

void func_8000DF5C(f32 *arg0) {
    f32 mag;

    mag = sqrtf(SQ(arg0[0]) + SQ(arg0[1]) + SQ(arg0[2]));
    if (mag != 0.0f) {
        arg0[0] /= mag;
        arg0[1] /= mag;
        arg0[2] /= mag;
    } else {
        arg0[0] = arg0[2] = 0.0f;
        arg0[1] = -1.0f;
    }
}

s32 func_8000DFF0(u32 arg0, u32 arg1, u16 *arg2, Vec3f *arg3, u32 arg4, u16 *arg5) {
    u32 i;
    s32 j;
    Vec3f *pos1 = &arg3[arg1];

    arg2 += 3 * arg1 + 3;
    for (i = arg1 + 1; i < arg4; i++, arg2 += 3) {
        for (j = 0; j < 3; j++) {
            if (arg0 == arg5[arg2[j]]) {
                if (pos1->x == arg3[i].x && pos1->y == arg3[i].y && pos1->z == arg3[i].z) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

void func_8000E0D8(Model *arg0) {
    u32 i;
    u32 sp110;
    u32 s0;
    u32 s1;
    ModelNodeAsset *s6;
    Vtx *s00;
    Vec3su *s4;
    u16 j;
    u16 k;
    u16 l;
    Vec3s *vec;
    UnkSamSub *sub;
    Vec3f *spE8;
    Vec3f *fp;
    s32 padding3[2];
    Vec3f *vec2;
    f32 x, y, z;
    s16 spCA;
    s16 *spC4;
    Vec3s spBC;
    s32 padding2;
    u16 s5;
    s16 temp;
    f32 fv0;
    Vtx *v0;
    Vtx *v1;
    Vtx *a1;
    f32 sp98[3];

    s0 = 0;
    s1 = 0;
    for (i = 0; i < arg0->numNodes; i++) {
        s6 = &arg0->unk_04->nodes[i];
        if (s0 < s6->numVertices) {
            s0 = s6->numVertices;
        }
        if (s1 < s6->numTriangles) {
            s1 = s6->numTriangles;
        }
    }

    spE8 = mem_alloc(s0 * 12, "kmd.c", 854);
    fp = mem_alloc(s1 * 12, "kmd.c", 855);
    spC4 = mem_alloc(s0 * 2, "kmd.c", 856);
    mem_fill(spE8, 0, s0 * 12);
    mem_fill(fp, 0, s1 * 12);

    for (i = 0; i < arg0->numNodes; i++) {
        spCA = func_8000DBC4(arg0, i, spC4);
        s6 = &arg0->unk_04->nodes[i];
        s5 = s6->numTriangles;
        s00 = s6->vertices;
        s4 = s6->triangles;

        for (j = 0; j < s5; j++, s4++) {
            a1 = s00;
            a1 += s4->vi[0];
            v0 = s00;
            v0 += s4->vi[1];
            v1 = s00;
            v1 += s4->vi[2];

            sp98[0] = a1->v.ob[1] * (v0->v.ob[2] - v1->v.ob[2]) + v0->v.ob[1] * (v1->v.ob[2] - a1->v.ob[2]) +
                      v1->v.ob[1] * (a1->v.ob[2] - v0->v.ob[2]);
            sp98[1] = a1->v.ob[2] * (v0->v.ob[0] - v1->v.ob[0]) + v0->v.ob[2] * (v1->v.ob[0] - a1->v.ob[0]) +
                      v1->v.ob[2] * (a1->v.ob[0] - v0->v.ob[0]);
            sp98[2] = a1->v.ob[0] * (v0->v.ob[1] - v1->v.ob[1]) + v0->v.ob[0] * (v1->v.ob[1] - a1->v.ob[1]) +
                      v1->v.ob[0] * (a1->v.ob[1] - v0->v.ob[1]);
            func_8000DF5C(sp98);
            fp[j].x = sp98[0];
            fp[j].y = sp98[1];
            fp[j].z = sp98[2];
        }

        for (k = 0; k < spCA; k++) {
            s4 = s6->triangles;
            for (j = 0; j < s5; j++, s4++) {
                vec2 = fp;
                vec2 += j;
                for (l = 0; l < 3; l++) {
                    if (k == spC4[s4->vi[l]] && func_8000DFF0(k, j, s6->triangles, fp, s5, spC4) == 0) {
                        spE8[k].x += vec2->x;
                        spE8[k].y += vec2->y;
                        spE8[k].z += vec2->z;
                    }
                }
            }
        }

        sub = arg0->unk_324[i];
        vec = &spBC;
        for (sp110 = 0; sp110 < spCA; sp110++) {
            x = spE8[sp110].x;
            y = spE8[sp110].y;
            z = spE8[sp110].z;
            fv0 = sqrtf(SQ(x) + SQ(y) + SQ(z));
            if (fv0 != 0) {
                spE8[sp110].x /= fv0;
                spE8[sp110].y /= fv0;
                spE8[sp110].z /= fv0;
            } else {
                spE8[sp110].x = spE8[sp110].y = spE8[sp110].z = 0.0;
            }

            vec->x = temp =
                ((spE8[sp110].x * 128.0f) >= 0.0) ? ((spE8[sp110].x * 128.0f) + 0.5) : ((spE8[sp110].x * 128.0f) - 0.5);
            if (temp > 127) {
                vec->x = 127;
            }
            vec->y = temp =
                ((spE8[sp110].y * 128.0f) >= 0.0) ? ((spE8[sp110].y * 128.0f) + 0.5) : ((spE8[sp110].y * 128.0f) - 0.5);
            if (temp > 127) {
                vec->y = 127;
            }
            vec->z = temp =
                ((spE8[sp110].z * 128.0f) >= 0.0) ? ((spE8[sp110].z * 128.0f) + 0.5) : ((spE8[sp110].z * 128.0f) - 0.5);
            if (temp > 127) {
                vec->z = 127;
            }

            sub[sp110].unk_00 = vec->x;
            sub[sp110].unk_01 = vec->y;
            sub[sp110].unk_02 = vec->z;
        }
    }

    mem_free(spE8);
    mem_free(fp);
    mem_free(spC4);
}

void func_8000E73C(Model *arg0, ModelAsset *arg1, char *name, u8 arg3, Unk8000C3CCArg3 *arg4, s32 arg5) {
    u32 i;
    s32 v1;
    s32 j;
    s32 padding2;
    char sp48[16];
    char padding[16];

    arg0->unk_04 = arg1;
    arg0->numNodes = arg1->numNodes;
    arg0->unk_318 = arg1->unk_C8;
    arg0->unk_320 = 0;
    arg0->unk_321 = 0;
    arg0->unk_322 = 0;

    for (i = 0; i < arg0->numNodes; i++) {
        func_8000C3CC(arg0, i, arg3, arg4);
    }

    if (arg0->unk_04->nodeHierarchy != NULL) {
        arg0->nodeHierarchy = mem_alloc(arg0->numNodes * 0x10 + 0x10, "kmd.c", 983);
        memcpy(arg0->nodeHierarchy, arg0->unk_04->nodeHierarchy, arg0->numNodes * 0x10 + 0x10);
    } else {
        arg0->nodeHierarchy = NULL;
    }

    str_copy(sp48, name);
    for (j = 0; sp48[j] != '\0' && j < 16;) {
        if (sp48[j++] == '.') {
            sp48[j - 1] = '\0';
            break;
        }
    }

    str_concat(sp48, "_anm.anm");
    v1 = asset_find(sp48, arg5);

    if (v1 < 0) {
        str_copy(sp48, name);
        sp48[3] = '\0';
        str_concat(sp48, "_anm.anm");
        v1 = asset_find(sp48, arg5);
    }

    if (v1 >= 0) {
        arg0->animations = D_8005AEB8[gAssets[v1].memory_slot].data;
        arg0->unk_14C = gAssets[v1].aux_data;
        heap_set_move_callback(gAssets[v1].memory_slot, func_8000C18C, arg0->unk_14C);
    } else {
        arg0->animations = NULL;
    }
}
