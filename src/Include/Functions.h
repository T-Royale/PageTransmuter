#ifndef FUNCTIONS_PAGETRANSMUTER_H
#define FUNCTIONS_PAGETRANSMUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>

// Definiciones de constantes
#define HTML_DIR "../HTML_AQUI/"
#define Saved_adr "../Program_files/Saved_adresses.bin"

//Indica que el programa ha salido correctamente
#define final "=======================\nHa salido correctamente\n======================="

// Valores Boleanos
#define true 1
#define false 0

// Declaración de variables externas
extern char* HTML_ELEGIDO;
extern bool limpiarEnInicio;
extern bool DebugMode;

// Estructura Rutas_t
typedef struct Rutas_t {
    char nombre[20];
    char path[FILENAME_MAX];
} Rutas_t;

// Declaraciones de variables
extern int nDirecciones;
extern Rutas_t* Rutas;

// Declaraciones de funciones
void CerrarPrograma();
void LeerRutas();
void MostrarRutasGuardadas();
void GuardarRutas();
void CrearRuta(Rutas_t ruta_a_crear);
void BorrarRuta(int pos);
int MostrarHTMLdocs();
char* SelectHTMLdocs(int pos);
void pulirPath(char* string);
bool rutaValida(char* ruta);
void quitarSaltoLineaYEspacios(char* str, bool QuitarEspacios);
bool charValido(char c, char* string, size_t *len);
char* leerLinea(FILE* dir);
bool TieneContenido(char* ruta);
void abrirRuta(char* ruta);
void AddIfndefDefine(FILE* stream, char* name);
void AddDefine(FILE* stream, char* name);
void AddEndif(FILE* stream);
void limpiar();
int inicio();
void ElegirHTML();
Rutas_t* DecidirDestino();
int masOpciones();
void noHayRutas();
void projectName(char* Nombre);
char* TransmutarLinea(FILE* archivoSRC, char* linea);
void TransmutarHTML(char* dest, char* src, char* name);
bool esUltimaLinea(FILE* archivo);

#endif