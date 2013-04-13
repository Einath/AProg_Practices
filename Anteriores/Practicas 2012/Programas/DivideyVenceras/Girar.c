#include <stdio.h>

#define MAXDIM 100


   void Girar (int Origen [MAXDIM][MAXDIM], int Girada [MAXDIM][MAXDIM],
               int Fila, int Columna, int FilaGirada, int ColGirada, int N);

   // Giramos la submatriz de la matriz Origen que comienza en [Fila,Columna]
   // y la ponemos en la submatriz de Traspuesta en la posición [FilaTrasp,ColTrasp],
   // ambas de dimensión N

               

   void Inicializa (int a[MAXDIM][MAXDIM], int N);

   void Escribe (int a[MAXDIM][MAXDIM], int N);



main () {

   int N;
   int a [MAXDIM][MAXDIM];
   int Girada [MAXDIM][MAXDIM];
   
   
   printf("Dimension de la matriz?... (debe ser potencia de 2) "); scanf(" %d",&N);

   //N = 8;
 
   Inicializa (a, N);
   
   printf("\n\nLa matriz Original es \n\n");

   Escribe (a,N);
   
   Girar (a,Girada,0,0,0,0,N);

   printf("\n\nLa matriz GIRADA es \n\n");
 
   Escribe (Girada,N);


} // Fin main



   void Girar (int Origen [MAXDIM][MAXDIM], int Girada [MAXDIM][MAXDIM],
               int Fila, int Columna, int FilaGirada, int ColGirada, int N) {
   
      if (N == 1) 
         Girada[FilaGirada][ColGirada] = Origen[Fila][Columna];
      else {
      	Girar (Origen,Girada,Fila,Columna,FilaGirada,ColGirada+N/2,N/2);
         Girar (Origen,Girada,Fila+N/2,Columna,FilaGirada,ColGirada,N/2);
         Girar (Origen,Girada,Fila+N/2,Columna+N/2,FilaGirada+N/2,ColGirada,N/2);
         Girar (Origen,Girada,Fila,Columna+N/2,FilaGirada+N/2,ColGirada+N/2,N/2);
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
   	
