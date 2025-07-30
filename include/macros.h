#ifndef __MACROS_H__
#define __MACROS_H__

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#define PHYSICAL_TO_VIRTUAL(addr) (void *) ((u32) (addr) + 0x80000000)
#define VIRTUAL_TO_PHYSICAL(addr) (u32)((u8 *) (addr) - 0x80000000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ROUND(x) (s32)((x) >= 0.0 ? (x) + 0.5 : (x) - 0.5)

#define GET_ITEM(array)             \
    array.elements[array.unk_0C--]; \
    array.count--;

#define RELEASE_ITEM(array, item)          \
    array.elements[++array.unk_0C] = item; \
    array.count++;

#endif
