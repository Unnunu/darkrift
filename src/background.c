#include "common.h"
#include "camera.h"

typedef struct x_80bba465 {
    /* 0x00 */ s32 x_af0aa1f8;
    /* 0x04 */ s32 x_1256da71;
    /* 0x08 */ s32 x_415ed9d6;
    /* 0x0C */ s32 x_b8173ab8;
} x_80bba465;

Gfx **D_80049CF0 = NULL;

x_88f11482 D_800814E0[8];
x_88f11482 D_80081560[8];
s16 D_800815E0;
s16 D_800815E2;
s16 D_800815E4;
s16 D_800815E6;
s16 D_800815E8;
s16 D_800815EA;
s16 D_800815EC;
s16 D_800815EE;
s16 D_800815F0;
s16 D_800815F2;
s16 D_800815F4;
s16 D_800815F6;
s16 D_800815F8;
s16 D_800815FA;
s16 D_800815FC;
s16 D_800815FE;
s16 D_80081600;
s16 D_80081602;
s16 D_80081604;
s16 D_80081606;
s16 D_80081608;
x_82e80914 *D_8008160C;
u16 *D_80081610;
Mtx D_80081618;

#ifdef NON_EQUIVALENT
void x_fc4a871b(void) {
    x_acccb624 x_c188a78e;
    s32 x_81bfdb41;
    s32 t1;
    s32 t5;
    s16 x_720f6ac9, x_aa1be933, dz;
    s16 x_5d21c78b, x_2dc9f256, x_b7cc9533;
    s16 i;
    s32 x1, y1, z1;
    s32 x2, y2, z2;

    x_720f6ac9 = x_435c561d.x - x_f4bce728->pos.x;
    x_aa1be933 = x_435c561d.y - x_f4bce728->pos.y;
    dz = x_435c561d.z - x_f4bce728->pos.z;

    x_5d21c78b = ABS(x_720f6ac9);
    x_b7cc9533 = ABS(dz);
    x_2dc9f256 = ABS(x_aa1be933);
    x_81bfdb41 = x_4a9e7834(x_5d21c78b, x_b7cc9533);
    t1 = -x_4a9e7834(x_81bfdb41, x_2dc9f256);
    t5 = 7500 - t1;

    x1 = ((x_c84980f9 * (D_8013C588 + 1000) / D_8013C588) >> 1);
    D_800814E0[0].x = x1;
    D_800814E0[1].x = -x1;
    D_800814E0[2].x = x1;
    D_800814E0[3].x = -x1;

    y1 = D_8013C588 + 1000 + t1;
    D_800814E0[0].y = y1;
    D_800814E0[1].y = y1;
    D_800814E0[2].y = y1;
    D_800814E0[3].y = y1;

    z1 = ((x_a4f5fb93 * (D_8013C588 + 1000) / D_8013C588) >> 1);
    D_800814E0[0].z = z1;
    D_800814E0[1].z = z1;
    D_800814E0[2].z = -z1;
    D_800814E0[3].z = -z1;

    x2 = ((x_c84980f9 * t5 / D_8013C588) >> 1);
    y2 = 7500;
    z2 = ((x_a4f5fb93 * t5 / D_8013C588) >> 1);

    D_800814E0[4].x = x2;
    D_800814E0[4].y = y2;
    D_800814E0[4].z = z2;

    D_800814E0[5].x = -x2;
    D_800814E0[5].y = y2;
    D_800814E0[5].z = z2;

    D_800814E0[6].x = -x2;
    D_800814E0[6].y = y2;
    D_800814E0[6].z = -z2;

    D_800814E0[7].x = x2;
    D_800814E0[7].y = y2;
    D_800814E0[7].z = -z2;

    x_c188a78e.x = atan2_lut(x_81bfdb41, x_aa1be933);
    x_c188a78e.y = atan2_lut(x_720f6ac9, dz);
    x_c188a78e.z = 0;

    mat4_from_euler(&gMat4Temp, &x_c188a78e);
    vec_transform_by_mat4(&D_800814E0[0], &D_80081560[0], &gMat4Temp);
    vec_transform_by_mat4(&D_800814E0[1], &D_80081560[1], &gMat4Temp);
    vec_transform_by_mat4(&D_800814E0[2], &D_80081560[2], &gMat4Temp);
    vec_transform_by_mat4(&D_800814E0[3], &D_80081560[3], &gMat4Temp);
    vec_transform_by_mat4(&D_800814E0[4], &D_80081560[4], &gMat4Temp);
    vec_transform_by_mat4(&D_800814E0[5], &D_80081560[5], &gMat4Temp);
    vec_transform_by_mat4(&D_800814E0[6], &D_80081560[6], &gMat4Temp);
    vec_transform_by_mat4(&D_800814E0[7], &D_80081560[7], &gMat4Temp);

    D_80081560[0].x += x_435c561d.x;
    D_80081560[0].z += x_435c561d.z;
    D_800815E2 = D_800815E0 = D_80081560[0].x;
    D_800815E6 = D_800815E4 = D_80081560[0].z;

    for (i = 1; i < 8; i++) {
        D_80081560[i].x += x_435c561d.x;
        D_80081560[i].y += x_435c561d.y;
        D_80081560[i].z += x_435c561d.z;

        if (D_800815E0 > D_80081560[i].x) {
            D_800815E0 = D_80081560[i].x;
        } else if (D_800815E2 < D_80081560[i].x) {
            D_800815E2 = D_80081560[i].x;
        }

        if (D_800815E4 > D_80081560[i].z) {
            D_800815E4 = D_80081560[i].z;
        } else if (D_800815E6 < D_80081560[i].z) {
            D_800815E6 = D_80081560[i].z;
        }
    }

    if (D_800815E4 < 0) {
        D_80081604 = D_800815F4 - (D_800815E4 - D_800815EE) / D_800815EE;
    } else {
        D_80081604 = D_800815F4 - D_800815E4 / D_800815EE;
    }

    if (D_800815E6 < 0) {
        D_80081602 = D_800815F4 - (D_800815E6 - D_800815EE) / D_800815EE;
    } else {
        D_80081602 = D_800815F4 - D_800815E6 / D_800815EE;
    }

    if (D_800815E0 < 0) {
        D_800815FE = D_800815F2 + (D_800815E0 - D_800815EC) / D_800815EC;
    } else {
        D_800815FE = D_800815F2 + D_800815E0 / D_800815EC;
    }

    if (D_800815E2 < 0) {
        D_80081600 = D_800815F2 + (D_800815E2 - D_800815EC) / D_800815EC;
    } else {
        D_80081600 = D_800815F2 + D_800815E2 / D_800815EC;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/background/x_fc4a871b.s")
void x_fc4a871b(void);
#endif

void x_ff4031b5(void) {
    s16 i, j;
    s16 v0, a0;

    x_fc4a871b();

    gDPLoadTLUT_pal16(gF3dDisplayListPtr++, 0, x_c485761a(D_80081610));
    gSPMatrix(gF3dDisplayListPtr++, x_c485761a(&D_80081618), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    for (i = D_80081602 - 1; i < D_80081604 + 1; i++) {
        for (j = D_800815FE; j < D_80081600 + 1; j++) {
            if (j >= 0) {
                a0 = j % D_800815E8;
            } else {
                a0 = j % D_800815E8;
                if (a0 != 0) {
                    a0 += D_800815E8;
                }
            }

            if (i >= 0) {
                v0 = i % D_800815EA;
            } else {
                v0 = i % D_800815EA;
                if (v0 != 0) {
                    v0 += D_800815EA;
                }
            }

            gSPDisplayList(gF3dDisplayListPtr++, x_c485761a(D_80049CF0[v0 * D_800815E8 + a0]));
        }
    }
}

void x_7a8b20f2(char *name, s32 x_84ff873b) {
    x_80bba465 *x_8a9089b3;
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
    D_8008160C = sWadEntries[wad_entry_find(x_f10a928a, x_84ff873b)].x_4962fc73;
    D_80049CF0 = &D_8008160C->model.x_bde24317;

    x_94b671c9 = D_8008160C->model.x_3bfb7219->x_45978ecb;
    x_9a110419 = x_94b671c9->x_063bc6a1;
    a3 = x_9a110419->texture;
    if (a3->format == 4) {
        D_80081610 = D_8008160C->model.x_3bfb7219->x_1dbd7f4a + a3->x_3f981ea3 * 0x20; // TODO: type
    } else {
        D_80081610 = D_8008160C->model.x_3bfb7219->x_d38574ae + a3->x_3f981ea3 * 0x200; // TODO: type
    }

    D_800815E8 = x_8a9089b3->x_af0aa1f8;
    D_800815EA = x_8a9089b3->x_1256da71;
    D_800815EC = x_8a9089b3->x_415ed9d6;
    D_800815EE = x_8a9089b3->x_b8173ab8;

    D_800815F0 = D_800815E8 * D_800815EA;
    D_80081606 = D_800815E8 * D_800815EC;
    D_80081608 = D_800815EA * D_800815EE;

    D_800815F2 = D_800815E8 / 2;
    D_800815F4 = D_800815E8 / 2;

    mat4_ident(&gMat4Temp);
    x_081c4eef.y = x_081c4eef.z = 0;
    x_081c4eef.x = -0x400;
    mat4_from_euler(&gMat4Temp, &x_081c4eef);
    mat4_to_mtx(&D_80081618, &gMat4Temp);
}
