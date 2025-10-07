#ifndef _CAMERA_H
#define _CAMERA_H
#include "common.h"

extern Object *gCamera;
extern Vec3s D_8013C668;
extern Matrix4f gCameraViewMatrix;
extern Matrix4f gCameraPerspMatrix;
extern Matrix4f gCameraProjectionMatrix;
extern Matrix4f D_8013C6B0;
extern Vec4i gCameraTarget;
extern s32 D_8013C588;
extern s32 D_8013C82C;
extern s32 D_8013C830;
extern s32 gCameraHeading;
extern s32 D_8013C828;
extern u8 D_8013C834;
extern f32 D_8013C5A0;
extern f32 D_8013C594;

void func_80038E00(Object *obj, AnimHeader **arg1);
void func_80038F34(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif
