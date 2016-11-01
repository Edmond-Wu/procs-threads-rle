#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* compress(char *string) {
	int length = strlen(string);
	char *compressed = (char *)malloc(sizeof(char) * (length * 2 + 1));
	for (int i = 0; i < length; i++) {
		
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
