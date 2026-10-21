#ifdef __cplusplus
extern "C" {
#endif
#ifndef STACK_H
#define STACK_H

#define STACK_MAX 50

typedef struct
{
    int operationId;
    int operationType;
    char description[200];
} UndoOperation;

typedef struct
{
    UndoOperation data[STACK_MAX];
    int top;
    int size;
} UndoStack;

void initializeStack(UndoStack *stack);

int isStackEmpty(UndoStack *stack);

int isStackFull(UndoStack *stack);

void pushUndo(UndoStack *stack, UndoOperation operation);

UndoOperation popUndo(UndoStack *stack);

UndoOperation peekUndo(UndoStack *stack);

void displayUndoStack(UndoStack *stack);

void clearUndoStack(UndoStack *stack);

#endif
#ifdef __cplusplus
}
#endif