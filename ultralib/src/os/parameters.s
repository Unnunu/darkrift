#include "PR/R4300.h"
#include "sys/asm.h"
#include "sys/regdef.h"

.text
ABS(leoBootID, 0x800001a0)
ABS(osTvType, 0x80000300)
ABS(osRomType, 0x80000304)
ABS(osRomBase, 0x80000308)
ABS(osResetType, 0x8000030c)
ABS(osCicId, 0x80000310)
ABS(osVersion, 0x80000314)
ABS(osMemSize, 0x80000318)
ABS(osAppNMIBuffer, 0x8000031c)

#ifdef LIBULTRA_DARK_RIFT
.space 0x40
/* padded to 0x40 in the object file */
#else
.space 0x60
/* padded to 0x60 in the object file */
#endif
