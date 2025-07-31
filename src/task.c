#include "task.h"

u8 gTasksDisabled = FALSE;

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
    GlobalObjBSub *stack;
    s16 flags;

    task = obj->taskList;

    if (gTasksDisabled) {
        return;
    }

    while (task != NULL) {
        obj->currentTask = task;
        flags = task->flags;

        if (((flags & 4) && obj->unk_084 >= task->unk_86) || ((flags & 8) && task->unk_86 < (gFrameCounter & 0xFFFF)) ||
            ((flags & 0x10) && (flags & 0x20))) {
            GlobalObjBSub *unk_90 = &task->unk_90;

            if (unk_90->flags & 0x40) {
                // push active task on stack
                task->stack[task->stackPos].func = task->func;
                task->stack[task->stackPos].counter = task->counter;
                task->stack[task->stackPos].flags = task->flags;
                task->stackPos++;
            } else {
                task->stackPos = 0;
            }
            task->func = unk_90->func;
            task->flags = unk_90->flags;
            task->counter = unk_90->counter;
        }

        if (flags & 0x80) {
            // pop task from stack
            stack = task->stack;
            if (task->stackPos != 0) {
                task->stackPos--;
                task->func = (stack + task->stackPos)->func;
                task->flags = (stack + task->stackPos)->flags;
                task->counter = (stack + task->stackPos)->counter;
            } else {
                task->flags &= ~0x80;
                task->counter = -1;
                continue;
            }
        }

        if (task->counter != 0) {
            if (task->counter < 0) {
                task = task->next;
            } else {
                task->counter--;
                task = task->next;
            }
        } else {
            if (task->flags & 1) {
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
    newTask->counter = 0;

    return newTask;
}

void task_default_func(Object *obj) {
    obj->currentTask->flags |= 0x80;
}
