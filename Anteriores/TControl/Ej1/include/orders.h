#include <stdio.h>

#define LVECT 20

void printvec(int v[], int longitud){
  int i; 
  for (i=0; i< longitud; i++)
    printf("%d\t", v[i]); 
}


void QS(int v[], int li, int ls){
  if(li < ls){
    int pos=Divide(v, li, ls);
    QS(v, li, pos-1);
    QS(v, pos+1, ls); 
  }
}

int Divide(int v[], int b, int t){

  int i; 
  int pivote, valorpivote;
  int temp;

  pivote=b;
  valorpivote=v[pivote];
  for (i=b+1; i<=t; i++){
    if(v[i]<valorpivote){
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



int OtroDivide (int v[], int li, int ls){/* No chuta bien*/
  int pivote=v[li];
  int aux;
  int izq=li;
  int der=ls;
  do{
    while(v[++izq]<pivote);
    while(v[--der]>pivote);

    if(izq<der){
      aux=v[izq];
      v[izq]=v[der];
      v[der]=aux;
    }
  }while(izq<der); 

  aux=v[izq];
  v[izq]=v[der];
  v[der]=aux;

  return der; 

}
