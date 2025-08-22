#include "common.h"
#include "string.h"
#include "PR/gt.h"

typedef struct Unk8000C3CC {
    /* 0x00 */ s8 a;
    /* 0x01 */ s8 b;
    /* 0x02 */ s8 c;
    /* 0x03 */ s8 d;
} Unk8000C3CC; // size = 4

void func_8000C158(AssetGmd *, u8);

void func_8000BCF0(AssetGmdSub2 *arg0, AssetUnkHeader2 *arg1, u32 arg2) {
    arg0->numVertices = arg1->unk_00;
    arg0->unk_04 = arg1->unk_04;
    arg0->vertices = arg1->unk_08 + (s32) arg1;
    arg0->unk_0C = arg1->unk_0C + (s32) arg1;

    if (arg2 >= 2) {
        arg0->unk_18 = *(s32 *) (arg1->unk_10 + (s32) arg1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000BD38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000BD70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000BDA8.s")

void func_8000BDB0(AssetGmd *arg0, AssetGmdSub1 *arg1) {
    if (arg1->unk_00 >= 0) {
        if ((u8) (arg0->unk_B0 == 1)) {
            arg1->unk_0C = (s32) arg0->unk_B8 + arg1->unk_00;
        } else {
            arg1->unk_0C = (s32) arg0->unk_B8 + arg0->unk_B8->offsets[arg0->numEntries + arg1->unk_00 + 1];
        }
    } else {
        arg1->unk_0C = 0;
    }
}

void func_8000BE18(AssetGmd *arg0) {
    AssetUnkHeader *s7;
    s32 sp40;
    u32 i;
    AssetGmdSub2 *s2;
    s32 s1;
    u32 j;

    s7 = (AssetUnkHeader *) D_8005AEB8[arg0->unk_AC].unk_04;
    arg0->unk_04 = (AssetGmdSub2 *) ((s32) arg0 + sizeof(AssetGmd) + arg0->numEntries * sizeof(AssetGmdSub1));
    arg0->unk_B8 = s7;

    if (!((u8) (arg0->unk_B0 == 1))) {
        sp40 = s7->offsets[arg0->numEntries];
    }
    arg0->unk_B4 = sp40;

    for (i = 0; i < arg0->numEntries; i++) {
        s2 = arg0->unk_04 + i;
        func_8000BCF0(s2, (AssetUnkHeader2 *) ((s32) s7 + s7->offsets[i]), arg0->unk_B0);
        if ((u8) (arg0->unk_B0 == 1)) {
            s2->unk_1C = &arg0->unk_CC[i];
        } else {
            s2->unk_1C = (AssetGmdSub1 *) ((s32) s7 + s7->offsets[arg0->numEntries + sp40 + i + 2]);
        }

        s1 = s2->unk_18;
        for (j = 0; j < s1; j++) {
            func_8000BDB0(arg0, &s2->unk_1C[j]);
        }
    }

    if (!((u8) (arg0->unk_B0 == 1))) {
        arg0->unk_C0 = (s32) s7 + s7->offsets[arg0->numEntries + sp40 + arg0->numEntries + 2];
        arg0->unk_C4 = (s32) s7 + s7->offsets[arg0->numEntries + sp40 + arg0->numEntries + 3];
    }

    if ((u8) (arg0->unk_B0 == 1)) {
        if (s7->offsets[2 * arg0->numEntries] != -1) {
            arg0->unk_08 = (s32) s7 + s7->offsets[2 * arg0->numEntries];
        } else {
            arg0->unk_08 = NULL;
        }
    } else {
        if (s7->offsets[arg0->numEntries + arg0->unk_B4 + 1] != -1) {
            arg0->unk_08 = (s32) s7 + s7->offsets[arg0->numEntries + arg0->unk_B4 + 1];
        } else {
            arg0->unk_08 = NULL;
        }
    }
}

void func_8000C044(AssetGmd *arg0, AssetUnkHeader *arg1) {
    u32 i;
    s32 var1, var2;

    arg0->unk_04 = (AssetGmdSub2 *) ((s32) arg0 + sizeof(AssetGmd) + arg0->numEntries * sizeof(AssetGmdSub1));

    for (i = 0; i < arg0->numEntries; i++) {
        AssetGmdSub2 *temp = arg0->unk_04 + i;
        temp->unk_18 = 1;

        var1 = ((AssetUnkHeader2 *) ((s32) arg1 + arg1->offsets[i]))->unk_00;
        var2 = ((AssetUnkHeader2 *) ((s32) arg1 + arg1->offsets[i]))->unk_04;

        arg0->unk_CC[i].unk_00 = arg1->offsets[arg0->numEntries + i];
        arg0->unk_CC[i].unk_04 = 0;
        arg0->unk_CC[i].unk_06 = 0;
        arg0->unk_CC[i].unk_08 = var1;
        arg0->unk_CC[i].unk_0A = var2;
    }
}

void func_8000C0E4(AssetGmd *arg0, s32 slot) {
    AssetUnkHeader *sp1C;

    arg0->unk_AC = slot;
    sp1C = D_8005AEB8[slot].unk_04;
    func_8000C158(arg0, sp1C->signature[0]);

    if ((u8) (arg0->unk_B0 == 1)) {
        func_8000C044(arg0, sp1C);
    }

    func_8000BE18(arg0);
}

void func_8000C158(AssetGmd *arg0, u8 arg1) {
    switch (arg1) {
        case '@':
            arg0->unk_B0 = 1;
            break;
        case '2':
            arg0->unk_B0 = 2;
            break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C18C.s")
void func_8000C18C(s32 *arg0, s32 arg1, u32 arg2);

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C1C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C258.s")
u16 func_8000C258(Vec3s *arg0, s32 arg1, s32 arg2);

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C328.s")
void func_8000C328(Vec3s *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4);

// #ifdef NON_MATCHING

#define G_IM_SIZ_8b_SHIFTL 1

void func_8000C3CC(UnkSam *arg0, s32 arg1, u8 arg2, Unk8000C3CCArg3 *arg3) {
    u32 sp95C;
    s32 s3;
    Unk8000C3CC *v0;
    u32 sp950;
    Gfx *gfx;
    s32 a3;
    s32 a0;
    s32 sp940;
    s32 sp93C;
    s32 s4;
    BatchInfo *s1;
    s32 v02;
    u8 sp933;
    u8 sp932;
    Vec3su *sp928;
    s32 padding[4];
    Vtx *sp914;
    Vtx *a11;
    Unk8000C3CC *sp770[100];
    s32 sp5E0[100];
    s32 sp450[100];
    u32 sp44C;
    Vtx *sp2BC[100];
    s32 sp2B8;
    u32 i; // s2
    s32 sp11C[100];
    Batch *sp118;
    AssetGmdSub2 *sp104;
    AssetGmdSub1 *t0;
    TextureAsset *tex;

    s32 s33;

    s32 s11;
    Vec3su *s02;
    s32 size;

    sp933 = FALSE;
    sp932 = FALSE;
    sp44C = 0;

    sp104 = &arg0->unk_04->unk_04[arg1];
    sp950 = sp104->unk_18;
    s3 = sp104->numVertices;
    sp914 = sp104->vertices;
    sp928 = sp104->unk_0C;

    if (arg0->unk_318) {
        for (i = 0; i < s3; i++) {
            sp914[i].v.tc[0] >>= 1;
            sp914[i].v.tc[1] >>= 1;
        }
    }

    for (sp95C = 0; sp95C < sp950; sp95C++) {
        t0 = sp104->unk_1C + sp95C;
        s4 = t0->unk_0A;
        s11 = t0->unk_04;
        s33 = t0->unk_08;
        s02 = &sp928[t0->unk_06];

        sp11C[sp95C] = sp44C;

        if (s33 <= 16U) {
            sp770[sp44C] = v0 = mem_alloc(s4 * sizeof(Unk8000C3CC), "kmd.c", 421);
            for (i = 0; i < s4; s02++, i++) {
                v0[i].a = s02->x - s11;
                v0[i].b = s02->y - s11;
                v0[i].c = s02->z - s11;
                v0[i].d = 0;
            }
            sp5E0[sp44C] = s4;
            sp450[sp44C] = s33;
            sp2BC[sp44C] = &sp914[s11];
            sp44C++;
        } else {
            do {
                v02 = func_8000C258(s02, s11, s4);
                sp2BC[sp44C] = &sp914[v02];
                func_8000C328(s02, v02, s4, &sp93C, &sp940);
                s4 -= sp93C;
                sp5E0[sp44C] = sp93C;
                sp450[sp44C] = sp940;
                v0 = sp770[sp44C] = mem_alloc(sp93C * sizeof(Unk8000C3CC), "kmd.c", 0x1C1);
                sp44C++;

                for (i = 0; i < sp93C; s02++, i++) {
                    v0[i].a = s02->x - v02;
                    v0[i].b = s02->y - v02;
                    v0[i].c = s02->z - v02;
                    v0[i].d = 0;
                }
                s11 = v02 + sp940;
            } while (s4 != 0);
        }
    }

    sp118 = arg0->unk_154[arg1] = (Batch *) mem_alloc(sp44C * sizeof(Batch), "kmd.c", 469);
    s1 = arg0->unk_2A8[arg1] = (BatchInfo *) mem_alloc(sp44C * sizeof(BatchInfo), "kmd.c", 470);

    for (i = 0; i < sp44C; i++) {
        sp118[i].context = NULL;
        sp118[i].vertices = sp2BC[i];
        sp118[i].triangles = sp770[i];
        sp118[i].info = &s1[i];

        sp2B8 += sp5E0[i] * 4; // ??

        func_80000E0C(&s1[i], 0, sizeof(BatchInfo));
        s1[i].header.unk_00 = arg3->unk_0C;
        s1[i].header.unk_04 = 0;
        s1[i].header.numVertices = sp450[i];
        s1[i].header.unk_09 = 0;
        s1[i].header.numTriangles = sp5E0[i];
        s1[i].header.unk_0B = (i != 0) ? 1 : 0;
        s1[i].header.unk_0C = NULL;
        gtStateSetOthermode(&s1[i].header.unk_10, GT_RENDERMODE, arg3->renderMode);
        gtStateSetOthermode(&s1[i].header.unk_10, GT_CYCLETYPE, G_CYC_1CYCLE);
        gtStateSetOthermode(&s1[i].header.unk_10, GT_TEXTFILT, G_TF_BILERP);
        gtStateSetOthermode(&s1[i].header.unk_10, GT_TEXTCONV, G_TC_FILT);
        gtStateSetOthermode(&s1[i].header.unk_10, GT_TEXTPERSP, G_TP_PERSP);
        gtStateSetOthermode(&s1[i].header.unk_10, GT_TEXTLUT, G_TT_RGBA16);
        gtStateSetOthermode(&s1[i].header.unk_10, GT_PIPELINE, G_PM_NPRIMITIVE);
    }
    arg0->unk_238[arg1] = sp44C;

    size = 22 * sizeof(Gfx) * sp950; // TODO: make constant
    gfx = (Gfx *) mem_alloc(size, "kmd.c", 501);
    func_80000E0C(gfx, 0, size);
    for (sp95C = 0; sp95C < sp950; sp95C++) {
        t0 = sp104->unk_1C + sp95C;
        a0 = sp11C[sp95C];
        a3 = (sp95C + 1 < sp950) ? sp11C[sp95C + 1] : sp44C;

        sp118[a0].info->header.unk_0C = gfx;
        if (sp95C == 0 && !(arg3->unk_14 & 1)) {
            gDPSetPrimColor(gfx++, 0, 0, arg3->unk_10.r, arg3->unk_10.g, arg3->unk_10.b, arg3->unk_10.a);
        }
        if (!sp933 && !((u8) (t0->unk_00 >= 0))) {
            gDPPipeSync(gfx++);
            gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
            sp933 = TRUE;
            sp932 = FALSE;
        } else if (!sp932 && (u8) (t0->unk_00 >= 0)) {
            gDPPipeSync(gfx++);
            gfx->words.w0 = arg3->unk_00.words.w0;
            gfx->words.w1 = arg3->unk_00.words.w1;
            gfx++;
            sp933 = FALSE;
            sp932 = TRUE;
        }

        if (sp932) {
            for (i = a0; i < a3; i++) {
                sp118[i].info->header.unk_00 |= 2;
            }

            s33 = t0->unk_08;
            a11 = &sp914[t0->unk_04];
            for (i = 0; i < s33; i++) {
                a11[i].v.cn[0] = a11[i].v.cn[1] = a11[i].v.cn[2] = 255;
            }

            tex = t0->unk_0C;
            if (tex->unk_08 == 4) {
                if (!arg2) {
                    u8 *palette = arg0->unk_04->unk_C0 + tex->unk_0C * 0x20;
                    palette[1] &= ~1;
                    gDPLoadTLUT_pal16(gfx++, 0, VIRTUAL_TO_PHYSICAL(palette));
                }
                gDPLoadTextureBlock_4b(gfx++, tex->data, G_IM_FMT_CI, tex->width, tex->height, 0,
                                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
            } else {
                if (!arg2) {
                    u8 *palette = arg0->unk_04->unk_C4 + tex->unk_0C * 0x200;
                    palette[1] &= ~1;
                    gDPLoadTLUT_pal256(gfx++, VIRTUAL_TO_PHYSICAL(palette));
                }
                gDPLoadTextureBlock(gfx++, tex->data, G_IM_FMT_CI, G_IM_SIZ_8b, tex->width, tex->height, 0,
                                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
            }
        }
        gSPNoOp(gfx++);
    }
}
// #else
// #pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C3CC.s")
// void func_8000C3CC(UnkSam *arg0, s32 arg1, u8 arg2, Unk8000C3CCArg3 *arg3);
// #endif

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000D11C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DAB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DBC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DF5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000E0D8.s")

void func_8000E73C(UnkSam *arg0, AssetGmd *arg1, char *arg2, u8 arg3, Unk8000C3CCArg3 *arg4, s32 arg5) {
    u32 i;
    s32 v1;
    s32 j;
    s32 padding2;
    char sp48[16];
    char padding[16];

    arg0->unk_04 = arg1;
    arg0->unk_128 = arg1->numEntries;
    arg0->unk_318 = arg1->unk_C8;
    arg0->unk_320 = 0;
    arg0->unk_321 = 0;
    arg0->unk_322 = 0;

    for (i = 0; i < arg0->unk_128; i++) {
        func_8000C3CC(arg0, i, arg3, arg4);
    }

    if (arg0->unk_04->unk_08 != 0) {
        arg0->unk_150 = mem_alloc(arg0->unk_128 * 0x10 + 0x10, "kmd.c", 983);
        memcpy(arg0->unk_150, arg0->unk_04->unk_08, arg0->unk_128 * 0x10 + 0x10);
    } else {
        arg0->unk_150 = NULL;
    }

    str_copy(sp48, arg2);
    for (j = 0; sp48[j] != '\0' && j < 16;) {
        if (sp48[j++] == '.') {
            sp48[j - 1] = '\0';
            break;
        }
    }

    str_concat(sp48, "_anm.anm");
    v1 = asset_find(sp48, arg5);

    if (v1 < 0) {
        str_copy(sp48, arg2);
        sp48[3] = '\0';
        str_concat(sp48, "_anm.anm");
        v1 = asset_find(sp48, arg5);
    }

    if (v1 >= 0) {
        arg0->unk_148 = D_8005AEB8[gAssets[v1].memory_slot].unk_04;
        arg0->unk_14C = gAssets[v1].aux_data;
        func_800010D4(gAssets[v1].memory_slot, func_8000C18C, arg0->unk_14C);
    } else {
        arg0->unk_148 = NULL;
    }
}
