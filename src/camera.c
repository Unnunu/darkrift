#include "camera.h"
#include "task.h"

// void model_update_animated_params(Object *);

x_a05f18ad *sNullAnimTable[] = { NULL };

Object *gCamTargetObj;
s32 D_8013C564; // unused
x_88f11482 sCamLookAt;
f32 sCamFov;
s32 D_8013C57C; // unused
s32 sCamNearClip;
s32 sCamFarClip;
s32 sCamUnkParam;
s32 sCamAngleToTarget;
s32 sCamPrevAngle;
f32 sCamVertRatio;
f32 sCamScale;
f32 sCamAnglePrev;
f32 sCamAngleCurr;
x_f9704fd6 sCamLookAtMtx;
x_f9704fd6 sCamProjMtx;
x_f9704fd6 sCamViewProjMtx;
x_acccb624 sCamEulerAngles;
x_f9704fd6 sCamDefLookAtMtx;
x_f9704fd6 sCamDefViewProjMtx;
Transform sCamTransform;
x_43bd08ed sCamUnkStruct;
x_88f11482 sCamBasePos;
s32 sCamYaw;
s32 sCamVertOffs;
s32 sCamHeightOffs;
u8 sCamFlag;
s32 sCamPrevYaw;

void cam_init(Object *obj, x_a05f18ad *x_ec23cef0) {
    x_6fcfcf46 *x_20d20338 = obj->x_20d20338;

    x_20d20338->x_ee205ef9 = 0;
    obj->x_2b06a023 = x_20d20338->x_2f4c4ce1 = -1;
    obj->frameCounter = 0;

    x_20d20338->x_50771dcd[0] = x_ec23cef0;

    sCamLookAt.x = sCamLookAt.z = 0;
    sCamLookAt.y = -480;

    obj->pos.y = 0;
    obj->pos.z = 0;
    obj->pos.x = 0;

    obj->x_224610f1.y = 0x400;

    x_20d20338->x_5d0e77f6[1].x = 0;
    x_20d20338->x_5d0e77f6[1].y = 0;
    x_20d20338->x_5d0e77f6[1].z = 0;

    sCamBasePos.x = sCamBasePos.y = sCamBasePos.z = 0;

    obj->x_20d20338->x_8e601526 = 0x7FFF;
    sCamFarClip = 11000;
}

void cam_init_pos(Object *obj, x_88f11482 *x_84ff873b, s32 x_2092f891, x_a05f18ad *x_ee71e5cb) {
    x_6fcfcf46 *model = obj->x_20d20338;

    model->x_2f4c4ce1 = -1;
    model->x_ee205ef9 = 0;
    obj->x_2b06a023 = model->x_2f4c4ce1;

    obj->frameCounter = 0;

    obj->x_20d20338->x_8e601526 = 0x7FFF;

    model->x_50771dcd[0] = x_ee71e5cb;

    obj->x_224610f1.x = obj->x_224610f1.z = 0;
    obj->x_224610f1.y = x_2092f891;

    obj->pos.x = x_84ff873b->x;
    obj->pos.y = x_84ff873b->y;
    obj->pos.z = x_84ff873b->z;

    sCamLookAt.x = x_84ff873b->x;
    sCamLookAt.z = x_84ff873b->z;
    sCamLookAt.y = -480;

    sCamBasePos.x = x_84ff873b->x;
    sCamBasePos.y = x_84ff873b->y;
    sCamBasePos.z = x_84ff873b->z;

    sCamFarClip = 11000;
}

void cam_calc_angle(s32 x_cc1d0de5, s32 x_84ff873b, s32 x_2092f891, s32 x_ee71e5cb) {
    s32 v1;
    f32 fv0;

    v1 = x_4a9e7834(x_2092f891, x_ee71e5cb);
    sCamAnglePrev = sCamAngleCurr;

    if (v1 != 0) {
        sCamAngleCurr = (f32) x_ee71e5cb / (f32) v1;
        if (x_cc1d0de5 <= 0 && x_84ff873b >= 0) {
            sCamAngleCurr = (1.0f - sCamAngleCurr) + 1.0f;
        } else if (x_cc1d0de5 <= 0 && x_84ff873b <= 0) {
            sCamAngleCurr += 2.0f;
        } else if (x_cc1d0de5 >= 0 && x_84ff873b <= 0) {
            sCamAngleCurr = (1.0f - sCamAngleCurr) + 3.0f;
        }

        fv0 = sCamAngleCurr - sCamAnglePrev;
        if (fv0 > 1.0f) {
            fv0 -= 4.0f;
        } else if (fv0 < -1.0f) {
            fv0 += 4.0f;
        }

        sCamPrevYaw = sCamYaw;
        sCamYaw -= ROUND(fv0 * 700.0f);
        fv0 = -(sCamVertRatio * 420.0f);
        sCamVertOffs = (s32) (fv0 - 10.0f);
    }
}

void cam_frame_update(Object *obj) {
    s32 x_2bef91d9, x_86fee161, x_2dffbf44;
    x_6fcfcf46 *model = obj->x_20d20338;
    s32 x_f0d1d935;
    u32 x_f5463fa4, x_98e2dc09;
    s32 unused;
    x_88f11482 x_f10a928a;
    u32 x_d16311d7;

    task_execute(obj);

    if (model->x_50771dcd[0] != NULL) {
        if (model->x_ee205ef9 != model->x_2f4c4ce1) {
            model_anim_load(obj);
            model->x_2f4c4ce1 = model->x_ee205ef9;
        }

        if (obj->frameCounter != obj->x_2b06a023) {
            model_anim_tick(obj);
            model_transforms_update(obj);
            obj->x_2b06a023 = obj->frameCounter;

            if (model->x_5d0e77f6[0].x != 0 || model->x_5d0e77f6[0].y != 0 || model->x_5d0e77f6[0].z != 0) {
                x_f10a928a.x = model->x_5d0e77f6[0].x;
                x_f10a928a.y = model->x_5d0e77f6[0].y;
                x_f10a928a.z = model->x_5d0e77f6[0].z;
                vec_rotate_by_euler(&x_f10a928a, &obj->x_224610f1);
                sCamLookAt.x = sCamBasePos.x + x_f10a928a.x;
                sCamLookAt.y = sCamBasePos.y + x_f10a928a.y;
                sCamLookAt.z = sCamBasePos.z + x_f10a928a.z;
            }
        }

        obj->pos.y = model->x_6689336b.y;
    }

    guPerspectiveF(&sCamProjMtx, &D_80080100->perspNorm, sCamFov, 4.0f / 3.0f, sCamNearClip, sCamFarClip, sCamScale);

    if (obj->pos.x != 0 || obj->pos.z != 0 || sCamLookAt.x != 0 || sCamLookAt.z != 0) {
        guLookAtF(&sCamLookAtMtx, obj->pos.x, obj->pos.y + (f32) sCamHeightOffs, obj->pos.z, sCamLookAt.x,
                  sCamLookAt.y + (f32) sCamHeightOffs, sCamLookAt.z, 0.0f, -1.0f, 0.0f);
        mat4_mul_general(&sCamLookAtMtx, &sCamProjMtx, &sCamViewProjMtx);
    }

    mat4_to_mtx(&D_80080100->x_0f39faa7, &sCamViewProjMtx);

    x_2bef91d9 = sCamLookAt.x - gCamTargetObj->pos.x;
    x_86fee161 = sCamLookAt.y - gCamTargetObj->pos.y;
    x_2dffbf44 = sCamLookAt.z - gCamTargetObj->pos.z;

    sCamPrevAngle = sCamAngleToTarget;
    sCamAngleToTarget = atan2_lut(x_2dffbf44, x_2bef91d9);

    x_f5463fa4 = ABS(x_2bef91d9);
    x_98e2dc09 = ABS(x_2dffbf44);
    x_d16311d7 = x_4a9e7834(x_f5463fa4, x_98e2dc09);
    sCamVertRatio = (f32) x_86fee161 / (f32) x_d16311d7;
    cam_calc_angle(x_2bef91d9, x_2dffbf44, x_f5463fa4, x_98e2dc09);

    sCamEulerAngles.y = -0xC00 - sCamAngleToTarget;
    sCamEulerAngles.x = -atan2_lut(x_86fee161, x_d16311d7);

    if (!(gGfxFlags & GFX_MENU_OVERLAY) || model->x_50771dcd[0]) {
        D_80081428 = sCamYaw;
        x_6c647b3a = sCamVertOffs - (s32) (sCamHeightOffs * 0.2f);
    }
}

void cam_reset_mtx(void) {
    s32 perspNorm;

    guPerspectiveF(&sCamProjMtx, &perspNorm, sCamFov, 4.0f / 3.0f, sCamNearClip, sCamFarClip, sCamScale);
    guLookAtF(&sCamDefLookAtMtx, 0.0f, 0.0f, -2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    mat4_mul_general(&sCamDefLookAtMtx, &sCamProjMtx, &sCamDefViewProjMtx);
}

Object *cam_create(void) {
    Object *obj;

    obj = obj_alloc(0x1200);

    obj->x_8da078cc.x = obj->x_8da078cc.y = obj->x_8da078cc.z = 0;
    obj->velocity.x = obj->velocity.y = obj->velocity.z = 0;
    obj->x_224610f1.x = obj->x_224610f1.y = obj->x_224610f1.z = 0;

    obj->flags = x_4271d4b5;
    obj->x_2b06a023 = -1;

    obj->taskListHead = (TaskNode *) x_6d619dce(gTaskPool);
    obj->currentTask = obj->taskListHead;
    obj->currentTask->delay = 0;
    obj->currentTask->flags = TASK_RUNNABLE;
    obj->currentTask->callback = task_remove_current;
    obj->currentTask->stackPtr = 0;
    obj->currentTask->next = NULL;

    sCamLookAt.x = sCamLookAt.z = 0;
    sCamLookAt.y = -563;

    obj->pos.x = 0;
    obj->pos.y = -583;
    obj->pos.z = -2200;

    sCamUnkParam = 180;
    sCamNearClip = 600;
    sCamFarClip = 11000;
    sCamScale = 1.0f;
    sCamFov = 30.0f;

    mat4_ident(&sCamLookAtMtx);
    mat4_ident(&sCamProjMtx);

    obj->x_0232396f = cam_frame_update;
    sCamEulerAngles.z = 0;

    obj->x_20d20338 = mem_alloc_debug(sizeof(x_6fcfcf46), "camera.c", 247);
    obj->x_20d20338->x_6dcce206 = 1;
    obj->x_20d20338->transforms = &sCamTransform;
    obj->x_20d20338->x_0094fc88 = &sCamUnkStruct;

    transform_init_node(NULL, &obj->x_20d20338->x_abd7b3c4, -1, -2);
    transform_init_node(&obj->x_20d20338->x_abd7b3c4, obj->x_20d20338->transforms, 0, -1);

    obj->x_20d20338->x_9cfd7bb4.x = obj->x_20d20338->x_9cfd7bb4.y = obj->x_20d20338->x_9cfd7bb4.z = 0;
    obj->x_20d20338->x_50771dcd = sNullAnimTable;
    sNullAnimTable[0] = NULL;
    obj->x_20d20338->x_713417ac = obj->x_20d20338->x_3aefae96 = obj->x_20d20338->x_6786034d.z = 0;

    obj->flags |= x_03ae0e9e | x_9ee447da;
    obj->flags &= ~x_56bbd9b2;

    obj->x_20d20338->x_ee205ef9 = obj->x_20d20338->x_2f4c4ce1 = -3;

    cam_reset_mtx();

    obj->flags |= x_4271d4b5;
    sCamAnglePrev = sCamAngleCurr = 0.0f;
    sCamFlag = FALSE;

    return obj;
}
