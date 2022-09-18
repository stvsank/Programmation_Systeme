#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

/*
Exercice 4.4 Même question qu’à l’exercice précédent mais en passant les
descripteurs de tube comme variables d’environnement.
*/

int main()
{
char assignation[15];
char assignation1[15];
char chaine[10];
char chaine1[10];
char chaine2[10];
char mot[10];
int pip[2],i,j;
pid_t retour;
pipe(pip);
 /* conversion de entier vers caractère */
 sprintf(chaine1,"%d",pip[0]);
 sprintf(chaine2,"%d",pip[1]);
 sprintf(assignation1, "HOME=%s",chaine1);
 putenv(assignation1);
 sprintf(assignation, "PATH=%s",chaine2);
 putenv(assignation);

retour=fork();
if(retour==0)
{
	//kill(getpid(),SIGSTOP);
char * argv[] = {"exo4.4.affiche",NULL};
	execv("/home/sss/Documents/Prog sys/exo4.4.affiche",argv);
	printf("Error\n");
}
else
{

/* Le père écrit dans le tube */
	printf("Entrez le message que vous voulez\n"); 
	scanf("%s",chaine);	
	close(pip[0]);
	write(pip[1],chaine,10);
	close(pip[1]);
	//kill(retour,SIGCONT);
	//wait();

}
}
