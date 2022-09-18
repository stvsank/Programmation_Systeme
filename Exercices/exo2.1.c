#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*
Écrire un programme qui prend deux arguments en ligne de
commande en supposant que ce sont des nombres entiers, et qui affiche
l’addition de ces deux nombres.
*/

int main(int argc, char **argv)
{
int somme;
//gestion des erreurs pour cela on utilise argc qui contient le nom du programme et les valeurs entrées en paramètre 
if(argc != 3)//dans notre cas 2 valeurs sont en entrée + le nom du programme dc 3
{
printf("Erreur paramètres\n");
exit(0);
}
somme=atoi(argv[1]) + atoi(argv[2]); /* atoi: conversion entier à caractère */
printf("\nLa somme de  %d  et de  %d  est %d\n",atoi(argv[1]),atoi(argv[2]),somme);
exit(0);
}
