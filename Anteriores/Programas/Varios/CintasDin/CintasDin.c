#include <stdio.h>
#define CARA_A 1
#define CARA_B 2
#define MAXDIM 20
#define MAXIMO(A,B) ((A>=B)?A:B)


typedef struct {
   int tiempo;
   int cancion [MAXDIM]; /* La cancion i esta en la caraA o CaraB */
} TSolucion;



   void CintasDinamica (int k, int tiempoA, int tiempoB,
                        TSolucion *solucion, int canciones[], int N){

      TSolucion solcaraA, solcaraB;

      if (k == N )
         solucion->tiempo = MAXIMO(tiempoA,tiempoB);
      else {
         /* La cancion k se mete en una de las caras */
         /*La metemos en la cara_A*/
         CintasDinamica(k+1,tiempoA+canciones[k],tiempoB,&solcaraA, 
                        canciones,N);
         solcaraA.cancion[k] = CARA_A;

         /*La metemos en la CARA_B*/
         CintasDinamica(k+1,tiempoA,tiempoB+canciones[k],&solcaraB,
                        canciones,N);
         solcaraB.cancion[k] = CARA_B;

         if (solcaraB.tiempo > solcaraA.tiempo) *solucion = solcaraA;
         else *solucion = solcaraB;
      }
   }


   void Salida (TSolucion sol, int canciones[MAXDIM], int N) {
      int i;
      
      printf("\nCanciones en la caraA: ");
      for (i=0; i<N; i++)
         if (sol.cancion[i] == CARA_A)
            printf("%d ( %d'), ",i,canciones[i]);

      printf("\nCanciones en la caraB: ");
      for (i=0; i<N; i++)
         if (sol.cancion[i] == CARA_B)
            printf("%d ( %d'), ",i,canciones[i]);
      printf("\n\nEl tiempo de cara que mas tarda es: %d",sol.tiempo);

   }


int main(){

   int canciones[MAXDIM];
   int N = 10;
   TSolucion resultado;

   canciones[0]=1;   canciones[5]=10;
   canciones[1]=2;   canciones[6]=2;
   canciones[2]=4;   canciones[7]=30;
   canciones[3]=5;   canciones[8]=4;
   canciones[4]=6;   canciones[9]=3;


   CintasDinamica(0,0,0,&resultado,canciones,N);
   Salida(resultado,canciones,N);

return 0;
}
