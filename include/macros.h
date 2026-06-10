#ifndef __MACROS_H__
#define __MACROS_H__

#define ARRAY_COUNT(x_2e6839f2) (s32)(sizeof(x_2e6839f2) / sizeof(x_2e6839f2[0]))

#define x_a4e17949(addr) (void *) ((u32) (addr) + 0x80000000)
#define x_c485761a(addr) (u32)((u8 *) (addr) - 0x80000000)

#define x_56e08f29 320
#define x_84e8ddf2 240

#define ROUND(x) (s32)((x) >= 0.0 ? (x) + 0.5 : (x) - 0.5)

#define x_6d619dce(array)             \
    array.elements[array.x_b8173ab8--]; \
    array.count--

#define x_48825d30(array, x_4a33eacd)                 \
    array.elements[++array.x_b8173ab8] = (u8 *) x_4a33eacd; \
    array.count++;

#define x_50746900(pkt, a, b, c, d) \
    pkt->context = (a);              \
    pkt->info = (b);                 \
    pkt->vertices = (c);             \
    pkt->triangles = (d);            \
    pkt++;

#define ABS(x) ((x) > 0 ? (x) : -(x))
// #define MIN(x, y) ((x) < (y) ? (x) : (y))

#define x_4a9e7834(x_720f6ac9, x_aa1be933) ((x_720f6ac9) + (x_aa1be933) - (MIN(x_720f6ac9, x_aa1be933) >> 1))
#define x_84ce1cfb(x) ((x) * (x))

#endif
