//Headers del programa
#include "Include/Functions.h"

flags_t* flags_get(int argc, char **argv){
    flags_t* result = malloc(sizeof(flags_t));
    result->output = NULL;
    result->input = NULL;
    result->help = false;
    result->version = false;
    result->http_headers = false;
    static struct option long_opts[] = {
        {"output", required_argument, 0, 'o'},
        {"file", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"http-headers", no_argument, 0, 't'},
    };
    int opt_index = 0;
    int c = -1;
    while((c = getopt_long(argc, argv, "o:f:hvt", long_opts, &opt_index)) != -1){
        switch(c){
            case 'o': {
                int len = strlen(optarg)+1;
                result->output = malloc(len * sizeof(char));
                strncpy(result->output, optarg, len);
                break;
            }
            case 'f': {
                int len = strlen(optarg)+1;
                result->input = malloc(len * sizeof(char));
                strncpy(result->input, optarg, len);
                break;
            }
            case 'h':
                result->help = true;
                break;
            case 'v':
                result->version = true;
                break;
            case 't':
                result->http_headers = true;
                break;
            case '?':
            default:
                printf("");
                break;
        }
    }
    return result;
}

void flags_free(flags_t* flags){
    if(flags->input) free(flags->input);
    if(flags->output) free(flags->output);
    free(flags);
}

void print_help(char* program_name){
    printf("%s -f file.html [opts]\n\t"\
        "-o --output <file.h>   Specify an output file, if not used will use stdin\n\t"\
        "-t --http-headers      Add HTTP headers in the output\n\t"\
        "-v --version           Show installed version\n", program_name);
}

void print_version(){
    printf("PageTransmuter %s\n", PROGRAM_VERSION);
}