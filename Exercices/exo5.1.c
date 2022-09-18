#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

/*
Écrire un programme qui crée un thread qui prend en
paramètre un tableau d’entiers et l’affiche dans la console.
*/
//< >
void affiche(int tab[])
{
int i;
	for(i=0;i<20;i++)
	{
		printf("Entier %d = %d\n",i+1,tab[i]);
	}
}

int main()
{
pthread_t num_thread;
int j,tmp[20];
for (j=0;j<20;j++)
{
	tmp[j]=rand()%100;	
}
pthread_create(&num_thread,NULL,(void *(*)())affiche,tmp);
pthread_join(num_thread,NULL);
}


