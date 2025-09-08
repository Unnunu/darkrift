#include "common.h"
#include "task.h"
#include "string.h"

extern ItemPool D_8013C2B0;
extern ItemPool D_8013C2C0;

extern Vec3s D_80049344;
extern Vec4i D_8004934C;

extern s32 D_80052C54;
extern ModelNodeRenderInfo *D_8013C4E8;

void func_800345D8(s32);
void task_default_func(Object *arg0);
void func_80012450(Mtx *);

void func_8002A8C0(ItemPool *arg0, u32 count, u32 element_size) {
    s16 i;
    u8 *buffer;

    arg0->elements = (u8 **) mem_alloc(count * 4, "item.c", 23);
    arg0->buffer = (u8 *) mem_alloc(element_size * count, "item.c", 24);
    mem_fill(arg0->buffer, 0, count * element_size);
    arg0->count = count;
    arg0->unk_0C = count - 1;

    buffer = arg0->buffer;
    for (i = 0; i < count; i++) {
        arg0->elements[i] = buffer + i * element_size;
    }
}

void func_8002A994(ItemPool *arg0, u32 count, u32 element_size) {
    u32 i;
    u32 j;
    u32 old_count;
    u32 new_count;
    void *buffer;
    u8 **new_elements;

    old_count = arg0->count;
    new_count = old_count + count;

    new_elements = (u8 **) mem_alloc(new_count * 4, "item.c", 45);
    buffer = mem_alloc(count * element_size, "item.c", 46);

    for (i = 0; i < old_count; i++) {
        new_elements[i] = arg0->elements[i];
    }

    for (j = i; j < new_count; j++) {
        new_elements[j] = (u8 *) buffer + (j - i) * element_size;
    }

    mem_free(arg0->elements);

    arg0->elements = new_elements;
    arg0->count = new_count;
    arg0->unk_0C = new_count - 1;
}

void func_8002ABCC(s32 count) {
    func_8002A994(&D_8013C2B0, count, sizeof(Object));
    func_8002A994(&gTaskPool, count, sizeof(ObjectTask));
}

void func_8002AC10(void) {
    func_8002A8C0(&D_8013C2B0, 50, sizeof(Object));
    func_8002A8C0(&D_8013C2C0, 16, sizeof(ModelInstance));
    D_80052C50 = NULL;
    D_80052C54 = 0;
}

#ifdef NON_MATCHING
Object *obj_allocate(s16 arg0) {
    Object *obj;
    Object *prev_obj;

    D_80052C54++;
    if (D_8013C2B0.unk_0C <= 0) {
        return NULL;
    }

    if (D_80052C50 == NULL) {
        obj = D_80052C50 = (Object *) GET_ITEM(D_8013C2B0);

        obj->prevObject = NULL;
        obj->nextObject = NULL;
    } else {
        obj = D_80052C50;

        while (obj != NULL && obj->unk_074 >= arg0) {
            prev_obj = obj;
            obj = obj->nextObject;
        }

        if (obj == NULL) {
            prev_obj->nextObject = (Object *) GET_ITEM(D_8013C2B0);

            obj = prev_obj->nextObject;
            obj->prevObject = prev_obj;
            obj->nextObject = NULL;
        } else if (obj->prevObject == NULL) {
            obj = (Object *) GET_ITEM(D_8013C2B0);

            obj->nextObject = D_80052C50;
            D_80052C50->prevObject = obj;
            D_80052C50 = obj;
            obj->prevObject = NULL;
        } else {
            prev_obj = (Object *) GET_ITEM(D_8013C2B0);

            obj->prevObject->nextObject = prev_obj;
            prev_obj->nextObject = obj;
            prev_obj->prevObject = obj->prevObject;
            obj->prevObject = prev_obj;
            obj = prev_obj;
        }
    }

    obj->unk_074 = arg0;
    return obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/item/obj_allocate.s")
Object *obj_allocate(s16 arg0);
#endif

void obj_delete(Object *obj) {
    D_80052C54--;
    if (obj->prevObject == NULL) {
        obj->nextObject->prevObject = NULL;
        D_80052C50 = obj->nextObject;
    } else if (obj->nextObject == NULL) {
        obj->prevObject->nextObject = NULL;
    } else {
        obj->prevObject->nextObject = obj->nextObject;
        obj->nextObject->prevObject = obj->prevObject;
    }

    if (obj->flags & 1) {
        D_8013C2C0.unk_0C++;
        D_8013C2C0.elements[D_8013C2C0.unk_0C] = obj->modInst;
        D_8013C2C0.count++;

        if (obj->modInst->transforms != NULL) {
            mem_free(obj->modInst->transforms);
        }
    }

    D_8013C2B0.unk_0C++;
    D_8013C2B0.elements[D_8013C2B0.unk_0C] = obj;
    D_8013C2B0.count++;
}

// unused
void func_8002AF08(BatchInfo *arg0) {
    func_80012450(&arg0->transform);
}

// unused
void func_8002AF28(Batch *arg0) {
    u32 i;

    func_8002AF08(arg0->info);

    for (i = 0; i < arg0->info->header.numVertices; i++) {}
    for (i = 0; i < arg0->info->header.numTriangles; i++) {}
}

void func_8002AF8C(Object *obj) {
    u32 dxAbs, dzAbs;
    s32 temp2;
    Object *curr;

    for (curr = D_80052C50; curr != NULL; curr = curr->nextObject) {
        if (curr != obj && (obj->unk_07C & curr->unk_07A)) {
            dxAbs = ABS(obj->pos.x - curr->pos.x);
            dzAbs = ABS(obj->pos.z - curr->pos.z);
            temp2 = DISTANCE(dxAbs, dzAbs) - obj->unk_1FC - curr->unk_1FC;
            if (temp2 <= 0) {
                if (obj->unk_076 & 2) {
                    obj->unk_1E8(obj, curr);
                }
                if (curr->unk_076 & 2) {
                    curr->unk_1E8(curr, obj);
                }
                break;
            }
        }
    }
}

void obj_update_all(void) {
    Object *obj;
    Object *tempObj;
    ModelNodeRenderInfo *renderInfo;
    s32 s1;
    u32 i;
    u32 j;
    Batch *v0;
    u32 t2;
    s32 temp2;

    D_8013C4E8 = NULL;
    obj = D_80052C50;
    while (obj != NULL) {
        if (obj->unk_07C != 0) {
            func_8002AF8C(obj);
        }

        if ((obj->flags & 0x10) && !(obj->flags & 4)) {
            obj->flags |= 4;
        } else if (obj->flags & 0x10) {
            if (obj->unk_076 & 8) {
                obj->unk_078 |= 8;
                obj->unk_1E8(obj, NULL);
            }
            if (obj->flags & 0x20000000) {
                func_800345D8(obj->unk_208);
            }
            task_clear(obj->taskList);
            obj->taskList = NULL;
            tempObj = obj;
            obj = obj->nextObject;
            obj_delete(tempObj);
        } else {
            obj->fn_render(obj);
            obj = obj->nextObject;
        }
    }

    for (renderInfo = D_8013C4E8; renderInfo != NULL; renderInfo = renderInfo->next) {
        s1 = renderInfo->unk_04->unk_24;
        if (renderInfo->unk_04->unk_00) {
            for (i = 0; i < s1; i++) {
                if (renderInfo->flags & 1) {
                    continue;
                }
                v0 = renderInfo->unk_04->unk_28[i];
                t2 = renderInfo->unk_04->unk_38[i];
                for (j = 0; j < t2; j++) {
                    if (renderInfo->flags & 2) {
                        gSPTriBatch(gOverlayBatchPos, NULL, (j != 0) ? v0->info : renderInfo->unk_08[i], v0->vertices,
                                    v0->triangles);
                        v0++;
                    } else {
                        gSPTriBatch(gMainBatchPos, NULL, (j != 0) ? v0->info : renderInfo->unk_08[i], v0->vertices,
                                    v0->triangles);
                        v0++;
                    }
                }
            }
        } else {
            s32 temp = D_8005BFCE * s1;
            for (i = 0; i < s1; i++) {
                gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(renderInfo->unk_04->unk_28[i + temp]),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(renderInfo->unk_04->unk_48[i]));
            }
        }
    }
}

#ifdef NON_EQUIVALENT
void obj_init(Object *arg0, Vec4i *arg1, Vec3s *arg2, Transform *arg3, void (*arg4)(Object *)) {
    s16 i;

    func_80012A20(arg3, &arg0->transform, -2, -3);

    arg0->unk_076 = 0;
    arg0->unk_088.r = arg0->unk_088.g = arg0->unk_088.b = 160;

    arg0->unk_000.x = 0;
    arg0->unk_000.y = 0;
    arg0->unk_000.z = 0;

    arg0->unk_010.x = 0;
    arg0->unk_010.y = 0;
    arg0->unk_010.z = 0;

    arg0->unk_08C = arg0->unk_076;

    arg0->pos.x = arg1->x;
    arg0->pos.y = arg1->y;
    arg0->pos.z = arg1->z;

    arg0->rotation.x = arg2->x;
    arg0->rotation.y = arg2->y;
    arg0->rotation.z = arg2->z;

    arg0->unk_07A = 0;
    arg0->unk_07C = 0;
    arg0->unk_1FC = 0;

    arg0->unk_058 = 0x100;
    arg0->unk_05C = 0x100;
    arg0->unk_060 = 0x100;

    arg0->unk_078 = 0;
    arg0->spriteId = 0;
    arg0->unk_086 = -1;
    arg0->unk_088.a = 128;
    arg0->unk_1F8 = 0;
    arg0->unk_1FA = 0;

    arg0->taskList = (ObjectTask *) GET_ITEM(gTaskPool);
    arg0->currentTask = arg0->taskList;
    if (arg4 != NULL) {
        arg0->currentTask->counter = 0;
        arg0->currentTask->flags = 1;
        arg0->currentTask->func = arg4;
        arg0->currentTask->stackPos = 0;
    } else {
        arg0->currentTask->counter = 0;
        arg0->currentTask->flags = 1;
        arg0->currentTask->func = task_default_func;
        arg0->currentTask->stackPos = 0;
    }

    arg0->currentTask->next = 0;
    arg0->currentTask->stackPos = 0;

    math_rotate(&arg0->transform.local_matrix, arg2);
    math_translate(&arg0->transform.local_matrix, arg1);

    for (i = 0; i < 13; i++) {
        arg0->vars[i] = 0;
    }

    arg0->unk_200.r = arg0->unk_200.g = arg0->unk_200.b = 255;
    arg0->unk_204.r = arg0->unk_204.g = arg0->unk_204.b = arg0->unk_204.a = 0;
    arg0->unk_208 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/item/obj_init.s")
void obj_init(Object *arg0, Vec4i *arg1, Vec3s *arg2, Transform *arg3, void (*arg4)(Object *));
#endif

void func_8002B850(Object *obj, UnkSam *arg1) {
    ModelInstance *model;
    u32 s5;
    Transform *s7;
    Transform *v0;
    StructAA8 *s2;
    u32 i;
    s32 a3;

    model = obj->modInst;
    s5 = arg1->unk_128;
    s7 = &model->unk_010;

    func_80012A20(&obj->transform, s7, -1, -2);
    model->transforms = v0 = mem_alloc(s5 * sizeof(Transform), "item.c", 453);

    s2 = arg1->unk_150;
    model->unk_AA8 = &s2[1];
    model->unk_9E4.x = s2->x;
    model->unk_9E4.y = s2->y;
    model->unk_9E4.z = s2->z;
    math_translate(&model->unk_010.local_matrix, &model->unk_9E4);

    for (i = 0; i < s5; i++) {
        s2 = arg1->unk_150 + i + 1;
        a3 = s2->unk_00;
        if (a3 >= 0) {
            func_80012A20(&v0[a3], &v0[i], i, a3);
        } else {
            func_80012A20(s7, &v0[i], i, a3);
        }
        math_translate(&v0[i].local_matrix, &s2->x);
    }
}

Object *func_8002B9AC(Vec4i *arg0, char *arg1, K2Def *arg2, s32 arg3) {
    Object *obj;
    char sp78[20];
    ModelInstance *model;
    UnkFrodo *s5;

    if (arg1 == NULL) {
        obj = obj_allocate(arg2->unk_0A);
        str_copy(sp78, arg2->unk_00);
        obj_init(obj, arg0, &D_80049344, NULL, arg2->unk_04);
    } else {
        str_copy(sp78, arg1);
        if (arg2 != NULL) {
            obj = obj_allocate(arg2->unk_0A);
            obj_init(obj, arg0, &D_80049344, NULL, arg2->unk_04);
        } else {
            obj = obj_allocate(0x1000);
            obj_init(obj, arg0, &D_80049344, NULL, NULL);
        }
    }

    obj->fn_render = func_8003795C;
    obj->flags = 1;
    model = obj->modInst = mem_alloc(sizeof(ModelInstance), "item.c", 523);

    str_concat(sp78, ".kmd");
    s5 = model->unk_A24 = gAssets[asset_find(sp78, arg3)].aux_data;
    model->unk_A28 = NULL;
    model->numNodes = s5->sam.unk_128;

    if (s5->sam.unk_150 != NULL) {
        func_8002B850(obj, &s5->sam);
    } else {
        obj->modInst->transforms = NULL;
    }

    model->unk_12C = s5->sam.unk_148;
    model->unk_A2C = s5->unk_A64;

    if (arg2 != NULL && arg2->unk_0C != 0) {
        func_800352FC(model, arg2->unk_0C);
    } else {
        model->unk_604 = NULL;
    }

    return obj;
}

Object *create_worker(void (*fn_render)(Object *), s16 arg1) {
    Object *obj;

    obj = obj_allocate(arg1);
    obj_init(obj, &D_8004934C, &D_80049344, NULL, NULL);
    obj->fn_render = fn_render;
    obj->flags = 8;
    return obj;
}

Object *create_ui_element(Vec4i *pos, UIElement *def, s32 context) {
    Object *obj;

    obj = obj_allocate(def->unk_0C);
    obj_init(obj, pos, &D_80049344, NULL, def->func);
    obj->fn_render = func_80015724;
    obj->flags = def->flags;
    obj->flags |= 0x10000;
    obj->spriteId = def->spriteID;
    obj->sprite_map = gAssets[asset_find(def->map_name, context)].data;

    return obj;
}

#ifdef NON_MATCHING
Object *func_8002BC84(Vec4i *arg0, char *arg1, K2Def *arg2, u32 arg3) {
    Object *obj;
    char sp78[20];
    ModelInstance *model;
    UnkSam *s5;
    u32 s6;
    s32 i;

    if (arg1 == NULL) {
        obj = obj_allocate(arg2->unk_0A);
        str_copy(sp78, arg2->unk_00);
        obj_init(obj, arg0, &D_80049344, NULL, arg2->unk_04);
    } else {
        str_copy(sp78, arg1);
        if (arg2 != NULL) {
            obj = obj_allocate(arg2->unk_0A);
            obj_init(obj, arg0, &D_80049344, NULL, arg2->unk_04);
        } else {
            obj = obj_allocate(0x1000);
            obj_init(obj, arg0, &D_80049344, NULL, NULL);
        }
    }

    obj->fn_render = func_800386E8;
    obj->flags = 1;
    obj->modInst = (ModelInstance *) GET_ITEM(D_8013C2C0);

    model = obj->modInst;
    s5 = model->unk_A28 = gAssets[asset_find(sp78, arg3)].aux_data;
    model->unk_A24 = NULL;
    s6 = model->numNodes = s5->unk_128;

    for (i = 0; i < s6; i++) {
        memcpy(&model->unk_AB0[i].header, s5->batchInfos[i], sizeof(BatchHeader));
        memcpy(&model->unk_AB0[30 + i].header, s5->batchInfos[i], sizeof(BatchHeader));
        model->unk_1F50[i] = FALSE;
        model->unk_1F6E[i] = FALSE;
    }

    if (s5->unk_150 != NULL) {
        func_8002B850(obj, s5);
    } else {
        obj->modInst->transforms = NULL;
    }

    model->unk_12C = s5->unk_148;
    model->unk_A2C = s5->unk_234;
    model->unk_A0E = -1;

    if (arg2 != NULL && arg2->unk_0C != 0) {
        func_800359E4(model, arg2->unk_0C);
    } else {
        model->unk_604 = NULL;
    }

    obj->flags |= 0x40000;
    model->unk_A1C = model->unk_A20 = 0;
    return obj;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BC84.s")
Object *func_8002BC84(Vec4i *arg0, char *arg1, K2Def *arg2, u32 arg3);
#endif

Object *func_8002BF1C(Vec4i *arg0, UnkK2Def *arg1, s32 arg2) {
    Object *obj;
    ModelNode *new_var;

    if (D_8013C2C0.count >= 2) {
        obj = func_8002BC84(arg0, NULL, arg1, arg2);
        obj->fn_render = func_80037CE4;
        obj->spriteId = arg1->unk_14;
        obj->flags |= arg1->unk_10 | 2;
        obj->unk_088.a = 128;

        new_var = &obj->modInst->unk_A50;
        new_var->unk_00 = 1;
        new_var->unk_24 = 1;
        obj->modInst->unk_A30.unk_04 = new_var;
        if (obj->flags & 0x800) {
            obj->modInst->unk_A30.zOrder = -0x80000000;
        } else {
            obj->modInst->unk_A30.zOrder = 0x7FFFFFFF;
        }
        obj->modInst->unk_A30.flags = 0;
        return obj;
    } else {
        return NULL;
    }
}

Object *func_8002BFF0(Vec4i *arg0, s32 arg1, void (*arg2)(Object *), UnkSam *arg3) {
    u32 s6;
    Object *obj;
    ModelInstance *model;
    u32 i;
    s32 unused[5];

    obj = obj_allocate(arg1);
    obj_init(obj, arg0, &D_80049344, NULL, arg2);

    obj->fn_render = func_800386E8;
    obj->flags = 1;

    if (D_8013C2C0.count == 0) {
        obj->fn_render = task_default_func;
        obj->flags = 0x10;
        obj->modInst = NULL;
        return NULL;
    }

    obj->modInst = (ModelInstance *) GET_ITEM(D_8013C2C0);

    model = obj->modInst;
    model->unk_A28 = arg3;
    model->unk_A24 = NULL;
    s6 = model->numNodes = arg3->unk_128;

    for (i = 0; i < s6; i++) {
        memcpy(&model->unk_AB0[i].header, arg3->batchInfos[i], sizeof(BatchHeader));
        memcpy(&model->unk_AB0[30 + i].header, arg3->batchInfos[i], sizeof(BatchHeader));
        model->unk_1F50[i] = model->unk_5E4[i] = FALSE;
        model->unk_1F6E[i] = FALSE;
    }

    if (arg3->unk_150 != NULL) {
        func_8002B850(obj, arg3);
    } else {
        obj->modInst->transforms = NULL;
        func_80012A20(&obj->transform, &model->unk_010, -1, -2);
        model->unk_9E4.x = 0;
        model->unk_9E4.y = 0;
        model->unk_9E4.z = 0;
        math_translate(&model->unk_010.local_matrix, &model->unk_9E4);
    }

    model->unk_12C = arg3->unk_148;
    model->unk_A2C = arg3->unk_234;
    obj->flags |= 0x44000;
    model->unk_9C8 = s6;
    model->unk_604 = arg3->unk_31C;

    for (i = 0; i < model->unk_9C8; i++) {
        model->unk_608[i].unk_04 = &arg3->unk_31C[i];
    }

    model->unk_A0C = 0;
    model->unk_A1C = model->unk_A20 = 0;

    if (model->unk_12C != NULL) {
        func_80037500(obj);
    }

    if (arg3->unk_3CC & 1) {
        obj->flags |= 0x80000000;
    }

    return obj;
}

Object *func_8002C27C(Vec4i *arg0, s32 arg1, void (*arg2)(Object *), UnkSam *arg3) {
    Object *obj;
    ModelNode *new_var;

    if (D_8013C2C0.count == 0) {
        return NULL;
    }

    obj = func_8002BFF0(arg0, arg1, arg2, arg3);
    obj->fn_render = func_80037CE4;
    obj->spriteId = 0;
    obj->flags |= 0x6002;
    obj->unk_088.a = 128;

    new_var = &obj->modInst->unk_A50;
    new_var->unk_00 = 1;
    new_var->unk_24 = 1;
    obj->modInst->unk_A30.unk_04 = new_var;
    obj->modInst->unk_A30.zOrder = -9000;
    obj->modInst->unk_A30.flags = 0;
    return obj;
}
