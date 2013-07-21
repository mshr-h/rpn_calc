#include "shared.h"
#define QUEUE_SIZE 11

typedef struct _str {
  char s[SCHEME_SIZE];
} STRING;
typedef STRING QUEUE_TYPE;

void initQueue();
void enqueue(QUEUE_TYPE x);
QUEUE_TYPE dequeue();
int isQueueEmpty();
