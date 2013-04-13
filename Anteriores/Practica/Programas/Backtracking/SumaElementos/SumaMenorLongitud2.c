#include <stdio.h>

   #define MAX 20
   #define INFINITO 1000
   #define TRUE 1
   #define FALSE 0

   typedef struct {
      int longitud;
      int indice[MAX];
    } TipoSolucion;

     
   void SumaSolMenorLong (int Etapa, int Estado[], int k, int SumaAcum,
                          TipoSolucion *solOptima,
                          int N, int A[]);

   void Salida (TipoSolucion sol, int Suma, int A[]);
   
   		
   
int main () {

   int Estado[MAX], // índices de los elementos de A que tomamos
       A[MAX];      // supondremos que A empieza en 1
    
   int N = 1, suma, i;
   TipoSolucion solOptima;
   
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

   solOptima.longitud = INFINITO;
   Estado[0] = 0; // los índices empiezan en 1
    
   SumaSolMenorLong(1,Estado,suma,0,&solOptima,N,A);

   Salida(solOptima,suma,A);
      
   return 0;
}
   
   

   void SumaSolMenorLong (int Etapa, int Estado[], int k, int SumaAcum,
                          TipoSolucion *solOptima,
                          int N, int A[]) {
      int i;

      if (Etapa-1 < (*solOptima).longitud)  
         // Solo seguimos si la solución que estamos construyendo 
         // es menor que la más corta que tenemos
         if (SumaAcum == k) {
            // hemos encontrado una solución más corta, actualizamos
            solOptima->longitud = Etapa-1;
            for (i=1; i<Etapa; i++) solOptima->indice[i] = Estado[i]; 

         }
         else  
            // si podemos prolongamos, en otro caso es un fracaso
            for (i = Estado[Etapa-1]+1; i<N; i++) 
               // si podemos cogerlo lo cogemos
               if (SumaAcum+A[i] <= k) {
                  Estado[Etapa] = i;
                  SumaSolMenorLong (Etapa+1, Estado, k, SumaAcum+A[i],
                                    solOptima, N, A);
               }
   }      


   void Salida (TipoSolucion sol, int Suma, int A[]) {
      int i;
      
      printf("\nLa longitud de la solucion es %d y la solucion es:",
             sol.longitud);
      printf("\n%d = ", Suma);
      for (i=1; i<sol.longitud; i++)
         printf("%d + ",A[sol.indice[i]]);
      printf("%d.", A[sol.indice[sol.longitud]]);
   }
	
