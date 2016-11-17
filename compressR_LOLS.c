#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

pid_t fork(void);
pid_t wait(int* status);

/**
 * Function to process a file; read file and extract its contents
 * split contents into array of strings, then compress each of them via multi-processing
 * @param file_name [name of file]
 * @param file      [actual file named file_name]
 * @param parts     [how many parts to be split]
 */
void process_file_R(char* file_name, FILE *file, int parts){
	int children_procs = 0;
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

		// Parts > 1, spawn children processes = number of parts
		else {
			char **array = split_string(buffer, parts);
			pid_t pid[parts];

			for (children_procs = 0; children_procs < parts; children_procs++) {
				pid[children_procs] = fork();
				// Fork failure errors
				if (pid[children_procs] == -1) {
					if (errno == EAGAIN || errno == ENOMEM)
						fprintf(stderr, "ERROR: Failed to fork child process, cannot allocate sufficient space\n");
					else
						fprintf(stderr, "Failed to fork new child process\n");
					exit(-1);
				}
				// This is child process
				if (pid[children_procs] == 0){
					printf("compressR_LOLS: child process %d, child PID is %d\n", children_procs, getpid());
					// Argument 1: Name of file to be executed
					//char * worker_file = "compressR_worker_LOLS.c";
					// Argument 2: Arguments for the file you just executed
					// Part, String, File Name
					char *path = "/Asst2/compressR_worker_LOLS.c";
					char *argList[4];
					argList[0] = (int)children_procs;
					argList[1] = array[children_procs];
					argList[2] = file_name;
					argList[3] = NULL;
					if (execvp(path, argList) < 0) {
						fprintf(stderr, "ERROR: execvp() failed\n");
						exit(-1);
					}
				}
				// Else, this is parent process
				else {
					printf("compressR_LOLS: child process %d, parent process PID is %d\n", children_procs, getpid());
				}
			}
			// Parent needs to wait for all child processes to finish
			for ( children_procs=0; children_procs < parts; children_procs++) {
				pid_t childPID;
				int childStatus;
				childPID = wait(&childStatus);
				printf("compressR_LOLS: child process %d exited with status %d\n",childPID, childStatus);
			}
		}
	}
}

// Argument 1: File to compress
// Argument 2: Number of parts
int main(int argc, char **argv) {
	if (argc != 3)
		fprintf(stderr, "ERROR: Invalid number of arguments (2 required)\n");
	else {
		FILE *file = fopen(argv[1], "r");

		if (file == NULL) {
			if (errno == EACCES)
				fprintf(stderr, "Lack file read permissions\n");
			else
				fprintf(stderr, "File does not exist\n");
		}

		else {
			int parts = atoi(argv[2]);
			printf("Parts: %d\n", parts);

			if (parts < 1)
				fprintf(stderr, "Invalid number of parts\n");
			// All error checking done, spawn children
			else
				process_file_R (argv[1], file, parts);
			fclose(file);
		}
	}
	return 0;
}
