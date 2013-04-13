#include <stdio.h>

main(){

  int A[10] = {0, 1, 3, 4, 2, 7, 9, 8, 6, 5};
  printf("\n*Iniciando QuickSort*\n"); 
  int Li = 0; 
  int Ls = 9; 
  QS(A, Li, Ls);

}

void QS(int A[], int Li, int Ls){

  if (Li<Ls){

    int pos = Divide ( A, Li, Ls+1); 
    QS(A, Li, pos-1); 
    QS(A, pos+1, Ls); 

  }
}

int Divide(int A[], int Li, int Ls){
  int pivote = A[Li]; 
  int izq = Li, der = Ls; 
  do{
    while(A[++izq] < pivote); 
    while(A[--der] > pivote); 
    if(izq < der) Intercambia(&v[izq] &v[der]); 


  }while(izq < der); 
  Intercambia(&v[Li], &v[der]); 


  return der; 
}

