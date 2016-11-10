CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -pthread -std=c11
OBJS = compressT_LOLS.o functions.o
OBJS2 = compressR_LOLS.o functions.o
DEPS = functions.h

all: compresst compressr
	rm *.o

compresst : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compresst -lm

compressr: $(OBJS2)
	$(CC) $(CLFAGS) $(OBJS2) -o compressr -lm

compressR_LOLS.o: compressR_LOLS.c
	$(CC) $(CFLAGS) -c compressR_LOLS.c

compressT_LOLS.o: compressT_LOLS.c
	$(CC) $(CFLAGS) -c compressT_LOLS.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm compresst compressr
