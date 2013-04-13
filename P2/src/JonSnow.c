#define N 5
#define M 15
#define JON -1

#include "orders.h"

void main(){

  int v1[N]; 
  int v2[M]; 
  int vmezcla[N+M+1]; 
  int i=0; 
  int a, b; 
  int jon=0; 
  float edad=0; 

  srand(getpid()); 

  printf("Generando vectores...\n"); 

  for(i=0; i<N; i++)
    v1[i]=rand()%10 + 15; 

  for(i=0; i<M; i++)
    v2[i]=rand()%10 + 15; 

  /* Ordenar los vectores con QS*/
  QS(v1,0,N-1); 
  printf("N soldados: "); 
  printvec(v1,N); 

  QS(v2,0,M-1); 
  printf("\nM soldados: "); 
  printvec(v2,M); 


  /* Búsqueda DYV */
  /* Comienzo del problema */

  /*índices de los vectores*/
  a=0; b=0;

  /*Vamos evaluando y colocando cada uno de los vectores (previamente ordenados)*/
  /*cuando encontremos la posición intermedia, nos ponemos ahí. */

  for(i=0; i<=N+M; i++){
    if(i==(N+M)/2){
      jon= (N+M)/2; /*posición de Jon*/
      vmezcla[i]= JON ; /*posicion de Jon*/
    }
    else if((v1[a]<=v2[b]) && a<N){

      vmezcla[i]=v1[a]; 
      a++; 
    }
    else if(b<M){
      vmezcla[i]=v2[b];
      b++; 
    }
  }

  /*Edad*/
  if(vmezcla[jon-1]<vmezcla[jon+1])
    edad=(int)(vmezcla[jon-1])+0.5; 
  else if(vmezcla[jon-1]==vmezcla[jon+1])
    edad=vmezcla[jon+1]; 
  else
    edad=(int)(vmezcla[jon+1])-0.5; 

  printf("Solucion:\n"); 
  printvec(vmezcla, (N+M+1)); 
  printf("\nJon Snow debe colocarse en la posición: %d, debe fingir tener %.1f anios \n", jon, edad); 
}
