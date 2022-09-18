#include "biblio.h" 

struct information info;
struct hostent *h;

int main()
{

	pid_t ret;
	ret=fork();
	if(ret==0)
		execlp("clear","clear",NULL,NULL);
	else
	{
		wait();
		int sock,n;
		printf("\t\t****************************\n");
		printf("\t\t*          CLIENT          *\n");
		printf("\t\t****************************\n\n");	
		n=1;

		/*Le client entre son nom, ceci est en dehors de la boucle pour que le client n'est pas saisir son nom plusieur fois s'il a plusieurs commande */
		printf("Entrez votre nom \n->");
		scanf("%s",info.nom);
		while(n==1)
		{
			/*création du socket et gestion d'erreur*/
			if ((sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
			{
				perror("socket");
				exit(1);
			}
			
			
			if(!(h=gethostbyname("192.168.1.6")))
			{
				perror("gethosnyname");
				exit(3);
			}
			
			
			/* la zone mémoire pour l'adresse est mise à 0 */
			bzero(&sin, sizeof(sin));
			sin.sin_family=AF_INET;
			bcopy(h->h_addr, &sin.sin_addr, h->h_length);
			sin.sin_port=htons(PORTS);
			
			
			/*connection du socket à l'adresse spécifiée dans la structure sockaddr*/
			if(connect(sock,(struct sockaddr*)&sin,sizeof(sin))<0)
			{
				perror("connect");
				exit(2);
			}
			
			/*Commande(info entré par l'utilisateur)*/
			printf("\nEntrez le nom du produit que vous voulez commander \n->");
			scanf("%s",info.nomP);
			printf("Entrez la quantité voulu \n->");
			scanf("%d",&info.qte);
			
			//envoie des donnée au serveur à travers le socket
			write(sock,&info,sizeof(struct information));
			recv(sock,&info, sizeof(struct information), 0);
			close(sock);	
			if(info.prix!=0)
				printf("Client : M./Mme %s\tProduit: %s\tQté: %d\tPrix_unitaire: %d Fcfa\tPrix total: %d Fcfa\n",info.nom,info.nomP,info.qte,info.prix,info.total);
			else
				printf("Le produit : %s que vous avez commander n'est pas disponible \n",info.nomP);	
			/*Permet a l'utilisateur de recommencer à souhait*/		
			printf("\n\nVoulez vous passer une autre commande ?\n");
			printf("Taper 1 pour continuer et tous autres touche pour arrêter\n->");
			scanf("%d",&n);
		}
	}		
}











