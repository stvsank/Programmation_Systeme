#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>//permet d'utiliser sleep
#include<time.h>//permet d'utiliser time

/*
Écrire un programme qui crée deux fils appelés fils 1 et fils 2.
Chaque fils doit attendre un nombre de secondes aléatoire entre 1 et 10, en
utilisant la fonction sleep. Le programme attend que le fils le plus long se
termine et affiche la durée totale. On pourra utiliser la fonction time de la
bibliothèque time.h, qui retourne le nombre de secondes depuis le premier
janvier 1970 à 0h (en temps universel).
*/

//< > i
//rand()%11 pour créer aléatoirement des valeurs de 0à10

int main()
{
int i,j,fin,id;
printf("Entrez le nombre de processus que vous voulez creer : \n");
scanf("%d",&fin);
int tmp[fin];
i=0;
for (j=0;j<=fin-1;j++)
{
	tmp[j]=rand()%11;	
	if (i < tmp[j])
	{
		i=tmp[j];
		id=j;
	}
}
pid_t ret[fin];
time_t begin = time(NULL);
for (i=0;i<=fin-1;i++)
{
	ret[i]=fork();
	if(ret[i]==0)
	{   
		printf("\nje suis le fils %d: mon pid est %d \n",i+1,getpid());
		printf("le pid de mon père est: %d\n",getppid());
		printf("TEMPS : %d sec\n",tmp[i]);
		sleep(tmp[i]);
		break;
	}
	else if( i==fin-1)
	{	
		waitpid(ret[id],NULL,NULL);
		time_t end=time(NULL);
		float secondes = (float) difftime( end, begin );
		printf("je suis le père; mon pid est %d\n\n",getpid());	
		printf("TMP %f\n",secondes);
	}
}

}





