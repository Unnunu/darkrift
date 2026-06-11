#ifndef x_6dbe68f0
#define x_6dbe68f0
#include "common.h"

enum TaskFlags {
    TASK_RUNNABLE = 0x1,
    TASK_TIME_BASED = 0x4,
    TASK_FRAME_BASED = 0x8,
    TASK_FLAG_10 = 0x10,
    TASK_FLAG_20 = 0x20,
    TASK_SAVE_STACK = 0x40,
    TASK_POP = 0x80
};

#define TASK_END(task) (task)->flags |= TASK_POP

extern u8 gTaskLock;
extern x_b57dc591 gTaskPool;

void task_free_list(TaskNode *list);
void task_execute(Object *obj);
TaskNode *task_append(Object *obj, void (*callback)(Object *), s16 flags);
void task_remove_current(Object *obj);

#endif
