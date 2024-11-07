#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

typedef struct UnkDispStruct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ u32 unk_0C;
} UnkDispStruct; // size = 0x10

typedef struct DisplayData {
    /* 0x0000 */ char unk_00[0x80];
    /* 0x0080 */ Gfx unk_80[0xC00];
    /* 0x6080 */ Gfx unk_6080[0x400];
    /* 0x8080 */ UnkDispStruct unk_8080[0x200];
    /* 0xA080 */ char unk_A080[0x8008];
} DisplayData; // size = 0x12088

#endif
