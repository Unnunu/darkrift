#include "common.h"
#include "string.h"

#define MEM_GUARD_MAGIC 0xABCD6789
#define HEAP_SIZE 0x23E806

void heap_link(ChunkHeader *arg0, ChunkHeader **arg1);
void mem_move(u32 *dest, u32 *src, u32 size);

ChunkHeader *sFreeChunksList = NULL;
ChunkHeader *sAllocatedChunksList = NULL;
u8 D_80049288 = FALSE;

OSIoMesg D_8005AE90;
char heap_padding[0x8];
s32 sAllocatedSize;
s32 sFreeSize;
UnkGamma D_8005AEB8[256];
s32 D_8005BEB8;
char heap_padding2[0x4];
void *gHeapBase;

void func_80000710(s32 arg0, s32 arg1) {
    s32 i, j;

    for (i = 0; i != arg1; i++) {
        for (j = 2; j < 10; j += 4) {
            // do nothing
        }
    }
}

void heap_init(void) {
    sFreeChunksList = (ChunkHeader *) gHeapBase;

    sFreeChunksList->end = ((u32) (gHeapBase) + HEAP_SIZE) & ~7;
    sFreeChunksList->flags = 1;
    sFreeChunksList->next = NULL;
    sFreeChunksList->previous = NULL;
    sAllocatedSize = 0;
    sFreeChunksList->guard = MEM_GUARD_MAGIC;

    sFreeSize = heap_get_free_mem(sFreeChunksList);
}

void heap_reset(void) {
    s32 end;
    s32 last_slot_index;
    void *last_slot_data;
    s32 v0;
    s32 i;
    ChunkHeader *slotHeader;
    s32 slot_data_size;
    void *new_data;
    ChunkHeader *newvar;

    sAllocatedSize = 0;

    sFreeChunksList = gHeapBase;
    sFreeChunksList->flags = 1;
    sFreeChunksList->previous = NULL;
    sFreeChunksList->next = NULL;

    sAllocatedChunksList = NULL;
    sFreeChunksList->guard = MEM_GUARD_MAGIC;

    end = ((u32) (gHeapBase) + HEAP_SIZE) & ~7;

    do {
        last_slot_index = -1;
        last_slot_data = NULL;

        for (i = 0; i < ARRAY_COUNT(D_8005AEB8); i++) {
            UnkGamma *slot = D_8005AEB8 + i;
            if (!(slot->unk_00 & 1) && (u32) slot->data < end) {
                void *slot_data = slot->data;
                if (slot_data > last_slot_data) {
                    last_slot_data = slot_data;
                    last_slot_index = i;
                }
                if (!sFreeChunksList) {} // required for matching
            }
        }

        if (last_slot_index >= 0) {
            s32 newvar2 = (u32) D_8005AEB8[last_slot_index].data - sizeof(ChunkHeader);
            slotHeader = (ChunkHeader *) newvar2;
            slot_data_size = slotHeader->end - (u32) slotHeader - sizeof(ChunkHeader);
            new_data = end - slot_data_size;
            if (new_data != D_8005AEB8[last_slot_index].data) {
                slotHeader = end - slotHeader->end + (s32) slotHeader;
                mem_move(new_data, D_8005AEB8[last_slot_index].data, slot_data_size);
                slotHeader->end = end;
                slotHeader->flags = 0;
                slotHeader->next = slotHeader->previous = NULL;
                slotHeader->guard = MEM_GUARD_MAGIC;
            } else {
                slotHeader->next = slotHeader->previous = NULL;
            }

            end = slotHeader;
            sAllocatedSize = sAllocatedSize + slotHeader->end - (u32) (newvar = slotHeader) - sizeof(ChunkHeader);
            heap_link(slotHeader, &sAllocatedChunksList);
            if (D_8005AEB8[last_slot_index].move_cb != NULL) {
                D_8005AEB8[last_slot_index].move_cb(new_data, D_8005AEB8[last_slot_index].data,
                                                    D_8005AEB8[last_slot_index].priv);
            }
            D_8005AEB8[last_slot_index].data = new_data;
        }
    } while (last_slot_index >= 0);

    sFreeChunksList->end = end;
    sFreeSize = heap_get_free_mem(sFreeChunksList);
}

void heap_set(ChunkHeader *list, s32 end) {
    list->end = end;
    list->flags = 1;
    list->next = NULL;
    list->previous = NULL;
    list->guard = MEM_GUARD_MAGIC;
    heap_link(list, &sFreeChunksList);
}

s32 heap_check(void) {
    ChunkHeader *ptr;
    s32 ret = TRUE;

    ptr = sAllocatedChunksList;
    while (ptr != NULL) {
        if (ptr->guard == MEM_GUARD_MAGIC) {
            ptr = ptr->next;
        } else {
            ret = FALSE;
            break;
        }
    }

    return ret;
}

s32 heap_get_free_mem(ChunkHeader *chunk) {
    s32 totalSize = 0;

    while (chunk != NULL) {
        totalSize += chunk->end - (u32) chunk;
        chunk = chunk->next;
        totalSize -= sizeof(ChunkHeader);
    }

    return totalSize;
}

void heap_link(ChunkHeader *chunk, ChunkHeader **listHead) {
    chunk->next = *listHead;
    if (chunk->next != NULL) {
        chunk->next->previous = chunk;
    }
    *listHead = chunk;
    chunk->previous = NULL;
}

void heap_unlink(ChunkHeader *chunk) {
    if (chunk == sFreeChunksList) {
        sFreeChunksList = chunk->next;
    }
    if (chunk == sAllocatedChunksList) {
        sAllocatedChunksList = chunk->next;
    }

    if (chunk->next != NULL && chunk->previous != NULL) {
        chunk->previous->next = chunk->next;
        chunk->next->previous = chunk->previous;
    } else if (chunk->next != NULL) {
        chunk->next->previous = NULL;
    } else {
        chunk->previous->next = NULL;
    }

    chunk->next = NULL;
    chunk->previous = NULL;
}

void heap_merge_chunks(void) {
    ChunkHeader *current;
    ChunkHeader *ptr;

    sFreeSize = heap_get_free_mem(sFreeChunksList);
    D_80049288 = FALSE;

    current = sFreeChunksList;
    while (current != NULL) {
        ptr = sFreeChunksList;
        while (ptr != NULL) {
            if (current == (struct ChunkHeader *) ptr->end) {
                // merge two chunks
                ptr->end = current->end;
                heap_unlink(current);
                current = NULL;
                break;
            }
            ptr = ptr->next;
        }

        if (current != NULL) {
            current = current->next;
        } else {
            current = sFreeChunksList;
        }
    }
}

#ifdef NON_MATCHING
void *do_mem_alloc(u32 size) {
    ChunkHeader *current;
    u32 curSize;
    u32 bestSize;
    ChunkHeader *bestChunk;
    ChunkHeader *s1;

restart:
    sAllocatedSize += size;
    sFreeSize = heap_get_free_mem(sFreeChunksList);

    if (size == 0) {
        return NULL;
    }

    size = (size + 0xF) & ~0xF;

    bestChunk = NULL;
    bestSize = 0x7FFFFFFF;

    for (current = sFreeChunksList; current != NULL; current = current->next) {
        curSize = current->end - ((u32) current) - sizeof(ChunkHeader);

        if (curSize == size) {
            bestSize = curSize;
            bestChunk = current;
            break;
        }

        if (curSize < bestSize && size + sizeof(ChunkHeader) < curSize) {
            bestSize = curSize;
            bestChunk = current;
        }
    }

    if (bestChunk != NULL) {
        s1 = bestChunk;
        if (size < bestSize) {
            u32 end = bestChunk->end;
            bestChunk->end = bestChunk->end - size - sizeof(ChunkHeader);
            s1 = bestChunk->end;
            s1->flags = 0;
            s1->guard = MEM_GUARD_MAGIC;
            s1->end = end;
        } else {
            bestChunk->flags &= ~1;
            bestChunk->guard = MEM_GUARD_MAGIC;
            heap_unlink(bestChunk);
        }
    } else {
        if (sFreeChunksList == NULL || !D_80049288) {
            return NULL;
        }

        heap_merge_chunks();
        sAllocatedSize -= size;
        goto restart;
    }

    heap_link(s1, &sAllocatedChunksList);
    return (u32) s1 + sizeof(ChunkHeader);
}
#else
void *do_mem_alloc(u32 arg0);
#pragma GLOBAL_ASM("asm/nonmatchings/heap/do_mem_alloc.s")
#endif

void mem_free(void *ptr) {
    ChunkHeader *chunk;

    chunk = (ChunkHeader *) ((u32) ptr - sizeof(ChunkHeader));
    sAllocatedSize = sAllocatedSize - chunk->end + (u32) chunk + sizeof(ChunkHeader);
    if (chunk->guard == MEM_GUARD_MAGIC) {
        chunk->guard = 0;
    }

    heap_unlink(chunk);
    chunk->flags |= 1;
    heap_link(chunk, &sFreeChunksList);
    D_80049288 = TRUE;
}

void mem_fill(u8 *arg0, u8 arg1, u32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        arg0[i] = arg1;
    }
}

void mem_move(u32 *dest, u32 *src, u32 size) {
    s32 i;
    u32 *temp = src;

    if (dest < src) {
        memcpy(dest, src, size);
    } else {
        for (i = size / 4 - 1; i >= 0; i--) {
            dest[i] = temp[i];
        }
    }
}

s32 mem_alloc_slot(s32 size) {
    s32 i;

    if (D_8005BEB8 < 0x100) {
        D_8005AEB8[D_8005BEB8].data = do_mem_alloc(size);
        D_8005AEB8[D_8005BEB8].unk_00 = 0;
        D_8005AEB8[D_8005BEB8].move_cb = 0;
        return D_8005BEB8++;
    }

    for (i = 0; i < 0x100; i++) {
        if (D_8005AEB8[i].unk_00 & 1) {
            D_8005AEB8[i].data = do_mem_alloc(size);
            D_8005AEB8[i].unk_00 = 0;
            D_8005AEB8[i].move_cb = 0;
            return i;
        }
    }

    return -1;
}

void mem_free_slot(s32 slotIndex) {
    mem_free(D_8005AEB8[slotIndex].data);
    D_8005AEB8[slotIndex].unk_00 = 1;
    D_8005AEB8[slotIndex].move_cb = NULL;
}

void dma_read(s32 romAddr, void *vramAddr, s32 size) {
    osWritebackDCacheAll();
    while (osRecvMesg(&gSchedDMAQueue, 0, 0) != -1) {}
    osPiStartDma(&D_8005AE90, 0, OS_READ, romAddr, vramAddr, size, &gSchedDMAQueue);
    osRecvMesg(&gSchedDMAQueue, NULL, OS_MESG_BLOCK);
    osInvalDCache(0, 0x3FFFFF);
}

void dma_read_noblock(s32 romAddr, void *vramAddr, s32 size) {
    osWritebackDCacheAll();
    osPiStartDma(&D_8005AE90, 0, OS_READ, romAddr, vramAddr, size, &gSchedDMAQueue);
    osInvalDCache(0, 0x3FFFFF);
}

void heap_set_move_callback(s32 slotIndex, void (*move_cb)(void *arg0, s32 arg1, s32 arg2), s32 priv) {
    D_8005AEB8[slotIndex].move_cb = move_cb;
    D_8005AEB8[slotIndex].priv = priv;
}

void *mem_alloc(s32 size, const char *file, s32 line) {
    return do_mem_alloc(size);
}
