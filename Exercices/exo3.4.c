#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>//permet d'utiliser sleep
#include<time.h>//permet d'utiliser time
#include<signal.h>
#include<fcntl.h>

/*
Exercice 3.4 Ecrire un programme qui saisit les valeurs d’un tableau
d’entier tab de n éléments alloué dynamiquement. L’entier n sera saisi au
clavier. Le programme affiche la valeur d’un élément tab[i] où i est saisi au
clavier. En cas d’erreur de segmentation le programme fait ressaisir la
valeur de i avant de l’afficher.
*/


//< > i
//rand()%11 pour créer aléatoirement des valeurs de 0à10

void gestion_segmentation();
int tmp=0;
int fin=0;
int main()
{
int i,j;
//sigset_t sign;
//sigemptyset(&sign);
if(signal(SIGSEGV, gestion_segmentation)==SIG_ERR)
{
perror("signal");
exit(1);
}
if(tmp==0)
{
	printf("Entrez le nombre d'élement que vous voulez creer : \n");
	scanf("%d",&fin);
}
	int tab[fin];
	i=0;
	for (j=0;j<=fin-1;j++)
	{
		tab[j]=rand()%11;
		printf("entier %d\t",tab[j]);
	}
	printf("entier %d",tab[j]);
if(tmp==0)
{
	printf("Entrez le numéro de l'entier que vous voulez afficher \n");
	scanf("%d",&i);
	printf ("L'élement numéro %d du tableau est %d",i,tab[i-1]);
}
else
{	
	printf("Entrez un nouveau numéro d'entier que vous voulez afficher \n");
	scanf("%d",&i);
	printf ("L'élement numéro %d du tableau est %d",i,tab[i-1]);
}
}
void gestion_segmentation()
{
	printf("\nErreur de segmentation\n\n");
	tmp=tmp+1;
	main();
	exit(0);
}




