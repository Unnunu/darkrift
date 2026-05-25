#ifndef _TASK_H
#define _TASK_H
#include "common.h"

enum TaskFlags {
    TASK_FLAG_ENABLED = 0x1,
    TASK_FLAG_TRIGGER_FRAME = 0x4,
    TASK_FLAG_TRIGGER_TIME = 0x8,
    TASK_FLAG_10 = 0x10,
    TASK_FLAG_20 = 0x20,
    TASK_FLAG_PREEMPT = 0x40,
    TASK_FLAG_END = 0x80
};

#define TASK_END(task) (task)->flags |= TASK_FLAG_END

extern u8 gIsPaused;
extern ItemPool gTaskPool;

void task_clear(ObjectTask *list);
void task_execute(Object *obj);
ObjectTask *task_add(Object *obj, void (*func)(Object *), s16 flags);
void task_default_func(Object *obj);

#endif
