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


        
   void CajasBackElem0 (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                        int Datos[MAXCAJAS][MAXCLASES], int N, int M);

   void CajasBackElem (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                       int Datos[MAXCAJAS][MAXCLASES], int N, int M);

   void Salida (TipoSolucion sol, int Datos[MAXCAJAS][MAXCLASES], int N, int M);
   
   void Entrada (int *N, int *M, int Datos[MAXCAJAS][MAXCLASES]);
   
   

   void Inicializa (TipoSolucion *Sol, TipoSolucion *SolOptima, int Cubiertas[], int N, int M) {
   	int i, j;
   	
   	Sol->NumCajas = 0;
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

   CajasBackElem (0,Cubiertas,&Sol,&SolOptima,Datos,N,M);
// CajasBackElem0 (0,Cubiertas,&Sol,&SolOptima,Datos,N,M);
   
   Salida (SolOptima,Datos,N,M);
      
   return 0;
      
}

   void CajasBackElem0 (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                        int Datos[MAXCAJAS][MAXCLASES], int N, int M) {

      int CubAux[MAXCLASES];
      
      if (k == N) {
         if ((NumClases(Cubiertas,M) == M) && (Sol->NumCajas < SolOptima->NumCajas)) 
            *SolOptima = *Sol;
         }
      else {
      	Copiar(Cubiertas,CubAux,M);
      	// Añadimos a CubAux las clases de la caja k
      	Actualizar(CubAux,Datos,k,M);
      	// Si amplía el número de clases cubiertas estudiamos elegirla
      	if (NumClases(Cubiertas,M) < NumClases(CubAux,M)) {
      		Sol->Caja[k] = TRUE;
      		Sol->NumCajas++;
      	   CajasBackElem0(k+1,CubAux,Sol,SolOptima,Datos,N,M);
      		Sol->NumCajas--;
      	}
      	
      	// siempre tenemos la opción de no elegirla
      	Copiar(Cubiertas,CubAux,M);
      	Sol->Caja[k] = FALSE;
      	CajasBackElem0(k+1,CubAux,Sol,SolOptima,Datos,N,M);
      }
   } // Fin CajasBackElem0


   
   
   void CajasBackElem (int k, int Cubiertas[MAXCLASES], TipoSolucion *Sol, TipoSolucion *SolOptima,
                       int Datos[MAXCAJAS][MAXCLASES], int N, int M) {

      int CubAux[MAXCLASES];
      
      // Ahora podamos antes, si no es mejor que la que tenemos construida no la estudiamos
      if (Sol->NumCajas < SolOptima->NumCajas) {
         if (k == N) {
            if (NumClases(Cubiertas,M) == M) *SolOptima = *Sol;
         }
         else {
      	   Copiar(Cubiertas,CubAux,M);
      	   // Añadimos a cub las clases de la caja k
      	   Actualizar(CubAux,Datos,k,M);
      	   // Si amplía el número de clases cubiertas estudiamos elegirla
      	   if (NumClases(Cubiertas,M) < NumClases(CubAux,M)) {
      	   	Sol->Caja[k] = TRUE;
      		   Sol->NumCajas++;
      	      CajasBackElem(k+1,CubAux,Sol,SolOptima,Datos,N,M);
      		   Sol->NumCajas--;
      	   }
      	
         	// siempre tenemos la opción de no elegirla
         	Copiar(Cubiertas,CubAux,M);
         	Sol->Caja[k] = FALSE;
      	   CajasBackElem(k+1,CubAux,Sol,SolOptima,Datos,N,M);
         }
      }
   } // Fin CajasBackElem

      		
      		
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

