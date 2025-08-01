#include "common.h"
#include "task.h"
#include "camera.h"

extern s32 *D_8013C4E8;

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800340E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003424C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800343EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800343F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034508.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003453C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800345D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034708.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034860.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800349F0.s")
void func_800349F0(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034A58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034AB8.s")
void func_80034AB8(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034C18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034D54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034F34.s")
void func_80034F34(Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034FC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003517C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/D_800551D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800352FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003561C.s")
void func_8003561C(Object *, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800359E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80035CCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80035DF8.s")
void func_80035DF8(UnkCameraSub2 *, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80035F5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80036194.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80036228.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003635C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80036760.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80036B68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80036E54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800371C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800373FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037788.s")
void func_80037788(UnkCameraSub4 *, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003795C.s")

void func_80037CE4(Object *obj) {
    Camera *camera;
    UnkMu *mu;
    UnkCameraSub2 *sub2;
    s32 index;
    UnkCameraSub6 *sub6;
    UnkCameraSub3 *newvar;
    s32 sp4C;
    s32 nv2;
    UnkCameraSub *sub;
    s32 unused[5];
    UnkCameraSub *AB0;
    int temp;

    temp = obj->flags & 4; // required to match

    index = obj->unk_084;
    camera = obj->camera;
    sub2 = camera->unk_A28;
    newvar = sub2->unk_154[index];
    sp4C = D_8005BFCE * 30 + index;

    task_execute(obj);

    if (obj->flags & 4) {
        return;
    }

    mu = &obj->unk_0D0;
    AB0 = camera->unk_AB0;

    if (obj->flags & 0x2000) {
        func_80034F34(obj);
    }

    if (!(obj->flags & 0x80000)) {
        obj->rotation.x = D_8013C668.x;
        obj->rotation.y = D_8013C668.y;
    }

    func_8001305C(&mu->unk_98, &obj->rotation);
    func_800136CC(&mu->unk_98, &obj->pos);
    func_800149F0(&mu->unk_98, &gCameraProjectionMatrix, &D_800813E0);

    sub = AB0 + sp4C;
    sub6 = &camera->unk_A50;
    func_80013A54(&sub->unk_18, &D_800813E0);
    nv2 = sub2->unk_238[index];
    camera->unk_A38 = sub;

    sub6->unk_28 = newvar;
    sub6->unk_38 = nv2;
    camera->unk_A48 = D_8013C4E8;
    D_8013C4E8 = &camera->unk_A30;
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037E28.s")

void func_800386E8(Object *obj) {
    UnkCameraSub3 **s2;
    Camera *camera;
    UnkMu *spAC;
    s32 j;
    u32 i;
    UnkCameraSub5 *new_var;
    Matrix4f *a1;
    UnkCameraSub *s0;
    s32 sp94;
    UnkCameraSub4 *q;
    s32 s6;
    UnkMu *mu;
    Matrix4f *nu;
    UnkCameraSub *s7;
    s32 unused[8];

    camera = obj->camera;
    spAC = camera->unk_128;
    s2 = camera->unk_A28->unk_154;
    sp94 = 30 * D_8005BFCE;

    task_execute(obj);
    if (obj->flags & 4) {
        return;
    }

    mu = &obj->unk_0D0;

    if (obj->flags & 0x10000000) {
        func_800349F0(obj);
    }

    if ((!(obj->flags & 0x4000)) || (obj->flags & 0x10000000)) {
        func_80034AB8(obj);
    }

    func_80034F34(obj);

    if (obj->flags & 0x80000000) {
        obj->rotation.y = D_8013C668.y;
        obj->rotation.x = D_8013C668.x;
    }

    if (camera->unk_12C != NULL) {
        if (camera->unk_A0C != camera->unk_A0E) {
            func_80037500(obj);
            camera->unk_A0E = camera->unk_A0C;
        }

        if (obj->unk_084 != obj->unk_086) {
            func_800371C0(obj);
            func_8003635C(obj);
            obj->unk_086 = obj->unk_084;
        }

        func_8001305C(&mu->unk_98, &obj->rotation);
        func_800136CC(&mu->unk_98, &obj->pos);
        func_80014974(mu);

        if (camera->unk_604 != 0) {
            if (obj->flags & 0x800) {
                func_8003561C(obj, -10000);
            } else {
                func_8003561C(obj, 0);
            }

            q = camera->unk_608;
            for (i = 0; i < camera->unk_9C8; i++) {
                new_var = q[i].unk_04;
                if (obj->flags & 0x02000000) {
                    q[i].unk_1C |= 2;
                }

                s6 = new_var->unk_24;
                s7 = camera->unk_AB0;

                for (j = 0; j < s6; j++) {
                    s32 s1 = new_var->unk_04[j];

                    if (obj->flags & 0x01000000) {
                        a1 = &D_8013C6B0;
                    } else {
                        a1 = &gCameraProjectionMatrix;
                    }

                    if (spAC != NULL) {
                        func_800149F0(&spAC[s1].unk_D8, a1, &D_800813E0);
                    } else {
                        func_800149F0(&camera->unk_010.unk_D8, a1, &D_800813E0);
                    }

                    s0 = &s7[s1 + sp94];
                    func_80013A54(&s0->unk_18, &D_800813E0);
                    q[i].unk_08[j] = s0;
                }
            }

            func_80037788(q, camera->unk_9C8);
        }
    } else {
        s0 = camera->unk_AB0;
        func_8001305C(&mu->unk_98, &obj->rotation);
        func_800136CC(&mu->unk_98, &obj->pos);
        func_80014974(mu);
        func_800149F0(&mu->unk_98, &gCameraProjectionMatrix, &D_800813E0);
        func_80013A54(&(s0 + sp94)->unk_18, &D_800813E0);
        func_80035DF8(camera->unk_A28, 0);
        (*s2)->unk_04 = s0 + sp94;
    }
}
