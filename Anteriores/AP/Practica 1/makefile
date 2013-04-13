LNKFLAGS = 

DIREXE = exec/
DIRHEA = include/
DIRSRC = src/

NEXEC1 = Bubble
NEXEC2 = Shell
NEXEC3 = QS

all : $(NEXEC1) $(NEXEC2) $(NEXEC3)

$(NEXEC1) : $(DIRSRC)Bubble.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC1) $(DIRSRC)Bubble.c

$(NEXEC2) : $(DIRSRC)Shell.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC2) $(DIRSRC)Shell.c

$(NEXEC3) : $(DIRSRC)QS.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC3) $(DIRSRC)QS.c
