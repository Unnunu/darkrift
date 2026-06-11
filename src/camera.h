#ifndef x_99c613fd
#define x_99c613fd
#include "common.h"

extern Object *gCamTargetObj;
extern x_acccb624 sCamEulerAngles;
extern x_f9704fd6 sCamLookAtMtx;
extern x_f9704fd6 sCamProjMtx;
extern x_f9704fd6 sCamViewProjMtx;
extern x_f9704fd6 sCamDefViewProjMtx;
extern x_88f11482 sCamLookAt;
extern s32 sCamUnkParam;
extern s32 sCamVertOffs;
extern s32 sCamHeightOffs;
extern s32 sCamAngleToTarget;
extern s32 sCamYaw;
extern u8 sCamFlag;
extern f32 sCamAngleCurr;
extern f32 sCamVertRatio;

void cam_init(Object *obj, x_a05f18ad *x_84ff873b);
void cam_calc_angle(s32 x_cc1d0de5, s32 x_84ff873b, s32 x_2092f891, s32 x_ee71e5cb);

#endif
