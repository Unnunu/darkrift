#include "common.h"

#define THREAD_STACK_SIZE 0x400
extern u8 D_800572E0_stack[THREAD_STACK_SIZE];
extern OSThread D_800572E0;

void func_800004AC(void*);

void func_80000450(void) {
    osInitialize();
    osCreateThread(&D_800572E0, 1, &func_800004AC, NULL, D_800572E0_stack + THREAD_STACK_SIZE, 10);
    osStartThread(&D_800572E0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/1050/func_800004AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1050/func_80000600.s")
