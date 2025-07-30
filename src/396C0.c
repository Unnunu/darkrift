#include "common.h"
#include "camera.h"

void func_80038AC0(GlobalObjB *arg0) {
    GlobalObjB *ptr;
    GlobalObjB *next;

    for (ptr = arg0; ptr != NULL; ptr = next) {
        next = ptr->next;
        RELEASE_ITEM(gGlobalObjBPool, ptr);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/396C0/func_80038B10.s")

GlobalObjB *func_80038D14(GlobalObjB *arg0, s16 arg1) {
    GlobalObjB *ptr;
    for (ptr = arg0; ptr != NULL; ptr = ptr->next) {
        if (ptr->unk_88 == arg1) {
            return ptr;
        }
    }
}

GlobalObjB *func_80038D50(Object *obj, void (*arg1)(Object *), s16 arg2) {
    GlobalObjB *a0;
    GlobalObjB *v0;
    GlobalObjB *newObjB;

    v0 = obj->unk_1F0;
    newObjB = (GlobalObjB *) GET_ITEM(gGlobalObjBPool);

    while (v0 != NULL) {
        a0 = v0;
        v0 = v0->next;
    }

    a0->next = newObjB;
    newObjB->next = NULL;

    newObjB->unk_88 = a0->unk_88 + 1;
    newObjB->unk_20 = 0;
    newObjB->unk_04 = arg1;
    newObjB->unk_00 = arg2;
    newObjB->unk_84 = 0;

    return newObjB;
}

void func_80038DE0(Object *obj) {
    obj->unk_1F4->unk_00 |= 0x80;
}
