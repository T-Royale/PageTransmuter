#include "Include/Functions.h"

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
        usleep(250 * 1000);
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
int MostrarHTMLdocs() {
    DIR *dir;
    struct dirent *entry;
    int i = 0;

    // Abre el directorio HTML_DIR
    dir = opendir(HTML_DIR);
    if (dir == NULL) {
        perror("No se pudo abrir el directorio HTML_DIR");
        return -1;
    }

    // Lee cada archivo en el directorio
    while ((entry = readdir(dir)) != NULL) {
        // Verifica si el archivo tiene la extensión .html
        if (strstr(entry->d_name, ".html") != NULL) {
            printf("%d- %s\n", i, entry->d_name);
            i++;
        }
    }

    closedir(dir);
    return i;
}

//Handlefiles.h
//Devuelve la cadena de la ruta en la posición (pos)
char *SelectHTMLdocs(int pos) {
    DIR *dir;
    struct dirent *entry;
    int i = 0;
    char *rutaCompleta = NULL;

    // Abre el directorio HTML_DIR
    dir = opendir(HTML_DIR);
    if (dir == NULL) {
        perror("No se pudo abrir el directorio HTML_DIR");
        return NULL;
    }

    // Lee cada archivo en el directorio
    while ((entry = readdir(dir)) != NULL) {
        // Verifica si el archivo tiene la extensión .html
        if (strstr(entry->d_name, ".html") != NULL) {
            if (i == pos) {
                // Asigna memoria para la ruta completa
                rutaCompleta = malloc(strlen(HTML_DIR) + strlen(entry->d_name) + 2);
                if (rutaCompleta != NULL) {
                    sprintf(rutaCompleta, "%s%s", HTML_DIR, entry->d_name);
                }
                break; // Encontramos el archivo en la posición deseada
            }
            i++;
        }
    }

    closedir(dir);
    return rutaCompleta; // Devuelve la ruta completa del archivo en la posición pos
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
extern bool charValido(char c, char* string, size_t *len);
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
    char msg[6 + FILENAME_MAX];
    snprintf(msg, sizeof(msg), "xdg-open \"%s\"", ruta);
    system(msg);
}