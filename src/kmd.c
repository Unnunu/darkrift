#include "common.h"
#include "string.h"
#include "PR/gt.h"

ModelRenderSettings sRenderSettingsTmd = {
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2,
    0x2200,
    { 192, 192, 192, 255 },
    1,
};
ModelRenderSettings sRenderSettingsK4 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_OPA_SURF | G_RM_OPA_SURF2,
    0x2000,
    { 255, 255, 255, 255 },
    1,
};
ModelRenderSettings sRenderSettingsK2K5SP3 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_XLU_SURF | G_RM_XLU_SURF2,
    0,
    { 255, 255, 255, 128 },
    0,
};
ModelRenderSettings sRenderSettingsK3 = {
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2,
    0x2000,
    { 192, 192, 192, 255 },
    0,
};
ModelRenderSettings D_80049988 = {
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

s32 model_asset_get_total_vertex_count(ModelAsset *modelAsset) {
    s32 sum = 0;
    u32 i;

    for (i = 0; i < modelAsset->numNodes; i++) {
        sum += modelAsset->nodes[i].numVertices;
    }
    return sum;
}

s32 model_asset_get_total_triangle_count(ModelAsset *modelAsset) {
    s32 sum = 0;
    u32 i;

    for (i = 0; i < modelAsset->numNodes; i++) {
        sum += modelAsset->nodes[i].numTriangles;
    }
    return sum;
}

void func_8000BDA8(s32 arg0) {
}

void model_asset_resolve_batch_texture(ModelAsset *modelAsset, BatchAsset *batchAsset) {
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
    s32 numTextures;
    u32 i;
    ModelNodeAsset *node;
    s32 numBatches;
    u32 j;

    header = (ModelFileHeader *) D_8005AEB8[modelAsset->rawFileMemSlot].data;
    modelAsset->nodes =
        (ModelNodeAsset *) ((s32) modelAsset + sizeof(ModelAsset) + modelAsset->numNodes * sizeof(BatchAsset));
    modelAsset->header = header;

    if (!((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1))) {
        numTextures = header->offsets[modelAsset->numNodes];
    }
    modelAsset->numTextures = numTextures;

    for (i = 0; i < modelAsset->numNodes; i++) {
        node = modelAsset->nodes + i;
        model_node_asset_init_from_file(node, (ModelNodeFileEntry *) ((s32) header + header->offsets[i]),
                                        modelAsset->fileFormat);
        if ((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1)) {
            node->batchAssets = &modelAsset->legacyBatches[i];
        } else {
            node->batchAssets =
                (BatchAsset *) ((s32) header + header->offsets[modelAsset->numNodes + numTextures + i + 2]);
        }

        numBatches = node->numBatches;
        for (j = 0; j < numBatches; j++) {
            model_asset_resolve_batch_texture(modelAsset, &node->batchAssets[j]);
        }
    }

    if (!((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1))) {
        modelAsset->palettes16 =
            (s32) header + header->offsets[modelAsset->numNodes + numTextures + modelAsset->numNodes + 2];
        modelAsset->palettes256 =
            (s32) header + header->offsets[modelAsset->numNodes + numTextures + modelAsset->numNodes + 3];
    }

    if ((u8) (modelAsset->fileFormat == MODEL_FILE_FORMAT_V1)) {
        if (header->offsets[2 * modelAsset->numNodes] != -1) {
            modelAsset->nodeHierarchy = (s32) header + header->offsets[2 * modelAsset->numNodes];
        } else {
            modelAsset->nodeHierarchy = NULL;
        }
    } else {
        if (header->offsets[modelAsset->numNodes + modelAsset->numTextures + 1] != -1) {
            modelAsset->nodeHierarchy =
                (s32) header + header->offsets[modelAsset->numNodes + modelAsset->numTextures + 1];
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

        modelAsset->legacyBatches[i].texIndex = header->offsets[modelAsset->numNodes + i];
        modelAsset->legacyBatches[i].vertIndex = 0;
        modelAsset->legacyBatches[i].triOffset = 0;
        modelAsset->legacyBatches[i].numVertices = numVertices;
        modelAsset->legacyBatches[i].numTriangles = numTriangles;
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
    ModelNodeAsset *v0 = &arg0->model.modelAsset->nodes[arg1];
    u32 numParts = v0->numBatches;
    u32 numVertices = v0->numVertices;
    u32 unk_04 = v0->numTriangles;
    s32 size;

    size = numParts * sizeof(Gfx) * 21 + (numVertices / 8) * sizeof(Gfx) + unk_04 * sizeof(Gfx); // TODO constant
    arg0->model.dlist[arg1] = mem_alloc(size, "kmd.c", 297);
    arg0->unk_A64 = size;
}

s32 find_min_triangle_vertex_index(u16 *triArray, u32 minIndex, s32 numTriangles) {
    u32 i;

    for (i = 0; i < numTriangles * 3; i++) {
        if (minIndex > triArray[i]) {
            minIndex = triArray[i];
        }
        if (triArray[i] * 0) {} // @fake
    }

    return minIndex;
}

void calculate_subbatch_vertex_window(Vec3su *arg0, u32 arg1, u32 arg2, s32 *arg3, s32 *arg4) {
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

void model_build_node_batches(Model *model, s32 nodeId, u8 skip_palette_upload, ModelRenderSettings *renderSettings) {
    u32 batchIndex;
    s32 numVerts;
    BatchTriangle *triangle;
    u32 numParts;
    Gfx *gfx;
    s32 partLastBatch;
    s32 partFirstBatch;
    s32 subbatch_vertex_count;
    s32 subbatch_triangle_count;
    s32 numTriangles;
    BatchInfo *batchInfos;
    u8 using_untextured_pipeline;
    u8 using_textured_pipeline;
    s32 v02;
    Vec3su *triangles;
    s32 padding[4];
    Vtx *vertices;
    Vtx *a11;
    s32 padding2;
    s32 vertIndex;
    Vec3su *triPtr;
    s32 size;
    BatchTriangle *runtime_triangles[100];
    s32 runtime_triangle_counts[100];
    s32 runtime_vertex_counts[100];
    u32 numBatches;
    Vtx *runtime_vertices[100];
    s32 sp2B8;
    u32 i;
    BatchAsset *nodeBatch;
    TextureAsset *tex;
    s32 batch_first_subbatch[100];
    Batch *batchArray;
    s32 padding3[2];
    u8 *pal16;
    u8 *pal256;
    ModelNodeAsset *node;

    using_untextured_pipeline = FALSE;
    using_textured_pipeline = FALSE;
    numBatches = 0;

    node = &model->modelAsset->nodes[nodeId];
    numParts = node->numBatches;
    numVerts = node->numVertices;
    vertices = node->vertices;
    triangles = node->triangles;

    if (model->unk_318) {
        for (i = 0; i < numVerts; i++) {
            vertices[i].v.tc[0] >>= 1;
            vertices[i].v.tc[1] >>= 1;
        }
    }

    for (batchIndex = 0; batchIndex < numParts; batchIndex++) {
        nodeBatch = node->batchAssets + batchIndex;
        numTriangles = nodeBatch->numTriangles;
        vertIndex = nodeBatch->vertIndex;
        numVerts = nodeBatch->numVertices;
        triPtr = triangles;
        triPtr += nodeBatch->triOffset;

        batch_first_subbatch[batchIndex] = numBatches;

        if (numVerts <= 16U) {
            triangle = runtime_triangles[numBatches] = mem_alloc(numTriangles * sizeof(BatchTriangle), "kmd.c", 421);
            for (i = 0; i < numTriangles; triPtr++, i++) {
                triangle[i].vi0 = triPtr->vi[0] - vertIndex;
                triangle[i].vi1 = triPtr->vi[1] - vertIndex;
                triangle[i].vi2 = triPtr->vi[2] - vertIndex;
                triangle[i].d = 0;
            }
            runtime_triangle_counts[numBatches] = numTriangles;
            runtime_vertices[numBatches] = vertices;
            runtime_vertices[numBatches] += vertIndex;
            runtime_vertex_counts[numBatches] = numVerts;
            numBatches++;
        } else {
            do {
                vertIndex = find_min_triangle_vertex_index(triPtr, vertIndex, numTriangles);
                runtime_vertices[numBatches] = vertices;
                runtime_vertices[numBatches] += vertIndex;
                calculate_subbatch_vertex_window(triPtr, vertIndex, numTriangles, &subbatch_triangle_count,
                                                 &subbatch_vertex_count);
                numTriangles -= subbatch_triangle_count;
                runtime_triangle_counts[numBatches] = subbatch_triangle_count;
                runtime_vertex_counts[numBatches] = subbatch_vertex_count;
                triangle = runtime_triangles[numBatches] =
                    mem_alloc(subbatch_triangle_count * sizeof(BatchTriangle), "kmd.c", 449);
                numBatches++;

                for (i = 0; i < subbatch_triangle_count; i++, triPtr++) {
                    triangle[i].vi0 = triPtr->vi[0] - vertIndex;
                    triangle[i].vi1 = triPtr->vi[1] - vertIndex;
                    triangle[i].vi2 = triPtr->vi[2] - vertIndex;
                    triangle[i].d = 0;
                }
                vertIndex += subbatch_vertex_count;
            } while (numTriangles != 0);
        }
    }

    batchArray = model->batches[nodeId] = (Batch *) mem_alloc(numBatches * sizeof(Batch), "kmd.c", 469);
    batchInfos = model->batchInfos[nodeId] = (BatchInfo *) mem_alloc(numBatches * sizeof(BatchInfo), "kmd.c", 470);

    for (i = 0; i < numBatches; i++) {
        batchArray[i].context = NULL;
        batchArray[i].vertices = runtime_vertices[i];
        batchArray[i].triangles = runtime_triangles[i];
        sp2B8 += runtime_triangle_counts[i] * 4; // ??
        batchArray[i].info = batchInfos + i;

        mem_fill(batchInfos + i, 0, sizeof(BatchInfo));
        (batchInfos + i)->header.triMask = renderSettings->triMask;
        (batchInfos + i)->header.unk_04 = 0;
        (batchInfos + i)->header.vtxNum = runtime_vertex_counts[i];
        (batchInfos + i)->header.vtxOffset = 0;
        (batchInfos + i)->header.numTriangles = runtime_triangle_counts[i];
        (batchInfos + i)->header.unk_0B = (i != 0) ? 1 : 0;
        (batchInfos + i)->header.texGfx = NULL;
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_RENDERMODE, renderSettings->renderMode);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_CYCLETYPE, G_CYC_1CYCLE);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTFILT, G_TF_BILERP);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTCONV, G_TC_FILT);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTPERSP, G_TP_PERSP);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_TEXTLUT, G_TT_RGBA16);
        gtStateSetOthermode(&(batchInfos + i)->header.otherMode, GT_PIPELINE, G_PM_NPRIMITIVE);
    }
    model->batchCounts[nodeId] = numBatches;

    size = 22 * sizeof(Gfx) * numParts; // TODO: make constant
    gfx = (Gfx *) mem_alloc(size, "kmd.c", 501);
    mem_fill(gfx, 0, size);
    for (batchIndex = 0; batchIndex < numParts; batchIndex++) {
        nodeBatch = node->batchAssets + batchIndex;
        partFirstBatch = batch_first_subbatch[batchIndex];
        partLastBatch = (batchIndex + 1 < numParts) ? batch_first_subbatch[batchIndex + 1] : numBatches;

        batchArray[partFirstBatch].info->header.texGfx = gfx;
        if (batchIndex == 0 && !(renderSettings->flags & 1)) {
            gDPSetPrimColor(gfx++, 0, 0, renderSettings->primColor.r, renderSettings->primColor.g,
                            renderSettings->primColor.b, renderSettings->primColor.a);
        }
        if (!using_untextured_pipeline && !((u8) (nodeBatch->texIndex >= 0))) {
            gDPPipeSync(gfx++);
            gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
            using_untextured_pipeline = TRUE;
            using_textured_pipeline = FALSE;
        } else if (!using_textured_pipeline && (u8) (nodeBatch->texIndex >= 0)) {
            gDPPipeSync(gfx++);
            gfx->words.w0 = renderSettings->combineMode.words.w0;
            gfx->words.w1 = renderSettings->combineMode.words.w1;
            gfx++;
            using_untextured_pipeline = FALSE;
            using_textured_pipeline = TRUE;
        }

        if (using_textured_pipeline) {
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
                if (!skip_palette_upload) {
                    pal16 = model->modelAsset->palettes16 + tex->palIndex * 0x20;
                    pal16[1] &= ~1;
                    gDPLoadTLUT_pal16(gfx++, 0, VIRTUAL_TO_PHYSICAL(pal16));
                }
                gDPLoadTextureBlock_4b(gfx++, tex->data, G_IM_FMT_CI, tex->width, tex->height, 0,
                                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                if (!skip_palette_upload) {
                    pal256 = model->modelAsset->palettes256 + tex->palIndex * 0x200;
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
    v0 = &arg0->model.modelAsset->nodes[arg1];
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
                    pal16 = arg0->model.modelAsset->palettes16 + a2->palIndex * 0x20;
                    gDPLoadTLUT_pal16(s3++, 0, VIRTUAL_TO_PHYSICAL(pal16));
                }
                gDPLoadTextureBlock_4b(s3++, a2->data, G_IM_FMT_CI, a2->width, a2->height, 0,
                                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                if (!arg2) {
                    pal256 = arg0->model.modelAsset->palettes256 + a2->palIndex * 0x200;
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
                s2 = find_min_triangle_vertex_index(s1, s2, s6);
                s7 = fp;
                s7 += s2;
                calculate_subbatch_vertex_window(s1, s2, s6, &sp134, &sp138);
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

    arg0->model.modelAsset = arg1;
    arg0->model.numNodes = arg1->numNodes;

    for (i = 0; i < arg0->model.numNodes; i++) {
        func_8000C1C4(arg0, i);
        func_8000D11C(arg0, i, arg3);
    }

    arg0->model.nodeHierarchy = v0 = arg0->model.modelAsset->nodeHierarchy;

    if (v0 != 0) {
        str_copy(sp30, name);
        sp30[3] = '\0';
        str_concat(sp30, "_anm.anm");
        asset = &gAssets[asset_find(sp30, arg4)];
        arg0->model.animations = D_8005AEB8[asset->memory_slot].data;
        arg0->model.animCount = asset->aux_data;
        heap_set_move_callback(asset->memory_slot, func_8000C18C, arg0->model.animCount);
    } else {
        arg0->model.animations = NULL;
    }
}

s32 model_build_vertex_position_groups(Model *model, s32 node_id, s16 *vertex_group_indices) {
    ModelNodeAsset *node;
    s32 num_vertex_groups;
    u32 i;
    u32 j;
    u32 num_vertices;
    Vtx *node_vertices;
    VertexPositionGroup *vertex_position_groups;
    s16 group_index;

    num_vertex_groups = 0;
    node = &model->modelAsset->nodes[node_id];
    num_vertices = node->numVertices;

    for (i = 0; i < num_vertices; i++) {
        vertex_group_indices[i] = i;
    }

    node_vertices = node->vertices;

    for (i = 0; i < num_vertices - 1; i++) {
        if (vertex_group_indices[i] == i) {
            num_vertex_groups++;
            for (j = 1; j < num_vertices; j++) {
                if (node_vertices[i].v.ob[0] == node_vertices[j].v.ob[0] &&
                    node_vertices[i].v.ob[1] == node_vertices[j].v.ob[1] &&
                    node_vertices[i].v.ob[2] == node_vertices[j].v.ob[2]) {
                    vertex_group_indices[j] = num_vertex_groups - 1;
                }
            }
        }
    }

    vertex_position_groups = mem_alloc(num_vertex_groups * sizeof(VertexPositionGroup), "kmd.c", 761);
    model->vertex_position_groups[node_id] = vertex_position_groups;
    model->num_vertex_position_groups[node_id] = num_vertex_groups;

    for (i = 0; i < num_vertex_groups; i++) {
        group_index = 0;
        for (j = 0; j < num_vertices; j++) {
            if (vertex_group_indices[j] == i) {
                vertex_position_groups[i].original_colors[group_index].r = node_vertices[j].v.cn[0];
                vertex_position_groups[i].original_colors[group_index].g = node_vertices[j].v.cn[1];
                vertex_position_groups[i].original_colors[group_index].b = node_vertices[j].v.cn[2];
                vertex_position_groups[i].vertex_indices[group_index++] = j;
                vertex_position_groups[i].vertex_indices[group_index] = -1;
            }
        }
    }

    return num_vertex_groups;
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

void model_build_vertex_normals(Model *model) {
    u32 i;
    u32 group_index;
    u32 s0;
    u32 s1;
    ModelNodeAsset *node;
    Vtx *vertices;
    Vec3su *triangles;
    u16 j;
    u16 k;
    u16 l;
    Vec3s *packed_normal;
    VertexPositionGroup *vertex_groups;
    Vec3f *accumulated_normals;
    Vec3f *face_normals;
    s32 padding3[2];
    Vec3f *vec2;
    f32 x, y, z;
    s16 num_vertex_groups;
    s16 *vertex_group_map;
    Vec3s spBC;
    s32 padding2;
    u16 num_triangles;
    s16 temp;
    f32 fv0;
    Vtx *v0;
    Vtx *v1;
    Vtx *a1;
    f32 face_normal[3];

    s0 = 0;
    s1 = 0;
    for (i = 0; i < model->numNodes; i++) {
        node = &model->modelAsset->nodes[i];
        if (s0 < node->numVertices) {
            s0 = node->numVertices;
        }
        if (s1 < node->numTriangles) {
            s1 = node->numTriangles;
        }
    }

    accumulated_normals = mem_alloc(s0 * 12, "kmd.c", 854);
    face_normals = mem_alloc(s1 * 12, "kmd.c", 855);
    vertex_group_map = mem_alloc(s0 * 2, "kmd.c", 856);
    mem_fill(accumulated_normals, 0, s0 * 12);
    mem_fill(face_normals, 0, s1 * 12);

    for (i = 0; i < model->numNodes; i++) {
        num_vertex_groups = model_build_vertex_position_groups(model, i, vertex_group_map);
        node = &model->modelAsset->nodes[i];
        num_triangles = node->numTriangles;
        vertices = node->vertices;
        triangles = node->triangles;

        for (j = 0; j < num_triangles; j++, triangles++) {
            a1 = vertices;
            a1 += triangles->vi[0];
            v0 = vertices;
            v0 += triangles->vi[1];
            v1 = vertices;
            v1 += triangles->vi[2];

            face_normal[0] = a1->v.ob[1] * (v0->v.ob[2] - v1->v.ob[2]) + v0->v.ob[1] * (v1->v.ob[2] - a1->v.ob[2]) +
                             v1->v.ob[1] * (a1->v.ob[2] - v0->v.ob[2]);
            face_normal[1] = a1->v.ob[2] * (v0->v.ob[0] - v1->v.ob[0]) + v0->v.ob[2] * (v1->v.ob[0] - a1->v.ob[0]) +
                             v1->v.ob[2] * (a1->v.ob[0] - v0->v.ob[0]);
            face_normal[2] = a1->v.ob[0] * (v0->v.ob[1] - v1->v.ob[1]) + v0->v.ob[0] * (v1->v.ob[1] - a1->v.ob[1]) +
                             v1->v.ob[0] * (a1->v.ob[1] - v0->v.ob[1]);
            func_8000DF5C(face_normal);
            face_normals[j].x = face_normal[0];
            face_normals[j].y = face_normal[1];
            face_normals[j].z = face_normal[2];
        }

        for (k = 0; k < num_vertex_groups; k++) {
            triangles = node->triangles;
            for (j = 0; j < num_triangles; j++, triangles++) {
                vec2 = face_normals;
                vec2 += j;
                for (l = 0; l < 3; l++) {
                    if (k == vertex_group_map[triangles->vi[l]] &&
                        func_8000DFF0(k, j, node->triangles, face_normals, num_triangles, vertex_group_map) == 0) {
                        accumulated_normals[k].x += vec2->x;
                        accumulated_normals[k].y += vec2->y;
                        accumulated_normals[k].z += vec2->z;
                    }
                }
            }
        }

        vertex_groups = model->vertex_position_groups[i];
        packed_normal = &spBC;
        for (group_index = 0; group_index < num_vertex_groups; group_index++) {
            x = accumulated_normals[group_index].x;
            y = accumulated_normals[group_index].y;
            z = accumulated_normals[group_index].z;
            fv0 = sqrtf(SQ(x) + SQ(y) + SQ(z));
            if (fv0 != 0) {
                accumulated_normals[group_index].x /= fv0;
                accumulated_normals[group_index].y /= fv0;
                accumulated_normals[group_index].z /= fv0;
            } else {
                accumulated_normals[group_index].x = accumulated_normals[group_index].y =
                    accumulated_normals[group_index].z = 0.0;
            }

            packed_normal->x = temp = ROUND(accumulated_normals[group_index].x * 128.0f);
            if (temp > 127) {
                packed_normal->x = 127;
            }
            packed_normal->y = temp = ROUND(accumulated_normals[group_index].y * 128.0f);
            if (temp > 127) {
                packed_normal->y = 127;
            }
            packed_normal->z = temp = ROUND(accumulated_normals[group_index].z * 128.0f);
            if (temp > 127) {
                packed_normal->z = 127;
            }

            vertex_groups[group_index].normal_x = packed_normal->x;
            vertex_groups[group_index].normal_y = packed_normal->y;
            vertex_groups[group_index].normal_z = packed_normal->z;
        }
    }

    mem_free(accumulated_normals);
    mem_free(face_normals);
    mem_free(vertex_group_map);
}

void model_init_from_asset(Model *model, ModelAsset *model_asset, char *name, u8 skip_palette_upload,
                           ModelRenderSettings *render_settings, s32 asset_context) {
    u32 i;
    s32 animation_asset_id;
    s32 j;
    s32 padding2;
    char animation_name[16];
    char padding[16];

    model->modelAsset = model_asset;
    model->numNodes = model_asset->numNodes;
    model->unk_318 = model_asset->unk_C8;
    model->unk_320 = 0;
    model->unk_321 = 0;
    model->unk_322 = 0;

    for (i = 0; i < model->numNodes; i++) {
        model_build_node_batches(model, i, skip_palette_upload, render_settings);
    }

    if (model->modelAsset->nodeHierarchy != NULL) {
        model->nodeHierarchy = mem_alloc((model->numNodes + 1) * sizeof(NodeAttachment), "kmd.c", 983);
        memcpy(model->nodeHierarchy, model->modelAsset->nodeHierarchy, (model->numNodes + 1) * sizeof(NodeAttachment));
    } else {
        model->nodeHierarchy = NULL;
    }

    str_copy(animation_name, name);
    for (j = 0; animation_name[j] != '\0' && j < 16;) {
        if (animation_name[j++] == '.') {
            animation_name[j - 1] = '\0';
            break;
        }
    }

    str_concat(animation_name, "_anm.anm");
    animation_asset_id = asset_find(animation_name, asset_context);

    if (animation_asset_id < 0) {
        str_copy(animation_name, name);
        animation_name[3] = '\0';
        str_concat(animation_name, "_anm.anm");
        animation_asset_id = asset_find(animation_name, asset_context);
    }

    if (animation_asset_id >= 0) {
        model->animations = D_8005AEB8[gAssets[animation_asset_id].memory_slot].data;
        model->animCount = gAssets[animation_asset_id].aux_data;
        heap_set_move_callback(gAssets[animation_asset_id].memory_slot, func_8000C18C, model->animCount);
    } else {
        model->animations = NULL;
    }
}
