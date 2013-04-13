#include <stdio.h>

   #define MAX 20
   #define INFINITO 1000
   #define TRUE 1
   #define FALSE 0

   typedef struct {
      int tiempo; 
      int trabajo [MAX]; // vector[i] es del procesador que hace el trabajo i
    } TipoSolucion;

     
   void ProcesadoresBack (int Etapa, int tiempo1, int tiempo2, 
                          TipoSolucion *sol, TipoSolucion *solOptima, int N, int Coste[2][MAX]);
   void Salida (TipoSolucion sol, int N, int Coste[2][MAX]);
   
   void Inicializa (TipoSolucion *solOptima);
   
   int maximo (int a, int b) {
      if (a < b) return b ;else return a;
   }

   
int main () {

   int Coste [2][MAX]; // matriz de costes 
    
   int N, i, j;
   TipoSolucion sol, solOptima;
   
   // entrada de datos

   printf("Introduzca el número de trabajos "); scanf("%d",&N);
   printf("\nDuración de los trabajos en el procesador 0 (separados por un espacio)\n");
   for (i=0; i<N; i++) 
      scanf(" %d", &Coste[0][i]);  
   printf("\nDuración de los trabajos en el procesador 1 (separados por un espacio)\n");
   for (i=0; i<N; i++) 
      scanf(" %d", &Coste[1][i]);  

   for (i= 0; i<2; i++) {
      for (j=0; j<N; j++) 
         printf(" %4d",Coste[i][j]);
      printf("\n");
   }
   
   Inicializa (&solOptima);    
       
   ProcesadoresBack(0,0,0,&sol,&solOptima,N,Coste);

   Salida(solOptima,N,Coste);
      
   return 0;
      
}
   
   

   void ProcesadoresBack (int Etapa, int tiempo1, int tiempo2, 
                          TipoSolucion *sol, TipoSolucion *solOptima, int N, int Coste[2][MAX]) {

      if (Etapa == N) {
         sol->tiempo = maximo (tiempo1,tiempo2);
         if (sol->tiempo < solOptima->tiempo) *solOptima = *sol;
      }
      else {
         // lo hace el procesador 0
         sol->trabajo[Etapa] = 0;
      	ProcesadoresBack (Etapa+1,tiempo1+Coste[0][Etapa],tiempo2,sol,solOptima,N,Coste);

         // lo hace el procesador 1
         sol->trabajo[Etapa] = 1;
      	ProcesadoresBack (Etapa+1,tiempo1,tiempo2+Coste[1][Etapa],sol,solOptima,N,Coste);
      }
   }        
   
   

   void Inicializa (TipoSolucion *solOptima) {
   	solOptima->tiempo = INFINITO;
   }



   void Salida (TipoSolucion sol, int N, int Coste[2][MAX]) {
      int i;
      
      printf("\nTrabajos realizados por el procesador 0: ");
      for (i=0; i<N; i++)
         if (sol.trabajo[i] == 0) printf("%d  (+ %d ) ", i, Coste[0][i]);

      printf("\nTrabajos realizados por el procesador 1: ");
      for (i=0; i<N; i++) 
         if (sol.trabajo[i] == 1) printf("%d  (+ %d ) ", i, Coste[1][i]);
      printf("\n\nEl coste de la solucion es: %d",sol.tiempo);

   }
	