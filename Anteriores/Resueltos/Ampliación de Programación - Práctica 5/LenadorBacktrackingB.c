
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define NM_MAX      10
#define NM_MIN      3
#define R_MAX       6
#define R_MIN       1
#define TIEMPO_MAX  50
#define TIEMPO_MIN  10
#define INFINITO    9999

int bosque[NM_MAX][NM_MAX];

struct point {
    int fila;
    int columna;
};

struct TSol {
    int tiempo;
    struct point camino[NM_MAX];
    int numar;
    int cogidas[NM_MAX];
} Sol, SolOpt;

void genBosque(int, int);
void printBosque(int, int);
void backtracking(int, int, double, int, int, struct TSol, struct TSol*);
void backtracking_start(double, int, int, struct TSol, struct TSol*);
void copySol(struct TSol*, struct TSol*, int);
void printSolBack(int, int);
double distancia(int,int,int,int);

int main(int argc, char** argv) {

    // Generamos el bosque aleatoriamente
    srand(getpid());
    int n, m, r;
    n = rand() % NM_MAX + NM_MIN;
    m = rand() % NM_MAX + NM_MIN;
    if (n > NM_MAX) n = NM_MAX;
    if (m > NM_MAX) m = NM_MAX;
    r = rand() % R_MAX + R_MIN;
    if (r > R_MAX) r = R_MAX;
    genBosque(n, m);
    //Mostramos el bosque generado
    printBosque(n, m);
    //Llamamos al algoritmo Backtracking
    SolOpt.tiempo = INFINITO;
    Sol.tiempo = 0;
    Sol.numar=0;
    backtracking_start(r, n, m, Sol, &SolOpt);
    printSolBack(n, r);


    return (EXIT_SUCCESS);
}

void printSolBack(int n, int r) {
    int i;
    printf("SOLUCION BACKTRACKING (%d minutos) (Radio = %d)\n", SolOpt.tiempo, r);
    for (i = 0; i < n; i++) {
        printf("Fila %2d -> Arbol %2d (%3d minutos)\n", SolOpt.camino[i].fila, SolOpt.camino[i].columna, bosque[SolOpt.camino[i].fila][SolOpt.camino[i].columna]);
    }
}

void backtracking_start(double R, int n, int m, struct TSol Sol, struct TSol* SolOpt){
    int i,j;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            Sol.tiempo = bosque[i][j];
            backtracking(i, j, R, n, m, Sol, SolOpt);
        }
    }
}

void backtracking(int x0, int y0, double R, int n, int m, struct TSol Sol, struct TSol* SolOpt) {
    int i, j;
    Sol.cogidas[x0]=1; //Marcamos la fila donde estamos c0mo cogida
    Sol.camino[Sol.numar].fila = x0;
    Sol.camino[Sol.numar].columna = y0;
    if (Sol.tiempo < SolOpt->tiempo) { //Podamos si no vamos a conseguir una solucion mejor
        if (Sol.numar > n-2) { //Hemos encontrado una solucion
            copySol(&Sol, SolOpt, n);
        } else {
            for(i=0; i<n; i++){
                for(j=0; j<m;j++){
                    if(Sol.cogidas[i]!=1 && distancia(x0,y0,i,j)<=R){ //Hemos encontrado un arbol talable
                        Sol.numar++;
                        Sol.tiempo += bosque[i][j]; //Incrementamos el tiempo
                        //Llamada recursiva
                        backtracking(i, j, R, n, m, Sol, SolOpt);
                        //Ahora deshacemos:
                        Sol.tiempo -= bosque[i][j];
                        Sol.numar--;
                    }
                }
            }
        }
    }
    Sol.camino[Sol.numar].fila = -1;
    Sol.camino[Sol.numar].columna = -1;
    Sol.cogidas[x0]=0;
}

double distancia(int x0, int y0, int x1, int y1){
    return sqrt((double)(x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
}

void copySol(struct TSol* A, struct TSol* B, int n) {
    B->tiempo = A->tiempo;
    int i;
    for (i = 0; i < n; i++) {
        B->camino[i] = A->camino[i];
    }
}

void genBosque(int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            bosque[i][j] = rand() % TIEMPO_MAX + TIEMPO_MIN;
        }
    }
}

void printBosque(int n, int m) {
    int i, j;
    printf("\nBOSQUE GENERADO (filas = tipos, columnas = arboles)\n");
    printf("    ||");
    for (j = 0; j < m; j++) {
        printf(" %3d |", j);
    }
    printf("\n------");
    for (j = 0; j < m; j++) {
        printf("------");
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf(" %2d ||", i);
        for (j = 0; j < m; j++) {
            printf(" %3d |", bosque[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


