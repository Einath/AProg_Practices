#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX_FICHAS  20
#define MIN_FICHAS  4
#define MAX_COLORES 10
#define MIN_COLORES 2
#define SI          0
#define NO          1
#define COLOR       99
#define NUMERO      98
#define COMPUTADOR  1
#define USUARIO     -1

//enum colores {ROJO, VERDE, AZUL, AMARILLO, NARANJA, VIOLETA, ROSA, MAGENTA};

struct jugada{
    int tipoQuitar;
    int cualQuitar;
    int ganadora;
};

struct ficha{
    int color;
    int numero;
    int cogida;
};

void mejorMovimiento(struct ficha[], int, int, int, struct jugada*);
int terminado(struct ficha[], int);
void printSituacion(struct ficha[], int);
void quitarUnColor(struct ficha[], int, int);
void quitarUnNumero(struct ficha[], int, int);
void cambiarJugador(int*);
int pertenece(struct ficha[], int, int, int);
void copia(struct ficha*, struct ficha*, int);
void printResultado(int gan);

int main(int argc, char* argv[]){
    int N, nColores, i, nNumeros;
    struct ficha juego[MAX_FICHAS];
    srand(getpid()); char buffer1[10]; int buffer2[1];
    /* Si el numero de fichas y colores se introduce con argumentos los cogemos
     * en caso contrario generamos esos 2 valores aleatoriamente */
    if(argc == 4){
        N = atoi(argv[1]); if(N > MAX_FICHAS) N = MAX_FICHAS;
        nColores = atoi(argv[2]); if(nColores > MAX_COLORES) nColores = MAX_COLORES;
        nNumeros = atoi(argv[3]); if(nNumeros > MAX_COLORES) nNumeros = MAX_COLORES;
    } else printf("El formato debe ser: ./game <numFichas> <numColores> <numNumeros>\n");
    
    /* Generamos aleatoriamente un juego, a partir de los números de colores y
     * de números introducidos. */
    for(i = 0; i < N; i++){
        juego[i].numero = rand() % nNumeros;
        juego[i].color = rand() % nColores; 
        juego[i].cogida = NO;
    }
    
    /* Mostramos el tablero */
    printf("N = %d, nColores = %d, nNumeros = %d\n",N, nColores, nNumeros);
    printSituacion(juego, N);
    printf("---\n");

    struct jugada mejorJugada;
    mejorJugada.ganadora = NO;
    mejorJugada.tipoQuitar = -1;
    mejorJugada.cualQuitar = -1;
    
    while(terminado(juego, N) == NO){
        printf("\nJUGADOR: Es tu turno, introduce lo siguiente: \"quitar [color/numero] [valor]\"\n");
        scanf("quitar %s %d\n", buffer1, buffer2);
        printf("Resultado de quitar el %s %d:\n", buffer1, buffer2[0]);
        if(strcmp(buffer1, "color")==0){
            quitarUnColor(juego, N, buffer2[0]);
        }else{
            quitarUnNumero(juego, N, buffer2[0]);
        }
        printSituacion(juego, N);
        mejorMovimiento(juego, N, nColores, nNumeros, &mejorJugada);
        if(terminado(juego, N) == NO){
            if(mejorJugada.tipoQuitar==COLOR){
                quitarUnColor(juego, N, mejorJugada.cualQuitar);
            }else{
                quitarUnNumero(juego, N, mejorJugada.cualQuitar);
            }
            printf("\nCOMPUTADOR (%d): Movimiento realizado: quitar el %s %d\n", mejorJugada.ganadora, (mejorJugada.tipoQuitar==NUMERO)?("numero"):("color"), mejorJugada.cualQuitar);
            printSituacion(juego,N);
            if(mejorJugada.ganadora == NO) printf("Vaya!, ahora lo tienes muy facil...\n");
            if(terminado(juego, N) == SI) printResultado(NO);
        }else{
            printResultado(SI);
        }
        
    }
    
    /*
    mejorMovimiento(juego, N, nColores, nNumeros, &mejorJugada);
    printf("Jugada %s: Quitar %s %d\n", (mejorJugada.ganadora == SI)?("ganadora"):("no ganadora"), (mejorJugada.tipoQuitar == COLOR)?("color"):("numero"), mejorJugada.cualQuitar);
    */
    
    return 0;
}
/* Funcion que selecciona un movimiento ganador */
void mejorMovimiento(struct ficha situacion[], int n, int numColores, int numNumeros, struct jugada* j){
    
    int i; struct ficha situacion2[n]; struct jugada jugada2; jugada2.ganadora = NO;
    
    /* Miramos si estamos en un caso base */
    if(terminado(situacion, n) == SI){
        j->ganadora = NO; /* El jugador anterior gano */
    } else {
        /* Recorremos todas las posibilidades para quitar un numero */
        for(i = 0, j->ganadora = NO; i < numNumeros && j->ganadora == NO; i++){
            if(pertenece(situacion, n, NUMERO, i) == SI){
                copia(situacion, situacion2, n);
                quitarUnNumero(situacion2, n, i);
                //printf("SITUACION NUEVA: Quitar numero %d \n", i); printSituacion(situacion2, n);
                mejorMovimiento(&situacion2[0], n, numColores, numNumeros, &jugada2);
                j->tipoQuitar = NUMERO;
                j->cualQuitar = i;
                if(jugada2.ganadora == NO){ //Si la jugada que dejamos es perdedora, nosotros ganamos
                    j->ganadora = SI;
                }
            }
        }
        /* ahora con los colores */
        for(i = 0; i < numColores && j->ganadora == NO; i++){
            if(pertenece(situacion, n, COLOR, i) == SI){
                copia(situacion, situacion2, n);
                quitarUnColor(situacion2, n, i);
                //printf("SITUACION NUEVA: Quitar color %d \n", i); printSituacion(situacion2, n);
                mejorMovimiento(situacion2, n, numColores, numNumeros, &jugada2);
                j->tipoQuitar = COLOR;
                j->cualQuitar = i;
                if(jugada2.ganadora == NO){
                    j->ganadora = SI;
                }
            }
        }
    }
}

int terminado(struct ficha situacion[], int n){
    int gan = SI, i;
    for(i = 0; i < n && gan == SI; i++){
        if(situacion[i].cogida == NO) gan = NO;
    }
    return gan;
}

void copia(struct ficha* situacion, struct ficha* copia, int n){
    int i;
    for(i = 0; i < n; i++){
        copia[i].numero = situacion[i].numero;
        copia[i].color = situacion[i].color;
        copia[i].cogida = situacion[i].cogida;
    }
}

void printSituacion(struct ficha situacion[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("[%c] Ficha %2d: Color = %2d, Numero = %2d\n", (situacion[i].cogida == SI)?('X'):(' '), i, situacion[i].color, situacion[i].numero);
    }
}

void quitarUnColor(struct ficha situacion[], int n, int color){
    int i;
    for(i = 0; i < n; i++){
        if(situacion[i].color == color) situacion[i].cogida = SI;
    }
}

void quitarUnNumero(struct ficha situacion[], int n, int numero){
    int i;
    for(i = 0; i < n; i++){
        if(situacion[i].numero == numero) situacion[i].cogida = SI;
    }
}

int pertenece(struct ficha situacion[], int n, int tipo, int valor){
    int i, esta = NO;
    for(i = 0; i < n; i++){
        if((situacion[i].cogida == NO) && ((tipo == COLOR && situacion[i].color == valor) || (tipo == NUMERO && situacion[i].numero == valor))) esta = SI;
    }
    return esta;
}

void printResultado(int gan){
    printf("-------------------------\n");
    if(gan == NO){
        printf("|      HAS PERDIDO      |\n");
    }else{
        printf("|       HAS GANADO      |\n");
    }
    printf("-------------------------\n");
}
