#include <stdio.h>
#include <stdlib.h>

#define DIM 20

void MergeSort(int* v, int pivote, int tope); 
int Ordenar(int* v, int pivote, int tope); 

main(){
  int i; 
  int V[DIM]; 

  srand(getpid()); 

  for(i=0; i<DIM; i++){
    V[i]=rand()%100;
    printf("%d ", V[i]); 
  }

  printf("\n*** INICIANDO MS ***\n"); 

  MergeSort(V,0,(DIM-1)); 

  for(i=0; i<DIM; i++)
    printf("%d ", V[i]); 

  printf("\n"); 

}
void MergeSort(int* v, int b, int t){


}

int Ordernar(int* v, int bottom, int top){
  return 1; 
}


