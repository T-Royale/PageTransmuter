//Librerías de C
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//Headers del programa
#include "../include/Messages.h"
#include "../include/HandleFiles.h"
#include "../include/RuleEngine.h"
//Debug:
//Limpiar terminal al inicio
bool limpiarEnInicio = true;

//Función principal:
int main() {
    inicio(); //Menú de bienvenida, termina cuando empieza la TRANSMUTACIÓN
    ElegirHTML(); //Pide al usuario que elija el HTML a transfusionar
    //La dirección del HTML orígen se almacena en HTML_ELEGIDO
    Rutas_t* rutaElegida = DecidirDestino();    //Decidir ubicación final
    char Nombre[20];    //Nombre del proyecto
    projectName(Nombre); //Guarda el nombre del proyecto
    printf("El nombre del archivo es %s\n", Nombre);
    printf("La ruta elegida es: %s\n", rutaElegida->path);
    //La ejecución termina aquí//
    TransmutarHTML(rutaElegida->path, HTML_ELEGIDO, Nombre);
    printf("=======================\nHa salido correctamente\n=======================");
    free(HTML_ELEGIDO);
    free(Rutas);
    return 0;
}