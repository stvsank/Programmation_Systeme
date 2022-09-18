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
int fd, i, entier,ret,fp;
pid_t pid;

pid=getpid();
printf(" mon pid est %d\n",pid);
//enregistrement du pid
fp=open("/tmp/pid.txt", O_WRONLY);
ret=lseek(fp,0,SEEK_SET);
write(fp, &pid, sizeof(pid));
close(fp);
kill(pid,SIGSTOP);
//lecture
fd=open("/tmp/entier.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
ret=lseek(fd,0,SEEK_SET);
if(fd==-1)
  perror("problème d'ouverture");
i=1;
while(i<=1)
{
read(fd,&entier,sizeof(entier));
printf("ENTIER = %d\n",entier);
i=i+1;
}
close(fd);
}
