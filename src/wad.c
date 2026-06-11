#include "common.h"
#include "ld_addrs.h"
#include "string.h"
#include "PR/gt.h"

enum WadFileType {
    WAD_ANM = 0,
    WAD_TEX = 1,
    WAD_SP2 = 2,
    WAD_KMD = 3,
    WAD_WAD = 4,
    WAD_DB = 5,
    WAD_PCL = 6,
    WAD_GMD = 7,
    WAD_TMD = 8,
    WAD_SEQ = 9,
    WAD_CTL = 10,
    WAD_TBL = 11,
    WAD_SP3 = 12,
    WAD_SFB = 13,
    WAD_SFX = 14,
    WAD_K2 = 15,
    WAD_MOV = 16,
    WAD_OC = 17,
    WAD_SYM = 18,
    WAD_VOX = 19,
    WAD_K3 = 20,
    WAD_K4 = 21,
    WAD_K5 = 22
};

typedef struct WadFolder {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 x_a0917d8d;
    /* 0x1C */ s32 x_d88e3a03;
} WadFolder; // size >= 0x20

typedef struct WadFileEntry {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 type;
    /* 0x1C */ s32 size;
    /* 0x20 */ s32 x_f1860703;
} WadFileEntry; // size = 0x24

typedef struct WadHeader {
    /* 0x00 */ u32 x_c6a89d30;
    /* 0x04 */ u32 x_1256da71; // unknown, same as numFolders
    /* 0x08 */ WadFolder x_63b85330[1];
} WadHeader;

typedef struct WadAnmHeader {
    /* 0x00 */ s32 x_af0aa1f8;
    /* 0x04 */ s32 x_1256da71[1];
} WadAnmHeader;

s32 sWadEntryCount = 0;

x_80d298c9 sWadEntries[256];
s32 sWadHeader;
WadHeader *sWadHeaderPtr;
s32 sWadDataEnd;
u8 *sWadDataPtr;
WadFolder *sWadFolder;
s32 sWadBufferSizeHdr;
s32 sWadBufferSizeData;
u32 sWadFileCount;
u32 sWadFolderCount;
s16 sWadUnk1;
s16 sWadUnk2;
void (*sWadMovCallback)(x_80d298c9 *);

void wad_setup_sfx_bank(ALBankFile *x_cc1d0de5, u8 *x_84ff873b, u32 x_2092f891);
void mem_copy_overlap(u32 *dest, u32 *src, u32 size);
void anim_buffer_resolve(x_13162abc *, s32);
void model_scaffold_register(x_82e80914 *, x_13162abc *, char *, s32, u16);
void lzhuf_start(x_80d298c9 *);
void wad_load_all(s32);
void wad_compact_entries(void);
void dma_read_sync(s32 romAddr, void *x_dda6dc06, s32 size);
void model_create_from_kmd(Model *, x_13162abc *, char *, s32, x_d8e0705d *, u16);
void model_bone_setup(Model *);
void model_anim_setup(Model *);

void wad_entry_free(x_80d298c9 *);
void wad_resolve_kmd(x_80d298c9 *);
void anim_buffer_relocate(x_13162abc *);

void wad_resolve_tmd(x_80d298c9 *);
void wad_resolve_gmd(x_80d298c9 *);
void wad_resolve_sp2(x_80d298c9 *);
void wad_resolve_tbl(x_80d298c9 *);
void wad_resolve_seq(x_80d298c9 *);
void wad_resolve_sfx(x_80d298c9 *);
void wad_resolve_sp3(x_80d298c9 *);
void wad_resolve_k2(x_80d298c9 *);
void wad_resolve_k3(x_80d298c9 *);
void wad_resolve_k4(x_80d298c9 *);
void wad_resolve_k5(x_80d298c9 *);
void wad_load_anm(x_80d298c9 *);
void wad_load_tex(x_80d298c9 *);
void wad_load_sp2(x_80d298c9 *);
void wad_load_kmd(x_80d298c9 *);
void wad_load_gmd(x_80d298c9 *);
void wad_load_k3(x_80d298c9 *);
void wad_load_k4(x_80d298c9 *);
void wad_load_k5(x_80d298c9 *);
void wad_load_tmd(x_80d298c9 *);
void wad_load_ctl(x_80d298c9 *);
void wad_load_vox(x_80d298c9 *);
void wad_load_sfb(x_80d298c9 *);
void wad_load_sp3(x_80d298c9 *);
void wad_load_oc(x_80d298c9 *);
void wad_load_k2(x_80d298c9 *);
void wad_load_mov(x_80d298c9 *);
void wad_load_sym(x_80d298c9 *);

void wad_debug_loop(void) {
    u32 i;

    for (i = 0; i < sWadEntryCount; i++) {}
}

void wad_strcat(char *x_0618013f, char *src) {
    u32 x_648569c9 = strlen(x_0618013f);
    u32 x_842e9df0 = strlen(src);
    s32 i;

    for (i = 0; i < x_842e9df0; i++) {
        x_0618013f[x_648569c9 + i] = *src++;
    }

    x_0618013f[x_648569c9 + x_842e9df0] = 0;
}

void wad_strcpy(char *x_cc1d0de5, char *x_84ff873b) {
    u32 size = strlen(x_84ff873b);
    s32 i;

    for (i = 0; i < size; i++) {
        *x_cc1d0de5++ = *x_84ff873b++;
    }

    *x_cc1d0de5 = 0;
}

s32 wad_streq(char *x_cc1d0de5, char *x_84ff873b) {
    u32 x_4346f5cb;
    u32 x_1ca25edc;
    u32 i;

    x_4346f5cb = strlen(x_cc1d0de5);
    x_1ca25edc = strlen(x_84ff873b);
    if (x_4346f5cb != x_1ca25edc) {
        return 1;
    }

    for (i = 0; i < x_4346f5cb; i++) {
        if (*x_cc1d0de5++ != *x_84ff873b++) {
            return 1;
        }
    }

    return 0;
}

void wad_strupr(char *str) {
    u32 size = strlen(str);
    u32 i;

    for (i = 0; i < size; i++) {
        str[i] = (str[i] >= 'a') ? str[i] -= 'a' - 'A' : str[i];
    }
}

u32 wad_entry_find(char *name, u32 context) {
    u32 i;

    wad_strupr(name);
    for (i = 0; i < sWadEntryCount; i++) {
        if (wad_streq(name, sWadEntries[i].name) == 0 && context == sWadEntries[i].context) {
            return i;
        }
    }

    return -1;
}

void wad_entries_reset(void) {
    u32 i;

    sWadEntryCount = 0;
    for (i = 0; i < 256; i++) {
        sWadEntries[i].x_d5b87ce9 = sWadEntries[i].x_89bf4f22 = -1;
        sWadEntries[i].flags = 1;
        sWadEntries[i].name[0] = '\0';
    }
}

void wad_load_area_init(s32 x_cc1d0de5, s32 size) {
    sWadHeader = x_cc1d0de5;
    sWadHeaderPtr = sWadHeader;
    sWadDataEnd = sWadHeader + 0x2800;
    sWadBufferSizeHdr = sWadDataEnd - x_cc1d0de5;
    sWadBufferSizeData = size - sWadBufferSizeHdr;
}

void wad_open_nested(char *name) {
    s32 i;
    char x_7244b466[20];
    WadFileEntry *x_7e19d904;
    WadFileEntry *file;

    x_7e19d904 = sWadFolder->offset + (u8 *) sWadHeaderPtr;
    wad_strcpy(x_7244b466, name);
    wad_strcat(x_7244b466, ".WAD");

    for (i = 0, file = x_7e19d904; i < sWadFileCount; i++, file++) {
        if (wad_streq(file->name, x_7244b466) == 0) {
            sWadDataPtr += file->offset;
            return;
        }
        if (file && file) {
            // FAKE MATCH
        }
    }
}

s32 wad_select_folder(char *x_e2308d38) {
    s32 pad;
    u32 i;
    WadFolder *x_63b85330;

    x_63b85330 = sWadHeaderPtr->x_63b85330;
    for (i = 0; i < sWadFolderCount; i++) {
        if (wad_streq(x_e2308d38, x_63b85330[i].name) == 0) {
            sWadFolder = &x_63b85330[i];
            sWadFolderCount = 1;
            sWadFileCount = x_63b85330[i].x_a0917d8d;
            return TRUE;
        }
    }

    return FALSE;
}

void wad_open(char *name) {
    if (name[0] == '\0') {
        // load root wad
        sWadDataPtr = resources_ROM_START;
        dma_read_sync(sWadDataPtr, sWadHeaderPtr, sWadBufferSizeHdr);
        sWadFolder = sWadHeaderPtr->x_63b85330;
        sWadFolderCount = sWadHeaderPtr->x_c6a89d30;
        sWadFileCount = sWadFolder->x_a0917d8d;
    } else if (wad_select_folder(name)) {
        // select folder in current wad file
    } else {
        wad_open_nested(name);
        dma_read_sync(sWadDataPtr, sWadHeaderPtr, sWadBufferSizeHdr);
        sWadFolder = sWadHeaderPtr->x_63b85330;
        sWadFolderCount = sWadHeaderPtr->x_c6a89d30;
        sWadFileCount = sWadFolder[0].x_a0917d8d;
    }
}

void wad_open_path(char *x_a0af9f86) {
    s32 len;
    char x_3893a365[24];
    u32 i;
    u32 j;

    len = strlen(x_a0af9f86);
    j = 0;
    wad_strupr(x_a0af9f86);
    x_3893a365[0] = '\0';

    for (i = 0; i < len; i++) {
        if (x_a0af9f86[i] != '/') {
            x_3893a365[j++] = x_a0af9f86[i];
        } else {
            x_3893a365[j] = '\0';
            j = 0;
            wad_open(x_3893a365);
        }
    }

    x_3893a365[j] = '\0';
    wad_open(x_3893a365);
}

void wad_sync_dma_slots(void) {
    u32 i;

    for (i = 0; i < sWadEntryCount; i++) {
        if (sWadEntries[i].x_d5b87ce9 >= 0) {
            sWadEntries[i].data = sDmaSlots[sWadEntries[i].x_d5b87ce9].data;
        }
        if (sWadEntries[i].x_89bf4f22 >= 0) {
            sWadEntries[i].x_4962fc73 = sDmaSlots[sWadEntries[i].x_89bf4f22].data;
        }
    }
}

void wad_load_path(char *x_a0af9f86, s32 context) {
    wad_compact_entries();
    wad_open_path(x_a0af9f86);
    wad_load_all(context);
    mem_set(sWadHeaderPtr, 0, sWadBufferSizeHdr);
    wad_compact_entries();
}

void wad_unload_context(s32 context) {
    u32 i;

    for (i = 0; i < sWadEntryCount; i++) {
        if (context == sWadEntries[i].context) {
            wad_entry_free(sWadEntries + i);
        }
    }

    wad_compact_entries();
}

void wad_unload_all(void) {
    u32 i;

    for (i = 0; i < sWadEntryCount; i++) {
        wad_entry_free(sWadEntries + i);
    }

    wad_compact_entries();
}

void wad_unload_type(s32 x_cc1d0de5) {
    u32 i;

    for (i = 0; i < sWadEntryCount; i++) {
        if (x_cc1d0de5 == sWadEntries[i].type) {
            wad_entry_free(sWadEntries + i);
        }
    }

    wad_compact_entries();
}

void wad_load_all(s32 context) {
    s32 pad[2];
    u32 i;
    u32 x_8a28cdcb;
    WadFileEntry *file;
    s32 v0;

    x_8a28cdcb = mem_free_space(sMemFreeList);
    file = (WadFileEntry *) ((u8 *) sWadHeaderPtr + sWadFolder->offset);

    for (i = 0; i < sWadFileCount; i++) {
        v0 = wad_entry_find(file[i].name, context);

        if (v0 >= 0) {
            switch (file[i].type) {
                case WAD_KMD:
                    wad_resolve_kmd(sWadEntries + v0);
                    break;
                case WAD_TMD:
                    wad_resolve_tmd(sWadEntries + v0);
                    break;
                case WAD_GMD:
                    wad_resolve_gmd(sWadEntries + v0);
                    break;
                case WAD_SP2:
                    wad_resolve_sp2(sWadEntries + v0);
                    break;
                case WAD_TBL:
                    wad_resolve_tbl(sWadEntries + v0);
                    break;
                case WAD_SEQ:
                    wad_resolve_seq(sWadEntries + v0);
                    break;
                case WAD_SFX:
                    wad_resolve_sfx(sWadEntries + v0);
                    break;
                case WAD_SP3:
                    wad_resolve_sp3(sWadEntries + v0);
                    break;
                case WAD_K2:
                    wad_resolve_k2(sWadEntries + v0);
                    break;
                case WAD_K3:
                    wad_resolve_k3(sWadEntries + v0);
                    break;
                case WAD_K4:
                    wad_resolve_k4(sWadEntries + v0);
                    break;
                case WAD_K5:
                    wad_resolve_k5(sWadEntries + v0);
                    break;
            }
        } else if (file[i].x_f1860703 <= x_8a28cdcb) {
            wad_strcpy(sWadEntries[sWadEntryCount].name, file[i].name);
            sWadEntries[sWadEntryCount].size = file[i].size;
            sWadEntries[sWadEntryCount].context = context;
            sWadEntries[sWadEntryCount].type = file[i].type;
            sWadEntries[sWadEntryCount].romAddr = sWadDataPtr + file[i].offset;
            sWadEntries[sWadEntryCount].x_f33d7764 = file[i].x_f1860703;

            if (file[i].size != file[i].x_f1860703) {
                sWadEntries[sWadEntryCount].flags = 2;
                sWadEntryCount++;
            } else {
                sWadEntries[sWadEntryCount].flags = 0;
                sWadEntryCount++;
            }

            switch (file[i].type) {
                case WAD_ANM:
                    wad_load_anm(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_TEX:
                    wad_load_tex(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_SP2:
                    wad_load_sp2(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_KMD:
                    wad_load_kmd(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_GMD:
                    wad_load_gmd(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_TMD:
                    wad_load_tmd(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_CTL:
                    wad_load_ctl(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_SEQ:
                    wad_entry_load_data(sWadEntries + sWadEntryCount - 1);
                    wad_resolve_seq(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_TBL:
                    wad_entry_load_data(sWadEntries + sWadEntryCount - 1);
                    wad_resolve_tbl(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_SP3:
                    wad_load_sp3(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_SFB:
                    wad_load_sfb(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_SFX:
                    wad_entry_load_data(sWadEntries + sWadEntryCount - 1);
                    wad_resolve_sfx(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_K2:
                    wad_load_k2(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_MOV:
                    wad_load_mov(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_OC:
                    wad_load_oc(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_SYM:
                    wad_load_sym(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_VOX:
                    wad_load_vox(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_K3:
                    wad_load_k3(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_K4:
                    wad_load_k4(sWadEntries + sWadEntryCount - 1);
                    break;
                case WAD_K5:
                    wad_load_k5(sWadEntries + sWadEntryCount - 1);
                    break;
                default:
                    wad_entry_load_data(sWadEntries + sWadEntryCount - 1);
                    break;
            }
        }
    }
}

void wad_entry_alloc_dma(x_80d298c9 *x_d59386e0, s32 size) {
    s32 index;
    index = mem_dma_alloc(size);
    x_d59386e0->x_d5b87ce9 = index;
    x_d59386e0->data = sDmaSlots[index].data;
}

void wad_entry_free_dma(x_80d298c9 *x_cc1d0de5) {
    mem_dma_free(x_cc1d0de5->x_d5b87ce9);
    x_cc1d0de5->x_d5b87ce9 = -1;
}

void wad_entry_free_unpacked(x_80d298c9 *x_cc1d0de5) {
    mem_dma_free(x_cc1d0de5->x_89bf4f22);
    x_cc1d0de5->x_89bf4f22 = -1;
}

void wad_entry_alloc_unpacked(x_80d298c9 *x_cc1d0de5, s32 x_84ff873b) {
    s32 index;
    index = mem_dma_alloc(x_84ff873b);
    x_cc1d0de5->x_89bf4f22 = index;
    x_cc1d0de5->x_4962fc73 = sDmaSlots[index].data;
}

void wad_entry_free(x_80d298c9 *x_d59386e0) {
    x_d59386e0->flags = 1;

    if (x_d59386e0->x_d5b87ce9 >= 0) {
        mem_dma_free(x_d59386e0->x_d5b87ce9);
    }

    if (x_d59386e0->x_89bf4f22 >= 0) {
        mem_dma_free(x_d59386e0->x_89bf4f22);
    }

    x_d59386e0->x_d5b87ce9 = -1;
    x_d59386e0->x_89bf4f22 = -1;
    x_d59386e0->name[0] = '\0';
    x_d59386e0->data = x_d59386e0->x_4962fc73 = NULL;
}

void wad_entry_load_data(x_80d298c9 *x_d59386e0) {
    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->x_f33d7764);
    if (x_d59386e0->flags & 2) {
        lzhuf_start(x_d59386e0);
    } else {
        dma_read_sync(x_d59386e0->romAddr, x_d59386e0->data, x_d59386e0->x_f33d7764);
    }
}

void wad_compact_entries(void) {
    u32 i, j;
    u32 s3;

    s3 = 0;
    for (i = 0; i < sWadEntryCount; i++) {
        if (sWadEntries[i].flags & 1) {
            for (j = i + 1; j < sWadEntryCount; j++) {
                if (!(sWadEntries[j].flags & 1)) {
                    break;
                }
            }

            if (j != sWadEntryCount) {
                sWadEntries[i].data = sWadEntries[j].data;
                sWadEntries[i].x_4962fc73 = sWadEntries[j].x_4962fc73;
                sWadEntries[i].size = sWadEntries[j].size;
                sWadEntries[i].x_f33d7764 = sWadEntries[j].x_f33d7764;
                sWadEntries[i].type = sWadEntries[j].type;
                sWadEntries[i].flags = sWadEntries[j].flags;
                sWadEntries[i].x_d5b87ce9 = sWadEntries[j].x_d5b87ce9;
                sWadEntries[i].x_89bf4f22 = sWadEntries[j].x_89bf4f22;
                sWadEntries[i].context = sWadEntries[j].context;
                wad_strcpy(sWadEntries[i].name, sWadEntries[j].name);
                sWadEntries[j].name[0] = '\0';
                sWadEntries[j].x_89bf4f22 = -1;
                sWadEntries[j].x_d5b87ce9 = -1;
                sWadEntries[j].flags = 1;
                s3++;
            } else {
                sWadEntries[i].name[0] = '\0';
                sWadEntries[i].x_89bf4f22 = -1;
                sWadEntries[i].x_d5b87ce9 = -1;
                sWadEntries[i].flags = 1;
                sWadEntryCount = s3;
                return;
            }
        } else {
            s3++;
        }
    }

    sWadEntryCount = s3;
    for (i = 0; i < sWadEntryCount; i++) {}
}

void wad_load_anm(x_80d298c9 *x_d59386e0) {
    WadAnmHeader *x_eecaffc6;
    s32 a3;
    u32 i;
    s32 *v1;
    x_a05f18ad **v0;
    u32 a0;

    wad_entry_load_data(x_d59386e0);
    x_eecaffc6 = (x_a05f18ad **) x_d59386e0->data;
    a3 = x_eecaffc6->x_af0aa1f8;

    a0 = (u32) ((u32) x_eecaffc6 + 4 + 4 * a3);
    v1 = x_eecaffc6->x_1256da71;

    for (i = 0; i < a3; i++) {
        v0 = x_eecaffc6;
        v0[i] = (x_a05f18ad *) (a0 + v1[i]);
    }

    x_d59386e0->x_4962fc73 = a3;
}

void wad_load_tex(x_80d298c9 *x_d59386e0) {
    wad_entry_load_data(x_d59386e0);
}

void wad_resolve_sp2(x_80d298c9 *x_d59386e0) {
    x_8ab35fe5 *header;
    s32 i;
    x_7cc7ad58 *entry;
    x_3b6b80ec *textures[4];

    header = x_d59386e0->data;
    entry = header->x_a34b89cc;
    for (i = 0; i < 4 && (header->x_6fb24ac9[i][0]) != '\0'; i++) {
        textures[i] = sWadEntries[wad_entry_find(header->x_6fb24ac9[i], x_d59386e0->context)].data;
    }

    for (i = 0; i < header->x_5b30c492; i++, entry++) {
        entry->texture = textures[entry->x_51d6cf57];
    }
}

void wad_relocate_sp2(void *x_cc1d0de5, void *x_84ff873b, s32 x_2092f891) {
    s32 x_02efc187;
    s32 i;
    x_7cc7ad58 *a2;
    x_8ab35fe5 *v2;

    x_02efc187 = ((u32) x_cc1d0de5 - (u32) x_84ff873b);

    v2 = x_cc1d0de5;
    v2->x_a34b89cc = (x_7cc7ad58 *) ((u32) v2->x_a34b89cc + x_02efc187);

    for (a2 = v2->x_a34b89cc, i = 0; i < v2->x_5b30c492; i++, a2++) {
        a2->parts = (x_425d6ed3 *) ((u32) a2->parts + x_02efc187);
    }
}

void wad_load_sp2(x_80d298c9 *x_d59386e0) {
    x_8ab35fe5 *header;
    s32 i;
    x_7cc7ad58 *entry;
    u8 *x_925c481a;
    u16 *palette;
    x_3b6b80ec *textures[4];
    x_3b6b80ec **x_23b71842;
    s32 unused[2];

    wad_entry_load_data(x_d59386e0);
    x_23b71842 = textures; // required to match
    header = x_d59386e0->data;
    entry = header->x_a34b89cc = (x_7cc7ad58 *) ((u32) header->x_a34b89cc + (u32) header);
    if ((x_d59386e0->data && x_d59386e0->data) != 0) {} // required to match
    for (i = 0; i < 4 && (header->x_6fb24ac9[i][0]) != '\0'; i++) {
        textures[i] = sWadEntries[wad_entry_find(header->x_6fb24ac9[i], x_d59386e0->context)].data;

        palette = (u16 *) &textures[i]->data[x_23b71842[i]->height * x_23b71842[i]->width];
        x_925c481a = textures[i]->data;
        palette[x_925c481a[0]] = 0;
    }

    for (i = 0; i < header->x_5b30c492; i++, entry++) {
        entry->parts = (x_425d6ed3 *) ((s32) entry->parts + (s32) header);
        entry->texture = x_23b71842[entry->x_51d6cf57];
    }

    mem_dma_set_callback(x_d59386e0->x_d5b87ce9, wad_relocate_sp2, 0);
}

void wad_load_kmd(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    x_82e80914 *x_49781937;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    x_49781937 = mem_alloc_debug(sizeof(x_82e80914), "wad.c", 742);
    model_scaffold_register(x_49781937, x_3bfb7219, x_d59386e0->name, 0, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = x_49781937;
}

void wad_load_gmd(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    x_82e80914 *x_49781937;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    x_49781937 = mem_alloc_debug(sizeof(x_82e80914), "wad.c", 777);
    model_scaffold_register(x_49781937, x_3bfb7219, x_d59386e0->name, 1, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = x_49781937;
}

void wad_load_k3(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    model = mem_alloc_debug(sizeof(Model), "wad.c", 813);
    x_3bfb7219->x_14bc93c1 = 1;
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_eec8b086, x_d59386e0->context);
    model->x_8ac8f967 = 0x10;
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void wad_load_k4(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    model = mem_alloc_debug(sizeof(Model), "wad.c", 854);
    x_3bfb7219->x_14bc93c1 = 1;
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_bb5426b0, x_d59386e0->context);
    model->x_8ac8f967 = 2;
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void wad_load_k5(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    model = mem_alloc_debug(sizeof(Model), "wad.c", 893);
    x_3bfb7219->x_14bc93c1 = 1;
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 1;
    model_bone_setup(model);
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void wad_load_tmd(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    model = mem_alloc_debug(sizeof(Model), "wad.c", 934);
    x_3bfb7219->x_14bc93c1 = 1;
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fd763f4f, x_d59386e0->context);
    model->x_8ac8f967 = 8;
    model_anim_setup(model);
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void wad_resolve_kmd(x_80d298c9 *x_d59386e0) {
    x_82e80914 *s0;
    x_13162abc *x_3bfb7219;

    s0 = mem_alloc_debug(sizeof(x_82e80914), "wad.c", 950);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_scaffold_register(s0, x_3bfb7219, x_d59386e0->name, 0, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = s0;
}

void wad_resolve_tmd(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = mem_alloc_debug(sizeof(Model), "wad.c", 963);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fd763f4f, x_d59386e0->context);
    model_anim_setup(model);
    model->x_8ac8f967 = 8;
    x_d59386e0->x_4962fc73 = model;
}

void wad_resolve_k3(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = mem_alloc_debug(sizeof(Model), "wad.c", 977);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_eec8b086, x_d59386e0->context);
    model->x_8ac8f967 = 0x10;
    x_d59386e0->x_4962fc73 = model;
}

void wad_resolve_k4(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = mem_alloc_debug(sizeof(Model), "wad.c", 991);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_bb5426b0, x_d59386e0->context);
    model->x_8ac8f967 = 2;
    x_d59386e0->x_4962fc73 = model;
}

void wad_resolve_k5(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = mem_alloc_debug(sizeof(Model), "wad.c", 1005);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 1;
    model_bone_setup(model);
    x_d59386e0->x_4962fc73 = model;
}

void wad_resolve_gmd(x_80d298c9 *x_d59386e0) {
    x_82e80914 *s0;
    x_13162abc *x_3bfb7219;

    s0 = mem_alloc_debug(sizeof(x_82e80914), "wad.c", 1019);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_scaffold_register(s0, x_3bfb7219, x_d59386e0->name, 1, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = s0;
}

void wad_load_ctl(x_80d298c9 *x_d59386e0) {
    wad_entry_load_data(x_d59386e0);
    if (x_d59386e0->data != NULL) {
        x_f133710d = x_d59386e0->x_f33d7764;
        mem_copy_overlap(x_f90c9091, x_d59386e0->data, x_f133710d);
        wad_entry_free(x_d59386e0);
    }
}

void wad_resolve_tbl(x_80d298c9 *x_d59386e0) {
    if (x_d59386e0->data != 0) {
        alBnkfNew(x_f90c9091, x_d59386e0->data);
    }
}

void wad_resolve_seq(x_80d298c9 *x_d59386e0) {
    if (x_d59386e0->data != NULL) {
        x_032a146b = x_d59386e0->x_f33d7764;
        x_adb8fe7f = x_d59386e0->data;
        alSeqNew(x_d896e1bb, x_adb8fe7f, x_032a146b);
        alSeqNewMarker(x_d896e1bb, &x_9ae0d7c5, 0);
        alSeqNewMarker(x_d896e1bb, &x_d452fc32, 0xFFFFFFFF);
        alSeqpLoop(x_85a4d96f, &x_9ae0d7c5, &x_d452fc32, -1);

        alSeqpSetBank(x_85a4d96f, x_f90c9091->bankArray[0]);
        alSeqpSetSeq(x_85a4d96f, x_d896e1bb);
        alSeqpSetVol(x_85a4d96f, x_66ddef46);
        x_24b82fef = TRUE;
        x_b5cc849a = x_66ddef46;
    }
}

void wad_load_vox(x_80d298c9 *x_d59386e0) {
    wad_entry_load_data(x_d59386e0);
    if (x_d59386e0->data != NULL) {
        mem_copy_overlap(gSfxBanks[2], x_d59386e0->data, x_d59386e0->x_f33d7764);
        x_df816944[2] = 1;
        wad_entry_free(x_d59386e0);
        wad_setup_sfx_bank(gSfxBanks[2], D_7DE880, 2);
    }
}

void wad_load_sfb(x_80d298c9 *x_d59386e0) {
    s32 x_3a540ba4;

    x_3a540ba4 = x_d59386e0->context;
    if (x_3a540ba4 >= 2U) {
        x_3a540ba4 = 2;
    }

    wad_entry_load_data(x_d59386e0);
    if (x_d59386e0->data != NULL) {
        mem_copy_overlap(gSfxBanks[x_3a540ba4], x_d59386e0->data, x_d59386e0->x_f33d7764);
        x_df816944[x_3a540ba4] = TRUE;
        wad_entry_free(x_d59386e0);
    }
}

void wad_resolve_sfx(x_80d298c9 *x_d59386e0) {
    s32 x_3a540ba4;

    x_3a540ba4 = x_d59386e0->context;

    if (x_d59386e0->data != NULL) {
        if (x_3a540ba4 >= 2U) {
            x_3a540ba4 = 2;
        }
        wad_setup_sfx_bank(gSfxBanks[x_3a540ba4], x_d59386e0->data, x_3a540ba4);
    }
}

void func_80027C54(x_320b5d80 *x_cc1d0de5, Gfx **x_84ff873b) {
    Gfx *gfx;
    if (x_84ff873b == NULL) {
        gtStateSetOthermode(&x_cc1d0de5->info->header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    } else {
        gfx = *x_84ff873b;
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        *x_84ff873b = gfx;
    }
}

void wad_load_sp3(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;
    char *name;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    model = mem_alloc_debug(sizeof(Model), "wad.c", 1226);
    x_3bfb7219->x_14bc93c1 = 1;
    name = x_d59386e0->name;
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    x_3bfb7219->x_14bc93c1 = 0;
    x_d59386e0->x_4962fc73 = model;
    strlen(name);
}

void wad_load_oc(x_80d298c9 *x_d59386e0) {
    wad_entry_load_data(x_d59386e0);
}

void wad_resolve_sp3(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = mem_alloc_debug(sizeof(Model), "wad.c", 1257);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = model;
}

void wad_load_k2(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    wad_entry_load_data(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    wad_entry_alloc_dma(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    anim_buffer_resolve(x_3bfb7219, x_1e61bca4);

    model = mem_alloc_debug(sizeof(Model), "wad.c", 1297);
    x_3bfb7219->x_14bc93c1 = 1;
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 4;
    model_bone_setup(model);
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void wad_resolve_k2(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = mem_alloc_debug(sizeof(Model), "wad.c", 1314);
    x_3bfb7219 = x_d59386e0->data;

    anim_buffer_relocate(x_3bfb7219);
    model_create_from_kmd(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 4;
    model_bone_setup(model);
    x_d59386e0->x_4962fc73 = model;
}

void wad_load_mov(x_80d298c9 *x_d59386e0) {
    if (sWadMovCallback != NULL) {
        sWadMovCallback(x_d59386e0);
    } else {
        wad_entry_load_data(x_d59386e0);
    }
}

void wad_load_sym(x_80d298c9 *x_d59386e0) {
    if (gWadCondLoad[x_d59386e0->context].x_6128220f) {
        wad_entry_load_data(x_d59386e0);
    }
}
