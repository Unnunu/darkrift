#include "common.h"
#include "task.h"

#define x_5ef2b67b 0x80

typedef struct x_2f176497 {
    /* 0x00 */ s32 frequency;
    /* 0x04 */ u32 x_ff7ca549;
    /* 0x08 */ s32 x_af00367e;
} x_2f176497; // size >= 0xC

typedef struct x_64d3e7c0 {
    /* 0x00 */ u8 *x_af0aa1f8;
    /* 0x04 */ s16 x_1256da71;
    /* 0x04 */ char x_8b47d6ce[0x60 - 0x6];
    /* 0x60 */ s16 x_b97435d0;
    /* 0x64 */ struct x_64d3e7c0 *x_a7753abb;
    /* 0x68 */ s32 x_c42e3970[6];
} x_64d3e7c0; // size = 0x80

typedef struct x_64e0fd68 {
    /* 0x00 */ struct x_64e0fd68 *next;
    /* 0x04 */ struct x_64e0fd68 *prev;
    /* 0x08 */ u32 x_af8b6f61;
    /* 0x0C */ u32 x_b8173ab8;
    /* 0x10 */ u8 *x_2b18f4e7;
} x_64e0fd68; // size = 0x14

typedef struct x_3eed2154 {
    /* 0x00 */ u8 x_af0aa1f8;
    /* 0x00 */ struct x_64e0fd68 *head;
    /* 0x00 */ struct x_64e0fd68 *tail;
} x_3eed2154; // size = 0xC

typedef struct x_5ecda142 {
    /* 0x00 */ Acmd *x_8d54ede8[2];
    /* 0x08 */ x_64d3e7c0 *x_415ed9d6[3];
} x_5ecda142;

// .bss

x_2f176497 x_3cc9b125;
ALSeqPlayer D_80081680;
ALSeq D_80081708;
ALSndPlayer x_ef25bafe[3];
ALHeap x_e1d5ba1b;
x_5ecda142 D_80081840;
char D_80081858[0x220]; // unused
ALGlobals D_80081A78;
u8 x_8671913b[0x22A00];
ALBankFile *x_f90c9091;
s32 x_f133710d;
s32 D_800A44D0; // unused
u8 *x_adb8fe7f;
s32 x_032a146b;
s32 D_800A44DC; // unused
ALSeqMarker x_9ae0d7c5;
ALSeqMarker x_d452fc32;
s32 x_b5cc849a;
ALSndpConfig x_00cc1736;
s32 D_800A4514;
s32 D_800A4518;
s32 D_800A451C; // unused
s32 x_aec099eb;
u8 D_800A4524[2];
x_3eed2154 x_1f2abefa;
x_64e0fd68 D_800A4538[8];
u32 D_800A45D8;
s32 x_9f4f5858;
s32 D_800A45E0;
u32 D_800A45E4;
u32 D_800A45E8;
s32 D_800A45EC;
s32 x_322bfd84;
s32 D_800A45F4;
s32 x_1287fac6;
s32 x_5582bbef[3];
u8 D_800A460C;
OSIoMesg x_b18883c4[32];
OSMesgQueue D_800A4890;
OSMesg D_800A48A8[32];

// .data

u8 x_24b82fef = FALSE;
u8 x_4553f199 = FALSE;
u8 x_a7d9a1e8 = 0;
u8 D_8004A42C = FALSE;
s32 D_8004A430 = 0; // unused
x_64d3e7c0 *D_8004A434 = NULL;
x_2f176497 *x_c46f8893 = &x_3cc9b125;
ALSeqPlayer *x_85a4d96f = &D_80081680;
ALSeq *x_d896e1bb = &D_80081708;
ALSndPlayer *x_e2b79a2c = &x_ef25bafe[0];
s32 x_66ddef46 = 0x7FFF;
ALSndId *x_7188dab8[3] = { NULL, NULL, NULL };
ALBankFile *x_f12166b8[3] = { NULL, NULL, NULL };
s32 D_8004A464[3] = { 0, 0, 0 }; // unused
u8 x_df816944[3] = { FALSE, FALSE, FALSE };
s8 x_af0cb8e3[3] = { -1, -1, -1 };
s32 x_15814eea = 0x7FFF;
s32 D_8004A47C = 0; // unused
OSTask x_3ab68193 = { { M_AUDTASK, 0, NULL, 0, NULL, SP_UCODE_SIZE, NULL, SP_UCODE_DATA_SIZE, NULL, SP_DRAM_STACK_SIZE8,
                        NULL, 0, NULL, 0, NULL, 0 } };

void x_3e63f835(ALSynConfig *);
ALDMAproc x_5feb315f(x_3eed2154 **state);
void x_914b0697(void);
s32 x_5b101de7(x_64d3e7c0 *x_cc1d0de5);
void x_84221e64(s32 x_cc1d0de5, u8 x_84ff873b);
void x_20c52092(s16 x_cc1d0de5);
void x_62551fe9(s32 x_cc1d0de5, s16 x_84ff873b);

void x_2fc55585(void) {
    x_3ab68193.t.type = M_AUDTASK;
    x_3ab68193.t.ucode_boot = (u64 *) rspbootTextStart;
    x_3ab68193.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    x_3ab68193.t.flags = 0;
    x_3ab68193.t.ucode = (u64 *) aspMainTextStart;
    x_3ab68193.t.ucode_data = (u64 *) aspMainDataStart;
    x_3ab68193.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    x_3ab68193.t.dram_stack = NULL;
    x_3ab68193.t.dram_stack_size = 0;
    x_3ab68193.t.output_buff = NULL;
    x_3ab68193.t.output_buff_size = 0;
    x_3ab68193.t.yield_data_ptr = NULL;
    x_3ab68193.t.yield_data_size = 0;
}

void x_df307371(void) {
    x_f133710d = 0;
    x_adb8fe7f = NULL;
    D_800A4514 = 0;
    D_800A4518 = 0;
    D_800A45D8 = 0;
    x_9f4f5858 = 0;
    D_800A45E0 = 0;
    D_800A460C = 0;
    x_5582bbef[0] = x_5582bbef[1] = x_5582bbef[2] = -1;
    x_24b82fef = FALSE;
    x_4553f199 = FALSE;
    D_8004A42C = FALSE;
    D_800A45F4 = x_1287fac6 = 0;
    x_aec099eb = x_15814eea;
    x_b5cc849a = x_66ddef46;
    D_8004A434 = NULL;
    x_2fc55585();
}

void x_3ef429e1(void) {
    ALSynConfig x_21359cb5;
    ALSeqpConfig x_de9adec2;
    u32 unused[5];

    alHeapInit(&x_e1d5ba1b, x_8671913b, sizeof(x_8671913b));
    x_df307371();

    x_21359cb5.maxVVoices = 42;
    x_21359cb5.maxPVoices = 42;
    x_21359cb5.maxUpdates = 32;
    x_21359cb5.dmaproc = NULL;
    x_21359cb5.fxType = AL_FX_SMALLROOM;
    x_21359cb5.outputRate = 0;
    x_21359cb5.heap = &x_e1d5ba1b;

    x_c46f8893->frequency = 11025;
    x_c46f8893->x_ff7ca549 = 1;
    x_c46f8893->x_af00367e = 0x1100;

    x_3e63f835(&x_21359cb5);

    x_de9adec2.maxVoices = 42;
    x_de9adec2.maxEvents = 48;
    x_de9adec2.maxChannels = 16;
    x_de9adec2.heap = &x_e1d5ba1b;
    x_de9adec2.initOsc = NULL;
    x_de9adec2.updateOsc = NULL;
    x_de9adec2.stopOsc = NULL;
    x_de9adec2.debugFlags = NO_SOUND_ERR_MASK | NOTE_OFF_ERR_MASK | NO_VOICE_ERR_MASK;
    alSeqpNew(x_85a4d96f, &x_de9adec2);

    x_00cc1736.maxSounds = 42;
    x_00cc1736.maxEvents = 60;
    x_00cc1736.heap = &x_e1d5ba1b;
    alSndpNew(&x_ef25bafe[0], &x_00cc1736);
    alSndpNew(&x_ef25bafe[1], &x_00cc1736);
    alSndpNew(&x_ef25bafe[2], &x_00cc1736);
    x_e2b79a2c = x_ef25bafe;
}

void x_0edd29ad(void) {
    u32 i;

    D_800A4538[0].prev = NULL;
    D_800A4538[0].next = NULL;

    for (i = 0; i < ARRAY_COUNT(D_800A4538) - 1; i++) {
        alLink(&D_800A4538[i + 1], &D_800A4538[i]);
        D_800A4538[i].x_2b18f4e7 = alHeapDBAlloc("audio.c", 238, &x_e1d5ba1b, 1, x_5ef2b67b);
    }
    D_800A4538[i].x_2b18f4e7 = alHeapDBAlloc("audio.c", 241, &x_e1d5ba1b, 1, x_5ef2b67b);

    for (i = 0; i < ARRAY_COUNT(D_80081840.x_8d54ede8); i++) {
        D_80081840.x_8d54ede8[i] = alHeapDBAlloc("audio.c", 244, &x_e1d5ba1b, 1, x_c46f8893->x_af00367e * sizeof(Acmd));
    }

    x_322bfd84 = x_c46f8893->x_af00367e;

    for (i = 0; i < ARRAY_COUNT(D_80081840.x_415ed9d6); i++) {
        D_80081840.x_415ed9d6[i] = alHeapDBAlloc("audio.c", 250, &x_e1d5ba1b, 1, sizeof(x_64d3e7c0));
        D_80081840.x_415ed9d6[i]->x_b97435d0 = 2;
        D_80081840.x_415ed9d6[i]->x_a7753abb = D_80081840.x_415ed9d6[i];
        D_80081840.x_415ed9d6[i]->x_af0aa1f8 = alHeapDBAlloc("audio.c", 253, &x_e1d5ba1b, 1, D_800A45EC * 4);
    }

    x_f90c9091 = alHeapDBAlloc("audio.c", 255, &x_e1d5ba1b, 1, 0x800);

    for (i = 0; i < 3; i++) {
        x_7188dab8[i] = alHeapDBAlloc("audio.c", 259, &x_e1d5ba1b, 1, 30 * sizeof(ALSndId));
        x_f12166b8[i] = alHeapDBAlloc("audio.c", 260, &x_e1d5ba1b, 1, 0x1600);
        x_df816944[i] = FALSE;
    }
}

void x_1e7c754d(void) {
    s32 i, j;
    ALSndId *x_cf10d3eb;

    x_df307371();

    for (i = 0; i < 3; i++) {
        if (x_df816944[i]) {
            x_cf10d3eb = x_7188dab8[i];
            x_e2b79a2c = &x_ef25bafe[i];
            for (j = x_af0cb8e3[i]; j > 0; j--) {
                alSndpSetSound(x_e2b79a2c, x_cf10d3eb[j - 1]);
                alSndpDeallocate(x_e2b79a2c, x_cf10d3eb[j - 1]);
            }
            x_df816944[i] = FALSE;
            x_af0cb8e3[i] = 0;
        }
    }

    x_5b101de7(D_80081840.x_415ed9d6[D_800A45D8 % 3]);
    x_914b0697();
    alClose(&D_80081A78);
    x_3ef429e1();
    x_08779f06(FALSE);
    x_08779f06(FALSE);
    x_08779f06(FALSE);
}

void x_3e63f835(ALSynConfig *config) {
    f32 x_cf10d3eb;

    x_1f2abefa.x_af0aa1f8 = FALSE;
    config->dmaproc = x_5feb315f;
    config->outputRate = osAiSetFrequency(x_c46f8893->frequency);

    x_cf10d3eb = (f32) x_c46f8893->x_ff7ca549 * (f32) config->outputRate / 60.0f;
    D_800A45E8 = (s32) x_cf10d3eb;
    if ((f32) D_800A45E8 < (f32) x_cf10d3eb) {
        D_800A45E8++;
    }
    if (D_800A45E8 & 0xF) {
        D_800A45E8 = (D_800A45E8 & ~0xF) + 0x10;
    }

    D_800A45E4 = D_800A45E8 - 0x10;
    D_800A45EC = D_800A45E8 + 0x60;

    alInit(&D_80081A78, config);
    x_0edd29ad();
    osCreateMesgQueue(&D_800A4890, D_800A48A8, ARRAY_COUNT(D_800A48A8));
}

s32 x_5b101de7(x_64d3e7c0 *x_cc1d0de5) {
    s32 x_4346f5cb;
    Acmd *a1;

    if (x_1287fac6 != 0) {
        x_1287fac6 = 0;
    }

    x_4346f5cb = osVirtualToPhysical(x_cc1d0de5->x_af0aa1f8);
    if (D_8004A434 != NULL) {
        osAiSetNextBuffer(D_8004A434->x_af0aa1f8, D_8004A434->x_1256da71 * 4);
    }

    x_cc1d0de5->x_1256da71 = (D_800A45E8 - osAiGetLength() / 4 + 96) & ~0xF;
    if (x_cc1d0de5->x_1256da71 < D_800A45E4) {
        x_cc1d0de5->x_1256da71 = D_800A45E4;
    }

    a1 = alAudioFrame(D_80081840.x_8d54ede8[D_800A45E0], &D_800A45F4, x_4346f5cb, x_cc1d0de5->x_1256da71);
    if (D_800A45F4 == 0) {
        return FALSE;
    }

    x_3ab68193.t.data_ptr = D_80081840.x_8d54ede8[D_800A45E0];
    x_3ab68193.t.data_size = (a1 - D_80081840.x_8d54ede8[D_800A45E0]) * sizeof(Acmd);

    D_8004A434 = D_80081840.x_415ed9d6[D_800A45D8 % 3]->x_a7753abb;
    D_800A45E0 ^= 1;
    return TRUE;
}

s32 x_ad4ca96e(s32 addr, s32 len, void *state) {
    u8 *x_fc517ba8;
    s32 x_081c4eef;
    s32 v1;
    s32 x_24aca5c4;
    x_64e0fd68 *x_7cdc2f34;
    x_64e0fd68 *x_c9614940;

    if (addr < 0) {
        return osVirtualToPhysical(addr);
    }

    x_c9614940 = NULL;
    for (x_7cdc2f34 = x_1f2abefa.head; x_7cdc2f34 != NULL; x_7cdc2f34 = x_7cdc2f34->next) {
        x_24aca5c4 = x_7cdc2f34->x_af8b6f61 + 0x80;
        if (addr < x_7cdc2f34->x_af8b6f61) {
            break;
        }

        x_c9614940 = x_7cdc2f34;
        v1 = addr + len;
        if (v1 <= x_24aca5c4) {
            x_7cdc2f34->x_b8173ab8 = D_800A45D8;
            return osVirtualToPhysical(x_7cdc2f34->x_2b18f4e7 + addr - x_7cdc2f34->x_af8b6f61);
        }
    }

    x_7cdc2f34 = x_1f2abefa.tail;
    x_1f2abefa.tail = x_7cdc2f34->next;

    alUnlink(x_7cdc2f34);
    if (x_c9614940 != NULL) {
        alLink(x_7cdc2f34, x_c9614940);
    } else {
        x_64e0fd68 *v0 = x_1f2abefa.head;
        if (v0 != NULL) {
            x_1f2abefa.head = x_7cdc2f34;
            x_7cdc2f34->next = v0;
            x_7cdc2f34->prev = NULL;
            v0->prev = x_7cdc2f34;
        } else {
            x_1f2abefa.head = x_7cdc2f34;
            x_7cdc2f34->next = NULL;
            x_7cdc2f34->prev = NULL;
        }
    }

    x_fc517ba8 = x_7cdc2f34->x_2b18f4e7;
    x_081c4eef = addr & 1;
    addr -= x_081c4eef;
    x_7cdc2f34->x_af8b6f61 = addr;
    x_7cdc2f34->x_b8173ab8 = D_800A45D8;

    osInvalDCache(x_fc517ba8, len);
    osPiStartDma(&x_b18883c4[x_9f4f5858++], OS_MESG_PRI_NORMAL, OS_READ, addr, x_fc517ba8, 0x80, &D_800A4890);
    return osVirtualToPhysical(x_fc517ba8) + x_081c4eef;
}

ALDMAproc x_5feb315f(x_3eed2154 **state) {
    if (!x_1f2abefa.x_af0aa1f8) {
        x_1f2abefa.head = NULL;
        x_1f2abefa.tail = D_800A4538;
        x_1f2abefa.x_af0aa1f8 = TRUE;
    }
    *state = &x_1f2abefa;
    return x_ad4ca96e;
}

void x_914b0697(void) {
    u32 i;
    OSMesg mesg;
    x_64e0fd68 *x_7cdc2f34;
    x_64e0fd68 *next;

    for (i = 0; i < x_9f4f5858; i++) {
        osRecvMesg(&D_800A4890, &mesg, OS_MESG_NOBLOCK);
    }

    for (x_7cdc2f34 = x_1f2abefa.head; x_7cdc2f34 != NULL; x_7cdc2f34 = next) {
        next = x_7cdc2f34->next;
        if (x_7cdc2f34->x_b8173ab8 + 1 < D_800A45D8) {
            if (x_7cdc2f34 == x_1f2abefa.head) {
                x_1f2abefa.head = x_7cdc2f34->next;
            }
            alUnlink(x_7cdc2f34);
            if (x_1f2abefa.tail != NULL) {
                alLink(x_7cdc2f34, x_1f2abefa.tail);
            } else {
                x_1f2abefa.tail = x_7cdc2f34;
                x_7cdc2f34->next = NULL;
                x_7cdc2f34->prev = NULL;
            }
        }
    }

    x_9f4f5858 = 0;
    D_800A45D8++;
}

void x_06fa0af9(void) {
    if (x_24b82fef + x_4553f199) {
        D_800A45F4 = 0;
        if (x_5b101de7(D_80081840.x_415ed9d6[D_800A45D8 % 3])) {
            x_914b0697();
        }
    }
}

s32 x_1790ee2a(void) {
    s32 i;

    if (!(x_24b82fef + x_4553f199)) {
        return 0;
    }

    if (D_800A45F4 != 0) {
        osSendMesg(&gRspMessageQueue, (OSMesg *) &x_3ab68193, OS_MESG_BLOCK);
    }

    for (i = 0; i < ARRAY_COUNT(x_5582bbef); i++) {
        if (x_5582bbef[i] >= 0) {
            x_7e194d55(i, x_5582bbef[i]);
        }
    }

    return 1;
}

void x_7e194d55(u32 x_3a540ba4, u32 x_1dc13257) {
    ALSndId *x_429c730a;
    s32 pan;

    if (x_3a540ba4 >= 2) {
        x_3a540ba4 = 2;
    }

    if (x_1dc13257 < x_af0cb8e3[x_3a540ba4] && x_df816944[x_3a540ba4]) {
        if (x_3a540ba4 < 2) {
            if (D_800A4524[x_3a540ba4] != x_59ce598c[x_3a540ba4].x_d93bcabf) {
                D_800A4524[x_3a540ba4] = x_59ce598c[x_3a540ba4].x_d93bcabf;

                if (D_800A4524[x_3a540ba4]) {
                    pan = 20;
                } else {
                    pan = 100;
                }

                x_84221e64(x_3a540ba4, pan);
            }
        }

        x_429c730a = x_7188dab8[x_3a540ba4];
        x_e2b79a2c = &x_ef25bafe[x_3a540ba4];
        alSndpSetSound(x_e2b79a2c, x_429c730a[x_1dc13257]);
        if (alSndpGetState(x_e2b79a2c) != AL_STOPPED) {
            alSndpStop(x_e2b79a2c);
            x_5582bbef[x_3a540ba4] = x_1dc13257;
        } else {
            alSndpPlay(x_e2b79a2c);
            x_5582bbef[x_3a540ba4] = -1;
            x_4553f199 = TRUE;
        }
    }
}

void x_f3da6ca2(u32 x_30bbe547, u32 x_1dc13257) {
    ALSndId *x_429c730a;

    if (x_30bbe547 >= 2) {
        x_30bbe547 = 2;
    }

    if (x_1dc13257 < x_af0cb8e3[x_30bbe547] && x_df816944[x_30bbe547]) {
        x_429c730a = x_7188dab8[x_30bbe547];
        x_e2b79a2c = &x_ef25bafe[x_30bbe547];
        alSndpSetSound(x_e2b79a2c, x_429c730a[x_1dc13257]);
        if (alSndpGetState(x_e2b79a2c) != AL_STOPPED) {
            alSndpStop(x_e2b79a2c);
        }
        x_4553f199 = TRUE; // @bug ? what is the point of it?
    }
}

void x_14d52001(s32 x_30bbe547) {
    ALSndId *x_429c730a;
    s32 i;

    if (x_df816944[x_30bbe547]) {
        x_429c730a = x_7188dab8[x_30bbe547];
        x_e2b79a2c = &x_ef25bafe[x_30bbe547];

        for (i = x_af0cb8e3[x_30bbe547]; i > 0; i--) {
            alSndpSetSound(x_e2b79a2c, x_429c730a[i - 1]);
            alSndpStop(x_e2b79a2c);
            x_1287fac6++;
        }
    }
}

void x_512c6246(void) {
    s32 x_30bbe547;

    if (x_4553f199) {
        for (x_30bbe547 = 0; x_30bbe547 < 3; x_30bbe547++) {
            x_14d52001(x_30bbe547);
        }
    }
}

void x_cee53c69(void) {
    if (x_24b82fef) {
        alSeqpStop(x_85a4d96f);
        x_1287fac6++;
    }
}

void x_4a2432d1(Object *obj) {
    if (obj->x_0f4167b4[0]-- < 0) {
        TASK_END(obj->currentTask);
    }
}

void x_f1ca6ba2(Object *obj, s32 x_84ff873b) {
    D_800A460C |= 1;

    if (x_4553f199 && x_aec099eb != 0) {
        x_aec099eb -= 0x7FFF / 27;
        if (x_aec099eb < 0) {
            x_aec099eb = 0;
        }

        if (x_aec099eb == 0) {
            x_512c6246();
        } else {
            x_62551fe9(0, x_aec099eb);
            x_62551fe9(1, x_aec099eb);
            x_62551fe9(2, x_aec099eb);
        }
    } else if (!x_4553f199) {
        x_aec099eb = 0;
    }

    if (x_24b82fef && x_b5cc849a != 0) {
        x_b5cc849a -= 0x7FFF / 27;
        if (x_b5cc849a < 0) {
            x_b5cc849a = 0;
        }

        if (x_b5cc849a == 0) {
            x_cee53c69();
        } else {
            x_20c52092(x_b5cc849a);
        }
    } else if (!x_24b82fef) {
        x_b5cc849a = 0;
    }

    if (x_b5cc849a + x_aec099eb == 0) {
        obj->x_0232396f = x_4a2432d1;
    }
}

void x_292e1d02(Object *obj, s32 unused) {
    s32 x_83bc437e = FALSE;

    if (x_24b82fef && x_24b82fef) { // @bug gMusicIsPlaying checked twice
        alSeqpPlay(x_85a4d96f);
        x_83bc437e = TRUE;
    }

    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] >= 16 || (D_800A460C & 1)) {
        x_83bc437e = TRUE;
    }

    if (x_83bc437e) {
        obj->flags |= x_f51cb721;
        TASK_END(obj->currentTask);
    }
}

void x_84221e64(s32 x_30bbe547, u8 pan) {
    s32 i;
    ALSndId *x_cf10d3eb;

    if (x_a7d9a1e8 != 0 || D_8004A42C) {
        return;
    }

    if (x_30bbe547 > 2) {
        x_30bbe547 = 2;
    }

    if (x_df816944[x_30bbe547]) {
        x_cf10d3eb = x_7188dab8[x_30bbe547];
        x_e2b79a2c = &x_ef25bafe[x_30bbe547];

        for (i = x_af0cb8e3[x_30bbe547]; i > 0; i--) {
            alSndpSetSound(x_e2b79a2c, x_cf10d3eb[i - 1]);
            alSndpSetPan(x_e2b79a2c, pan);
        }
    }
}

void x_62551fe9(s32 x_30bbe547, s16 volume) {
    s32 i;
    ALSndId *temp;

    if (x_30bbe547 >= 2) {
        x_30bbe547 = 2;
    }

    if (x_df816944[x_30bbe547]) {
        temp = x_7188dab8[x_30bbe547];
        x_e2b79a2c = &x_ef25bafe[x_30bbe547];

        for (i = x_af0cb8e3[x_30bbe547]; i > 0; i--) {
            alSndpSetSound(x_e2b79a2c, temp[i - 1]);
            alSndpSetVol(x_e2b79a2c, volume);
        }
    }
}

void x_20c52092(s16 volume) {
    alSeqpSetVol(x_85a4d96f, volume);
}

void x_e6e6fcf8(ALBankFile *f, u8 *table, u32 x_30bbe547) {
    ALSndId *x_429c730a;
    ALInstrument *inst;
    u32 i;
    s32 x_33944a37 = 0;
    ALBank *bank;

    if (table == NULL) {
        return;
    }
    if (x_30bbe547 >= 2) {
        x_30bbe547 = 2;
    }

    x_429c730a = x_7188dab8[x_30bbe547];
    alBnkfNew(f, table);
    bank = f->bankArray[0];
    inst = bank->instArray[0];
    x_e2b79a2c = &x_ef25bafe[x_30bbe547];

    for (i = 0, x_33944a37 = 0; i < inst->soundCount; i++) {
        ALSndId x_1dc13257;
        ALSound *sound = inst->soundArray[i];

        x_429c730a[i] = x_1dc13257 = alSndpAllocate(x_e2b79a2c, sound);
        if (x_1dc13257 != -1) {
            alSndpSetSound(x_e2b79a2c, x_429c730a[i]);
            alSndpSetVol(x_e2b79a2c, x_15814eea);
            x_33944a37++;
        }
    }

    if (x_33944a37 == inst->soundCount) {
        x_af0cb8e3[x_30bbe547] = x_33944a37;
        x_4553f199 = TRUE;
        x_aec099eb = x_15814eea;
    } else {
        x_af0cb8e3[x_30bbe547] = -1;
    }
}

void x_073e79bc(void) {
    D_8004A42C = FALSE;
}
