#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* compress(char *string) {

}

int main(int argc, char **argv) {
  if (argc != 2) {
		fprintf(stderr, "ERROR: Invalid number of arguments; only 1 argument required\n");
	}
	else {
    char *compressed = compress(argv[1]);
		printf("Compressed string: %s\n", compressed);
	}
  return 0;
}
