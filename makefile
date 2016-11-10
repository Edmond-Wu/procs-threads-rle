CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -pthread -std=c11
OBJS = compressT_LOLS.o functions.o
DEPS = functions.h

all: compresst
	rm *.o

compresst : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compresst -lm

compressT_LOLS.o: compressT_LOLS.c
	$(CC) $(CFLAGS) -c compressT_LOLS.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm compresst
