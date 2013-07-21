#include "queue.h"
#include "shared.h"

int gFront= 0;
int gRear= 0;
QUEUE_TYPE gQueue[QUEUE_SIZE];

void initQueue() {
  gFront = 0;
  gRear = 0;
}

void enqueue(QUEUE_TYPE x) {
  if(gFront == ((gRear + 1)%QUEUE_SIZE))
    gFront = (gFront+ 1) % QUEUE_SIZE;
  gQueue[gRear] = x;
  gRear = (gRear + 1) % QUEUE_SIZE;
}
/*
  Front                                Rear
    |                                   |
    V                                   V
  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
*/

QUEUE_TYPE dequeue() {
  QUEUE_TYPE x;
  x = gQueue[gFront];
  gFront = (gFront+ 1) % QUEUE_SIZE;
  return x;
}

int isQueueEmpty() {
  return gFront == gRear;
}
