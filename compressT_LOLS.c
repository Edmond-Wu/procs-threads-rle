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
			if (consecutive == 1) {
				placeholder = (char *)malloc(sizeof(char) * 2);
				placeholder[0] = c;
				placeholder[1] = '\0';
			}
			else if (consecutive == 2) {
				placeholder = (char *)malloc(sizeof(char) * 3);
				placeholder[0] = c;
				placeholder[1] = c;
				placeholder[2] = '\0';
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

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "ERROR: Invalid number of arguments; only 1 argument required\n");
	}
	else {
    		char *compressed = compress(argv[1]);
		printf("Compressed string: %s\n", compressed);
		free(compressed);
	}
	return 0;
}
