#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "functions.h"

/* Argument List
 *** Arg 1: Int part
 *** Arg 2: String to compress
 *** Arg 3: Input File name
*/
int main(int argc, char **argv) {

		int part = atoi(argv[1]);
		char * string = argv[2];
		char * file_name = argv[3];

		printf("worker: argc= %d\n", argc);
		printf("worker: part= %d, string= %s, filename= %s\n", part, string, file_name);

		if (argc != 4){
			fprintf(stderr, "ERROR: Invalid number of arguments (3 required)\n");
		}
		else {
	    FILE *file = fopen(argv[3], "r");
			if (file == NULL) {
				if (errno == EACCES)
					fprintf(stderr, "Lack file read permissions\n");
				else
					fprintf(stderr, "File doesn't exist\n");
			}
			else {
				char *compressed = compress(string);
				//printf("Compressed: %s\n", compressed);
				int file_name_length = strlen(file_name);
				char *new_file_name = (char *)malloc(sizeof(char) * (file_name_length + 7));
				strncpy(new_file_name, file_name, file_name_length - strlen(strpbrk(file_name, ".")));
				sprintf(new_file_name, "%s_%s_LOLS%d", new_file_name, get_file_extension(file_name), part);
				fprintf(stderr, "Compressed string: %s\n", compressed);
				fprintf(stderr, "New File Name: %s\n", new_file_name);
				write_file(new_file_name, compressed);
				free(new_file_name);
				free(compressed);
			}
		}
		// return 0;
}
