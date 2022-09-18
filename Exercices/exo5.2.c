#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

/*
Écrire un programme qui crée un thread qui alloue un tableau 
d’entiers, initialise les éléments par des entiers aléatoires entre 0 et 99, et 
retourne le tableau d’entiers. 
*/

//< >
int* creation_entier(int tab[])
{
int j;
for (j=0;j<30;j++)
{
	tab[j]=rand()%100;	
}
return tab;
}

int main()
{
pthread_t num_thread;
int i,tmp[30];
pthread_create(&num_thread,NULL,creation_entier,tmp);
pthread_join(num_thread,NULL);
for(i=0;i<30;i++)
{
	printf("Entier %d = %d\n",i+1,tmp[i]);
}
}


