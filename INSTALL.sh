#!/usr/bin/env bash

# Script de instalación de PageTransmuter

# Variables:
cli="$HOME/.bashrc"     # Modificar si usas otro

release="v1.0-alfa"
release_version="v1.0-Alpha"
release_file="PageTransmuter_${release_version}.tar.gz"
release_link="https://github.com/T-Royale/PageTransmuter/releases/download/${release_version}/PageTransmuter_${release}.tar.gz"

programs_dir="/usr/local/bin/T_Royale"
program_dir="$programs_dir/PageTransmuter"

# Comprobar que xdg-utils está instalado
if command -v xdg-open &> /dev/null
then
    echo "xdg-utils está instalado"
else
    echo -e "ERROR: xdg-open NO está instalado y es necesario para PageTransmuter."
    exit 1
fi

# Instalación
sudo mkdir -p "$program_dir"\
&& echo "Directorio de programa creado"\
|| echo "ERROR: al crear directorio del programa"

sudo curl -L -o "$release_file" "$release_link"\
&& echo "PageTransmuter descargado desde GitHub"\
|| echo "ERROR: al descargar PageTransmuter desde GitHub"

sudo tar -xvzf "$release_file" -C "$programs_dir"\
&& echo "PageTransmuter descomprimido con éxito"\
|| echo "ERROR: al descomprimir PageTransmuter"

sudo rm -f "$release_file"\
&& echo "Archivos temporales de instalación eliminados"\
|| echo "ERROR: al eliminar archivos temporales de la instalación"

echo "PageTransmuter(){ cd /usr/local/bin/T_Royale/PageTransmuter; ./PageTransmuter;}" >> "$cli"\
&& echo "PageTransmuter ha sido añadido a las variables de entorno PATH"\
|| echo "ERROR: al añadir PageTransmuter a las variables de entorno PATH"

sudo mv "$program_dir/Program_files/PageTransmuter.desktop" "/usr/share/applications"\
&& echo "El archivo .desktop de PageTransmuter ha sido movido a /usr/share/applications"\
|| echo "ERROR: al mover el archivo .desktop a /usr/share/applications"

echo "Instalación terminada"