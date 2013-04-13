#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXDIM 20
#define INFINITO 10000


typedef struct {
   int Coste;
   int Objeto [MAXDIM]; /* Vector de enteros que nos indica la bolsa en la que ponemos el objeto */
} TSolucion;



   void BolsasDin (int k, int Peso1, int Peso2, TSolucion *SolOptima, 
                   int PesoMax, int PesoMin, int Objetos[], int N) {

      TSolucion Sol1, Sol2, Sol;

      if ((Peso1 > PesoMax) || (Peso2 > PesoMax))
         SolOptima->Coste = INFINITO;
      else if (k == N) 
 	           if ((Peso1 >= PesoMin) && (Peso2 >= PesoMin)) 
			        SolOptima->Coste = abs(Peso1 - Peso2);
		        else SolOptima->Coste = INFINITO;
		     else {

			     /* Lo metemos en la bolsa 1 */
              BolsasDin (k+1,Peso1+Objetos[k],Peso2,&Sol1,PesoMax,PesoMin,Objetos,N);
              Sol1.Objeto[k] = 1;
                
			     /* Lo metemos en la bolsa 2 */
              BolsasDin (k+1,Peso1,Peso2+Objetos[k],&Sol2,PesoMax,PesoMin,Objetos,N);
              Sol2.Objeto[k] = 2;
              
              if (Sol1.Coste < Sol2.Coste) *SolOptima = Sol1;
              else *SolOptima = Sol2;
                
			     /* No lo metemos en ninguna bolsa */
              BolsasDin (k+1,Peso1,Peso2,&Sol,PesoMax,PesoMin,Objetos,N);
              Sol.Objeto[k] = 0;

              if (Sol.Coste < SolOptima->Coste) *SolOptima = Sol;
           }
   }



   void Salida (TSolucion Sol, int PesoMax, int PesoMin, int Objetos[], int N) {
      int i, k, Peso;
      
      printf("\n\nEl Peso Maximo es: %d, y el Peso Minimo es: %d\n\n",PesoMax,PesoMin);
      printf("Los pesos de los objetos son:\n");
      for (i=0; i<N; i++) printf("%3d ( %3d), ",i,Objetos[i]);
      printf("\n\n");   
      for (k= 1; k<=2; k++) {
         Peso = 0;
         printf("Objetos que metemos en la bolsa %d:\n",k);
         for (i=0; i<N; i++) 
            if (Sol.Objeto[i] == k) {
               printf("%3d ( %3d), ",i,Objetos[i]);
               Peso += Objetos[i];
            }
         printf("\nEl peso total de dicha bolsa es: %d\n\n",Peso);
      }
      printf("La diferencia de pesos es: %d\n", Sol.Coste);
   }



   void Entrada (int *N, int Objetos[], int *PesoMax, int *PesoMin) {

      int i;

      printf("Numero de objetos (< %d) ",MAXDIM); scanf("%d",N);
      printf("Peso Minimo... "); scanf("%d",PesoMin);
      printf("Peso Maximo... "); scanf("%d",PesoMax);
      printf("Volumen de los objetos(separados por un espacio)\n");
      for (i=0; i<*N; i++) scanf(" %d", &Objetos[i]);
   }




int main(){

   int Objetos[MAXDIM];
   int N, PesoMaximo, PesoMinimo;
   TSolucion SolOptima;

   Entrada (&N,Objetos,&PesoMaximo,&PesoMinimo);
   BolsasDin (0,0,0,&SolOptima,PesoMaximo,PesoMinimo,Objetos,N);
   Salida(SolOptima,PesoMaximo,PesoMinimo,Objetos,N);

   return 0;
}
