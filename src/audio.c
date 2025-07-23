#include "common.h"

typedef struct UnkAudioAlpha {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ s32 unk_08;
} UnkAudioAlpha; // size >= 0xC

typedef struct UnkAudioBeta {
    /* 0x00 */ u8 *unk_00;
    /* 0x04 */ s16 unk_04;
} UnkAudioBeta; // size >= 0x8

typedef struct UnkAudioGamma {
    /* 0x00 */ u8 *unk_00;
    /* 0x04 */ s32 unk_04;
} UnkAudioGamma; // size >= 0x8

extern OSMesgQueue gSchedSPTaskQueue;

extern u8 D_8004A420;
extern u8 D_8004A424;
extern u8 D_8004A428;
extern u8 D_8004A42C;
extern UnkAudioGamma *D_8004A434;
extern UnkAudioAlpha *D_8004A438;
extern ALSeqPlayer *D_8004A43C;
extern ALSndPlayer *D_8004A444;
extern s32 D_8004A448;
extern ALSndId *D_8004A44C[];
extern u8 D_8004A470[];
extern s8 D_8004A474[];
extern s32 D_8004A478;
extern OSTask D_8004A480;

extern ALSndPlayer D_80081728[3];
extern ALHeap D_80081830;
extern Acmd *D_80081840[];
extern ALGlobals D_80081A78;
extern u8 D_80081AC8[0x22A00];
extern s32 D_800A44CC;
extern s32 D_800A44D4;
extern s32 D_800A4500;
extern ALSndpConfig D_800A4508;
extern s32 D_800A4514;
extern s32 D_800A4518;
extern s32 D_800A4520;
extern u8 D_800A4528;
extern s32 D_800A45D8;
extern s32 D_800A45DC;
extern s32 D_800A45E0;
extern s32 D_800A45E4;
extern u32 D_800A45E8;
extern s32 D_800A45EC;
extern s32 D_800A45F4;
extern s32 D_800A45F8;
extern s32 D_800A4600[3];
extern u8 D_800A460C;
extern OSMesgQueue D_800A4890;
extern OSMesg D_800A48A8[32];

void func_80020D20(ALSynConfig *);
ALDMAproc func_80021178(void *state);

void func_800206B0(void) {
    D_8004A480.t.type = M_AUDTASK;
    D_8004A480.t.ucode_boot = rspbootTextStart;
    D_8004A480.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    D_8004A480.t.flags = 0;
    D_8004A480.t.ucode = aspMainTextStart;
    D_8004A480.t.ucode_data = aspMainDataStart;
    D_8004A480.t.ucode_data_size = 0x800;
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
    D_8004A420 = 0;
    D_8004A424 = 0;
    D_8004A42C = 0;
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

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80020934.s")
void func_80020934(void);

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80020BB4.s")

void func_80020D20(ALSynConfig *config) {
    f32 tmp;

    D_800A4528 = 0;
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

#ifdef NON_MATCHING
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

    arg0->unk_04 = (D_800A45E8 - osAiGetLength() / 4 + 60) & ~0xF;

    a1 = alAudioFrame(D_80081840[D_800A45E0], &D_800A45F4, sp1C, arg0->unk_04);
    D_8004A480.t.data_ptr = D_80081840[D_800A45E0];
    D_8004A480.t.data_size = (a1 - D_80081840[D_800A45E0]) * sizeof(Acmd);

    D_8004A434 = D_80081840[D_800A45D8 % 3 + 1];
    D_800A45E0 ^= 1;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80020E54.s")
s32 func_80020E54(UnkAudioBeta *arg0);
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80020FBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80021178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_800211B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_800212C8.s")

s32 func_80021338(void) {
    s32 i;

    if (D_8004A420 + D_8004A424 == 0) {
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

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_800213E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80021550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80021618.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_800216E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80021734.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80021778.s")

#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_800217A0.s")

void func_80021918(Object *arg0, s32 arg1) {
    s32 v1 = FALSE;

    if (D_8004A420 != 0 && D_8004A420 != 0) {
        alSeqpPlay(D_8004A43C);
        v1 = TRUE;
    }

    arg0->unk_090[0]++;
    if (arg0->unk_090[0] >= 16 || (D_800A460C & 1)) {
        v1 = TRUE;
    }

    if (v1) {
        arg0->unk_080 |= 0x10;
        arg0->unk_1F4->unk_00 |= 0x80;
    }
}

void func_800219B8(s32 arg0, u8 arg1) {
    s32 i;
    ALSndId *tmp;

    if (D_8004A428 != 0 || D_8004A42C != 0) {
        return;
    }

    if (arg0 > 2) {
        arg0 = 2;
    }

    if (D_8004A470[arg0] != 0) {
        tmp = D_8004A44C[arg0];
        D_8004A444 = &D_80081728[arg0];

        for (i = D_8004A474[arg0]; i > 0; i--) {
            alSndpSetSound(D_8004A444, tmp[i - 1]);
            alSndpSetPan(D_8004A444, arg1);
        }
    }
}

#ifdef NON_MATCHING
void func_80021AA8(s32 arg0, s16 arg1) {
    s32 i;

    if (arg0 >= 2) {
        arg0 = 2;
    }

    if (D_8004A470[arg0] != 0) {
        D_8004A444 = &D_80081728[arg0];

        for (i = D_8004A474[arg0]; i >= 0; i--) {
            alSndpSetSound(D_8004A444, D_8004A44C[arg0][i]);
            alSndpSetVol(D_8004A444, arg1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80021AA8.s")
#endif

#ifdef NON_MATCHING
void func_80021B8C(s16 arg0) {
    alSeqpSetVol(D_8004A43C, arg0);
}
#else
void func_80021B8C(s16 arg0);
#pragma GLOBAL_ASM("asm/nonmatchings/audio/func_80021B8C.s")
#endif

void func_80021BC0(ALBankFile *arg0, u8 *arg1, u32 arg2) {
    ALSndId *s6;
    ALInstrument *s5;
    u32 i;
    s32 s4 = 0;
    ALBank *bank;

    if (arg1 == NULL) {
        return;
    }
    if (arg2 >= 2) {
        arg2 = 2;
    }

    s6 = D_8004A44C[arg2];
    alBnkfNew(arg0, arg1);
    bank = arg0->bankArray[0];
    s5 = bank->instArray[0];
    D_8004A444 = &D_80081728[arg2];

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
        D_8004A474[arg2] = s4;
        D_8004A424 = 1;
        D_800A4520 = D_8004A478;
    } else {
        D_8004A474[arg2] = -1;
    }
}

void func_80021D30(void) {
    D_8004A42C = 0;
}
