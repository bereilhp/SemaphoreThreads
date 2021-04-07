#include <stddef.h>
#include <pthread.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>


long vueltas = 1000000000;
int cuenta = 0;
sem_t semaforo;


void * suma(void * args){

	
	for(int i = 0; i<vueltas;i++){

		cuenta++;
		//sem_post(&semaforo);
	}
	
	sem_post(&semaforo);
	
	pthread_exit(0);
}


void * resta(void * args){
	
	for(int i = 0; i<vueltas;i++){
		
		sem_wait(&semaforo);
		cuenta--;
		sem_post(&semaforo);
			
	}

	//sem_post(&semaforo);
	pthread_exit(0);
}

void main(){

	pthread_t th_a, th_b;

	pthread_create
		(&th_a, NULL, suma, "Suma");
	pthread_create
		(&th_b, NULL, resta, "Resta");

		sleep(1);
		pthread_join(th_a,NULL);
		pthread_join(th_b,NULL);
		printf("%d \n", cuenta);
	
	sem_init(&semaforo, 0, 1);
	sem_destroy(&semaforo);
}
