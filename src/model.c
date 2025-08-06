#include "common.h"
#include "task.h"
#include "camera.h"

extern s32 *D_8013C4E8;
extern s32 D_8013C540;

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034090.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800340E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003424C.s")

void func_800343EC(void) {
    D_8013C540 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800343F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034508.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003453C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800345D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034648.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034708.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034860.s")

void func_800349F0(Object *obj) {
    u32 i;
    Model *model = obj->model;
    s32 count = model->unk_000;
    s8 *buffer = model->unk_1F6E;

    for (i = 0; i < count; i++) {
        buffer[i] = 1;
    }
}

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

void func_80036760(u8 *arg0, s16 *arg1, Object *obj) {
    s32 v0;
    Model *model;

    v0 = arg0[2];
    model = obj->model;

    if (v0 == 0xFF) {
        switch (arg0[3] & 0xF) {
            case 1:
                model->unk_9CC.x = (*arg1 + model->unk_9CC.x) >> 1;
                model->unk_9F4 = 1;
                break;
            case 2:
                model->unk_9CC.y = (*arg1 + model->unk_9CC.y) >> 1;
                model->unk_9F4 = 1;
                break;
            case 3:
                model->unk_9CC.z = (*arg1 + model->unk_9CC.z) >> 1;
                model->unk_9F4 = 1;
                break;
            case 4:
                model->unk_9D4.x = ((*arg1 + model->unk_9D4.x - model->unk_9E4.x) >> 1) + model->unk_9E4.x;
                break;
            case 5:
                model->unk_9D4.y = ((*arg1 + model->unk_9D4.y - model->unk_9E4.y) >> 1) + model->unk_9E4.y;
                break;
            case 6:
                model->unk_9D4.z = ((*arg1 + model->unk_9D4.z - model->unk_9E4.z) >> 1) + model->unk_9E4.z;
                break;
            case 7:
                model->unk_9F8.x = (*arg1 + model->unk_9F8.x) >> 1;
                model->unk_9F4 = 1;
                break;
            case 8:
                model->unk_9F8.y = (*arg1 + model->unk_9F8.y) >> 1;
                model->unk_9F4 = 1;
                break;
            case 9:
                model->unk_9F8.z = (*arg1 + model->unk_9F8.z) >> 1;
                model->unk_9F4 = 1;
                break;
        }
    } else if (v0 == 0xFE) {
        switch (arg0[3] & 0xF) {
            case 5:
                obj->pos.y = (*arg1 + obj->pos.y) >> 1;
                break;
            case 6:
                model->unk_00C = (*arg1 * obj->unk_010.z + model->unk_00C) >> 1;
                break;
            case 2:
                model->unk_132 = (*arg1 + model->unk_132) >> 1;
                break;
        }
    } else {
        Vec4s *temp = &model->unk_134[v0];
        switch (arg0[3] & 0xF) {
            case 1:
                temp->x = (*arg1 + temp->x) >> 1;
                model->unk_5E4[v0] = 1;
                break;
            case 2:
                temp->y = (*arg1 + temp->y) >> 1;
                model->unk_5E4[v0] = 1;
                break;
            case 3:
                temp->z = (*arg1 + temp->z) >> 1;
                model->unk_5E4[v0] = 1;
                break;
            case 4:
                model->unk_404[v0].x = (f32) ((model->unk_404[v0].x + *arg1) >> 1);
                model->unk_5E4[v0] = 1;
                break;
            case 5:
                model->unk_404[v0].y = (f32) ((model->unk_404[v0].y + *arg1) >> 1);
                model->unk_5E4[v0] = 1;
                break;
            case 6:
                model->unk_404[v0].z = (f32) ((model->unk_404[v0].z + *arg1) >> 1);
                model->unk_5E4[v0] = 1;
                break;
            case 7:
                model->unk_224[v0].x = (*arg1 + model->unk_224[v0].x) >> 1;
                model->unk_5E4[v0] = 1;
                break;
            case 8:
                model->unk_224[v0].y = (*arg1 + model->unk_224[v0].y) >> 1;
                model->unk_5E4[v0] = 1;
                break;
            case 9:
                model->unk_224[v0].z = (*arg1 + model->unk_224[v0].z) >> 1;
                model->unk_5E4[v0] = 1;
                break;
        }
    }
}

void func_80036B68(u8 *arg0, s16 *arg1, Object *obj) {
    s32 v0;
    Model *model;

    v0 = arg0[2];
    model = obj->model;

    if (v0 == 0xFF) {
        switch (arg0[3] & 0xF) {
            case 1:
                model->unk_9CC.x = *arg1;
                model->unk_9F4 = 1;
                break;
            case 2:
                model->unk_9CC.y = *arg1;
                model->unk_9F4 = 1;
                break;
            case 3:
                model->unk_9CC.z = *arg1;
                model->unk_9F4 = 1;
                break;
            case 4:
                model->unk_9D4.x = *arg1 + model->unk_9E4.x;
                break;
            case 5:
                model->unk_9D4.y = *arg1 + model->unk_9E4.y;
                break;
            case 6:
                model->unk_9D4.z = *arg1 + model->unk_9E4.z;
                break;
            case 7:
                model->unk_9F8.x = *arg1;
                model->unk_9F4 = 1;
                break;
            case 8:
                model->unk_9F8.y = *arg1;
                model->unk_9F4 = 1;
                break;
            case 9:
                model->unk_9F8.z = *arg1;
                model->unk_9F4 = 1;
                break;
        }
    } else if (v0 == 0xFE) {
        switch (arg0[3] & 0xF) {
            case 5:
                obj->pos.y = *arg1;
                break;
            case 6:
                model->unk_00C = *arg1 * obj->unk_010.z;
                break;
            case 2:
                model->unk_132 = *arg1;
                break;
        }
    } else {
        switch (arg0[3] & 0xF) {
            case 1:
                model->unk_134[v0].x = *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 2:
                model->unk_134[v0].y = *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 3:
                model->unk_134[v0].z = *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 4:
                model->unk_404[v0].x = (f32) *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 5:
                model->unk_404[v0].y = (f32) *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 6:
                model->unk_404[v0].z = (f32) *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 7:
                model->unk_224[v0].x = *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 8:
                model->unk_224[v0].y = *arg1;
                model->unk_5E4[v0] = 1;
                break;
            case 9:
                model->unk_224[v0].z = *arg1;
                model->unk_5E4[v0] = 1;
                break;
        }
    }
}

void func_80036E54(u8 *arg0, u8 *arg1, Object *obj) {
    s32 a3;
    s32 v0;
    Model *model;
    Vec4s *temp;

    v0 = arg0[2];
    model = obj->model;
    a3 = *arg1;

    if (a3 & 0x80) {
        a3 |= 0xFFFFFF00; // sign extend
    }

    if (v0 == 0xFF) {
        switch ((arg0[3] & 0xF0) >> 4) {
            case 1:
                model->unk_9CC.x += a3;
                model->unk_9F4 = 1;
                break;
            case 2:
                model->unk_9CC.y += a3;
                model->unk_9F4 = 1;
                break;
            case 3:
                model->unk_9CC.z += a3;
                model->unk_9F4 = 1;
                break;
            case 4:
                model->unk_9D4.x += a3;
                break;
            case 5:
                model->unk_9D4.y += a3;
                break;
            case 6:
                model->unk_9D4.z += a3;
                break;
            case 7:
                model->unk_9F8.x += a3;
                model->unk_9F4 = 1;
                break;
            case 8:
                model->unk_9F8.y += a3;
                model->unk_9F4 = 1;
                break;
            case 9:
                model->unk_9F8.z += a3;
                model->unk_9F4 = 1;
                break;
        }
    } else if (v0 == 0xFE) {
        switch ((arg0[3] & 0xF0) >> 4) {
            case 5:
                obj->pos.y += a3;
                break;
            case 6:
                model->unk_00C += a3 * obj->unk_010.z;
                break;
            case 2:
                model->unk_132 += a3;
                break;
        }
    } else {
        temp = model->unk_134 + v0;
        switch ((arg0[3] & 0xF0) >> 4) {
            case 1:
                temp->x += a3;
                model->unk_5E4[v0] = 1;
                break;
            case 2:
                temp->y += a3;
                model->unk_5E4[v0] = 1;
                break;
            case 3:
                temp->z += a3;
                model->unk_5E4[v0] = 1;
                break;
            case 4:
                model->unk_404[v0].x += (f32) a3;
                model->unk_5E4[v0] = 1;
                break;
            case 5:
                model->unk_404[v0].y += (f32) a3;
                model->unk_5E4[v0] = 1;
                break;
            case 6:
                model->unk_404[v0].z += (f32) a3;
                model->unk_5E4[v0] = 1;
                break;
            case 7:
                model->unk_224[v0].x += a3;
                model->unk_5E4[v0] = 1;
                break;
            case 8:
                model->unk_224[v0].y += a3;
                model->unk_5E4[v0] = 1;
                break;
            case 9:
                model->unk_224[v0].z += a3;
                model->unk_5E4[v0] = 1;
                break;
        }
    }
}

void func_800371C0(Object *obj) {
    u8 *s0;
    s16 t7;
    Model *model = obj->model;
    s32 s6 = FALSE;

    if (obj->unk_084 & 1) {
        s6 = TRUE;
    }
    t7 = (obj->unk_084 + 1) >> 1;

    s0 = model->unk_A14;
    while (*(s32 *) s0 != -1) {
        s32 s2 = s0[0];
        s32 s3 = s0[1];

        if (s3 < t7 || s2 > t7) {
            if (s0[3] & 0xF) {
                s0 += s3 * 2 - s2 * 2 + 6;
                if ((s32) s0 & 3) {
                    s0 += 2;
                }
            } else {
                s0 += s3 - s2 + 5;
                while ((s32) s0 & 3) {
                    s0++;
                }
            }
        } else {
            if (s0[3] & 0xF) {
                if (s6) {
                    func_80036760(s0, s0 + 4 + t7 * 2 - s2 * 2, obj);
                } else {
                    func_80036B68(s0, s0 + 4 + t7 * 2 - s2 * 2, obj);
                }
                s0 += s3 * 2 - s2 * 2 + 6;
                if ((s32) s0 & 3) {
                    s0 += 2;
                }
            } else {
                func_80036E54(s0, s0 + 4 + t7 - s2, obj);
                s0 += s3 - s2 + 5;
                while ((s32) s0 & 3) {
                    s0++;
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037394.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800373FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037788.s")
void func_80037788(UnkCameraSub4 *, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003795C.s")

void func_80037CE4(Object *obj) {
    Model *model;
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
    model = obj->model;
    sub2 = model->unk_A28;
    newvar = sub2->unk_154[index];
    sp4C = D_8005BFCE * 30 + index;

    task_execute(obj);

    if (obj->flags & 4) {
        return;
    }

    mu = &obj->unk_0D0;
    AB0 = model->unk_AB0;

    if (obj->flags & 0x2000) {
        func_80034F34(obj);
    }

    if (!(obj->flags & 0x80000)) {
        obj->rotation.x = D_8013C668.x;
        obj->rotation.y = D_8013C668.y;
    }

    math_rotate(&mu->unk_98, &obj->rotation);
    math_translate(&mu->unk_98, &obj->pos);
    math_mtxf_mul(&mu->unk_98, &gCameraProjectionMatrix, &D_800813E0);

    sub = AB0 + sp4C;
    sub6 = &model->unk_A50;
    math_mtxf2mtx(&sub->unk_18, &D_800813E0);
    nv2 = sub2->unk_238[index];
    model->unk_A38 = sub;

    sub6->unk_28 = newvar;
    sub6->unk_38 = nv2;
    model->unk_A48 = D_8013C4E8;
    D_8013C4E8 = &model->unk_A30;
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80037E28.s")

void func_800386E8(Object *obj) {
    UnkCameraSub3 **s2;
    Model *model;
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

    model = obj->model;
    spAC = model->unk_128;
    s2 = model->unk_A28->unk_154;
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

    if (model->unk_12C != NULL) {
        if (model->unk_A0C != model->unk_A0E) {
            func_80037500(obj);
            model->unk_A0E = model->unk_A0C;
        }

        if (obj->unk_084 != obj->unk_086) {
            func_800371C0(obj);
            func_8003635C(obj);
            obj->unk_086 = obj->unk_084;
        }

        math_rotate(&mu->unk_98, &obj->rotation);
        math_translate(&mu->unk_98, &obj->pos);
        func_80014974(mu);

        if (model->unk_604 != 0) {
            if (obj->flags & 0x800) {
                func_8003561C(obj, -10000);
            } else {
                func_8003561C(obj, 0);
            }

            q = model->unk_608;
            for (i = 0; i < model->unk_9C8; i++) {
                new_var = q[i].unk_04;
                if (obj->flags & 0x02000000) {
                    q[i].unk_1C |= 2;
                }

                s6 = new_var->unk_24;
                s7 = model->unk_AB0;

                for (j = 0; j < s6; j++) {
                    s32 s1 = new_var->unk_04[j];

                    if (obj->flags & 0x01000000) {
                        a1 = &D_8013C6B0;
                    } else {
                        a1 = &gCameraProjectionMatrix;
                    }

                    if (spAC != NULL) {
                        math_mtxf_mul(&spAC[s1].unk_D8, a1, &D_800813E0);
                    } else {
                        math_mtxf_mul(&model->unk_010.unk_D8, a1, &D_800813E0);
                    }

                    s0 = &s7[s1 + sp94];
                    math_mtxf2mtx(&s0->unk_18, &D_800813E0);
                    q[i].unk_08[j] = s0;
                }
            }

            func_80037788(q, model->unk_9C8);
        }
    } else {
        s0 = model->unk_AB0;
        math_rotate(&mu->unk_98, &obj->rotation);
        math_translate(&mu->unk_98, &obj->pos);
        func_80014974(mu);
        math_mtxf_mul(&mu->unk_98, &gCameraProjectionMatrix, &D_800813E0);
        math_mtxf2mtx(&(s0 + sp94)->unk_18, &D_800813E0);
        func_80035DF8(model->unk_A28, 0);
        (*s2)->unk_04 = s0 + sp94;
    }
}
