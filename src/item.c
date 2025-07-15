#include "common.h"

#define GET_ITEM(array)             \
    array.elements[array.unk_0C--]; \
    array.count--;

extern UnkItemAlpha D_8013C2B0;
extern UnkItemAlpha D_8013C2C0;
extern UnkItemAlpha D_8013C550;

extern GlobalObjA *D_80052C50;
extern s32 D_80052C54;

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
    func_8002A994(&D_8013C2B0, count, sizeof(GlobalObjA));
    func_8002A994(&D_8013C550, count, sizeof(GlobalObjB));
}

void func_8002AC10(void) {
    func_8002A8C0(&D_8013C2B0, 50, sizeof(GlobalObjA));
    func_8002A8C0(&D_8013C2C0, 16, sizeof(GlobalObjC));
    D_80052C50 = NULL;
    D_80052C54 = 0;
}

#ifdef NON_MATCHING
GlobalObjA *func_8002AC5C(s16 arg0) {
    GlobalObjA *obj;
    GlobalObjA *prev_obj;

    D_80052C54++;
    if (D_8013C2B0.unk_0C <= 0) {
        return NULL;
    }

    if (D_80052C50 == NULL) {
        obj = D_80052C50 = (GlobalObjA *) GET_ITEM(D_8013C2B0);

        obj->prevObject = NULL;
        obj->nextObject = NULL;
    } else {
        obj = D_80052C50;

        while (obj != NULL && obj->unk_074 >= arg0) {
            prev_obj = obj;
            obj = obj->nextObject;
        }

        if (obj == NULL) {
            prev_obj->nextObject = (GlobalObjA *) GET_ITEM(D_8013C2B0);

            obj = prev_obj->nextObject;
            obj->prevObject = prev_obj;
            obj->nextObject = NULL;
        } else if (obj->prevObject == NULL) {
            obj = (GlobalObjA *) GET_ITEM(D_8013C2B0);

            obj->nextObject = D_80052C50;
            D_80052C50->prevObject = obj;
            D_80052C50 = obj;
            obj->prevObject = NULL;
        } else {
            prev_obj = (GlobalObjA *) GET_ITEM(D_8013C2B0);

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
#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002AC5C.s")
GlobalObjA *func_8002AC5C(s16 arg0);
#endif

void func_8002ADFC(GlobalObjA *obj) {
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
        D_8013C2C0.elements[D_8013C2C0.unk_0C] = obj->camera;
        D_8013C2C0.count++;

        if (obj->camera->unk_128 != NULL) {
            mem_free(obj->camera->unk_128);
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

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002B658.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002B850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002B9AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BB6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BBD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BC84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BF1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002BFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/item/func_8002C27C.s")
