# PageTransmuter
## Convierte un HTML en una cadena válida en C y C++
## La herramienta que buscas para tu servidor HTTP personal
### Versión: *ALPHA 1.0*
---
#### Instalación (Linux):
1. Confirma que tienes **curl** instalado.
    ```
    curl --version
    ```
    + Si no está instalado, [instálalo.](https://curl.se/download.html)
2. Ejecuta mi script de instalación.
    ```
    curl -sSL https://raw.githubusercontent.com/T-Royale/PageTransmuter/refs/heads/Linux_Version/INSTALL.sh | bash
    ```
+ Desinstalar PageTransmuter.
    ```
    curl -sSL https://raw.githubusercontent.com/T-Royale/PageTransmuter/refs/heads/Linux_Version/DELETE.sh | bash
    ```
---
#### Opciones adicionales:
**Ejecutar el programa desde la línea de comandos con las opciones deseadas**
+ ``-low``: Añade la línea de estado y los encabezados de una respuesta HTTP.
+ ``-cpp``: Crea un archivo ``.hpp`` en lugar de ``.h``.
+ ``-css``: Transmutará archivos ``.css`` en lugar de ``.html``.
