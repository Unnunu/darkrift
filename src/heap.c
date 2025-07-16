#include "common.h"
#include "string.h"

#define MEM_GUARD_MAGIC 0xABCD6789
#define HEAP_SIZE 0x23E806

void heap_link(ChunkHeader *arg0, ChunkHeader **arg1);

extern OSMesgQueue gSchedDMAQueue;

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

void init_heap(void) {
    sFreeChunksList = (ChunkHeader *) gHeapBase;

    sFreeChunksList->end = ((u32) (gHeapBase) + HEAP_SIZE) & ~7;
    sFreeChunksList->flags = 1;
    sFreeChunksList->next = NULL;
    sFreeChunksList->previous = NULL;
    sAllocatedSize = 0;
    sFreeChunksList->guard = MEM_GUARD_MAGIC;

    sFreeSize = get_free_mem(sFreeChunksList);
}

#pragma GLOBAL_ASM("asm/nonmatchings/heap/func_800007C8.s")
#if 0
void func_800007C8(void) {
    s32 s1;
    s32 s2;
    void* a2;
    s32 v0;
    s32 i;
    ChunkHeader* s0;

    sAllocatedSize = 0;
    sFreeChunksList = gHeapBase;
    sFreeChunksList->unk_00 = 1;
    sFreeChunksList->unk_0C = 0;
    sFreeChunksList->unk_08 = 0;
    sAllocatedChunksList = 0;
    sFreeChunksList->guard = MEM_GUARD_MAGIC;

    s1 = ((u32)(gHeapBase) + HEAP_SIZE) & ~7;

    while (TRUE) {
        s2 = -1;
        a2 = NULL;

        for (i = 0; i < 0x100; i++) {
            if (!(D_8005AEB8[i].unk_00 & 1) && (u32)D_8005AEB8[i].unk_04 < s1 && D_8005AEB8[i].unk_04 > a2) {
                a2 = D_8005AEB8[i].unk_04;
                s2 = i;
            }
        }

        if (s2 >= 0) {
            s0 = (u32)(D_8005AEB8[s2].unk_04) - sizeof(ChunkHeader);
        }

        if (s2 < 0) {
            break;
        }
    }
}
#endif

void reset_heap(ChunkHeader *arg0, s32 end) {
    arg0->end = end;
    arg0->flags = 1;
    arg0->next = NULL;
    arg0->previous = NULL;
    arg0->guard = MEM_GUARD_MAGIC;
    heap_link(arg0, &sFreeChunksList);
}

s32 func_80000A1C(void) {
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

s32 get_free_mem(ChunkHeader *chunk) {
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

    sFreeSize = get_free_mem(sFreeChunksList);
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
    s32 curSize;
    u32 bestSize;
    ChunkHeader *bestChunk;
    ChunkHeader *s1;

    while (TRUE) {
        sAllocatedSize += size;
        sFreeSize = get_free_mem(sFreeChunksList);

        if (size == 0) {
            return NULL;
        }

        size = (size + 0xF) & ~0xF;

        bestChunk = NULL;
        bestSize = 0x7FFFFFFF;
        current = sFreeChunksList;
        while (current != NULL) {
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

            current = current->next;
        }

        if (bestChunk != NULL) {
            s1 = bestChunk;
            if (size < bestSize) {
                u32 end = (s64) bestChunk->end;
                s1 = bestChunk->end - size - sizeof(ChunkHeader);
                bestChunk->end = s1;
                s1->flags = 0;
                s1->guard = MEM_GUARD_MAGIC;
                s1->end = end;
            } else {
                bestChunk->flags &= ~1;
                bestChunk->guard = MEM_GUARD_MAGIC;
                heap_unlink(bestChunk);
            }
            break;
        }

        if (sFreeChunksList == NULL || !D_80049288) {
            return NULL;
        }

        heap_merge_chunks();
        sAllocatedSize -= size;
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

void func_80000E0C(u8 *arg0, u8 arg1, u32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        arg0[i] = arg1;
    }
}

void func_80000E40(u32 *dest, u32 *src, u32 size) {
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

s32 func_80000EA8(s32 size) {
    s32 i;

    if (D_8005BEB8 < 0x100) {
        D_8005AEB8[D_8005BEB8].unk_04 = do_mem_alloc(size);
        D_8005AEB8[D_8005BEB8].unk_00 = 0;
        D_8005AEB8[D_8005BEB8].unk_0C = 0;
        return D_8005BEB8++;
    }

    for (i = 0; i < 0x100; i++) {
        if (D_8005AEB8[i].unk_00 & 1) {
            D_8005AEB8[i].unk_04 = do_mem_alloc(size);
            D_8005AEB8[i].unk_00 = 0;
            D_8005AEB8[i].unk_0C = 0;
            return i;
        }
    }

    return -1;
}

void func_80000F70(s32 arg0) {
    mem_free(D_8005AEB8[arg0].unk_04);
    D_8005AEB8[arg0].unk_00 = 1;
    D_8005AEB8[arg0].unk_0C = 0;
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

void func_800010D4(s32 arg0, s32 arg1, s32 arg2) {
    D_8005AEB8[arg0].unk_0C = arg1;
    D_8005AEB8[arg0].unk_08 = arg2;
}

void *mem_alloc(s32 size, const char *file, s32 line) {
    return do_mem_alloc(size);
}
