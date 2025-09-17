#include "common.h"

extern s16 D_80049390;
extern Object *D_8013C23C;
extern Unk80015E74 D_8004C008[];
extern Unk80015E74 D_8004C0C8[];
extern u8 D_8004A42C;
extern s16 D_8004C1D0;
extern Unk80015E74 D_8004C058;
extern Unk80015E74 D_8004C068;

void func_80016A00(Object *);

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

Object *func_80015FB4(vs16 arg0) { // fake match ?
    Object *obj;

    obj = func_80015E74(&D_8004C008[arg0], 0xABAB);
    if (obj != NULL && arg0 == 3) {
        obj->unk_1E8 = func_80015F60;
        obj->unk_076 |= 8;
    }

    return obj;
}

Object *func_80016020(s32 arg0, s32 arg1, s32 arg2) {
    s32 unused;
    Object *obj;

    obj = func_80015E74(&D_8004C0C8[arg0], arg2);

    if (obj != NULL) {
        obj->currentTask->counter = arg1;
        obj->flags |= 4;
        if (D_800B6328[arg2].unk_02 != 0) {
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
        a0 = &D_8004C058;
    } else {
        a0 = &D_8004C068;
    }
    obj = func_80015E74(a0, 0xABAB);
    if (obj != NULL) {
        obj->spriteId = arg0 * 2;
    }
    return a0->unk_04;
}

extern u16 D_8013C24C;

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

    obj->vars[1] = gPlayerInput[1 - D_8013C24C].buttons; // probably bug

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

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800167D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016880.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800168F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800169C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016C34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016D90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80016F6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800171EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017304.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800173DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800175B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800175D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017614.s")

const char D_800547F4[] = "bars.sp2";

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017650.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_800177C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_8001792C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017A90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017B3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017C3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/167C0/func_80017CA8.s")
