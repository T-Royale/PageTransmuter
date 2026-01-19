#ifndef CONTENT_H
#define CONTENT_H

#include <stdio.h>

void create_macro(FILE *stream, const char *name);
char* transmute_line(const char *line, int len);
void add_include_guards(FILE *stream, const char *name);
void add_http_headers(FILE *stream, long long *content_length);
void write_line(char* line, FILE* stream);
void close_include_guards(FILE *stream);

#endif