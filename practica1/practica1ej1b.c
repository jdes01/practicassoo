//Programa b) Lo mismo, pero recreando lo que representa la segunda figura. (cada hijo de un solo padre(en plan en cadena, uno detras de otro todo el rato))

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(){

    int nHijos=5, hijo, status;

    printf("Padre con ID %d \n", getpid());
    printf("\n");

    for (int i=0; i<nHijos; i++){
        
        hijo=fork(); //aqui llegan los hijos
            
        switch (hijo){
        
        case -1:

            printf("Error en la creación \n");
            exit(EXIT_FAILURE);
        
        case 0:

            printf("Hijo %d con ID %d del proceso %d \n", i+1, getpid(), getppid());
            printf("\n");
            break;

        default:

            printf("Esperando hijo numero %d \n", i+1);
            wait(&status);
            printf("Hijo %d termindo con ID %d, codigo de salida: %d \n", i+1, getpid(), WEXITSTATUS(status));
            printf("\n");
            exit(EXIT_SUCCESS);

        }

        
    } 

    return 0;
}