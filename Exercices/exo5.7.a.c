#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

/*
Les sémaphores permettent de réaliser simplement des rendez-vous. 
Deux threads T1 et T2 itèrent un traitement 10 fois. On souhaite qu’à 
chaque itération le thread T1 attende à la fin de son traitement qui dure 2 
secondes le thread T2 réalisant un traitement d’une durée aléatoire entre 4 
et 9 secondes. Écrire le programme principal qui crée les deux threads, 
ainsi que les fonctions de threads en organisant le rendez-vous avec des 
sémaphores. 
*/
sem_t semaphore; /* variable globale : sémaphore */

void * funcThread1()
{
int i; 
for (i=1;i<=10;i++)
{
	sleep(2);
	printf("\nITERATION NUMERO %d\n",i);
	printf("\nJe suis T1, mon temps d'exécution est de 2 secondes et je m'endors pour attendre T2\n"); 
	sem_wait(&semaphore);
	printf("Je suis T1 et T2 viens de me réveiller\n");
}
}

void * funcThread2()
{
int i,attente;
for (i=1;i<=10;i++)
{
attente=rand()%6+4;
	sleep(attente);
	printf("Je suis T2, mon temps d'exécution est de %d secondes et je m'en vais réveiller T1\n",attente);
	sem_post(&semaphore);

}
}

int main()
{
pthread_t thread1,thread2;

/* initialisation */
sem_init(&semaphore, 0, 0); 

// création des threads.
pthread_create(&thread1, NULL, funcThread1, NULL);
pthread_create(&thread2, NULL, funcThread2, NULL);

//attente
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

//destruction du sémaphore
sem_destroy(&semaphore);
}


