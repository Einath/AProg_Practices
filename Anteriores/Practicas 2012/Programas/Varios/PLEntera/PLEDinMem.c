#include <stdio.h>
#include <stdlib.h>

#define INFINITO 10000
#define MAXDIM 100
#define MAXVALOR 100     /* Valor máximo del término independiente D */
#define TRUE 1
#define FALSE 0


typedef struct {
	int Suma;		 
	int Variable[MAXDIM]; /* Valor de la Variable[i] es el valor de la variable i*/
} TipoSolucion;

typedef struct {
	int Calculado;
	TipoSolucion Sol;
} TipoDato;

typedef TipoDato TipoMemoria [MAXVALOR][MAXDIM];


   void PLEDin (int k, int puntos, TipoSolucion *SolOptima,
                int N, int CoefFObjetivo[], int CoefRestriccion[],
                TipoMemoria *Mem);
                   
   
   void LeeDatos (int *D, int *N, int CoefFObjetivo[], int CoefRestriccion[]);
   void Salida (TipoSolucion Sol, int N, int CoefFObjetivo[], int CoefRestriccion[]);

   
   int Busca (TipoMemoria *Mem, int N, int k, int D, TipoSolucion *SolOptima) {
   	  
   	  if ((*Mem)[D][k].Calculado) *SolOptima = (*Mem)[D][k].Sol;
   	  return ((*Mem)[D][k].Calculado);
   }
   	
   void Almacenar (TipoMemoria *Mem, int N, int k, int Puntos, TipoSolucion SolOptima) {
   	  (*Mem)[Puntos][k].Calculado = TRUE;
   	  (*Mem)[Puntos][k].Sol = SolOptima;
   }
   
   
   void InicializaMem (TipoMemoria *Mem, int N, int D) {
   	  int i, j;
   	  
   	  for (i = 0; i <= D; i++) 
   	     for (j = 0; j < N; j++) 
   	        (*Mem)[i][j].Calculado = FALSE;
   }
   



int main () {

	int CoefFObjetivo[MAXDIM], CoefRestriccion[MAXDIM];
	TipoSolucion SolOptima;
	int N, D;
	TipoMemoria Mem;
	
	
	LeeDatos (&D, &N, CoefFObjetivo, CoefRestriccion);
	
	if (D >= MAXVALOR) {
		printf("ERROR: D < %D\n",MAXVALOR);
		return 0;
   }
	
	InicializaMem (&Mem,N,D);
	
	PLEDin (0,D,&SolOptima,N,CoefFObjetivo,CoefRestriccion,&Mem);
	
   Salida (SolOptima, N, CoefFObjetivo,CoefRestriccion);
	
} /* main */



   void PLEDin (int k, int D, TipoSolucion *SolOptima,
                int N, int CoefFObjetivo[], int CoefRestriccion[],
                TipoMemoria *Mem) {
                   
	   int i, Enc;
	   TipoSolucion Sol, SolMejor;
	
	   Enc = Busca (Mem, N, k, D, SolOptima);
	   if (!Enc) {
   	   if (k == N) 
	   	   if (D >= 0) SolOptima->Suma = 0;
		      else SolOptima->Suma = -INFINITO; // Nunca se dará por construcción
		   else {
		 	   SolMejor.Suma = -INFINITO;
		      for (i = D / CoefRestriccion[k]; i >= 0; i--) {
		 	      PLEDin (k+1, D-i*CoefRestriccion[k], &Sol, N, CoefFObjetivo, CoefRestriccion, Mem);
               Sol.Variable[k] = i;
               Sol.Suma += i*CoefFObjetivo[k];
               // Comparamos con la mejor en esta etapa
               if (Sol.Suma > SolMejor.Suma) SolMejor = Sol;
            }
            *SolOptima = SolMejor;
         }
         Almacenar(Mem, N, k, D, *SolOptima);
      }   
      
   } // Fin PLEDin



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



