#ifndef _COMMON_H
#define _COMMON_H

#include "ultra64.h"
#include "macros.h"
#include "common_structs.h"
#include "functions.h"
#include "variables.h"

// TODO find better place

#define INP_LTRIG 0x0001
#define INP_A 0x0002
#define INP_RTRIG 0x0004
#define INP_B 0x0008

#define INP_CUP 0x0010
#define INP_CRIGHT 0x0020
#define INP_CDOWN 0x0040
#define INP_CLEFT 0x0080

#define INP_ZTRIG 0x0100
#define INP_START 0x0800

#define INP_UP 0x1000
#define INP_RIGHT 0x2000
#define INP_DOWN 0x4000
#define INP_LEFT 0x8000

typedef u8 Addr[];

#endif
