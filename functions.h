#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/**
 * Gives number of digits of an integer
 * @param  n [integer]
 * @return   [number of digits n has]
 */
int num_digits(int n);

/**
 * Gets a substring from an input string
 * @param  string [input]
 * @param  start  [starting index]
 * @param  end    [ending index]
 * @return        [substring of input from start to but not including end]
 */
char* get_substring(char *string, int start, int end);

char** split_string(char *string, int parts);

/**
 * RLE compression algorithm
 * repeated instances of character replaced with a number followed by that character
 * number represents how many instances (ignores instances of 2 or fewer however)
 * @param  string [string to be compressed]
 * @return        [compressed string]
 */
char* compress(char *string);

/**
 * Writes a string to a file
 * @param file_name [file to be written]
 * @param content   [string to be written to file]
 */
void write_file(char *file_name, char *content);
#endif
