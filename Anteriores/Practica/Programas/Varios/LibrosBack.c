#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAXDIM 20
#define INFINITO 10000


typedef struct {
   int Resto;
   int Libro [MAXDIM]; /* TRUE sii compramos el libro k */
} TSolucion;

void LibrosBack (int k, int Dinero, int N, int Precio[N], 
                 TSolucion *Sol, TSolucion *SolOptima) {
   // Test de solucion: Vemos si ya hemos decidido los N libros
   if (k == N) {
      Sol->Resto = Dinero;
      if ((Sol->Resto < SolOptima->Resto) *SolOptima = *Sol; 
   }
   else {
      // Lo compramos, si podemos
      if (Dinero >= Precio[k]) {
          Sol->Comprado[k] = TRUE;
          LibrosBack (k,Dinero-Precio[k],N,Precio,Sol,SolOptima);
      }
      // Siempre podemos no comprarlo
      Sol->Comprado[k] = FALSE;
      LibrosBack (k,Dinero,N,Precio,Sol,SolOptima);
   }
} // LibrosBack


       
void LibrosBack2 (int k, int N, int Precio[N], 
                  TSolucion *Sol, TSolucion *SolOptima) {
   // Test de solucion: Vemos si ya hemos decidido los N libros
   if (k == N) {
      if ((Sol->Resto < SolOptima->Resto) *SolOptima = *Sol; 
   }
   else {
      // Lo compramos si podemos
      if (Sol->Resto >= Precio[k]) {
          Sol->Resto -= Precio[k]);
          Sol->Comprado[k] = TRUE;
          LibrosBack2 (k,Dinero-Precio[k],N,Precio,Sol,SolOptima);
          Sol->Resto += Precio[k]);
      }
      // Siempre podemos no comprarlo
      Sol->Comprado[k] = FALSE;
      LibrosBack2 (k,N,Precio,Sol,SolOptima);
   }
} // LibrosBack2
       
      

void main() {
   int Dinero;
   int Precio[MAXLIBROS];
   TSolucion Sol, SolOptima;
   
   
   LeerDatos(&Dinero,&N,Precio);
   
   // Inicializaciones
   SolOptima.Resto = INFINITO;
   // Llamada inicial
   LibrosBack (0,Dinero,N,Precio,&Sol,&SolOptima);

   Salida(SolOptima,Dinero,Precio,N);

   // OTRA VERSION
   // Inicializaciones
   SolOptima.Resto = INFINITO;
   Sol.Resto = Dinero;
   LibrosBack2 (0,N,Precio,&Sol,&SolOptima);

   Salida(SolOptima,Dinero,Precio,N);
}


void Salida (TSolucion Sol, int Dinero, int Precio[], int N) {
   int i;
   
   printf("Dinero disponible %d\n",Dinero);
   printf("Libros comprados y su precio:\n\n");
   for (i=0; i<N; i++) 
      if (Sol.Comprado[k]) printf("Libro %d ( %d), ",k,Precio[k]);
   printf("\n\nEn total ha quedado por gastar %d\n",Sol.Resto);
}
   
 
