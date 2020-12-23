//Cree un programa que reciba por la linea de argumentos un número y calcule el factorial de ese
//número. Compílelo y compruebe su funcionamiento. A partir de ahí cree otro programa aparte que
//reciba dos números enteros como parámetros en la linea de argumentos y cree dos procesos hijos,
//de manera que cada uno calcule el factorial de uno de los números usando el ejecutable creado
//anteriormente (“./a.out 3 5”), use para ello la familia de funciones exec(). En el programa que
//calcula el factorial ponga un sleep(1) entre los cálculos parciales para poder observar en consola
//como se van ejecutando los dos procesos que se lanzarán en paralelo


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    int status;

    printf("Soy el proceso %d\n", getpid());

    for (int i = 0; i < argc - 1; i++){


        switch (fork()){

            case -1:

                    printf("ERROR");
                    exit(EXIT_FAILURE);
                    break;

            case 0: //aqui entran los hijos (fork le dara a cada hijo un 0)

                    printf("soy el hijo numero %d; mi padre es el proceso: %d\n", getpid(), getppid); //getpid nos da el id de cada proceso; getppid el id del padre de cada proceso

                        printf(" %i \n", factorial( atoi(argv[i+1]) ) );
                    exit(EXIT_SUCCESS);
                
                    break;

            default:

                    wait(&status); //se bloquea el padre hasta que el hijo muera
        }

    }

    return 0;
}


int factorial(int n){ //Funcion para calcular el factorial del numero pasado como argumento

  int resultado = 1;//Inicializamos la variable resultado a 1

  for (int i = n; i > 0; i--) {//En cada iteración del bucle el proceso se duerme 1 segundo

    resultado *=i;
  }
  
  return resultado;//Devuelve el factorial del numero introducido
}