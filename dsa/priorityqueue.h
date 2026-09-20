#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#define PRIORITY_QUEUE_MAX 100

typedef struct {
    int data;
    int priority;
} PriorityItem;

typedef struct {
    PriorityItem items[PRIORITY_QUEUE_MAX];
    int size;
} PriorityQueue;

void initPriorityQueue(PriorityQueue* pq);
int isPriorityQueueEmpty(PriorityQueue* pq);
int isPriorityQueueFull(PriorityQueue* pq);
int enqueuePriority(PriorityQueue* pq, int data, int priority);
int dequeuePriority(PriorityQueue* pq, PriorityItem* item);
int peekPriority(PriorityQueue* pq, PriorityItem* item);
void displayPriorityQueue(PriorityQueue* pq);

#ifdef __cplusplus
}
#endif

#endif