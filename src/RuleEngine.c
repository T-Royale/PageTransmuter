//Aquí irá el proceso de1 adaptar el codigo HTML a un header de C++

//Cabeceras del proyecto
#include "Include/Functions.h"

//RuleEngine.h
//Lee el HTML y lo analiza
void TransmutarHTML(char* dest, char* src, char* name){
    char headerPath[MAX_PATH];  //Ruta del header
    if(hppFile) snprintf(headerPath, sizeof(headerPath), "%s/%s.hpp", dest, name);
    else snprintf(headerPath, sizeof(headerPath), "%s/%s.h", dest, name);
    printf("%s\n", headerPath);
    FILE *HeaderFile = fopen(headerPath, "w");
    AddIfndefDefine(HeaderFile, name);
    AddDefine(HeaderFile, name);
    LowLevelHeader(HeaderFile);

    FILE *HTML_FILE = fopen(src, "r");
    char *RawLinea = NULL;  //Línea recién leida

    while ((RawLinea = leerLinea(HTML_FILE)) != NULL) {
        char* linea = TransmutarLinea(HTML_FILE, RawLinea);
        nLineas++;
        if (linea != NULL) {
            //Será NULL cuando sea la última línea del documento
            fprintf(HeaderFile, "%s\n", linea);
            free(linea);  // Liberar memoria de la línea transmutada
        }
        free(RawLinea);  // Liberar memoria de la línea original
    }

    AddEndif(HeaderFile);
    fclose(HTML_FILE);
    fclose(HeaderFile);
}
//RuleEngine.h
//Comprueba si la línea leida es la última
bool esUltimaLinea(FILE *archivo) {
    long pos = ftell(archivo);  // Guarda posicion inicial
    int c = fgetc(archivo);

    if (c == EOF) {
        return true;
    }
    
    fseek(archivo, pos, SEEK_SET);  // Vuelve a pos
    return false;
}
//RuleEngine.h
//Añade comillas y barra invertida a la cadena
char* TransmutarLinea(FILE *archivoSRC, char *linea) {
    size_t len = strlen(linea) + 7;  // Espacio para las comillas, el '\0' y el \r\n
    char* result = malloc(len * sizeof(char));
    if (result == NULL) {
        perror("Error en malloc");
        return NULL;
    }

    // Formatear la línea con comillas
    snprintf(result, len,"\"%s\\r\\n\"", linea);

    // Si no es la última línea, añadir barra invertida y espacio
    bool UltimaLinea = esUltimaLinea(archivoSRC);
    if (!UltimaLinea) {
        // Para el espacio, la barra invertida, el null terminator y la última línea en caso de ser lowlevel
        len += (LowLevelHTML) ? 5 : 3;  
        char* newResult = realloc(result, len * sizeof(char));
        if (newResult == NULL) {
            perror("Error en realloc");
            free(result);
            return NULL;
        }

        result = newResult;
        strncat(result, " \\", len);  // Añadir barra invertida y espacio
    }
    else if(LowLevelHTML) strncat(result, " \\\n", len);
    //retorna la línea transmutada
    return result;
}
//RuleEngine.h
//Si el caracter no es valido lo escapa
bool charValido(char c, char* string, size_t *len){
    //Se ejecuta mientras lee la línea
    //Manejar comillas dobles
    if(c == '\''){
        string[(*len)++] = '\\';
        string[(*len)++] = '\'';
        return false;
    }
    //Manejar comillas dobles
    if(c == '"'){
        string[(*len)++] = '\\';
        string[(*len)++] = '\"';
        return false;
    }
    //Manejar barra invertida
    if(c == '\\'){
        string[(*len)++] = '\\';
        string[(*len)++] = '\\';
        return false;
    }
    return true;
}