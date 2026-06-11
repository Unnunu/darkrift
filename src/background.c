#include "common.h"
#include "camera.h"

typedef struct GroundTileHeader {
    /* 0x00 */ s32 tileCountX;
    /* 0x04 */ s32 tileCountZ;
    /* 0x08 */ s32 tileSizeX;
    /* 0x0C */ s32 tileSizeZ;
} GroundTileHeader;

Gfx **sGroundTileDlTable = NULL;

x_88f11482 sGroundFrustumLocal[8];
x_88f11482 sGroundFrustumWorld[8];
s16 sGroundFrustumMinX;
s16 sGroundFrustumMaxX;
s16 sGroundFrustumMinZ;
s16 sGroundFrustumMaxZ;
s16 sGroundTileCountX;
s16 sGroundTileCountZ;
s16 sGroundTileSizeX;
s16 sGroundTileSizeZ;
s16 sGroundTileTotal;
s16 sGroundTileHalfX;
s16 sGroundTileHalfZ;
s16 D_800815F6;
s16 D_800815F8;
s16 D_800815FA;
s16 D_800815FC;
s16 sGroundTileStartX;
s16 sGroundTileEndX;
s16 sGroundTileStartZ;
s16 sGroundTileEndZ;
s16 sGroundRowWidth;
s16 sGroundColHeight;
x_82e80914 *sGroundModel;
u16 *sGroundPalette;
Mtx sGroundRotMatrix;

#ifdef NON_EQUIVALENT
void ground_frustum_compute(void) {
    x_acccb624 x_c188a78e;
    s32 x_81bfdb41;
    s32 t1;
    s32 t5;
    s16 x_720f6ac9, x_aa1be933, dz;
    s16 x_5d21c78b, x_2dc9f256, x_b7cc9533;
    s16 i;
    s32 x1, y1, z1;
    s32 x2, y2, z2;

    x_720f6ac9 = sCamLookAt.x - gCamTargetObj->pos.x;
    x_aa1be933 = sCamLookAt.y - gCamTargetObj->pos.y;
    dz = sCamLookAt.z - gCamTargetObj->pos.z;

    x_5d21c78b = ABS(x_720f6ac9);
    x_b7cc9533 = ABS(dz);
    x_2dc9f256 = ABS(x_aa1be933);
    x_81bfdb41 = x_4a9e7834(x_5d21c78b, x_b7cc9533);
    t1 = -x_4a9e7834(x_81bfdb41, x_2dc9f256);
    t5 = 7500 - t1;

    x1 = ((x_c84980f9 * (sCamUnkParam + 1000) / sCamUnkParam) >> 1);
    sGroundFrustumLocal[0].x = x1;
    sGroundFrustumLocal[1].x = -x1;
    sGroundFrustumLocal[2].x = x1;
    sGroundFrustumLocal[3].x = -x1;

    y1 = sCamUnkParam + 1000 + t1;
    sGroundFrustumLocal[0].y = y1;
    sGroundFrustumLocal[1].y = y1;
    sGroundFrustumLocal[2].y = y1;
    sGroundFrustumLocal[3].y = y1;

    z1 = ((x_a4f5fb93 * (sCamUnkParam + 1000) / sCamUnkParam) >> 1);
    sGroundFrustumLocal[0].z = z1;
    sGroundFrustumLocal[1].z = z1;
    sGroundFrustumLocal[2].z = -z1;
    sGroundFrustumLocal[3].z = -z1;

    x2 = ((x_c84980f9 * t5 / sCamUnkParam) >> 1);
    y2 = 7500;
    z2 = ((x_a4f5fb93 * t5 / sCamUnkParam) >> 1);

    sGroundFrustumLocal[4].x = x2;
    sGroundFrustumLocal[4].y = y2;
    sGroundFrustumLocal[4].z = z2;

    sGroundFrustumLocal[5].x = -x2;
    sGroundFrustumLocal[5].y = y2;
    sGroundFrustumLocal[5].z = z2;

    sGroundFrustumLocal[6].x = -x2;
    sGroundFrustumLocal[6].y = y2;
    sGroundFrustumLocal[6].z = -z2;

    sGroundFrustumLocal[7].x = x2;
    sGroundFrustumLocal[7].y = y2;
    sGroundFrustumLocal[7].z = -z2;

    x_c188a78e.x = atan2_lut(x_81bfdb41, x_aa1be933);
    x_c188a78e.y = atan2_lut(x_720f6ac9, dz);
    x_c188a78e.z = 0;

    mat4_from_euler(&gMat4Temp, &x_c188a78e);
    vec_transform_by_mat4(&sGroundFrustumLocal[0], &sGroundFrustumWorld[0], &gMat4Temp);
    vec_transform_by_mat4(&sGroundFrustumLocal[1], &sGroundFrustumWorld[1], &gMat4Temp);
    vec_transform_by_mat4(&sGroundFrustumLocal[2], &sGroundFrustumWorld[2], &gMat4Temp);
    vec_transform_by_mat4(&sGroundFrustumLocal[3], &sGroundFrustumWorld[3], &gMat4Temp);
    vec_transform_by_mat4(&sGroundFrustumLocal[4], &sGroundFrustumWorld[4], &gMat4Temp);
    vec_transform_by_mat4(&sGroundFrustumLocal[5], &sGroundFrustumWorld[5], &gMat4Temp);
    vec_transform_by_mat4(&sGroundFrustumLocal[6], &sGroundFrustumWorld[6], &gMat4Temp);
    vec_transform_by_mat4(&sGroundFrustumLocal[7], &sGroundFrustumWorld[7], &gMat4Temp);

    sGroundFrustumWorld[0].x += sCamLookAt.x;
    sGroundFrustumWorld[0].z += sCamLookAt.z;
    sGroundFrustumMaxX = sGroundFrustumMinX = sGroundFrustumWorld[0].x;
    sGroundFrustumMaxZ = sGroundFrustumMinZ = sGroundFrustumWorld[0].z;

    for (i = 1; i < 8; i++) {
        sGroundFrustumWorld[i].x += sCamLookAt.x;
        sGroundFrustumWorld[i].y += sCamLookAt.y;
        sGroundFrustumWorld[i].z += sCamLookAt.z;

        if (sGroundFrustumMinX > sGroundFrustumWorld[i].x) {
            sGroundFrustumMinX = sGroundFrustumWorld[i].x;
        } else if (sGroundFrustumMaxX < sGroundFrustumWorld[i].x) {
            sGroundFrustumMaxX = sGroundFrustumWorld[i].x;
        }

        if (sGroundFrustumMinZ > sGroundFrustumWorld[i].z) {
            sGroundFrustumMinZ = sGroundFrustumWorld[i].z;
        } else if (sGroundFrustumMaxZ < sGroundFrustumWorld[i].z) {
            sGroundFrustumMaxZ = sGroundFrustumWorld[i].z;
        }
    }

    if (sGroundFrustumMinZ < 0) {
        sGroundTileEndZ = sGroundTileHalfZ - (sGroundFrustumMinZ - sGroundTileSizeZ) / sGroundTileSizeZ;
    } else {
        sGroundTileEndZ = sGroundTileHalfZ - sGroundFrustumMinZ / sGroundTileSizeZ;
    }

    if (sGroundFrustumMaxZ < 0) {
        sGroundTileStartZ = sGroundTileHalfZ - (sGroundFrustumMaxZ - sGroundTileSizeZ) / sGroundTileSizeZ;
    } else {
        sGroundTileStartZ = sGroundTileHalfZ - sGroundFrustumMaxZ / sGroundTileSizeZ;
    }

    if (sGroundFrustumMinX < 0) {
        sGroundTileStartX = sGroundTileHalfX + (sGroundFrustumMinX - sGroundTileSizeX) / sGroundTileSizeX;
    } else {
        sGroundTileStartX = sGroundTileHalfX + sGroundFrustumMinX / sGroundTileSizeX;
    }

    if (sGroundFrustumMaxX < 0) {
        sGroundTileEndX = sGroundTileHalfX + (sGroundFrustumMaxX - sGroundTileSizeX) / sGroundTileSizeX;
    } else {
        sGroundTileEndX = sGroundTileHalfX + sGroundFrustumMaxX / sGroundTileSizeX;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/background/ground_frustum_compute.s")
void ground_frustum_compute(void);
#endif

void ground_render(void) {
    s16 i, j;
    s16 v0, a0;

    ground_frustum_compute();

    gDPLoadTLUT_pal16(gF3dDisplayListPtr++, 0, x_c485761a(sGroundPalette));
    gSPMatrix(gF3dDisplayListPtr++, x_c485761a(&sGroundRotMatrix), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    for (i = sGroundTileStartZ - 1; i < sGroundTileEndZ + 1; i++) {
        for (j = sGroundTileStartX; j < sGroundTileEndX + 1; j++) {
            if (j >= 0) {
                a0 = j % sGroundTileCountX;
            } else {
                a0 = j % sGroundTileCountX;
                if (a0 != 0) {
                    a0 += sGroundTileCountX;
                }
            }

            if (i >= 0) {
                v0 = i % sGroundTileCountZ;
            } else {
                v0 = i % sGroundTileCountZ;
                if (v0 != 0) {
                    v0 += sGroundTileCountZ;
                }
            }

            gSPDisplayList(gF3dDisplayListPtr++, x_c485761a(sGroundTileDlTable[v0 * sGroundTileCountX + a0]));
        }
    }
}

void ground_load(char *name, s32 x_84ff873b) {
    GroundTileHeader *x_8a9089b3;
    x_c3c252eb *x_94b671c9;
    char x_840385a0[20];
    char x_f10a928a[20];
    x_acccb624 x_081c4eef;
    s32 unused;
    x_3b6b80ec *a3;
    x_36123519 *x_9a110419;
    x_88f11482 x_5bbba600 = { 0, 0, 6000, 0 };

    wad_strcpy(x_840385a0, name);
    wad_strcat(x_840385a0, ".pcl");
    x_8a9089b3 = sWadEntries[wad_entry_find(x_840385a0, x_84ff873b)].data;

    wad_strcpy(x_f10a928a, name);
    wad_strcat(x_f10a928a, ".GMD");
    sGroundModel = sWadEntries[wad_entry_find(x_f10a928a, x_84ff873b)].x_4962fc73;
    sGroundTileDlTable = &sGroundModel->model.x_bde24317;

    x_94b671c9 = sGroundModel->model.x_3bfb7219->x_45978ecb;
    x_9a110419 = x_94b671c9->x_063bc6a1;
    a3 = x_9a110419->texture;
    if (a3->format == 4) {
        sGroundPalette = sGroundModel->model.x_3bfb7219->x_1dbd7f4a + a3->x_3f981ea3 * 0x20; // TODO: type
    } else {
        sGroundPalette = sGroundModel->model.x_3bfb7219->x_d38574ae + a3->x_3f981ea3 * 0x200; // TODO: type
    }

    sGroundTileCountX = x_8a9089b3->tileCountX;
    sGroundTileCountZ = x_8a9089b3->tileCountZ;
    sGroundTileSizeX = x_8a9089b3->tileSizeX;
    sGroundTileSizeZ = x_8a9089b3->tileSizeZ;

    sGroundTileTotal = sGroundTileCountX * sGroundTileCountZ;
    sGroundRowWidth = sGroundTileCountX * sGroundTileSizeX;
    sGroundColHeight = sGroundTileCountZ * sGroundTileSizeZ;

    sGroundTileHalfX = sGroundTileCountX / 2;
    sGroundTileHalfZ = sGroundTileCountX / 2;

    mat4_ident(&gMat4Temp);
    x_081c4eef.y = x_081c4eef.z = 0;
    x_081c4eef.x = -0x400;
    mat4_from_euler(&gMat4Temp, &x_081c4eef);
    mat4_to_mtx(&sGroundRotMatrix, &gMat4Temp);
}
