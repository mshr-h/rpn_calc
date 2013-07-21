#include "stack.h"

int gSNum = 0;
STACK_TYPE gStack[STACK_SIZE];

void initStack() {
  gSNum = 0;
}

STACK_TYPE pop() {
  STACK_TYPE x;
  x = gStack[gSNum - 1];
  gSNum--;
  return x;
}

void push(STACK_TYPE x) {
  gStack[gSNum++] = x;
}
