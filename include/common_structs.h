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

struct Object;
struct Player;
typedef void (*ObjFunc)(struct Object *);

typedef struct RenderContext {
    /* 0x00 */ s16 perspNorm;
    /* 0x02 */ char pad_02[6];
    /* 0x08 */ Gfx unk_08;
    /* 0x10 */ s32 segmentTable[16];
    /* 0x50 */ Vp unk_50;
    /* 0x60 */ Gfx *unk_60;
} RenderContext; // size = 0x64

typedef struct BatchHeader {
    /* 0x00 */ s32 triMask;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 vtxNum;
    /* 0x09 */ u8 vtxOffset;
    /* 0x0A */ u8 numTriangles;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ Gfx *texGfx;
    /* 0x10 */ Gfx otherMode;
} BatchHeader; // size = 0x18

typedef struct BatchInfo {
    /* 0x00 */ BatchHeader header;
    /* 0x18 */ Mtx transform;
} BatchInfo; // size = 0x58

typedef struct BatchTriangle {
    /* 0x00 */ s8 vi0;
    /* 0x01 */ s8 vi1;
    /* 0x02 */ s8 vi2;
    /* 0x03 */ s8 d;
} BatchTriangle; // size = 4

typedef struct Batch {
    /* 0x00 */ RenderContext *context;
    /* 0x04 */ BatchInfo *info;
    /* 0x08 */ Vtx *vertices;
    /* 0x0C */ BatchTriangle *triangles;
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

typedef struct DirectionalLight {
    /* 0x00 */ ColorRGBA color;
    /* 0x04 */ s32 dir_x;
    /* 0x08 */ s32 dir_y;
    /* 0x0C */ s32 dir_z;
} DirectionalLight; // size = 0x10

typedef struct GlobalLighting {
    /* 0x00 */ DirectionalLight lights[2];
} GlobalLighting; // size = 0x20

typedef struct GameMode {
    /* 0x00 */ void (*fn_run)(void);
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ s32 unk_08;
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
    /* 0x18 */ GlobalLighting *unk_18;
    /* 0x1C */ ColorRGBA ambient_color;
} GameMode; // size = 0x20

typedef struct PlayerInput {
    /* 0x00 */ u16 buttons;
    /* 0x02 */ u16 prev_buttons;
    /* 0x04 */ u16 held_buttons;
    /* 0x06 */ u16 raw_buttons;
    /* 0x08 */ u8 pendingInput;
    /* 0x09 */ u8 mirrored;
    /* 0x0A */ u8 enabled;
    /* 0x0B */ u8 connected;
    /* 0x0C */ u8 remapped;
    /* 0x0D */ u8 disableStick;
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
    /* 0x8C */ s32 id;
    /* 0x90 */ s32 parentId;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ Matrix4f local_matrix;
    /* 0xD8 */ Matrix4f world_matrix;
} Transform; // size = 0x118

typedef struct BatchAsset {
    /* 0x00 */ s32 texIndex;
    /* 0x04 */ u16 vertIndex;
    /* 0x06 */ u16 triOffset;
    /* 0x08 */ u16 numVertices;
    /* 0x0A */ u16 numTriangles;
    /* 0x0C */ TextureAsset *texture;
} BatchAsset; // size = 0x10

typedef struct ModelNodeAsset {
    /* 0x00 */ s32 numVertices;
    /* 0x04 */ s32 numTriangles;
    /* 0x08 */ Vtx *vertices;
    /* 0x0C */ Vec3su *triangles;
    /* 0x10 */ char unk_10[0x8];
    /* 0x18 */ s32 numBatches;
    /* 0x1C */ BatchAsset *batchAssets;
} ModelNodeAsset; // size = 0x20

typedef struct ModelFileHeader {
    /* 0x00 */ u8 signature[4]; // '2KMD' or '@KMD' ??
    /* 0x04 */ s32 numNodes;
    /* 0x08 */ s32 offsets[1];
} ModelFileHeader;

typedef struct NodeAttachment {
    /* 0x00 */ s32 parent;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 z;
} NodeAttachment; // size = 0x10

typedef struct ModelAsset {
    /* 0x00 */ u32 numNodes;
    /* 0x04 */ ModelNodeAsset *nodes;
    /* 0x08 */ NodeAttachment *nodeHierarchy;
    /* 0x0C */ char unk_0C[0xA0];
    /* 0xAC */ s32 rawFileMemSlot;
    /* 0xB0 */ s32 fileFormat;
    /* 0xB4 */ s32 numTextures;
    /* 0xB8 */ ModelFileHeader *header;
    /* 0xBC */ char unk_BC[4];
    /* 0xC0 */ u8 *palettes16;
    /* 0xC4 */ u8 *palettes256;
    /* 0xC8 */ u8 unk_C8;
    /* 0xCC */ BatchAsset legacyBatches[0];
} ModelAsset; // size = 0xCC

typedef struct ModelNodeFileEntry {
    /* 0x00 */ s32 numVertices;
    /* 0x04 */ s32 numTriangles;
    /* 0x08 */ s32 verticesOffset;
    /* 0x0C */ s32 trianglesOffset;
    /* 0x10 */ s32 numBatchesOffset;
    /* 0x14 */ s32 unused;
} ModelNodeFileEntry;

typedef struct NodeCluster {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ s32 group[4];
    /* 0x14 */ Vec3i centroid;
    /* 0x20 */ s32 singleNode;
    /* 0x24 */ u32 groupSize;
    /* 0x28 */ Batch *transforms[4]; // union Batch or Mtx
    /* 0x38 */ s32 batchCounts[4];
    /* 0x48 */ Gfx *dlists[4];
} NodeCluster; // size = 0x58

typedef struct VertexPositionGroup {
    /* 0x00 */ u8 normal_x;
    /* 0x01 */ u8 normal_y;
    /* 0x02 */ u8 normal_z;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ ColorRGBA original_colors[16];
    /* 0x44 */ s16 vertex_indices[16];
} VertexPositionGroup; // size = 0x64;

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

typedef struct Model {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ ModelAsset *modelAsset;
    /* 0x008 */ char unk_08[0x128 - 8];
    /* 0x128 */ s32 numNodes;
    /* 0x12C */ char unk_12C[0x148 - 0x12C];
    /* 0x148 */ AnimHeader **animations;
    /* 0x14C */ s32 animCount;
    /* 0x150 */ NodeAttachment *nodeHierarchy;
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
    /* 0x31C */ NodeCluster *unk_31C;
    /* 0x320 */ u8 unk_320;
    /* 0x321 */ u8 unk_321;
    /* 0x322 */ u8 unk_322;
    /* 0x323 */ u8 unk_323;
    /* 0x324 */ VertexPositionGroup *vertex_position_groups[28];
    /* 0x394 */ u16 num_vertex_position_groups[28];
    /* 0x3CC */ s32 unk_3CC;
} Model; // size = 0x3D0

typedef struct KModel {
    /* 0x000 */ Model model;
    /* 0x3D0 */ char unk_3D0[0xA64 - 0x3D0];
    /* 0xA64 */ u16 unk_A64;
} KModel; // szie = 0xA68

typedef struct ClusterRenderSlot {
    /* 0x00 */ s32 zOrder;
    /* 0x04 */ NodeCluster *cluster;
    /* 0x08 */ BatchInfo *unk_08[4];
    /* 0x18 */ struct ClusterRenderSlot *next;
    /* 0x1C */ s32 flags;
} ClusterRenderSlot; // size = 0x20

typedef struct ModelInstance {
    /* 0x0000 */ s16 numNodes;
    /* 0x0002 */ Vec3s velocity;
    /* 0x0008 */ Vec3s anotherVel;
    /* 0x000E */ char unk_00E[2];
    /* 0x0010 */ Transform rootTransform;
    /* 0x0128 */ Transform *transforms;
    /* 0x012C */ AnimHeader **animations;
    /* 0x0130 */ s16 unk_130;
    /* 0x0132 */ s16 unk_132;
    /* 0x0134 */ Vec4s nodeRotation[30];
    /* 0x0224 */ Vec4i nodeScale[30];
    /* 0x0404 */ Vec4i nodePosition[30];
    /* 0x05E4 */ u8 nodeUpdated[30];
    /* 0x0604 */ NodeCluster *nodeClusters;
    /* 0x0608 */ ClusterRenderSlot unk_608[30];
    /* 0x09C8 */ s32 unk_9C8;
    /* 0x09CC */ Vec3s rootRotation;
    /* 0x09D8 */ Vec4i currentRootPos;
    /* 0x09E4 */ Vec4i baseRootPos;
    /* 0x09F4 */ u8 rootUpdated;
    /* 0x09F8 */ Vec4i rootScale;
    /* 0x0A08 */ s32 numAnimFrames;
    /* 0x0A0C */ s16 currentAnimId;
    /* 0x0A0E */ s16 previousAnimId;
    /* 0x0A10 */ s32 unk_A10;
    /* 0x0A14 */ AnimEntry *unk_A14;
    /* 0x0A18 */ s32 unk_A18;
    /* 0x0A1C */ s16 unk_A1C;
    /* 0x0A1E */ s16 unk_A1E;
    /* 0x0A20 */ s16 unk_A20;
    /* 0x0A22 */ char unk_A22[2];
    /* 0x0A24 */ KModel *kmodel;
    /* 0x0A28 */ Model *model;
    /* 0x0A2C */ s32 unk_A2C;
    /* 0x0A30 */ ClusterRenderSlot unk_A30;
    /* 0x0A50 */ NodeCluster unk_A50;
    /* 0x0AA8 */ NodeAttachment *nodeAttachments;
    /* 0x0AAC */ char unk_AAC[4];
    /* 0x0AB0 */ BatchInfo renderBatches[60];
    /* 0x1F50 */ u8 nodeOpaquePrev[30];
    /* 0x1F6E */ u8 nodeOpaque[30];
    /* 0x1F8C */ char unk_1F8C[4];
} ModelInstance; // size = 0x1F90

typedef struct AssetSP2Sub3 {
    /* 0x00 */ s32 topT;
    /* 0x04 */ u32 leftS;
    /* 0x08 */ u32 rightS;
    /* 0x0C */ s32 bottomT;
    /* 0x10 */ s32 offsetX;
    /* 0x14 */ s32 offsetY;
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
    /* 0x000 */ Vec4i acceleration;
    /* 0x010 */ Vec4i velocity;
    /* 0x020 */ Vec4i pos;
    /* 0x030 */ char unk_030[0x40 - 0x30];
    /* 0x040 */ Vec4i unk_040;
    /* 0x050 */ Vec4s rotation;
    /* 0x058 */ s32 unk_058;
    /* 0x05C */ s32 unk_05C;
    /* 0x060 */ s32 unk_060;
    /* 0x064 */ char unk_064[0x70 - 0x64];
    /* 0x070 */ s16 playerHp;
    /* 0x072 */ s16 unk_072;
    /* 0x074 */ s16 priority;
    /* 0x076 */ s16 unk_076;
    /* 0x078 */ s16 unk_078;
    /* 0x07A */ s16 unk_07A;
    /* 0x07C */ s16 unk_07C;
    /* 0x07E */ s16 unk_07E;
    /* 0x080 */ s32 flags;
    /* 0x084 */ s16 frameIndex;
    /* 0x086 */ s16 previousFrameIndex;
    /* 0x088 */ ColorRGBA color;
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
    /* 0x1EC */ ObjFunc fn_render;
    /* 0x1F0 */ struct ObjectTask *taskList;
    /* 0x1F4 */ struct ObjectTask *currentTask;
    /* 0x1F8 */ s16 unk_1F8;
    /* 0x1FA */ s16 unk_1FA;
    /* 0x1FC */ s32 unk_1FC;
    /* 0x200 */ ColorRGBA unk_200;
    /* 0x204 */ ColorRGBA unk_204;
    /* 0x208 */ struct GlobalObjD *light;
    /* 0x20C */ char unk_20C[4];
    /* 0x210 */ struct Object *nextObject;
    /* 0x214 */ struct Object *prevObject;
} Object; // size = 0x218

typedef struct TaskContext {
    /* 0x00 */ u32 flags;
    /* 0x04 */ ObjFunc func;
    /* 0x08 */ s16 start_delay;
} TaskContext; // size = 0xC

typedef struct TransitionRule {
    /* 0x00 */ s16 timingIndex;
    /* 0x02 */ u16 requiredButtons;
    /* 0x04 */ u16 flags;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ s16 behaviorId;
    /* 0x0A */ s16 targetStateId;
    /* 0x0C */ u16 button_mask;
    /* 0x0E */ u8 unk_0E[11];
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ char unk_1C[2];
} TransitionRule; // size = 0x1C

typedef struct ObjectTask {
    /* 0x00 */ u32 flags;
    /* 0x04 */ ObjFunc func;
    /* 0x08 */ s32 params[6];
    /* 0x20 */ u16 stackPos;
    /* 0x24 */ TaskContext stack[8];
    /* 0x84 */ s16 start_delay;
    /* 0x86 */ s16 triggerAt;
    /* 0x88 */ s16 id;
    /* 0x8A */ char unk_8A[6];
    /* 0x90 */ TaskContext triggerSlot;
    /* 0x9C */ struct ObjectTask *next;
} ObjectTask; // size = 0xA0

typedef struct UIElement {
    /* 0x00 */ s16 spriteID;
    /* 0x04 */ ObjFunc func;
    /* 0x08 */ s32 flags;
    /* 0x0C */ s16 objPriority;
    /* 0x10 */ char *map_name;
} UIElement;

typedef struct BackgroundLayer {
    /* 0x00 */ u32 width;
    /* 0x04 */ u32 height;
    /* 0x08 */ s32 colorIndexed;
    /* 0x0C */ s32 flags;
    /* 0x10 */ u8 *raster;
    /* 0x14 */ u8 *palette;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 posY;
    /* 0x20 */ s32 parallaxX;
    /* 0x24 */ s32 parallaxY;
    /* 0x28 */ struct BackgroundLayer *next;
} BackgroundLayer; // size = 0x2C

typedef struct CombatState {
    /* 0x00 */ s16 minFrame;
    /* 0x02 */ s16 maxFrame;
    /* 0x04 */ s16 hitboxActiveStart;
    /* 0x06 */ s16 hitboxActiveEnd;
    /* 0x08 */ s16 animationId;
    /* 0x0A */ s16 hitStanding;
    /* 0x0C */ s16 hitCrouch;
    /* 0x0E */ s16 blockStanding;
    /* 0x10 */ s16 blockCrouch;
    /* 0x12 */ s16 hitAirborne;
    /* 0x14 */ s16 hitJuggle;
    /* 0x16 */ s16 hitBackStanding;
    /* 0x18 */ s16 hitBackCrouch;
    /* 0x1A */ s16 hitBackAirborne;
    /* 0x1C */ s16 hitMove10;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 damage;
    /* 0x22 */ s16 soundTableIndex;
    /* 0x24 */ s16 bodyHitboxStart;
    /* 0x26 */ s16 bodyHitboxEnd;
    /* 0x28 */ s16 projBarrage;
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 cutsceneId; // combat state where animationId is for camera, not for Player.
    /* 0x2E */ s16 custsceneDelay;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s32 flags;
} CombatState; // size = 0x38

typedef struct Behavior {
    /* 0x00 */ s32 newFlags;
    /* 0x04 */ ObjFunc animFunc;
    /* 0x08 */ ObjFunc actionFunc;
    /* 0x0C */ u8 (*transitionAllowedFunc)(Object *);
    /* 0x10 */ s32 preserveFlags;
} Behavior;

typedef struct PositionRingBuffer {
    /* 0x00 */ Vec4i positions[4];
    /* 0x40 */ s32 readIndex;
    /* 0x44 */ s32 writeIndex;
    /* 0x48 */ s32 bufferMask;
    /* 0x4C */ s32 count;
} PositionRingBuffer; // size = 0x50

typedef struct SplineInterpolator {
    /* 0x00 */ PositionRingBuffer inputBuffer;
    /* 0x50 */ PositionRingBuffer outputBuffer;
    /* 0x50 */ Matrix4f splineMatrix;
} SplineInterpolator; // size = 0xE0

typedef struct HitboxTrailSegment {
    /* 0x000 */ BatchInfo batchInfo;
    /* 0x058 */ Vtx vertices[10];
    /* 0x0F8 */ s32 lifetime;
    /* 0x0FC */ s32 vertexCount;
    /* 0x100 */ s32 triangleCount;
    /* 0x104 */ BatchTriangle *triangles;
    /* 0x108 */ u8 isBehind;
    /* 0x10C */ s32 unk_10C;
} HitboxTrailSegment; // size = 0x110

typedef struct PlayerHitbox {
    /* 0x0000 */ ModelInstance *modelInst;
    /* 0x0004 */ Matrix4f *boneMatrixA;
    /* 0x0008 */ Matrix4f *boneMatrixB;
    /* 0x000C */ SplineInterpolator splineB;
    /* 0x00EC */ SplineInterpolator splineA;
    /* 0x01CC */ s32 unk_1CC;
    /* 0x01D0 */ s32 segmentCount;
    /* 0x01D4 */ s32 unk_1D4;
    /* 0x01D8 */ HitboxTrailSegment segments[16];
    /* 0x12D8 */ BatchInfo unk_12D8[4];
    /* 0x1438 */ f32 boneBPosX;
    /* 0x143C */ f32 boneBPosY;
    /* 0x1440 */ f32 boneBPosZ;
    /* 0x1444 */ f32 boneAPosX;
    /* 0x1448 */ f32 boneAPosY;
    /* 0x144C */ f32 boneAPosZ;
    /* 0x1450 */ Vec4i *refPosition;
    /* 0x1454 */ ColorRGBA baseColor;
} PlayerHitbox; // size = 0x1458;

typedef struct HitboxBones {
    /* 0x000 */ u8 hasTorsoZone;
    /* 0x001 */ u8 hasGrabZone;
    /* 0x002 */ u8 hasHeadZone;
    /* 0x003 */ u8 hasTailZone;
    /* 0x004 */ u8 hasWingZone;
    /* 0x005 */ u8 hasLegZone;
    /* 0x006 */ u8 hasExtraZone;
    /* 0x007 */ u8 unk_07;
    /* 0x008 */ Vec4f *handPos;
    /* 0x00C */ Vec4f *footPos;
    /* 0x010 */ Vec4f *torsoPos;
    /* 0x014 */ Vec4f *thighPos;
    /* 0x018 */ Vec4f *headPos;
    /* 0x018 */ Vec4f *shinPos;
    /* 0x018 */ Vec4f *armPos;
    /* 0x018 */ Vec4f *extraBonePos;
    /* 0x018 */ Vec4f *rootPos;
    /* 0x02C */ s32 strikeRadius;
    /* 0x030 */ s32 comboRadius;
    /* 0x034 */ s32 unk_34;
    /* 0x038 */ Transform torsoTransform;
    /* 0x150 */ Transform grabTransform;
    /* 0x268 */ Transform wingTransform;
    /* 0x380 */ Transform legTransform;
    /* 0x498 */ Transform tailTransform;
} HitboxBones; // size = 0x5B0

typedef struct ProjectileShot {
    /* 0x00 */ u8 projectileId;
    /* 0x01 */ u8 frameIndex;
    /* 0x02 */ u8 unk_02;
} ProjectileShot; // size = 0x3

typedef struct ProjectileBarrage {
    /* 0x00 */ ProjectileShot unk_00[8];
} ProjectileBarrage; // size = 0x18

typedef struct AnimationSoundTriggers {
    /* 0x00 */ u8 soundId1;
    /* 0x01 */ u8 frame1;
    /* 0x02 */ u8 soundId2;
    /* 0x03 */ u8 frame2;
    /* 0x04 */ u8 soundId3;
    /* 0x05 */ u8 frame3;
    /* 0x06 */ u8 soundId4;
    /* 0x07 */ u8 frame4;
} AnimationSoundTriggers; // size = 0x8

typedef struct StateOverrideIndex {
    /* 0x00 */ s16 overrideTableOffset;
    /* 0x02 */ u16 numOverrides;
} StateOverrideIndex; // size = 0x4

typedef struct FrameTriggerOverride {
    /* 0x00 */ s16 stateIdOverride;
    /* 0x02 */ s16 frameIndex;
    /* 0x04 */ s16 stateId;
    /* 0x06 */ s16 transitionActionOverride;
} FrameTriggerOverride; // size = 0x8

typedef struct TransitionTiming {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 moveTimeout;
} TransitionTiming; // size = 0x10

typedef struct ProjectileDef {
    /* 0x00 */ s16 lifetime;
    /* 0x02 */ s16 boneId;
    /* 0x04 */ s32 originX;
    /* 0x08 */ s32 originY;
    /* 0x0C */ s32 originZ;
    /* 0x10 */ s32 velocityX;
    /* 0x14 */ s32 velocityY;
    /* 0x18 */ s32 velocityZ;
    /* 0x1C */ s16 spriteFrame;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 spriteIndex;
    /* 0x22 */ s16 modelIndex;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s16 flags;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ ColorRGBA lightColors[2];
} ProjectileDef; // size = 0x4C

typedef struct AiAction {
    /* 0x00 */ s16 actionIndex;
    /* 0x02 */ s16 difficultyMask;
    /* 0x04 */ s16 distanceMax;
    /* 0x06 */ s16 distanceMin;
    /* 0x08 */ u16 conditionFlags;
    /* 0x0A */ s16 unk_0A;
} AiAction; // size = 0xC

typedef struct AiState {
    /* 0x0000 */ AiAction *recentActions[3];
    /* 0x000C */ s16 *sequencePtr;
    /* 0x0010 */ u16 *actionPtr;
    /* 0x0014 */ s16 (*stateCallback)(struct Player *);
    /* 0x0018 */ s16 actionParam;
    /* 0x001A */ s16 unk_1A;
    /* 0x001C */ s32 conditionFlags;
    /* 0x0020 */ s32 actionFlags;
    /* 0x0024 */ s16 unk_24;
    /* 0x0026 */ s16 opponentHpAtAction;
    /* 0x0028 */ s32 unk_28;
    /* 0x002C */ s16 *tableRow;
    /* 0x00D8 */ s32 unk_D8;
    /* 0x00DC */ s16 hitCount;
    /* 0x00DE */ s16 delayCount;
    /* 0x00E0 */ char aiDebugName[160];
    /* 0x0180 */ s32 aiFlags;
} AiState;

typedef struct Player {
    /* 0x0000 */ Object *obj;
    /* 0x0004 */ s16 playerId;
    /* 0x0006 */ s16 characterId;
    /* 0x0008 */ ObjectTask *actionTask;
    /* 0x000C */ ObjectTask *animTask;
    /* 0x0010 */ ObjectTask *audioTask;
    /* 0x0014 */ ObjectTask *cameraTask;
    /* 0x0018 */ ObjectTask *unk_18;

    // tables from .db file
    /* 0x001C */ FrameTriggerOverride *frameTriggerOverrideTable;
    /* 0x0020 */ CombatState *combatStateTable;
    /* 0x0024 */ Behavior *behaviorTable;
    /* 0x0028 */ TransitionTiming *transitionTimingTable;
    /* 0x002C */ TransitionRule *transitionRuleTable;
    /* 0x0030 */ StateOverrideIndex *stateOverrideIndices;
    /* 0x0034 */ s16 *logicStateTable;
    /* 0x0038 */ s16 *moveToLogicStateMap;
    /* 0x003C */ s32 unk_3C;
    /* 0x0040 */ AnimationSoundTriggers *soundTable;
    /* 0x0044 */ u8 *unk_44;
    /* 0x0048 */ ProjectileDef *projectileTable;
    /* 0x004C */ ProjectileBarrage *barrageTable;
    /* 0x0050 */ u16 *aiActionTable;
    /* 0x0054 */ s16 *aiActionIndexMap;
    /* 0x0058 */ AiAction *aiCandidateTable;
    /* 0x005C */ s16 *aiSequenceTable;
    /* 0x0060 */ s16 *aiResponseTable;
    /* 0x0064 */ s16 *aiResponseIndexMap;
    /* 0x0068 */ u8 *unk_68;

    /* 0x006C */ s32 unk_6C;
    /* 0x0070 */ s16 unk_70;
    /* 0x0072 */ s16 unk_72;
    /* 0x0074 */ s16 transitionId;
    /* 0x0076 */ s16 lookupLogicTable;
    /* 0x0078 */ s16 currentLogicState;
    /* 0x007A */ s16 unk_7A;
    /* 0x007C */ s16 behaviorId;
    /* 0x007E */ s16 combatStateId;
    /* 0x0080 */ s32 flags;
    /* 0x0084 */ s32 unk_84;
    /* 0x0088 */ TransitionTiming *currentTiming;
    /* 0x008C */ s32 transitionTimeStamp;
    /* 0x0090 */ CombatState *combatState;
    /* 0x0094 */ s16 autoTransitionTimer;
    /* 0x0098 */ Behavior *behavior;
    /* 0x009C */ ProjectileBarrage *barrage;
    /* 0x00A0 */ TransitionRule *transition;
    /* 0x00A4 */ TransitionRule *previousTransition;
    /* 0x00A8 */ AiState aiState;
    /* 0x0184 */ u8 allowTransition;
    /* 0x0186 */ s16 previousBehaviorId;
    /* 0x0188 */ s16 previousCombatStateId;
    /* 0x018C */ s32 previousFlags;
    /* 0x0190 */ s32 unk_190;
    /* 0x0194 */ Object *projectileObj;
    /* 0x0198 */ HitboxBones hitboxBones;
    /* 0x0748 */ char unk_748[8];
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
    /* 0x0DC0 */ Model *effectSprites[3];
    /* 0x0DCC */ Model *effectModels[6];
    /* 0x0DE8 */ PlayerHitbox unk_DE8;
    /* 0x2240 */ PlayerHitbox unk_2240;
    /* 0x3698 */ PlayerHitbox unk_3698;
    /* 0x4AF0 */ PlayerHitbox unk_4AF0;
    /* 0x5F48 */ s16 hitCooldown;
    /* 0x5F4A */ u8 unk_5F4A;
    /* 0x5F4B */ u8 unk_5F4B;
    /* 0x5F4C */ s16 total_damage;
    /* 0x5F4E */ s16 damage;
} Player; // size = 0x5F50

typedef struct Player12 {
    /* 0x00 */ s16 characterId;
    /* 0x02 */ u8 isCpu; // probably wrong name
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 assetContext;
    /* 0x08 */ s16 roundsWon;
    /* 0x0A */ s16 consecutiveWins;
    /* 0x0C */ s16 initialHp;
    /* 0x0E */ u8 isDebug;
    /* 0x0F */ u8 unk_0F;
    /* 0x0F */ u8 isDummy;
    /* 0x0F */ u8 unk_11;
} Player12; // size = 0x12

typedef struct ModelNodeGroup {
    /* 0x00 */ s32 idInGroup[4];
    /* 0x10 */ s32 singleNode;
} ModelNodeGroup; // size = 0x14

typedef struct K2Def {
    /* 0x00 */ char *name;
    /* 0x04 */ ObjFunc taskFunc;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 objPriority;
    /* 0x0C */ ModelNodeGroup *unk_0C;
} K2Def;

typedef struct UnkK2Def {
    /* 0x00 */ K2Def base;
    /* 0x10 */ s32 flags;
    /* 0x14 */ s32 startingFrame;
} UnkK2Def;

typedef struct HudMessage {
    /* 0x00 */ char *name;
    /* 0x04 */ u16 duration;
    /* 0x06 */ u16 fadeRate;
    /* 0x08 */ ObjFunc fn_update;
    /* 0x0C */ s32 soundId;
} HudMessage;

typedef struct ModelRenderSettings {
    /* 0x00 */ Gfx combineMode;
    /* 0x08 */ s32 renderMode;
    /* 0x0C */ s32 triMask;
    /* 0x10 */ ColorRGBA primColor;
    /* 0x14 */ s32 flags;
} ModelRenderSettings;

typedef struct HitboxBoneSetup {
    /* 0x00 */ s32 boneId1;
    /* 0x04 */ s32 boneId2;
    /* 0x08 */ s32 boneId3;
    /* 0x0C */ s32 boneId4;
    /* 0x10 */ s32 boneId5;
    /* 0x14 */ s32 boneId6;
    /* 0x18 */ s32 boneId7;
    /* 0x1C */ s32 torsoParentBoneId;
    /* 0x20 */ s32 grabParentBoneId;
    /* 0x24 */ s32 strikeRadius;
    /* 0x28 */ s32 comboRadius;
    /* 0x2C */ Vec4i torsoOffset;
    /* 0x3C */ Vec4i grabOffset;
    /* 0x4C */ Vec4i wingOffset;
    /* 0x5C */ Vec4i legOffset;
    /* 0x6C */ s32 headBoneId2;
    /* 0x70 */ Vec4i tailOffset;
} HitboxBoneSetup;

typedef struct UnkTau {
    /* 0x00 */ HitboxBoneSetup *unk_00;
    /* 0x04 */ K2Def *unk_04;
    /* 0x08 */ ColorRGBA unk_08[2];
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
    /* 0x00 */ u32 red;
    /* 0x04 */ u32 green;
    /* 0x08 */ u32 blue;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x2C */ Object *object;
    /* 0x2C */ struct GlobalObjD *next;
    /* 0x30 */ struct GlobalObjD *previous;
} GlobalObjD; // size = 0x34

typedef struct UnkQwe {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ char *unk_04;
} UnkQwe; // size = 8

typedef struct UnkStruct800031FC {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} UnkStruct800031FC; // size = 0x08

typedef struct CharacterStats {
    /* 0x00 */ s16 wins;
    /* 0x02 */ s16 loses;
} CharacterStats; // size = 0x4

typedef s32 (*DISPCB)(void *);

#endif
