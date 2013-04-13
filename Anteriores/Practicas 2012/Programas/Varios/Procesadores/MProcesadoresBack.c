#include <stdio.h>

   #define DIMMAX 20
   #define INFINITO 10000
   #define TRUE 1
   #define FALSE 0

   typedef struct {
      int coste; 
      int trabajo [DIMMAX]; // trabajo[i] es del procesador que hace el trabajo i
    } TipoSolucion;


     
   void MProcesadores (int k, int tproc[DIMMAX], 
                       TipoSolucion *sol,
                       TipoSolucion *solOptima,
                       int M, int N, int tiempo[DIMMAX][DIMMAX]);

   void Salida (TipoSolucion sol, int M, int N, int tiempo[DIMMAX][DIMMAX]);
   
   
   int maximo (int tproc[DIMMAX], int M) {
   	int i, max;
   	
   	max = tproc[0];
   	for (i=1; i<M; i++) if (max < tproc[i]) max = tproc[i];
   	return max;
   }


   void Copia (TipoSolucion sol, TipoSolucion *solCopia, int N) {
   	int i;
   	
   	(*solCopia).coste = sol.coste;
   	for (i=0; i<N; i++) 
   	   (*solCopia).trabajo[i] = sol.trabajo[i];
   }
   

   void Inicializa (int tproc[DIMMAX], TipoSolucion *sol, int M) {
   	int i;
   	
   	for (i=0; i<M; i++) tproc[i] = 0;
   	(*sol).coste = INFINITO;
   }
   
   
   void Entrada (int *M, int *N, int tiempo[DIMMAX][DIMMAX]);
   	
   
int main () {

   int tiempo [DIMMAX][DIMMAX]; // matriz de costes 
    
   int M, N;
   TipoSolucion sol, solOptima;
   int tproc [DIMMAX];
   
   // entrada de datos
  
   Entrada(&M,&N,tiempo); 
   
   Inicializa (tproc,&solOptima,M);
       
   MProcesadores(0,tproc,&sol,&solOptima,M,N,tiempo);

   Salida(solOptima,M,N,tiempo);
      
   return 0;
      
}
   
   

   void MProcesadores (int k, int tproc[DIMMAX], 
                       TipoSolucion *sol, 
                       TipoSolucion *solOptima, 
                       int M, int N, int tiempo[DIMMAX][DIMMAX]) {

      int p;

      (*sol).coste = maximo (tproc,M);
      if ((*sol).coste < (*solOptima).coste) 
         if (k == N)
            Copia(*sol,solOptima,N);
         else {
            for (p=0; p<M; p++) {
               // lo hace el procesador p
               tproc[p] += tiempo[p][k];
               (*sol).trabajo[k] = p;
      	      MProcesadores (k+1,tproc,sol,solOptima,M,N,tiempo);

               // deshacemos para la siguiente iteración
               tproc[p] -= tiempo[p][k];
     	      }
         }        
   }        


   void Entrada (int *M, int *N, int tiempo[DIMMAX][DIMMAX]) {
   	
   	int i, j;
   	

      printf("Introduzca el número de trabajos "); scanf("%d",N);
      printf("Introduzca el número de procesadores "); scanf("%d",M);
      for (i=0; i<*M; i++) {
         printf("\nDuración de los trabajos en el procesador %d (separados por un espacio)\n",i);
         for (j=0; j<*N; j++) 
            scanf(" %d", &tiempo[i][j]);  
      }
   
      printf("\n\n");
      for (i= 0; i<*M; i++) {
         for (j=0; j<*N; j++) 
            printf(" %4d",tiempo[i][j]);
         printf("\n");
      }
   
      	
   	
   	
   }



   void Salida (TipoSolucion sol, int M, int N, int tiempo[DIMMAX][DIMMAX]) {
      int i, p;
      
      for (p= 0; p<M; p++) {
      	printf("\nTrabajos realizados por el procesador %d: ", p);
         for (i=0; i<N; i++)
            if (sol.trabajo[i] == p) printf("%d  (+ %d ) ", i, tiempo[p][i]);
         printf("\n");
      }   
      printf("\n\nEl coste de la solucion es: %d",sol.coste);

   }
	