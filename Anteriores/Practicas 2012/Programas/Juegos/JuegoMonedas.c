#include <stdio.h>

#define MAXDIM 50
#define TRUE 1
#define FALSE 0


typedef enum { Perdedora, Tablas, Ganadora } TPosicion;

void Evaluar (int Suma, int SumaA, int SumaB, int Monedas [], int N, TPosicion *Pos, int *Moneda);
void Evaluar2 (int Suma, int SumaA, int SumaB, int Monedas [], int N, TPosicion *Pos, int *Moneda);
int MontonVacio (int Monedas[], int N);


main () {

   int N, Suma, Moneda, i;
   TPosicion Pos;
   
   int Monedas[MAXDIM];

   printf("Introduzca la cantidad a sumar... "); scanf(" %d",&Suma);

   printf("Introduzca el numero de monedas del Monton... "); scanf(" %d",&N);
      
   printf("Introduzca el valor de cada moneda (separados por espacios)\n");
   
   for (i = 0; i < N; i++) scanf(" %d", &Monedas[i]);
   
   printf("\n");
    
   printf("\nLas monedas son:  ");
   for (i = 0; i < N; i++)
      printf(" %4d",Monedas[i]);
   
   printf("\n\nEvaluando Posicion...\n");
         
   Evaluar2 (Suma,0,0,Monedas, N, &Pos, &Moneda);
       
   printf("\n");
    
   printf("\nLas monedas son:  ");
   for (i = 0; i < N; i++)
      printf(" %4d",Monedas[i]);
         
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
      Monedas[Moneda] = 0;
      for (i = 0; i < N; i++)
         printf(" %4d",Monedas[i]);
      printf("\n");
      
   }

    

   } // fin main





void Evaluar (int Suma, int SumaA, int SumaB, int Monedas [], int N, TPosicion *Pos, int *Moneda) {
   int i, x, Valor;
   TPosicion PosDejamos;
   
   if (SumaB == Suma) *Pos = Perdedora;
   else if ((MontonVacio(Monedas,N)) 
            || ((SumaA > Suma) && (SumaB > Suma)))
           *Pos = Tablas;
        else {
           i = 0; *Pos = Perdedora;
           while ((i<N) && (*Pos != Ganadora)) {
              if (Monedas[i] != 0) {
         	     Valor = Monedas[i]; 
         	     Monedas[i] = 0;
                 Evaluar(Suma,SumaB,SumaA+Valor,Monedas,N,&PosDejamos,&x);            
                 if (PosDejamos != Ganadora) {
                 	  *Moneda = i;
                 	  if (PosDejamos == Perdedora) *Pos = Ganadora;
                 	  else *Pos = Tablas;
                 }
                 Monedas[i] = Valor;
              }   
              i++;
           }
        }    
} // Fin Evaluar 


void Evaluar2 (int Suma, int SumaA, int SumaB, int Monedas [], int N, TPosicion *Pos, int *Moneda) {
   int i, x, Valor;
   TPosicion PosDejamos;
   
   if ( (MontonVacio(Monedas,N)) || ((SumaA > Suma) && (SumaB > Suma)) )
      *Pos = Tablas;
   else {
      i = 0; *Pos = Perdedora;
      while ((i<N) && (*Pos != Ganadora)) {
         if (Monedas[i] != 0) {
            if (Suma == SumaA + Monedas[i]) { // La posicion es GANADORA: elegimos la moneda i
        	      *Pos = Ganadora; *Moneda = i;
        	   }
        	   else { // Hay que evaluar la jugada (Tomamos la moneda i)	  
     	         Valor = Monedas[i]; 
     	         Monedas[i] = 0;
               Evaluar2(Suma,SumaB,SumaA+Valor,Monedas,N,&PosDejamos,&x);            
               if (PosDejamos != Ganadora) {
                  *Moneda = i;
           	      if (PosDejamos == Perdedora) *Pos = Ganadora;
             	   else *Pos = Tablas;
               }
               Monedas[i] = Valor;
            }
         }
         i++;
      }
   }    
} // Fin Evaluar2 


int MontonVacio (int Monedas[], int N) {
   int i = 0;
   while (i<N) 
     if (Monedas[i] != 0) return FALSE; else i++;
   return TRUE;
} // Fin MontonVacio

























