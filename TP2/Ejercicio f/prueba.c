#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define CANT 45



/* ------------------------------------------------------------------------------ */
/*propagar: calcula los valores de salida de la red para un conjunto de datos
  la matriz S tiene que tener el formato adecuado ( definido en arquitec() )
  pat_ini y pat_fin son los extremos a tomar en la matriz
  usar_seq define si se accede a los datos directamente o a travez del indice seq
  los resultados (las propagaciones) se guardan en la matriz seq                  */
/* ------------------------------------------------------------------------------ */
float propagar2(float x3[CANT], float S[CANT], int CCLAS){

  int i,patron,nu;
  float discrete_error=0.;
  
  /* Variables que se utilizan para calcular la clase a la cual corresponde un valor */
  float j, clas, min;
  FILE *fprueba;
  
  fprueba = fopen("prueba","w");
  
  for (patron= 0; patron < CANT; patron ++) {

	min = 99.9;

		/* Busco a qué clase corresponde el resultado obtenido*/  
		for (j = 0.0; j < CCLAS; j = j + 1.0){
			printf("j= %f %f ",j, fabs (x3[patron] - j));
			if (fabs (x3[patron] - j) < min){
				min = (fabs (x3[patron] - j));
				clas = j;
			}
		}
		printf("J definitivo: %f \n", clas);
		/* Comparo la clase obtenida por mi resultado con el punto real*/
			if (fabs (clas - S[patron]) > 0.5)
				discrete_error += 1.0;
			fprintf(fprueba, "%f ",S[patron]);		
			fprintf(fprueba, "%f \n",clas);	
	}
  
    
 
  discrete_error /= (float) (45);
  return discrete_error;
}


/*
 * sed -r 's/.{1}$//' iris.predic > iris2
 * sed -r 's/.{36}//' iris2 > iris3
 * 
 * */
int main(){
	
	float X[CANT];
	float S[CANT];
	int i;
	
	printf("Ingrese los números: \n");
	for (i =0; i < 45; i++)
		scanf("%f ", &X[i]);
	
	for (i = 0; i < 15; i++)
		S[i] = 0.;
	
	for (i = 15; i < 30; i++)
		S[i] = 1.;
		
	for (i = 30; i < 45; i++)
		S[i] = 2.;			
	
	printf("%f ", propagar2(X,S,3));
	return 0;
}
