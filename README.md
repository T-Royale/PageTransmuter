# PageTransmuter
## Convierte un HTML en una cadena válida en C y C++
## La herramienta que buscas para tu servidor HTTP
### Versión: *ALPHA 1.0*
---
## Instalación (Windows) 
### Método 1: Descarga directa
<a href="https://github.com/T-Royale/PageTransmuter/releases/download/v1.0-Alpha/PageTransmuter_v1.0_Windows.zip">
  <img 
    src="https://i.ibb.co/7dxGfK3Q/Descargar.png" 
    alt="Descargar para Windows" 
    style="border-radius: 15px;"
  >
</a>

Por algún motivo muchos navegadores lo detectan como malicioso, en ese caso puedes pasar al método 2

### Método 2: Compilación manual
1. Verifica que tienes git, make y gcc instalados
    ```
        git --version
        make --version
        gcc --version
    ```
    Si alguno muestra un error, instálalo
2. Clonar el repositorio a tu máquina
    ```
    git clone https://github.com/T-Royale/PageTransmuter.git PageTransmuter_tmp
    ```
3. Entrar en la carpeta del programa y compilar
    ```
    cd PageTransmuter_tmp
    git switch Windows_Version
    make build
    ```
    Se habrá creado una nueva carpeta llamada *PageTransmuter* con el programa y sus archivos 
## Instalación (Linux):
### Método 1 : Script de instalación
1. Confirma que tienes **curl** instalado.
    ```
    curl --version
    ```
    + Si no está instalado, [instálalo.](https://curl.se/download.html)
2. Ejecuta mi script de instalación.
    ```
    curl -sSL https://raw.githubusercontent.com/T-Royale/PageTransmuter/refs/heads/Linux_Version/INSTALL.sh | bash
    ```
+ Desinstalar PageTransmuter. 😭
    ```
    curl -sSL https://raw.githubusercontent.com/T-Royale/PageTransmuter/refs/heads/Linux_Version/DELETE.sh | bash
    ```
### Método 2: Compilación manual
1. Verifica que tienes git, make y gcc instalados
    ```
        git --version
        make --version
        gcc --version
    ```
    Si alguno muestra un error, instálalo
2. Clonar el repositorio a tu máquina
    ```
    git clone https://github.com/T-Royale/PageTransmuter.git ./PageTransmuter_tmp
    ```
3. Entrar en la carpeta del programa y compilar
    ```
    cd PageTransmuter_tmp
    make build
    ```
Se habrá creado una nueva carpeta llamada *PageTransmuter* con el programa y sus archivos

---
## Opciones adicionales:
**Ejecutar el programa desde la línea de comandos con las opciones deseadas**
+ ``-low``: Añade la línea de estado y los encabezados de una respuesta HTTP.
+ ``-cpp``: Crea un archivo ``.hpp`` en lugar de ``.h``.
+ ``-css``: Transmutará archivos ``.css`` en lugar de ``.html``.
