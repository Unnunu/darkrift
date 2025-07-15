#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

void *mem_alloc(s32 size, const char *file, s32 line);
void mem_free(void *);
s32 cont_init(s32);
void func_800027A0(void);
s32 get_free_mem(ChunkHeader *arg0);
void dma_read_noblock(s32 romAddr, void *vramAddr, s32 size);
s32 func_80000EA8(s32 size);
void func_80000F70(s32 arg0);
void func_8002A8C0(UnkItemAlpha *arg0, u32 arg1, u32 arg2);
void func_80000E0C(u8 *arg0, u8 arg1, u32 arg2);

#endif
