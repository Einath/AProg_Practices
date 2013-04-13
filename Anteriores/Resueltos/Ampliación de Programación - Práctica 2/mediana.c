#include <stdio.h>
#include <stdlib.h>
#define DIM 100

void quicksort(int*, int*);
void swap(int*, int*);
double mediana2(int*, int, int*, int);
double mediana(int*, int);
void printv(int*, int n);

int contador = 0;

int main(){

    int i=0, v1[DIM], v2[DIM], n1, n2; double solucion;
    
    printf("Introduce los elementos del primer vector, separados por espacios, y pulsa Ctrl+D para terminar:\n");
    while(scanf("%d",(v1 + i++))!=EOF){}
    n1 = i-1;
    quicksort(&v1[0],&v1[n1-1]);
    i = 0;
    printf("Introduce los elementos del segundo vector, separados por espacios, y pulsa Ctrl+D para terminar:\n");
    while(scanf("%d",(v2 + i++))!=EOF){}
    n2 = i-1;
    quicksort(&v2[0],&v2[n2-1]);
    
    printf("\n");
    
    if(n2 > n1){
        solucion = mediana2(v2,n2,v1,n1);
    }else{
        solucion = mediana2(v1,n1,v2,n2);
    }
    
    printf("\n-------------------------------------------\n");
    printf("Solucion: la mediana de la mezcla es %.2f\n",solucion);
    printf("----------------------------------------------\n");
    
    /* PARA COMPROBAR LOS RESULTADOS */
    printf("\n----------------------PARA DEPURAR -------------------------\n\n");
    printf("* Vector 1: "); printv(v1,n1);
    printf("  n=%d\n",n1);
    printf("  Mediana v1: %.2f\n",mediana(&v1[0],n1));
    printf("* Vector 2: "); printv(v2,n2);
    printf("  n=%d\n",n2);
    printf("  Mediana v2: %.2f\n",mediana(&v2[0],n2));
    
    int v[n1+n2];
    for(i = 0; i < n1; i++) v[i] = v1[i];
    for(i = n1; i < n2 + n1; i++) v[i] = v2[i-n1];
    
    printf("* Mezcla: "); printv(v,n1+n2);
    quicksort(&v[0],&v[n1+n2-1]);
    printf("  Mezcla ordenada: "); printv(v,n1+n2);
    
    printf("  Mediana (para comprobar): %.2f\n", mediana(v,n1+n2)); 
    printf("------------------------------------------------------------\n\n");

    return 0;
}

double mediana2(int* ini1, int n1, int* ini2, int n2){
    
    printf("Vuelta: %d\n\n",contador++);
    printv(ini1,n1);
    printv(ini2,n2);
    
    double m;
    if(n2==1){ /* ------------------------------------------------------------*/
        if(n1 == 1){ /* Ambos vectores tienen un solo elemento */
            m = (ini1[0]+ini2[0])/2.0;
            printf("Caso base: cada vector tiene 1 elemento\n");
        }else{ /* El segundo vector tiene 1 elemento y el primero no */
            printf("Caso base: uno de los vectores tiene un solo elemento\n");
            if(n1%2==0){ /* n1 es par */
                if(*(ini2) <= mediana(ini1,n1)){ /* Va a la izquierda de la mediana */
                    if(*(ini2) < *(ini1 + n1/2 - 1)){ /* Va a la izda del anterior a la mediana */
                        m = *(ini1 + n1/2 - 1);
                    }else{ /* Va pegado a la izquierda de la mediana */
                        m = *(ini2);
                    }
                }else{ /* Va a la derecha de la mediana */
                    if(*(ini2) > *(ini1 + n1/2)){ /* Va a la drecha del posterior a la mediana */
                        m = *(ini1 + n1/2);
                    }else{ /* Va pegado a la drcha de la mediana */
                        m = *(ini2);
                    }
                }
            }else{ /* n1 es impar */
                if(*(ini2) <= mediana(ini1,n1)){ /* Va a la izquierda de la mediana */
                    if(*(ini2) < *(ini1 + n1/2 - 1)){ /* Va a la izda del anterior a la mediana */
                        m = (*(ini1 + n1/2)+*(ini1 + n1/2 - 1))/2.0;
                    }else{ /* Va pegado a la izquierda de la mediana */
                        m = (*(ini2)+*(ini1 + n1/2))/2.0;
                    }
                }else{ /* Va a la derecha de la mediana */
                    if(*(ini2) > *(ini1 + n1/2 + 1)){ /* Va a la derecha del elemento posterior a la mediana */
                        m = (*(ini1 + n1/2)+*(ini1 + n1/2 + 1))/2.0;
                    }else{ /* Va pegado a la mediana por la derecha */
                        m = (*(ini2)+*(ini1 + n1/2))/2.0;
                    }
                }
            }
        }
    }else{ /* -------------------------------------------------------------- */
        if(n2==2){ /* El vector mas corto es de 2 elementos, y el mas largo de 2 o mas */
            if(n1==2){ /* Ambos vectores tienen 2 elementos */
            printf("Caso base: Ambos vectores tienen 2 elementos\n");
                if(ini1[0] > ini2[1]) m = (ini1[1]+ini2[0])/2.0;
                else if(ini2[1] <= ini1[0]) m = (ini1[0] + ini2[1])/2.0;
                else if(ini2[0] <= ini1[0] && ini2[1] >= ini1[1]) m = mediana(ini1,n1);
                else if(ini2[0] >= ini1[0] && ini2[1] <= ini1[1]) m = mediana(ini2,n2);
                else if(ini2[0] <= ini1[0] && ini2[1] <= ini1[1]) m = (ini2[1]+ini1[0])/2.0;
                else if(ini2[0] >= ini1[0] && ini2[1] >= ini1[1]) m = (ini1[1]+ini2[0])/2.0;
            }else{
                printf("Caso base: uno de los vectores alcanza los 2 elementos\n");
                if(n1%2==0){ /* El vector grande es par */
                
                    if(ini2[0] <= ini1[n1/2-1] && ini2[1] >= ini1[n1/2]){
                        m = mediana(ini1,n1);
                    }else if(ini2[0] >= ini1[n1/2-1] && ini2[1] <= ini1[n1/2]){
                        m = mediana(ini2,n2);
                    }else if(ini2[1] <= ini1[n1/2-1] && ini2[1] >= ini1[n1/2-2]){
                        m = (ini1[n1/2-1]+ini2[1])/2.0;
                    }else if(ini2[0] >= ini1[n1/2] && ini2[0] <= ini1[n1/2+1]){
                        m = (ini2[0] + ini1[n1/2])/2.0;
                    }else if(ini2[1] <= ini1[n1/2-2]){
                        m = (ini1[n1/2-1]+ini1[n1/2-2])/2.0;
                    }else if(ini2[0] >= ini1[n1/2+1]){
                        m = (ini1[n1/2]+ini1[n1/2+1])/2.0;
                    }
                }else{ /* El vector grande es impar */
                    if(ini2[0] <= mediana(ini1,n1)){
                        if(ini2[1] > mediana(ini1,n1)){
                            m = mediana(ini1,n1);
                        }else{
                            if(ini2[1] < ini1[n1/2 - 1]){
                                m = ini1[n1/2 - 1];
                            }else{
                                m = ini2[1];
                            }
                        }
                    }else{
                        if(ini2[0] > ini1[n1/2 + 1]){
                            m = ini1[n1/2 + 1];
                        }else{
                            m = ini2[0];
                        }
                    }
                }
            }
        }else{ /* CASO GENERAL. LLAMADA RECURSIVA --------------------------- */
            printf("No se da un caso base. Se realizara llamada recursiva.\n\n");
            double m1 = mediana(ini1,n1);
            double m2 = mediana(ini2,n2);
            /* Recordemos que al llegar a esta funcion, ini2 es el vector mas pequeno */
            int quitados = 0;
            
            if(n2%2==0){ /* El vector pequeno es par */
                quitados = n2/2 - 1;
            }else{ /* El vector pequeno es impar */
                quitados = n2/2;
            }
            
            if(m1 > m2){
                m = mediana2(ini1,n1-quitados,ini2+quitados,n2-quitados);
            }else{
                if(m1 == m2){
                    m = m1;
                }else{ /* m1 < m2 */
                    m = mediana2(ini1+quitados,n1-quitados,ini2,n2-quitados);
                }
            }
        }
    }
    
    return m;
}

/* FUNCION QUE CALCULA LA MEDIANA DE UN VECTOR */
double mediana(int* ini, int n){
    if(n%2 == 0){ /* vector par */
        return (ini[n/2] + ini[n/2 - 1])/2.0;
    }else{ /* vector impar */
        return ini[n/2];
    }
}

/* FUNCION DE ORDENACION QUICKSORT */
void quicksort(int* izq, int* der){
    
    if(!(der < izq)){
	    int pivot = *izq;
	    int* ult = der;
	    int* pri = izq;
 
	    while(izq<der){
		    while(*izq <= pivot && izq < der+1) izq++;
		    while(*der > pivot && der > izq-1) der--;
		    if(izq < der) swap(izq,der);
	    }
	    swap(pri,der);
	    quicksort(pri,der-1);
	    quicksort(der+1,ult);
	}
}
void swap(int* a, int* b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

/* FUNCION QUE IMPRIME VECTORES */
void printv(int* ini,int n){
    int i;
    printf("| ");
    for(i=0; i<n; i++) printf("%d | ", ini[i]);
    printf("\n");
}
