/*29-III-2011

Juegos

Ver Fig 1


Ej. (Juego de los palillos)

2 Player

Tres grupos de bolitas. 

Cada jugador va tomando bolitas. El que tome la última es el que gana. 

Se puede coger cualquier número de bolitas, pero solo de un grupo. 

..

Tipos de jugadas: Ganadora / Perdedora (no hay tablas)

*/

TDec struct{
  int Monton, NumPalillos;
}Dec;


void Palillos(int Montm[], int N, TPos *Pos, TDec *Dec){
  if (EsVacio(Montm, N)) *Pos = PERDEDORA;
  else{
    *Pos=Perdedora;
    for(i=0; (i<N) && (*Pos!=GANADORA); i++){
      NPalillos=Montm[i];
      while((Montm[i]>0) && (*Pos!=GANADORA)){
	Montm[i]--;
	Palillos(Montm, N, &PosDejamos, &Decxxx); /*La decisión no nos servirá, decide P2*/
	if(PosDejamos!=GANADORA){
	  *Pos=GANADORA;
	  Dec->Montm=i; Dec->NumPalillos=NPalillos-Montm[i];
	}/*if*/
      }/*while*/
      Montm[i]=NPalillos;
    }/*for*/
  }
}


/*Ejercicio 3 de la relación de problemas
*/

void Cerillas(int N, int M, TPos *Pos, int *Dec){ /*N; num cerillas. M; las que podemos coger*/
  if(N==0); *Pos= PERDEDORA; /* Puede omitirse*/
  else{
    *Pos=PERDEDORA;
    for(i=1; (i<=M) && (*Pos!=GANADORA); i++){
      Cerillas(N-i, 2*i - 1, &PosDejamos, &DecXXX);/*M debe estar acotada*/
      if(PosDejamos != GANADORA){
	*Pos=GANADORA;
	*Dec=i;
      }
    }
  }
}
/*Llamada inicial*/

Cerillas(N, N-1, &Pos, &Dec);


/* Ejercicio 6
Tableros de casillas accesibles

Ejercicio 7
 */


typedef struct{
  int fila;
  int columna;
}casilla;

typedef struct
  casilla c;
  int NumCasillas;
}Jugador;


void Eval(Jugador JugA, Jugador JugB, int N, int Tab[][], TPos *Pos, casilla *Dec){

  if(/*caso base*/)

  else{

    *Pos PERDEDORA;
 /*asegurar que la casilla está dentro del tablero y no está visitada*/
    for(i=-1;(i<=1) && (*Pos != GANADORA); i++) /*ojo que ahora puede haber tablas*/
      for(j=-1; (j<=1) && (*Pos!= GANADORA); j++){
	Jug=JugA;
	Ncas=JugA.casilla.fila+i; JugA.casilla.columna+j;
	if(Dentro(NCas))
	  if(Tab[NCas.fila][Ncas.columna]){
	    JugA.casilla=NCas;
	    JugA.NumCasillas++;
	    Tab[NCas.fila][NCas.columna]=FALSE;
	    Eval(JugB, JugA, N, Tab, &PosDejamos, &DecXXX);
	    if(PosDejamos != GANADORA){
	      if(PosDejamos==PERDEDORA)
		*Pos=GANADORA;
	      else{
		*Pos=TABLAS;
		*Dec=NCas;
		/*Deshacemos*/
		Tab[NCas.fila][NCas.columna]=TRUE;
		JugA=Jug;
	      }
	    }
	  }
      }
  
  }
}


/* 
Caso base de este ejercicio
ejercicio número 6
ejercicio número 4!,5
ej 8, 10
*/

/*Ejercicio 5*/

void Eval(int SumaA, int SumaB, int N, TDato Moneda [], TPos *Pos, int *Dec){

  if(SumaB==0)
    *Pos==PERDEDORA;
  else{ /*Juega A*/
    *Pos=PERDEDORA;
    for(i=0; ((i<N) && (*Pos != GANADORA)); i++){
      Monedas]i].Cogido=TRUE;
      Eval(SumaB, SumaA-Monedas[i].Valor, N, Monedas, &PosDejamos, &DecXXX);
      if(PosDejamos != GANADORA){
	*Dec=i;
	if(PosDejamos==PERDEDORA) *Pos=Ganadora;
	*Pos=TABLAS;
      }
      else if((SumaA < 0 ) && (SumaB <0) )
	*Pos=TABLAS;
  }
}

/*Ejercicio 10

5, 7, 8, 15, 1, 11, 10, 25, 14, 2, 3

JugA -> 15
5, 15, 1, 3

JugB -> 14
7, 2

JugA -> 25
25

JugB -> 10
10

...


                                        (int) */
void Eval10(int Num[], int N, TPos *Pos, TDec *Dec){

  if(Vacio(Num, N)) *Pos=PERDEDORA; /*Esto es omitible*/
  else{
    *Pos=PERDEDORA;Copia(Num, NumAux);/*Trabajaremos sobre una copia del vector*/
    for(i=0; (i<N)&&(*Pos!=GANADORA); i++){
      if(NumAux[i]>0){
	EliminaDivisores(NumAux, NumAux[i], N);
	Eval10(NumAux,&PosDejamos, &DecXXXX);
	if(PosDejamos!=GANADORA){
	  *Pos=GANADORA;
	  *Dec=i;
	}
	Copia(Num, NumAux);
      }
    }
  }
}

void EliminaDivisores(int V[], int Num, int N)
  for(i=0; i<N; i++){
    if((Num%V[i]==0) && (V[i]>0);
       V[i]=0;
  }
}
/*Ejercicios de los demás controles L/M*/
