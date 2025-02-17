#!/bin/bash

app_desktop_file="/usr/share/applications/PageTransmuter.desktop"

program_dir="/usr/local/bin/T_Royale/PageTransmuter"

sudo rm -rf ${program_dir} && echo "PageTransmuter eliminado con éxito" || echo "ERROR: Ha habido un problema al eliminar PageTransmuter"

sudo rm -f ${app_desktop_file} && echo "PageTransmuter.desktop eliminado con éxito" || echo "ERROR: No se ha podido eliminar el archivo .desktop de PageTransmuter"