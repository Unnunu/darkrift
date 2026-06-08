#include "common.h"
#include "camera.h"
#include "task.h"

s16 x_8b270b48(Player *);
s16 x_a92b640d(Player *);

void x_f1e3e841(Object *obj);
void x_d5db0c41(Object *);
void x_e47877a0(Object *);
void x_67a3a840(Object *);
void x_adf28f33(Object *);
void x_b6853055(Object *);
void x_17ad7985(Object *);
void x_77f7ce0e(Object *);
void x_c1018f80(x_448872e8 *, x_998ccc48 *, Object *);

x_8b39d614 D_80052CF0 = { "dusthit.sp3", x_f1e3e841, 0, 0x1100, 0, 0x2800, 0 };
s32 D_80052D08[] = { 14, 17, 18, 21, 21, 24, 12, 15, 11, 14, 0, 0, 14, 17, 18, 21, 11, 14, 14, 17, 11, 14 };
Object *D_80052D60 = NULL;
s16 D_80052D64[] = { 0, 0 };
s16 D_80052D68[] = { 0, 0 };
s16 D_80052D6C[] = { 0, 0 };
s16 D_80052D70[] = { 0, 0 };
s16 D_80052D74[] = { 0, 0 };
s16 D_80052D78[] = { 2, 2 };

x_88f11482 D_8013C3A0[2];
s16 D_8013C3C0[2];
s32 D_8013C3C8[2];

u8 x_82bfe825(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    return (player->flags & x_cf6c9b89) || x_77831b2c[player->x_30bbe547].x_03604d94;
}

void x_19fed2ac(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->x_5fcb1654 > 5 && (player->flags & x_188f9cec)) {
        player->flags &= ~x_188f9cec;
        x_5e6f40dd(obj->x_64946db0);
    }
}

void x_f95cb1c9(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    player->flags &= ~x_cf6c9b89;
    if (!(player->x_7f68c36b->flags & x_037894c1)) {
        player->flags &= ~x_188f9cec;
    }
    obj->x_64946db0->x_f6382727 = x_0ae6735d;
}

void x_56d15e8a(Object *obj) {
    obj->x_64946db0->x_c7f843c2 = 10;
    obj->x_64946db0->x_f6382727 = x_f95cb1c9;
}

void x_f1e3e841(Object *obj) {
    obj->color.a -= 5;
    obj->x_5fcb1654++;
    if (obj->x_5fcb1654 > 9) {
        obj->flags |= x_f51cb721;
    }
    obj->x_64946db0->x_c7f843c2 = 2;
}

void x_5dea773a(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_30bbe547 = player->x_30bbe547;
    x_88f11482 *s1;
    Object *v0;
    x_88f11482 x_5aee6615;

    s1 = &D_8013C3A0[x_30bbe547];

    if ((abs(s1->x - obj->pos.x) > 20 || abs(s1->z - obj->pos.z) > 20) && !(player->flags & x_c865be3f)) {
        x_5aee6615.x = obj->pos.x;
        x_5aee6615.z = obj->pos.z;
        x_5aee6615.y = 0;
        v0 = x_1d5cf6e2(&x_5aee6615, &D_80052CF0, x_2587f84f);
        if (v0 != NULL) {
            v0->color.a = 60;
        }
    }

    s1->x = obj->pos.x;
    s1->z = obj->pos.z;
    if (--obj->x_0f4167b4[3] < 0) {
        player->x_95a50856 = 0;
    }
}

void x_8a61a432(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 v0;
    s32 x_720f6ac9, dz;

    v0 = 0;
    x_720f6ac9 = player->x_5c5b1d93.x_6e7f4fd8->x - player->x_5c5b1d93.x_1b148bc2->x;
    dz = player->x_5c5b1d93.x_6e7f4fd8->z - player->x_5c5b1d93.x_1b148bc2->z;

    if (x_720f6ac9 != 0 || dz != 0) {
        v0 = (u32) (sqrtf(x_84ce1cfb(x_720f6ac9) + x_84ce1cfb(dz)) + 0.5) >> 1;
    }
    if (v0 < 150) {
        v0 = 150;
    }

    player->x_5c5b1d93.x_38ae036c = x_84ce1cfb(v0);
    v0 = (v0 * 0xE000) >> 16;
    player->x_5c5b1d93.x_62706fff = x_84ce1cfb(v0);

    if (player->x_7f68c36b->flags & x_ff05097f) {
        obj->x_64946db0->x_f6382727 = x_5dea773a;
    } else {
        x_56d15e8a(obj);
    }
    obj->x_0f4167b4[3] = 50;
}

void x_9891654e(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_30bbe547 = player->x_30bbe547;

    player->flags &= ~x_030d2322;
    obj->x_20d20338->x_3aefae96 = D_8004BA98[player->x_eb1fe45b].x;
    obj->x_20d20338->x_713417ac = D_8004BA98[player->x_eb1fe45b].z;
    obj->x_64946db0->x_c7f843c2 = 2;
    obj->x_64946db0->x_f6382727 = x_8a61a432;
    obj->x_64946db0->x_c7f843c2 = 2;
    D_8013C3A0[x_30bbe547].x = obj->pos.x;
    D_8013C3A0[x_30bbe547].z = obj->pos.z;
}

void x_afe56bcd(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_30bbe547 = player->x_30bbe547;

    player->flags &= ~x_030d2322;
    obj->x_20d20338->x_713417ac = D_8004BAF0[player->x_eb1fe45b].z;
    obj->x_20d20338->x_3aefae96 = D_8004BAF0[player->x_eb1fe45b].x;
    obj->x_64946db0->x_c7f843c2 = 2;
    obj->x_64946db0->x_f6382727 = x_8a61a432;
    D_8013C3A0[x_30bbe547].x = obj->pos.x;
    D_8013C3A0[x_30bbe547].z = obj->pos.z;
}

void x_aa63f018(Object *obj) {
    x_5e6f40dd(obj->x_64946db0);
}

void x_01a2aa4d(Object *obj) {
    x_5e6f40dd(obj->x_64946db0);
}

void x_efd0ce39(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_7d3ef158;
    s32 temp;
    s16 v1;

    x_7d3ef158 = (0xC00 - obj->x_224610f1.y) & 0xFFF;

    temp = x_39970af2(x_09a33777 - (player->x_30bbe547 != x_83106b21 ? 0 : 0x800), x_7d3ef158);
    if (temp < 0) {
        v1 = temp + 0x800;
    } else {
        v1 = temp - 0x800;
    }

    obj->x_224610f1.y = 0xC00 - x_7d3ef158 - v1;
    x_5e6f40dd(obj->x_64946db0);
}

u8 x_52c80142(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 pad[3];
    s16 x_eb1fe45b;
    s16 x_de68d2a6 = 1 - player->x_30bbe547;
    s16 temp;
    x_88f11482 x_93463df6;

    x_eb1fe45b = x_824b9544[x_de68d2a6].x_eb1fe45b;
    temp = D_8004B920[x_eb1fe45b].x_af0aa1f8;

    x_93463df6.x = 0;
    x_93463df6.y = 0;
    x_93463df6.z = -temp;
    x_9b0df250(&x_93463df6, &obj->x_224610f1);
    (x_824b9544 + x_de68d2a6)->obj->pos.x = obj->pos.x + x_93463df6.x;
    (x_824b9544 + x_de68d2a6)->obj->pos.z = obj->pos.z + x_93463df6.z;
    (x_824b9544 + x_de68d2a6)->obj->x_224610f1.y = 0x400 - ((0xC00 - obj->x_224610f1.y) & 0xFFF);

    return TRUE;
}

void x_82fdb659(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = x_824b9544 + 1 - player->x_30bbe547;
    s16 x_eb1fe45b = player->x_eb1fe45b;

    if (obj->x_5fcb1654 == player->x_7f68c36b->x_bab9966d - 1) {
        player->x_6f5a5c61 = obj->x_0f4167b4[2];
        if (obj->x_0f4167b4[3] < 0) {
            player->x_95a50856 += player->x_6f5a5c61;
        } else {
            player->x_95a50856 = player->x_6f5a5c61;
            obj->x_0f4167b4[3] = -1;
        }

        if (x_5e4e2788 != x_79c2dc5b) {
            x_98c4e5a5->obj->x_9200c538 -= obj->x_0f4167b4[2];
        }
        if (x_98c4e5a5->obj->x_9200c538 < 0) {
            x_98c4e5a5->obj->x_9200c538 = 0;
        }
    }

    switch (x_eb1fe45b) {
        case x_c4ddde6d:
            x_c3947955(obj);
            break;
        case x_73cf9ceb:
            if (x_77831b2c[1 - player->x_30bbe547].x_eb1fe45b == x_13ed828f &&
                obj->x_5fcb1654 < player->x_7f68c36b->x_bab9966d - 1) {
                obj->pos.y = 100;
            } else {
                obj->pos.y = 0;
            }
            x_77f7ce0e(obj);
            break;
        default:
            if (D_8004BA40[x_eb1fe45b] != NULL) {
                x_77f7ce0e(obj);
            }
            break;
    }
}

void x_82196a2e(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->x_5fcb1654 >= player->x_7f68c36b->x_bab9966d - 2) {
        player->x_6f5a5c61 = obj->x_0f4167b4[2];
        if (obj->x_0f4167b4[3] < 0) {
            player->x_95a50856 += player->x_6f5a5c61;
        } else {
            player->x_95a50856 = player->x_6f5a5c61;
            obj->x_0f4167b4[3] = -1;
        }

        if (x_5e4e2788 != x_79c2dc5b) {
            player->obj->x_9200c538 -= obj->x_0f4167b4[2];
        }
        if (player->obj->x_9200c538 < 0) {
            player->obj->x_9200c538 = 0;
        }

        player->x_08b62e4f->x_f6382727 = x_340c2137;
    }
}

void x_6c979ff3(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s16 x_de68d2a6 = 1 - player->x_30bbe547;

    player->x_08b62e4f->x_f6382727 = x_82196a2e;

    if (x_824b9544[x_de68d2a6].x_eb1fe45b != x_c4ddde6d) {
        obj->x_64946db0->x_f6382727 = x_17ad7985;
    } else {
        x_5e6f40dd(obj->x_64946db0);
    }
}

void x_6098478f(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 pad[2];
    s16 x_eb1fe45b;
    s16 x_de68d2a6;
    s32 pad2;
    s16 temp;
    x_388306ba *x_fc517ba8;
    x_88f11482 x_93463df6;

    if (x_9df63a90 && x_33abac12 == 0) {
        x_5e6f40dd(obj->x_64946db0);
        return;
    }

    if (obj->x_5fcb1654 != player->x_7f68c36b->x_bab9966d - 1) {
        return;
    }

    x_eb1fe45b = player->x_eb1fe45b;
    x_de68d2a6 = 1 - player->x_30bbe547;
    player->x_381817ae = 2;

    if (!(player->flags & x_9298c772) && x_9a96200f < D_8004C178[player->x_eb1fe45b] &&
        (x_824b9544[x_de68d2a6].x_7f68c36b->flags & x_ff05097f) && !(x_824b9544[x_de68d2a6].x_7f68c36b->flags & x_7b8f7fad)) {
        x_5e6f40dd(obj->x_64946db0);

        if (x_824b9544[x_de68d2a6].flags & x_9298c772) {
            if (!(x_824b9544[x_de68d2a6].x_7f68c36b->flags & x_cdcff2e1)) {
                x_c05bfb58(&x_824b9544[x_de68d2a6], x_e7a14975, 1);
            }
            return;
        }

        player->flags |= x_a45101c0;

        D_80080236 = TRUE;
        x_c05bfb58(&x_824b9544[x_de68d2a6], D_8004B8F4[x_eb1fe45b].x_cd679b4c, 1);
        x_c05bfb58(player, x_67148cc8, 1);
        D_80080236 = FALSE;
        x_fc517ba8 = &player->x_68a6b5cd[player->x_cd14c741];
        player->obj->x_e2f64c57[2] = x_fc517ba8->x_6f5a5c61;

        temp = D_8004B8F4[x_eb1fe45b].x_af0aa1f8;
        x_93463df6.x = 0;
        x_93463df6.y = 0;
        x_93463df6.z = -temp;
        x_9b0df250(&x_93463df6, &obj->x_224610f1);
        (x_824b9544 + x_de68d2a6)->obj->pos.x = obj->pos.x + x_93463df6.x;
        (x_824b9544 + x_de68d2a6)->obj->pos.z = obj->pos.z + x_93463df6.z;
        (x_824b9544 + x_de68d2a6)->obj->x_224610f1.y = 0x400 - ((0xC00 - obj->x_224610f1.y) & 0xFFF);

        D_8008012C &= ~x_c626209d;
        x_943bfef8();

        switch (x_eb1fe45b) {
            case x_537ef8a7:
                obj->flags |= x_d13a68b5;
                break;
            case x_c4ddde6d:
                if (x_fc517ba8->x_fc1da284 >= 0) {
                    player->x_0b88f58e = &player->x_38b3091d[x_fc517ba8->x_fc1da284];
                    player->x_66350762 = NULL;
                }
                break;
        }
    }
}

void x_602b94bb(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    s32 x_eb1fe45b;
    s16 x_de68d2a6;
    s32 unused[3];

    if (obj->x_5fcb1654 == player->x_7f68c36b->x_c53ac2df) {
        x_eb1fe45b = player->x_eb1fe45b;
        x_de68d2a6 = 1 - player->x_30bbe547;
        x_c05bfb58(&x_824b9544[x_de68d2a6], D_8004B920[x_eb1fe45b].x_cd679b4c, 1);

        if (player->x_eb1fe45b == x_c4ddde6d) {
            obj->x_64946db0->x_f6382727 = x_cfb419a2;
        } else if (D_8004BA6C[x_eb1fe45b] != NULL) {
            obj->x_64946db0->x_f6382727 = x_d5db0c41;
        } else {
            x_5e6f40dd(obj->x_64946db0);
        }
    }
}

void x_23eecff5(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (player->x_eb1fe45b == x_968cc9a2) {
        obj->x_64946db0->x_f6382727 = x_cfb419a2;
    } else if (D_8004BA6C[player->x_eb1fe45b] != NULL) {
        obj->x_64946db0->x_f6382727 = x_d5db0c41;
    } else {
        x_5e6f40dd(obj->x_64946db0);
    }
}

u8 x_e0b539de(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[1 - player->x_30bbe547];

    if (x_98c4e5a5->flags & x_6de2d515) {
        return TRUE;
    } else {
        return FALSE;
    }
}

u8 x_d52f4e7d(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[1 - player->x_30bbe547];

    if (x_98c4e5a5->flags & x_d8a402c3) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void x_05bc3408(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] > 60) {
        obj->flags |= x_f51cb721;
        x_cf60a652 = 0;
        D_80052D60 = 0;
    } else if (x_cf60a652 > 0) {
        x_cf60a652 -= 10;
    } else {
        obj->x_0232396f = x_b6853055;
    }
}

void x_b6853055(Object *obj) {
    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] > 60) {
        obj->flags |= x_f51cb721;
        x_cf60a652 = 0;
        D_80052D60 = 0;
    } else if (x_cf60a652 < obj->x_0f4167b4[1]) {
        x_cf60a652 += 10;
    } else {
        obj->x_0232396f = x_05bc3408;
        obj->x_0f4167b4[1] -= 15;
    }
}

Object *x_24276d64(void) {
    if (D_80052D60 != NULL) {
        D_80052D60->flags |= x_f51cb721;
    }

    D_80052D60 = x_4495b42c(x_b6853055, 0x1000);
    return D_80052D60;
}

void x_507d2a70(Object *obj) {
    if (obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y > -200.0f) {
        x_7621a350(obj);
        obj->x_64946db0->x_f6382727 = x_adf28f33;
        obj->x_64946db0->x_c7f843c2 = 20;
    }
}

void x_adf28f33(Object *obj) {
    if (obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y > -200.0f) {
        return;
    }

    obj->x_64946db0->x_f6382727 = x_507d2a70;
}

void x_17ad7985(Object *obj) {
    Object *v0;

    if (obj->x_20d20338->x_abd7b3c4.x_3fde9cd9.w.y > -200.0f) {
        x_7621a350(obj);
        v0 = x_24276d64();
        if (v0 != NULL) {
            v0->x_0f4167b4[1] = 50;
        }

        obj->x_64946db0->x_f6382727 = x_adf28f33;
        obj->x_64946db0->x_c7f843c2 = 20;
    }
}

void x_5b5c4189(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->x_5fcb1654 > (player->x_7f68c36b->x_bab9966d >> 1)) {
        player->x_b9252303->x_f6382727 = x_d18c17c2;
        player->x_b9252303->x_c7f843c2 = 0;
        player->x_b9252303->flags = x_0fb55613;
    } else {
        player->x_b9252303->x_f6382727 = x_55af5110;
        player->x_b9252303->x_c7f843c2 = 0;
        player->x_b9252303->flags = x_0fb55613;
        obj->flags |= x_56bbd9b2;
    }

    player->flags &= ~x_188f9cec;
    x_5e6f40dd(obj->x_64946db0);
}

void x_ca73900f(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    obj->velocity.y += obj->x_8da078cc.y;
    obj->pos.y += obj->velocity.y >> 16;

    if (obj->pos.y >= 0) {
        obj->pos.y = 0;
        if (player->flags & x_9298c772) {
            x_c05bfb58(player, x_98df8f9f, 1);
        } else {
            x_c05bfb58(player, x_37718e57, 1);
        }
    }
}

void x_297fd9f3(Object *obj) {
    obj->velocity.y = 0xFFEC0000;
    obj->x_8da078cc.y = 0x20000;
    obj->x_64946db0->x_f6382727 = x_ca73900f;
    x_67a3a840(obj);
}

u8 x_af5ccc8a(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    u8 x_cd986d3c;
    s32 t8;

    x_cd986d3c = FALSE;
    t8 = (0xC00 - obj->x_224610f1.y) & 0xFFF;

    if (obj->flags & x_da584e3c) {
        return FALSE;
    }

    if (player->x_30bbe547 != x_83106b21) {
        if (abs(x_39970af2(x_09a33777, t8)) > 0x400) {
            x_cd986d3c = TRUE;
        }
    } else {
        if (abs(x_39970af2(x_09a33777, t8)) < 0x400) {
            x_cd986d3c = TRUE;
        }
    }

    return x_cd986d3c;
}

void x_c946d6b1(Object *obj) {
    s16 v0;

    v0 = (0xC00 - obj->x_224610f1.y) & 0xFFF;
    obj->x_224610f1.y = 0x400 - v0;
}

u8 x_8c8da256(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    if (((x_98c4e5a5->x_7f68c36b->flags & (x_7507aa4b | x_eac5209f | x_8b64a078 | x_c1df43e1)) &&
         !(x_98c4e5a5->x_7f68c36b->flags & x_7b8f7fad)) > 0) {
        if (player->x_30bbe547 != x_83106b21) {
            player->obj->x_224610f1.y = 0xC00 - x_09a33777;
        } else {
            player->obj->x_224610f1.y = 0x1400 - x_09a33777;
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

void x_d76c20a9(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    obj->x_64946db0->x_c7f843c2 = player->x_68a6b5cd[player->x_cd14c741].x_887b6be9 - obj->x_5fcb1654 + 2;
    obj->x_64946db0->x_f6382727 = x_e47877a0;
}

void x_e47877a0(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    s16 a1 = x_dba71d7e;

    if ((x_98c4e5a5->flags & (x_030d2322 | x_6de2d515 | x_faf494e7)) &&
        x_9a96200f < 400 && obj->x_5fcb1654 >= player->x_7f68c36b->x_c53ac2df) {
        if (x_98c4e5a5->x_7f68c36b->flags & x_7507aa4b) {
            a1 = x_caa30513;
        }
        x_c05bfb58(x_98c4e5a5, a1, 1);
        x_5e6f40dd(obj->x_64946db0);
    }
}

void x_eb9bf905(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (x_9a96200f < D_8004C1A4[player->x_eb1fe45b] && player->x_cd14c741 != 17) {
        x_c05bfb58(player, x_e5ca67a6, 1);
        x_5e6f40dd(obj->x_64946db0);
    }
}

void x_af431a0a(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (player->x_eb1fe45b == x_b52da315) {
        obj->x_64946db0->x_c7f843c2 = 2;
    } else {
        obj->x_64946db0->x_c7f843c2 = 6;
    }
    obj->x_64946db0->x_f6382727 = x_eb9bf905;
}

u8 x_e821cb83(s32 x_cc1d0de5) {
    return x_9a96200f > 550;
}

void x_31926e97(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    s16 x_434431dd;
    s16 x_7d3ef158;

    x_434431dd = (0xC00 - x_98c4e5a5->obj->x_224610f1.y) & 0xFFF;
    x_7d3ef158 = x_39970af2(x_09a33777, x_434431dd);

    if (x_7d3ef158 < 0) {
        x_7d3ef158 -= 0x800;
    } else {
        x_7d3ef158 += 0x800;
    }
    x_98c4e5a5->obj->x_224610f1.y = 0xC00 - (x_434431dd + x_7d3ef158);
}

void x_e1ae01d8(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    x_98c4e5a5->flags |= x_188f9cec;
}

void x_df5751ad(Object *obj) {
    if (obj->pos.y == 0) {
        x_ebe27fa0(obj);
    }

    obj->x_64946db0->x_f6382727 = x_e1ae01d8;
}

void x_67a3a840(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    if ((x_98c4e5a5->x_7f68c36b->flags & x_6f3569a1) || (x_98c4e5a5->x_08bf2418->x_bb8c769c & x_188f9cec)) {
        x_98c4e5a5->flags |= x_188f9cec;
    } else {
        x_98c4e5a5->flags &= ~x_188f9cec;
    }
}

void x_02f6f8ad(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (obj->x_5fcb1654 == player->x_7f68c36b->x_bab9966d - 1) {
        x_67a3a840(obj);
    }
}

void x_18bd9b95(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];

    if (x_98c4e5a5->x_7f68c36b->flags & x_6f3569a1) {
        x_98c4e5a5->flags |= x_188f9cec;
    }

    if (obj->x_5fcb1654 >= 24) {
        player->flags &= ~x_188f9cec;
    }
}

void x_ca4d8099(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    Object *x_5bbba600 = x_3ac11521[x_83106b21];
    Object *x_dd7ffac5 = x_3ac11521[x_6f0b3be3];
    s16 x_f6289181;
    s16 x_4346f5cb;
    s16 x_7d3ef158;

    if (x_98c4e5a5->x_7f68c36b->x_6f5a5c61 != 0) {
        x_98c4e5a5->flags |= x_188f9cec;
    }

    if (!(player->flags & x_188f9cec) && (player->flags & x_9298c772) &&
        (player->x_cd14c741 == 39 || player->x_cd14c741 == 84)) {
        if (player->x_30bbe547 != x_83106b21) {
            x_4346f5cb = (0xC00 - x_dd7ffac5->x_224610f1.y) & 0xFFF;
            x_7d3ef158 = x_39970af2(x_09a33777 - 0x800, x_4346f5cb);

            if (abs(x_7d3ef158) > 140) {
                if (x_7d3ef158 < 0) {
                    x_7d3ef158 = -140;
                } else {
                    x_7d3ef158 = 140;
                }
            }
            x_dd7ffac5->x_224610f1.y = 0xC00 - (x_4346f5cb + x_7d3ef158);
        } else {
            x_f6289181 = (0xC00 - x_5bbba600->x_224610f1.y) & 0xFFF;
            x_7d3ef158 = x_39970af2(x_09a33777, x_f6289181);

            if (abs(x_7d3ef158) > 140) {
                if (x_7d3ef158 < 0) {
                    x_7d3ef158 = -140;
                } else {
                    x_7d3ef158 = 140;
                }
            }
            x_5bbba600->x_224610f1.y = 0xC00 - (x_f6289181 + x_7d3ef158);
        }
    }
}

void x_7ef99aca(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Object *x_13d65ace = x_3ac11521[x_83106b21];
    Object *x_c48d15e0 = x_3ac11521[x_6f0b3be3];

    if (!(player->flags & x_9298c772) && obj->x_5fcb1654 >= player->x_7f68c36b->x_bab9966d - 1) {
        if (player->x_30bbe547 != x_83106b21) {
            x_c48d15e0->x_224610f1.y = 0xC00 - x_09a33777;
        } else {
            x_13d65ace->x_224610f1.y = 0x1400 - x_09a33777;
        }
    }
}

void x_d87a4f6e(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *x_98c4e5a5;
    s32 v12;
    s16 a3;

    x_98c4e5a5 = &x_824b9544[player->x_30bbe547 != x_83106b21 ? x_83106b21 : x_6f0b3be3];
    a3 = x_98c4e5a5->x_cd14c741;
    switch (a3) {
        case 36:
        case 48:
        case 81:
        case 82:
        case 88:
        case 89:
        case 94:
        case 118:
        case 119:
        case 120:
        case 121:
            v12 = TRUE;
            break;
        default:
            v12 = FALSE;
            break;
    }

    if (a3 == 52) {
        v12 = TRUE;
        if (x_98c4e5a5->flags & x_188f9cec) {
            if (x_98c4e5a5->x_30bbe547 != x_83106b21) {
                x_98c4e5a5->obj->x_224610f1.y = 0x1400 - x_09a33777;
            } else {
                x_98c4e5a5->obj->x_224610f1.y = 0xC00 - x_09a33777;
            }
        } else {
            if (x_98c4e5a5->x_30bbe547 != x_83106b21) {
                x_98c4e5a5->obj->x_224610f1.y = 0xC00 - x_09a33777;
            } else {
                x_98c4e5a5->obj->x_224610f1.y = 0x1400 - x_09a33777;
            }
        }
    }

    if (player->x_101ebc50 > 0x100 || (x_98c4e5a5->x_7f68c36b->flags & x_025a12b8) || v12) {
        player->flags |= x_188f9cec;
        x_5e6f40dd(obj->x_64946db0);
    }
}

u8 x_5127226c(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (x_77831b2c[player->x_30bbe547].x_03604d94) {
        return TRUE;
    }

    return x_59ce598c[player->x_30bbe547].x_d93bcabf;
}

u8 x_a8ff9909(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];

    if (x_77831b2c[player->x_30bbe547].x_03604d94) {
        return TRUE;
    }

    return ~x_59ce598c[player->x_30bbe547].x_d93bcabf;
}

u8 x_29d2787d(Object *obj) {
    Player *player;
    Player *v1;
    s32 a1;

    player = (Player *) obj->x_e2f64c57[0];
    v1 = x_824b9544 + (1 - player->x_30bbe547);

    a1 = (v1->x_7f68c36b->flags & x_01e3e146) && (v1->x_7f68c36b->x_fedecf5c < v1->obj->x_5fcb1654 ||
                                                   v1->x_7f68c36b->x_c53ac2df > v1->obj->x_5fcb1654);
    return a1 > 0;
}

void x_4a0e9b26(Object *obj) {
    Player *player = (Player *) obj->x_e2f64c57[0];
    Player *v0;
    x_388306ba *v1;

    v0 = x_824b9544 + (1 - player->x_30bbe547);
    v1 = &player->x_68a6b5cd[player->x_cd14c741];

    if (!(v1->flags & x_f79587cb) && x_77831b2c[player->x_30bbe547].x_03604d94 && (v0->x_7f68c36b->flags & x_01e3e146) &&
        v0->obj->x_5fcb1654 < v0->x_7f68c36b->x_c53ac2df) {
        if (v0->flags & x_ed8e51a2) {
            x_c05bfb58(player, x_e2a42ecd, 1);
            player->x_81570fde.x_ca75ac5d = x_8b270b48;
            player->x_81570fde.x_5a6554ba = 60;
        } else {
            x_c05bfb58(player, x_8a9cd4d8, 1);
            player->x_81570fde.x_ca75ac5d = x_a92b640d;
            player->x_81570fde.x_5a6554ba = 60;
        }
    }
}

#ifdef x_0fab73bf
void x_340c2137(Object *x_cc1d0de5) {
    x_2758cdab x_331089fa;
    x_2758cdab x_fd09f53e;
    Player *x_3be4fcf3;
    u8 x_e9fc447d;
    u8 x_3f615590;
    s16 x_ccb8eae3;
    s32 x_7be1f4c5;
    s16 x_e22db69c;

    s16 x_8450963f;
    s16 x_e27567e2;
    s16 x_dab5f4cd;
    s16 x_201aee20;
    s16 x_e03d0d18;

    s16 x_cf297abc;

    s16 x_73c8560b;
    s16 x_c8532a08;

    x_3be4fcf3 = (Player *) x_cc1d0de5->x_e2f64c57[0];
    x_e9fc447d = x_3be4fcf3->x_30bbe547;
    x_3f615590 = 1 - x_e9fc447d;

    x_331089fa.z = 0;
    x_fd09f53e.x = 0;
    x_fd09f53e.z = 0;

    x_ccb8eae3 = x_3be4fcf3->x_a4b33e43;
    x_7be1f4c5 = x_3ac11521[x_3f615590]->x_20d20338->x_abd7b3c4.x_0c1a9bdd.y.y + 360.0f;
    if (x_ccb8eae3 == 0 || x_ccb8eae3 == 7 || (x_3be4fcf3->x_7f68c36b->flags & x_f79587cb)) {
        x_331089fa.x = x_47d273d8(x_7be1f4c5, x_9a96200f);
        x_cf297abc = x_39970af2((s16) ((0xC00 - x_cc1d0de5->x_224610f1.y) & 0xFFF), (s16) (x_09a33777 - (x_3f615590 << 0xB)));

        if (x_cf297abc > 1700) {
            x_cf297abc = 1700;
        } else if (x_cf297abc < -1100) {
            x_cf297abc = -1100;
        }

        x_c8532a08 = D_80052D64[x_e9fc447d];
        x_73c8560b = D_80052D68[x_e9fc447d];
        x_e22db69c = x_cf297abc - x_c8532a08 - x_73c8560b;
    } else {
        x_73c8560b = D_80052D68[x_e9fc447d];
        x_c8532a08 = D_80052D64[x_e9fc447d];
        x_cf297abc = 0;
        x_331089fa.x = 0;
        x_e22db69c = -(x_73c8560b + x_c8532a08);
    }

    if (x_e22db69c == 0) {
        D_80052D70[x_e9fc447d] = D_80052D74[x_e9fc447d] = 0;
        D_80052D78[x_e9fc447d] = 2;
        D_8013C3C0[x_e9fc447d] = x_73c8560b + x_c8532a08;
    }

    D_80052D6C[x_e9fc447d] = ((D_8013C3C0[x_e9fc447d] + x_cf297abc) >> 1);
    D_80052D74[x_e9fc447d] += D_80052D78[x_e9fc447d];
    D_80052D70[x_e9fc447d] += D_80052D74[x_e9fc447d];

    if (D_80052D70[x_e9fc447d] > 60) {
        D_80052D70[x_e9fc447d] = 60;
        D_80052D78[x_e9fc447d] = 0;
    } else if (D_80052D70[x_e9fc447d] <= 0) {
        D_80052D70[x_e9fc447d] = 2;
        D_80052D78[x_e9fc447d] = 2;
    }
    if (D_80052D70[x_e9fc447d] < x_e22db69c) {
        x_e22db69c = D_80052D70[x_e9fc447d];
    } else if (x_e22db69c < -D_80052D70[x_e9fc447d]) {
        x_e22db69c = -D_80052D70[x_e9fc447d];
    }
    if (x_73c8560b > 0) {
        x_e03d0d18 = x_c8532a08 + x_e22db69c;
        if (x_e22db69c >= 0) {
            x_8450963f = x_73c8560b + x_e22db69c;
            if (x_8450963f > 600) {
                x_e22db69c = x_8450963f - 600;
                x_e03d0d18 = x_c8532a08 + x_e22db69c;

                x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = 600;
                if (x_e03d0d18 > 1100) {
                    x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = 1100;
                } else {
                    x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
                }
            } else {
                x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_8450963f;
                x_331089fa.y = x_c8532a08;
            }
        } else {
            if (x_e03d0d18 < 0) {
                x_e27567e2 = x_73c8560b + x_e03d0d18;
                x_e22db69c = x_e03d0d18;

                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = 0;
                if (x_e27567e2 < 0) {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = 0;
                } else {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_e27567e2;
                }
            } else {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
                x_fd09f53e.y = x_73c8560b;
            }
        }
    } else if (x_73c8560b < 0) {
        x_dab5f4cd = x_73c8560b + x_e22db69c;
        if (x_e22db69c >= 0) {
            x_e03d0d18 = x_c8532a08 + x_e22db69c;
            if (x_e03d0d18 > 0) {
                x_201aee20 = x_73c8560b + x_e03d0d18;
                x_e22db69c = x_e03d0d18;

                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = 0;
                if (x_201aee20 > 0) {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = 0;
                } else {
                    x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_201aee20;
                }
            } else {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
                x_fd09f53e.y = x_73c8560b;
            }
        } else if (x_dab5f4cd < -600) {
            x_e22db69c = x_dab5f4cd + 600;
            x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = -600;
            x_e03d0d18 = x_c8532a08 + x_e22db69c;
            if (x_e03d0d18 < -500) {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = -500;
            } else {
                x_331089fa.y = x_c8532a08 = D_80052D64[x_e9fc447d] = x_e03d0d18;
            }
        } else {
            x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_dab5f4cd;
            x_331089fa.y = x_c8532a08;
        }
    } else {
        x_331089fa.y = x_c8532a08;
        x_fd09f53e.y = x_73c8560b = D_80052D68[x_e9fc447d] = x_73c8560b + x_e22db69c;
    }

    if (D_80052D74[x_e9fc447d] > 0) {
        if (x_e22db69c >= 0 && x_c8532a08 + x_73c8560b >= D_80052D6C[x_e9fc447d]) {
            D_80052D78[x_e9fc447d] = -2;
        } else if (D_80052D6C[x_e9fc447d] >= x_c8532a08 + x_73c8560b) {
            D_80052D78[x_e9fc447d] = -2;
        }
    }

    x_948f0b9f(&x_3be4fcf3->x_a4d7c80d.x_3fde9cd9, &x_331089fa);
    x_948f0b9f(&x_3be4fcf3->x_022dff72.x_3fde9cd9, &x_fd09f53e);
}
#else
#pragma x_eda6f9e3("asm/nonmatchings/305A0/func_8003184C.s")
#endif

void x_77f7ce0e(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    x_448872e8 *s0;

    for (s0 = D_8004BA40[v0->x_eb1fe45b]; s0->x_af0aa1f8 != 0; s0++) {
        if (obj->x_5fcb1654 == s0->x_af0aa1f8) {
            x_c1018f80(s0, &v0->x_5c5b1d93, obj);
        }
    }
}

void x_d5db0c41(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    x_448872e8 *s0;

    for (s0 = D_8004BA6C[v0->x_eb1fe45b]; s0->x_af0aa1f8 != 0; s0++) {
        if (obj->x_5fcb1654 == s0->x_af0aa1f8) {
            x_c1018f80(s0, &v0->x_5c5b1d93, obj);
        }
    }
}

void x_c1018f80(x_448872e8 *x_cc1d0de5, x_998ccc48 *x_5c5b1d93, Object *x_2092f891) {
    Player *player = (Player *) x_2092f891->x_e2f64c57[0];
    x_123b8fa2 *v0;
    x_acccb624 x_a1fcc259;

    switch (x_cc1d0de5->x_cd679b4c) {
        case 0:
            v0 = x_5c5b1d93->x_1b148bc2;
            break;
        case 1:
            v0 = x_5c5b1d93->x_6e7f4fd8;
            break;
        case 2:
            v0 = x_5c5b1d93->x_b7552092;
            break;
        case 3:
            v0 = &x_5c5b1d93->x_0548cec6.x_0c1a9bdd.w;
            break;
        case 4:
            v0 = &x_5c5b1d93->x_cc2c17a6.x_0c1a9bdd.w;
            break;
        case 5:
            v0 = x_5c5b1d93->x_3b24b185;
            break;
        case 6:
        default:
            v0 = x_5c5b1d93->x_55f532bb;
            break;
    }

    x_a1fcc259.x = v0->x;
    x_a1fcc259.y = v0->y;
    x_a1fcc259.z = v0->z;
    x_801c8e55(&x_a1fcc259, x_cc1d0de5->x_1256da71, x_2092f891, &D_8004BA14[player->x_eb1fe45b]);
}

void x_370c7b4f(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (v0->x_eb1fe45b == x_c4ddde6d) {
        obj->x_64946db0->x_f6382727 = x_cfb419a2;
    } else {
        x_5e6f40dd(obj->x_64946db0);
    }
}

void x_05731c3c(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    x_c05bfb58(v0, x_dcbb43b9, 1);
}

void x_e9917882(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (obj->x_5fcb1654 == v0->x_7f68c36b->x_bab9966d - 2) {
        obj->x_64946db0->x_f6382727 = x_05731c3c;
    }
}

void x_96e05dec(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (v0->flags & x_9298c772) {
        x_c05bfb58(v0, x_9f2970bc, 1);
    } else {
        obj->x_64946db0->x_c7f843c2 = 60;
        obj->x_64946db0->x_f6382727 = x_05731c3c;
    }
}

void x_a3014bb9(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    x_c05bfb58(v0, x_445015b3, 1);
}

void x_fd0916cc(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];

    if (x_77831b2c[x_83106b21].x_eb1fe45b == x_77831b2c[x_6f0b3be3].x_eb1fe45b && v0->x_30bbe547 != 0) {
        obj->x_64946db0->x_c7f843c2 = 15;
    }

    obj->x_64946db0->x_f6382727 = x_a3014bb9;
}

void x_c1c8c6a7(Object *obj) {
    x_88f11482 x_dd7ffac5;
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    s32 v1 = v0->x_30bbe547;

    if (obj->x_5fcb1654 == v0->x_7f68c36b->x_bab9966d - 1) {
        x_dd7ffac5.x = x_dd7ffac5.y = 0;
        x_dd7ffac5.z = -D_8013C3C8[v1];
        x_9b0df250(&x_dd7ffac5, &obj->x_224610f1);
        obj->pos.x += x_dd7ffac5.x;
        obj->pos.z += x_dd7ffac5.z;
        obj->x_64946db0->x_f6382727 = x_c3947955;
    }

    x_c3947955(obj);
}

void x_bc38049f(Object *obj) {
    Player *v0 = (Player *) obj->x_e2f64c57[0];
    s32 v1 = v0->x_30bbe547;

    if (v0->x_eb1fe45b == x_ff5073d4 && obj->x_5fcb1654 > 50) {
        x_c3947955(obj);
        obj->x_64946db0->x_f6382727 = x_c3947955;
    } else {
        D_8013C3C8[v1] = x_9a96200f;
        x_cfb419a2(obj);
        obj->x_64946db0->x_f6382727 = x_c1c8c6a7;
    }
}
