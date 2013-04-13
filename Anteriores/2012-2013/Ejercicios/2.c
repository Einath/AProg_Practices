/*Disponemos de un vector A de N enteros ordenados en sentido decreciente, no 
  no necesariamente estricto. Se pretende encontrar una posición I, tal que A[I]=I */

#include <stdio.h>

main(){

  /* Vector de pruebas */
  int A[10]={9, 8, 4, 3, 1, 0, -1};
  printf("*Buscar posición: %d\n", decide(A, 0, 6)); 

}

int decide(int A[], int Li, int Ls){

  if (Li>Ls)
    return -1;
  else{
    int md = (Li+Ls)/2; 
    if(A[md] == md) return md;
    else if (A[md] < md) return decide(A, Li, md-1); 
    else return decide(A,md+1, Ls); 

  return 0;   
  }
}
