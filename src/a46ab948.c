#include "camera.h"
#include "task.h"

// void model_update_animated_params(Object *);

x_a05f18ad *D_80053030[] = { NULL };

Object *x_f4bce728;
s32 D_8013C564; // unused
x_88f11482 x_435c561d;
f32 x_9972afd1;
s32 D_8013C57C; // unused
s32 x_37b927c9;
s32 x_45c764a7;
s32 D_8013C588;
s32 x_4c17a2ba;
s32 x_f81735c3;
f32 D_8013C594;
f32 x_bc5e8843;
f32 D_8013C59C;
f32 D_8013C5A0;
x_f9704fd6 x_b082fd90;
x_f9704fd6 x_e1751f31;
x_f9704fd6 x_7eefcd11;
x_acccb624 D_8013C668;
x_f9704fd6 D_8013C670;
x_f9704fd6 D_8013C6B0;
Transform D_8013C6F0;
x_43bd08ed D_8013C808;
x_88f11482 D_8013C818;
s32 D_8013C828;
s32 D_8013C82C;
s32 x_cf60a652;
u8 x_6f8aa7af;
s32 D_8013C838;

void x_7bb27e6e(Object *obj, x_a05f18ad *x_ec23cef0) {
    x_6fcfcf46 *x_20d20338 = obj->x_20d20338;

    x_20d20338->x_ee205ef9 = 0;
    obj->x_2b06a023 = x_20d20338->x_2f4c4ce1 = -1;
    obj->x_5fcb1654 = 0;

    x_20d20338->x_50771dcd[0] = x_ec23cef0;

    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -480;

    obj->pos.y = 0;
    obj->pos.z = 0;
    obj->pos.x = 0;

    obj->x_224610f1.y = 0x400;

    x_20d20338->x_5d0e77f6[1].x = 0;
    x_20d20338->x_5d0e77f6[1].y = 0;
    x_20d20338->x_5d0e77f6[1].z = 0;

    D_8013C818.x = D_8013C818.y = D_8013C818.z = 0;

    obj->x_20d20338->x_8e601526 = 0x7FFF;
    x_45c764a7 = 11000;
}

void x_434424a1(Object *obj, x_88f11482 *x_84ff873b, s32 x_2092f891, x_a05f18ad *x_ee71e5cb) {
    x_6fcfcf46 *model = obj->x_20d20338;

    model->x_2f4c4ce1 = -1;
    model->x_ee205ef9 = 0;
    obj->x_2b06a023 = model->x_2f4c4ce1;

    obj->x_5fcb1654 = 0;

    obj->x_20d20338->x_8e601526 = 0x7FFF;

    model->x_50771dcd[0] = x_ee71e5cb;

    obj->x_224610f1.x = obj->x_224610f1.z = 0;
    obj->x_224610f1.y = x_2092f891;

    obj->pos.x = x_84ff873b->x;
    obj->pos.y = x_84ff873b->y;
    obj->pos.z = x_84ff873b->z;

    x_435c561d.x = x_84ff873b->x;
    x_435c561d.z = x_84ff873b->z;
    x_435c561d.y = -480;

    D_8013C818.x = x_84ff873b->x;
    D_8013C818.y = x_84ff873b->y;
    D_8013C818.z = x_84ff873b->z;

    x_45c764a7 = 11000;
}

void x_3f054879(s32 x_cc1d0de5, s32 x_84ff873b, s32 x_2092f891, s32 x_ee71e5cb) {
    s32 v1;
    f32 fv0;

    v1 = x_4a9e7834(x_2092f891, x_ee71e5cb);
    D_8013C59C = D_8013C5A0;

    if (v1 != 0) {
        D_8013C5A0 = (f32) x_ee71e5cb / (f32) v1;
        if (x_cc1d0de5 <= 0 && x_84ff873b >= 0) {
            D_8013C5A0 = (1.0f - D_8013C5A0) + 1.0f;
        } else if (x_cc1d0de5 <= 0 && x_84ff873b <= 0) {
            D_8013C5A0 += 2.0f;
        } else if (x_cc1d0de5 >= 0 && x_84ff873b <= 0) {
            D_8013C5A0 = (1.0f - D_8013C5A0) + 3.0f;
        }

        fv0 = D_8013C5A0 - D_8013C59C;
        if (fv0 > 1.0f) {
            fv0 -= 4.0f;
        } else if (fv0 < -1.0f) {
            fv0 += 4.0f;
        }

        D_8013C838 = D_8013C828;
        D_8013C828 -= ROUND(fv0 * 700.0f);
        fv0 = -(D_8013C594 * 420.0f);
        D_8013C82C = (s32) (fv0 - 10.0f);
    }
}

void x_2b791dba(Object *obj) {
    s32 x_2bef91d9, x_86fee161, x_2dffbf44;
    x_6fcfcf46 *model = obj->x_20d20338;
    s32 x_f0d1d935;
    u32 x_f5463fa4, x_98e2dc09;
    s32 unused;
    x_88f11482 x_f10a928a;
    u32 x_d16311d7;

    x_c0a431f7(obj);

    if (model->x_50771dcd[0] != NULL) {
        if (model->x_ee205ef9 != model->x_2f4c4ce1) {
            x_0f2c2c2a(obj);
            model->x_2f4c4ce1 = model->x_ee205ef9;
        }

        if (obj->x_5fcb1654 != obj->x_2b06a023) {
            x_b6e96a17(obj);
            x_2a8d0730(obj);
            obj->x_2b06a023 = obj->x_5fcb1654;

            if (model->x_5d0e77f6[0].x != 0 || model->x_5d0e77f6[0].y != 0 || model->x_5d0e77f6[0].z != 0) {
                x_f10a928a.x = model->x_5d0e77f6[0].x;
                x_f10a928a.y = model->x_5d0e77f6[0].y;
                x_f10a928a.z = model->x_5d0e77f6[0].z;
                x_9b0df250(&x_f10a928a, &obj->x_224610f1);
                x_435c561d.x = D_8013C818.x + x_f10a928a.x;
                x_435c561d.y = D_8013C818.y + x_f10a928a.y;
                x_435c561d.z = D_8013C818.z + x_f10a928a.z;
            }
        }

        obj->pos.y = model->x_6689336b.y;
    }

    guPerspectiveF(&x_e1751f31, &D_80080100->perspNorm, x_9972afd1, 4.0f / 3.0f, x_37b927c9,
                   x_45c764a7, x_bc5e8843);

    if (obj->pos.x != 0 || obj->pos.z != 0 || x_435c561d.x != 0 || x_435c561d.z != 0) {
        guLookAtF(&x_b082fd90, obj->pos.x, obj->pos.y + (f32) x_cf60a652, obj->pos.z, x_435c561d.x,
                  x_435c561d.y + (f32) x_cf60a652, x_435c561d.z, 0.0f, -1.0f, 0.0f);
        x_16eff9cc(&x_b082fd90, &x_e1751f31, &x_7eefcd11);
    }

    x_ba58a12b(&D_80080100->x_0f39faa7, &x_7eefcd11);

    x_2bef91d9 = x_435c561d.x - x_f4bce728->pos.x;
    x_86fee161 = x_435c561d.y - x_f4bce728->pos.y;
    x_2dffbf44 = x_435c561d.z - x_f4bce728->pos.z;

    x_f81735c3 = x_4c17a2ba;
    x_4c17a2ba = x_47d273d8(x_2dffbf44, x_2bef91d9);

    x_f5463fa4 = ABS(x_2bef91d9);
    x_98e2dc09 = ABS(x_2dffbf44);
    x_d16311d7 = x_4a9e7834(x_f5463fa4, x_98e2dc09);
    D_8013C594 = (f32) x_86fee161 / (f32) x_d16311d7;
    x_3f054879(x_2bef91d9, x_2dffbf44, x_f5463fa4, x_98e2dc09);

    D_8013C668.y = -0xC00 - x_4c17a2ba;
    D_8013C668.x = -x_47d273d8(x_86fee161, x_d16311d7);

    if (!(D_8008012C & x_8df87377) || model->x_50771dcd[0]) {
        D_80081428 = D_8013C828;
        x_6c647b3a = D_8013C82C - (s32) (x_cf60a652 * 0.2f);
    }
}

void x_80ee4395(void) {
    s32 perspNorm;

    guPerspectiveF(&x_e1751f31, &perspNorm, x_9972afd1, 4.0f / 3.0f, x_37b927c9, x_45c764a7,
                   x_bc5e8843);
    guLookAtF(&D_8013C670, 0.0f, 0.0f, -2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    x_16eff9cc(&D_8013C670, &x_e1751f31, &D_8013C6B0);
}

Object *x_7b6cfabc(void) {
    Object *obj;

    obj = x_5283664d(0x1200);

    obj->x_8da078cc.x = obj->x_8da078cc.y = obj->x_8da078cc.z = 0;
    obj->velocity.x = obj->velocity.y = obj->velocity.z = 0;
    obj->x_224610f1.x = obj->x_224610f1.y = obj->x_224610f1.z = 0;

    obj->flags = x_4271d4b5;
    obj->x_2b06a023 = -1;

    obj->x_d178c88f = (x_41a0e1e6 *) x_6d619dce(x_30839b82);
    obj->x_64946db0 = obj->x_d178c88f;
    obj->x_64946db0->x_c7f843c2 = 0;
    obj->x_64946db0->flags = x_0fb55613;
    obj->x_64946db0->x_f6382727 = x_0ae6735d;
    obj->x_64946db0->x_116c9ff3 = 0;
    obj->x_64946db0->next = NULL;

    x_435c561d.x = x_435c561d.z = 0;
    x_435c561d.y = -563;

    obj->pos.x = 0;
    obj->pos.y = -583;
    obj->pos.z = -2200;

    D_8013C588 = 180;
    x_37b927c9 = 600;
    x_45c764a7 = 11000;
    x_bc5e8843 = 1.0f;
    x_9972afd1 = 30.0f;

    x_3004a565(&x_b082fd90);
    x_3004a565(&x_e1751f31);

    obj->x_0232396f = x_2b791dba;
    D_8013C668.z = 0;

    obj->x_20d20338 = x_56c3086a(sizeof(x_6fcfcf46), "camera.c", 247);
    obj->x_20d20338->x_6dcce206 = 1;
    obj->x_20d20338->transforms = &D_8013C6F0;
    obj->x_20d20338->x_0094fc88 = &D_8013C808;

    x_f2c7456d(NULL, &obj->x_20d20338->x_abd7b3c4, -1, -2);
    x_f2c7456d(&obj->x_20d20338->x_abd7b3c4, obj->x_20d20338->transforms, 0, -1);

    obj->x_20d20338->x_9cfd7bb4.x = obj->x_20d20338->x_9cfd7bb4.y = obj->x_20d20338->x_9cfd7bb4.z = 0;
    obj->x_20d20338->x_50771dcd = D_80053030;
    D_80053030[0] = NULL;
    obj->x_20d20338->x_713417ac = obj->x_20d20338->x_3aefae96 = obj->x_20d20338->x_6786034d.z = 0;

    obj->flags |= x_03ae0e9e | x_9ee447da;
    obj->flags &= ~x_56bbd9b2;

    obj->x_20d20338->x_ee205ef9 = obj->x_20d20338->x_2f4c4ce1 = -3;

    x_80ee4395();

    obj->flags |= x_4271d4b5;
    D_8013C59C = D_8013C5A0 = 0.0f;
    x_6f8aa7af = FALSE;

    return obj;
}
