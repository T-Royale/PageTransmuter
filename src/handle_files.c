#include "Include/Functions.h"

/* handle_files.c - handling files and paths
	- These functions don't display custom error messages.
	- System errors are reported using perror().
*/

// Gets rid of final newline character in filepaths
static void fix_filepath(char* string) {
	int size = strlen(string);
	for(int i = 0; i < size; i++){
		if(string[i] == '\n') string[i] = '\0';
	}
}

// Check if filepath is valid
bool check_path(const char* path){
	char *path_fixed = malloc(strlen(path));
	memcpy(path_fixed, path, strlen(path)); 
	fix_filepath(path_fixed);
	bool result = (access(path_fixed, F_OK) == 0);
	free(path_fixed);
	return result;
}

// Check if file exists and is HTML
bool validate_html_file(char* filename){
	if(strcasestr(filename, ".html") == NULL){
		return false;
	}
	FILE* test = fopen(filename, "r");
	if(!test) {
		perror("fopen");
		return false;
	}
	fclose(test);
	return true;
}

// Get file length
long long get_content_length(char* filename){
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		perror("fopen");
		return -1LL;
	}
	fseeko(file, 0, SEEK_END);
	off_t filesize = ftello(file);
	if(filesize == -1) {
		perror("ftello");
		fclose(file);
		return -1LL;
	}
	fclose(file);
	return (long long)filesize;
}


// Returns length of the next line in the file and -1 if EOF
long get_line_len(FILE* stream){
	long pos =  ftell(stream);
	long len = 0;
	char c;
	while ((c = getc(stream)) != EOF){
		len++;
		if(c == '\n'){
			break;
		}
	}
	fseek(stream, pos, SEEK_SET);

	if(len == 0 && c == EOF)
		return -1;
	return len;
}