#include "common.h"

typedef struct Unk_8004BA6C {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} Unk_8004BA6C; // size = 0xC

extern Unk_8004BA6C *D_8004BA40[];
extern Unk_8004BA6C *D_8004BA6C[];

extern s32 D_8013C3C8[];

void func_80031E4C(Unk_8004BA6C *, char *, Object *);

#pragma GLOBAL_ASM("asm/nonmatchings/322A0/func_800316A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/322A0/func_80031724.s")

#pragma GLOBAL_ASM("asm/nonmatchings/322A0/func_8003184C.s")

void func_80031D4C(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA40[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->spriteId == s0->unk_00) {
            func_80031E4C(s0, v0->unk_198, obj);
        }
    }
}

void func_80031DCC(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    Unk_8004BA6C *s0;

    for (s0 = D_8004BA6C[v0->characterId]; s0->unk_00 != 0; s0++) {
        if (obj->spriteId == s0->unk_00) {
            func_80031E4C(s0, v0->unk_198, obj);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/322A0/func_80031E4C.s")

void func_80031F24(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (v0->characterId == AARON) {
        obj->currentTask->func = func_80021E34;
    } else {
        obj->currentTask->flags |= 0x80;
    }
}

void func_80031F60(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    func_800063C4(v0, 382, 1);
}

void func_80031F88(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (obj->spriteId == v0->unk_90->unk_02 - 2) {
        obj->currentTask->func = func_80031F60;
    }
}

void func_80031FBC(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (v0->unk_80 & 8) {
        func_800063C4(v0, 383, 1);
    } else {
        obj->currentTask->counter = 60;
        obj->currentTask->func = func_80031F60;
    }
}

void func_8003201C(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    func_800063C4(v0, 140, 1);
}

void func_80032044(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];

    if (D_800B6328[PLAYER_1].characterId == D_800B6328[PLAYER_2].characterId && v0->unk_04 != 0) {
        obj->currentTask->counter = 15;
    }

    obj->currentTask->func = func_8003201C;
}

void func_8003208C(Object *obj) {
    Vec4i sp20;
    Player *v0 = (Player *) obj->varObj[0];
    s32 v1 = v0->unk_04;

    if (obj->spriteId == v0->unk_90->unk_02 - 1) {
        sp20.x = sp20.y = 0;
        sp20.z = -D_8013C3C8[v1];
        func_8001370C(&sp20, &obj->rotation);
        obj->pos.x += sp20.x;
        obj->pos.z += sp20.z;
        obj->currentTask->func = func_80021DC4;
    }

    func_80021DC4(obj);
}

void func_80032130(Object *obj) {
    Player *v0 = (Player *) obj->varObj[0];
    s32 v1 = v0->unk_04;

    if (v0->characterId == DEMITRON && obj->spriteId > 50) {
        func_80021DC4(obj);
        obj->currentTask->func = func_80021DC4;
    } else {
        D_8013C3C8[v1] = D_80080210;
        func_80021E34(obj);
        obj->currentTask->func = func_8003208C;
    }
}
