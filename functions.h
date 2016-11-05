#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int num_digits(int n);

char* compress(char *string);

void write_file(char *file_name, char *content);
#endif
