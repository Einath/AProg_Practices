LNKFLAGS = -ggdb -ansi

DIREXE = exec/
DIRHEA = include/
DIRSRC = src/
NEXEC1 = P3


all : $(NEXEC1)

$(NEXEC1) : $(DIRSRC)P3.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC1) $(DIRSRC)P3.c


