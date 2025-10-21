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

typedef struct Vec3su {
    u16 vi[3];
} Vec3su;

typedef struct Vec4s {
    s16 x, y, z, w;
} Vec4s;

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

typedef struct RenderContext {
    /* 0x00 */ s16 perspNorm;
    /* 0x02 */ char unk_02[0xE];
    /* 0x10 */ s32 segmentTable[16];
    /* 0x50 */ char unk_50[0x14];
} RenderContext; // size = 0x64

typedef struct BatchHeader {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 numVertices;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 numTriangles;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ Gfx *texGfx;
    /* 0x10 */ Gfx otherMode;
} BatchHeader; // size = 0x18

typedef struct BatchInfo {
    /* 0x00 */ BatchHeader header;
    /* 0x18 */ Mtx transform;
} BatchInfo; // size = 0x58

typedef struct Batch {
    /* 0x00 */ RenderContext *context;
    /* 0x04 */ BatchInfo *info;
    /* 0x08 */ Vtx *vertices;
    /* 0x0C */ u16 *triangles;
} Batch; // size = 0x10

typedef struct DisplayData {
    /* 0x0000 */ Mtx mtxViewProj;
    /* 0x0040 */ char unk_40[0x40];
    /* 0x0080 */ Gfx gfxMain[0x800];
    /* 0x4080 */ Gfx unk_4080[0x400];
    /* 0x6080 */ Gfx gfxOverlay[0x400];
    /* 0x8080 */ Batch batchMain[0x800];
    /* 0x10080 */ Batch batchOverlay[0x200];
    /* 0x12080 */ u16 perspNorm;
    /* 0x12082 */ char unk_12082[6];
} DisplayData; // size = 0x12088

typedef struct UnkKappa {
    /* 0x00 */ u8 unk_0;
    /* 0x01 */ u8 unk_1;
    /* 0x02 */ u8 unk_2;
    /* 0x03 */ u8 unk_3;
    /* 0x04 */ s32 unk_4;
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ s32 unk_C;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} UnkKappa; // size = 0x20

typedef struct GameMode {
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
} GameMode; // size = 0x20

typedef struct PlayerInput {
    /* 0x00 */ u16 buttons;
    /* 0x02 */ u16 prev_buttons;
    /* 0x04 */ u16 held_buttons;
    /* 0x06 */ u16 raw_buttons;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 enabled;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
} PlayerInput;

typedef struct UnkGamma {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ void *data;
    /* 0x08 */ s32 priv;
    /* 0x0C */ void (*move_cb)(s32, s32, s32);
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
    /* 0x00 */ u32 width;
    /* 0x04 */ u32 height;
    /* 0x08 */ s32 format;
    /* 0x0C */ s32 palIndex;
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

typedef struct Transform {
    /* 0x00 */ Mtx mtx[2];
    /* 0x80 */ struct Transform *firstChild;
    /* 0x84 */ struct Transform *nextSibling;
    /* 0x88 */ struct Transform *parent;
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ s32 unk_90;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ Matrix4f local_matrix;
    /* 0xD8 */ Matrix4f wolrd_matrix;
} Transform; // size = 0x118

typedef struct BatchAsset {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u16 vertIndex;
    /* 0x06 */ u16 triOffset;
    /* 0x08 */ u16 numVertices;
    /* 0x0A */ u16 numTriangles;
    /* 0x0C */ TextureAsset *texture;
} BatchAsset; // size = 0x10

typedef struct ModelNodeAsset {
    /* 0x00 */ s32 numVertices;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vtx *vertices;
    /* 0x0C */ Vec3su *triangles;
    /* 0x10 */ char unk_10[0x8];
    /* 0x18 */ s32 numParts;
    /* 0x1C */ BatchAsset *batchAssets;
} ModelNodeAsset; // size = 0x20

typedef struct AssetUnkHeader {
    /* 0x00 */ u8 signature[4]; // '2KMD' or '@KMD' ??
    /* 0x04 */ s32 numEntries;
    /* 0x08 */ s32 offsets[1];
} AssetUnkHeader;

typedef struct AssetGmd {
    /* 0x00 */ u32 numNodes;
    /* 0x04 */ ModelNodeAsset *nodes;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ char unk_0C[0xA0];
    /* 0xAC */ s32 unk_AC;
    /* 0xB0 */ s32 unk_B0;
    /* 0xB4 */ s32 unk_B4;
    /* 0xB8 */ AssetUnkHeader *unk_B8;
    /* 0xBC */ char unk_BC[4];
    /* 0xC0 */ u8 *palettes16;
    /* 0xC4 */ u8 *palettes256;
    /* 0xC8 */ u8 unk_C8;
    /* 0xCC */ BatchAsset unk_CC[0];
} AssetGmd; // size = 0xCC

typedef struct AssetUnkHeader2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} AssetUnkHeader2;

typedef struct StructAA8 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 z;
} StructAA8; // size = 0x10

typedef struct ModelNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ s32 unk_04[4];
    /* 0x14 */ Vec3i unk_14;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ Batch *unk_28[4]; // union Batch or Mtx
    /* 0x38 */ s32 unk_38[4];
    /* 0x48 */ Gfx *unk_48[4];
} ModelNode; // size = 0x58

typedef struct UnkSamSub {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ ColorRGBA unk_04[16];
    /* 0x44 */ s16 unk_44[16];
} UnkSamSub; // size = 0x64;

typedef union AnimEntry {
    s32 w;
    struct {
        u8 b0;
        u8 b1;
        u8 b2;
        u8 b3;
    };
} AnimEntry;

typedef struct AnimHeader {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    AnimEntry entries[1];
} AnimHeader;

typedef struct UnkSam {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ AssetGmd *unk_04;
    /* 0x008 */ char unk_08[0x128 - 8];
    /* 0x128 */ s32 unk_128;
    /* 0x12C */ char unk_12C[0x148 - 0x12C];
    /* 0x148 */ AnimHeader **unk_148;
    /* 0x14C */ s32 unk_14C;
    /* 0x150 */ StructAA8 *unk_150;
    /* 0x154 */ union {
        Batch *batches[28];
        Gfx *dlist[28 * 2];
    };
    /* 0x234 */ u16 unk_234;
    /* 0x236 */ s16 unk_236;
    /* 0x238 */ s32 batchCounts[28];
    /* 0x2A8 */ BatchInfo *batchInfos[28];
    /* 0x318 */ u8 unk_318;
    /* 0x319 */ char unk_319[3];
    /* 0x31C */ ModelNode *unk_31C;
    /* 0x320 */ u8 unk_320;
    /* 0x321 */ u8 unk_321;
    /* 0x322 */ u8 unk_322;
    /* 0x323 */ u8 unk_323;
    /* 0x324 */ UnkSamSub *unk_324[28];
    /* 0x394 */ u16 unk_394[28];
    /* 0x3CC */ s32 unk_3CC;
} UnkSam; // size = 0x3D0

typedef struct UnkFrodo {
    /* 0x000 */ UnkSam sam;
    /* 0x3D0 */ char unk_3D0[0xA64 - 0x3D0];
    /* 0xA64 */ u16 unk_A64;
} UnkFrodo; // szie = 0xA68

typedef struct ModelNodeRenderInfo {
    /* 0x00 */ s32 zOrder;
    /* 0x04 */ ModelNode *unk_04;
    /* 0x08 */ BatchInfo *unk_08[4];
    /* 0x18 */ struct ModelNodeRenderInfo *next;
    /* 0x1C */ s32 flags;
} ModelNodeRenderInfo; // size = 0x20

typedef struct ModelInstance {
    /* 0x0000 */ s16 numNodes;
    /* 0x0002 */ s16 unk_002;
    /* 0x0004 */ s16 unk_004;
    /* 0x0006 */ s16 unk_006;
    /* 0x0008 */ char unk_008[4];
    /* 0x000C */ s16 unk_00C;
    /* 0x000E */ char unk_00E[2];
    /* 0x0010 */ Transform unk_010;
    /* 0x0128 */ Transform *transforms;
    /* 0x012C */ AnimHeader **animations;
    /* 0x0130 */ s16 unk_130;
    /* 0x0132 */ s16 unk_132;
    /* 0x0134 */ Vec4s nodeRotation[30];
    /* 0x0224 */ Vec4i nodeScale[30];
    /* 0x0404 */ Vec4i nodePosition[30];
    /* 0x05E4 */ u8 unk_5E4[32];
    /* 0x0604 */ ModelNode *unk_604;
    /* 0x0608 */ ModelNodeRenderInfo unk_608[30];
    /* 0x09C8 */ s32 unk_9C8;
    /* 0x09CC */ Vec3s unk_9CC;
    /* 0x09D2 */ char unk_9D2[2];
    /* 0x09D8 */ Vec4i unk_9D4;
    /* 0x09E4 */ Vec4i unk_9E4;
    /* 0x09F4 */ u8 unk_9F4;
    /* 0x09F8 */ Vec4i unk_9F8;
    /* 0x0A08 */ s32 numAnimFrames;
    /* 0x0A0C */ s16 currentAnimId;
    /* 0x0A0E */ s16 unk_A0E;
    /* 0x0A10 */ s32 unk_A10;
    /* 0x0A14 */ AnimEntry *unk_A14;
    /* 0x0A18 */ s32 unk_A18;
    /* 0x0A1C */ s16 unk_A1C;
    /* 0x0A1E */ s16 unk_A1E;
    /* 0x0A20 */ s16 unk_A20;
    /* 0x0A22 */ char unk_A22[2];
    /* 0x0A24 */ UnkFrodo *unk_A24;
    /* 0x0A28 */ UnkSam *unk_A28;
    /* 0x0A2C */ s32 unk_A2C;
    /* 0x0A30 */ ModelNodeRenderInfo unk_A30;
    /* 0x0A50 */ ModelNode unk_A50;
    /* 0x0AA8 */ StructAA8 *unk_AA8;
    /* 0x0AAC */ char unk_AAC[4];
    /* 0x0AB0 */ BatchInfo unk_AB0[60];
    /* 0x1F50 */ u8 unk_1F50[30];
    /* 0x1F6E */ u8 unk_1F6E[30];
    /* 0x1F8C */ char unk_1F8C[4];
} ModelInstance; // size = 0x1F90

typedef struct AssetSP2Sub3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} AssetSP2Sub3; // size ?

typedef struct AssetSP2Sub2 {
    /* 0x00 */ s32 numParts;
    /* 0x04 */ AssetSP2Sub3 *parts;
    /* 0x08 */ s32 tex_index;
    /* 0x0C */ TextureAsset *texture;
} AssetSP2Sub2; // size = 0x10

typedef struct AssetSP2 {
    /* 0x00 */ s32 size;
    /* 0x04 */ u32 numSprites;
    /* 0x08 */ char texture_name[4][16];
    /* 0x48 */ AssetSP2Sub2 *sprites;
} AssetSP2;

typedef struct Object {
    /* 0x000 */ Vec4i unk_000;
    /* 0x010 */ Vec4i unk_010;
    /* 0x020 */ Vec4i pos;
    /* 0x030 */ char unk_030[0x50 - 0x30];
    /* 0x050 */ Vec4s rotation;
    /* 0x058 */ s32 unk_058;
    /* 0x05C */ s32 unk_05C;
    /* 0x060 */ s32 unk_060;
    /* 0x064 */ char unk_064[0x70 - 0x64];
    /* 0x070 */ s16 unk_070;
    /* 0x072 */ s16 unk_072;
    /* 0x074 */ s16 unk_074;
    /* 0x076 */ s16 unk_076;
    /* 0x078 */ s16 unk_078;
    /* 0x07A */ s16 unk_07A;
    /* 0x07C */ s16 unk_07C;
    /* 0x07E */ s16 unk_07E;
    /* 0x080 */ s32 flags;
    /* 0x084 */ s16 spriteId;
    /* 0x086 */ s16 unk_086;
    /* 0x088 */ ColorRGBA unk_088;
    /* 0x08C */ s16 unk_08C;
    /* 0x08E */ char unk_08E[2];
    /* 0x090 */ union {
        s32 vars[13];
        struct Object *varObj[13];
    };
    /* 0x0C4 */ AssetSP2 *sprite_map;
    /* 0x0C8 */ ModelInstance *modInst;
    /* 0x0CC */ char unk_0CC[4];
    /* 0x0D0 */ Transform transform;
    /* 0x1E8 */ void (*unk_1E8)(struct Object *, struct Object *);
    /* 0x1EC */ void (*fn_render)(struct Object *);
    /* 0x1F0 */ struct ObjectTask *taskList;
    /* 0x1F4 */ struct ObjectTask *currentTask;
    /* 0x1F8 */ s16 unk_1F8;
    /* 0x1FA */ s16 unk_1FA;
    /* 0x1FC */ s32 unk_1FC;
    /* 0x200 */ ColorRGBA unk_200;
    /* 0x204 */ ColorRGBA unk_204;
    /* 0x208 */ struct GlobalObjD *unk_208;
    /* 0x20C */ char unk_20C[4];
    /* 0x210 */ struct Object *nextObject;
    /* 0x214 */ struct Object *prevObject;
} Object; // size = 0x218

typedef struct GlobalObjBSub {
    /* 0x00 */ u32 flags;
    /* 0x04 */ void (*func)(Object *);
    /* 0x08 */ s16 counter;
} GlobalObjBSub; // size = 0xC

typedef struct ObjectTaskSub {
    union {
        s32 unk_00_i;
        void (*unk_00_f)(Object *);
    };
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ void (*unk_10)(Object *);
    /* 0x14 */ char unk_14[4];
} ObjectTaskSub; // size >= 0xC

typedef struct ObjectTask {
    /* 0x00 */ u32 flags;
    /* 0x04 */ void (*func)(Object *);
    /* 0x08 */ ObjectTaskSub unk_08;
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

typedef struct UIElement {
    /* 0x00 */ s16 spriteID;
    /* 0x04 */ void (*func)(Object *);
    /* 0x08 */ s32 flags;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ char *map_name;
} UIElement;

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

typedef struct PlayerSub3 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[0x20 - 0xA];
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s32 unk_34;
} PlayerSub3; // size = 0x38

typedef struct PlayerSub5 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ void (*unk_04)(Object *);
    /* 0x08 */ void (*unk_08)(Object *);
    /* 0x0C */ u8 (*unk_0C)(Object *);
    /* 0x10 */ s32 unk_10;
} PlayerSub5;

typedef struct PlayerSub6Sub1 {
    /* 0x00 */ char unk_00[0xA0];
} PlayerSub6Sub1; // size >= 0xA0

typedef struct PlayerSub6 {
    /* 0x0000 */ char unk_00[0xC];
    /* 0x000C */ PlayerSub6Sub1 unk_0C;
    /* 0x00AC */ char unk_AC[0x40];
    /* 0x00EC */ PlayerSub6Sub1 unk_EC;
    /* 0x018C */ char unk_18C[0x1D0 - 0x18C];
    /* 0x01D0 */ s32 unk_1D0;
    /* 0x01D4 */ char unk_1D4[0x1458 - 0x1D4];
} PlayerSub6; // size = 0x1458;

typedef struct PlayerSub8 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ char unk_0C[0x10];
} PlayerSub8; // size = 0x1C

typedef struct PlayerSub9 {
    /* 0x000 */ char unk_00[8];
    /* 0x008 */ Vec4f *unk_08;
    /* 0x00C */ Vec4f *unk_0C;
    /* 0x010 */ Vec4f *unk_10;
    /* 0x014 */ Vec4f *unk_14;
    /* 0x018 */ Vec4f *unk_18;
    /* 0x01C */ char unk_1C[0x10];
    /* 0x02C */ s32 unk_2C;
    /* 0x030 */ s32 unk_30;
    /* 0x034 */ s32 unk_34;
    /* 0x038 */ Transform unk_1D0;
    /* 0x150 */ Transform unk_2E8;
} PlayerSub9;

typedef struct PlayerSubB {
    /* 0x00 */ char unk_00[0x18];
} PlayerSubB; // size = 0x18

typedef struct PlayerSubC {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
} PlayerSubC; // size = 0x8

typedef struct PlayerSubD {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
} PlayerSubD; // size = 0x4

typedef struct PlayerSubE {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} PlayerSubE; // size = 0x8

typedef struct PlayerSubF {
    /* 0x00 */ s32 unk_00[2];
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} PlayerSubF; // size = 0x10

typedef struct Player {
    /* 0x0000 */ Object *unk_00;
    /* 0x0004 */ s16 playerId;
    /* 0x0006 */ s16 characterId;
    /* 0x0008 */ ObjectTask *unk_08;
    /* 0x000C */ ObjectTask *unk_0C;
    /* 0x0010 */ ObjectTask *unk_10;
    /* 0x0014 */ ObjectTask *unk_14;
    /* 0x0018 */ ObjectTask *unk_18;
    /* 0x001C */ PlayerSubE *unk_1C;
    /* 0x0020 */ PlayerSub3 *unk_20;
    /* 0x0024 */ PlayerSub5 *unk_24;
    /* 0x0028 */ PlayerSubF *unk_28;
    /* 0x002C */ PlayerSub8 *unk_2C;
    /* 0x0030 */ PlayerSubD *unk_30;
    /* 0x0034 */ s16 *unk_34;
    /* 0x0038 */ s16 *unk_38;
    /* 0x003C */ s32 unk_3C;
    /* 0x0040 */ PlayerSubC *unk_40;
    /* 0x0044 */ s32 *unk_44;
    /* 0x0048 */ s32 unk_48;
    /* 0x004C */ PlayerSubB *unk_4C;
    /* 0x0050 */ s32 unk_50;
    /* 0x0054 */ s32 unk_54;
    /* 0x0058 */ s32 unk_58;
    /* 0x005C */ s32 unk_5C;
    /* 0x0060 */ s32 unk_60;
    /* 0x0064 */ s32 unk_64;
    /* 0x0068 */ u8 *unk_68;
    /* 0x006C */ s32 unk_6C;
    /* 0x0070 */ s16 unk_70;
    /* 0x0072 */ s16 unk_72;
    /* 0x0074 */ s16 unk_74;
    /* 0x0076 */ s16 unk_76;
    /* 0x0078 */ s16 unk_78;
    /* 0x007A */ s16 unk_7A;
    /* 0x007C */ s16 unk_7C;
    /* 0x007E */ s16 unk_7E;
    /* 0x0080 */ s32 unk_80;
    /* 0x0084 */ s32 unk_84;
    /* 0x0088 */ PlayerSubF *unk_88;
    /* 0x008C */ s32 unk_8C;
    /* 0x0090 */ PlayerSub3 *unk_90;
    /* 0x0094 */ s16 unk_94;
    /* 0x0096 */ s16 unk_96;
    /* 0x0098 */ PlayerSub5 *unk_98;
    /* 0x009C */ PlayerSubB *unk_9C;
    /* 0x00A0 */ PlayerSub8 *unk_A0;
    /* 0x00A4 */ PlayerSub8 *unk_A4;
    /* 0x00A8 */ s32 unk_A8;
    /* 0x00AC */ s32 unk_AC;
    /* 0x00B0 */ s32 unk_B0;
    /* 0x00B4 */ s16 *unk_B4;
    /* 0x00B8 */ s16 *unk_B8;
    /* 0x00BC */ void (*unk_BC)(Object *);
    /* 0x00C0 */ s16 unk_C0;
    /* 0x00C2 */ s16 unk_C2;
    /* 0x00C4 */ s32 unk_C4;
    /* 0x00C8 */ char unk_C8[0x180 - 0xC8];
    /* 0x0180 */ s32 unk_180;
    /* 0x0184 */ u8 unk_184;
    /* 0x0186 */ s16 unk_186;
    /* 0x0188 */ s16 unk_188;
    /* 0x018A */ s16 unk_18A;
    /* 0x018C */ s32 unk_18C;
    /* 0x0190 */ s32 unk_190;
    /* 0x0194 */ s32 unk_194;
    /* 0x0198 */ PlayerSub9 unk_198;
    /* 0x0400 */ char unk_400[0x750 - 0x400];
    /* 0x0750 */ Transform unk_750;
    /* 0x0868 */ Transform unk_868;
    /* 0x0980 */ char unk_980[40];
    /* 0x09A8 */ s32 unk_9A8;
    /* 0x09AC */ s32 unk_9AC;
    /* 0x09B0 */ s32 unk_9B0;
    /* 0x09B4 */ s32 unk_9B4;
    /* 0x09B8 */ char unk_9B8[1024];
    /* 0x0DB8 */ s16 unk_DB8;
    /* 0x0DBA */ s16 unk_DBA;
    /* 0x0DBC */ s16 unk_DBC;
    /* 0x0DBE */ s16 unk_DBE;
    /* 0x0DC0 */ void *unk_DC0[3]; // size unknown
    /* 0x0DCC */ void *unk_DCC[3]; // size unknown
    /* 0x0DD8 */ char unk_DD8[4];
    /* 0x0DDC */ UnkSam *unk_DDC;
    /* 0x0DE0 */ char unk_DE0[4];
    /* 0x0DE4 */ UnkSam *unk_DE4;
    /* 0x0DE8 */ PlayerSub6 unk_DE8;
    /* 0x2240 */ PlayerSub6 unk_2240;
    /* 0x3698 */ PlayerSub6 unk_3698;
    /* 0x4AF0 */ PlayerSub6 unk_4AF0;
    /* 0x5F48 */ s16 unk_5F48;
    /* 0x5F4A */ u8 unk_5F4A;
    /* 0x5F4B */ u8 unk_5F4B;
    /* 0x5F4C */ s16 unk_5F4C;
    /* 0x5F4E */ s16 unk_5F4E;
} Player; // size = 0x5F50

typedef struct Player12 {
    /* 0x00 */ s16 characterId;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ char unk_03;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ char unk_07;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F;
    /* 0x0F */ u8 unk_10;
    /* 0x0F */ u8 unk_11;
} Player12; // size = 0x12

typedef struct K2DefSub {
    /* 0x00 */ s32 unk_00[4];
    /* 0x10 */ s32 unk_10;
} K2DefSub; // size = 0x14

typedef struct K2Def {
    /* 0x00 */ char *unk_00;
    /* 0x04 */ void (*unk_04)(Object *);
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ K2DefSub *unk_0C;
} K2Def;

typedef struct UnkK2Def {
    /* 0x00 */ char *unk_00;
    /* 0x04 */ void (*unk_04)(Object *);
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} UnkK2Def;

typedef struct Unk80015E74 {
    /* 0x00 */ char *unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ void (*unk_08)(Object *);
    /* 0x0C */ s32 unk_0C;
} Unk80015E74;

typedef struct Unk8000C3CCArg3 {
    /* 0x00 */ Gfx combineMode;
    /* 0x08 */ s32 renderMode;
    /* 0x0C */ s32 unk_0C;
    /* 0x0C */ ColorRGBA primColor;
    /* 0x0C */ s32 flags;
} Unk8000C3CCArg3;

typedef struct UnkTauSub {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} UnkTauSub;

typedef struct UnkTau {
    /* 0x00 */ UnkTauSub *unk_00;
    /* 0x04 */ K2Def *unk_04;
    /* 0x08 */ s32 unk_08[2];
} UnkTau; // size = 0x10

typedef struct Unk_8004BA6C {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} Unk_8004BA6C; // size = 0xC

typedef struct UnkVec2s {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} UnkVec2s; // size = 0x4

typedef struct GlobalObjD {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x2C */ Object *unk_28;
    /* 0x2C */ struct GlobalObjD *unk_2C;
    /* 0x30 */ struct GlobalObjD *unk_30;
} GlobalObjD; // size = 0x34

#endif
