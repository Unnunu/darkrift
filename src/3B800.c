#include "common.h"

void alSeqGetLoc(ALSeq *seq, ALSeqMarker *m)
{
    m->curPtr = seq->curPtr;
    m->lastStatus = seq->lastStatus;
    m->lastTicks = seq->lastTicks;
}

void alSeqSetLoc(ALSeq *seq, ALSeqMarker *m)
{
    seq->curPtr     = m->curPtr;
    seq->lastStatus = m->lastStatus;
    seq->lastTicks  = m->lastTicks;
}

s32 alSeqGetTicks(ALSeq *seq)
{
    return seq->lastTicks;
}

void func_8003AC40(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/readVarLen.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/alSeqNextEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/alSeqNewMarker.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/alSeqSecToTicks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/alSeqTicksToSec.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/__alSeqNextDelta.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/read32.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/read16.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3B800/alSeqNew.s")
