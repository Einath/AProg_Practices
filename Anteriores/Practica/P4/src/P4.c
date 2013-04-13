#include <stdio.h>
#define MAXDIM 20
#define M 4
#define P 5
#define TRUE 1
#define FALSE 0
#define INFINITO 9999


typedef struct{
  int D; 
  int C; 
  int actual;
  int camino[MAXDIM]; 
  int cantidad[M]; 
}TSol; 

void BarcosDin(TSol *SolOpt, int Dist[P][P], int Merc[P][M], int T){
  TSol solparc, solmejor; 
  int i, j, k, l, precio; 
  solparc= *SolOpt;
  /* 1) Vendemos el producto */
  for(i=0; i<M; i++){
    if(solparc.cantidad[i]>0){
      solparc.D += (SolOpt->cantidad[i])*(Merc[SolOpt->actual][i]); 
      solparc.C += solparc.cantidad[i]; 
      solparc.cantidad[i]=0; 
    }
  }
 /*Caso base */
  if(T == (Dist[SolOpt->actual][SolOpt->camino[0]])){ 
    for(i=0; i< MAXDIM; i++)
      if(solparc.camino[i]<0){
	solparc.camino[i]=solparc.camino[0];
	solparc.actual=solparc.camino[0];
	i=MAXDIM;
      }
    *SolOpt = solparc;
  }/*Fin caso base */

  else if (T > Dist[SolOpt->actual][SolOpt->camino[0]]){
    solmejor.D=-INFINITO; 
    for(i=0; i<M; i++){  /* 2) Para cada mercancía... */
      for(j=0; j<P; j++){/* ...en cada puerto... */
	if(j!=SolOpt->actual){
	  solparc = *SolOpt; 
	  precio=Merc[solparc.actual][i];
	  for(k=0; (k<solparc.C); k++){ /* ...compramos */
	    if(solparc.D > precio){   /* control de que no nos pasemos del presupuesto */
	      solparc.D -= precio;
	      solparc.C--; 
	    }
	    else
	      k=solparc.C;
	  }
	  for(l=0; l<MAXDIM; l++){ /*actualizar el destino */
	      if(solparc.camino[l]<0){
		solparc.camino[l]=i+1; 
		solparc.actual=i+1;
		l=MAXDIM;
	      }
	  } /*for l*/
	  T-= Dist[solparc.actual][j];
	  BarcosDin(&solparc, Dist, Merc, T);
	  T+= Dist[solparc.actual][j];

	  if(solmejor.D<solparc.D)
	    solmejor=solparc;
	}/*if*/
      }/*for j*/
    }/*for i*/
    if(SolOpt->D < solmejor.D)
      *SolOpt=solmejor;
  }/*else if*/

  else{
    /* T es negativo, se debe descartar esta solución */
  }
}

void main(){
  FILE *fichero;
  int C, T, D,  valor, i, j; 
  char cad[2]; 
  int origen, destino; 
  int camino[MAXDIM];
  TSol Solucion, SolOpt; 

  for(i=0; i<MAXDIM-1; i++)
    camino[i]=-1; 
 
  if((fichero=fopen("DatosP4Barco.txt", "r"))==NULL)
    printf("Error al abrir fichero\n");
  else
    printf("\nFichero de datos abierto\n");

  printf("Teclee el puerto de origen\n");
  scanf("%d", &origen); 
  destino=origen;
  printf("Teclee el capital inicial\n");
  scanf("%d",&D);
  printf("Teclee el número de días\n");
  scanf("%d",&T);
  printf("D: %d\tT: %d\n\n", D, T);

  while(!feof(fichero)){
    fscanf(fichero, "%c\t\t %d\n",&cad[0], &valor);

    if(cad[0]=='C') 
      C = valor; 
/*  if(cad[0]=='M') Aquí da fallo al leer del archivo 
      M = valor; */ 
  }
  printf("C: %d\tP: %d\tM: %d\n\n", C, P, M);
  int cant[M]; 
  for(i=0; i<M; i++) /* cantidad inicial de cada mercancía es 0 */
    cant[i]=0;  

  int Dist[P][P]; 
  int Merc[P][M]; 
  int auxd[P-1];

  Dist[0][0]=0;   Dist[0][1]=3;   Dist[0][2]=3;   Dist[0][3]=2;   Dist[0][4]=6;  
  Dist[1][0]=3;   Dist[1][1]=0;   Dist[1][2]=2;   Dist[1][3]=4;   Dist[1][4]=1; 
  Dist[2][0]=3;   Dist[2][1]=2;   Dist[2][2]=0;   Dist[2][3]=5;   Dist[2][4]=3; 
  Dist[3][0]=2;   Dist[3][1]=4;   Dist[3][2]=3;   Dist[3][3]=0;   Dist[3][4]=4; 
  Dist[4][0]=6;   Dist[4][1]=1;   Dist[4][2]=3;   Dist[4][3]=4;   Dist[4][4]=0;  

  for(i=0; i<P; i++)
    for(j=0; j<P; j++){
      if(j==0)
	printf("P%d-Pi\t", j+1);

      printf("%d\t", Dist[i][j]); 

      if(j==4)
	printf("\n");
    }

  Merc[0][0]=10; Merc[0][1]=8; Merc[0][2]=5; Merc[0][3]=3; 
  Merc[1][0]=6; Merc[1][1]=7; Merc[1][2]=11; Merc[1][3]=15; 
  Merc[2][0]=8; Merc[2][1]=4; Merc[2][2]=3; Merc[2][3]=6; 
  Merc[3][0]=2; Merc[3][1]=12; Merc[3][2]=10; Merc[3][3]=7; 
  Merc[4][0]=4; Merc[4][1]=5; Merc[4][2]=6; Merc[4][3]=8; 

  for(i=0; i<P; i++)
    printf("\nM-P%d\t%d\t%d\t%d\t%d", i+1, Merc[i][0], Merc[i][1], Merc[i][2], Merc[i][3]);  

  printf("\n"); 
  fclose(fichero);

  /* primera llamada */

  Solucion.C = C; 
  Solucion.D = D; 
  Solucion.camino[0]=origen; 
  Solucion.actual=origen;
  for(i=1; i<MAXDIM; i++)
    Solucion.camino[i]=-1;
  for(i=0; i<M; i++)
    Solucion.cantidad[i]=0; 
  SolOpt=Solucion;

  BarcosDin(&SolOpt, Dist, Merc, T); 

  printf("==Solución==\nD: %d\nC: %d\nRuta: ",SolOpt.D, SolOpt.C); 
  for(i=0; i< MAXDIM; i++)
    if(SolOpt.camino[i] >= 0)
      printf("%d\t", SolOpt.camino[i]);
  printf("\n\n"); 
} /* FIN */



/* Estructuras de datos: 

<TSol>
  D : Presupuesto
  C : Capacidad
  actual: Puerto actual
  camino[]: arreglo de camino seguido
  cantidad[]: arreglo de cantidad de cada mercancía Mi   i=0...M


<Distancia entre el puerto i y puerto j>
  Dist[P-1][P-1]

<Precio de las mercancías i en el puerto j>
  Merc[P][M]

*/












