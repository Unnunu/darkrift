#include "camera.h"
#include "task.h"

s32 D_80053030[] = { 0 };

Object *gCamera;
s32 D_8013C564; // unused
Vec4i gCameraTarget;
f32 gCameraFieldOfView;
s32 D_8013C57C; // unused
s32 gCameraNearClip;
s32 gCameraFarClip;
s32 D_8013C588;
s32 gCameraHeading;
s32 gCameraPreviousHeading;
f32 D_8013C594;
f32 gCameraScale;
f32 D_8013C59C;
f32 D_8013C5A0;
Matrix4f gCameraViewMatrix;
Matrix4f gCameraPerspMatrix;
Matrix4f gCameraProjectionMatrix;
Vec3s D_8013C668;
Matrix4f D_8013C670;
Matrix4f D_8013C6B0;
Transform D_8013C6F0;
s32 D_8013C808[4];
Vec4i D_8013C818;
s32 D_8013C828;
s32 D_8013C82C;
s32 D_8013C830;
s8 D_8013C834;
s32 D_8013C838;

void func_80038E00(Object *obj, s32 arg1) {
    ModelInstance *model = obj->modInst;

    model->currentAnimId = 0;
    obj->unk_086 = model->unk_A0E = -1;
    obj->spriteId = 0;

    model->animations[0] = arg1;

    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -480;

    obj->pos.y = 0;
    obj->pos.z = 0;
    obj->pos.x = 0;

    obj->rotation.y = 0x400;

    model->nodePosition[1].x = 0;
    model->nodePosition[1].y = 0;
    model->nodePosition[1].z = 0;

    D_8013C818.x = D_8013C818.y = D_8013C818.z = 0;

    obj->modInst->numAnimFrames = 0x7FFF;
    gCameraFarClip = 11000;
}

void func_80038E8C(Object *obj, Vec3i *arg1, s32 arg2, s32 arg3) {
    ModelInstance *model = obj->modInst;

    model->unk_A0E = -1;
    model->currentAnimId = 0;
    obj->unk_086 = model->unk_A0E;

    obj->spriteId = 0;

    obj->modInst->numAnimFrames = 0x7FFF;

    model->animations[0] = arg3;

    obj->rotation.x = obj->rotation.z = 0;
    obj->rotation.y = arg2;

    obj->pos.x = arg1->x;
    obj->pos.y = arg1->y;
    obj->pos.z = arg1->z;

    gCameraTarget.x = arg1->x;
    gCameraTarget.z = arg1->z;
    gCameraTarget.y = -480;

    D_8013C818.x = arg1->x;
    D_8013C818.y = arg1->y;
    D_8013C818.z = arg1->z;

    gCameraFarClip = 11000;
}

void func_80038F34(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v1;
    f32 fv0;

    v1 = DISTANCE(arg2, arg3);
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

void camera_update(Object *obj) {
    s32 deltaX, deltaY, deltaZ;
    ModelInstance *model = obj->modInst;
    s32 unused2;
    u32 absDeltaX, absDeltaZ;
    s32 unused;
    Vec4i sp48;
    u32 sp3C;

    task_execute(obj);

    if (model->animations[0]) {
        if (model->currentAnimId != model->unk_A0E) {
            func_80037500(obj);
            model->unk_A0E = model->currentAnimId;
        }

        if (obj->spriteId != obj->unk_086) {
            func_800371C0(obj);
            func_8003635C(obj);
            obj->unk_086 = obj->spriteId;

            unused = model->nodePosition[0].x; // required to match
            if (unused != 0 || model->nodePosition[0].y != 0 || model->nodePosition[0].z != 0) {
                sp48.x = model->nodePosition[0].x;
                sp48.y = model->nodePosition[0].y;
                sp48.z = model->nodePosition[0].z;
                func_8001370C(&sp48, &obj->rotation);
                gCameraTarget.x = D_8013C818.x + sp48.x;
                gCameraTarget.y = D_8013C818.y + sp48.y;
                gCameraTarget.z = D_8013C818.z + sp48.z;
            }
        }

        obj->pos.y = model->unk_9D4.y;
    }

    guPerspectiveF(&gCameraPerspMatrix, &D_80080100->perspNorm, gCameraFieldOfView, 4.0f / 3.0f, gCameraNearClip,
                   gCameraFarClip, gCameraScale);

    if (obj->pos.x != 0 || obj->pos.z != 0 || gCameraTarget.x != 0 || gCameraTarget.z != 0) {
        guLookAtF(&gCameraViewMatrix, obj->pos.x, obj->pos.y + (f32) D_8013C830, obj->pos.z, gCameraTarget.x,
                  gCameraTarget.y + (f32) D_8013C830, gCameraTarget.z, 0.0f, -1.0f, 0.0f);
        math_mtxf_mul(&gCameraViewMatrix, &gCameraPerspMatrix, &gCameraProjectionMatrix);
    }

    math_mtxf2mtx(&D_80080100->mtxViewProj, &gCameraProjectionMatrix);

    deltaX = gCameraTarget.x - gCamera->pos.x;
    deltaY = gCameraTarget.y - gCamera->pos.y;
    deltaZ = gCameraTarget.z - gCamera->pos.z;

    gCameraPreviousHeading = gCameraHeading;
    gCameraHeading = func_80012518(deltaZ, deltaX);

    absDeltaX = ABS(deltaX);
    absDeltaZ = ABS(deltaZ);
    sp3C = DISTANCE(absDeltaX, absDeltaZ);
    D_8013C594 = (f32) deltaY / (f32) sp3C;
    func_80038F34(deltaX, deltaZ, absDeltaX, absDeltaZ);

    D_8013C668.y = -0xC00 - gCameraHeading;
    D_8013C668.x = -func_80012518(deltaY, sp3C);

    if (!(D_8008012C & 0x20) || model->animations[0]) {
        D_80081428 = D_8013C828;
        D_80049AE8 = D_8013C82C - (s32) (D_8013C830 * 0.2f);
    }
}

void camera_default_view(void) {
    s32 perspNorm;

    guPerspectiveF(&gCameraPerspMatrix, &perspNorm, gCameraFieldOfView, 4.0f / 3.0f, gCameraNearClip, gCameraFarClip,
                   gCameraScale);
    guLookAtF(&D_8013C670, 0.0f, 0.0f, -2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    math_mtxf_mul(&D_8013C670, &gCameraPerspMatrix, &D_8013C6B0);
}

Object *camera_create(void) {
    Object *obj;

    obj = obj_allocate(0x1200);

    obj->unk_000.x = obj->unk_000.y = obj->unk_000.z = 0;
    obj->unk_010.x = obj->unk_010.y = obj->unk_010.z = 0;
    obj->rotation.x = obj->rotation.y = obj->rotation.z = 0;

    obj->flags = 0x20;
    obj->unk_086 = -1;

    obj->taskList = (ObjectTask *) GET_ITEM(gTaskPool);
    obj->currentTask = obj->taskList;

    obj->currentTask->counter = 0;
    obj->currentTask->flags = 1;
    obj->currentTask->func = task_default_func;
    obj->currentTask->stackPos = 0;
    obj->currentTask->next = NULL;

    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -563;

    obj->pos.x = 0;
    obj->pos.y = -583;
    obj->pos.z = -2200;

    D_8013C588 = 180;
    gCameraNearClip = 600;
    gCameraFarClip = 11000;
    gCameraScale = 1.0f;
    gCameraFieldOfView = 30.0f;

    func_80012AA8(&gCameraViewMatrix);
    func_80012AA8(&gCameraPerspMatrix);

    obj->fn_render = camera_update;
    D_8013C668.z = 0;

    obj->modInst = mem_alloc(sizeof(ModelInstance), "camera.c", 247);
    obj->modInst->numNodes = 1;
    obj->modInst->transforms = &D_8013C6F0;
    obj->modInst->unk_AA8 = D_8013C808;

    func_80012A20(NULL, &obj->modInst->unk_010, -1, -2);
    func_80012A20(&obj->modInst->unk_010, obj->modInst->transforms, 0, -1);

    obj->modInst->unk_9E4.x = obj->modInst->unk_9E4.y = obj->modInst->unk_9E4.z = 0;
    obj->modInst->animations = D_80053030;
    D_80053030[0] = NULL;
    obj->modInst->unk_A20 = obj->modInst->unk_A1C = obj->modInst->unk_00C = 0;

    obj->flags |= 0x20400;
    obj->flags &= ~0x8000;

    obj->modInst->currentAnimId = obj->modInst->unk_A0E = -3;

    camera_default_view();

    obj->flags |= 0x20;
    D_8013C59C = D_8013C5A0 = 0.0f;
    D_8013C834 = 0;

    return obj;
}
