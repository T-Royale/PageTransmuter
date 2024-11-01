//Librerías de C
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//Headers del programa
#include "Include/Functions.h"
//Debug:
//Limpiar terminal al inicio (ver advertencias)
bool limpiarEnInicio = true;
//Mostrar mensages de debug
bool DebugMode = false;

//Función principal:
int main(int argc, char *argv[]) {
    inicio(); //Menú de bienvenida, termina cuando empieza la TRANSMUTACIÓN
    ElegirHTML(); //Pide al usuario que elija el HTML a transmutar
    //La dirección del HTML orígen se almacena en HTML_ELEGIDO
    Rutas_t* rutaElegida = DecidirDestino();    //Decidir ubicación final
    char Nombre[20];    //Nombre del proyecto
    projectName(Nombre); //Guarda el nombre del proyecto
    TransmutarHTML(rutaElegida->path, HTML_ELEGIDO, Nombre);
    free(HTML_ELEGIDO);
    free(Rutas);
    if(DebugMode){
        printf("%s", final);
        system("pause");
    }
    abrirRuta(rutaElegida->path);
    return 0;
}