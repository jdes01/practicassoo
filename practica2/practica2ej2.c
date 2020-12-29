//Implemente un programa que cuente las líneas de los ficheros de texto que se le pasen como
//parámetros y al final muestre el número de líneas totales (contando las de todos los ficheros juntos).
//Ejemplo de llamada: ./a.out fichero1 fichero2 fichero3
//Debe crear un hilo por cada fichero indicado por linea de argumentos, de forma que todos los
//ficheros se procesen de manera paralela, uno por cada hilo.


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


void * cuentaLineas( void * argv ){

    int * numeroLineas = malloc(sizeof(int));

    * numeroLineas = 0;
    
    char const * fichero;

    char aux[256];

    fichero = (char*) argv;

    FILE* f = fopen(fichero, "r"); 

    if (f==NULL){

        printf("Error al abrir el archivo\n"); 
        EXIT_FAILURE;
    }

    while(fgets(aux, 256, f)!=NULL){ ++*numeroLineas; } //tiene que ser ++*numeroLineas en vez de *numeroLineas++, por que si no al salir del while se pierde el valor
    
    fclose(f);
 
	pthread_exit( (void**) numeroLineas);
}


int main(int argc, char const * argv[] ){

    int totalLineas = 0;

    int * retorno;

    pthread_t hilos[argc-1];

    for (int i = 0; i < argc-1; i++){
    
        if ( pthread_create( &(hilos[i]), NULL, (void *) cuentaLineas, (void *) argv[i+1] ) != 0){
        
            fprintf(stderr, "Error en la creacion de la hebra \n");

            exit(EXIT_FAILURE);
        }
        
    }

    for (int i = 0; i < argc-1; i++){
    
        if ( pthread_join( hilos[i], (void **) &retorno ) != 0){
        
            fprintf(stderr, "Error al hacer join \n");

            exit(EXIT_FAILURE);
        }

        printf("El numero de lineas del fichero %i es %d \n", i + 1, *retorno);


        totalLineas = totalLineas + *retorno;
    }
    
    printf("El numero de lineas totales son %i \n", totalLineas);

    return 0;
}