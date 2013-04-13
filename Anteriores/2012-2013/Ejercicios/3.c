/*Disponemos de un vector A de N enteros ordenados en sentido creciente y 
otro B en sentido decreciente. Al menos uno de ellos en sentido estricto. Se
 pretende encontrar una posición I, tal que A[I]=B[I] */

#include <stdio.h>

main(){

  /* Vector de pruebas */
  int A[7]={-1, 1, 2, 3, 4, 5, 5};
  int B[7]={9, 8, 4, 3, 1, 0, -1};
  printf("*Buscar posición: %d\n", decide(A, B, 0, 6)); 

}

int decide(int A[], int B[], int Li, int Ls){

  if (Li>Ls)
    return -1;
  else{
    int md = (Li+Ls)/2; 
    if(A[md] == B[md]) return md;
    else if (A[md] < B[md]) return decide(A, B, Li, md-1); 
    else return decide(A, B, md+1, Ls); 

  return 0;   
  }
}
