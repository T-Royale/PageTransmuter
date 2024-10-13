//Definiciones y funciones que tienen que ver con interactuar con el usuario a través de la terminal
#ifndef MENSAJES_H
#define MENSAJES_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<io.h>

#include"../Include/HandleFiles.h"

int masOpciones();
void noHayRutas();

//Messages.h
//Limpiar la pantalla
void limpiar(){
    system("cls");
    system("color a");
}
extern bool limpiarEnInicio;

//Messages.h
//Mensajes y opciones de inicio
int inicio(){
    if(limpiarEnInicio) limpiar();
    printf("Bienvenido a PageTransmuter\n");
    printf("Formatea un archivo HTML para usarlo en C y C++\n");

    while(getchar() != '\n'); //Limpiar el buffer de entrada
    //mostrar opciones de inicio
    bool teclavalida = true;
    //Abrir instrucciones por si se consultan
    FILE *instrucciones;
    char linea[256];
    do {
        limpiar();
        printf("Selecciona una opcion:\n");
        printf("1- Transmutar HTML\n2- Instrucciones\n3- Salir\n");
        char tecla = getchar();
        while(getchar() != '\n'); //Limpiar el buffer de entrada
        teclavalida = true;
        switch(tecla){
            case '1':
                break;
            case '2':
                limpiar();
                //Secuencia de explicación
                instrucciones = fopen("../Include/Instrucciones.txt", "r");
                while (fgets(linea, sizeof(linea), instrucciones) != NULL) {
                    printf("%s", linea); // Mostrar cada línea en la terminal
                    Sleep(500);
                }
                // Cerrar el archivo
                fclose(instrucciones);
                switch (getchar())
                {
                case '1':
                    break;
                case '2':
                    system("start https://github.com/T-Royale");
                    break;
                case '3':
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
                perror("Tecla invalida\nPresiona ENTER para reintentar");
                teclavalida = false;
                break;
        }
    } while(!teclavalida);
    return 0;
}

char* HTML_ELEGIDO = NULL;

//Messages.h
//Elegir doucumento HTML a transfusionar
void ElegirHTML(){
    inicio:
    limpiar();
    printf("Selecciona el archivo HTML a Transmutar\n");
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
        goto inicio;
    }
    HTML_ELEGIDO = SelectHTMLdocs(eleccion);
}
//Messages.h
//Decidir la ruta destino donde será creado el header
Rutas_t* DecidirDestino(){
inicio:
    limpiar();
    printf("Elige la ruta destino:\n");
    MostrarRutasGuardadas();    //nDirecciones es en nº de rutas guardadas+1
    printf("%d- Mas opciones\n", nDirecciones);
    int eleccion = 0;
    scanf("%d", &eleccion);
    while(getchar() != '\n');
    if(eleccion > nDirecciones || eleccion < 0) goto inicio;
    if(eleccion == nDirecciones) if(masOpciones() == 0) goto inicio;
    //si no se ha decidido crear ninguna ruta
    Rutas_t* rutaElegida = &Rutas[eleccion];
    quitarSaltoLineaYEspacios(rutaElegida->path, false);
    return rutaElegida;

}
//HandleFiles.h
//Más opciones de rutas guardadas
int masOpciones(){
    //Más opciones
    int ans = 0;
MasOpciones:
    limpiar();
    printf("Que quieres hacer?\n\t1. Crear nueva ruta\n\t2. Eliminar ruta existente \
    \n\t3. Volver atras\n");
    scanf("%d", &ans);
    while(getchar() != '\n');
    //Añadir ruta
    if(ans == 1){
    AñadirRuta:
        limpiar();
        Rutas_t NuevaRuta;

        printf("Nombre de la nueva direccion:");
        fgets(NuevaRuta.nombre, sizeof(NuevaRuta.nombre), stdin);
        printf("Direccion del directorio destino:");
        fgets(NuevaRuta.path, sizeof(NuevaRuta.path), stdin);

        printf("Seguro que quieres anadir la siguiente ruta:\nNombre: %s\nPath: %s\nS/N\n", NuevaRuta.nombre, NuevaRuta.path);
        char ans = getchar();
        while(getchar() != '\n');
        if(ans == 'n' || ans == 'N'){
            goto AñadirRuta;
        }
        if(rutaValida(NuevaRuta)){
            limpiar();
            printf("Nuevo destino anadido con exito\n");
            Sleep(1000);
            CrearRuta(NuevaRuta);
            return 0;
        }
        else{
            limpiar();
            system("color 0c");  //rojo para indicar error
            printf("La ruta %s no es valida\nAsegurate de que la ruta es un directorio valido \
            \nSi estas seguro ejecuta PageTransmuter como administrador\n",NuevaRuta.path);
            system("pause");
        }
    }
    //Borrar ruta
    else if(ans == 2){
        if(nDirecciones == 0){
            noHayRutas();
            goto AñadirRuta;
        }
        int eliminar;
        limpiar();
        printf("Selecciona la ruta que quieres borrar\n");
        MostrarRutasGuardadas();
        scanf("%d", &eliminar);
        while(getchar() != '\n');
        BorrarRuta(eliminar);
        if(nDirecciones == 0){
            noHayRutas();
            goto AñadirRuta;
        }
        return 0;
    }
    else if(ans == 3){
        return 0;
    }
    else goto MasOpciones;
}
void noHayRutas(){
    system("color c");
    printf("No se han encontrado rutas guardadas :(\nENTER: Crear una nueva\n");
    while(getchar() != '\n');
}
//Messages.h
//Darle un nombre al proyecto
void projectName(char* Nombre){
    limpiar();
    printf("Nuevo nombre del archivo:");
    fgets(Nombre, 20, stdin);
    quitarSaltoLineaYEspacios(Nombre, true);
}
#endif