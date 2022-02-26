CC = gcc
CFLAGS  = -Wall
DEPS  = Both.h

all:	Insort.o	QuickThreshold1.o	QuickThreshold10.o	QuickThreshold100.o	Both.o	Insort	QuickThreshold1	QuickThreshold10	QuickThreshold100 clean

Insort.o:	Insort.c
	$(CC)	$(CFLAGS)	-o	Insort.o	-c Insort.c	-lm

QuickThreshold1.o:	Quicksort.c
	$(CC)	$(CFLAGS)	-o	QuickThreshold1.o	-c	Quicksort.c	-lm	-DTHRESHOLD=1

QuickThreshold10.o:	Quicksort.c
	$(CC)	$(CFLAGS)	-o	QuickThreshold10.o	-c	Quicksort.c	-lm	-DTHRESHOLD=10

QuickThreshold100.o:	Quicksort.c
	$(CC)	$(CFLAGS)	-o	QuickThreshold100.o	-c	Quicksort.c	-lm	-DTHRESHOLD=100

Both.o:	Both.c
	$(CC)	$(CFLAGS)	-c	Both.c

Insort:	Insort.o	Both.o
	$(CC)	$(CFLAGS)	-o	Insort	Insort.o	Both.o	-lm

QuickThreshold1:	QuickThreshold1.o	Both.o
	$(CC)	$(CFLAGS)	-o	QuickThreshold1	QuickThreshold1.o	Both.o	-lm

QuickThreshold10:	QuickThreshold10.o	Both.o
	$(CC)	$(CFLAGS)	-o	QuickThreshold10	QuickThreshold10.o	Both.o	-lm

QuickThreshold100:	QuickThreshold100.o	Both.o
	$(CC)	$(CFLAGS)	-o	QuickThreshold100	QuickThreshold100.o	Both.o	-lm
clean:
	$(RM)	*.o
