#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

/*
Créer une structure TypeTableau qui contient :
• Un tableau d’entiers ;
• Le nombre d’éléments du tableau ;
• Un entier x.
Écrire un programme qui crée un thread qui initialise un TypeTableau avec
des valeurs aléatoires entre 0 et 99. Le nombre d’éléments du tableau est
passé en paramètre. Dans le même temps, le thread principal lit un entiers
x au clavier. Lorsque le tableau est fini de générer, le programme crée un
thread qui renvoie 1 si l’élément x est dans le tableau, et 0 sinon.
*/


struct TypeTableau
{
int nbr_elem;
int * tmp;
int x;
};
struct TypeTableau tab;


void * init_nbr_elem(void *arg)
{
int j;
tab.nbr_elem=(int) arg;
tab.tmp = malloc(tab.nbr_elem * sizeof(int));
for (j=0;j<tab.nbr_elem;j++)
{
	tab.tmp[j]=rand()%100;	
}
}


void * rechercher()
{
int j, rep;
for (j=0;j<tab.nbr_elem;j++)
{
	if (tab.x == tab.tmp[j])
	{
		printf("Le mot a été trouvé et c'est l'entier numéro %d\n",j+1);	
		return 1;
	}
}
printf("Le mot n'a pas été trouvé\n");
return 0;
}


int main()
{
pthread_t num_thread,num_thread1;
int i,j;
printf("Combien d'élement voulez vous\n");
scanf("%d",&i);
pthread_create(&num_thread,NULL,init_nbr_elem,(void *) i);
pthread_join(num_thread,NULL);
for (j=0;j<tab.nbr_elem;j++)
{
	printf("Entier %d = %d\n",j+1,tab.tmp[j]);
}
printf("Entrez l'entier à rechercher\n");
scanf("%d",&tab.x);
pthread_create(&num_thread1,NULL,rechercher,NULL);
pthread_join(num_thread1,NULL);
}











