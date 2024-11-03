#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//Librerías de C
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<windows.h>
#include<io.h>

// Macros
#define final "=======================\nHa salido correctamente\n======================="
#define HTML_DIR "../HTML_AQUI/"
#define Saved_adr "../Program_files/Saved_adresses.bin"

// Estructura de rutas
typedef struct {
    char nombre[20];     // Nombre de la ubicación
    char path[MAX_PATH]; // Dirección que guarda
} Rutas_t;

// Variables globales externas
extern bool limpiarEnInicio;
extern bool DebugMode;
extern char* HTML_ELEGIDO;
extern int nDirecciones;
extern Rutas_t* Rutas;

// Declaraciones de funciones

// Funciones de interacción con el usuario
void limpiar();
int inicio();
void ElegirHTML();
Rutas_t* DecidirDestino();
int masOpciones();
void noHayRutas();
void projectName(char* Nombre);

// Funciones de procesamiento del HTML
void TransmutarHTML(char* dest, char* src, char* name);
bool esUltimaLinea(FILE* archivo);
char* TransmutarLinea(FILE* archivoSRC, char* linea);
bool charValido(char c, char* string, size_t* len);

// Funciones para la creación del header
void AddIfndefDefine(FILE* stream, char* name);
void AddDefine(FILE* stream, char* name);
void AddEndif(FILE* stream);

// Manejo de archivos y rutas
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
char* leerLinea(FILE* dir);
bool TieneContenido(char* ruta);
void abrirRuta(char* ruta);

#endif