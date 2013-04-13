#include <stdio.h>
#include <stdlib.h>

#define INFINITO 10000
#define MAXDIM 100

typedef struct {
	int Suma;		 
	int Variable[MAXDIM]; /* Valor de la Variable[i] es el valor de la variable i*/
} TipoSolucion;


   void PLEBack (int k, int puntos, TipoSolucion *Sol, TipoSolucion *SolOptima,
                 int N, int CoefFObjetivo[], int CoefRestriccion[]);
                   
   void Inicializa (TipoSolucion *Sol, TipoSolucion *SolOptima);
   
   void LeeDatos (int *D, int *N, int CoefFObjetivo[], int CoefRestriccion[]);
   void Salida (TipoSolucion Sol, int N, int CoefFObjetivo[], int CoefRestriccion[]);


int main () {

	int CoefFObjetivo[MAXDIM], CoefRestriccion[MAXDIM];
	TipoSolucion Sol, SolOptima;
	int N, D;
	
	
	LeeDatos (&D, &N, CoefFObjetivo, CoefRestriccion);
	
	Inicializa (&Sol, &SolOptima);
	
	PLEBack (0,D,&Sol,&SolOptima,N,CoefFObjetivo,CoefRestriccion);
	
   Salida (SolOptima, N, CoefFObjetivo,CoefRestriccion);
	
} /* main */



   void PLEBack (int k, int D, TipoSolucion *Sol, TipoSolucion *SolOptima,
                 int N, int CoefFObjetivo[], int CoefRestriccion[]) {
                   
	   int i;
	
	   if (k == N) {
		   if (Sol->Suma > SolOptima->Suma) *SolOptima = *Sol;
		}
		else 
		   for (i = D / CoefRestriccion[k]; i >= 0; i--) {
            Sol->Variable[k] = i;
            Sol->Suma += i*CoefFObjetivo[k];
		 	   PLEBack (k+1, D-i*CoefRestriccion[k], Sol, SolOptima, N, CoefFObjetivo, CoefRestriccion);
            // Deshacemos para la siguiente iteracion
            Sol->Suma -= i*CoefFObjetivo[k];
         }
      
   } // Fin PLEBack



   void Inicializa (TipoSolucion *Sol, TipoSolucion *SolOptima) {
   	Sol->Suma = 0;
   	SolOptima->Suma = -INFINITO;
   }


   void LeeDatos (int *D, int *N, int CoefFObjetivo[], int CoefRestriccion[]) {
	   int i;
	   *N = 0;
	   
      printf("Termino independiente en Restricciones (D)?... "); scanf(" %d",D);
      printf("Numero de variables?... "); scanf(" %d",N);
      
      printf("Coef. func. OBJETIVO separados por un espacio (%d enteros)\n", *N);
      for (i = 0; i < *N; i++) 
         scanf("%d",&CoefFObjetivo[i]);
            
      printf("Coef. de la RESTRICCION separados por un espacio (%d enteros)\n", *N);
      for (i = 0; i < *N; i++) 
         scanf("%d",&CoefRestriccion[i]);
   }


   void Salida (TipoSolucion Sol, int N, int CoefFObjetivo[], int CoefRestriccion[]) {
	   int i;
	
      printf("\n\nEl valor de suma maxima es %d, y se obtiene con: \n\n", Sol.Suma);
	   for (i = 0; i < N; i++) 
		   printf("X%d = %3d, --> Valor a sumar (%4d)\n", 
		             i, Sol.Variable[i], Sol.Variable[i]*CoefFObjetivo[i]);
      printf("\n\n");
         
   }   



