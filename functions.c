#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "functions.h"

int num_digits(int n) {
	return floor(log10(abs(n))) + 1;
}

char* get_substring(char *string, int start, int end) {
	char *substring;
	int difference = end - start;
	substring = malloc((difference + 1) * sizeof(char));
	int i;
	for (i = start; i < end; i++) {
		substring[i - start] = string[i];
	}
	substring[difference] = '\0';
	return substring;
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
	int compressed_length = strlen(compressed);
	compressed[compressed_length - 1] = '\0';
	return compressed;
}

void write_file(char *file_name, char *content) {
	FILE *file = fopen(file_name, "a");
	if (file != NULL) {
		fputs(content, file);
		fclose(file);
	}
}
