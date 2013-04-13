#include <stdio.h>

#define MAXCAJAS 20
#define MAXCLASES 20
#define INFINITO 10000
#define TRUE 1
#define FALSE 0


   typedef struct {
   	int NumCajas;
   	int Caja[MAXCAJAS];
   } TipoSolucion;


        
   void CajasBombonesDin (int k, int Cubiertas[MAXCLASES], TipoSolucion *SolOptima,
                          int Datos[MAXCAJAS][MAXCLASES], int N, int M);

   void Salida (TipoSolucion sol, int Datos[MAXCAJAS][MAXCLASES], int N, int M);
   
   void Entrada (int *N, int *M, int Datos[MAXCAJAS][MAXCLASES]);
   
   

   void Inicializa (int Cubiertas[], int M) {
   	int i;
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
   int M;        // Numero de clases
   TipoSolucion SolOptima;
   
   int Cubiertas[MAXCLASES];
   int Datos[MAXCAJAS][MAXCLASES];


   // entrada de datos
  
   Entrada (&N,&M,Datos);
   
   Inicializa(Cubiertas,M);

   CajasBombonesDin (0,Cubiertas,&SolOptima,Datos,N,M);
   
   Salida (SolOptima,Datos,N,M);
      
   return 0;
      
}
   
   
   void CajasBombonesDin (int k, int Cubiertas[MAXCLASES], TipoSolucion *SolOptima,
                          int Datos[MAXCAJAS][MAXCLASES], int N, int M) {

      TipoSolucion SolElegirla, SolNOElegirla;
      int cub[MAXCLASES];
      int cubNO[MAXCLASES];
      
      if (k == N) 
         if (NumClases(Cubiertas,M) == M) SolOptima->NumCajas = 0;
         else SolOptima->NumCajas = INFINITO;
      else {
      	Copiar(Cubiertas,cub,M);
      	Copiar(Cubiertas,cubNO,M);
      	// Añadimos a cub las clases de la caja k
      	Actualizar(cub,Datos,k,M);
      	// Si amplía el número de clases cubiertas estudiamos elegirla
      	if (NumClases(Cubiertas,M) < NumClases(cub,M)) {
      	   // La elegimos
      	   CajasBombonesDin(k+1,cub,&SolElegirla,Datos,N,M);
      	   SolElegirla.Caja[k] = TRUE;
      	   SolElegirla.NumCajas++;
      	}
      	else // la solucion sería peor que no elegirla pues no aporta nada
      	   SolElegirla.NumCajas = INFINITO;
      	
      	// siempre tenemos la opción de no elegirla
      	CajasBombonesDin(k+1,cubNO,&SolNOElegirla,Datos,N,M);
      	SolNOElegirla.Caja[k] = FALSE;

         // Nos quedamos con la mejor solucion
         if (SolElegirla.NumCajas < SolNOElegirla.NumCajas) *SolOptima = SolElegirla;
         else *SolOptima = SolNOElegirla;      	
      }
   } // Fin CajasDin




      		
      		
   void Entrada (int *N, int *M, int Datos[MAXCAJAS][MAXCLASES]) {
      int i, j, x;

      printf("NUMERO DE CAJAS (< %d) ", MAXCAJAS); scanf("%d",N);
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

         for (i = 0; i < N; i++)
            if (sol.Caja[i]) {
      	      printf("Caja %d -> ", i);
      	      for (j = 0; j < M; j++) 
      	         if (Datos[i][j]) printf(" %d, ", j);
      	      printf("\n");
      	   }
      }

   } // Fin Salida

