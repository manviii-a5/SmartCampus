#include <assert.h>
#include <stdio.h>
#include "queue.h"
int main(void){
 BookingQueue q; initializeQueue(&q); assert(isQueueEmpty(&q));
 BookingRequest empty=dequeue(&q); assert(empty.bookingId==-1);
 for(int i=1;i<=QUEUE_MAX;i++){ BookingRequest r={i,1000+i,1}; enqueue(&q,r); }
 assert(isQueueFull(&q)); assert(peekQueue(&q).bookingId==1);
 BookingRequest first=dequeue(&q); assert(first.bookingId==1);
 BookingRequest r={QUEUE_MAX+1,2000,2}; enqueue(&q,r);
 for(int i=2;i<=QUEUE_MAX+1;i++){ BookingRequest got=dequeue(&q); assert(got.bookingId==i); }
 assert(isQueueEmpty(&q)); puts("PASS: Queue tests"); return 0;
}
