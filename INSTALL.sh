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

applications_dir="/usr/share/applications"
desktop_file="${applications_dir}/PageTransmuter.desktop"

# Comprobar si clear está instalado
if command -v clear &> /dev/null; then
    echo "clear está instalado"
else
    echo "ERROR: clear NO está instalado y es necesario para PageTransmuter."
    echo "Descarga ncurses y prueba otra vez"
    exit 1
fi

# Comprobar que xdg-utils está instalado
if command -v xdg-open &> /dev/null
then
    echo "xdg-utils está instalado"
else
    echo "ERROR: xdg-open NO está instalado y es necesario para PageTransmuter."
    echo -e "Puedes descargar xdg-utils desde el siguiente enlace: \nhttps://www.freedesktop.org/wiki/Software/xdg-utils/"
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

USER_GROUP=$(id -gn $USER)

read -p "¿Quieres instalar PageTransmuter para todos los usuarios? (S/n): " respuesta
respuesta=${respuesta:-S}  # S por defecto
respuesta=$(echo "$respuesta" | tr '[:lower:]' '[:upper:]')  # Convertir a mayúsculas

if [[ "$respuesta" == "S" ]]; then
    sudo chmod -R 777 ${program_dir}/\
    && echo "Permisos otorgados a todos los usuarios"\
    || echo "ERROR: al modificar los permisos del programa"echo "Has cancelado la operación."
else
    sudo chmod -R 771 ${program_dir}/\
    && echo "Permisos otorgados sólamente a $USER y grupo $USER_GROUP"\
    || echo "ERROR: al modificar los permisos del programa"
fi

sudo rm -f "$release_file"\
&& echo "Archivos temporales de instalación eliminados"\
|| echo "ERROR: al eliminar archivos temporales de la instalación"

if command -v which PageTransmuter &> /dev/null; then
    echo "La PageTransmuter ya está definido en la CLI."
else
    echo "PageTransmuter() { cd /usr/local/bin/T_Royale/PageTransmuter; ./PageTransmuter "$@"; cd }" >> "$cli"\
    && echo "PageTransmuter ha sido añadido a la línea de comandos bash"\
    || echo "ERROR: al crear función en .bashrc"
fi
 
if [ -f "${desktop_file}" ]; then
    sudo rm "${desktop_file}"\
    && echo "Eliminado ${desktop_file} antiguo"\
    || echo "ERROR: al eliminar ${desktop_file} antiguo"
fi

sudo mv "$program_dir/Program_files/PageTransmuter.desktop" "${applications_dir}"\
&& echo "Se ha creado la aplicación PageTransmuter"\
|| echo "ERROR: al mover el archivo .desktop a /usr/share/applications"

echo "Instalación terminada"