CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -pthread -std=c11
OBJS = compressT_LOLS.o functions.o
OBJS2 = compressR_LOLS.o functions.o
OBJS3 = compressR_worker_LOLS.o functions.o
DEPS = functions.h

all: compressT_LOLS compressR_LOLS compressR_worker_LOLS
	rm *.o

compressT_LOLS : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compressT_LOLS -lm

compressR_LOLS: $(OBJS2)
	$(CC) $(CLFAGS) $(OBJS2) -o compressR_LOLS -lm

compressR_worker_LOLS: $(OBJS3)
	$(CC) $(CFLAGS) $(OBJS3) -o compressR_worker_LOLS -lm

compressT_LOLS.o: compressT_LOLS.c
	$(CC) $(CFLAGS) -c compressT_LOLS.c

compressR_LOLS.o: compressR_LOLS.c
	$(CC) $(CFLAGS) -c compressR_LOLS.c

compressR_worker_LOLS.o: compressR_worker_LOLS.c
	$(CC) $(CFLAGS) -c compressR_worker_LOLS.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm compressT_LOLS compressR_LOLS compressR_worker_LOLS
