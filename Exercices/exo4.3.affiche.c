#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char **argv)
{
char chaine[10];
int pip[2];
pip[0]=atoi(argv[1]);
pip[1]=atoi(argv[2]);
//lecture 
close(pip[1]);
read(pip[0],chaine,10);
close(pip[0]);
printf("Votre message est %s\n",chaine);

} 
