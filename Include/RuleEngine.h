//Aquí irán todas las funciones que tengan que ver con adaptar el codigo HTML a un header de C++
#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H
//Librerías de C
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
//Cabeceras del proyecto
#include "../include/Messages.h"
#include "../include/HandleFiles.h"
#include "HeaderCreation.h"

void TransmutarHTML(char* dest, char* src, char* name){
    char headerPath[MAX_PATH];  //Ruta del header
    sprintf(headerPath, "%s/%s.h", dest, name);   //De momento lo crearemos como un txt
    printf("%s\n", headerPath);
    FILE *HeaderFile = fopen(headerPath, "w");
    AddIfndefDefine(HeaderFile, name);
    fclose(HeaderFile);
}

#endif