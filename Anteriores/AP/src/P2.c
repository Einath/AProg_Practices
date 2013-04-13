#include "orders.h"

void pk (int v[], int p, int inf, int sup, int k){
  int pivote, pivote_sup, pivote_inf;
  int li=0;
  int ls=LVECT-1;



  while(p>=0){
    pivote=Divide(v, li, ls); 
    if((inf<=pivote)&&(pivote<=sup) && (k!= pivote)){ /*Caso 1: Dentro del rango*/

      if(pivote==inf)
	li=pivote+1;

      else if(pivote==sup)
	ls=pivote-1;

      else{
	pivote_inf=Divide(v, li, pivote-1); /*Búsqueda por abajo*/
	pivote_sup=Divide(v, pivote+1, ls); /*Búsqueda por arriba*/

	if(inf>pivote_inf)
	  li=pivote_inf;
	if(sup<pivote_sup)
	  ls=pivote_sup;
      }
      p--;
    }

    if(pivote>sup){/*Caso 2: Fuera del rango, por arriba*/
      ls=pivote-1;
    }

    if(pivote<inf){/*Caso 3: Fuera del rango, por abajo*/
      li=pivote+1;
    }
  }
}
void main(){
  int v[LVECT], i; /*vector de trabajo y vector resultado*/
  int p, k;
  srand(getpid());
  printf("Introduzca un valor para P:\n");
  scanf("%d", &p); 
  printf("Introduzca un valor para K:\n");
  scanf("%d", &k)
;
  int inf=k-p/2; /*Límite inferior*/
  if(inf<0)
    inf=0;

  int sup=k+(p-p/2);/*Límite superior*/
  if(sup>=LVECT)
    sup=LVECT-1;

  printf("\nVector de números aleatorios:\n"); /*Generamos el vector de números aleatorios valores 0-999*/ 
  for (i=0; i<LVECT; i++){
    v[i]=rand()%1000;
    printf("%d\t", v[i]);
  }

  int copia[LVECT];   /*Vector copia para comparar resultado final*/
  for(i=0; i< LVECT; i++)
    copia[i]=v[i];
  printf("\nVector ordenado con QS:\n");
  QS(copia, 0, LVECT-1);
  printvec(copia, LVECT);

  printf("\n\ninf: %d\nsup: %d\n\n", inf, sup);
  printf("K-esimo elemento: %d\n", copia[k]);

  pk(v, p, inf, sup, k); /*Llamada al método pk*/

  printf("====RESULTADO====\n");
  for(i=inf; i<=sup; i++){
      printf("%d\t", v[i]);
  }
  printf("\n\n");
}
