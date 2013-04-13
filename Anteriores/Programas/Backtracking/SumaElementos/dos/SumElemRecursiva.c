#include <stdio.h>


   typedef int boolean;
   #define MAX 20
   #define TRUE 1
   #define FALSE 0
   
      
   
   void SumaElemRecursiva (int Etapa, boolean Estado[], int Suma, int N, int A[]);

   void Salida (int Etapa, boolean Estado[], int A[]);
   
   		
   
int main () {

   boolean Estado[MAX];
   int  A[MAX];
    
   int N = 0, suma, i;
   
   printf("Introduzca los elementos separados por un espacio añadiendo 0 al final\n");
   scanf("%d",&A[N]);
   while (A[N] > 0) {
      scanf(" %d", &A[++N]);  
   }
      
   printf("\nIntroduzca la cantidad a sumar "); scanf("%d", &suma);
            
   printf("\n\nNumero de elementos %d\n",N);
   printf("Los elementos son... ");
   for (i=0; i<N; i++) printf("%d ",A[i]);
   printf("\ny la cantidad a sumar %d\n\n", suma);


   for (i=0; i<N; i++) Estado[i] = FALSE;
    
   SumaElemRecursiva(0,Estado,suma,N,A);
      
   return 0;
      
}
   
   

   void SumaElemRecursiva (int Etapa, boolean Estado[], int Suma, int N, int A[]) {

      if (Etapa == N){
         if (Suma == 0) Salida (Etapa, Estado, A);
      }
      else {// si podemos cogerlo lo cogemos
         if (A[Etapa] <= Suma) {
            Estado[Etapa] = TRUE;
            SumaElemRecursiva (Etapa+1, Estado, Suma-A[Etapa], N, A);
          }
          // siempre tenemos la posibilidad de no cogerlo
          Estado[Etapa] = FALSE;
          SumaElemRecursiva (Etapa+1, Estado, Suma, N, A);
       }
   }        


   void Salida (int Etapa, boolean Estado[], int A[]) {

      int i, suma = 0, Ult = Etapa-1;
      
      while (!Estado[Ult]) Ult--;
      for (i=0; i<Ult; i++)
         if (Estado[i]) suma += A[i];
      printf("\n%d = ", suma);
      for (i=0; i<Ult; i++)
         if (Estado[i]) printf("%d + ",A[i]);
      printf("%d.", A[Ult]);
   }
	
