#include <stdio.h>
#include <stdlib.h>

#define MAX 20

main(){

  int V[MAX];
  int i; 
  srand(getpid()); 

  for(i=0; i<MAX; i++){
    V[i]=rand()%100; 
    printf("%d ", V[i]); 
  }
  
  printf("\n*Iniciando QuickSort*\n"); 

  Quicksort(V, 0, MAX-1); 

  for(i=0; i< MAX; i++){

    printf("%d ", V[i]); 
  }
  printf("\n"); 

}

int colocar(int *v, int b, int t)
{
    int i;
    int pivote, valor_pivote;
    int temp;
 
    pivote = b;
    valor_pivote = v[pivote];
    for (i=b+1; i<=t; i++){
        if (v[i] < valor_pivote){
                pivote++;    
                temp=v[i];
                v[i]=v[pivote];
                v[pivote]=temp;
         }
    }
    temp=v[b];
    v[b]=v[pivote];
    v[pivote]=temp;
    return pivote;
} 
 
void Quicksort(int* v, int b, int t)
{
     int pivote;
     if(b < t){
        pivote=colocar(v, b, t);
        Quicksort(v, b, pivote-1);
        Quicksort(v, pivote+1, t);
     }  
}

