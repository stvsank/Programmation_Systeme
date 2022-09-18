#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

/*
Ce problème modélise les accès à une base de données. On peut accepter
que plusieurs processus lisent la base en même temps mais si un processus
est en train de la modifier, aucun processus, pas même un lecteur, ne doit
être autorisé à y accéder. Comment programmer les lecteurs et les
rédacteurs ? Proposer une solution avec famine des écrivains : les écrivains
attendent qu’il n’y ait aucun lecteur. Écrire une programme avec N threads
lecteurs et M threads rédacteurs, les nombres N et M étant saisis au clavier.
La base de donnée est représentée par un tableau de 15 octets initialisés à
0. À chaque lecture/écriture, le lecteur/écrivain lit/modifie l’octet à un
emplacement aléatoire. Entre deux lectures, les lecteurs attendent un temps
aléatoire entre 1 et 3 secondes. Entre deux écritures, les écrivains attendent
un temps aléatoire entre 1 et 10 secondes.
*/

void * redacteur()
{

}

void * lecteur()
{

}

int main ()
{
int i;
printf("Entrez le nombre de Producteur que vous voulez.\n");
scanf("%d",&N);
pthread_t thread1[N];
printf("Entrez le nombre de Comsommateur que vous voulez.\n");
scanf("%d",&M);
pthread_t thread2[M];

produit=0;
tab = malloc(10*1);// tableau de 10 octets

/* initialisation du sémaphore*/
sem_init(&semaphore, 0, 0); 
sem_init(&semaphor, 0, 0);


sem_post(&semaphor);//je libère le premier producteur.
/* création des threads redacteur*/
for (i=0 ; i<N ; i++)
	pthread_create(&thread1[i], NULL, redacteur, NULL);

/* création des threads lecteur */
for (i=0 ; i<M ; i++)
	pthread_create(&thread2[i], NULL, lecteur, NULL);

/* attente */
for (i=0 ; i<N ; i++)
	pthread_join(thread1[i], NULL);
for (i=0 ; i<M ; i++)
	pthread_join(thread2[i], NULL);
	
//destruction du sémaphore
sem_destroy(&semaphore);
sem_destroy(&semaphor);
}

