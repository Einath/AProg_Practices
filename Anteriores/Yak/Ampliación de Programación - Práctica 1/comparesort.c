#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static unsigned long t;

int v11[10000], v21[100000], v31[1000000];
int v12[10000], v22[100000], v32[1000000];
int v13[10000], v23[100000], v33[1000000];

void insercionDirecta(int);
void shell(int);
void quicksort(int*,int*);
void swap(int*,int*);

int main(){

    /* Generamos las matrices aleatoriamente */
    int i;
    for(i = 0; i < 1000000; i++){
        v31[i] = v32[i] = v33[i] = rand();
        if(i < 100000) v21[i] = v22[i] = v23[i] = rand();
        if(i < 10000) v11[i] = v12[i] = v13[i] = rand();
    }
    
    /* Llamamos a las funciones de ordenacion e imprimimos lo que tardan */
    printf("--------------------------------------------------------------------------------\n");
    /* 10000 elementos */
    t = clock();
    quicksort(&v13[0],&v13[10000-1]);
    t = clock() - t;
    printf("Quicksort (  10000 elementos):\t\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    shell(10000);
    printf("Metodo Shell (  10000 elementos):\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    insercionDirecta(10000);
    printf("Insercion directa (  10000 elementos):\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    
    printf("--------------------------------------------------------------------------------\n");
    /*100000 elementos */
    t = clock();
    quicksort(&v23[0],&v23[100000-1]);
    t = clock() - t;
    printf("Quicksort ( 100000 elementos):\t\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    shell(100000);
    printf("Metodo Shell ( 100000 elementos):\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    insercionDirecta(100000);
    printf("Insercion directa ( 100000 elementos):\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    
    printf("--------------------------------------------------------------------------------\n");
    /* 1000000 elementos  */
    t = clock();
    quicksort(&v33[0],&v33[1000000-1]);
    t = clock() - t;
    printf("Quicksort (1000000 elementos):\t\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    shell(1000000);
    printf("Metodo Shell (1000000 elementos):\t %.5f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
    insercionDirecta(1000000);
    printf("Insercion directa (1000000 elementos):\t %.3f segundos (%.5f minutos)\n",(t*1.0)/CLOCKS_PER_SEC,((t*1.0)/CLOCKS_PER_SEC)/60);
	
	return 0;
}

void insercionDirecta(int n){
    int* vector;
    int i,j,v;
    switch(n){
        case 10000:
            vector = v11;
            break;
        case 100000:
            vector = v21;
            break;
        case 1000000:
            vector = v31;
            break;
    }
    t = clock();
    for(i = 1; i < n; i++){
        v = *(vector + i);
        j = i - 1;
        while((j >= 0) && *(vector + j) > v){
            *(vector + (j+1)) = *(vector + j);
            j--;
        }
        *(vector + (j+1)) = v;
    }
    t = clock() - t;
}

void shell(int n){
    int* vector;
    int k, subarray, i, j, v;
    switch(n){
        case 10000:
            vector = v12;
            break;
        case 100000:
            vector = v22;
            break;
        case 1000000:
            vector = v32;
            break;
    }
    t = clock();
    k = n/2;
    while(k >= 1){
        for(subarray = 0; subarray < k; subarray++){
            for(i = k + subarray; i < n; i += k){
                v = *(vector + i);
                j = i - k;
                while(j >= 0 && *(vector + j) > v){
                    *(vector + j + k) = *(vector + j);
                    j -= k;
                }
                *(vector + j + k) = v;
            }
        }
        k = k/2;
    }
    t = clock() - t;
}

void quicksort(int* izq, int* der){
    
    if(der<izq) return;
	int pivot=*izq;
	int* ult=der;
	int* pri=izq;
 
	while(izq<der)
	{
		while(*izq<=pivot && izq<der+1) izq++;
		while(*der>pivot && der>izq-1) der--;
		if(izq<der) swap(izq,der);
	}
	swap(pri,der);
	quicksort(pri,der-1);
	quicksort(der+1,ult);
	
}
 
void swap(int* a, int* b){
	int temp=*a;
	*a=*b;
	*b=temp;
}



