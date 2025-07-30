#include "common.h"

s32 D_80053030 = 0;

UnkItemAlpha D_8013C550;
Object *D_8013C560;
s32 D_8013C564; // unused
Vec4i D_8013C568;
f32 D_8013C578;
s32 D_8013C57C; // unused
s32 D_8013C580;
s32 D_8013C584;
s32 D_8013C588;
s32 D_8013C58C;
s32 D_8013C590;
f32 D_8013C594;
f32 D_8013C598;
f32 D_8013C59C;
f32 D_8013C5A0;
Matrix4f D_8013C5A8;
Matrix4f D_8013C5E8;
Matrix4f D_8013C628;
Vec3s D_8013C668;
Matrix4f D_8013C670;
Matrix4f D_8013C6B0;
UnkMu D_8013C6F0;
s32 D_8013C808[4];
Vec4i D_8013C818;
s32 D_8013C828;
s32 D_8013C82C;
s32 D_8013C830;
s8 D_8013C834;
s32 D_8013C838;

void func_80038E00(Object *obj, s32 arg1) {
    GlobalObjC *camera = obj->unk_0C8;

    camera->unk_A0C = 0;
    obj->unk_086 = camera->unk_A0E = -1;
    obj->spriteID = 0;

    *camera->unk_12C = arg1;

    D_8013C568.x = D_8013C568.z = 0;
    D_8013C568.y = -480;

    obj->unk_020.y = 0;
    obj->unk_020.z = 0;
    obj->unk_020.x = 0;

    obj->unk_050.y = 0x400;

    camera->unk_414 = 0;
    camera->unk_418 = 0;
    camera->unk_41C = 0;

    D_8013C818.x = D_8013C818.y = D_8013C818.z = 0;

    obj->unk_0C8->unk_A08 = 0x7FFF;
    D_8013C584 = 11000;
}

void func_80038E8C(Object *obj, Vec3i *arg1, s32 arg2, s32 arg3) {
    GlobalObjC *camera = obj->unk_0C8;

    camera->unk_A0E = -1;
    camera->unk_A0C = 0;
    obj->unk_086 = camera->unk_A0E;

    obj->spriteID = 0;

    obj->unk_0C8->unk_A08 = 0x7FFF;

    *camera->unk_12C = arg3;

    obj->unk_050.x = obj->unk_050.z = 0;
    obj->unk_050.y = arg2;

    obj->unk_020.x = arg1->x;
    obj->unk_020.y = arg1->y;
    obj->unk_020.z = arg1->z;

    D_8013C568.x = arg1->x;
    D_8013C568.z = arg1->z;
    D_8013C568.y = -480;

    D_8013C818.x = arg1->x;
    D_8013C818.y = arg1->y;
    D_8013C818.z = arg1->z;

    D_8013C584 = 11000;
}

void func_80038F34(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0;
    s32 v1;
    f32 fv0;

    if (arg2 < arg3) {
        v0 = arg2;
    } else {
        v0 = arg3;
    }

    v1 = (arg2 + arg3) - (v0 >> 1);
    D_8013C59C = D_8013C5A0;

    if (v1 != 0) {
        D_8013C5A0 = (f32) arg3 / (f32) v1;
        if (arg0 <= 0 && arg1 >= 0) {
            D_8013C5A0 = (1.0f - D_8013C5A0) + 1.0f;
        } else if (arg0 <= 0 && arg1 <= 0) {
            D_8013C5A0 += 2.0f;
        } else if (arg0 >= 0 && arg1 <= 0) {
            D_8013C5A0 = (1.0f - D_8013C5A0) + 3.0f;
        }

        fv0 = D_8013C5A0 - D_8013C59C;
        if (fv0 > 1.0f) {
            fv0 -= 4.0f;
        } else if (fv0 < -1.0f) {
            fv0 += 4.0f;
        }

        D_8013C838 = D_8013C828;
        D_8013C828 -= ROUND(fv0 * 700.0f);
        fv0 = -(D_8013C594 * 420.0f);
        D_8013C82C = (s32) (fv0 - 10.0f);
    }
}

void func_80039118(Object *obj) {
    s32 dx, dy, dz;
    GlobalObjC *s1 = obj->unk_0C8;
    u32 a2, a3, v0;
    s32 unused;
    Vec4i sp48;
    u32 sp3C;
    s32 unused2;

    func_80038B10(obj);

    if (*s1->unk_12C) {
        if (s1->unk_A0C != s1->unk_A0E) {
            func_80037500(obj);
            s1->unk_A0E = s1->unk_A0C;
        }

        if (obj->spriteID != obj->unk_086) {
            func_800371C0(obj);
            func_8003635C(obj);
            obj->unk_086 = obj->spriteID;

            unused = s1->unk_404.x; // required to match
            if (unused != 0 || s1->unk_404.y != 0 || s1->unk_404.z != 0) {
                sp48.x = s1->unk_404.x;
                sp48.y = s1->unk_404.y;
                sp48.z = s1->unk_404.z;
                func_8001370C(&sp48, &obj->unk_050);
                D_8013C568.x = D_8013C818.x + sp48.x;
                D_8013C568.y = D_8013C818.y + sp48.y;
                D_8013C568.z = D_8013C818.z + sp48.z;
            }
        }

        obj->unk_020.y = s1->unk_9D8;
    }

    guPerspectiveF(&D_8013C5E8, &D_80080100->unk_12080, D_8013C578, 4.0f / 3.0f, D_8013C580, D_8013C584, D_8013C598);

    if (obj->unk_020.x != 0 || obj->unk_020.z != 0 || D_8013C568.x != 0 || D_8013C568.z != 0) {
        guLookAtF(&D_8013C5A8, obj->unk_020.x, obj->unk_020.y + (f32) D_8013C830, obj->unk_020.z, D_8013C568.x,
                  D_8013C568.y + (f32) D_8013C830, D_8013C568.z, 0.0f, -1.0f, 0.0f);
        func_800149F0(&D_8013C5A8, &D_8013C5E8, &D_8013C628);
    }

    func_80013A54(&D_80080100->unk_00, &D_8013C628);

    dx = D_8013C568.x - D_8013C560->unk_020.x;
    dy = D_8013C568.y - D_8013C560->unk_020.y;
    dz = D_8013C568.z - D_8013C560->unk_020.z;

    D_8013C590 = D_8013C58C;
    D_8013C58C = func_80012518(dz, dx);

    if (dx > 0) {
        a2 = dx;
    } else {
        a2 = -dx;
    }
    if (dz > 0) {
        a3 = dz;
    } else {
        a3 = -dz;
    }
    if (a2 < a3) {
        v0 = a2;
    } else {
        v0 = a3;
    }

    sp3C = (a2 + a3) - (v0 >> 1);
    D_8013C594 = (f32) dy / (f32) sp3C;
    func_80038F34(dx, dz, a2, a3);

    D_8013C668.y = -0xC00 - D_8013C58C;
    D_8013C668.x = -func_80012518(dy, sp3C);

    if (!(D_8008012C & 0x20) || *s1->unk_12C) {
        D_80081428 = D_8013C828;
        D_80049AE8 = D_8013C82C - (s32) (D_8013C830 * 0.2f);
    }
}

void func_8003950C(void) {
    s32 perspNorm;

    guPerspectiveF(&D_8013C5E8, &perspNorm, D_8013C578, 4.0f / 3.0f, D_8013C580, D_8013C584, D_8013C598);
    guLookAtF(&D_8013C670, 0.0f, 0.0f, -2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    func_800149F0(&D_8013C670, &D_8013C5E8, &D_8013C6B0);
}

Object *func_800395D4(void) {
    Object *obj;

    obj = obj_allocate(0x1200);

    obj->unk_000.x = obj->unk_000.y = obj->unk_000.z = 0;
    obj->unk_010.x = obj->unk_010.y = obj->unk_010.z = 0;
    obj->unk_050.x = obj->unk_050.y = obj->unk_050.z = 0;

    obj->flags = 0x20;
    obj->unk_086 = -1;

    obj->unk_1F0 = (GlobalObjB *) GET_ITEM(D_8013C550);
    obj->unk_1F4 = obj->unk_1F0;

    obj->unk_1F4->unk_84 = 0;
    obj->unk_1F4->unk_00 = 1;
    obj->unk_1F4->unk_04 = func_80038DE0;
    obj->unk_1F4->unk_20 = 0;
    obj->unk_1F4->unk_9C = 0;

    D_8013C568.x = D_8013C568.z = 0;
    D_8013C568.y = -563;

    obj->unk_020.x = 0;
    obj->unk_020.y = -583;
    obj->unk_020.z = -2200;

    D_8013C588 = 180;
    D_8013C580 = 600;
    D_8013C584 = 11000;
    D_8013C598 = 1.0f;
    D_8013C578 = 30.0f;

    func_80012AA8(&D_8013C5A8);
    func_80012AA8(&D_8013C5E8);

    obj->fn_update = func_80039118;
    D_8013C668.z = 0;

    obj->unk_0C8 = mem_alloc(sizeof(GlobalObjC), "camera.c", 247);
    obj->unk_0C8->unk_000 = 1;
    obj->unk_0C8->unk_128 = &D_8013C6F0;
    obj->unk_0C8->unk_AA8 = D_8013C808;

    func_80012A20(NULL, &obj->unk_0C8->unk_010, -1, -2);
    func_80012A20(&obj->unk_0C8->unk_010, obj->unk_0C8->unk_128, 0, -1);

    obj->unk_0C8->unk_9E4.x = obj->unk_0C8->unk_9E4.y = obj->unk_0C8->unk_9E4.z = 0;
    obj->unk_0C8->unk_12C = &D_80053030;
    D_80053030 = FALSE;
    obj->unk_0C8->unk_A20 = obj->unk_0C8->unk_A1C = obj->unk_0C8->unk_00C = 0;

    obj->flags |= 0x20400;
    obj->flags &= ~0x8000;

    obj->unk_0C8->unk_A0C = obj->unk_0C8->unk_A0E = -3;

    func_8003950C();

    obj->flags |= 0x20;
    D_8013C59C = D_8013C5A0 = 0.0f;
    D_8013C834 = 0;

    return obj;
}
