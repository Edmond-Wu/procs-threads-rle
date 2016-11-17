#include "functions.h"

int num_digits(int n) {
	return floor(log10(abs(n))) + 1;
}

char* get_file_extension(char *file_name) {
	char *dot = strrchr(file_name, '.');
	if (!dot || dot == file_name)
		return "";
	return dot + 1;
}

char* extract_file(FILE *file) {
	if (file == NULL) {
		fprintf(stderr, "Invalid file to be read\n");
		return NULL;
	}
	fseek(file, 0, SEEK_END);
	size_t length = ftell(file);
	rewind(file);
	char *buffer = (char *)malloc(length);
	fread(buffer, 1, length - 1, file);
	return buffer;
}

char* get_substring(char *string, int start, int end) {
	int difference = end - start;
	char *substring = malloc((difference + 1) * sizeof(char));
	int i;
	for (i = start; i < end; i++) {
		substring[i - start] = string[i];
	}
	substring[difference] = '\0';
	return substring;
}

char** split_string(char *string, int parts) {
	int length = strlen(string);
	int char_size = length / parts;
	int num_rounded_up_strings = -1;
	if (length % parts != 0)
		num_rounded_up_strings = length / (char_size + 1);
	char **array = (char **)malloc(sizeof(char *) * (parts));
	int counter = 0;
	for (int i = 0; i < parts; i++) {
		char *substring;
		if (num_rounded_up_strings > 0) {
			substring = get_substring(string, counter, counter + (char_size + 1));
			num_rounded_up_strings--;
			counter += (char_size + 1);
		}
		else {
			//even string lengths
			if (num_rounded_up_strings == -1) {
				substring = get_substring(string, counter, counter + char_size);
				counter += char_size;
			}
			//otherwise it means you're at last segment
			else {
				int difference = length - counter - 1;
				substring = get_substring(string, counter, counter + difference);
			}
		}
		array[i] = substring;
	}
	return array;
}

int next_char_same(char *string, int index) {
	int length = strlen(string);
	char c = string[index];
	if (index >= length)
		return 0;
	if (index != length - 1 && c == string[index + 1])
		return 1;
	int i = index + 1;
	char x = string[i];
	while (!isalpha(x)) {
		x = string[i];
		i++;
	}
	if (x == c)
		return 1;
	return 0;
}

char* compress(char *string) {
	int length = strlen(string);
	char *compressed = (char *)malloc(sizeof(char) * (length + 1));
	compressed[0] = '\0';
	int consecutive = 1;
	int compressed_length = 0;
	for (int i = 0; i < length; i++) {
		char c = string[i];
		if (!isalpha(c))
			continue;
		if (next_char_same(string, i) == 1)
			consecutive++;
		else {
			char *placeholder;
			if (consecutive == 1 || consecutive == 2) {
				placeholder = (char *)malloc(sizeof(char) * 3);
				placeholder[0] = c;
				if (consecutive == 1) {
					placeholder[1] = '\0';
					compressed_length++;
				}
				else {
					placeholder[1] = c;
					placeholder[2] = '\0';
					compressed_length += 2;
				}
			}
			else {
				placeholder = (char *)malloc(sizeof(char) * (2 + num_digits(consecutive)));
				int placeholder_length = 1 + num_digits(consecutive);
				sprintf(placeholder, "%d%c", consecutive, c);
				placeholder[placeholder_length] = '\0';
				compressed_length += placeholder_length;
			}
			strcat(compressed, placeholder);
			free(placeholder);
			consecutive = 1;
		}
	}
	//printf("Compressed length: %d\n", compressed_length);
	compressed[compressed_length] = '\0';
	return compressed;
}

int compressed_exists(char *file_name) {
	int file_name_length = strlen(file_name);
	char *new_file = (char *)malloc(sizeof(char) * (file_name_length + 6));
	strncpy(new_file, file_name, file_name_length - strlen(strpbrk(file_name, ".")));
	sprintf(new_file, "%s_%s_LOLS", new_file, get_file_extension(file_name));
	if (access(new_file, F_OK) != -1) {
		free(new_file);
		return 1;
	}
	else {
		char *new_file_parts = (char *)malloc(sizeof(char) * (file_name_length + 7));
		strcat(new_file_parts, new_file);
		new_file_parts[file_name_length + 5] = '0';
		new_file_parts[file_name_length + 6] = '\0';
		if (access(new_file_parts, F_OK) != -1) {
			free(new_file_parts);
			free(new_file);
			return 1;
		}
		free(new_file_parts);
		free(new_file);
	}
	return 0;
}

void write_file(char *file_name, char *content) {
	FILE *file = fopen(file_name, "w");
	if (file != NULL) {
		fputs(content, file);
		fclose(file);
	}
}
