
#include "biblio.h" 
void * traitement(void *arg);
void fic_uniq(FILE *fd, char *DATE,struct information info);
void creation_historique(FILE *fd, char *DATE,struct information info);
void aff_et_env_prix(int newsock,struct information info);
struct information recherche(FILE *fd,struct information info);

int num=1;

int main(argc,argv)
{
	pid_t ret;
	ret=fork();
	if(ret==0)
		execlp("clear","clear",NULL,NULL);
	else
	{
		wait();	
		pthread_t thread[N];
		int i,sock,newsock,namelen;
		printf("\t\t****************************\n");
		printf("\t\t*         SERVEUR          *\n");
		printf("\t\t****************************\n\n");	
		
		/*création du socket et gestion d'erreur*/ 
		if((sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		{
			perror("socket");
			exit(1);
		}
		
		/* la zone mémoire pour l'adresse est mise à 0 */
		bzero(&sin,sizeof(sin));

		/*Définissons l'adresse d'application associée au socket*/
		sin.sin_family=AF_INET;
		sin.sin_port=htons(PORTS); /* passage au format réseau */
		sin.sin_addr.s_addr=INADDR_ANY; /* n'importe quelle adresse ip de la machine locale */
		
		/*attachons l'adresse au socket et gestion d'erreur*/ 
		if(bind(sock,(struct sockaddr*)&sin,sizeof(sin))<0)
		{
			perror("bind");
			exit(2);
		}
		printf("Attente de requete \n");
		/*définissons la taille de la file de connexions en attente du socket*/
		if(listen(sock,5)<0)
		{
			perror("listen");
			exit(3);
		}
		i=0;
		
		while(1)
		{
			if((newsock=accept(sock,(struct sockaddr*)&sin,&namelen))<0)
			{
				perror("accept");
				exit(4);
			}
			printf("\nRequếte %d \n",i+1);
			pthread_create(&thread[i], NULL, traitement, (void *) newsock);
			i++;
		}
	}
}

void * traitement(void *arg)
{
	int newsock=(int)arg;
	char DATE[50];
	
	FILE * fd = NULL;
	time_t t = time(NULL);
	
	 	
	struct information info;
	struct tm *timeptr;
	
	info.prix=0;
	time_t temp = time(NULL);
	timeptr = localtime(&temp);
	
	/*création d'une chaine de caractère unique avec la date(isentifiant)*/
	strftime(DATE,sizeof(DATE),"commande_%a_%b_%d_%Y_%T.txt", timeptr);

	recv(newsock,&info, sizeof(struct information), 0);
	info.prix=0;
	/*Recherche du prix du produit commandé*/
	info=recherche(fd,info);

	/*affichage du prix et envoie au client*/
	aff_et_env_prix(newsock,info);
	
	/*création du fichier de commande individuel*/
	fic_uniq(fd,DATE,info);
	
	/*création d'un fichier d'historique qui contient toutes les commandes*/
	/*l'accès au fichier historique.txt doit être protégé car plusieur processus ne doivent pas y acceder simultanément*/
	creation_historique(fd, DATE,info);
}

void fic_uniq(FILE *fd, char *DATE,struct information info)
{
	fd=fopen(DATE,"w");
	if(fd==-1)
		perror("problème d'ouverture");
  	fprintf(fd,"Nom_client: %s\tNom_produit: %s\tQté: %d\tprix_unitaire: %d Fcfa\tprix_total: %d Fcfa\n",info.nom,info.nomP,info.qte,info.prix,info.total);
	fclose(fd);

}

void creation_historique(FILE *fd, char *DATE,struct information info)
{
	pthread_mutex_lock(&mutex);
	fd=fopen("historique.txt","a");
	if(fd==-1)
		perror("problème d'ouverture");
  	fprintf(fd,"Num: %d\tNom: %s\tNom_Produit: %s\tQté: %d\tPrix_unit: %d Fcfa\t Prix_total: %d Fcfa\tFichier:%s\n",num,info.nom,info.nomP,info.qte,info.prix,info.total,DATE);
	fclose(fd);
	num++;
	pthread_mutex_unlock(&mutex);
}

void aff_et_env_prix(int newsock,struct information info)
{
	if(info.prix!=0)
		printf("Client : M./Mme %s\tProduit: %s\tQté: %d\tPrix_unitaire: %d Fcfa\tPrix total: %d Fcfa\n",info.nom,info.nomP,info.qte,info.prix,info.total);
	else
		printf("Le produit : %s que Monsieur %s a commandé n'est pas disponible \n",info.nomP,info.nom);	
		
	write(newsock, &info,sizeof(struct information));
	close(newsock);
}


struct information recherche(FILE *fd,struct information info)
{
	char nom_produit[30];
	int prix;
	fd=fopen("base_de_donnee.txt","r");
	if(fd==-1)
		perror("problème d'ouverture");
	while(!feof(fd))
  	{
  		fscanf(fd,"Nom_produit: %s\t\tPrix: %d Fcfa\n",nom_produit,&prix);
		if (strcmp(nom_produit,info.nomP)==0)
			info.prix=prix;
	}
	close(fd);
	info.total=info.qte*info.prix;
	return(info);
}






