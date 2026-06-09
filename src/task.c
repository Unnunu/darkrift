#include "task.h"

u8 gTaskLock = FALSE;

x_b57dc591 gTaskPool;

/**
 * task_free_list - Free all task nodes in a linked list back to the pool allocator.
 * Iterates through the list and calls pool free (x_48825d30) on each node.
 * Params: list - head of task linked list
 */
void task_free_list(TaskNode *list) {
    TaskNode *ptr;
    TaskNode *next;

    for (ptr = list; ptr != NULL; ptr = next) {
        next = ptr->next;
        x_48825d30(gTaskPool, ptr);
    }
}

/**
 * task_execute - Core task scheduler dispatcher for an Object.
 * Iterates the object's task list, handles push/pop substate stack,
 * delay counters, and executes runnable callbacks.
 * If global lock (gTaskLock) is set, returns immediately.
 * Push conditions: time-based (TASK_TIME_BASED), frame-based (TASK_FRAME_BASED),
 * or forced push (TASK_PUSH | TASK_FORCE_PUSH).
 * Pop flag (TASK_POP) restores previous state from stack.
 * Runnable flag (TASK_RUNNABLE) triggers callback execution.
 * Params: obj - Object whose task list to process
 */
void task_execute(Object *obj) {
    TaskNode *task;
    FsmState *stack;
    s16 flags;

    task = obj->taskListHead;

    if (gTaskLock) {
        return;
    }

    while (task != NULL) {
        obj->currentTask = task;
        flags = task->flags;

        if (((flags & TASK_TIME_BASED) && obj->frameCounter >= task->triggerTime) ||
            ((flags & TASK_FRAME_BASED) && task->triggerTime < (gFrameCounter & 0xFFFF)) ||
            ((flags & TASK_PUSH) && (flags & TASK_FORCE_PUSH))) {
            FsmState *slot = &task->pushState;

            if (slot->flags & TASK_SAVE_STACK) {
                // push active task on stack
                task->stack[task->stackPtr].callback = task->callback;
                task->stack[task->stackPtr].delay = task->delay;
                task->stack[task->stackPtr].flags = task->flags;
                task->stackPtr++;
            } else {
                task->stackPtr = 0;
            }
            task->callback = slot->callback;
            task->flags = slot->flags;
            task->delay = slot->delay;
        }

        if (flags & TASK_POP) {
            // pop task from stack
            FsmState *stack = task->stack;
            if (task->stackPtr != 0) {
                task->stackPtr--;
                task->callback = (stack + task->stackPtr)->callback;
                task->flags = (stack + task->stackPtr)->flags;
                task->delay = (stack + task->stackPtr)->delay;
            } else {
                task->flags &= ~TASK_POP;
                task->delay = -1;
                continue;
            }
        }

        if (task->delay != 0) {
            if (task->delay < 0) {
                task = task->next;
            } else {
                task->delay--;
                task = task->next;
            }
        } else {
            if (task->flags & TASK_RUNNABLE) {
                task->callback(obj);
            }
            task = task->next;
        }
    }
}

/**
 * task_find_by_id - Linear search for a task by ID in a linked list.
 * Returns pointer to task if found, otherwise falls through (no explicit NULL return).
 * Params: head - head of task list, id - task ID to find
 * Returns: TaskNode* - matching task or undefined if not found
 */
TaskNode *task_find_by_id(TaskNode *head, s16 id) {
    TaskNode *ptr;
    for (ptr = head; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == id) {
            return ptr;
        }
    }
}

/**
 * task_append - Allocate and append a new task to an Object's task list.
 * Pulls from pool allocator (x_6d619dce), appends to end of list,
 * assigns auto-incrementing ID, initializes stack pointer, callback, flags, delay.
 * Params: obj - parent Object, callback - callback function, flags - task flags
 * Returns: TaskNode* - newly created task node
 */
TaskNode *task_append(Object *obj, void (*callback)(Object *), s16 flags) {
    TaskNode *prev;
    TaskNode *curr;
    TaskNode *newTask;

    curr = obj->taskListHead;
    newTask = (TaskNode *) x_6d619dce(gTaskPool);

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = newTask;
    newTask->next = NULL;

    newTask->id = prev->id + 1;
    newTask->stackPtr = 0;
    newTask->callback = callback;
    newTask->flags = flags;
    newTask->delay = 0;

    return newTask;
}

/**
 * task_remove_current - Mark the currently executing task for pop/removal.
 * Sets the pop flag (TASK_POP) on the current task via TASK_END macro.
 * Called from task callbacks to signal completion/transition.
 * Params: obj - parent Object (current task in obj->currentTask)
 */
void task_remove_current(Object *obj) {
    TASK_END(obj->currentTask);
}
