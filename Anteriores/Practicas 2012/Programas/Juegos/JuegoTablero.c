#include <stdio.h>

#define MAXDIM 10
#define TRUE 1
#define FALSE 0


   typedef enum { Perdedora, Tablas, Ganadora } TPosicion;

   typedef struct {
      int Fila, Columna;
   } TCasilla;


   typedef struct {
      TCasilla Casilla;
      int NumCasillas;
   } TJugador;


   
   

   void Evaluar (TJugador JugadorA, TJugador JugadorB,
                 int Tab [MAXDIM][MAXDIM], int N,
                 TPosicion *Pos, TCasilla *Cas);

   void Inicializa (int Tab[][MAXDIM], int N, TJugador *JugadorA,
                    TJugador *JugadorB);

   TCasilla NuevaCasilla (int F, int C);

   int Dentro (TCasilla Cas, int N);

   int Valida (int Tab[MAXDIM][MAXDIM], int N, TCasilla Cas);

   int Bloqueado (int T[MAXDIM][MAXDIM], int N, TCasilla Cas);

   void EscribeTablero (int T[MAXDIM][MAXDIM], int N);



main () {

   int N, x, y;
   TPosicion Pos;
   TCasilla Casilla;
   TJugador JugadorA, JugadorB;
   int Tablero [MAXDIM][MAXDIM] =
          {1,1,0,1,1,1,1,1,1,1,
           1,1,0,1,1,1,0,0,1,1,
           1,1,0,0,1,1,1,1,1,1,
           1,1,1,0,1,1,0,1,1,1,
           1,1,1,1,1,0,1,1,1,1,
           0,0,0,1,1,0,1,1,1,1,
           0,0,0,1,1,1,0,0,1,1,
           0,0,0,1,1,1,0,1,1,1,
           0,0,0,1,1,1,0,1,1,1,
           1,1,1,1,1,1,0,1,1,1};
   
   
   printf("Dimension del tablero?... "); scanf(" %d",&N);
 
   printf("Posicion del jugador A (fila y columna separados por un");
   printf(" espacio)?... "); scanf(" %d %d",&x,&y);
   JugadorA.Casilla = NuevaCasilla(x,y);

   printf("Posicion del jugador B (fila y columna separados por un");
   printf(" espacio)?... "); scanf(" %d %d",&x,&y);
   JugadorB.Casilla = NuevaCasilla(x,y);


   Inicializa (Tablero, N, &JugadorA, &JugadorB);
   
   EscribeTablero(Tablero,N);

   printf("\n\nEvaluando Posicion...\n");
         
   Evaluar (JugadorA, JugadorB, Tablero, N, &Pos, &Casilla);
       
   printf("\n\nLa posicion del juego es ");
 
   if (Pos == Perdedora)
      printf("PERDEDORA\n\n");
   else {   
      if (Pos == Ganadora) printf("GANADORA\n\n");
      else printf("TABLAS\n\n");
     
      printf("El resultado moviendose a la casilla (%d,%d)\n",
             Casilla.Fila,Casilla.Columna);
   }

} // Fin main





   void Evaluar (TJugador JugadorA, TJugador JugadorB,
                 int Tab[MAXDIM][MAXDIM], int N,
                 TPosicion *Pos, TCasilla *Cas) {
      int i, j;
      TPosicion PosDejamos;
      TCasilla NCas, CasX;
      TJugador Jugador;
   
      if (Bloqueado(Tab,N,JugadorA.Casilla)) // JugadorA no puede moverse
         if (JugadorA.NumCasillas < JugadorB.NumCasillas) 
            *Pos = Perdedora;
         else if (Bloqueado(Tab,N,JugadorB.Casilla))
                 // JugadorB tampoco puede moverse
                 if (JugadorA.NumCasillas == JugadorB.NumCasillas)
                    *Pos = Tablas;
                 else *Pos = Ganadora;
              else { // JugadorB puede moverse, luego jugará
                 Evaluar(JugadorB,JugadorA,Tab,N,&PosDejamos,&CasX);
                 if (PosDejamos == Ganadora) *Pos = Perdedora;
                 else if (PosDejamos == Perdedora) *Pos = Ganadora;
                 else *Pos = Tablas;
              }
      else {
         i = -1; *Pos = Perdedora;
         while ((i <= 1) && (*Pos != Ganadora)) {
            j = -1; 
            while ((j <= 1) && (*Pos != Ganadora)) {
               NCas = NuevaCasilla(JugadorA.Casilla.Fila+i,
                                   JugadorA.Casilla.Columna+j);
               if ( Valida(Tab,N,NCas) ) {
                  Tab[NCas.Fila][NCas.Columna] = FALSE;
                  Jugador = JugadorA;
                  JugadorA.Casilla = NCas; JugadorA.NumCasillas++;
                  Evaluar(JugadorB,JugadorA,Tab,N,&PosDejamos,&CasX);
                  if (PosDejamos != Ganadora) {
                     *Cas = NCas;
                     if (PosDejamos == Perdedora) *Pos = Ganadora;
                     else *Pos = Tablas;
                  }
                  Tab[NCas.Fila][NCas.Columna] = TRUE;
                  JugadorA = Jugador;
               }   
               j++;
            }
            i++;
         }
      }     
   } // Fin Evaluar 


   void Inicializa (int Tab[][MAXDIM], int N, TJugador *JugadorA,
                    TJugador *JugadorB) {

      JugadorA->NumCasillas = 0;
      JugadorB->NumCasillas = 0;
      Tab[JugadorA->Casilla.Fila][JugadorA->Casilla.Columna] = 0;
      Tab[JugadorB->Casilla.Fila][JugadorB->Casilla.Columna] = 0;
   }


   TCasilla NuevaCasilla (int F, int C) {
      TCasilla Cas; 
      Cas.Fila = F; Cas.Columna = C;
      return Cas;
   }


   int Dentro (TCasilla Cas, int N) {
      return ((0 <= Cas.Fila) && (Cas.Fila < N) 
              && (0 <= Cas.Columna) && (Cas.Columna < N));
   }
     

   int Valida (int Tab[MAXDIM][MAXDIM], int N, TCasilla Cas) {
      if (!Dentro(Cas,N)) return FALSE;
      else return (Tab[Cas.Fila][Cas.Columna]);
   }


   int Bloqueado (int T[MAXDIM][MAXDIM], int N, TCasilla Cas) {
      int i, j; TCasilla NCas;
   
      for (i = -1; i <= 1; i++) 
         for (j = -1; j <= 1; j++) {
            NCas = NuevaCasilla(Cas.Fila+i,Cas.Columna+j);
            if (Dentro(NCas,N)) if (T[NCas.Fila][NCas.Columna])
               return FALSE;
         }
      return TRUE;
   }
   

   void EscribeTablero (int T[MAXDIM][MAXDIM], int N) {
      int i, j;

      printf("\nEl tablero es:\n");
      for (i = 0; i < N; i++) {
         for (j= 0; j < N; j++)
            if (T[i][j]) printf("-");
            else printf("X");
         printf("\n");
      }
      printf("\n");
   }
