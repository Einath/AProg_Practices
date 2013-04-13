#include <stdio.h>

#define MAXDIM 10
#define TRUE 1
#define FALSE 0
#define INFINITO = 10000; //MAXDIM*MAXDIM +1


   typedef struct {
      int Fila, Columna;
   } TCasilla;
   
   typedef struct {
   	int Visitada;
   	char Letra;
   } TCasTablero;
      


   typedef struct {      
      int Longitud;
      TCasilla Camino [MAXDIM*MAXDIM];
   } TSolucion;


	void VocalesBack (TCasilla Cas, int M, int N, TCasTablero Tablero[MAXDIM][MAXDIM], 
	                  TSolucion *Sol, TSolucion *SolOptima) {
	   // Cas tiene una vocal   
	   int i, j; TCasilla NCas;
	   
	   if (SolOptima->Longitud < Sol->Longitud) *SolOptima = *Sol;
	   
	   for (i=-1; i<2; i++) 
	      for (j=-1; j<2; j++) {
	      	NCas.Fila = Cas.Fila +i;
	      	NCas.Columna = Cas.Columna + j;
	      	if (Dentro (NCas,M,N))
	      	   if (!Tablero[NCas.Fila][NCas.Columna].Visitada 
	      	       &&
	      	       EsVocal(Tablero[NCas.Fila][NCas.Columna].Letra)) {
	      	      Tablero[NCas.Fila][NCas.Columna].Visitada = TRUE;
	      	      Sol->Longitud++;
	      	      Sol->Camino[Sol->Longitud] = NCas;
	      	      VocalesBack(NCas,M,N,Tablero,Sol,SolOptima);
	      	      
	      	      //Deshacemos
	      	      Tablero[NCas.Fila][NCas.Columna].Visitada = FALSE;
	      	      Sol->Longitud--;
	      	   }
			}
	} // VocalesBack
	
	
	
	int Dentro (TCasilla Cas, int M, int N) {
		return ((0 <= Cas.Fila) && (Cas.Fila < M)
		        &&
		        (0 <= Cas.Columna) && (Cas.Columna < N))
	}	        
	
	
	
	// Inicializaciones
	
	for (i=0; i<M; i++) 
	   for (j= 0; j<N; j++)
	   	Tablero[i][j].Visitada = FALSE;
	Sol.Longitud=-1;
	SolOptima.Longitud = -INFINITO;
	   	
	   	
	   	
	// Llamada Inicial
	if (EsVocal(Tablero[0][0].Letra)) {
		Cas.Fila=0; Cas.Columna=0;
		Tablero[0][0].Visitada = TRUE;
		Sol.Longitud++;
		Sol.Camino[Sol.Longitud] = Cas;
		VocalesBack(Cas,M,N,Tablero,&Sol,&SolOptima)
	}
	
	      
	   
   
   