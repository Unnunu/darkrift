#include "common.h"
#include "string.h"

#define MEM_MAGIC 0xABCD6789
#define MEM_HEAP_SIZE 0x23E806
#define DMA_SLOT_MAX 256

void mem_list_prepend(x_704d55d4 *x_cc1d0de5, x_704d55d4 **x_84ff873b);
void mem_copy_overlap(u32 *dest, u32 *src, u32 size);

x_704d55d4 *sMemFreeList = NULL;
x_704d55d4 *sMemUsedList = NULL;
u8 sDefragNeeded = FALSE;

OSIoMesg sDmaMesg;
char sMemPad1[0x8];
s32 sMemAllocated;
s32 sMemFreeBytes;
x_37652cbd sDmaSlots[DMA_SLOT_MAX];
s32 sDmaSlotCount;
char sMemPad2[0x4];
void *sHeapBase;

void mem_delay(s32 x_cc1d0de5, s32 x_84ff873b) {
    s32 i, j;

    for (i = 0; i != x_84ff873b; i++) {
        for (j = 2; j < 10; j += 4) {
            // do nothing
        }
    }
}

void mem_pool_init(void) {
    sMemFreeList = (x_704d55d4 *) sHeapBase;

    sMemFreeList->end = ((u32) (sHeapBase) + MEM_HEAP_SIZE) & ~7;
    sMemFreeList->flags = 1;
    sMemFreeList->next = NULL;
    sMemFreeList->previous = NULL;
    sMemAllocated = 0;
    sMemFreeList->x_a9d4034d = MEM_MAGIC;

    sMemFreeBytes = mem_free_space(sMemFreeList);
}

void mem_defrag(void) {
    s32 end;
    s32 x_d70d9bc9;
    void *x_968605c7;
    s32 v0;
    s32 i;
    x_704d55d4 *x_5d7a764d;
    s32 x_4cf275a8;
    void *x_50f1dbff;
    x_704d55d4 *x_24aca5c4;

    sMemAllocated = 0;

    sMemFreeList = sHeapBase;
    sMemFreeList->flags = 1;
    sMemFreeList->previous = NULL;
    sMemFreeList->next = NULL;

    sMemUsedList = NULL;
    sMemFreeList->x_a9d4034d = MEM_MAGIC;

    end = ((u32) (sHeapBase) + MEM_HEAP_SIZE) & ~7;

    do {
        x_d70d9bc9 = -1;
        x_968605c7 = NULL;

        for (i = 0; i < ARRAY_COUNT(sDmaSlots); i++) {
            x_37652cbd *slot = sDmaSlots + i;
            if (!(slot->x_af0aa1f8 & 1) && (u32) slot->data < end) {
                void *x_d1231a38 = slot->data;
                if (x_d1231a38 > x_968605c7) {
                    x_968605c7 = x_d1231a38;
                    x_d70d9bc9 = i;
                }
                if (!sMemFreeList) {} // required for matching
            }
        }

        if (x_d70d9bc9 >= 0) {
            s32 x_c028c62d = (u32) sDmaSlots[x_d70d9bc9].data - sizeof(x_704d55d4);
            x_5d7a764d = (x_704d55d4 *) x_c028c62d;
            x_4cf275a8 = x_5d7a764d->end - (u32) x_5d7a764d - sizeof(x_704d55d4);
            x_50f1dbff = end - x_4cf275a8;
            if (x_50f1dbff != sDmaSlots[x_d70d9bc9].data) {
                x_5d7a764d = end - x_5d7a764d->end + (s32) x_5d7a764d;
                mem_copy_overlap(x_50f1dbff, sDmaSlots[x_d70d9bc9].data, x_4cf275a8);
                x_5d7a764d->end = end;
                x_5d7a764d->flags = 0;
                x_5d7a764d->next = x_5d7a764d->previous = NULL;
                x_5d7a764d->x_a9d4034d = MEM_MAGIC;
            } else {
                x_5d7a764d->next = x_5d7a764d->previous = NULL;
            }

            end = x_5d7a764d;
            sMemAllocated = sMemAllocated + x_5d7a764d->end - (u32) (x_24aca5c4 = x_5d7a764d) - sizeof(x_704d55d4);
            mem_list_prepend(x_5d7a764d, &sMemUsedList);
            if (sDmaSlots[x_d70d9bc9].x_3c30b5f3 != NULL) {
                sDmaSlots[x_d70d9bc9].x_3c30b5f3(x_50f1dbff, sDmaSlots[x_d70d9bc9].data,
                                                 sDmaSlots[x_d70d9bc9].x_3b9aa142);
            }
            sDmaSlots[x_d70d9bc9].data = x_50f1dbff;
        }
    } while (x_d70d9bc9 >= 0);

    sMemFreeList->end = end;
    sMemFreeBytes = mem_free_space(sMemFreeList);
}

void mem_free_add(x_704d55d4 *list, s32 end) {
    list->end = end;
    list->flags = 1;
    list->next = NULL;
    list->previous = NULL;
    list->x_a9d4034d = MEM_MAGIC;
    mem_list_prepend(list, &sMemFreeList);
}

s32 mem_validate(void) {
    x_704d55d4 *ptr;
    s32 ret = TRUE;

    ptr = sMemUsedList;
    while (ptr != NULL) {
        if (ptr->x_a9d4034d == MEM_MAGIC) {
            ptr = ptr->next;
        } else {
            ret = FALSE;
            break;
        }
    }

    return ret;
}

s32 mem_free_space(x_704d55d4 *x_6c87f683) {
    s32 x_cab1ae75 = 0;

    while (x_6c87f683 != NULL) {
        x_cab1ae75 += x_6c87f683->end - (u32) x_6c87f683;
        x_6c87f683 = x_6c87f683->next;
        x_cab1ae75 -= sizeof(x_704d55d4);
    }

    return x_cab1ae75;
}

void mem_list_prepend(x_704d55d4 *x_6c87f683, x_704d55d4 **x_bf0b39b3) {
    x_6c87f683->next = *x_bf0b39b3;
    if (x_6c87f683->next != NULL) {
        x_6c87f683->next->previous = x_6c87f683;
    }
    *x_bf0b39b3 = x_6c87f683;
    x_6c87f683->previous = NULL;
}

void mem_list_remove(x_704d55d4 *x_6c87f683) {
    if (x_6c87f683 == sMemFreeList) {
        sMemFreeList = x_6c87f683->next;
    }
    if (x_6c87f683 == sMemUsedList) {
        sMemUsedList = x_6c87f683->next;
    }

    if (x_6c87f683->next != NULL && x_6c87f683->previous != NULL) {
        x_6c87f683->previous->next = x_6c87f683->next;
        x_6c87f683->next->previous = x_6c87f683->previous;
    } else if (x_6c87f683->next != NULL) {
        x_6c87f683->next->previous = NULL;
    } else {
        x_6c87f683->previous->next = NULL;
    }

    x_6c87f683->next = NULL;
    x_6c87f683->previous = NULL;
}

void mem_merge_free(void) {
    x_704d55d4 *current;
    x_704d55d4 *ptr;

    sMemFreeBytes = mem_free_space(sMemFreeList);
    sDefragNeeded = FALSE;

    current = sMemFreeList;
    while (current != NULL) {
        ptr = sMemFreeList;
        while (ptr != NULL) {
            if (current == (struct x_704d55d4 *) ptr->end) {
                // merge two chunks
                ptr->end = current->end;
                mem_list_remove(current);
                current = NULL;
                break;
            }
            ptr = ptr->next;
        }

        if (current != NULL) {
            current = current->next;
        } else {
            current = sMemFreeList;
        }
    }
}

#ifdef NON_MATCHING
void *mem_alloc(u32 size) {
    x_704d55d4 *current;
    u32 x_bc354e67;
    u32 x_e26ee934;
    x_704d55d4 *x_b264b422;
    x_704d55d4 *s1;

retry_alloc:
    sMemAllocated += size;
    sMemFreeBytes = mem_free_space(sMemFreeList);

    if (size == 0) {
        return NULL;
    }

    size = (size + 0xF) & ~0xF;

    x_b264b422 = NULL;
    x_e26ee934 = 0x7FFFFFFF;

    for (current = sMemFreeList; current != NULL; current = current->next) {
        x_bc354e67 = current->end - ((u32) current) - sizeof(x_704d55d4);

        if (x_bc354e67 == size) {
            x_e26ee934 = x_bc354e67;
            x_b264b422 = current;
            break;
        }

        if (x_bc354e67 < x_e26ee934 && size + sizeof(x_704d55d4) < x_bc354e67) {
            x_e26ee934 = x_bc354e67;
            x_b264b422 = current;
        }
    }

    if (x_b264b422 != NULL) {
        s1 = x_b264b422;
        if (size < x_e26ee934) {
            u32 end = x_b264b422->end;
            x_b264b422->end = x_b264b422->end - size - sizeof(x_704d55d4);
            s1 = x_b264b422->end;
            s1->flags = 0;
            s1->x_a9d4034d = MEM_MAGIC;
            s1->end = end;
        } else {
            x_b264b422->flags &= ~1;
            x_b264b422->x_a9d4034d = MEM_MAGIC;
            mem_list_remove(x_b264b422);
        }
    } else {
        if (sMemFreeList == NULL || !sDefragNeeded) {
            return NULL;
        }

        mem_merge_free();
        sMemAllocated -= size;
        goto retry_alloc;
    }

    mem_list_prepend(s1, &sMemUsedList);
    return (u32) s1 + sizeof(x_704d55d4);
}
#else
void *mem_alloc(u32 x_cc1d0de5);
#pragma GLOBAL_ASM("asm/nonmatchings/memory/mem_alloc.s")
#endif

void mem_free(void *ptr) {
    x_704d55d4 *x_6c87f683;

    x_6c87f683 = (x_704d55d4 *) ((u32) ptr - sizeof(x_704d55d4));
    sMemAllocated = sMemAllocated - x_6c87f683->end + (u32) x_6c87f683 + sizeof(x_704d55d4);
    if (x_6c87f683->x_a9d4034d == MEM_MAGIC) {
        x_6c87f683->x_a9d4034d = 0;
    }

    mem_list_remove(x_6c87f683);
    x_6c87f683->flags |= 1;
    mem_list_prepend(x_6c87f683, &sMemFreeList);
    sDefragNeeded = TRUE;
}

void mem_set(u8 *x_cc1d0de5, u8 x_84ff873b, u32 x_2092f891) {
    s32 i;

    for (i = 0; i < x_2092f891; i++) {
        x_cc1d0de5[i] = x_84ff873b;
    }
}

void mem_copy_overlap(u32 *dest, u32 *src, u32 size) {
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

s32 mem_dma_alloc(s32 size) {
    s32 i;

    if (sDmaSlotCount < DMA_SLOT_MAX) {
        sDmaSlots[sDmaSlotCount].data = mem_alloc(size);
        sDmaSlots[sDmaSlotCount].x_af0aa1f8 = 0;
        sDmaSlots[sDmaSlotCount].x_3c30b5f3 = 0;
        return sDmaSlotCount++;
    }

    for (i = 0; i < DMA_SLOT_MAX; i++) {
        if (sDmaSlots[i].x_af0aa1f8 & 1) {
            sDmaSlots[i].data = mem_alloc(size);
            sDmaSlots[i].x_af0aa1f8 = 0;
            sDmaSlots[i].x_3c30b5f3 = 0;
            return i;
        }
    }

    return -1;
}

void mem_dma_free(s32 x_ef190cf1) {
    mem_free(sDmaSlots[x_ef190cf1].data);
    sDmaSlots[x_ef190cf1].x_af0aa1f8 = 1;
    sDmaSlots[x_ef190cf1].x_3c30b5f3 = NULL;
}

void dma_read_sync(s32 romAddr, void *x_dda6dc06, s32 size) {
    osWritebackDCacheAll();
    while (osRecvMesg(&gPiMessageQueue, NULL, OS_MESG_NOBLOCK) != -1) {}
    osPiStartDma(&sDmaMesg, 0, OS_READ, romAddr, x_dda6dc06, size, &gPiMessageQueue);
    osRecvMesg(&gPiMessageQueue, NULL, OS_MESG_BLOCK);
    osInvalDCache(0, 0x3FFFFF);
}

void dma_read_async(s32 romAddr, void *x_dda6dc06, s32 size) {
    osWritebackDCacheAll();
    osPiStartDma(&sDmaMesg, 0, OS_READ, romAddr, x_dda6dc06, size, &gPiMessageQueue);
    osInvalDCache(0, 0x3FFFFF);
}

void mem_dma_set_callback(s32 x_ef190cf1, void (*x_3c30b5f3)(void *x_cc1d0de5, s32 x_84ff873b, s32 x_2092f891),
                          s32 x_3b9aa142) {
    sDmaSlots[x_ef190cf1].x_3c30b5f3 = x_3c30b5f3;
    sDmaSlots[x_ef190cf1].x_3b9aa142 = x_3b9aa142;
}

void *mem_alloc_debug(s32 size, const char *file, s32 line) {
    return mem_alloc(size);
}
