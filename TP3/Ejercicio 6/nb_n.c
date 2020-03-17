/*
nb_n.c : Clasificador Naive Bayes usando discretización recursiva por mínima entropía
Formato de datos: c4.5
La clase a predecir tiene que ser un numero comenzando de 0: por ejemplo, para 3 clases, las clases deben ser 0,1,2

PMG - Ultima revision: 20/06/2001
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define LOW 1.e-14                                 /*Minimo valor posible para una probabilidad*/
#define PI    3.141592653
#define M 	1			/* equivalent sample size */
#define MAX_BINS 200 /* Máxima cantidad de bins para un atributo */


typedef struct punto{
			double valor;
			int clase;
		} punto;

int N_IN;                     /*Total numbre of inputs*/
int N_Class;                /*Total number of classes (outputs)*/

int PTOT;                     /* cantidad TOTAL de patrones en el archivo .data */
int PR;                         /* cantidad de patrones de ENTRENAMIENTO */
int PTEST;                    /* cantidad de patrones de TEST (archivo .test) */
                                        /* cantidad de patrones de VALIDACION: PTOT - PR*/
                                        
int SEED;                     /* semilla para la funcion rand(). Los posibles valores son:*/
                                        /* SEED: -1: No mezclar los patrones: usar los primeros PR para entrenar
                                                                 y el resto para validar.Toma la semilla del rand con el reloj.
                                                            0: Seleccionar semilla con el reloj, y mezclar los patrones.
                                                         >0: Usa el numero leido como semilla, y mezcla los patrones. */

int CONTROL;                /* nivel de verbosity: 0 -> solo resumen, 1 -> 0 + pesos, 2 -> 1 + datos*/

int N_TOTAL;                                            /*Numero de patrones a usar durante el entrenamiento*/

/*matrices globales    DECLARAR ACA LAS MATRICES NECESARIAS */

double **data;                                         /* train data */
double **test;                                         /* test    data */
int        *pred;                                       /* clases predichas */
double* probTrain;		/*probTrain[k] contiene la probabilidad intrinseca de la clase k*/
punto** traspuesta;  /* data traspuesta sin la columna de clases*/
double *minimo;		/* minimo[a] contiene el valor minimo del atributo a */
double *maximo; 	/* maximo[a] contiene el valor maximo del atributo a */
double **limite;	/* limite[a] es un arreglo que contiene los inicios de cada uno de los bins para el atributo a */
double ***histograma; /* histograma[a][b][c] contiene cuantos puntos del atributo a pertenecientes al bin b son de clase c*/
int *seq;            	             		    /* sequencia de presentacion de los patrones*/
int *cant_bins;			/*Cantidad de bins para cada atributo*/

/*variables globales auxiliares*/
char filepat[100];
/*bandera de error*/
int error;
/*indica la posicion en el arreglo que tiene que usar la funcion minimalEntropy()*/
int posicion;

int constante = 0;

/* -------------------------------------------------------------------------- */
/*define_matrix: reserva espacio en memoria para todas las matrices declaradas.
    Todas las dimensiones son leidas del archivo .nb en la funcion arquitec()    */
/* -------------------------------------------------------------------------- */
int define_matrix(){

    int i,max, j;
    if(PTOT>PTEST) max=PTOT;
    else max=PTEST;

    seq =(int *)calloc(max,sizeof(int));
    pred=(int *)calloc(max,sizeof(int));
    if(seq==NULL||pred==NULL) return 1;
    
    data=(double **)calloc(PTOT,sizeof(double *));
    if(PTEST) 
		test=(double **)calloc(PTEST,sizeof(double *));
    if(data==NULL||(PTEST&&test==NULL)) 
		return 1;

    for(i=0;i<PTOT;i++){
        data[i]=(double *)calloc(N_IN+1,sizeof(double));
	if(data[i]==NULL) return 1;
    }
    for(i=0;i<PTEST;i++){
        test[i]=(double *)calloc(N_IN+1,sizeof(double));
		if(test[i]==NULL) 
			return 1;
    }

/*ALLOCAR ESPACIO PARA LAS MATRICES DEL ALGORITMO*/

	cant_bins = (int*)calloc(N_IN,sizeof(int));

    probTrain =(double *)calloc(N_Class+1,sizeof(double));
	if(probTrain==NULL)
		return 1;	
		
    limite =(double **)calloc(N_IN,sizeof(double*));
	if(limite==NULL)
		return 1;	
	for (i = 0; i < N_IN; i++){
		limite[i] = (double *)calloc(MAX_BINS,sizeof(double));
		if (limite[i] == NULL)
			return 1;
	}
		
    minimo =(double *)calloc(N_IN,sizeof(double));
	if(minimo==NULL)
		return 1;	

    maximo =(double *)calloc(N_IN,sizeof(double));
	if(maximo==NULL)
		return 1;			

	traspuesta = (punto **)calloc(N_IN,sizeof(punto *));
	for(i=0;i<N_IN;i++)
        traspuesta[i]=(punto *)calloc(PTOT,sizeof(punto));    
        
	histograma = (double***)calloc(N_IN,sizeof(double**));	

	for(i = 0; i < N_IN; i++){
		histograma[i] = (double **)calloc(MAX_BINS,sizeof(double*));		
		if(histograma[i]==NULL) 
			return 1;
		for (j = 0; j < MAX_BINS; j++){
			histograma[i][j] = (double *)calloc(N_Class,sizeof(double));		
			if(histograma[i][j]==NULL) 
				return 1;		
		}	
	}        

    return 0;
}
/* ---------------------------------------------------------------------------------- */
/*arquitec: Lee el archivo .nb e inicializa el algoritmo en funcion de los valores leidos
    filename es el nombre del archivo .nb (sin la extension) */
/* ---------------------------------------------------------------------------------- */
int arquitec(char *filename){
    FILE *b;
    time_t t;

    /*Paso 1:leer el archivo con la configuracion*/
    sprintf(filepat,"%s.nb",filename);
    b=fopen(filepat,"r");
    error=(b==NULL);
    if(error){
        printf("Error al abrir el archivo de parametros\n");
        return 1;
    }

    /* Dimensiones */
    fscanf(b,"%d",&N_IN);
    fscanf(b,"%d",&N_Class);

    /* Archivo de patrones: datos para train y para validacion */
    fscanf(b,"%d",&PTOT);
    fscanf(b,"%d",&PR);
    fscanf(b,"%d",&PTEST); 

    /* Semilla para la funcion rand()*/
    fscanf(b,"%d",&SEED);

    /* Nivel de verbosity*/
    fscanf(b,"%d",&CONTROL);

    fclose(b);


    /*Paso 2: Definir matrices para datos y parametros (e inicializarlos) */
    error=define_matrix();
    if(error){
        printf("Error en la definicion de matrices\n");
        return 1;
    }

    /* Chequear semilla para la funcion rand() */
    if(SEED==0) SEED=time(&t);

    /*Imprimir control por pantalla*/
    printf("\nNaive Bayes usando discretización recursiva por mínima entropía:\nCantidad de entradas:%d",N_IN);
    printf("\nCantidad de clases:%d",N_Class);
    printf("\nArchivo de patrones: %s",filename);
    printf("\nCantidad total de patrones: %d",PTOT);
    printf("\nCantidad de patrones de entrenamiento: %d",PR);
    printf("\nCantidad de patrones de validacion: %d",PTOT-PR);
    printf("\nCantidad de patrones de test: %d",PTEST);  
    printf("\nSemilla para la funcion rand(): %d",SEED); 

    return 0;
}
/* -------------------------------------------------------------------------------------- */
/*read_data: lee los datos de los archivos de entrenamiento(.data) y test(.test)
    filename es el nombre de los archivos (sin extension)
    La cantidad de datos y la estructura de los archivos fue leida en la funcion arquitec()
    Los registros en el archivo pueden estar separados por blancos ( o tab ) o por comas        */
/* -------------------------------------------------------------------------------------- */
int read_data(char *filename){

    FILE *fpat;
    double valor;
    int i,k,separador;

    sprintf(filepat,"%s.data",filename);
    fpat=fopen(filepat,"r");
    error=(fpat==NULL);
    if(error){
        printf("Error al abrir el archivo de datos\n");
        return 1;
    }

    if(CONTROL>1) printf("\n\nDatos de entrenamiento:");

    for(k=0;k<PTOT;k++){
        if(CONTROL>1) printf("\nP%d:\t",k);
        for(i=0;i<N_IN+1;i++){
            fscanf(fpat,"%lf",&valor);
            data[k][i]=valor;
            if(CONTROL>1) printf("%lf\t",data[k][i]);
            separador=getc(fpat);
            if(separador!=',') ungetc(separador,fpat);
        }
    }
    fclose(fpat);

    if(!PTEST) return 0;

    sprintf(filepat,"%s.test",filename);
    fpat=fopen(filepat,"r");
    error=(fpat==NULL);
    if(error){
        printf("Error al abrir el archivo de test\n");
        return 1;
    }

    if(CONTROL>1) printf("\n\nDatos de test:");

    for(k=0;k<PTEST;k++){
        if(CONTROL>1) printf("\nP%d:\t",k);
        for(i=0;i<N_IN+1;i++){
            fscanf(fpat,"%lf",&valor);
            test[k][i]=valor;
            if(CONTROL>1) printf("%lf\t",test[k][i]);
            separador=getc(fpat);
            if(separador!=',') ungetc(separador,fpat);
        }
    }
    fclose(fpat);

    return 0;

}
/* ------------------------------------------------------------ */
/* shuffle: mezcla el vector seq al azar.
     El vector seq es un indice para acceder a los patrones.
     Los patrones mezclados van desde seq[0] hasta seq[hasta-1]
     Esto permite separar la parte de validacion de la de train     */
/* ------------------------------------------------------------ */
void shuffle(int hasta){
     double x;
     int tmp;
     int top,select;

     top=hasta-1;
     while (top > 0) {
	x = (double)rand();
	x /= RAND_MAX;
	x *= (top+1);
	select = (int)x;
	tmp = seq[top];
	seq[top] = seq[select];
	seq[select] = tmp;
	top --;
     }
    if(CONTROL>3) {printf("End shuffle\n");fflush(NULL);}
}
/* ------------------------------------------------------------------------*/
 /* inicializar: Inicializa las matrices minimo y maximo en  */
/* ------------------------------------------------------------------------*/
void inicializar(){
	int i;
	
	for(i = 0; i < N_IN; i++){
		minimo[i] = 99999.9;
		maximo[i] = -99999.9;
	}
	return;
}

/* ------------------------------------------------------------------- */
/*trasponer: toma como entrada una matriz de doubles y sus dimensiones 
 *                                                                     */
/* ------------------------------------------------------------------- */
void  trasponer (double** matriz, int cFil, int cCol, punto** trasp){
	int i,j;
	
	for (i = 0; i < cCol; i++)
		for(j = 0; j < cFil; j++){
			(trasp[i][j]).valor = matriz[j][i];
			(trasp[i][j]).clase = matriz[j][cCol];
		}	
	return;

}

/* ------------------------------------------------------------------- */
/*cmpfunc: función para comparar valores en qsort
 *                                                                     */
/* ------------------------------------------------------------------- */
int cmpfunc (const void * a, const void * b)
{
	if( ((punto*)a)->valor > ((punto*)b)->valor )
		return 1;
	else
		return -1;
}
/* ------------------------------------------------------------------- */
/*cmpfunc2: función para comparar valores en qsort
 *                                                                     */
/* ------------------------------------------------------------------- */
int cmpfunc2 (const void * a, const void * b)
{
	if( *(double*)a > *(double*)b)
		return 1;
	else
		return -1;
}


/* ------------------------------------------------------------------- */
/*ordenar : toma como entrada una matriz y la ordena según sus filas
 *                                                                     */
/* ------------------------------------------------------------------- */
void  ordenar (punto** matriz, int cFil, int cCol){
	int i;
		
	for (i = 0; i < cFil; i++)
		qsort(matriz[i], cCol, sizeof(punto), cmpfunc);

	return;
}
/* ------------------------------------------------------------------- */
/* entropy: toma como argumento un arreglo de puntos (valor de la
 * feature y clase) y los indices de inicio y fin.                     *
 * Calcula la entropia de ese conjunto.
 * Hecho para problemas de dos clases                                  */
/* ------------------------------------------------------------------- */
double  entropy (punto* matriz, int inicio, int fin){
	int i;
	double p0=0.0, p1=0.0;
	double log2p0, log2p1;
	
	for(i = inicio; i < fin; i++)
		if(matriz[i].clase)
			p1 = p1 + 1.0;
		else
			p0 = p0 + 1.0;	

	p0 = p0 /(double)(fin-inicio);
	p1 = p1 /(double)(fin-inicio);	
	
	if(p0 > 0.0)
		log2p0 = log(p0)/log(2.0);
	if(p1 > 0.0)	
		log2p1 = log(p1)/log(2.0);	
	
	return -p0 * log2p0 - p1 * log2p1;
}
/* ------------------------------------------------------------------- */
/* calcularK: determina cuantas clases hay en un conjunto */
/* ------------------------------------------------------------------- */
double calcularK (punto* matriz, int inicio, int cant){
	int i, clase;
	int clases[2];
	
	for(i = 0; i<2; i++)
		clases[i] = 0;
	
	for(i = inicio; i < cant; i++){
		clase = matriz[i].clase;
		clases[clase] ++;
	}
	
	if(clases[0] && clases[1])
		return 2.0;
	else
		return 1.0;
		
}

/* ------------------------------------------------------------------- */
/*parada: determina si se cumple el criterio de parada*/
/* ------------------------------------------------------------------- */
int parada(punto* matriz, int inicio, int cant, double E, int finS1, int size){
	
	//if (cant - inicio <= 1 || finS1 - inicio <= 1 || cant - finS1 <= 1)
		//return 1;

	double gain, eS = entropy(matriz, inicio, cant), delta, t;
	double k =  calcularK(matriz,inicio, cant);
	double k1 = calcularK(matriz,inicio, finS1);
	double k2 = calcularK(matriz,finS1, cant);
		
		
	//printf("\nk %f k1 %f k2 %f ",k,k1,k2);	
	gain = eS - E;
	delta = (log(pow(3.0,k)-2.0)/log(2.0)) - (k * entropy(matriz, inicio, cant) - k1 * entropy(matriz, inicio, finS1) - k2 * entropy(matriz, finS1 ,cant)) ;		
	t = (log((double)size-1)/log(2.0)) / (double) size + delta / (double) size;
	 
	printf("\ngain: %f delta %f t %f ",gain,delta,t); 
	 if(gain < t)
		return 1;
	else
		return 0;
	
}
/* ------------------------------------------------------------------- */
/* minimalEntropy: toma como argumento un arreglo de puntos (valor de la
 * feature y clase) y la cantidad de elementos                         */
/* ------------------------------------------------------------------- */
void  minimalEntropy (punto* matriz,int inicio, int cant, int feature, int size){
	int i, l1, l2, minFin, fin;
	double E, minE;

	printf("\n Busco entre %d y %d Tamaño %d", inicio, cant, size);

	if(posicion == MAX_BINS)
		return ;
	
	if(size <= 1)
			return;
	
	/*S1 va desde matriz[inicio] hasta matriz[fin-1]
	 * S2 va desde matriz[fin] hasta matriz[cant-1] */
	
	fin = inicio+1;

	/* Calculo la primera partición */
	/* Determino los cardinales de los conjuntos */
	l1 = fin - inicio;
	l2 = cant - l1;
		
	/* class information entropy of the partition induced by T*/
	E = ((double) l1 / (double) size)  * entropy(matriz, inicio, fin) + ((double) l2 / (double) size) * entropy(matriz, fin, cant);
	minE = E;	
	minFin = fin;

	while( fin < cant - 1){
		/* Actualizo fin */
		fin ++;		
		
		/* Determino los cardinales de los conjuntos */
		l1 = fin - inicio;
		l2 = size - l1;
		
		/* class information entropy of the partition induced by T*/
		E = ((double) l1 / (double) size) * entropy(matriz, inicio, fin) + ((double) l2 / (double) size) * entropy(matriz, fin, cant);
		
		if(E < minE){
				minE = E;
				minFin = fin;
		}

	}
	
	printf("\n min elegido %f %d", matriz[minFin].valor, minFin);
	
	printf("\nPrimer bin: ");
	for(i = inicio; i <minFin;i++)
		printf("%d ",matriz[i].clase);
	printf("\nSegundo bin: ");
	for(i = minFin; i <cant;i++)
		printf("%d ",matriz[i].clase);	
	
	if( ! parada(matriz, inicio, cant, minE, minFin, size)){
		printf("\n MINFIN ELEGIDO: %d %f ",minFin,matriz[minFin].valor);
		limite[feature][posicion] = matriz[minFin].valor;
		posicion++;
		//printf("\nPosicion: %d", posicion);			
		minimalEntropy (matriz, inicio, minFin, feature, minFin - inicio);
		minimalEntropy(matriz, minFin, cant, feature, cant - minFin);	
	 }
			
	return;
}

/* ------------------------------------------------------------------- */
/*Prob:Calcula la probabilidad de obtener el valor x para el input feature y la clase clase
    Construye histogramas */
/* ------------------------------------------------------------------- */
double prob(double x,int feature,int clase){
	double extr_izq, extr_der;
	int i;
		
		/* Encuentro limites del bin al cual pertenece */
		for (i = 0; i < cant_bins[feature] - 1; i++){
			extr_izq = limite[feature][i];
			extr_der = limite[feature][i+1];
			if (x >= extr_izq && x <= extr_der)
				return histograma[feature][i][clase];
		}

}

/* ------------------------------------------------------------------------------ */
/*output: calcula la probabilidad de cada clase dado un vector de entrada *input
    usa el log(p(x)) (sumado)
    devuelve la de mayor probabilidad                                             */
/* ------------------------------------------------------------------------------ */
int output(double *input){
     	

    double prob_de_clase;
    double max_prob=-1e40;
    int i,k,clase_MAP;
    
    for(k=0;k<N_Class;k++) {
        prob_de_clase=0.;

        /*calcula la probabilidad de cada feature individual dada la clase y la acumula*/
        for(i=0;i<N_IN;i++) 
			prob_de_clase += log( prob( input[i] ,i ,k ) );

        /*agrega la probabilidad a priori de la clase*/
        prob_de_clase += log(probTrain[k]);

        /*guarda la clase con prob maxima*/
        if (prob_de_clase>=max_prob){
            max_prob=prob_de_clase;
            clase_MAP=k;
        }
    }
    
    return clase_MAP;
}
/* ------------------------------------------------------------------------------ */
/*propagar: calcula las clases predichas para un conjunto de datos
    la matriz S tiene que tener el formato adecuado ( definido en arquitec() )
    pat_ini y pat_fin son los extremos a tomar en la matriz
    usar_seq define si se accede a los datos directamente o a travez del indice seq
    los resultados (las propagaciones) se guardan en la matriz seq                                    */
/* ------------------------------------------------------------------------------ */
double propagar(double **S,int pat_ini,int pat_fin,int usar_seq){

    double mse=0.0;
    int nu;
    int patron;
    
    for (patron=pat_ini; patron < pat_fin; patron ++) {

     /*nu tiene el numero del patron que se va a presentar*/
        if(usar_seq) nu = seq[patron];
        else                 nu = patron;

        /*clase MAP para el patron nu*/
        pred[nu]=output(S[nu]);

        /*actualizar error*/
        if(S[nu][N_IN]!=(double)pred[nu]) mse+=1.;
    }
        

    mse /= ( (double)(pat_fin-pat_ini));

    if(CONTROL>3) {printf("End prop\n");fflush(NULL);}

    return mse;
}

/* --------------------------------------------------------------------------------------- */
/*train: ajusta los parametros del algoritmo a los datos de entrenamiento
                 guarda los parametros en un archivo de control
                 calcula porcentaje de error en ajuste y test                                                                            */
/* --------------------------------------------------------------------------------------- */
int train(char *filename){

    int i,j,k,feature,clase;
  	int nu;
	int patron, cont;
	int usar_seq = 0;       	
	float prob = 0.0;
    double sigma,me, extr_izq, extr_der;
    double train_error,valid_error,test_error;
    FILE *salida,*fpredic;

    /*Asigno todos los patrones del .data como entrenamiento porque este metodo no requiere validacion*/
    N_TOTAL=PTOT;
    
    /*N_TOTAL=PR; si hay validacion*/
    for(k=0;k<PTOT;k++) 
		seq[k]=k;    /* inicializacion del indice de acceso a los datos */

    /*efectuar shuffle inicial de los datos de entrenamiento si SEED != -1 (y hay validacion)*/
    if(SEED>-1 && N_TOTAL<PTOT){
        srand((unsigned)SEED);        
        shuffle(PTOT);
        usar_seq = 1;
    }

    /*Calcular probabilidad intrinseca de cada clase para train*/

	for (k = 0; k < N_Class; k++){

		for (patron=0; patron < PR; patron ++) {

			/*nu tiene el numero del patron que se va a presentar*/
			if(usar_seq) 
				nu = seq[patron];
			else                 
				nu = patron;
		
			if(data[nu][N_IN] == k)
				probTrain[k] += 1.0/(double) PR;		
			
		}
		//printf("Clase %d prob a priori %f",k,probTrain[k]);
	}	

	/* Traspongo el data train, y lo trasnsformo en una matriz de estructuras punto*/
	trasponer(data, PTOT, N_IN, traspuesta);


	/* Ordeno cada fila respecto al campo valor */
	ordenar(traspuesta,N_IN,PTOT);

	/* Calculo limites para cada atributo */
	for(i = 0; i < N_IN; i++){
		limite[i][0] = traspuesta[i][0].valor;
		posicion = 1;
		minimalEntropy(traspuesta[i], 0, PR, i, PR);
		limite[i][posicion] = traspuesta[i][PR-1].valor;
		cant_bins[i] = posicion + 1;
	}
	
	/* Ordeno los límites */
	for(i = 0; i < N_IN; i++)
		qsort(limite[i], cant_bins[i], sizeof(double), cmpfunc2);

	/* Imprimo los limites */
	for (i = 0; i < N_IN; i++){
		printf("\n");
		for(j = 0; j < cant_bins[i]; j++)
			printf("%f ",limite[i][j]);
		}

	/* Itero en los atributos */
	for(i = 0; i < N_IN; i++){
		/* Itero en los bins */
		for (j = 0; j < cant_bins[i]-1; j++){
			/*Itero en las clases */
			for (k = 0; k < N_Class; k++){
				/*Itero en los patrones*/
				for (patron=0; patron < PR; patron ++) {
					extr_izq = limite[i][j];
					extr_der = limite[i][j+1];
					/* Si el punto se encuentra entre los dos extremos y pertenece a la clase k+1 */	
					if (data[patron][i]	>= extr_izq && data[patron][i] <= extr_der && data[patron][N_IN] == k){
						/*Acumulo la cantidad de puntos de esa clase en ese bin */
						histograma[i][j][k] += 1.0;
					}
					}
				/* Sumo +1 correspondiente a mp */
				histograma[i][j][k] += 1.0;
				/* Divido por n + m*/
				histograma[i][j][k] /= ((double) PR * probTrain[k] + M);	
				}
			}
		}
		
  /*calcular error de entrenamiento*/
    train_error=propagar(data,0,PR,1);
    
    /*calcular error de validacion; si no hay, usar mse_train*/
    if(PR==PTOT) 
		valid_error=train_error;
    else
		valid_error=propagar(data,PR,PTOT,1);
    
    /*calcular error de test (si hay)*/
    if (PTEST>0) 
		test_error =propagar(test,0,PTEST,0);
    else
		test_error =0.;
    
    /*mostrar errores*/
    printf("\nFin del entrenamiento.\n\n");
    printf("Errores:\nEntrenamiento:%f%%\n",train_error*100.);
    printf("Validacion:%f%%\nTest:%f%%\n",valid_error*100.,test_error*100.);
    if(CONTROL) fflush(NULL);

    /* archivo de predicciones */
    sprintf(filepat,"%s.predic",filename);
    fpredic=fopen(filepat,"w");
    error=(fpredic==NULL);
    if(error){
        printf("Error al abrir archivo para guardar predicciones\n");
        return 1;
    }
    for(k=0; k < PTEST ; k++){
        for( i = 0 ;i< N_IN;i++) fprintf(fpredic,"%f,",test[k][i]);
        fprintf(fpredic,"%d\n",pred[k]);
    }
    fclose(fpredic);	


								
	
    return 0;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
int main(int argc, char **argv){

    if(argc!=2){
        printf("Modo de uso: nb <filename>\ndonde filename es el nombre del archivo (sin extension)\n");
        return 0;
    }
    		
    /* defino la estructura*/
    error=arquitec(argv[1]);
    if(error){
        printf("Error en la definicion de parametros\n");
        return 1;
    }
 
	
    /* leo los datos */
    error=read_data(argv[1]);                                 
    if(error){
        printf("Error en la lectura de datos\n");
        return 1;
    }
  
        
  /* ajusto los parametros y calcula errores en ajuste y test*/
  error=train(argv[1]);                     
  if(error){
    printf("Error en el ajuste\n");
    return 1;
  }

    return 0;

}
/* ----------------------------------------------------------------------------------------------------- */

