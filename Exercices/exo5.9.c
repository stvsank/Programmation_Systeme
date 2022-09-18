#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

/*
Des processus producteurs produisent des objets et les insère un par un
dans un tampon de n places. Bien entendu des processus consommateurs
retirent, de temps en temps les objets (un par un).
Résolvez le problème pour qu’aucun objet ne soit ni perdu ni consommé
plusieurs fois. Écrire une programme avec N threads producteurs et M
threads consommateurs, les nombres N et M étant saisis au clavier. Les
producteurs et les consommateurs attendent un temps aléatoire entre 1 et 3
secondes entre deux produits. Les produits sont des octets que l’on stocke
dans un tableau de 10 octets avec gestion LIFO. S’il n’y a plus de place,
les producteurs restent bloqués en attendant que des places se libèrent.
*/

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore,semaphor; /* variable globale : sémaphore */
int produit,N,M; 
char *tab;

void * Producteur()
{
int i;
for(;;)
{
	sem_wait(&semaphor);
	if (produit<9)
	{
		for(i=produit;i<produit+2;i++)//les producteurs produisent deux objets
		{	
			tab[i]=rand()%100+1;
			printf("Valeur déposé tab[%d] : %d \n",i,tab[i]);
		}
		produit=produit+2;
		sleep(rand()%3+1);// attente entre 1 à 3 secondes
	}
	else
	{
		printf("Le Tableau est plein\n");
	}
	sem_post(&semaphore);
}
}

void * Comsommateur()
{
for(;;)
{
	sleep(rand()%3+1);// attente entre 1 à 3 secondes
	sem_wait(&semaphore);
	printf("Le caractère lu tab[%d] est : %d \n",produit-1,tab[produit-1]);// les comsommateurs recupèrent un objet
	tab[produit-1]=0;
	produit=produit-1;
	if (produit>9)
	{
		sem_post(&semaphore);
	}
	else
	{
		sem_post(&semaphor);
	}
}
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
/* création des threads Producteurs*/
for (i=0 ; i<N ; i++)
	pthread_create(&thread1[i], NULL, Producteur, NULL);

/* création des threads Comsommateurs */
for (i=0 ; i<M ; i++)
	pthread_create(&thread2[i], NULL, Comsommateur, NULL);

/* attente */
for (i=0 ; i<N ; i++)
	pthread_join(thread1[i], NULL);
for (i=0 ; i<M ; i++)
	pthread_join(thread2[i], NULL);
	
//destruction du sémaphore
sem_destroy(&semaphore);
sem_destroy(&semaphor);
}


