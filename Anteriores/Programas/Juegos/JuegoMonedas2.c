#include <stdio.h>

#define MAXDIM 50
#define TRUE 1
#define FALSE 0


typedef enum { Perdedora, Tablas, Ganadora } TPosicion;

typedef struct {
	int Valor, Cogida;
} TMoneda;


void Evaluar (int Suma, int SumaA, int SumaB, TMoneda Monedas [], int N,
              TPosicion *Pos, int *Moneda);
int MontonVacio (TMoneda Monedas[], int N);


void main () {

   int N, Suma, Moneda, i;
   TPosicion Pos;
  
   TMoneda Monedas[MAXDIM];

   printf("Introduzca la cantidad a sumar... "); scanf(" %d",&Suma);

   printf("Introduzca el numero de monedas del Monton... "); scanf(" %d",&N);
      
   printf("Introduzca el valor de cada moneda (separados por espacios)\n");
   
   for (i = 0; i < N; i++) {
   	scanf(" %d", &Monedas[i].Valor);
   	Monedas[i].Cogida = FALSE;
   }
   printf("\n");
    
   printf("\nLas monedas son:  ");
   for (i = 0; i < N; i++)
      printf(" %4d",Monedas[i].Valor);
   
   printf("\n\nEvaluando Posicion...\n");
         
   Evaluar2 (Suma,0,0,Monedas, N, &Pos, &Moneda);
       
   printf("\n");
    
   printf("\nLas monedas son:  ");
   for (i = 0; i < N; i++)
      printf(" %4d",Monedas[i].Valor);
         
   printf("\n\nLa posicion del juego es ");
  
   if (Pos == Perdedora)
   	printf("PERDEDORA\n\n");
   else {	
   	if (Pos == Ganadora) printf("GANADORA\n\n");
   	else printf("TABLAS\n\n");
   	
      printf("El resultado se obtiene cogiendo la moneda %d (Valor %d)\n",Moneda,Monedas[Moneda]);
      printf("(Las monedas comienzan a numerarse por 0)\n");
   
      printf("Quedando la posicion:\n\nLas monedas son:",
             " (Un cero indica que la moneda no está en el montón)\n");
      Monedas[Moneda].Cogida = TRUE;
      for (i = 0; i < N; i++) 
         if (!Monedas[i].Cogida)
            printf(" %4d",Monedas[i].Valor);
         else printf(" %4d",0);
         
      printf("\n");
   }

} // fin main



int MontonVacio (TMoneda Monedas[], int N) {
   int i = 0;
   while (i<N) 
     if (!Monedas[i].Cogida) return FALSE; else i++;
   return TRUE;
} // Fin MontonVacio



void Evaluar (int Suma, int SumaA, int SumaB, TMoneda Monedas [], int N,
              TPosicion *Pos, int *Moneda) {
              	
   int i, x;
   TPosicion PosDejamos;
   
   // Preguntamos siempre por el último que jugó
   if (SumaB == Suma) *Pos = Perdedora;
   else if (MontonVacio(Monedas,N))
            ||((SumaB > Suma) && (SumaA > Suma))) {
           // Si no tenemos monedas, o ambos se han pasado serán tablas
           *Pos = Tablas; *Moneda = -1; }
   else { // Caso no base, podemos jugar
	   i = 0; 
	   *Pos = Perdedora;
	
	   while ((i<N) && *Pos == Perdedora)) {
	      if (!Monedas[i].Cogida) {
	   	   Monedas[i].Cogida = TRUE;
	   	   Evaluar (Suma,SumaB,SumaA+Monedas[i].Valor,Monedas,N,&PosDejamos,&x);

            if (PosDejamos != Ganadora) {
               *Moneda = i;
           	   if (PosDejamos == Perdedora) *Pos = Ganadora;
               else *Pos = Tablas;
            }
            Monedas[i].Cogida = FALSE;
         } 
         i++;
      }
    }
