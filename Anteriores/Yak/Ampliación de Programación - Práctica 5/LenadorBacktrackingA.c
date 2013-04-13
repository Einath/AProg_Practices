
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NM_MAX      10
#define NM_MIN      2
#define TIEMPO_MAX  50
#define TIEMPO_MIN  10
#define INFINITO    9999

int bosque[NM_MAX][NM_MAX];

struct TSol {
    int tiempo;
    int camino[NM_MAX];
} Sol, SolOpt;

void genBosque(int, int);
void printBosque(int, int);
void backtracking(int, int, int, int, int, struct TSol, struct TSol*);
void copySol(struct TSol*, struct TSol*, int);
void printSolBack(int);

struct str {
    int valor;
    int yanterior;
};
struct soldinamica {
    struct str sol[NM_MAX][NM_MAX];
    int camino[NM_MAX];
} soldin;
void dinamica(int, int);
void printSolDin(int, int);
int menorEnFila2(struct str[][NM_MAX], int, int, int);


int main(int argc, char** argv) {

    // Generamos el bosque aleatoriamente
    srand(getpid());
    int n, m;
    n = rand() % NM_MAX + NM_MIN;
    m = rand() % NM_MAX + NM_MIN;
    if (n > NM_MAX) n = NM_MAX;
    if (m > NM_MAX) m = NM_MAX;
    genBosque(n, m);
    //Mostramos el bosque generado
    printBosque(n, m);
    //Llamamos al algoritmo Backtracking
    SolOpt.tiempo = INFINITO;
    Sol.tiempo = 0;
    backtracking(0, n, m, 0, m-1, Sol, &SolOpt);
    printSolBack( n);

    /*Para comprobar
        dinamica(n, m);
    printSolDin(n, m);*/

    return (EXIT_SUCCESS);
}

void printSolBack(int n) {
    int i;
    printf("SOLUCION BACKTRACKING (%d minutos)\n", SolOpt.tiempo);
    for (i = 0; i < n; i++) {
        printf("Fila %2d -> Arbol %2d (%3d minutos)\n", i, SolOpt.camino[i], bosque[i][SolOpt.camino[i]]);
    }
}

void backtracking(int fila, int n, int m, int ini, int fin, struct TSol Sol, struct TSol* SolOpt) {
    int j, nini, nfin;
    if (Sol.tiempo < SolOpt->tiempo) { //Podamos si no vamos a conseguir una solucion mejor
        if (fila == n) { //Ya hemos terminado
            copySol(&Sol, SolOpt, n);
        } else {    
            for (j = ini; j <= fin; j++) {
                Sol.camino[fila] = j;
                Sol.tiempo += bosque[fila][j];
                if (j == 0) {
                    nini = 0;
                    nfin = 1;
                } else if (j == m - 1) {
                    nini = m - 2;
                    nfin = m - 1;
                } else {
                    nini = j - 1;
                    nfin = j + 1;
                }
                
                backtracking(fila + 1, n, m, nini, nfin, Sol, SolOpt);
                //Sol.camino[fila] = 0; //Deshacemos
                Sol.tiempo -= bosque[fila][j]; //Deshacemos
            }
        }
    }
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


/* PARA COMPROBAR RESULTADOS


void dinamica(int n, int m) {
    int i, j, y;

    // La primera fila la rellenamos igual
    for (j = 0; j < m; j++) {
        soldin.sol[0][j].valor = bosque[0][j];
    }
    // Ahora el resto de filas
    for (i = 1; i < n; i++) {
        // Rellenamos los extremos j=0 y j=m-1
        soldin.sol[i][0].yanterior = menorEnFila2(soldin.sol, i - 1, 0, 1);
        soldin.sol[i][0].valor = bosque[i][0] + soldin.sol[i - 1][menorEnFila2(soldin.sol, i - 1, 0, 1)].valor;
        soldin.sol[i][m - 1].yanterior = menorEnFila2(soldin.sol, i - 1, m - 2, m - 1);
        soldin.sol[i][m - 1].valor = bosque[i][m - 1] + soldin.sol[i - 1][menorEnFila2(soldin.sol, i - 1, m - 2, m - 1)].valor;
        // Ahora rellenamos las celdas desde 1 hasta m-2
        for (j = 1; j < m - 1; j++) {
            soldin.sol[i][j].yanterior = menorEnFila2(soldin.sol, i - 1, j - 1, j + 1);
            soldin.sol[i][j].valor = bosque[i][j] + soldin.sol[i - 1][menorEnFila2(soldin.sol, i - 1, j - 1, j + 1)].valor;
        }
    }
    // Ahora sacamos el camino
    soldin.camino[n - 1] = menorEnFila2(soldin.sol, n - 1, 0, m - 1);
    y = soldin.sol[n - 1][menorEnFila2(soldin.sol, n - 1, 0, m - 1)].yanterior;
    for (i = n - 2; i >= 0; i--) {
        soldin.camino[i] = y;
        y = soldin.sol[i][y].yanterior;
    }
}

int menorEnFila2(struct str matriz[][NM_MAX], int fila, int ini, int fin) {
    int j, menor = ini;
    for (j = ini + 1; j <= fin; j++) {
        if (matriz[fila][j].valor < matriz[fila][menor].valor) {
            menor = j;
        }
    }
    return menor;
}

void printSolDin(int n, int m) {
    int i;
    printf("\nSOLUCIÓN CON PROGRAMACIÓN DINÁMICA (%3d minutos)\n", soldin.sol[n - 1][menorEnFila2(soldin.sol, n - 1, 0, m - 1)].valor);
    printf("    ||");
    for (j = 0; j < m; j++) {
        printf(" %3d      |", j);
    }
    printf("\n------");
    for (j = 0; j < m; j++) {
        printf("-----------");
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf(" %2d ||", i);
        for (j = 0; j < m; j++) {
            printf(" %3d (%2d) |", soldin.sol[i][j].valor, soldin.sol[i][j].yanterior);
        }
        printf("\n");
    }
    printf("\nb) Resultado (%3d minutos)\n", soldin.sol[n - 1][menorEnFila2(soldin.sol, n - 1, 0, m - 1)].valor);

    for (i = 0; i < n; i++) {
        printf("Fila %2d -> Arbol %2d (%d minutos)\n", i, soldin.camino[i], bosque[i][soldin.camino[i]]);
    }
}*/
