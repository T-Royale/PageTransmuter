# gcc -o PageTransmuter main.c HandleFiles.c HeaderCreation.c Messages.c RuleEngine.c
# Directorios y archivos
SRCS = main.c HandleFiles.c HeaderCreation.c Messages.c RuleEngine.c
LIB = Include/Functions.h

# Nombre del ejecutable
TARGET = PageTransmuter

# Objetivo predeterminado para compilar
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(SRCS) $(LIB)
	gcc -o $(TARGET) $(SRCS)

# Limpiar archivos generados
clean:
	rm -f $(TARGET)
