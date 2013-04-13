LNKFLAGS = -ggdb -ansi

DIREXE = exec/
DIRHEA = include/
DIRSRC = src/

NEXEC1 = Ej2


all : $(NEXEC1)

$(NEXEC1) : $(DIRSRC)Ej2.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC1) $(DIRSRC)Ej2.c


