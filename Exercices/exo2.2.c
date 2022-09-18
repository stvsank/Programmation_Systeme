#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>//permet d'utiliser sleep
#include<time.h>//permet d'utiliser time

/*
Écrire un programme qui prend en argument un chemin vers
un répertoire R, et copie le répertoire courant dans ce répertoire R.
*/

int main(int argc, char **argv)
{
//gestion des erreurs pour cela on utilise argc qui contient le nom du programme et les valeurs entrées en paramètre 
if(argc != 2)//dans notre cas 1 valeurs sont en entrée + le nom du programme dc 2
{
printf("Erreur paramètres\n");
exit(0);
}
else
{
	execlp("cp","cp","-r","/home/sss/Documents/Prog sys/",argv[1],NULL);
}



}
