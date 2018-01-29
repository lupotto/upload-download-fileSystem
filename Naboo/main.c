#include "api.h"


int fdSocket, memid;

int* freePortFlag;
semaphore* freePortSem;

semaphore sem;


void ksighandler(int signum){
    char text[MAXC];
    switch (signum){
        case SIGINT:
        	close (fdSocket);
        	//CLOSE SHMEM & SEMS
        	destroySemafors();
        	freeSharedMem();
            sprintf(text,"\n\nSocket, memòria compartida i semàfors alliberats, A10!\n\n");
            write(PANTALLA,text,strlen(text));
            exit(1);
        break;
        default:
        break;
    }
}

int main ()
{
	//*** INIT ***
	Config server;
	char text[MAXC];
	int fdSocket, newsockfd, pid;
	Trama trama;

	signal(SIGINT, ksighandler);

	freePortFlag = (int *) malloc (sizeof(int)*9);

	if (freePortFlag==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    freePortSem = (semaphore *) malloc (sizeof(semaphore)*9);

    

	if (freePortSem==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

	//*** INICIALITZA SEMAFORS ***
	inicialitzaSemafors();
	if (SEM_constructor(&sem) == 0){
        //printf("hola\n");
        SEM_init(&sem, 1);
    }

	//*** INICIALITZA MEM COMPARTIDA ***
	inicialitzaSharedMem();

	//*** LLEGIR EL FITXER ***
	server = llegirFitxerConfig();

	//*** PREPARAR EL SOCKET ***
	fdSocket = preparaSocketFd(server.port);

	struct sockaddr_in cliente_addr;
	socklen_t cliente_len = sizeof(cliente_addr);


	//*** COMENÇA A ESCOLTAR ***
	sprintf(text,"Sense conexions\n");
	write(1,text,strlen(text));

	while (1) {
		//*** ESPERO NOVA CONEXIÓ***
      	newsockfd = accept(fdSocket, (void *)&cliente_addr, &cliente_len);

      	if (newsockfd < 0) {
      		//*** ERROR ***
        	sprintf(text,"ERROR al accept\n");
			write(1,text,strlen(text));
        	//exit(1);

      	}else{
      		//*** CREAR SERVIDOR DEDICAT ***
		    pid = fork();

		    if (pid < 0) {
		    	//*** ERROR ***
		        sprintf(text,"ERROR al crear el fork\n");
				write(1,text,strlen(text));

				enviaTramaKO(newsockfd);

		        close(newsockfd);
		        exit(-1);

		    }else if (pid == 0) {
		    	//*** SERVIDOR DEDICAT ***
		        close(fdSocket);
		        char gunganName[INFO_PPAL+1];

		        
		        //*** ESPERO TRAMA CON ***
			    trama = llegeixTrama(newsockfd);

			    if(strcmp(trama.tipoTrama, "CON")==0){
			    	//*** NEW GUNGAN ***
					strcpy(gunganName, trama.infoPpal);
					sprintf(text,"New gungan %s\n",trama.infoPpal);
					write(1,text,strlen(text));

					enviaTramaOK(newsockfd);


					//*** ESPERO TRAMA P_QRY ***
					trama = llegeixTrama(newsockfd);

					//*** ENVIO TRAMA D_QRY ***
					enviaTramaD_QRY(newsockfd, gunganName);

					if(strcmp(trama.tipoTrama, "P_QRY")==0){
						//*** CONEXIÓ OBERTA ***
						while (1){
							//*** ESPERO TRAMA ***
							trama = llegeixTrama(newsockfd);

							//printf("[DEBUG] TramaUpload: TIPO--> %s\n", trama.tipoTrama);
							//printf("[DEBUG] TramaUpload: fitxer--> %s\n", trama.infoPpal);
							//printf("[DEBUG] TramaUpload: DATA--> %s\n", trama.data);
							

							//*** GESTIONO TRAMA ***
							gestionaTrama (newsockfd, trama, gunganName, server.port, server.timeOut);
						}
					}else{
						sprintf(text,"ERROR esperaba trama P_QRY\n");
						write(1,text,strlen(text));
					}

				}else{
					sprintf(text,"ERROR esperaba trama CON\n");
					write(1,text,strlen(text));
				}

				close(newsockfd);     
		        exit(0);
		    }
		    else {
		        close(newsockfd);
		    }
		}	
   } 

	return 1;
}
