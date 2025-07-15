#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

typedef struct UnkDispStructPart1 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[0xE];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char unk_18[0x64 - 0x18];
} UnkDispStructPart1; // size = 0x64

typedef struct UnkDispStructPart2 {
    /* 0x00 */ char unk_00[0x18];
} UnkDispStructPart2; // size = 0x18

typedef struct UnkDispStruct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ UnkDispStructPart2 *unk_04;
    /* 0x08 */ Vtx *unk_08;
    /* 0x0C */ u16 *unk_0C;
} UnkDispStruct; // size = 0x10

typedef struct DisplayData {
    /* 0x0000 */ Mtx unk_00;
    /* 0x0040 */ char unk_40[0x40];
    /* 0x0080 */ Gfx unk_80[0x800];
    /* 0x4080 */ Gfx unk_4080[0x400];
    /* 0x6080 */ Gfx unk_6080[0x400];
    /* 0x8080 */ UnkDispStruct unk_8080[0x800];
    /* 0x10080 */ UnkDispStruct unk_10080[0x200];
    /* 0x12080 */ u16 unk_12080;
    /* 0x12082 */ char unk_12082[6];
} DisplayData; // size = 0x12088

typedef struct UnkKappa {
    /* 0x00 */ char unk_00[16];
} UnkKappa; // size = 0x10

typedef struct UnkDelta {
    /* 0x00 */ void (*unk_00)(void);
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
    /* 0x0B */ u8 unk_0B;
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

typedef struct WadStructGamma {
    /* 0x00 */ void *data;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char name[20];
    /* 0x24 */ s32 size;
    /* 0x28 */ s32 unpacked_size;
    /* 0x2C */ u16 type;
    /* 0x2E */ s16 flags;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ char pad_32[2];
    /* 0x34 */ u8 *romAddr;
} WadStructGamma; // size = 0x38

typedef struct UnkItemAlpha {
    /* 0x00 */ u8 *buffer;
    /* 0x04 */ s32 count;
    /* 0x08 */ u8 **elements;
    /* 0x0C */ s16 unk_0C;
} UnkItemAlpha; // size >= 0xE

typedef struct GlobalObjA {
    /* 0x000 */ char unk_000[0x74];
    /* 0x074 */ s16 unk_074;
    /* 0x076 */ char unk_076[10];
    /* 0x080 */ s32 unk_080;
    /* 0x084 */ char unk_084[68];
    /* 0x0C8 */ struct GlobalObjC *unk_0C8;
    /* 0x0CC */ char unk_0CC[324];
    /* 0x210 */ struct GlobalObjA *nextObject;
    /* 0x214 */ struct GlobalObjA *prevObject;
} GlobalObjA; // size = 0x218

typedef struct GlobalObjB {
    /* 0x000 */ char unk_000[0xA0];
} GlobalObjB; // size = 0xA0

typedef struct GlobalObjC {
    /* 0x000 */ char unk_000[0x128];
    /* 0x128 */ void *unk_128;
    /* 0x12C */ char unk_12C[7780];
} GlobalObjC; // size = 0x1F90

#endif
