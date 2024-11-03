# Makefile para PageTransmuter en Windows

# Variables
SRCDIR = src
INCLUDEDIR = $(SRCDIR)/Include
BUILDDIR = PageTransmuter
HTMLSRC = HTML_AQUI
HTMLDEST = $(BUILDDIR)/HTML_AQUI
PROGSRC = Program_files
PROGDEST = $(BUILDDIR)/Program_files
BINDIR = $(BUILDDIR)/PageTransmuter
EXE = PageTransmuter.exe

# Lista de archivos fuente
SOURCES = main.c HandleFiles.c Messages.c RuleEngine.c HeaderCreation.c

# Lista de archivos objeto con rutas completas
OBJECTS = \
	$(BINDIR)/main.o \
	$(BINDIR)/HandleFiles.o \
	$(BINDIR)/Messages.o \
	$(BINDIR)/RuleEngine.o \
	$(BINDIR)/HeaderCreation.o

# Compilador y flags
CC = gcc
CFLAGS = -Wall -I$(INCLUDEDIR)

# Ver comandos
all:
	@echo Lista de comandos make
	@echo 	make build: Construir proyecto
	@echo 	make clean: Limpiar archivos generados por build
	@echo 	make RemoveOBJS: Eliminar archivos objeto .o

# Regla por defecto
build: $(BINDIR)/$(EXE)

# Crear el directorio principal de compilación
$(BUILDDIR):
	if not exist "$(BUILDDIR)" mkdir "$(BUILDDIR)"

# Copiar el contenido de HTML_AQUI
$(HTMLDEST): $(BUILDDIR)
	if not exist "$(HTMLDEST)" mkdir "$(HTMLDEST)"
	xcopy /E /I /Y "$(HTMLSRC)\*" "$(HTMLDEST)\"

# Copiar el contenido de Program_files
$(PROGDEST): $(BUILDDIR)
	if not exist "$(PROGDEST)" mkdir "$(PROGDEST)"
	xcopy /E /I /Y "$(PROGSRC)\*" "$(PROGDEST)\"

# Crear el directorio para el ejecutable y objetos
$(BINDIR): $(BUILDDIR)
	if not exist "$(BINDIR)" mkdir "$(BINDIR)"

# Reglas para compilar cada archivo objeto
$(BINDIR)/main.o: $(SRCDIR)/main.c $(INCLUDEDIR)/Functions.h | $(BINDIR)
	$(CC) $(CFLAGS) -c "$(SRCDIR)/main.c" -o "$(BINDIR)/main.o"

$(BINDIR)/HandleFiles.o: $(SRCDIR)/HandleFiles.c $(INCLUDEDIR)/Functions.h | $(BINDIR)
	$(CC) $(CFLAGS) -c "$(SRCDIR)/HandleFiles.c" -o "$(BINDIR)/HandleFiles.o"

$(BINDIR)/Messages.o: $(SRCDIR)/Messages.c $(INCLUDEDIR)/Functions.h | $(BINDIR)
	$(CC) $(CFLAGS) -c "$(SRCDIR)/Messages.c" -o "$(BINDIR)/Messages.o"

$(BINDIR)/RuleEngine.o: $(SRCDIR)/RuleEngine.c $(INCLUDEDIR)/Functions.h | $(BINDIR)
	$(CC) $(CFLAGS) -c "$(SRCDIR)/RuleEngine.c" -o "$(BINDIR)/RuleEngine.o"

$(BINDIR)/HeaderCreation.o: $(SRCDIR)/HeaderCreation.c $(INCLUDEDIR)/Functions.h | $(BINDIR)
	$(CC) $(CFLAGS) -c "$(SRCDIR)/HeaderCreation.c" -o "$(BINDIR)/HeaderCreation.o"

# Enlazar los objetos para crear el ejecutable
$(BINDIR)/$(EXE): $(OBJECTS) $(HTMLDEST) $(PROGDEST)
	$(CC) $(CFLAGS) $(OBJECTS) -o "$(BINDIR)/$(EXE)"

# Limpiar los archivos generados
clean:
	if exist "$(BUILDDIR)" rd /S /Q "$(BUILDDIR)"

# Limpiar objetos generados
RemoveOBJS:
	if exist "PageTransmuter\PageTransmuter" del /Q "PageTransmuter\PageTransmuter\*.o"

.PHONY: all clean
