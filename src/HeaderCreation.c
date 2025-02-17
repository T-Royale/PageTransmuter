//Headers del programa
#include "Include/Functions.h"

//HeaderCreation.h
//Añadir el #ifndef ... #define ...
void AddIfndefDefine(FILE* stream, char* name){
    char defName[30];
    sprintf(defName, (hppFile) ? "%s_HPP" : "%s_H", name);
    for(int i = 0; i < strlen(defName); i++){
        if(defName[i] == ' ') defName[i] = '_';
        if(islower(defName[i])) defName[i] = toupper(defName[i]);
    }
    fprintf(stream, "#ifndef %s\n#define %s\n\n", defName, defName);
}
//HeaderCreation.h
//Si se aplica -low, añadir líneas necesarias
void LowLevelHeader(FILE* stream){
    if(LowLevelHTML){
        long long Content_Length = get_content_length(HTML_ELEGIDO);
        Content_Length += (nLineas+1)*2;  //Apariciones de \r\n
        fprintf(stream, "\"HTTP/1.1 200 OK \\r\\n\"\\\n"            \
                        "\"Content-Type:text/html\\r\\n\"\\\n"      \
                        "\"Content-Length: %lld\\r\\n\"\\\n"         \
                        "\"Connection: keep-alive\\r\\n\"\\\n"      \
                        "\"\\r\\n\"\\\n", Content_Length);
    }
}
//HeaderCreation.h
//añadir la definición de la macro que devolverá el HTML
void AddDefine(FILE* stream, char* name){
    fprintf(stream, "#define %s \\ \n", name);
}
//HeaderCreation.h
//Añadir el endif
void AddEndif(FILE* stream){
    fprintf(stream, "\n#endif");
}
