#include "orders.h" 

void bubble (int v[LVECT]){

  int i, j, rep, aux; 
  rep=1;
  int cuentavueltas=0;



  while(rep==1){
    rep=0;
    cuentavueltas++;
    printf("Cuentavueltas: %d\n", cuentavueltas);  /*Contemplamos el lento progreso del algoritmo así */
    for(i=0; i<LVECT-1; i++)
      if(v[i]<=v[i+1]){
       /*no hace falta ordenar*/
    }
      else{
	aux=v[i];
	v[i]=v[i+1];
	v[i+1]=aux;
	rep=1;
      }
  }
  for (i=0; i<LVECT; i++)
    printf("%d\t", v[i]);  
}

void main(int argc, char argv[]){

  int v[LVECT], i;
  printf("Vector de números aleatorios:\n"); 
  srand(getpid()); 
  for (i=0; i<LVECT; i++){
    v[i]=rand()%10;
  } 
  printvec(v); 
  printf("\n"); 
  printf("Vector ordenado:\n"); 
  bubble(v);
  printf("\nBubblesort finalizado [%d elementos]\n", LVECT); 
}
