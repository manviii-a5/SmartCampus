#include <stdio.h>
#include "queue.h"

void initializeQueue(BookingQueue *q)
{
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isQueueEmpty(BookingQueue *q)
{
    return q->size == 0;
}

int isQueueFull(BookingQueue *q)
{
    return q->size == QUEUE_MAX;
}

void enqueue(BookingQueue *q, BookingRequest request)
{
    if (isQueueFull(q))
    {
        printf("Booking queue is full.\n");
        return;
    }

    q->rear = (q->rear + 1) % QUEUE_MAX;
    q->data[q->rear] = request;
    q->size++;
}

BookingRequest dequeue(BookingQueue *q)
{
    BookingRequest emptyRequest = {-1, -1, -1};

    if (isQueueEmpty(q))
    {
        printf("Booking queue is empty.\n");
        return emptyRequest;
    }

    BookingRequest request = q->data[q->front];

    q->front = (q->front + 1) % QUEUE_MAX;
    q->size--;

    return request;
}

BookingRequest peekQueue(BookingQueue *q)
{
    BookingRequest emptyRequest = {-1, -1, -1};

    if (isQueueEmpty(q))
    {
        printf("Booking queue is empty.\n");
        return emptyRequest;
    }

    return q->data[q->front];
}

void displayQueue(BookingQueue *q)
{
    if (isQueueEmpty(q))
    {
        printf("Booking queue is empty.\n");
        return;
    }

    int index = q->front;

    printf("\n--- Booking Queue ---\n");

    for (int i = 0; i < q->size; i++)
    {
        printf("Booking ID: %d | Requester ID: %lld | Type: %s\n",
               q->data[index].bookingId,
               q->data[index].requesterId,
               q->data[index].requesterType == 1 ? "Student" : "Faculty");

        index = (index + 1) % QUEUE_MAX;
    }
}