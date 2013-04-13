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


        
   void CajasVoraz (TipoSolucion *Sol, int Datos[MAXCAJAS][MAXCLASES], int N, int M);

   void Salida (TipoSolucion sol, int Datos[MAXCAJAS][MAXCLASES], int N, int M);
   
   void Entrada (int *N, int *M, int Datos[MAXCAJAS][MAXCLASES]);
   
   

   void Inicializa (TipoSolucion *Sol, int Cubiertas[], int Candidatos[], int N, int M) {
   	int i;
   	
   	Sol->NumCajas = -1;
   	for (i = 0; i < M; i++) Cubiertas[i] = FALSE;
   	for (i = 0; i < N; i++) Candidatos[i] = TRUE;
   	
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
   TipoSolucion Sol;
   
   int Datos[MAXCAJAS][MAXCLASES];


   Entrada (&N,&M,Datos);
   
   CajasVoraz (&Sol,Datos,N,M);
   
   Salida (Sol,Datos,N,M);

   return 0;
      
}

   void CajasVoraz (TipoSolucion *Sol, int Datos[MAXCAJAS][MAXCLASES], int N, int M) {
   	
      int i, j;
      int Cubiertas[MAXCLASES]; 
      int CubAux[MAXCLASES]; 
      int Candidatos [MAXCAJAS];
      int Beneficio, MejorBeneficio, MejorCaja;
      
      // Inicializacion
      Inicializa(Sol,Cubiertas,Candidatos,N,M);
      
      do {
         MejorBeneficio = -INFINITO;
         
         for (i=0; i < N; i++) 
            if (Candidatos[i]) {
            	Copiar(Cubiertas,CubAux,M);
      	      // Añadimos a CubAux las clases de la caja i
           	   Actualizar(CubAux,Datos,i,M);
      	      // Si amplía el número de clases cubiertas estudiamos elegirla
      	      Beneficio = NumClases(CubAux,M);
      	      if (NumClases(Cubiertas,M) == Beneficio) 
      	         // si no mejorara las que ya tenemos es que ya estaría cubierta"
      	         Candidatos[i] = FALSE; 
      	      else if (MejorBeneficio < Beneficio) {
      		         MejorBeneficio = Beneficio;
      		         MejorCaja = i;
      		        }
      	   }
      	   
      	if (MejorBeneficio != -INFINITO) {
      		Sol->NumCajas++;
      		Sol->Caja[Sol->NumCajas] = MejorCaja;
      		Actualizar (Cubiertas,Datos,MejorCaja,M);
      		Candidatos[MejorCaja] = FALSE;
      	}
      	
      } while ((NumClases(Cubiertas,M) != M) || (MejorBeneficio != -INFINITO));
      
      if  (NumClases(Cubiertas,M) != M) Sol->NumCajas = INFINITO;
      
   } // Fin CajasVoraz


      		
      		
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
         printf("\nEl numero de cajas elegidas es: %d", sol.NumCajas+1);
         printf("\ny consiste en seleccionar las cajas:\n");

         for (i = 0; i <= sol.NumCajas; i++) {
     	      printf("Caja %d -> ", sol.Caja[i]);
     	      for (j = 0; j < M; j++) 
     	         if (Datos[sol.Caja[i]][j]) printf(" %d, ", j);
     	      printf("\n");
     	   }
      }

   } // Fin Salida

