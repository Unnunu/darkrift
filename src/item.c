#include "common.h"

typedef struct UnkObjectDef {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ void (*unk_04)(Object *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkObjectDef;

#define GET_ITEM(array)             \
    array.elements[array.unk_0C--]; \
    array.count--;

extern UnkItemAlpha D_8013C2B0;
extern UnkItemAlpha D_8013C2C0;
extern UnkItemAlpha D_8013C550;

extern Vec3s D_80049344;
extern Vec3i D_8004934C;
extern Object *D_80052C50;
extern s32 D_80052C54;

void func_80038DE0(Object *arg0);

void func_8002A8C0(UnkItemAlpha *arg0, u32 count, u32 element_size) {
    s16 i;
    u8 *buffer;

    arg0->elements = (u8 **) mem_alloc(count * 4, "item.c", 23);
    arg0->buffer = (u8 *) mem_alloc(element_size * count, "item.c", 24);
    func_80000E0C(arg0->buffer, 0, count * element_size);
    arg0->count = count;
    arg0->unk_0C = count - 1;

    buffer = arg0->buffer;
    for (i = 0; i < count; i++) {
        arg0->elements[i] = buffer + i * element_size;
    }
}

void func_8002A994(UnkItemAlpha *arg0, u32 count, u32 element_size) {
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
    func_8002A994(&D_8013C550, count, sizeof(GlobalObjB));
}

void func_8002AC10(void) {
    func_8002A8C0(&D_8013C2B0, 50, sizeof(Object));
    func_8002A8C0(&D_8013C2C0, 16, sizeof(GlobalObjC));
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

void func_8002ADFC(Object *obj) {
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

    if (obj->unk_080 & 1) {
        D_8013C2C0.unk_0C++;
        D_8013C2C0.elements[D_8013C2C0.unk_0C] = obj->unk_0C8;
        D_8013C2C0.count++;

        if (obj->unk_0C8->unk_128 != NULL) {
            mem_free(obj->unk_0C8->unk_128);
        }
    }

    D_8013C2B0.unk_0C++;
    D_8013C2B0.elements[D_8013C2B0.unk_0C] = obj;
    D_8013C2B0.count++;
}

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002AF08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002AF28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002AF8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002B0AC.s")

#ifdef NON_EQUIVALENT
void func_8002B658(Object *arg0, Vec3i *arg1, Vec3s *arg2, UnkMu *arg3, void (*arg4)(Object *)) {
    s16 i;

    func_80012A20(arg3, &arg0->unk_0D0, -2, -3);

    arg0->unk_076 = 0;
    arg0->unk_088.r = arg0->unk_088.g = arg0->unk_088.b = 160;

    arg0->unk_000 = 0;
    arg0->unk_004 = 0;
    arg0->unk_008 = 0;

    arg0->unk_010 = 0;
    arg0->unk_014 = 0;
    arg0->unk_018 = 0;

    arg0->unk_08C = arg0->unk_076;

    arg0->unk_020.x = arg1->x;
    arg0->unk_020.y = arg1->y;
    arg0->unk_020.z = arg1->z;

    arg0->unk_050.x = arg2->x;
    arg0->unk_050.y = arg2->y;
    arg0->unk_050.z = arg2->z;

    arg0->unk_07A = 0;
    arg0->unk_07C = 0;
    arg0->unk_1FC = 0;

    arg0->unk_058 = 0x100;
    arg0->unk_05C = 0x100;
    arg0->unk_060 = 0x100;

    arg0->unk_078 = 0;
    arg0->unk_084 = 0;
    arg0->unk_086 = -1;
    arg0->unk_088.a = 128;
    arg0->unk_1F8 = 0;
    arg0->unk_1FA = 0;

    arg0->unk_1F0 = (GlobalObjB *) GET_ITEM(D_8013C550);
    arg0->unk_1F4 = arg0->unk_1F0;
    if (arg4 != NULL) {
        arg0->unk_1F4->unk_84 = 0;
        arg0->unk_1F4->unk_00 = 1;
        arg0->unk_1F4->unk_04 = arg4;
        arg0->unk_1F4->unk_20 = 0;
    } else {
        arg0->unk_1F4->unk_84 = 0;
        arg0->unk_1F4->unk_00 = 1;
        arg0->unk_1F4->unk_04 = func_80038DE0;
        arg0->unk_1F4->unk_20 = 0;
    }

    arg0->unk_1F4->unk_9C = 0;
    arg0->unk_1F4->unk_20 = 0;

    func_8001305C(&arg0->unk_0D0.unk_98, arg2);
    func_800136CC(&arg0->unk_0D0.unk_98, arg1);

    for (i = 0; i < 13; i++) {
        arg0->unk_090[i] = 0;
    }

    arg0->unk_200.r = arg0->unk_200.g = arg0->unk_200.b = 255;
    arg0->unk_204.r = arg0->unk_204.g = arg0->unk_204.b = arg0->unk_204.a = 0;
    arg0->unk_208 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002B658.s")
void func_8002B658(Object *arg0, Vec3i *arg1, Vec3s *arg2, UnkMu *arg3, void (*arg4)(Object *));
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002B850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002B9AC.s")

Object *func_8002BB6C(void (*arg0)(Object *), s16 arg1) {
    Object *obj;

    obj = obj_allocate(arg1);
    func_8002B658(obj, &D_8004934C, &D_80049344, NULL, NULL);
    obj->unk_1EC = arg0;
    obj->unk_080 = 8;
    return obj;
}

Object *func_8002BBD4(s32 arg0, UnkObjectDef *arg1, s32 arg2) {
    Object *obj;

    obj = obj_allocate(arg1->unk_0C);
    func_8002B658(obj, arg0, &D_80049344, NULL, arg1->unk_04);
    obj->unk_1EC = func_80015724;
    obj->unk_080 = arg1->unk_08;
    obj->unk_080 |= 0x10000;
    obj->unk_084 = arg1->unk_00;
    obj->unk_0C4 = gAssets[asset_find(arg1->unk_10, arg2)].data;

    return obj;
}

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BC84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BF1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002C27C.s")
