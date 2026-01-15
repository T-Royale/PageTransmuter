//Headers del programa
#include "Include/Functions.h"

//Comprueba si una dirección es valida
bool valid_path(char* path){
    pulirPath(path);
    return (access(path, F_OK)) ? false : true;
}

//Comprueba si un archivo existe
bool valid_file(char* file){
    FILE* test = fopen(file, "r");
    if(!test) return false;
    fclose(test);
    return true;
}

//Cambia los "\" por "/" y quita un salto de línea
void pulirPath(char* string) {
    int size = strlen(string);
    for(int i = 0; i < size; i++){
        if(string[i] == '\\') string[i] = '/';
        if(string[i] == '\n') string[i] = '\0';
    }
}
/*
//Leer rutas gruardadas
void LeerRutas() {
    FILE *save = fopen(Saved_adr, "rb");
    fread(&nDirecciones, sizeof(int), 1, save);
    Rutas = calloc(nDirecciones, sizeof(Rutas_t));
    fread(Rutas, sizeof(Rutas_t), nDirecciones, save);
    fclose(save);
}

//Lee las rutas guardadas y las muestra
void MostrarRutasGuardadas() {
    LeerRutas();
    for(int i = 0; i < nDirecciones; i++){
        printf("%d- %s\n", i,Rutas[i].nombre);
        usleep(250 * 1000);
    }
}

//Guardar rutas
void GuardarRutas() {
    FILE *save = fopen(Saved_adr, "wb");
    fwrite(&nDirecciones, sizeof(int), 1, save);
    fwrite(Rutas, sizeof(Rutas_t), nDirecciones, save);
    fclose(save);
}

//Crear la primera ruta
void CrearPrimeraRuta(){
    while(getchar() != '\n');
    limpiar();
    printf( "Añade tu primera ruta a PageTransmuter.\n"\
            "Una ruta es la carpeta de tu proyecto donde quieres guardar el archivo transmutado.\n"\
            "Puedes añadir mas de una ruta.\n"\
            "La ruta se guardará para que la puedas usar más tarde.\n");
    while(getchar() != '\n');
    DefinirNuevaRuta();
}

//Definir una nueva ruta
void DefinirNuevaRuta(){
    bool salir = false;
    while(!salir){
        limpiar();
        Rutas_t NuevaRuta;

        printf("Nombre de la nueva direccion:");
        //Leer entrada del usuario y consumir carácteres restantes
        if (fgets(NuevaRuta.nombre, sizeof(NuevaRuta.nombre), stdin) != NULL) {
            if (strchr(NuevaRuta.nombre, '\n') == NULL) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }

        printf("Direccion del directorio destino:");
        //Leer entrada del usuario y consumir carácteres restantes
        if (fgets(NuevaRuta.path, sizeof(NuevaRuta.path), stdin) != NULL) {
            if (strchr(NuevaRuta.path, '\n') == NULL) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }

        quitarSaltoLineaYEspacios(NuevaRuta.nombre, true);
        quitarSaltoLineaYEspacios(NuevaRuta.path, false);

        printf("Seguro que quieres añadir la siguiente ruta:\nNombre: %s\nPath: %s\nS/N\n", NuevaRuta.nombre, NuevaRuta.path);
        char ans = getchar();
        while(getchar() != '\n');
        if(ans == 'n' || ans == 'N'){
            continue;
        }
        if(rutaValida(NuevaRuta.path)){
            limpiar();
            printf("Nuevo destino añadido con éxito\n");
            usleep(1000 * 1000);
            CrearRuta(NuevaRuta);
            return;
        }
        else{
            limpiar();
            system(BASH_COLOR_ROJO);  //rojo para indicar error
            printf("La ruta \"%s\" no es válida.\nAsegúrate de que la ruta es un directorio válido. \
            \nLas rutas con espacios no son válidas, reemplázalos con guiones bajos. \
            \nSi estás seguro prueba a ejecutar PageTransmuter como superusuario.\n",NuevaRuta.path);
            printf("Pulsa ENTER para continuar\n");
            while(getchar() != '\n');
        }
    }
}

//Crear ruta
//Pasar Rutas_t como argumento
void CrearRuta(Rutas_t ruta_a_crear) {
    LeerRutas();
    nDirecciones++;
    Rutas = realloc(Rutas, nDirecciones * sizeof(Rutas_t));
    Rutas[nDirecciones - 1] = ruta_a_crear;
    GuardarRutas();
}

//Borrar Ruta
//Pasar posición a eliminar como argumento
void BorrarRuta(){
    bool posicionvalida = false;
    int eliminar;
    do{
        LeerRutas();
        limpiar();
        printf("Selecciona la ruta que quieres borrar\n");
        MostrarRutasGuardadas();
        scanf("%d", &eliminar);
        // Verificar ruta seleccionada
        if(eliminar >= 0 && eliminar < nDirecciones) posicionvalida = true;
    } while(!posicionvalida);
    //Borrar la ruta
    int nextPos = eliminar;
    for(int i = 0; i < nDirecciones - eliminar; i++, nextPos++){
        Rutas[nextPos] = Rutas[nextPos+1];
    }
    nDirecciones--;
    GuardarRutas();
}

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
        if (strstr(entry->d_name, (LookforCSS) ? ".css" : ".html") != NULL) {
            printf("%d- %s\n", i, entry->d_name);
            i++;
        }
    }

    if(i == 0){
        printf((LookforCSS) ?   "No se han encontrado arhcivos .css en la carpeta HTML_AQUI\n" : 
                                "No se han encontrado arhcivos .html en la carpeta HTML_AQUI\n");
        printf("Abrir la carpeta HTML_AQUI");
        while(getchar() != '\n');
        abrirRuta(HTML_DIR);
        CerrarPrograma();
    }

    closedir(dir);
    return i;
}

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
        if (strstr(entry->d_name, ".html") != NULL || strstr(entry->d_name, ".css") != NULL ) {
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

//Quitar salto de linea (y espacios)
void quitarSaltoLineaYEspacios(char* str, bool QuitarEspacios){
    for(int i = 0; i < strlen(str);i++){
        if(str[i] == '\n') str[i] = '\0';
        if (QuitarEspacios) if(str[i] == ' ') str[i] = '_';
    }
}

//Leer línea que no se su tamaño
//Escapa los caracteres no validos
char* leerLinea(FILE* dir) {
    size_t tam = 10; //Tamaño maximo de la cadena
    size_t len = 0;  //Tamaño real de la cadena
    char c; //Caracter leido
    char* result = calloc(tam, sizeof(char));

    if (result == NULL) {
        return NULL; // Verificamos si la reserva de memoria falló
    }
    //Mientras haya caracteres para leer
    while((c = fgetc(dir)) != EOF && c != '\n'){
        //Si hay que darle mas memoria
        if(len+2 >= tam){
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
//Devuelve true el archivo tiene contenido
bool TieneContenido(char* ruta){
    FILE* archivo = fopen(ruta, "r");
    char c;
    c = fgetc(archivo);
    fclose(archivo);
    return (c == EOF) ? false : true;
}
//Inicia la ruta donde esta guardado el header
void abrirRuta(char* ruta){
    char msg[6 + FILENAME_MAX];
    snprintf(msg, sizeof(msg), "xdg-open \"%s\"", ruta);
    system(msg);
}

//Verifica los archivos del programa
void verificarArchivos(){
    // No hace falta comprobar si HTML_AQUI existe, mkdir -p lo creará si no existe
    char crear_html_dir[FILENAME_MAX] = {0};
    snprintf(crear_html_dir, FILENAME_MAX, "mkdir -p ./%s", HTML_DIR);
    system(crear_html_dir);
    int nArchivos = 2;
    char *archivos_de_programa[] = {Instrucciones_adr, Saved_adr};
    FILE *current = NULL;
    for(int i = 0; i < nArchivos; i++){
        current = fopen(archivos_de_programa[i], "r");
        if(current == NULL) {
            system("clear");
            system(BASH_COLOR_ROJO);
            perror("Faltan archivos del programa\nPrueba a reinstalar PageTransmuter");
            CerrarPrograma();
        }
    }
}

//Obtiene el tamaño del archivo HTML
long long get_content_length(char* filename) {
    FILE *file = fopen(filename, "rb"); // Abrir el archivo en modo binario
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return -1LL;
    }

    // Mover el puntero al final del archivo
    if (fseeko(file, 0, SEEK_END) != 0) {
        perror("Error al mover el puntero del archivo");
        fclose(file);
        return -1LL;
    }

    // Obtener la posición del puntero, que es el tamaño del archivo
    off_t filesize = ftello(file);

    if(filesize == -1) {
        perror("Error al leer el tamaño del archivo");
        fclose(file);
        return -1LL;
    }
    fclose(file); // Cerrar el archivo
    return (long long)filesize;
}
*/