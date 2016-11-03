CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -std=c11

compress : compressT_LOLS.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm compress
