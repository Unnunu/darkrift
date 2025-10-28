#include "common.h"
#include "camera.h"

void func_80023F54(Object *);

void func_80023D30(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    u16 playerId = player->playerId;
    s32 v1;

    if (D_800B6328[playerId].unk_02 && !D_800801F0) {
        if (func_8001BB80(player) || func_8001C53C(player, TRUE)) {
            return;
        }

        func_8001BB2C(player);

        if (player->unk_76 >= 0 && (player->unk_80 & 0x1000) && func_800069C0(player)) {
            player->unk_180 |= 0x8000;
            return;
        }
    } else if (!(player->unk_80 & 0x400) && (gPlayerInput[playerId].unk_08 || (player->unk_80 & 0x1000)) &&
               player->unk_76 >= 0 && !(player->unk_0C->flags & 4) && func_8000642C(player, TRUE)) {
        return;
    }

    D_80080236 = 1;
    v1 = player->unk_90->unk_34;
    if (player->unk_80 & 0x08000000) {
        player->unk_80 &= ~0x08000000;
        v1 ^= 5;
    }

    if (v1 & 1) {
        func_8000636C(player, 320, 0);
    } else {
        func_8000636C(player, 68, 0);
    }

    D_80080236 = 0;
    player->unk_80 |= 0x400;
}

void func_80023ED0(Object *obj) {
    Player *player = (Player *) obj->varObj[0];

    if (obj->frameIndex > player->unk_90->unk_00 + 1) {
        obj->frameIndex--;
    } else {
        obj->frameIndex--;
        func_80023D30(obj);
    }
}

void func_80023F20(Object *obj) {
    if (obj->frameIndex != 0) {
        obj->frameIndex--;
    } else {
        obj->frameIndex++;
        obj->currentTask->func = func_80023F54;
    }
}

void func_80023F54(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames - 1) {
        obj->frameIndex++;
    } else {
        obj->frameIndex--;
        obj->currentTask->func = func_80023F20;
    }
}

void func_80023F9C(Object *obj) {
    if (obj->frameIndex < obj->modInst->numAnimFrames - 1) {
        obj->frameIndex++;
    } else {
        obj->currentTask->flags |= 0x80;
    }
}

void func_80023FDC(Object *obj) {
    Player *player;
    s16 characterId;

    if (obj->frameIndex < ((Player *) obj->varObj[0])->unk_90->unk_02) {
        obj->frameIndex++;
        return;
    }

    obj->frameIndex = 0;
    player = (Player *) obj->varObj[0];
    characterId = player->characterId;

    if (obj->modInst->velocity.z != 0) {
        if (player->unk_90->unk_34 & 4) {
            obj->modInst->velocity.z = D_8004BA98[characterId].z;
        } else {
            obj->modInst->velocity.z = D_8004BAF0[characterId].z;
        }
        obj->modInst->currentRootPos.z = obj->modInst->baseRootPos.z;
    } else {
        obj->modInst->previousAnimId = -1;
    }
}

void func_80024078(Object *obj) {
    if (obj->frameIndex < ((Player *) obj->varObj[0])->unk_90->unk_02 - 1) {
        obj->frameIndex++;
    } else {
        obj->frameIndex++;
        func_80023D30(obj);
    }
}

void func_800240C8(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    Vec4i sp2C;

    if (player->unk_90->unk_2C < 0) {
        obj->currentTask->flags |= 0x80;
    } else if (obj->frameIndex >= player->unk_90->unk_2E) {
        func_8002C340();

        sp2C.x = (gPlayers[PLAYER_1].unk_00->pos.x + gPlayers[PLAYER_2].unk_00->pos.x) >> 1;
        sp2C.z = (gPlayers[PLAYER_1].unk_00->pos.z + gPlayers[PLAYER_2].unk_00->pos.z) >> 1;
        sp2C.y = 0;
        func_80038E8C(gCamera, &sp2C, obj->rotation.y,
                      obj->modInst->animations[player->unk_20[player->unk_90->unk_2C].unk_08]);

        gCamera->currentTask->func = func_8002C490;
        gCamera->currentTask->counter = 0;
        gCamera->currentTask->flags = 1;
        gCamera->currentTask->counter = 1;
        obj->currentTask->flags |= 0x80;
    }
}

void func_80024214(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 unused[2];
    PlayerSub3 *v1;

    v1 = player->unk_20 + player->unk_7E;
    player->unk_90 = v1;

    if (v1->unk_2C >= 0 && v1->unk_2E != -1) {
        player->unk_14->func = func_800240C8;
        player->unk_14->counter = 0;
        player->unk_14->flags = 1;
    }

    if (v1->unk_30 != -1) {
        func_80034C18(obj, player->unk_68 + v1->unk_30 * obj->modInst->numNodes);
    } else {
        func_80034A58(obj);
    }

    obj->currentTask->func = func_80024078;
    obj->frameIndex++;

    if (v1->unk_34 & 0x10) {
        obj->flags |= 0x400;
        if (v1->unk_34 & 0x8000) {
            obj->flags |= 0x20000;
        }
    } else {
        obj->flags &= ~0x400;
    }

    if (v1->unk_34 & 0x80) {
        obj->flags |= 0x800000;
    }

    if (v1->unk_34 & 0x200000) {
        obj->flags |= 0x100000;
    }
}

void func_80024390(Object *obj) {
    ObjectTaskSub *sp24;
    Player *player = (Player *) obj->varObj[0];
    PlayerSub3 *sp1C;

    sp1C = player->unk_90;
    sp24 = &obj->currentTask->unk_08;

    if (player->unk_7E >= 0) {
        sp1C = player->unk_20 + player->unk_7E;
        if (sp1C->unk_08 == obj->modInst->currentAnimId && obj->frameIndex + 1 < sp1C->unk_00) {
            obj->frameIndex++;
            player->unk_0C->flags |= 4;
            player->unk_0C->unk_86 = sp1C->unk_00 - 2;
            player->unk_0C->unk_90.flags = 1;
            player->unk_0C->unk_90.func = func_80024214;
            obj->currentTask->func = func_80024078;
            return;
        }

        if (sp1C->unk_08 == obj->modInst->currentAnimId && obj->frameIndex == sp1C->unk_00 - 1) {
            func_80024214(obj);
            return;
        }

        if (sp1C->unk_2C >= 0 && sp1C->unk_2E != -1) {
            player->unk_14->func = func_800240C8;
            player->unk_14->counter = 0;
            player->unk_14->flags = 1;
        }

        if (sp1C->unk_30 != -1) {
            func_80034C18(obj, player->unk_68 + sp1C->unk_30 * obj->modInst->numNodes);
        } else {
            func_80034A58(obj);
        }

        player->unk_90 = sp1C;

        if (player->unk_80 & 0x800) {
            obj->frameIndex = sp1C->unk_02;
        } else {
            obj->frameIndex = MAX(sp1C->unk_00, sp24->unk_08);
        }

        obj->modInst->currentAnimId = sp1C->unk_08;
        obj->modInst->previousAnimId = -1;
    }

    obj->currentTask->func = sp24->unk_00_f; // ????

    if (sp1C->unk_34 & 0x10) {
        obj->flags |= 0x400;
        if (sp1C->unk_34 & 0x8000) {
            obj->flags |= 0x20000;
        } else {
            obj->flags &= ~0x20000;
        }
    } else {
        obj->flags &= ~0x400;
    }

    if (sp1C->unk_34 & 0x80) {
        obj->flags |= 0x400000;
    }

    if (sp1C->unk_34 & 0x200000) {
        obj->flags |= 0x100000;
    }
}

void func_80024640(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s32 i;
    s32 s2;
    ObjectTaskSub *v0;

    if (obj->frameIndex < player->unk_90->unk_02) {
        obj->frameIndex++;
        return;
    }

    player->unk_80 &= ~0x400;
    v0 = &obj->currentTask->unk_08;
    player->unk_08->func = v0->unk_10;
    player->unk_08->counter = 0;
    player->unk_08->flags = 1;
    func_80024390(obj);

    if (obj->frameIndex >= 2) {
        model_change_animation(obj);
        obj->modInst->previousAnimId = obj->modInst->currentAnimId;
        obj->flags |= 0x8000;

        s2 = obj->frameIndex;
        for (i = 0; i < s2; i += 2) {
            obj->frameIndex = i;
            model_process_animation(obj);
        }

        obj->flags &= ~0x8000;
        obj->frameIndex = s2;
    }

    player->unk_180 &= ~0x20000;
}

void func_80024764(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    PlayerSub3 *temp;

    obj->currentTask->func = func_80024640;
    obj->frameIndex = 1;
    temp = obj->currentTask->unk_08.unk_0C + player->unk_20; // required to match
    player->unk_90 = temp;
    obj->modInst->currentAnimId = temp->unk_08;
    player->unk_80 |= 0x400;
    player->unk_180 |= 0x20000;
}

void func_800247CC(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    ObjectTask *v0;
    s32 pad2;
    s16 sp2A;
    s16 *sp24;
    GlobalObjBSub *stack;
    ObjectTask *sp1C;

    v0 = player->unk_0C;
    sp2A = v0->unk_08.unk_00_i;
    sp24 = player->unk_34;
    sp1C = obj->currentTask;
    obj->frameIndex++;

    if (func_80005EE4(player, TRUE, sp2A)) {
        player->unk_76 = sp24[sp2A + 1];
        player->unk_184 = 0;
        sp1C->stackPos--;
    } else {
        stack = sp1C->stack + (--sp1C->stackPos);
        sp1C->func = stack->func;
        sp1C->flags = stack->flags;
        sp1C->counter = stack->counter;

        if (sp1C->counter != 0) {
            sp1C->counter--;
        } else {
            sp1C->func(obj);
        }
    }
}

void func_800248C4(Object *obj) {
    Player *player = (Player *) obj->varObj[0];
    s16 v1 = player->unk_90->unk_22;
    PlayerSubC *s0 = player->unk_40;
    s16 playerId = player->playerId;

    if (v1 != -1) {
        s0 += v1;
        if (obj->frameIndex != 0) {
            if (obj->frameIndex == s0->unk_01) {
                sound_play(playerId, s0->unk_00);
            }
            if (obj->frameIndex == s0->unk_03) {
                sound_play(playerId, s0->unk_02);
            }
            if (obj->frameIndex == s0->unk_05) {
                sound_play(playerId, s0->unk_04);
            }
            if (obj->frameIndex == s0->unk_07) {
                sound_play(playerId, s0->unk_06);
            }
        }
    }
}

void func_800249A4(Object *obj) {
}
