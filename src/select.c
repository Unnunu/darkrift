#include "common.h"
#include "task.h"
#include "sprite_ids.h"

#define x_7fe97e23 10

s16 D_80049B20[] = { 4, 7, 6, 5, 1, 3, 0, 2 };
s16 D_80049B30[] = { x_84d0a51b, x_ffe9ce36, x_b2ae561b, x_37f8540c, x_c7089780, x_af0e0a9f, x_64a28e7d, x_29dbff14 };

Object *x_fa7941af;
char x_ed1bd1d1[4];
Object *x_f80fc81d[x_7fe97e23];
s16 x_e7bcb342;
s32 x_4c13fe65;
s16 x_dced62f4[x_edb381f3];
s16 x_587aa870[x_edb381f3];
x_88f11482 x_6c6f1601;

void x_08d315fd(Object *obj, s16 buttons, s16 x_30bbe547) {
    s16 x_350d585b;
    s16 counter;
    s32 x_e15348ae;

    x_e15348ae = FALSE;
    x_350d585b = obj->x_0f4167b4[x_20586666];
    obj->x_0f4167b4[x_20586666] = buttons;
    counter = obj->x_0f4167b4[x_2ad56392]--;

    if (counter > 0 && buttons == x_350d585b) {
        return;
    }
    obj->x_0f4167b4[x_2ad56392] = 15;

    if (buttons & x_f7763ed8) {
        obj->x_0f4167b4[x_399d646a] = 0;
        obj->x_0f4167b4[x_f6733052] = (obj->x_0f4167b4[x_f6733052] + 9) % 10;
        x_e15348ae = TRUE;
    } else if (buttons & x_b8c91680) {
        obj->x_0f4167b4[x_399d646a] = 0;
        obj->x_0f4167b4[x_f6733052] = (obj->x_0f4167b4[x_f6733052] + 1) % 10;
        x_e15348ae = TRUE;
    } else if (buttons & x_ad1aebe6) {
        obj->x_0f4167b4[x_399d646a] = -1;
        x_e15348ae = TRUE;
    } else if (buttons & x_fc4a9735) {
        obj->x_0f4167b4[x_399d646a] = 1;
        x_e15348ae = TRUE;
    }

    if (x_e15348ae) {
        x_7e194d55(2, 1);
    }
}

void x_a2a8ba2f(Object *obj) {
    s16 buttons;
    s16 x_a6a94456;

    buttons = x_59ce598c[x_83106b21].buttons;
    x_a6a94456 = x_59ce598c[x_6f0b3be3].buttons;

    if (buttons != 0) {
        x_08d315fd(obj, buttons, x_83106b21);
    } else if (x_a6a94456 != 0) {
        x_08d315fd(obj, x_a6a94456, x_6f0b3be3);
    } else {
        obj->x_0f4167b4[x_20586666] = 0;
    }
}

void x_bc5bf713(Object *obj) {
    Object *controller;
    s16 x_68fff389;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 0) {
        if (obj->frameCounter >= x_163d32e3 && obj->frameCounter <= x_93d2dd03) {
            obj->frameCounter += 3;
        }

        x_68fff389 = controller->x_0f4167b4[x_399d646a];
        if (x_68fff389 != 0) {
            obj->frameCounter = x_be30259d + ((obj->frameCounter + x_68fff389 + 2) % 3);
            controller->x_0f4167b4[x_399d646a] = 0;
            x_028e5846 = obj->frameCounter - x_be30259d;
        }
    } else {
        if (obj->frameCounter >= x_be30259d && obj->frameCounter <= x_1c85d2bf) {
            obj->frameCounter -= 3;
        }
    }
}

void x_0e243657(Object *obj) {
    Object *controller;
    s16 x_68fff389;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 1) {
        if (obj->frameCounter >= x_336693df && obj->frameCounter <= x_adc09931) {
            obj->frameCounter += 3;
        }

        x_68fff389 = controller->x_0f4167b4[x_399d646a];
        if (x_68fff389 != 0) {
            obj->frameCounter = x_c19404b0 + ((obj->frameCounter + x_68fff389) % 3);
            controller->x_0f4167b4[x_399d646a] = 0;
            x_c8356c60 = obj->frameCounter - x_c19404b0;
        }
    } else {
        if (obj->frameCounter >= x_c19404b0 && obj->frameCounter <= x_aa0b2ee9) {
            obj->frameCounter -= 3;
        }
    }
}

void x_4d34121d(Object *obj) {
    Object *controller;
    s16 x_68fff389;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 2) {
        if (obj->frameCounter >= x_11370290 && obj->frameCounter <= x_48e11d4e) {
            obj->frameCounter += 10;
        }

        x_68fff389 = controller->x_0f4167b4[x_399d646a];
        if (x_68fff389 != 0) {
            obj->frameCounter = x_a0942644 + ((obj->frameCounter + x_68fff389 + 3) % 5);
            controller->x_0f4167b4[x_399d646a] = 0;
            x_adcfd05c = obj->frameCounter - x_9042e738;
        }
    } else {
        if (obj->frameCounter >= x_a0942644 && obj->frameCounter <= x_b794ba80) {
            obj->frameCounter -= 10;
        }
    }
}

void x_c1c0a10d(Object *obj) {
    Object *controller;
    s16 x_68fff389;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 3) {
        if (obj->frameCounter == x_4b8a6796 || obj->frameCounter == x_164d5f72) {
            obj->frameCounter += 2;
        }

        x_68fff389 = controller->x_0f4167b4[x_399d646a];
        if (x_68fff389 != 0) {
            obj->frameCounter = x_75706032 + ((obj->frameCounter + x_68fff389 + 1) % 2);
            controller->x_0f4167b4[x_399d646a] = 0;
            x_a7d9a1e8 = obj->frameCounter - x_75706032;
        }
    } else {
        if (obj->frameCounter == x_75706032 || obj->frameCounter == x_7c7b1540) {
            obj->frameCounter -= 2;
        }
    }
}

void x_ff609efb(Object *obj) {
    Object *controller;
    s16 x_68fff389;
    s32 volume;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 4) {
        if (obj->frameCounter >= x_afcff1b4 && obj->frameCounter <= x_86be64ca) {
            obj->frameCounter += 10;
        }

        x_68fff389 = controller->x_0f4167b4[x_399d646a];
        if (x_68fff389 != 0) {
            obj->frameCounter = x_9042e738 + ((obj->frameCounter + x_68fff389 + 9) % 10);
            controller->x_0f4167b4[x_399d646a] = 0;

            volume = (obj->frameCounter - x_9042e738) * (0x7FFF / 9);
            if (volume > 0x7FFF) {
                volume = 0x7FFF;
            }
            if (volume == 0) {
                volume = 1;
            }

            if (volume != x_66ddef46) {
                x_20c52092(volume);
            }
            x_b5cc849a = x_66ddef46 = volume;
        }
    } else {
        if (obj->frameCounter >= x_9042e738 && obj->frameCounter <= x_bb2ebaaa) {
            obj->frameCounter -= 10;
        }
    }
}

void x_28ceb562(Object *obj) {
    Object *controller;
    s16 x_68fff389;
    s32 volume;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 5) {
        if (obj->frameCounter >= x_afcff1b4 && obj->frameCounter <= x_86be64ca) {
            obj->frameCounter += 10;
        }

        x_68fff389 = controller->x_0f4167b4[x_399d646a];
        if (x_68fff389 != 0) {
            obj->frameCounter = x_9042e738 + ((obj->frameCounter + x_68fff389 + 9) % 10);
            controller->x_0f4167b4[x_399d646a] = 0;

            volume = (obj->frameCounter - x_9042e738) * (0x7FFF / 9);
            if (volume > 0x7FFF) {
                volume = 0x7FFF;
            }
            if (volume == 0) {
                volume = 1;
            }

            if (volume != x_15814eea) {
                x_62551fe9(2, volume);
            }
            x_aec099eb = x_15814eea = volume;
        }
    } else {
        if (obj->frameCounter >= x_9042e738 && obj->frameCounter <= x_bb2ebaaa) {
            obj->frameCounter -= 10;
        }
    }
}

void x_12081995(Object *obj) {
    Object *controller;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 6) {
        obj->flags &= ~x_c537cafa;
        if ((x_59ce598c[x_83106b21].buttons == x_9cefe76c) || x_59ce598c[x_6f0b3be3].buttons == x_9cefe76c) {
            x_e38a6e19 = x_b84bd571;
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
            x_7e194d55(2, 0);
        }
    } else {
        obj->flags |= x_c537cafa;
    }
}

void x_53598eda(Object *obj) {
    Object *controller;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 7) {
        obj->flags &= ~x_c537cafa;
        if ((x_59ce598c[x_83106b21].buttons == x_9cefe76c) || x_59ce598c[x_6f0b3be3].buttons == x_9cefe76c) {
            x_e38a6e19 = x_2e33c051;
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
            x_7e194d55(2, 0);
        }
    } else {
        obj->flags |= x_c537cafa;
    }
}

void x_b5c125fc(Object *obj) {
    Object *controller;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 8) {
        obj->flags &= ~x_c537cafa;
        if ((x_59ce598c[x_83106b21].buttons == x_9cefe76c) || x_59ce598c[x_6f0b3be3].buttons == x_9cefe76c) {
            x_e38a6e19 = x_c63c063f;
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
            x_7e194d55(2, 0);
        }
    } else {
        obj->flags |= x_c537cafa;
    }
}

void x_dd25b026(Object *obj) {
    Object *controller;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == 9) {
        obj->flags &= ~x_c537cafa;
        if ((x_59ce598c[x_83106b21].buttons == x_9cefe76c) || x_59ce598c[x_6f0b3be3].buttons == x_9cefe76c) {
            x_e38a6e19 = SCREEN_ATTRACT;
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
            x_7e194d55(2, 0);
        }
    } else {
        obj->flags |= x_c537cafa;
    }
}

void x_d1cd74f9(Object *obj, s16 buttons, s16 x_30bbe547) {
    s16 x_350d585b;
    s16 counter;
    s32 x_e15348ae;

    x_e15348ae = FALSE;
    x_350d585b = obj->x_0f4167b4[x_20586666];
    obj->x_0f4167b4[x_20586666] = buttons;
    counter = obj->x_0f4167b4[x_2ad56392]--;

    if (counter > 0 && buttons == x_350d585b) {
        return;
    }
    obj->x_0f4167b4[x_2ad56392] = 15;

    if (buttons & x_f7763ed8) {
        obj->x_0f4167b4[x_399d646a] = 0;
        obj->x_0f4167b4[x_f6733052] = (obj->x_0f4167b4[x_f6733052] + 8) % 9;
        obj->x_0f4167b4[x_4ba680cf] = 0;
        x_e15348ae = TRUE;
    } else if (buttons & x_b8c91680) {
        obj->x_0f4167b4[x_399d646a] = 0;
        obj->x_0f4167b4[x_f6733052] = (obj->x_0f4167b4[x_f6733052] + 1) % 9;
        obj->x_0f4167b4[x_4ba680cf] = 0;
        x_e15348ae = TRUE;
    } else if (buttons & x_b1ef0708) {
        x_e15348ae = TRUE;

        if (buttons & x_84d0a51b) {
            obj->x_0f4167b4[x_399d646a] = x_810a8a6e;
        } else if (buttons & x_ffe9ce36) {
            obj->x_0f4167b4[x_399d646a] = x_ab3153db;
        } else if (buttons & x_b2ae561b) {
            obj->x_0f4167b4[x_399d646a] = x_a4344608;
        } else if (buttons & x_37f8540c) {
            obj->x_0f4167b4[x_399d646a] = x_acee1321;
        } else if (buttons & x_29dbff14) {
            obj->x_0f4167b4[x_399d646a] = x_a9cd5d36;
        } else if (buttons & x_c7089780) {
            obj->x_0f4167b4[x_399d646a] = x_23d505ec;
        } else if (buttons & x_af0e0a9f) {
            obj->x_0f4167b4[x_399d646a] = x_729a61e6;
        } else if (buttons & x_64a28e7d) {
            obj->x_0f4167b4[x_399d646a] = x_6dce29db;
        }
    }
    if (x_350d585b) {} // @fake
    if (x_e15348ae) {
        x_7e194d55(2, 1);
    }
}

void x_d4ae14dc(Object *obj) {
    Object *controller;
    s16 x_4c652bcb;
    s16 x_30bbe547;
    s16 i;
    s16 q;
    s16 w;

    controller = obj->x_e2f64c57[x_0371940a];
    if (controller->x_0f4167b4[x_f6733052] == obj->x_0f4167b4[x_13266785]) {
        if (obj->frameCounter >= x_810a8a6e && obj->frameCounter <= x_c91660df) {
            obj->frameCounter += 9;
        }

        x_4c652bcb = controller->x_0f4167b4[x_399d646a];
        if (x_4c652bcb != 0) {
            controller->x_0f4167b4[x_d1a83f73] = obj->frameCounter;
            controller->x_0f4167b4[x_4ba680cf] = obj->frameCounter = x_4c652bcb;
            controller->x_0f4167b4[x_399d646a] = 0;

            x_30bbe547 = controller->x_0f4167b4[x_283009b1];
            w = D_80049B30[obj->x_0f4167b4[x_13266785]];
            q = D_80049B20[controller->x_0f4167b4[x_4ba680cf] - x_810a8a6e];

            gRemapTable[x_30bbe547][q] = w;
            for (i = 0; i < 8; i++) {}
        }
    } else {
        if (obj->frameCounter >= x_7eb4b3f4 && obj->frameCounter <= x_526f9f68) {
            obj->frameCounter -= 9;
        }

        if (obj->frameCounter == controller->x_0f4167b4[x_4ba680cf]) {
            obj->frameCounter = controller->x_0f4167b4[x_d1a83f73];

            x_30bbe547 = controller->x_0f4167b4[x_283009b1];
            w = D_80049B30[obj->x_0f4167b4[x_13266785]];
            q = D_80049B20[controller->x_0f4167b4[x_d1a83f73] - x_7eb4b3f4];
            gRemapTable[x_30bbe547][q] = w;
            for (i = 0; i < 8; i++) {}
        }
    }
}

void x_a9342b2f(Object *obj) {
    s16 x_d8bc4e5e;
    s16 x_30bbe547;

    x_30bbe547 = obj->x_0f4167b4[x_283009b1];
    x_d8bc4e5e = x_59ce598c[x_30bbe547].x_f3756179;

    if (x_d8bc4e5e != 0) {
        x_d1cd74f9(obj, x_d8bc4e5e, x_30bbe547);
    } else {
        obj->x_0f4167b4[x_20586666] = 0;
    }

    x_d4ae14dc(obj);
}

void x_2cae892b(Object *obj) {
    u8 v1;
    Object *x_7e485fc0;
    Object *x_71d00f40;

    obj->flags |= x_c537cafa;

    x_7e485fc0 = obj->x_e2f64c57[x_f2901470];
    x_71d00f40 = obj->x_e2f64c57[x_88d435fa];

    v1 = 0;
    if (x_7e485fc0->x_0f4167b4[x_f6733052] == 8) {
        obj->flags &= ~x_c537cafa;
        if (x_59ce598c[x_83106b21].buttons == x_9cefe76c) {
            x_e38a6e19 = x_f699a14d;
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
            v1++;
        }
    }
    if (x_71d00f40->x_0f4167b4[x_f6733052] == 8) {
        obj->flags &= ~x_c537cafa;
        if (x_59ce598c[x_6f0b3be3].buttons == x_9cefe76c) {
            x_e38a6e19 = x_f699a14d;
            x_e30d50d2 |= x_bee364e0;
            TASK_END(obj->currentTask);
            v1++;
        }
    }

    if (v1 != 0) {
        x_7e194d55(2, 0);
    }
}

void x_8383794c(Object *obj) {
    s16 x_350d585b;
    s16 buttons;
    char x_c309f013[20];
    s16 x_eb1fe45b;
    s16 counter;

    x_350d585b = obj->x_0f4167b4[1];
    obj->x_0f4167b4[1] = buttons = x_59ce598c[x_83106b21].buttons | x_59ce598c[x_6f0b3be3].buttons;
    counter = obj->x_0f4167b4[2]--;

    if (counter > 0 && buttons == x_350d585b) {
        return;
    }

    obj->x_0f4167b4[2] = 15;
    if (buttons & x_ad1aebe6) {
        x_eb1fe45b = obj->x_0f4167b4[0] = (obj->x_0f4167b4[0] + x_edb381f3 - 1) % x_edb381f3;
        if (x_eb1fe45b == x_e235676f || x_eb1fe45b == x_968cc9a2 && !x_5c207a56 ||
            x_eb1fe45b == x_ff5073d4 && !x_aee302fc) {
            obj->x_0f4167b4[0]--;
        }

        mem_free(x_3b49183f);
        x_3b49183f = NULL;
        x_dab0846a(x_c309f013, D_8004B844[obj->x_0f4167b4[0]].x_1256da71->name);
        x_8c518b47(x_c309f013, "st");
        x_a0e73601(x_c309f013, 0, 13, 0, 0, x_96186256, x_35b88489);
        x_7e194d55(2, 1);
    } else if (buttons & x_fc4a9735) {
        x_eb1fe45b = obj->x_0f4167b4[0] = (obj->x_0f4167b4[0] + 1) % x_edb381f3;
        if (x_eb1fe45b == x_e235676f || x_eb1fe45b == x_968cc9a2 && !x_5c207a56 ||
            x_eb1fe45b == x_ff5073d4 && !x_aee302fc) {
            obj->x_0f4167b4[0]++;
        }

        mem_free(x_3b49183f);
        x_3b49183f = NULL;
        x_dab0846a(x_c309f013, D_8004B844[obj->x_0f4167b4[0]].x_1256da71->name);
        x_8c518b47(x_c309f013, "st");
        x_a0e73601(x_c309f013, 0, 13, 0, 0, x_96186256, x_35b88489);
        x_7e194d55(2, 1);
    } else if (buttons & x_9cefe76c) {
        x_e38a6e19 = x_f699a14d;
        x_e30d50d2 |= x_bee364e0;
        TASK_END(obj->currentTask);
        x_7e194d55(2, 0);
    }
}

void x_a9b3a737(Object *obj) {
    s16 buttons;

    buttons = x_59ce598c[x_83106b21].buttons | x_59ce598c[x_6f0b3be3].buttons;
    if (buttons & x_9cefe76c) {
        x_e38a6e19 = x_f699a14d;
        x_e30d50d2 |= x_bee364e0;
        TASK_END(obj->currentTask);
        x_7e194d55(2, 0);
    }
}

void x_aad8fe8c(s16 number, s16 x_051b562d, s16 x_64a8566c) {
    x_f0d7e70f x_0aeac7e8 = { 0, NULL, 0, x_9d442987, "options2.sp2" };
    s16 x_a8677df7;
    s16 x_523c079f;
    s16 x_d413f652;
    Object *v1;

    if (number > 999) {
        number = 999;
    }

    x_a8677df7 = number / 100;
    number -= x_a8677df7 * 100;
    x_523c079f = number / 10;
    x_d413f652 = number - x_523c079f * 10;

    if (x_a8677df7 != 0) {
        v1 = x_f80fc81d[x_e7bcb342++];
        v1->pos.x = x_051b562d;
        v1->pos.y = x_64a8566c;
        v1->frameCounter = 21 + x_a8677df7;
        v1->flags &= ~x_c537cafa;
    }

    x_051b562d += 7;

    if (x_a8677df7 != 0 || x_a8677df7 == 0 && x_523c079f != 0) {
        v1 = x_f80fc81d[x_e7bcb342++];
        v1->pos.x = x_051b562d;
        v1->pos.y = x_64a8566c;
        v1->frameCounter = 21 + x_523c079f;
        v1->flags &= ~x_c537cafa;
    }

    x_051b562d += 7;

    v1 = x_f80fc81d[x_e7bcb342++];
    v1->pos.x = x_051b562d;
    v1->pos.y = x_64a8566c;
    v1->frameCounter = 21 + x_d413f652;
    v1->flags &= ~x_c537cafa;
}

void x_0073afdd(Object *obj) {
    s16 i;
    s16 x_634768da;
    s16 x_05e00b01;
    Object *x_c309f013;
    s32 pad;

    if (!(x_e30d50d2 & x_e3ff543d)) {
        return;
    }
    x_634768da = obj->x_0f4167b4[0]++;
    if (x_634768da == 0) {
        x_25025961(x_3b49183f);
    }

    for (i = 0; i < x_7fe97e23; i++) {
        x_f80fc81d[i]->flags |= x_c537cafa;
    }

    if (x_634768da > 10) {
        obj->currentTask->callback = x_a9b3a737;
        x_fa7941af->flags |= x_c537cafa;
        return;
    }

    x_05e00b01 = x_dced62f4[x_634768da];
    if (x_05e00b01 == x_e235676f || x_05e00b01 == x_968cc9a2 && !x_5c207a56 ||
        x_05e00b01 == x_ff5073d4 && !x_aee302fc) {
        return;
    }

    x_7e194d55(2, 0);
    x_e7bcb342 = 0;

    x_c309f013 = x_f80fc81d[x_e7bcb342++];
    x_c309f013->pos.x = x_6c6f1601.x;
    x_c309f013->pos.y = x_6c6f1601.y;
    x_c309f013->frameCounter = 188 + (x_05e00b01 - (x_05e00b01 > x_e235676f));
    x_c309f013->flags &= ~x_c537cafa;

    x_aad8fe8c(x_587aa870[x_05e00b01], x_6c6f1601.x + 68, x_6c6f1601.y);
    x_aad8fe8c(D_800B6368[x_05e00b01].x_a962826d, x_6c6f1601.x + 123, x_6c6f1601.y);
    x_aad8fe8c(D_800B6368[x_05e00b01].x_3f3ac621, x_6c6f1601.x + 165, x_6c6f1601.y);
    x_6c6f1601.y += 16;
    obj->currentTask->delay = 10;
}

void x_8da34614(void) {
    x_f0d7e70f x_0aeac7e8 = { 0, NULL, 0, x_9d442987, "options2.sp2" };
    s16 i, j, k;
    s16 x_a962826d;
    s16 x_3f3ac621;
    s16 total;

    x_6c6f1601.x = 75;
    x_6c6f1601.y = 71;

    for (i = 0; i < x_7fe97e23; i++) {
        x_f80fc81d[i] = x_12014163(&x_6c6f1601, &x_0aeac7e8, x_35b88489);
        x_f80fc81d[i]->flags |= x_c537cafa;
    }

    for (i = 0; i < x_edb381f3; i++) {
        x_dced62f4[i] = i;
    }

    for (j = 0; j < x_edb381f3; j++) {
        x_a962826d = D_800B6368[j].x_a962826d;
        x_3f3ac621 = D_800B6368[j].x_3f3ac621;
        total = x_a962826d + x_3f3ac621;
        if (total != 0) {
            x_587aa870[j] = (x_a962826d * 200 + total) / (2 * total);
        } else {
            x_587aa870[j] = 0;
        }
    }

    for (j = 1; j < x_edb381f3; j++) {
        for (i = 0; i < j; i++) {
            if (x_587aa870[x_dced62f4[i]] < x_587aa870[j]) {
                for (k = j - 1; k >= i; k--) {
                    x_dced62f4[k + 1] = x_dced62f4[k];
                }
                x_dced62f4[i] = j;
                break;
            }
        }
    }
}
