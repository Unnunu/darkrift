#include "task.h"

u8 x_66c4e9c7 = FALSE;

x_b57dc591 x_30839b82;

void x_bbe35044(x_41a0e1e6 *list) {
    x_41a0e1e6 *ptr;
    x_41a0e1e6 *next;

    for (ptr = list; ptr != NULL; ptr = next) {
        next = ptr->next;
        x_48825d30(x_30839b82, ptr);
    }
}

void x_c0a431f7(Object *obj) {
    x_41a0e1e6 *task;
    x_c305712a *stack;
    s16 flags;

    task = obj->x_d178c88f;

    if (x_66c4e9c7) {
        return;
    }

    while (task != NULL) {
        obj->x_64946db0 = task;
        flags = task->flags;

        if (((flags & x_09809fad) && obj->x_5fcb1654 >= task->x_8a242a5a) ||
            ((flags & x_c6236507) && task->x_8a242a5a < (x_e3a9f332 & 0xFFFF)) ||
            ((flags & x_04b7a0c6) && (flags & x_2612575e))) {
            x_c305712a *slot = &task->x_bda3dc45;

            if (slot->flags & x_a3cbfe49) {
                // push active task on stack
                task->stack[task->x_116c9ff3].x_f6382727 = task->x_f6382727;
                task->stack[task->x_116c9ff3].x_c7f843c2 = task->x_c7f843c2;
                task->stack[task->x_116c9ff3].flags = task->flags;
                task->x_116c9ff3++;
            } else {
                task->x_116c9ff3 = 0;
            }
            task->x_f6382727 = slot->x_f6382727;
            task->flags = slot->flags;
            task->x_c7f843c2 = slot->x_c7f843c2;
        }

        if (flags & x_d8bfe182) {
            // pop task from stack
            stack = task->stack;
            if (task->x_116c9ff3 != 0) {
                task->x_116c9ff3--;
                task->x_f6382727 = (stack + task->x_116c9ff3)->x_f6382727;
                task->flags = (stack + task->x_116c9ff3)->flags;
                task->x_c7f843c2 = (stack + task->x_116c9ff3)->x_c7f843c2;
            } else {
                task->flags &= ~x_d8bfe182;
                task->x_c7f843c2 = -1;
                continue;
            }
        }

        if (task->x_c7f843c2 != 0) {
            if (task->x_c7f843c2 < 0) {
                task = task->next;
            } else {
                task->x_c7f843c2--;
                task = task->next;
            }
        } else {
            if (task->flags & x_0fb55613) {
                task->x_f6382727(obj);
            }
            task = task->next;
        }
    }
}

x_41a0e1e6 *x_52c4e4a9(x_41a0e1e6 *x_cc1d0de5, s16 id) {
    x_41a0e1e6 *ptr;
    for (ptr = x_cc1d0de5; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == id) {
            return ptr;
        }
    }
}

x_41a0e1e6 *x_20a23ba4(Object *obj, void (*x_f6382727)(Object *), s16 flags) {
    x_41a0e1e6 *prev;
    x_41a0e1e6 *x_7cdc2f34;
    x_41a0e1e6 *x_04972722;

    x_7cdc2f34 = obj->x_d178c88f;
    x_04972722 = (x_41a0e1e6 *) x_6d619dce(x_30839b82);

    while (x_7cdc2f34 != NULL) {
        prev = x_7cdc2f34;
        x_7cdc2f34 = x_7cdc2f34->next;
    }

    prev->next = x_04972722;
    x_04972722->next = NULL;

    x_04972722->id = prev->id + 1;
    x_04972722->x_116c9ff3 = 0;
    x_04972722->x_f6382727 = x_f6382727;
    x_04972722->flags = flags;
    x_04972722->x_c7f843c2 = 0;

    return x_04972722;
}

void x_0ae6735d(Object *obj) {
    x_5e6f40dd(obj->x_64946db0);
}
