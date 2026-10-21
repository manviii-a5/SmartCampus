
#ifdef __cplusplus
extern "C" {
#endif
#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_MAX 50

typedef struct
{
    int bookingId;
    long long requesterId;
    int requesterType;   // 1 = Student, 2 = Faculty
} BookingRequest;

typedef struct
{
    BookingRequest data[QUEUE_MAX];
    int front;
    int rear;
    int size;
} BookingQueue;

void initializeQueue(BookingQueue *q);

int isQueueEmpty(BookingQueue *q);

int isQueueFull(BookingQueue *q);

void enqueue(BookingQueue *q, BookingRequest request);

BookingRequest dequeue(BookingQueue *q);

BookingRequest peekQueue(BookingQueue *q);

void displayQueue(BookingQueue *q);

#endif
#ifdef __cplusplus
}
#endif
