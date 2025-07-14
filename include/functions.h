#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

s32 cont_init(s32);
void func_800027A0(void);
s32 get_free_mem(ChunkHeader *arg0);
void dma_read_noblock(s32 romAddr, void *vramAddr, s32 size);
s32 func_80000EA8(s32 size);
void func_80000F70(s32 arg0);

#endif
