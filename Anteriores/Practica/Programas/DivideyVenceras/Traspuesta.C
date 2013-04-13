#include <stdio.h>

#define MAXDIM 100


   void Trasponer (int Origen [MAXDIM][MAXDIM], int Traspuesta [MAXDIM][MAXDIM],
                   int Fila, int Columna, int FilaTrasp, int ColTrasp, int N);
                   
   // Trasponemos la submatriz de la matriz Origen que comienza en [Fila,Columna]
   // y la ponemos en la submatriz de Traspuesta en la posición [FilaTrasp,ColTrasp],
   // ambas de dimensión N

   void Inicializa (int a[MAXDIM][MAXDIM], int N);

   void Escribe (int a[MAXDIM][MAXDIM], int N);



main () {

   int N;
   int a [MAXDIM][MAXDIM];
   int Traspuesta [MAXDIM][MAXDIM];
   
   
   printf("Dimension de la matriz?... (debe ser potencia de 2) "); scanf(" %d",&N);

   //N = 8;
 
   Inicializa (a, N);
   
   printf("\n\nLa matriz Original es \n\n");

   Escribe (a,N);
   
   Trasponer (a,Traspuesta,0,0,0,0,N);

   printf("\n\nLa matriz TRASPUESTA es \n\n");
 
   Escribe (Traspuesta,N);


} // Fin main



   void Trasponer (int Origen [MAXDIM][MAXDIM], int Traspuesta [MAXDIM][MAXDIM],
                   int Fila, int Columna, int FilaTrasp, int ColTrasp, int N) {
   
      if (N == 1) 
         Traspuesta[FilaTrasp][ColTrasp] = Origen[Fila][Columna];
      else {
      	Trasponer (Origen,Traspuesta,Fila,Columna,FilaTrasp,ColTrasp,N/2);
         Trasponer (Origen,Traspuesta,Fila+N/2,Columna,FilaTrasp,ColTrasp+N/2,N/2);
         Trasponer (Origen,Traspuesta,Fila,Columna+N/2,FilaTrasp+N/2,ColTrasp,N/2);
         Trasponer (Origen,Traspuesta,Fila+N/2,Columna+N/2,FilaTrasp+N/2,ColTrasp+N/2,N/2);
      }         	
               	
   }

   

   void Escribe (int a[MAXDIM][MAXDIM], int N) {
      int i, j;

      for (i = 0; i < N; i++) {
         for (j= 0; j < N; j++)
            printf(" %4d ",a[i][j]);
         printf("\n");
      }
      printf("\n");
   }
   

   void Inicializa (int a[MAXDIM][MAXDIM], int N) {
      int i, j;

      for (i = 0; i < N; i++) 
         for (j= 0; j < N; j++)
            a[i][j] = i*N + j;
   }
   	
