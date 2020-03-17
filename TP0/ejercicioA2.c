/* Traabajo Práctico 0 - Machine Learning - Ejercicio A - Gabina Luz Bianchi */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Para graficar los gausianas (d=2, n=200 y C=0.75) utilicé los siguientes comandos en R:

pdf("gausianasA.pdf")
p <- read.csv('/home/gabina/Facultad/Machine Learning/TP0/gausianasA.data')
plot(p[,1], p[,2],col=p[,3]+3)
abline(h=1,col="black")
abline(h=-1,col="black")
abline(v=1,col="black")
abline(v=-1,col="black")
dev.off()

*/

/* Las verificaciones de los valores de la media y la desviación estandar los calculé en R y dieron los siguientes resultados (d=4, n=2000 y C=2.00):

p <- read.csv('/home/gabina/Facultad/Machine Learning/TP0/gausianasA.data')

a <- p[p[,5] == 0,]
a <- a[,-5]

mean(a[,1])
[1] -1.178634
mean(a[,2])
[1] -1.030135
mean(a[,3])
[1] -0.9570348
mean(a[,4])
[1] -1.013055

sd(a[,1])
[1] 4.167347
sd(a[,2])
[1] 3.978574
sd(a[,3])
[1] 3.956285
sd(a[,4])
[1] 3.887374
 
a <- p[p[,5] == 1,]
a <- a[,-5]

mean(a[,1])
[1] 0.8065172
mean(a[,2])
[1] 1.031178
mean(a[,3])
[1] 0.952728
mean(a[,4])
[1] 0.9795515

sd(a[,1])
[1] 3.996575
sd(a[,2])
[1] 4.014656
sd(a[,3])
[1] 4.199054
sd(a[,4])
[1] 3.934165

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
	

/* La función createNamesFile crea el archivo "gausianasA.names" el cual indica las clases y los tipos de las variables*/

void createNamesFile(int d, char name[]){
	FILE *fp;
	int i;	
	fp = fopen( name, "w");
	fprintf(fp,"%d%c%d\n\n", 0, ',',1);
	for(i = 0;i < d; i++)	
		fprintf(fp, "X%d: continuous.\n", i);	
	fclose(fp);	
}


int main() {
	FILE *fp;
	int d, n, i, j, k;
	float  C, sigma;
	float *vector, *mu0, *mu1;
	char *fileName =  malloc(sizeof(char)*20);

	srand(time(NULL));
	        
	/*printf("Dimensión: ");
        scanf("%d",&d);

	printf("Cantidad de puntos: ");
        scanf("%d",&n);

	printf("C: ");
        scanf("%f",&C);*/

	C = 0.5;
	d = 5;
	n = 10000;
	
	if(n % 2 != 0)
		n = n + 1;

	mu0 = (float *) malloc(sizeof(float)*d);
	mu1 = (float *) malloc(sizeof(float)*d);
	vector = (float *) malloc(sizeof(float)*d);


	
	// empezar el for
	
	for (k = 0; k < 5; k++){

		sigma = C * sqrt(d);

		sprintf(fileName,"gausianasA%d.names",k);

		createNamesFile(d, fileName);

		sprintf(fileName,"gausianasA%d.data",k);

		fp = fopen(fileName, "w");
	
		/* Inicializo los arreglos con los mu adecuados según el enunciado del ejercicio*/
		for (i = 0; i < d; i++){
			mu0[i] = -1;
			mu1[i] = 1;
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
		C = C + 0.5;
	}

		
	free(mu0);
	free(mu1);
	free(vector);
	


	return 0;
}
