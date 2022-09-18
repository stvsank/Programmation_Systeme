#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>


/*
Exercice 3.2 Ecrire un programme saisit.c qui saisit un int au clavier, et
l’enregistre dans un fichier /tmp/entier.txt. Écrire un programme affiche.c
qui attend (avec sleep) un signal utilisateur du programme saisit.c.
Lorsque l’entier a été saisi, le programme affiche.c affiche la valeur de
l’entier.
*/

int main()
{
int fp,nombr,ret,fd;
pid_t pid;
//écriture
fp=open("/tmp/entier.txt", O_WRONLY);
ret=lseek(fp,0,SEEK_SET);
printf("Donnez moi l'entier \n");
scanf("%d",&nombr);
write(fp, &nombr, sizeof(nombr));
close(fp);

//lecture pid
fd=open("/tmp/pid.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
ret=lseek(fd,0,SEEK_SET);
read(fd,&pid,sizeof(pid));
close(fd);
printf("le pid est %d\n",pid);
kill(pid,SIGCONT);
exit(0);
}
