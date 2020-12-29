#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct{

  int * vector;
  int numeroElementos;

} vInfo;

int comprobacionArgumento(int argumento){

  if (argumento==2 || argumento==5){ return 1; }

  return 0;
}

int * reservarMemoria(int numeroElementos){

	int *vector;

	vector = (int *) malloc( numeroElementos * sizeof(int) );

	return vector;
}

void rellenaVector(int *vector, int numeroElementos){

    srand( time(NULL) );

	for (int i = 0; i < numeroElementos; ++i){ vector[i] = (rand() % 9) + 1; }
}

void imprimeVector (int *vector, int numeroElementos){

	printf("[");
    printf(" %d ", vector[0]);

	for (int i = 1; i < numeroElementos; ++i){ printf(", %d ", vector[i]); }

	printf("]\n");
    printf("\n");
}

vInfo * creaHijos(int * vPadre, int numeroHilos){

    int numeroElementos = 10 / numeroHilos;

	vInfo * vHijos = (vInfo *) malloc (numeroHilos * sizeof(vInfo));

	for (int i=0;i<numeroHilos;i++){

		vHijos[i].vector = reservarMemoria(numeroElementos);

        vHijos[i].numeroElementos = numeroElementos;

        int k = 0;

        for (int j = (i * numeroElementos); j < ( (i * numeroElementos) + numeroElementos ); j++){

            vHijos[i].vector[k] =vPadre[j];

            k++;
        }

        printf("El vector hijo es: \n");
    
        imprimeVector(vHijos[i].vector, vHijos->numeroElementos);
	}

    return vHijos;
}

void * sumaHilos (void* d){

    int * suma = malloc( sizeof(int) );

    *suma = 0;

    vInfo *v;

    v = (vInfo*) d;

    for (int i = 0; i < v->numeroElementos; i++){

        *suma = *suma + v->vector[i];
    }
		 
    printf("La suma de los elementos de este vector es: %d \n", *suma);

	pthread_exit((void**) suma);
}

int main(int argc, char const *argv[]){

    if( argc < 2 || comprobacionArgumento( atoi(argv[1]) ) == 0 ){

        printf("Error llame al programa de la siguiente forma:\n");
        printf("./E3 2. o /E3 5\n");

        exit(EXIT_FAILURE);
    }

    int numeroHilos = atoi(argv[1]);

    vInfo *vPadre = malloc( sizeof(vInfo) ); 

    vPadre->numeroElementos = 10;
  
    vPadre->vector = reservarMemoria( vPadre->numeroElementos );

    rellenaVector( vPadre->vector, vPadre->numeroElementos );

    printf("El vector padre es: \n");

    imprimeVector( vPadre->vector, vPadre->numeroElementos );

    vInfo * vHijos = creaHijos(vPadre->vector, numeroHilos); 

    pthread_t hilos[numeroHilos];

    int * retorno, suma = 0;

    for (int i = 0; i < numeroHilos; i++){

      	if( pthread_create( &hilos[i], NULL, (void *) sumaHilos, (void *) vHijos+( sizeof(vInfo)*i ) ) != 0 ){

	        fprintf(stderr, "Error creating thread\n");
	        exit(EXIT_FAILURE); 
	    }
    }

    for (int i = 0; i < numeroHilos; i++){
  	
        if(pthread_join( hilos[i], (void**) &retorno) ){
        
	        fprintf(stderr, "Error joining thread\n");
	        exit(EXIT_FAILURE);
	    }

        suma += *retorno;
    }    

    printf("\nLa suma de los numeros de todos los vectores es: %d\n", suma);
    exit(EXIT_SUCCESS);
}