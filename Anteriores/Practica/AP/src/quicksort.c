


void swap( int v[], int x, int y){
  int aux;
  aux=v[x];
  v[x]=v[y];
  v[y]=aux;
}

int pivotar (int v[], int izq, int der){

    int posicionPivote = (izq + der) / 2;
    int valorPivote = v[posicionPivote];
    int indiceAlmacenamiento, indiceLectura;

    swap (v, posicionPivote, der);//Se situa el pivote al final del vector
    indiceAlmacenamiento = izq;
 
    for (indiceLectura = izq; indiceLectura < der; indiceLectura++){
        if (v[indiceLectura] <= valorPivote){
           swap (v, indiceLectura, indiceAlmacenamiento);
            indiceAlmacenamiento++;
        }
    }
 
    swap (v, indiceAlmacenamiento, der); //Se coloca el pivote en su lugar.
 
    return indiceAlmacenamiento;
}
 
void quicksort (int v[], int izq, int der){

    int pivote;
     if(izq < der){
        pivote = pivotar (v, izq, der); //Esta operación coloca el pivote en su lugar.
        quicksort(v, izq, pivote-1);
        quicksort(v, pivote+1, der);
    } 
}

void main(){
}
