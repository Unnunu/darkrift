#include "common.h"
#include "task.h"
#include "camera.h"
#include "string.h"

extern s32 *D_8013C4E8;
extern s32 D_8013C540;
extern char *D_80053010;
extern Vec4i D_8004934C;
extern UnkDispStruct **D_8013C4E0;
Object *func_8002BC84(Vec4i *, s32, char **, s32);
void func_800028E0(s32 arg0, s32 arg1);

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
void func_80034D54(void);

void func_80034F34(Object *obj) {
    ColorRGBA *color1 = &obj->unk_200;
    ColorRGBA *color2 = &obj->unk_204;

    color1->a = obj->unk_088.a;

    if (color2->r != color1->r || color2->g != color1->g || color2->b != color1->b || color2->a != color1->a) {
        func_800028E0(func_80034D54, obj);
        memcpy(&obj->unk_204, &obj->unk_200, sizeof(ColorRGBA));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80034FC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003517C.s")
void func_8003517C(UnkSam *, s32, Vec4i *);

#pragma GLOBAL_ASM("asm/nonmatchings/model/D_800551D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800352FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_8003561C.s")
void func_8003561C(Object *, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_800359E4.s")

void func_80035CCC(UnkSam *arg0) {
    s32 count;
    u32 i;
    UnkSamSub *s1;
    s32 unused[4];
    u32 j;
    UnkDispStruct **var1;
    s32 temp;
    Vec4i sp58;
    s32 temp2;

    count = arg0->unk_128;
    s1 = arg0->unk_31C = (UnkSamSub *) mem_alloc(count * sizeof(UnkSamSub), "model.c", 766);
    temp = 1; // required to match
    var1 = arg0->unk_154;
    for (i = 0; i < count; i++, s1++) {
        s1->unk_00 = temp;

        func_8003517C(arg0, i, &sp58);
        s1->unk_14 = sp58.x;
        s1->unk_18 = sp58.y;
        s1->unk_1C = sp58.z;

        s1->unk_04[0] = i;
        s1->unk_08 = -1;
        s1->unk_20 = i;
        s1->unk_24 = temp;

        temp2 = 1; // required to match
        for (j = 0; j < temp2; j++) {
            s32 v0 = s1->unk_04[j];
            s1->unk_28[j] = var1[v0];
            s1->unk_38[j] = arg0->unk_238[v0];
        }
    }
}

void func_80035DF8(UnkSam *arg0, s32 arg1) {
    u32 i;
    s32 a2;
    UnkDispStruct *v0;

    v0 = arg0->unk_154[arg1];
    a2 = arg0->unk_238[arg1];

    for (i = 0; i < a2; i++) {
        PUSH_UNK_DISP(D_8005BFE4, NULL, v0->unk_04, v0->unk_08, v0->unk_0C);
        v0++;
    }
}

void func_80035F5C(Object *obj) {
    Model *model;
    Object *parent;
    s16 j;
    s16 i;
    s16 s6;
    Matrix4f sp98;
    f32 v1, a0;
    UnkDispStructPart2 *sub;
    UnkMu *trans;
    s32 unused[4];
    UnkDispStruct **sub3;
    Matrix4f *newvar;

    model = obj->model;
    trans = model->unk_128;
    parent = (Object *) obj->unk_090[1];
    newvar = &obj->unk_0D0.unk_98;
    sub3 = model->unk_A28->unk_154;

    if (parent->flags & 0x4) {
        return;
    }

    D_8013C4E0 = model->unk_A24->unk_154;
    func_80012AA8(&sp98);
    s6 = D_8005BFCE * 30;

    for (i = 0; i < model->unk_000; i++) {
        func_80014718(&sp98, &trans[i].unk_D8, newvar);
        math_mtxf_mul(&sp98, &gCameraProjectionMatrix, &D_800813E0);

        if (D_800813E0.w.w != 0.0f) {
            v1 = D_800813E0.w.x / D_800813E0.w.w;
            a0 = D_800813E0.w.y / D_800813E0.w.w;
        } else {
            v1 = a0 = 2.0f;
        }

        if (v1 > 1.0 || v1 < -1.0 || a0 > 1.0 || a0 < -1.0) {
            continue;
        }

        j = i + s6;

        sub = j + model->unk_AB0;
        if (&D_800813E0 && &D_800813E0) {} // required to match

        math_mtxf2mtx(&sub->unk_18, &D_800813E0);
        sub3[i]->unk_04 = sub;
        func_80035DF8(model->unk_A28, i);
    }
}

void func_80036194(Object *arg0, char *arg1, s32 arg2) {
    Object *v0;

    str_copy(D_80053010, arg1);
    v0 = func_8002BC84(&D_8004934C, 0, &D_80053010, arg2);

    v0->unk_090[0] = v0->model->unk_128;
    v0->unk_090[1] = arg0;
    v0->model->unk_128 = arg0->model->unk_128;
    v0->fn_update = func_80035F5C;

    v0->unk_0D0.unk_98.y.x = 0.0f;
    v0->unk_0D0.unk_98.x.y = 0.0f;
    v0->unk_0D0.unk_98.y.y = 0.0f;
    v0->unk_0D0.unk_98.z.y = 0.0f;
    v0->unk_0D0.unk_98.y.z = -1.5f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/model/func_80036228.s")

void func_8003635C(Object *obj) {
    Model *model = obj->model;
    s32 count;
    s32 i;
    s16 v1;
    u8 *ptr;
    UnkMu *trans;
    Vec4i sp88;
    s32 unused[5];
    Vec4i *vec1;
    Vec4s *vec3;
    StructAA8 *vec2;
    Vec4i *vec4;

    vec4 = model->unk_224;
    ptr = model->unk_5E4;
    vec2 = model->unk_AA8;
    vec1 = model->unk_404;
    vec3 = model->unk_134;
    count = model->unk_000;
    trans = model->unk_128;

    for (i = 0; i < count; i++) {
        if (ptr[i]) {
            math_rotate(&trans[i].unk_98, &vec3[i]);
            func_800139A0(&trans[i].unk_98, &vec4[i]);

            trans[i].unk_98.w.x = vec2[i].x + vec1[i].x;
            trans[i].unk_98.w.y = vec2[i].y + vec1[i].y;
            trans[i].unk_98.w.z = vec2[i].z + vec1[i].z;
            ptr[i] = FALSE;
        }
    }

    if (model->unk_9F4 || model->unk_132 != 0) {
        math_rotate(&model->unk_010.unk_98, &model->unk_9CC);
        func_800139A0(&model->unk_010.unk_98, &model->unk_9F8);
        model->unk_9F4 = FALSE;
    }

    if (obj->flags & 0x400) {
        model->unk_010.unk_98.w.y = model->unk_9D4.y;
        sp88.y = 0;
        if (obj->flags & 0x20000) {
            sp88.x = model->unk_9D4.x - model->unk_9E4.x - model->unk_A1C;
            v1 = sp88.x - model->unk_002;
            model->unk_002 = sp88.x;
            sp88.x = v1;
            model->unk_010.unk_98.w.x = model->unk_9E4.x;
        } else {
            sp88.x = 0;
        }
        sp88.z = model->unk_9D4.z - model->unk_9E4.z;

        if (sp88.z != 0 || sp88.x != 0) {
            v1 = 0;
            if (obj->flags & 0x100000) {
                obj->flags &= ~0x100000;
            } else {
                v1 = sp88.z - model->unk_006;
            }
            model->unk_006 = sp88.z;
            sp88.z = v1;

            model->unk_010.unk_98.w.z = model->unk_9E4.z;
            func_8001370C(&sp88, &obj->rotation);
            if (!(obj->flags & 0x8000)) {
                obj->pos.x += sp88.x;
                obj->pos.z += sp88.z;
            }
        }
    } else {
        model->unk_010.unk_98.w.x = model->unk_9D4.x;
        model->unk_010.unk_98.w.y = model->unk_9D4.y;
        model->unk_010.unk_98.w.z = model->unk_9D4.z;

        if (model->unk_00C != 0) {
            sp88.x = 0;
            sp88.z = model->unk_00C - model->unk_006;
            model->unk_006 = model->unk_00C;
            func_8001370C(&sp88, &obj->rotation); // @bug sp88.y undefined
            obj->pos.x += sp88.x;
            obj->pos.z += sp88.z;
        }

        if (obj->flags & 0x8000000) {
            if (obj->flags & 0x800000) {
                obj->rotation.y = 0x400 - ((0xC00 - obj->rotation.y) & 0xFFF);
                obj->flags &= ~0x800000;
            }

            obj->flags &= ~0x8000000;

            sp88.y = 0;
            sp88.x = model->unk_9D4.x;
            sp88.z = model->unk_9D4.z;

            func_8001370C(&sp88, &obj->rotation);
            obj->pos.x -= sp88.x;
            obj->pos.z -= sp88.z;
        }
    }
}

void func_80036760(u8 *arg0, s16 *arg1, Object *obj) {
    s32 v0;
    Model *model;

    v0 = arg0[2];
    model = obj->model;

    if (v0 == 0xFF) {
        switch (arg0[3] & 0xF) {
            case 1:
                model->unk_9CC.x = (*arg1 + model->unk_9CC.x) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 2:
                model->unk_9CC.y = (*arg1 + model->unk_9CC.y) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 3:
                model->unk_9CC.z = (*arg1 + model->unk_9CC.z) >> 1;
                model->unk_9F4 = TRUE;
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
                model->unk_9F4 = TRUE;
                break;
            case 8:
                model->unk_9F8.y = (*arg1 + model->unk_9F8.y) >> 1;
                model->unk_9F4 = TRUE;
                break;
            case 9:
                model->unk_9F8.z = (*arg1 + model->unk_9F8.z) >> 1;
                model->unk_9F4 = TRUE;
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
                model->unk_9F4 = TRUE;
                break;
            case 2:
                model->unk_9CC.y = *arg1;
                model->unk_9F4 = TRUE;
                break;
            case 3:
                model->unk_9CC.z = *arg1;
                model->unk_9F4 = TRUE;
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
                model->unk_9F4 = TRUE;
                break;
            case 8:
                model->unk_9F8.y = *arg1;
                model->unk_9F4 = TRUE;
                break;
            case 9:
                model->unk_9F8.z = *arg1;
                model->unk_9F4 = TRUE;
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
                model->unk_9F4 = TRUE;
                break;
            case 2:
                model->unk_9CC.y += a3;
                model->unk_9F4 = TRUE;
                break;
            case 3:
                model->unk_9CC.z += a3;
                model->unk_9F4 = TRUE;
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
                model->unk_9F4 = TRUE;
                break;
            case 8:
                model->unk_9F8.y += a3;
                model->unk_9F4 = TRUE;
                break;
            case 9:
                model->unk_9F8.z += a3;
                model->unk_9F4 = TRUE;
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
    UnkSam *sub2;
    s32 index;
    UnkCameraSub6 *sub6;
    UnkDispStruct *newvar;
    s32 sp4C;
    s32 nv2;
    UnkDispStructPart2 *sub;
    s32 unused[5];
    UnkDispStructPart2 *AB0;
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
    UnkDispStruct **s2;
    Model *model;
    UnkMu *spAC;
    s32 j;
    u32 i;
    UnkCameraSub5 *new_var;
    Matrix4f *a1;
    UnkDispStructPart2 *s0;
    s32 sp94;
    UnkCameraSub4 *q;
    s32 s6;
    UnkMu *mu;
    Matrix4f *nu;
    UnkDispStructPart2 *s7;
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
