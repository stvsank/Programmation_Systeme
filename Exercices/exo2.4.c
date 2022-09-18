#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>//permet d'utiliser sleep
#include<time.h>//permet d'utiliser time

/*
Exercice 2.4 Écrire un programme qui saisit des noms de répertoires au
clavier et copie le répertoire courant dans tous ces répertoires. Le
programme doit se poursuivre jusqu’à ce que l’utilisateur demande de
quitter le programme.
*/

int main(int argc, char **argv)
{
char txt[60];
int tmp;
pid_t pid;
tmp=1;
while(tmp!=0)
{
	pid=fork();
	if(pid==0)
	{
		printf("\nEntrez le nom du repertoire :  ");
		scanf("%s",txt);
		execlp("cp","cp","-r","/home/sss/Documents/Prog sys/",txt,NULL);	
		break;
	}
	else
	{
		wait();
		printf("\nTapez 0 pour arrêter et toutes autres touches pour continer   ");
		scanf("%d",&tmp);
	}
	
	
 }
}
