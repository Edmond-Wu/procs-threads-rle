#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h> /*needs -pthread compilation option*/
#include "functions.h"

/**
 * Thread function that compresses the string and writes it to a corresponding file
 * @param args [argument struct, which includes a string, file name, and int]
 */
void* thread_function(Args *args) {
	char *str = compress(args->string);
	printf("Compressed: %s\n", str);
	int file_name_length = strlen(args->file_name);
	char *new_file_name = (char *)malloc(sizeof(char) * (file_name_length + 7));

	//create new file name
	strncpy(new_file_name,args->file_name,file_name_length - strlen(strpbrk(args->file_name,".")));
	sprintf(new_file_name, "%s_%s_LOLS%d", new_file_name, get_file_extension(args->file_name), args->part);

	//write to new file
	write_file(new_file_name, str);
	free(new_file_name);
	free(str);
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
		char *buffer = extract_file(file);
		char *compressed = compress(buffer);
		printf("Compressed string: %s\n", compressed);
		char **array = split_string(buffer, parts);
		pthread_t threads[parts];

		//multi-threading operation
		for (int i = 0; i < parts; i++) {
			Args *args = (Args *)malloc(sizeof(Args));
			args->part = i;
			args->string = array[i];
			args->file_name = file_name;
			pthread_create(&threads[i], NULL, thread_function, (void *)args);
		}
		//wait for threads to finish
		for (int j = 0; j < parts; j++) {
			pthread_join(threads[j], NULL);
		}
		free(array);
		free(compressed);
		free(buffer);
	}
}

int main(int argc, char **argv) {
	//2 only additional argument is a text file name
	if (argc != 3)
		fprintf(stderr, "ERROR: Invalid number of arguments (2 required)\n");
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
