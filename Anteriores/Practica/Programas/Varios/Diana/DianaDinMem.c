#include <stdio.h>
#include <stdlib.h>

#define INFINITO 10000
#define MAXDIM 50
#define MAXPUNTOS 1000
#define TRUE 1
#define FALSE 0


typedef struct {
	int NumDardos;		 
	int DardosSector[MAXDIM]; /* Dardos[i] es el nº de dardos que han caido en el sector i*/
} TipoSolucion;

typedef struct {
	int Calculado;
	TipoSolucion Sol;
	} TipoDato;

typedef TipoDato TipoMemoria [MAXPUNTOS][MAXDIM];


   void DianaDinMem (int k, int Puntos, TipoSolucion *SolOptima,
                     int N, int PuntosSector[],
                     TipoMemoria *Mem);
                   
   
   void LeeDatos (int *Puntos, int *N, int PuntosSector[]);
   void Salida (TipoSolucion Sol, int N, int PuntosSector[]);

   
   int Busca (TipoMemoria *Mem, int N, int k, int Puntos, TipoSolucion *SolOptima) {
   	  
   	  if ((*Mem)[Puntos][k].Calculado) *SolOptima = (*Mem)[Puntos][k].Sol;
   	  return ((*Mem)[Puntos][k].Calculado);
   }
   	
   void Almacenar (TipoMemoria *Mem, int N, int k, int Puntos, TipoSolucion SolOptima) {
   	  (*Mem)[Puntos][k].Calculado = TRUE;
   	  (*Mem)[Puntos][k].Sol = SolOptima;
   }
   
   void InicializaMem (TipoMemoria *Mem, int N, int Puntos) {
   	  int i, j;
   	  
   	  for (i = 0; i <= Puntos; i++) 
   	     for (j = 0; j < N; j++) 
   	        (*Mem)[i][j].Calculado = FALSE;
   	        
   }
   

int main () {

	int PuntosSector[MAXDIM];
	TipoSolucion SolOptima;
	int N, Puntos;
	TipoMemoria Mem;

	
	LeeDatos (&Puntos, &N, PuntosSector);
	
	InicializaMem (&Mem, N, Puntos);
	
	DianaDinMem (0,Puntos,&SolOptima,N,PuntosSector,&Mem);
	
   Salida (SolOptima, N, PuntosSector);
	
	
} /* main */



   void DianaDinMem (int k, int Puntos, TipoSolucion *SolOptima,
                     int N, int PuntosSector[], TipoMemoria *Mem) {
	   int i, Enc;
	   TipoSolucion Sol, SolMejor;
	   
	   Enc = Busca (Mem, N, k, Puntos, SolOptima);
	   if (!Enc) {
         if (k == N) 
	         if (Puntos == 0) SolOptima->NumDardos = 0;
	         else SolOptima->NumDardos = INFINITO;
	      else {
	   	   SolMejor.NumDardos = INFINITO;
	         for (i = Puntos / PuntosSector[k]; i >= 0; i--) {
	   	      DianaDinMem (k+1, Puntos-i*PuntosSector[k], &Sol, N, PuntosSector, Mem);
     	         Sol.DardosSector[k] = i;
               Sol.NumDardos += i;
        	      // Comparamos con la mejor en esta etapa
        	      if (Sol.NumDardos < SolMejor.NumDardos) SolMejor = Sol;
            }
            *SolOptima = SolMejor;
         }
         Almacenar(Mem, N, k, Puntos, *SolOptima);
      }   
      
   } // Fin DianaDinMem
   



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


