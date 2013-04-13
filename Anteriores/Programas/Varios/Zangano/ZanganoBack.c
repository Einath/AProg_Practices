#include <stdio.h>

#define MAXVERTICES 20
#define INFINITO 10000
#define TRUE 1
#define FALSE 0

   typedef struct {
      int Coste, Longitud; 
      int Camino [MAXVERTICES]; // el camino estará en orden inverso
   } TipoSolucion;
   
    
   typedef struct {
    	int Visitado, Polen;
   } DatosVertice;
   
   
   typedef struct {
   	int Dist, Intermedio;
   } TipoDato;
   
        
   void ZanganoBack (int v, int Polen, DatosVertice Vertices[], 
                     TipoSolucion *Sol, TipoSolucion *SolOptima,
                     int N, TipoDato Dist[MAXVERTICES][MAXVERTICES]);


   void Salida (int Polen, int N, TipoSolucion sol, DatosVertice Vertices[],
                int C[MAXVERTICES][MAXVERTICES], TipoDato Dist[MAXVERTICES][MAXVERTICES]);
                   
   void ReconstruyeCamino (int Origen, int Destino, TipoDato Dist[MAXVERTICES][MAXVERTICES]);
   
   void Entrada (int *Polen, int *N, int *Origen, DatosVertice Vertices[], 
                 int C[MAXVERTICES][MAXVERTICES]);
   
   int PolenTotal (DatosVertice Vertice[], int N);
   
   int Minimo (int a, int b) {
      if (a < b) return a; else return b;
   }

   int Maximo (int a, int b) {
      if (a > b) return a; else return b;
   }

   
   void Inicializa (DatosVertice Vertices[MAXVERTICES], int N, int Origen, int *Polen,
                    TipoSolucion *Sol, TipoSolucion *SolOptima) {
   	int i;
   	
   	for (i = 0; i < N; i++) Vertices[i].Visitado = FALSE;
   	Vertices[Origen].Visitado = TRUE;
   	
   	*Polen -= Vertices[Origen].Polen;
   	*Polen = Maximo (0,*Polen); // Por si acaso ya con el primer vértice tenemos suficiente
   	Sol->Longitud = 0; Sol->Camino[0] = Origen; 
   	Sol->Coste = 0;
   	SolOptima->Coste = INFINITO;
   }
   
   
   
   
   void Floyd (int C[MAXVERTICES][MAXVERTICES], TipoDato D[MAXVERTICES][MAXVERTICES], int N) {
   	int i, j, k;
   	
   	for (i = 0; i < N; i++)
   	   for (j = 0; j < N; j++) {
   	      D[i][j].Dist = C[i][j];
   	      D[i][j].Intermedio = j;
   	   }
   	
   	for (k = 0; k < N; k++)
   		for (i = 0; i < N; i++)
      	   for (j = 0; j < N; j++) 
      	      if (D[i][j].Dist > D[i][k].Dist + D[k][j].Dist) {
   	            D[i][j].Dist = D[i][k].Dist + D[k][j].Dist;
   	            D[i][j].Intermedio = k;
   	         }
   	      
   }
   	
   	
   
   void SalidaMatrices (int C[MAXVERTICES][MAXVERTICES], TipoDato Dist[MAXVERTICES][MAXVERTICES], int N) {
      int i, j;      

      printf("\n\nLa matriz ORIGINAL es: \n");
   	for (i = 0; i < N; i++) {
   	   for (j = 0; j < N; j++)
   	      if (C[i][j] == INFINITO) printf("    -");
   	      else printf("%5d", C[i][j]);
   	   printf("\n");
   	}
      
      printf("\n\nLa matriz de DISTANCIAS MINIMAS es: \n");
   	for (i = 0; i < N; i++) {
   	   for (j = 0; j < N; j++)
   	      if (Dist[i][j].Dist == INFINITO) printf("    -");
   	      else printf("%5d", Dist[i][j].Dist);
   	   printf("\n");
   	}
   	
      //printf("\n\n");
   }
      
      
   
   
int main () {

   
   int N;        // numero de Vertices
   int Polen;    // Polen a recolectar
   int Origen;   // Vertice origen
   TipoSolucion Sol, SolOptima;
   int C[MAXVERTICES][MAXVERTICES];
   DatosVertice Vertices[MAXVERTICES];
   
   TipoDato Dist[MAXVERTICES][MAXVERTICES];


   // entrada de datos

  
   Entrada (&Polen, &N, &Origen, Vertices, C);

   if (PolenTotal(Vertices,N) < Polen) {
   	printf("ERROR: Insuficiente cantidad de polen en el campo %d < %d\n",PolenTotal(Vertices,N),Polen);
   	return 0;
   }
   
   Floyd(C,Dist,N);
   
   Inicializa(Vertices,N,Origen,&Polen,&Sol,&SolOptima);
   
   ZanganoBack (Origen,Polen,Vertices,&Sol,&SolOptima,N,Dist);
   
   Salida (Polen, N, SolOptima, Vertices, C, Dist);
      
   return 0;
      
}
   
   

   void ZanganoBack (int v, int Polen, DatosVertice Vertices[], 
                     TipoSolucion *Sol, TipoSolucion *SolOptima,
                     int N, TipoDato Dist[MAXVERTICES][MAXVERTICES]) {

      int i;

      if (Sol->Coste < SolOptima->Coste)  // vamos bien, si no NO seguimos
         if (Polen == 0) 
      	   *SolOptima = *Sol;
      	else 
      	  	for (i = 0; i < N; i++)
      	      if (!Vertices[i].Visitado) {
      	         Vertices[i].Visitado = TRUE;
      	         Sol->Longitud++; Sol->Camino[Sol->Longitud] = i;
      	   	   Sol->Coste += Dist[v][i].Dist;
      	   	   
      	   	   ZanganoBack (i,Maximo(0,Polen-Vertices[i].Polen),Vertices,Sol,SolOptima,N,Dist);
      	   	   
       	   	   // Deshacemos para la siguiente iteración
      	   	   Vertices[i].Visitado = FALSE;
      	   	   Sol->Longitud--;
      	   	   Sol->Coste -= Dist[v][i].Dist;
      	      }
   } // Fin ZanganoBack
      	   	
      		

   int PolenTotal (DatosVertice Vertice[], int N) {
   	int i, Total = 0;
   	
   	for (i = 0; i < N; i++) Total += Vertice[i].Polen;
   	return Total;
   }



   void Entrada (int *Polen, int *N, int *Origen, DatosVertice Vertices[], 
                 int C[MAXVERTICES][MAXVERTICES]) {
   	
      int i, j;

      printf("Introduzca el POLEN a recolectar "); scanf("%d",Polen);
      printf("Introduzca el numero de vertices "); scanf("%d",N);
      printf("Introduzca el vertice Origen "); scanf("%d",Origen);
      printf("\nCantidad de Polen en cada vertice (separados por un espacio)\n");
      for (i=0; i<*N; i++)
         scanf(" %d", &Vertices[i].Polen);  
      
      
      for (i = 0; i < *N; i++) 
         for (j= 0; j < *N; j++)
            if (i == j) C[i][j] = 0;
            else C[i][j] = INFINITO;
/*
      C[0][1] = 1; C[0][7] = 1; C[0][2] = 1;
      C[1][0] = 1; C[1][4] = 1;
      C[2][0] = 1;
      C[3][5] = 1; C[3][6] = 1; C[3][7] = 1; 
      C[4][1] = 1; C[4][5] = 1;
      C[5][3] = 1; C[5][4] = 1; C[5][3] = 3;
      C[6][3] = 1; C[5][3] = 4; C[5][4] = 3; C[5][5] = 0;     
      C[7][0] = 1; C[7][2] = 1; C[7][3] = 1;
      
 */
            
      C[0][1] = 1; C[0][2] = 1; C[0][3] = 1;
      C[1][0] = 1; C[1][5] = 1;
      C[2][0] = 1; C[2][3] = 1; C[2][4] = 1;
      C[3][0] = 1; C[3][2] = 1;
      C[4][2] = 1;
      C[5][1] = 1;
  
   } // Fin Entrada



   void Salida (int Polen, int N, TipoSolucion sol, DatosVertice Vertices[],
                int C[MAXVERTICES][MAXVERTICES], TipoDato Dist[MAXVERTICES][MAXVERTICES]) {
      int i, j;      
      
      printf("\nEl POLEN a recolectar es: %d\n\n", Polen);
      
      printf("\nCantidad de Polen en cada vertice: \n");
      for (i=0; i < N; i++)
         printf(" %d -> %d;  ", i, Vertices[i].Polen);  

      printf("\n\nLa matriz ORIGINAL es: \n");
   	for (i = 0; i < N; i++) {
   	   for (j = 0; j < N; j++)
   	      if (C[i][j] == INFINITO) printf("    -");
   	      else printf("%5d", C[i][j]);
   	   printf("\n");
   	}
      
      printf("\n\nLa matriz de DISTANCIAS MINIMAS es: \n");
   	for (i = 0; i < N; i++) {
   	   for (j = 0; j < N; j++)
   	      if (Dist[i][j].Dist == INFINITO) printf("    -");
   	      else printf("%5d", Dist[i][j].Dist);
   	   printf("\n");
   	}
   	
      //printf("\n\n");
      
      if (sol.Coste == INFINITO) 
         printf("\nEl problema no tiene solución. No hay suficiente polen en las flores\n");
      else {
         printf("\nLa solucion tiene un coste de: %d\n",sol.Coste);
         printf("\ny consiste en visitar los vertices:\n\n");
      
         printf(" %d ( %d ) ", sol.Camino[0], Vertices[sol.Camino[0]].Polen);
         for (i = 1; i <= sol.Longitud; i++) {
      	   ReconstruyeCamino (sol.Camino[i-1],sol.Camino[i],Dist);
      	   printf(" -> %d ( %d ) ", sol.Camino[i], Vertices[sol.Camino[i]].Polen);
         }
         printf("\n");
      }

   } // Fin Salida


   void ReconstruyeCamino (int Origen, int Destino, TipoDato Dist[MAXVERTICES][MAXVERTICES]) {
   	
   	if (Dist[Origen][Destino].Intermedio != Destino) {
   		ReconstruyeCamino (Origen,Dist[Origen][Destino].Intermedio,Dist);
   		printf(" -> %d ", Dist[Origen][Destino].Intermedio);
   		ReconstruyeCamino (Dist[Origen][Destino].Intermedio,Destino,Dist);
      }
   }
   