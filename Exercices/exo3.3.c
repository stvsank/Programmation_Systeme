#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

/*
Écrire un programme qui crée 5 processus fils qui font une boucle while
(1). Le processus père proposera dans une boucle sans fin un menu à
l’utilisateur : -Endormir un fils ; - Réveiller un fils ; -Terminer un fils ;
Modifier les fils pour qu’ils affichent un message lorsqu’ils sont tués. Le
processus père affichera un autre message s’il est tué.
*/

void message();
void messag();

int main()
{
int i,j,fin,rep,tmp,calcul;
char reponse;
printf("Entrez le nombre de processus que vous voulez creer : \n");
scanf("%d",&fin);
pid_t ret[fin];
for (i=0;i<=fin-1;i++)
{
	ret[i]=fork();
	if(ret[i]==0)
	{   
		if(signal(SIGTERM, messag)==SIG_ERR)
		{
			perror("signal");
			exit(1);
		}
		printf("je suis le fils %d: mon pid est %d \n",i+1,getpid());
		printf("le pid de mon père est: %d\n",getppid());
		while(1)
			calcul=i+1;
		break;
	}
	else if(ret[i]!=0 && i==fin-1)
	{
		if(signal(SIGKILL, message)==SIG_ERR)
		{
			perror("signal");
			exit(1);
		}
		printf("\nje suis le père; mon pid est %d\n",getpid());	
		tmp=1;
		while(tmp!=0)
		{
			sleep(1);
			printf("Taper e, r, t ou s pour endormir, réveiller, terminer un fils ou sortir du programme\n");
			scanf("%c",&reponse);
			if(reponse=='e')
			{
				printf("Entrez le numéro du processus\n");
				scanf("%d",&rep);
				kill(ret[rep-1],SIGSTOP);	
			}
			else if (reponse=='r')
			{
				printf("Entrez le numéro du processus\n");
				scanf("%d",&rep);
				kill(ret[rep-1],SIGCONT);
			}
			else if (reponse=='t')
			{
				printf("Entrez le numéro du processus\n");
				scanf("%d",&rep);
				kill(ret[rep-1],SIGTERM);	
			}
			else if (reponse=='s')
			{
				for (j=0;j<=fin-1;j++)
				{
					kill(ret[j],SIGTERM);
				}	
				tmp=0;
			}
		}
	
	}
}


}

void message()
{

printf("je suis le père et on m'a tué");
exit(0);
}
void messag()
{

printf("je suis un fils et on m'a tué");
exit(0);
}



























