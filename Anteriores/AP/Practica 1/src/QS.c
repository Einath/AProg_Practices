#include "orders.h"

void QS(int v[LVECT], int inf, int sup){
  int pivote, i, j, aux;
  i=inf;
  j=sup;
  pivote=(sup+inf)/2;
  pivote=v[pivote];
  do{
    while(v[i]<pivote)
      i++;
    while(v[j]>pivote)
      j--;
    if(i<=j){
      aux=v[i];
      v[i]=v[j];
      v[j]=aux;
      i++; 
      j--;
    }
  }while(i<=j); 
  if(inf<j) QS(v, inf, j); 
  if(i<sup) QS(v, i, sup); 
}


void main(int argc, char argv[]){
  int v[LVECT], i, inf, sup; 
  inf=0; 
  sup=LVECT-1; 
  printf("Vector de números aleatorios:\n");
  srand(getpid()); 
  for(i=0; i<LVECT; i++)
    v[i]=rand()%10;

  printvec(v); 
  printf("\n");
  printf("Vector ordenado:\n"); 
  QS(v, inf, sup); 
  printvec(v);
  printf("\nQuicksort finalizado [%d elementos]\n", LVECT);
}
