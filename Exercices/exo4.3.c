#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

/*
Exercice 4.3 Écrire un programme qui crée un tube, crée un processus fils,
puis, dans le fils, lance par execv un autre programme, appelé programme
fils. Le programme père transmets les descripteurs de tubes au
programmes fils en argument, et transmet un message au fils par le tube.
Le programme fils affiche le message.
*/

int main()
{
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
retour=fork();
if(retour==0)
{
char * argv[] = {"exo4.3.affiche", chaine1,chaine2,NULL};
	execv("/home/sss/Documents/Prog sys/exo4.3.affiche",argv);
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

}
}
