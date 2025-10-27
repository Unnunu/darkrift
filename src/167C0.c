#include "common.h"
#include "camera.h"
#include "task.h"

extern s16 D_80049390;
extern Unk80015E74 D_8004C008[];
extern Unk80015E74 D_8004C0C8[];
extern u8 D_8004A42C;
extern s16 D_8004C1D0;

extern Object *D_8013C23C;
extern Object *D_80081440;
extern Object *D_80081444;
extern Object *D_80081448;
extern s32 D_8008144C;
extern s32 D_80081450;
extern Object *D_80081454;

void func_80016A00(Object *);
void func_800177C0(Object *);

void func_80015BC0(Object *obj) {
    D_8005BFC0 |= 0xC1;
    gGameMode = GAME_MODE_PLAYER_SELECTION;
    func_800194E0(50);
    if (D_800B6328[PLAYER_1].unk_02 != 0) {
        D_80049390 = D_800B6328[PLAYER_1].characterId;
    } else {
        D_80049390 = D_800B6328[PLAYER_2].characterId;
    }

    D_800B6328[PLAYER_1].unk_02 = D_800B6328[PLAYER_2].unk_02 = 0;
    D_800B6328[PLAYER_1].unk_08 = D_800B6328[PLAYER_2].unk_08 = 0;
    obj->flags |= 0x10;
}

void func_80015C58(Object *obj) {
    if (obj->spriteId >= obj->modInst->numAnimFrames) {
        if (--obj->vars[1] <= 0) {
            if (obj->vars[0] < obj->unk_088.a) {
                obj->unk_088.a -= obj->vars[0];
            } else {
                obj->unk_088.a = 0;
                obj->fn_render = func_80015BC0;
            }
        }
    } else {
        obj->spriteId++;
    }

    func_800386E8(obj);
}

void func_80015CD8(Object *obj) {
    if (--obj->vars[1] <= 0) {
        obj->flags &= ~4;
        if (obj->spriteId == 0 && obj->vars[2] != -1) {
            sound_play(2, obj->vars[2]);
        }

        if (obj->spriteId < obj->modInst->numAnimFrames - 1) {
            obj->spriteId++;
        }
    }
}

void func_80015D60(Object *obj) {
    obj->flags &= ~4;
    if (obj->spriteId == 0 && obj->vars[2] != -1) {
        sound_play(2, obj->vars[2]);
    }

    if (obj->spriteId >= obj->modInst->numAnimFrames) {
        if (--obj->vars[1] <= 0) {
            if (obj->vars[0] < obj->unk_088.a) {
                obj->unk_088.a -= obj->vars[0];
            } else {
                obj->unk_088.a = 0;
                obj->currentTask->flags |= 0x80;
                obj->flags |= 0x10;
            }
        }
    } else {
        obj->spriteId++;
    }
}

void func_80015E24(Object *obj) {
    if (--obj->vars[1] <= 0) {
        if (obj->vars[0] < obj->unk_088.a) {
            obj->unk_088.a -= obj->vars[0];
        } else {
            obj->currentTask->flags |= 0x80;
            obj->flags |= 0x10;
        }
    }
}

Object *func_80015E74(Unk80015E74 *arg0, s32 arg1) {
    Object *obj;
    Vec4i sp7C;
    UnkSam *a3;
    char sp28[80];

    sound_stop(2);
    str_copy(sp28, arg0->unk_00);
    str_concat(sp28, ".k2");

    a3 = gAssets[asset_find(sp28, arg1)].aux_data;
    sp7C.x = sp7C.y = sp7C.z = 0;
    obj = func_8002BFF0(&sp7C, 0x1000, arg0->unk_08, a3);

    if (obj != NULL) {
        obj->flags |= 0x1000000;

        obj->vars[1] = arg0->unk_04;
        obj->flags |= 0x800;
        if (arg0->unk_06 != 0) {
            obj->unk_088.a = 128;
            obj->vars[0] = arg0->unk_06;
            obj->flags |= 0x2000;
        }
        obj->vars[2] = arg0->unk_0C;
        obj->currentTask->counter = 2;
    }

    return obj;
}

void func_80015F60(Object *arg0, Object *arg1) {
    D_8013C23C->currentTask->func = func_80016A00;
    D_8013C23C->currentTask->counter = 0;
    D_8013C23C->currentTask->flags = 1;
    D_8013C23C->currentTask->counter = 30;
}

Object *func_80015FB4(s16 arg0) {
    Object *obj;

    obj = func_80015E74(D_8004C008 + arg0, 0xABAB);
    if (obj != NULL && arg0 == 3) {
        obj->unk_1E8 = func_80015F60;
        obj->unk_076 |= 8;
    }

    return obj;
}

Object *func_80016020(s32 characterId, s32 arg1, u32 playerId) {
    s32 unused;
    Object *obj;

    obj = func_80015E74(D_8004C0C8 + characterId, playerId);

    if (obj != NULL) {
        obj->currentTask->counter = arg1;
        obj->flags |= 4;
        if (D_800B6328[playerId].unk_02 != 0) {
            obj->vars[2] = 7;
        }
    }

    sound_set_pan(0, 64);
    sound_set_pan(1, 64);
    D_8004A42C = TRUE;
    return obj;
}

u16 func_800160C8(s32 arg0) {
    Unk80015E74 *a0;
    Object *obj;

    if (D_800B6328[PLAYER_1].unk_08 == D_8004C1D0 - 1 && D_800B6328[PLAYER_2].unk_08 == D_8004C1D0 - 1) {
        a0 = &D_8004C008[5];
    } else {
        a0 = &D_8004C008[6];
    }
    obj = func_80015E74(a0, 0xABAB);
    if (obj != NULL) {
        obj->spriteId = arg0 * 2;
    }
    return a0->unk_04;
}

void func_80016144(Object *obj) {
    Object *unkObj;

    obj->flags &= ~4;
    if ((gPlayerInput[1 - D_8013C24C].buttons & INP_DIRECTION) && obj->vars[1] == 0) {
        if (obj->spriteId < obj->modInst->numAnimFrames) {
            obj->spriteId += 30;
        }
        unkObj = D_8013C23C->varObj[5];
        unkObj->vars[1] -= 30;
    }

    obj->vars[1] = gPlayerInput[1 - D_8013C24C].buttons; // probably @bug

    if (obj->spriteId >= obj->modInst->numAnimFrames) {
        if (--obj->vars[1] <= 0) {
            if (obj->vars[0] < obj->unk_088.a) {
                obj->unk_088.a -= obj->vars[0];
            } else {
                obj->unk_088.a = 0;
                obj->currentTask->flags |= 0x80;
                obj->flags |= 0x10;
            }
        }
    } else {
        obj->spriteId++;
    }
}

void func_80016264(void) {
    Object *obj;

    for (obj = D_80052C50; obj != NULL; obj = obj->nextObject) {
        if ((obj->flags & 0x4000) || (obj->flags & 2)) {
            obj->flags |= 0x10;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800162A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_8001675C.s")
u32 func_8001675C(Player *arg0, s32 arg1, s32 arg2);

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800167D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016880.s")
void func_80016880(Object *obj);

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800168F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800169C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016C34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016D90.s")
ObjFunc func_80016D90(s32 arg0, u8 arg1);

void func_80016F6C(Object *obj) {
    s32 sp2C;
    ObjFunc v02;

    sp2C = func_8001675C(&gPlayers[D_8013C24C], (gFrameCounter & 1) ? 0x84 : 0xF7, 0x78);
    func_80016264();
    obj->varObj[4] = D_80081440 = func_80016020(gPlayers[D_8013C24C].characterId, 6, D_8013C24C);
    v02 = func_80016D90(D_8013C24C, 0);

    obj->vars[0] = sp2C + 0x78;
    obj->vars[1] = 10;
    obj->vars[2] = 0xbe;
    obj->currentTask->func = v02;

    D_8005BFC0 &= ~0x200;
    gPlayers[1 - D_8013C24C].unk_00->flags |= 4;
    gPlayers[D_8013C24C].unk_00->pos.x = gPlayers[D_8013C24C].unk_00->pos.y = gPlayers[D_8013C24C].unk_00->pos.z = 0;
    gPlayers[1 - D_8013C24C].unk_00->pos.x = gPlayers[1 - D_8013C24C].unk_00->pos.y =
        gPlayers[1 - D_8013C24C].unk_00->pos.z = 0;

    gPlayers[PLAYER_1].unk_00->rotation.y = 0;
    gPlayers[PLAYER_1].unk_80 |= 0x400000;
    gPlayers[PLAYER_2].unk_80 |= 0x400000;

    gCameraTarget.x = gCameraTarget.z = 0;
    gCameraTarget.y = -400;

    if (D_800B6328[D_8013C24C].characterId != MORPHIX) {
        gPlayers[D_8013C24C].unk_00->flags |= 0x10000000;
    }

    gPlayers[D_8013C24C].unk_00->flags &= ~0x8800000;
}

void func_800171EC(Object *obj) {
    s32 pad;
    Object *v0;
    ObjFunc a3;

    v0 = func_80015FB4(4);
    a3 = func_80016880;

    if (v0 != NULL) {
        v0->currentTask->counter = 5;
    }

    D_80081444 = v0;

    func_8001675C(&gPlayers[PLAYER_2], 0x180, func_8001675C(&gPlayers[PLAYER_1], 0x180, 0x78));

    if (D_8004C1D0 == D_800B6328[PLAYER_1].unk_08 + 1) {
        a3 = func_80016D90(PLAYER_1, 1);
    } else {
        D_800B6328[PLAYER_1].unk_08++;
    }

    if (D_8004C1D0 == D_800B6328[PLAYER_2].unk_08 + 1) {
        a3 = func_80016D90(PLAYER_2, 1);
    } else {
        D_800B6328[PLAYER_2].unk_08++;
    }

    obj->vars[0] = 0xf5;
    obj->vars[1] = 10;
    obj->vars[2] = 0xbe;
    obj->varObj[4] = v0;

    obj->currentTask->func = a3;
}

void func_80017304(Object *obj) {
    Object *a0;

    if (--obj->vars[0] > 0) {
        if ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START)) {
            a0 = obj->varObj[4];
            a0->flags |= 0x10;

            if (gPlayerInput[PLAYER_1].buttons & INP_START) {
                gPlayerInput[PLAYER_1].unk_08 = FALSE;
            }
            if (gPlayerInput[PLAYER_2].buttons & INP_START) {
                gPlayerInput[PLAYER_2].unk_08 = FALSE;
            }
        } else {
            return;
        }
    }

    if (D_8013C24E) {
        obj->currentTask->func = func_800171EC;
    } else {
        gPlayerInput[1 - D_8013C24C].unk_0A = FALSE;
        gPlayerInput[1 - D_8013C24C].buttons = 0;
        obj->currentTask->func = func_80016F6C;
    }
}

void func_800173DC(Object *obj) {
    if (gPlayers[PLAYER_1].unk_80 & 0x80) {
        if (--gPlayers[PLAYER_1].unk_94 > 20) {
            gPlayers[PLAYER_1].unk_94 = 20;
        } else {
            func_8000642C(&gPlayers[PLAYER_1], TRUE);
        }
    } else if (gPlayers[PLAYER_2].unk_80 & 0x80) {
        if (--gPlayers[PLAYER_2].unk_94 > 20) {
            gPlayers[PLAYER_2].unk_94 = 20;
        } else {
            func_8000642C(&gPlayers[PLAYER_2], TRUE);
        }
    } else if ((gPlayers[PLAYER_1].unk_80 & 0x40000) && (gPlayers[PLAYER_2].unk_80 & 0x40000)) {
        if ((gPlayers[PLAYER_1].unk_90->unk_34 & 1) && gPlayers[PLAYER_1].unk_7E != 4) {
            func_8000636C(&gPlayers[PLAYER_1], 320, FALSE);
        } else if (gPlayers[PLAYER_1].unk_7E != 17) {
            func_8000636C(&gPlayers[PLAYER_1], 68, FALSE);
        }

        if ((gPlayers[PLAYER_2].unk_90->unk_34 & 1) && gPlayers[PLAYER_2].unk_7E != 4) {
            func_8000636C(&gPlayers[PLAYER_2], 320, FALSE);
        } else if (gPlayers[PLAYER_2].unk_7E != 17) {
            func_8000636C(&gPlayers[PLAYER_2], 68, FALSE);
        }

        gPlayerInput[PLAYER_1].unk_0A = gPlayerInput[PLAYER_2].unk_0A = TRUE;

        obj->currentTask->func = func_80017304;
        obj->currentTask->counter = 10;
        obj->vars[0] = 80;
        D_80080234 = TRUE;
    }
}

void func_800175B0(Object *obj) {
    if (D_80080234) {
        obj->currentTask->func = func_800177C0;
    }
}

void func_800175D8(Object *obj) {
    if (++obj->vars[0] & 8) {
        obj->flags &= ~4;
    } else {
        obj->flags |= 4;
    }
}

void func_80017614(Object *obj) {
    if (D_80080234) {
        obj->flags |= 0x10;
    }
    func_800175D8(obj);
}

void func_80017650(Object *obj) {
    UIElement sp60 = { 0x26, func_80017614, 0x4000000, 0x1001, "bars.sp2" };
    Vec4i sp50 = { 250, 220, 0, 0 };

    gPlayerInput[D_8013C24C].unk_0A = TRUE;
    D_8005BFC0 &= ~0x200;
    if (TRUE) {
        D_80080234 = TRUE;
    }
    obj->currentTask->func = func_800177C0;
    obj->currentTask->counter = 45;
    func_80016264();
}

void func_80017728(Object *obj) {
    Object *a0;

    if (--obj->vars[0] > 0) {
        if (gPlayerInput[D_8013C24C].buttons & INP_START) {
            a0 = obj->varObj[4];
            if (a0 != NULL) {
                a0->flags |= 0x10;
            }

            if (gPlayerInput[PLAYER_1].buttons & INP_START) {
                gPlayerInput[PLAYER_1].unk_08 = FALSE;
            }
            if (gPlayerInput[PLAYER_2].buttons & INP_START) {
                gPlayerInput[PLAYER_2].unk_08 = FALSE;
            }
        } else {
            return;
        }
    }

    obj->currentTask->func = func_80017650;
}

void func_800177C0(Object *obj) {
    D_8005BFC0 &= ~0x200;

    if (!D_80080234) {
        if (gPlayers[PLAYER_1].unk_00->unk_070 == D_800B6328[PLAYER_1].unk_0C &&
                gPlayers[PLAYER_2].unk_00->unk_070 == 0 ||
            gPlayers[PLAYER_1].unk_00->unk_070 == 0 &&
                gPlayers[PLAYER_2].unk_00->unk_070 == D_800B6328[PLAYER_2].unk_0C) {
            obj->varObj[4] = D_80081448 = func_80015FB4(11);
            obj->vars[0] = 90;
            gPlayerInput[D_8013C24C].unk_0A = TRUE;
            obj->currentTask->func = func_80017728;
        } else {
            obj->currentTask->func = func_80017650;
        }
    } else {
        gPlayerInput[D_8013C24C].unk_0A = TRUE;
        if (D_8013C24E) {
            gPlayerInput[1 - D_8013C24C].unk_0A = TRUE;
            obj->currentTask->func = func_800171EC;
        } else {
            obj->currentTask->func = func_80016F6C;
        }
    }
}

void func_8001792C(Object *obj) {
    Object *newObj;

    if (D_800801F0 || gPlayers[PLAYER_1].unk_00->unk_070 <= 0 || gPlayers[PLAYER_2].unk_00->unk_070 <= 0) {
        func_80029044();
        D_800801F0 = TRUE;
        if (!(D_8005BFC0 & 4)) {
            D_8005BFC0 |= 4;
            return;
        }

        gPlayerInput[PLAYER_1].unk_0A = gPlayerInput[PLAYER_2].unk_0A = FALSE;
        if (gPlayers[PLAYER_1].unk_00->unk_070 > gPlayers[PLAYER_2].unk_00->unk_070) {
            D_8013C24C = PLAYER_1;
        } else {
            D_8013C24C = PLAYER_2;
        }

        D_8013C24E = (gPlayers[PLAYER_1].unk_00->unk_070 == gPlayers[PLAYER_2].unk_00->unk_070);

        if (D_800801F0 && gPlayers[PLAYER_1].unk_00->unk_070 != 0 && gPlayers[PLAYER_2].unk_00->unk_070 != 0) {
            newObj = func_80015FB4(10);
            D_80081454 = newObj;
            obj->varObj[4] = newObj;
            obj->currentTask->func = func_800173DC;
        } else {
            obj->currentTask->func = func_800177C0;
        }

        D_80080234 = FALSE;
        obj->currentTask->counter = 45;
    }
}

void func_80017A90(Object *obj) {
    D_8005BFC0 |= 4;
    gPlayerInput[PLAYER_1].unk_0A = gPlayerInput[PLAYER_2].unk_0A = TRUE;

    if (++obj->vars[0] > 900) {
        gGameMode = GAME_MODE_29;
        D_8005BFC0 |= 1;
        obj->flags |= 0x10;
    } else if ((gPlayerInput[PLAYER_1].buttons & INP_START) || (gPlayerInput[PLAYER_2].buttons & INP_START)) {
        D_8005BFC0 |= 1;
        gGameMode = GAME_MODE_0;
        obj->flags |= 0x10;
    }
}

void func_80017B3C(Object *obj) {
    if (D_80080230 == 30) {
        obj->currentTask->func = func_80017A90;
        obj->vars[0] = 0;
        D_8005BFC0 |= 4;
    } else {
        obj->currentTask->func = func_8001792C;
        D_8005BFC0 &= ~4;
    }

    gPlayerInput[PLAYER_1].unk_0A = gPlayerInput[PLAYER_2].unk_0A = TRUE;
    gPlayers[PLAYER_1].unk_80 &= ~0x100000;
    gPlayers[PLAYER_2].unk_80 &= ~0x100000;

    if (D_800B6328[PLAYER_1].unk_02) {
        gPlayers[PLAYER_1].unk_180 &= ~0x20000;
    }
    if (D_800B6328[PLAYER_2].unk_02) {
        gPlayers[PLAYER_2].unk_180 &= ~0x20000;
    }

    func_80028FCC();
}

void func_80017C3C(Object *obj) {
    obj->currentTask->func = func_80017B3C;
    obj->currentTask->counter = func_80015FB4(0)->modInst->numAnimFrames + 20;
}

void func_80017C88(Object *obj) {
    task_execute(obj);
}

void func_80017CA8(void) {
    D_8013C23C = create_worker(func_80017C88, 1);
    D_800801F0 = FALSE;
    D_8013C834 = 0;

    gPlayerInput[PLAYER_1].unk_0A = gPlayerInput[PLAYER_2].unk_0A = FALSE;
    gPlayers[PLAYER_1].unk_80 |= 0x100000;
    gPlayers[PLAYER_2].unk_80 |= 0x100000;
    D_8013C250 = FALSE;
    D_80080234 = FALSE;

    if (D_800B6328[PLAYER_1].unk_02) {
        gPlayers[PLAYER_1].unk_180 |= 0x20000;
    }
    if (D_800B6328[PLAYER_2].unk_02) {
        gPlayers[PLAYER_2].unk_180 |= 0x20000;
    }

    D_8013C23C->currentTask->func = func_80017C3C;
    D_8013C23C->currentTask->counter = 0;
    D_8013C23C->currentTask->flags = 1;
    D_8013C23C->currentTask->counter = func_800160C8(D_800B6328[PLAYER_1].unk_08 + D_800B6328[PLAYER_2].unk_08);
    D_80081440 = D_80081448 = D_8008144C = D_80081450 = D_80081454 = D_80081444 = NULL;
}
