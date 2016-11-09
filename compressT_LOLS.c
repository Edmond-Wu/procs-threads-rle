#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h> /*needs -pthread compilation option*/
#include "functions.h"

void thread_function(Args *args) {
	char *str = compress(args->string);
	printf("Compressed: %s\n", str);
	int file_name_length = strlen(args->file_name);
	char *new_file_name = (char *)malloc(sizeof(char) * (file_name_length + 7));
	if (args->part > 1)
		sprintf(new_file_name, "test_%s_LOLS%d", get_file_extension(args->file_name), args->part);
	else
		sprintf(new_file_name, "test_%s_LOLS", get_file_extension(args->file_name));
	write_file(new_file_name, str);
	free(new_file_name);
	free(str);
	return NULL;
}

void process_file(char *file_name, FILE *file, int parts) {
	if (file == NULL)
		fprintf(stderr, "Invalid file input\n");
	else {
		char *buffer = extract_file(file);
		char *compressed = compress(buffer);
		printf("Compressed string: %s\n", compressed);

		char **array = split_string(buffer, parts);
		pthread_t threads[parts];
		/*
		for (int x = 0; x < parts; x++)
			printf("Substring: %s\n", array[x]);
		for (int i = 0; i < parts; i++)
			printf("Compressed: %s\n", compress(array[i]));
		*/
		
		for (int i = 0; i < parts; i++) {
			Args *args = (Args *)malloc(sizeof(Args));
			args->part = i + 1;
			args->string = array[i];
			args->file_name = file_name;
			pthread_create(&threads[i], NULL, thread_function, args);
		}
		for (int j = 0; j < parts; j++) {
			pthread_join(threads[j], NULL);
		}
		
		free(buffer);
	}
}

int main(int argc, char **argv) {
	//2 only additional argument is a text file name
	if (argc != 3)
		fprintf(stderr, "ERROR: Invalid number of arguments; only 1 argument required\n");
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
			process_file(argv[1], file, parts);
			fclose(file);
		}
	}
	return 0;
}
