//Aquí irán las funciones que tendrán que ver con acceder a otras direcciones
#include "Include/Functions.h"

#define HTML_DIR "../HTML_AQUI/"

#define Saved_adr "../Program_files/Saved_adresses.bin"

extern void limpiar();

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
//Devuelve la cadena de la ruta en la posición (pos)
char *SelectHTMLdocs(int pos) {
    WIN32_FIND_DATA findFile;
    char rutaBusqueda[MAX_PATH];

    sprintf(rutaBusqueda, "%s*.html", HTML_DIR);
    HANDLE hFind = FindFirstFile(rutaBusqueda, &findFile);

    if (hFind == INVALID_HANDLE_VALUE) return NULL; // Manejo de errores

    char* nombreArchivo = NULL;

    for (int i = 0; i <= pos; i++) {
        if (i == pos) {
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
bool rutaValida(char* ruta){
    //Formatea la ruta
    pulirPath(ruta);
    //comprobar si tiene espacios
    for(int i = 0; i < strlen(ruta); i++){
        if(ruta[i] == ' ') return false;
    }
    //Si existe devuelve 0 (falso) al if
    return (access(ruta, F_OK)) ? false : true;
}
//HandleFiles.h
//Quitar salto de linea (y espacios)
void quitarSaltoLineaYEspacios(char* str, bool QuitarEspacios){
    for(int i = 0; i < strlen(str);i++){
        if(str[i] == '\n') str[i] = '\0';
        if (QuitarEspacios) if(str[i] == ' ') str[i] = '_';
    }
}
//HandleFiles.h
//Leer línea que no se su tamaño
//Escapa los caracteres no validos
char* leerLinea(FILE* dir) {
    size_t tam = 10; //Tamaño maximo de la cadena
    size_t len = 0; //Tamaño actual de la cadena
    char c; //Caracter leido
    char* result = calloc(tam, sizeof(char));

    if (result == NULL) {
        return NULL; // Verificamos si la reserva de memoria falló
    }
    //Mientras haya caracteres para leer
    while((c = fgetc(dir)) != EOF && c != '\n'){
        //Si hay que darle mas memoria
        if(len + 1 >= tam){
            tam *= 2;
            char* newResult = realloc(result, sizeof(char) * tam);

            if(newResult == NULL){
                free(result);
                return NULL;
            }
            result = newResult;
        }
        if(charValido(c, result, &len)) result[len++] = c;
    }
    //Si no ha leido nada
    if (len == 0 && c == EOF) {
        free(result);
        return NULL;
    }

    result[len] = '\0';
    return result;
}
//HandleFiles.h
//Devuelve true el archivo tiene contenido
bool TieneContenido(char* ruta){
    FILE* archivo = fopen(ruta, "r");
    char c;
    c = fgetc(archivo);
    fclose(archivo);
    return (c == EOF) ? false : true;
}
//HandleFiles.h
//Inicia la ruta donde esta guardado el header
void abrirRuta(char* ruta){
    char msg[6 + MAX_PATH] = "start ";
    snprintf(msg, sizeof(msg), "start %s", ruta);
    system(msg);
}
