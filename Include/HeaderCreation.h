//Mensajes y pasos para crear el heather
#ifndef CREATE_HEADER_H
#define CREATE_HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

#include"RuleEngine.h"

void AddIfndefDefine(FILE* stream, char* name){
    char defName[30];
    sprintf(defName, "%s_H", name);
    for(int i = 0; i < strlen(defName); i++){
        if(defName[i] == ' ') defName[i] = '_';
        if(islower(defName[i])) defName[i] = toupper(defName[i]);
    }
    fprintf(stream, "#ifndef %s\n#define %s\n\n", defName, defName);
}
#endif