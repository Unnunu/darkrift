#include "common.h"
#include "camera.h"
#include "task.h"

s32 sCamDeadZone = 170;
s32 sCamZoomDeadZone = 500;
s32 D_80052C68_unused[] = { 0, 0xFFFFFE20, 0xFFFFF704, 0 };
s32 sZoomDecelThreshold = 0x400;
s32 sZoomSpeedMaxAccum = 0x480000;
s32 sZoomAccel = 0x1C000;
s32 sZoomDecel = 0x20000;
s32 sZoomMomentumMin = 0x100000;
s32 sZoomMomentumCur = 0;
s32 sPanDeadZone = 200;
s32 sPanSpeedMaxAccum = 0x240000;
s32 sPanAccel = 0x2000;
s32 sPanDecel = 0xE000;
s32 sPanMomentumMin = 0x40000;
s32 sPanMomentumCur = 0;
s32 D_80052CA8_unused = 0;
s32 sRotStep = 0x400;
s8 sRotDeltaCur = 0;
u8 sZoomSettled = FALSE;
s32 sHitZoomAccum = 0;
s32 sHitHeightAdj = 0;
s32 sHitScrollTimer = 0;
s32 sHitScrollStep = 0x8000;
s32 sHitScrollAccum = 0;
char *sCutsceneFilename = "opencamX.oc";

Vec4i sSavedCamPos;
Vec4i sSavedCamTarget;
s16 D_8013C300;
s16 D_8013C302;
s16 D_8013C304;
f32 D_8013C308;
s32 D_8013C30C_unused;
Vec4i D_8013C310;
Vec4i D_8013C320;
s16 D_8013C330_unused;
s16 D_8013C332;
s16 D_8013C334;
s16 D_8013C336;
f32 D_8013C338;
s16 D_8013C33C;
s16 D_8013C33E;
s32 sOrbitAngle;
s32 sOrbitHeightMul;
s32 sOrbitRadiusMul;
s32 sOrbitRadius;
s32 sOrbitMaxZoomOut;
s32 sZoomFromDistRatio;
s32 sZoomYOffsetMul;
s32 sCamBaseY;
s32 sCamHeightMul;
s32 sBgScrollYmul;
s32 D_8013C368_unused;
s32 D_8013C36C_unused;
s32 D_8013C370;
s32 D_8013C374_unused;
s32 D_8013C378_unused;
s32 sRotVelCap;
s32 sRotAccum;
s32 sRotDecelTimer;
s16 D_8013C388_unused;
s16 sShakeSpeed;
s16 sShakeHeightDelta;
s16 sShakeDistDelta;
s32 D_8013C390_unused;

s32 func_80012854(s32 arg0);

void camera_battle_update(Object *obj);
void camera_orbit_update(Object *obj, u8 arg1);
void camera_push_players_apart(u8 arg0);

s32 abs(s32 arg0) {
    return arg0 < 0 ? -arg0 : arg0;
}

s32 abs2(s32 arg0) {
    return arg0 < 0 ? -arg0 : arg0;
}

void camera_save_state(void) {
    D_8013C320.x = gCameraTarget.x;
    D_8013C320.y = gCameraTarget.y;
    D_8013C320.z = gCameraTarget.z;

    D_8013C310.x = gCamera->pos.x;
    D_8013C310.y = gCamera->pos.y;
    D_8013C310.z = gCamera->pos.z;

    D_8013C332 = gBgScrollX;
    D_8013C334 = gBgScrollY;
    D_8013C336 = D_8013C828;
    D_8013C338 = D_8013C5A0;

    if (gCurrentGameMode <= GAME_MODE_17) {
        D_8008012C |= GFX_FLAG_1;
    }
}

void camera_save_target_pos(void) {
    D_8013C302 = gBgScrollX;

    sSavedCamTarget.x = gCameraTarget.x;
    sSavedCamTarget.y = gCameraTarget.y;
    sSavedCamTarget.z = gCameraTarget.z;

    sSavedCamPos.x = gCamera->pos.x;
    sSavedCamPos.y = gCamera->pos.y;
    sSavedCamPos.z = gCamera->pos.z;

    D_8013C300 = gBgScrollY;
    D_8013C304 = D_8013C828;
    D_8013C308 = D_8013C5A0;
}

void camera_cutscene_playback(Object *obj) {

    camera_save_target_pos();

    obj->pos.x = D_8013C310.x;
    obj->pos.y = D_8013C310.y;
    obj->pos.z = D_8013C310.z;

    gCameraTarget.x = D_8013C320.x;
    gCameraTarget.y = D_8013C320.y;
    gCameraTarget.z = D_8013C320.z;

    gBgScrollX = D_8013C332;
    gBgScrollY = D_8013C334;
    D_8013C828 = D_8013C336;
    D_8013C5A0 = D_8013C338;

    camera_orbit_update(obj, FALSE);
    camera_save_state();

    if (obj->modInst->animations[0] != NULL) {
        obj->frameIndex++;
        if (obj->frameIndex >= obj->modInst->numAnimFrames - 1) {
            obj->modInst->animations[0] = NULL;
            if (!gRoundOver || D_80080234 == 0) {
                obj->currentTask->func = camera_battle_update;
                obj->currentTask->start_delay = 1;
                D_8008012C &= ~GFX_FLAG_1;
                gPlayers[PLAYER_1].obj->flags &= ~OBJ_FLAG_200000;
                gPlayers[PLAYER_2].obj->flags &= ~OBJ_FLAG_200000;
                return;
            }
            sCutsceneAnimDone = TRUE;
        }
    }

    D_8008012C &= ~GFX_FLAG_20;

    obj->pos.x = sSavedCamPos.x;
    obj->pos.y = sSavedCamPos.y;
    obj->pos.z = sSavedCamPos.z;

    gCameraTarget.x = sSavedCamTarget.x;
    gCameraTarget.y = sSavedCamTarget.y;
    gCameraTarget.z = sSavedCamTarget.z;

    gBgScrollY = D_8013C300 - (s32) (sPostCutsceneZoom * 0.2f);
    gBgScrollX = 0;
    D_8013C828 = D_8013C304;
    D_8013C5A0 = D_8013C308;
}

void camera_outro_playback(Object *obj) {

    camera_cutscene_playback(obj);

    if (obj->frameIndex >= obj->modInst->numAnimFrames - 1 || (gPlayerInput[PLAYER_1].buttons & INP_START) ||
        (gPlayerInput[PLAYER_2].buttons & INP_START)) {
        if (gPlayMode != PLAY_MODE_PRACTICE) {
            func_80017CA8();
        } else {
            gPlayers[PLAYER_1].flags &= ~PLAYER_FLAG_100000;
            gPlayers[PLAYER_2].flags &= ~PLAYER_FLAG_100000;
            gGlobalFlags &= ~GAME_FLAG_4;
        }

        gBgScrollX = 0;
        D_8013C828 = D_8013C304;
        D_8013C5A0 = D_8013C308;

        camera_orbit_update(obj, FALSE);

        obj->currentTask->func = camera_battle_update;
        obj->modInst->animations[0] = NULL;
        gPlayerInput[PLAYER_1].pendingInput = gPlayerInput[PLAYER_2].pendingInput = FALSE;
        D_8008012C &= ~(GFX_FLAG_1 | GFX_FLAG_10);
    }

    gPlayers[PLAYER_1].obj->flags |= OBJ_FLAG_200000;
    gPlayers[PLAYER_2].obj->flags |= OBJ_FLAG_200000;
}

void camera_debug_control(Object *obj) {
    u32 v0;

    v0 = gPlayerInput[PLAYER_1].buttons;

    gPlayers[PLAYER_1].flags |= PLAYER_FLAG_100000;
    gPlayers[PLAYER_2].flags |= PLAYER_FLAG_100000;

    if (v0 & INP_R) {
        D_8013C588 -= 10;
    } else if (v0 & INP_CUP) {
        gCameraTarget.y -= 10;
    } else if (v0 & INP_CDOWN) {
        gCameraTarget.y += 10;
    } else if (v0 & INP_CLEFT) {
        obj->pos.z -= 10;
    } else if (v0 & INP_CRIGHT) {
        obj->pos.z += 10;
    } else if (v0 & INP_L) {
        D_8013C588 += 10;
    } else if (v0 & INP_UP) {
        obj->pos.y += 10;
    } else if (v0 & INP_DOWN) {
        obj->pos.y -= 10;
    } else if (v0 & INP_B) {
        obj->pos.z += 10;
    } else if (v0 & INP_A) {
        obj->pos.z -= 10;
    } else if (v0 & INP_R) {
        gPlayers[PLAYER_1].obj->pos.x = -1600;
        gPlayers[PLAYER_2].obj->pos.x = 1600;
    } else if (v0 & INP_L) {
        gPlayers[PLAYER_1].obj->pos.x = -400;
        gPlayers[PLAYER_2].obj->pos.x = 400;
    }
}

void camera_debug_light_control(Object *obj) {
    u32 temp1;
    u32 v1;
    u32 a1;
    GlobalLighting *v0;

    v0 = gGameModes[gCurrentGameMode].unk_18;
    temp1 = gPlayerInput[PLAYER_1].buttons;
    v1 = temp1 & 0xFFFF;
    a1 = temp1 >> 16;
    temp1 = v1;

    if (temp1 != 0 || a1 != 0) {
        switch (temp1) {
            case 0x80:
                obj->pos.x = -2000;
                obj->pos.z = 0;
                break;
            case 0x20:
                obj->pos.x = 2000;
                obj->pos.z = 0;
                break;
            case 0x10:
                obj->pos.x = 20;
                obj->pos.z = 20;
                obj->pos.y = -2000;
                break;
            case 0x40:
                obj->pos.x = 0;
                obj->pos.z = -2000;
                break;
        }

        switch (a1) {
            case 0x80:
                v0->lights[0].dir_x = -127;
                v0->lights[0].dir_z = 0;
                break;
            case 0x20:
                v0->lights[0].dir_x = 127;
                v0->lights[0].dir_z = 0;
                break;
            case 0x10:
                v0->lights[0].dir_x = 0;
                v0->lights[0].dir_z = 127;
                break;
            case 0x40:
                v0->lights[0].dir_x = 0;
                v0->lights[0].dir_z = -127;
                break;
        }
    }
}

void camera_debug_init(Object *obj) {
    obj->pos.x = 0;
    obj->pos.y = -480;
    obj->pos.z = -2300;
    gCameraTarget.y = -480;
    D_8013C588 = 597;
    obj->currentTask->func = camera_debug_control;
}

void camera_update_player_facing(void) {
    Object *player1;
    Object *player2;
    s16 sp26;

    player1 = gPlayerObjects[PLAYER_1];
    player2 = gPlayerObjects[PLAYER_2];
    D_8013C33C = (0xC00 - player1->rotation.y) & 0xFFF;
    D_8013C33E = (0xC00 - player2->rotation.y) & 0xFFF;

    if (abs(angle_diff(gPlayerAngle, D_8013C33C)) < 0x400) {
        ((Player *) player1->varObj[0])->flags |= PLAYER_FLAG_NOT_FACING_OPP;
        ((Player *) player1->varObj[0])->flags &= ~PLAYER_FLAG_200;
    } else {
        sp26 = angle_diff(gPlayerAngle - 0x800, D_8013C33C);
        if (abs(sp26) > 140) {
            if (sp26 < 0) {
                sp26 = -140;
            } else {
                sp26 = 140;
            }
        }

        if (!(((Player *) player1->varObj[0])->flags & (PLAYER_FLAG_10 | PLAYER_FLAG_20000 | PLAYER_FLAG_400000))) {
            player1->rotation.y = 0xC00 - D_8013C33C - sp26;
        }

        if ((gPlayers[PLAYER_1].unk_DBC = abs(sp26)) < 8) {
            ((Player *) player1->varObj[0])->flags |= PLAYER_FLAG_200;
        } else {
            ((Player *) player1->varObj[0])->flags &= ~PLAYER_FLAG_200;
        }
        ((Player *) player1->varObj[0])->flags &= ~PLAYER_FLAG_NOT_FACING_OPP;
    }

    if (abs(angle_diff(gPlayerAngle, D_8013C33E)) < 0x400) {
        sp26 = angle_diff(gPlayerAngle, D_8013C33E);
        if (abs(sp26) > 140) {
            if (sp26 < 0) {
                sp26 = -140;
            } else {
                sp26 = 140;
            }
        }

        if (!(((Player *) player2->varObj[0])->flags & (PLAYER_FLAG_10 | PLAYER_FLAG_20000 | PLAYER_FLAG_400000))) {
            player2->rotation.y = 0xC00 - D_8013C33E - sp26;
        }

        if ((gPlayers[PLAYER_2].unk_DBC = abs(sp26)) < 8) {
            ((Player *) player2->varObj[0])->flags |= PLAYER_FLAG_200;
        } else {
            ((Player *) player2->varObj[0])->flags &= ~PLAYER_FLAG_200;
        }
        ((Player *) player2->varObj[0])->flags &= ~PLAYER_FLAG_NOT_FACING_OPP;
    } else {
        ((Player *) player2->varObj[0])->flags |= PLAYER_FLAG_NOT_FACING_OPP;
        ((Player *) player2->varObj[0])->flags &= ~PLAYER_FLAG_200;
    }
}

s32 lerp16(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0 -= arg1;
    arg0 = (arg0 * arg3) >> 16;
    return arg2 + arg0;
}

s16 angle_diff(s16 arg0, s16 arg1) {
    s16 v1;

    v1 = (arg0 & 0xFFF) - (arg1 & 0xFFF);
    if (v1 > 0x800) {
        v1 -= 0x1000;
    }
    if (v1 < -0x800) {
        v1 += 0x1000;
    }
    return v1;
}

void camera_shift_world(s32 arg0, s32 arg1) {
    Object *obj;

    for (obj = gObjectList; obj != NULL; obj = obj->nextObject) {
        if (!(obj->flags & OBJ_FLAG_UIELEMENT)) {
            obj->pos.x += arg0;
            obj->pos.z += arg1;
            math_sync_transforms(&obj->transform);
        }
    }

    gPlayers[PLAYER_1].rightHandTrail.segmentCount = gPlayers[PLAYER_1].leftHandTrail.segmentCount =
        gPlayers[PLAYER_1].leftLegTrail.segmentCount = gPlayers[PLAYER_1].rightLegTrail.segmentCount =
            gPlayers[PLAYER_2].rightHandTrail.segmentCount = gPlayers[PLAYER_2].leftHandTrail.segmentCount =
                gPlayers[PLAYER_2].leftLegTrail.segmentCount = gPlayers[PLAYER_2].rightLegTrail.segmentCount = 0;

    spline_interpolator_init(&gPlayers[PLAYER_1].rightHandTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_1].rightHandTrail.splineA);
    spline_interpolator_init(&gPlayers[PLAYER_1].leftHandTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_1].leftHandTrail.splineA);
    spline_interpolator_init(&gPlayers[PLAYER_1].leftLegTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_1].leftLegTrail.splineA);
    spline_interpolator_init(&gPlayers[PLAYER_1].rightLegTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_1].rightLegTrail.splineA);
    spline_interpolator_init(&gPlayers[PLAYER_2].rightHandTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_2].rightHandTrail.splineA);
    spline_interpolator_init(&gPlayers[PLAYER_2].leftHandTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_2].leftHandTrail.splineA);
    spline_interpolator_init(&gPlayers[PLAYER_2].leftLegTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_2].leftLegTrail.splineA);
    spline_interpolator_init(&gPlayers[PLAYER_2].rightLegTrail.splineB);
    spline_interpolator_init(&gPlayers[PLAYER_2].rightLegTrail.splineA);
}

s32 camera_wrapping_post_render(void *arg0) {
    s32 a3, a1;

    a3 = gCamera->vars[3];
    a1 = gCamera->vars[4];

    if (gCameraTarget.x > 0x2300 || gCamera->pos.x > 0x2300 || gCameraTarget.x < -0x2300 || gCamera->pos.x < -0x2300 ||
        gCameraTarget.z > 0x2300 || gCamera->pos.z > 0x2300 || gCameraTarget.z < -0x2300 || gCamera->pos.z < -0x2300) {

        gCameraTarget.x += a3;
        gCameraTarget.z += a1;
        camera_shift_world(a3, a1);
        if (gCamera->pos.x != 0 || gCamera->pos.z != 0 || gCameraTarget.x != 0 || gCameraTarget.z != 0) {
            guLookAtF(&gCameraViewMatrix, gCamera->pos.x, gCamera->pos.y, gCamera->pos.z, gCameraTarget.x,
                      gCameraTarget.y, gCameraTarget.z, 0.0f, -1.0f, 0.0f);
            math_mtxf_mul(&gCameraViewMatrix, &gCameraPerspMatrix, &gCameraProjectionMatrix);
        }
    }
    return 0;
}

s32 camera_reset_origin(s32 arg0) {
    camera_shift_world(-gCameraTarget.x, -gCameraTarget.z);
    gCameraTarget.x = gCameraTarget.z = 0;
    return 0;
}

void camera_check_bounds(Object *obj) {
    s32 a2, a3;

    a2 = 0;
    a3 = 0;

    if (gCameraTarget.x > 0x2300 || obj->pos.x > 0x2300) {
        a2 = -0x2800;
    } else if (gCameraTarget.x < -0x2300 || obj->pos.x < -0x2300) {
        a2 = 0x2800;
    }

    if (gCameraTarget.z > 0x2300 || obj->pos.z > 0x2300) {
        a3 = -0x2800;
    } else if (gCameraTarget.z < -0x2300 || obj->pos.z < -0x2300) {
        a3 = 0x2800;
    }

    if (a2 != 0 || a3 != 0) {
        obj->vars[3] = a2;
        obj->vars[4] = a3;
        set_post_render_hook(camera_wrapping_post_render, NULL);
    }
}

void camera_orbit_update(Object *obj, u8 arg1) {
    s32 pad1[3];
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 pad2[3];
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s32 pad3[4];
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    s32 v02;
    s32 a0;
    s32 dx, dy, dz;
    u32 dxAbs, dzAbs;
    s32 temp2;
    s32 sp78;
    Vec4i sp68;
    Vec4s sp60;
    s32 pad5[4];
    f32 ft5;
    s32 temp;

    if (gReplayActive == 0) {
        D_8008012C |= GFX_FLAG_20;
    } else {
        D_8008012C &= ~GFX_FLAG_20;
    }

    camera_push_players_apart(FALSE);

    if (gPlayerDistance > 800) {
        spC0 = ((gPlayerDistance - 800) * sZoomFromDistRatio) >> 0x10;
    } else {
        spC0 = 0;
    }
    if (spC0 > sOrbitMaxZoomOut) {
        spC0 = sOrbitMaxZoomOut;
    }

    obj->vars[2] = spC0 = ((spC0 - obj->vars[2]) ^ 0) + obj->vars[2]; // @fake ^ 0
    spD8 = obj->vars[1];

    v02 = angle_diff(gPlayerAngle, spD8);
    if (v02 < 0) {
        a0 = v02 + sRotStep;
    } else {
        a0 = v02 - sRotStep;
    }
    obj->vars[1] = temp = spD8 + a0;

    camera_update_player_facing();
    if (angle_diff(gPlayerAngle, spD8) > 0) {
        gPlayerObjects[PLAYER_1]->flags &= ~OBJ_FLAG_200;
        gPlayerInput[PLAYER_1].mirrored = FALSE;
        gPlayerObjects[PLAYER_2]->flags |= OBJ_FLAG_200;
        gPlayerInput[PLAYER_2].mirrored = TRUE;
    } else {
        gPlayerObjects[PLAYER_1]->flags |= OBJ_FLAG_200;
        gPlayerInput[PLAYER_1].mirrored = TRUE;
        gPlayerObjects[PLAYER_2]->flags &= ~OBJ_FLAG_200;
        gPlayerInput[PLAYER_2].mirrored = FALSE;
    }

    gCameraTarget.y = ((sCamHeightMul * spC0) >> 0x10) + sHitHeightAdj - 480;
    spD4 = ((gPlayerPos2->x + gPlayerPos1->x) >> 1) - gCameraTarget.x;
    spD0 = ((gPlayerPos2->z + gPlayerPos1->z) >> 1) - gCameraTarget.z;
    gCameraTarget.x += spD4;
    gCameraTarget.z += spD0;

    spBC = ((func_80012854(temp) * sOrbitRadius) >> 12) + gCameraTarget.x;
    spB8 = ((-func_80012854(temp + 0x400) * sOrbitRadius) >> 12) + gCameraTarget.z;
    spA4 = (func_80012854(temp) * sOrbitRadiusMul) >> 12;
    spA0 = (-func_80012854(temp + 0x400) * sOrbitRadiusMul) >> 12;
    sp9C = (spC0 * sOrbitHeightMul) >> 12;

    obj->pos.x = ((spC0 * spA4) >> 12) + spBC;
    obj->pos.z = ((spC0 * spA0) >> 12) + spB8;
    obj->pos.y = sCamBaseY + sHitZoomAccum - sp9C;

    if (spD4 != 0 || spD0 != 0) {
        sp68.x = spD4;
        sp68.z = -spD0;
        sp60.y = (0x400 - gCameraHeading) & 0xFFF;
        sp60.x = sp60.z = 0;
        math_rotate_vector(&sp68, &sp60);
        if (sp68.x > 0) {
            sp78 = (u32) (sqrtf(SQ(spD4) + SQ(spD0)) + 0.5) >> 1;
        } else if (sp68.x < 0) {
            sp78 = -((u32) (sqrtf(SQ(spD4) + SQ(spD0)) + 0.5) >> 1);
        }
        gBgScrollX += sp78;
    }

    dx = gCameraTarget.x - gCamera->pos.x;
    dy = gCameraTarget.y - gCamera->pos.y;
    dz = gCameraTarget.z - gCamera->pos.z;
    dxAbs = ABS(dx);
    dzAbs = ABS(dz);
    ft5 = FAST_HYPOT(dxAbs, dzAbs);
    D_8013C594 = dy / ft5;

    func_80038F34(dx, dz, dxAbs, dzAbs);

    gBgScrollY = D_8013C82C;
    if (spC0 > 1500) {
        gBgScrollY += (sBgScrollYmul * (spC0 - 1500)) >> 0x10;
        if (obj->vars || obj->vars) {} // @fake
    }
    D_80081428 = D_8013C828;

    if (arg1) {
        camera_check_bounds(obj);
        if (obj->pos.x != 0 || obj->pos.z != 0 || gCameraTarget.x != 0 || gCameraTarget.z != 0) {
            guLookAtF(&gCameraViewMatrix, obj->pos.x, obj->pos.y, obj->pos.z, gCameraTarget.x, gCameraTarget.y,
                      gCameraTarget.z, 0.0f, -1.0f, 0.0f);
            math_mtxf_mul(&gCameraViewMatrix, &gCameraPerspMatrix, &gCameraProjectionMatrix);
        }
    }
}

void camera_orbit_init(Object *obj) {
    gCameraTarget.y = -480;
    sOrbitAngle = func_80012518(899, 5045);
    sOrbitHeightMul = -func_80012854(sOrbitAngle + 0x400);
    sOrbitRadiusMul = func_80012854(sOrbitAngle);
    sOrbitRadius = 2300;
    sOrbitMaxZoomOut = -5045;
    sOrbitMaxZoomOut = (u32) (sqrtf(SQ(sOrbitMaxZoomOut) + SQ(1379)) + 0.5);
    sZoomFromDistRatio = (sOrbitMaxZoomOut << 16) / 2400;
    sZoomYOffsetMul = (-347 << 16) / sOrbitMaxZoomOut;
    sCamHeightMul = (-400 << 16) / sOrbitMaxZoomOut;
    sBgScrollYmul = (12 << 16) / sOrbitMaxZoomOut;
    D_8013C36C_unused = 291271;
    sCamBaseY = -480;
    gPlayerPos1 = &gPlayers[PLAYER_1].obj->pos;
    gPlayerPos2 = &gPlayers[PLAYER_2].obj->pos;

    obj->vars[1] = 0xC00;
    obj->vars[2] = 0;
    camera_orbit_update(obj, FALSE);
    sPostCutsceneZoom = 0;
    obj->pos.x = 0;
    obj->pos.z = -2300;
    obj->pos.y = -480;
    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -480;
    sHitScrollTimer = sHitZoomAccum = sHitHeightAdj = 0;
}

void camera_intro_playback(Object *obj) {
    gBgScrollY = D_8013C82C;
    D_80081428 = D_8013C828;

    if ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START)) {
        if (gPlayMode != PLAY_MODE_PRACTICE) {
            func_80017CA8();
        } else {
            gPlayers[PLAYER_1].flags &= ~PLAYER_FLAG_100000;
            gPlayers[PLAYER_2].flags &= ~PLAYER_FLAG_100000;
            gGlobalFlags &= ~GAME_FLAG_4;
        }

        gBgScrollX = 0;
        D_8013C828 = D_8013C304;
        D_8013C5A0 = D_8013C308;

        camera_orbit_update(obj, FALSE);

        obj->currentTask->func = camera_battle_update;
        obj->modInst->animations[0] = NULL;
        gPlayerInput[PLAYER_1].pendingInput = gPlayerInput[PLAYER_2].pendingInput = FALSE;
        D_8008012C &= ~(GFX_FLAG_1 | GFX_FLAG_10);
    } else {
        if (--obj->vars[10] <= 0) {
            obj->currentTask->func = camera_outro_playback;
        }
    }
}

void camera_intro_start(Object *obj) {
    s32 assetId;
    char sp18[20];

    camera_orbit_init(obj);
    camera_save_state();

    str_copy(sp18, sCutsceneFilename);
    sp18[7] = '1' + sCutsceneVariant;
    assetId = asset_find(sp18, CONTEXT_ABAB);
    camera_set_animation(gCamera, (AnimHeader *) gAssets[assetId].data);
    gCamera->currentTask->func = camera_intro_playback;
    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->start_delay = 1;
    gCamera->vars[10] = 60;
    gPlayerInput[PLAYER_1].pendingInput = assetId = gPlayerInput[PLAYER_2].pendingInput = FALSE; // required to match
}

void camera_outro_start(Object *obj) {
    s32 assetId;
    char sp18[20];

    camera_orbit_init(obj);
    camera_save_state();

    str_copy(sp18, sCutsceneFilename);
    sp18[7] = '1' + sCutsceneVariant;
    assetId = asset_find(sp18, CONTEXT_ABAB);
    camera_set_animation(gCamera, (AnimHeader *) gAssets[assetId].data);
    gCamera->currentTask->func = camera_outro_playback;
    gCamera->currentTask->start_delay = 0;
    gCamera->currentTask->flags = TASK_FLAG_ENABLED;
    gCamera->currentTask->start_delay = 1;
    gPlayerInput[PLAYER_1].pendingInput = assetId = gPlayerInput[PLAYER_2].pendingInput = FALSE; // required to match
}

#ifdef NON_EQUIVALENT
void camera_push_players_apart(u8 arg0) {
    s16 s6;
    s16 s1;
    s32 v1, v0;
    u8 s0;
    s16 s3;
    s16 lo;
    s16 s4;
    Player *temp = gPlayers;

restart:
    D_800801F4 = D_80080200;
    D_800801F8 = D_80080204;

    D_80080200 = gPlayerPos1->x - gPlayerPos2->x;
    D_80080208 = -MIN(gPlayerPos1->y, gPlayerPos2->y);
    D_80080204 = gPlayerPos1->z - gPlayerPos2->z;

    s6 = func_80012518(D_80080204, D_80080200);
    if (D_80080200 != 0 || D_80080204 != 0) {
        s1 = (u32) (sqrtf(SQ(D_80080200) + SQ(D_80080204)) + 0.5);
    } else {
        s1 = 0;
    }

    if ((gPlayers[PLAYER_1].flags & PLAYER_FLAG_400000) || (gPlayers[PLAYER_2].flags & PLAYER_FLAG_400000) ||
        (gPlayers[PLAYER_1].flags & PLAYER_FLAG_1000000) ||
        (gPlayers[PLAYER_2].flags & PLAYER_FLAG_1000000) && s1 < 3200) { // @bug?
        D_8008021C = gPlayerAngle;
        gPlayerAngle = s6;
        gPlayerDistance = s1;
        return;
    }

    v1 = MIN(temp[PLAYER_1].hitZones.rightFootPos->y, temp[PLAYER_1].hitZones.leftFootPos->y);
    v0 = MIN(temp[PLAYER_2].hitZones.rightFootPos->y, temp[PLAYER_2].hitZones.leftFootPos->y);

    if (v1 < v0) {
        s0 = (temp[PLAYER_2].hitZones.headPos->y - 200.0f) < v1;
    } else {
        s0 = (temp[PLAYER_1].hitZones.headPos->y - 200.0f) < v0;
    }

    if ((gPlayers[PLAYER_1].combatState->flags & CSF_80000) || (gPlayers[PLAYER_2].combatState->flags & CSF_80000)) {
        s0 = TRUE;
    }

    if (!arg0 && s0 && abs(angle_diff(s6, gPlayerAngle)) > 0x200) {
        s4 = (s1 + 280) >> 1;

        s3 = (func_80012854(s6) * s4) >> 12;
        lo = ((-func_80012854(s6 + 0x400)) * s4) >> 12;
        gPlayerPos1->x -= s3;
        gPlayerPos1->z -= lo;

        s3 = (func_80012854(s6) * s4) >> 12;
        lo = ((-func_80012854(s6 + 0x400)) * s4) >> 12;
        gPlayerPos2->x += s3;
        gPlayerPos2->z += lo;

        arg0 = TRUE;
        goto restart;
    }

    if (s1 < D_80080214 &&
        (!(gPlayers[PLAYER_1].flags & PLAYER_FLAG_8000) || (gPlayers[PLAYER_2].flags & PLAYER_FLAG_8000))) { // @bug ??
        s4 = D_80080214 - s1;
        if ((gPlayers[PLAYER_1].combatState->flags & CSF_80000) ||
            (gPlayers[PLAYER_2].combatState->flags & CSF_80000) || (gPlayers[PLAYER_1].flags & PLAYER_FLAG_4000000) ||
            (gPlayers[PLAYER_2].flags & PLAYER_FLAG_4000000)) {
            s4 >>= 1;
        }
    } else {
        if (s1 > 3200) {
            s4 = 3200 - s1;
        } else {
            s4 = 0;
        }
    }

    D_8008021C = gPlayerAngle;
    gPlayerAngle = s6;
    gPlayerDistance = s1 + s4;

    if (s4 != 0 && (s0 || s1 > 3200)) {
        s4 >>= 1;
        s3 = (func_80012854(gPlayerAngle) * s4) >> 12;
        lo = (-func_80012854(gPlayerAngle + 0x400) * s4) >> 12;
        gPlayerPos1->x += s3;
        gPlayerPos1->z += lo;
        gPlayerPos2->x -= s3;
        gPlayerPos2->z -= lo;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/opencam/camera_push_players_apart.s")
void camera_push_players_apart(u8);
#endif

void camera_project_to_screen(Vec4i *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 x, y, z;
    f32 temp;
    x = arg0->x;
    z = arg0->z;
    y = arg0->y;
    *arg2 = 0;
    *arg1 = 0;
    *arg3 = 0;

    if (*gCamera->modInst->animations == 0) {
        *arg1 = gCameraProjectionMatrix.x.x * x + gCameraProjectionMatrix.y.x * y + gCameraProjectionMatrix.z.x * z +
                gCameraProjectionMatrix.w.x;
        *arg2 = gCameraProjectionMatrix.x.y * x + gCameraProjectionMatrix.y.y * y + gCameraProjectionMatrix.z.y * z +
                gCameraProjectionMatrix.w.y;
        temp = gCameraProjectionMatrix.x.w * x + gCameraProjectionMatrix.y.w * y + gCameraProjectionMatrix.z.w * z +
               gCameraProjectionMatrix.w.w;
        if (temp != 0) {
            *arg1 /= temp;
            *arg2 /= temp;
            if (*arg1 < 0) {
                *arg3 = -*arg1;
            } else {
                *arg3 = *arg1;
            }
        }
    }
}

void camera_cutscene_shake(Object *obj) {
    s32 pad[2];
    s32 sp44;
    u32 ft4;
    s16 a1;
    s16 sp3E;
    Vec4i sp2C = { -200, 0, 0, 0 };

    sCutsceneAnimDone = FALSE;

    if (gCameraTarget.x > sp2C.x) {
        if (gCameraTarget.x - 5 > sp2C.x) {
            gCameraTarget.x = gCameraTarget.x - 5;
        } else {
            gCameraTarget.x = sp2C.x;
        }
    } else if (gCameraTarget.x < sp2C.x) {
        if (gCameraTarget.x + 5 < sp2C.x) {
            gCameraTarget.x = gCameraTarget.x + 5;
        } else {
            gCameraTarget.x = sp2C.x;
        }
    }

    if (gCameraTarget.z > sp2C.z) {
        if (gCameraTarget.z - 5 > sp2C.z) {
            gCameraTarget.z = gCameraTarget.z - 5;
        } else {
            gCameraTarget.z = sp2C.z;
        }
    } else if (gCameraTarget.z < sp2C.z) {
        if (gCameraTarget.z + 5 < sp2C.z) {
            gCameraTarget.z = gCameraTarget.z + 5;
        } else {
            gCameraTarget.z = sp2C.z;
        }
    }

    ft4 = sqrtf(SQ(obj->pos.x - gCameraTarget.x) + SQ(obj->pos.z - gCameraTarget.z)) + 0.5;
    a1 = obj->vars[1];
    a1 = (a1 + sShakeSpeed) & 0xFFF;
    obj->vars[1] = sp3E = a1;
    sp44 = (s32) ft4 + sShakeDistDelta;
    if (sShakeDistDelta > 0 && sp44 > 1800) {
        sShakeDistDelta = -sShakeDistDelta;
    }
    if (sShakeDistDelta < 0 && sp44 < 1500) {
        sShakeDistDelta = -sShakeDistDelta;
    }

    obj->pos.x = ((func_80012854(sp3E) * sp44) >> 12) + gCameraTarget.x;
    obj->pos.z = (((-func_80012854(sp3E + 0x400)) * sp44) >> 12) + gCameraTarget.z;
    obj->pos.y += sShakeHeightDelta;
    if (sShakeHeightDelta > 0 && obj->pos.y > -360) {
        sShakeHeightDelta = -sShakeHeightDelta;
    }
    if (sShakeHeightDelta < 0 && obj->pos.y < -1200) {
        sShakeHeightDelta = -sShakeHeightDelta;
    }
}

void camera_cutscene_shake_start(Object *obj, s32 arg1) {
    s32 sp24;
    s32 sp20;

    sp24 = obj->pos.x - gCameraTarget.x;
    sp20 = obj->pos.z - gCameraTarget.z;
    sShakeSpeed = (guRandom() % 2) + 2;
    sShakeHeightDelta = -1;
    sShakeDistDelta = (guRandom() % 2) + 1;
    obj->currentTask->func = camera_cutscene_shake;
    obj->currentTask->start_delay = 0;
    obj->vars[3] = arg1;
    obj->vars[1] = func_80012518(sp20, sp24);
    camera_cutscene_shake(obj);
}

u8 sNeedsRecenter = TRUE;

void camera_battle_update(Object *obj) {
    s32 sp10C;
    s32 sp108;
    s32 sp104;
    s32 sp100;
    s32 spFC;
    s32 pad_spF0[3];
    s32 spEC;
    s32 spE8;
    s32 spE4;
    s32 spE0;
    s32 pad_spDC;
    s32 spD8;
    s32 pad_spD4;
    s32 spD0;
    s32 spCC;
    s32 temp1;
    s32 pad_sp9C[11];
    s32 sp98;
    s32 pad_sp84[5];
    Vec4i sp74;
    Vec4s sp6C;
    u8 sp6B;
    u8 sp6A;
    s32 v02;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    Vec4i sp34;

    sp6A = FALSE;
    if (gReplayActive == 0) {
        D_8008012C |= GFX_FLAG_20;
    } else {
        D_8008012C &= ~GFX_FLAG_20;
    }

    camera_push_players_apart(FALSE);

    if (gPlayerDistance > 800) {
        spEC = ((gPlayerDistance - 800) * sZoomFromDistRatio) >> 0x10;
    } else {
        spEC = 0;
    }
    if (spEC > sOrbitMaxZoomOut) {
        spEC = sOrbitMaxZoomOut;
    }

    spE0 = obj->vars[2];
    spD8 = spEC - spE0;
    sp104 = obj->vars[1];

    v02 = angle_diff(gPlayerAngle, sp104);
    if (v02 < 0) {
        sp108 = v02 + sRotStep;
    } else {
        sp108 = v02 - sRotStep;
    }

    camera_update_player_facing();

    if (angle_diff(gPlayerAngle, sp104) > 0) {
        gPlayerObjects[PLAYER_1]->flags &= ~OBJ_FLAG_200;
        gPlayerInput[PLAYER_1].mirrored = FALSE;
        gPlayerObjects[PLAYER_2]->flags |= OBJ_FLAG_200;
        gPlayerInput[PLAYER_2].mirrored = TRUE;
    } else {
        gPlayerObjects[PLAYER_1]->flags |= OBJ_FLAG_200;
        gPlayerInput[PLAYER_1].mirrored = TRUE;
        gPlayerObjects[PLAYER_2]->flags &= ~OBJ_FLAG_200;
        gPlayerInput[PLAYER_2].mirrored = FALSE;
    }

    if (abs2(sp108) < 450 && sRotAccum < 0x20000) {
        sRotDecelTimer = 30;
        sRotAccum = 0;
        sp6A = 1;
        sRotDeltaCur = 0;
        sp10C = sp104;
    } else if (abs2(sp108) > 450 && sRotAccum < 0xA0000) {
        sRotAccum += 0x2000;
        sRotVelCap = sRotAccum >> 16;
        if (sp108 < -sRotVelCap) {
            sp108 = -sRotVelCap;
        } else if (sp108 > sRotVelCap) {
            sp108 = sRotVelCap;
        }
        sRotDeltaCur = sp108;
        sp10C = sp104 + sp108;
    } else {
        sRotAccum -= 0x3000;
        sRotVelCap = sRotAccum >> 16;
        if (sp108 < -sRotVelCap) {
            sp108 = -sRotVelCap;
        } else if (sp108 > sRotVelCap) {
            sp108 = sRotVelCap;
        }
        sRotDeltaCur = sp108;
        sp10C = sp104 + sp108;
    }

    obj->vars[1] = sp10C;

    if (abs2(spD8) < sCamZoomDeadZone && sZoomSettled == 0) {
        spEC = spE0;
    } else {
        if (abs(spD8) < sZoomDecelThreshold) {
            if (sZoomMomentumMin < sZoomMomentumCur - sZoomAccel) {
                sZoomMomentumCur -= sZoomDecel;
            } else {
                sZoomMomentumCur = sZoomMomentumMin;
            }
        } else if (sZoomMomentumCur + sPanAccel < sPanSpeedMaxAccum) {
            sZoomMomentumCur += sZoomAccel;
        } else {
            sZoomMomentumCur = sZoomSpeedMaxAccum;
        }

        D_8013C370 = sZoomMomentumCur >> 0x10;

        if (spD8 < -D_8013C370) {
            spD8 = -D_8013C370;
        } else if (spD8 > D_8013C370) {
            spD8 = D_8013C370;
        }
        sZoomSettled = spD8;
        spEC = spE0 + spD8;
    }

    sp34.x = gPlayerPos1->x;
    sp34.y = gPlayers[PLAYER_1].hitZones.headPos->y;
    sp34.z = gPlayerPos1->z;
    camera_project_to_screen(&sp34, &sp60, &sp5C, &sp50);

    sp34.x = gPlayerPos2->x;
    sp34.y = gPlayers[PLAYER_2].hitZones.headPos->y;
    sp34.z = gPlayerPos2->z;
    camera_project_to_screen(&sp34, &sp58, &sp54, &sp4C);

    if (sHitZoomAccum < 250 && (sp54 > 0.6 || sp5C > 0.6)) {
        sp5C = MAX(sp54, sp5C);
        sp5C -= 0.6;
        spEC = spE0 + sp5C * 700;
        sHitZoomAccum += sp5C * 60;
        sHitHeightAdj -= sp5C * 30;
        sHitScrollAccum += sHitScrollStep;
        sHitScrollTimer += sp5C * 2;
    } else if (sp54 <= 0.6 && sp5C <= 0.6) {
        if (sHitZoomAccum > 8) {
            sHitZoomAccum -= 8;
            sHitHeightAdj += 4;
        } else {
            sHitZoomAccum = sHitHeightAdj = 0;
        }

        if (sHitScrollTimer != 0) {
            sHitScrollTimer--;
        }

        if (sp50 > 0.65 || sp4C > 0.65) {
            sp50 = MAX(sp4C, sp50);
            sp50 -= 0.65;
            if (sp50 < 0.55) {
                spEC = spE0 + sp50 * 600;
            }
        }
    } else {
        spEC = spE0;
    }

    if (spEC > 6500) {
        spEC = 6500;
    }
    obj->vars[2] = spEC;

    gBgScrollY = D_8013C82C + sHitScrollTimer - (s32) (sPostCutsceneZoom * 0.2f);
    if (spEC > 1500 && gBgScrollY < -24) {
        gBgScrollY = -24;
    }

    gCameraTarget.y = ((sCamHeightMul * spEC) >> 16) + sHitHeightAdj - 480;

    sp34.x = (gPlayerPos2->x + gPlayerPos1->x) >> 1;
    sp34.z = (gPlayerPos2->z + gPlayerPos1->z) >> 1;
    sp34.y = -480;
    camera_project_to_screen(&sp34, &sp48, &sp44, &sp50);

    sp6B = sp50 > 0.2f;
    sp100 = ((gPlayerPos2->x + gPlayerPos1->x) >> 1) - gCameraTarget.x;
    spFC = ((gPlayerPos2->z + gPlayerPos1->z) >> 1) - gCameraTarget.z;

    if (abs2(sp100) > sCamDeadZone || abs2(spFC) > sCamDeadZone || sNeedsRecenter) {
        if (abs(sp100) < sPanDeadZone && abs(spFC) < sPanDeadZone) {
            if (sPanMomentumCur - sPanAccel > sPanMomentumMin) {
                sPanMomentumCur -= sPanDecel; // @bug ??
            } else {
                sPanMomentumCur = sPanMomentumMin;
            }
        } else {
            if (sPanMomentumCur + sPanAccel < sPanSpeedMaxAccum) {
                sPanMomentumCur += sPanAccel;
            } else {
                sPanMomentumCur = sPanSpeedMaxAccum;
            }
        }

        D_8013C370 = sPanMomentumCur >> 16;

        if (sp100 < -D_8013C370) {
            sp100 = -D_8013C370;
        } else if (sp100 > D_8013C370) {
            sp100 = D_8013C370;
        }

        if (spFC < -D_8013C370) {
            spFC = -D_8013C370;
        } else if (spFC > D_8013C370) {
            spFC = D_8013C370;
        }

        sNeedsRecenter = ((sp100 != 0) || (spFC != 0));

        gCameraTarget.x += sp100;
        gCameraTarget.z += spFC;

        if (sp6A && sp6B && (spFC != 0 || sp100 != 0)) {
            sp74.x = sp100;
            sp74.z = -spFC;

            sp6C.y = (0x400 - gCameraHeading) & 0xFFF;
            sp6C.x = sp6C.z = 0;
            math_rotate_vector(&sp74, &sp6C);

            if (sp74.x > 0) {
                sp98 = (u32) (sqrtf(sp100 * sp100 + spFC * spFC) + 0.5) >> 1;
            } else if (sp74.x < 0) {
                sp98 = -((u32) (sqrtf(sp100 * sp100 + spFC * spFC) + 0.5) >> 1);
            }

            if (sp98 > 2) {
                sp98 = 2;
            }
            if (sp98 < -2) {
                sp98 = -2;
            }
            gBgScrollX += sp98;
        }
    }

    spE8 = ((func_80012854(sp10C) * sOrbitRadius) >> 12) + gCameraTarget.x;
    spE4 = ((-func_80012854(sp10C + 0x400) * sOrbitRadius) >> 12) + gCameraTarget.z;
    spD0 = (func_80012854(sp10C) * sOrbitRadiusMul) >> 12;
    spCC = (-func_80012854(sp10C + 0x400) * sOrbitRadiusMul) >> 12;
    temp1 = (spEC * sOrbitHeightMul) >> 12;

    obj->pos.x = ((spEC * spD0) >> 12) + spE8;
    obj->pos.z = ((spEC * spCC) >> 12) + spE4;
    obj->pos.y = sCamBaseY + sHitZoomAccum - temp1;

    D_80081428 = D_8013C828;

    if (*gCamera->modInst->animations == NULL && !(gPlayers[PLAYER_1].flags & PLAYER_FLAG_400000) &&
            !(gPlayers[PLAYER_2].flags & PLAYER_FLAG_400000) ||
        gReplayActive != 0) {
        camera_check_bounds(obj);
    }
}
