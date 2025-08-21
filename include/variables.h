#ifndef VARIABLES_H
#define VARIABLES_H

extern PlayerInput gPlayerInput[2];
extern UnkGamma D_8005AEB8[256];
extern ChunkHeader *sFreeChunksList;
extern Asset gAssets[256];
extern u16 D_8005BFC0;
extern s32 D_8005BEFC;
extern Texture *D_80049AE0;
extern u16 D_8005BFCE;
extern s16 D_80080118;
extern u16 gGameMode;
extern u16 D_800AA450[2][8];
extern DisplayData *D_80080100;
extern s32 D_80049AE8;
extern s32 D_8008012C;
extern s32 D_80081428;
extern s32 gFrameCounter;
extern Matrix4f D_800813E0;
extern OSMesgQueue gSchedSPTaskQueue;
extern Batch *gMainBatchPos;
extern Player D_800AA488[2];
extern GameMode gGameModes[];
extern s16 D_80080110;
extern s16 D_80080112;
extern s16 D_80080114;
extern s16 D_80080130;
extern s16 D_80080132;
extern s16 D_80080134;
extern s16 D_80080136;
extern s16 D_80080138;
extern Player12 D_800B6328[2];
extern u8 D_800801F1;
extern u8 D_800B6350[2][11];
extern s16 D_80080230;
extern u16 gPracticingPlayer; // wrong name probably
extern Batch *gMainBatchPos;
extern Batch *gOverlayBatchPos;
extern Gfx *gMainGfxPos;
extern u8 D_800801E2;
extern Object *D_80052C50;
extern u16 gScreenWidth;
extern u16 gScreenHeight;

#endif
