#include "common.h"
#include "ld_addrs.h"
#include "string.h"
#include "PR/gt.h"

enum WadFileTypes {
    WAD_FILE_ANM = 0,
    WAD_FILE_TEX = 1,
    WAD_FILE_SP2 = 2,
    WAD_FILE_3 = 3,
    WAD_FILE_WAD = 4,
    WAD_FILE_DB = 5,
    WAD_FILE_PCL = 6,
    WAD_FILE_GMD = 7,
    WAD_FILE_TMD = 8,
    WAD_FILE_SEQ = 9,
    WAD_FILE_CTL = 10,
    WAD_FILE_TBL = 11,
    WAD_FILE_SP3 = 12,
    WAD_FILE_SFB = 13,
    WAD_FILE_SFX = 14,
    WAD_FILE_K2 = 15,
    WAD_FILE_MOV = 16,
    WAD_FILE_OC = 17,
    WAD_FILE_SYM = 18,
    WAD_FILE_VOX = 19,
    WAD_FILE_K3 = 20,
    WAD_FILE_K4 = 21,
    WAD_FILE_K5 = 22
};

typedef struct WadFolder {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 numFiles;
    /* 0x1C */ s32 folderIndex;
} WadFolder; // size >= 0x20

typedef struct WadFileEntry {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 type;
    /* 0x1C */ s32 size;
    /* 0x20 */ s32 unpackedSize;
} WadFileEntry; // size = 0x24

typedef struct WadFile {
    /* 0x00 */ u32 numFolders;
    /* 0x04 */ u32 unk_04; // unknown, same as numFolders
    /* 0x08 */ WadFolder folders[1];
} WadFile;

typedef struct AnimAsset {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04[1];
} AnimAsset;

s32 gNumAssets = 0;

Asset gAssets[256];
s32 D_8013C200;
WadFile *gWadFile;
s32 D_8013C208;
u8 *gWadRomAddress;
WadFolder *gWadCurrentFolder;
s32 D_8013C214;
s32 D_8013C218;
u32 gWadNumFiles;
u32 gWadNumFolders;
s16 D_8013C224;
s16 D_8013C226;
void (*D_8013C228)(Asset *);

void sound_init_player(ALBankFile *arg0, u8 *arg1, u32 arg2);
void mem_move(u32 *dest, u32 *src, u32 size);
void func_8000C0E4(AssetGmd *, s32);
void func_8000DAB0(UnkFrodo *, AssetGmd *, char *, s32, u16);
void func_80025A0C(Asset *);
void asset_read_all_files_in_folder(s32);
void assets_clear_unused(void);
void dma_read(s32 romAddr, void *vramAddr, s32 size);
void func_8000E73C(UnkSam *, AssetGmd *, char *, s32, Unk8000C3CCArg3 *, u16);
void func_80035CCC(UnkSam *);
void func_8000E0D8(UnkSam *);

void func_80026B74(Asset *);
void func_80027680(Asset *);
void func_8000BE18(AssetGmd *);

void asset_reload_tmd(Asset *);
void asset_reload_gmd(Asset *);
void func_80026EEC(Asset *);
void asset_load_tbl(Asset *);
void asset_load_seq(Asset *);
void asset_load_sfx(Asset *);
void asset_reload_sp3(Asset *);
void asset_reload_k2(Asset *);
void asset_reload_k3(Asset *);
void asset_reload_k4(Asset *);
void asset_reload_k5(Asset *);
void func_80026DF0(Asset *);
void asset_load_tex(Asset *);
void asset_load_sp2(Asset *);
void func_800271C0(Asset *);
void asset_load_gmd(Asset *);
void asset_load_k3(Asset *);
void asset_load_k4(Asset *);
void asset_load_k5(Asset *);
void asset_load_tmd(Asset *);
void asset_load_ctl(Asset *);
void asset_load_vox(Asset *);
void asset_load_sfb(Asset *);
void asset_load_sp3(Asset *);
void asset_load_oc(Asset *);
void asset_load_k2(Asset *);
void asset_load_mov(Asset *);
void asset_load_sym(Asset *);

void func_80025B40(void) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {}
}

void str_concat(char *dst, char *src) {
    u32 dst_len = strlen(dst);
    u32 src_len = strlen(src);
    s32 i;

    for (i = 0; i < src_len; i++) {
        dst[dst_len + i] = *src++;
    }

    dst[dst_len + src_len] = 0;
}

void str_copy(char *arg0, char *arg1) {
    u32 size = strlen(arg1);
    s32 i;

    for (i = 0; i < size; i++) {
        *arg0++ = *arg1++;
    }

    *arg0 = 0;
}

s32 str_compare(char *arg0, char *arg1) {
    u32 sp1C;
    u32 len2;
    u32 i;

    sp1C = strlen(arg0);
    len2 = strlen(arg1);
    if (sp1C != len2) {
        return 1;
    }

    for (i = 0; i < sp1C; i++) {
        if (*arg0++ != *arg1++) {
            return 1;
        }
    }

    return 0;
}

void str_toupper(char *str) {
    u32 size = strlen(str);
    u32 i;

    for (i = 0; i < size; i++) {
        str[i] = (str[i] >= 'a') ? str[i] -= 'a' - 'A' : str[i];
    }
}

u32 asset_find(char *name, u32 context) {
    u32 i;

    str_toupper(name);
    for (i = 0; i < gNumAssets; i++) {
        if (str_compare(name, gAssets[i].name) == 0 && context == gAssets[i].context) {
            return i;
        }
    }

    return -1;
}

void func_80025E6C(void) {
    u32 i;

    gNumAssets = 0;
    for (i = 0; i < 256; i++) {
        gAssets[i].memory_slot = gAssets[i].aux_memory_slot = -1;
        gAssets[i].flags = 1;
        gAssets[i].name[0] = '\0';
    }
}

void func_80025EDC(s32 arg0, s32 size) {
    D_8013C200 = arg0;
    gWadFile = D_8013C200;
    D_8013C208 = D_8013C200 + 0x2800;
    D_8013C214 = D_8013C208 - arg0;
    D_8013C218 = size - D_8013C214;
}

void wad_find_wad(char *name) {
    s32 i;
    char fullname[20];
    WadFileEntry *firstFile;
    WadFileEntry *file;

    firstFile = gWadCurrentFolder->offset + (u8 *) gWadFile;
    str_copy(fullname, name);
    str_concat(fullname, ".WAD");

    for (i = 0, file = firstFile; i < gWadNumFiles; i++, file++) {
        if (str_compare(file->name, fullname) == 0) {
            gWadRomAddress += file->offset;
            return;
        }
        if (file && file) {
            // FAKE MATCH
        }
    }
}

s32 wad_select_folder(char *folderName) {
    s32 pad;
    u32 i;
    WadFolder *folders;

    folders = gWadFile->folders;
    for (i = 0; i < gWadNumFolders; i++) {
        if (str_compare(folderName, folders[i].name) == 0) {
            gWadCurrentFolder = &folders[i];
            gWadNumFolders = 1;
            gWadNumFiles = folders[i].numFiles;
            return TRUE;
        }
    }

    return FALSE;
}

void wad_open_one(char *name) {
    if (name[0] == '\0') {
        // load root wad
        gWadRomAddress = resources_ROM_START;
        dma_read(gWadRomAddress, gWadFile, D_8013C214);
        gWadCurrentFolder = gWadFile->folders;
        gWadNumFolders = gWadFile->numFolders;
        gWadNumFiles = gWadCurrentFolder->numFiles;
    } else if (wad_select_folder(name)) {
        // select folder in current wad file
    } else {
        wad_find_wad(name);
        dma_read(gWadRomAddress, gWadFile, D_8013C214);
        gWadCurrentFolder = gWadFile->folders;
        gWadNumFolders = gWadFile->numFolders;
        gWadNumFiles = gWadCurrentFolder[0].numFiles;
    }
}

void wad_open_path(char *path) {
    s32 len;
    char path_item[24];
    u32 i;
    u32 j;

    len = strlen(path);
    j = 0;
    str_toupper(path);
    path_item[0] = '\0';

    for (i = 0; i < len; i++) {
        if (path[i] != '/') {
            path_item[j++] = path[i];
        } else {
            path_item[j] = '\0';
            j = 0;
            wad_open_one(path_item);
        }
    }

    path_item[j] = '\0';
    wad_open_one(path_item);
}

void func_80026250(void) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        if (gAssets[i].memory_slot >= 0) {
            gAssets[i].data = D_8005AEB8[gAssets[i].memory_slot].data;
        }
        if (gAssets[i].aux_memory_slot >= 0) {
            gAssets[i].aux_data = D_8005AEB8[gAssets[i].aux_memory_slot].data;
        }
    }
}

void asset_open_folder(char *path, s32 context) {
    assets_clear_unused();
    wad_open_path(path);
    asset_read_all_files_in_folder(context);
    mem_fill(gWadFile, 0, D_8013C214);
    assets_clear_unused();
}

void func_8002630C(s32 arg0) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        if (arg0 == gAssets[i].context) {
            func_80026B74(gAssets + i);
        }
    }

    assets_clear_unused();
}

void func_800263A8(void) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        func_80026B74(gAssets + i);
    }

    assets_clear_unused();
}

void func_80026418(s32 arg0) {
    u32 i;

    for (i = 0; i < gNumAssets; i++) {
        if (arg0 == gAssets[i].type) {
            func_80026B74(gAssets + i);
        }
    }

    assets_clear_unused();
}

void asset_read_all_files_in_folder(s32 context) {
    s32 pad[2];
    u32 i;
    u32 free_memory;
    WadFileEntry *file;
    s32 v0;

    free_memory = heap_get_free_mem(sFreeChunksList);
    file = (WadFileEntry *) ((u8 *) gWadFile + gWadCurrentFolder->offset);

    for (i = 0; i < gWadNumFiles; i++) {
        v0 = asset_find(file[i].name, context);

        if (v0 >= 0) {
            switch (file[i].type) {
                case WAD_FILE_3:
                    func_80027680(gAssets + v0);
                    break;
                case WAD_FILE_TMD:
                    asset_reload_tmd(gAssets + v0);
                    break;
                case WAD_FILE_GMD:
                    asset_reload_gmd(gAssets + v0);
                    break;
                case WAD_FILE_SP2:
                    func_80026EEC(gAssets + v0);
                    break;
                case WAD_FILE_TBL:
                    asset_load_tbl(gAssets + v0);
                    break;
                case WAD_FILE_SEQ:
                    asset_load_seq(gAssets + v0);
                    break;
                case WAD_FILE_SFX:
                    asset_load_sfx(gAssets + v0);
                    break;
                case WAD_FILE_SP3:
                    asset_reload_sp3(gAssets + v0);
                    break;
                case WAD_FILE_K2:
                    asset_reload_k2(gAssets + v0);
                    break;
                case WAD_FILE_K3:
                    asset_reload_k3(gAssets + v0);
                    break;
                case WAD_FILE_K4:
                    asset_reload_k4(gAssets + v0);
                    break;
                case WAD_FILE_K5:
                    asset_reload_k5(gAssets + v0);
                    break;
            }
        } else if (file[i].unpackedSize <= free_memory) {
            str_copy(gAssets[gNumAssets].name, file[i].name);
            gAssets[gNumAssets].size = file[i].size;
            gAssets[gNumAssets].context = context;
            gAssets[gNumAssets].type = file[i].type;
            gAssets[gNumAssets].romAddr = gWadRomAddress + file[i].offset;
            gAssets[gNumAssets].unpacked_size = file[i].unpackedSize;

            if (file[i].size != file[i].unpackedSize) {
                gAssets[gNumAssets].flags = 2;
                gNumAssets++;
            } else {
                gAssets[gNumAssets].flags = 0;
                gNumAssets++;
            }

            switch (file[i].type) {
                case WAD_FILE_ANM:
                    func_80026DF0(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_TEX:
                    asset_load_tex(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SP2:
                    asset_load_sp2(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_3:
                    func_800271C0(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_GMD:
                    asset_load_gmd(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_TMD:
                    asset_load_tmd(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_CTL:
                    asset_load_ctl(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SEQ:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    asset_load_seq(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_TBL:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    asset_load_tbl(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SP3:
                    asset_load_sp3(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SFB:
                    asset_load_sfb(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SFX:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    asset_load_sfx(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K2:
                    asset_load_k2(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_MOV:
                    asset_load_mov(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_OC:
                    asset_load_oc(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_SYM:
                    asset_load_sym(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_VOX:
                    asset_load_vox(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K3:
                    asset_load_k3(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K4:
                    asset_load_k4(gAssets + gNumAssets - 1);
                    break;
                case WAD_FILE_K5:
                    asset_load_k5(gAssets + gNumAssets - 1);
                    break;
                default:
                    func_80026BE0(gAssets + gNumAssets - 1);
                    break;
            }
        }
    }
}

void func_80026A94(Asset *asset, s32 size) {
    s32 index;
    index = mem_alloc_slot(size);
    asset->memory_slot = index;
    asset->data = D_8005AEB8[index].data;
}

void func_80026AD4(Asset *arg0) {
    mem_free_slot(arg0->memory_slot);
    arg0->memory_slot = -1;
}

void func_80026B04(Asset *arg0) {
    mem_free_slot(arg0->aux_memory_slot);
    arg0->aux_memory_slot = -1;
}

void func_80026B34(Asset *arg0, s32 arg1) {
    s32 index;
    index = mem_alloc_slot(arg1);
    arg0->aux_memory_slot = index;
    arg0->aux_data = D_8005AEB8[index].data;
}

void func_80026B74(Asset *arg0) {
    arg0->flags = 1;

    if (arg0->memory_slot >= 0) {
        mem_free_slot(arg0->memory_slot);
    }

    if (arg0->aux_memory_slot >= 0) {
        mem_free_slot(arg0->aux_memory_slot);
    }

    arg0->memory_slot = -1;
    arg0->aux_memory_slot = -1;
    arg0->name[0] = '\0';
    arg0->data = arg0->aux_data = NULL;
}

void func_80026BE0(Asset *asset) {
    func_80026A94(asset, asset->unpacked_size);
    if (asset->flags & 2) {
        func_80025A0C(asset);
    } else {
        dma_read(asset->romAddr, asset->data, asset->unpacked_size);
    }
}

void assets_clear_unused(void) {
    u32 i, j;
    u32 s3;

    s3 = 0;
    for (i = 0; i < gNumAssets; i++) {
        if (gAssets[i].flags & 1) {
            for (j = i + 1; j < gNumAssets; j++) {
                if (!(gAssets[j].flags & 1)) {
                    break;
                }
            }

            if (j != gNumAssets) {
                gAssets[i].data = gAssets[j].data;
                gAssets[i].aux_data = gAssets[j].aux_data;
                gAssets[i].size = gAssets[j].size;
                gAssets[i].unpacked_size = gAssets[j].unpacked_size;
                gAssets[i].type = gAssets[j].type;
                gAssets[i].flags = gAssets[j].flags;
                gAssets[i].memory_slot = gAssets[j].memory_slot;
                gAssets[i].aux_memory_slot = gAssets[j].aux_memory_slot;
                gAssets[i].context = gAssets[j].context;
                str_copy(gAssets[i].name, gAssets[j].name);
                gAssets[j].name[0] = '\0';
                gAssets[j].aux_memory_slot = -1;
                gAssets[j].memory_slot = -1;
                gAssets[j].flags = 1;
                s3++;
            } else {
                gAssets[i].name[0] = '\0';
                gAssets[i].aux_memory_slot = -1;
                gAssets[i].memory_slot = -1;
                gAssets[i].flags = 1;
                gNumAssets = s3;
                return;
            }
        } else {
            s3++;
        }
    }

    gNumAssets = s3;
    for (i = 0; i < gNumAssets; i++) {}
}

void func_80026DF0(Asset *asset) {
    AnimAsset *animAsset;
    s32 a3;
    u32 i;
    s32 *v1;
    AnimHeader **v0;
    u32 a0;

    func_80026BE0(asset);
    animAsset = (AnimHeader **) asset->data;
    a3 = animAsset->unk_00;

    a0 = (u32) ((u32) animAsset + 4 + 4 * a3);
    v1 = animAsset->unk_04;

    for (i = 0; i < a3; i++) {
        v0 = animAsset;
        v0[i] = (AnimHeader *) (a0 + v1[i]);
    }

    asset->aux_data = a3;
}

void asset_load_tex(Asset *asset) {
    func_80026BE0(asset);
}

void func_80026EEC(Asset *asset) {
    AssetSP2 *header;
    s32 i;
    AssetSP2Sub2 *entry;
    TextureAsset *textures[4];

    header = asset->data;
    entry = header->sprites;
    for (i = 0; i < 4 && (header->texture_name[i][0]) != '\0'; i++) {
        textures[i] = gAssets[asset_find(header->texture_name[i], asset->context)].data;
    }

    for (i = 0; i < header->numSprites; i++, entry++) {
        entry->texture = textures[entry->tex_index];
    }
}

#ifdef NON_MATCHING
void func_80027004(AssetSP2 *arg0, AssetSP2 *arg1, s32 arg2) {
    s32 addr_diff;
    u32 i;
    AssetSP2Sub2 *a2;
    AssetSP2 *v1;

    addr_diff = ((u32) arg0 - (u32) arg1);
    v1 = arg0;
    a2 = arg0->sprites = (AssetSP2Sub2 *) ((u32) arg0->sprites + addr_diff);

    for (i = 0; i < v1->numSprites; i++) {
        a2[i].parts = (AssetSP2Sub3 *) ((u32) a2[i].parts + addr_diff);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/wad/func_80027004.s")
void func_80027004(AssetSP2 *arg0, AssetSP2 *arg1, s32 arg2);
#endif

#ifdef NON_MATCHING
void asset_load_sp2(Asset *asset) {
    AssetSP2 *header;
    s32 i;
    AssetSP2Sub2 *entry;
    u8 *raster;
    u16 *palette;
    TextureAsset *textures[4];
    AssetSP2Sub2 *tmp;
    s32 unused[2];

    func_80026BE0(asset);
    entry = tmp = (AssetSP2Sub2 *) ((s32) header->sprites + (u8 *) header);
    header = asset->data;
    entry = tmp = (AssetSP2Sub2 *) ((s32) header->sprites + (u8 *) header);
    header->sprites = tmp;
    for (i = 0; i < 4 && (header->texture_name[i][0]) != '\0'; i++) {
        textures[i] = gAssets[asset_find(header->texture_name[i], asset->context)].data;

        raster = textures[i]->data;
        palette = (u16 *) &textures[i]->data[textures[i]->height * textures[i]->width];
        palette[raster[0]] = 0;
    }

    for (i = 0; i < header->numSprites; i++, entry++) {
        entry->parts = entry->parts + (s32) header;
        entry->texture = textures[entry->tex_index];
    }

    heap_set_move_callback(asset->memory_slot, func_80027004, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/wad/asset_load_sp2.s")
#endif

void func_800271C0(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkFrodo *sp38;
    s32 sp34;
    s32 sp30;
    AssetGmd *sp2C;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp34 = asset->memory_slot;
    sp30 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp30 * sizeof(ModelNodeAsset) + sp30 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    sp2C = (AssetGmd *) (asset->data);
    sp2C->numNodes = sp30;
    func_8000C0E4(sp2C, sp34);

    sp38 = mem_alloc(sizeof(UnkFrodo), "wad.c", 742);
    func_8000DAB0(sp38, sp2C, asset->name, 0, asset->context);
    asset->aux_data = sp38;
}

void asset_load_gmd(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkFrodo *sp38;
    s32 sp34;
    s32 sp30;
    AssetGmd *sp2C;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp34 = asset->memory_slot;
    sp30 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp30 * sizeof(ModelNodeAsset) + sp30 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    sp2C = (AssetGmd *) (asset->data);
    sp2C->numNodes = sp30;
    func_8000C0E4(sp2C, sp34);

    sp38 = mem_alloc(sizeof(UnkFrodo), "wad.c", 777);
    func_8000DAB0(sp38, sp2C, asset->name, 1, asset->context);
    asset->aux_data = sp38;
}

void asset_load_k3(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkSam *sp30;
    s32 sp2C;
    s32 sp28;
    AssetGmd *s1;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp2C = asset->memory_slot;
    sp28 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp28 * sizeof(ModelNodeAsset) + sp28 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    s1 = (AssetGmd *) (asset->data);
    s1->numNodes = sp28;
    func_8000C0E4(s1, sp2C);

    sp30 = mem_alloc(sizeof(UnkSam), "wad.c", 813);
    s1->unk_C8 = 1;
    func_8000E73C(sp30, s1, asset->name, 0, &D_80049968, asset->context);
    sp30->unk_3CC = 0x10;
    asset->aux_data = sp30;
    s1->unk_C8 = 0;
}

void asset_load_k4(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkSam *sp30;
    s32 sp2C;
    s32 sp28;
    AssetGmd *s1;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp2C = asset->memory_slot;
    sp28 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp28 * sizeof(ModelNodeAsset) + sp28 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    s1 = (AssetGmd *) (asset->data);
    s1->numNodes = sp28;
    func_8000C0E4(s1, sp2C);

    sp30 = mem_alloc(sizeof(UnkSam), "wad.c", 854);
    s1->unk_C8 = 1;
    func_8000E73C(sp30, s1, asset->name, 0, &D_80049938, asset->context);
    sp30->unk_3CC = 2;
    asset->aux_data = sp30;
    s1->unk_C8 = 0;
}

void asset_load_k5(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkSam *sp30;
    s32 sp2C;
    s32 sp28;
    AssetGmd *s1;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp2C = asset->memory_slot;
    sp28 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp28 * sizeof(ModelNodeAsset) + sp28 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    s1 = (AssetGmd *) (asset->data);
    s1->numNodes = sp28;
    func_8000C0E4(s1, sp2C);

    sp30 = mem_alloc(sizeof(UnkSam), "wad.c", 893);
    s1->unk_C8 = 1;
    func_8000E73C(sp30, s1, asset->name, 0, &D_80049950, asset->context);
    sp30->unk_3CC = 1;
    func_80035CCC(sp30);
    asset->aux_data = sp30;
    s1->unk_C8 = 0;
}

void asset_load_tmd(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkSam *sp30;
    s32 sp2C;
    s32 sp28;
    AssetGmd *s1;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp2C = asset->memory_slot;
    sp28 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp28 * sizeof(ModelNodeAsset) + sp28 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    s1 = (AssetGmd *) (asset->data);
    s1->numNodes = sp28;
    func_8000C0E4(s1, sp2C);

    sp30 = mem_alloc(sizeof(UnkSam), "wad.c", 934);
    s1->unk_C8 = 1;
    func_8000E73C(sp30, s1, asset->name, 0, &D_80049920, asset->context);
    sp30->unk_3CC = 8;
    func_8000E0D8(sp30);
    asset->aux_data = sp30;
    s1->unk_C8 = 0;
}

void func_80027680(Asset *asset) {
    UnkFrodo *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkFrodo), "wad.c", 950);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000DAB0(s0, sp28, asset->name, 0, asset->context);
    asset->aux_data = s0;
}

void asset_reload_tmd(Asset *asset) {
    UnkSam *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkSam), "wad.c", 963);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000E73C(s0, sp28, asset->name, 0, &D_80049920, asset->context);
    func_8000E0D8(s0);
    s0->unk_3CC = 8;
    asset->aux_data = s0;
}

void asset_reload_k3(Asset *asset) {
    UnkSam *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkSam), "wad.c", 977);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000E73C(s0, sp28, asset->name, 0, &D_80049968, asset->context);
    s0->unk_3CC = 0x10;
    asset->aux_data = s0;
}

void asset_reload_k4(Asset *asset) {
    UnkSam *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkSam), "wad.c", 991);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000E73C(s0, sp28, asset->name, 0, &D_80049938, asset->context);
    s0->unk_3CC = 2;
    asset->aux_data = s0;
}

void asset_reload_k5(Asset *asset) {
    UnkSam *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkSam), "wad.c", 1005);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000E73C(s0, sp28, asset->name, 0, &D_80049950, asset->context);
    s0->unk_3CC = 1;
    func_80035CCC(s0);
    asset->aux_data = s0;
}

void asset_reload_gmd(Asset *asset) {
    UnkFrodo *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkFrodo), "wad.c", 1019);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000DAB0(s0, sp28, asset->name, 1, asset->context);
    asset->aux_data = s0;
}

void asset_load_ctl(Asset *asset) {
    func_80026BE0(asset);
    if (asset->data != NULL) {
        gMusicBankFileSize = asset->unpacked_size;
        mem_move(gMusicBankFile, asset->data, gMusicBankFileSize);
        func_80026B74(asset);
    }
}

void asset_load_tbl(Asset *asset) {
    if (asset->data != 0) {
        alBnkfNew(gMusicBankFile, asset->data);
    }
}

void asset_load_seq(Asset *asset) {
    if (asset->data != NULL) {
        gCurrentSongDataSize = asset->unpacked_size;
        gCurrentSongData = asset->data;
        alSeqNew(gMusicSequence, gCurrentSongData, gCurrentSongDataSize);
        alSeqNewMarker(gMusicSequence, &gMusicMarkerStart, 0);
        alSeqNewMarker(gMusicSequence, &gMusicMarkerEnd, 0xFFFFFFFF);
        alSeqpLoop(gMusicPlayer, &gMusicMarkerStart, &gMusicMarkerEnd, -1);

        alSeqpSetBank(gMusicPlayer, gMusicBankFile->bankArray[0]);
        alSeqpSetSeq(gMusicPlayer, gMusicSequence);
        alSeqpSetVol(gMusicPlayer, gMusicVolume);
        gMusicIsPlaying = TRUE;
        gMusicVolumeFading = gMusicVolume;
    }
}

void asset_load_vox(Asset *asset) {
    func_80026BE0(asset);
    if (asset->data != NULL) {
        mem_move(gAudioBankFiles[2], asset->data, asset->unpacked_size);
        gSfxPlayerOn[2] = 1;
        func_80026B74(asset);
        sound_init_player(gAudioBankFiles[2], D_7DE880, 2);
    }
}

void asset_load_sfb(Asset *asset) {
    s32 playerID;

    playerID = asset->context;
    if (playerID >= 2U) {
        playerID = 2;
    }

    func_80026BE0(asset);
    if (asset->data != NULL) {
        mem_move(gAudioBankFiles[playerID], asset->data, asset->unpacked_size);
        gSfxPlayerOn[playerID] = TRUE;
        func_80026B74(asset);
    }
}

void asset_load_sfx(Asset *asset) {
    s32 playerID;

    playerID = asset->context;

    if (asset->data != NULL) {
        if (playerID >= 2U) {
            playerID = 2;
        }
        sound_init_player(gAudioBankFiles[playerID], asset->data, playerID);
    }
}

void func_80027C54(Batch *arg0, Gfx **arg1) {
    Gfx *gfx;
    if (arg1 == NULL) {
        gtStateSetOthermode(&arg0->info->header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    } else {
        gfx = *arg1;
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        *arg1 = gfx;
    }
}

void asset_load_sp3(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkSam *sp30;
    s32 sp2C;
    s32 sp28;
    AssetGmd *s1;
    char *name;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp2C = asset->memory_slot;
    sp28 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp28 * sizeof(ModelNodeAsset) + sp28 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    s1 = (AssetGmd *) (asset->data);
    s1->numNodes = sp28;
    func_8000C0E4(s1, sp2C);

    sp30 = mem_alloc(sizeof(UnkSam), "wad.c", 1226);
    s1->unk_C8 = 1;
    name = asset->name;
    func_8000E73C(sp30, s1, asset->name, 0, &D_80049950, asset->context);
    s1->unk_C8 = 0;
    asset->aux_data = sp30;
    strlen(name);
}

void asset_load_oc(Asset *asset) {
    func_80026BE0(asset);
}

void asset_reload_sp3(Asset *asset) {
    UnkSam *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkSam), "wad.c", 1257);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000E73C(s0, sp28, asset->name, 0, &D_80049950, asset->context);
    asset->aux_data = s0;
}

void asset_load_k2(Asset *asset) {
    AssetUnkHeader *unkHeader;
    UnkSam *sp30;
    s32 sp2C;
    s32 sp28;
    AssetGmd *s1;

    func_80026BE0(asset);
    unkHeader = asset->data;
    sp2C = asset->memory_slot;
    sp28 = unkHeader->numEntries;
    asset->aux_memory_slot = asset->memory_slot;
    asset->size = sp28 * sizeof(ModelNodeAsset) + sp28 * sizeof(BatchAsset) + sizeof(AssetGmd);

    func_80026A94(asset, asset->size);
    s1 = (AssetGmd *) (asset->data);
    s1->numNodes = sp28;
    func_8000C0E4(s1, sp2C);

    sp30 = mem_alloc(sizeof(UnkSam), "wad.c", 1297);
    s1->unk_C8 = 1;
    func_8000E73C(sp30, s1, asset->name, 0, &D_80049950, asset->context);
    sp30->unk_3CC = 4;
    func_80035CCC(sp30);
    asset->aux_data = sp30;
    s1->unk_C8 = 0;
}

void asset_reload_k2(Asset *asset) {
    UnkSam *s0;
    AssetGmd *sp28;

    s0 = mem_alloc(sizeof(UnkSam), "wad.c", 1314);
    sp28 = asset->data;

    func_8000BE18(sp28);
    func_8000E73C(s0, sp28, asset->name, 0, &D_80049950, asset->context);
    s0->unk_3CC = 4;
    func_80035CCC(s0);
    asset->aux_data = s0;
}

void asset_load_mov(Asset *asset) {
    if (D_8013C228 != NULL) {
        D_8013C228(asset);
    } else {
        func_80026BE0(asset);
    }
}

void asset_load_sym(Asset *asset) {
    if (D_800B6328[asset->context].unk_0E != 0) {
        func_80026BE0(asset);
    }
}
