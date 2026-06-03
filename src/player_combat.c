#include "common.h"
#include "task.h"

ColorRGBA sRedColor = { 255, 0, 0, 0 };
ColorRGBA sBlueColor = { 0, 0, 255, 0 };

/* .bss */
s32 D_80081260[2];
Vec4s D_80081268;
s32 D_80081270;
Model *gHitSparkModel;
Model *gBlockSparkModel;

void hit_spark_update(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames) {
        D_8008012C |= GFX_FLAG_10;
        obj->frameIndex++;
        if (obj->frameIndex > 12) {
            if (obj->color.a > obj->vars[0]) {
                obj->color.a -= obj->vars[0];
            } else {
                obj->color.a = 0;
            }
        }
    } else {
        obj->flags |= OBJ_FLAG_DELETE;
        D_8008012C &= ~GFX_FLAG_10;
        TASK_END(obj->currentTask);
    }
}

void block_spark_update(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames) {
        D_8008012C |= GFX_FLAG_10;
        obj->frameIndex++;
        if (obj->frameIndex > 2) {
            if (obj->color.a > obj->vars[0]) {
                obj->color.a -= obj->vars[0];
            } else {
                obj->color.a = 0;
            }
        }
    } else {
        D_8008012C &= ~GFX_FLAG_10;
        obj->flags |= OBJ_FLAG_DELETE;
        TASK_END(obj->currentTask);
    }
}

void spawn_hit_effect(Vec4s *pos, u8 isBlocked, Object *arg2, ColorRGBA *arg3) {
    Object *v0;
    Vec4i sp24;
    Player *sp20;
    Player *sp1C;

    sp20 = (Player *) arg2->varObj[0];
    sp1C = gPlayers + (1 - sp20->playerId);

    sp24.x = pos->x;
    sp24.y = pos->y;
    sp24.z = pos->z;

    if (isBlocked) {
        v0 = create_model_instance(&sp24, OBJ_PRIO_DEFAULT, block_spark_update, gBlockSparkModel);
        if (v0 != NULL) {
            v0->vars[0] = 255 / (v0->modInst->numAnimFrames - 2);
            v0->flags |= OBJ_FLAG_TRANSPARENT;
            create_light(v0, &sBlueColor);
            v0->color.a = 255;
        }

        if (arg3 == NULL) {
            arg3 = &D_8004B844[sp1C->characterId].trailColors[sp1C->playerId];
        }
        func_80023BE4(pos, arg2, arg3);
    } else {
        v0 = create_model_instance(&sp24, OBJ_PRIO_DEFAULT, hit_spark_update, gHitSparkModel);
        if (v0 != NULL) {
            v0->vars[0] = 255 / (v0->modInst->numAnimFrames - 12);
            v0->flags |= OBJ_FLAG_TRANSPARENT;
            create_light(v0, &sRedColor);
            v0->color.a = 255;
        }
    }
}

u8 is_point_in_hit_range(Vec4s *arg0, Vec4i *arg1, u32 radiusSq, Vec4s *point) {
    s16 x1, z1;

    if (point->y < arg0->y - 200 || arg1->y < point->y) {
        return FALSE;
    }

    x1 = (arg0->x + arg1->x) * 0.5f;
    z1 = (arg0->z + arg1->z) * 0.5f;

    if (SQ(x1 - point->x) + SQ(z1 - point->z) < radiusSq) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Vec4s *find_collision_point(Vec4s *attPoint1, Vec4i *attPoint2, u32 radiusSq, Vec4s *defPoint1, Vec4s *defPoint2) {
    s16 attPosX, attPosZ;
    s32 dx, dz;
    s32 pad[4];
    s16 defMidX, defMidY, defMidZ;

    attPosX = (attPoint1->x + attPoint2->x) >> 1;
    attPosZ = (attPoint1->z + attPoint2->z) >> 1;

    if (defPoint1->y > attPoint1->y - 200 && defPoint1->y < attPoint2->y) {
        dx = attPosX - defPoint1->x;
        dz = attPosZ - defPoint1->z;
        if (SQ(dx) + SQ(dz) < radiusSq) {
            return defPoint1;
        }
    }

    if (defPoint2->y > attPoint1->y - 200 && defPoint2->y < attPoint2->y) {
        dx = attPosX - defPoint2->x;
        dz = attPosZ - defPoint2->z;
        if (SQ(dx) + SQ(dz) < radiusSq) {
            return defPoint2;
        }
    }

    defMidX = D_80081268.x = (defPoint1->x + defPoint2->x) >> 1;
    defMidY = D_80081268.y = (defPoint1->y + defPoint2->y) >> 1;
    defMidZ = D_80081268.z = (defPoint1->z + defPoint2->z) >> 1;

    if (D_80081268.y > attPoint1->y - 200 && D_80081268.y < attPoint2->y) {
        dx = attPosX - D_80081268.x;
        dz = attPosZ - D_80081268.z;
        if (SQ(dx) + SQ(dz) < radiusSq) {
            return &D_80081268;
        }
    }

    D_80081268.x = (defMidX + defPoint2->x) >> 1;
    D_80081268.y = (defMidY + defPoint2->y) >> 1;
    D_80081268.z = (defMidZ + defPoint2->z) >> 1;

    if (D_80081268.y > attPoint1->y - 200 && D_80081268.y < attPoint2->y) {
        dx = attPosX - D_80081268.x;
        dz = attPosZ - D_80081268.z;
        if (SQ(dx) + SQ(dz) < radiusSq) {
            return &D_80081268;
        }
    }

    D_80081268.x = (defMidX + defPoint1->x) >> 1;
    D_80081268.y = (defMidY + defPoint1->y) >> 1;
    D_80081268.z = (defMidZ + defPoint1->z) >> 1;

    if (D_80081268.y > attPoint1->y - 200 && D_80081268.y < attPoint2->y) {
        dx = attPosX - D_80081268.x;
        dz = attPosZ - D_80081268.z;
        if (SQ(dx) + SQ(dz) < radiusSq) {
            return &D_80081268;
        }
    }

    return NULL;
}

#ifdef NON_MATCHING
s32 apply_damage_and_reaction(Player *defender, Player *attacker, CombatState *attackerStateDef) {
    CombatState *defenderState;
    s32 hp;
    s32 pad;
    s16 pad2;
    s16 moveId;
    u8 v1;
    u8 v12;
    s32 defenderFlags;

    moveId = 0;
    defenderState = defender->combatState;
    defenderFlags = defenderState->flags;

    if ((defenderFlags & (CSF_JUMP | CSF_HOP)) &&
        defender->obj->pos.y + defender->obj->modInst->rootTransform.local_matrix.w.y > -400.0f &&
        defender->hitZones.leftFootPos->y - defender->hitZones.headPos->y > 200.0f) {
        defenderFlags &= ~(CSF_JUMP | CSF_HOP);
        defenderFlags |= CSF_STANDING;
    }

    v1 = (defenderFlags & CSF_80) && (defender->obj->frameIndex >= 12);

    if (defenderFlags & CSF_BLOCK) {
        if (defenderFlags & CSF_STANDING) {
            moveId = attackerStateDef->blockStanding;
        } else {
            moveId = attackerStateDef->blockCrouch;
        }
    } else if (defenderFlags & CSF_10000) {
        moveId = attackerStateDef->hitMove10;
    } else if (defenderFlags & CSF_JUGGLED) {
        moveId = attackerStateDef->hitJuggle;
    } else if ((defenderFlags & CSF_400) && attackerStateDef->unk_1E != 0) {
        if (defenderFlags & CSF_200) {
            moveId = MOVE_ID_SLAMMED_FACE_D; // slammed face down
        } else {
            moveId = MOVE_ID_SLAMMED_FACE_U; // slammed face up
        }
    } else if (player_check_func_2(defender->obj) && !v1) {
        if (defenderFlags & (CSF_JUMP | CSF_STANDING | CSF_HOP)) {
            moveId = attackerStateDef->hitBackStanding;
        } else if (defenderFlags & CSF_CROUCH) {
            moveId = attackerStateDef->hitBackCrouch;
        }

        if (defenderFlags & (CSF_JUMP | CSF_HOP)) {
            moveId = attackerStateDef->hitBackAirborne;
        } else {
            defender->obj->pos.y = 0;
        }

        defender->obj->flags &= ~OBJ_FLAG_800000;
    } else {
        if (defenderFlags & (CSF_JUMP | CSF_STANDING | CSF_HOP)) {
            moveId = attackerStateDef->hitStanding;
        } else if (defenderFlags & CSF_CROUCH) {
            moveId = attackerStateDef->hitCrouch;
        }

        if (defenderFlags & (CSF_JUMP | CSF_HOP)) {
            moveId = attackerStateDef->hitAirborne;
        } else {
            defender->obj->pos.y = 0;
        }
    }

    v12 = (moveId == MOVE_ID_STANDING_BLOCK_270) || (moveId == MOVE_ID_CROUCH_BLOCK_I);

    if (moveId != 0 && !gReplayActive) {
        attacker->damage = attackerStateDef->damage;
        if (attacker->obj->vars[3] < 0) {
            attacker->total_damage += attacker->damage;
        } else {
            attacker->total_damage = attacker->damage;
            attacker->obj->vars[3] = -1;
        }

        if (moveId >= MOVE_ID_COGRABBED_BY_A_236 && moveId <= MOVE_ID_COGRABBED_BY_Z_245) {
            // CoGrabbed
            defender->obj->vars[2] = attackerStateDef->damage;
        } else if (!v12 && gPlayMode != PLAY_MODE_PRACTICE) {
            defender->obj->playerHp -= attackerStateDef->damage;
        }

        hp = defender->obj->playerHp;
        if (hp < 0) {
            hp = defender->obj->playerHp = 0;
        }

        if (hp == 0) {
            gGlobalFlags |= GAME_FLAG_BATTLE_FINISHED;
            if (defender->flags & PLAYER_FLAG_NOT_FACING_OPP) {
                if (defenderFlags & CSF_STANDING) {
                    moveId = MOVE_ID_KD_FALL_FORWAR_118;
                } else if (defenderFlags & CSF_CROUCH) {
                    moveId = MOVE_ID_KD_FALL_FORWAR_081;
                }
            } else {
                if (defenderFlags & CSF_STANDING) {
                    moveId = MOVE_ID_KD_UPPER_CUT;
                } else if (defenderFlags & CSF_CROUCH) {
                    moveId = MOVE_ID_KD_FALL_BACK_C;
                }
            }
        }

        player_force_move(defender, moveId, TRUE);
    }

    return moveId;
}
#else
s32 apply_damage_and_reaction(Player *arg0, Player *arg1, CombatState *arg2);
#pragma GLOBAL_ASM("asm/nonmatchings/player_combat/apply_damage_and_reaction.s")
#endif

void process_hit(Player *defender, Player *attacker, Vec4s *hitPos) {
    s32 moveId;
    s16 isBlock;
    CombatState *attackerCombatState;

    attackerCombatState = attacker->combatState;

    if (!gRoundOver || gReplayActive) {
        moveId = apply_damage_and_reaction(defender, attacker, attackerCombatState);
        isBlock = moveId == 270 || moveId == 271;
        if (moveId != 0) {
            spawn_hit_effect(hitPos, isBlock, defender->obj, NULL);
            defender->hitCooldown = 13;
            attacker->hitCooldown = 2;
        }
    }
}

void check_punch_air(Player *defender, Player *attacker) {
    Vec4i *defPoint1;
    Vec4s attPoint2;
    Vec4s somePos;
    Vec4s defPoint2;
    Vec4s attPoint1;
    Vec4s attLeftHandPos;
    Vec4s *hitPos;
    s32 pad[70];
    Transform *sp54;
    HitZones *defZones;
    HitZones *attZones;
    s32 pad2[6];

    defPoint1 = &defender->obj->pos;

    defZones = &defender->hitZones;
    attZones = &attacker->hitZones;

    defPoint2.x = defZones->headPos->x;
    defPoint2.y = defZones->headPos->y;
    defPoint2.z = defZones->headPos->z;

    attPoint1.x = attZones->rightHandPos->x;
    attPoint1.y = attZones->rightHandPos->y;
    attPoint1.z = attZones->rightHandPos->z;

    if (attZones->hasRightPunchStrike) {
        attPoint2.x = attZones->rightPunchStrike.world_matrix.w.x;
        attPoint2.y = attZones->rightPunchStrike.world_matrix.w.y;
        attPoint2.z = attZones->rightPunchStrike.world_matrix.w.z;

        hitPos = find_collision_point(&defPoint2, defPoint1, defZones->radius1 + 55000, &attPoint1, &attPoint2);
        if (hitPos != NULL) {
            if (hitPos->y < defPoint2.y) {
                hitPos->y = defPoint2.y;
            }

            hitPos->x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + defPoint1->x;
            hitPos->z =
                ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + defPoint1->z;
            process_hit(defender, attacker, hitPos);
            return;
        }
    } else if (is_point_in_hit_range(&defPoint2, defPoint1, defZones->radius1, &attPoint1)) {
        if (attPoint1.y < defPoint2.y) {
            attPoint1.y = defPoint2.y;
        }
        attPoint1.x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + defPoint1->x;
        attPoint1.z =
            ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + defPoint1->z;
        process_hit(defender, attacker, &attPoint1);
        return;
    }

    attLeftHandPos.x = attZones->leftHandPos->x;
    attLeftHandPos.y = attZones->leftHandPos->y;
    attLeftHandPos.z = attZones->leftHandPos->z;

    if (attZones->hasLeftPunchStrike) {
        sp54 = &attZones->leftPunchStrike;
        somePos.x = attZones->leftPunchStrike.world_matrix.w.x;
        somePos.y = attZones->leftPunchStrike.world_matrix.w.y;
        somePos.z = attZones->leftPunchStrike.world_matrix.w.z;

        hitPos = find_collision_point(&defPoint2, defPoint1, defZones->radius1 + 55000, &attLeftHandPos, &somePos);
        if (hitPos != NULL) {
            if (hitPos->y < defPoint2.y) {
                hitPos->y = defPoint2.y;
            }

            hitPos->x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + defPoint1->x;
            hitPos->z =
                ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + defPoint1->z;
            process_hit(defender, attacker, hitPos);
            return;
        }
    } else if (is_point_in_hit_range(&defPoint2, defPoint1, defZones->radius1, &attLeftHandPos)) {
        if (attLeftHandPos.y < defPoint2.y) {
            attLeftHandPos.y = defPoint2.y;
        }
        attLeftHandPos.x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + defPoint1->x;
        attLeftHandPos.z =
            ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + defPoint1->z;
        process_hit(defender, attacker, &attLeftHandPos);
        return;
    }

    if (attZones->hasZone3) {
        if (attZones->hasZone4) {
            // @bug sp54 could be uninitialized?
            somePos.x = sp54->world_matrix.w.x;
            somePos.y = sp54->world_matrix.w.y;
            somePos.z = sp54->world_matrix.w.z;
        } else {
            somePos.x = attZones->pos8->x;
            somePos.y = attZones->pos8->y;
            somePos.z = attZones->pos8->z;
        }

        if (is_point_in_hit_range(&defPoint2, defPoint1, defZones->radius2, &somePos)) {
            if (somePos.y < defPoint2.y) {
                somePos.y = defPoint2.y;
            }
            somePos.x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + defPoint1->x;
            somePos.z =
                ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + defPoint1->z;
            process_hit(defender, attacker, &somePos);
        }
    }
}

void check_kick_air(Player *defender, Player *attacker) {
    Vec4i *defPoint1;
    Vec4s defHead;
    Vec4s attPoint1;
    Vec4s attPoint2;
    HitZones *attZones;
    HitZones *defZones;
    u32 radius;
    Vec4s *hitPos;
    u8 v0;

    defPoint1 = &defender->obj->pos;

    attZones = &attacker->hitZones;
    defZones = &defender->hitZones;

    defHead.x = defZones->headPos->x;
    defHead.y = defZones->headPos->y;
    defHead.z = defZones->headPos->z;

    if (attZones->hasRightKickStrike) {
        attPoint1.x = attZones->rightKickStrike.world_matrix.w.x;
        attPoint1.y = attZones->rightKickStrike.world_matrix.w.y;
        attPoint1.z = attZones->rightKickStrike.world_matrix.w.z;
    } else {
        attPoint1.x = attZones->rightFootPos->x;
        attPoint1.y = attZones->rightFootPos->y;
        attPoint1.z = attZones->rightFootPos->z;
    }

    attPoint2.x = attZones->rightCalfPos->x;
    attPoint2.y = attZones->rightCalfPos->y;
    attPoint2.z = attZones->rightCalfPos->z;

    v0 = (attacker->combatState->flags & CSF_ATTACK_RIGHT_FOOT_2) || (attPoint1.y < -200);

    if (attPoint1.y < defZones->rightCalfPos->y) {
        radius = defZones->radius1;
    } else {
        radius = defZones->radius2;
    }

    if (v0) {
        hitPos = find_collision_point(&defHead, defPoint1, radius, &attPoint2, &attPoint1);
        if (hitPos != NULL) {
            process_hit(defender, attacker, hitPos);
            return;
        }
    }

    if (attZones->hasLeftKickStrike) {
        attPoint1.x = attZones->leftKickStrike.world_matrix.w.x;
        attPoint1.y = attZones->leftKickStrike.world_matrix.w.y;
        attPoint1.z = attZones->leftKickStrike.world_matrix.w.z;
    } else {
        attPoint1.x = attZones->leftFootPos->x;
        attPoint1.y = attZones->leftFootPos->y;
        attPoint1.z = attZones->leftFootPos->z;
    }

    attPoint2.x = attZones->leftCalfPos->x;
    attPoint2.y = attZones->leftCalfPos->y;
    attPoint2.z = attZones->leftCalfPos->z;

    if (attPoint1.y < defZones->leftCalfPos->y) {
        radius = defZones->radius1;
    } else {
        radius = defZones->radius2;
    }

    v0 = (attacker->combatState->flags & CSF_ATTACK_LEFT_FOOT) || (attPoint1.y < -200);

    if (v0) {
        hitPos = find_collision_point(&defHead, defPoint1, radius, &attPoint2, &attPoint1);
        if (hitPos != NULL) {
            process_hit(defender, attacker, hitPos);
        }
    }
}

void check_punch_ground(Player *defender, Player *attacker) {
    HitZones *defZones;
    HitZones *attZones;
    Vec4s defPoint1;
    Vec4s defPoint2;
    Vec4s attPoint1;
    Vec4i attPoint2;
    Vec4s *hitPos;
    s32 pad;

    defZones = &defender->hitZones;
    attZones = &attacker->hitZones;

    if (attacker->obj->pos.y < -20 ||
        attacker->obj->modInst->rootTransform.local_matrix.w.y < attacker->obj->modInst->baseRootPos.y) {
        return;
    }

    defPoint1.x = defZones->headPos->x;
    defPoint1.y = defZones->headPos->y;
    defPoint1.z = defZones->headPos->z;

    defPoint2.x = defZones->rightFootPos->x;
    defPoint2.y = defZones->rightFootPos->y;
    defPoint2.z = defZones->rightFootPos->z;

    attPoint1.x = attZones->torsoPos->x;
    attPoint1.z = attZones->torsoPos->z;
    attPoint1.y = attZones->torsoPos->y - 100.0f;

    attPoint2.x = attZones->torsoPos->x;
    attPoint2.z = attZones->torsoPos->z;
    attPoint2.y = attZones->torsoPos->y;

    hitPos = find_collision_point(&attPoint1, &attPoint2, 80000, &defPoint1, &defPoint2);
    if (hitPos != NULL) {
        process_hit(defender, attacker, hitPos);
        return;
    }

    if (attZones->hasRightPunchStrike) {
        attPoint1.x = attZones->rightPunchStrike.world_matrix.w.x;
        attPoint1.y = -100;
        attPoint1.z = attZones->rightPunchStrike.world_matrix.w.z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPos = find_collision_point(&attPoint1, &attPoint2, 15000, &defPoint1, &defPoint2);
        if (hitPos != NULL) {
            process_hit(defender, attacker, hitPos);
            return;
        }
    } else {
        attPoint1.x = attZones->rightHandPos->x;
        attPoint1.y = -100;
        attPoint1.z = attZones->rightHandPos->z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPos = find_collision_point(&attPoint1, &attPoint2, 15000, &defPoint1, &defPoint2);
        if (hitPos != NULL) {
            process_hit(defender, attacker, hitPos);
            return;
        }
    }

    if (attZones->hasLeftPunchStrike) {
        attPoint1.x = attZones->leftPunchStrike.world_matrix.w.x;
        attPoint1.y = -100;
        attPoint1.z = attZones->leftPunchStrike.world_matrix.w.z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPos = find_collision_point(&attPoint1, &attPoint2, 15000, &defPoint1, &defPoint2);
        if (hitPos != NULL) {
            process_hit(defender, attacker, hitPos);
            return;
        }
    } else {
        attPoint1.x = attZones->leftHandPos->x;
        attPoint1.y = -100;
        attPoint1.z = attZones->leftHandPos->z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPos = find_collision_point(&attPoint1, &attPoint2, 15000, &defPoint1, &defPoint2);
        if (hitPos != NULL) {
            process_hit(defender, attacker, hitPos);
            return;
        }
    }
}

void check_kick_ground(Player *defender, Player *attacker) {
    HitZones *defZones;
    HitZones *attZones;
    Vec4s defPoint1;
    Vec4s defPoint2;
    Vec4s attPoint1;
    Vec4i attPoint2;
    Vec4s *hitPoint;

    defZones = &defender->hitZones;
    attZones = &attacker->hitZones;

    if (attacker->obj->pos.y < -20 ||
        attacker->obj->modInst->rootTransform.local_matrix.w.y < attacker->obj->modInst->baseRootPos.y) {
        return;
    }

    defPoint1.x = defZones->headPos->x;
    defPoint1.y = defZones->headPos->y;
    defPoint1.z = defZones->headPos->z;

    defPoint2.x = defZones->rightFootPos->x;
    defPoint2.y = defZones->rightFootPos->y;
    defPoint2.z = defZones->rightFootPos->z;

    attPoint1.x = attZones->torsoPos->x;
    attPoint1.z = attZones->torsoPos->z;
    attPoint1.y = attZones->torsoPos->y - 100.0f;

    attPoint2.x = attZones->torsoPos->x;
    attPoint2.z = attZones->torsoPos->z;
    attPoint2.y = attZones->torsoPos->y;

    hitPoint = find_collision_point(&attPoint1, &attPoint2, 80000, &defPoint1, &defPoint2);
    if (hitPoint != NULL) {
        process_hit(defender, attacker, hitPoint);
        return;
    }

    if (attZones->hasLeftKickStrike) {
        attPoint1.x = attZones->leftKickStrike.world_matrix.w.x;
        attPoint1.y = -100;
        attPoint1.z = attZones->leftKickStrike.world_matrix.w.z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPoint = find_collision_point(&attPoint1, &attPoint2, 50000, &defPoint1, &defPoint2);
        if (hitPoint != NULL) {
            process_hit(defender, attacker, hitPoint);
            return;
        }
    } else {
        attPoint1.x = attZones->leftFootPos->x;
        attPoint1.y = -100;
        attPoint1.z = attZones->leftFootPos->z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPoint = find_collision_point(&attPoint1, &attPoint2, 50000, &defPoint1, &defPoint2);
        if (hitPoint != NULL) {
            process_hit(defender, attacker, hitPoint);
            return;
        }
    }

    if (attZones->hasRightKickStrike) {
        attPoint1.x = attZones->rightKickStrike.world_matrix.w.x;
        attPoint1.y = -100;
        attPoint1.z = attZones->rightKickStrike.world_matrix.w.z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPoint = find_collision_point(&attPoint1, &attPoint2, 50000, &defPoint1, &defPoint2);
        if (hitPoint != NULL) {
            process_hit(defender, attacker, hitPoint);
            return;
        }
    } else {
        attPoint1.x = attZones->rightFootPos->x;
        attPoint1.y = -100;
        attPoint1.z = attZones->rightFootPos->z;

        attPoint2.x = attPoint1.x;
        attPoint2.y = 0;
        attPoint2.z = attPoint1.z;

        hitPoint = find_collision_point(&attPoint1, &attPoint2, 50000, &defPoint1, &defPoint2);
        if (hitPoint != NULL) {
            process_hit(defender, attacker, hitPoint);
            return;
        }
    }
}

void init_player_hitboxes(Player *player, HitZonesSetup *hitZonesSetup) {
    player->hitZones.headPos = &player->obj->modInst->transforms[hitZonesSetup->headBoneId].world_matrix.w;
    player->hitZones.leftHandPos = &player->obj->modInst->transforms[hitZonesSetup->leftHandId].world_matrix.w;
    player->hitZones.rightHandPos = &player->obj->modInst->transforms[hitZonesSetup->rightHandId].world_matrix.w;
    player->hitZones.leftFootPos = &player->obj->modInst->transforms[hitZonesSetup->leftFootBoneId].world_matrix.w;
    player->hitZones.rightFootPos = &player->obj->modInst->transforms[hitZonesSetup->rightFootBoneId].world_matrix.w;
    player->hitZones.leftCalfPos = &player->obj->modInst->transforms[hitZonesSetup->leftCalfBoneId].world_matrix.w;
    player->hitZones.rightCalfPos = &player->obj->modInst->transforms[hitZonesSetup->rightCalfBoneId].world_matrix.w;
    player->hitZones.torsoPos = &player->obj->modInst->transforms[0].world_matrix.w;

    if (hitZonesSetup->boneIdz3z4 > 0) {
        player->hitZones.pos8 = &player->obj->modInst->transforms[hitZonesSetup->boneIdz3z4].world_matrix.w;
        player->hitZones.hasZone3 = TRUE;
    } else {
        player->hitZones.hasZone3 = FALSE;
    }

    player->hitZones.radius1 = hitZonesSetup->radius1;
    player->hitZones.radius2 = hitZonesSetup->radius2;

    if (hitZonesSetup->rightPunchPos.x != 0 || hitZonesSetup->rightPunchPos.y != 0 ||
        hitZonesSetup->rightPunchPos.z != 0) {
        player->hitZones.hasRightPunchStrike = TRUE;
        init_transform(&player->obj->modInst->transforms[hitZonesSetup->rightPunchBoneId],
                       &player->hitZones.rightPunchStrike, -3, -3);
        player->hitZones.rightPunchStrike.local_matrix.w.x = hitZonesSetup->rightPunchPos.x;
        player->hitZones.rightPunchStrike.local_matrix.w.y = hitZonesSetup->rightPunchPos.y;
        player->hitZones.rightPunchStrike.local_matrix.w.z = hitZonesSetup->rightPunchPos.z;
    } else {
        player->hitZones.hasRightPunchStrike = FALSE;
    }

    if (hitZonesSetup->leftPunchPos.x != 0 || hitZonesSetup->leftPunchPos.y != 0 ||
        hitZonesSetup->leftPunchPos.z != 0) {
        player->hitZones.hasLeftPunchStrike = TRUE;
        init_transform(&player->obj->modInst->transforms[hitZonesSetup->leftPunchBoneId],
                       &player->hitZones.leftPunchStrike, -3, -3);
        player->hitZones.leftPunchStrike.local_matrix.w.x = hitZonesSetup->leftPunchPos.x;
        player->hitZones.leftPunchStrike.local_matrix.w.y = hitZonesSetup->leftPunchPos.y;
        player->hitZones.leftPunchStrike.local_matrix.w.z = hitZonesSetup->leftPunchPos.z;
    } else {
        player->hitZones.hasLeftPunchStrike = FALSE;
    }

    if (hitZonesSetup->z4offset.x != 0 || hitZonesSetup->z4offset.y != 0 || hitZonesSetup->z4offset.z != 0) {
        player->hitZones.hasZone4 = TRUE;
        init_transform(&player->obj->modInst->transforms[hitZonesSetup->boneIdz3z4], &player->hitZones.zone4trans, -3,
                       -3);
        player->hitZones.zone4trans.local_matrix.w.x = hitZonesSetup->z4offset.x;
        player->hitZones.zone4trans.local_matrix.w.y = hitZonesSetup->z4offset.y;
        player->hitZones.zone4trans.local_matrix.w.z = hitZonesSetup->z4offset.z;
    } else {
        player->hitZones.hasZone4 = FALSE;
    }

    if (hitZonesSetup->rightKickPos.x != 0 || hitZonesSetup->rightKickPos.y != 0 ||
        hitZonesSetup->rightKickPos.z != 0) {
        player->hitZones.hasRightKickStrike = TRUE;
        init_transform(&player->obj->modInst->transforms[hitZonesSetup->rightFootBoneId],
                       &player->hitZones.rightKickStrike, -3, -3);
        player->hitZones.rightKickStrike.local_matrix.w.x = hitZonesSetup->rightKickPos.x;
        player->hitZones.rightKickStrike.local_matrix.w.y = hitZonesSetup->rightKickPos.y;
        player->hitZones.rightKickStrike.local_matrix.w.z = hitZonesSetup->rightKickPos.z;
    } else {
        player->hitZones.hasRightKickStrike = FALSE;
    }

    if (hitZonesSetup->leftKickPos.x != 0 || hitZonesSetup->leftKickPos.y != 0 || hitZonesSetup->leftKickPos.z != 0) {
        player->hitZones.hasLeftKickStrike = TRUE;
        init_transform(&player->obj->modInst->transforms[hitZonesSetup->leftFootBoneId],
                       &player->hitZones.leftKickStrike, -3, -3);
        player->hitZones.leftKickStrike.local_matrix.w.x = hitZonesSetup->leftKickPos.x;
        player->hitZones.leftKickStrike.local_matrix.w.y = hitZonesSetup->leftKickPos.y;
        player->hitZones.leftKickStrike.local_matrix.w.z = hitZonesSetup->leftKickPos.z;
    } else {
        player->hitZones.hasLeftKickStrike = FALSE;
    }
}
