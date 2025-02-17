# Makefile para PageTransmuter en Linux

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
	$(PROGDEST)/Page.ico \
	$(PROGDEST)/Saved_adresses.bin

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
	@cp -r $(PROGSRC)/* $(PROGDEST)/
	@echo "Program_files creado"

# Crear el directorio para el ejecutable y objetos
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)
	@echo "Ruta de programa creada"

# Reglas para compilar cada archivo objeto
$(BUILDDIR)/main.o: $(SRCDIR)/main.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(BUILDDIR)/main.o
	@echo "main.c recompilado"

$(BUILDDIR)/HandleFiles.o: $(SRCDIR)/HandleFiles.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -D_FILE_OFFSET_BITS=64 -c $(SRCDIR)/HandleFiles.c -o $(BUILDDIR)/HandleFiles.o
	@echo "HandleFiles.c recompilado"

$(BUILDDIR)/Messages.o: $(SRCDIR)/Messages.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/Messages.c -o $(BUILDDIR)/Messages.o
	@echo "Messages.c recompilado"

$(BUILDDIR)/RuleEngine.o: $(SRCDIR)/RuleEngine.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/RuleEngine.c -o $(BUILDDIR)/RuleEngine.o
	@echo "RuleEngine.c recompilado"

$(BUILDDIR)/HeaderCreation.o: $(SRCDIR)/HeaderCreation.c $(INCLUDEDIR)/Functions.h | $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/HeaderCreation.c -o $(BUILDDIR)/HeaderCreation.o
	@echo "HeaderCreation.c recompilado"

# Enlazar los objetos para crear el ejecutable
$(BUILDDIR)/$(EXE): $(OBJECTS) $(HTMLDEST) $(PageTransmuter_files)
	@$(CC) $(CFLAGS) $(OBJECTS) -o "$(BUILDDIR)/$(EXE)"
	@echo "PageTransmuter recompilado"

# Comprimir carpeta en .tar.gz para el lanzamiento
release: build
	tar -zcvf $(COMPRIMIDO) $(BUILDDIR)

# Limpiar los archivos generados
clean:
	@rm -fr $(BUILDDIR)
	@rm -f $(COMPRIMIDO)
	@echo "$(BUILDDIR) eliminado"

# Limpiar objetos generados
RemoveOBJS:
	@rm -fr $(BUILDDIR)/*.o
	@echo "Objetos eliminados"