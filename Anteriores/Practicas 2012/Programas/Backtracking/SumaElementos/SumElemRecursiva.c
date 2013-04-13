#include <stdio.h>


   typedef int boolean;
   #define MAX 20
   #define TRUE 1
   #define FALSE 0
   
      
   
   void SumaElemRecursiva (int Etapa, boolean Estado[], int k,
                           int SumaAcum, int N, int A[]);

   void Salida (int Etapa, boolean Estado[], int Suma, int A[]);
   
   		
   
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
    
   SumaElemRecursiva(0,Estado,suma,0,N,A);
      
   return 0;
      
}
   
   

   void SumaElemRecursiva (int Etapa, boolean Estado[], int k,
                           int SumaAcum, int N, int A[]) {

      if (Etapa == N){
         if (SumaAcum == k) Salida (Etapa, Estado, SumaAcum, A);
      }
      else {// si podemos cogerlo lo cogemos
         if (SumaAcum+A[Etapa] <= k) {
            Estado[Etapa] = TRUE;
            SumaElemRecursiva (Etapa+1, Estado, k, SumaAcum+A[Etapa], N, A);
          }
          // siempre tenemos la posibilidad de no cogerlo
          Estado[Etapa] = FALSE;
          SumaElemRecursiva (Etapa+1, Estado, k, SumaAcum, N, A);
       }
   }        


   void Salida (int Etapa, boolean Estado[], int Suma, int A[]) {

      int i, Ult = Etapa-1;
      while (!Estado[Ult]) Ult--;
      printf("\n%d = ", Suma);
      for (i=0; i<Ult; i++)
         if (Estado[i]) printf("%d + ",A[i]);
      printf("%d.", A[Ult]);
   }
	
