#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/rdb.h"

extern OSThread __osThreadSave;
extern s32 D_80053D40;
extern s32 D_80053D44;
extern s32 D_80053D48;
extern u8 D_8013EE00[];

void u32_to_string(u32 i, u8 *str) {
    str[0] = (i >> 24) & 0xFF;
    str[1] = (i >> 16) & 0xFF;
    str[2] = (i >> 8) & 0xFF;
    str[3] = i & 0xFF;
}

u32 func_800450E0(u8 *str) {
    u32 i;
    i = (str[0] & 0xff) << 0x18;
    i |= (str[1] & 0xff) << 0x10;
    i |= (str[2] & 0xff) << 0x8;
    i |= (str[3] & 0xff);
    return i;
}

void func_80045138(u8 *s, s32 n) {
    rdbPacket packet;
    s32 i;

    packet.type = 2;
    packet.length = n;

    for (i = 0; i < n; i++) {
        packet.buf[i] = s[i];
    }
    *(vu32 *) RDB_BASE_REG = *(u32 *) &packet;

    while (!(__osGetCause() & CAUSE_IP6)) {
        ;
    }

    *(vu32 *) RDB_READ_INTR_REG = 0;
}

void func_800451F8(u8 *buff, s32 len) {
    s32 i;
    s32 end;
    s32 rem;

    if (!__osRdbWriteOK) {
        while (!(__osGetCause() & CAUSE_IP6)) {
            ;
        }
        *(vu32 *) RDB_READ_INTR_REG = 0;
        __osRdbWriteOK = 1;
    }

    rem = len % 3;
    end = len - rem;
    for (i = 0; i < end; i += 3) {
        func_80045138(&buff[i], 3);
    }
    if (rem > 0) {
        func_80045138(&buff[end], rem);
    }
}

void func_800452D0(void) {
    u8 *addr;
    s32 length;

    addr = (u8 *) func_800450E0(&D_8013EE00[1]);
    length = func_800450E0(&D_8013EE00[5]);
    func_800451F8(addr, length);
}

void func_8004531C(void) {
    func_800451F8((u8 *) &__osThreadSave.context, sizeof(__OSThreadContext));
}

void kdebugserver(u32 arg) {
    u32 i;
    rdbPacket packet;

    *(u32 *) &packet = arg;

    for (i = 0; i < packet.length; i++) {
        D_8013EE00[D_80053D44++] = packet.buf[i];
    }

    D_80053D48 -= packet.length;

    switch (D_80053D40) {
        case 0:
            switch (packet.buf[0]) {
                case 1:
                    D_80053D40 = 1;
                    D_80053D48 = 9 - packet.length;
                    break;
                case 2:
                    func_8004531C();
                    D_80053D40 = 0;
                    D_80053D44 = 0;
                    D_80053D48 = 0;
                    break;
                default:
                    D_80053D40 = 0;
                    D_80053D44 = 0;
                    D_80053D48 = 0;
                    break;
            }
            break;
        case 1:
            if (D_80053D48 <= 0) {
                if (D_8013EE00[0] == 1) {
                    func_800452D0();
                    D_80053D40 = 0;
                    D_80053D44 = 0;
                    D_80053D48 = 0;
                } else {
                    D_80053D40 = 0;
                    D_80053D44 = 0;
                    D_80053D48 = 0;
                }
            }
            break;
        default:
            D_80053D40 = 0;
            D_80053D44 = 0;
            D_80053D48 = 0;
            break;
    }
}
