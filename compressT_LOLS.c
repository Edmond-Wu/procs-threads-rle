#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compressT_LOLS.h"

int num_digits(int n) {
	return floor(log10(abs(n))) + 1;
}

char* compress(char *string) {
	int length = strlen(string);
	char *compressed = (char *)malloc(sizeof(char) * (length * 2 + 1));
	int consecutive = 1;
	for (int i = 0; i < length; i++) {
		char c = string[i];
		if (i != length - 1 && c == string[i + 1])
			consecutive++;
		else {
			char *placeholder;
			if (consecutive == 1 || consecutive == 2) {
				placeholder = (char *)malloc(sizeof(char) * 3);
				placeholder[0] = c;
				if (consecutive == 1)
					placeholder[1] = '\0';
				else {
					placeholder[1] = c;
					placeholder[2] = '\0';
				}
			}
			else {
				placeholder = (char *)malloc(sizeof(char) * (2 + num_digits(consecutive)));
				int placeholder_length = 1 + num_digits(consecutive);
				sprintf(placeholder, "%d%c", consecutive, c);
				placeholder[placeholder_length] = '\0';
			}
			strcat(compressed, placeholder);
			free(placeholder);
			consecutive = 1;
		}
	}
	return compressed;
}

void write_file(char *file_name, char *content) {
	FILE *file = fopen(file_name, "w");
	if (file != NULL) {
		fputs(content, file);
		fclose(file);
	}
}

void read_file(FILE *file) {
	if (file == NULL)
		fprintf(stderr, "Invalid file input\n");
	else {
		fseek(file, 0, SEEK_END);
		size_t length = ftell(file);
		rewind(file);
		char *buffer = (char *)malloc(length + 1);
		buffer[length] = '\0';
		fread(buffer, 1, length, file);
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
			read_file(file);
			fclose(file);
		}
	}
	return 0;
}
