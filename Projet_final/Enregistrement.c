#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

struct enregistrement 
{
	char nomP[30];
	int prix;
}; 


int main()
{	
	pid_t ret;
	ret=fork();
	if(ret==0)
		execlp("clear","clear",NULL,NULL);
	else
	{
		wait();
		struct enregistrement info;
		int ret,n,i;
		FILE * fd = NULL;
	  	printf("\t\t*************************************\n");
		printf("\t\t*           ENREGISTREMENT          *\n");
		printf("\t\t*************************************\n\n");	
			
		//création du fichier de commande
		fd=fopen("base_de_donnee.txt","a+");
		if(ret==-1)
	  		perror("problème de fseek");
	  		
	  	//Enregistrement
	  	printf("Combien d'enregistrement voulez vous faire ? \n->");
	  	scanf("%d",&n);
	  	i=0;
	  	while(i<n)
	  	{
	  		ret=fseek(fd, 0, SEEK_END);
		  	printf("\nEntrez le nom du produit que vous voulez enregistrer \n->");
			scanf("%s",info.nomP);
			printf("Entrez le prix du produit \n->");
			scanf("%d",&info.prix);
	  		fprintf(fd,"Nom_produit: %s\t\tPrix: %d Fcfa\n",info.nomP,info.prix);
			i++;
		}
		fclose(fd);
		
		//affichage de toute la base de donnée
		fd=fopen("base_de_donnee.txt","r");
		if(fd==-1)
			perror("problème d'ouverture");
		ret=fseek(fd,0,SEEK_SET);
		//if(ret==-1)
	  	//	perror("problème de fseek");
	  	printf("\t\t*************************************\n");
		printf("\t\t*           BASE DE DONNEE          *\n");
		printf("\t\t*************************************\n\n");	

		while(!feof(fd))
	  	{
	  		fscanf(fd,"Nom_produit: %s\t\tPrix: %d Fcfa\n",info.nomP,&info.prix);
	  		printf(" Nom produit : %s \t Prix : %d Fcfa\n",info.nomP,info.prix);
		}
		fclose(fd);
	}
}










