#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "functions.h"

int main(int argc, char **argv) {
	if (argc != 3)
		fprintf(stderr, "ERROR: Invalid number of arguments (needs 2)\n");
	else {
		FILE *file = fopen(argv[1], "r");
		if (file == NULL) {
			if (errno == EACCES)
				fprintf(stderr, "Lack file read permissions\n");
			else
				fprintf(stderr, "File doesn't exist\n");
		}
		else {
			int parts = atoi(argv[2]);
			printf("Parts: %d\n", parts);
			char *extracted = extract_file(file);
			char *compressed = compress(extracted);
			printf("Compressed: %s\n", compressed);
			fclose(file);
			free(compressed);
			free(extracted);
		}
	}
	return 0;
}
