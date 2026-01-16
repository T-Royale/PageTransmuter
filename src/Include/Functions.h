#ifndef FUNCTIONS_PAGETRANSMUTER_H
#define FUNCTIONS_PAGETRANSMUTER_H

#define PROGRAM_VERSION "2.0"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <getopt.h>

typedef struct {
    char* output;
    char* input;
    bool http_headers;
    bool help;
    bool version;
} flags_t;

// Declaraciones de funciones
flags_t* flags_get(int argc, char *argv[]);
void flags_free(flags_t* flags);
void print_help(char* program_name);
void print_version();

// Funciones de procesamiento del HTML
void create_macro(FILE* stream, char* name);
void transmute(char* dest, char* src, char* name);
bool is_last_line(FILE* archivo);
char* transmute_line(FILE* archivoSRC, char* linea);
bool char_valid(char c, char* string, size_t* len);

// Funciones para la creación del header
void add_include_guards(FILE* stream, char* name);
void add_http_headers(FILE* stream, long long *content_length);
void close_include_guards(FILE* stream);

// Manejo de archivos y rutas
bool check_path(char* path);
bool validate_html_file(char* file);
void close_files(FILE* input, FILE* output);
long long get_content_length(char* filename);

void CerrarPrograma();
void LeerRutas();
void MostrarRutasGuardadas();
void GuardarRutas();
void DefinirNuevaRuta();
void CrearPrimeraRuta();
void BorrarRuta();
int MostrarHTMLdocs();
char* SelectHTMLdocs(int pos);
void pulirPath(char* string);
void quitarSaltoLineaYEspacios(char* str, bool QuitarEspacios);
char* leerLinea(FILE* dir);
bool TieneContenido(char* ruta);
void abrirRuta(char* ruta);
void verificarArchivos();

#endif