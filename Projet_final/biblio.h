#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<signal.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

#define PORTS 6260 /* port du serveur */
#define N 200


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

struct sockaddr_in sin;
struct sockaddr_in adresse_client;

struct information 
{
	char nomP[30];
	int qte;
        char nom[30];
        int prix;
        int total;
}; 




