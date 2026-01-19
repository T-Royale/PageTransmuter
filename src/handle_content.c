#include "Include/content.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* handle_content.c - craft and print program output
	- system errors are only reported using perror
*/

void add_include_guards(FILE* stream, const char* name){
	int len = strlen(name) + 3;
	char *defName = malloc(len);
	sprintf(defName, "%s_H", name);
	for(int i = 0; i < defName[i]; i++){
		if(defName[i] == ' ') defName[i] = '_';
		if(islower(defName[i])) defName[i] = toupper(defName[i]);
	}
	fprintf(stream, "#ifndef %s\n#define %s\n\n", defName, defName);
	free(defName);
}

void create_macro(FILE* stream, const char* name){
	fprintf(stream, "#define %s \\ \n", name);
}

void add_http_headers(FILE* stream, long long *content_length){
	char* content = "\"HTTP/1.1 200 OK \\r\\n\"\\\n"            \
					"\"Content-Type:text/html\\r\\n\"\\\n"      \
					"\"Content-Length: %lld\\r\\n\"\\\n"        \
					"\"Connection: keep-alive\\r\\n\"\\\n"      \
					"\"\\r\\n\"\\\n";
	fprintf(stream, content, *content_length);
}

//Añadir el endif
void close_include_guards(FILE* stream){
	fprintf(stream, "\n#endif");
}

// returns a name after a filepath
// /home/user/helloworld.html -> helloworld
char* get_name_from_filepath(const char* filepath){
	int len = strlen(filepath);
	char* buff = malloc(len+1);
	if(!buff){
		perror("malloc");
		return NULL;
	}
	strncpy(buff, filepath, len);
	char* start = buff;
	bool start_found = false;
	char* end = &buff[len-1];
	bool end_found = false;
	
	for(int i = len-1; i >= 0; i--){
		if(filepath[i] == '.' && !end_found){
			end_found = true;
			end = &buff[i];
		} else if(filepath[i] == '/' && !start_found){
			start_found = true;
			start = &buff[i+1];
		}
	}

	char* result = malloc(len+1);
	if(result){
		memcpy(result, start, end-start);
		result[end - start] = '\0';
	}
	free(buff);
	return result;
}

// Escape invalid characters in line
char* transmute_line(const char* line, int len){
	int initial_len = len;
	char* result = calloc((len)*2+1, sizeof(char));
	if(!result) return NULL;
	int pos = 0;							// pos tracks position on output string
	for(int i = 0; i < initial_len; i++){	// i tracks position on input string
		if(line[i] == '\n') continue;
		if(line[i] == '\'' || line[i] == '\"' || line[i] == '\\'){
			result[pos++] = '\\';
		}
		result[pos++] = line[i];
	}
	result[pos] = '\0';
	return result;
}

// write line on output with propper formatting
void write_line(char* line, FILE* stream){
	fprintf(stream, "\"%s\"\\\n", line);
}