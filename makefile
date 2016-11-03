CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -std=c11 -pthread

compress : compressT_LOLS.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm compress
