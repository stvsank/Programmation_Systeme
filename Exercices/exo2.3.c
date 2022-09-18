#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>//permet d'utiliser sleep
#include<time.h>//permet d'utiliser time

/*
Exercice 2.3 Écrire un programme qui saisit un nom de fichier texte au
clavier et ouvre ce fichier dans l’éditeur de votre choix.
*/

int main(int argc, char **argv)
{
char txt[60];
printf("Entrez le nom du fichier :  ");
scanf("%s",txt);
execlp("gedit","gedit",txt,NULL);
}
