/* Traabajo Práctico 0 - Machine Learning - Ejercicio A - Gabina Luz Bianchi */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CANT_PUNTOS 2000
#define DIM 4


float getDistance( float vector[DIM], float mu[DIM]){
	float dist = 0;
	int i;
	
	for ( i = 0; i < DIM; i++)
		dist = dist + pow((vector[i] - mu[i]), 2.0);
		
	return pow(dist, 0.5);
}

int getClass (float vector[DIM], float mu0[DIM],float mu1[DIM]){
	float dist0 = getDistance(vector, mu0);
	float dist1 = getDistance(vector, mu1);
	
	if (dist0 < dist1)
		return 0;
	else if (dist1 < dist0)
			return 1;
		else
			return (int) (rand() % 2);	

}



int main() {
	FILE *fp;
	FILE *readfp;
	int d, n, i, j;
	float  C, sigma;
	float *vector, *mu0, *mu1;

	d = DIM;

	srand(time(NULL));
	
	fp = fopen( "clasificacionIdealA.test", "w");
	readfp = fopen( "gausianasA.test", "r");
	
	mu0 = (float *) malloc(sizeof(float)*d);
	mu1 = (float *) malloc(sizeof(float)*d);
	vector = (float *) malloc(sizeof(float)*d);
	
		
	/* Inicializo los arreglos con los mu adecuados según el enunciado del ejercicio*/
	for (i = 0; i < d; i++){
		mu0[i] = -1;
		mu1[i] = 1;
	}


	for (i = 0; i < CANT_PUNTOS; i++){
		for ( j = 0; j < d; j++){
			fread(vector+j, 1, 1, readfp);
			printf("%f \n",vector[j]);
			fprintf(fp,"%f%c", vector[j], ',');
		}
		//fprintf(fp, "%d\n", getClass(vector, mu0, mu1));


	}

	fclose(fp);

	free(mu0);
	free(mu1);
	free(vector);


	return 0;
}
