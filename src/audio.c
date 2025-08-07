#include "common.h"

#define CONST_80 0x80

typedef struct AudioConfig {
    /* 0x00 */ s32 frequency;
    /* 0x04 */ u32 freqMultiplier;
    /* 0x08 */ s32 maxCommands;
} AudioConfig; // size >= 0xC

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
    /* 0x04 */ struct UnkAudioDelta *prev;
    /* 0x08 */ u32 rom_addr;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u8 *vram_addr;
} UnkAudioDelta; // size = 0x14

typedef struct AudioDMAState {
    /* 0x00 */ u8 unk_00;
    /* 0x00 */ struct UnkAudioDelta *head;
    /* 0x00 */ struct UnkAudioDelta *tail;
} AudioDMAState; // size = 0xC

typedef struct UnkAudioEpsilon {
    /* 0x00 */ Acmd *cmdBuffers[2];
    /* 0x08 */ UnkAudioBeta *unk_08[3];
} UnkAudioEpsilon;

// .bss

AudioConfig gAudioConfigData;
ALSeqPlayer D_80081680;
ALSeq D_80081708;
ALSndPlayer gSfxPlayers[3];
ALHeap gAudioHeap;
UnkAudioEpsilon D_80081840;
char D_80081858[0x220]; // unused
ALGlobals D_80081A78;
u8 gAudioHeapBuffer[0x22A00];
ALBankFile *gMusicBankFile;
s32 gMusicBankFileSize;
s32 D_800A44D0; // unused
u8 *gCurrentSongData;
s32 gCurrentSongDataSize;
s32 D_800A44DC; // unused
ALSeqMarker gMusicMarkerStart;
ALSeqMarker gMusicMarkerEnd;
s32 gMusicVolumeFading;
ALSndpConfig gSfxPlayerConfig;
s32 D_800A4514;
s32 D_800A4518;
s32 D_800A451C; // unused
s32 gSoundVolumeFading;
u8 D_800A4524[2];
AudioDMAState gAudioDMAState;
UnkAudioDelta D_800A4538[8];
u32 D_800A45D8;
s32 gAudioNextDMA;
s32 D_800A45E0;
u32 D_800A45E4;
u32 D_800A45E8;
s32 D_800A45EC;
s32 gAudioCmdBufferSize;
s32 D_800A45F4;
s32 gSoundStopCounter;
s32 gPendingSound[3];
u8 D_800A460C;
OSIoMesg gAudioSMAIOMesgBuf[32];
OSMesgQueue D_800A4890;
OSMesg D_800A48A8[32];

// .data

u8 gMusicIsPlaying = FALSE;
u8 gSoundIsPlaying = FALSE;
u8 D_8004A428 = 0;
u8 D_8004A42C = FALSE;
s32 D_8004A430 = 0; // unused
UnkAudioBeta *D_8004A434 = NULL;
AudioConfig *gAudioConfig = &gAudioConfigData;
ALSeqPlayer *gMusicPlayer = &D_80081680;
ALSeq *gMusicSequence = &D_80081708;
ALSndPlayer *gCurrentSfxPlayer = &gSfxPlayers[0];
s32 gMusicVolume = 0x7FFF;
ALSndId *gSoundTables[3] = { NULL, NULL, NULL };
ALBankFile *gAudioBankFiles[3] = { NULL, NULL, NULL };
s32 D_8004A464[3] = { 0, 0, 0 }; // unused
u8 gSfxPlayerOn[3] = { FALSE, FALSE, FALSE };
s8 gSfxNumSounds[3] = { -1, -1, -1 };
s32 gSoundVolume = 0x7FFF;
s32 D_8004A47C = 0; // unused
OSTask gAudioOsTask = { { M_AUDTASK, 0, NULL, 0, NULL, SP_UCODE_SIZE, NULL, SP_UCODE_DATA_SIZE, NULL,
                          SP_DRAM_STACK_SIZE8, NULL, 0, NULL, 0, NULL, 0 } };

void func_80020D20(ALSynConfig *);
ALDMAproc audio_dmanew(AudioDMAState **state);
void func_800211B0(void);
s32 func_80020E54(UnkAudioBeta *arg0);
void sound_set_pan(s32 arg0, u8 arg1);
void music_set_volume(s16 arg0);
void sound_set_volume(s32 arg0, s16 arg1);

void audio_init_ostask(void) {
    gAudioOsTask.t.type = M_AUDTASK;
    gAudioOsTask.t.ucode_boot = (u64 *) rspbootTextStart;
    gAudioOsTask.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    gAudioOsTask.t.flags = 0;
    gAudioOsTask.t.ucode = (u64 *) aspMainTextStart;
    gAudioOsTask.t.ucode_data = (u64 *) aspMainDataStart;
    gAudioOsTask.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    gAudioOsTask.t.dram_stack = NULL;
    gAudioOsTask.t.dram_stack_size = 0;
    gAudioOsTask.t.output_buff = NULL;
    gAudioOsTask.t.output_buff_size = 0;
    gAudioOsTask.t.yield_data_ptr = NULL;
    gAudioOsTask.t.yield_data_size = 0;
}

void audio_clear_params(void) {
    gMusicBankFileSize = 0;
    gCurrentSongData = NULL;
    D_800A4514 = 0;
    D_800A4518 = 0;
    D_800A45D8 = 0;
    gAudioNextDMA = 0;
    D_800A45E0 = 0;
    D_800A460C = 0;
    gPendingSound[0] = gPendingSound[1] = gPendingSound[2] = -1;
    gMusicIsPlaying = FALSE;
    gSoundIsPlaying = FALSE;
    D_8004A42C = FALSE;
    D_800A45F4 = gSoundStopCounter = 0;
    gSoundVolumeFading = gSoundVolume;
    gMusicVolumeFading = gMusicVolume;
    D_8004A434 = NULL;
    audio_init_ostask();
}

void audio_init(void) {
    ALSynConfig synConfig;
    ALSeqpConfig seqpConfig;
    u32 unused[5];

    alHeapInit(&gAudioHeap, gAudioHeapBuffer, sizeof(gAudioHeapBuffer));
    audio_clear_params();

    synConfig.maxVVoices = 42;
    synConfig.maxPVoices = 42;
    synConfig.maxUpdates = 32;
    synConfig.dmaproc = NULL;
    synConfig.fxType = AL_FX_SMALLROOM;
    synConfig.outputRate = 0;
    synConfig.heap = &gAudioHeap;

    gAudioConfig->frequency = 11025;
    gAudioConfig->freqMultiplier = 1;
    gAudioConfig->maxCommands = 0x1100;

    func_80020D20(&synConfig);

    seqpConfig.maxVoices = 42;
    seqpConfig.maxEvents = 48;
    seqpConfig.maxChannels = 16;
    seqpConfig.heap = &gAudioHeap;
    seqpConfig.initOsc = NULL;
    seqpConfig.updateOsc = NULL;
    seqpConfig.stopOsc = NULL;
    seqpConfig.debugFlags = NO_SOUND_ERR_MASK | NOTE_OFF_ERR_MASK | NO_VOICE_ERR_MASK;
    alSeqpNew(gMusicPlayer, &seqpConfig);

    gSfxPlayerConfig.maxSounds = 42;
    gSfxPlayerConfig.maxEvents = 60;
    gSfxPlayerConfig.heap = &gAudioHeap;
    alSndpNew(&gSfxPlayers[0], &gSfxPlayerConfig);
    alSndpNew(&gSfxPlayers[1], &gSfxPlayerConfig);
    alSndpNew(&gSfxPlayers[2], &gSfxPlayerConfig);
    gCurrentSfxPlayer = gSfxPlayers;
}

void audio_allocate_buffers(void) {
    u32 i;

    D_800A4538[0].prev = NULL;
    D_800A4538[0].next = NULL;

    for (i = 0; i < ARRAY_COUNT(D_800A4538) - 1; i++) {
        alLink(&D_800A4538[i + 1], &D_800A4538[i]);
        D_800A4538[i].vram_addr = alHeapDBAlloc("audio.c", 238, &gAudioHeap, 1, CONST_80);
    }
    D_800A4538[i].vram_addr = alHeapDBAlloc("audio.c", 241, &gAudioHeap, 1, CONST_80);

    for (i = 0; i < ARRAY_COUNT(D_80081840.cmdBuffers); i++) {
        D_80081840.cmdBuffers[i] =
            alHeapDBAlloc("audio.c", 244, &gAudioHeap, 1, gAudioConfig->maxCommands * sizeof(Acmd));
    }

    gAudioCmdBufferSize = gAudioConfig->maxCommands;

    for (i = 0; i < ARRAY_COUNT(D_80081840.unk_08); i++) {
        D_80081840.unk_08[i] = alHeapDBAlloc("audio.c", 250, &gAudioHeap, 1, sizeof(UnkAudioBeta));
        D_80081840.unk_08[i]->unk_60 = 2;
        D_80081840.unk_08[i]->unk_64 = D_80081840.unk_08[i];
        D_80081840.unk_08[i]->unk_00 = alHeapDBAlloc("audio.c", 253, &gAudioHeap, 1, D_800A45EC * 4);
    }

    gMusicBankFile = alHeapDBAlloc("audio.c", 255, &gAudioHeap, 1, 0x800);

    for (i = 0; i < 3; i++) {
        gSoundTables[i] = alHeapDBAlloc("audio.c", 259, &gAudioHeap, 1, 30 * sizeof(ALSndId));
        gAudioBankFiles[i] = alHeapDBAlloc("audio.c", 260, &gAudioHeap, 1, 0x1600);
        gSfxPlayerOn[i] = FALSE;
    }
}

void audio_reset(void) {
    s32 i, j;
    ALSndId *tmp;

    audio_clear_params();

    for (i = 0; i < 3; i++) {
        if (gSfxPlayerOn[i]) {
            tmp = gSoundTables[i];
            gCurrentSfxPlayer = &gSfxPlayers[i];
            for (j = gSfxNumSounds[i]; j > 0; j--) {
                alSndpSetSound(gCurrentSfxPlayer, tmp[j - 1]);
                alSndpDeallocate(gCurrentSfxPlayer, tmp[j - 1]);
            }
            gSfxPlayerOn[i] = FALSE;
            gSfxNumSounds[i] = 0;
        }
    }

    func_80020E54(D_80081840.unk_08[D_800A45D8 % 3]);
    func_800211B0();
    alClose(&D_80081A78);
    audio_init();
    sched_wait_vretrace(FALSE);
    sched_wait_vretrace(FALSE);
    sched_wait_vretrace(FALSE);
}

void func_80020D20(ALSynConfig *config) {
    f32 tmp;

    gAudioDMAState.unk_00 = FALSE;
    config->dmaproc = audio_dmanew;
    config->outputRate = osAiSetFrequency(gAudioConfig->frequency);

    tmp = (f32) gAudioConfig->freqMultiplier * (f32) config->outputRate / 60.0f;
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
    audio_allocate_buffers();
    osCreateMesgQueue(&D_800A4890, D_800A48A8, ARRAY_COUNT(D_800A48A8));
}

s32 func_80020E54(UnkAudioBeta *arg0) {
    s32 sp1C;
    Acmd *a1;

    if (gSoundStopCounter != 0) {
        gSoundStopCounter = 0;
    }

    sp1C = osVirtualToPhysical(arg0->unk_00);
    if (D_8004A434 != NULL) {
        osAiSetNextBuffer(D_8004A434->unk_00, D_8004A434->unk_04 * 4);
    }

    arg0->unk_04 = (D_800A45E8 - osAiGetLength() / 4 + 96) & ~0xF;
    if (arg0->unk_04 < D_800A45E4) {
        arg0->unk_04 = D_800A45E4;
    }

    a1 = alAudioFrame(D_80081840.cmdBuffers[D_800A45E0], &D_800A45F4, sp1C, arg0->unk_04);
    if (D_800A45F4 == 0) {
        return FALSE;
    }

    gAudioOsTask.t.data_ptr = D_80081840.cmdBuffers[D_800A45E0];
    gAudioOsTask.t.data_size = (a1 - D_80081840.cmdBuffers[D_800A45E0]) * sizeof(Acmd);

    D_8004A434 = D_80081840.unk_08[D_800A45D8 % 3]->unk_64;
    D_800A45E0 ^= 1;
    return TRUE;
}

s32 audio_dma(s32 addr, s32 len, void *state) {
    u8 *sp44;
    s32 sp40;
    s32 v1;
    s32 newvar;
    UnkAudioDelta *curr;
    UnkAudioDelta *sp30;

    if (addr < 0) {
        return osVirtualToPhysical(addr);
    }

    sp30 = NULL;
    for (curr = gAudioDMAState.head; curr != NULL; curr = curr->next) {
        newvar = curr->rom_addr + 0x80;
        if (addr < curr->rom_addr) {
            break;
        }

        sp30 = curr;
        v1 = addr + len;
        if (v1 <= newvar) {
            curr->unk_0C = D_800A45D8;
            return osVirtualToPhysical(curr->vram_addr + addr - curr->rom_addr);
        }
    }

    curr = gAudioDMAState.tail;
    gAudioDMAState.tail = curr->next;

    alUnlink(curr);
    if (sp30 != NULL) {
        alLink(curr, sp30);
    } else {
        UnkAudioDelta *v0 = gAudioDMAState.head;
        if (v0 != NULL) {
            gAudioDMAState.head = curr;
            curr->next = v0;
            curr->prev = NULL;
            v0->prev = curr;
        } else {
            gAudioDMAState.head = curr;
            curr->next = NULL;
            curr->prev = NULL;
        }
    }

    sp44 = curr->vram_addr;
    sp40 = addr & 1;
    addr -= sp40;
    curr->rom_addr = addr;
    curr->unk_0C = D_800A45D8;

    osInvalDCache(sp44, len);
    osPiStartDma(&gAudioSMAIOMesgBuf[gAudioNextDMA++], OS_MESG_PRI_NORMAL, OS_READ, addr, sp44, 0x80, &D_800A4890);
    return osVirtualToPhysical(sp44) + sp40;
}

ALDMAproc audio_dmanew(AudioDMAState **state) {
    if (!gAudioDMAState.unk_00) {
        gAudioDMAState.head = NULL;
        gAudioDMAState.tail = D_800A4538;
        gAudioDMAState.unk_00 = TRUE;
    }
    *state = &gAudioDMAState;
    return audio_dma;
}

void func_800211B0(void) {
    u32 i;
    OSMesg mesg;
    UnkAudioDelta *curr;
    UnkAudioDelta *next;

    for (i = 0; i < gAudioNextDMA; i++) {
        osRecvMesg(&D_800A4890, &mesg, OS_MESG_NOBLOCK);
    }

    for (curr = gAudioDMAState.head; curr != NULL; curr = next) {
        next = curr->next;
        if (curr->unk_0C + 1 < D_800A45D8) {
            if (curr == gAudioDMAState.head) {
                gAudioDMAState.head = curr->next;
            }
            alUnlink(curr);
            if (gAudioDMAState.tail != NULL) {
                alLink(curr, gAudioDMAState.tail);
            } else {
                gAudioDMAState.tail = curr;
                curr->next = NULL;
                curr->prev = NULL;
            }
        }
    }

    gAudioNextDMA = 0;
    D_800A45D8++;
}

void func_800212C8(void) {
    if (gMusicIsPlaying + gSoundIsPlaying) {
        D_800A45F4 = 0;
        if (func_80020E54(D_80081840.unk_08[D_800A45D8 % 3])) {
            func_800211B0();
        }
    }
}

s32 func_80021338(void) {
    s32 i;

    if (!(gMusicIsPlaying + gSoundIsPlaying)) {
        return 0;
    }

    if (D_800A45F4 != 0) {
        osSendMesg(&gSchedSPTaskQueue, (OSMesg *) &gAudioOsTask, OS_MESG_BLOCK);
    }

    for (i = 0; i < ARRAY_COUNT(gPendingSound); i++) {
        if (gPendingSound[i] >= 0) {
            sound_play(i, gPendingSound[i]);
        }
    }

    return 1;
}

void sound_play(u32 playerID, u32 soundId) {
    ALSndId *soundTable;
    s32 pan;

    if (playerID >= 2) {
        playerID = 2;
    }

    if (soundId < gSfxNumSounds[playerID] && gSfxPlayerOn[playerID]) {
        if (playerID < 2) {
            if (D_800A4524[playerID] != gPlayerInput[playerID].unk_09) {
                D_800A4524[playerID] = gPlayerInput[playerID].unk_09;

                if (D_800A4524[playerID]) {
                    pan = 20;
                } else {
                    pan = 100;
                }

                sound_set_pan(playerID, pan);
            }
        }

        soundTable = gSoundTables[playerID];
        gCurrentSfxPlayer = &gSfxPlayers[playerID];
        alSndpSetSound(gCurrentSfxPlayer, soundTable[soundId]);
        if (alSndpGetState(gCurrentSfxPlayer) != AL_STOPPED) {
            alSndpStop(gCurrentSfxPlayer);
            gPendingSound[playerID] = soundId;
        } else {
            alSndpPlay(gCurrentSfxPlayer);
            gPendingSound[playerID] = -1;
            gSoundIsPlaying = TRUE;
        }
    }
}

void sound_stop_one(u32 playerId, u32 soundId) {
    ALSndId *soundTable;

    if (playerId >= 2) {
        playerId = 2;
    }

    if (soundId < gSfxNumSounds[playerId] && gSfxPlayerOn[playerId]) {
        soundTable = gSoundTables[playerId];
        gCurrentSfxPlayer = &gSfxPlayers[playerId];
        alSndpSetSound(gCurrentSfxPlayer, soundTable[soundId]);
        if (alSndpGetState(gCurrentSfxPlayer) != AL_STOPPED) {
            alSndpStop(gCurrentSfxPlayer);
        }
        gSoundIsPlaying = TRUE; // @bug ? what is the point of it?
    }
}

void sound_stop(s32 playerId) {
    ALSndId *soundTable;
    s32 i;

    if (gSfxPlayerOn[playerId]) {
        soundTable = gSoundTables[playerId];
        gCurrentSfxPlayer = &gSfxPlayers[playerId];

        for (i = gSfxNumSounds[playerId]; i > 0; i--) {
            alSndpSetSound(gCurrentSfxPlayer, soundTable[i - 1]);
            alSndpStop(gCurrentSfxPlayer);
            gSoundStopCounter++;
        }
    }
}

void sound_stop_all(void) {
    s32 playerId;

    if (gSoundIsPlaying) {
        for (playerId = 0; playerId < 3; playerId++) {
            sound_stop(playerId);
        }
    }
}

void music_stop(void) {
    if (gMusicIsPlaying) {
        alSeqpStop(gMusicPlayer);
        gSoundStopCounter++;
    }
}

void func_80021778(Object *obj) {
    if (obj->unk_090[0]-- < 0) {
        obj->currentTask->flags |= 0x80;
    }
}

void audio_fade_out_all(Object *obj, s32 arg1) {
    D_800A460C |= 1;

    if (gSoundIsPlaying && gSoundVolumeFading != 0) {
        gSoundVolumeFading -= 0x7FFF / 27;
        if (gSoundVolumeFading < 0) {
            gSoundVolumeFading = 0;
        }

        if (gSoundVolumeFading == 0) {
            sound_stop_all();
        } else {
            sound_set_volume(0, gSoundVolumeFading);
            sound_set_volume(1, gSoundVolumeFading);
            sound_set_volume(2, gSoundVolumeFading);
        }
    } else if (!gSoundIsPlaying) {
        gSoundVolumeFading = 0;
    }

    if (gMusicIsPlaying && gMusicVolumeFading != 0) {
        gMusicVolumeFading -= 0x7FFF / 27;
        if (gMusicVolumeFading < 0) {
            gMusicVolumeFading = 0;
        }

        if (gMusicVolumeFading == 0) {
            music_stop();
        } else {
            music_set_volume(gMusicVolumeFading);
        }
    } else if (!gMusicIsPlaying) {
        gMusicVolumeFading = 0;
    }

    if (gMusicVolumeFading + gSoundVolumeFading == 0) {
        obj->fn_update = func_80021778;
    }
}

void func_80021918(Object *obj, s32 arg1) {
    s32 v1 = FALSE;

    if (gMusicIsPlaying && gMusicIsPlaying) { // @bug gMusicIsPlaying checked twice
        alSeqpPlay(gMusicPlayer);
        v1 = TRUE;
    }

    obj->unk_090[0]++;
    if (obj->unk_090[0] >= 16 || (D_800A460C & 1)) {
        v1 = TRUE;
    }

    if (v1) {
        obj->flags |= 0x10;
        obj->currentTask->flags |= 0x80;
    }
}

void sound_set_pan(s32 playerId, u8 pan) {
    s32 i;
    ALSndId *tmp;

    if (D_8004A428 != 0 || D_8004A42C) {
        return;
    }

    if (playerId > 2) {
        playerId = 2;
    }

    if (gSfxPlayerOn[playerId]) {
        tmp = gSoundTables[playerId];
        gCurrentSfxPlayer = &gSfxPlayers[playerId];

        for (i = gSfxNumSounds[playerId]; i > 0; i--) {
            alSndpSetSound(gCurrentSfxPlayer, tmp[i - 1]);
            alSndpSetPan(gCurrentSfxPlayer, pan);
        }
    }
}

void sound_set_volume(s32 playerId, s16 volume) {
    s32 i;
    ALSndId *temp;

    if (playerId >= 2) {
        playerId = 2;
    }

    if (gSfxPlayerOn[playerId]) {
        temp = gSoundTables[playerId];
        gCurrentSfxPlayer = &gSfxPlayers[playerId];

        for (i = gSfxNumSounds[playerId]; i > 0; i--) {
            alSndpSetSound(gCurrentSfxPlayer, temp[i - 1]);
            alSndpSetVol(gCurrentSfxPlayer, volume);
        }
    }
}

void music_set_volume(s16 volume) {
    alSeqpSetVol(gMusicPlayer, volume);
}

void sound_init_player(ALBankFile *f, u8 *table, u32 playerId) {
    ALSndId *soundTable;
    ALInstrument *inst;
    u32 i;
    s32 numSounds = 0;
    ALBank *bank;

    if (table == NULL) {
        return;
    }
    if (playerId >= 2) {
        playerId = 2;
    }

    soundTable = gSoundTables[playerId];
    alBnkfNew(f, table);
    bank = f->bankArray[0];
    inst = bank->instArray[0];
    gCurrentSfxPlayer = &gSfxPlayers[playerId];

    for (i = 0, numSounds = 0; i < inst->soundCount; i++) {
        ALSndId soundId;
        ALSound *sound = inst->soundArray[i];

        soundTable[i] = soundId = alSndpAllocate(gCurrentSfxPlayer, sound);
        if (soundId != -1) {
            alSndpSetSound(gCurrentSfxPlayer, soundTable[i]);
            alSndpSetVol(gCurrentSfxPlayer, gSoundVolume);
            numSounds++;
        }
    }

    if (numSounds == inst->soundCount) {
        gSfxNumSounds[playerId] = numSounds;
        gSoundIsPlaying = TRUE;
        gSoundVolumeFading = gSoundVolume;
    } else {
        gSfxNumSounds[playerId] = -1;
    }
}

void func_80021D30(void) {
    D_8004A42C = FALSE;
}
