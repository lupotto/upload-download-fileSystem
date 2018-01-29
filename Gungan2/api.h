//
//  api.h
//  LsTransfer
//
//  Created by Alex Gracia Lupotto on 21/10/15.
//  Copyright © 2015 Alex Gracia Lupotto. All rights reserved.
//

#ifndef api_h
#define api_h
#define TECLADO 1
#define PANTALLA 0
#define MAXC 100
#define MAXP 51
#include <string.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<sys/msg.h> 
#include<sys/time.h>
#include<sys/select.h>
#include <pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

extern int sock;
extern char* comanda;

#define TIPO_TRAMA 5
#define INFO_PPAL 10
#define DATA 100
#define TRAMA 115

typedef struct {
	char tipoTrama[TIPO_TRAMA+1];
	char infoPpal[INFO_PPAL+1];
	char data[DATA+1];
}Trama;

typedef struct {
    char nomUsuari[MAXC];
    char ipUsuari[MAXC];
    int portTCP;
}Usuari;

Usuari llegirFitxerConfig();
int identificaComanda(char* comanda);
int llegeixComanda(char* comanda);
int contaEspais(char* comanda);
void treuEspais();
void executaComandaUNIX(char *argv[]);
int parseComandaUNIX(char* line, char *argv[]);
char* existeixFitxer(char* comanda);
void myPrint(char* sOut);
int connexio(Usuari usuari);
Trama parseTrama(char* tramaInput);
char* buildTrama(Trama trama);
int preparaSocket (Usuari usuari);
void enviaTramaCON (int sock, Usuari usuari);
void exitGungan(int i);
int tipusTrama(Trama trama);
Trama llegeixTrama ();
void enviaTramaDCON (int sock);
void gestionaUpload(char* comanda, Usuari usuari);
void gestionaComandaUnix(char* comanda,char* argv[]);
void gestionaDownload(char* comanda, Usuari usuari);
void gestionaExit(int sock);
void enviaTramaUPLD(char* comanda);
void creaForkGunganUpload(int port, Usuari usuari, char* nomFitxer);
void creaForkGunganDownload(int port, Usuari usuari, char* nomFitxer);
int preparaSocketUPLD(int port, Usuari usuari);
int connexioUPLD(int port, Usuari usuari);
void enviaTramaINIT();
int getPortUpload();
int getMidaFitxer(int fd);
void enviaTramaDATA (int sock, Trama trama, int restant);
void extreuBytes(int midaFitxer,int restant, int fd, char nBytes[DATA+1]);
void enviaTramaMD5(char* nomFitxer);
void enviaTramaMD5(char* nomFitxer);
void enviaTramaP_QRY();
void mostraDownloadsPendents(Trama trama);


#endif /* api_h */
