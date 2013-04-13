#include <stdio.h>

#define MAXCAPITAL 100
#define MAXBANCOS 20
#define INFINITO 10000
#define TRUE 1
#define FALSE 0


   typedef struct {
      int beneficio; 
      int inversion [MAXBANCOS]; // inversion[i] es del capital invertido en el banco i
    } TSolucion;


     
   void BancosDin2 (int disponible, TSolucion *solOptima,
                    int M, int N, int rend[MAXCAPITAL][MAXBANCOS]);

   void Salida (TSolucion sol, int M, int N, int rend[MAXCAPITAL][MAXBANCOS]);
   
  
   int minimo (int a, int b) {
      if (a<b) return a; else return b;
   }


   void Inicializa (TSolucion *sol, TSolucion *solOptima) {

   	solOptima->beneficio = -INFINITO;
   	sol->beneficio = 0;
   }
   
   
   void Entrada (int *Cap, int *M, int *N, int rend[MAXCAPITAL][MAXBANCOS]);
   	
   
int main () {

   int rend[MAXCAPITAL][MAXBANCOS]; // matriz de rendimientos
    
   int Cap; // Capital disponible para invertir
   int M;   // capital máximo que se puede invertir en un banco
   int N;   // numero de bancos
   TSolucion sol, solOptima;

  
   Entrada(&Cap,&M,&N,rend); 
   BancosDin2 (Cap,&solOptima,M,N,rend);
   Salida(solOptima,Cap,N,rend);
      
   return 0;
}
   
   

   void BancosDin2 (int disponible, TSolucion *solOptima,
                    int M, int N, int rend[MAXCAPITAL][MAXBANCOS]) {

      int i, j, k, disp, qinv;
      typedef struct {
      	int beneficio, resto;
      } TDato;
      TDato tabla[MAXCAPITAL][MAXBANCOS];
      TDato mejor;
      	 
      for (i=0; i<=disponible; i++) 
      	tabla[i][N].beneficio = 0;
      
      for (k = N-1; k>=0; k--)
         for (disp = 0; disp <= disponible; disp++) {
      	   mejor.beneficio = -INFINITO;
      	   for (qinv = minimo(M,disp); qinv >= 0; qinv--)
      	      if (tabla[disp-qinv][k+1].beneficio + rend[qinv][k] > mejor.beneficio) {
      	         mejor.beneficio = tabla[disp-qinv][k+1].beneficio + rend[qinv][k];
      	      	mejor.resto = disp-qinv;
      	      }
      	   tabla[disp][k] = mejor;
      	}
     
/*
      printf("\n\n");
      for (i=0; i<=disponible; i++) {
         for (j= 0; j<N; j++)
            printf("->%d-%2d ( %d)  ",i,tabla[i][j].beneficio,tabla[i][j].resto );
         printf("\n");
      }
      printf("\n\n");
*/   
      
      disp = disponible;      
      solOptima->beneficio = tabla[disp][0].beneficio;
      solOptima->inversion[0] = disp-tabla[disp][0].resto;
      for (k=1; k<N; k++) {
      	disp -= solOptima->inversion[k-1];
         solOptima->inversion[k] = disp-tabla[disp][k].resto;
      }
         
   }        


   void Entrada (int *Cap, int *M, int *N, int rend[MAXCAPITAL][MAXBANCOS]) {
   	
      int i, j;

      printf("Numero de bancos (< %d) ",MAXBANCOS); scanf("%d",N);
      printf("Cantidad a invertir (< %d) ",MAXCAPITAL); scanf("%d",Cap);
      printf("Maxima cantidad a invertir en un banco (< %d) ",MAXCAPITAL); scanf("%d",M);
      for (i=0; i<*N; i++) {
         printf("Rendimientos en el banco %d (separados por un espacio)\n",i);
         for (j=0; j<=*M; j++) 
            scanf(" %d", &rend[j][i]);  
      }
   
      printf("\n\n");
      for (i= 0; i<*N; i++) {
         for (j=0; j<=*M; j++) 
            printf(" %4d",rend[j][i]);
         printf("\n");
      }
  
   }


   void Salida (TSolucion sol, int Cap, int N, int rend[MAXCAPITAL][MAXBANCOS]) {
      int i, inversionTotal = 0;
      
      printf("\nCapital disponible para invertir: %d\n", Cap);
      for (i= 0; i<N; i++) {
      	printf("\nCapital invertido en el banco %4d -> %4d  (rend: %3d )",
      	       i, sol.inversion[i], rend[sol.inversion[i]][i]);
      	inversionTotal += sol.inversion[i];       
      }   
      printf("\n\nEl beneficio de la solucion es: %d\n",sol.beneficio);
      printf("En total se han invertido: %d\n", inversionTotal);

   }
	