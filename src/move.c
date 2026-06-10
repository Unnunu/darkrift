#include "common.h"
#include "camera.h"
#include "task.h"

u8 player_force_transition(Player *);

void x_d16f8fa6(Object *);

void x_d30a20e1(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    u16 x_30bbe547 = player->x_30bbe547;
    s32 x_76041836;

    if (x_77831b2c[x_30bbe547].x_03604d94 && !x_9df63a90) {
        if (x_12c88671(player) || x_bed222e0(player, TRUE)) {
            return;
        }

        x_5587ad5e(player);

        if (player->x_0a8e33d7 >= 0 && (player->flags & x_f6191783)) {
            if (player_force_transition(player)) {
                player->x_81570fde.x_b2c79d6e |= x_096af79a;
                return;
            }
        }
    } else if (!(player->flags & x_030d2322) && (x_59ce598c[x_30bbe547].x_c4397934 || (player->flags & x_f6191783)) &&
               player->x_0a8e33d7 >= 0 && !(player->x_b9252303->flags & TASK_TIME_BASED)) {
        if (player_select_move(player, TRUE)) {
            return;
        }
    }

    D_80080236 = TRUE;
    x_76041836 = player->x_7f68c36b->flags;
    if (player->flags & x_ebfbeab4) {
        player->flags &= ~x_ebfbeab4;
        x_76041836 ^= x_037894c1 | x_ff05097f;
    }

    if (x_76041836 & x_037894c1) {
        player_exec_move(player, x_26778114, FALSE);
    } else {
        player_exec_move(player, x_ee946ac0, FALSE);
    }

    D_80080236 = FALSE;
    player->flags |= x_030d2322;
}

void x_55af5110(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->frameCounter > player->x_7f68c36b->x_887b6be9 + 1) {
        obj->frameCounter--;
    } else {
        obj->frameCounter--;
        x_d30a20e1(obj);
    }
}

void x_209f3063(Object *obj) {
    if (obj->frameCounter != 0) {
        obj->frameCounter--;
    } else {
        obj->frameCounter++;
        obj->currentTask->callback = x_d16f8fa6;
    }
}

void x_d16f8fa6(Object *obj) {
    if (obj->frameCounter < obj->x_20d20338->x_8e601526 - 1) {
        obj->frameCounter++;
    } else {
        obj->frameCounter--;
        obj->currentTask->callback = x_209f3063;
    }
}

void x_fe7e2137(Object *obj) {
    if (obj->frameCounter < obj->x_20d20338->x_8e601526 - 1) {
        obj->frameCounter++;
    } else {
        TASK_END(obj->currentTask);
    }
}

void x_378d4f8e(Object *obj) {
    Player *player;
    s16 x_eb1fe45b;

    if (obj->frameCounter < ((Player *) obj->x_e2f64c57[0])->x_7f68c36b->x_bab9966d) {
        obj->frameCounter++;
        return;
    } else {
        obj->frameCounter = 0;
        player = (Player *) obj->x_e2f64c57[0];
        x_eb1fe45b = player->x_eb1fe45b;

        if (obj->x_20d20338->velocity.z != 0) {
            if (player->x_7f68c36b->flags & x_ff05097f) {
                obj->x_20d20338->velocity.z = D_8004BA98[x_eb1fe45b].z;
            } else {
                obj->x_20d20338->velocity.z = D_8004BAF0[x_eb1fe45b].z;
            }
            obj->x_20d20338->x_6689336b.z = obj->x_20d20338->x_9cfd7bb4.z;
        } else {
            obj->x_20d20338->x_2f4c4ce1 = -1;
        }
    }
}

void x_d18c17c2(Object *obj) {
    if (obj->frameCounter < ((Player *) obj->x_e2f64c57[0])->x_7f68c36b->x_bab9966d - 1) {
        obj->frameCounter++;
    } else {
        obj->frameCounter++;
        x_d30a20e1(obj);
    }
}

void x_330375dc(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    x_88f11482 x_32f1d6e2;

    if (player->x_7f68c36b->x_016911c1 < 0) {
        TASK_END(obj->currentTask);
    } else if (obj->frameCounter >= player->x_7f68c36b->x_71e17346) {
        cam_save_state();

        x_32f1d6e2.x = (x_824b9544[x_83106b21].obj->pos.x + x_824b9544[x_6f0b3be3].obj->pos.x) >> 1;
        x_32f1d6e2.z = (x_824b9544[x_83106b21].obj->pos.z + x_824b9544[x_6f0b3be3].obj->pos.z) >> 1;
        x_32f1d6e2.y = 0;
        x_434424a1(x_f4bce728, &x_32f1d6e2, obj->x_224610f1.y,
                   obj->x_20d20338->x_50771dcd[player->x_68a6b5cd[player->x_7f68c36b->x_016911c1].x_43d35340]);

        x_f4bce728->currentTask->callback = cam_cinematic_update;
        x_f4bce728->currentTask->delay = 0;
        x_f4bce728->currentTask->flags = TASK_RUNNABLE;
        x_f4bce728->currentTask->delay = 1;
        TASK_END(obj->currentTask);
    }
}

void x_7c333f6c(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 unused[2];
    x_388306ba *x_fc58f0f1;

    x_fc58f0f1 = player->x_68a6b5cd + player->x_cd14c741;
    player->x_7f68c36b = x_fc58f0f1;

    if (x_fc58f0f1->x_016911c1 >= 0 && x_fc58f0f1->x_71e17346 != -1) {
        player->x_cdb23d89->callback = x_330375dc;
        player->x_cdb23d89->delay = 0;
        player->x_cdb23d89->flags = TASK_RUNNABLE;
    }

    if (x_fc58f0f1->x_49e4c93e != -1) {
        model_visibility_set(obj, player->x_c42e3970 + x_fc58f0f1->x_49e4c93e * obj->x_20d20338->x_6dcce206);
    } else {
        model_parts_disable_all(obj);
    }

    obj->currentTask->callback = x_d18c17c2;
    obj->frameCounter++;

    if (x_fc58f0f1->flags & x_c979afe4) {
        obj->flags |= x_9ee447da;
        if (x_fc58f0f1->flags & x_1befc3ad) {
            obj->flags |= x_03ae0e9e;
        }
    } else {
        obj->flags &= ~x_9ee447da;
    }

    if (x_fc58f0f1->flags & x_cdcff2e1) {
        obj->flags |= x_da584e3c;
    }

    if (x_fc58f0f1->flags & x_41efdde7) {
        obj->flags |= x_d645b406;
    }
}

void x_73e8f926(Object *obj) {
    s32 *params;
    Player *player = (Player *) obj->x_e2f64c57[0];
    x_388306ba *x_fc58f0f1;

    x_fc58f0f1 = player->x_7f68c36b;
    params = obj->currentTask->params;

    if (player->x_cd14c741 >= 0) {
        x_fc58f0f1 = player->x_68a6b5cd + player->x_cd14c741;

        if (x_fc58f0f1->x_43d35340 == obj->x_20d20338->x_ee205ef9 && obj->frameCounter + 1 < x_fc58f0f1->x_887b6be9) {
            obj->frameCounter++;
            player->x_b9252303->flags |= TASK_TIME_BASED;
            player->x_b9252303->triggerTime = x_fc58f0f1->x_887b6be9 - 2;
            player->x_b9252303->pushState.flags = TASK_RUNNABLE;
            player->x_b9252303->pushState.callback = x_7c333f6c;
            obj->currentTask->callback = x_d18c17c2;
            return;
        }

        if (x_fc58f0f1->x_43d35340 == obj->x_20d20338->x_ee205ef9 && obj->frameCounter == x_fc58f0f1->x_887b6be9 - 1) {
            x_7c333f6c(obj);
            return;
        }

        if (x_fc58f0f1->x_016911c1 >= 0 && x_fc58f0f1->x_71e17346 != -1) {
            player->x_cdb23d89->callback = x_330375dc;
            player->x_cdb23d89->delay = 0;
            player->x_cdb23d89->flags = TASK_RUNNABLE;
        }

        if (x_fc58f0f1->x_49e4c93e != -1) {
            model_visibility_set(obj, player->x_c42e3970 + x_fc58f0f1->x_49e4c93e * obj->x_20d20338->x_6dcce206);
        } else {
            model_parts_disable_all(obj);
        }

        player->x_7f68c36b = x_fc58f0f1;

        if (player->flags & x_d7755e38) {
            obj->frameCounter = x_fc58f0f1->x_bab9966d;
        } else {
            obj->frameCounter = MAX(x_fc58f0f1->x_887b6be9, params[2]);
        }

        obj->x_20d20338->x_ee205ef9 = x_fc58f0f1->x_43d35340;
        // trigger animation change code in model_update
        obj->x_20d20338->x_2f4c4ce1 = -1;
    }

    obj->currentTask->callback = params[0];

    if (x_fc58f0f1->flags & x_c979afe4) {
        obj->flags |= x_9ee447da;
        if (x_fc58f0f1->flags & x_1befc3ad) {
            obj->flags |= x_03ae0e9e;
        } else {
            obj->flags &= ~x_03ae0e9e;
        }
    } else {
        obj->flags &= ~x_9ee447da;
    }

    if (x_fc58f0f1->flags & x_cdcff2e1) {
        obj->flags |= x_977143b5;
    }

    if (x_fc58f0f1->flags & x_41efdde7) {
        obj->flags |= x_d645b406;
    }
}

void x_6ac04b7a(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 i;
    s32 s2;
    s32 *v0;

    if (obj->frameCounter < player->x_7f68c36b->x_bab9966d) {
        obj->frameCounter++;
        return;
    }

    player->flags &= ~x_030d2322;
    v0 = obj->currentTask->params;
    player->x_147ade82->callback = v0[4];
    player->x_147ade82->delay = 0;
    player->x_147ade82->flags = TASK_RUNNABLE;
    x_73e8f926(obj);

    if (obj->frameCounter >= 2) {
        model_anim_load(obj);
        obj->x_20d20338->x_2f4c4ce1 = obj->x_20d20338->x_ee205ef9;
        obj->flags |= x_56bbd9b2;

        s2 = obj->frameCounter;
        for (i = 0; i < s2; i += 2) {
            obj->frameCounter = i;
            model_anim_tick(obj);
        }

        obj->flags &= ~x_56bbd9b2;
        obj->frameCounter = s2;
    }

    player->x_81570fde.x_b2c79d6e &= ~x_c74d666c;
}

void x_46bebbb5(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    x_388306ba *temp;

    obj->currentTask->callback = x_6ac04b7a;
    obj->frameCounter = 1;
    temp = obj->currentTask->params[3] + player->x_68a6b5cd; // required to match
    player->x_7f68c36b = temp;
    obj->x_20d20338->x_ee205ef9 = temp->x_43d35340;
    player->flags |= x_030d2322;
    player->x_81570fde.x_b2c79d6e |= x_c74d666c;
}

void x_8126b2af(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    TaskNode *v0;
    s32 pad2;
    s16 x_0f12118c;
    s16 *x_554ac37d;
    FsmState *stack;
    TaskNode *currentTask;

    v0 = player->x_b9252303;
    x_0f12118c = v0->params[0];
    x_554ac37d = player->x_b8b27276;
    currentTask = obj->currentTask;
    obj->frameCounter++;

    if (player_exec_state(player, TRUE, x_0f12118c)) {
        player->x_0a8e33d7 = x_554ac37d[x_0f12118c + 1];
        player->x_cadf184a = FALSE;
        currentTask->stackPtr--;
    } else {
        stack = currentTask->stack + (--currentTask->stackPtr);
        currentTask->callback = stack->callback;
        currentTask->flags = stack->flags;
        currentTask->delay = stack->delay;

        if (currentTask->delay != 0) {
            currentTask->delay--;
        } else {
            currentTask->callback(obj);
        }
    }
}

void x_9a2e218f(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_9e993e2f = player->x_7f68c36b->x_9e993e2f;
    x_c8184673 *x_429c730a = player->x_429c730a;
    s16 x_30bbe547 = player->x_30bbe547;

    if (x_9e993e2f != -1) {
        x_429c730a += x_9e993e2f;
        if (obj->frameCounter != 0) {
            if (obj->frameCounter == x_429c730a->x_70149fad) {
                x_7e194d55(x_30bbe547, x_429c730a->x_6c6074c0);
            }
            if (obj->frameCounter == x_429c730a->x_bf6039d8) {
                x_7e194d55(x_30bbe547, x_429c730a->x_a1942e25);
            }
            if (obj->frameCounter == x_429c730a->x_8c856b1f) {
                x_7e194d55(x_30bbe547, x_429c730a->x_94e185f0);
            }
            if (obj->frameCounter == x_429c730a->x_851b801d) {
                x_7e194d55(x_30bbe547, x_429c730a->x_155a7631);
            }
        }
    }
}

void x_cdd4d8f3(Object *obj) {
}
