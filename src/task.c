#include "task.h"

u8 gIsPaused = FALSE;

ItemPool gTaskPool;

void task_clear(ObjectTask *list) {
    ObjectTask *ptr;
    ObjectTask *next;

    for (ptr = list; ptr != NULL; ptr = next) {
        next = ptr->next;
        RELEASE_ITEM(gTaskPool, ptr);
    }
}

void task_execute(Object *obj) {
    ObjectTask *task;
    TaskContext *stack;
    s16 flags;

    task = obj->taskList;

    if (gIsPaused) {
        return;
    }

    while (task != NULL) {
        obj->currentTask = task;
        flags = task->flags;

        if (((flags & TASK_FLAG_FRAME_TRIGGER) && obj->frameIndex >= task->unk_86) ||
            ((flags & TASK_FLAG_TIME_TRIGGER) && task->unk_86 < (gFrameCounter & 0xFFFF)) ||
            ((flags & TASK_FLAG_10) && (flags & TASK_FLAG_20))) {
            TaskContext *conditional_context = &task->conditional_context;

            if (conditional_context->flags & TASK_FLAG_CALL) {
                // push active task on stack
                task->stack[task->stackPos].func = task->func;
                task->stack[task->stackPos].start_delay = task->start_delay;
                task->stack[task->stackPos].flags = task->flags;
                task->stackPos++;
            } else {
                task->stackPos = 0;
            }
            task->func = conditional_context->func;
            task->flags = conditional_context->flags;
            task->start_delay = conditional_context->start_delay;
        }

        if (flags & TASK_FLAG_END) {
            // pop task from stack
            stack = task->stack;
            if (task->stackPos != 0) {
                task->stackPos--;
                task->func = (stack + task->stackPos)->func;
                task->flags = (stack + task->stackPos)->flags;
                task->start_delay = (stack + task->stackPos)->start_delay;
            } else {
                task->flags &= ~TASK_FLAG_END;
                task->start_delay = -1;
                continue;
            }
        }

        if (task->start_delay != 0) {
            if (task->start_delay < 0) {
                task = task->next;
            } else {
                task->start_delay--;
                task = task->next;
            }
        } else {
            if (task->flags & TASK_FLAG_ENABLED) {
                task->func(obj);
            }
            task = task->next;
        }
    }
}

ObjectTask *task_get(ObjectTask *arg0, s16 id) {
    ObjectTask *ptr;
    for (ptr = arg0; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == id) {
            return ptr;
        }
    }
}

ObjectTask *task_add(Object *obj, void (*func)(Object *), s16 flags) {
    ObjectTask *prev;
    ObjectTask *curr;
    ObjectTask *newTask;

    curr = obj->taskList;
    newTask = (ObjectTask *) GET_ITEM(gTaskPool);

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = newTask;
    newTask->next = NULL;

    newTask->id = prev->id + 1;
    newTask->stackPos = 0;
    newTask->func = func;
    newTask->flags = flags;
    newTask->start_delay = 0;

    return newTask;
}

void task_default_func(Object *obj) {
    TASK_END(obj->currentTask);
}
