#include <stdio.h>


   #define MAX 20
   #define TRUE 1
   #define FALSE 0
   
      
   
   void SumaSolRecursiva (int Etapa, int Estado[], int Suma, int N, int A[]);

   void Salida (int Etapa, int Estado[], int A[]);
   
   		
   
int main () {

   int Estado[MAX], // índices de los elementos de A que tomamos
       A[MAX];      // supondremos que A empieza en 1
    
   int N = 1, suma, i;
   
   printf("Introduzca los elementos separados por un espacio añadiendo 0 al final\n");
   scanf("%d",&A[N]);
   while (A[N] > 0) {
      scanf(" %d", &A[++N]);  
   }
      
   printf("\nIntroduzca la cantidad a sumar "); scanf("%d", &suma);
            
   printf("\n\nNumero de elementos %d\n",N);
   printf("Los elementos son... ");
   for (i=1; i<N; i++) printf("%d ",A[i]);
   printf("\ny la cantidad a sumar %d\n\n", suma);


   Estado[0] = 0; // Estado empieza en 1, para hacer más simple el código

   SumaSolRecursiva(1,Estado,suma,N,A);
      
   return 0;
      
}
   
   

   void SumaSolRecursiva (int Etapa, int Estado[], int Suma, int N, int A[]) {
      int i;

      if (Suma == 0) 
         Salida (Etapa, Estado, A);
      else  
         // si podemos prolongar, prolongamos, 
         // en otro caso es un fracaso
         for (i = Estado[Etapa-1]+1; i<N; i++) 
            // si podemos cogerlo lo cogemos
            if (A[i] <= Suma) {
               Estado[Etapa] = i;
               SumaSolRecursiva (Etapa+1, Estado, Suma-A[i], N, A);
            }   
   }        


   void Salida (int Etapa, int Estado[], int A[]) {
      int i, suma = 0;
      
      for (i=1; i<Etapa-1; i++) suma += A[Estado[i]];
      printf("\n%d = ", suma);
      for (i=1; i<Etapa-1; i++)
         printf("%d + ",A[Estado[i]]);
      printf("%d.", A[Estado[Etapa-1]]);
   }
	
