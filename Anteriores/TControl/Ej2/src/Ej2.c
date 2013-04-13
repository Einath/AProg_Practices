/* Ejercicio 7: Juan el Gorrilla (por voraces) */

#include <stdio.h>
#define INFINITO 9999
#define TRUE 0
#define FALSE 1

void main(){
  int N, L;
  int i, mejor; 

  double aux=0.001, ratio=0.001; 

  int Beneficio=0; 
  int seguir=TRUE; 
  printf("Introduzca Número de vehículos\n");
  scanf("%d", &N); 
  printf("N: %d\n", N); 
  int Coche[2][N]; /* para 'i' Fila 0: Beneficio. Fila 1: Longitud */
  int Aparcado[N]; 

  for(i=0; i<N; i++) /* El vehículo i estará aparcado en Aparcado[i]*/
    Aparcado[i]=-1; 

  printf("Introduzca Propina/Longitud para cada vehículo\n"); 
  for(i=0; i<N; i++){
    scanf("%d/%d", &Coche[0][i], &Coche[1][i]); /*Se piden datos y se muestran */
    printf("%d- %d / %d \t", i+1, Coche[0][i], Coche[1][i]); 
  }
  printf("\n"); 

  printf("Introduzca Longitud de las aceras\n"); 
  scanf("%d", &L); 
  printf("L: %d\n", L); 

  int Acera[2]; /* Acera 0, Acera 1, podría haberse dado L0!=L1 */
  Acera[0]=L; 
  Acera[1]=L;

  while(seguir==TRUE){
    ratio=-INFINITO; 
    mejor=-1; 

    for(i=0; i<N; i++){ /* selección del mejor candidato */
      aux = (double) Coche[0][i]/Coche[1][i]; 
      if((aux > ratio) && (aux >0)){
	mejor=i; 
	ratio=aux; 
      }
    }
    if(mejor!=-1){
      if(Acera[0]>=Coche[1][mejor]){ /* aparcamos en Acera 0 */
	Acera[0]-=Coche[1][mejor]; 
	Beneficio+= Coche[0][mejor]; 
	Coche[0][mejor]=-INFINITO; 
	Aparcado[mejor]=0; 
      }
      else if(Acera[1]>=Coche[1][mejor]){ /* aparcamos en Acera 1 */
	Acera[1]-=Coche[1][mejor]; 
	Beneficio+= Coche[0][mejor]; 
	Coche[0][mejor]=-INFINITO; 
	Aparcado[mejor]=1; 
      }
      else{                               /* No aparcamos este vehículo */
	Aparcado[mejor]=-1; 
	Coche[0][mejor]=-INFINITO; 
      }
    }
    else
      seguir = FALSE; 
  }

  printf("Beneficio total: %d\n", Beneficio); 
  for(i=0; i<N; i++){
    printf("Vehículo %d:\t", i+1); 
    if(Aparcado[i]==0)
      printf("Acera 0\n"); 
    else if(Aparcado[i]==1)
      printf("Acera 1\n"); 
    else
      printf("No aparcado\n"); 
  }
  printf("Hueco libre en Acera 0: %d\n", Acera[0]); 
  printf("Hueco libre en Acera 1: %d\n", Acera[1]); 
}
