CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -std=c99

compress : compressT_LOLS.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm compress
