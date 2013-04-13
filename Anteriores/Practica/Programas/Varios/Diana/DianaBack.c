#include <stdio.h>
#include <stdlib.h>

#define INFINITO 10000
#define MAXDIM 100

typedef struct {
	int NumDardos;		 
	int DardosSector[MAXDIM]; /* Dardos[i] es el nº de dardos que han caido en el sector i*/
} TipoSolucion;


   void DianaBack (int k, int puntos, TipoSolucion *Sol, TipoSolucion *SolOptima,
                   int N, int PuntosSector[]);
                   
   void Inicializacion (TipoSolucion *Sol, TipoSolucion *SolOptima, int N);

   void LeeDatos (int *Puntos, int *N, int PuntosSector[]);
   void Salida (TipoSolucion Sol, int N, int PuntosSector[]);
   



int main () {

	int PuntosSector[MAXDIM];
	TipoSolucion Sol, SolOptima;
	int N, Puntos;
	
	
	LeeDatos (&Puntos, &N, PuntosSector);
	
	Inicializacion (&Sol, &SolOptima, N);
	
	DianaBack (0,Puntos,&Sol,&SolOptima,N,PuntosSector);
	
   Salida (SolOptima, N, PuntosSector);
	
} // main



   void DianaBack (int k, int Puntos, TipoSolucion *Sol, TipoSolucion *SolOptima,
                   int N, int PuntosSector[]) {
	   int i;
	
	   if ( Sol->NumDardos < SolOptima->NumDardos ) {
		   if (k == N) {
		      if (Puntos == 0) *SolOptima = *Sol;
		   }   
		   else 
		      for (i = Puntos / PuntosSector[k]; i >= 0; i--) {
		   	   Sol->DardosSector[k] = i;
               Sol->NumDardos += i;
      	      DianaBack (k+1, Puntos-i*PuntosSector[k], Sol, SolOptima, N, PuntosSector);
      	      // deshacemos para la siguiente iteración
      	      Sol->NumDardos -= i;
            }
      } 
   } // Fin DianaBack
   

   void Inicializacion (TipoSolucion *Sol, TipoSolucion *SolOptima, int N) {
	
      Sol->NumDardos = 0;
	   SolOptima->NumDardos = INFINITO;
   }



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


