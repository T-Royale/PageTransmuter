#ifndef FILES_H
#define FILES_H

#include <stdbool.h>
#include <stdio.h>

bool check_path(const char *path);
bool validate_html_file(char *file);
long long get_content_length(char *filename);
char* get_name_from_filepath(const char *filepath);
long get_line_len(FILE* stream);

#endif