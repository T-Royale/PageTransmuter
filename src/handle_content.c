//Headers del programa
#include "Include/Functions.h"

//Añadir el #ifndef ... #define ...
void add_include_guards(FILE* stream, char* name){
    char defName[strlen(name)+1];
    sprintf(defName, "%s_H", name);
    for(int i = 0; i < strlen(defName); i++){
        if(defName[i] == ' ') defName[i] = '_';
        if(islower(defName[i])) defName[i] = toupper(defName[i]);
    }
    fprintf(stream, "#ifndef %s\n#define %s\n\n", defName, defName);
}

//Añadir la definición de la macro que devolverá el HTML
void create_macro(FILE* stream, char* name){
    fprintf(stream, "#define %s \\ \n", name);
}

void add_http_headers(FILE* stream, long long *content_length){
    char* content =  "\"HTTP/1.1 200 OK \\r\\n\"\\\n"            \
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
