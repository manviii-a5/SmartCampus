#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#define QUEUE_MAX 100

typedef struct {
    int data[QUEUE_MAX];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue* queue);
int isQueueEmpty(Queue* queue);
int isQueueFull(Queue* queue);
int enqueue(Queue* queue, int data);
int dequeue(Queue* queue, int* data);
int peekQueue(Queue* queue, int* data);
void displayQueue(Queue* queue);

#ifdef __cplusplus
}
#endif

#endif