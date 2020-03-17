/*
nb_n.c : Clasificador Naive Bayes usando la aproximacion de funciones normales para features continuos
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
double **mediaTrain;	/* mediaTrain[a][b] contiene la media para el atributo a y la clase b*/
double **deTrain;	/* deTrain[a][b] contiene la desviacióne estándar para el atributo a y la clase b*/

int *seq;            	             		    /* sequencia de presentacion de los patrones*/

/*variables globales auxiliares*/
char filepat[100];
/*bandera de error*/
int error;


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

    probTrain =(double *)calloc(N_Class+1,sizeof(double));
	if(probTrain==NULL)
		return 1;	

    mediaTrain=(double **)calloc(N_IN,sizeof(double *));
    
	for(i = 0; i < N_IN; i++){
		mediaTrain[i] = (double *)calloc(N_Class,sizeof(double));
		if(mediaTrain[i]==NULL) 
			return 1;
	}

    deTrain=(double **)calloc(N_IN,sizeof(double *));

	for(i = 0; i < N_IN; i++){
		deTrain[i] = (double *)calloc(N_Class+1,sizeof(double));		
		if(deTrain[i]==NULL) 
			return 1;
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
    printf("\nNaive Bayes con distribuciones normales:\nCantidad de entradas:%d",N_IN);
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
 /* inicializar: Inicializa las matrices mediaTrain y deTrain en 0 */
/* ------------------------------------------------------------------------*/
void inicializar(){
	int i, j;
	
	for(i = 0; i < N_IN; i++)
		for (j = 0; j < N_Class; i++){
			mediaTrain[i][j] = 0.0;
			deTrain[i][j] = 0.0;
		}
	return ;
}

/* ------------------------------------------------------------------------*/
 /* Función densidad correspondiente a una distribución normal univariable */
/* ------------------------------------------------------------------------*/

double density (double x, double mu, double sigma){
 
	double a,b,c;
	a = sigma * sqrt(2.0 * M_PI);
	b = pow(((x - mu) / sigma), 2.0);
	c = pow(M_E, ( -0.5 * b));
	
	return (1.0/a) * c;
}

/* ------------------------------------------------------------------- */
/*Prob:Calcula la probabilidad de obtener el valor x para el input feature y la clase clase
    Aproxima las probabilidades por distribuciones normales */
/* ------------------------------------------------------------------- */
double prob(double x,int feature,int clase){
	
	return density(x, mediaTrain[feature][clase], deTrain[feature][clase]);    
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
        for(i=0;i<N_IN;i++) {
			//printf("\n Prob %f Clase %d Atributo %d Valor %f",prob( input[i] ,i ,k ),k,i,input[i]);
			prob_de_clase += log( prob( input[i] ,i ,k ) );
		}
		//printf("\n Para la clase %d Atributo %d la probabilidad individual es: %f",k,i,prob_de_clase);
			
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
    double sigma,me;
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


	}	

    /*Calculo media por clase y cada atributo*/
    
	/* Itero en las clases*/
	for (k = 0; k < N_Class; k++){

		/* Itero en los atributos*/
		for(j = 0; j < N_IN; j++){

			cont = 0;

			/* Itero en los patrones*/
			for (patron=0; patron < PR; patron ++) {

				/*nu tiene el numero del patron que se va a presentar*/
				if(usar_seq) 
					nu = seq[patron];
				else                 
					nu = patron;
			
				if(data[nu][N_IN] == k){
					 mediaTrain[j][k] += data[nu][j];
					 cont ++;
				}

			}	
			
			mediaTrain[j][k] = mediaTrain[j][k] / (double) cont;		
				
		}
			
	}	


    /*Calculo desviación estándar por clase y cada atributo*/
	
	/* Itero en las clases*/
	for (k = 0; k < N_Class; k++){

		/* Itero en los atributos*/
		for(j = 0; j < N_IN; j++){
			cont = 0;
			
			/* Itero en los patrones*/
			for (patron=0; patron < PR; patron ++) {
				/*nu tiene el numero del patron que se va a presentar*/
				if(usar_seq) 
					nu = seq[patron];
				else                 
					nu = patron;
			
				if(data[nu][N_IN] == k){
					 deTrain[j][k] += pow(data[nu][j], 2.0);
					 cont ++;
				}

			}	
			
			deTrain[j][k] = deTrain[j][k] / (double) cont;	
			deTrain[j][k] -= pow(mediaTrain[j][k], 2.0);
			deTrain[j][k] = sqrt(deTrain[j][k]);
			printf("\n Clase %d Atributo %d Media: %f DE: %f",k,j,mediaTrain[j][k],deTrain[j][k]);
				
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

