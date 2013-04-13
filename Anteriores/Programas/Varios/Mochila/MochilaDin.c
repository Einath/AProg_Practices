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


   void MochilaDin (int k, int VolDisp, TSolucion *SolOptima, TObjeto Objetos[], int N) {

      TSolucion SolMeterlo, SolNOMeterlo;

      if (VolDisp < 0) SolOptima->Beneficio = -INFINITO;
      else if (k == N) SolOptima->Beneficio = 0;
           else {
                /* Metemos el objeto en la mochila */
                MochilaDin (k+1,VolDisp-Objetos[k].Volumen,&SolMeterlo,Objetos,N);
                SolMeterlo.Beneficio += Objetos[k].Beneficio;
                SolMeterlo.Objeto[k] = TRUE;
                
                /* NO Metemos el objeto en la mochila */
                MochilaDin (k+1,VolDisp,&SolNOMeterlo,Objetos,N);
                SolNOMeterlo.Objeto[k] = FALSE;
                
                if (SolMeterlo.Beneficio > SolNOMeterlo.Beneficio) *SolOptima = SolMeterlo;
                else *SolOptima = SolNOMeterlo;
           }
   }




   void Salida (TSolucion Sol, int Volumen, TObjeto Objetos[], int N) {
      int i, VolOcupado = 0;
      
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
   TSolucion SolOptima;

   Entrada (&N,&Volumen,Objetos);
   MochilaDin (0,Volumen,&SolOptima,Objetos,N);
   Salida(SolOptima,Volumen,Objetos,N);

   return 0;
}
