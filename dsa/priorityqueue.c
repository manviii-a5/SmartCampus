#include <stdio.h>
#include "priorityqueue.h"

void initializePriorityQueue(EmergencyPriorityQueue *pq)
{
    pq->size = 0;
}

int isPriorityQueueEmpty(EmergencyPriorityQueue *pq)
{
    return pq->size == 0;
}

int isPriorityQueueFull(EmergencyPriorityQueue *pq)
{
    return pq->size == PRIORITY_QUEUE_MAX;
}

void enqueueEmergency(EmergencyPriorityQueue *pq,
                      EmergencyRequest emergency)
{
    if (isPriorityQueueFull(pq))
    {
        printf("Emergency queue is full.\n");
        return;
    }

    int position = pq->size;

    /*
       Larger priority value means higher priority.

       4 = Critical
       3 = High
       2 = Medium
       1 = Low

       We insert after existing emergencies having
       the same priority, preserving FIFO.
    */

    while (position > 0 &&
           pq->data[position - 1].priority < emergency.priority)
    {
        pq->data[position] = pq->data[position - 1];
        position--;
    }

    pq->data[position] = emergency;
    pq->size++;
}

EmergencyRequest dequeueEmergency(EmergencyPriorityQueue *pq)
{
    EmergencyRequest emptyRequest = {-1, -1, -1};

    if (isPriorityQueueEmpty(pq))
    {
        printf("Emergency queue is empty.\n");
        return emptyRequest;
    }

    EmergencyRequest emergency = pq->data[0];

    for (int i = 1; i < pq->size; i++)
    {
        pq->data[i - 1] = pq->data[i];
    }

    pq->size--;

    return emergency;
}

EmergencyRequest peekEmergency(EmergencyPriorityQueue *pq)
{
    EmergencyRequest emptyRequest = {-1, -1, -1};

    if (isPriorityQueueEmpty(pq))
    {
        printf("Emergency queue is empty.\n");
        return emptyRequest;
    }

    return pq->data[0];
}

void displayEmergencyQueue(EmergencyPriorityQueue *pq)
{
    if (isPriorityQueueEmpty(pq))
    {
        printf("Emergency queue is empty.\n");
        return;
    }

    printf("\n--- Emergency Priority Queue ---\n");

    for (int i = 0; i < pq->size; i++)
    {
        const char *priority;

        switch (pq->data[i].priority)
        {
            case 4:
                priority = "CRITICAL";
                break;

            case 3:
                priority = "HIGH";
                break;

            case 2:
                priority = "MEDIUM";
                break;

            default:
                priority = "LOW";
        }

        printf("Emergency ID: %d | Reporter: %lld | Priority: %s\n",
               pq->data[i].emergencyId,
               pq->data[i].reporterId,
               priority);
    }
}