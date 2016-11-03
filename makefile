CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -std=c11 -pthread
OBJS = compressT_LOLS.o functions.o
DEPS = functions.h

all: compress
	rm *.o

memgrind : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compress

memgrind.o: compressT_LOLS.c
	$(CC) $(CFLAGS) -c compressT_LOLS.c

mymalloc.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm compress
