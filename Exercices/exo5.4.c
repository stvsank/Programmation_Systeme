#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

/*
a) Reprendre la fonction de thread de génération d’un tableau aléatoire du
4.1. Le thread principal crée en parallèle deux tableaux T1 et T2, avec le
nombre d’éléments de T1 plus petit que le nombre d’éléments de T2.
b) Lorsque les tableaux sont finis de générer, lancer un thread qui
détermine si le tableau T1 est inclus dans le tableau T2. Quelle est la
complexité de l’algorithme ?
c) Modifier le programme précédent pour qu’un autre thread puisse
terminer le programme si l’utilisateur appuie sur la touche ’A’ (par exit(0)).
Le programme doit afficher un message en cas d’annulation, et doit
afficher le résultat du calcul sinon.
*/

//< >

int *T1;
int *T2;
int nbr_elem1;
int nbr_elem2;

void * init_nbr_elem1()
{
int j;
T1 = malloc(nbr_elem1 * sizeof(int));
for (j=0;j<nbr_elem1;j++)
{
	T1[j]=rand()%100;	
}
}


void * init_nbr_elem2()
{
int j;
T2 = malloc(nbr_elem2 * sizeof(int));
for (j=0;j<nbr_elem2;j++)
{
	T2[j]=rand()%100;	
}
}

void *inclusion()
{
int i,j,tmp,present;
present=0;
for(i=0;i<nbr_elem1;i++)
{
	tmp=0;
	for (j=0;j<nbr_elem2;j++)
	{
		if(T1[i] == T2[j])
		{	
			tmp=1;
		}
	}
	present=present+tmp;
}
if(present==nbr_elem1)
{
	printf("\nT1 est inclu dans T2\n");
}
else
	printf("\nT1 n'est pas inclu dans T2\n");
}

void * term_proc()
{
char i[2];
printf("\nEntrez A pour terminer\n");
scanf("%s",i);
if(i[0]=='A' ||i[0]=='a' )
{
	printf("Vous avez arrêté le programme\n");
	exit(0);
}
else 
	printf("\nLe programme continu\n");
}

int main()
{
pthread_t num_thread1,num_thread2,num_thread3,num_thread4;
int i,j;
printf("Combien d'élement pour T1 voulez vous\n"); 
scanf("%d",&nbr_elem1);
printf("Combien d'élement pour T2 voulez vous\n");
scanf("%d",&nbr_elem2);
pthread_create(&num_thread1,NULL,init_nbr_elem1,NULL);
pthread_create(&num_thread2,NULL,init_nbr_elem2,NULL);
pthread_join(num_thread1,NULL);
pthread_join(num_thread2,NULL);
printf("\n\nTableau 1\n");
for(i=0;i<nbr_elem1;i++)
{
	printf("Entier %d = %d\n",i+1,T1[i]);
}
printf("\nTableau 2\n");
for(i=0;i<nbr_elem2;i++)
{	
	printf("Entier %d = %d\n",i+1,T2[i]);
}
pthread_create(&num_thread3,NULL,term_proc,NULL);
pthread_join(num_thread3,NULL);
pthread_create(&num_thread4,NULL,inclusion,NULL);
pthread_join(num_thread4,NULL);

}

