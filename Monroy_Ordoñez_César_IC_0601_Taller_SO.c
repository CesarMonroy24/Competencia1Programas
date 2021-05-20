/*En el presente código de programación se realiza lo que es el uso de la multiprogramación a partir de una variable estático que compartirán 2 procesos para incrementar 
y decrementar ese valor al término de la ejecución de uno con el uso de la creación de hilos con pthread y la creación de un proceso en Linux con fork para ello es necesario 
ejecución  en un sistema con distribución en Linux */
#include <stdio.h> // declaración de librería para el uso de operaciones estándar de E/S
#include <stdlib.h>// declaración de librería para la gestión de memoria dinámica y control de procesos
#include <pthread.h>// declaración de librería para el manejo de hilos en c
#include <errno.h>// declaración de biblioteca para presentar un informe en caso de un error al ejecutar el código 
#include <unistd.h>//declaración de librería para el uso de procesos al sistema con fork en Linux


static int variable = 10; //declaración de una variable estática de tipo entero

void *proceso1(void *data){ //este es el primer proceso que se llevara a cabo a traves del uso de un puntero para la creación del hilo el cual recibe un puntero data
int i;//variable de tipo entero i
for(i=0; i<100;i++){ //entrada a un bucle de repetición de la variable i 100 veces 
variable++; // la variable de tipo estático aumentara 100 veces su valor 
	}
}
	
void *proceso2(void *data){//este es el segundo proceso que se llevara a cabo a traves del uso de un puntero para la creación del hilo el cual recibe un puntero data
int i;//variable de tipo entero i
for(i=0; i<100;i++){//entrada a un bucle de repetición con la variable i 100 veces
variable--;//la variable de tipo estático ahora decrementara  su valor 100 veces 
	}
}
	
void error(char *strerr){ //función error la cual a traves de la declaración de un puntero imprime el eror y termina el programa 
perror(strerr);
exit(1);
}
	
int main(){
pid_t PIDP;//declaración de una variable para la identificación de un proceso en Linux
printf("proceso PID = %d COMIENZA  \n", getpid());//imprime en pantalla el proceso PID(identificador de proceso) para ello utilizamos la función getpid()
PIDP = fork();//crea una llamada al sistema después crea el proceso y el valor que nos da fork se almacena en la variable PIDP 
printf("Proceso PID = %d, PIDP = %d ejecutandose \n",getpid(), PIDP);//imprime en pantalla el proceso PID tanto del proceso padre como del proceso hijo que se a creado.  
pthread_t hilo1, hilo2;//declaración de dos variable de tipo pthread_t que almacenaran el identificador de cada uno de los hilos que vamos a crear 
if(0 != pthread_create(&hilo1, NULL, proceso1, NULL))//entramos en un if si no es igual o distinto de c el identificador del hilo crea el hilo con pthread_create, después almacena el identificador del hilo creado en la variable hilo 1, utilizamos NULL ya que no necesita ningún argumento la función que ejecutara el proceso1 
error("hilo 1 no se pudo crear"); //Llama a la función error en caso de no poderse crear el hilo 1
if(0 != pthread_create(&hilo2, NULL, proceso2, NULL))// pasa lo mismo que el hilo 1 crea el segundo hilo ejecutando ahora la función del proceso 2
error("hilo 2 no se pudo crear");// llama a la función error en caso de no poderse crear el segundo hilo
/*Hacemos uso de pthread_join para realizar un mecanismo de sincronización que nos permitirá esperar la terminación de un hilo. */	
pthread_join(hilo1, NULL);
pthread_join(hilo2, NULL);
		
while(1){ //entramos en un bucle infinito
sleep(2); //los dos hilos creados con los proceso PID esperan 2 segundos para ver su ejecución 	
printf("proceso. PID = %d ,el valor es %d \n", getpid(),variable); // Imprime o muestra en pantalla el proceso PID que se está ejecutando y el valor que tienen los dos hilos creados que se están ejecutando al mismo tiempo incrementando y decrementando el valor estático 
	}
return 0; //retorna un valor 0
}//fin del main
/* Para la ejecución del programa se utiliza un sistema operativo con distribución de Linux y se ejecuta el siguiente comando para  su ejecución en la terminal gcc Multiprogramacion.c  (Nombre del programa) –pthread(librería de la cual estamos haciendo uso) -o Multiprogramacion(nombre del ejecutable), entonces quedaría  --> gcc Multiprogramacion.c -pthread -o Multiprogramacion y para la ejecución del ejecutable solamente ejecutamos el ejecutable de la siguiente manera --> ./ Multiprogramacion. El programa nos tiene que mostrar el PID del proceso en ejecucion padre que es el primero y el proceso con el PID del hijo con el valor de la variable 10 ya que esta incrementa primeramente 100 veces y posteriormente tiene un decremento 100 veces por lo tanto nos tiene que mostrar el mismo valor */

