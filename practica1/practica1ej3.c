//Implemente un programa donde se creen dos hijos. Uno de ellos que abra la calculadora de su
//distribución de Linux (busque como se llama ese ejecutable) y el otro que abra un editor de textos
//con N ficheros pasados como argumentos (recuerde hacer que el padre espere a los hijos). Use para
//ello la familia de funciones exec().
//Un ejemplo de invocación sería: ./a.out gnome-calculator vim practica1ej1a.c practica1ej1b.c  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    switch (fork()){

        case -1:

                printf("ERROR");
                exit(EXIT_FAILURE);
                break;

        case 0: //aqui entran los hijos (fork le dara a cada hijo un 0)

                printf("soy el hijo numero %d; mi padre es %d\n", getpid(), getppid); //getpid nos da el id de cada proceso; getppid el id del padre de cada proceso
                execlp(argv[1], argv[1], NULL);
                exit(EXIT_SUCCESS);
                
                break;
    }

    
    switch (fork()){

        case -1:

                printf("ERROR");
                exit(EXIT_FAILURE);
                break;

        case 0: //aqui entran los hijos (fork le dara a cada hijo un 0)

                printf("soy el hijo numero %d; mi padre es %d\n", getpid(), getppid); //getpid nos da el id de cada proceso; getppid el id del padre de cada proceso
                execvp(argv[2], argv+2);
                exit(EXIT_SUCCESS);
                break;
    }


    return 0;
}