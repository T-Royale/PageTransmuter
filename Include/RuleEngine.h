//Aquí irá el proceso de1 adaptar el codigo HTML a un header de C++
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
//Firmas de funciones
char* TransmutarLinea(FILE *archivoSRC, char *linea);

void TransmutarHTML(char* dest, char* src, char* name){
    char headerPath[MAX_PATH];  //Ruta del header
    sprintf(headerPath, "%s/%s.h", dest, name);
    printf("%s\n", headerPath);
    FILE *HeaderFile = fopen(headerPath, "w");
    AddIfndefDefine(HeaderFile, name);
    AddDefine(HeaderFile, name);

    FILE *HTML_FILE = fopen(src, "r");
    char *RawLinea = NULL;  //Línea recién leida

    while ((RawLinea = leerLinea(HTML_FILE)) != NULL) {
        char* linea = TransmutarLinea(HTML_FILE, RawLinea);
        if (linea != NULL) {
            fprintf(HeaderFile, "%s\n", linea);
            free(linea);  // Liberar memoria de la línea transmutada
        }
        free(RawLinea);  // Liberar memoria de la línea original
    }

    AddEndif(HeaderFile);
    fclose(HTML_FILE);
    fclose(HeaderFile);
    free(RawLinea);
}
//RuleEngine.h
//Comprueba si la línea leida es la última
bool esUltimaLinea(FILE *archivo) {
    long pos = ftell(archivo);  // Guarda posicion inicial
    int c = fgetc(archivo);

    if (c == EOF) {
        return true;
    }
    
    fseek(archivo, pos, SEEK_SET);  // Vuelve a pos
    return false;
}
//RuleEngine.h
//Función que analizará la línea leida
char* TransmutarLinea(FILE *archivoSRC, char *linea) {
    size_t len = strlen(linea) + 3;  // Espacio para las comillas y el null terminator
    char* result = malloc(len * sizeof(char));
    if (result == NULL) {
        perror("Error en malloc");
        return NULL;
    }

    // Formatear la línea con comillas
    sprintf(result, "\"%s\"", linea);

    // Si no es la última línea, añadir barra invertida y espacio
    if (!esUltimaLinea(archivoSRC)) {
        len += 3;  // Para el espacio, la barra invertida y el null terminator
        char* newResult = realloc(result, len * sizeof(char));
        if (newResult == NULL) {
            perror("Error en realloc");
            free(result);
            return NULL;
        }

        result = newResult;
        strcat(result, " \\");  // Añadir barra invertida y espacio
    }

    return result;
}

#endif