#include <stdio.h>
#include <string.h>
#include "stack.h"

void initializeStack(UndoStack *stack)
{
    stack->top = -1;
    stack->size = 0;
}

int isStackEmpty(UndoStack *stack)
{
    return stack->size == 0;
}

int isStackFull(UndoStack *stack)
{
    return stack->size == STACK_MAX;
}

void pushUndo(UndoStack *stack, UndoOperation operation)
{
    /*
        If the stack is full, remove the oldest record.

        Since the stack stores records from bottom to top,
        data[0] is the oldest operation.
    */

    if (isStackFull(stack))
    {
        for (int i = 1; i < STACK_MAX; i++)
        {
            stack->data[i - 1] = stack->data[i];
        }

        stack->top = STACK_MAX - 2;
        stack->size = STACK_MAX - 1;
    }

    stack->top++;
    stack->data[stack->top] = operation;
    stack->size++;
}

UndoOperation popUndo(UndoStack *stack)
{
    UndoOperation emptyOperation;

    emptyOperation.operationId = -1;
    emptyOperation.operationType = -1;
    strcpy(emptyOperation.description, "");

    if (isStackEmpty(stack))
    {
        printf("Undo stack is empty.\n");
        return emptyOperation;
    }

    UndoOperation operation = stack->data[stack->top];

    stack->top--;
    stack->size--;

    return operation;
}

UndoOperation peekUndo(UndoStack *stack)
{
    UndoOperation emptyOperation;

    emptyOperation.operationId = -1;
    emptyOperation.operationType = -1;
    strcpy(emptyOperation.description, "");

    if (isStackEmpty(stack))
    {
        printf("Undo stack is empty.\n");
        return emptyOperation;
    }

    return stack->data[stack->top];
}

void displayUndoStack(UndoStack *stack)
{
    if (isStackEmpty(stack))
    {
        printf("No operations available for undo.\n");
        return;
    }

    printf("\n========== UNDO STACK ==========\n");

    for (int i = stack->top; i >= 0; i--)
    {
        printf("Operation ID : %d\n",
               stack->data[i].operationId);

        printf("Operation Type : %d\n",
               stack->data[i].operationType);

        printf("Description : %s\n",
               stack->data[i].description);

        printf("--------------------------------\n");
    }
}

void clearUndoStack(UndoStack *stack)
{
    stack->top = -1;
    stack->size = 0;
}