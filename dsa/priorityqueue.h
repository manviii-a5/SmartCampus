
#ifdef __cplusplus
extern "C" {
#endif
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#define PRIORITY_QUEUE_MAX 100

typedef struct
{
    int emergencyId;
    long long reporterId;
    int priority;
} EmergencyRequest;

typedef struct
{
    EmergencyRequest data[PRIORITY_QUEUE_MAX];
    int size;
} EmergencyPriorityQueue;

void initializePriorityQueue(EmergencyPriorityQueue *pq);

int isPriorityQueueEmpty(EmergencyPriorityQueue *pq);

int isPriorityQueueFull(EmergencyPriorityQueue *pq);

void enqueueEmergency(EmergencyPriorityQueue *pq,
                      EmergencyRequest emergency);

EmergencyRequest dequeueEmergency(EmergencyPriorityQueue *pq);

EmergencyRequest peekEmergency(EmergencyPriorityQueue *pq);

void displayEmergencyQueue(EmergencyPriorityQueue *pq);

#endif
#ifdef __cplusplus
}
#endif
