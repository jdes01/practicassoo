// Programa a) Cree un abanico de procesos como el que se refleja en la primera figura (1 padre; varios hijos (del mismo padre))


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

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
            exit(EXIT_SUCCESS); //aqui muere el hijo

        default:
            printf("Esperando hijo numero %d \n", i+1);
            wait(&status); //se bloquea el padre hasta que el hijo muera
            printf("Hijo %d termindo con ID %d, codigo de salida: %d \n", i+1, getpid(), WEXITSTATUS(status)); 
            printf("\n");

        }

        
    } 

    return 0;
}