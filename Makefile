CC = gcc
CFLAGS = -Wall -c
all: rpn_calc

rpn_calc: main.o stack.o evalscheme.o queue.o
	$(CC) -o $@ $^ -lm -lncursesw

.o:.c
	$(CC) $(CFLAGS) $<

.c:.h

clean:
	rm rpn_calc *.o history.txt
