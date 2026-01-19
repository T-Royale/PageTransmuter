#include "Include/cli.h"
#include "Include/files.h"
#include "Include/content.h"
#include <stdio.h>
#include <stdlib.h>

/* main.c - program entry point
	- Performs necesary checks before entering main loop
	- Handles all error messages printed to stderr
	- The 'cleanup' tag is used to exit the program safely
*/

int main(int argc, char *argv[]) {
	FILE* input = NULL;
	FILE* output = NULL;
	flags_t* flags = flags_get(argc, argv);
	
	if(!flags){
		fprintf(stderr, "Failed to parse arguments\n");
		return -1;
	}
	if(flags->help) {
		print_help(argv[0]);
		goto cleanup;
	}
	if(flags->version){
		print_version();
		goto cleanup;
	}
	if(!flags->input) {
		fprintf(stderr, "-f flag is required\nRun %s -h for help\n", argv[0]);
		goto cleanup;
	}
	if(!check_path(flags->input)){
		fprintf(stderr, "Input path is not valid\n");
		goto cleanup;
	}	
	if (!validate_html_file(flags->input)){
		fprintf(stderr, "Input file is not html or accessable from this scope\n");
		goto cleanup;
	}
	input = fopen(flags->input, "r");
	if(!input){
		perror("fopen");
		goto cleanup;
	}
	if(flags->output){
		output = fopen(flags->output, "w");
		if(!output){
			perror("fopen");
			goto cleanup;
		}
	} else {
		output = stdout;   // If no output defined, default to stdout
	}

	if(!output) {
		perror("fopen");
		goto cleanup;
	}
	if(!flags->macro_name)
		flags->macro_name = get_name_from_filepath(flags->input);
	long long content_length = get_content_length(flags->input);
	if(content_length <= 0){
		fprintf(stderr, "File has no content\n");
		goto cleanup;
	}
	add_include_guards(output, flags->macro_name);
	create_macro(output, flags->macro_name);
	if(!flags->http_headers)
		add_http_headers(output, &content_length);
	// Main program loop
	for(int len = get_line_len(input); len != -1; len = get_line_len(input)){
		char *line = malloc(len+1);
		if(!line){
			perror("malloc");
			goto cleanup;
		}
		if(!fgets(line, len+1, input)){

		}
		char* transmuted_line = transmute_line(line, len);
		if(!transmuted_line){
			fprintf(stderr, "failed to allocate memory for transmuted line\n");
			goto cleanup;
		}
		write_line(transmuted_line, output);
		free(line);
		free(transmuted_line);
	}
	fprintf(output, "\"\"");
	close_include_guards(output);
cleanup:	// Terminate program safely
	flags_free(flags);
	if(input)
		fclose(input);
	if(output && output != stdout) 
		fclose(output);
	return 0;
}