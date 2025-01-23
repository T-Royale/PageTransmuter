#include "Include/Functions.h"

//HeaderCreation.h
//Añadir el #ifndef ... #define ...
void AddIfndefDefine(FILE* stream, char* name){
    char defName[30];
    sprintf(defName, "%s_H", name);
    for(int i = 0; i < strlen(defName); i++){
        if(defName[i] == ' ') defName[i] = '_';
        if(islower(defName[i])) defName[i] = toupper(defName[i]);
    }
    fprintf(stream, "#ifndef %s\n#define %s\n\n", defName, defName);
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