#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*
Écrire un programme qui crée 5 fils en utilisant une boucle
for. On remarquera que pour que le fils ne crée pas lui-même plusieurs fils,
il faut interrompre la boucle par un break dans le fils.
*/
//< > i

int main()
{
int i;

pid_t ret;

for (i=1;i<=5;i++)
{
	ret=fork();
	if(ret==0)
	{   
		printf("je suis le fils %d: mon pid est %d \n",i,getpid());
		printf("le pid de mon père est: %d\n",getppid());
		break;
	}
	else if(ret!=0 && i==1)
	{
		printf("je suis le père; mon pid est %d\n\n",getpid());	
	}
	else
	{
		wait();
		printf("***erttrezhgfds***");
		
	}
}
}
