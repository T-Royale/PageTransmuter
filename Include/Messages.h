//Definiciones y funciones que tienen que ver con interactuar con el usuario a través de la terminal
#ifndef MENSAJES_H
#define MENSAJES_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>

#include"../Include/HandleFiles.h"

//Messages.h
//Limpiar la pantalla
void limpiar(){
    system("cls");
    system("color a");
}
//Messages.h
//Mensajes y opciones de inicio
int inicio(){
    limpiar();
    printf("Bienvenido a PageTransmuter\n");
    printf("Formatea un archivo HTML para usarlo en C y C++\n");
    getchar();
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
#endif