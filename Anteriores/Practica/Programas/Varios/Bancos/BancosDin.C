#include <stdio.h>

#define MAXCAPITAL 100
#define MAXBANCOS 20
#define INFINITO 10000
#define TRUE 1
#define FALSE 0


   typedef struct {
      int beneficio; 
      int inversion [MAXBANCOS]; // inversion[i] es del capital invertido en el banco i
    } TSolucion;


     
   void BancosDin (int k, int disponible, TSolucion *solOptima,
                   int M, int N, int rend[MAXCAPITAL][MAXBANCOS]);

   void Salida (TSolucion sol, int M, int N, int rend[MAXCAPITAL][MAXBANCOS]);
   
   
   
   int minimo (int a, int b) {
      if (a<b) return a; else return b;
   }



   void Inicializa (TSolucion *sol, TSolucion *solOptima) {

   	solOptima->beneficio = -INFINITO;
   	sol->beneficio = 0;
   }
   
   
   void Entrada (int *Cap, int *M, int *N, int rend[MAXCAPITAL][MAXBANCOS]);
   	
   
int main () {

   int rend[MAXCAPITAL][MAXBANCOS]; // matriz de rendimientos
    
   int Cap; // Capital disponible para invertir
   int M;   // capital máximo que se puede invertir en un banco
   int N;   // numero de bancos
   TSolucion sol, solOptima;
   

   Entrada(&Cap,&M,&N,rend); 
   BancosDin(0,Cap,&solOptima,M,N,rend);
   Salida(solOptima,M,N,rend);
      
   return 0;
}
   
   

   void BancosDin (int k, int disponible, TSolucion *solOptima,
                   int M, int N, int rend[MAXCAPITAL][MAXBANCOS]) {

      int c;
      TSolucion solMejor, sol;

      if (k == N) 
         solOptima->beneficio = 0;
      else {
      	solMejor.beneficio = - INFINITO;
         for (c = 0; c <= minimo(M,disponible); c++) {
            // invertimos el capital c en el banco k
            BancosDin (k+1,disponible-c,&sol,M,N,rend);
      	   sol.inversion[k] = c;
            sol.beneficio += rend[c][k];
      	    // actualizamos si es mejor
      	    if (sol.beneficio > solMejor.beneficio) solMejor = sol;
      	 }
         *solOptima = solMejor;
      }        
   }        



   void Entrada (int *Cap, int *M, int *N, int rend[MAXCAPITAL][MAXBANCOS]) {
   	
      int i, j;

      printf("Numero de bancos (< %d) ",MAXBANCOS); scanf("%d",N);
      printf("Cantidad a invertir (< %d) ",MAXCAPITAL); scanf("%d",Cap);
      printf("Maxima cantidad a invertir en un banco (< %d) ",MAXCAPITAL); scanf("%d",M);
      for (i=0; i<*N; i++) {
         printf("Rendimientos en el banco %d (separados por un espacio)\n",i);
         for (j=0; j<=*M; j++) 
            scanf(" %d", &rend[j][i]);  
      }
   
      printf("\n\n");
      for (i= 0; i<*N; i++) {
         for (j=0; j<=*M; j++) 
            printf(" %4d",rend[j][i]);
         printf("\n");
      }
  
   }



   void Salida (TSolucion sol, int Cap, int N, int rend[MAXCAPITAL][MAXBANCOS]) {
      int i, inversionTotal = 0;
      
      printf("\nCapital disponible para invertir: %d\n", Cap);
      for (i= 0; i<N; i++) {
      	printf("\nCapital invertido en el banco %4d -> %4d  (rend: %3d )",
      	       i, sol.inversion[i], rend[sol.inversion[i]][i]);
      	inversionTotal += sol.inversion[i];       
      }   
      printf("\n\nEl beneficio de la solucion es: %d\n",sol.beneficio);
      printf("En total se han invertido: %d\n", inversionTotal);

   }
	