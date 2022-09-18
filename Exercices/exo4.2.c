
#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

/*
Exercice 4.2 Reprendre les programmes de l’exercice. Nous allons faire un
programme qui fait la même chose, mais transmet les données
différemment. Dans le programme père, on liera les flots stdout et stdin à
un tube.
*/

int main()
{
char chaine[10];
char chaine1[2];
char mot[10];
int pip[2],pip1[2],i,j,fd,ret;
pid_t retour;
pipe(pip);
pipe(pip1);
retour=fork();
if(retour==0)
{
/* Le fils écrit dans le tube */
	printf("Entrez le mot à rechercher\t");
	scanf("%s",chaine);
	close(pip[0]);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);

//Le fils lit le tube 
	
	close(pip1[1]);
	if(read(pip1[0],chaine1,2)!=2)
	close(pip1[0]);
	printf("***%s*** se répète %d fois\n",chaine,atoi(chaine1));
	exit(0);
}
else
{
/* Le père lit le tube */sleep(3);
	close(pip[1]);
	dup2(pip[0], STDIN_FILENO);
	scanf(STDIN_FILENO, "%s", chaine);
	close(pip[0]);
	printf("Le mot a rechercher est %s\n",chaine);
//ouverture du fichier mot.txt
	fd=open("mot.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	ret=lseek(fd,0,SEEK_SET);
	if(ret==-1)
  		perror("problème de lseek");
	j=0;
	i=0;
	while(i<4)
	{
		read(fd,mot,sizeof(mot));
		printf("%s\n",mot);
		if(strcmp(mot,chaine)==0)
		{

			j=j+1;
		}
		i=i+1;
	}
	close(fd);
	sprintf(chaine1,"%d",j);
	
/* Le père écrit dans le tube */
	close(pip1[0]);
	write(pip1[1],chaine1,2);
	close(pip1[1]);
	//wait();
	printf("père ***%s*** se répète %d fois",chaine,j);
}
}

