#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CALLE           10
#define PLAZA           11
#define MAX_COSTE       5000
#define MIN_COSTE       1000
#define MAX_VOTANTES    3000
#define MIN_VOTANTES    100
#define SI              1
#define NO              0
#define MAX_PLAZAS      10
#define MAX_CALLES      10
#define PRESUPUESTO     20000
#define ASFALTADA       -1
#define CARA            -2

struct st {
    int coste;
    int votantes;
    double densidad;
    int tipo;
    int estado;
    int indice;
};

int presupuesto = PRESUPUESTO;

struct st* candidatos[MAX_PLAZAS + MAX_CALLES];
int ncandidatos = 0;

void genst(struct st v[],int n, int t){
    int i;
    for (i = 0; i < n; i++) {
        v[i].coste = rand() % MAX_COSTE + MIN_COSTE;
        v[i].votantes = rand() % MAX_VOTANTES + MIN_VOTANTES;
        v[i].densidad = v[i].votantes/(double)v[i].coste;
        v[i].tipo = t;
        v[i].indice = i;
        v[i].estado = 0;
    }
}

void printst(struct st v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("       %2d        |", i);
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("-----------------");
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf(" c:%5d, v:%4d |", v[i].coste, v[i].votantes);
    }
}

void inicializa(int v[], int n, int valor){
    int i;
    for(i = 0; i < n; i++){
        v[i] = valor;
    }
}

int numApariciones(int v[], int n, int valor){
    int i, num = 0;
    for(i = 0; i < n; i++){
        if(v[i] == valor){
            num++;
        }
    }
    return num;
}

void printgrafo(int v[][MAX_PLAZAS], int ncalles, int nplazas){
    int i, j;
    for(i = 0; i < ncalles; i++){
        for(j = 0; j < nplazas; j++){
            printf(" %d |",v[i][j]);    
        }
        printf("\n");
    }
}

void gengrafo(int v[][MAX_PLAZAS],int ncalles, int nplazas){
    int i, j, aux, elegidos[ncalles], neleg = 0;
    inicializa(elegidos,ncalles,-1);

    /* Inicializamos el grafo con ceros*/
    for(i = 0; i < ncalles; i++){
        for(j = 0; j < nplazas; j++){
            v[i][j] = 0;
        }
    }
   
    /* Le asignamos a cada plaza una calle */
    for(j = 0; j < nplazas; j++){
        do{
            aux = rand() % ncalles;
        }while((numApariciones(elegidos,ncalles,aux) > 0) && (neleg < ncalles));
        v[aux][j] = 1;
        elegidos[neleg] = aux;
        neleg++;
    }
    
    /* Hacemos que cada calle tenga 2 plazas <-------------------------------------------------- */
    int faltan,k;
    for(i = 0; i < ncalles; i++){
        faltan = 2 - numApariciones(v[i],nplazas,1);
        for(k = 0; k < faltan; k++){
            do{
                aux = rand() % nplazas;
            }while(v[i][aux]==1);
            v[i][aux]=1;
        }
    }
}

struct st* mejorAlPrincipio(struct st plazas[], int nplazas, struct st calles[], int ncalles){
    struct st* aux = &plazas[0];
    int i;
    for(i = 1; i < nplazas; i++){
        if(plazas[i].densidad > aux->densidad){
            aux = &plazas[i];
        }
    }
    for(i = 0; i < ncalles; i++){
        if(calles[i].densidad > aux->densidad){
            aux = &calles[i];
        }
    }
    return aux;
}

int estaEnCandidatos(struct st* c){
    int esta = NO, i;
    for(i = 0; i < ncandidatos; i++){
        if((candidatos[i]->indice == c->indice) && (candidatos[i]->tipo == c->tipo)){
            esta = SI; i = ncandidatos; //para salir del bucle
        }
    }
    return esta;
}

void addAdy(struct st* aux, int grafo[][MAX_PLAZAS], int nplazas, int ncalles, struct st plazas[], struct st calles[]){
    int i,j;
    if(aux->tipo == PLAZA){ // es una plaza
        for(i = 0; i < ncalles; i++){
            if(grafo[i][aux->indice] == 1){
                //Comprobamos que no este ya en candidatos
                if(estaEnCandidatos(&calles[i]) == NO) candidatos[ncandidatos++] = &calles[i];
            } 
        }
    }else{ // es una calle
        for(j = 0; j < nplazas; j++){
            if(grafo[aux->indice][j] == 1){
                //Comprobamos que no este ya en candidatos
                if(estaEnCandidatos(&plazas[j]) == NO) candidatos[ncandidatos++] = &plazas[j];
            }
        }
    }
}

//Recorre los candidatos y nos dice el mejor de entre los que no son ni caros ni estan asfaltados, si no hay ninguno libre devuelve NULL
struct st* mejorCandidato(){
    int i;
    struct st* mejor = NULL;
    /* Buscamos alguno libre */
    for(i = 0; i < ncandidatos; i++){
        if(candidatos[i]->estado == 0){
            mejor = candidatos[i];
            i = ncandidatos;
        }
    }
    if(mejor!=NULL){
        for(i = 1; i < ncandidatos; i++){
            if((candidatos[i]->densidad > mejor->densidad) && (candidatos[i]->estado == 0)) mejor = candidatos[i];
        }
    }
    return mejor;
}

void asfaltar(struct st* s){
    if(s->coste <= presupuesto){
        s->estado = ASFALTADA;
        presupuesto -= s->coste;
    }else{
        s->estado = CARA;
    }
}

int main(){
    
    srand(getpid());
       
    int i;
    
    int nplazas;
    int ncalles;
    nplazas = rand() % (MAX_PLAZAS-1) + 2;
    ncalles = rand() % (MAX_CALLES-1) + (nplazas - 1);
    struct st plazas[nplazas];
    struct st calles[ncalles];
    genst(plazas,nplazas,PLAZA); //11 es plaza
    genst(calles,ncalles,CALLE); //10 es calle
    
    int grafo[ncalles+1][nplazas+1];
    gengrafo(grafo,ncalles,nplazas);
    
    
    printf("nplazas = %d, ncalles = %d\n", nplazas, ncalles);
    printf("\nEl grafo es: (Filas: calles, Columnas: plazas)\n");
    printgrafo(grafo,ncalles,nplazas);
    
    /* PARA DEPURAR 
    printf("PLAZAS:\n");
    for(i = 0; i < nplazas; i++){
        printf("Tipo:%2d Coste: %d, votantes: %d, estado: %d, densidad: %5f, indice: %d\n",plazas[i].tipo,plazas[i].coste, plazas[i].votantes, plazas[i].estado, plazas[i].densidad, plazas[i].indice);
    }
    
    printf("CALLES:\n");
    for(i = 0; i < ncalles; i++){
        printf("Tipo: %2d Coste: %d, votantes: %d, estado: %d, densidad: %5f, indice: %d\n",calles[i].tipo,calles[i].coste, calles[i].votantes, calles[i].estado, calles[i].densidad, calles[i].indice);
    }
    printf("--\n");*/
    
    
    /* Algoritmo voraz */
    int fin = SI; struct st* aux;
    do{
    
        if(ncandidatos == 0){
            aux = mejorAlPrincipio(plazas,nplazas,calles,ncalles);
            candidatos[ncandidatos++] = aux;
            asfaltar(aux);
            if(aux->estado == -1) addAdy(aux,grafo,nplazas,ncalles,plazas,calles);
            
        }else{
            aux = mejorCandidato();
            if(aux!=NULL){
                asfaltar(aux);
                if(aux->estado == -1) addAdy(aux,grafo,nplazas,ncalles,plazas,calles);
            }else{
                fin = SI;
            }

        }
        
        /*Esto imprime los candidatos para depurar
        printf("CANDIDATOS:\n");
        for(i = 0; i < ncandidatos; i++){
            printf("Tipo %d, indice %d, densidad %f, estado %d\n",candidatos[i]->tipo,candidatos[i]->indice, candidatos[i]->densidad, candidatos[i]->estado);
        }
        printf("--\n");*/
        
        for(i=0; i<ncandidatos; i++){
            if(candidatos[i]->estado == 0){
                fin = NO;
                i = ncandidatos;
            }
        }
    }while(fin == NO);
    
    /* AHORA IMPRIMIMOS EL RESULTADO */
    printf("\nPRESUPUESTO INICIAL: %d\n",PRESUPUESTO);
    printf("CALLES y PLAZAS ASFALTADAS:\n");
    for(i = 0; i < ncandidatos; i++){
        if(candidatos[i]->estado == ASFALTADA){
            if(candidatos[i]->tipo == PLAZA) printf("\tPlaza ");
            else printf("\tCalle ");
            printf("%2d\n", candidatos[i]->indice);
        }
    }
    
    printf("PRESUPUESTO RESTANTE: %d\n\n",presupuesto);
    
    
    return 0;
}

