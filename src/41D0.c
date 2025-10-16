#include "common.h"
#include "task.h"
#include "camera.h"

typedef struct UnkOmicronSub {
    /* 0x00 */ s16 unk_00[2];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
} UnkOmicronSub; // size=0x8

typedef struct UnkOmicron {
    /* 0x0000 */ UnkOmicronSub unk_00[512];
    /* 0x1000 */ u16 unk_1000;
    /* 0x1002 */ u16 unk_1002;
    /* 0x1004 */ s32 unk_1004;
    /* 0x1008 */ s32 unk_1008;
} UnkOmicron;

typedef struct UnkQwe {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ char *unk_04;
} UnkQwe; // size = 8

extern s16 D_8004A730[];
extern s16 D_8004A748[];
extern char D_8004B654[]; // TODO: type
extern char D_8004B674[]; // TODO: type
extern char D_8004B774[]; // TODO: type
extern char D_8004B794[]; // TODO: type
extern UnkQwe D_8004B94C[];
extern PlayerSub5 D_8004C1E8[];

extern s32 D_80080218;
extern UnkOmicron D_80080238;
extern s32 D_80081240;

void func_80012150(PlayerSub6 *arg0, ModelInstance *arg1, Matrix4f *arg2, Matrix4f *arg3, Vec4i *arg4, s32 *arg5);

void func_80005B70(s16 playerId);
void func_80003C04(Object *obj);

typedef struct AssetDB {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
} AssetDB; // size = 0x44

extern s16 D_8004B9FC[];

#ifdef NON_MATCHING
void func_800035D0(Player *player) {
    UnkOmicronSub *a1;
    u16 t8;
    u16 a2;
    Object *v0;
    s32 v1;
    s32 nv, nv2, nv3;

    v0 = player->unk_00;

    if (D_80080236 || D_800801F0) {
        return;
    }
    v1 = D_80080238.unk_1002;
    a1 = D_80080238.unk_00 + v1;
    a1->unk_04 = player->unk_78;
    a1->unk_06 = player->playerId;
    a1->unk_07 = 255;

    a2 = player->playerId;
    t8 = 1 - player->playerId;
    a1->unk_00[a2] = v0->unk_070;
    a1->unk_00[t8] = gPlayers[t8].unk_00->unk_070;

    nv = D_80080238.unk_1002;
    nv2 = (nv - 1) & 0x1FF;
    D_80080238.unk_00[nv2].unk_07 = gFrameCounter - D_80080238.unk_1004;
    nv = (nv + 1) & 0x1FF;
    D_80080238.unk_1002 = nv;
    D_80080238.unk_1004 = gFrameCounter;

    if (D_80080238.unk_1000 == nv) {
        D_80080234 = 1;
        D_80080238.unk_1000 = (D_80080238.unk_1000 + 1) & 0x1FF;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800035D0.s")
void func_800035D0(Player *player);
#endif

void func_800036E8(Object *obj) {
    obj->flags |= 0x10;
    D_80080234 = 1;
}

void func_80003704(Object *obj) {
    if (gPlayers[1 - D_8013C24C].unk_00->unk_070 <= 0 || --obj->vars[0] <= 0) {
        obj->currentTask->counter = 55;
        obj->currentTask->func = func_800036E8;
    }
}

#ifdef NON_EQUIVALENT
void func_80003780(Object *obj) {
    s32 s0;
    UnkOmicronSub *s1;
    s32 s3;

    while (TRUE) {
        s0 = D_80080238.unk_1000;
        s1 = &D_80080238.unk_00[s0];
        s3 = s1->unk_06;
        gPlayers[s3].unk_80 |= 0x800000;
        func_80005EE4(gPlayers + s1->unk_06, TRUE, s1->unk_04);
        gPlayers[s3].unk_00->unk_070 = s1->unk_00[s3];
        if (s1->unk_00[s3] == 0) {
            D_8005BFC0 |= 0x200;
        }

        if (s1->unk_07 == 255) {
            break;
        }

        D_80080238.unk_1000 = (s0 + 1) & 0xFDFF; // ???
        if (s1->unk_07 != 0) {
            obj->currentTask->counter = s1->unk_07 - 1;
            return;
        }
    }

    obj->currentTask->func = func_80003704;
    obj->vars[0] = 260;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003780.s")
void func_80003780(Object *obj);
#endif

void func_800038C8(Object *obj) {
    task_execute(obj);

    if (gPlayerInput[D_8013C24C].buttons & INP_START) {
        obj->flags |= 0x10;
        D_80080234 = 1;
        D_8013C23C->currentTask->counter = 0;
        D_8013C23C->currentTask->func = func_800177C0;
        gPlayerInput[D_8013C24C].unk_08 = FALSE;
    }
}

#ifdef NON_MATCHING
s32 func_80003974(void *arg0) {
    s32 s3;
    Object *v0;
    u32 i;
    s32 temp;

    s3 = gFrameCounter - D_80080238.unk_1008;

    D_80080238.unk_1000 = 0;
    D_8013C250 = 1;
    gPlayers[PLAYER_1].unk_7E = 0;
    gPlayers[PLAYER_2].unk_7E = 0;

    func_80005B70(PLAYER_1);
    func_80005B70(PLAYER_2);
    gPlayers[PLAYER_1].unk_00->spriteId = 2;
    gPlayers[PLAYER_2].unk_00->spriteId = 2;
    func_80037500(gPlayers[PLAYER_1].unk_00);
    func_80037500(gPlayers[PLAYER_2].unk_00);

    func_80012AF4(&gPlayers[PLAYER_1].unk_750.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_1].unk_868.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_2].unk_750.local_matrix);
    func_80012AF4(&gPlayers[PLAYER_2].unk_868.local_matrix);

    func_8003635C(gPlayers[PLAYER_1].unk_00);
    func_8003635C(gPlayers[PLAYER_2].unk_00);
    gPlayers[PLAYER_1].unk_00->unk_086 = gPlayers[PLAYER_1].unk_00->spriteId;
    gPlayers[PLAYER_2].unk_00->unk_086 = gPlayers[PLAYER_2].unk_00->spriteId;
    gPlayers[PLAYER_1].unk_0C->flags &= ~4;
    gPlayers[PLAYER_2].unk_0C->flags &= ~4;

    D_8008020C = 0x800;
    func_8002DA08(gCamera);
    gCamera->currentTask->func = func_8002EB2C;
    gCamera->currentTask->counter = 0;
    gCameraTarget.x = 0;
    gCameraTarget.z = 0;
    gCameraTarget.y = -400;
    D_8013C834 = FALSE;

    temp = guRandom() % 2;

    if (temp) {}

    v0 = create_worker(func_800038C8, -0x7001 + temp * 0);
    v0->currentTask->func = func_80003780;
    v0->currentTask->counter = 0;
    v0->currentTask->flags = 1;

    D_8008012C |= 1;
    D_8005BFC0 &= ~0x200;

    if (s3 > 960) {
        s3 -= 960;
        for (i = 0; i < s3; i++) {
            func_80003C04(gPlayers[PLAYER_1].unk_00);
            func_80003C04(gPlayers[PLAYER_2].unk_00);
            func_800038C8(v0);
        }

        func_8002D278(gCamera, TRUE);
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80003974.s")
s32 func_80003974(void *arg0);
#endif

s32 func_80003BB4(void) {
    s32 diff = gFrameCounter - D_80081240;

    if (diff < 60) {
        return FALSE;
    } else {
        func_800028E0(func_80003974, NULL);
        return TRUE;
    }
}

void func_80003C04(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    s32 unused[7];
    ModelInstance *sp20 = obj->modInst;

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    task_execute(obj);

    if (sp20->currentAnimId != sp20->unk_A0E) {
        func_80037500(obj);
        sp20->unk_A0E = sp20->currentAnimId;
    }

    if (obj->spriteId != obj->unk_086) {
        func_800371C0(obj);
        func_8003635C(obj);
        obj->unk_086 = obj->spriteId;
    }

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    if (player->unk_184) {
        if (player->unk_94 != 0 && --player->unk_94 == 0) {
            func_8000642C(player, TRUE);
        } else if (!(player->unk_80 & 0x100400) && gPlayerInput[playerId].unk_08 && player->unk_76 >= 0 &&
                   !(player->unk_0C->flags & 4)) {
            func_8000642C(player, FALSE);
        }
    }

    player->unk_184 = TRUE;
}

void func_80003DA4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 sp4A = player->playerId;
    u16 oppId;
    Player *sp24;
    PlayerSub3 *sp40;
    PlayerSub3 *sp3C;
    s32 pad[2];
    Object *sp30;
    u8 pad2;
    u8 sp2E;

    sp40 = player->unk_90;
    oppId = 1 - sp4A;
    sp24 = &gPlayers[oppId];
    sp3C = sp24->unk_90;
    sp30 = sp24->unk_00;

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    func_800386E8(obj);

    if (func_80030BB0(obj)) {
        player->unk_80 |= 8;
    } else {
        player->unk_80 &= ~8;
    }

    sp2E = (sp40->unk_20 != 0) && (obj->spriteId >= sp40->unk_24) && (obj->spriteId < sp40->unk_26);

    func_800115A0(&player->unk_DE8, (sp40->unk_34 & 0x40) && sp2E);
    if (player->unk_5F4A) {
        func_800115A0(&player->unk_2240, (sp40->unk_34 & 0x2000) && sp2E);
    }
    func_800115A0(&player->unk_3698, (sp40->unk_34 & 0x800) && sp2E);
    func_800115A0(&player->unk_4AF0, (sp40->unk_34 & 0x1020) && sp2E);

    if (player->characterId != MORPHIX) {
        func_80037E28(obj);
    }

    if (!gTasksDisabled) {
        if (D_80080230 == 40) {
            if (D_8013C430 == 16) {
                func_800338D0();
            } else if (D_8013C430 == 18) {
                func_80033D64();
            }
            if (D_8013C434 == 66) {
                func_80033D64();
            }
        }

        if (D_800B6328[sp4A].unk_02 && !D_800801F0 && !(player->unk_80 & 0x100000)) {
            if (!(player->unk_180 & 0x20000)) {
                func_8001B810(player);
            }
            if (D_8013C444 && gPlayerInput[sp4A].unk_08 && player->unk_76 >= 0 && !(player->unk_0C->flags & 4) &&
                !(player->unk_80 & 0x2000)) {
                func_8000642C(player, FALSE);
            }
        } else if (player->unk_184 && !D_800801F0) {
            if (player->unk_94 != 0 && --player->unk_94 == 0) {
                func_8000642C(player, TRUE);
            } else if (!(player->unk_80 & 0x100400) && gPlayerInput[sp4A].unk_08 && player->unk_76 >= 0 &&
                       !(player->unk_0C->flags & 4)) {
                func_8000642C(player, FALSE);
            }
        }

        if (player->unk_5F48 > 0) {
            player->unk_5F48--;
        }

        if (D_80080218 >= D_80080210 && !(player->unk_90->unk_34 & 0x40000) && player->unk_5F48 == 0 &&
            sp30->spriteId >= sp3C->unk_04 && sp30->spriteId <= sp3C->unk_06) {
            if (sp3C->unk_34 & 0x2040) {
                if ((player->unk_90->unk_34 & 0x30400) && obj->modInst->unk_010.wolrd_matrix.w.y > -100.0f) {
                    func_8000FE9C(player, sp24);
                } else {
                    func_8000F494(player, sp24);
                }
            }

            if (player->unk_5F48 == 0 && (sp3C->unk_34 & 0x1820)) {
                if ((player->unk_90->unk_34 & 0x30400) && obj->modInst->unk_010.wolrd_matrix.w.y > -100.0f) {
                    func_80010280(player, sp24);
                } else {
                    func_8000FB30(player, sp24);
                }
            }
        }

        player->unk_184 = TRUE;
    }
}

void func_80004304(char *arg0, char *arg1, char *arg2) {
    str_copy(arg0, arg1);
    str_concat(arg0, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80004334.s")
void func_80004334(AssetDB *, s16);

void func_800045B4(s16 playerId, s16 characterId) {
    char sp94[20];
    char sp80[20];
    PlayerSub3 *s0;
    s32 *pad3;
    s32 *sp74;
    Player *player;
    ModelInstance *modInst;
    s16 a12;
    Player12 *sp44;
    AssetDB *s3;
    s32 i;
    s32 pad;
    s16 q;
    s16 v03; // sp54?
    s16 pad2;
    s16 sp50;

    player = &gPlayers[playerId];
    modInst = player->unk_00->modInst;
    sp44 = &D_800B6328[playerId];
    sp50 = D_800B6328[1 - playerId].characterId;

    if (sp44->unk_10) {
        str_copy(sp80, "dum.db");
    } else {
        func_80004304(sp80, D_8004B844[characterId].unk_04->unk_00, ".db");
    }

    s3 = (AssetDB *) gAssets[asset_find(sp80, playerId)].data;
    player->unk_28 = s3->unk_00 + (u32) s3;
    player->unk_2C = pad = s3->unk_04 + 4 + (u32) s3;
    player->unk_34 = s3->unk_08 + (u32) s3;
    player->unk_30 = s3->unk_0C + (u32) s3;
    player->unk_1C = s3->unk_10 + (u32) s3;

    sp74 = s3->unk_14 + (u32) s3;
    if (sp44->unk_10) {
        *sp74 = 0;
    }
    player->unk_20 = s0 = (u32) s3 + s3->unk_14 + 4;

    player->unk_40 = pad = s3->unk_18 + (u32) s3 + 4;
    pad3 = s3->unk_1C + (u32) s3;
    player->unk_6C = *pad3;
    if (((!player->unk_00) && (!player->unk_00)) & 0xFFFFFFFFu) {} // @fake
    player->unk_38 = s3->unk_20 + (u32) s3;
    player->unk_44 = s3->unk_24 + (u32) s3;
    player->unk_48 = s3->unk_28 + (u32) s3;
    player->unk_4C = s3->unk_2C + (u32) s3;
    player->unk_68 = s3->unk_40 + (u32) s3;

    str_copy(sp94, D_8004B94C[sp50].unk_04);
    str_concat(sp94, ".MOV");
    if ((v03 = asset_find(sp94, 0x5000 + playerId)) > 0) {
        q = D_8004B94C[sp50].unk_00;
        a12 = s0[q].unk_08;
        modInst->animations[a12] = gAssets[v03].data;
        s0[q].unk_02 = func_80037394(modInst, a12) - 1;
    }

    str_copy(sp94, D_8004B94C[11 + sp50].unk_04);
    str_concat(sp94, ".MOV");
    if ((v03 = asset_find(sp94, 0x5000 + playerId)) > 0) {
        q = D_8004B94C[11 + sp50].unk_00;
        a12 = s0[q].unk_08;
        modInst->animations[a12] = gAssets[v03].data;
        if (sp50 != AARON) {
            s0[q].unk_02 = func_80037394(modInst, a12) - 1;
        }

        q = D_8004B9FC[sp50];
        a12 = s0[q].unk_08;
        modInst->animations[a12] = gAssets[v03].data;
        s0[q].unk_02 = func_80037394(modInst, a12) - 1;
    }

    player->unk_7E = 0;

    for (i = 0; i < *sp74; i++, s0++) {
        if (s0->unk_02 == -1) {
            s0->unk_02 = func_80037394(modInst, s0->unk_08) - 1;
        } else if (func_80037394(modInst, s0->unk_08) < s0->unk_02) {
            s0->unk_02 = func_80037394(modInst, s0->unk_08) - 1;
        }

        if (s0->unk_24 == -1 || s0->unk_26 == -1) {
            s0->unk_24 = s0->unk_04 + 3;
            s0->unk_26 = s0->unk_06 - 1;
            do {
            } while (0); // @fake
        }
    }

    if (sp44->unk_02) {
        func_80004334(s3, playerId);
    }

    if (sp44->unk_0E) {
        if (sp44->unk_10) {
            str_copy(sp80, "dum.sym");
        } else {
            func_80004304(sp80, D_8004B844[characterId].unk_04->unk_00, ".sym");
        }
        s3 = (AssetDB *) gAssets[asset_find(sp80, playerId)].data;
        player->unk_9A8 = s3->unk_00 + (u32) s3;
        player->unk_9AC = s3->unk_04 + (u32) s3;
        player->unk_9B0 = s3->unk_08 + (u32) s3;
        player->unk_9B4 = s3->unk_0C + (u32) s3;
    }
}

void func_80004AE0(Transform *arg0) {
    Transform *next;
    Transform *prev;

    prev = arg0->parent->firstChild;

    if (prev == arg0) {
        arg0->parent->firstChild = arg0->nextSibling;
        arg0->nextSibling = NULL;
        return;
    }

    next = prev->nextSibling;
    while (arg0 != next) {
        prev = next;
        next = next->nextSibling;
    }

    prev->nextSibling = arg0->nextSibling;
    arg0->nextSibling = NULL;
}

void func_80004B30(Object *obj, s16 playerId, s16 arg2) {
    Transform *s1;
    Transform *sp38;
    Transform *s0;
    StructAA8 *v1 = obj->modInst->unk_AA8;

    v1[D_8004C1D8[arg2]].x = 0;
    v1[D_8004C1D8[arg2]].y = 0;
    v1[D_8004C1D8[arg2]].z = 0;

    s0 = &obj->modInst->transforms[D_8004C1D8[arg2]];
    s1 = &gPlayers[playerId].unk_750;
    func_80012A20(s0->parent, s1, -3, -3);
    s1->local_matrix.w.x = s0->local_matrix.w.x;
    s1->local_matrix.w.y = s0->local_matrix.w.y;
    s1->local_matrix.w.z = s0->local_matrix.w.z;
    func_80004AE0(s0);
    sp38 = s0->firstChild;
    func_80012A20(s1, s0, -3, -3);
    s0->firstChild = sp38;

    v1[0].x = 0;
    v1[0].y = 0;
    v1[0].z = 0;

    s0 = &obj->modInst->transforms[0];
    s1 = &gPlayers[playerId].unk_868;
    func_80012A20(s0->parent, s1, -3, -3);
    s1->local_matrix.w.x = s0->local_matrix.w.x;
    s1->local_matrix.w.y = s0->local_matrix.w.y;
    s1->local_matrix.w.z = s0->local_matrix.w.z;
    func_80004AE0(s0);
    sp38 = s0->firstChild;
    func_80012A20(s1, s0, -3, -3);
    s0->firstChild = sp38;

    D_80052D64[playerId] = D_80052D68[playerId] = D_80052D6C[playerId] = D_80052D70[playerId] = D_80052D74[playerId] =
        0;
    D_80052D78[playerId] = 2;
}

void func_80004D40(Asset *asset) {
    s16 v1;
    s16 v2;
    u8 sp2B;

    v1 = D_800B6328[1 - asset->context].characterId;
    sp2B = asset->name[6];
    asset->name[6] = '\0';

    if (str_compare(asset->name, D_8004B94C[v1].unk_04) != 0) {
        v1 += 11;
        if (str_compare(asset->name, D_8004B94C[v1].unk_04) != 0) {
            asset->name[0] = '\0';
            asset->flags |= 1;
            return;
        }
    }
    asset->name[6] = sp2B;
    func_80026BE0(asset);
    asset->context += 0x5000;
}

void func_80004E14(s16 playerId) {
    char sp38[40];
    char sp2C[12];
    u8 characterId = D_800B6328[playerId].characterId;

    if (D_800B6328[playerId].unk_10) {
        str_copy(sp38, "/aaro/dummy");
    } else {
        str_copy(sp2C, D_8004B844[characterId].unk_04->unk_00);
        str_copy(sp38, "/");
        str_concat(sp38, sp2C);
        str_concat(sp38, "/");
        str_concat(sp38, sp2C);
        if (playerId != PLAYER_1) {
            str_concat(sp38, "2");
        } else {
            str_concat(sp38, "1");
        }
        if (D_800B6328[playerId].unk_06) {
            str_concat(sp38, "_h");
        } else {
            str_concat(sp38, "_v");
        }
    }

    if (str_compare(sp38, gPlayers[playerId].unk_980)) {
        func_8002630C(playerId);
        str_copy(gPlayers[playerId].unk_980, sp38);
    }
    D_8013C228 = func_80004D40;
    asset_open_folder(sp38, playerId);
}

void func_80004FC0(Object *obj) {
    ColorRGBA *sp1C = obj->varObj[0];
    ColorRGBA *sp18 = obj->varObj[1];
    u32 v1;

    if (--obj->vars[2] <= 0) {
        v1 = (guRandom() % 192) + 64;
        sp18->r = sp1C->r * v1 / 256;
        sp18->g = sp1C->g * v1 / 256;
        sp18->b = sp1C->b * v1 / 256;
        obj->vars[2] = 8;
    }
}

void func_80005060(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->unk_00->modInst->transforms[5].wolrd_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

void func_800050B0(Object *obj) {
    Player *player = obj->varObj[0];
    Matrix4f *m = &player->unk_00->modInst->unk_010.wolrd_matrix;

    obj->pos.x = m->w.x;
    obj->pos.y = m->w.y;
    obj->pos.z = m->w.z;
}

s32 D_80049390 = 0xFFFF0000;
s32 D_80049394 = 0xFFFF0000;

void func_800050FC(u16 arg0, u16 arg1) {
    ColorRGBA sp38[] = { { 0, 200, 0, 0 }, { 200, 0, 0, 0 } };
    ColorRGBA sp30[] = { { 0, 0, 255, 0 }, { 200, 50, 0, 0 } };
    Object *sp2C;

    switch (arg1) {
        case EVE:
            sp2C = create_worker(func_80005060, 0x1000);
            func_8003453C(sp2C, &sp38[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case MORPHIX:
            sp2C = create_worker(func_800050B0, 0x1000);
            func_8003453C(sp2C, &sp30[arg0]);
            sp2C->varObj[0] = &gPlayers[arg0];
            break;
        case DEMITRON:
            if (D_800B6328[arg0].unk_06) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = D_8004B774;
                sp2C->varObj[1] = D_8004B654;
            }
            break;
        case DEMONICA:
            if (D_800B6328[arg0].unk_06) {
                sp2C = create_worker(func_80004FC0, 0x1000);
                sp2C->varObj[0] = D_8004B794;
                sp2C->varObj[1] = D_8004B674;
            }
            break;
    }
}

void func_800052EC(s16 playerId) {
    Object *spDC;
    s16 v00;
    s16 i;
    s16 spD6;
    Vec4i spB4[] = { { -400, 0, 0, 0 }, { 400, 0, 0, 0 } };
    s16 spB0[] = { 0, 0x800 };
    char spA4[12];
    char sp74[48];
    char *str1 = "mod0.k2";
    char *str2 = "spr0.sp3";
    char sp60[12];

    func_80004E14(playerId);

    gPlayers[playerId].playerId = playerId;
    gPlayers[playerId].unk_80 = 0;
    spD6 = gPlayers[playerId].characterId = D_800B6328[playerId].characterId;

    if (D_800B6328[playerId].unk_10) {
        spD6 = AARON;
        str_copy(spA4, "dum.tmd");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->unk_00);
        if (spD6 != MORPHIX) {
            if (playerId != 0) {
                str_concat(spA4, "2.tmd");
            } else {
                str_concat(spA4, ".tmd");
            }
        } else {
            if (playerId != 0) {
                str_concat(spA4, "2.k3");
            } else {
                str_concat(spA4, ".k3");
            }
        }
    }

    spDC = gPlayers[playerId].unk_00 = func_8002BC84(&spB4[playerId], spA4, D_8004B844[spD6].unk_04, playerId);
    spDC->flags |= 0x80;

    if (spD6 == MORPHIX && !D_800B6328[playerId].unk_10) {
        func_8002A890(gPlayers + playerId);
    }

    if (D_800B6328[playerId].unk_10) {
        str_copy(spA4, "dumshad.k4");
    } else {
        str_copy(spA4, D_8004B844[spD6].unk_04->unk_00);
        spA4[3] = '\0';
        if (playerId != 0) {
            do {
            } while (0);
            str_concat(spA4, "shad2.k4");
        } else {
            str_concat(spA4, "shad.k4");
        }
    }

    func_80036194(spDC, spA4, playerId);

    spDC->rotation.y = 0xC00 - spB0[playerId];
    spDC->fn_render = func_80003DA4;
    if (spDC->currentTask && spDC->currentTask) {} // @fake
    spDC->varObj[0] = gPlayers + playerId;

    i = 0;
    str_copy(sp74, str2);
    while (TRUE) {
        v00 = asset_find(sp74, playerId);
        if (v00 >= 0) {
            gPlayers[playerId].unk_DC0[i++] = gAssets[v00].aux_data;
        } else {
            break;
        }
        sp74[3]++;
    }

    i = 0;
    str_copy(sp74, str1);
    str_copy(sp60, str1);
    sp60[6] = '5';
    while (TRUE) {
        v00 = asset_find(sp74, playerId);
        if (v00 >= 0) {
            gPlayers[playerId].unk_DCC[i++] = gAssets[v00].aux_data;
        } else {
            v00 = asset_find(sp60, playerId);
            if (v00 >= 0) {
                gPlayers[playerId].unk_DCC[i++] = gAssets[v00].aux_data;
            } else {
                break;
            }
        }

        sp74[3]++;
        sp60[3]++;
    }

    func_800045B4(playerId, spD6);

    gPlayers[playerId].unk_08 = spDC->currentTask;
    gPlayers[playerId].unk_0C = task_add(spDC, task_default_func, 1);
    gPlayers[playerId].unk_10 = task_add(spDC, func_800248C4, 1);
    gPlayers[playerId].unk_14 = task_add(spDC, task_default_func, 1);
    gPlayers[playerId].unk_18 = task_add(spDC, func_8003184C, 1);
    gPlayers[playerId].unk_24 = D_8004C1E8;

    D_80080214 = D_8004A730[D_800B6328[PLAYER_1].characterId] + D_8004A730[D_800B6328[PLAYER_2].characterId];
    D_80080218 = D_8004A748[D_800B6328[PLAYER_1].characterId] + D_8004A748[D_800B6328[PLAYER_2].characterId];
    D_8008020C = 0x800;
    D_80080210 = 1600;

    D_80080228[playerId] = spDC;
    D_80080238.unk_1000 = D_80080238.unk_1002 = 0;
    D_80080238.unk_1008 = gFrameCounter;

    D_80080236 = 1;

    if (D_800B6328[playerId].unk_02) {
        func_8000636C(gPlayers + playerId, 282, 0);
    } else {
        func_8000636C(gPlayers + playerId, 68, 0);
    }

    if (playerId != 0) {
        D_80080236 = 0;
    }

    gPlayers[playerId].unk_90 = gPlayers[playerId].unk_20 + gPlayers[playerId].unk_7E;
    func_80010664(&gPlayers[playerId], D_8004B844[spD6].unk_00);

    spDC->unk_070 = D_800B6328[playerId].unk_0C;
    func_80004B30(spDC, playerId, spD6);

    if (playerId == 0) {
        gPlayerInput[playerId].unk_09 = TRUE;
    }

    func_80012150(&gPlayers[playerId].unk_DE8, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_08].wolrd_matrix,
                  &gPlayers[playerId].unk_198.unk_2E8.wolrd_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[playerId]);

    if (D_8004B844[spD6].unk_00->unk_1C >= 0) {
        func_80012150(&gPlayers[playerId].unk_2240, spDC->modInst,
                      &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_04].wolrd_matrix,
                      &gPlayers[playerId].unk_198.unk_1D0.wolrd_matrix, &spDC->pos, &D_8004B844[spD6].unk_08[playerId]);
        gPlayers[playerId].unk_5F4A = 1;
    } else {
        gPlayers[playerId].unk_5F4A = 0;
    }

    func_80012150(&gPlayers[playerId].unk_3698, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_14].wolrd_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_0C].wolrd_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[playerId]);
    func_80012150(&gPlayers[playerId].unk_4AF0, spDC->modInst,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_18].wolrd_matrix,
                  &spDC->modInst->transforms[D_8004B844[spD6].unk_00->unk_10].wolrd_matrix, &spDC->pos,
                  &D_8004B844[spD6].unk_08[playerId]);

    gPlayers[playerId].unk_184 = 0;
    if (D_80080230 == 40) {
        if (playerId == gPracticingPlayer) {
            practice_init_hud();
        } else {
            gPlayers[playerId].unk_80 |= 0x200000;
        }
    }

    func_800050FC(playerId, spD6);
}

s32 D_800493CC = 0xFFFFFE70;

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80005B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_80005EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_8000636C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800063C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_8000642C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/41D0/func_800069C0.s")
