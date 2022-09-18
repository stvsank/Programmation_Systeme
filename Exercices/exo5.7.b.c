#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

/*
Dans cette version N threads doivent se donner rendez-vous, N étant
passé en argument au programme. Les threads ont tous une durée aléatoire
entre 1 et 5 secondes.
*/

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore; /* variable globale : sémaphore */
int NbArrives,N; 

void * funcThread()
{
int i,attente;
attente=rand()%5+1;
sleep(attente);
pthread_mutex_lock(&mutex);
	NbArrives=NbArrives+1;
	if (NbArrives < N)
	{
		printf("Je suis arrivé Numéro %d et mon temps d'exécution est de %d seconde(s).\n",NbArrives,attente);
		pthread_mutex_unlock(&mutex); /* on libère mutex et */
		sem_wait(&semaphore); /* on se bloque */
		printf("Je suis débloqué.\n");
	}
	else
	{
		printf("\nJe suis le dernier arrivé donc je ne me bloque pas.\n\n");
		pthread_mutex_unlock(&mutex);              /* le dernier arrivé libère mutex et */ 
		for (i=1; i<N; i++)/* réveille les N-1 bloqués, dans l'ordre d'arrivée */ 
			sem_post(&semaphore);
	
}
}


int main ()
{
int i;
printf("Entrez le nombre de processus que vous voulez.\n");
scanf("%d",&N);
pthread_t thread[N];

/* initialisation */
sem_init(&semaphore, 0, 0); 

/* création des threads */
for (i=0 ; i<N ; i++)
	pthread_create(&thread[i], NULL, funcThread, NULL);

/* attente */
for (i=0 ; i<N ; i++)
	pthread_join(thread[i], NULL);
	
//destruction du sémaphore
sem_destroy(&semaphore);

}



