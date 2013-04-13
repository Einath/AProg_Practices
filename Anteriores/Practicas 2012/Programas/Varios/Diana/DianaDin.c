#include <stdio.h>
#include <stdlib.h>

#define INFINITO 10000
#define MAXDIM 100

typedef struct {
	int NumDardos;		 
	int DardosSector[MAXDIM]; /* Dardos[i] es el nº de dardos que han caido en el sector i*/
} TipoSolucion;


   void DianaDin (int k, int puntos, TipoSolucion *SolOptima,
                  int N, int PuntosSector[]);
                   
   
   void LeeDatos (int *Puntos, int *N, int PuntosSector[]);
   void Salida (TipoSolucion Sol, int N, int PuntosSector[]);
   



int main () {

	int PuntosSector[MAXDIM];
	TipoSolucion SolOptima;
	int N, Puntos;
	
	
	LeeDatos (&Puntos, &N, PuntosSector);
	
	
	DianaDin (0,Puntos,&SolOptima,N,PuntosSector);
	
   Salida (SolOptima, N, PuntosSector);
	
} /* main */



   void DianaDin (int k, int Puntos, TipoSolucion *SolOptima,
                  int N, int PuntosSector[]) {
	   int i;
	   TipoSolucion Sol, SolMejor;
	
	   if (Puntos < 0) SolOptima->NumDardos = INFINITO;
	   else
	      if (k == N) 
		      if (Puntos == 0) SolOptima->NumDardos = 0;
		      else SolOptima->NumDardos = INFINITO;
		   else {
		   	SolMejor.NumDardos = INFINITO;
		      for (i = Puntos / PuntosSector[k]; i >= 0; i--) {
		   	   DianaDin (k+1, Puntos-i*PuntosSector[k], &Sol, N, PuntosSector);
      	      Sol.DardosSector[k] = i;
               if (Sol.Dardos != INFINITO) Sol.NumDardos += i;
      	      // Comparamos con la mejor en esta etapa
      	      if (Sol.NumDardos < SolMejor.NumDardos) SolMejor = Sol;
            }
            *SolOptima = SolMejor;
         }   
      
   } // Fin DianaDin
   



   void LeeDatos (int *Puntos, int *N, int PuntosSector[]) {
	   *N = 0;
	   
      printf("Puntos a sumar?... "); scanf(" %d",Puntos);
      printf("Valores de las areas separados por un espacio añadiendo 0 al final\n");
      scanf("%d",&PuntosSector[*N]);
      while (PuntosSector[*N] > 0) {
         scanf(" %d", &PuntosSector[++(*N)]);  
      }
   }


   void Salida (TipoSolucion Sol, int N, int PuntosSector[]) {
	   int i;
	
      if (Sol.NumDardos == INFINITO)
	      printf("\n\nNo tiene solución\n\n");
	   else {
         printf("\n\nLa solucion es tirar %d dardos, con la siguiente distribucion: \n\n", Sol.NumDardos);
	      for (i = 0; i < N; i++) 
		      printf("Area %2d --> Valor: %3d Puntos, Dardos --> %3d)\n", 
		             i, PuntosSector[i], Sol.DardosSector[i]);
         printf("\n\n");
      }   
   }   
