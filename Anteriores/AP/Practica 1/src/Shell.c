#include "orders.h"

  void shell(int A[LVECT]){
  int i, j, incrmnt, temp;
 
  incrmnt = LVECT/2;
  while (incrmnt > 0)
  {
    for (i=incrmnt; i < LVECT; i++)
    {
      j = i;
      temp = A[i];
      while ((j >= incrmnt) && (A[j-incrmnt] > temp))
      {
        A[j] = A[j - incrmnt];
        j = j - incrmnt;
      }
      A[j] = temp;
    }
    incrmnt /= 2;
  }
}



void main(int argc, char argv[]){

  int v[LVECT], i; 
  printf("Vector de números aleatorios:\n");
  srand(getpid()); 
  for(i=0; i<LVECT; i++){
    v[i]=rand()%10;
  }
   printvec(v);
  printf("\n");
  printf("Vector ordenado:\n"); 
  shell(v); 
  printvec(v); 
  printf("\nShellsort finalizado [%d elementos]\n", LVECT); 
}
