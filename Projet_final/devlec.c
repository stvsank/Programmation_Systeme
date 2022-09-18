#include "biblio.h" 

void affiche(FILE *fd, char *DATE,struct information info);
void affiche_hist(FILE *fd, char *DATE,struct information info);
void recherche(FILE *fd, char *DATE,struct information info);

int main(int argc, char** argv)
{
	pid_t ret;
	ret=fork();
	if(ret==0)
		execlp("clear","clear",NULL,NULL);
	else
	{
		wait();
		struct information info;
		char DATE[50];
		int n=1;
		FILE * fd = NULL;
		printf("\t\t********************************\n");
		printf("\t\t*          HISTORIQUE          *\n");
		printf("\t\t********************************\n\n");
		
		/*affichage de l'historique*/
		affiche_hist(fd,DATE,info);
		
		while(n==1)
		{
			/*recherche et affiche le fichier demandé par l'utilisateur*/
			recherche(fd,DATE,info);
			
			/*Permet a l'utilisateur de recommencer à souhait*/	
			printf("\n\nVoulez vous ouvrir un autre fichier ?\n");
			printf("Taper 1 pour continuer et tous autres touches pour arrêter\n->");
			scanf("%d",&n);
		}	
	}
}


	
void affiche_fic(FILE *fd, char *DATE,struct information info)
{
	fd=fopen(DATE,"r");
	if(fd==-1)
		perror("problème d'ouverture");
	fscanf(fd,"Nom_client: %s\tNom_produit: %s\tQté: %d\tprix_unitaire: %d Fcfa\tprix_total: %d Fcfa\n",info.nom,info.nomP,&info.qte,&info.prix,&info.total);
	printf("\nNom_client: %s\tNom_produit: %s\tQté: %d\tPrix_unitaire: %d Fcfa\tPrix_total: %d Fcfa\n",info.nom,info.nomP,info.qte,info.prix,info.total);
	close(fd);
}
	
void affiche_hist(FILE *fd, char *DATE,struct information info)
{
	int i;
	fd=fopen("historique.txt","r");
	if(fd==-1)
		perror("problème d'ouverture");
	while(!feof(fd))
	{
		fscanf(fd,"Num: %d\tNom: %s\tNom_Produit: %s\tQté: %d\tPrix_unit: %d Fcfa\t Prix_total: %d Fcfa\tFichier:%s\n",&i,info.nom,info.nomP,&info.qte,&info.prix,&info.total,DATE);	
		printf("Num: %d\tNom: %s\tNom_Produit: %s\tQuantité: %d\tPrix_unitaire: %d Fcfa\t Prix_total: %d Fcfa\tFichier:%s\n",i,info.nom,info.nomP,info.qte,info.prix,info.total,DATE);
		}	
	close(fd);
}

void recherche(FILE *fd, char *DATE,struct information info)
{
	int i,cmd;
	printf("\nQuel fichier de commande voulez vous afficher ?\nEntrez le numéro\n->");
	scanf("%d",&cmd);
	fd=fopen("historique.txt","r");
	if(fd==-1)
		perror("problème d'ouverture");
	while(!feof(fd))
	{
		fscanf(fd,"Num: %d\tNom: %s\tNom_Produit: %s\tQté: %d\tPrix_unit: %d Fcfa\t Prix_total: %d Fcfa\tFichier:%s\n",&i,info.nom,info.nomP,&info.qte,&info.prix,&info.total,DATE);
		if(i==cmd)
		{
			affiche_fic(fd,DATE,info);
			cmd=0;
		}
	}
	if(cmd!=0)
	{
		printf("\nNuméro invalide\n");	
	}
	close(fd);
}



	
	
	
	
