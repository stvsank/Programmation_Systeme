#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>//permet d'utiliser sleep
#include<time.h>//permet d'utiliser time

/*
Exercice 2.5 Écrire un programme qui saisit des nom de fichiers texte au
clavier et ouvre tous ces fichiers dans l’éditeur de votre choix. Le
programme doit se poursuivre jusqu’à ce que l’utilisateur demande de
quitter.
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
		printf("\nEntrez le nom du fichier :  ");
		scanf("%s",txt);
		execlp("gedit","gedit",txt,NULL);
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
