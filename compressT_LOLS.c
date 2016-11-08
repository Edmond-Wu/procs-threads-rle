#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /*needs -pthread compilation option*/
#include "functions.h"

void thread_function(void *arg) {
	char *str = compress((char *)arg);
	printf("Compressed: %s\n", str);
	write_file("test_txt_LOLS", str);
	free(str);
}

void process_file(FILE *file, int parts) {
	if (file == NULL)
		fprintf(stderr, "Invalid file input\n");
	else {
		//remove older outputs
		remove("test_txt_LOLS");

		char *buffer = extract_file(file);
		char *compressed = compress(buffer);
		printf("Compressed string: %s\n", compressed);

		char **array = split_string(buffer, parts);
		//pthread_t threads[parts];
		for (int x = 0; x < parts; x++)
			printf("Substring: %s\n", array[x]);
		for (int i = 0; i < parts; i++)
			printf("Compressed: %s\n", compress(array[i]));
		/*
		for (int i = 0; i < parts; i++) {
			pthread_t thread;
			pthread_create(&threads[i], NULL, thread_function, array[i]);
		}
		for (int j = 0; j < parts; j++) {
			pthread_join(threads[j], NULL);
		}
		*/
		/*
		pthread_t thread;
		pthread_create(&thread, NULL, thread_function, (void *)buffer);
		printf("waiting for thread to terminate...\n");
		pthread_join(thread, NULL);
		*/
		free(buffer);
	}
}

int main(int argc, char **argv) {
	//2 only additional argument is a text file name
	if (argc != 3)
		fprintf(stderr, "ERROR: Invalid number of arguments; only 1 argument required\n");
	else {
    		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
			fprintf(stderr, "Invalid file\n");
		else {
			int parts = atoi(argv[2]);
			process_file(file, parts);
			fclose(file);
		}
		/*
		int length = strlen(argv[1]);
		char *substring = get_substring(argv[1], 0, length);
		printf("Substring: %s\n", substring);
		*/
	}
	return 0;
}
