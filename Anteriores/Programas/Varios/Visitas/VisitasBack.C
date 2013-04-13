#include <stdio.h>

#define MAXDIM 20
#define INFINITO 10000
#define TRUE 1
#define FALSE 0

// Consideramos el aeropuerto como una casa más, aunque el coste de la visita es 0
// Además, sin pérdida de generalidad, en lo que sigue suponemos que el aeropuerto
// es la casa etiquetada con O (CERO)


   typedef struct {
      int Longitud;             // Numero de casas visitadas
      int Camino [MAXDIM]; // el camino estará en orden inverso
   } TipoSolucion;
   
    
   typedef struct {
   	int Dist, Intermedio;
   } TipoDato;
   
        
   void VisitasBack (int v, int Tiempo, int Visitados[], TipoSolucion *Sol, TipoSolucion *SolOptima,
                     int N, int Dist[MAXDIM][MAXDIM]);

   void Salida (int Tiempo, int N, TipoSolucion sol, int DuracionVisita[],
                int C[MAXDIM][MAXDIM], TipoDato Dist[MAXDIM][MAXDIM]);
                   
   void ReconstruyeCamino (int Origen, int Destino, TipoDato Dist[MAXDIM][MAXDIM]);
   
   void Entrada (int *Tiempo, int *N, int TiempoVisita[], int C[MAXDIM][MAXDIM]);
   
   
   int Minimo (int a, int b) {
      if (a < b) return a; else return b;
   }


   int Maximo (int a, int b) {
      if (a > b) return a; else return b;
   }
   

   void Inicializa (TipoSolucion *Sol, TipoSolucion *SolOptima, int Visitados[], int N) {
   	int i;
      Sol->Longitud = 0; Sol->Camino[0] = 0;
      SolOptima->Longitud = -1;
   	for (i = 0; i < N; i++) Visitados[i] = FALSE;
   }
   
   
   
   
   void Floyd (int C[MAXDIM][MAXDIM], TipoDato D[MAXDIM][MAXDIM], int N) {
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
   	
  
   void IncluirTiempoVisitas (int TiempoVisita[], TipoDato D[MAXDIM][MAXDIM], 
                              int DistMod[MAXDIM][MAXDIM], int N) {
  	// Incluimos en el coste de ir de una casa a otra el tiempo de la visita en la casa destino
  	// En realidad en DistMod[i][i] no debería incluirse la duracion de la visita pero da igual
  	// pues no visitamos una casa ya visitada, nótese también que DistMod[i][0] no cambia pues
  	// TiempoVisita[0] (el aeropuerto) es 0
  	   int i, j;
  	  
  	   for (i = 0; i < N; i++)
   	   for (j = 0; j < N; j++) 
   	      DistMod[i][j] = D[i][j].Dist + TiempoVisita[j];
   }
   	
   	
   
   void SalidaMatrices (int C[MAXDIM][MAXDIM], TipoDato Dist[MAXDIM][MAXDIM], int N) {
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
   	
   }
      
      
   
   
int main () {

   
   int N;        // numero de Casas además del aeropuerto 
   int Tiempo;   // Tiempo disponible para realizar las visitas
   TipoSolucion Sol, SolOptima;
   int TiempoVisita[MAXDIM]; // Tiempo de duracion de la visita
   int C[MAXDIM][MAXDIM];
   
   int Visitados[MAXDIM];
   TipoDato Dist [MAXDIM][MAXDIM];
   int DistMod [MAXDIM][MAXDIM];


   // entrada de datos
  
   Entrada (&Tiempo, &N, TiempoVisita, C);
   
   Floyd(C,Dist,N);
   
   Inicializa(&Sol,&SolOptima,Visitados,N);
   IncluirTiempoVisitas (TiempoVisita, Dist, DistMod, N);
   
   Visitados[0]= TRUE; // El aeropuerto está visitado, no forma parte de las visitas
   VisitasBack(0,Tiempo,Visitados,&Sol,&SolOptima,N,DistMod);
   // Incluimos como inicio el aeropuerto (0) para tratar la solucion con más facilidad
   
   Salida (Tiempo, N, SolOptima, TiempoVisita, C, Dist);
      
   return 0;
      
}
   

         	   	
   void VisitasBack (int v, int Tiempo, int Visitados[], TipoSolucion *Sol, TipoSolucion *SolOptima,
                     int N, int Dist[MAXDIM][MAXDIM]) {
   // Nunca hacemos una visita si sabemos que no tendremos tiempo para volver al aeropuerto
      int w;
      
     	if (SolOptima->Longitud < Sol->Longitud) *SolOptima = *Sol;
     	for (w = 0; w < N; w++)
     	   if (!Visitados[w] && (Dist[v][w]+Dist[w][0] <= Tiempo)) {
     	   	// Si w no ha sido visitada aún y nos da tiempo a ir a ella y volver al aeropuerto
     	   	Visitados[w] = TRUE;
     	   	Sol->Longitud++; Sol->Camino[Sol->Longitud] = w;
     	   	VisitasBack (w,Tiempo-Dist[v][w],Visitados,Sol,SolOptima,N,Dist);
     	   	   
     	   	// Deshacemos para la siguiente iteración
     	   	Sol->Longitud--;
     	   	Visitados[w] = FALSE;
     	   }
   } // Fin VisitasBack
      	   	
      		
      		
   void Entrada (int *Tiempo, int *N, int TiempoVisita[], int C[MAXDIM][MAXDIM]) {
   	
      int i, j;

      printf("Introduzca el TIEMPO DISPONIBLE "); scanf("%d",Tiempo);
      printf("Introduzca el numero de Casas (Incluya el aeropuerto como casa 0) "); scanf("%d",N);
      printf("\nDuracion de la visita en cada casa (%d datos, el aeropuerto no cuenta)\n", *N-1);
      for (i=1; i<*N; i++) scanf(" %d", &TiempoVisita[i]); 
      TiempoVisita[0] = 0; 
      
      printf("\nIntroduzca la distancia en tiempo entre casas (-1 indica que no hay camino)\n");
      for (i = 0; i < *N; i++) {
      	printf("Distancia en tiempo desde %d al resto\n", i);
      	for (j = 0; j < *N; j++) scanf("%d",&C[i][j]);
      }
      
      for (i = 0; i < *N; i++)
      	for (j = 0; j < *N; j++) 
      	   if (C[i][j] == -1) C[i][j] = INFINITO;
      
   } // Fin Entrada


   void Salida (int Tiempo, int N, TipoSolucion sol, int DuracionVisita[],
                int C[MAXDIM][MAXDIM], TipoDato Dist[MAXDIM][MAXDIM]) {
      int i, j, TiempoVisitas;      
      
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
   	
      printf("\nEl TIEMPO DISPONIBLE es: %d\n", Tiempo);

      printf("\nLa duracion de los tiempos de visita es: \n");
      for (i = 1; i < N; i++)
         printf(" %d -> %d;  ", i, DuracionVisita[i]);  
      
      if (sol.Longitud == 0) 
         printf("\nNo hay suficiente tiempo para hacer visitas\n");
      else {
         printf("\n\nEl numero de casas que podemos visitar es: %d",sol.Longitud);
         printf("\ny consiste en visitar las casas:\n");

         for (i = 0; i < sol.Longitud; i++)
      	   printf(" -> %d ( %d + %d ) ", sol.Camino[i+1], 
      	          Dist[sol.Camino[i]][sol.Camino[i+1]].Dist, DuracionVisita[sol.Camino[i+1]]);
         printf(" -> %d ( %d )\n", 0, Dist[sol.Camino[sol.Longitud]][0].Dist);
         
         printf("\n\nMas detalladamente, el camino seguido es:\n\n");
         for (i = 0; i < sol.Longitud; i++) {
      	   ReconstruyeCamino (sol.Camino[i],sol.Camino[i+1],Dist);
      	   printf(" -> %d ( %d + %d ) ", sol.Camino[i+1], 
      	          Dist[sol.Camino[i]][sol.Camino[i+1]].Dist, DuracionVisita[sol.Camino[i+1]]);
         }
    	   ReconstruyeCamino (sol.Camino[sol.Longitud],0,Dist);
    	   printf(" -> %d ( %d )\n", 0, Dist[sol.Camino[sol.Longitud]][0].Dist);
    	   
    	   TiempoVisitas = 0;
    	   for (i = 0; i < sol.Longitud; i++)
      	   TiempoVisitas += (Dist[sol.Camino[i]][sol.Camino[i+1]].Dist + DuracionVisita[sol.Camino[i+1]]);
    	   TiempoVisitas += Dist[sol.Camino[sol.Longitud]][0].Dist;
         printf("\nEl tiempo restante es %d\n", Tiempo-TiempoVisitas);
      }

   } // Fin Salida


   void ReconstruyeCamino (int Origen, int Destino, TipoDato Dist[MAXDIM][MAXDIM]) {
   	
   	if (Dist[Origen][Destino].Intermedio != Destino) {
   		ReconstruyeCamino (Origen,Dist[Origen][Destino].Intermedio,Dist);
   		printf(" -> %d ", Dist[Origen][Destino].Intermedio);
   		ReconstruyeCamino (Dist[Origen][Destino].Intermedio,Destino,Dist);
      }
   }
   
   

