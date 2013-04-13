LNKFLAGS = -ggdb -ansi

DIREXE = exec/
DIRHEA = include/
DIRSRC = src/

NEXEC1 = P4


all : $(NEXEC1)

$(NEXEC1) : $(DIRSRC)P4.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC1) $(DIRSRC)P4.c


