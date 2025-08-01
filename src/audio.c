#include "common.h"

typedef struct UnkAudioAlpha {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ s32 unk_08;
} UnkAudioAlpha; // size >= 0xC

typedef struct UnkAudioBeta {
    /* 0x00 */ u8 *unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x04 */ char unk_06[0x60 - 0x6];
    /* 0x60 */ s16 unk_60;
    /* 0x64 */ struct UnkAudioBeta *unk_64;
    /* 0x68 */ s32 unk_68[6];
} UnkAudioBeta; // size = 0x80

typedef struct UnkAudioDelta {
    /* 0x00 */ struct UnkAudioDelta *next;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u8 *unk_10;
} UnkAudioDelta; // size = 0x14

typedef struct AudioDMAState {
    /* 0x00 */ u8 unk_00;
    /* 0x00 */ struct UnkAudioDelta *unk_04;
    /* 0x00 */ struct UnkAudioDelta *unk_08;
} AudioDMAState; // size = 0xC

typedef struct UnkAudioEpsilon {
    /* 0x00 */ Acmd *unk_00[2];
    /* 0x08 */ UnkAudioBeta *unk_08[3];
} UnkAudioEpsilon;

// .bss

UnkAudioAlpha D_80081670;
ALSeqPlayer D_80081680;
ALSeq D_80081708;
ALSndPlayer D_80081728[3];
ALHeap D_80081830;
UnkAudioEpsilon D_80081840;
char D_80081858[0x220]; // unused?
ALGlobals D_80081A78;
u8 D_80081AC8[0x22A00];
ALBankFile *D_800A44C8;
s32 D_800A44CC;
s32 D_800A44D0; // unused
s32 D_800A44D4;
s32 D_800A44D8;
s32 D_800A44DC; // unused, file split?
ALSeqMarker D_800A44E0;
ALSeqMarker D_800A44F0;
s32 D_800A4500;
ALSndpConfig D_800A4508;
s32 D_800A4514;
s32 D_800A4518;
s32 D_800A451C; // unused, file split?
s32 D_800A4520;
u8 D_800A4524[2];
AudioDMAState D_800A4528;
UnkAudioDelta D_800A4538[8];
u32 D_800A45D8;
s32 D_800A45DC;
s32 D_800A45E0;
u32 D_800A45E4;
u32 D_800A45E8;
s32 D_800A45EC;
s32 D_800A45F0;
s32 D_800A45F4;
s32 D_800A45F8;
s32 D_800A4600[3];
u8 D_800A460C;
OSIoMesg D_800A4610[32];
OSMesgQueue D_800A4890;
OSMesg D_800A48A8[32];

// .data

u8 D_8004A420 = FALSE;
u8 D_8004A424 = FALSE;
u8 D_8004A428 = 0;
u8 D_8004A42C = FALSE;
s32 D_8004A430 = 0; // unused
UnkAudioBeta *D_8004A434 = NULL;
UnkAudioAlpha *D_8004A438 = &D_80081670;
ALSeqPlayer *D_8004A43C = &D_80081680;
ALSeq *D_8004A440 = &D_80081708;
ALSndPlayer *D_8004A444 = &D_80081728[0];
s32 D_8004A448 = 0x7FFF;
ALSndId *D_8004A44C[3] = { NULL, NULL, NULL };
ALBankFile *D_8004A458[3] = { NULL, NULL, NULL };
s32 D_8004A464[3] = { 0, 0, 0 }; // unused, file split??

u8 D_8004A470[3] = { FALSE, FALSE, FALSE };
s8 D_8004A474[3] = { -1, -1, -1 };
s32 D_8004A478 = 0x7FFF;
s32 D_8004A47C = 0; // unused, file split?

OSTask D_8004A480 = { { 2, 0, NULL, 0, NULL, 0x1000, NULL, 0x800, NULL, 0x400, NULL, 0, NULL, 0, NULL, 0 } };

void func_80020D20(ALSynConfig *);
ALDMAproc func_80021178(AudioDMAState **state);
void func_800211B0(void);
s32 func_80020E54(UnkAudioBeta *arg0);
void func_800219B8(s32 arg0, u8 arg1);
void func_80021B8C(s16 arg0);
void func_80021AA8(s32 arg0, s16 arg1);

void func_800206B0(void) {
    D_8004A480.t.type = M_AUDTASK;
    D_8004A480.t.ucode_boot = (u64 *) rspbootTextStart;
    D_8004A480.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    D_8004A480.t.flags = 0;
    D_8004A480.t.ucode = (u64 *) aspMainTextStart;
    D_8004A480.t.ucode_data = (u64 *) aspMainDataStart;
    D_8004A480.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    D_8004A480.t.dram_stack = NULL;
    D_8004A480.t.dram_stack_size = 0;
    D_8004A480.t.output_buff = NULL;
    D_8004A480.t.output_buff_size = 0;
    D_8004A480.t.yield_data_ptr = NULL;
    D_8004A480.t.yield_data_size = 0;
}

void func_8002071C(void) {
    D_800A44CC = 0;
    D_800A44D4 = 0;
    D_800A4514 = 0;
    D_800A4518 = 0;
    D_800A45D8 = 0;
    D_800A45DC = 0;
    D_800A45E0 = 0;
    D_800A460C = 0;
    D_800A4600[0] = D_800A4600[1] = D_800A4600[2] = -1;
    D_8004A420 = FALSE;
    D_8004A424 = FALSE;
    D_8004A42C = FALSE;
    D_800A45F4 = D_800A45F8 = 0;
    D_800A4520 = D_8004A478;
    D_800A4500 = D_8004A448;
    D_8004A434 = NULL;
    func_800206B0();
}

void func_800207E4(void) {
    ALSynConfig synConfig;
    ALSeqpConfig seqpConfig;
    u32 unused[5];

    alHeapInit(&D_80081830, D_80081AC8, sizeof(D_80081AC8));
    func_8002071C();

    synConfig.maxVVoices = 42;
    synConfig.maxPVoices = 42;
    synConfig.maxUpdates = 32;
    synConfig.dmaproc = NULL;
    synConfig.fxType = AL_FX_SMALLROOM;
    synConfig.outputRate = 0;
    synConfig.heap = &D_80081830;

    D_8004A438->unk_00 = 11025;
    D_8004A438->unk_04 = 1;
    D_8004A438->unk_08 = 0x1100;

    func_80020D20(&synConfig);

    seqpConfig.maxVoices = 42;
    seqpConfig.maxEvents = 48;
    seqpConfig.maxChannels = 16;
    seqpConfig.heap = &D_80081830;
    seqpConfig.initOsc = NULL;
    seqpConfig.updateOsc = NULL;
    seqpConfig.stopOsc = NULL;
    seqpConfig.debugFlags = NO_SOUND_ERR_MASK | NOTE_OFF_ERR_MASK | NO_VOICE_ERR_MASK;
    alSeqpNew(D_8004A43C, &seqpConfig);

    D_800A4508.maxSounds = 42;
    D_800A4508.maxEvents = 60;
    D_800A4508.heap = &D_80081830;
    alSndpNew(&D_80081728[0], &D_800A4508);
    alSndpNew(&D_80081728[1], &D_800A4508);
    alSndpNew(&D_80081728[2], &D_800A4508);
    D_8004A444 = D_80081728;
}

void func_80020934(void) {
    u32 i;

    D_800A4538[0].unk_04 = NULL;
    D_800A4538[0].next = NULL;

    for (i = 0; i < 7; i++) {
        alLink(&D_800A4538[i + 1], &D_800A4538[i]);
        D_800A4538[i].unk_10 = alHeapDBAlloc("audio.c", 238, &D_80081830, 1, 0x80);
    }
    D_800A4538[i].unk_10 = alHeapDBAlloc("audio.c", 241, &D_80081830, 1, 0x80);

    for (i = 0; i < 2; i++) {
        D_80081840.unk_00[i] = alHeapDBAlloc("audio.c", 244, &D_80081830, 1, D_8004A438->unk_08 * sizeof(Acmd));
    }

    D_800A45F0 = D_8004A438->unk_08;

    for (i = 0; i < 3; i++) {
        D_80081840.unk_08[i] = alHeapDBAlloc("audio.c", 250, &D_80081830, 1, sizeof(UnkAudioBeta));
        D_80081840.unk_08[i]->unk_60 = 2;
        D_80081840.unk_08[i]->unk_64 = D_80081840.unk_08[i];
        D_80081840.unk_08[i]->unk_00 = alHeapDBAlloc("audio.c", 253, &D_80081830, 1, D_800A45EC * 4);
    }

    D_800A44C8 = alHeapDBAlloc("audio.c", 255, &D_80081830, 1, 0x800);

    for (i = 0; i < 3; i++) {
        D_8004A44C[i] = alHeapDBAlloc("audio.c", 259, &D_80081830, 1, 30 * sizeof(ALSndId));
        D_8004A458[i] = alHeapDBAlloc("audio.c", 260, &D_80081830, 1, 0x1600);
        D_8004A470[i] = FALSE;
    }
}

void func_80020BB4(void) {
    s32 i, j;
    ALSndId *tmp;

    func_8002071C();

    for (i = 0; i < 3; i++) {
        if (D_8004A470[i]) {
            tmp = D_8004A44C[i];
            D_8004A444 = &D_80081728[i];
            for (j = D_8004A474[i]; j > 0; j--) {
                alSndpSetSound(D_8004A444, tmp[j - 1]);
                alSndpDeallocate(D_8004A444, tmp[j - 1]);
            }
            D_8004A470[i] = FALSE;
            D_8004A474[i] = 0;
        }
    }

    func_80020E54(D_80081840.unk_08[D_800A45D8 % 3]);
    func_800211B0();
    alClose(&D_80081A78);
    func_800207E4();
    sched_wait_vretrace(FALSE);
    sched_wait_vretrace(FALSE);
    sched_wait_vretrace(FALSE);
}

void func_80020D20(ALSynConfig *config) {
    f32 tmp;

    D_800A4528.unk_00 = FALSE;
    config->dmaproc = func_80021178;
    config->outputRate = osAiSetFrequency(D_8004A438->unk_00);

    tmp = (f32) D_8004A438->unk_04 * (f32) config->outputRate / 60.0f;
    D_800A45E8 = (s32) tmp;
    if ((f32) D_800A45E8 < (f32) tmp) {
        D_800A45E8++;
    }
    if (D_800A45E8 & 0xF) {
        D_800A45E8 = (D_800A45E8 & ~0xF) + 0x10;
    }

    D_800A45E4 = D_800A45E8 - 0x10;
    D_800A45EC = D_800A45E8 + 0x60;

    alInit(&D_80081A78, config);
    func_80020934();
    osCreateMesgQueue(&D_800A4890, D_800A48A8, ARRAY_COUNT(D_800A48A8));
}

s32 func_80020E54(UnkAudioBeta *arg0) {
    s32 sp1C;
    Acmd *a1;

    if (D_800A45F8 != 0) {
        D_800A45F8 = 0;
    }

    sp1C = osVirtualToPhysical(arg0->unk_00);
    if (D_8004A434 != NULL) {
        osAiSetNextBuffer(D_8004A434->unk_00, D_8004A434->unk_04 * 4);
    }

    arg0->unk_04 = (D_800A45E8 - osAiGetLength() / 4 + 96) & ~0xF;
    if (arg0->unk_04 < D_800A45E4) {
        arg0->unk_04 = D_800A45E4;
    }

    a1 = alAudioFrame(D_80081840.unk_00[D_800A45E0], &D_800A45F4, sp1C, arg0->unk_04);
    if (D_800A45F4 == 0) {
        return FALSE;
    }

    D_8004A480.t.data_ptr = D_80081840.unk_00[D_800A45E0];
    D_8004A480.t.data_size = (a1 - D_80081840.unk_00[D_800A45E0]) * sizeof(Acmd);

    D_8004A434 = D_80081840.unk_08[D_800A45D8 % 3]->unk_64;
    D_800A45E0 ^= 1;
    return TRUE;
}

s32 func_80020FBC(s32 addr, s32 len, void *state) {
    u8 *sp44;
    s32 sp40;
    s32 v1;
    s32 newvar;
    UnkAudioDelta *sp34;
    UnkAudioDelta *sp30;

    if (addr < 0) {
        return osVirtualToPhysical(addr);
    }

    sp30 = NULL;
    for (sp34 = D_800A4528.unk_04; sp34 != NULL; sp34 = sp34->next) {
        newvar = sp34->unk_08 + 0x80;
        if (addr < sp34->unk_08) {
            break;
        }

        sp30 = sp34;
        v1 = addr + len;
        if (v1 <= newvar) {
            sp34->unk_0C = D_800A45D8;
            return osVirtualToPhysical(sp34->unk_10 + addr - sp34->unk_08);
        }
    }

    sp34 = D_800A4528.unk_08;
    D_800A4528.unk_08 = sp34->next;

    alUnlink(sp34);
    if (sp30 != NULL) {
        alLink(sp34, sp30);
    } else {
        UnkAudioDelta *v0 = D_800A4528.unk_04;
        if (v0 != NULL) {
            D_800A4528.unk_04 = sp34;
            sp34->next = v0;
            sp34->unk_04 = NULL;
            v0->unk_04 = sp34;
        } else {
            D_800A4528.unk_04 = sp34;
            sp34->next = NULL;
            sp34->unk_04 = NULL;
        }
    }

    sp44 = sp34->unk_10;
    sp40 = addr & 1;
    addr -= sp40;
    sp34->unk_08 = addr;
    sp34->unk_0C = D_800A45D8;

    osInvalDCache(sp44, len);
    osPiStartDma(&D_800A4610[D_800A45DC++], OS_MESG_PRI_NORMAL, OS_READ, addr, sp44, 0x80, &D_800A4890);
    return osVirtualToPhysical(sp44) + sp40;
}

ALDMAproc func_80021178(AudioDMAState **state) {
    if (!D_800A4528.unk_00) {
        D_800A4528.unk_04 = 0;
        D_800A4528.unk_08 = D_800A4538;
        D_800A4528.unk_00 = TRUE;
    }
    *state = &D_800A4528;
    return func_80020FBC;
}

void func_800211B0(void) {
    u32 i;
    OSMesg mesg;
    UnkAudioDelta *s0;
    UnkAudioDelta *next;

    for (i = 0; i < D_800A45DC; i++) {
        osRecvMesg(&D_800A4890, &mesg, OS_MESG_NOBLOCK);
    }

    for (s0 = D_800A4528.unk_04; s0 != NULL; s0 = next) {
        next = s0->next;
        if (s0->unk_0C + 1 < D_800A45D8) {
            if (s0 == D_800A4528.unk_04) {
                D_800A4528.unk_04 = s0->next;
            }
            alUnlink(s0);
            if (D_800A4528.unk_08 != NULL) {
                alLink(s0, D_800A4528.unk_08);
            } else {
                D_800A4528.unk_08 = s0;
                s0->next = NULL;
                s0->unk_04 = NULL;
            }
        }
    }

    D_800A45DC = 0;
    D_800A45D8++;
}

void func_800212C8(void) {
    if (D_8004A420 + D_8004A424) {
        D_800A45F4 = 0;
        if (func_80020E54(D_80081840.unk_08[D_800A45D8 % 3])) {
            func_800211B0();
        }
    }
}

s32 func_80021338(void) {
    s32 i;

    if (!(D_8004A420 + D_8004A424)) {
        return FALSE;
    }

    if (D_800A45F4 != 0) {
        osSendMesg(&gSchedSPTaskQueue, (OSMesg *) &D_8004A480, OS_MESG_BLOCK);
    }

    for (i = 0; i < ARRAY_COUNT(D_800A4600); i++) {
        if (D_800A4600[i] >= 0) {
            func_800213E0(i, D_800A4600[i]);
        }
    }

    return TRUE;
}

void func_800213E0(u32 arg0, u32 arg1) {
    ALSndId *tmp;
    s32 v0;

    if (arg0 >= 2) {
        arg0 = 2;
    }

    if (arg1 < D_8004A474[arg0] && D_8004A470[arg0]) {
        if (arg0 < 2) {
            if (D_800A4524[arg0] != gPlayerInput[arg0].unk_09) {
                D_800A4524[arg0] = gPlayerInput[arg0].unk_09;

                if (D_800A4524[arg0]) {
                    v0 = 20;
                } else {
                    v0 = 100;
                }

                func_800219B8(arg0, v0);
            }
        }

        tmp = D_8004A44C[arg0];
        D_8004A444 = &D_80081728[arg0];
        alSndpSetSound(D_8004A444, tmp[arg1]);
        if (alSndpGetState(D_8004A444) != AL_STOPPED) {
            alSndpStop(D_8004A444);
            D_800A4600[arg0] = arg1;
        } else {
            alSndpPlay(D_8004A444);
            D_800A4600[arg0] = -1;
            D_8004A424 = TRUE;
        }
    }
}

void func_80021550(u32 arg0, u32 arg1) {
    ALSndId *tmp;

    if (arg0 >= 2) {
        arg0 = 2;
    }

    if (arg1 < D_8004A474[arg0] && D_8004A470[arg0]) {
        tmp = D_8004A44C[arg0];
        D_8004A444 = &D_80081728[arg0];
        alSndpSetSound(D_8004A444, tmp[arg1]);
        if (alSndpGetState(D_8004A444) != AL_STOPPED) {
            alSndpStop(D_8004A444);
        }
        D_8004A424 = TRUE;
    }
}

void func_80021618(s32 arg0) {
    ALSndId *tmp;
    s32 i;

    if (D_8004A470[arg0]) {
        tmp = D_8004A44C[arg0];
        D_8004A444 = &D_80081728[arg0];

        for (i = D_8004A474[arg0]; i > 0; i--) {
            alSndpSetSound(D_8004A444, tmp[i - 1]);
            alSndpStop(D_8004A444);
            D_800A45F8++;
        }
    }
}

void func_800216E8(void) {
    s32 i;

    if (D_8004A424) {
        for (i = 0; i < 3; i++) {
            func_80021618(i);
        }
    }
}

void func_80021734(void) {
    if (D_8004A420) {
        alSeqpStop(D_8004A43C);
        D_800A45F8++;
    }
}

void func_80021778(Object *obj) {
    if (obj->unk_090[0]-- < 0) {
        obj->currentTask->flags |= 0x80;
    }
}

void func_800217A0(Object *obj, s32 arg1) {
    D_800A460C |= 1;

    if (D_8004A424 && D_800A4520 != 0) {
        D_800A4520 -= 1213;
        if (D_800A4520 < 0) {
            D_800A4520 = 0;
        }

        if (D_800A4520 == 0) {
            func_800216E8();
        } else {
            func_80021AA8(0, D_800A4520);
            func_80021AA8(1, D_800A4520);
            func_80021AA8(2, D_800A4520);
        }
    } else if (!D_8004A424) {
        D_800A4520 = 0;
    }

    if (D_8004A420 && D_800A4500 != 0) {
        D_800A4500 -= 1213;
        if (D_800A4500 < 0) {
            D_800A4500 = 0;
        }

        if (D_800A4500 == 0) {
            func_80021734();
        } else {
            func_80021B8C(D_800A4500);
        }
    } else if (!D_8004A420) {
        D_800A4500 = 0;
    }

    if (D_800A4500 + D_800A4520 == 0) {
        obj->fn_update = func_80021778;
    }
}

void func_80021918(Object *arg0, s32 arg1) {
    s32 v1 = FALSE;

    if (D_8004A420 && D_8004A420) { // @bug
        alSeqpPlay(D_8004A43C);
        v1 = TRUE;
    }

    arg0->unk_090[0]++;
    if (arg0->unk_090[0] >= 16 || (D_800A460C & 1)) {
        v1 = TRUE;
    }

    if (v1) {
        arg0->flags |= 0x10;
        arg0->currentTask->flags |= 0x80;
    }
}

void func_800219B8(s32 arg0, u8 arg1) {
    s32 i;
    ALSndId *tmp;

    if (D_8004A428 != 0 || D_8004A42C) {
        return;
    }

    if (arg0 > 2) {
        arg0 = 2;
    }

    if (D_8004A470[arg0]) {
        tmp = D_8004A44C[arg0];
        D_8004A444 = &D_80081728[arg0];

        for (i = D_8004A474[arg0]; i > 0; i--) {
            alSndpSetSound(D_8004A444, tmp[i - 1]);
            alSndpSetPan(D_8004A444, arg1);
        }
    }
}

void func_80021AA8(s32 arg0, s16 arg1) {
    s32 i;
    ALSndId *temp;

    if (arg0 >= 2) {
        arg0 = 2;
    }

    if (D_8004A470[arg0]) {
        temp = D_8004A44C[arg0];
        D_8004A444 = &D_80081728[arg0];

        for (i = D_8004A474[arg0]; i > 0; i--) {
            alSndpSetSound(D_8004A444, temp[i - 1]);
            alSndpSetVol(D_8004A444, arg1);
        }
    }
}

void func_80021B8C(s16 volume) {
    alSeqpSetVol(D_8004A43C, volume);
}

void func_80021BC0(ALBankFile *f, u8 *table, u32 playerId) {
    ALSndId *s6;
    ALInstrument *s5;
    u32 i;
    s32 s4 = 0;
    ALBank *bank;

    if (table == NULL) {
        return;
    }
    if (playerId >= 2) {
        playerId = 2;
    }

    s6 = D_8004A44C[playerId];
    alBnkfNew(f, table);
    bank = f->bankArray[0];
    s5 = bank->instArray[0];
    D_8004A444 = &D_80081728[playerId];

    for (i = 0, s4 = 0; i < s5->soundCount; i++) {
        ALSndId soundId;
        ALSound *sound = s5->soundArray[i];

        s6[i] = soundId = alSndpAllocate(D_8004A444, sound);
        if (soundId != -1) {
            alSndpSetSound(D_8004A444, s6[i]);
            alSndpSetVol(D_8004A444, D_8004A478);
            s4++;
        }
    }

    if (s4 == s5->soundCount) {
        D_8004A474[playerId] = s4;
        D_8004A424 = TRUE;
        D_800A4520 = D_8004A478;
    } else {
        D_8004A474[playerId] = -1;
    }
}

void func_80021D30(void) {
    D_8004A42C = FALSE;
}
