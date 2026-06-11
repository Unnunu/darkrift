#include "common.h"
#include "task.h"

#define AUDIO_DMA_BUF_SIZE 0x80

typedef struct AudioConfig {
    /* 0x00 */ s32 frequency;
    /* 0x04 */ u32 x_ff7ca549;
    /* 0x08 */ s32 x_af00367e;
} AudioConfig; // size >= 0xC

typedef struct AudioDmaBuf {
    /* 0x00 */ u8 *x_af0aa1f8;
    /* 0x04 */ s16 x_1256da71;
    /* 0x04 */ char x_8b47d6ce[0x60 - 0x6];
    /* 0x60 */ s16 x_b97435d0;
    /* 0x64 */ struct AudioDmaBuf *x_a7753abb;
    /* 0x68 */ s32 x_c42e3970[6];
} AudioDmaBuf; // size = 0x80

typedef struct AudioBufEntry {
    /* 0x00 */ struct AudioBufEntry *next;
    /* 0x04 */ struct AudioBufEntry *prev;
    /* 0x08 */ u32 x_af8b6f61;
    /* 0x0C */ u32 x_b8173ab8;
    /* 0x10 */ u8 *x_2b18f4e7;
} AudioBufEntry; // size = 0x14

typedef struct AudioBufPool {
    /* 0x00 */ u8 x_af0aa1f8;
    /* 0x00 */ struct AudioBufEntry *head;
    /* 0x00 */ struct AudioBufEntry *tail;
} AudioBufPool; // size = 0xC

typedef struct AudioFrameCtx {
    /* 0x00 */ Acmd *x_8d54ede8[2];
    /* 0x08 */ AudioDmaBuf *x_415ed9d6[3];
} AudioFrameCtx;

// .bss

AudioConfig sAudioConfig;
ALSeqPlayer sAlSeqPlayer;
ALSeq sAlSeq;
ALSndPlayer sAlSndPlayers[3];
ALHeap sAlHeap;
AudioFrameCtx sAudioFrameCtx;
char D_80081858[0x220]; // unused
ALGlobals sAlGlobals;
u8 sAudioHeapData[0x22A00];
ALBankFile *sAlBankFile;
s32 sAlBankFileSize;
s32 D_800A44D0; // unused
u8 *sAlSeqData;
s32 sAlSeqSize;
s32 D_800A44DC; // unused
ALSeqMarker sAlSeqMarkerStart;
ALSeqMarker sAlSeqMarkerEnd;
s32 sMusicVolume;
ALSndpConfig sAlSndpConfig;
s32 sAudioUnk1;
s32 sAudioUnk2;
s32 sAudioUnk3; // unused
s32 sSfxVolume;
u8 sSfxPanState[2];
AudioBufPool sAudioBufPool;
AudioBufEntry sAudioBufEntries[8];
u32 sAudioFrameCount;
s32 sAudioDmaPending;
s32 sAudioCmdBufIndex;
u32 sAudioBufMinLen;
u32 sAudioBufLen;
s32 sAudioHeapBufLen;
s32 sAudioCmdBufSize;
s32 sAudioFramesRendered;
s32 sAudioBusy;
s32 sPendingSfxId[3];
u8 sAudioMuteReq;
OSIoMesg sAudioDmaIOMesgs[32];
OSMesgQueue sAudioDmaMQ;
OSMesg sAudioDmaMsgBuf[32];

// .data

u8 sBgmPlaying = FALSE;
u8 sSfxPlaying = FALSE;
u8 sAudioMuted = 0;
u8 sAudioForceMute = FALSE;
s32 D_8004A430 = 0; // unused
AudioDmaBuf *sAudioAiBufPtr = NULL;
AudioConfig *sAudioConfigPtr = &sAudioConfig;
ALSeqPlayer *sAlSeqPlayerPtr = &sAlSeqPlayer;
ALSeq *sAlSeqPtr = &sAlSeq;
ALSndPlayer *sCurSndPlayerPtr = &sAlSndPlayers[0];
s32 sMusicVolumeSetting = 0x7FFF;
ALSndId *sSfxSndIds[3] = { NULL, NULL, NULL };
ALBankFile *gSfxBanks[3] = { NULL, NULL, NULL };
s32 D_8004A464[3] = { 0, 0, 0 }; // unused
u8 gSfxBankLoaded[3] = { FALSE, FALSE, FALSE };
s8 gSfxSoundCount[3] = { -1, -1, -1 };
s32 gSfxVolumeSetting = 0x7FFF;
s32 D_8004A47C = 0; // unused
OSTask sAudioTask = { { M_AUDTASK, 0, NULL, 0, NULL, SP_UCODE_SIZE, NULL, SP_UCODE_DATA_SIZE, NULL, SP_DRAM_STACK_SIZE8,
                        NULL, 0, NULL, 0, NULL, 0 } };

void audio_synth_config(ALSynConfig *);
ALDMAproc audio_get_dma_proc(AudioBufPool **state);
void audio_dma_wait(void);
s32 audio_frame_render(AudioDmaBuf *x_cc1d0de5);
void audio_sfx_set_pan(s32 x_cc1d0de5, u8 x_84ff873b);
void audio_bgm_set_vol(s16 x_cc1d0de5);
void audio_sfx_set_vol(s32 x_cc1d0de5, s16 x_84ff873b);

void audio_ostask_init(void) {
    sAudioTask.t.type = M_AUDTASK;
    sAudioTask.t.ucode_boot = (u64 *) rspbootTextStart;
    sAudioTask.t.ucode_boot_size = (u32) rspbootTextEnd - (u32) rspbootTextStart;
    sAudioTask.t.flags = 0;
    sAudioTask.t.ucode = (u64 *) aspMainTextStart;
    sAudioTask.t.ucode_data = (u64 *) aspMainDataStart;
    sAudioTask.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    sAudioTask.t.dram_stack = NULL;
    sAudioTask.t.dram_stack_size = 0;
    sAudioTask.t.output_buff = NULL;
    sAudioTask.t.output_buff_size = 0;
    sAudioTask.t.yield_data_ptr = NULL;
    sAudioTask.t.yield_data_size = 0;
}

void audio_state_reset(void) {
    sAlBankFileSize = 0;
    sAlSeqData = NULL;
    sAudioUnk1 = 0;
    sAudioUnk2 = 0;
    sAudioFrameCount = 0;
    sAudioDmaPending = 0;
    sAudioCmdBufIndex = 0;
    sAudioMuteReq = 0;
    sPendingSfxId[0] = sPendingSfxId[1] = sPendingSfxId[2] = -1;
    sBgmPlaying = FALSE;
    sSfxPlaying = FALSE;
    sAudioForceMute = FALSE;
    sAudioFramesRendered = sAudioBusy = 0;
    sSfxVolume = gSfxVolumeSetting;
    sMusicVolume = sMusicVolumeSetting;
    sAudioAiBufPtr = NULL;
    audio_ostask_init();
}

void audio_init(void) {
    ALSynConfig x_21359cb5;
    ALSeqpConfig x_de9adec2;
    u32 unused[5];

    alHeapInit(&sAlHeap, sAudioHeapData, sizeof(sAudioHeapData));
    audio_state_reset();

    x_21359cb5.maxVVoices = 42;
    x_21359cb5.maxPVoices = 42;
    x_21359cb5.maxUpdates = 32;
    x_21359cb5.dmaproc = NULL;
    x_21359cb5.fxType = AL_FX_SMALLROOM;
    x_21359cb5.outputRate = 0;
    x_21359cb5.heap = &sAlHeap;

    sAudioConfigPtr->frequency = 11025;
    sAudioConfigPtr->x_ff7ca549 = 1;
    sAudioConfigPtr->x_af00367e = 0x1100;

    audio_synth_config(&x_21359cb5);

    x_de9adec2.maxVoices = 42;
    x_de9adec2.maxEvents = 48;
    x_de9adec2.maxChannels = 16;
    x_de9adec2.heap = &sAlHeap;
    x_de9adec2.initOsc = NULL;
    x_de9adec2.updateOsc = NULL;
    x_de9adec2.stopOsc = NULL;
    x_de9adec2.debugFlags = NO_SOUND_ERR_MASK | NOTE_OFF_ERR_MASK | NO_VOICE_ERR_MASK;
    alSeqpNew(sAlSeqPlayerPtr, &x_de9adec2);

    sAlSndpConfig.maxSounds = 42;
    sAlSndpConfig.maxEvents = 60;
    sAlSndpConfig.heap = &sAlHeap;
    alSndpNew(&sAlSndPlayers[0], &sAlSndpConfig);
    alSndpNew(&sAlSndPlayers[1], &sAlSndpConfig);
    alSndpNew(&sAlSndPlayers[2], &sAlSndpConfig);
    sCurSndPlayerPtr = sAlSndPlayers;
}

void audio_heap_alloc(void) {
    u32 i;

    sAudioBufEntries[0].prev = NULL;
    sAudioBufEntries[0].next = NULL;

    for (i = 0; i < ARRAY_COUNT(sAudioBufEntries) - 1; i++) {
        alLink(&sAudioBufEntries[i + 1], &sAudioBufEntries[i]);
        sAudioBufEntries[i].x_2b18f4e7 = alHeapDBAlloc("audio.c", 238, &sAlHeap, 1, AUDIO_DMA_BUF_SIZE);
    }
    sAudioBufEntries[i].x_2b18f4e7 = alHeapDBAlloc("audio.c", 241, &sAlHeap, 1, AUDIO_DMA_BUF_SIZE);

    for (i = 0; i < ARRAY_COUNT(sAudioFrameCtx.x_8d54ede8); i++) {
        sAudioFrameCtx.x_8d54ede8[i] =
            alHeapDBAlloc("audio.c", 244, &sAlHeap, 1, sAudioConfigPtr->x_af00367e * sizeof(Acmd));
    }

    sAudioCmdBufSize = sAudioConfigPtr->x_af00367e;

    for (i = 0; i < ARRAY_COUNT(sAudioFrameCtx.x_415ed9d6); i++) {
        sAudioFrameCtx.x_415ed9d6[i] = alHeapDBAlloc("audio.c", 250, &sAlHeap, 1, sizeof(AudioDmaBuf));
        sAudioFrameCtx.x_415ed9d6[i]->x_b97435d0 = 2;
        sAudioFrameCtx.x_415ed9d6[i]->x_a7753abb = sAudioFrameCtx.x_415ed9d6[i];
        sAudioFrameCtx.x_415ed9d6[i]->x_af0aa1f8 = alHeapDBAlloc("audio.c", 253, &sAlHeap, 1, sAudioHeapBufLen * 4);
    }

    sAlBankFile = alHeapDBAlloc("audio.c", 255, &sAlHeap, 1, 0x800);

    for (i = 0; i < 3; i++) {
        sSfxSndIds[i] = alHeapDBAlloc("audio.c", 259, &sAlHeap, 1, 30 * sizeof(ALSndId));
        gSfxBanks[i] = alHeapDBAlloc("audio.c", 260, &sAlHeap, 1, 0x1600);
        gSfxBankLoaded[i] = FALSE;
    }
}

void audio_reinit(void) {
    s32 i, j;
    ALSndId *x_cf10d3eb;

    audio_state_reset();

    for (i = 0; i < 3; i++) {
        if (gSfxBankLoaded[i]) {
            x_cf10d3eb = sSfxSndIds[i];
            sCurSndPlayerPtr = &sAlSndPlayers[i];
            for (j = gSfxSoundCount[i]; j > 0; j--) {
                alSndpSetSound(sCurSndPlayerPtr, x_cf10d3eb[j - 1]);
                alSndpDeallocate(sCurSndPlayerPtr, x_cf10d3eb[j - 1]);
            }
            gSfxBankLoaded[i] = FALSE;
            gSfxSoundCount[i] = 0;
        }
    }

    audio_frame_render(sAudioFrameCtx.x_415ed9d6[sAudioFrameCount % 3]);
    audio_dma_wait();
    alClose(&sAlGlobals);
    audio_init();
    rsp_vi_sync(FALSE);
    rsp_vi_sync(FALSE);
    rsp_vi_sync(FALSE);
}

void audio_synth_config(ALSynConfig *config) {
    f32 x_cf10d3eb;

    sAudioBufPool.x_af0aa1f8 = FALSE;
    config->dmaproc = audio_get_dma_proc;
    config->outputRate = osAiSetFrequency(sAudioConfigPtr->frequency);

    x_cf10d3eb = (f32) sAudioConfigPtr->x_ff7ca549 * (f32) config->outputRate / 60.0f;
    sAudioBufLen = (s32) x_cf10d3eb;
    if ((f32) sAudioBufLen < (f32) x_cf10d3eb) {
        sAudioBufLen++;
    }
    if (sAudioBufLen & 0xF) {
        sAudioBufLen = (sAudioBufLen & ~0xF) + 0x10;
    }

    sAudioBufMinLen = sAudioBufLen - 0x10;
    sAudioHeapBufLen = sAudioBufLen + 0x60;

    alInit(&sAlGlobals, config);
    audio_heap_alloc();
    osCreateMesgQueue(&sAudioDmaMQ, sAudioDmaMsgBuf, ARRAY_COUNT(sAudioDmaMsgBuf));
}

s32 audio_frame_render(AudioDmaBuf *x_cc1d0de5) {
    s32 x_4346f5cb;
    Acmd *a1;

    if (sAudioBusy != 0) {
        sAudioBusy = 0;
    }

    x_4346f5cb = osVirtualToPhysical(x_cc1d0de5->x_af0aa1f8);
    if (sAudioAiBufPtr != NULL) {
        osAiSetNextBuffer(sAudioAiBufPtr->x_af0aa1f8, sAudioAiBufPtr->x_1256da71 * 4);
    }

    x_cc1d0de5->x_1256da71 = (sAudioBufLen - osAiGetLength() / 4 + 96) & ~0xF;
    if (x_cc1d0de5->x_1256da71 < sAudioBufMinLen) {
        x_cc1d0de5->x_1256da71 = sAudioBufMinLen;
    }

    a1 = alAudioFrame(sAudioFrameCtx.x_8d54ede8[sAudioCmdBufIndex], &sAudioFramesRendered, x_4346f5cb,
                      x_cc1d0de5->x_1256da71);
    if (sAudioFramesRendered == 0) {
        return FALSE;
    }

    sAudioTask.t.data_ptr = sAudioFrameCtx.x_8d54ede8[sAudioCmdBufIndex];
    sAudioTask.t.data_size = (a1 - sAudioFrameCtx.x_8d54ede8[sAudioCmdBufIndex]) * sizeof(Acmd);

    sAudioAiBufPtr = sAudioFrameCtx.x_415ed9d6[sAudioFrameCount % 3]->x_a7753abb;
    sAudioCmdBufIndex ^= 1;
    return TRUE;
}

s32 audio_dma_callback(s32 addr, s32 len, void *state) {
    u8 *x_fc517ba8;
    s32 x_081c4eef;
    s32 v1;
    s32 x_24aca5c4;
    AudioBufEntry *x_7cdc2f34;
    AudioBufEntry *x_c9614940;

    if (addr < 0) {
        return osVirtualToPhysical(addr);
    }

    x_c9614940 = NULL;
    for (x_7cdc2f34 = sAudioBufPool.head; x_7cdc2f34 != NULL; x_7cdc2f34 = x_7cdc2f34->next) {
        x_24aca5c4 = x_7cdc2f34->x_af8b6f61 + 0x80;
        if (addr < x_7cdc2f34->x_af8b6f61) {
            break;
        }

        x_c9614940 = x_7cdc2f34;
        v1 = addr + len;
        if (v1 <= x_24aca5c4) {
            x_7cdc2f34->x_b8173ab8 = sAudioFrameCount;
            return osVirtualToPhysical(x_7cdc2f34->x_2b18f4e7 + addr - x_7cdc2f34->x_af8b6f61);
        }
    }

    x_7cdc2f34 = sAudioBufPool.tail;
    sAudioBufPool.tail = x_7cdc2f34->next;

    alUnlink(x_7cdc2f34);
    if (x_c9614940 != NULL) {
        alLink(x_7cdc2f34, x_c9614940);
    } else {
        AudioBufEntry *v0 = sAudioBufPool.head;
        if (v0 != NULL) {
            sAudioBufPool.head = x_7cdc2f34;
            x_7cdc2f34->next = v0;
            x_7cdc2f34->prev = NULL;
            v0->prev = x_7cdc2f34;
        } else {
            sAudioBufPool.head = x_7cdc2f34;
            x_7cdc2f34->next = NULL;
            x_7cdc2f34->prev = NULL;
        }
    }

    x_fc517ba8 = x_7cdc2f34->x_2b18f4e7;
    x_081c4eef = addr & 1;
    addr -= x_081c4eef;
    x_7cdc2f34->x_af8b6f61 = addr;
    x_7cdc2f34->x_b8173ab8 = sAudioFrameCount;

    osInvalDCache(x_fc517ba8, len);
    osPiStartDma(&sAudioDmaIOMesgs[sAudioDmaPending++], OS_MESG_PRI_NORMAL, OS_READ, addr, x_fc517ba8, 0x80,
                 &sAudioDmaMQ);
    return osVirtualToPhysical(x_fc517ba8) + x_081c4eef;
}

ALDMAproc audio_get_dma_proc(AudioBufPool **state) {
    if (!sAudioBufPool.x_af0aa1f8) {
        sAudioBufPool.head = NULL;
        sAudioBufPool.tail = sAudioBufEntries;
        sAudioBufPool.x_af0aa1f8 = TRUE;
    }
    *state = &sAudioBufPool;
    return audio_dma_callback;
}

void audio_dma_wait(void) {
    u32 i;
    OSMesg mesg;
    AudioBufEntry *x_7cdc2f34;
    AudioBufEntry *next;

    for (i = 0; i < sAudioDmaPending; i++) {
        osRecvMesg(&sAudioDmaMQ, &mesg, OS_MESG_NOBLOCK);
    }

    for (x_7cdc2f34 = sAudioBufPool.head; x_7cdc2f34 != NULL; x_7cdc2f34 = next) {
        next = x_7cdc2f34->next;
        if (x_7cdc2f34->x_b8173ab8 + 1 < sAudioFrameCount) {
            if (x_7cdc2f34 == sAudioBufPool.head) {
                sAudioBufPool.head = x_7cdc2f34->next;
            }
            alUnlink(x_7cdc2f34);
            if (sAudioBufPool.tail != NULL) {
                alLink(x_7cdc2f34, sAudioBufPool.tail);
            } else {
                sAudioBufPool.tail = x_7cdc2f34;
                x_7cdc2f34->next = NULL;
                x_7cdc2f34->prev = NULL;
            }
        }
    }

    sAudioDmaPending = 0;
    sAudioFrameCount++;
}

void audio_frame_update(void) {
    if (sBgmPlaying + sSfxPlaying) {
        sAudioFramesRendered = 0;
        if (audio_frame_render(sAudioFrameCtx.x_415ed9d6[sAudioFrameCount % 3])) {
            audio_dma_wait();
        }
    }
}

s32 audio_submit_task(void) {
    s32 i;

    if (!(sBgmPlaying + sSfxPlaying)) {
        return 0;
    }

    if (sAudioFramesRendered != 0) {
        osSendMesg(&gRspMessageQueue, (OSMesg *) &sAudioTask, OS_MESG_BLOCK);
    }

    for (i = 0; i < ARRAY_COUNT(sPendingSfxId); i++) {
        if (sPendingSfxId[i] >= 0) {
            audio_sfx_play(i, sPendingSfxId[i]);
        }
    }

    return 1;
}

void audio_sfx_play(u32 x_3a540ba4, u32 x_1dc13257) {
    ALSndId *x_429c730a;
    s32 pan;

    if (x_3a540ba4 >= 2) {
        x_3a540ba4 = 2;
    }

    if (x_1dc13257 < gSfxSoundCount[x_3a540ba4] && gSfxBankLoaded[x_3a540ba4]) {
        if (x_3a540ba4 < 2) {
            if (sSfxPanState[x_3a540ba4] != x_59ce598c[x_3a540ba4].x_d93bcabf) {
                sSfxPanState[x_3a540ba4] = x_59ce598c[x_3a540ba4].x_d93bcabf;

                if (sSfxPanState[x_3a540ba4]) {
                    pan = 20;
                } else {
                    pan = 100;
                }

                audio_sfx_set_pan(x_3a540ba4, pan);
            }
        }

        x_429c730a = sSfxSndIds[x_3a540ba4];
        sCurSndPlayerPtr = &sAlSndPlayers[x_3a540ba4];
        alSndpSetSound(sCurSndPlayerPtr, x_429c730a[x_1dc13257]);
        if (alSndpGetState(sCurSndPlayerPtr) != AL_STOPPED) {
            alSndpStop(sCurSndPlayerPtr);
            sPendingSfxId[x_3a540ba4] = x_1dc13257;
        } else {
            alSndpPlay(sCurSndPlayerPtr);
            sPendingSfxId[x_3a540ba4] = -1;
            sSfxPlaying = TRUE;
        }
    }
}

void audio_sfx_stop(u32 x_30bbe547, u32 x_1dc13257) {
    ALSndId *x_429c730a;

    if (x_30bbe547 >= 2) {
        x_30bbe547 = 2;
    }

    if (x_1dc13257 < gSfxSoundCount[x_30bbe547] && gSfxBankLoaded[x_30bbe547]) {
        x_429c730a = sSfxSndIds[x_30bbe547];
        sCurSndPlayerPtr = &sAlSndPlayers[x_30bbe547];
        alSndpSetSound(sCurSndPlayerPtr, x_429c730a[x_1dc13257]);
        if (alSndpGetState(sCurSndPlayerPtr) != AL_STOPPED) {
            alSndpStop(sCurSndPlayerPtr);
        }
        sSfxPlaying = TRUE; // @bug ? what is the point of it?
    }
}

void audio_sfx_stop_bank(s32 x_30bbe547) {
    ALSndId *x_429c730a;
    s32 i;

    if (gSfxBankLoaded[x_30bbe547]) {
        x_429c730a = sSfxSndIds[x_30bbe547];
        sCurSndPlayerPtr = &sAlSndPlayers[x_30bbe547];

        for (i = gSfxSoundCount[x_30bbe547]; i > 0; i--) {
            alSndpSetSound(sCurSndPlayerPtr, x_429c730a[i - 1]);
            alSndpStop(sCurSndPlayerPtr);
            sAudioBusy++;
        }
    }
}

void audio_sfx_stop_all(void) {
    s32 x_30bbe547;

    if (sSfxPlaying) {
        for (x_30bbe547 = 0; x_30bbe547 < 3; x_30bbe547++) {
            audio_sfx_stop_bank(x_30bbe547);
        }
    }
}

void audio_bgm_stop(void) {
    if (sBgmPlaying) {
        alSeqpStop(sAlSeqPlayerPtr);
        sAudioBusy++;
    }
}

void audio_fade_complete(Object *obj) {
    if (obj->x_0f4167b4[0]-- < 0) {
        TASK_END(obj->currentTask);
    }
}

void audio_fade_out_task(Object *obj, s32 x_84ff873b) {
    sAudioMuteReq |= 1;

    if (sSfxPlaying && sSfxVolume != 0) {
        sSfxVolume -= 0x7FFF / 27;
        if (sSfxVolume < 0) {
            sSfxVolume = 0;
        }

        if (sSfxVolume == 0) {
            audio_sfx_stop_all();
        } else {
            audio_sfx_set_vol(0, sSfxVolume);
            audio_sfx_set_vol(1, sSfxVolume);
            audio_sfx_set_vol(2, sSfxVolume);
        }
    } else if (!sSfxPlaying) {
        sSfxVolume = 0;
    }

    if (sBgmPlaying && sMusicVolume != 0) {
        sMusicVolume -= 0x7FFF / 27;
        if (sMusicVolume < 0) {
            sMusicVolume = 0;
        }

        if (sMusicVolume == 0) {
            audio_bgm_stop();
        } else {
            audio_bgm_set_vol(sMusicVolume);
        }
    } else if (!sBgmPlaying) {
        sMusicVolume = 0;
    }

    if (sMusicVolume + sSfxVolume == 0) {
        obj->x_0232396f = audio_fade_complete;
    }
}

void audio_fade_in_task(Object *obj, s32 unused) {
    s32 x_83bc437e = FALSE;

    if (sBgmPlaying && sBgmPlaying) { // @bug gMusicIsPlaying checked twice
        alSeqpPlay(sAlSeqPlayerPtr);
        x_83bc437e = TRUE;
    }

    obj->x_0f4167b4[0]++;
    if (obj->x_0f4167b4[0] >= 16 || (sAudioMuteReq & 1)) {
        x_83bc437e = TRUE;
    }

    if (x_83bc437e) {
        obj->flags |= x_f51cb721;
        TASK_END(obj->currentTask);
    }
}

void audio_sfx_set_pan(s32 x_30bbe547, u8 pan) {
    s32 i;
    ALSndId *x_cf10d3eb;

    if (sAudioMuted != 0 || sAudioForceMute) {
        return;
    }

    if (x_30bbe547 > 2) {
        x_30bbe547 = 2;
    }

    if (gSfxBankLoaded[x_30bbe547]) {
        x_cf10d3eb = sSfxSndIds[x_30bbe547];
        sCurSndPlayerPtr = &sAlSndPlayers[x_30bbe547];

        for (i = gSfxSoundCount[x_30bbe547]; i > 0; i--) {
            alSndpSetSound(sCurSndPlayerPtr, x_cf10d3eb[i - 1]);
            alSndpSetPan(sCurSndPlayerPtr, pan);
        }
    }
}

void audio_sfx_set_vol(s32 x_30bbe547, s16 volume) {
    s32 i;
    ALSndId *temp;

    if (x_30bbe547 >= 2) {
        x_30bbe547 = 2;
    }

    if (gSfxBankLoaded[x_30bbe547]) {
        temp = sSfxSndIds[x_30bbe547];
        sCurSndPlayerPtr = &sAlSndPlayers[x_30bbe547];

        for (i = gSfxSoundCount[x_30bbe547]; i > 0; i--) {
            alSndpSetSound(sCurSndPlayerPtr, temp[i - 1]);
            alSndpSetVol(sCurSndPlayerPtr, volume);
        }
    }
}

void audio_bgm_set_vol(s16 volume) {
    alSeqpSetVol(sAlSeqPlayerPtr, volume);
}

void wad_setup_sfx_bank(ALBankFile *f, u8 *table, u32 x_30bbe547) {
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

    x_429c730a = sSfxSndIds[x_30bbe547];
    alBnkfNew(f, table);
    bank = f->bankArray[0];
    inst = bank->instArray[0];
    sCurSndPlayerPtr = &sAlSndPlayers[x_30bbe547];

    for (i = 0, x_33944a37 = 0; i < inst->soundCount; i++) {
        ALSndId x_1dc13257;
        ALSound *sound = inst->soundArray[i];

        x_429c730a[i] = x_1dc13257 = alSndpAllocate(sCurSndPlayerPtr, sound);
        if (x_1dc13257 != -1) {
            alSndpSetSound(sCurSndPlayerPtr, x_429c730a[i]);
            alSndpSetVol(sCurSndPlayerPtr, gSfxVolumeSetting);
            x_33944a37++;
        }
    }

    if (x_33944a37 == inst->soundCount) {
        gSfxSoundCount[x_30bbe547] = x_33944a37;
        sSfxPlaying = TRUE;
        sSfxVolume = gSfxVolumeSetting;
    } else {
        gSfxSoundCount[x_30bbe547] = -1;
    }
}

void audio_unmute(void) {
    sAudioForceMute = FALSE;
}
