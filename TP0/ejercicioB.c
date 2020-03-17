/* Traabajo Práctico 0 - Machine Learning - Ejercicio B - Gabina Luz Bianchi */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Para graficar los gausianas (2 dimensiones) utilicé los siguientes comandos en R:

pdf("gausianasB.pdf")
p <- read.csv('/home/gabina/Facultad/Machine Learning/TP0/gausianasB.data')
plot(p[,1], p[,2],col=p[,3]+3)
abline(h=0,col="black")
abline(v=1,col="black")
abline(v=-1,col="black")
dev.off()

*/

/* Las verificaciones de los valores de la media y la desviación estandar los calculé en R y dieron los siguientes resultados (d=4, n=2000 y C=2.00):

p <- read.csv('/home/gabina/Facultad/Machine Learning/TP0/gausianasB.data')

a <- p[p[,5] == 0,]
a <- a[,-5]

mean(a[,1])
[1] 0.9326239
mean(a[,2])
[1] -0.0383418
mean(a[,3])
[1] -0.06748256
mean(a[,4])
[1] -0.04684477

sd(a[,1])
[1] 4.037719
sd(a[,2])
[1] 4.001625
sd(a[,3])
[1] 4.171101
sd(a[,4])
[1] 3.97831

a <- p[p[,5] == 1,]
a <- a[,-5]

mean(a[,1])
[1] -1.041233
mean(a[,2])
[1] 0.03431923
mean(a[,3])
[1] -0.07378244
mean(a[,4])
[1] -0.006900543

sd(a[,1])
[1] 3.966273
sd(a[,2])
[1] 3.904087
sd(a[,3])
[1] 4.107264
sd(a[,4])
[1] 4.031949

 */


/* Función densidad correspondiente a una distribución normal univariable */

double density (float x, float mu, float sigma){
	double a,b,c;
	a = sigma * sqrt(2 * M_PI);
	b = pow(((x - mu) / sigma), 2);
	c = pow(M_E, ( -0.5 * b));
	
	return (1/a) * c;
}

/* La función isValid() retorna 1 si el punto debe formar parte de la distribución normal y 0 en caso contrario */

int isValid (float point, float prob, float mu, double sigma){
	if ( prob <  density(point, mu, sigma))
		return 1;
	return 0;	
}

/* La función generatePoint() toma como argumento un mu y un sigma, y devuelve un punto perteneciente a una distribución normal de acuerdo a los parámetros*/

float generatePoint(float mu, float sigma){
	float point, prob;

	point = ((float)rand()/(float)RAND_MAX)*10*sigma + (mu - 5*sigma);
	prob = ((float)rand()/(float)RAND_MAX) * (1/(sqrt(2*M_PI) * sigma));

	if (isValid(point, prob, mu, sigma))
		return point;
	generatePoint(mu, sigma);
}

/* La función generateVector() toma como argumento un arreglo de floats representando los distintos mu, un sigma y una dimensión d, y retorna un arreglo de d puntos pertenecientes a una distribución normal con sigma y mu adecuados */

float* generateVector(float mu[], float sigma, int d){
	int i;
	float* point;
	point = (float *) malloc(sizeof(float)*d);

	for(i = 0; i < d; i++)
		point[i] = generatePoint(mu[i],sigma); 
	
	return point;

}
	

/* La función createNamesFile crea el archivo "gausianasB.names" el cual indica las clases y los tipos de las variables*/

void createNamesFile(int d){
	FILE *fp;
	int i;	
	fp = fopen( "gausianasB.names", "w");
	fprintf(fp,"%d%c%d\n\n", 0, ',',1);
	for(i = 0;i < d; i++)	
		fprintf(fp, "X%d: continuous.\n", i);	
	fclose(fp);	
}


int main() {
	FILE *fp;
	int d, n, i, j;
	float  C, sigma;
	float *vector, *mu0, *mu1;

	srand(time(NULL));
	        
	printf("Dimensión: ");
        scanf("%d",&d);

	printf("Cantidad de puntos: ");
        scanf("%d",&n);

	printf("C: ");
        scanf("%f",&C);

	createNamesFile(d);
	
	if(n % 2 != 0)
		n = n + 1;

	mu0 = (float *) malloc(sizeof(float)*d);
	mu1 = (float *) malloc(sizeof(float)*d);
	vector = (float *) malloc(sizeof(float)*d);

	sigma = C;

	fp = fopen( "gausianasB.data", "w");
	
	/* Inicializo los arreglos con los mu adecuados según el enunciado del ejercicio*/
	mu0[0] = 1;
	mu1[0] = -1;
	for (i = 1; i < d; i++){
		mu0[i] = 0;
		mu1[i] = 0;
	}


	for (i = 0; i < n/2; i++){
		vector = generateVector(mu0, sigma, d);
		for ( j = 0; j < d; j++){
			fprintf(fp,"%f%c", vector[j], ',');
			//printf("%f ", vector[j]);		
		}
		fprintf(fp, "%d\n", 0);

		vector = generateVector(mu1, sigma, d);
		for ( j = 0; j < d; j++){
			fprintf(fp,"%f%c", vector[j], ',');
			//printf("%f ", vector[j]);		
		}
		fprintf(fp, "%d\n", 1);


	}

	fclose(fp);

	free(mu0);
	free(mu1);
	free(vector);


	return 0;
}
