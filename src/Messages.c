//Headers del programa
#include "Include/Functions.h"

//Messages.h
//Limpiar la pantalla
void limpiar(){
    system("clear");
    system(BASH_COLOR_VERDE);
}

void ComprobarArgumentos(int argc, char **argv){
    system(BASH_COLOR_RESET);
    int errorlen = 1;
    //Lista de argumentos inválidos
    char *ErrorMessage = calloc(errorlen, sizeof(char));
    bool invalidArgument = true;   //Revisa si el argumento actual es válido
    bool invalidCommand = false;    //Revisa si hay algún argumento invalido
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            invalidArgument = true;
            if(strcmp(argv[i], "-low") == 0) {
                LowLevelHTML = true;
                invalidArgument = false;    //El argumento es valido
            }
            if(strcmp(argv[i], "-cpp") == 0) {
                hppFile = true;
                invalidArgument = false;    //El argumento es valido
            }
            if(strcmp(argv[i], "-css") == 0){
                LookforCSS = true;
                invalidArgument = false;    //El argumento es valido
            }
            if(strcmp(argv[i], "-help") == 0){
                ayuda = true;
                invalidArgument = false;    //El argumento es valido
            }
            //Manejar argumentos invalidos
            if(invalidArgument){
                //Mostrar lista de argumentos invalidos
                invalidCommand = true;
                int argv_len = strlen(argv[i])+2;
                errorlen += argv_len;
                char *NewErrorMessage = realloc(ErrorMessage, errorlen);
                ErrorMessage = NewErrorMessage;
                NewErrorMessage = NULL;
                char tempError[argv_len];
                snprintf(tempError, errorlen, "%s ", argv[i]);
                strncat(ErrorMessage, tempError, errorlen);
            }
        }
        if(LookforCSS && LowLevelHTML){
            printf("ERROR: No es posible aplicar -low y -css al mismo tiempo\n");
            if(!invalidCommand) CerrarPrograma();
        }
        //Una vez se han pasado todos los argumentos
        if(invalidCommand){
            printf("ERROR: Argumentos inválidos encontrados:\n%s\n"\
            "Ejecuta 'PageTransmuter -help' para aprender sobre estas opciones.\n"\
            "Presiona enter para salir de PageTransmuter\n", ErrorMessage);
            free(ErrorMessage);
            while(getchar() != '\n');
            system(BASH_COLOR_RESET);
            CerrarPrograma();
        }
    }
    free(ErrorMessage);
    //Resumen de argumentos
    if(ayuda){
        printf("Opciones adicionales del programa:\n"                               \
        "+ -low: Añade la linea de estado y los encabezados de respuesta HTTP.\n" \
        "+ -cpp: Crea un archivo .hpp en lugar de .h.\n"                            \
        "+ -css: Transmutará archivos .css en lugar de .html.\n");
        CerrarPrograma();
    }
}
//Messages.h
//Mensajes y opciones de inicio
int inicio(){
    if(limpiarEnInicio) limpiar();
    printf(PageTransmuter);
    printf((LookforCSS) ? "Formatea un archivo CSS para usarlo en C y C++\n" : "Formatea un archivo HTML para usarlo en C y C++\n");
    linealarga(50);
    printf("version: %s", version);

    while(getchar() != '\n'); //Limpiar el buffer de entrada
    
    //mostrar opciones de inicio
    bool teclavalida = true;
    //Abrir instrucciones por si se consultan
    FILE *instrucciones;
    char linea[256];
    do {
        limpiar();
        printf("Selecciona una opcion:\n");
        printf((LookforCSS) ? "1- Transmutar CSS\n2- Instrucciones\n3- Salir\n" : "1- Transmutar HTML\n2- Instrucciones\n3- Salir\n");
        char tecla = getchar();
        while(getchar() != '\n'); //Limpiar el buffer de entrada
        teclavalida = true;
        switch(tecla){
            case '1':
                break;
            case '2':
                limpiar();
                //Secuencia de explicación
                instrucciones = fopen(Instrucciones_adr, "rb");
                if (instrucciones == NULL) {
                    perror("Error al abrir el archivo de instrucciones");
                    usleep(500 * 1000);
                    return -1;
                }
                while (fgets(linea, sizeof(linea), instrucciones) != NULL) {
                    printf("%s", linea); // Mostrar cada línea en la terminal
                    usleep(500 * 1000);
                }
                // Cerrar el archivo
                fclose(instrucciones);
                switch (getchar())
                {
                case '1':
                    break;
                case '2':
                    system("xdg-open ../HTML_AQUI/");
                    break;
                case '3':
                    system("xdg-open https://github.com/T-Royale");
                    break;
                case '4':
                    CerrarPrograma();
                    break;
                default:
                    break;
                }
                while(getchar() != '\n'); //Limpiar buffer
                break;
            case '3':
                CerrarPrograma();
                break;
            default: 
                perror("Tecla inválida\nPresiona ENTER para reintentar");
                teclavalida = false;
                break;
        }
    } while(!teclavalida);
    return 0;
}

//Messages.h
//Elegir doucumento HTML a transfusionar
void ElegirHTML(){
    bool salir = false;
    while(!salir){
        limpiar();
        printf((LookforCSS) ? "Selecciona el archivo CSS a Transmutar\n" : "Selecciona el archivo HTML a Transmutar\n");
        int nArchivos = MostrarHTMLdocs();
        
        int eleccion = 0; //Archivo elegido
        scanf("%d", &eleccion);
        if(eleccion > nArchivos - 1 || eleccion < 0){
            system("clear");
            printf("Número no valido\nInténtalo otra vez\n");
            usleep(500 * 1000);
            continue;
        }
        HTML_ELEGIDO = SelectHTMLdocs(eleccion);
        if(!TieneContenido(HTML_ELEGIDO)){
            limpiar();
            system(BASH_COLOR_ROJO);
            printf((LookforCSS) ? "El CSS elegido no tiene contenido\n" : "El HTML elegido no tiene contenido\n");
            usleep(100 * 1000);
            printf("Seleciona otro\n");
            usleep(1000 * 1000);
            continue;
        }
        salir = true;
    }
}

//Messages.h
//Decidir la ruta destino donde será creado el header
Rutas_t* DecidirDestino(){
    if(nDirecciones == 0) CrearPrimeraRuta();
    Rutas_t* rutaElegida;
    bool salir = false;
    while(!salir){
        limpiar();
        printf("Elige la ruta destino:\n");
        MostrarRutasGuardadas();    //nDirecciones es en nº de rutas guardadas+1
        printf("%d- Más opciones\n", nDirecciones);
        int eleccion = 0;
        scanf("%d", &eleccion);
        while(getchar() != '\n');
        if(eleccion > nDirecciones || eleccion < 0) continue;
        if(eleccion == nDirecciones) if(masOpciones() == 0) continue;
        //si no se ha decidido crear ninguna ruta
        rutaElegida = &Rutas[eleccion];
        //Quitar solo salto de linea
        quitarSaltoLineaYEspacios(rutaElegida->path, false);
        //Comprobar si la ruta elegida existe
        if(!rutaValida(rutaElegida->path)){
            limpiar();
            system("BASH_COLOR_ROJO");
            printf("La ruta seleccionada ya no es válida\n");
            usleep(100 * 1000);
            printf("Prueba otra vez\n");
            printf("Pulsa ENTER para continuar");
            while(getchar() != '\n');
            continue;
        }
        salir = true;
    }
    if(DebugMode) printf("La ruta elegida es: %s\n", rutaElegida->path);
    return rutaElegida;
}
//HandleFiles.h
//Más opciones de rutas guardadas
int masOpciones(){
    //Más opciones
    int ans = 0;
    bool salir = false;
    while(!salir){
        limpiar();
        printf("Que quieres hacer?\n\t1. Crear nueva ruta\n\t2. Eliminar ruta existente \
        \n\t3. Volver atrás\n");
        scanf("%d", &ans);
        while(getchar() != '\n');
        //Añadir ruta
        if(ans == 1){
            DefinirNuevaRuta();
        }
        //Borrar ruta
        else if(ans == 2){
            if(nDirecciones == 0){
                CrearPrimeraRuta();
            }
            BorrarRuta();
            if(nDirecciones == 0){
                CrearPrimeraRuta();
            }
            return 0;
        }
        else if(ans == 3){
            return 0;
        }
        //Sino vuelve al principio
        else continue;
        salir = true;
    }
    return 0;
}
extern bool DebugMode;

//Messages.h
//Darle un nombre al proyecto
void projectName(char* Nombre, int len){
    bool salir = false;
    while(!salir){
        salir = true;
        limpiar();
        printf("Nombre del archivo:\n");
        fgets(Nombre, 20, stdin);
        quitarSaltoLineaYEspacios(Nombre, true);
        if(strlen(Nombre) == 0) salir = false;
        if(DebugMode) printf("El nombre del archivo es %s\n", Nombre);
    }
}

//Messages.c
//Imprime una línea horizontal de longitud n
void linealarga(int n){
    for(int i = 0; i < n; i++){
        printf("\u2500");
    }
    printf("\n");
}