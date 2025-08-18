#include "common.h"

extern Gfx **D_80049CF0;

extern s16 D_800815E8;
extern s16 D_800815EA;
extern s16 D_800815FE;
extern s16 D_80081600;
extern s16 D_80081602;
extern s16 D_80081604;
extern u16 *D_80081610;
extern Mtx D_80081618;

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001AAE0.s")
void func_8001AAE0(void);

void func_8001B26C(void) {
    s16 i, j;
    s16 v0, a0;

    func_8001AAE0();

    gDPLoadTLUT_pal16(D_8005BFD8++, 0, VIRTUAL_TO_PHYSICAL(D_80081610));
    gSPMatrix(D_8005BFD8++, VIRTUAL_TO_PHYSICAL(&D_80081618), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

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

            gSPDisplayList(D_8005BFD8++, VIRTUAL_TO_PHYSICAL(D_80049CF0[v0 * D_800815E8 + a0]));
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001B5B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001B7D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001B810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001BB2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001BB80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001BC7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001BD5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001BF40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001C02C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001C114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001C1C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001C2B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001C404.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001C48C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001C53C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CB74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CC18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CC8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CD28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CDAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CDE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CE0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001CE18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D070.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D1F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D44C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D660.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D6C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001D9B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001DA10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001DA90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001DB2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001DC68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001DDA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/1B6E0/func_8001DDEC.s")
