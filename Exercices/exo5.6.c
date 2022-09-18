#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

/*
Créer un programme qui a en variable globale un tableau de
N double, avec N=100.
Dans le main, le tableau sera initialisé avec des valeurs réelles aléatoires
entre 0 et 100, sauf les valeurs tableau[0] et tableau[99] qui vallent 0.
Le programme crée deux threads :
• Le premier thread remplace chaque valeur tableau[i], avec i = 1,2,. . .,98
par la moyenne (tableau[i-1]+tableau[i]+tableau[i+1])/3
Il attend ensuite un temps aléatoire entre 1 et 3 secondes ;
• Le deuxième thread affiche le tableau toutes les 4 secondes.
*/

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
double tab[100];

void *remplacement()
{
int i;
double tmp1,tmp2;//tmp1 et tmp2 permettrons de garder les anciennes valeures du tableau pour pouvoir réaliser la moyenne.
for(;;)
{
	pthread_mutex_lock(&mutex);
	for (i=1;i<99;i++)
	{	
		tmp1=tab[i];
		tab[i]=(tmp2+tab[i]+tab[i+1])/3;
		tmp2=tmp1;	
	}
	pthread_mutex_unlock(&mutex);
	sleep(rand()%3+1);
}
}

void * affichage()
{
int i;
for(;;)
{
	pthread_mutex_lock(&mutex);
	for (i=0;i<100;i++)
	{
		printf("Entier %d = %lf\n",i+1,tab[i]);	
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);
	sleep(4);
}
}


int main()
{
int i;
pthread_t num_thread1,num_thread2;
//initialisation du tableau
tab[0]=0;
tab[99]=0;
for (i=1;i<99;i++)
{
	tab[i]=rand()%101;
}
printf("Tableau initial\n\n");
for (i=0;i<100;i++)
{
	printf("Entier %d = %lf\n",i+1,tab[i]);	
}

printf("\n");
pthread_create(&num_thread1,NULL,remplacement,NULL);	pthread_create(&num_thread2,NULL,affichage,NULL);
pthread_join(num_thread1,NULL);
pthread_join(num_thread2,NULL);


}
