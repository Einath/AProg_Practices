#include <stdio.h>
#include <stdlib.h>

#define DIM 20

void QuickSort(int* v, int pivote, int tope); 
int colocar(int* v, int pivote, int tope); 

main(){
  int i; 
  int V[DIM]; 

  srand(getpid()); 

  for(i=0; i<DIM; i++){
    V[i]=rand()%100;
    printf("%d ", V[i]); 
  }

  printf("\n*** INICIANDO QS ***\n"); 

  QuickSort(V,0,(DIM-1)); 

  for(i=0; i<DIM; i++)
    printf("%d ", V[i]); 

  printf("\n"); 

}
void QuickSort(int* v, int b, int t){
  int pivote = 0; 

     if(b < t){
        pivote=colocar(v, b, t);
        QuickSort(v, b, pivote-1);
        QuickSort(v, pivote+1, t);
     }  
}

int colocar(int* v, int bottom, int top){
  int i, v_pivote, pivote, temp; 

  pivote = bottom; 
  v_pivote=v[bottom]; 

  for(i=bottom+1; i<=top; i++){
    if(v[i]<v_pivote){
      pivote++;
      temp=v[i];
      v[i]=v[pivote];
      v[pivote]=temp;
    }
  }

  temp=v[bottom];
  v[bottom]=v[pivote];
  v[pivote]=temp;

  return pivote; 
}


