#include "common.h"
#include "string.h"

/**
 * @file heap.c
 * @brief Heap memory manager
 *
 * Implements a simple heap allocator with a free list and an allocated list.
 * Supports slot-based tracked allocations with move callbacks for
 * compaction, DMA read helpers, and memory block operations.
 *
 * Heap layout:
 *   [ChunkHeader | user data | ChunkHeader | user data | ...]
 *   Free chunks are linked via gFreeChunksList.
 *   Allocated chunks via sAllocatedChunksList.
 *
 * The slot system (gMemSlots) tracks up to NUM_SLOTS allocations with
 * optional move callbacks called during heap compaction.
 */

#define MEM_GUARD_MAGIC 0xABCD6789
#define HEAP_SIZE 0x23E806
#define NUM_SLOTS 256

void heap_link(ChunkHeader *arg0, ChunkHeader **arg1);
void mem_move(u32 *dest, u32 *src, u32 size);

ChunkHeader *gFreeChunksList = NULL;
ChunkHeader *sAllocatedChunksList = NULL;
u8 sHeapDirty = FALSE; // set by mem_free, reset by heap_merge_chunks

OSIoMesg sDmaIoMesg;
char heapPadding[0x8]; // unused
s32 sAllocatedSize;
s32 sFreeSize;
MemSlot gMemSlots[NUM_SLOTS];
s32 sNextSlotIndex;
char heapPadding2[0x4]; // unused
void *gHeapBase;

/**
 * @brief Unused stub function. The loop body has been stripped,
 *        making the original purpose unknowable.
 */
void func_80000710(s32 arg0, s32 arg1) {
    s32 i, j;

    for (i = 0; i != arg1; i++) {
        for (j = 2; j < 10; j += 4) {
            // do nothing
        }
    }
}

/**
 * @brief Initializes the heap from gHeapBase.
 *        Sets up a single free chunk covering the entire heap area.
 */
void initialize_memory_heap(void) {
    gFreeChunksList = (ChunkHeader *) gHeapBase;

    gFreeChunksList->end = ((u32) (gHeapBase) + HEAP_SIZE) & ~7;
    gFreeChunksList->flags = 1;
    gFreeChunksList->next = NULL;
    gFreeChunksList->previous = NULL;
    sAllocatedSize = 0;
    gFreeChunksList->guard = MEM_GUARD_MAGIC;

    sFreeSize = heap_get_free_mem(gFreeChunksList);
}

/**
 * @brief Compact heap by moving allocated slots towards the top, defragmenting
 *        free space.
 *
 * Finds the highest-addressed allocated slot, moves it to the current end
 * boundary, then repeats. This compacts all live allocations into the upper
 * portion of the heap, leaving a single contiguous free block at the bottom.
 */
void reset_and_compact_heap(void) {
    s32 end;
    s32 last_slot_index;
    void *last_slot_data;
    s32 i;
    ChunkHeader *slotHeader;
    s32 slot_data_size;
    void *new_data;
    ChunkHeader *newvar;

    sAllocatedSize = 0;

    gFreeChunksList = gHeapBase;
    gFreeChunksList->flags = 1;
    gFreeChunksList->previous = NULL;
    gFreeChunksList->next = NULL;

    sAllocatedChunksList = NULL;
    gFreeChunksList->guard = MEM_GUARD_MAGIC;

    end = ((u32) (gHeapBase) + HEAP_SIZE) & ~7;

    do {
        last_slot_index = -1;
        last_slot_data = NULL;

        // find the highest-addressed live slot whose data lies below end
        for (i = 0; i < ARRAY_COUNT(gMemSlots); i++) {
            MemSlot *slot = gMemSlots + i;
            if (!(slot->flags & 1) && (u32) slot->data < end) {
                void *slot_data = slot->data;
                if (slot_data > last_slot_data) {
                    last_slot_data = slot_data;
                    last_slot_index = i;
                }
                if (!gFreeChunksList) {} // required for matching
            }
        }

        if (last_slot_index >= 0) {
            // move the slot's data to just below the end boundary
            s32 newvar2 = (u32) gMemSlots[last_slot_index].data - sizeof(ChunkHeader);
            slotHeader = (ChunkHeader *) newvar2;
            slot_data_size = slotHeader->end - (u32) slotHeader - sizeof(ChunkHeader);
            new_data = end - slot_data_size;
            if (new_data != gMemSlots[last_slot_index].data) {
                slotHeader = end - slotHeader->end + (s32) slotHeader;
                mem_move(new_data, gMemSlots[last_slot_index].data, slot_data_size);
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
            if (gMemSlots[last_slot_index].move_cb != NULL) {
                gMemSlots[last_slot_index].move_cb(new_data, gMemSlots[last_slot_index].data,
                                                   gMemSlots[last_slot_index].priv);
            }
            gMemSlots[last_slot_index].data = new_data;
        }
    } while (last_slot_index >= 0);

    gFreeChunksList->end = end;
    sFreeSize = heap_get_free_mem(gFreeChunksList);
}

/**
 * @brief Initialise a new chunk header and link it into the free list.
 *        Unused — the function body exists but is never called.
 */
void heap_add_free_chunk(ChunkHeader *list, s32 end) {
    list->end = end;
    list->flags = 1;
    list->next = NULL;
    list->previous = NULL;
    list->guard = MEM_GUARD_MAGIC;
    heap_link(list, &gFreeChunksList);
}

/**
 * @brief Validate all allocated chunks by checking for corrupted guards.
 *        Returns TRUE if all guards are valid.
 */
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

/**
 * @brief Traverse a chunk list and compute total free/available size.
 */
s32 heap_get_free_mem(ChunkHeader *chunk) {
    s32 totalSize = 0;

    while (chunk != NULL) {
        totalSize += chunk->end - (u32) chunk;
        chunk = chunk->next;
        totalSize -= sizeof(ChunkHeader);
    }

    return totalSize;
}

/**
 * @brief Insert a chunk at the head of a linked list.
 */
void heap_link(ChunkHeader *chunk, ChunkHeader **listHead) {
    chunk->next = *listHead;
    if (chunk->next != NULL) {
        chunk->next->previous = chunk;
    }
    *listHead = chunk;
    chunk->previous = NULL;
}

/**
 * @brief Remove a chunk from its linked list.
 */
void heap_unlink(ChunkHeader *chunk) {
    if (chunk == gFreeChunksList) {
        gFreeChunksList = chunk->next;
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

/**
 * @brief Merge adjacent free chunks into larger blocks.
 *        Iterates the free list looking for chunks that are immediately
 *        followed by another free chunk (current == ptr->end).
 */
void heap_merge_chunks(void) {
    ChunkHeader *current;
    ChunkHeader *ptr;

    sFreeSize = heap_get_free_mem(gFreeChunksList);
    sHeapDirty = FALSE;

    current = gFreeChunksList;
    while (current != NULL) {
        ptr = gFreeChunksList;
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
            current = gFreeChunksList;
        }
    }
}

#ifdef NON_MATCHING
/**
 * @brief Core memory allocator. Best-fit strategy.
 *        If allocation fails and the heap is dirty (has been freed since
 *        last merge), merges free chunks and retries once.
 */
void *do_mem_alloc(u32 size) {
    ChunkHeader *current;
    u32 curSize;
    u32 bestSize;
    ChunkHeader *bestChunk;
    ChunkHeader *s1;

restart:
    sAllocatedSize += size;
    sFreeSize = heap_get_free_mem(gFreeChunksList);

    if (size == 0) {
        return NULL;
    }

    size = (size + 0xF) & ~0xF;

    bestChunk = NULL;
    bestSize = 0x7FFFFFFF;

    // best-fit: find the smallest chunk that can hold the request
    for (current = gFreeChunksList; current != NULL; current = current->next) {
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
            // split the chunk: allocate from the end, keep remainder free
            u32 end = bestChunk->end;
            bestChunk->end = bestChunk->end - size - sizeof(ChunkHeader);
            s1 = bestChunk->end;
            s1->flags = 0;
            s1->guard = MEM_GUARD_MAGIC;
            s1->end = end;
        } else {
            // exact fit: take the whole chunk
            bestChunk->flags &= ~1;
            bestChunk->guard = MEM_GUARD_MAGIC;
            heap_unlink(bestChunk);
        }
    } else {
        if (gFreeChunksList == NULL || !sHeapDirty) {
            return NULL;
        }

        // allocation failed but heap is dirty — merge and retry once
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

/**
 * @brief Free an allocated block. The block is linked back into the free
 *        list and the dirty flag is set so the next alloc can attempt merge.
 */
void mem_free(void *ptr) {
    ChunkHeader *chunk;

    chunk = (ChunkHeader *) ((u32) ptr - sizeof(ChunkHeader));
    sAllocatedSize = sAllocatedSize - chunk->end + (u32) chunk + sizeof(ChunkHeader);
    if (chunk->guard == MEM_GUARD_MAGIC) {
        chunk->guard = 0;
    }

    heap_unlink(chunk);
    chunk->flags |= 1;
    heap_link(chunk, &gFreeChunksList);
    sHeapDirty = TRUE;
}

/**
 * @brief Fill a buffer with a single byte value.
 */
void mem_fill(u8 *arg0, u8 arg1, u32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        arg0[i] = arg1;
    }
}

/**
 * @brief Copy memory, safe for overlapping regions.
 *        Uses memcpy (forward) when dest < src, otherwise copies backwards.
 */
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

/**
 * @brief Allocate from the slot system. Returns a slot index, or -1 if full.
 *        Tries the linear next-slot first, then searches for a free slot.
 */
s32 mem_alloc_slot(s32 size) {
    s32 i;

    if (sNextSlotIndex < NUM_SLOTS) {
        gMemSlots[sNextSlotIndex].data = do_mem_alloc(size);
        gMemSlots[sNextSlotIndex].flags = 0;
        gMemSlots[sNextSlotIndex].move_cb = 0;
        return sNextSlotIndex++;
    }

    for (i = 0; i < NUM_SLOTS; i++) {
        if (gMemSlots[i].flags & 1) {
            gMemSlots[i].data = do_mem_alloc(size);
            gMemSlots[i].flags = 0;
            gMemSlots[i].move_cb = 0;
            return i;
        }
    }

    return -1;
}

/**
 * @brief Free a slot by index. Marks it as free (bit 0) and clears move_cb.
 */
void mem_free_slot(s32 slotIndex) {
    mem_free(gMemSlots[slotIndex].data);
    gMemSlots[slotIndex].flags = 1;
    gMemSlots[slotIndex].move_cb = NULL;
}

/**
 * @brief Blocking DMA read from ROM to RAM.
 *        Drains any pending DMA completions first, then waits for transfer.
 *        Invalidates entire data cache after the read (4MB range).
 */
void dma_read(s32 romAddr, void *vramAddr, s32 size) {
    osWritebackDCacheAll();
    // drain any pending DMA completions
    while (osRecvMesg(&gSchedDMAQueue, NULL, OS_MESG_NOBLOCK) != -1) {}
    osPiStartDma(&sDmaIoMesg, 0, OS_READ, romAddr, vramAddr, size, &gSchedDMAQueue);
    osRecvMesg(&gSchedDMAQueue, NULL, OS_MESG_BLOCK);
    osInvalDCache(0, 0x3FFFFF);
}

/**
 * @brief Non-blocking DMA read. Fires and returns without waiting.
 *
 * NOTE: osInvalDCache is called immediately after starting the DMA, before
 * the transfer completes. This means the cache invalidation covers stale data
 * rather than the freshly-DMA'd data. The caller must ensure coherency,
 * typically by calling osInvalDCache again once the DMA is known to be done.
 */
void dma_read_noblock(s32 romAddr, void *vramAddr, s32 size) {
    osWritebackDCacheAll();
    osPiStartDma(&sDmaIoMesg, 0, OS_READ, romAddr, vramAddr, size, &gSchedDMAQueue);
    osInvalDCache(0, 0x3FFFFF);
}

/**
 * @brief Set the move callback and private data for a slot.
 *        Called during heap compaction to relocate external pointers.
 */
void heap_set_move_callback(s32 slotIndex, void (*move_cb)(void *arg0, s32 arg1, s32 arg2), s32 priv) {
    gMemSlots[slotIndex].move_cb = move_cb;
    gMemSlots[slotIndex].priv = priv;
}

/**
 * @brief Allocate memory. The file/line params are unused but kept for
 *        debugging compatibility with the SDK-style allocator interface.
 */
void *mem_alloc(s32 size, const char *file, s32 line) {
    return do_mem_alloc(size);
}
