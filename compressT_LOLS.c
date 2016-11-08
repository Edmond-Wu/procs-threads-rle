#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /*needs -pthread compilation option*/
#include "functions.h"
#define NUM_THREADS 5

void process_file(FILE *file) {
	if (file == NULL)
		fprintf(stderr, "Invalid file input\n");
	else {
		//open file and store contents in string
		fseek(file, 0, SEEK_END);
		size_t length = ftell(file);
		rewind(file);
		char *buffer = (char *)malloc(length + 1);
		buffer[length] = '\0';
		fread(buffer, 1, length, file);

		//compress string and write to new file
		char *compressed = compress(buffer);
		printf("Compressed string: %s\n", compressed);
		write_file("test_txt_LOLS", compressed);
		free(compressed);
		free(buffer);
	}
}

int main(int argc, char **argv) {
	//2 only additional argument is a text file name
	if (argc != 2)
		fprintf(stderr, "ERROR: Invalid number of arguments; only 1 argument required\n");
	else {
    		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
			fprintf(stderr, "Invalid file\n");
		else {
			process_file(file);
			fclose(file);
		}
	}
	return 0;
}
