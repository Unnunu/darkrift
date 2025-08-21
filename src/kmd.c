#include "common.h"
#include "string.h"

typedef struct Unk8000C3CC {
    /* 0x00 */ s8 a;
    /* 0x01 */ s8 b;
    /* 0x02 */ s8 c;
    /* 0x03 */ s8 d;
} Unk8000C3CC; // size = 4

void func_8000C158(AssetGmd *, u8);

void func_8000BCF0(AssetGmdSub2 *arg0, AssetUnkHeader2 *arg1, u32 arg2) {
    arg0->unk_00 = arg1->unk_00;
    arg0->unk_04 = arg1->unk_04;
    arg0->unk_08 = arg1->unk_08 + (s32) arg1;
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
u16 func_8000C258(Vec3s *arg0, u16 arg1, u16 arg2);

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C328.s")
void func_8000C328(Vec3s *arg0, u16 arg1, s32 arg2, s32 *arg3, s32 *arg4);

#ifdef NON_MATCHING
void func_8000C3CC(UnkSam *arg0, s32 arg1, u8 arg2, u8 *arg3) {
    u32 sp95C;
    u32 sp950;
    s32 sp940;
    s32 sp93C;
    u8 sp933;
    u8 sp932;
    Vec3s *sp928;
    AssetGmdSub3 *sp914;
    Unk8000C3CC *sp770[10];
    s32 sp5E0[10];
    s32 sp450[10];
    u32 sp44C;
    AssetGmdSub3 *sp2BC[10];
    u32 i; // s2
    s32 sp11C[10];
    AssetGmdSub2 *sp104;
    s32 s3;
    Unk8000C3CC *v0;

    sp933 = 0;
    sp932 = 0;
    sp44C = 0;

    sp104 = &arg0->unk_04->unk_04[arg1];
    sp950 = sp104->unk_18;
    s3 = sp104->unk_00;
    sp914 = sp104->unk_08;
    sp928 = sp104->unk_0C;

    if (arg0->unk_318) {
        for (i = 0; i < s3; i++) {
            sp914[i].unk_08 >>= 1;
            sp914[i].unk_0A >>= 1;
        }
    }

    for (sp95C = 0; sp95C < sp950; sp95C++) {
        u16 s33 = sp104->unk_1C[sp95C].unk_08;
        u16 s4 = sp104->unk_1C[sp95C].unk_0A;
        u16 s1 = sp104->unk_1C[sp95C].unk_04;
        Vec3s *s02 = &sp928[sp104->unk_1C[sp95C].unk_06];

        sp11C[sp95C] = sp44C;

        if (s33 <= 16) {
            sp770[sp44C] = v0 = mem_alloc(s4 * sizeof(Unk8000C3CC), "kmd.c", 0x1A5);
            for (i = 0; i < s4; i++) {
                v0[i].a = s02[i].x - s1;
                v0[i].b = s02[i].y - s1;
                v0[i].c = s02[i].z - s1;
                v0[i].d = 0;
            }
            sp5E0[sp44C] = s4;
            sp450[sp44C] = s33;
            sp2BC[sp44C] = &sp914[s1];
            sp44C++;
        } else {
            u16 v02;

            v02 = func_8000C258(s02, s1, s4);
            sp2BC[sp44C] = &sp914[v02];
            func_8000C328(s02, v02, s4, &sp93C, &sp940);
            sp5E0[sp44C] = sp93C;
            s4 -= sp93C;
            sp450[sp44C] = sp940;
            sp770[sp44C] = v0 = mem_alloc(sp93C * sizeof(Unk8000C3CC), "kmd.c", 0x1A5);
            sp44C++;

            for (i = 0; i < sp93C; i++) {
                v0[i].a = s02[i].x - v02;
                v0[i].b = s02[i].y - v02;
                v0[i].c = s02[i].z - v02;
                v0[i].d = 0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C3CC.s")
void func_8000C3CC(UnkSam *arg0, s32 arg1, u8 arg2, u8 *arg3);
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000D11C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DAB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DBC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DF5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000DFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000E0D8.s")

void func_8000E73C(UnkSam *arg0, AssetGmd *arg1, char *arg2, u8 arg3, u8 *arg4, s32 arg5) {
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
