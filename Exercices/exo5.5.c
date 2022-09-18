#include<stdio.h>
#include<stdlib.h>//pour l'utilisation de la fonction rand
#include<pthread.h>
#include<unistd.h>// pour l'utilisation de la fonction sleep

/*
Écrire un programme, avec un compteur global compt, et qui
crée deux threads :
• Le premier thread itère l’opération suivante : on incrémente le compteur
et attend un temps alléatoire entre 1 et 5 secondes.
• Le deuxième thread affiche la valeur du compteur toutes les deux
secondes.
Les accès au compteur seront bien sûr protégés par un mutex. Les deux
threads se terminent lorsque le compteur atteint une valeur limite passée en
argument (en ligne de commande) au programme.
*/
int fin;
int compt=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void * incrementation()
{
for(;;)
{
	pthread_mutex_lock(&mutex);
	if (compt == fin) 
	{
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	}
	compt++;
	pthread_mutex_unlock(&mutex);
	sleep(rand()%5+1);
}
}

void * affichage()
{
for(;;)
{
	pthread_mutex_lock(&mutex);
	printf("\nCompteur =  %d",compt);
	if (compt == fin) 
	{
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	}	
	pthread_mutex_unlock(&mutex);
	sleep(2);
		
}
}

int main()
{

	pthread_t num_thread1,num_thread2;
//insertion valeur 
	printf("Entrez la valeur limite\n");
	scanf("%d",&fin);	
//création thread	
	pthread_create(&num_thread1,NULL,incrementation,NULL);
	pthread_create(&num_thread2,NULL,affichage,NULL);
	pthread_join(num_thread1,NULL);
	pthread_join(num_thread2,NULL);
}

