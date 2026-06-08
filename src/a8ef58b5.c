#include "common.h"
#include "string.h"

#define x_2bc76549 0xABCD6789
#define x_6919331f 0x23E806
#define x_af32df05 256

void x_28d4de16(x_704d55d4 *x_cc1d0de5, x_704d55d4 **x_84ff873b);
void x_0be47d8a(u32 *dest, u32 *src, u32 size);

x_704d55d4 *x_cf9b7451 = NULL;
x_704d55d4 *x_3c86e126 = NULL;
u8 D_80049288 = FALSE;

OSIoMesg D_8005AE90;
char x_898d1dc9[0x8];
s32 x_21ce7377;
s32 x_04e9945f;
x_37652cbd D_8005AEB8[x_af32df05];
s32 D_8005BEB8;
char x_7cb809a7[0x4];
void *x_40c4fc96;

void x_6779fd58(s32 x_cc1d0de5, s32 x_84ff873b) {
    s32 i, j;

    for (i = 0; i != x_84ff873b; i++) {
        for (j = 2; j < 10; j += 4) {
            // do nothing
        }
    }
}

void x_82b801fe(void) {
    x_cf9b7451 = (x_704d55d4 *) x_40c4fc96;

    x_cf9b7451->end = ((u32) (x_40c4fc96) + x_6919331f) & ~7;
    x_cf9b7451->flags = 1;
    x_cf9b7451->next = NULL;
    x_cf9b7451->previous = NULL;
    x_21ce7377 = 0;
    x_cf9b7451->x_a9d4034d = x_2bc76549;

    x_04e9945f = x_b30d1d21(x_cf9b7451);
}

void x_fd701d0e(void) {
    s32 end;
    s32 x_d70d9bc9;
    void *x_968605c7;
    s32 v0;
    s32 i;
    x_704d55d4 *x_5d7a764d;
    s32 x_4cf275a8;
    void *x_50f1dbff;
    x_704d55d4 *x_24aca5c4;

    x_21ce7377 = 0;

    x_cf9b7451 = x_40c4fc96;
    x_cf9b7451->flags = 1;
    x_cf9b7451->previous = NULL;
    x_cf9b7451->next = NULL;

    x_3c86e126 = NULL;
    x_cf9b7451->x_a9d4034d = x_2bc76549;

    end = ((u32) (x_40c4fc96) + x_6919331f) & ~7;

    do {
        x_d70d9bc9 = -1;
        x_968605c7 = NULL;

        for (i = 0; i < x_e286d4b7(D_8005AEB8); i++) {
            x_37652cbd *slot = D_8005AEB8 + i;
            if (!(slot->x_af0aa1f8 & 1) && (u32) slot->data < end) {
                void *x_d1231a38 = slot->data;
                if (x_d1231a38 > x_968605c7) {
                    x_968605c7 = x_d1231a38;
                    x_d70d9bc9 = i;
                }
                if (!x_cf9b7451) {} // required for matching
            }
        }

        if (x_d70d9bc9 >= 0) {
            s32 x_c028c62d = (u32) D_8005AEB8[x_d70d9bc9].data - sizeof(x_704d55d4);
            x_5d7a764d = (x_704d55d4 *) x_c028c62d;
            x_4cf275a8 = x_5d7a764d->end - (u32) x_5d7a764d - sizeof(x_704d55d4);
            x_50f1dbff = end - x_4cf275a8;
            if (x_50f1dbff != D_8005AEB8[x_d70d9bc9].data) {
                x_5d7a764d = end - x_5d7a764d->end + (s32) x_5d7a764d;
                x_0be47d8a(x_50f1dbff, D_8005AEB8[x_d70d9bc9].data, x_4cf275a8);
                x_5d7a764d->end = end;
                x_5d7a764d->flags = 0;
                x_5d7a764d->next = x_5d7a764d->previous = NULL;
                x_5d7a764d->x_a9d4034d = x_2bc76549;
            } else {
                x_5d7a764d->next = x_5d7a764d->previous = NULL;
            }

            end = x_5d7a764d;
            x_21ce7377 = x_21ce7377 + x_5d7a764d->end - (u32) (x_24aca5c4 = x_5d7a764d) - sizeof(x_704d55d4);
            x_28d4de16(x_5d7a764d, &x_3c86e126);
            if (D_8005AEB8[x_d70d9bc9].x_3c30b5f3 != NULL) {
                D_8005AEB8[x_d70d9bc9].x_3c30b5f3(x_50f1dbff, D_8005AEB8[x_d70d9bc9].data,
                                                  D_8005AEB8[x_d70d9bc9].x_3b9aa142);
            }
            D_8005AEB8[x_d70d9bc9].data = x_50f1dbff;
        }
    } while (x_d70d9bc9 >= 0);

    x_cf9b7451->end = end;
    x_04e9945f = x_b30d1d21(x_cf9b7451);
}

void x_aa5915df(x_704d55d4 *list, s32 end) {
    list->end = end;
    list->flags = 1;
    list->next = NULL;
    list->previous = NULL;
    list->x_a9d4034d = x_2bc76549;
    x_28d4de16(list, &x_cf9b7451);
}

s32 x_28fecd4a(void) {
    x_704d55d4 *ptr;
    s32 ret = TRUE;

    ptr = x_3c86e126;
    while (ptr != NULL) {
        if (ptr->x_a9d4034d == x_2bc76549) {
            ptr = ptr->next;
        } else {
            ret = FALSE;
            break;
        }
    }

    return ret;
}

s32 x_b30d1d21(x_704d55d4 *x_6c87f683) {
    s32 x_cab1ae75 = 0;

    while (x_6c87f683 != NULL) {
        x_cab1ae75 += x_6c87f683->end - (u32) x_6c87f683;
        x_6c87f683 = x_6c87f683->next;
        x_cab1ae75 -= sizeof(x_704d55d4);
    }

    return x_cab1ae75;
}

void x_28d4de16(x_704d55d4 *x_6c87f683, x_704d55d4 **x_bf0b39b3) {
    x_6c87f683->next = *x_bf0b39b3;
    if (x_6c87f683->next != NULL) {
        x_6c87f683->next->previous = x_6c87f683;
    }
    *x_bf0b39b3 = x_6c87f683;
    x_6c87f683->previous = NULL;
}

void x_090192d9(x_704d55d4 *x_6c87f683) {
    if (x_6c87f683 == x_cf9b7451) {
        x_cf9b7451 = x_6c87f683->next;
    }
    if (x_6c87f683 == x_3c86e126) {
        x_3c86e126 = x_6c87f683->next;
    }

    if (x_6c87f683->next != NULL && x_6c87f683->previous != NULL) {
        x_6c87f683->previous->next = x_6c87f683->next;
        x_6c87f683->next->previous = x_6c87f683->previous;
    } else if (x_6c87f683->next != NULL) {
        x_6c87f683->next->previous = NULL;
    } else {
        x_6c87f683->previous->next = NULL;
    }

    x_6c87f683->next = NULL;
    x_6c87f683->previous = NULL;
}

void x_2c0505ad(void) {
    x_704d55d4 *current;
    x_704d55d4 *ptr;

    x_04e9945f = x_b30d1d21(x_cf9b7451);
    D_80049288 = FALSE;

    current = x_cf9b7451;
    while (current != NULL) {
        ptr = x_cf9b7451;
        while (ptr != NULL) {
            if (current == (struct x_704d55d4 *) ptr->end) {
                // merge two chunks
                ptr->end = current->end;
                x_090192d9(current);
                current = NULL;
                break;
            }
            ptr = ptr->next;
        }

        if (current != NULL) {
            current = current->next;
        } else {
            current = x_cf9b7451;
        }
    }
}

#ifdef NON_MATCHING
void *x_5319ff51(u32 size) {
    x_704d55d4 *current;
    u32 x_bc354e67;
    u32 x_e26ee934;
    x_704d55d4 *x_b264b422;
    x_704d55d4 *s1;

x_3ace60b0:
    x_21ce7377 += size;
    x_04e9945f = x_b30d1d21(x_cf9b7451);

    if (size == 0) {
        return NULL;
    }

    size = (size + 0xF) & ~0xF;

    x_b264b422 = NULL;
    x_e26ee934 = 0x7FFFFFFF;

    for (current = x_cf9b7451; current != NULL; current = current->next) {
        x_bc354e67 = current->end - ((u32) current) - sizeof(x_704d55d4);

        if (x_bc354e67 == size) {
            x_e26ee934 = x_bc354e67;
            x_b264b422 = current;
            break;
        }

        if (x_bc354e67 < x_e26ee934 && size + sizeof(x_704d55d4) < x_bc354e67) {
            x_e26ee934 = x_bc354e67;
            x_b264b422 = current;
        }
    }

    if (x_b264b422 != NULL) {
        s1 = x_b264b422;
        if (size < x_e26ee934) {
            u32 end = x_b264b422->end;
            x_b264b422->end = x_b264b422->end - size - sizeof(x_704d55d4);
            s1 = x_b264b422->end;
            s1->flags = 0;
            s1->x_a9d4034d = x_2bc76549;
            s1->end = end;
        } else {
            x_b264b422->flags &= ~1;
            x_b264b422->x_a9d4034d = x_2bc76549;
            x_090192d9(x_b264b422);
        }
    } else {
        if (x_cf9b7451 == NULL || !D_80049288) {
            return NULL;
        }

        x_2c0505ad();
        x_21ce7377 -= size;
        goto x_3ace60b0;
    }

    x_28d4de16(s1, &x_3c86e126);
    return (u32) s1 + sizeof(x_704d55d4);
}
#else
void *x_5319ff51(u32 x_cc1d0de5);
#pragma GLOBAL_ASM("asm/nonmatchings/a8ef58b5/x_5319ff51.s")
#endif

void x_86715543(void *ptr) {
    x_704d55d4 *x_6c87f683;

    x_6c87f683 = (x_704d55d4 *) ((u32) ptr - sizeof(x_704d55d4));
    x_21ce7377 = x_21ce7377 - x_6c87f683->end + (u32) x_6c87f683 + sizeof(x_704d55d4);
    if (x_6c87f683->x_a9d4034d == x_2bc76549) {
        x_6c87f683->x_a9d4034d = 0;
    }

    x_090192d9(x_6c87f683);
    x_6c87f683->flags |= 1;
    x_28d4de16(x_6c87f683, &x_cf9b7451);
    D_80049288 = TRUE;
}

void x_ad92c136(u8 *x_cc1d0de5, u8 x_84ff873b, u32 x_2092f891) {
    s32 i;

    for (i = 0; i < x_2092f891; i++) {
        x_cc1d0de5[i] = x_84ff873b;
    }
}

void x_0be47d8a(u32 *dest, u32 *src, u32 size) {
    s32 i;
    u32 *temp = src;

    if (dest < src) {
        memcpy(dest, src, size);
    } else {
        for (i = size / 4 - 1; i >= 0; i--) {
            dest[i] = temp[i];
        }
    }
}

s32 x_0c316ed1(s32 size) {
    s32 i;

    if (D_8005BEB8 < x_af32df05) {
        D_8005AEB8[D_8005BEB8].data = x_5319ff51(size);
        D_8005AEB8[D_8005BEB8].x_af0aa1f8 = 0;
        D_8005AEB8[D_8005BEB8].x_3c30b5f3 = 0;
        return D_8005BEB8++;
    }

    for (i = 0; i < x_af32df05; i++) {
        if (D_8005AEB8[i].x_af0aa1f8 & 1) {
            D_8005AEB8[i].data = x_5319ff51(size);
            D_8005AEB8[i].x_af0aa1f8 = 0;
            D_8005AEB8[i].x_3c30b5f3 = 0;
            return i;
        }
    }

    return -1;
}

void x_d5aca165(s32 x_ef190cf1) {
    x_86715543(D_8005AEB8[x_ef190cf1].data);
    D_8005AEB8[x_ef190cf1].x_af0aa1f8 = 1;
    D_8005AEB8[x_ef190cf1].x_3c30b5f3 = NULL;
}

void x_07194b79(s32 romAddr, void *x_dda6dc06, s32 size) {
    osWritebackDCacheAll();
    while (osRecvMesg(&x_0c7f0f6c, NULL, OS_MESG_NOBLOCK) != -1) {}
    osPiStartDma(&D_8005AE90, 0, OS_READ, romAddr, x_dda6dc06, size, &x_0c7f0f6c);
    osRecvMesg(&x_0c7f0f6c, NULL, OS_MESG_BLOCK);
    osInvalDCache(0, 0x3FFFFF);
}

void x_2add4a13(s32 romAddr, void *x_dda6dc06, s32 size) {
    osWritebackDCacheAll();
    osPiStartDma(&D_8005AE90, 0, OS_READ, romAddr, x_dda6dc06, size, &x_0c7f0f6c);
    osInvalDCache(0, 0x3FFFFF);
}

void x_1bf854b7(s32 x_ef190cf1, void (*x_3c30b5f3)(void *x_cc1d0de5, s32 x_84ff873b, s32 x_2092f891), s32 x_3b9aa142) {
    D_8005AEB8[x_ef190cf1].x_3c30b5f3 = x_3c30b5f3;
    D_8005AEB8[x_ef190cf1].x_3b9aa142 = x_3b9aa142;
}

void *x_56c3086a(s32 size, const char *file, s32 line) {
    return x_5319ff51(size);
}
