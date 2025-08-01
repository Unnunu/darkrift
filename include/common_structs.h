#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

typedef struct Vec3f {
    f32 x, y, z;
} Vec3f;

typedef struct Vec3i {
    s32 x, y, z;
} Vec3i;

typedef struct Vec4i {
    s32 x, y, z, w;
} Vec4i;

typedef struct Vec3s {
    s16 x, y, z;
} Vec3s;

typedef struct Vec4f {
    f32 x, y, z, w;
} Vec4f;

typedef struct Matrix4f {
    Vec4f x, y, z, w;
} Matrix4f;

typedef struct ColorRGBA {
    u8 r, g, b, a;
} ColorRGBA;

typedef struct Quad {
    Vtx v[4];
} Quad;

typedef struct UnkDispStructPart1 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[0xE];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char unk_18[0x64 - 0x18];
} UnkDispStructPart1; // size = 0x64

typedef struct UnkDispStructPart2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ Gfx *unk_0C;
    /* 0x10 */ char unk_10[8];
} UnkDispStructPart2; // size = 0x18

typedef struct UnkDispStruct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ UnkDispStructPart2 *unk_04;
    /* 0x08 */ Vtx *unk_08;
    /* 0x0C */ u16 *unk_0C;
} UnkDispStruct; // size = 0x10

typedef struct DisplayData {
    /* 0x0000 */ Mtx mtxViewProj;
    /* 0x0040 */ char unk_40[0x40];
    /* 0x0080 */ Gfx unk_80[0x800];
    /* 0x4080 */ Gfx unk_4080[0x400];
    /* 0x6080 */ Gfx unk_6080[0x400];
    /* 0x8080 */ UnkDispStruct unk_8080[0x800];
    /* 0x10080 */ UnkDispStruct unk_10080[0x200];
    /* 0x12080 */ u16 perspNorm;
    /* 0x12082 */ char unk_12082[6];
} DisplayData; // size = 0x12088

typedef struct UnkKappa {
    /* 0x00 */ char unk_00[16];
} UnkKappa; // size = 0x10

typedef struct UnkDelta {
    /* 0x00 */ void (*fn_run)(void);
    /* 0x04 */ s32 unk_04;
    /* 0x04 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ UnkKappa *unk_18;
    /* 0x1C */ u8 unk_1C;
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ u8 unk_1F;
} UnkDelta; // size = 0x20

typedef struct UnkAlpha {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ char unk_0A;
    /* 0x0B */ u8 enabled;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
} UnkAlpha;

typedef struct UnkGamma {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkGamma; // size = 0x10

typedef struct ChunkHeader {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 end;
    /* 0x08 */ struct ChunkHeader *next;
    /* 0x0C */ struct ChunkHeader *previous;
    /* 0x10 */ s32 guard;
    /* 0x14 */ char padding[0x4];
} ChunkHeader; // size = 0x18

typedef struct TextureAsset {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 data[1];
} TextureAsset;

typedef struct Asset {
    /* 0x00 */ void *data;
    /* 0x04 */ void *aux_data;
    /* 0x08 */ s32 memory_slot;
    /* 0x0C */ s32 aux_memory_slot;
    /* 0x10 */ char name[20];
    /* 0x24 */ s32 size;
    /* 0x28 */ u32 unpacked_size;
    /* 0x2C */ u16 type;
    /* 0x2E */ s16 flags;
    /* 0x30 */ u16 context;
    /* 0x32 */ char pad_32[2];
    /* 0x34 */ u8 *romAddr;
} Asset; // size = 0x38

typedef struct ItemPool {
    /* 0x00 */ u8 *buffer;
    /* 0x04 */ s32 count;
    /* 0x08 */ u8 **elements;
    /* 0x0C */ s16 unk_0C;
} ItemPool; // size >= 0xE

typedef struct UnkMu {
    /* 0x00 */ Mtx unk_00;
    /* 0x40 */ Mtx unk_40;
    /* 0x80 */ struct UnkMu *unk_80;
    /* 0x84 */ struct UnkMu *unk_84;
    /* 0x88 */ struct UnkMu *unk_88;
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ s32 unk_90;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ Matrix4f unk_98;
    /* 0xD8 */ Matrix4f unk_D8;
} UnkMu; // size >= 0x118

typedef struct UnkCameraSub {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ Mtx unk_18;
} UnkCameraSub; // size = 0x58

typedef struct UnkCameraSub3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UnkCameraSub *unk_04;
} UnkCameraSub3;

typedef struct UnkCameraSub2 {
    /* 0x000 */ char unk_00[0x154];
    /* 0x154 */ UnkCameraSub3 *unk_154[1];
    /* 0x158 */ char unk_158[0x238 - 0x158];
    /* 0x238 */ s32 unk_238[1];
} UnkCameraSub2;

typedef struct UnkCameraSub5 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04[8];
    /* 0x24 */ s32 unk_24;
} UnkCameraSub5;

typedef struct UnkCameraSub4 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UnkCameraSub5 *unk_04;
    /* 0x08 */ UnkCameraSub *unk_08[5];
    /* 0x1C */ s32 unk_1C;
} UnkCameraSub4; // size = 0x20

typedef struct UnkCameraSub6 {
    /* 0x00 */ char unk_00[0x28];
    /* 0x28 */ UnkCameraSub3 *unk_28;
    /* 0x2C */ char unk_2C[0xC];
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ char unk_3C[0x58 - 0x3C];
} UnkCameraSub6; // size = 0x58

typedef struct Camera {
    /* 0x0000 */ s16 unk_000;
    /* 0x0002 */ char unk_002[10];
    /* 0x000C */ s16 unk_00C;
    /* 0x000E */ char unk_00E[2];
    /* 0x0010 */ UnkMu unk_010;
    /* 0x0128 */ UnkMu *unk_128;
    /* 0x012C */ s32 *unk_12C;
    /* 0x0130 */ char unk_130[0x404 - 0x130];
    /* 0x0404 */ Vec4i unk_404;
    /* 0x0414 */ s32 unk_414;
    /* 0x0418 */ s32 unk_418;
    /* 0x041C */ s32 unk_41C;
    /* 0x0420 */ char unk_420[0x604 - 0x420];
    /* 0x0604 */ s32 unk_604;
    /* 0x0608 */ UnkCameraSub4 unk_608[30];
    /* 0x09C8 */ s32 unk_9C8;
    /* 0x09CC */ char unk_9CC[12];
    /* 0x09D8 */ s32 unk_9D8;
    /* 0x09DC */ char unk_9DC[0x9E4 - 0x9DC];
    /* 0x09E4 */ Vec3i unk_9E4;
    /* 0x09F0 */ char unk_9F0[0xA08 - 0x9F0];
    /* 0x0A08 */ s32 unk_A08;
    /* 0x0A0C */ s16 unk_A0C;
    /* 0x0A0E */ s16 unk_A0E;
    /* 0x0A10 */ char unk_A10[0xA1C - 0xA10];
    /* 0x0A1C */ s16 unk_A1C;
    /* 0x0A1E */ s16 unk_A1E;
    /* 0x0A20 */ s16 unk_A20;
    /* 0x0A22 */ char unk_A22[6];
    /* 0x0A28 */ UnkCameraSub2 *unk_A28;
    /* 0x0A2C */ s32 unk_A2C;
    /* 0x0A30 */ s32 unk_A30;
    /* 0x0A34 */ s32 unk_A34;
    /* 0x0A38 */ UnkCameraSub *unk_A38;
    /* 0x0A3C */ char unk_A3C[0xC];
    /* 0x0A48 */ s32 *unk_A48;
    /* 0x0A4C */ s32 unk_A4C;
    /* 0x0A50 */ UnkCameraSub6 unk_A50;
    /* 0x0AA8 */ s32 *unk_AA8;
    /* 0x0AAC */ char unk_AAC[4];
    /* 0x0AB0 */ UnkCameraSub unk_AB0[60];
    /* 0x1F50 */ char unk_1F50[0x40];
} Camera; // size = 0x1F90

typedef struct UnkObjectSub2 {
    /* 0x00 */ s32 unk_00;
    /* 0x00 */ s32 unk_04;
    /* 0x00 */ s32 unk_08;
    /* 0x00 */ s32 unk_0C;
} UnkObjectSub2; // size = 0x10

typedef struct UnkObjectSub {
    /* 0x00 */ char unk_00[0x48];
    /* 0x48 */ UnkObjectSub2 *unk_48;
} UnkObjectSub;

typedef struct Object {
    /* 0x000 */ Vec4i unk_000;
    /* 0x010 */ Vec4i unk_010;
    /* 0x020 */ Vec4i pos;
    /* 0x030 */ char unk_030[0x50 - 0x30];
    /* 0x050 */ Vec3s rotation;
    /* 0x056 */ char unk_056[2];
    /* 0x058 */ s32 unk_058;
    /* 0x05C */ s32 unk_05C;
    /* 0x060 */ s32 unk_060;
    /* 0x064 */ char unk_064[0x74 - 0x64];
    /* 0x074 */ s16 unk_074;
    /* 0x076 */ s16 unk_076;
    /* 0x078 */ s16 unk_078;
    /* 0x07A */ s16 unk_07A;
    /* 0x07C */ s16 unk_07C;
    /* 0x07E */ s16 unk_07E;
    /* 0x080 */ s32 flags;
    /* 0x084 */ s16 unk_084;
    /* 0x086 */ s16 unk_086;
    /* 0x088 */ ColorRGBA unk_088;
    /* 0x08C */ s16 unk_08C;
    /* 0x08E */ char unk_08E[2];
    /* 0x090 */ s32 unk_090[13];
    /* 0x0C4 */ UnkObjectSub *sprite_map;
    /* 0x0C8 */ struct Camera *camera;
    /* 0x0CC */ char unk_0CC[4];
    /* 0x0D0 */ UnkMu unk_0D0;
    /* 0x1E8 */ char unk_1E8[4];
    /* 0x1EC */ void (*fn_update)(struct Object *);
    /* 0x1F0 */ struct ObjectTask *taskList;
    /* 0x1F4 */ struct ObjectTask *currentTask;
    /* 0x1F8 */ s16 unk_1F8;
    /* 0x1FA */ s16 unk_1FA;
    /* 0x1FC */ s32 unk_1FC;
    /* 0x200 */ ColorRGBA unk_200;
    /* 0x204 */ ColorRGBA unk_204;
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ char unk_20C[4];
    /* 0x210 */ struct Object *nextObject;
    /* 0x214 */ struct Object *prevObject;
} Object; // size = 0x218

typedef struct GlobalObjBSub {
    /* 0x00 */ s32 flags;
    /* 0x04 */ void (*func)(Object *);
    /* 0x08 */ s16 counter;
} GlobalObjBSub; // size = 0xC

typedef struct ObjectTask {
    /* 0x00 */ s32 flags;
    /* 0x04 */ void (*func)(Object *);
    /* 0x08 */ char unk_08[0x18];
    /* 0x20 */ u16 stackPos;
    /* 0x22 */ char unk_22[2];
    /* 0x24 */ GlobalObjBSub stack[8];
    /* 0x84 */ s16 counter;
    /* 0x86 */ s16 unk_86;
    /* 0x88 */ s16 id;
    /* 0x8A */ char unk_8A[6];
    /* 0x90 */ GlobalObjBSub unk_90;
    /* 0x9C */ struct ObjectTask *next;
} ObjectTask; // size = 0xA0

typedef struct SpriteDef {
    /* 0x00 */ s16 spriteID;
    /* 0x04 */ void (*unk_04)(Object *);
    /* 0x08 */ s32 flags;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ char *map_name;
} SpriteDef;

typedef struct UnkObjDef3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkObjDef3; // size = 0x10

typedef struct Texture {
    /* 0x00 */ u32 width;
    /* 0x04 */ u32 height;
    /* 0x08 */ s32 colorIndexed;
    /* 0x0C */ s32 flags;
    /* 0x10 */ u8 *raster;
    /* 0x14 */ u8 *palette;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ struct Texture *next;
} Texture; // size = 0x2C

#endif
