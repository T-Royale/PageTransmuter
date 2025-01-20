//Headers del programa
#include "Include/Functions.h"
// Variables globales
bool limpiarEnInicio = true;
bool DebugMode = false;
char* HTML_ELEGIDO = NULL;
int nDirecciones = 0;
Rutas_t *Rutas = NULL;
bool LowLevelHTML = false;
bool hppFile = false;
bool LookforCSS = false;
bool ayuda = false;
int nLineas = 0;
//Función principal:
int main(int argc, char *argv[]) {
    LeerRutas();
    verificarArchivos();//Verifica los archivos del programa
    ComprobarArgumentos(argc, argv);
    inicio(); //Menú de bienvenida, termina cuando empieza la TRANSMUTACIÓN
    ElegirHTML(); //Pide al usuario que elija el HTML a transmutar
    //La dirección del HTML orígen se almacena en HTML_ELEGIDO
    Rutas_t* rutaElegida = DecidirDestino();    //Decidir ubicación final
    char Nombre[50];    //Nombre del proyecto
    projectName(Nombre, sizeof(Nombre)); //Guarda el nombre del proyecto
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