/*
knn.c: algoritmo k vecinos más cercanos.
La clase a predecir tiene que ser un numero comenzando de 0: por ejemplo, para 3 clases, las clases deben ser 0,1,2
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define LOW 1.e-14		/*Minimo valor posible para una probabilidad */
#define PI    3.141592653

typedef struct punto{
	int clase;
	double distancia;
} punto;

int N_IN;			/*Total numbre of inputs */
int N_Class;		/*Total number of classes (outputs) */
int PTOT;			/* cantidad TOTAL de patrones en el archivo .data */
int PR;				/* cantidad de patrones de ENTRENAMIENTO */
int PTEST;			/* cantidad de patrones de TEST (archivo .test) */
					/* cantidad de patrones de VALIDACION: PTOT - PR */
int SEED;			/* semilla para la funcion rand(). Los posibles valores son: */
					/* SEED: -1: No mezclar los patrones: usar los primeros PR para entrenar
					   y el resto para validar.Toma la semilla del rand con el reloj.
					   0: Seleccionar semilla con el reloj, y mezclar los patrones.
					   >0: Usa el numero leido como semilla, y mezcla los patrones. */
					   
int CONTROL;		/* nivel de verbosity: 0 -> solo resumen, 1 -> 0 + pesos, 2 -> 1 + datos */
int N_TOTAL;		/*Numero de patrones a usar durante el entrenamiento */
int N_NEIG;			/* cantidad de vecinos a considerar*/

/*matrices globales    DECLARAR ACA LAS MATRICES NECESARIAS */

double **data;		/* train data */
double **test;		/* test    data */
int *pred;			/* clases predichas */
int *seq;			/* sequencia de presentacion de los patrones */
punto *dist;       /* distancia de un punto a cada punto de entrenamiento*/

/*variables globales auxiliares*/
char filepat[100];
/*bandera de error*/
int error;
/* -------------------------------------------------------------------------- */
/*define_matrix: reserva espacio en memoria para todas las matrices declaradas.
    Todas las dimensiones son leidas del archivo .nb en la funcion arquitec()    */
/* -------------------------------------------------------------------------- */
int
define_matrix ()
{

  int i, max, j;
  if (PTOT > PTEST)
    max = PTOT;
  else
    max = PTEST;

  seq = (int *) calloc (max, sizeof (int));
  pred = (int *) calloc (max, sizeof (int));
  if (seq == NULL || pred == NULL)
    return 1;

  data = (double **) calloc (PTOT, sizeof (double *));
  if (PTEST)
    test = (double **) calloc (PTEST, sizeof (double *));
  if (data == NULL || (PTEST && test == NULL))
    return 1;

  for (i = 0; i < PTOT; i++)
    {
      data[i] = (double *) calloc (N_IN + 1, sizeof (double));
      if (data[i] == NULL)
	return 1;
    }
  for (i = 0; i < PTEST; i++)
    {
      test[i] = (double *) calloc (N_IN + 1, sizeof (double));
      if (test[i] == NULL)
	return 1;
    }

/*ALLOCAR ESPACIO PARA LAS MATRICES DEL ALGORITMO*/
  dist = calloc(PR, sizeof(punto)); 

  return 0;
}

/* ---------------------------------------------------------------------------------- */
/*arquitec: Lee el archivo .nb e inicializa el algoritmo en funcion de los valores leidos
    filename es el nombre del archivo .nb (sin la extension) */
/* ---------------------------------------------------------------------------------- */
int
arquitec (char *filename)
{
  FILE *b;
  time_t t;

  /*Paso 1:leer el archivo con la configuracion */
  sprintf (filepat, "%s.nb", filename);
  b = fopen (filepat, "r");
  error = (b == NULL);
  if (error)
    {
      printf ("Error al abrir el archivo de parametros\n");
      return 1;
    }

  /* Dimensiones */
  fscanf (b, "%d", &N_IN);
  fscanf (b, "%d", &N_Class);

  /* Archivo de patrones: datos para train y para validacion */
  fscanf (b, "%d", &PTOT);
  fscanf (b, "%d", &PR);
  fscanf (b, "%d", &PTEST);
  
  /* Cantidad de vecinos */
  fscanf (b, "%d", &N_NEIG);

  /* Semilla para la funcion rand() */
  fscanf (b, "%d", &SEED);

  /* Nivel de verbosity */
  fscanf (b, "%d", &CONTROL);

  fclose (b);


  /*Paso 2: Definir matrices para datos y parametros (e inicializarlos) */
  error = define_matrix ();
  if (error)
    {
      printf ("Error en la definicion de matrices\n");
      return 1;
    }

  /* Chequear semilla para la funcion rand() */
  if (SEED == 0)
    SEED = time (&t);

  /*Imprimir control por pantalla */
  printf
    ("\nK vecinos más cercanos\nCantidad de atributos:%d",
     N_IN);
  printf ("\nCantidad de clases:%d", N_Class);
  printf ("\nArchivo de patrones: %s", filename);
  printf ("\nCantidad total de patrones: %d", PTOT);
  printf ("\nCantidad de patrones de entrenamiento: %d", PR);
  printf ("\nCantidad de patrones de validacion: %d", PTOT - PR);
  printf ("\nCantidad de patrones de test: %d", PTEST);
  printf ("\nCantidad vecinos: %d", N_NEIG); 
  printf ("\nSemilla para la funcion rand(): %d", SEED);

  return 0;
}

/* -------------------------------------------------------------------------------------- */
/*read_data: lee los datos de los archivos de entrenamiento(.data) y test(.test)
    filename es el nombre de los archivos (sin extension)
    La cantidad de datos y la estructura de los archivos fue leida en la funcion arquitec()
    Los registros en el archivo pueden estar separados por blancos ( o tab ) o por comas        */
/* -------------------------------------------------------------------------------------- */
int
read_data (char *filename)
{

  FILE *fpat;
  double valor;
  int i, k, separador;

  sprintf (filepat, "%s.data", filename);
  fpat = fopen (filepat, "r");
  error = (fpat == NULL);
  if (error)
    {
      printf ("Error al abrir el archivo de datos\n");
      return 1;
    }

  if (CONTROL > 1)
    printf ("\n\nDatos de entrenamiento:");

  for (k = 0; k < PTOT; k++)
    {
      if (CONTROL > 1)
	printf ("\nP%d:\t", k);
      for (i = 0; i < N_IN + 1; i++)
	{
	  fscanf (fpat, "%lf", &valor);
	  data[k][i] = valor;
	  if (CONTROL > 1)
	    printf ("%lf\t", data[k][i]);
	  separador = getc (fpat);
	  if (separador != ',')
	    ungetc (separador, fpat);
	}
    }
  fclose (fpat);

  if (!PTEST)
    return 0;

  sprintf (filepat, "%s.test", filename);
  fpat = fopen (filepat, "r");
  error = (fpat == NULL);
  if (error)
    {
      printf ("Error al abrir el archivo de test\n");
      return 1;
    }

  if (CONTROL > 1)
    printf ("\n\nDatos de test:");

  for (k = 0; k < PTEST; k++)
    {
      if (CONTROL > 1)
	printf ("\nP%d:\t", k);
      for (i = 0; i < N_IN + 1; i++)
	{
	  fscanf (fpat, "%lf", &valor);
	  test[k][i] = valor;
	  if (CONTROL > 1)
	    printf ("%lf\t", test[k][i]);
	  separador = getc (fpat);
	  if (separador != ',')
	    ungetc (separador, fpat);
	}
    }
  fclose (fpat);

  return 0;

}

/* ------------------------------------------------------------ */
/* shuffle: mezcla el vector seq al azar.
     El vector seq es un indice para acceder a los patrones.
     Los patrones mezclados van desde seq[0] hasta seq[hasta-1]
     Esto permite separar la parte de validacion de la de train     */
/* ------------------------------------------------------------ */
void
shuffle (int hasta)
{
  double x;
  int tmp;
  int top, select;

  top = hasta - 1;
  while (top > 0)
    {
      x = (double) rand ();
      x /= RAND_MAX;
      x *= (top + 1);
      select = (int) x;
      tmp = seq[top];
      seq[top] = seq[select];
      seq[select] = tmp;
      top--;
    }
  if (CONTROL > 3)
    {
      printf ("End shuffle\n");
      fflush (NULL);
    }
}
/* ------------------------------------------------------------------- */
/*cmpfunc: función para comparar valores en qsort
 *                                                                     */
/* ------------------------------------------------------------------- */
int cmpfunc (const void * a, const void * b)
{
	if( ((punto*)a)->distancia > ((punto*)b)->distancia )
		return 1;
	else
		return -1;
}

/* ------------------------------------------------------------------- */
/*Prob:Calcula la probabilidad de obtener el valor x para el input feature y la clase clase
    Aproxima las probabilidades por distribuciones normales */
/* ------------------------------------------------------------------- */
void distancia (double *input)
{
  int i, patron, nu;
  double d;
  for(patron = 0; patron < PR; patron ++){
     d = 0;
     /*nu tiene el numero del patron que se va a presentar */
     nu = seq[patron];

	  /*Itero en los atributos*/
	  for(i = 0; i < N_IN; i++)
		d += pow((data[nu][i] - input[i]),2.0);
	(dist[patron]).clase = data[nu][N_IN];
	(dist[patron]).distancia = sqrt(d);
	}
	
  return;
}

/* ------------------------------------------------------------------------------ */
/*output: calcula la distancia euclidia entre el input (punto a determinar clase)
 * y todos los puntos de entrenamiento.
 * Devuelve la clase mayoritaria de los k más cercanos. En caso de empate, devuelve
 * la clase de los k-1 más cercanos.                                              */
/* ------------------------------------------------------------------------------ */
int
output (double *input, int vecinos, int isTrain)
{
  int i, k, clase_MAP, cant_max, cant_ganadoras;
  int clases[N_Class];
  
  /* Inicializo clases en 0 */
  for(i = 0; i < N_Class; i++)
	clases[i] = 0;
	
   /*Dejo en el arreglo dist, la distancia del punto input a cada punto de entrenamiento*/
   distancia(input);
   /*Ordeno el arreglo*/
   qsort(dist, PR, sizeof(punto), cmpfunc);

	/*Cuento para los N_NEIG primeros vecinos cuántos hay de cada clase*/
	if(isTrain){
		for(k = 1; k < vecinos + 1; k++)
			clases[(dist[k]).clase] ++;   
		}
	else{
   for(k = 0; k < vecinos; k++)
      clases[(dist[k]).clase] ++;
	}
   cant_max = clases[0];
   /*Prendo la clase 0 como ganadora*/
   cant_ganadoras = 1;
   clase_MAP = 0;
   for(k = 1; k < N_Class; k++){
   
	  /* Si empata, sumo esa clase como ganadora*/
   	  if(clases[k] == cant_max)
		cant_ganadoras ++;
   	  
   	  /* Si gana, apago las demás y prendo la clase k como ganadora */
      if(clases[k] > cant_max){
		cant_max = clases[k];
		cant_ganadoras = 1;
		clase_MAP = k;
	  }
  }
    /*Si hay una única clase ganadora, la devuelvo. En caso de empate, hago el mismo cálculo pero con un vecino menos*/
  if(cant_ganadoras == 1)
	return clase_MAP;
  else
   return output(input, vecinos - 1, isTrain);
}

/* ------------------------------------------------------------------------------ */
/*propagar: calcula las clases predichas para un conjunto de datos
    la matriz S tiene que tener el formato adecuado ( definido en arquitec() )
    pat_ini y pat_fin son los extremos a tomar en la matriz
    usar_seq define si se accede a los datos directamente o a travez del indice seq
    los resultados (las propagaciones) se guardan en la matriz seq                                    */
/* ------------------------------------------------------------------------------ */
double
propagar (double **S, int pat_ini, int pat_fin, int usar_seq, int isTrain)
{

  double mse = 0.0;
  int nu;
  int patron;

  for (patron = pat_ini; patron < pat_fin; patron++)
    {

      /*nu tiene el numero del patron que se va a presentar */
      if (usar_seq)
	     nu = seq[patron];
      else
	     nu = patron;

      /*clase MAP para el patron nu */
      pred[nu] = output (S[nu], N_NEIG, isTrain);;
      /*actualizar error */
      if (S[nu][N_IN] != (double) pred[nu])
		mse += 1.;
	
    }


  mse /= ((double) (pat_fin - pat_ini));

  if (CONTROL > 3)
    {
      printf ("End prop\n");
      fflush (NULL);
    }

  return mse;
}

/* --------------------------------------------------------------------------------------- */
/*train: ajusta los parametros del algoritmo a los datos de entrenamiento
                 guarda los parametros en un archivo de control
                 calcula porcentaje de error en ajuste y test                                                                            */
/* --------------------------------------------------------------------------------------- */
int
train (char *filename)
{

  int i, j, k, feature, clase;
  int nu;
  int patron, cont;
  int usar_seq = 0;
  float prob = 0.0;
  double sigma, me;
  double train_error, valid_error, test_error;
  FILE *salida, *fpredic;

  /*Asigno todos los patrones del .data como entrenamiento porque este metodo no requiere validacion */
  //N_TOTAL = PTOT;

  /*N_TOTAL=PR; si hay validacion */
  for (k = 0; k < PTOT; k++)
    seq[k] = k;			/* inicializacion del indice de acceso a los datos */

  /*efectuar shuffle inicial de los datos de entrenamiento si SEED != -1 (y hay validacion) */
  if (SEED > -1 && N_TOTAL < PTOT)
    {
      srand ((unsigned) SEED);
      shuffle (PTOT);
      usar_seq = 1;
    }

  /*calcular error de entrenamiento */
  train_error = propagar (data, 0, PR, 1, 1);

  /*calcular error de validacion; si no hay, usar mse_train */
  if (PR == PTOT)
    valid_error = train_error;
  else
    valid_error = propagar (data, PR, PTOT, 1, 0);

  /*calcular error de test (si hay) */
  if (PTEST > 0)
    test_error = propagar (test, 0, PTEST, 0, 0);
  else
    test_error = 0.;

  /*mostrar errores */
  printf ("\nFin del entrenamiento.\n\n");
  printf ("Errores:\nEntrenamiento:%f%%\n", train_error * 100.);
  printf ("Validacion:%f%%\nTest:%f%%\n", valid_error * 100.,
	  test_error * 100.);
  if (CONTROL)
    fflush (NULL);

  /* archivo de predicciones */
  sprintf (filepat, "%s.predic", filename);
  fpredic = fopen (filepat, "w");
  error = (fpredic == NULL);
  if (error)
    {
      printf ("Error al abrir archivo para guardar predicciones\n");
      return 1;
    }
  for (k = 0; k < PTEST; k++)
    {
      for (i = 0; i < N_IN; i++)
	fprintf (fpredic, "%f,", test[k][i]);
      fprintf (fpredic, "%d\n", pred[k]);
    }
  fclose (fpredic);

  return 0;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
int
main (int argc, char **argv)
{

  if (argc != 2)
    {
      printf
	("Modo de uso: nb <filename>\ndonde filename es el nombre del archivo (sin extension)\n");
      return 0;
    }


  /* defino la estructura */
  error = arquitec (argv[1]);
  if (error)
    {
      printf ("Error en la definicion de parametros\n");
      return 1;
    }


  /* leo los datos */
  error = read_data (argv[1]);
  if (error)
    {
      printf ("Error en la lectura de datos\n");
      return 1;
    }

  /* ajusto los parametros y calcula errores en ajuste y test */
  error = train (argv[1]);
  if (error)
    {
      printf ("Error en el ajuste\n");
      return 1;
    }


  return 0;

}

/* ----------------------------------------------------------------------------------------------------- */
