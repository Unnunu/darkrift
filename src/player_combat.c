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
            if (obj->unk_088.a > obj->vars[0]) {
                obj->unk_088.a -= obj->vars[0];
            } else {
                obj->unk_088.a = 0;
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
            if (obj->unk_088.a > obj->vars[0]) {
                obj->unk_088.a -= obj->vars[0];
            } else {
                obj->unk_088.a = 0;
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
            v0->flags |= OBJ_FLAG_2000;
            create_light(v0, &sBlueColor);
            v0->unk_088.a = 255;
        }

        if (arg3 == NULL) {
            arg3 = &D_8004B844[sp1C->characterId].unk_08[sp1C->playerId];
        }
        func_80023BE4(pos, arg2, arg3);
    } else {
        v0 = create_model_instance(&sp24, OBJ_PRIO_DEFAULT, hit_spark_update, gHitSparkModel);
        if (v0 != NULL) {
            v0->vars[0] = 255 / (v0->modInst->numAnimFrames - 12);
            v0->flags |= OBJ_FLAG_2000;
            create_light(v0, &sRedColor);
            v0->unk_088.a = 255;
        }
    }
}

u8 is_point_in_hit_range(Vec4s *arg0, Vec4i *arg1, u32 arg2, Vec4s *arg3) {
    s16 x1, z1;

    if (arg3->y < arg0->y - 200 || arg1->y < arg3->y) {
        return FALSE;
    }

    x1 = (arg0->x + arg1->x) * 0.5f;
    z1 = (arg0->z + arg1->z) * 0.5f;

    if (SQ(x1 - arg3->x) + SQ(z1 - arg3->z) < arg2) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Vec4s *find_closest_hit_point(Vec4s *arg0, Vec4i *arg1, u32 arg2, Vec4s *arg3, Vec4s *arg4) {
    s16 x1, z1;
    s32 dx, dz;
    s32 pad[4];
    s16 x2, y2, z2;

    x1 = (arg0->x + arg1->x) >> 1;
    z1 = (arg0->z + arg1->z) >> 1;

    if (arg3->y > arg0->y - 200 && arg1->y > arg3->y) {
        dx = x1 - arg3->x;
        dz = z1 - arg3->z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return arg3;
        }
    }

    if (arg4->y > arg0->y - 200 && arg1->y > arg4->y) {
        dx = x1 - arg4->x;
        dz = z1 - arg4->z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return arg4;
        }
    }

    x2 = D_80081268.x = (arg3->x + arg4->x) >> 1;
    y2 = D_80081268.y = (arg3->y + arg4->y) >> 1;
    z2 = D_80081268.z = (arg3->z + arg4->z) >> 1;

    if (D_80081268.y > arg0->y - 200 && arg1->y > D_80081268.y) {
        dx = x1 - D_80081268.x;
        dz = z1 - D_80081268.z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return &D_80081268;
        }
    }

    D_80081268.x = (x2 + arg4->x) >> 1;
    D_80081268.y = (y2 + arg4->y) >> 1;
    D_80081268.z = (z2 + arg4->z) >> 1;

    if (D_80081268.y > arg0->y - 200 && arg1->y > D_80081268.y) {
        dx = x1 - D_80081268.x;
        dz = z1 - D_80081268.z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return &D_80081268;
        }
    }

    D_80081268.x = (x2 + arg3->x) >> 1;
    D_80081268.y = (y2 + arg3->y) >> 1;
    D_80081268.z = (z2 + arg3->z) >> 1;

    if (D_80081268.y > arg0->y - 200 && arg1->y > D_80081268.y) {
        dx = x1 - D_80081268.x;
        dz = z1 - D_80081268.z;
        if (SQ(dx) + SQ(dz) < arg2) {
            return &D_80081268;
        }
    }

    return NULL;
}

#ifdef NON_MATCHING
s32 apply_damage_and_reaction(Player *defender, Player *attacker, PlayerStateDef *attackerStateDef) {
    PlayerStateDef *sub3;
    s32 hp;
    s32 pad;
    s16 pad2;
    s16 a3;
    u8 v1;
    u8 v12;
    s32 t0;

    a3 = 0;
    sub3 = defender->currentStateDef;
    t0 = sub3->flags;

    if ((t0 & (STATE_FLAG_2 | STATE_FLAG_8)) &&
        defender->obj->pos.y + defender->obj->modInst->rootTransform.local_matrix.w.y > -400.0f &&
        defender->hitboxBones.thighPos->y - defender->hitboxBones.handPos->y > 200.0f) {
        t0 &= ~(STATE_FLAG_2 | STATE_FLAG_8);
        t0 |= STATE_FLAG_4;
    }

    v1 = (t0 & STATE_FLAG_80) && (defender->obj->frameIndex >= 12);

    if (t0 & STATE_FLAG_4000) {
        if (t0 & STATE_FLAG_4) {
            a3 = attackerStateDef->hitMove3;
        } else {
            a3 = attackerStateDef->hitMove4;
        }
    } else if (t0 & STATE_FLAG_10000) {
        a3 = attackerStateDef->unk_1C;
    } else if (t0 & STATE_FLAG_20000) {
        a3 = attackerStateDef->unk_14;
    } else if ((t0 & STATE_FLAG_400) && attackerStateDef->unk_1E != 0) {
        if (t0 & STATE_FLAG_200) {
            a3 = 206;
        } else {
            a3 = 97;
        }
    } else if (func_80030BB0(defender->obj) && !v1) {
        if (t0 & (STATE_FLAG_2 | STATE_FLAG_4 | STATE_FLAG_8)) {
            a3 = attackerStateDef->unk_16;
        } else if (t0 & STATE_FLAG_1) {
            a3 = attackerStateDef->unk_18;
        }

        if (t0 & (STATE_FLAG_2 | STATE_FLAG_8)) {
            a3 = attackerStateDef->unk_1A;
        } else {
            defender->obj->pos.y = 0;
        }

        defender->obj->flags &= ~OBJ_FLAG_800000;
    } else {
        if (t0 & (STATE_FLAG_2 | STATE_FLAG_4 | STATE_FLAG_8)) {
            a3 = attackerStateDef->hitMove1;
        } else if (t0 & STATE_FLAG_1) {
            a3 = attackerStateDef->hitMove2;
        }

        if (t0 & (STATE_FLAG_2 | STATE_FLAG_8)) {
            a3 = attackerStateDef->unk_12;
        } else {
            defender->obj->pos.y = 0;
        }
    }
    v12 = (a3 == 270) || (a3 == 271);

    if (a3 != 0 && !sReplayActive) {
        attacker->damage = attackerStateDef->damage;
        if (attacker->obj->vars[3] < 0) {
            attacker->total_damage += attacker->damage;
        } else {
            attacker->total_damage = attacker->damage;
            attacker->obj->vars[3] = -1;
        }

        if (a3 >= 236 && a3 <= 245) {
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
                if (t0 & STATE_FLAG_4) {
                    a3 = 118;
                } else if (t0 & STATE_FLAG_1) {
                    a3 = 81;
                }
            } else {
                if (t0 & STATE_FLAG_4) {
                    a3 = 70;
                } else if (t0 & STATE_FLAG_1) {
                    a3 = 73;
                }
            }
        }

        func_800063C4(defender, a3, TRUE);
    }

    return a3;
}
#else
s32 apply_damage_and_reaction(Player *arg0, Player *arg1, PlayerStateDef *arg2);
#pragma GLOBAL_ASM("asm/nonmatchings/player_combat/apply_damage_and_reaction.s")
#endif

void process_hit(Player *defender, Player *attacker, Vec4s *arg2) {
    s32 v0;
    s16 isBlock;
    PlayerStateDef *attackerStateDef;

    attackerStateDef = attacker->currentStateDef;

    if (!gRoundOver || sReplayActive) {
        v0 = apply_damage_and_reaction(defender, attacker, attackerStateDef);
        isBlock = v0 == 270 || v0 == 271;
        if (v0 != 0) {
            spawn_hit_effect(arg2, isBlock, defender->obj, NULL);
            defender->hitCooldown = 13;
            attacker->hitCooldown = 2;
        }
    }
}

void check_strike_hit(Player *defender, Player *attacker) {
    Vec4i *s1;
    Vec4s sp194;
    Vec4s sp18C;
    Vec4s sp184;
    Vec4s sp17C;
    Vec4s sp174;
    Vec4s *sp170;
    s32 pad[70];
    Transform *sp54;
    HitboxBones *arg09;
    HitboxBones *arg19;
    s32 pad2[6];

    s1 = &defender->obj->pos;

    arg09 = &defender->hitboxBones;
    arg19 = &attacker->hitboxBones;

    sp184.x = arg09->handPos->x;
    sp184.y = arg09->handPos->y;
    sp184.z = arg09->handPos->z;

    sp17C.x = arg19->torsoPos->x;
    sp17C.y = arg19->torsoPos->y;
    sp17C.z = arg19->torsoPos->z;

    if (arg19->hasGrabZone) {
        sp194.x = arg19->grabTransform.world_matrix.w.x;
        sp194.y = arg19->grabTransform.world_matrix.w.y;
        sp194.z = arg19->grabTransform.world_matrix.w.z;

        sp170 = find_closest_hit_point(&sp184, s1, arg09->strikeRadius + 55000, &sp17C, &sp194);
        if (sp170 != NULL) {
            if (sp170->y < sp184.y) {
                sp170->y = sp184.y;
            }

            sp170->x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
            sp170->z = ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
            process_hit(defender, attacker, sp170);
            return;
        }
    } else if (is_point_in_hit_range(&sp184, s1, arg09->strikeRadius, &sp17C)) {
        if (sp17C.y < sp184.y) {
            sp17C.y = sp184.y;
        }
        sp17C.x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
        sp17C.z = ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
        process_hit(defender, attacker, &sp17C);
        return;
    }

    sp174.x = arg19->footPos->x;
    sp174.y = arg19->footPos->y;
    sp174.z = arg19->footPos->z;

    if (arg19->hasTorsoZone) {
        sp54 = &arg19->torsoTransform;
        sp18C.x = arg19->torsoTransform.world_matrix.w.x;
        sp18C.y = arg19->torsoTransform.world_matrix.w.y;
        sp18C.z = arg19->torsoTransform.world_matrix.w.z;

        sp170 = find_closest_hit_point(&sp184, s1, arg09->strikeRadius + 55000, &sp174, &sp18C);
        if (sp170 != NULL) {
            if (sp170->y < sp184.y) {
                sp170->y = sp184.y;
            }

            sp170->x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
            sp170->z = ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
            process_hit(defender, attacker, sp170);
            return;
        }
    } else if (is_point_in_hit_range(&sp184, s1, arg09->strikeRadius, &sp174)) {
        if (sp174.y < sp184.y) {
            sp174.y = sp184.y;
        }
        sp174.x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
        sp174.z = ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
        process_hit(defender, attacker, &sp174);
        return;
    }

    if (arg19->hasHeadZone) {
        if (arg19->hasTailZone) {
            // @bug sp54 could be uninitialized?
            sp18C.x = sp54->world_matrix.w.x;
            sp18C.y = sp54->world_matrix.w.y;
            sp18C.z = sp54->world_matrix.w.z;
        } else {
            sp18C.x = arg19->extraBonePos->x;
            sp18C.y = arg19->extraBonePos->y;
            sp18C.z = arg19->extraBonePos->z;
        }

        if (is_point_in_hit_range(&sp184, s1, arg09->comboRadius, &sp18C)) {
            if (sp18C.y < sp184.y) {
                sp18C.y = sp184.y;
            }
            sp18C.x = ((func_80012854((0xC00 - defender->obj->rotation.y) & 0xFFF) * 100) >> 12) + s1->x;
            sp18C.z = ((-func_80012854(((0xC00 - defender->obj->rotation.y) & 0xFFF) + 0x400) * 100) >> 12) + s1->z;
            process_hit(defender, attacker, &sp18C);
        }
    }
}

void check_launcher_hit(Player *arg0, Player *arg1) {
    Vec4i *sp5C;
    Vec4s sp54;
    Vec4s sp4C;
    Vec4s sp44;
    HitboxBones *arg19;
    HitboxBones *arg09;
    u32 a2;
    Vec4s *v02;
    u8 v0;

    sp5C = &arg0->obj->pos;

    arg19 = &arg1->hitboxBones;
    arg09 = &arg0->hitboxBones;

    sp54.x = arg09->handPos->x;
    sp54.y = arg09->handPos->y;
    sp54.z = arg09->handPos->z;

    if (arg19->hasLegZone) {
        sp4C.x = arg19->legTransform.world_matrix.w.x;
        sp4C.y = arg19->legTransform.world_matrix.w.y;
        sp4C.z = arg19->legTransform.world_matrix.w.z;
    } else {
        sp4C.x = arg19->headPos->x;
        sp4C.y = arg19->headPos->y;
        sp4C.z = arg19->headPos->z;
    }

    sp44.x = arg19->armPos->x;
    sp44.y = arg19->armPos->y;
    sp44.z = arg19->armPos->z;

    v0 = (arg1->currentStateDef->flags & STATE_FLAG_1000) || (sp4C.y < -200);

    if (sp4C.y < arg09->armPos->y) {
        a2 = arg09->strikeRadius;
    } else {
        a2 = arg09->comboRadius;
    }

    if (v0) {
        v02 = find_closest_hit_point(&sp54, sp5C, a2, &sp44, &sp4C);
        if (v02 != NULL) {
            process_hit(arg0, arg1, v02);
            return;
        }
    }

    if (arg19->hasWingZone) {
        sp4C.x = arg19->wingTransform.world_matrix.w.x;
        sp4C.y = arg19->wingTransform.world_matrix.w.y;
        sp4C.z = arg19->wingTransform.world_matrix.w.z;
    } else {
        sp4C.x = arg19->thighPos->x;
        sp4C.y = arg19->thighPos->y;
        sp4C.z = arg19->thighPos->z;
    }

    sp44.x = arg19->shinPos->x;
    sp44.y = arg19->shinPos->y;
    sp44.z = arg19->shinPos->z;

    if (sp4C.y < arg09->shinPos->y) {
        a2 = arg09->strikeRadius;
    } else {
        a2 = arg09->comboRadius;
    }

    v0 = (arg1->currentStateDef->flags & STATE_FLAG_800) || (sp4C.y < -200);

    if (v0) {
        v02 = find_closest_hit_point(&sp54, sp5C, a2, &sp44, &sp4C);
        if (v02 != NULL) {
            process_hit(arg0, arg1, v02);
        }
    }
}

void check_ground_combo_hit(Player *arg0, Player *arg1) {
    HitboxBones *arg09;
    HitboxBones *arg19;
    Vec4s sp50;
    Vec4s sp48;
    Vec4s sp40;
    Vec4i sp30;
    Vec4s *v03;
    s32 pad;

    arg09 = &arg0->hitboxBones;
    arg19 = &arg1->hitboxBones;

    if (arg1->obj->pos.y < -20 ||
        arg1->obj->modInst->rootTransform.local_matrix.w.y < arg1->obj->modInst->baseRootPos.y) {
        return;
    }

    sp50.x = arg09->handPos->x;
    sp50.y = arg09->handPos->y;
    sp50.z = arg09->handPos->z;

    sp48.x = arg09->headPos->x;
    sp48.y = arg09->headPos->y;
    sp48.z = arg09->headPos->z;

    sp40.x = arg19->rootPos->x;
    sp40.z = arg19->rootPos->z;
    sp40.y = arg19->rootPos->y - 100.0f;

    sp30.x = arg19->rootPos->x;
    sp30.z = arg19->rootPos->z;
    sp30.y = arg19->rootPos->y;

    v03 = find_closest_hit_point(&sp40, &sp30, 80000, &sp50, &sp48);
    if (v03 != NULL) {
        process_hit(arg0, arg1, v03);
        return;
    }

    if (arg19->hasGrabZone) {
        sp40.x = arg19->grabTransform.world_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->grabTransform.world_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->torsoPos->x;
        sp40.y = -100;
        sp40.z = arg19->torsoPos->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    }

    if (arg19->hasTorsoZone) {
        sp40.x = arg19->torsoTransform.world_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->torsoTransform.world_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->footPos->x;
        sp40.y = -100;
        sp40.z = arg19->footPos->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 15000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    }
}

void check_air_combo_hit(Player *arg0, Player *arg1) {
    HitboxBones *arg09;
    HitboxBones *arg19;
    Vec4s sp50;
    Vec4s sp48;
    Vec4s sp40;
    Vec4i sp30;
    Vec4s *v03;

    arg09 = &arg0->hitboxBones;
    arg19 = &arg1->hitboxBones;

    if (arg1->obj->pos.y < -20 ||
        arg1->obj->modInst->rootTransform.local_matrix.w.y < arg1->obj->modInst->baseRootPos.y) {
        return;
    }

    sp50.x = arg09->handPos->x;
    sp50.y = arg09->handPos->y;
    sp50.z = arg09->handPos->z;

    sp48.x = arg09->headPos->x;
    sp48.y = arg09->headPos->y;
    sp48.z = arg09->headPos->z;

    sp40.x = arg19->rootPos->x;
    sp40.z = arg19->rootPos->z;
    sp40.y = arg19->rootPos->y - 100.0f;

    sp30.x = arg19->rootPos->x;
    sp30.z = arg19->rootPos->z;
    sp30.y = arg19->rootPos->y;

    v03 = find_closest_hit_point(&sp40, &sp30, 80000, &sp50, &sp48);
    if (v03 != NULL) {
        process_hit(arg0, arg1, v03);
        return;
    }

    if (arg19->hasWingZone) {
        sp40.x = arg19->wingTransform.world_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->wingTransform.world_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->thighPos->x;
        sp40.y = -100;
        sp40.z = arg19->thighPos->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    }

    if (arg19->hasLegZone) {
        sp40.x = arg19->legTransform.world_matrix.w.x;
        sp40.y = -100;
        sp40.z = arg19->legTransform.world_matrix.w.z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    } else {
        sp40.x = arg19->headPos->x;
        sp40.y = -100;
        sp40.z = arg19->headPos->z;

        sp30.x = sp40.x;
        sp30.y = 0;
        sp30.z = sp40.z;

        v03 = find_closest_hit_point(&sp40, &sp30, 50000, &sp50, &sp48);
        if (v03 != NULL) {
            process_hit(arg0, arg1, v03);
            return;
        }
    }
}

void init_player_hitboxes(Player *arg0, HitboxBoneSetup *arg1) {
    arg0->hitboxBones.handPos = &arg0->obj->modInst->transforms[arg1->handBoneId].world_matrix.w;
    arg0->hitboxBones.footPos = &arg0->obj->modInst->transforms[arg1->footBoneId].world_matrix.w;
    arg0->hitboxBones.torsoPos = &arg0->obj->modInst->transforms[arg1->torsoBoneId].world_matrix.w;
    arg0->hitboxBones.thighPos = &arg0->obj->modInst->transforms[arg1->thighBoneId].world_matrix.w;
    arg0->hitboxBones.headPos = &arg0->obj->modInst->transforms[arg1->headBoneId].world_matrix.w;
    arg0->hitboxBones.shinPos = &arg0->obj->modInst->transforms[arg1->shinBoneId].world_matrix.w;
    arg0->hitboxBones.armPos = &arg0->obj->modInst->transforms[arg1->armBoneId].world_matrix.w;
    arg0->hitboxBones.rootPos = &arg0->obj->modInst->transforms[0].world_matrix.w;

    if (arg1->headBoneId2 > 0) {
        arg0->hitboxBones.extraBonePos = &arg0->obj->modInst->transforms[arg1->headBoneId2].world_matrix.w;
        arg0->hitboxBones.hasHeadZone = TRUE;
    } else {
        arg0->hitboxBones.hasHeadZone = FALSE;
    }

    arg0->hitboxBones.strikeRadius = arg1->strikeRadius;
    arg0->hitboxBones.comboRadius = arg1->comboRadius;

    if (arg1->grabOffset.x != 0 || arg1->grabOffset.y != 0 || arg1->grabOffset.z != 0) {
        arg0->hitboxBones.hasGrabZone = TRUE;
        func_80012A20(&arg0->obj->modInst->transforms[arg1->grabParentBoneId], &arg0->hitboxBones.grabTransform, -3,
                      -3);
        arg0->hitboxBones.grabTransform.local_matrix.w.x = arg1->grabOffset.x;
        arg0->hitboxBones.grabTransform.local_matrix.w.y = arg1->grabOffset.y;
        arg0->hitboxBones.grabTransform.local_matrix.w.z = arg1->grabOffset.z;
    } else {
        arg0->hitboxBones.hasGrabZone = FALSE;
    }

    if (arg1->torsoOffset.x != 0 || arg1->torsoOffset.y != 0 || arg1->torsoOffset.z != 0) {
        arg0->hitboxBones.hasTorsoZone = TRUE;
        func_80012A20(&arg0->obj->modInst->transforms[arg1->torsoParentBoneId], &arg0->hitboxBones.torsoTransform, -3,
                      -3);
        arg0->hitboxBones.torsoTransform.local_matrix.w.x = arg1->torsoOffset.x;
        arg0->hitboxBones.torsoTransform.local_matrix.w.y = arg1->torsoOffset.y;
        arg0->hitboxBones.torsoTransform.local_matrix.w.z = arg1->torsoOffset.z;
    } else {
        arg0->hitboxBones.hasTorsoZone = FALSE;
    }

    if (arg1->tailOffset.x != 0 || arg1->tailOffset.y != 0 || arg1->tailOffset.z != 0) {
        arg0->hitboxBones.hasTailZone = TRUE;
        func_80012A20(&arg0->obj->modInst->transforms[arg1->headBoneId2], &arg0->hitboxBones.tailTransform, -3, -3);
        arg0->hitboxBones.tailTransform.local_matrix.w.x = arg1->tailOffset.x;
        arg0->hitboxBones.tailTransform.local_matrix.w.y = arg1->tailOffset.y;
        arg0->hitboxBones.tailTransform.local_matrix.w.z = arg1->tailOffset.z;
    } else {
        arg0->hitboxBones.hasTailZone = FALSE;
    }

    if (arg1->legOffset.x != 0 || arg1->legOffset.y != 0 || arg1->legOffset.z != 0) {
        arg0->hitboxBones.hasLegZone = TRUE;
        func_80012A20(&arg0->obj->modInst->transforms[arg1->headBoneId], &arg0->hitboxBones.legTransform, -3, -3);
        arg0->hitboxBones.legTransform.local_matrix.w.x = arg1->legOffset.x;
        arg0->hitboxBones.legTransform.local_matrix.w.y = arg1->legOffset.y;
        arg0->hitboxBones.legTransform.local_matrix.w.z = arg1->legOffset.z;
    } else {
        arg0->hitboxBones.hasLegZone = FALSE;
    }

    if (arg1->wingOffset.x != 0 || arg1->wingOffset.y != 0 || arg1->wingOffset.z != 0) {
        arg0->hitboxBones.hasWingZone = TRUE;
        func_80012A20(&arg0->obj->modInst->transforms[arg1->thighBoneId], &arg0->hitboxBones.wingTransform, -3, -3);
        arg0->hitboxBones.wingTransform.local_matrix.w.x = arg1->wingOffset.x;
        arg0->hitboxBones.wingTransform.local_matrix.w.y = arg1->wingOffset.y;
        arg0->hitboxBones.wingTransform.local_matrix.w.z = arg1->wingOffset.z;
    } else {
        arg0->hitboxBones.hasWingZone = FALSE;
    }
}
