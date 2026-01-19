#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

typedef struct {
    char *output;
    char *input;
    char *macro_name;
    bool http_headers;
    bool help;
    bool version;
} flags_t;

flags_t* flags_get(int argc, char *argv[]);
void flags_free(flags_t *flags);
void print_help(const char *program_name);
void print_version(void);

#endif