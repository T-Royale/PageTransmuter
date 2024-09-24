# Nombre del ejecutable
EXECUTABLE = PageTransmuter.exe

# Directorios
SRC_DIR = src
INC_DIR = Include
PROG_FILES_DIR = Program_files
HTML_DIR = HTML_AQUI
DEST_DIR = PageTransmuter
BIN_DIR = $(DEST_DIR)\PageTransmuter

# Archivo fuente
SRC = main.c

# Flags de compilación
CFLAGS = -Wall -I..\Include

# Comando para el compilador
CC = gcc

# Regla por defecto
all: $(BIN_DIR)\$(EXECUTABLE)

# Regla para crear el ejecutable y preparar los directorios
$(BIN_DIR)\$(EXECUTABLE): $(SRC_DIR)\$(SRC)
	@echo Creando directorios...
	@if not exist "$(DEST_DIR)" mkdir "$(DEST_DIR)"
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@echo Copiando Program_files...
	xcopy /s /e /i "$(PROG_FILES_DIR)\*" "$(DEST_DIR)\$(PROG_FILES_DIR)\"
	@echo Copiando Include...
	xcopy /s /e /i "$(INC_DIR)\*" "$(DEST_DIR)\$(INC_DIR)\"
	@echo Copiando HTML_AQUI...
	xcopy /s /e /i "$(HTML_DIR)\*" "$(DEST_DIR)\$(HTML_DIR)\"
	@echo Compilando el ejecutable...
	cd $(SRC_DIR) && \
	$(CC) $(CFLAGS) -o "..\$(BIN_DIR)\$(EXECUTABLE)" $(SRC)
	@echo Compilación completada.

# Regla de limpieza
clean:
	rd /s /q "$(DEST_DIR)"
