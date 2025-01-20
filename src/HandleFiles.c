//Aquí irán las funciones que tendrán que ver con acceder a otras direcciones
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
//Pide al usuario que cree la primera ruta del programa
void CrearPrimeraRuta(){
    while(getchar() != '\n');
    limpiar();
    printf( "Anade tu primera ruta a PageTransmuter\n"\
            "Una ruta es la carpeta de tu proyecto donde quieres guardar el archivo transmutado\n"\
            "Puedes anadir mas de una ruta\n"\
            "La ruta se guardara para que la puedas usar mas tarde\n");
    while(getchar() != '\n');
    DefinirNuevaRuta();
}

//HandleFiles.h
//Lee las rutas guardadas y las muestra
void MostrarRutasGuardadas() {
    LeerRutas();
    for(int i = 0; i < nDirecciones; i++){
        printf("%d- %s\n", i,Rutas[i].nombre);
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
    //Verificar que la posición es válida
    if(pos > nDirecciones || pos < 0) return;
    //Confirmación
    bool salir = false;
    while(!salir){
        limpiar();
        printf("Seguro que quieres borrar la siguiente ruta\nNombre: %s\nRuta: %s\nSI(S)/NO(N)\n", Rutas[pos].nombre, Rutas[pos].path);
        char c = getchar();
        if(c == 's' || c == 'S') salir = true;
        else if(c == 'n' || c == 'N') return;
    }
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

    if(!LookforCSS)snprintf(rutaBusqueda, sizeof(rutaBusqueda)/sizeof(char), "%s*.html", HTML_DIR);
    else snprintf(rutaBusqueda, sizeof(rutaBusqueda)/sizeof(char), "%s*.css", HTML_DIR);
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

    if(!LookforCSS)snprintf(rutaBusqueda,sizeof(rutaBusqueda) ,"%s*.html", HTML_DIR);
    else snprintf(rutaBusqueda,sizeof(rutaBusqueda) ,"%s*.css", HTML_DIR);

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
    snprintf(rutaCompleta, MAX_PATH, "%s\\%s", HTML_DIR, nombreArchivo);

    free(nombreArchivo);

    return rutaCompleta; // devolver la ruta completa
}
//HandleFiles.h
//Formatea una ruta para que sean de un único formato
void pulirPath(char* string) {
    int len = strlen(string);
    for(int i = 0; i < len; i++){
        switch(string[i]){
            case '\\':
                string[i] = '/';
                break;
            case '\n':
                string[i] = '\0';
                break;
            case '\"':
                for (int j = i; j < len; j++) {
                    string[j] = string[j + 1];
                }
                len--;
                break;
            default:
                break;
        }
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
//HandleFiles.h
//Verifica los archivos del programa
void verificarArchivos(){
    int nArchivos = 2;
    char *archivos_de_programa[] = {"../Program_files/Instrucciones.bin", "../Program_files/Saved_adresses.bin"};
    FILE *current = NULL;
    for(int i = 0; i < nArchivos; i++){
        current = fopen(archivos_de_programa[i], "r");
        if(current == NULL) {
            system("cls");
            system("color 4");
            perror("Faltan archivos del programa\nPrueba a reinstalar PageTransmuter");
            system("pause");
            CerrarPrograma();
        }
    }
}
//HandleFiles.h
//Obtiene el tamaño del archivo HTML
long long get_content_length(char* filename) {
    FILE *file = fopen(filename, "rb"); // Abrir el archivo en modo binario
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return -1LL;
    }

    // Mover el puntero al final del archivo
    if (_fseeki64(file, 0, SEEK_END) != 0) {
        perror("Error al mover el puntero del archivo");
        fclose(file);
        return -1LL;
    }

    // Obtener la posición del puntero, que es el tamaño del archivo
    unsigned long filesize = _ftelli64(file);
    if (filesize == -1LL) {
        perror("Error al obtener el tamaño del archivo");
        fclose(file);
        return -1LL;
    }

    fclose(file); // Cerrar el archivo
    return filesize;
}