#include <stdio.h>

#define MAXDIM 50
#define TRUE 1
#define FALSE 0


typedef enum { Perdedora, Ganadora } TPosicion;

void Jugada (int Monton [], int N, TPosicion *Pos, int *NumMonton, int *NumPalillos); 
int Vacios (int Monton[], int N);


main () {

   int N, i;
   TPosicion Pos;
   int NumPalillos, NumMonton;

   int Monton[MAXDIM];

   printf("Introduzca el numero de Montones... "); scanf(" %d",&N);
      
   printf("El numero de montones es... %d\n", N);
      
   printf("Introduzca el numero de palillos de cada monton (separados por espacios)\n");
   
   for (i = 0; i < N; i++) scanf(" %d", &Monton[i]);
   
   printf("\n");
    
   printf("\nLos montones son:  ");
   for (i = 0; i < N; i++)
      printf(" %4d",Monton[i]);
   
   printf("\n\nEvaluando Posicion...\n");
         
   Jugada (Monton, N, &Pos, &NumMonton, &NumPalillos);
       
   printf("\n");
    
   printf("\nLos montones son:  ");
   for (i = 0; i < N; i++)
      printf(" %4d",Monton[i]);
         
   printf("\n\nLa posicion del juego es ");
  
   if (Pos == Ganadora) { 
      printf("GANADORA\n\n");
      printf("El resultado se obtiene tomando ");
      printf("%d PALILLOS del MONTON %d\n(Los montones comienzan a numerarse por 0)\n", NumPalillos, NumMonton);
   
      printf("Quedando la posicion:\n\nLos montones son:  ");
      Monton[NumMonton] -= NumPalillos;
      for (i = 0; i < N; i++)
         printf(" %4d",Monton[i]);
      printf("\n");
      
   }
   else printf("PERDEDORA\n\n");

    

   } // fin main





void Jugada (int Monton [], int N, TPosicion *Pos, int *NumMonton, int *NumPalillos) {
   int i, NPalillos, x, y;
   TPosicion PosDejamos;
   
   if (Vacios(Monton,N)) *Pos = Perdedora;
   else {
	
      i = 0; *Pos = Perdedora;
      while ((i<N) && (*Pos != Ganadora)) {
         NPalillos = Monton[i];
         while ((Monton[i] > 0) && (*Pos != Ganadora)) {
            Monton[i]--;
            Jugada(Monton,N,&PosDejamos,&x,&y);            
            if (PosDejamos == Perdedora) {
               *Pos = Ganadora; 
               *NumPalillos = NPalillos - Monton[i];
               *NumMonton = i;
            }
         }    
         Monton[i] = NPalillos;
         i++;
      }
      
   }   
} // Fin Jugada 

int Vacios (int Monton[], int N) {
   int i = 0;
   while (i<N) 
     if (Monton[i] != 0) return FALSE; else i++;
   return TRUE;
} // Fin Vacios  

























