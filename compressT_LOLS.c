#include <stdio.h>
#include <errno.h>
#include <pthread.h> /*needs -pthread compilation option*/
#include "functions.h"

/**
 * Thread function that compresses the string and writes it to a corresponding file
 * @param args [argument struct, which includes a string, file name, and int]
 */
void* thread_function(Args *args) {
	char *compressed = compress(args->string);
	//printf("Compressed: %s\n", compressed);
	int file_name_length = strlen(args->file_name);
	//creating new file name and writing to that file
	char *new_file_name = (char *)malloc(sizeof(char) * (file_name_length + 7));
	strncpy(new_file_name, args->file_name, file_name_length - strlen(strpbrk(args->file_name, ".")));
	sprintf(new_file_name, "%s_%s_LOLS%d", new_file_name, get_file_extension(args->file_name), args->part);
	printf("Compressed string: %s\n", compressed);
	write_file(new_file_name, compressed);
	free(new_file_name);
	free(compressed);
	free(args->string);
	free(args);
	return NULL;
}

/**
 * Function to process a file; read file and extract its contents
 * split contents into array of strings, then compress each of them via multi-threading
 * @param file_name [name of file]
 * @param file      [actual file named file_name]
 * @param parts     [how many parts to be split]
 */
void process_file(char *file_name, FILE *file, int parts) {
	if (file == NULL)
		fprintf(stderr, "Invalid file input\n");
	else {
		int file_name_length = strlen(file_name);
		char *buffer = extract_file(file);
		char *new_file = (char *)malloc(sizeof(char) * (file_name_length + 6));
		strncpy(new_file, file_name, file_name_length - strlen(strpbrk(file_name, ".")));
		sprintf(new_file, "%s_%s_LOLS", new_file, get_file_extension(file_name));
		//abort if compressed file(s) already exist
		if (compressed_exists(file_name) == 1) {
			fprintf(stderr, "Compressed file(s) exist!\n");
			free(new_file);
			free(buffer);
			return;
		}
		if (parts == 1) {
			char *compressed = compress(buffer);
			write_file(new_file, compressed);
			printf("Compressed string: %s\n", compressed);
			free(compressed);
		}
		else {
			char **array = split_string(buffer, parts);
			//multi-threading, number of threads = number of parts to be split
			pthread_t threads[parts];
			for (int i = 0; i < parts; i++) {
				Args *args = (Args *)malloc(sizeof(Args));
				args->part = i;
				args->string = array[i];
				args->file_name = file_name;
				pthread_create(&threads[i], NULL, thread_function, args);
			}
			for (int j = 0; j < parts; j++)
				pthread_join(threads[j], NULL);
			free(array);
		}
		free(buffer);
		free(new_file);
	}
}

/**
 * Arg 1: input file
 * Arg 2: number of parts to be split
 */
int main(int argc, char **argv) {
	if (argc != 3)
		fprintf(stderr, "ERROR: Invalid number of arguments (2 required)\n");
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
			if (parts < 1)
				fprintf(stderr, "Invalid number of parts to be split\n");
			else {
				printf("Parts: %d\n", parts);
				process_file(argv[1], file, parts);
			}
			fclose(file);
		}
	}
	return 0;
}
