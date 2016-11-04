#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /*needs -pthread compilation option*/
#include "functions.h"

int main(int argc, char **argv) {
	//2 only additional argument is a text file name
	if (argc != 2)
		fprintf(stderr, "ERROR: Invalid number of arguments; only 1 argument required\n");
	else {
    		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
			fprintf(stderr, "Invalid file\n");
		else {
			read_file(file);
			fclose(file);
		}
	}
	return 0;
}
