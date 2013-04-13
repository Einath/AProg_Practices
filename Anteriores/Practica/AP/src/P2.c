#include "orders.h"

void pk (int v[], int res[], int p, int inf, int sup, int k){
  /*algoritmo p-k*/
  int pivote, li, ls, low, up;
  int i=0;
  li=0;
  ls=LVECT-1;
  low=k-inf;
  up=sup-k;


  pivote=Divide(v, li, ls); 

  while(res[sup-inf-1]<0){

    if((inf<=pivote)&&(pivote<=sup) && (k!= pivote)){
      res[i]=v[pivote];
      i++;
      pivote=Divide(v, li, pivote-1);
      pivote=Divide(v, pivote+1, ls);
    }

    if(pivote>=sup){
      ls=pivote -1;
      pivote=Divide(v, li, ls); 
    }

    if(pivote<=inf){
      li=pivote +1;
      pivote=Divide(v, li, ls); 
    }
  }

  printf("\n===RESULTADO===\n");
  printvec(res, sup-inf);
  printf("\n");
}

void main(){
  int v[LVECT], i; /*vector de trabajo y vector resultado*/
  int p, k;
  srand(getpid());
  /*generamos un p aleatorio
  srand(getpid()); la semilla será el Pid del proceso

  int p=(rand()%(LVECT-2))+1;   rango de p: [1, x] , x es la longitud del vector -1 (k-ésimo elemento)

  generamos un k aleatorio

  int k=rand()%(LVECT-1);  rango de k: [0, LVECT -1] */
  printf("Introduzca un valor para P:\n");
  scanf("%d", &p); 
  printf("Introduzca un valor para K:\n");
  scanf("%d", &k);

  int inf=k-p/2;
  int sup=k+(p-p/2);

  int res[sup-inf-1];
  for(i=0; i<LVECT; i++)
    res[i]=-1;
  printf("\nres inicializado:\n");
  printvec(res, sup-inf);

  printf("\nVector de números aleatorios:\n"); 
  for (i=0; i<LVECT; i++){
    v[i]=rand()%100;
    printf("%d\t", v[i]);
  }


  int copia[LVECT]; 
  for(i=0; i< LVECT; i++)
    copia[i]=v[i];
  printf("\nVector ordenado con QS:\n");
  QS(copia, 0, LVECT-1);
  printvec(copia, LVECT);


  printf("\n\ninf: %d\nsup: %d\n", inf, sup);
  pk(v, res, p, inf, sup, k);
  printf("\n");
  printvec(v, LVECT);

}




