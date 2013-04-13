#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NM_MAX      10
#define NM_MIN      5
#define TIEMPO_MAX  50
#define TIEMPO_MIN  10

int bosque[NM_MAX][NM_MAX];

struct pos {
    int i;
    int j;
} p;

struct solucionvoraz {
    int n;
    int sol[NM_MAX];
} solvor;

struct str {
    int valor;
    int yanterior;
};

struct soldinamica {
    struct str sol[NM_MAX][NM_MAX];
    int camino[NM_MAX];
} soldin;

void genBosque(int, int);
void printBosque(int, int);
void voraz(int[][NM_MAX], int, int);
void dinamica(int, int);
int menorEnFila(int[][NM_MAX], int, int, int);
void printSolVoraz();
void printSolDin(int, int);
int menorEnFila2(struct str[][NM_MAX], int, int, int);

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

int main(int argc, char** argv) {

    // Generamos aleatoriamente el bosque
    srand(getpid());
    int n, m;
    n = rand() % NM_MAX + NM_MIN;
    m = rand() % NM_MAX + NM_MIN;
    if (n > NM_MAX) n = NM_MAX;
    if (m > NM_MAX) m = NM_MAX;
    solvor.n = n;
    genBosque(n, m);
    printBosque(n, m);

    voraz(bosque, n, m);
    printSolVoraz();

    dinamica(n, m);
    printSolDin(n, m);

    return (0);
}

// PARTE DINAMICA --------------------------------------------------------------

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
    int i, j;
    printf("\nSOLUCIÓN CON PROGRAMACIÓN DINÁMICA\na) Tabla forward:\n");
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
        printf("Fila %2d -> Arbol %2d (%3d minutos)\n", i, soldin.camino[i], bosque[i][soldin.camino[i]]);
    }
}

//------------------------------------------------------------------------------

// PARTE VORAZ -----------------------------------------------------------------

void voraz(int matriz[][NM_MAX], int n, int m) {
    int i;
    //Elegimos el arbol de menor tiempo de la primera fila
    p.i = 0;
    p.j = menorEnFila(bosque, 0, 0, m - 1);
    solvor.sol[0] = p.j;
    //Para cada fila, elegimos la mejor opcion de entre las posibles
    for (i = 1; i < n; i++) {
        p.i = i;
        if (p.j == 0 || p.j == m - 1) {
            if (p.j == 0) {
                p.j = menorEnFila(bosque, i, p.j, p.j + 1);
            } else {
                p.j = menorEnFila(bosque, i, p.j - 1, p.j);
            }
        } else {
            p.j = menorEnFila(bosque, i, p.j - 1, p.j + 1);
        }
        solvor.sol[i] = p.j;
    }
}

void printSolVoraz() {
    int i, total = 0;
    for (i = 0; i < solvor.n; i++) {
        total += bosque[i][solvor.sol[i]];
    }
    printf("SOLUCION VORAZ (%d minutos)\n", total);
    for (i = 0; i < solvor.n; i++) {
        printf("Fila %2d -> Arbol %2d (%3d minutos)\n", i, solvor.sol[i], bosque[i][solvor.sol[i]]);
    }
}

//Dada una fila, nos devuelve la columna donde se encuentra el elemento menor

int menorEnFila(int matriz[][NM_MAX], int fila, int ini, int fin) {
    int j, menor = ini;
    for (j = ini + 1; j <= fin; j++) {
        if (matriz[fila][j] < matriz[fila][menor]) {
            menor = j;
        }
    }
    return menor;
}
// FIN PARTE VORAZ -------------------------------------------------------------

