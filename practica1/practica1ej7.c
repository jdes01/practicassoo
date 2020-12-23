//Realizar un programa padre que expanda un hijo y al cual le envíe cada 1 segundo una señal
//personalizada de usuario SIGUSR1. El hijo debe imprimir un mensaje en pantalla cada vez que
//recibe la señal del padre, tratándola en una función aparte llamada tratarSignal(). Enviados 5
//mensajes los procesos deben salir. Utiliza las funciones signal() y kill().

//RECUERDE, LOS SLEEPS() SON A MODO DIVULGATIVO. NO USAR SLEEPS() PARA
//SINCRONIZAR SUS PROCESOS, ESO ES CUESTIÓN DEL NÚCLEO DEL SISTEMA
//OPERATIVO.






#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void tratarSignal() { printf("Señal recibida\n"); }

int main(){

    pid_t pid;

    printf("Soy %d el padre de todos\n", getpid()); 

    pid = fork();

    switch(pid){


        case -1: 

            printf("Error al crear el proceso hijo\n"); 
            exit(EXIT_FAILURE);

        case 0:

            signal(SIGUSR1, tratarSignal);      //se emite esta señal (que ejecutara tratarSignal cuando sea notificada)

            printf("Soy %d el hijo del proceso: %d\n", getpid(), getppid()); 

            for (int i = 0; i < 5; i++){      //el hijo cae aqui donde se pausa
        
                pause();
            }

            sleep(10);


        default: //aqui cae el padre

            printf("Esperando a que acabe mi hijo\n");

            for (int i = 0; i < 5; i++){ //a cada pausa del hijo , el padre sleepea 3 segundos y notifica a la señal, activando tratarSignal
      
                sleep(3);
                kill(pid, SIGUSR1);
            }

            sleep(3);
            kill(pid, SIGKILL);//El padre le dice al hijo que acabe
    }
   
  exit(EXIT_SUCCESS); //Como todo ha ido bien el proceso padre acaba exitosamente
}