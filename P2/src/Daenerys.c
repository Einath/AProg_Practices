#define INPUTFILE "src/P2_DaenerysInput.txt"
#define PLACES 4
#define COL 3

#define CAMP 0
#define BHORASH 1
#define MEEREEN 2
#define YUNKAI  3
#define ASTAPOR 4

#define GOLD 1
#define UNITS 2

#define INITIAL_STEP 1

#define TRUE 1
#define FALSE 0

#define RESERVED -2

#include "orders.h"

typedef struct {
  int S;
  int day;
  int position; 
  int units; 
  int g_obtained; 
  int g_spent; 
  int balance; 
} solution_step; 


void voraz(int distancia[PLACES+1][PLACES+1], int RnU[PLACES][COL], int visited[PLACES+2], int variante, solution_step sol[PLACES+2]); 
void back(int distancia[PLACES+1][PLACES+1], int RnU[PLACES][COL], int visited[PLACES+2], int variante, solution_step sol[PLACES+2], int step);
void progdin(int distancia[PLACES+1][PLACES+1], int RnU[PLACES][COL], int visited[PLACES+2], int variante, solution_step sol[PLACES+2]);

void calc(int RnU[PLACES][COL], int distancia[PLACES+1][PLACES+1], solution_step sol[], int origen, int destino, int index);
void undo(int RnU[PLACES][COL], int distancia[PLACES+1][PLACES+1], solution_step sol[], int origen, int destino, int index); /*Igual no es necesario*/

int selection_var1(int RnU[PLACES][COL], int distancia[PLACES+1][PLACES+1], int visited[PLACES+2], int position);
int selection_var2(int RnU[PLACES][COL], int distancia[PLACES+1][PLACES+1], int visited[PLACES+2], int position); /**/
int complete(int visited[PLACES+2]);

void print_sol(solution_step sol[PLACES+2]);
void print_status(solution_step sol);
void print_header();

void main(){

  FILE *fichero;
  int N, S, X; 
  int distancia[PLACES+1][PLACES+1]; 
  int RnU [PLACES+1][COL]; 
  solution_step sol[PLACES+2];
  int visited[PLACES+2];

  int variante, estrategia;
  int i, j; 


  fichero = fopen(INPUTFILE, "r");
    
  /*Lectura de datos */
  fscanf(fichero, "N\t%d\n", &N); 
  fscanf(fichero, "S\t%d\n", &S); 
  fscanf(fichero, "X\t%d\n", &X); 
  
  /*Lectura del array de distancias*/
  for(i=0; i<=PLACES; i++){
    for(j=0; j<PLACES; j++)
      fscanf(fichero, "%d\t", &distancia[i][j]); 
    fscanf(fichero, "%d\n", &distancia[i][j]); 
  }

  /*Lectura de Resources 'n Units*/

  /* Cuadramos una fila extra para que se ajusten los mismos 
   * índices en todas las tablas */
  RnU[0][0]=0; 
  RnU[0][1]=0; 
  RnU[0][2]=0; 

  for(i=1; i<=PLACES; i++)
    fscanf(fichero, "RU%d\t%d\t%d\n", &RnU[i][0], &RnU[i][1], &RnU[i][2]); 

  fclose(fichero); 
  printf("Datos:\n"); 
  /*Mostramos datos */
  printf("N: %d\n", N); 
  printf("S: %d\n", S); 
  printf("X: %d\n", X); 
  printf("Distancias:\n"); 
  /*Distancias */  
  for(i=0; i<=PLACES; i++){
    for(j=0; j<PLACES; j++)
      printf("%d\t", distancia[i][j]); 
    printf("%d\n", distancia[i][j]); 
  }
  printf("Recursos y Unidades:\n"); 
  /*Recursos y Unidades */
  for(i=1; i<=PLACES; i++){
    for(j=0; j<(COL -1); j++)
      printf("%d\t", RnU[i][j]); 
    printf("%d\n", RnU[i][j]); 
  }

  /*Inicializamos la estructura */
  sol[CAMP].S = S; 
  /* - Día */
  sol[CAMP].day=0; 

  /* - Posición */
  sol[CAMP].position = CAMP; 

  /* - Unidades */
  sol[CAMP].units = 0; 

  /* - Oro obtenido */
  sol[CAMP].g_obtained = 0; 

  /* - Oro gastado */
  sol[CAMP].g_spent = 0; 

  /* - Balance (oro total) */
  sol[CAMP].balance = X; 

  /* - Visitados */

  visited[0]=TRUE; 

  for(i=1; i<PLACES+1; i++)
    visited[i]=FALSE; 

  /*Fin estructura */

  do{
    printf("\n==========="); 
    printf("\nSeleccione:"); 
    printf("\n==========="); 
    printf("\n1. Variante 1\n2. Variante 2\n3. Variante 3\n=>"); 
    scanf("%d", &variante); 
    if((variante<=0) || (variante >3))
      printf("Error: Introduzca un valor [1, 3]\n"); 
  }while((variante<=0) || (variante >3));

  do{
    printf("\n==========="); 
    printf("\nSeleccione:"); 
    printf("\n==========="); 
    printf("\n1. Algoritmo voraz \n2. Backtracking \n3. Prog. Dinamica \n=>"); 
    scanf("%d", &estrategia); 
    if((estrategia<=0) || (estrategia >3))
      printf("Error: Introduzca un valor [1, 3]\n"); 
  }while((estrategia<=0) || (estrategia >3));

  if(estrategia == 1)
    voraz(distancia, RnU, visited, variante, sol); 
  else if(estrategia == 2)
    back(distancia, RnU, visited, variante, sol, INITIAL_STEP); 
  else if (estrategia == 3)
    progdin(distancia, RnU, visited, variante, sol); 

}


void voraz(int distancia[PLACES+1][PLACES+1], int RnU[PLACES][COL], int visited[PLACES+2], int variante, solution_step sol[PLACES+2]){ 
  int i; 
  printf("== Algoritmo Voraz | Variante %d ==\n", variante); 
  int destination, current; 
  /*
   * calc(RnU, distancia, sol, CAMP, ASTAPOR, 1); 
   * calc(RnU, distancia, sol, ASTAPOR, BHORASH, 2); 
   * calc(RnU, distancia, sol, BHORASH, YUNKAI, 3); 
   * calc(RnU, distancia, sol, YUNKAI, MEEREEN, 4); 
   * calc(RnU, distancia, sol, MEEREEN, CAMP, 5); 
   * !!Brassard 13.1.2 - 13.2.3 pp. 266 trp
   */


  visited[CAMP] = RESERVED; 

  i=1; 
  while(complete(visited)==FALSE){
    current = sol[i-1].position; 

    /* --------------------------- selección de variante */
    if((variante == 1) || (variante == 2))
      destination = selection_var1(RnU, distancia, visited, sol[i-1].position);
    else
      printf("No implementado\n"); 
    /* ------------------------fin selección de variante */

    calc(RnU, distancia, sol, current, destination, i); 
    visited[destination]=TRUE; 
    i++; 
  }

  current = sol[PLACES].position; 
  calc(RnU, distancia, sol, current, CAMP, PLACES+1); 

  print_sol(sol); 
}

void back(int distancia[PLACES+1][PLACES+1], int RnU[PLACES][COL], int visited[PLACES+2], int variante, solution_step sol[PLACES+2], int step){ 
  printf("== Backtracking | Variante %d ==\n", variante);   
  /*
   * Expansión
   * Solución
   * Fallo
   * Nodos:
   * - Solución
   * - Problema
   * - Fracaso
   */
  int current;
  int i=1; 

  visited[CAMP] = RESERVED; 

 
  // while(complete(visited)==FALSE){
  for(i=1; i<=PLACES; i++){
    current = sol[i-1].position; 
    
    if(visited[i]==FALSE){ // objetivo
      calc(RnU, distancia, sol, current, i, step);
      visited[i]=TRUE; 
      back(distancia, RnU, visited, variante, sol, step+1); 
      if((sol[i].balance <0)){ // Deshacer
	visited[i]=FALSE; 
      }
    }
    //  i++; 
  }

  current = sol[PLACES].position; 
  calc(RnU, distancia, sol, current, CAMP, PLACES+1); 
  
  print_sol(sol); 

}

void progdin(int distancia[PLACES+1][PLACES+1], int RnU[PLACES][COL], int visited[PLACES+2], int variante, solution_step sol[PLACES+2]){ 
   printf("== Programacion Dinamica | Variante %d ==\n", variante); 

}

void calc(int RnU[PLACES][COL], int distancia[PLACES+1][PLACES+1], solution_step sol[], int origen, int destino, int index){

  sol[index].day = sol[index-1].day + distancia[origen][destino];
  sol[index].position = destino; 

  if(destino != CAMP){
    sol[index].units = sol[index-1].units + RnU[destino][UNITS]; 
    sol[index].g_obtained = RnU[destino][GOLD]; 
  }
  else{
    sol[index].units = sol[index-1].units; 
    sol[index].g_obtained = 0; 
  }

  sol[index].g_spent = sol[index-1].units * sol[CAMP].S * distancia[origen][destino]; 
  sol[index].balance = sol[index-1].balance + sol[index].g_obtained - sol[index].g_spent; 

  /* Actualizamos datos del lugar */
  RnU[destino][GOLD] = 0; 
  RnU[destino][UNITS]=0; 

}

void print_sol(solution_step sol[PLACES+2]){
  int i; 

  print_header(); 
  for(i=0; i<(PLACES+2); i++)
    print_status(sol[i]);

}
void print_status(solution_step sol){
  printf("%d\t", sol.day); 
  if(sol.position==0)
    printf("CAMP"); 
  else if (sol.position==1) 
    printf("BHORASH"); 
  else if (sol.position==2) 
    printf("MEEREEN"); 
  else if (sol.position==3) 
    printf("YUNKAI"); 
  else if (sol.position==4) 
    printf("ASTAPOR"); 

  printf("\t%d\t%d\t%d\t%d\n", sol.units, sol.g_obtained, sol.g_spent, sol.balance); 
}
void print_header(){
  printf("\n=================================================\nDay\tPlace\tUnits\tGold\tSpent\tBalance\n=================================================\n"); 
}

int complete(int visited[PLACES+2]){
  int i, result=TRUE; 
  for(i=0; i<((PLACES+2)|| result == FALSE); i++){
    if(visited[i]!=TRUE)
      result = FALSE; 
  }

  return result; 
}

int selection_var1(int RnU[PLACES][COL], int distancia[PLACES+1][PLACES+1], int visited[PLACES+2], int position){

  int i; 
  int min=999, max=-999, i_min, i_max; 
  int destination=0, reserved_back=FALSE; 
  int last_destiny = FALSE; 
  int meta_far = -999; 

  /*Heurísticas*/
  /* 1 - La ruta maś corta se deja para el regreso. Así consume menos el mantenimiento de los soldados 
   *
   * 2 - La ubicación más larga ha de hacerse de las primeras, para ahorrar todo el coste: 
   *   - conforme nos vamos acercando a ese nodo, miramos si podemos ir recorriendo alguno más
   *   - de entre las posibles rutas intermedias seleccionar la más alejada al nodo final
   */


  if(position==CAMP){ 
    for(i=1; i<=PLACES; i++){/* H2 */
      if(meta_far < RnU[i][GOLD]/((RnU[i][UNITS])*distancia[CAMP][i])){
	meta_far = RnU[i][GOLD]/((RnU[i][UNITS])*distancia[CAMP][i]); 
	destination = i; 
      }
      
      /*     if(max < distancia[CAMP][i]){
       *	max = distancia[CAMP][i]; 
       *	i_max = i; 
       */

      if(min > distancia[CAMP][i]){
	min = distancia[CAMP][i]; 
	i_min = i; 
      }
    }
    visited[i_min]=RESERVED; /* H1 */

    return destination; 
  }

  else{
    for(i=1; i<=PLACES; i++) /* Guardamos el último destino antes del campamento */
      if(visited[i]==RESERVED)
	last_destiny=i; 

    for(i=1; i<=PLACES; i++){
      if(visited[i]==FALSE){ /* Es un candidato */
	/* Aquí va la chicha */
	if(meta_far < RnU[i][GOLD]/((RnU[i][UNITS])*distancia[position][i])){
	  meta_far = RnU[i][GOLD]/((RnU[i][UNITS])*distancia[position][i]); 
	  destination = i; 
	}
      }

      if(visited[i]== RESERVED) /* Controlamos si es el último paso */
	reserved_back = i; 
    }

    if(destination==0) /* Si no hubo destino, será el reservado de menor longitud */
      destination = reserved_back; 

    return destination; 
  }

}

int selection_var2(int RnU[PLACES][COL], int distancia[PLACES+1][PLACES+1], int visited[PLACES+2], int position){
  return 0; 
}

