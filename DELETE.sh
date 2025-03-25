#!/bin/bash

app_desktop_file="/usr/share/applications/PageTransmuter.desktop"

program_dir="/usr/local/bin/T_Royale/PageTransmuter"

SoftLink_target="/usr/local/bin/T_Royale/PageTransmuter/Program_files/PageTransmuter.sh"
Softlink_dir="/usr/local/bin/PageTransmuter"

sudo rm -rf "$program_dir" \
&& echo "PageTransmuter eliminado con éxito" \
|| echo "ERROR: Ha habido un problema al eliminar PageTransmuter"

sudo rm "$app_desktop_file" \
&& echo "PageTransmuter.desktop eliminado con éxito" \
|| echo "ERROR: No se ha podido eliminar el archivo .desktop de PageTransmuter"

sudo rm "$Softlink_dir" \
&& echo "El enlace simbólico del programa ha sido eliminado" \
|| echo "Error al eliminar el enlace simbólico de PageTransmuter"