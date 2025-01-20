//Definiciones y funciones que tienen que ver con interactuar con el usuario a través de la terminal

//Funciones del codigo
#include "Include/Functions.h"

//Messages.h
//Limpiar la pantalla
void limpiar(){
    system("cls");
    system("color a");
}

//Messages.h
//Comprueba el programa se ha ejecutado con opciones adicionales
void ComprobarArgumentos(int argc, char *argv[]){
    system("color");
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
            printf("ERROR: Argumentos invalidos encontrados:\n%s\n"\
            "Consulta -help para aprender sobre estas opciones.\n"\
            "Presiona enter para salir de PageTransmuter\n", ErrorMessage);
            free(ErrorMessage);
            while(getchar() != '\n');
            system("color");
            CerrarPrograma();
        }
    }
    free(ErrorMessage);
}


//Messages.h
//Mensajes y opciones de inicio
int inicio(){
    //Resumen de argumentos
    if(ayuda){
        printf("Opciones adicionales del programa:\n"                               \
        "+ -low: Anade la linea de estado y los encabezados a la respuesta HTTP.\n" \
        "+ -cpp: Crea un archivo .hpp en lugar de .h.\n"                            \
        "+ -css: Transmutara archivos .css en lugar de .html.\n");
        CerrarPrograma();
    }
    if(limpiarEnInicio) limpiar();
    printf("Bienvenido a\n");
    printf(PageTransmuter);
    if(!LookforCSS) printf("Formatea un archivo HTML para usarlo en C y C++\n");
    else printf("Formatea un archivo CSS para usarlo en C y C++\n");
    

    while(getchar() != '\n'); //Limpiar el buffer de entrada
    //mostrar opciones de inicio
    bool teclavalida = true;
    //Abrir instrucciones por si se consultan
    FILE *instrucciones;
    do {
        limpiar();
        printf("Selecciona una opcion:\n");
        if(!LookforCSS)printf("1- Transmutar HTML\n2- Instrucciones\n3- Salir\n");
        else printf("1- Transmutar CSS\n2- Instrucciones\n3- Salir\n");
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
                    return -1;
                }
                int c;
                while ((c = fgetc(instrucciones)) != EOF) {
                    putchar(c);
                    Sleep(10);
                }
                // Cerrar el archivo
                fclose(instrucciones);
                switch (getchar())
                {
                case '1':
                    break;
                case '2':
                    system("start ..\\HTML_AQUI\\");
                    break;
                case '3':
                    system("start https://github.com/T-Royale");
                    break;
                case '4':
                    CerrarPrograma();
                    break;
                default:
                    break;
                }
                while(getchar() != '\n'); //Limpiar buffer
                system("cls");
                printf("Hasta la proxima\n");
                CerrarPrograma();
                break;
            case '3':
                CerrarPrograma();
                break;
            default: 
                perror("Tecla invalida\nPresiona ENTER para reintentar");
                teclavalida = false;
                break;
        }
    } while(!teclavalida);
    return 0;
}

//Messages.h
//Elegir doucumento HTML a transmutar
void ElegirHTML(){
    bool salir = false;
    while(!salir){
        limpiar();
        if(!LookforCSS) printf("Selecciona el archivo HTML a Transmutar:\n");
        else printf("Selecciona el archivo CSS a Transmutar:\n");
        int nArchivos = MostrarHTMLdocs();
        if(nArchivos == -1) {
            printf("No se ha encontrado ningún HTML\n");
            CerrarPrograma();
        }
        int eleccion = 0; //Archivo elegido
        scanf("%d", &eleccion);
        if(eleccion > nArchivos - 1 || eleccion < 0){
            system("cls");
            printf("Numero no valido\nIntentalo otra vez\n");
            Sleep(500);
            continue;
        }
        HTML_ELEGIDO = SelectHTMLdocs(eleccion);
        if(!TieneContenido(HTML_ELEGIDO)){
            limpiar();
            system("color c");
            if(!LookforCSS) printf("El HTML elegido no tiene contenido\n");
            else printf("El CSS elegido no tiene contenido\n");
            Sleep(100);
            printf("Seleciona otro\n");
            Sleep(1000);
            continue;
        }
        salir = true;
    }
}

extern bool DebugMode;

//Messages.h
//Decidir la ruta destino donde será creado el header
Rutas_t* DecidirDestino(){
    bool salir = false;
    while(!salir){
        if(nDirecciones == 0) {
            CrearPrimeraRuta();
        }
        else {
            limpiar();
            printf("Elige la ruta destino:\n");
            MostrarRutasGuardadas();    //nDirecciones es en nº de rutas guardadas+1
            printf("%d- Mas opciones\n", nDirecciones);
            int eleccion = 0;
            scanf("%d", &eleccion);
            while(getchar() != '\n');
            if(eleccion > nDirecciones || eleccion < 0) continue;
            if(eleccion == nDirecciones) {
                masOpciones();
                continue;
            }
            //si no se ha decidido crear ninguna ruta
            Rutas_t* rutaElegida = &Rutas[eleccion];
            //Quitar solo salto de linea
            quitarSaltoLineaYEspacios(rutaElegida->path, false);
            //Comprobar si la ruta elegida existe
            if(!rutaValida(rutaElegida->path)){
                limpiar();
                system("color c");
                printf("La ruta seleccionada ya no es valida\n");
                Sleep(100);
                printf("Prueba otra vez\n");
                system("pause");
                continue;
            }
            if(DebugMode) printf("La ruta elegida es: %s\n", rutaElegida->path);
            return rutaElegida;
        }
    }
    return NULL;
}
//HandleFiles.h
//Más opciones de rutas guardadas
void masOpciones(){
    bool repetir = true;
    while(repetir){
        int ans = 0;
        limpiar();
        printf("Que quieres hacer?\n\t1. Crear nueva ruta\n\t2. Eliminar ruta existente \
        \n\t3. Volver atras\n");
        scanf("%d", &ans);
        while(getchar() != '\n');
        //Añadir ruta
        if(ans == 1){
            DefinirNuevaRuta();
        }
        //Borrar ruta
        else if(ans == 2){
            int eliminar;
            limpiar();
            printf("Selecciona la ruta que quieres borrar\n");
            MostrarRutasGuardadas();
            scanf("%d", &eliminar);
            while(getchar() != '\n');
            BorrarRuta(eliminar);
            return;
        }
        else if(ans == 3){
            return;
        }
        return;
    }
}

void DefinirNuevaRuta(){
    bool repetir = true;
    while(repetir){
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
        limpiar();
        printf("Seguro que quieres anadir la siguiente ruta:\nNombre: %s\nPath: %s\nS/N\n", NuevaRuta.nombre, NuevaRuta.path);
        
        char ans = getchar();
        while(getchar() != '\n');
        if(ans == 'n' || ans == 'N'){
            repetir = false;
        }
        else if(ans == 's' || ans == 'S'){
            if(rutaValida(NuevaRuta.path)){
                limpiar();
                printf("Nuevo destino anadido con exito\n");
                Sleep(1000);
                CrearRuta(NuevaRuta);
                return;
            }
            else{
                limpiar();
                system("color 0c");  //rojo para indicar error
                printf("La ruta \"%s\" no es valida\nAsegurate de que la ruta es un directorio valido "\
                "\nLas rutas con espacios no son validas, reemplazalos con guiones bajos" \
                "\nSi estas seguro ejecuta PageTransmuter como administrador\n",NuevaRuta.path);
                system("pause");
            }
        }
    }    
}

extern bool DebugMode;

//Messages.h
//Darle un nombre al proyecto
void projectName(char* Nombre, int len){
    bool nombreValido = false;
    while(!nombreValido){
        limpiar();
        printf("Nombre del archivo a generar:");
        fgets(Nombre, len, stdin);
        int Nombre_len = strlen(Nombre);
        if(Nombre_len < 1) continue;
        //Verificar que hay al menos ún carácter en el nombre
        for(int i = 0; i < Nombre_len; i++){
            switch(Nombre[i]){
                case ' ':
                    break;
                case '\n':
                    break;
                case '\0':
                    break;
                case '\t':
                    break;
                default:
                    nombreValido = true;
                    break;
            }
            if(nombreValido) break;
        }
        //Parpadeo para indicar error
        system("color c");
        Sleep(25);
        system("color a");
    }
    quitarSaltoLineaYEspacios(Nombre, true);
    if(DebugMode) printf("El nombre del archivo es %s\n", Nombre);
}