# Makefile para PageTransmuter en Linux

SHELL := /bin/bash

# Variables
SRCDIR = src
INCLUDEDIR = $(SRCDIR)/Include
BUILDDIR = PageTransmuter
HTMLSRC = HTML_AQUI
HTMLDEST = $(BUILDDIR)/HTML_AQUI
PROGSRC = Program_files
PROGDEST = $(BUILDDIR)/Program_files
EXE = PageTransmuter
COMPRIMIDO = $(EXE).tar.gz

# Lista de archivos fuente
SOURCES = main.c HandleFiles.c Messages.c RuleEngine.c HeaderCreation.c

# Lista de archivos objeto con rutas completas
OBJECTS = \
	$(BUILDDIR)/main.o \
	$(BUILDDIR)/HandleFiles.o \
	$(BUILDDIR)/Messages.o \
	$(BUILDDIR)/RuleEngine.o \
	$(BUILDDIR)/HeaderCreation.o

# Lista de archivos en Program_files
PageTransmuter_files = \
	$(PROGDEST)/Instrucciones.bin \
	$(PROGDEST)/PageTransmuter_icon.png \
	$(PROGDEST)/Saved_adresses.bin\
	$(PROGDEST)/PageTransmuter.desktop\
	$(PROGDEST)/PageTransmuter.sh

# Compilador y flags
CC = gcc
CFLAGS = -Wall -I$(INCLUDEDIR) -std=c11

# Ver comandos
all:
	@echo Lista de comandos make
	@echo 	make build: Generar objetos y compilar
	@echo 	make clean: Limpiar archivos generados por build
	@echo 	make RemoveOBJS: Eliminar archivos objeto .o

# Regla por defecto
build: $(BUILDDIR)/$(EXE)

# Copiar el contenido de HTML_AQUI
$(HTMLDEST): $(BUILDDIR) $(HTMLSRC)
	@mkdir -p $(HTMLDEST)
	@cp -r $(HTMLSRC)/* $(HTMLDEST)/

# Copiar el contenido de Program_files
$(PROGDEST): $(BUILDDIR)
	@mkdir -p $(PROGDEST)

$(PageTransmuter_files): $(PROGDEST)
	@cp -r $(PROGSRC)/* $(PROGDEST) \
	&& echo "Program_files creado" \
	|| echo "ERROR: Al acceder a Program_files"

# Crear el directorio para el ejecutable y objetos
$(BUILDDIR):
	@mkdir -p $(BUILDDIR) \
	&& echo "Ruta de programa creada" \
	|| echo "ERROR: Al crear ruta del programa en $(BUILDDIR)"

# Reglas para compilar cada archivo objeto
$(BUILDDIR)/main.o: $(SRCDIR)/main.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(BUILDDIR)/main.o \
	&& echo "main.c compilado" \
	|| echo "ERROR: Al compilar main.c"

$(BUILDDIR)/HandleFiles.o: $(SRCDIR)/HandleFiles.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -D_FILE_OFFSET_BITS=64 -c $(SRCDIR)/HandleFiles.c -o $(BUILDDIR)/HandleFiles.o \
	&& echo "HandleFiles.c compilado" \
	|| echo "ERROR: Al compilar HandleFiles"

$(BUILDDIR)/Messages.o: $(SRCDIR)/Messages.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/Messages.c -o $(BUILDDIR)/Messages.o \
	&& echo "Messages.c compilado" \
	|| echo "ERROR: Al compilar Messages.c"

$(BUILDDIR)/RuleEngine.o: $(SRCDIR)/RuleEngine.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/RuleEngine.c -o $(BUILDDIR)/RuleEngine.o \
	&& echo "RuleEngine.c compilado" \
	|| echo "ERROR: Al compilar RuleEngine"

$(BUILDDIR)/HeaderCreation.o: $(SRCDIR)/HeaderCreation.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/HeaderCreation.c -o $(BUILDDIR)/HeaderCreation.o \
	&& echo "HeaderCreation.c compilado" \
	|| echo "ERROR: al compilar HeaderCreation.c"

# Enlazar los objetos para crear el ejecutable
$(BUILDDIR)/$(EXE): $(OBJECTS) $(HTMLDEST) $(PageTransmuter_files)
	@$(CC) $(CFLAGS) $(OBJECTS) -o "$(BUILDDIR)/$(EXE)" \
	&& echo "PageTransmuter enlazado y compilado con éxito" \
	|| echo "ERROR: Al enlazar y compilar PageTransmuter"

# Comprimir carpeta en .tar.gz para el lanzamiento
release: build RemoveOBJS
	tar -zcvf $(COMPRIMIDO) $(BUILDDIR) \
	&& echo "PageTransmuter comprimido en .tar.gz" \
	|| echo "ERROR: al comprimir PageTransmuter"

# Limpiar los archivos generados
clean:
	@rm -fr $(BUILDDIR) \
	&& echo "$(BUILDDIR) eliminado" \
	|| echo "ERROR: al eliminar $(BUILDDIR)"
	@rm -f $(COMPRIMIDO) \
	&& echo "$(COMPRIMIDO) eliminado" \
	|| echo "ERROR: al eliminar $(COMPRIMIDO)"

# Limpiar objetos generados
RemoveOBJS:
	@rm -fr $(BUILDDIR)/*.o \
	&& echo "Objetos eliminados" \
	|| echo "ERROR: al eliminar objetos"