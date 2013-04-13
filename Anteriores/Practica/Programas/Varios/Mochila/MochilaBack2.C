#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXDIM 20
#define INFINITO 10000


typedef struct {
   int Beneficio;
   int Objeto [MAXDIM]; /* Vector de Booleanos que nos indica si cogemos o no el objeto */
} TSolucion;


typedef struct {
	int Volumen, Beneficio;
} TObjeto;	


   void MochilaBack2 (int k, int VolDisp, TSolucion *Sol, TSolucion *SolOptima,
                     TObjeto Objetos[], int N) {
      /* VolDisp >= 0 */

      if (k == N) {
         if (SolOptima->Beneficio < Sol->Beneficio) *SolOptima = *Sol;
      }
      else {
         /* Soluciones que resultan si Metemos el objeto en la mochila, */
         /* si podemos, i.e., si tenemos volumen disponible             */
         if (VolDisp >= 0) 
            Sol->Beneficio += Objetos[k].Beneficio;
            Sol->Objeto[k] = TRUE;
            MochilaBack2 (k+1,VolDisp-Objetos[k].Volumen,Sol,SolOptima,Objetos,N);
            /* Deshacemos */ 
            Sol->Beneficio -= Objetos[k].Beneficio;
         }
         /* Soluciones que resultan si NO Metemos el objeto en la mochila, */
         /* esto siempre lo podemos hacer                                  */
         Sol->Objeto[k] = FALSE;
         MochilaBack2 (k+1,VolDisp,Sol,SolOptima,Objetos,N);
      }
   }



   void Inicializa (TSolucion *Sol, TSolucion *SolOptima) {
   	Sol->Beneficio = 0;
   	SolOptima->Beneficio = -INFINITO;
   }



   void Salida (TSolucion Sol, int Volumen, TObjeto Objetos[], int N) {
      int i, VolOcupado = 0;
      
      if (Sol.Beneficio == -INFINITO)
         printf("El problema no tiene solucion\n");      
      else {
         printf("Objetos que metemos en la mochila:\n");
         for (i=0; i<N; i++) 
            if (Sol.Objeto[i]) {
               printf("%3d (Ben %3d, Vol %3d)\n",i,Objetos[i].Beneficio,Objetos[i].Volumen);
               VolOcupado += Objetos[i].Volumen;
            }
         printf("\n");
         printf("El volumen de la mochila es: %d, el volumen OCUPADO: %d,\n", Volumen,VolOcupado);
         printf("y el BENEFICIO obtenido es: %d\n", Sol.Beneficio);
      }
   }



   void Entrada (int *N, int *Volumen, TObjeto Objetos[]) {
   	
      int i;

      printf("Numero de objetos (< %d) ",MAXDIM); scanf("%d",N);
      printf("Volumen disponible en la mochila... "); scanf("%d",Volumen);
      printf("Volumen de los objetos(separados por un espacio)\n");
      for (i=0; i<*N; i++) scanf(" %d", &Objetos[i].Volumen);

      printf("Beneficio de los objetos(separados por un espacio)\n");
      for (i=0; i<*N; i++) scanf(" %d", &Objetos[i].Beneficio);
   }




int main(){

   TObjeto Objetos[MAXDIM];
   int N, Volumen;
   TSolucion Sol, SolOptima;

   Entrada (&N,&Volumen,Objetos);
   Inicializa (&Sol,&SolOptima);
   MochilaBack2 (0,Volumen,&Sol,&SolOptima,Objetos,N);
   Salida(SolOptima,Volumen,Objetos,N);

   return 0;
}
