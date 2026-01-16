//Headers del programa
#include "Include/Functions.h"

int main(int argc, char *argv[]) {
    FILE* input;
    FILE* output;
    flags_t* flags = flags_get(argc, argv);
    
    if(flags->version) print_version();
    else if(flags->help) print_help(argv[0]);
    else if(!flags->input) fprintf(stderr, "-f flag is required\nRun %s -h for help\n", argv[0]);   // No input is specified
    else if(!check_path(flags->input)) fprintf(stderr, "Input path is not valid\n");                // Invalid input path
    else if (validate_html_file(flags->input)){
        input = fopen(flags->input, "r");
        if(!input)
            perror("fopen");
        if(flags->output){
            output = fopen(flags->output, "w");
            if(!output)
                perror("fopen");
        } else if(!flags->output) output = stdout;   // If no output defined, default to stdout
        if(output) {
            char* name = "test1";
            long long content_length = get_content_length(flags->input);
            if(content_length > 0) {
                add_include_guards(output, name);
                create_macro(output, name);
                if(flags->http_headers)
                    add_http_headers(output, &content_length);
                close_include_guards(output);
            } else fprintf(stderr, "File has no content\n");
        } else perror("fopen");
    }
    flags_free(flags);
    close_files(input, output);
    return 0;
}

void close_files(FILE* input, FILE* output){
    if(input != NULL) fclose(input);
    if(output != NULL && output != STDIN_FILENO) fclose(output);
}