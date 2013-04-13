#include <stdio.h>

#define DIM 20

   typedef int TipoEstado[DIM];
   typedef int boolean;

   int N, Cont;
   int Estado[DIM];


   boolean Admisible (int Etapa, TipoEstado Estado) {
      int    i;
      boolean Seguir;

      Seguir = 1; i = 1;
      while ((i < Etapa) && (Seguir != 0)) {
         Seguir = (abs (i-Etapa) != abs (Estado[i]-Estado[Etapa]))
                  &&
                  (Estado[i] != Estado[Etapa]);
         i++;
      }
      return (Seguir);
   }


   void DamasRec (int Etapa, TipoEstado Estado, int *Cont) {
      int i;

      if (Etapa == N + 1) (*Cont)++;
      else 
         for (i = 1; i <= N; i++) {
            Estado[Etapa] = i;
            if (Admisible (Etapa, Estado))
               DamasRec (Etapa+1,Estado,Cont);
         }
   }


int main () {
   Cont = 0; 
   printf (" Introduzca la dimension del tablero...? ");
   scanf ("%d", &N);
   printf ("\n");
   DamasRec (1,Estado,&Cont);
   printf (" La dimension del tablero es %d\n", N);
   printf (" El numero de posiciones es... %d\n", Cont);
   return (0);
}

