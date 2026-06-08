#include "common.h"
#include "ld_addrs.h"
#include "string.h"
#include "PR/gt.h"

enum x_94e9bb96 {
    x_abbfa82d = 0,
    x_9a28a0e8 = 1,
    x_a2efc39c = 2,
    x_4f58385b = 3,
    x_e78214f3 = 4,
    x_af80c4c4 = 5,
    x_62b457ad = 6,
    x_a333ecc9 = 7,
    x_fbd3116b = 8,
    x_33701dde = 9,
    x_343dc94b = 10,
    x_8b91feb4 = 11,
    x_079fabb5 = 12,
    x_6fc08d0e = 13,
    x_6eac6883 = 14,
    x_d15f1ef4 = 15,
    x_08983e66 = 16,
    x_b4b41045 = 17,
    x_e9a94289 = 18,
    x_0abe41d8 = 19,
    x_f24d8020 = 20,
    x_f83b5104 = 21,
    x_6bfea1ff = 22
};

typedef struct x_f56bf0e5 {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 x_a0917d8d;
    /* 0x1C */ s32 x_d88e3a03;
} x_f56bf0e5; // size >= 0x20

typedef struct x_e28b4412 {
    /* 0x00 */ char name[20];
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 type;
    /* 0x1C */ s32 size;
    /* 0x20 */ s32 x_f1860703;
} x_e28b4412; // size = 0x24

typedef struct x_909544ae {
    /* 0x00 */ u32 x_c6a89d30;
    /* 0x04 */ u32 x_1256da71; // unknown, same as numFolders
    /* 0x08 */ x_f56bf0e5 x_63b85330[1];
} x_909544ae;

typedef struct x_8e2f21bf {
    /* 0x00 */ s32 x_af0aa1f8;
    /* 0x04 */ s32 x_1256da71[1];
} x_8e2f21bf;

s32 x_646456b5 = 0;

x_80d298c9 x_b717ed65[256];
s32 D_8013C200;
x_909544ae *x_897e2c89;
s32 D_8013C208;
u8 *x_77d8d882;
x_f56bf0e5 *x_51ce9d2c;
s32 D_8013C214;
s32 D_8013C218;
u32 x_456f0177;
u32 x_aaf3898b;
s16 x_2615d8ad;
s16 D_8013C226;
void (*D_8013C228)(x_80d298c9 *);

void x_e6e6fcf8(ALBankFile *x_cc1d0de5, u8 *x_84ff873b, u32 x_2092f891);
void x_0be47d8a(u32 *dest, u32 *src, u32 size);
void x_36b7cd1c(x_13162abc *, s32);
void x_f8c73c4c(x_82e80914 *, x_13162abc *, char *, s32, u16);
void x_69c2895e(x_80d298c9 *);
void x_ef5a0926(s32);
void x_f4b1f18f(void);
void x_07194b79(s32 romAddr, void *x_dda6dc06, s32 size);
void x_1a472aba(Model *, x_13162abc *, char *, s32, x_d8e0705d *, u16);
void x_aced8439(Model *);
void x_0aa2034a(Model *);

void x_ac647f84(x_80d298c9 *);
void x_cdb51e25(x_80d298c9 *);
void x_b36d80d1(x_13162abc *);

void x_034d49df(x_80d298c9 *);
void x_c9891aed(x_80d298c9 *);
void x_d1e0523b(x_80d298c9 *);
void x_295cf668(x_80d298c9 *);
void x_f7130eee(x_80d298c9 *);
void x_bb4bf8e9(x_80d298c9 *);
void x_de8b0a30(x_80d298c9 *);
void x_fe33de23(x_80d298c9 *);
void x_f4f0da78(x_80d298c9 *);
void x_89bda4c8(x_80d298c9 *);
void x_aad81579(x_80d298c9 *);
void x_4f787172(x_80d298c9 *);
void x_07e71e6a(x_80d298c9 *);
void x_c4cf10bc(x_80d298c9 *);
void x_1e0203e3(x_80d298c9 *);
void x_d3551c38(x_80d298c9 *);
void x_553db989(x_80d298c9 *);
void x_937aa64a(x_80d298c9 *);
void x_b7445979(x_80d298c9 *);
void x_935de8c5(x_80d298c9 *);
void x_e24bd86f(x_80d298c9 *);
void x_8b9b3927(x_80d298c9 *);
void x_82f0a39b(x_80d298c9 *);
void x_23346b22(x_80d298c9 *);
void x_691ab4b1(x_80d298c9 *);
void x_4efddabd(x_80d298c9 *);
void x_204b7d4a(x_80d298c9 *);
void x_4aa7c56b(x_80d298c9 *);

void x_33b084c7(void) {
    u32 i;

    for (i = 0; i < x_646456b5; i++) {}
}

void x_8c518b47(char *x_0618013f, char *src) {
    u32 x_648569c9 = strlen(x_0618013f);
    u32 x_842e9df0 = strlen(src);
    s32 i;

    for (i = 0; i < x_842e9df0; i++) {
        x_0618013f[x_648569c9 + i] = *src++;
    }

    x_0618013f[x_648569c9 + x_842e9df0] = 0;
}

void x_dab0846a(char *x_cc1d0de5, char *x_84ff873b) {
    u32 size = strlen(x_84ff873b);
    s32 i;

    for (i = 0; i < size; i++) {
        *x_cc1d0de5++ = *x_84ff873b++;
    }

    *x_cc1d0de5 = 0;
}

s32 x_6b61a084(char *x_cc1d0de5, char *x_84ff873b) {
    u32 x_4346f5cb;
    u32 x_1ca25edc;
    u32 i;

    x_4346f5cb = strlen(x_cc1d0de5);
    x_1ca25edc = strlen(x_84ff873b);
    if (x_4346f5cb != x_1ca25edc) {
        return 1;
    }

    for (i = 0; i < x_4346f5cb; i++) {
        if (*x_cc1d0de5++ != *x_84ff873b++) {
            return 1;
        }
    }

    return 0;
}

void x_4856ad1b(char *str) {
    u32 size = strlen(str);
    u32 i;

    for (i = 0; i < size; i++) {
        str[i] = (str[i] >= 'a') ? str[i] -= 'a' - 'A' : str[i];
    }
}

u32 x_e720f37d(char *name, u32 context) {
    u32 i;

    x_4856ad1b(name);
    for (i = 0; i < x_646456b5; i++) {
        if (x_6b61a084(name, x_b717ed65[i].name) == 0 && context == x_b717ed65[i].context) {
            return i;
        }
    }

    return -1;
}

void x_43d722ac(void) {
    u32 i;

    x_646456b5 = 0;
    for (i = 0; i < 256; i++) {
        x_b717ed65[i].x_d5b87ce9 = x_b717ed65[i].x_89bf4f22 = -1;
        x_b717ed65[i].flags = 1;
        x_b717ed65[i].name[0] = '\0';
    }
}

void x_ab4a6fed(s32 x_cc1d0de5, s32 size) {
    D_8013C200 = x_cc1d0de5;
    x_897e2c89 = D_8013C200;
    D_8013C208 = D_8013C200 + 0x2800;
    D_8013C214 = D_8013C208 - x_cc1d0de5;
    D_8013C218 = size - D_8013C214;
}

void x_3301f34a(char *name) {
    s32 i;
    char x_7244b466[20];
    x_e28b4412 *x_7e19d904;
    x_e28b4412 *file;

    x_7e19d904 = x_51ce9d2c->offset + (u8 *) x_897e2c89;
    x_dab0846a(x_7244b466, name);
    x_8c518b47(x_7244b466, ".WAD");

    for (i = 0, file = x_7e19d904; i < x_456f0177; i++, file++) {
        if (x_6b61a084(file->name, x_7244b466) == 0) {
            x_77d8d882 += file->offset;
            return;
        }
        if (file && file) {
            // FAKE MATCH
        }
    }
}

s32 x_66e69c02(char *x_e2308d38) {
    s32 pad;
    u32 i;
    x_f56bf0e5 *x_63b85330;

    x_63b85330 = x_897e2c89->x_63b85330;
    for (i = 0; i < x_aaf3898b; i++) {
        if (x_6b61a084(x_e2308d38, x_63b85330[i].name) == 0) {
            x_51ce9d2c = &x_63b85330[i];
            x_aaf3898b = 1;
            x_456f0177 = x_63b85330[i].x_a0917d8d;
            return TRUE;
        }
    }

    return FALSE;
}

void x_9b2b63e0(char *name) {
    if (name[0] == '\0') {
        // load root wad
        x_77d8d882 = x_76136bc5;
        x_07194b79(x_77d8d882, x_897e2c89, D_8013C214);
        x_51ce9d2c = x_897e2c89->x_63b85330;
        x_aaf3898b = x_897e2c89->x_c6a89d30;
        x_456f0177 = x_51ce9d2c->x_a0917d8d;
    } else if (x_66e69c02(name)) {
        // select folder in current wad file
    } else {
        x_3301f34a(name);
        x_07194b79(x_77d8d882, x_897e2c89, D_8013C214);
        x_51ce9d2c = x_897e2c89->x_63b85330;
        x_aaf3898b = x_897e2c89->x_c6a89d30;
        x_456f0177 = x_51ce9d2c[0].x_a0917d8d;
    }
}

void x_42440629(char *x_a0af9f86) {
    s32 len;
    char x_3893a365[24];
    u32 i;
    u32 j;

    len = strlen(x_a0af9f86);
    j = 0;
    x_4856ad1b(x_a0af9f86);
    x_3893a365[0] = '\0';

    for (i = 0; i < len; i++) {
        if (x_a0af9f86[i] != '/') {
            x_3893a365[j++] = x_a0af9f86[i];
        } else {
            x_3893a365[j] = '\0';
            j = 0;
            x_9b2b63e0(x_3893a365);
        }
    }

    x_3893a365[j] = '\0';
    x_9b2b63e0(x_3893a365);
}

void x_29f4699a(void) {
    u32 i;

    for (i = 0; i < x_646456b5; i++) {
        if (x_b717ed65[i].x_d5b87ce9 >= 0) {
            x_b717ed65[i].data = D_8005AEB8[x_b717ed65[i].x_d5b87ce9].data;
        }
        if (x_b717ed65[i].x_89bf4f22 >= 0) {
            x_b717ed65[i].x_4962fc73 = D_8005AEB8[x_b717ed65[i].x_89bf4f22].data;
        }
    }
}

void x_0928eec2(char *x_a0af9f86, s32 context) {
    x_f4b1f18f();
    x_42440629(x_a0af9f86);
    x_ef5a0926(context);
    x_ad92c136(x_897e2c89, 0, D_8013C214);
    x_f4b1f18f();
}

void x_ad9889cf(s32 context) {
    u32 i;

    for (i = 0; i < x_646456b5; i++) {
        if (context == x_b717ed65[i].context) {
            x_ac647f84(x_b717ed65 + i);
        }
    }

    x_f4b1f18f();
}

void x_40b36af5(void) {
    u32 i;

    for (i = 0; i < x_646456b5; i++) {
        x_ac647f84(x_b717ed65 + i);
    }

    x_f4b1f18f();
}

void x_e25b23f0(s32 x_cc1d0de5) {
    u32 i;

    for (i = 0; i < x_646456b5; i++) {
        if (x_cc1d0de5 == x_b717ed65[i].type) {
            x_ac647f84(x_b717ed65 + i);
        }
    }

    x_f4b1f18f();
}

void x_ef5a0926(s32 context) {
    s32 pad[2];
    u32 i;
    u32 x_8a28cdcb;
    x_e28b4412 *file;
    s32 v0;

    x_8a28cdcb = x_b30d1d21(x_cf9b7451);
    file = (x_e28b4412 *) ((u8 *) x_897e2c89 + x_51ce9d2c->offset);

    for (i = 0; i < x_456f0177; i++) {
        v0 = x_e720f37d(file[i].name, context);

        if (v0 >= 0) {
            switch (file[i].type) {
                case x_4f58385b:
                    x_cdb51e25(x_b717ed65 + v0);
                    break;
                case x_fbd3116b:
                    x_034d49df(x_b717ed65 + v0);
                    break;
                case x_a333ecc9:
                    x_c9891aed(x_b717ed65 + v0);
                    break;
                case x_a2efc39c:
                    x_d1e0523b(x_b717ed65 + v0);
                    break;
                case x_8b91feb4:
                    x_295cf668(x_b717ed65 + v0);
                    break;
                case x_33701dde:
                    x_f7130eee(x_b717ed65 + v0);
                    break;
                case x_6eac6883:
                    x_bb4bf8e9(x_b717ed65 + v0);
                    break;
                case x_079fabb5:
                    x_de8b0a30(x_b717ed65 + v0);
                    break;
                case x_d15f1ef4:
                    x_fe33de23(x_b717ed65 + v0);
                    break;
                case x_f24d8020:
                    x_f4f0da78(x_b717ed65 + v0);
                    break;
                case x_f83b5104:
                    x_89bda4c8(x_b717ed65 + v0);
                    break;
                case x_6bfea1ff:
                    x_aad81579(x_b717ed65 + v0);
                    break;
            }
        } else if (file[i].x_f1860703 <= x_8a28cdcb) {
            x_dab0846a(x_b717ed65[x_646456b5].name, file[i].name);
            x_b717ed65[x_646456b5].size = file[i].size;
            x_b717ed65[x_646456b5].context = context;
            x_b717ed65[x_646456b5].type = file[i].type;
            x_b717ed65[x_646456b5].romAddr = x_77d8d882 + file[i].offset;
            x_b717ed65[x_646456b5].x_f33d7764 = file[i].x_f1860703;

            if (file[i].size != file[i].x_f1860703) {
                x_b717ed65[x_646456b5].flags = 2;
                x_646456b5++;
            } else {
                x_b717ed65[x_646456b5].flags = 0;
                x_646456b5++;
            }

            switch (file[i].type) {
                case x_abbfa82d:
                    x_4f787172(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_9a28a0e8:
                    x_07e71e6a(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_a2efc39c:
                    x_c4cf10bc(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_4f58385b:
                    x_1e0203e3(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_a333ecc9:
                    x_d3551c38(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_fbd3116b:
                    x_935de8c5(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_343dc94b:
                    x_e24bd86f(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_33701dde:
                    x_09120adb(x_b717ed65 + x_646456b5 - 1);
                    x_f7130eee(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_8b91feb4:
                    x_09120adb(x_b717ed65 + x_646456b5 - 1);
                    x_295cf668(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_079fabb5:
                    x_23346b22(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_6fc08d0e:
                    x_82f0a39b(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_6eac6883:
                    x_09120adb(x_b717ed65 + x_646456b5 - 1);
                    x_bb4bf8e9(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_d15f1ef4:
                    x_4efddabd(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_08983e66:
                    x_204b7d4a(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_b4b41045:
                    x_691ab4b1(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_e9a94289:
                    x_4aa7c56b(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_0abe41d8:
                    x_8b9b3927(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_f24d8020:
                    x_553db989(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_f83b5104:
                    x_937aa64a(x_b717ed65 + x_646456b5 - 1);
                    break;
                case x_6bfea1ff:
                    x_b7445979(x_b717ed65 + x_646456b5 - 1);
                    break;
                default:
                    x_09120adb(x_b717ed65 + x_646456b5 - 1);
                    break;
            }
        }
    }
}

void x_57054f7e(x_80d298c9 *x_d59386e0, s32 size) {
    s32 index;
    index = x_0c316ed1(size);
    x_d59386e0->x_d5b87ce9 = index;
    x_d59386e0->data = D_8005AEB8[index].data;
}

void x_e45657fa(x_80d298c9 *x_cc1d0de5) {
    x_d5aca165(x_cc1d0de5->x_d5b87ce9);
    x_cc1d0de5->x_d5b87ce9 = -1;
}

void x_dcbf31af(x_80d298c9 *x_cc1d0de5) {
    x_d5aca165(x_cc1d0de5->x_89bf4f22);
    x_cc1d0de5->x_89bf4f22 = -1;
}

void x_ffcc7604(x_80d298c9 *x_cc1d0de5, s32 x_84ff873b) {
    s32 index;
    index = x_0c316ed1(x_84ff873b);
    x_cc1d0de5->x_89bf4f22 = index;
    x_cc1d0de5->x_4962fc73 = D_8005AEB8[index].data;
}

void x_ac647f84(x_80d298c9 *x_d59386e0) {
    x_d59386e0->flags = 1;

    if (x_d59386e0->x_d5b87ce9 >= 0) {
        x_d5aca165(x_d59386e0->x_d5b87ce9);
    }

    if (x_d59386e0->x_89bf4f22 >= 0) {
        x_d5aca165(x_d59386e0->x_89bf4f22);
    }

    x_d59386e0->x_d5b87ce9 = -1;
    x_d59386e0->x_89bf4f22 = -1;
    x_d59386e0->name[0] = '\0';
    x_d59386e0->data = x_d59386e0->x_4962fc73 = NULL;
}

void x_09120adb(x_80d298c9 *x_d59386e0) {
    x_57054f7e(x_d59386e0, x_d59386e0->x_f33d7764);
    if (x_d59386e0->flags & 2) {
        x_69c2895e(x_d59386e0);
    } else {
        x_07194b79(x_d59386e0->romAddr, x_d59386e0->data, x_d59386e0->x_f33d7764);
    }
}

void x_f4b1f18f(void) {
    u32 i, j;
    u32 s3;

    s3 = 0;
    for (i = 0; i < x_646456b5; i++) {
        if (x_b717ed65[i].flags & 1) {
            for (j = i + 1; j < x_646456b5; j++) {
                if (!(x_b717ed65[j].flags & 1)) {
                    break;
                }
            }

            if (j != x_646456b5) {
                x_b717ed65[i].data = x_b717ed65[j].data;
                x_b717ed65[i].x_4962fc73 = x_b717ed65[j].x_4962fc73;
                x_b717ed65[i].size = x_b717ed65[j].size;
                x_b717ed65[i].x_f33d7764 = x_b717ed65[j].x_f33d7764;
                x_b717ed65[i].type = x_b717ed65[j].type;
                x_b717ed65[i].flags = x_b717ed65[j].flags;
                x_b717ed65[i].x_d5b87ce9 = x_b717ed65[j].x_d5b87ce9;
                x_b717ed65[i].x_89bf4f22 = x_b717ed65[j].x_89bf4f22;
                x_b717ed65[i].context = x_b717ed65[j].context;
                x_dab0846a(x_b717ed65[i].name, x_b717ed65[j].name);
                x_b717ed65[j].name[0] = '\0';
                x_b717ed65[j].x_89bf4f22 = -1;
                x_b717ed65[j].x_d5b87ce9 = -1;
                x_b717ed65[j].flags = 1;
                s3++;
            } else {
                x_b717ed65[i].name[0] = '\0';
                x_b717ed65[i].x_89bf4f22 = -1;
                x_b717ed65[i].x_d5b87ce9 = -1;
                x_b717ed65[i].flags = 1;
                x_646456b5 = s3;
                return;
            }
        } else {
            s3++;
        }
    }

    x_646456b5 = s3;
    for (i = 0; i < x_646456b5; i++) {}
}

void x_4f787172(x_80d298c9 *x_d59386e0) {
    x_8e2f21bf *x_eecaffc6;
    s32 a3;
    u32 i;
    s32 *v1;
    x_a05f18ad **v0;
    u32 a0;

    x_09120adb(x_d59386e0);
    x_eecaffc6 = (x_a05f18ad **) x_d59386e0->data;
    a3 = x_eecaffc6->x_af0aa1f8;

    a0 = (u32) ((u32) x_eecaffc6 + 4 + 4 * a3);
    v1 = x_eecaffc6->x_1256da71;

    for (i = 0; i < a3; i++) {
        v0 = x_eecaffc6;
        v0[i] = (x_a05f18ad *) (a0 + v1[i]);
    }

    x_d59386e0->x_4962fc73 = a3;
}

void x_07e71e6a(x_80d298c9 *x_d59386e0) {
    x_09120adb(x_d59386e0);
}

void x_d1e0523b(x_80d298c9 *x_d59386e0) {
    x_8ab35fe5 *header;
    s32 i;
    x_7cc7ad58 *entry;
    x_3b6b80ec *textures[4];

    header = x_d59386e0->data;
    entry = header->x_a34b89cc;
    for (i = 0; i < 4 && (header->x_6fb24ac9[i][0]) != '\0'; i++) {
        textures[i] = x_b717ed65[x_e720f37d(header->x_6fb24ac9[i], x_d59386e0->context)].data;
    }

    for (i = 0; i < header->x_5b30c492; i++, entry++) {
        entry->texture = textures[entry->x_51d6cf57];
    }
}

void x_f68ebff4(void *x_cc1d0de5, void *x_84ff873b, s32 x_2092f891) {
    s32 x_02efc187;
    s32 i;
    x_7cc7ad58 *a2;
    x_8ab35fe5 *v2;

    x_02efc187 = ((u32) x_cc1d0de5 - (u32) x_84ff873b);

    v2 = x_cc1d0de5;
    v2->x_a34b89cc = (x_7cc7ad58 *) ((u32) v2->x_a34b89cc + x_02efc187);

    for (a2 = v2->x_a34b89cc, i = 0; i < v2->x_5b30c492; i++, a2++) {
        a2->parts = (x_425d6ed3 *) ((u32) a2->parts + x_02efc187);
    }
}

void x_c4cf10bc(x_80d298c9 *x_d59386e0) {
    x_8ab35fe5 *header;
    s32 i;
    x_7cc7ad58 *entry;
    u8 *x_925c481a;
    u16 *palette;
    x_3b6b80ec *textures[4];
    x_3b6b80ec **x_23b71842;
    s32 unused[2];

    x_09120adb(x_d59386e0);
    x_23b71842 = textures; // required to match
    header = x_d59386e0->data;
    entry = header->x_a34b89cc = (x_7cc7ad58 *) ((u32) header->x_a34b89cc + (u32) header);
    if ((x_d59386e0->data && x_d59386e0->data) != 0) {} // required to match
    for (i = 0; i < 4 && (header->x_6fb24ac9[i][0]) != '\0'; i++) {
        textures[i] = x_b717ed65[x_e720f37d(header->x_6fb24ac9[i], x_d59386e0->context)].data;

        palette = (u16 *) &textures[i]->data[x_23b71842[i]->height * x_23b71842[i]->width];
        x_925c481a = textures[i]->data;
        palette[x_925c481a[0]] = 0;
    }

    for (i = 0; i < header->x_5b30c492; i++, entry++) {
        entry->parts = (x_425d6ed3 *) ((s32) entry->parts + (s32) header);
        entry->texture = x_23b71842[entry->x_51d6cf57];
    }

    x_1bf854b7(x_d59386e0->x_d5b87ce9, x_f68ebff4, 0);
}

void x_1e0203e3(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    x_82e80914 *x_49781937;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    x_49781937 = x_56c3086a(sizeof(x_82e80914), "wad.c", 742);
    x_f8c73c4c(x_49781937, x_3bfb7219, x_d59386e0->name, 0, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = x_49781937;
}

void x_d3551c38(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    x_82e80914 *x_49781937;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    x_49781937 = x_56c3086a(sizeof(x_82e80914), "wad.c", 777);
    x_f8c73c4c(x_49781937, x_3bfb7219, x_d59386e0->name, 1, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = x_49781937;
}

void x_553db989(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    model = x_56c3086a(sizeof(Model), "wad.c", 813);
    x_3bfb7219->x_14bc93c1 = 1;
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_eec8b086, x_d59386e0->context);
    model->x_8ac8f967 = 0x10;
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void x_937aa64a(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    model = x_56c3086a(sizeof(Model), "wad.c", 854);
    x_3bfb7219->x_14bc93c1 = 1;
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_bb5426b0, x_d59386e0->context);
    model->x_8ac8f967 = 2;
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void x_b7445979(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    model = x_56c3086a(sizeof(Model), "wad.c", 893);
    x_3bfb7219->x_14bc93c1 = 1;
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 1;
    x_aced8439(model);
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void x_935de8c5(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    model = x_56c3086a(sizeof(Model), "wad.c", 934);
    x_3bfb7219->x_14bc93c1 = 1;
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fd763f4f, x_d59386e0->context);
    model->x_8ac8f967 = 8;
    x_0aa2034a(model);
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void x_cdb51e25(x_80d298c9 *x_d59386e0) {
    x_82e80914 *s0;
    x_13162abc *x_3bfb7219;

    s0 = x_56c3086a(sizeof(x_82e80914), "wad.c", 950);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_f8c73c4c(s0, x_3bfb7219, x_d59386e0->name, 0, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = s0;
}

void x_034d49df(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = x_56c3086a(sizeof(Model), "wad.c", 963);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fd763f4f, x_d59386e0->context);
    x_0aa2034a(model);
    model->x_8ac8f967 = 8;
    x_d59386e0->x_4962fc73 = model;
}

void x_f4f0da78(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = x_56c3086a(sizeof(Model), "wad.c", 977);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_eec8b086, x_d59386e0->context);
    model->x_8ac8f967 = 0x10;
    x_d59386e0->x_4962fc73 = model;
}

void x_89bda4c8(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = x_56c3086a(sizeof(Model), "wad.c", 991);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_bb5426b0, x_d59386e0->context);
    model->x_8ac8f967 = 2;
    x_d59386e0->x_4962fc73 = model;
}

void x_aad81579(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = x_56c3086a(sizeof(Model), "wad.c", 1005);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 1;
    x_aced8439(model);
    x_d59386e0->x_4962fc73 = model;
}

void x_c9891aed(x_80d298c9 *x_d59386e0) {
    x_82e80914 *s0;
    x_13162abc *x_3bfb7219;

    s0 = x_56c3086a(sizeof(x_82e80914), "wad.c", 1019);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_f8c73c4c(s0, x_3bfb7219, x_d59386e0->name, 1, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = s0;
}

void x_e24bd86f(x_80d298c9 *x_d59386e0) {
    x_09120adb(x_d59386e0);
    if (x_d59386e0->data != NULL) {
        x_f133710d = x_d59386e0->x_f33d7764;
        x_0be47d8a(x_f90c9091, x_d59386e0->data, x_f133710d);
        x_ac647f84(x_d59386e0);
    }
}

void x_295cf668(x_80d298c9 *x_d59386e0) {
    if (x_d59386e0->data != 0) {
        alBnkfNew(x_f90c9091, x_d59386e0->data);
    }
}

void x_f7130eee(x_80d298c9 *x_d59386e0) {
    if (x_d59386e0->data != NULL) {
        x_032a146b = x_d59386e0->x_f33d7764;
        x_adb8fe7f = x_d59386e0->data;
        alSeqNew(x_d896e1bb, x_adb8fe7f, x_032a146b);
        alSeqNewMarker(x_d896e1bb, &x_9ae0d7c5, 0);
        alSeqNewMarker(x_d896e1bb, &x_d452fc32, 0xFFFFFFFF);
        alSeqpLoop(x_85a4d96f, &x_9ae0d7c5, &x_d452fc32, -1);

        alSeqpSetBank(x_85a4d96f, x_f90c9091->bankArray[0]);
        alSeqpSetSeq(x_85a4d96f, x_d896e1bb);
        alSeqpSetVol(x_85a4d96f, x_66ddef46);
        x_24b82fef = TRUE;
        x_b5cc849a = x_66ddef46;
    }
}

void x_8b9b3927(x_80d298c9 *x_d59386e0) {
    x_09120adb(x_d59386e0);
    if (x_d59386e0->data != NULL) {
        x_0be47d8a(x_f12166b8[2], x_d59386e0->data, x_d59386e0->x_f33d7764);
        x_df816944[2] = 1;
        x_ac647f84(x_d59386e0);
        x_e6e6fcf8(x_f12166b8[2], D_7DE880, 2);
    }
}

void x_82f0a39b(x_80d298c9 *x_d59386e0) {
    s32 x_3a540ba4;

    x_3a540ba4 = x_d59386e0->context;
    if (x_3a540ba4 >= 2U) {
        x_3a540ba4 = 2;
    }

    x_09120adb(x_d59386e0);
    if (x_d59386e0->data != NULL) {
        x_0be47d8a(x_f12166b8[x_3a540ba4], x_d59386e0->data, x_d59386e0->x_f33d7764);
        x_df816944[x_3a540ba4] = TRUE;
        x_ac647f84(x_d59386e0);
    }
}

void x_bb4bf8e9(x_80d298c9 *x_d59386e0) {
    s32 x_3a540ba4;

    x_3a540ba4 = x_d59386e0->context;

    if (x_d59386e0->data != NULL) {
        if (x_3a540ba4 >= 2U) {
            x_3a540ba4 = 2;
        }
        x_e6e6fcf8(x_f12166b8[x_3a540ba4], x_d59386e0->data, x_3a540ba4);
    }
}

void x_f7724912(x_320b5d80 *x_cc1d0de5, Gfx **x_84ff873b) {
    Gfx *gfx;
    if (x_84ff873b == NULL) {
        gtStateSetOthermode(&x_cc1d0de5->info->header.otherMode, GT_RENDERMODE, G_RM_XLU_SURF | G_RM_XLU_SURF2);
    } else {
        gfx = *x_84ff873b;
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        *x_84ff873b = gfx;
    }
}

void x_23346b22(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;
    char *name;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    model = x_56c3086a(sizeof(Model), "wad.c", 1226);
    x_3bfb7219->x_14bc93c1 = 1;
    name = x_d59386e0->name;
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    x_3bfb7219->x_14bc93c1 = 0;
    x_d59386e0->x_4962fc73 = model;
    strlen(name);
}

void x_691ab4b1(x_80d298c9 *x_d59386e0) {
    x_09120adb(x_d59386e0);
}

void x_de8b0a30(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = x_56c3086a(sizeof(Model), "wad.c", 1257);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    x_d59386e0->x_4962fc73 = model;
}

void x_4efddabd(x_80d298c9 *x_d59386e0) {
    x_291fbc91 *x_0fc71c4e;
    Model *model;
    s32 x_1e61bca4;
    s32 x_6dcce206;
    x_13162abc *x_3bfb7219;

    x_09120adb(x_d59386e0);
    x_0fc71c4e = x_d59386e0->data;
    x_1e61bca4 = x_d59386e0->x_d5b87ce9;
    x_6dcce206 = x_0fc71c4e->x_6dcce206;
    x_d59386e0->x_89bf4f22 = x_d59386e0->x_d5b87ce9;
    x_d59386e0->size = x_6dcce206 * sizeof(x_c3c252eb) + x_6dcce206 * sizeof(x_36123519) + sizeof(x_13162abc);

    x_57054f7e(x_d59386e0, x_d59386e0->size);
    x_3bfb7219 = (x_13162abc *) (x_d59386e0->data);
    x_3bfb7219->x_6dcce206 = x_6dcce206;
    x_36b7cd1c(x_3bfb7219, x_1e61bca4);

    model = x_56c3086a(sizeof(Model), "wad.c", 1297);
    x_3bfb7219->x_14bc93c1 = 1;
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 4;
    x_aced8439(model);
    x_d59386e0->x_4962fc73 = model;
    x_3bfb7219->x_14bc93c1 = 0;
}

void x_fe33de23(x_80d298c9 *x_d59386e0) {
    Model *model;
    x_13162abc *x_3bfb7219;

    model = x_56c3086a(sizeof(Model), "wad.c", 1314);
    x_3bfb7219 = x_d59386e0->data;

    x_b36d80d1(x_3bfb7219);
    x_1a472aba(model, x_3bfb7219, x_d59386e0->name, FALSE, &x_fc23f083, x_d59386e0->context);
    model->x_8ac8f967 = 4;
    x_aced8439(model);
    x_d59386e0->x_4962fc73 = model;
}

void x_204b7d4a(x_80d298c9 *x_d59386e0) {
    if (D_8013C228 != NULL) {
        D_8013C228(x_d59386e0);
    } else {
        x_09120adb(x_d59386e0);
    }
}

void x_4aa7c56b(x_80d298c9 *x_d59386e0) {
    if (x_77831b2c[x_d59386e0->context].x_6128220f) {
        x_09120adb(x_d59386e0);
    }
}
