#include <stdio.h>
#include "stack.h"

void initStack(Stack* stack)
{
    stack->top = -1;
}

int isStackEmpty(Stack* stack)
{
    return stack->top == -1;
}

int isStackFull(Stack* stack)
{
    return stack->top == STACK_MAX - 1;
}

int push(Stack* stack, int data)
{
    if (isStackFull(stack))
        return 0;

    stack->data[++stack->top] = data;

    return 1;
}

int pop(Stack* stack, int* data)
{
    if (isStackEmpty(stack))
        return 0;

    *data = stack->data[stack->top--];

    return 1;
}

int peek(Stack* stack, int* data)
{
    if (isStackEmpty(stack))
        return 0;

    *data = stack->data[stack->top];

    return 1;
}

void displayStack(Stack* stack)
{
    if (isStackEmpty(stack))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack (Top -> Bottom): ");

    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d ", stack->data[i]);
    }

    printf("\n");
}