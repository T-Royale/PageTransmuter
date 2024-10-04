//Librerías de C
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//Headers del programa
#include "../include/Messages.h"
#include "../include/HandleFiles.h"
#include "../include/RuleEngine.h"

//Función principal:
int main() {
    inicio(); //Menú de bienvenida, termina cuando empieza la TRANSMUTACIÓN
    ElegirHTML(); //Pide al usuario que elija el HTML a transfusionar
    //La dirección del HTML orígen se almacena en HTML_ELEGIDO
    printf("%s\n", HTML_ELEGIDO);
    printf("=======================\nHa salido correctamente\n=======================");
    free(HTML_ELEGIDO);
    free(Rutas);
    return 0;
}
