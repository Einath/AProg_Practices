#include <stdio.h>

#define MAXCAJAS 20
#define MAXCLASES 20
#define INFINITO 10000
#define TRUE 1
#define FALSE 0


   typedef struct {
   	int NumCajas;
   	int Caja[MAXCAJAS]; // Contiene los numeros de las cajas
   } TipoSolucion;


        
   void CajasBackSol0 (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                       int Datos[MAXCAJAS][MAXCLASES], int N, int M);

   void CajasBackSol (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                      int Datos[MAXCAJAS][MAXCLASES], int N, int M);

   void Salida (TipoSolucion sol, int Datos[MAXCAJAS][MAXCLASES], int N, int M);
   
   void Entrada (int *N, int *M, int Datos[MAXCAJAS][MAXCLASES]);
   
   

   void Inicializa (TipoSolucion *Sol, TipoSolucion *SolOptima, int Cubiertas[], int N, int M) {
   	int i;
   	
   	Sol->NumCajas = 0;
   	Sol->Caja[0] = -1;
   	SolOptima->NumCajas = INFINITO;
   	
   	for (i = 0; i < M; i++) Cubiertas[i] = FALSE;
   }
   
   
   int NumClases (int Cubiertas[], int M) {
   	int i, cont = 0;
   	for (i = 0; i < M; i++) if (Cubiertas[i]) cont++;
   	return cont;
   }
   

   void Actualizar (int Cubiertas[], int Datos[MAXCAJAS][MAXCLASES], int k, int M) {
   	int i;
   	for (i = 0; i < M; i++) Cubiertas[i] = Cubiertas[i] || Datos[k][i];
   }
   
   
   void Copiar (int a[], int b[], int M) {
   	int i;
   	for (i = 0; i < M; i++) b[i] = a[i];
   }
   
   
   
int main () {

   
   int N;        // Numero de cajas
   int M;        // Numero de clases de bombones
   TipoSolucion Sol, SolOptima;
   
   int Cubiertas[MAXCLASES];
   int Datos[MAXCAJAS][MAXCLASES];


   // entrada de datos
  
   Entrada (&N,&M,Datos);
   
   
   Inicializa(&Sol,&SolOptima,Cubiertas,N,M);

   CajasBackSol (0,Cubiertas,&Sol,&SolOptima,Datos,N,M);
// CajasBackSol0 (0,Cubiertas,&Sol,&SolOptima,Datos,N,M);
   
   Salida (SolOptima,Datos,N,M);

   return 0;
      
}

   void CajasBackSol0 (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                       int Datos[MAXCAJAS][MAXCLASES], int N, int M) {

      int CubAux[MAXCLASES]; int i;
      
      if (NumClases(Cubiertas,M) == M) {
         if (Sol->NumCajas < SolOptima->NumCajas) *SolOptima = *Sol;
      }
      else 
         for (i = Sol->Caja[Sol->NumCajas]+1; i < N; i++) {
      	   Copiar(Cubiertas,CubAux,M);
      	   // Añadimos a CubAux las clases de la caja i
           	Actualizar(CubAux,Datos,i,M);
      	   // Si amplía el número de clases cubiertas estudiamos elegirla
      	   if (NumClases(Cubiertas,M) < NumClases(CubAux,M)) {
      		   Sol->NumCajas++;
      		   Sol->Caja[Sol->NumCajas] = i;
      	      CajasBackSol0(k+1,CubAux,Sol,SolOptima,Datos,N,M);
      		   Sol->NumCajas--;
      	   }
         }
   } // Fin CajasBackSol0



   void CajasBackSol (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                      int Datos[MAXCAJAS][MAXCLASES], int N, int M) {

      int CubAux[MAXCLASES]; int i;
      
      // Ahora podamos antes, si no es mejor que la que tenemos construida no la estudiamos
      if (Sol->NumCajas < SolOptima->NumCajas) 
         if (NumClases(Cubiertas,M) == M) *SolOptima = *Sol;
         else 
            for (i = Sol->Caja[Sol->NumCajas]+1; i < N; i++) {
         	   Copiar(Cubiertas,CubAux,M);
      	      // Añadimos a CubAux las clases de la caja i
           	   Actualizar(CubAux,Datos,i,M);
      	      // Si amplía el número de clases cubiertas estudiamos elegirla
      	      if (NumClases(Cubiertas,M) < NumClases(CubAux,M)) {
      		      Sol->NumCajas++;
         		   Sol->Caja[Sol->NumCajas] = i;
         	      CajasBackSol(k+1,CubAux,Sol,SolOptima,Datos,N,M);
         		   Sol->NumCajas--;
      	      }
            }
   } // Fin CajasBackSol


      		
      		
   void Entrada (int *N, int *M, int Datos[MAXCAJAS][MAXCLASES]) {
      int i, j, x;

      printf("NUMERO DE CAJAS (< %d) ", MAXCAJAS-1); scanf("%d",N);
      printf("NUMERO DE CLASES DE BOMBONES distintas (< %d) ", MAXCLASES); scanf("%d",M);
      
   	for (i = 0; i < *N; i++) 
   	   for (j = 0; j < *M; j++)
   	      Datos[i][j] = FALSE;

      printf("\n");
      for (i = 0; i < *N; i++) {
      	printf("Clases de bombones de la caja %d (-1 para terminar)\n", i);
      	scanf("%d",&x);
      	while (x >= 0) {
      		if (x < *M) Datos[i][x] = TRUE;
      		scanf("%d",&x);
         }
      }
      
   } // Fin Entrada



   void Salida (TipoSolucion sol, int Datos[MAXCAJAS][MAXCLASES], int N, int M) {
      int i, j;      
      
      printf("\n\nLas clases de cada caja son: \n");
   	for (i = 0; i < N; i++) {
   	   printf("Caja %2d -> ", i);
   	   for (j = 0; j < M; j++)
   	      if (Datos[i][j]) printf(" %d,", j);
   	   printf("\n");
   	}

      if (sol.NumCajas == INFINITO) 
         printf("\nImposible conseguir todas las clases de bombones\n");
      else {
         printf("\nEl numero de cajas elegidas es: %d", sol.NumCajas);
         printf("\ny consiste en seleccionar las cajas:\n");

         for (i = 1; i <= sol.NumCajas; i++) {
     	      printf("Caja %d -> ", sol.Caja[i]);
     	      for (j = 0; j < M; j++) 
     	         if (Datos[sol.Caja[i]][j]) printf(" %d, ", j);
     	      printf("\n");
     	   }
      }

   } // Fin Salida

