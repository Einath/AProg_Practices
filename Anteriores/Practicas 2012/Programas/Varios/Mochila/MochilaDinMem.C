#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXDIM 20
#define MAXVOLUMEN 200
#define INFINITO 10000

//typedef int boolean;

typedef struct {
   int Beneficio;
   int Objeto [MAXDIM]; /* Vector de Booleanos que nos indica si cogemos o no el objeto */
} TSolucion;


typedef struct {
	int Volumen, Beneficio;
} TObjeto;	

typedef struct {
	int Calculado;
	TSolucion Sol;
} TDato;

typedef TDato TMemoria [MAXVOLUMEN][MAXDIM];


   
   int Busca (TMemoria *Mem, int N, int k, int Vol, TSolucion *SolOptima) {
   	  
   	  if ((*Mem)[Vol][k].Calculado) *SolOptima = (*Mem)[Vol][k].Sol;
   	  return ((*Mem)[Vol][k].Calculado);
   }
   	
   void Almacenar (TMemoria *Mem, int N, int k, int Vol, TSolucion SolOptima) {
   	  (*Mem)[Vol][k].Calculado = TRUE;
   	  (*Mem)[Vol][k].Sol = SolOptima;
   }
   
   
   void InicializaMem (TMemoria *Mem, int N, int Vol) {
   	  int i, j;
   	  
   	  for (i = 0; i <= Vol; i++) 
   	     for (j = 0; j < N; j++) 
   	        (*Mem)[i][j].Calculado = FALSE;
   }
   

   void MochilaDinMem (int k, int VolDisp, TSolucion *SolOptima, TObjeto Objetos[], int N,
                       TMemoria *Mem) {

      TSolucion SolMeterlo, SolNOMeterlo;
      int Enc;

      if (VolDisp < 0) SolOptima->Beneficio = -INFINITO;
      else if (k == N) SolOptima->Beneficio = 0;
           else {
              Enc = Busca (Mem,N,k,VolDisp,SolOptima);
              if (!Enc) {
                 /* Metemos el objeto en la mochila */
                 MochilaDinMem (k+1,VolDisp-Objetos[k].Volumen,&SolMeterlo,Objetos,N,Mem);
                 SolMeterlo.Beneficio += Objetos[k].Beneficio;
                 SolMeterlo.Objeto[k] = TRUE;
                
                 /* NO Metemos el objeto en la mochila */
                 MochilaDinMem (k+1,VolDisp,&SolNOMeterlo,Objetos,N,Mem);
                 SolNOMeterlo.Objeto[k] = FALSE;
                
                 if (SolMeterlo.Beneficio > SolNOMeterlo.Beneficio) *SolOptima = SolMeterlo;
                 else *SolOptima = SolNOMeterlo;
              }
              Almacenar(Mem,N,k,VolDisp,*SolOptima);
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
   TMemoria Mem;

   Entrada (&N,&Volumen,Objetos);
   InicializaMem (&Mem,N,Volumen);
   MochilaDinMem (0,Volumen,&SolOptima,Objetos,N,&Mem);
   Salida(SolOptima,Volumen,Objetos,N);

   return 0;
}
