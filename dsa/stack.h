#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;
} Stack;

void initStack(Stack* stack);
int isStackEmpty(Stack* stack);
int isStackFull(Stack* stack);
int push(Stack* stack, int data);
int pop(Stack* stack, int* data);
int peek(Stack* stack, int* data);
void displayStack(Stack* stack);

#ifdef __cplusplus
}
#endif

#endif