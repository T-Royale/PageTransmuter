//Aquí irán las funciones que tendrán que ver con acceder a otras direcciones
#ifndef HANDLE_FILES_H
#define HANDLE_FILES_H
#include "Messages.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define HTML_DIR "../HTML_AQUI/"

#define Saved_adr"../Program_files/Saved_adresses.txt"

typedef struct Rutas_t{
    char nombre[20]; //Nombre de la ubicación
    char path[MAX_PATH];   //Dirección que guarda
} Rutas_t;

//Número de direcciones
int nDirecciones = 0;

//Array global de rutas
Rutas_t *Rutas = NULL;

//HandleFiles.h
//Termina el programa de forma segura
void CerrarPrograma(){
    if(Rutas != NULL) free(Rutas);
    exit(1);
}

//HandleFiles.h
//Leer rutas gruardadas
void LeerRutas() {
    FILE *Direccion = fopen(Saved_adr, "r");
    char Buffer[MAX_PATH];
    fgets(Buffer, MAX_PATH, Direccion);
    sscanf(Buffer, "Numero elementos: %d\n",&nDirecciones);
    Rutas = calloc(nDirecciones, sizeof(Rutas_t));
    for (int i = 0; i < nDirecciones; i++) {
        if (fgets(Buffer, sizeof(Buffer), Direccion) != NULL) {
            sscanf(Buffer, "%s, %s\n", Rutas[i].nombre, Rutas[i].path);
        }
    }
    fclose(Direccion);
}


//HandleFiles.h
//Mostrar rutas guardadas
void MostrarRutasGuardadas() {
    limpiar();
    LeerRutas();
    for(int i = 0; i < nDirecciones; i++){
        printf("%d- %s\n", i,Rutas[i].nombre);
    }
    system("pause");
}


//HandleFiles.h
//Guardar rutas
void GuardarRutas() {
    FILE *Direccion = fopen(Saved_adr, "w");
    fprintf(Direccion, "Numero elementos: %d\n", nDirecciones);
    for(int i = 0; i < nDirecciones; i++){
        fprintf(Direccion, "%s, %s\n",Rutas[i].nombre, Rutas[i].path);
    }
    fclose(Direccion);
}


//HandleFiles.h
//Crear ruta
//Pasar Rutas_t como argumento
void CrearRuta(Rutas_t ruta_a_crear) {
    FILE *Direccion = fopen(Saved_adr, "a");
    fprintf(Direccion, "%s, %s\n", ruta_a_crear.nombre, ruta_a_crear.path);
    fclose(Direccion);
    LeerRutas();
    GuardarRutas();
}


//HandleFiles.h
//Borrar Ruta
//Pasar Rutas_t como argumento
void BorrarRuta(Rutas_t ruta_a_borrar){
    char linea[MAX_PATH];    //línea leida
    char esperada[MAX_PATH]; //Línea esperada (para eliminar)
    sprintf(esperada, "%s, %s\n", ruta_a_borrar.nombre, ruta_a_borrar.path);
    FILE *save = fopen(Saved_adr, "r"); //abrir para leer y reemplazar el contenido
    FILE *temp = fopen("../Program_files/temp.txt","w"); //abrir para almacenar contenido
    while(fgets(linea, sizeof(linea), save) != NULL){
        if(strcmp(linea, esperada) != 0){   //Si no son iguales
            fprintf(temp, "%s", linea); //Imprime el resultado
        }
    }
    fclose(save);
    fclose(temp);
    remove(Saved_adr);
    rename("../Program_files/temp.txt", Saved_adr);
    GuardarRutas();
}

//HandleFiles.h
//Muestra los documentos HTML en la carpeta
//Devuelve el número de archivos encontrados
int MostrarHTMLdocs(){
    WIN32_FIND_DATA findFile;
    char rutaBusqueda[MAX_PATH];
    int i = 0;

    sprintf(rutaBusqueda, "%s*.html", HTML_DIR); // Usar rutaBusqueda correctamente

    HANDLE hFind = FindFirstFile(rutaBusqueda, &findFile); // Corregido aquí


    if(hFind == INVALID_HANDLE_VALUE){
        return -1;
    }
    do {
        const char* nombreArchivo = findFile.cFileName;
        printf("%d- %s\n", i, nombreArchivo);
        i++;
    } while(FindNextFile(hFind, &findFile) != 0);

    FindClose(hFind);
    return i;
}
//Handlefiles.h
//Devuelve un puntero a la dirección de la ruta completa
char *SelectHTMLdocs(int elegido) {
    WIN32_FIND_DATA findFile;
    char rutaBusqueda[MAX_PATH];

    sprintf(rutaBusqueda, "%s*.html", HTML_DIR);
    HANDLE hFind = FindFirstFile(rutaBusqueda, &findFile);

    if (hFind == INVALID_HANDLE_VALUE) return NULL; // Manejo de errores

    char* nombreArchivo = NULL;

    for (int i = 0; i <= elegido; i++) {
        if (i == elegido) {
            nombreArchivo = malloc(strlen(findFile.cFileName) + 1);
            strcpy(nombreArchivo, findFile.cFileName);
            break; // Encontramos el archivo
        }
        FindNextFile(hFind, &findFile); // Avanzar al siguiente
    }

    FindClose(hFind);
    char* rutaCompleta = malloc(MAX_PATH);
    sprintf(rutaCompleta, "%s\\%s", HTML_DIR, nombreArchivo);

    free(nombreArchivo);

    return rutaCompleta; // devolver la ruta completa
}

#endif