#include "common.h"
#include "camera.h"

extern s32 D_800492AC;
extern u8 D_80053020;

void func_80038AC0(GlobalObjB *arg0) {
    GlobalObjB *ptr;
    GlobalObjB *next;

    for (ptr = arg0; ptr != NULL; ptr = next) {
        next = ptr->next;
        RELEASE_ITEM(gGlobalObjBPool, ptr);
    }
}

void func_80038B10(Object *obj) {
    GlobalObjB *ptr;
    GlobalObjBSub *bsub;
    s16 v1;

    ptr = obj->unk_1F0;

    if (D_80053020) {
        return;
    }

    while (ptr != NULL) {
        obj->unk_1F4 = ptr;
        v1 = ptr->unk_00;

        if (((v1 & 4) && obj->unk_084 >= ptr->unk_86) || ((v1 & 8) && ptr->unk_86 < (D_800492AC & 0xFFFF)) ||
            ((v1 & 0x10) && (v1 & 0x20))) {
            GlobalObjBSub *unk_90 = &ptr->unk_90;

            if (ptr->unk_90.unk_00 & 0x40) {
                ptr->unk_24[ptr->unk_20].unk_04 = ptr->unk_04;
                ptr->unk_24[ptr->unk_20].unk_08 = ptr->unk_84;
                ptr->unk_24[ptr->unk_20].unk_00 = ptr->unk_00;
                ptr->unk_20++;
            } else {
                ptr->unk_20 = 0;
            }
            ptr->unk_04 = unk_90->unk_04;
            ptr->unk_00 = unk_90->unk_00;
            ptr->unk_84 = unk_90->unk_08;
        }

        if (v1 & 0x80) {
            bsub = ptr->unk_24;
            if (ptr->unk_20 != 0) {
                ptr->unk_20--;
                ptr->unk_04 = (bsub + ptr->unk_20)->unk_04;
                ptr->unk_00 = (bsub + ptr->unk_20)->unk_00;
                ptr->unk_84 = (bsub + ptr->unk_20)->unk_08;
            } else {
                ptr->unk_00 &= ~0x80;
                ptr->unk_84 = -1;
                continue;
            }
        }

        if (ptr->unk_84 != 0) {
            if (ptr->unk_84 < 0) {
                ptr = ptr->next;
            } else {
                ptr->unk_84--;
                ptr = ptr->next;
            }
        } else {
            if (ptr->unk_00 & 1) {
                ptr->unk_04(obj);
            }
            ptr = ptr->next;
        }
    }
}

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
