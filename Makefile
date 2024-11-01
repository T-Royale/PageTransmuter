# gcc -o PageTransmuter main.c HandleFiles.c HeaderCreation.c Messages.c RuleEngine.c
# Variables
SRCDIR = src
INCLUDEDIR = $(SRCDIR)/Include
OUTDIR = PageTransmuter
BINDIR = $(OUTDIR)/PageTransmuter
PROGRAM = PageTransmuter
SRCS = main.c HandleFiles.c HeaderCreation.c Messages.c RuleEngine.c

CC = gcc
CFLAGS = -I$(INCLUDEDIR)

# Regla por defecto
all: $(BINDIR)/$(PROGRAM)

# Compilación del programa
$(BINDIR)/$(PROGRAM): $(addprefix $(SRCDIR)/, $(SRCS)) | prepare
	$(CC) $(CFLAGS) $^ -o $@

# Preparación de directorios y copiado de carpetas y archivos
prepare:
	# Crear directorios necesarios
	mkdir -p $(BINDIR)
	# Copiar Program_files sin run.txt
	mkdir -p $(OUTDIR)/Program_files
	rsync -av --exclude='run.txt' Program_files/ $(OUTDIR)/Program_files/
	# Copiar run.txt al directorio del binario
	cp Program_files/run.txt $(BINDIR)/
	# Copiar HTML_AQUI al directorio de salida
	cp -r HTML_AQUI $(OUTDIR)/

# Limpiar archivos generados
clean:
	rm -rf $(OUTDIR)