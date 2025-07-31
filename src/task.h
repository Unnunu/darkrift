#ifndef _TASK_H
#define _TASK_H
#include "common.h"

extern u8 gTasksDisabled;
extern ItemPool gTaskPool;

void task_clear(ObjectTask *list);
void task_execute(Object *obj);
ObjectTask *task_add(Object *obj, void (*func)(Object *), s16 flags);
void task_default_func(Object *obj);

#endif
