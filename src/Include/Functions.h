#ifndef FUNCTIONS_PAGETRANSMUTER_H
#define FUNCTIONS_PAGETRANSMUTER_H

#define version "ALPHA 1.0"

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>

//Codigos de colores terminal linux
#define BASH_COLOR_VERDE "tput setaf 2"
#define BASH_COLOR_ROJO  "tput setaf 1"
#define BASH_COLOR_RESET "tput sgr0"

// Estructura de rutas
typedef struct {
    char nombre[50];     // Nombre de la ubicación
    char path[FILENAME_MAX]; // Dirección que guarda
} Rutas_t;

// Macros
#define final "=======================\nHa salido correctamente\n=======================\n"
#define HTML_DIR "HTML_AQUI/"
#define Saved_adr "Program_files/Saved_adresses.bin"
#define Instrucciones_adr "Program_files/Instrucciones.bin"
#define MAX_NAME_LEN 20
#define true 1
#define false 0

// Variables globales (en main.c)
extern bool limpiarEnInicio;
extern bool DebugMode;
extern char* HTML_ELEGIDO;
extern int nDirecciones;
extern Rutas_t *Rutas;
extern bool LowLevelHTML;
extern bool hppFile;
extern bool LookforCSS;
extern bool ayuda;
extern int nLineas;

// Declaraciones de funciones

// Funciones de interacción con el usuario
void ComprobarArgumentos(int argc, char *argv[]);
void limpiar();
int inicio();
void ElegirHTML();
Rutas_t* DecidirDestino();
int masOpciones();
void projectName(char* Nombre, int len);
void linealarga(int n);

// Funciones de procesamiento del HTML
void TransmutarHTML(char* dest, char* src, char* name);
bool esUltimaLinea(FILE* archivo);
char* TransmutarLinea(FILE* archivoSRC, char* linea);
bool charValido(char c, char* string, size_t* len);

// Funciones para la creación del header
void AddIfndefDefine(FILE* stream, char* name);
void AddDefine(FILE* stream, char* name);
void LowLevelHeader(FILE* stream);
void AddEndif(FILE* stream);

// Manejo de archivos y rutas
void CerrarPrograma();
void LeerRutas();
void MostrarRutasGuardadas();
void GuardarRutas();
void DefinirNuevaRuta();
void CrearPrimeraRuta();
void CrearRuta(Rutas_t ruta_a_crear);
void BorrarRuta();
int MostrarHTMLdocs();
char* SelectHTMLdocs(int pos);
void pulirPath(char* string);
bool rutaValida(char* ruta);
void quitarSaltoLineaYEspacios(char* str, bool QuitarEspacios);
char* leerLinea(FILE* dir);
bool TieneContenido(char* ruta);
void abrirRuta(char* ruta);
void verificarArchivos();
long long get_content_length(char* filename);

//Logo de inicio
#define PageTransmuter \
" _____              _______                                  _\n" \
"|  __ \\            |__   __|                                | |\n" \
"| |__) |_ _  __ _  ___| |_ __ __ _ _ __  ___ _ __ ___  _   _| |_ ___ _ __\n" \
"|  ___/ _` |/ _` |/ _ \\ | '__/ _` | '_ \\/ __| '_ ` _ \\| | | | __/ _ \\ '__|\n" \
"| |  | (_| | (_| |  __/ | | | (_| | | | \\__ \\ | | | | | |_| | ||  __/ |\n" \
"|_|   \\__,_|\\__, |\\___|_|_|  \\__,_|_| |_|___/_| |_| |_|\\__,_|\\__\\___|_|\n" \
"             __/ |\n"\
"            |___/\n"

#endif
