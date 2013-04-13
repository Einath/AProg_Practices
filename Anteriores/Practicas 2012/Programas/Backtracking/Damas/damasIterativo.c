#include <stdio.h>
#include <string.h>

#define MAX 20

int reinas (int pos[], int n);
int colocada (int pos[], int k);
void salida (int pos[], int n);


int main () {
   int n, cont, pos[MAX];
   printf("Introduzca número de reinas: "); scanf("%d",&n);
   cont = DamasIterativo(pos,n);
   if (cont == 0) printf("No hay ninguna solucion");
   else printf("Total:%d soluciones",cont);
   return 0;
}


int DamasIterativo (int pos[], int n) {
   int cont = 0, k = 1;

   pos[1]=0;
   while (k>0) {
      pos[k]++;
      while ((pos[k]<=n)&&(Colocada(pos,k)==0)) pos[k]++;
      if (pos[k]<=n)
         if (k==n) { Salida(pos,n); cont++; }
         else { k++; pos[k]=0; }
      else k--;
   }
   return cont;
}


int Colocada (int pos[], int k) {
   int i;
   for i=1; i<k; i++)
      if ((pos[i] == pos[k]) && (abs(pos[i]-pos[k]) == abs(i-k))
         return 0;
   return 1;
} 


void Salida (int pos[], int n) {
   int i, j;
   for (i=1; i<=n; i++){
      for (j=1; j<=n; j++){
         if (pos[i]==j) printf("*");
         else printf("-");
      }
      printf("\n");
   }
   printf("\n");
}
