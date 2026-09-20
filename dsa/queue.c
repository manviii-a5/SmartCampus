#include <stdio.h>
#include "queue.h"

void initQueue(Queue* queue)
{
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

int isQueueEmpty(Queue* queue)
{
    return queue->size == 0;
}

int isQueueFull(Queue* queue)
{
    return queue->size == QUEUE_MAX;
}

int enqueue(Queue* queue, int data)
{
    if (isQueueFull(queue))
        return 0;

    queue->rear = (queue->rear + 1) % QUEUE_MAX;
    queue->data[queue->rear] = data;
    queue->size++;

    return 1;
}

int dequeue(Queue* queue, int* data)
{
    if (isQueueEmpty(queue))
        return 0;

    *data = queue->data[queue->front];

    queue->front = (queue->front + 1) % QUEUE_MAX;
    queue->size--;

    return 1;
}

int peekQueue(Queue* queue, int* data)
{
    if (isQueueEmpty(queue))
        return 0;

    *data = queue->data[queue->front];

    return 1;
}

void displayQueue(Queue* queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue (Front -> Rear): ");

    int index = queue->front;

    for (int i = 0; i < queue->size; i++)
    {
        printf("%d ", queue->data[index]);
        index = (index + 1) % QUEUE_MAX;
    }

    printf("\n");
}