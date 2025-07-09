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

typedef struct UnkDelta {
    /* 0x00 */ void (*unk_00)(void);
    /* 0x04 */ char unk_04[8];
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
    /* 0x18 */ char unk_18[8];
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

#endif
