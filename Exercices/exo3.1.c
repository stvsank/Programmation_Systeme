#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

/*
Exercice 3.1 Ecrire un programme qui crée un fils qui fait un calcul sans
fin. Le processus père propose alors un menu :
• Lorsque l’utilisateur appuie sur la touche 's', le processus père endort
son fils.
• Lorsque l’utilisateur appuie sur la touche 'r', le processus père
redémare son fils.
• Lorsque l’utilisateur appuie sur la touche 'q', le processus près tue
son fils avant de se terminer.
*/

void fin_attente();


int main()
{
int i;
char reponse;
int pid;
pid=fork();
if(pid==0)
{
	printf("je suis le fils mon pid est %d\n",getpid());
	printf("le pid de mon père est %d\n",getppid());
	printf("je suis en train de faire un calcul\n");
	i=0;
	while(1) 
	{
		i=i+1;
		printf("Seconde = %d\n",i);
		sleep(1);
	}
}
else 
{
	while(1)
	{
		printf("Entrez la lettre s, r ou q pour endormir, réveiller ou tuer\n");
		scanf("%c",&reponse);
		if(reponse=='s')
			kill(pid,SIGSTOP);
		else if (reponse=='r')
			kill(pid,SIGCONT);
		else if (reponse=='q')
			kill(pid,SIGTERM);				
	}
}
}





