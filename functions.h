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
 * Extracts file contents and returns it as a string
 * @param  file [name of file]
 * @return      [string containing file's contents]
 */
char* extract_file(FILE *file);

/**
 * Gets a substring from an input string
 * @param  string [input]
 * @param  start  [starting index]
 * @param  end    [ending index]
 * @return        [substring of input from start to but not including end]
 */
char* get_substring(char *string, int start, int end);

/**
 * Splits a string into parts
 * @param  string [string to be split]
 * @param  parts  [number of parts to be split]
 * @return        [array containing split strings]
 */
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
