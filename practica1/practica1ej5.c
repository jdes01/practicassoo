//Use por ejemplo el ejercicio 1a) y cree una variable global de tipo entero inicializada a 0.
//Haga que cada hijo aumente en uno el valor de esa variable global y que el padre imprima el
//resultado final. ¿Qué ocurre? Correcto, su valor no se modifica porque los hijos son procesos
//nuevos que no comparten memoria. Para ello, y concretamente en sistemas basados en POSIX, se
//utilizan métodos de intercomunicación de procesos como son memoria compartida y semáforos, los
//cuales se estudiarán en otra práctica de la asignatura.



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int variableGlobal = 0;

int main(){

    int n=5, status;

    printf("Padre con ID %d \n", getpid());
    printf("\n");

    for (int i=0; i<n; i++){
        
        switch (fork()){ //El que llega aqui todas las veces es el padre (y crea su hijo)
        
        case -1:

            printf("Error en la creación \n");
            exit(EXIT_FAILURE);
        
        case 0:

            printf("Hijo %d con ID %d, padre: %d \n", i+1, getpid(), getppid());

            variableGlobal++;
            printf("%i\n", variableGlobal);

            exit(EXIT_SUCCESS); //aqui muere el hijo

        default:

            printf("Esperando hijo numero %d \n", i+1);
            wait(&status); //se bloquea el padre hasta que el hijo muera
            printf("Hijo %d termindo con ID %d, codigo de salida: %d \n", i+1, getpid(), WEXITSTATUS(status)); 
            printf("\n");

        }

        
    } 

    printf("%i\n", variableGlobal);

    return 0;
}