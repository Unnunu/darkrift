#include "common.h"
#include "string.h"

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

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C328.s")

#pragma GLOBAL_ASM("asm/nonmatchings/kmd/func_8000C3CC.s")
void func_8000C3CC(UnkSam *, s32, u8, u8 *);

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
