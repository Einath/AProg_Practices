/*Ejercicio 5 del control: Conferencias en la universidad */

#include <stdio.h>
#define INFINITO 9999

void main(){
  int N, i, j, k, menor=INFINITO, aux;
  int NumSalas=0;

  printf("Introduzca Número de conferencias\n");
  scanf("%d",&N);
  printf("N: %d\n", N);
  int Sala[N];
  int Conf[2][N];
  printf("Introduzca H_Inicio/H_Fin para cada conferencia\n");
  for(i=0; i<N; i++){ 
    Sala[i]= 0;
    scanf("%d/%d", &Conf[0][i], &Conf[1][i]); /* Se piden datos y se muestran */
    printf("%d- %d / %d \t", i+1, Conf[0][i], Conf[1][i]); 
  }
  printf("\n");

  /*Comienza el algoritmo */

  for(i=0; i<N; i++){

    for(k=0; k<N; k++){    /* Seleccionamos la conferencia que comience antes*/
      if(Conf[0][k]<menor){
	aux=k; 
	menor=Conf[0][k];
      }
    }


    for(j=0; j<N; j++){
      if(Sala[j]<=Conf[0][aux]){
	Sala[j]=Conf[1][aux];
	Conf[1][aux]=j; /*j es la sala en la que se ha dado la conferencia que comienza antes*/
	j=N;
      }
    }
    Conf[0][aux]=INFINITO; /*Descartamos la conferencia elegida del grupo de posibles soluciones para futuras iteraciones*/
    menor=INFINITO;

  }

  for(i=0; i<N; i++)
    printf("Conferencia: %d Sala: %d\n", i+1, Conf[1][i]); 
}
