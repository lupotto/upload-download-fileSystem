#if !defined( API_H )
#define api_h
#define TECLADO 1
#define PANTALLA 0
#define MAXC 100
#define MAXP 51

#include "semaphore.h"
#include "list.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/msg.h> 
#include<sys/stat.h>
#include<sys/time.h>
#include<sys/select.h>
#include<sys/wait.h>
#include <pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include <sys/types.h>
#include <sys/shm.h>

#define TIPO_TRAMA 5
#define INFO_PPAL 10
#define DATA 100
#define TRAMA 115

typedef struct 
{	
	int timeOut;
	int port;
}Config;

typedef struct 
{
	char tipoTrama[TIPO_TRAMA+1];
	char infoPpal[INFO_PPAL+1];
	char data[DATA+1];
}Trama;

/*typedef struct
{
	semaphore sem1;
	semaphore sem2;
	semaphore sem3;
}FreePortSem;
*/
extern int* freePortFlag;
extern semaphore* freePortSem;
extern semaphore sem;
extern int memid;

Config llegirFitxerConfig();
Trama parseTrama(char tramaInput[TRAMA]);
char* buildTrama(Trama trama);
void enviaTramaKO (int newsockfd);
void enviaTramaOK (int newsockfd);
int preparaSocketFd(int port);
void gestionaTrama(int newsockfd, Trama trama, char gunganName[INFO_PPAL+1], int portBase, int timeOut);
Trama llegeixTrama (int newsockfd);
void inicialitzaSemafors();
void inicialitzaSharedMem();
void destroySemafors();
void freeSharedMem();
int getNomUsers(char* line, char *argv[]);
int getNextPort(int portBase);
void treuEspais (char* comanda);
void enviaTramaPort (int port, int newsockfd);
char* getMd5FromFile(char* nomFitxer);
void enviaTramaD_QRY(int newsockfd, char gunganName[INFO_PPAL+1]);
void enviaTramaOKmd5 (int newsockfd);
void enviaTramaKOmd5 (int newsockfd);
void freePort (int i);
void gestionaUpload(int newsockfd, Trama trama, int portBase);
void gestionaDownload(int newsockfd, Trama trama, int portBase, char gunganName[INFO_PPAL+1], int timeOut);


#endif 
