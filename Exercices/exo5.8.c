#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

/*
Un thread émetteur dépose , à intervalle variable entre 1 et 3 secondes, un
octet dans une variable globale à destination d’un processus récepteur. Le
récepteur lit cet octet à intervalle variable aussi entre 1 et 3 secondes.
Quelle solution proposez-vous pour que l’émetteur ne dépose pas un
nouvel octet alors que le récepteur n’a pas encore lu le précédent et que le
récepteur ne lise pas deux fois le même octet ?
*/


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore; /* variable globale : sémaphore */
int *octet;
void * emetteur()
{
octet = malloc(1);
for(;;)
{
	pthread_mutex_lock(&mutex);
	sleep(rand()%3+1);
	octet[0]=rand()%500+100;
	printf("Valeur déposé : %d \n",octet[0]);
	sem_post(&semaphore);
}
}

void * recepteur()
{
for(;;)
{
	sem_wait(&semaphore);
	sleep(rand()%3+1);
	printf("Le caractère lu est : %d \n",octet[0]);
	pthread_mutex_unlock(&mutex);	
}
}

int main()
{
pthread_t thread1,thread2;

/* initialisation */
sem_init(&semaphore, 0, 0); 

// création des threads.
pthread_create(&thread1, NULL, emetteur, NULL);
pthread_create(&thread2, NULL, recepteur, NULL);

//attente
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

//destruction du sémaphore
sem_destroy(&semaphore);
}



