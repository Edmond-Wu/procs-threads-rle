CC = gcc
CFLAGS = -g -Wall -pedantic -ansi -std=c11 -pthread

compress : functions.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm compress
