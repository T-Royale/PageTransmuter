//Aquí irán las funciones que tendrán que ver con acceder a otras direcciones
#ifndef HANDLE_FILES_H
#define HANDLE_FILES_H
#include "Messages.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>

#define HTML_DIR "../HTML_AQUI/"

#define Saved_adr "../Program_files/Saved_adresses.bin"

extern void limpiar();

typedef struct Rutas_t{
    char nombre[20]; //Nombre de la ubicación
    char path[MAX_PATH];   //Dirección que guarda
} Rutas_t;

//Número de direcciones
int nDirecciones = 0;

//HandleFiles.h
//Array global de rutas
Rutas_t *Rutas = NULL;

extern char* HTML_ELEGIDO;

//HandleFiles.h
//Termina el programa de forma segura
void CerrarPrograma(){
    if(Rutas != NULL) free(Rutas);
    if(HTML_ELEGIDO != NULL) free(HTML_ELEGIDO);
    exit(0);
}

//HandleFiles.h
//Leer rutas gruardadas
void LeerRutas() {
    FILE *save = fopen(Saved_adr, "rb");
    fread(&nDirecciones, sizeof(int), 1, save);
    Rutas = calloc(nDirecciones, sizeof(Rutas_t));
    fread(Rutas, sizeof(Rutas_t), nDirecciones, save);
    fclose(save);
}


//HandleFiles.h
//Lee las rutas guardadas y las muestra
void MostrarRutasGuardadas() {
    LeerRutas();
    for(int i = 0; i < nDirecciones; i++){
        printf("%d- %s", i,Rutas[i].nombre);
        Sleep(250);
    }
}


//HandleFiles.h
//Guardar rutas
void GuardarRutas() {
    FILE *save = fopen(Saved_adr, "wb");
    fwrite(&nDirecciones, sizeof(int), 1, save);
    fwrite(Rutas, sizeof(Rutas_t), nDirecciones, save);
    fclose(save);
}


//HandleFiles.h
//Crear ruta
//Pasar Rutas_t como argumento
void CrearRuta(Rutas_t ruta_a_crear) {
    LeerRutas();
    nDirecciones++;
    Rutas = realloc(Rutas, nDirecciones * sizeof(Rutas_t));
    Rutas[nDirecciones - 1] = ruta_a_crear;
    GuardarRutas();
}


//HandleFiles.h
//Borrar Ruta
//Pasar posición a eliminar como argumento
void BorrarRuta(int pos){
    LeerRutas();
    //Borrar la ruta
    int nextPos = pos;
    for(int i = 0; i < nDirecciones - pos; i++, nextPos++){
        if(&Rutas[nextPos+1] == NULL) break;
        Rutas[nextPos] = Rutas[nextPos+1];
    }
    nDirecciones--;
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
//HandleFiles.h
//Cambia los "\" por "/" y quita un salto de línea
void pulirPath(char* string) {
    int size = strlen(string);
    for(int i = 0; i < size; i++){
        if(string[i] == '\\') string[i] = '/';
        if(string[i] == '\n') string[i] = '\0';
    }
}
//HandleFiles.h
//Comprueba si una dirección es valida
bool rutaValida(Rutas_t Ruta){
        //Verificar si la ruta es valida
        pulirPath(Ruta.path);
        const char *verificar = Ruta.path;
        //Si existe devuelve 0 (falso) al if
        return (access(verificar, F_OK)) ? false : true;
}

void quitarSaltoLinea(char* str){
    for(int i = 0; i < strlen(str);i++){
        if(str[i] == '\n') str[i] = '\0';
    }
}

#endif