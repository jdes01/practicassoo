//Implemente un programa que cree un número N de hebras. Cada hebra creará 2 números
//aleatorios flotantes (consulte Moodle para la generación de aleatorios) y guardará su suma en una
//variable para ello, que será devuelta a la hebra principal o llamadora (la que invocó
//pthread_create()).
//La hebra principal ira recogiendo los valores devueltos por las N hebras y los ira sumando en
//una variable no global cuyo resultado mostrará al final por pantalla. Para ver que los resultados
//finales son los que usted espera, muestre los 2 números que va creando cada hebra y su suma, de
//forma que pueda comparar esas sumas parciales con la suma final que realizará el main() o hebra
//principal. Utilice macros definidas y comprobación de errores en sus programas (errno y
//comprobación de valores devueltos en cada llamada, con sus posibles alternativas).

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


void * generarNumeros(){

    int * z = malloc(sizeof(int)); 

    int x = rand() % 10;
    printf("x = %i \n", x);

    int y = rand() % 10;
    printf("y = %i \n", y);

    *z = x + y;

    printf("x + y = %i \n", *z);

    pthread_exit(z);
}


int main(int argc, char const *argv[]){

    srand (time(NULL));

    int nHebras = atoi(argv[1]);

    pthread_t thread[nHebras]; //en este vector (de tamaño suma) se iran almacenando los IDs de cada hebras

    int *numero, suma=0; //puntero donde guardamos el numero generado por cada hebra y entero donde almacenamos la suma total

    for (int i = 0; i < nHebras; i++){
   
        if( pthread_create( &(thread[i]), NULL, (void*) generarNumeros, NULL ) != 0 ){ // ( identificador de la hebra a crear, modo por defecto, funcion a ejecutar, argumentos que le pasamos a la funcion)

            fprintf(stderr, "Error al crear la hebra");         //como pthread_create devuelve 0 en caso de exito, 
            exit(EXIT_FAILURE);                                 //solo entrara dentro del if si ha ocurrido algun error
        }
    }


    for (int i = 0; i < nHebras; i++){
   
        if( pthread_join( thread[i], (void **) &numero ) != 0 ){ //aqui acaban las hebras despues de ejecutar la funcion, guardando el valor de retorno en el puntero "numero"

            fprintf(stderr, "Error al usar join");         
            exit(EXIT_FAILURE);                  
        }

        suma = suma + *numero;
    }
    
    printf("%i", suma);

    return 0;
}


