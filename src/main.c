//Headers del programa
#include "Include/Functions.h"
// Variables globales
bool DebugMode = false;
int nLineas = 0; 

int main(int argc, char *argv[]) {
    FILE* input;
    FILE* output;
    flags_t* flags = flags_get(argc, argv);

    if(flags->version) print_version();
    else if(flags->help) print_help(argv[0]);
    else if(!flags->input) fprintf(stderr, "-f flag is required\nRun %s -h for help\n", argv[0]);
    else if(!valid_path(flags->input)) fprintf(stderr, "Input path is not valid\n");
    else {
        input = fopen(flags->input, "r");
        if(!flags->output || valid_file(flags->output)){
            output = (flags->output) ? fopen(flags->output, "w") : stdout;
            fprintf(output, "Success!\n");
        }
    }

    flags_free(flags);
    close_files(input, output);
    return 0;
}

void close_files(FILE* input, FILE* output){
    if(input != NULL) fclose(input);
    if(output != NULL && output != STDIN_FILENO) fclose(output);
}