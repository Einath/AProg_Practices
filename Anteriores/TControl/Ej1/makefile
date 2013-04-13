LNKFLAGS = -ggdb -ansi

DIREXE = exec/
DIRHEA = include/
DIRSRC = src/

NEXEC1 = Ej1


all : $(NEXEC1)

$(NEXEC1) : $(DIRSRC)Ej1.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC1) $(DIRSRC)Ej1.c


