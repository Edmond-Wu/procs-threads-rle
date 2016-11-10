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
			if (errno == ENOENT)
				fprintf(stderr, "File doesn't exist\n");
			else if (errno == EACCES)
				fprintf(stderr, "Don't have file read permissions\n");
		}
		else {
			int parts = atoi(argv[2]);
			char *compressed = compress(extract_file(file));
			printf("Compressed: %s\n", compressed);
			fclose(file);
			free(compressed);
		}
	}
	return 0;
}
