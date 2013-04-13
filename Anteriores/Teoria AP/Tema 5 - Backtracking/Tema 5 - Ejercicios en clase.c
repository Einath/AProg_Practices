/*22-III-2011

Ejercicio 11.
Fig 1

Apartado a)

*Asignar a Personas un trabajo
test de fracaso: No se puede asignar a una persona un trabajo ya asignado. 
generación de descendientes: una persona puede realizar cualquier trabajo

libre[] si el trabajo ha sido asignado (true/false)
*/
tsolucion
  coste
  persona[N]


			     

void AsignaA( int k, int libre[] , int t[][], tsolucion *sol, tsolucion *solopt){

  if (k==n){
     if(sol->coste < solopt->coste)
        *solopt=*sol;
  }
  else{
    for(i=0; i<n; i++)
      if(libre[i]){
	libre[i]=FALSE;
	sol->Persona[k]=i;
	sol->coste+=t[i][k];

	AsignaA(k+1, -----);
    //Si no está libre, deshacemos para la siguiente iteración
	libre[i]=TRUE;
	sol->coste=tik;
      }
}

  //inicializacion

  for(i=0; i<N; i++) 
    libre[i]=TRUE;
 sol.coste=0;
 soloptima.coste= -INFINITO;
 // Lamada inicial
 AsignaA(0, libre, t, $sol, &solopt); 
}

//Asignar trabajos a personas

 
void AsignaT(int k, int libre[], int t[][], tsol *sol, tsol *solopt){

  if(sol->coste < solopt->coste) //comprobar si la solución tiene futuro
    if(k==n)
      *solopt=*sol;
    else
      for(p=0; p<n; p++)
	if(libre[p]){
	  libre[p]=FALSE;
	  sol-> trabajo[k]=p; 
	  sol->coste+=tkp;
	  AsignaT(k+1,----);
	  //Deshacer
	  libre[p]=TRUE;
	  sol->coste-=tkp;
	}
}

/*Apartado b)

Etapa k = asignar trabajo k a una persona
fin cuando se asignan todos los trabajos
no hay restricciones para asignar trabajos a personas. 

Mismo código sin el vector libre[].
*/	     	     

/*Apartado c)

como en a) minimizando el tiempo de trabajos.
Todos los trabajadores comienzan simultáneamente
El coste será el máximo entre los trabajos realizados puesto que empiezan 
todos trabajando simultáneamente.

Etapa k: qué persona realiza el trabajo k
*/

void AsignaC(int k, int libre[], int t[][], tsolucion *sol, tsolucion *solopt){

  if(sol->coste < solopt -> coste)
    if(k==n)
      *solopt=*sol;
    else{
      for(p=0; p<n; p++)
	if (libre[p]){
	  libre[p]=FALSE;
	  Aux=sol->coste; //para deshacer
	  sol->coste=max(sol_coste,tkp);
	  Asignac(k+1, ----,);
	  //Deshacemos para la siguiente iteración
	  libre[p]=TRUE;
	  sol->coste=Aux;
	}
    }
}

/* Ej 12 -> para el jueves
   Ej 6, 7, 22*/

/*Ejercicio 22 (fig 2)

Etapa k: 
- ¿Qué objeto metemos? o bien
- ¿En qué bolsa metemos el objeto k? <-

Generación de descendientes
- El objeto k lo meteremos en una de las bolsas ya utilizadas o en una nueva

Fin: habiendo colocado todos los objetos (etapa n, para n objetos)

Test de fracaso: Si el objeto no entra en la bolsa.
*Test de optimalidad

- El código está en campusvirtual



*/

typedef struct{
  int num;
  vector envases; //envases [i]= envase en el que metemos el objeto i
}Solucion: 


/* Ejercicio 6
(Fig 3)

Etapa k: asignar el trabajo k a un procesador (supuestos los trabajos anteriores ya están asignados)


Test fracaso: 


Test solución: Todos los trabajos están asignados


Gen descendientes: 

*/

/*t0,t1 tiempos consumidos en proc 0 y proc 1*/
void 2ProcBack(int k, int t0, int t1, int t[2][N], tsolucion *sol, tsolucion *solopt){

  if(k==n){
    sol->coste = max(t0,t1);
    if(sol->coste < solopt->coste)
      *solopt=*sol;
  }
  else{
    //hacerlo en proc 0
    sol->trabajo[k]=0;
    2ProcBack(k+1, t0+t[0][k], t1, --------);
    //hacerlo en proc 1
    sol-trabajo[k]=1;
    2ProcBack(k+1, t0, t1+t[1][k], ----); 
  }
}

//llamada inicial

2ProcBack(0, 0, 0, -----);
//Código en campusvirtual 

// mejora de la solución
void 2ProcBack(int k, int t0, int t1, int t[2][N], tsolucion *sol, tsolucion *solopt){

  sol->coste=max(t0,t1); //comprobamos si la solución tiene futuro
  if(sol->coste < solopt->coste){
    if(k==n)
      *solopt=*sol;
  }
  else
    [...]

      }

/* M procesadores 

etapa k: decidimos el procesador en el que realicamos el trabajo k  (supuestos los k-1)
test solución: k=n
(ver fotocopias)

Prog dinámica

Dink(t0,t1)=min{Dink+q(t0+t0k, t1), Dink+1(t0, t1+t1k)}



*/
/*Jueves -> Ejercicio 76

Etapa K: Elegir qué casa visitar
Test de solución: visitar mientras tengamos tiempo.
Test de fracaso: 
  tvw + tw +
v------------w
   tw0 +t0 < T

t'uw= tvw+tw
ir y visitar

t'vw t'w0 <=T

Generación de Descendientes: No iremos a una casa que ya esté visitada y tampoco si no nos da tiempo a regresar al aeropuerto.
- controlaremos si hemos visitado o no la casa con un vector de Booleanos. 

Solución: 

struct
  - long (número de casas que he visitado)
  - camino[] (las casas que he visitado)

Nota:

-Puedes elegir poner como última solución el regreso al aeropuerto
-tvw: Tiempo para ir de v a w + tiempo de hacer la visita

 */


void VisitasBack(int v, int TDisponible, int visitado[], int t[][],tsolucion *sol, tsolucion *opt){

  if (SinTiempoVisitas(v, TDisponible, Visitados, t))
    if(sol->long > solopt -> long)
      *solopt = *sol;
    else
      for(w=1; w<N; w++){
	if (!Visitado[w] && ((tvw+tw0)<=TDisponible)){
	  Visitado[w]=true;
	  Sol->long++; // se iniciará a -1
	  sol->camino[sol-long]=w; //sol->cam[++sol->long]=w; o sol->cam[sol->long++]=w 

	  VisitasBack(w,TDisponible-tvw,-----------);
  //Deshacer
	  Visitado[w]=FALSE;
	  Sol->long -;
	}
      }
}

//Inicialización
/*
sol.long = -1;
solopt.long=-INFINITO;

VisitasBack(0, ---------- &sol, &solopt);

visitados[w]=FALSE; visitados[0]=TRUE
1<=w<N
*/

   int SinTiempoVisitas(){
     for(w=1; w<N; w++)
       if(!Visitado[w] && (tvw+tw0 <=TDisponible))
	 return FALSE;
     return TRUE;
   }




//versión 2.0


void VisitasBack(int v, int TDisponible, int visitado[], int t[][],tsolucion *sol, tsolucion *opt){
  if(sol->long>solopt->long) // siempre intentamos prolongar
    *solopt=*sol;
  for(w=1; w<N; w++){
	if (!Visitado[w] && ((tvw+tw0)<=TDisponible)){
	  Visitado[w]=true;
	  Sol->long++; // se iniciará a -1
	  sol->camino[sol-long]=w; //sol->cam[++sol->long]=w; o sol->cam[sol->long++]=w 

	  VisitasBack(w,TDisponible-tvw,-----------);
  //Deshacer
	  Visitado[w]=FALSE;
	  Sol->long -;
	}
  }
}


// Versión en Programación Dinámica
/*
Viajante(v,W,T) = max{1+Viajante(w, W-{w}, T - tvw)}


  e={w€W,
     tvw+tw0 <=T}

Si C=0
  Viajante(v,W,T)=0
*/


void VisitasDin(int v, int TDisponible, int visitados[], int t[][], tsolucion *solopt){//atrás
  tsolucion solpar, solmejor;
  int w;
  if (SinTiempoVisitas(v, TDisponible, visitados, t)) Solopt->Long=-1;
  else{
    solmejor.Long= - 1; // o -Inifnito, 0
    for(w=1; w<N; w++)
      if(!Visitado[w] && ((tvw + tw0) <= TDisponible)){
	vistado[w]=TRUE;
	VisitasDin(w, TDisponible -tvw, visitados, t, &solpar);
	solpar.Long ++;
	solpar.cam[solpar.Long]=w;
	if (solpar.Long > solmejor.Long)
	  solmejor=solparc;
      }
    *solopt=solmejor;
  }
}
// Pos1 -> la última casa que he visitado... etc.

//version 2.0


void VisitasDin(int v, int TDisponible, int visitados[], int t[][], tsolucion *solopt){//atrás
  tsolucion solpar, solmejor;
  int w;
 
 
    solmejor.Long= - 1; // o -Inifnito, 0
    for(w=1; w<N; w++)
      if(!Visitado[w] && ((tvw + tw0) <= TDisponible)){
	vistado[w]=TRUE;
	VisitasDin(w, TDisponible -tvw, visitados, t, &solpar);
	solpar.Long ++;
	solpar.cam[solpar.Long]=w;
	if (solpar.Long > solmejor.Long)
	  solmejor=solparc;
      }
    *solopt=solmejor;
}


///////////28-III-2011////////////

/*Control el día 12 (o el 5 omfg)*/
/*Hasta lo que veamos en esta semana*/


/*La vuelta del caballo: Tablero 8x8 casillas. El caballo debe visitar todas las casillas sin pasar dos veces por la misma. Casilla de inicio = casilla de fin. 
-Etapak: Decidir la k-esima casilla del recorrido, supuesto que ya tengamos recorridos los anteriores.
-Condición de fin: cuando el caballo ha recorrido todas las casillas, sin repetir, acabando donde comenzó.(La primera es accesible desde la última)
* Dimensión n; n². Etapas 0 - n²
-Test de error: Las casillas no estén visitadas.

-Solución: un vector de soluciones. [ | | | | | ]
           - Otra forma de hacerlo es numerar las casillas que vamos visitando. 
*/


void VueltaBack(int k, tcasilla Cas, int N, int Tab[Dim][Dim]){
  /*En la posición Cas hemos anotado k-1 
    Casilla de partida: cualquiera*/
  if(k==N*N){/*falta comprobar si puede llegar a la casilla inicial*/
    if(Accesible(cas,Tab,N))
      Salida(Tab,N);
  }
  else{
    for(i-2, i<=2; i++)
      for(j=-2; j<=2; j++){
	if(abs(i)+abs(j)==3){
	  NCas=Casilla(Cas.Fila+i, Cas.Columna+j);
	  if(Admisible(NCas,Tab,N)){
	    Tab[Ncas.Fila][NCas.Columna]=k;
	    VueltaBack(k+1, NCas, N, Tab);
	  }
	}
      }
  }
}


int Admisible(TCas Cas, int Tab, int N){
  if Dentro(Cas, N) /*Y no está visitada*/
      return Tab[Cas.Fila]þCas.Columna]==-1;
 else
   return FALSE;
}

int Accesible(TCas Cas, int Tab[][], int N){ /*Eliminar el doble return*/
  for(i=-2; i<=2; i++)
    for(j=-2; j<=2; j++){
      Nas=Casilla(Cas.Fila+i, Cas.columna+j);
      if((abs(i)+abs(j)==3) && Dentro(NCas,N))
	if(Tab[NCas.Fila][NCas.Columna]==0)
	  return TRUE;/**/
    }
  return FALSE;/**/
}

int Dentro(TCas cas, int N){
  return ((Cas.Fila >=0) && (Cas.Fila<N) && (Cas.Columna >=0) && (Cas.Columna < N));
}

/*
1)Existe una variante del problema del caballo en la que se da la restricción de visitar (no necesariamente de manera consecutiva) una serie de casillas en orden.

(Implementarlo voluntariamente semana que viene)


2)Dadas dos casillas (origen y destino) hallar el camino mínimo entre ellas
Test de fracaso: 
-Si la solución hallada es peor que la óptima que tenemos, falla. 
-Si la casilla ya está visitada, falla. 

Marcamos la casilla origen: 0
Marcamos las casillas accesibles desde ahí(origen + 1 paso): 1
Marcamos las casillas accesibles desde primer paso: 2
... etc

(Implementarlo voluntariamente antes del jueves)

3) Todos los caminos mínimos que nos llevan desde el origen hasta el destino


 */

 
   ///////// 29-III-2011 //////



