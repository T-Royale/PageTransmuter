FILES = main.c HandleFiles.c HeaderCreation.c Messages.c RuleEngine.c
all:
	gcc -o PageTransmuter $(FILES)

clear:
	rm -f PageTransmuter
