Ej 23. 

Una matriz 4x4 se subdivide en cuatro submatrices 2x2. Esas submatrices se rotan internamente y después se ubican en su sitio. 

void Girar (int Origen [MAXDIM][MAXDIM], int Girada [MAXDIM][MAXDIM], int Fila, int Columna, int FilaGirada, int ColGirada, int N){

  if (N==1) /*caso base*/
    Girada[FilaGirada]þColGirada]=Origen[FIla][Columna];

 else{
   Girar(Origen, Girada, Fila, Columna, FilaGirada, ColGirada +N/2, N/2);
   Girar(Origen, Girada, Fila+N/2, Columna, FilaGirada, ColGirada , N/2);
   /*se operan los demás cambios añadiendo los índices apropiados*/
   Girar(Origen, Girada, Fila, Columna, FilaGirada, ColGirada, N/2);
   Girar(Origen, Girada, Fila, Columna, FilaGirada, ColGirada, N/2); 
 }
}


/*Traspuesta de una matriz. 

Una matriz NxN en general se subdivide en matrices N/2 * N/2. Se trasponen internamente y se colocan en su sitio. 

*/

void Girar (int Origen [MAXDIM][MAXDIM], int Girada [MAXDIM][MAXDIM], int Fila, int Columna, int FilaGirada, int ColGirada, int N){

    if (N==1) /*caso base*/
      Girada[FilaGirada]þColGirada]=Origen[FIla][Columna];
 else{
   Girar(Origen, Girada, Fila, Columna, FilaGirada, ColGirada , N/2);
   Girar(Origen, Girada, Fila+N/2, Columna, FilaGirada, ColGirada +N/2 , N/2);
   /*se operan los demás cambios añadiendo los índices apropiados*/
   Girar(Origen, Girada, Fila, Columna+N/2, FilaGirada+N/2, ColGirada, N/2);
   Girar(Origen, Girada, Fila+N/2, Columna, FilaGirada+N/2, ColGirada+N/2, N/2); 
 }

/* Ejercicio 18 

1)Ponemos de raíz la mayor de los dos. (Se generan dos árboles nuevos, total hay 3)
2)Se cuelga de la nueva raíz, el otro montículo (hay 2 montículos)
3)Se mezclan los dos montículos que quedan. 

*/

TMonticulo Monticulo (TMonticulo A, TMonticulo B){
  TMonticulo Izq, Der; 
  if(esVacio(A))
    return B; 
  else if(esVacio(B))
    return A;
  else{
    if(Raiz(A) >= Raiz(B))
      return Construir (Raiz(A), B, Monticulo(HijoIzq(A), HijoDer(A)));

    else
      return Construir (Raiz(B), A, Monticulo(HijoIzq(B), HijoDer(B)));
  }
}

/*Ejercicio 28 - Closes Pair Divide y vencerás 

- Se ordenan los puntos según una componente (x)
- Se divide a la mitad (número de puntos) 
- El mínimo puede hallarse en: 
  - Parte izq
  - Parte der
  - Un punto en parte izq y otro en parte der




*/




