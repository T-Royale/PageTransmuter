#include "Include/Functions.h"

/* cli.c - user interaction via command line
	- parse cli flags and print help messages
	- system errors are only reported using perror
*/

flags_t* flags_get(int argc, char **argv){
	flags_t* result = malloc(sizeof(flags_t));
	if(!result) return NULL;
	result->output = NULL;
	result->input = NULL;
	result->help = false;
	result->version = false;
	result->http_headers = false;
	result->macro_name = NULL;
	static const struct option long_opts[] = {
		{"output", required_argument, 0, 'o'},
		{"file", required_argument, 0, 'f'},
		{"macro-name", required_argument, 0, 'n'},
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'v'},
		{"http-headers", no_argument, 0, 't'},
	};
	int opt_index = 0;
	int c = -1;
	while((c = getopt_long(argc, argv, "o:f:n:hvt", long_opts, &opt_index)) != -1){
		switch(c){
			case 'o': {
				if(!result->output){
					int len = strlen(optarg)+1;
					result->output = malloc(len * sizeof(char));
					if(!result->output){
						perror("malloc");
						goto error;
					}
					memcpy(result->output, optarg, len);
				}
				break;
			}
			case 'f': {
				if(!result->input){
					int len = strlen(optarg)+1;
					result->input = malloc(len * sizeof(char));
					if(!result->input){
						perror("malloc");
						goto error;
					}
					memcpy(result->input, optarg, len);
				}
				break;
			}
			case 'n': {
				if(!result->macro_name){
					int len = strlen(optarg)+1;
					result->macro_name = malloc(len * sizeof(char));
					if(!result->macro_name){
						perror("malloc");
						goto error;
					}
					memcpy(result->macro_name, optarg, len);
				}
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
				result->help = true;
				break;
		}
	}
	return result;

error:					// Return NULL without memory leaks
	flags_free(result);
	return NULL;
}

void flags_free(flags_t* flags){
	if(!flags) return;
	if(flags->input) free(flags->input);
	if(flags->output) free(flags->output);
	if(flags->macro_name) free(flags->macro_name);
	free(flags);
}

void print_help(char* program_name){
	printf(
		"Usage:\n"
		"	%s -f <file.html> [options]\n"
		"Options:\n"
		"	-f, --file <file.html>		Input HTML file (required)\n"
		"	-o, --output <file.h>		Output header file (default: stdout)\n"
		"	-n, --macro-name			Macro name (default: derived from input file)\n"
		"	-t, --http-headers			Add HTTP headers to output\n"\
		"	-v, --version				Show installed version\n"
		"	-h, --help					Display this help message\n"
		, program_name);
}

void print_version(){
	printf("PageTransmuter %s\n", PROGRAM_VERSION);
}