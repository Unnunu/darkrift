#include "common.h"

/* .bss */

u64 D_800B85B0[SP_DRAM_STACK_SIZE64];
Gfx D_800B89B0[0x10000];
u64 D_801389B0;
OSTask D_801389B8;

/* .data */

Vp D_8004C9B0 = {
    {
        { (SCREEN_WIDTH / 2) << 2, (SCREEN_HEIGHT / 2) << 2, G_MAXZ / 2, 0 },
        { (SCREEN_WIDTH / 2) << 2, (SCREEN_HEIGHT / 2) << 2, G_MAXZ / 2, 0 },
    },
};

Gfx D_8004C9C0[] = {
    gsSPViewport(&D_8004C9B0),
    gsSPClearGeometryMode(G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                          G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_8004C9E8[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8004CA68[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_KEY),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPNoOp(),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0, 0, 0, 1),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8004CB00[] = {
    gsDPPipeSync(),
    gsSPViewport(&D_8004C9B0),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPClipRatio(FRUSTRATIO_6),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
    gsDPPipeSync(), // ????
};

OSTask D_8004CBC8 = {
    M_GFXTASK,           OS_TASK_DP_WAIT, NULL,        0,    NULL, SP_UCODE_SIZE, NULL, SP_UCODE_DATA_SIZE, D_800B85B0,
    SP_DRAM_STACK_SIZE8, D_800B89B0,      &D_801389B0, NULL, 0,    NULL,          0,
};

Gfx D_8004CC08[] = {
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 0, 192, 192, 192, 255),
    gsSPNoOp(),
};

RenderContext D_8004CC20 = {
    -1,
    { 0, 0, 0, 0, 0, 0 },
    gsDPSetOtherMode(0, 0),
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { {
        { (SCREEN_WIDTH / 2) << 2, (SCREEN_HEIGHT / 2) << 2, G_MAXZ / 2, 0 },
        { (SCREEN_WIDTH / 2) << 2, (SCREEN_HEIGHT / 2) << 2, G_MAXZ / 2, 0 },
    } },
    D_8004CC08,
};

OSTask D_8004CC88 = {
    M_GFXTASK, OS_TASK_DP_WAIT,
    NULL,      0,
    NULL,      SP_UCODE_SIZE,
    NULL,      SP_UCODE_DATA_SIZE,
    NULL,      SP_DRAM_STACK_SIZE8,
    NULL,      NULL,
    NULL,      0,
    NULL,      0,
};

BatchInfo D_8004CCC8 = {
    { 0, 0, 0, 0, 0, 0, NULL, gsDPSetOtherMode(0, 0) },
    { {
        { 0x00010000, 0x00000000, 0x00000001, 0x00000000 },
        { 0x00000000, 0x00010000, 0x00000000, 0x00000001 },
        { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
    } },
};

Gfx D_8004CD20[] = {
    gsDPFullSync(),
    gsSPNoOp(),
};

BatchInfo D_8004CD30 = {
    { 0, 0, 0, 0, 0, 0, D_8004CD20, gsDPSetOtherMode(0, 0) },
    { {
        { 0x00010000, 0x00000000, 0x00000001, 0x00000000 },
        { 0x00000000, 0x00010000, 0x00000000, 0x00000001 },
        { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
        { 0x00000000, 0x00000000, 0x00000000, 0x00000000 },
    } },
};
