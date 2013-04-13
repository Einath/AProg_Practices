#include <stdio.h>

#define ARBOLEDA 0
#define CULTIVO 1
#define GANADO 2

double Beneficios(double Ganado, double Cosecha, double Arboleda, double BG, double BC, double BA){
  double resul;
  resul=((Ganado*BG) + (Cosecha * BC) + (Arboleda * BA));
  return resul;
}
int max(double A, double C, double G){
  int resul; 

  if((A>C) && (A>G))
    resul=ARBOLEDA;
  if((C>A) && (C>G))
    resul=CULTIVO;
  if((G>A) && (G>C))
    resul=GANADO;

  return resul;
}

void main(){
  FILE *fichero;
  char cad[2], tipo[2];
  double Tipo[3], BTipo[3];
  int valor=-1, i,compra=-1;
  double NG, NC, NA, G0, C0, A0, BG, BC, BA, PG, PC, PA;
  double G, C, A, Ben, auxA,auxC,auxG, actual, BAmA, BAmC, BAmG, BenTotal, P, AmA, AmC, AmG;
  int N, Pinic, maximo;
  if((fichero=fopen("DatosP3Granja.txt", "r"))==NULL)
    printf("Error al abrir fichero\n");
  else
    printf("\nFichero de datos abierto\n");

  printf("Teclee el presupuesto inicial\n");
  scanf("%d",&Pinic);
  printf("Teclee el número de temporadas\n");
  scanf("%d",&N);
  P=Pinic;
  printf("P: %5.2f\tN: %d\n\n", P, N);
  
  while(!feof(fichero)){
    fscanf(fichero, "%c%c\t %d\n",&cad[0], &cad[1],&valor);
    if(cad[0]=='N'){
      if(cad[1]=='G')
	NG=valor;
      if(cad[1]=='C')
	NC=valor;
      if(cad[1]=='A')
	NA=valor;
    }
    if(cad[0]=='B'){
      if(cad[1]=='G')
	BG=valor;
      if(cad[1]=='C')
	BC=valor;
      if(cad[1]=='A')
	BA=valor;
    }
    if(cad[0]=='P'){
      if(cad[1]=='G')
	PG=valor;
      if(cad[1]=='C')
	PC=valor;
      if(cad[1]=='A')
	PA=valor;
    }
    if(cad[1]=='0'){
      if(cad[0]=='G')
	G0=valor;
      if(cad[0]=='C')
	C0=valor;
      if(cad[0]=='A')
	A0=valor;
    }
  }

  /*Datos iniciales*/

  /*Amortizaciones*/
  AmA=PA/BA;
  if((AmA -(int)AmA)>=0) 
    AmA++;
  AmC=PC/BC;
  if((AmC-(int)AmC)>=0)
    AmC++;
  AmG=PG/BG;
  if((AmG-(int)AmG)>=0)
    AmG++;

  BenTotal=0;

  Ben=Beneficios(G0, C0, A0, BG, BC, BA);
  printf("Estado inicial:\nArboleda: %5.2f\nCosecha: %5.2f\nGanado: %5.2f\nBeneficio: %5.2f\nPresupuesto Inicial: %d\n\n", A0, C0, G0, Ben, Pinic);
  
  for(i=1; i<=N; i++){

    BAmA=BA*(N-i) -(BG*0.5*(N-i)) -PA;
    BAmC=BC*(N-i) -(BA*0.5*(N-i)) -PC;
    BAmG=BG*(N-i) -(BC*0.5*(N-i)) -PG;

 /*Si no podemos comprar arboleda (porque no hay zona de ganado) no tenemos en cuenta si éste es el beneficio mayor*/

    if((G0==0) || (BAmA<0))
      BAmA=0;
    if((A0==0) || (BAmC<0))
      BAmC=0;
    if((C0==0) || (BAmG<0))
      BAmG=0;

    maximo=max(BAmA, BAmC, BAmG);

    /*Seleccionamos la compra*/

    if((NA>0) && (G0>=0.5) && (P >= PA) && (maximo==ARBOLEDA)){
      auxA=Beneficios(G0-0.5, C0, A0+1, BG, BC, BA);
      if(auxA>Ben){
	compra=ARBOLEDA;
	Ben=auxA;
      }
    }
    if((NC>0) && (A0 >=0.5) && (P>= PC) && (maximo==CULTIVO)){
      auxC=Beneficios(G0, C0+1, A0-0.5, BG, BC, BA);
      if(auxC>Ben){
	compra=CULTIVO;
	Ben=auxC;
      }
    }
    if((NG>0) && (C0 >=0.5) && (P>= PG) && (maximo==GANADO)){
      auxG=Beneficios(G0+1, C0-0.5, A0, BG, BC, BA);
      if(auxG>Ben){
	compra=GANADO;
	Ben=auxC;
      }
    }

    /*Realizamos cálculos*/

    if(compra==ARBOLEDA){
      A0=A0+1;
      G0=G0-0.5;
      P=P-PA;
      printf(">>>>>>>Compra -> ARBOLEDA\n\n");
    }
    if(compra==CULTIVO){
      A0=A0-0.5;
      C0=C0+1;
      P=P-PC;
      printf(">>>>>>>Compra -> COSECHA\n\n");
    }
    if(compra==GANADO){
      G0=G0+1;
      C0=C0-0.5;
      P=P-PG;
      printf(">>>>>>>Compra -> GANADO\n");
    }
    if(compra==-1)
      printf(">>>>>>>No se realiza compra\n\n");

    P=P+Ben;
    BenTotal=BenTotal+Ben;

    printf("\nTEMPORADA %d:\n==========\n", i);

    printf("Arboleda: %5.2f\n", A0);
    printf("Cosecha: %5.2f\n", C0);
    printf("Ganado: %5.2f\n", G0);
    printf("Presupuesto: %5.2f\n", P);
    printf("Beneficio total acumulado: %5.2f\n", BenTotal);
    printf("Beneficio mensual: %5.2f\n\n", Ben);

    compra = -1;
  }
  fclose(fichero);
}


/*
Para P=20 y N=8 el Pfinal debe ser 372 aprox

Beneficios a la larga máx


Criterio 1

(Bcompro - 0.5Belimino)/Precio

Criterio 2 (criterio seleccionado)

Bcom*Ntemp - Belim*0.5*Ntem -Preciocompro

*/
