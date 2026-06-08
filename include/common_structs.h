#ifndef x_0a538080
#define x_0a538080

typedef struct x_625bda2c {
    f32 x, y, z;
} x_625bda2c;

typedef struct x_770ebaaf {
    s32 x, y, z;
} x_770ebaaf;

typedef struct x_88f11482 {
    s32 x, y, z, w;
} x_88f11482;

typedef struct x_acccb624 {
    s16 x, y, z;
} x_acccb624;

typedef struct x_61d6ae0d {
    u16 vi[3];
} x_61d6ae0d;

typedef struct x_2758cdab {
    s16 x, y, z, w;
} x_2758cdab;

typedef struct x_123b8fa2 {
    f32 x, y, z, w;
} x_123b8fa2;

typedef struct x_f9704fd6 {
    x_123b8fa2 x, y, z, w;
} x_f9704fd6;

typedef struct x_6751d717 {
    u8 r, g, b, a;
} x_6751d717;

struct Object;
struct Player;
typedef void (*x_09d6a3c8)(struct Object *);

typedef struct x_3e2f9cf1 {
    /* 0x00 */ s16 perspNorm;
    /* 0x02 */ char x_663d6aa0[6];
    /* 0x08 */ Gfx x_415ed9d6;
    /* 0x10 */ s32 x_cf1ea5d1[16];
    /* 0x50 */ Vp x_4e72a1b0;
    /* 0x60 */ Gfx *x_b97435d0;
} x_3e2f9cf1; // size = 0x64

typedef struct x_c32f9ed9 {
    /* 0x00 */ s32 x_09cf7a45;
    /* 0x04 */ s32 x_1256da71;
    /* 0x08 */ u8 x_4c5e05f8;
    /* 0x09 */ u8 x_ed66866b;
    /* 0x0A */ u8 x_8a54e96a;
    /* 0x0B */ u8 x_70b508ea;
    /* 0x0C */ Gfx *x_b7ba6d35;
    /* 0x10 */ Gfx otherMode;
} x_c32f9ed9; // size = 0x18

typedef struct x_c1cedf06 {
    /* 0x00 */ x_c32f9ed9 header;
    /* 0x18 */ Mtx transform;
} x_c1cedf06; // size = 0x58

typedef struct x_562d2a02 {
    /* 0x00 */ s8 x_091f00cd;
    /* 0x01 */ s8 x_83f352dd;
    /* 0x02 */ s8 x_6bf9e1d5;
    /* 0x03 */ s8 d;
} x_562d2a02; // size = 4

typedef struct x_320b5d80 {
    /* 0x00 */ x_3e2f9cf1 *context;
    /* 0x04 */ x_c1cedf06 *info;
    /* 0x08 */ Vtx *vertices;
    /* 0x0C */ x_562d2a02 *triangles;
} x_320b5d80; // size = 0x10

typedef struct x_ee01e8c6 {
    /* 0x0000 */ Mtx x_0f39faa7;
    /* 0x0040 */ char x_a484ea08[0x40];
    /* 0x0080 */ Gfx x_700a6ea1[0x800];
    /* 0x4080 */ Gfx x_5b2cc439[0x400];
    /* 0x6080 */ Gfx x_a4c192ba[0x400];
    /* 0x8080 */ x_320b5d80 x_79588dca[0x800];
    /* 0x10080 */ x_320b5d80 x_b8131490[0x200];
    /* 0x12080 */ u16 perspNorm;
    /* 0x12082 */ char x_fb9ff3ad[6];
} x_ee01e8c6; // size = 0x12088

typedef struct x_885b9582 {
    /* 0x00 */ x_6751d717 color;
    /* 0x04 */ s32 x_5962f1cd;
    /* 0x08 */ s32 x_f9f5d537;
    /* 0x0C */ s32 x_a18bc2e0;
} x_885b9582; // size = 0x10

typedef struct x_2bb4cf6f {
    /* 0x00 */ x_885b9582 lights[2];
} x_2bb4cf6f; // size = 0x20

typedef struct x_d0fba50a {
    /* 0x00 */ void (*x_bdfdc522)(void);
    /* 0x04 */ s16 x_1256da71;
    /* 0x08 */ s32 x_415ed9d6;
    /* 0x0C */ u8 x_b8173ab8;
    /* 0x0D */ u8 x_d863406f;
    /* 0x0E */ u8 x_f6c089c5;
    /* 0x0F */ u8 x_f74c4cfa;
    /* 0x10 */ u8 x_60c27ea9;
    /* 0x11 */ u8 x_ee25ce89;
    /* 0x12 */ u8 x_747e2503;
    /* 0x13 */ u8 x_876a16f1;
    /* 0x14 */ u16 x_d23de2ad;
    /* 0x16 */ u16 x_55739355;
    /* 0x18 */ x_2bb4cf6f *x_08b62e4f;
    /* 0x1C */ x_6751d717 x_389f2997;
} x_d0fba50a; // size = 0x20

typedef struct x_23580eef {
    /* 0x00 */ u16 buttons;
    /* 0x02 */ u16 x_33260da8;
    /* 0x04 */ u16 x_245d87f4;
    /* 0x06 */ u16 x_f3756179;
    /* 0x08 */ u8 x_c4397934;
    /* 0x09 */ u8 x_d93bcabf;
    /* 0x0A */ u8 enabled;
    /* 0x0B */ u8 x_12a7bd86;
    /* 0x0C */ u8 x_3fb684fe;
    /* 0x0D */ u8 x_40ccbb76;
} x_23580eef;

typedef struct x_37652cbd {
    /* 0x00 */ s32 x_af0aa1f8;
    /* 0x04 */ void *data;
    /* 0x08 */ s32 x_3b9aa142;
    /* 0x0C */ void (*x_3c30b5f3)(s32, s32, s32);
} x_37652cbd; // size = 0x10

typedef struct x_704d55d4 {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 end;
    /* 0x08 */ struct x_704d55d4 *next;
    /* 0x0C */ struct x_704d55d4 *previous;
    /* 0x10 */ s32 x_a9d4034d;
    /* 0x14 */ char padding[0x4];
} x_704d55d4; // size = 0x18

typedef struct x_3b6b80ec {
    /* 0x00 */ u32 width;
    /* 0x04 */ u32 height;
    /* 0x08 */ s32 format;
    /* 0x0C */ s32 x_3f981ea3;
    /* 0x10 */ u8 data[1];
} x_3b6b80ec;

typedef struct x_80d298c9 {
    /* 0x00 */ void *data;
    /* 0x04 */ void *x_4962fc73;
    /* 0x08 */ s32 x_d5b87ce9;
    /* 0x0C */ s32 x_89bf4f22;
    /* 0x10 */ char name[20];
    /* 0x24 */ s32 size;
    /* 0x28 */ u32 x_f33d7764;
    /* 0x2C */ u16 type;
    /* 0x2E */ s16 flags;
    /* 0x30 */ u16 context;
    /* 0x34 */ u8 *romAddr;
} x_80d298c9; // size = 0x38

typedef struct x_b57dc591 {
    /* 0x00 */ u8 *buffer;
    /* 0x04 */ s32 count;
    /* 0x08 */ u8 **elements;
    /* 0x0C */ s16 x_b8173ab8;
} x_b57dc591; // size >= 0xE

typedef struct Transform {
    /* 0x00 */ Mtx mtx[2];
    /* 0x80 */ struct Transform *x_171183e4;
    /* 0x84 */ struct Transform *x_fda6b96a;
    /* 0x88 */ struct Transform *x_e4712596;
    /* 0x8C */ s32 id;
    /* 0x90 */ s32 x_eb290249;
    /* 0x94 */ s32 x_834cdf4f;
    /* 0x98 */ x_f9704fd6 x_3fde9cd9;
    /* 0xD8 */ x_f9704fd6 x_0c1a9bdd;
} Transform; // size = 0x118

typedef struct x_36123519 {
    /* 0x00 */ s32 x_cb2a5131;
    /* 0x04 */ u16 x_5ab6332d;
    /* 0x06 */ u16 x_146f3cd6;
    /* 0x08 */ u16 x_9d9b2b65;
    /* 0x0A */ u16 x_8a54e96a;
    /* 0x0C */ x_3b6b80ec *texture;
} x_36123519; // size = 0x10

typedef struct x_c3c252eb {
    /* 0x00 */ s32 x_9d9b2b65;
    /* 0x04 */ s32 x_8a54e96a;
    /* 0x08 */ Vtx *vertices;
    /* 0x0C */ x_61d6ae0d *triangles;
    /* 0x10 */ char x_60c27ea9[0x8];
    /* 0x18 */ s32 x_5a8a4e18;
    /* 0x1C */ x_36123519 *x_063bc6a1;
} x_c3c252eb; // size = 0x20

typedef struct x_291fbc91 {
    /* 0x00 */ u8 x_1a2fc26d[4]; // '2KMD' or '@KMD' ??
    /* 0x04 */ s32 x_6dcce206;
    /* 0x08 */ s32 offsets[1];
} x_291fbc91;

typedef struct x_43bd08ed {
    /* 0x00 */ s32 x_e4712596;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 z;
} x_43bd08ed; // size = 0x10

typedef struct x_13162abc {
    /* 0x00 */ u32 x_6dcce206;
    /* 0x04 */ x_c3c252eb *x_45978ecb;
    /* 0x08 */ x_43bd08ed *x_e7962160;
    /* 0x0C */ char x_b8173ab8[0xA0];
    /* 0xAC */ s32 x_7d9f29c8;
    /* 0xB0 */ s32 x_8d36349d;
    /* 0xB4 */ s32 x_2caca85b;
    /* 0xB8 */ x_291fbc91 *header;
    /* 0xBC */ char x_6362fc9e[4];
    /* 0xC0 */ u8 *x_1dbd7f4a;
    /* 0xC4 */ u8 *x_d38574ae;
    /* 0xC8 */ u8 x_14bc93c1;
    /* 0xCC */ x_36123519 x_8e7d60e8[0];
} x_13162abc; // size = 0xCC

typedef struct x_76f6b32b {
    /* 0x00 */ s32 x_9d9b2b65;
    /* 0x04 */ s32 x_8a54e96a;
    /* 0x08 */ s32 x_009cb3fe;
    /* 0x0C */ s32 x_3a1206c9;
    /* 0x10 */ s32 x_9cc3894f;
    /* 0x14 */ s32 unused;
} x_76f6b32b;

typedef struct x_257b53b4 {
    /* 0x00 */ u8 x_af0aa1f8;
    /* 0x04 */ s32 group[4];
    /* 0x14 */ x_770ebaaf x_b6669964;
    /* 0x20 */ s32 x_0c9f73ee;
    /* 0x24 */ u32 x_ceaf196d;
    /* 0x28 */ x_320b5d80 *transforms[4]; // union Batch or Mtx
    /* 0x38 */ s32 x_c246f31f[4];
    /* 0x48 */ Gfx *x_1aae351f[4];
} x_257b53b4; // size = 0x58

typedef struct x_81d7569b {
    /* 0x00 */ u8 x_fb9d51cc;
    /* 0x01 */ u8 x_c7f5b137;
    /* 0x02 */ u8 x_a546469c;
    /* 0x03 */ u8 x_656233ce;
    /* 0x04 */ x_6751d717 x_b21a405e[16];
    /* 0x44 */ s16 x_d0dadb00[16];
} x_81d7569b; // size = 0x64;

typedef union x_4aeb64bb {
    s32 w;
    struct {
        u8 b0;
        u8 b1;
        u8 b2;
        u8 b3;
    };
} x_4aeb64bb;

typedef struct x_a05f18ad {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    x_4aeb64bb entries[1];
} x_a05f18ad;

typedef struct Model {
    /* 0x000 */ s32 x_af0aa1f8;
    /* 0x004 */ x_13162abc *x_3bfb7219;
    /* 0x008 */ char x_415ed9d6[0x128 - 8];
    /* 0x128 */ s32 x_6dcce206;
    /* 0x12C */ char x_3a05f974[0x148 - 0x12C];
    /* 0x148 */ x_a05f18ad **x_50771dcd;
    /* 0x14C */ s32 x_c4306fe5;
    /* 0x150 */ x_43bd08ed *x_e7962160;
    /* 0x154 */ union {
        x_320b5d80 *x_467629e6[28];
        Gfx *x_bde24317[28 * 2];
    };
    /* 0x234 */ u16 x_cb6af9da;
    /* 0x236 */ s16 x_f0d3baa5;
    /* 0x238 */ s32 x_c246f31f[28];
    /* 0x2A8 */ x_c1cedf06 *x_d6eac39a[28];
    /* 0x318 */ u8 x_1d24de6a;
    /* 0x319 */ char x_a7952e5f[3];
    /* 0x31C */ x_257b53b4 *x_761a0268;
    /* 0x320 */ u8 x_5e8d7fdd;
    /* 0x321 */ u8 x_70d4cd21;
    /* 0x322 */ u8 x_ca98492d;
    /* 0x323 */ u8 x_0222e016;
    /* 0x324 */ x_81d7569b *x_5b386c41[28];
    /* 0x394 */ u16 x_810b9a68[28];
    /* 0x3CC */ s32 x_8ac8f967;
} Model; // size = 0x3D0

typedef struct x_82e80914 {
    /* 0x000 */ Model model;
    /* 0x3D0 */ char x_d19236e7[0xA64 - 0x3D0];
    /* 0xA64 */ u16 x_2640873a;
} x_82e80914; // szie = 0xA68

typedef struct x_f752bb53 {
    /* 0x00 */ s32 x_9dca29cd;
    /* 0x04 */ x_257b53b4 *x_164cf1ca;
    /* 0x08 */ x_c1cedf06 *x_415ed9d6[4];
    /* 0x18 */ struct x_f752bb53 *next;
    /* 0x1C */ s32 flags;
} x_f752bb53; // size = 0x20

typedef struct x_6fcfcf46 {
    /* 0x0000 */ s16 x_6dcce206;
    /* 0x0002 */ x_acccb624 velocity;
    /* 0x0008 */ x_acccb624 x_6786034d;
    /* 0x000E */ char x_f9a976e3[2];
    /* 0x0010 */ Transform x_abd7b3c4;
    /* 0x0128 */ Transform *transforms;
    /* 0x012C */ x_a05f18ad **x_50771dcd;
    /* 0x0130 */ s16 x_85b6be0b;
    /* 0x0132 */ s16 x_766c2c4d;
    /* 0x0134 */ x_2758cdab x_b3db7eeb[30];
    /* 0x0224 */ x_88f11482 x_d6354d00[30];
    /* 0x0404 */ x_88f11482 x_5d0e77f6[30];
    /* 0x05E4 */ u8 x_07bd45a3[30];
    /* 0x0604 */ x_257b53b4 *x_9a3e80ff;
    /* 0x0608 */ x_f752bb53 x_61b49b7b[30];
    /* 0x09C8 */ s32 x_88c9004e;
    /* 0x09CC */ x_acccb624 x_08d6ba0b;
    /* 0x09D8 */ x_88f11482 x_6689336b;
    /* 0x09E4 */ x_88f11482 x_9cfd7bb4;
    /* 0x09F4 */ u8 x_898495c5;
    /* 0x09F8 */ x_88f11482 x_4e599cb3;
    /* 0x0A08 */ s32 x_8e601526;
    /* 0x0A0C */ s16 x_ee205ef9;
    /* 0x0A0E */ s16 x_2f4c4ce1;
    /* 0x0A10 */ s32 x_13ea4bdf;
    /* 0x0A14 */ x_4aeb64bb *x_924433d2;
    /* 0x0A18 */ s32 x_02f44f77;
    /* 0x0A1C */ s16 x_3aefae96;
    /* 0x0A1E */ s16 x_83b02ec3;
    /* 0x0A20 */ s16 x_713417ac;
    /* 0x0A22 */ char x_adae4ba1[2];
    /* 0x0A24 */ x_82e80914 *x_305a60f8;
    /* 0x0A28 */ Model *model;
    /* 0x0A2C */ s32 x_1d0c1660;
    /* 0x0A30 */ x_f752bb53 x_da66be9b;
    /* 0x0A50 */ x_257b53b4 x_8b36595a;
    /* 0x0AA8 */ x_43bd08ed *x_0094fc88;
    /* 0x0AAC */ char x_54b30e37[4];
    /* 0x0AB0 */ x_c1cedf06 x_78526b81[60];
    /* 0x1F50 */ u8 x_8f151cd3[30];
    /* 0x1F6E */ u8 x_c8099ad6[30];
    /* 0x1F8C */ char x_609cda18[4];
} x_6fcfcf46; // size = 0x1F90

typedef struct x_425d6ed3 {
    /* 0x00 */ s32 x_a2264414;
    /* 0x04 */ u32 x_b88b3756;
    /* 0x08 */ u32 rightS;
    /* 0x0C */ s32 x_f2864eba;
    /* 0x10 */ s32 x_e7f1952a;
    /* 0x14 */ s32 x_67347149;
} x_425d6ed3; // size ?

typedef struct x_7cc7ad58 {
    /* 0x00 */ s32 x_fa21689f;
    /* 0x04 */ x_425d6ed3 *parts;
    /* 0x08 */ s32 x_51d6cf57;
    /* 0x0C */ x_3b6b80ec *texture;
} x_7cc7ad58; // size = 0x10

typedef struct x_8ab35fe5 {
    /* 0x00 */ s32 size;
    /* 0x04 */ u32 x_5b30c492;
    /* 0x08 */ char x_6fb24ac9[4][16];
    /* 0x48 */ x_7cc7ad58 *x_a34b89cc;
} x_8ab35fe5;

typedef struct Object {
    /* 0x000 */ x_88f11482 x_8da078cc;
    /* 0x010 */ x_88f11482 velocity;
    /* 0x020 */ x_88f11482 pos;
    /* 0x030 */ char x_1579d4fa[0x40 - 0x30];
    /* 0x040 */ x_88f11482 x_d7f6e5d2;
    /* 0x050 */ x_2758cdab x_224610f1;
    /* 0x058 */ s32 x_860b579a;
    /* 0x05C */ s32 x_2fa0bbed;
    /* 0x060 */ s32 x_3e400065;
    /* 0x064 */ char x_46008031[0x70 - 0x64];
    /* 0x070 */ s16 x_9200c538;
    /* 0x072 */ s16 x_9086a9ee;
    /* 0x074 */ s16 priority;
    /* 0x076 */ s16 x_61f772e7;
    /* 0x078 */ s16 x_1b0e7aa2;
    /* 0x07A */ s16 x_e4466eca;
    /* 0x07C */ s16 x_b1e624ba;
    /* 0x07E */ s16 x_89c109c9;
    /* 0x080 */ s32 flags;
    /* 0x084 */ s16 x_5fcb1654;
    /* 0x086 */ s16 x_2b06a023;
    /* 0x088 */ x_6751d717 color;
    /* 0x08C */ s16 x_f9866d50;
    /* 0x08E */ char x_029e6d39[2];
    /* 0x090 */ union {
        s32 x_0f4167b4[13];
        struct Object *x_e2f64c57[13];
    };
    /* 0x0C4 */ x_8ab35fe5 *x_904eaf67;
    /* 0x0C8 */ x_6fcfcf46 *x_20d20338;
    /* 0x0CC */ char x_34dbb1c7[4];
    /* 0x0D0 */ Transform transform;
    /* 0x1E8 */ void (*x_450fdcd0)(struct Object *, struct Object *);
    /* 0x1EC */ x_09d6a3c8 x_0232396f;
    /* 0x1F0 */ struct x_41a0e1e6 *x_d178c88f;
    /* 0x1F4 */ struct x_41a0e1e6 *x_64946db0;
    /* 0x1F8 */ s16 x_8f6ab396;
    /* 0x1FA */ s16 x_9112b8b9;
    /* 0x1FC */ s32 x_de73d1d5;
    /* 0x200 */ x_6751d717 x_47e6a04c;
    /* 0x204 */ x_6751d717 x_da940449;
    /* 0x208 */ struct x_a8b4b5ce *light;
    /* 0x20C */ char x_79805729[4];
    /* 0x210 */ struct Object *x_2d5f3fbd;
    /* 0x214 */ struct Object *x_d0268c0d;
} Object; // size = 0x218

typedef struct x_c305712a {
    /* 0x00 */ u32 flags;
    /* 0x04 */ x_09d6a3c8 x_f6382727;
    /* 0x08 */ s16 x_c7f843c2;
} x_c305712a; // size = 0xC

typedef struct x_e0b9a726 {
    /* 0x00 */ s16 x_4f311d1d;
    /* 0x02 */ u16 x_5512bb4f;
    /* 0x04 */ u16 flags;
    /* 0x06 */ u16 x_8b47d6ce;
    /* 0x08 */ s16 x_a4b33e43;
    /* 0x0A */ s16 x_86977b23;
    /* 0x0C */ u16 x_b2075a91;
    /* 0x0E */ u8 x_acda7e96[11];
    /* 0x19 */ u8 x_18eb6c3d;
    /* 0x1A */ char x_c250cfce[2];
} x_e0b9a726; // size = 0x1C

typedef struct x_41a0e1e6 {
    /* 0x00 */ u32 flags;
    /* 0x04 */ x_09d6a3c8 x_f6382727;
    /* 0x08 */ s32 params[6];
    /* 0x20 */ u16 x_116c9ff3;
    /* 0x24 */ x_c305712a stack[8];
    /* 0x84 */ s16 x_c7f843c2;
    /* 0x86 */ s16 x_8a242a5a;
    /* 0x88 */ s16 id;
    /* 0x8A */ char x_5f7c7171[6];
    /* 0x90 */ x_c305712a x_bda3dc45;
    /* 0x9C */ struct x_41a0e1e6 *next;
} x_41a0e1e6; // size = 0xA0

typedef struct x_f0d7e70f {
    /* 0x00 */ s16 x_f85f1359;
    /* 0x04 */ x_09d6a3c8 x_f6382727;
    /* 0x08 */ s32 flags;
    /* 0x0C */ s16 x_95ee18a8;
    /* 0x10 */ char *x_6870fa4a;
} x_f0d7e70f;

typedef struct x_4a7d6dd4 {
    /* 0x00 */ u32 width;
    /* 0x04 */ u32 height;
    /* 0x08 */ s32 x_519855f8;
    /* 0x0C */ s32 flags;
    /* 0x10 */ u8 *x_925c481a;
    /* 0x14 */ u8 *palette;
    /* 0x18 */ s32 x_08b62e4f;
    /* 0x1C */ s32 x_64a8566c;
    /* 0x20 */ s32 x_afebb108;
    /* 0x24 */ s32 x_86f38745;
    /* 0x28 */ struct x_4a7d6dd4 *next;
} x_4a7d6dd4; // size = 0x2C

typedef struct x_388306ba {
    /* 0x00 */ s16 x_887b6be9;
    /* 0x02 */ s16 x_bab9966d;
    /* 0x04 */ s16 x_c53ac2df;
    /* 0x06 */ s16 x_fedecf5c;
    /* 0x08 */ s16 x_43d35340;
    /* 0x0A */ s16 x_237b8772;
    /* 0x0C */ s16 x_71357e64;
    /* 0x0E */ s16 x_40be83c8;
    /* 0x10 */ s16 x_b033c680;
    /* 0x12 */ s16 x_d3699524;
    /* 0x14 */ s16 x_2955cef8;
    /* 0x16 */ s16 x_c33946bb;
    /* 0x18 */ s16 x_cdc30d39;
    /* 0x1A */ s16 x_dc90c3b6;
    /* 0x1C */ s16 x_6290ef5a;
    /* 0x1E */ s16 x_fbb09ed1;
    /* 0x20 */ s16 x_6f5a5c61;
    /* 0x22 */ s16 x_9e993e2f;
    /* 0x24 */ s16 x_946f41d3;
    /* 0x26 */ s16 x_79b8e870;
    /* 0x28 */ s16 x_fc1da284;
    /* 0x2A */ s16 x_baa31b64;
    /* 0x2C */ s16 x_016911c1; // combat state where animationId is for camera, not for Player.
    /* 0x2E */ s16 x_71e17346;
    /* 0x30 */ s16 x_49e4c93e;
    /* 0x32 */ s16 x_c3bc2262;
    /* 0x34 */ s32 flags;
} x_388306ba; // size = 0x38

typedef struct x_edf8d3f1 {
    /* 0x00 */ s32 x_bb8c769c;
    /* 0x04 */ x_09d6a3c8 x_9ed41890;
    /* 0x08 */ x_09d6a3c8 x_9ac0a1c4;
    /* 0x0C */ u8 (*x_9cba3528)(Object *);
    /* 0x10 */ s32 x_8dd1ed1c;
} x_edf8d3f1;

typedef struct x_c2fa3c06 {
    /* 0x00 */ x_88f11482 x_f50871d1[4];
    /* 0x40 */ s32 x_5e0afed5;
    /* 0x44 */ s32 x_e7f3bb4b;
    /* 0x48 */ s32 x_e8bea4b4;
    /* 0x4C */ s32 count;
} x_c2fa3c06; // size = 0x50

typedef struct x_12f9ebc0 {
    /* 0x00 */ x_c2fa3c06 x_646d43df;
    /* 0x50 */ x_c2fa3c06 x_48fb4701;
    /* 0x50 */ x_f9704fd6 x_1996624f;
} x_12f9ebc0; // size = 0xE0

typedef struct x_90f055ea {
    /* 0x000 */ x_c1cedf06 x_3ab7202f;
    /* 0x058 */ Vtx vertices[10];
    /* 0x0F8 */ s32 x_6f6a6d94;
    /* 0x0FC */ s32 x_723971cf;
    /* 0x100 */ s32 x_a1256713;
    /* 0x104 */ x_562d2a02 *triangles;
    /* 0x108 */ u8 x_24fe8ee6;
    /* 0x10C */ s32 x_db246239;
} x_90f055ea; // size = 0x110

typedef struct x_056d4f07 {
    /* 0x0000 */ x_6fcfcf46 *x_c657ede8;
    /* 0x0004 */ x_f9704fd6 *x_89f63109;
    /* 0x0008 */ x_f9704fd6 *x_007a9250;
    /* 0x000C */ x_12f9ebc0 x_1091fcc6;
    /* 0x00EC */ x_12f9ebc0 x_60635a2d;
    /* 0x01CC */ s32 x_30459015;
    /* 0x01D0 */ s32 x_b1f57d55;
    /* 0x01D4 */ s32 x_908a6960;
    /* 0x01D8 */ x_90f055ea x_08fddbc8[16];
    /* 0x12D8 */ x_c1cedf06 x_ad2af5d9[4];
    /* 0x1438 */ f32 x_c08ab25c;
    /* 0x143C */ f32 x_9810c807;
    /* 0x1440 */ f32 x_b8fd00e2;
    /* 0x1444 */ f32 x_bc587679;
    /* 0x1448 */ f32 x_fc05a02f;
    /* 0x144C */ f32 x_1ba29927;
    /* 0x1450 */ x_88f11482 *x_36bb3f9b;
    /* 0x1454 */ x_6751d717 x_57e44061;
} x_056d4f07; // size = 0x1458;

typedef struct x_998ccc48 {
    /* 0x000 */ u8 x_a1c57a3b;
    /* 0x001 */ u8 x_c01445c3;
    /* 0x002 */ u8 x_b7aa4e8a;
    /* 0x003 */ u8 x_d8ede1db;
    /* 0x004 */ u8 x_6216b7a1;
    /* 0x005 */ u8 x_22014d8c;
    /* 0x006 */ u8 x_a2414217;
    /* 0x007 */ u8 x_1a83b5ae;
    /* 0x008 */ x_123b8fa2 *x_b7552092;
    /* 0x00C */ x_123b8fa2 *x_3b24b185;
    /* 0x010 */ x_123b8fa2 *x_55f532bb;
    /* 0x014 */ x_123b8fa2 *x_6e7f4fd8;
    /* 0x018 */ x_123b8fa2 *x_1b148bc2;
    /* 0x018 */ x_123b8fa2 *x_4c227952;
    /* 0x018 */ x_123b8fa2 *x_ef41f475;
    /* 0x018 */ x_123b8fa2 *x_9829da43;
    /* 0x018 */ x_123b8fa2 *x_82e589d5;
    /* 0x02C */ s32 x_62706fff;
    /* 0x030 */ s32 x_38ae036c;
    /* 0x034 */ s32 x_8cd129ed;
    /* 0x038 */ Transform x_0548cec6;
    /* 0x150 */ Transform x_cc2c17a6;
    /* 0x268 */ Transform x_20d81af7;
    /* 0x380 */ Transform x_45875993;
    /* 0x498 */ Transform x_6057c67e;
} x_998ccc48; // size = 0x5B0

typedef struct x_b842de24 {
    /* 0x00 */ u8 x_d7ce6b8d;
    /* 0x01 */ u8 x_5fcb1654;
    /* 0x02 */ u8 x_cd679b4c;
} x_b842de24; // size = 0x3

typedef struct x_76bab60d {
    /* 0x00 */ x_b842de24 x_af0aa1f8[8];
} x_76bab60d; // size = 0x18

typedef struct x_c8184673 {
    /* 0x00 */ u8 x_6c6074c0;
    /* 0x01 */ u8 x_70149fad;
    /* 0x02 */ u8 x_a1942e25;
    /* 0x03 */ u8 x_bf6039d8;
    /* 0x04 */ u8 x_94e185f0;
    /* 0x05 */ u8 x_8c856b1f;
    /* 0x06 */ u8 x_155a7631;
    /* 0x07 */ u8 x_851b801d;
} x_c8184673; // size = 0x8

typedef struct x_5d25c43c {
    /* 0x00 */ s16 x_7f6512f9;
    /* 0x02 */ u16 x_7e85e5f1;
} x_5d25c43c; // size = 0x4

typedef struct x_58fcf07a {
    /* 0x00 */ s16 x_300600ea;
    /* 0x02 */ s16 x_5fcb1654;
    /* 0x04 */ s16 x_9d8a9022;
    /* 0x06 */ s16 x_7028ad92;
} x_58fcf07a; // size = 0x8

typedef struct x_89b0c74e {
    /* 0x00 */ s16 x_af0aa1f8;
    /* 0x02 */ s16 x_cd679b4c;
    /* 0x04 */ s16 x_1256da71;
    /* 0x06 */ s16 x_8b47d6ce;
    /* 0x08 */ s16 x_415ed9d6;
    /* 0x0A */ s16 x_4bc5d40d;
    /* 0x0C */ s16 x_b8173ab8;
    /* 0x0E */ s16 x_6785159a;
} x_89b0c74e; // size = 0x10

typedef struct x_6fc0b62f {
    /* 0x00 */ s16 x_6f6a6d94;
    /* 0x02 */ s16 x_32485e13;
    /* 0x04 */ s32 x_1422e8f9;
    /* 0x08 */ s32 x_6f7546e4;
    /* 0x0C */ s32 x_95b3e972;
    /* 0x10 */ s32 x_52756e64;
    /* 0x14 */ s32 x_4615af37;
    /* 0x18 */ s32 x_2c9fb9af;
    /* 0x1C */ s16 x_bc085e56;
    /* 0x1E */ s16 x_fbb09ed1;
    /* 0x20 */ s16 x_e2f3aa2a;
    /* 0x22 */ s16 x_1d88fb18;
    /* 0x24 */ s32 x_817784f2;
    /* 0x28 */ s32 x_952b6fea;
    /* 0x2C */ s16 flags;
    /* 0x2E */ s16 x_f494f157;
    /* 0x30 */ s16 x_49e4c93e;
    /* 0x32 */ s16 x_c3bc2262;
    /* 0x34 */ s16 x_8cd129ed;
    /* 0x36 */ s16 x_1adc8f8a;
    /* 0x38 */ s16 x_251abb64;
    /* 0x3A */ s16 x_67a74844;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 x_a484ea08;
    /* 0x42 */ s16 x_350c85ef;
    /* 0x44 */ x_6751d717 x_c3357d6a[2];
} x_6fc0b62f; // size = 0x4C

typedef struct x_eea787ea {
    /* 0x00 */ s16 x_d3e51cdb;
    /* 0x02 */ s16 x_1e623531;
    /* 0x04 */ s16 x_1350cb4d;
    /* 0x06 */ s16 x_62addb22;
    /* 0x08 */ u16 x_c3afc384;
    /* 0x0A */ s16 x_4bc5d40d;
} x_eea787ea; // size = 0xC

typedef struct x_dff9d873 {
    /* 0x00 */ s16 x_86deb4e9; // index into callback table (-1 = none)
    /* 0x02 */ s16 x_5a6554ba;
    /* 0x04 */ u16 x_c3afc384;
    /* 0x06 */ s16 x_0678afb9;
    /* 0x08 */ s16 x_76cf2d04[]; // MOVE_ID list, -1 terminated
} x_dff9d873;

typedef struct x_ccb3bba0 {
    /* 0x00 */ s16 flags;
    /* 0x02 */ s16 x_cd679b4c;
    /* 0x04 */ s16 x_1256da71;
    /* 0x06 */ s16 x_b129ae42;
    /* 0x08 */ s16 x_ba159dbf[]; // -1 terminated, indices into aiCandidateTable (AiTactic[])
} x_ccb3bba0;

typedef struct x_1e5e42da {
    /* 0x0000 */ x_eea787ea *x_14906c66[3];
    /* 0x000C */ s16 *x_9daba480;
    /* 0x0010 */ u16 *x_76cf2d04;
    /* 0x0014 */ s16 (*x_ca75ac5d)(struct Player *);
    /* 0x0018 */ s16 x_5a6554ba;
    /* 0x001A */ s16 x_d8cea3af;
    /* 0x001C */ s32 x_5c398490;
    /* 0x0020 */ s32 x_d098505c;
    /* 0x0024 */ s16 x_817784f2;
    /* 0x0026 */ s16 x_ef647f03;
    /* 0x0028 */ s32 x_952b6fea;
    /* 0x002C */ x_ccb3bba0 *x_011116d7;
    /* 0x00D8 */ s32 x_4b76bb24;
    /* 0x00DC */ s16 x_60227f92;
    /* 0x00DE */ s16 x_4390a1c3;
    /* 0x00E0 */ char x_599a5202[160];
    /* 0x0180 */ s32 x_b2c79d6e;
} x_1e5e42da;

typedef struct Player {
    /* 0x0000 */ Object *obj;
    /* 0x0004 */ s16 x_30bbe547;
    /* 0x0006 */ s16 x_eb1fe45b;
    /* 0x0008 */ x_41a0e1e6 *x_147ade82;
    /* 0x000C */ x_41a0e1e6 *x_b9252303;
    /* 0x0010 */ x_41a0e1e6 *x_50a9ff14;
    /* 0x0014 */ x_41a0e1e6 *x_cdb23d89;
    /* 0x0018 */ x_41a0e1e6 *x_08b62e4f;

    // tables from .db file
    /* 0x001C */ x_58fcf07a *x_ae3aa7af;
    /* 0x0020 */ x_388306ba *x_68a6b5cd;
    /* 0x0024 */ x_edf8d3f1 *x_f003fafb;
    /* 0x0028 */ x_89b0c74e *x_cfd37298;
    /* 0x002C */ x_e0b9a726 *x_1af5b64c;
    /* 0x0030 */ x_5d25c43c *x_a1696a6b;
    /* 0x0034 */ s16 *x_b8b27276;
    /* 0x0038 */ s16 *x_59f97427;
    /* 0x003C */ s32 unk_3C;
    /* 0x0040 */ x_c8184673 *x_429c730a;
    /* 0x0044 */ u8 *x_8b00beac;
    /* 0x0048 */ x_6fc0b62f *x_e4ca14d3;
    /* 0x004C */ x_76bab60d *x_38b3091d;
    /* 0x0050 */ u16 *x_994b73a7;
    /* 0x0054 */ s16 *x_4ec7bbf8;
    /* 0x0058 */ x_eea787ea *x_ad9d3e42;
    /* 0x005C */ s16 *x_d908b580;
    /* 0x0060 */ s16 *x_0bc74042;
    /* 0x0064 */ s16 *x_78242925;
    /* 0x0068 */ u8 *x_c42e3970;

    /* 0x006C */ s32 x_ea8ec382;
    /* 0x0070 */ s16 x_8d3b87a9;
    /* 0x0072 */ s16 x_82df8dbb;
    /* 0x0074 */ s16 x_6cbdf667;
    /* 0x0076 */ s16 x_0a8e33d7;
    /* 0x0078 */ s16 x_a6423339;
    /* 0x007A */ s16 x_6e6f54b6;
    /* 0x007C */ s16 x_a4b33e43;
    /* 0x007E */ s16 x_cd14c741;
    /* 0x0080 */ s32 flags;
    /* 0x0084 */ s32 x_04397658;
    /* 0x0088 */ x_89b0c74e *x_b544b169;
    /* 0x008C */ s32 x_965e5473;
    /* 0x0090 */ x_388306ba *x_7f68c36b;
    /* 0x0094 */ s16 x_448f0851;
    /* 0x0098 */ x_edf8d3f1 *x_08bf2418;
    /* 0x009C */ x_76bab60d *x_0b88f58e;
    /* 0x00A0 */ x_e0b9a726 *transition;
    /* 0x00A4 */ x_e0b9a726 *x_eaf4e410;
    /* 0x00A8 */ x_1e5e42da x_81570fde;
    /* 0x0184 */ u8 x_cadf184a;
    /* 0x0186 */ s16 x_81828f2f;
    /* 0x0188 */ s16 x_45f71fd9;
    /* 0x018C */ s32 x_1a6e9e97;
    /* 0x0190 */ s32 x_ab5262a6;
    /* 0x0194 */ Object *x_66350762;
    /* 0x0198 */ x_998ccc48 x_5c5b1d93;
    /* 0x0748 */ char x_38c2b102[8];
    /* 0x0750 */ Transform x_a4d7c80d;
    /* 0x0868 */ Transform x_022dff72;
    /* 0x0980 */ char x_b920f376[40];
    /* 0x09A8 */ s32 x_b10c1d88;
    /* 0x09AC */ s32 x_bfd481b9;
    /* 0x09B0 */ s32 x_71560fc1;
    /* 0x09B4 */ s32 x_be67e057;
    /* 0x09B8 */ char x_3b574867[1024];
    /* 0x0DB8 */ s16 x_81ca4eb2;
    /* 0x0DBA */ s16 x_261980db;
    /* 0x0DBC */ s16 x_101ebc50;
    /* 0x0DBE */ s16 x_0b34e01a;
    /* 0x0DC0 */ Model *x_a1dcdb62[3];
    /* 0x0DCC */ Model *x_dd32bc14[6];
    /* 0x0DE8 */ x_056d4f07 x_d8a19723;
    /* 0x2240 */ x_056d4f07 x_238ba16f;
    /* 0x3698 */ x_056d4f07 x_29c9094f;
    /* 0x4AF0 */ x_056d4f07 x_a241ea2a;
    /* 0x5F48 */ s16 x_381817ae;
    /* 0x5F4A */ u8 x_8bc5a2ac;
    /* 0x5F4B */ u8 x_15b59b63;
    /* 0x5F4C */ s16 x_95a50856;
    /* 0x5F4E */ s16 x_6f5a5c61;
} Player; // size = 0x5F50

typedef struct x_7bac7836 {
    /* 0x00 */ s16 x_eb1fe45b;
    /* 0x02 */ u8 x_03604d94; // probably wrong name
    /* 0x04 */ u16 x_cc57155e;
    /* 0x06 */ u8 x_fb21ca8c;
    /* 0x08 */ s16 x_b2b764b3;
    /* 0x0A */ s16 x_7d8e7a6f;
    /* 0x0C */ s16 x_c35c64af;
    /* 0x0E */ u8 x_6128220f;
    /* 0x0F */ u8 x_8a8d66c9;
    /* 0x0F */ u8 x_178eafa6;
    /* 0x0F */ u8 x_ee25ce89;
} x_7bac7836; // size = 0x12

typedef struct x_40f23fab {
    /* 0x00 */ s32 x_67091bea[4];
    /* 0x10 */ s32 x_0c9f73ee;
} x_40f23fab; // size = 0x14

typedef struct x_aece7675 {
    /* 0x00 */ char *name;
    /* 0x04 */ x_09d6a3c8 x_08ae3bb4;
    /* 0x08 */ s16 x_415ed9d6;
    /* 0x0A */ s16 x_95ee18a8;
    /* 0x0C */ x_40f23fab *x_b8173ab8;
} x_aece7675;

typedef struct x_8b39d614 {
    /* 0x00 */ x_aece7675 base;
    /* 0x10 */ s32 flags;
    /* 0x14 */ s32 x_14033586;
} x_8b39d614;

typedef struct x_3da8fdd8 {
    /* 0x00 */ char *name;
    /* 0x04 */ u16 duration;
    /* 0x06 */ u16 x_ba814dc8;
    /* 0x08 */ x_09d6a3c8 x_5cb18fd3;
    /* 0x0C */ s32 x_1dc13257;
} x_3da8fdd8;

typedef struct x_d8e0705d {
    /* 0x00 */ Gfx x_25501148;
    /* 0x08 */ s32 x_e5c5ede4;
    /* 0x0C */ s32 x_09cf7a45;
    /* 0x10 */ x_6751d717 primColor;
    /* 0x14 */ s32 flags;
} x_d8e0705d;

typedef struct x_87049dce {
    /* 0x00 */ s32 x_283c5e35;
    /* 0x04 */ s32 x_41b5ccd6;
    /* 0x08 */ s32 x_8680658c;
    /* 0x0C */ s32 x_cc509e17;
    /* 0x10 */ s32 x_df4167c9;
    /* 0x14 */ s32 x_35b6f6e0;
    /* 0x18 */ s32 x_71801879;
    /* 0x1C */ s32 x_1ffa33d9;
    /* 0x20 */ s32 x_e888d5ae;
    /* 0x24 */ s32 x_62706fff;
    /* 0x28 */ s32 x_38ae036c;
    /* 0x2C */ x_88f11482 x_f95a218e;
    /* 0x3C */ x_88f11482 x_3bf3046a;
    /* 0x4C */ x_88f11482 x_495dd749;
    /* 0x5C */ x_88f11482 x_150bdca9;
    /* 0x6C */ s32 x_baea923a;
    /* 0x70 */ x_88f11482 x_8f7663b3;
} x_87049dce;

typedef struct x_e630c828 {
    /* 0x00 */ x_87049dce *x_46ce35c8;
    /* 0x04 */ x_aece7675 *x_1256da71;
    /* 0x08 */ x_6751d717 x_732aef72[2];
} x_e630c828; // size = 0x10

typedef struct x_448872e8 {
    /* 0x00 */ u16 x_af0aa1f8;
    /* 0x02 */ u16 x_cd679b4c;
    /* 0x04 */ u16 x_1256da71;
} x_448872e8; // size = 0xC

typedef struct x_f1ef2747 {
    /* 0x00 */ s16 x_af0aa1f8;
    /* 0x02 */ s16 x_cd679b4c;
} x_f1ef2747; // size = 0x4

typedef struct x_a8b4b5ce {
    /* 0x00 */ u32 red;
    /* 0x04 */ u32 green;
    /* 0x08 */ u32 blue;
    /* 0x0C */ s32 x_b8173ab8;
    /* 0x10 */ s32 x_60c27ea9;
    /* 0x14 */ s32 x_d23de2ad;
    /* 0x18 */ s32 x_08b62e4f;
    /* 0x1C */ s32 x_2c79259e;
    /* 0x20 */ s32 x_034f3eb1;
    /* 0x24 */ s32 x_817784f2;
    /* 0x2C */ Object *object;
    /* 0x2C */ struct x_a8b4b5ce *next;
    /* 0x30 */ struct x_a8b4b5ce *previous;
} x_a8b4b5ce; // size = 0x34

typedef struct x_6dac5499 {
    /* 0x00 */ s16 x_af0aa1f8;
    /* 0x04 */ char *x_1256da71;
} x_6dac5499; // size = 8

typedef struct x_cc16c016 {
    /* 0x00 */ s16 x_af0aa1f8;
    /* 0x02 */ s16 x_cd679b4c;
    /* 0x04 */ s16 x_1256da71;
    /* 0x06 */ s16 x_8b47d6ce;
} x_cc16c016; // size = 0x08

typedef struct x_79eacfe1 {
    /* 0x00 */ s16 x_a962826d;
    /* 0x02 */ s16 x_3f3ac621;
} x_79eacfe1; // size = 0x4

typedef s32 (*x_1c3c0f22)(void *);

#endif
