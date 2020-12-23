//Para ver un proceso zombie, implemente un programa que tenga un hijo que acabe inmediatamente
//(por ejemplo, que imprima su ID y termine). Deje dormir al padre mediante la función sleep()
//durante 20 segundos y que luego acabe usando por ejemplo exit(EXIT_SUCCESS), sin recoger al
//hijo.
//Con otro terminal monitorice los procesos la orden de la “ps -a”. 


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(){

    int status;
    pid_t hijo;

    printf("Soy el padre \n");
    printf("\n");

    hijo = fork();

    if (hijo == -1){

        printf("Error \n");
        exit(EXIT_FAILURE);
    }

    if (hijo == 0){

        printf("HIJO ID: %d \n", getpid());
        exit(EXIT_SUCCESS);
    }

    else{

        printf("sleep 20s \n");
        sleep(20);

        wait(&status);

        printf("Proceso hijo termindo con el codigo %d \n", WEXITSTATUS(status));

        sleep(20);
        exit(EXIT_SUCCESS);
    }

    return 0;
}