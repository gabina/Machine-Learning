/* Traabajo Práctico 0 - Machine Learning - Ejercicio C - Gabina Luz Bianchi */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Para graficar los espirales utilicé los siguientes comandos en R:

pdf(espirales.pdf")
p <- read.csv('/home/gabina/Facultad/Machine Learning/TP0/espirales.data')
plot(p[,1], p[,2],col=p[,3]+3)
abline(h=0,col="black")
abline(v=0,col="black")
dev.off()

*/


/*La función isValid devuelve 1 en caso de que el punto pasado como argumento pertenezca a la circunferencia de radio 1 y centro en (0,0), y 0 en caso contrario.*/

int isValid (float point[]){
	if ((pow(point[0],2) + pow(point[1],2)) <= 1)
		return 1;
	return 0;	
}

/* La función generator() devuelve un punto aleatorio pertenciente a la circunferencia de radio 1 y centro en (0,0). */

float* generator(){
	int i;
	float* punto;
	punto = (float *) malloc(sizeof(float)*2);

	punto[0] = ((float)rand()/(float)RAND_MAX)- (rand() % 2);
	punto[1] = ((float)rand()/(float)RAND_MAX)- (rand() % 2);
	
	if (isValid(punto))
		return punto;
	generator();
}
	
/* La función cartToPolar convierte un punto desde coordanadas cartesianas a polares */

float* cartToPolar(float point[]){
	float* pointPolar;
	pointPolar = (float *) malloc(sizeof(float)*2);
	/* El componente 0 indica la distancia al origen*/
	pointPolar[0] = sqrt(pow(point[0],2) + pow(point[1],2));

	/* El componente 1 indica el ángulo */
	pointPolar[1] = atan2(point[1],point[0]);

	if(pointPolar[1] < 0)
		pointPolar[1] = pointPolar[1] + 2 * M_PI;
	return pointPolar;
}

/* La función determinateClass devuelve 0 en caso de que el punto pasado como argumento se encuentre entre las curvas
   ro = theta / 4pi y
   ro = (theta + pi) /4pi,
   y devuelve 1 en caso contrario. */

int determinateClass(float point[]){

	float curve0, curve1;

	curve0 = point[1] / (4 * M_PI);
	curve1 = (point[1] + M_PI) / (4 * M_PI);

	if ( curve0 <= point[0] && point[0] <= curve1 )
		return 0;

	curve0 = (2 * M_PI + point[1]) / (4 * M_PI);
	curve1 = (2 * M_PI + point[1] + M_PI) / (4 * M_PI);

	if ( curve0 <= point[0] && point[0] <= curve1 )
		return 0;

	curve0 = (-2 * M_PI + point[1]) / (4 * M_PI);
	curve1 = (-2 * M_PI + point[1] + M_PI) / (4 * M_PI);
	if ( curve0 <= point[0] && point[0] <= curve1 )
		return 0;

	return 1;

}

/* La función createNamesFile crea el archivo "espirales.names" el cual indica las clases y los tipos de las variables*/

void createNamesFile(){
	FILE *fp;
	fp = fopen( "espirales.names", "w");
	fprintf(fp,"%d%c%d\n\n", 0, ',',1);
	fprintf(fp, "X: continuous.\n");
	fprintf(fp, "Y: continuous.\n");	
	fclose(fp);	
}


int main() {
	FILE *fp;
	float *point, *pointPolar;	
	int n, i, cantPoints[2], class;

	createNamesFile();

	srand(time(NULL));
	
	printf("Cantidad de puntos: ");
        scanf("%d",&n);

	if (n % 2 != 0)
		n = n+1;

	cantPoints[0] = 0;
	cantPoints[1] = 0;

	fp = fopen( "espirales.data", "w");


	while (cantPoints[0] < n/2 || cantPoints[1] < n/2){
		/* Genero un punto perteneciente a la circunferencia pedida */
		point = generator();
		
		//printf("X: %f  \n Y: %f \n", point[0],point[1]);

		/* Transformo el punto a coordenadas polares */
		pointPolar = cartToPolar(point);
		
		//printf("R: %f  \n Angulo: %f \n", pointPolar[0],pointPolar[1]);

		/* Determino la clase a la que pertence */
		class = determinateClass(pointPolar);

		//printf("Clase: %d \n", class);
		
		if(cantPoints[class] < n/2){
			fprintf(fp,"%f%c%f%c%d\n", point[0], ',',point[1], ',',class);
			cantPoints[class] = cantPoints[class] + 1;				
		}

	}

	fclose(fp);
	
	
	return 0;
}