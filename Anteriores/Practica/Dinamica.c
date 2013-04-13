/*Problema de monedas

c=8	1	2	3	4	5	6	7	8

m1	1	1+1	1*3	1*4	1*5	1*6	1*7	1*8

m4	1	1+1	1*3	4	4+1	4+1+1	4+1*3	4*2

m6	1	1+1	1*3	4	4+1	6	6+1	4+4(*)

(*)
6+1+1 vs 4+4

Si CandidatoActual > Cantidad -> CasillaSuperior
SiNo
	Mejor{CasillaSuperior, MonedaActual+Casilla(Subproblema)}


Problema de la mochila

Capacidad=15
i=0..2
Beneficio(38, 40, 24)
Pesos(9, 6, 5)

Voraces:

Criterio primer candidato: Mejor relación Beneficio/Peso

i=1,2,0 

40 64 |78
6  11 |15


Dinámica

	1    2    3    4    5    6    7    8    9    10    11    12    13    14    15     

Ob1(9)  0 ...               0    0    0    0    38   38    38    38    38    62    78

Ob2(6)  0 ...               0    40   40   40   40   40    64    64    64    62    78

Ob3(5)  0 ...               24   40   40   40   40   40(*) 64    64    64    64    78


(*)
No se puede meter dos veces el mismo objeto (24+24 incorrecto)

(2,11),(3,11),...= 64 = 40+24

(1,14) = 38+24 = 62

(1,15) = 78 = 38+40
*/

  RecurDin(SolParcial, etapaK)


