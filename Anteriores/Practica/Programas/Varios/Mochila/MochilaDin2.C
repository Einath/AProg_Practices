#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXDIM 20
#define MAXVOLUMEN 200
#define INFINITO 10000


typedef struct {
   int Beneficio;
   int Objeto [MAXDIM]; /* Vector de Booleanos que nos indica si cogemos o no el objeto */
} TSolucion;


typedef struct {
	int Volumen, Beneficio;
} TObjeto;	



   
   void MochilaDin2 (int VolDisp, TSolucion *SolOptima, TObjeto Objetos[], int N) {
   	
      int i, j, k; int Opc, Vol, VolRestante;
      typedef struct {
      	 int Beneficio, Opcion; /* Opcion 1: elegido;  Opcion 0: NO elegido */
      } TDato;
      TDato Tabla[MAXVOLUMEN][MAXDIM];
      TDato Mejor;
      	 
      for (i=0; i<=VolDisp; i++) 
      	Tabla[i][N].Beneficio = 0;
      
      for (k = N-1; k>=0; k--)
         for (Vol = 0; Vol <= VolDisp; Vol++) {
      	   Mejor.Beneficio = -INFINITO;
      	   for (Opc=0; Opc<=1; Opc++) {
      	   	VolRestante = Vol - Opc*Objetos[k].Volumen;
      	      if (VolRestante >= 0) 
      	         if (Tabla[VolRestante][k+1].Beneficio + Opc*Objetos[k].Beneficio > Mejor.Beneficio) {
      	            Mejor.Beneficio = Tabla[VolRestante][k+1].Beneficio + Opc*Objetos[k].Beneficio;
      	         	Mejor.Opcion = Opc;
      	         }
      	   }
      	   Tabla[Vol][k] = Mejor;
      	}

/*     
      for (i=0; i<=VolDisp; i++) {
         for (j= 0; j<N; j++)
            printf("->%d-%2d ( %d)  ",i,Tabla[i][j].Beneficio,Tabla[i][j].Opcion );
         printf("\n");
      }
      printf("\n\n");
*/   
      
      Vol = VolDisp;      
      SolOptima->Beneficio = Tabla[VolDisp][0].Beneficio;
      SolOptima->Objeto[0] = Tabla[VolDisp][0].Opcion;
      for (k=1; k<N; k++) {
      	Vol -= SolOptima->Objeto[k-1] * Objetos[k-1].Volumen;
         SolOptima->Objeto[k] = Tabla[Vol][k].Opcion;
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
      printf("Volumen disponible en la mochila... (< %d) ",MAXVOLUMEN); scanf("%d",Volumen);
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
   MochilaDin2 (Volumen,&SolOptima,Objetos,N);
   Salida(SolOptima,Volumen,Objetos,N);

   return 0;
}
