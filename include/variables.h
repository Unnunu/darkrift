#ifndef VARIABLES_H
#define VARIABLES_H

extern UnkAlpha gPlayerInput[2];
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
extern UnkDispStruct *D_8005BFE4;

#endif
