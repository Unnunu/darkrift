#ifndef _TASK_H
#define _TASK_H
#include "common.h"

enum TaskFlags {
    TASK_FLAG_ENABLED = 1 << 0,
    TASK_FLAG_2 = 1 << 1,
    TASK_FLAG_FRAME_TRIGGER = 1 << 2,
    TASK_FLAG_TIME_TRIGGER = 1 << 3,
    TASK_FLAG_10 = 1 << 4,
    TASK_FLAG_20 = 1 << 5,
    TASK_FLAG_CALL = 1 << 6,
    TASK_FLAG_END = 1 << 7
};

#define TASK_END(task) (task)->flags |= TASK_FLAG_END

extern u8 gIsPaused;
extern ItemPool gTaskPool;

void task_clear(ObjectTask *list);
void task_execute(Object *obj);
ObjectTask *task_add(Object *obj, void (*func)(Object *), s16 flags);
void task_default_func(Object *obj);

#endif
