#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*
Écrire un programme avec un processus père qui engendre 5
fils dans une boucle for. Les fils sont nommés fils 1 à fils 5. Le fils 1 doit
afficher “je suis le fils 1” et le fils 2 doit afficher je suis le fils 2, et ainsi de
suite. Chaque processus affichera son PID.
Indication. on pourra utiliser une variable globale.
*/
//< > i

int main()
{
int i,j,fin;

printf("Entrez le nombre de processus que vous voulez creer : \n");
scanf("%d",&fin);
pid_t ret[fin];
for (i=0;i<=fin-1;i++)
{
	ret[i]=fork();
	if(ret[i]==0)
	{   
		printf("je suis le fils %d: mon pid est %d \n",i+1,getpid());
		printf("le pid de mon père est: %d\n",getppid());
		break;
	}
	else if(ret[i]!=0 && i==fin-1)
	{
		printf("\nje suis le père; mon pid est %d\n",getpid());	
		printf("Les Pids de mes fils sont : \n");
		for (j=0;j<=fin-1;j++)
		{
			printf("Fils %d : %d\n",j+1,ret[j]);	
		}
	}

	else 
	{
		wait();		
	}
wait();
}
}
