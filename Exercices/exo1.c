#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*Écrire un programme qui crée un fils. Le père doit afficher “je 
suis le père” puis afficher son PID et le fils doit afficher “je suis le fils” 
puis afficher son PID.*/


int main()
{
pid_t ret;
ret=fork();
if(ret==0)
{
    
    printf("je suis le fils; mon pid est %d \n",getpid());
   
}
else
{
    printf("je suis le père; mon pid est %d\n",getpid());
}
}    
