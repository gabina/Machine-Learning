/* Traabajo Práctico 0 - Machine Learning - Ejercicio C - Gabina Luz Bianchi */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Para graficar los espirales utilicé los siguientes comandos en R:

pdf("datosE.pdf")
p <- read.csv('/home/gabina/Facultad/Machine Learning/TP4/Ejercicio e/datosE.data')
plot(p[,1], p[,2],col=p[,3]+3)
dev.off()

*/


/*La función getClase devuelve 1 en caso de que el punto pasado como argumento pertenezca a la circunferencia, 0 en otro caso */

int getClass (float point[]){
	if ( abs(point[0]*10) % 2 == 1 && abs(point[1]*10) % 2 == 1)
		return 1;
	return 0;	
}

/* La función generator() devuelve un punto aleatorio pertenciente al cuadrado de lado 1 y centro en (0,0). */

float* generator(){
	int i;
	float* punto;
	punto = (float *) malloc(sizeof(float)*2);

	punto[0] = ((float)rand()/(float)RAND_MAX)- (rand() % 2);
	punto[1] = ((float)rand()/(float)RAND_MAX)- (rand() % 2);

	return punto;
}
	

int main() {
	FILE *fp;
	float *point;	
	int n, i, class;

	srand(time(NULL));
	
	printf("Cantidad de puntos: ");
        scanf("%d",&n);

	if (n % 2 != 0)
		n = n+1;

	fp = fopen( "datosE.data", "w");

	for(i = 0; i < n; i++){
		point = generator();
		class = getClass(point);
		fprintf(fp,"%f%c%f%c%d\n", point[0], ',',point[1], ',',class);	
	}

	fclose(fp);
	
	
	return 0;
}
