#include <stdio.h>
#include "priorityqueue.h"

void initPriorityQueue(PriorityQueue* pq)
{
    pq->size = 0;
}

int isPriorityQueueEmpty(PriorityQueue* pq)
{
    return pq->size == 0;
}

int isPriorityQueueFull(PriorityQueue* pq)
{
    return pq->size == PRIORITY_QUEUE_MAX;
}

int enqueuePriority(PriorityQueue* pq, int data, int priority)
{
    if (isPriorityQueueFull(pq))
        return 0;

    int i = pq->size - 1;

    while (i >= 0 && pq->items[i].priority < priority)
    {
        pq->items[i + 1] = pq->items[i];
        i--;
    }

    pq->items[i + 1].data = data;
    pq->items[i + 1].priority = priority;

    pq->size++;

    return 1;
}

int dequeuePriority(PriorityQueue* pq, PriorityItem* item)
{
    if (isPriorityQueueEmpty(pq))
        return 0;

    *item = pq->items[0];

    for (int i = 1; i < pq->size; i++)
    {
        pq->items[i - 1] = pq->items[i];
    }

    pq->size--;

    return 1;
}

int peekPriority(PriorityQueue* pq, PriorityItem* item)
{
    if (isPriorityQueueEmpty(pq))
        return 0;

    *item = pq->items[0];

    return 1;
}

void displayPriorityQueue(PriorityQueue* pq)
{
    if (isPriorityQueueEmpty(pq))
    {
        printf("Priority Queue is empty.\n");
        return;
    }

    printf("Priority Queue:\n");

    for (int i = 0; i < pq->size; i++)
    {
        printf("Data: %d | Priority: %d\n",
               pq->items[i].data,
               pq->items[i].priority);
    }
}