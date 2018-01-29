#include "api.h"



void enviaTramaKO (int newsockfd){
    Trama trama;
    char* tramaOutput;
    char text[MAXC];

    tramaOutput = malloc(TRAMA * sizeof(char));

    if (tramaOutput==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

    strcpy(trama.tipoTrama,"KO");

    tramaOutput = buildTrama(trama);

    //printf("[DEBUG] Enviant trama KO \n");

    write(newsockfd, tramaOutput, TRAMA);

    free (tramaOutput);
}

void enviaTramaKOmd5(int newsockfd){
    Trama trama;
    char* tramaOutput;
    char text[MAXC];

    tramaOutput = malloc(TRAMA * sizeof(char));

    if (tramaOutput==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

    strcpy(trama.tipoTrama,"KO");
    strcpy(trama.data,"Darth Vader segueix viu");

    tramaOutput = buildTrama(trama);

    //printf("[DEBUG] Enviant trama KO \n");

    write(newsockfd, tramaOutput, TRAMA);

    free (tramaOutput);
}

void enviaTramaOK (int newsockfd){
    Trama trama;
    char* tramaOutput;
    char text[MAXC];

    tramaOutput = malloc(TRAMA * sizeof(char));

    if (tramaOutput==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

    strcpy(trama.tipoTrama,"OK");

    tramaOutput = buildTrama(trama);

    //printf("[DEBUG] Enviant trama OK \n");
    write(newsockfd, tramaOutput, TRAMA);
    free (tramaOutput);
}

void enviaTramaInit (int newsockfd){
    Trama trama;
    char* tramaOutput;
    char text[MAXC];

    tramaOutput = malloc(TRAMA * sizeof(char));

    if (tramaOutput==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

    strcpy(trama.tipoTrama,"INIT");

    tramaOutput = buildTrama(trama);

    //printf("[DEBUG] Enviant trama INIT\n");
    write(newsockfd, tramaOutput, TRAMA);
    free (tramaOutput);
}

void enviaTramaOKmd5 (int newsockfd){
    Trama trama;
    char* tramaOutput;
    char text[MAXC];

    tramaOutput = malloc(TRAMA * sizeof(char));

    if (tramaOutput==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

    strcpy(trama.tipoTrama,"OK");
    strcpy(trama.data,"Darth Vader segueix viu");


    tramaOutput = buildTrama(trama);

    //printf("[DEBUG] Enviant trama OK \n");
    write(newsockfd, tramaOutput, TRAMA);
    free (tramaOutput);
}

void enviaTramaD_QRY(int newsockfd, char gunganName[INFO_PPAL+1]){
    int fitxerUsuariFd;
    int nBytes;
    Trama trama;
    char* tramaOutput;
    char text[MAXC];
    char character[2];
    int i = 0;

    tramaOutput = malloc(TRAMA * sizeof(char));

    if (tramaOutput==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

    strcpy(trama.tipoTrama,"D_QRY");

    //populate data
    SEM_wait(&sem);
    sprintf(text, "%s.db", gunganName);
    fitxerUsuariFd = open (text,O_RDONLY);
    if (fitxerUsuariFd<0){

    }else{
        //printf("[DEBUG] D_QRY Fitxer %s exiteix\n", text);
        nBytes=read(fitxerUsuariFd, character, 1);
        while(nBytes > 0){
            //get 1 file name
            while (character[0]!= '\n' && nBytes>0){
                trama.data[i] = character[0];
                nBytes=read(fitxerUsuariFd, character, 1);
                i++;
            } 
            nBytes=read(fitxerUsuariFd, character, 1);

            //throw 1 file ts
            while (character[0]!= '\n' && nBytes>0){
                nBytes=read(fitxerUsuariFd, character, 1);
            } 
            nBytes=read(fitxerUsuariFd, character, 1);

            if (nBytes>0){
                while (i%10!=0) i++; 
            }
        }
        close(fitxerUsuariFd);
    }


    SEM_signal(&sem);



    tramaOutput = buildTrama(trama);

    //printf("[DEBUG] Enviant trama D_QRY \n");
    write(newsockfd, tramaOutput, TRAMA);
    free (tramaOutput);
}

void enviaTramaPort (int port, int newsockfd){
    Trama trama;
    char* tramaOutput;
    char text[MAXC];
    char* portString;

    portString = malloc(INFO_PPAL * sizeof(char));

    if (portString==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    tramaOutput = malloc(TRAMA * sizeof(char));

    if (tramaOutput==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

    strcpy(trama.tipoTrama,"PORT");
    sprintf(portString, "%d", port);
    strcpy(trama.infoPpal, portString);

    tramaOutput = buildTrama(trama);

    //printf("[DEBUG] Enviant trama PORT \n");
    write(newsockfd, tramaOutput, TRAMA);
    free (tramaOutput);
}

void enviaTramaMD5(int sock, char* nomFitxer){
  char* tramaOutput;
  char text[MAXC];
  Trama trama;

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exit(-1);
  }

  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  bzero(trama.data, sizeof(trama.data));

  strcpy(trama.tipoTrama,"MD5");
  strcpy(trama.data, getMd5FromFile(nomFitxer));

  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama MD5 \n");
  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
}

void extreuBytes(int midaFitxer, int restant, int fd, char nBytes[DATA+1]){
  //midaFitxer = 356 // restant == 356
  //Ens retorna els bytes que llegim del fitxer
  int offset;
  //nBytes = malloc(DATA*sizeof(char)+1);
  offset=midaFitxer-restant;
  bzero (nBytes, DATA);
  lseek(fd,(off_t)offset,SEEK_SET);
  if (restant >= 100){
    read(fd,nBytes,100);
  }else{
    read(fd,nBytes,restant);
  }

  //printf("DATA: %s\n", nBytes);
}

void enviaTramaDATA (int sock, Trama trama, int restant){
  char* tramaOutput;
  char text[MAXC];
  char buffer[2];

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exit(-1);
  }
  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  //bzero(trama.data, sizeof(trama.data));

  strcpy(trama.tipoTrama,"DATA");
  //itoa(restant, buffer, 10);
  sprintf(buffer, "%d", restant);
  strcpy(trama.infoPpal, buffer);
  //strcpy(trama.data,dataTramaDATA);
  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama DATA \n");
  //printf("[DEBUG] Restant: %s \n", trama.infoPpal);

  //printf("DATA: %s\n", trama.data);

  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
}

int borrarUsuariFitxer (char nomFitxer[11], char gunganName[INFO_PPAL+1]){
    FileInfo e;
    int fitxerUsuariFd;
    int nBytes;
    char text[MAXC];
    char character[2];
    int i = 0;
    node_t * list = NULL;
    int index;

    SEM_wait(&sem);

    sprintf(text, "%s.db", gunganName);
    fitxerUsuariFd = open (text,O_RDONLY);
    if (fitxerUsuariFd<0){
        close(fitxerUsuariFd);
        SEM_signal(&sem);
        return 0;
    }else{
        //printf("[DEBUG] Borrar %s \n", text);

        nBytes=read(fitxerUsuariFd, character, 1);

        bzero (e.name, 11);
        bzero (e.ts, 20);

        //get 1 file name
        i=0;
        while (character[0]!= '\n' && nBytes>0){
            e.name[i] = character[0];
            nBytes=read(fitxerUsuariFd, character, 1);
            i++;
        } 
        nBytes=read(fitxerUsuariFd, character, 1);
        i=0;
        //throw 1 file ts
        while (character[0]!= '\n' && nBytes>0){
            e.ts[i] = character[0];
            nBytes=read(fitxerUsuariFd, character, 1);
            i++;
        } 
        nBytes=read(fitxerUsuariFd, character, 1);

        list = LIST_create(e);

        while(nBytes > 0){
            bzero (e.name, 11);
            bzero (e.ts, 20);

            //get 1 file name
            i=0;
            while (character[0]!= '\n' && nBytes>0){
                e.name[i] = character[0];
                nBytes=read(fitxerUsuariFd, character, 1);
                i++;
            } 
            nBytes=read(fitxerUsuariFd, character, 1);
            i=0;
            //throw 1 file ts
            while (character[0]!= '\n' && nBytes>0){
                e.ts[i] = character[0];
                nBytes=read(fitxerUsuariFd, character, 1);
                i++;
            } 
            nBytes=read(fitxerUsuariFd, character, 1);

            LIST_push(list, e);

        }


        strcpy(e.name, nomFitxer);

        index = LIST_getIndexByValue(list, e);

        //LIST_print(list);


        LIST_removeByIndex(&list, index);

        //LIST_print(list);


        close(fitxerUsuariFd);


        sprintf(text, "%s.db", gunganName);

        fitxerUsuariFd = open(text,O_TRUNC|O_WRONLY,0640); //,0640
        while (list != NULL){
            e = LIST_pop(&list);
            write (fitxerUsuariFd, e.name, strlen(e.name));
            write (fitxerUsuariFd, "\n", 1);
            write (fitxerUsuariFd, e.ts, strlen(e.ts));
            write (fitxerUsuariFd, "\n", 1);
        }
        close(fitxerUsuariFd);

    }

    SEM_signal(&sem);

    return 0;
}

int comrpovarUsuariFitxer (char nomFitxer[11], char gunganName[INFO_PPAL+1], int timeOut){
    int i = 0;
    char nomFitxerAux[11];
    int fitxerUsuariFd;
    int nBytes;
    char timeOutChar[20];
    unsigned long timeOutLong;
    char text[MAXC];
    char character[2];
    //populate data


    SEM_wait(&sem);
    fitxerUsuariFd = open (nomFitxer,O_RDONLY);
    if (fitxerUsuariFd < 0){
        close(fitxerUsuariFd);
        SEM_signal(&sem);
        return 0;
    }
    close (fitxerUsuariFd);


    sprintf(text, "%s.db", gunganName);
    fitxerUsuariFd = open (text,O_RDONLY);
    if (fitxerUsuariFd<0){
        close(fitxerUsuariFd);
        SEM_signal(&sem);
        return 0;
    }else{
        //printf("[DEBUG] Fitxer %s exiteix\n", text);
        nBytes=read(fitxerUsuariFd, character, 1);
        while(nBytes > 0){
            bzero (nomFitxerAux, 11);
            bzero (timeOutChar, 20);

            //get 1 file name
            i=0;
            while (character[0]!= '\n' && nBytes>0){
                nomFitxerAux[i] = character[0];
                nBytes=read(fitxerUsuariFd, character, 1);
                i++;
            } 
            nBytes=read(fitxerUsuariFd, character, 1);
            i=0;
            //throw 1 file ts
            while (character[0]!= '\n' && nBytes>0){
                timeOutChar[i] = character[0];
                nBytes=read(fitxerUsuariFd, character, 1);
                i++;
            } 
            nBytes=read(fitxerUsuariFd, character, 1);


            timeOutLong = atoi(timeOutChar);
            //printf("nomFitxerAux: %s\n", nomFitxerAux);
            //printf("timeOutsrc: %lu\n", (unsigned long)time(NULL) - timeOutLong);
            //printf("timeOutto: %lu\n", (unsigned long)timeOut);

            if (strcmp(nomFitxerAux, nomFitxer)==0 ){
                if ((unsigned long)time(NULL)- timeOutLong < (unsigned long)timeOut ){
                    close(fitxerUsuariFd);
                    SEM_signal(&sem);
                    return 1;
                }else{
                    //printf("timeOut caducado\n");
                    //BORRAR usuariFitxer
                    close(fitxerUsuariFd);
                    SEM_signal(&sem);
                    borrarUsuariFitxer(nomFitxerAux, gunganName);
                    return 0;
                }
            }
        }
        close(fitxerUsuariFd);
    }


    SEM_signal(&sem);

    return 0;
}

int getMidaFitxer(int fd){
  int midaFitxer;
  char text[MAXC];

   
    if(fd<0){
        sprintf(text,"ERROR en el proces d'upload\n");
        write(1,text,strlen(text));
        exit(-1);

    }else{
      midaFitxer=lseek(fd, 0, SEEK_END);

    }
    return midaFitxer;
}

int preparaSocketFd(int port){
    int fdSocket;
    struct sockaddr_in s_addr;
    char text[MAXC];

    fdSocket=socket(AF_INET, SOCK_STREAM, 0);

    if (fdSocket<0){
        sprintf(text,"Error al crear el socket\n");
        write(1,text,sizeof(text));
        return -1;
    }

    int one = 1;

    setsockopt(fdSocket,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one));

    memset(&s_addr, 0, sizeof(s_addr));

    s_addr.sin_family=AF_INET;
    s_addr.sin_port=htons(port);
    s_addr.sin_addr.s_addr =INADDR_ANY;
    


    if(bind(fdSocket, (void *)&s_addr, sizeof(s_addr))<0){
        sprintf(text,"Error bind\n");
        write(1,text,sizeof(text));
        return -1;
    }

    listen(fdSocket,3);

    return fdSocket;
}

Config llegirFitxerConfig(){
    Config serv;
    int fd;
    int i;
    char aux;
    char string[MAXC];
    
    //INIT
    bzero (string, sizeof(string));
    serv.timeOut= -1;
    serv.port = -1;
    i=0;
    
    
    fd=open("naboo.cfg",O_RDONLY);
    
    if (fd < 0){
        return serv;
    }
    //printf("Fichero existe\n");
    read(fd, &aux, 1);
    
    while ( aux != '\n' ){
        
        string[i]=aux;
        
        i++;
        if ( i >= MAXC) {
            return serv;
        }
        
        read(fd, &aux, 1);
    }
    
    string[i] = '\0';
    serv.timeOut= atoi(string); 
    
    i=0;
    bzero (string, sizeof(string));

    
    read(fd, &aux, 1);
    
    while ( aux != '\n' ){
        
        string[i]=aux;
        
        i++;
        if ( i >= MAXC) {
            return serv;
        }
        
        read(fd, &aux, 1);
    }
    
    string[i] = '\0';
    serv.port= atoi(string); 

    return serv;
}

Trama parseTrama(char tramaInput[TRAMA]){
    int i;
    int j;
    Trama trama;

    bzero(trama.tipoTrama, TIPO_TRAMA);
    bzero(trama.infoPpal, INFO_PPAL);
    bzero(trama.data, DATA);

    j=0;
    i=0;

    while(i<TIPO_TRAMA && tramaInput[j]!='\0'){
        trama.tipoTrama[i] = tramaInput[j];
        j++;
        i++;
    }
    trama.tipoTrama[i] = '\0';

    j=TIPO_TRAMA;
    i=0;

    while(i<INFO_PPAL && tramaInput[j]!='\0'){
        trama.infoPpal[i] = tramaInput[j];
        j++;
        i++;
    }
    trama.infoPpal[i] = '\0';

    j=INFO_PPAL+TIPO_TRAMA;
    i=0;

    while(i<DATA){
        trama.data[i] = tramaInput[j];
        j++;
        i++;
    }   
    //trama.data[i] = '\0';


    return trama;
}

char* buildTrama(Trama trama){
    char* tramaBuilded;
    char text[MAXC];

    tramaBuilded = malloc(TRAMA*sizeof(char));

    if (tramaBuilded==NULL){
        sprintf(text,"ERROR al demanar memoria\n");
        write(1,text,strlen(text));
        exit(-1);
    }

    bzero (tramaBuilded, TRAMA);
    int i;
    int j;

    i=0;
    j=0;
    while (i<TIPO_TRAMA && trama.tipoTrama[i]!='\0'){
        tramaBuilded[j] = trama.tipoTrama[i];
        i++;
        j++;
    }

    i=0;
    j=TIPO_TRAMA;
    while (i<INFO_PPAL && trama.infoPpal[i]!='\0'){
        tramaBuilded[j] = trama.infoPpal[i];
        i++;
        j++;
    }

    i=0;
    j=INFO_PPAL+TIPO_TRAMA;
    while (i<DATA){
        tramaBuilded[j] = trama.data[i];
        i++;
        j++;
    }

    return tramaBuilded;
}

char* getMd5FromFile(char* nomFitxer){
  char *execvp_args[] = {"md5sum", nomFitxer, NULL}; 
  char* aux;
  int saved_stdout;
  int fd[2];

  aux = malloc(100 * sizeof(char));

                
  pipe(fd);

  //dup2 i llegir de pipe
  saved_stdout = dup(1);
  dup2(fd[1], 1);


  if (fork() == 0){
      execvp(execvp_args[0], execvp_args);
  }

  wait(NULL);

  read(fd[0], aux, 100);


  dup2(saved_stdout, 1);
  close(saved_stdout);
  close(fd[1]);
  close(fd[0]);

  int i = 0;
  while (aux[i]!= '\n') i++;

  aux[i]= '\0';

  //printf("MD5: %s \n", aux);
  return aux;
}

void treuEspais (char* comanda){

  char *desti = comanda; 
  while (*comanda != '\0')
  {
    while (*comanda == ' ' && *(comanda + 1) == ' ')
      comanda++;  
      *desti++ = *comanda++;
    }
  *desti = '\0';   
}

int getNomUsers (char* line, char *argv[]){
     int i=0;
     int j=0;
     int k=0;
     char aux[MAXC];

     treuEspais(line);

     if (line[i] == ' '){
          i++;
     }

     while (line[i] != '\0'){
          bzero(aux, sizeof(aux));
          j=0;

          while (line[i] != ' ' && line[i] != '\0' && j<10){
               aux[j] = line[i];
               i++;
               j++;
          }

          argv[k] = (char *) malloc (sizeof(aux));
          if(argv[k] == NULL){
               return 0;
          }
          strcpy(argv[k],aux);

          k++;

          if (line[i] != '\0'){
             i++;  
          }
          
          if (j == 10){
            i--;
          }

     }
     bzero(aux, sizeof(aux));
     argv[k] = (char *) malloc (sizeof(aux));
     if(argv[k] == NULL){
          return 0;
     }
     argv[k]=NULL;

     return 1;
}

Trama llegeixTrama (int newsockfd){

    char tramaInput[TRAMA];
    Trama trama;
    int bytes;

    //printf("[DEBUG] Esperant trama \n");
    bytes = read(newsockfd, tramaInput, TRAMA);

    if (bytes < 1){
        strcpy(trama.tipoTrama, "SDOWN");
        return trama;
    }

    trama = parseTrama(tramaInput);

    //printf("[DEBUG] He rebut trama %s\n", trama.tipoTrama);


    return trama;
}

int tipusTrama(Trama trama){

    if(strcmp(trama.tipoTrama, "SDOWN")==0){
        return 0;
    }

    if(strcmp(trama.tipoTrama, "DCON")==0){
        return 1;
    }

    if(strcmp(trama.tipoTrama, "UPLD")==0){
        return 2;
    }

    if(strcmp(trama.tipoTrama, "DWNLD")==0){
        return 3;
    }

    return -1;  
}

int getNextPort(int portBase){
    int i;

    i=0;

    while (i<9 ){
        SEM_wait(&freePortSem[i]);
        if (freePortFlag[i]==0){
            freePortFlag[i]=1;
            SEM_signal(&freePortSem[i]);
            i++;
            return portBase+i;
        }else{
            SEM_signal(&freePortSem[i]);
        }
        
        i++;
    }

    return -1;
}

void freePort (int i){
    SEM_wait(&freePortSem[i]);
    freePortFlag[i]=0;
    SEM_signal(&freePortSem[i]);        
}

void gestionaUpload(int newsockfd, Trama trama, int portBase){
    char text[MAXC];

    //*** GESTIONAR TRAMA ***
    char nomFitxer[11];
    char* nomUsers[10];
    int uploadPort;
    int uploadFd;
    int uploadSocketFd;
    struct sockaddr_in cliente_addr;
    socklen_t cliente_len = sizeof(cliente_addr);
    int nouFitxerFd;
    int restant;
    int i;
    int fitxerUsuariFd;


    if (fork() == 0){
        getNomUsers(trama.data, nomUsers);

        strcpy (nomFitxer, trama.infoPpal);

        sprintf(text,"Nom Fitxer: %s\n",trama.infoPpal);
        write(1,text,strlen(text));

        //getNextPort
        uploadPort = getNextPort(portBase);

        switch (uploadPort){
            case -1:
                //KO
                enviaTramaKO(newsockfd);
                close (newsockfd);
                exit (-1);

            break;
            default:
                //OK

                uploadFd = preparaSocketFd(uploadPort);

                enviaTramaPort (uploadPort, newsockfd);

                sprintf(text,"Esperant conexió\n");
                write(1,text,strlen(text));

                uploadSocketFd = accept(uploadFd, (void *)&cliente_addr, &cliente_len);

                if (uploadSocketFd < 0) {
                    //*** ERROR ***
                    sprintf(text,"ERROR al accept\n");
                    write(1,text,strlen(text));
                }else{
                    close(uploadFd);
                    sprintf(text,"Conectat!\n");
                    write(1,text,strlen(text)); 
                    //espero trama init
                    trama = llegeixTrama(uploadSocketFd);
                    nouFitxerFd=open(nomFitxer,O_WRONLY|O_CREAT,0640); //,0640

                    //printf("Tipo trama: %s", trama.tipoTrama );

                    if (strcmp (trama.tipoTrama, "INIT") == 0 && nouFitxerFd>0){
                        enviaTramaOK(uploadSocketFd);

                        //bucle copia
                        trama = llegeixTrama(uploadSocketFd);
                        //printf("Tipo trama: %s", trama.tipoTrama );
                        while (strcmp (trama.tipoTrama, "MD5")!=0){
                            restant = atoi(trama.infoPpal);
                            if (!restant){
                                write (nouFitxerFd, trama.data, DATA);
                            }else{
                                write (nouFitxerFd, trama.data, restant);
                            }
                            trama = llegeixTrama(uploadSocketFd);
                        }
                        close(nouFitxerFd);
                        //printf("[DEBUG] He rebut trama MD5: %s \n", trama.data);

                        if (strcmp (trama.data, getMd5FromFile(nomFitxer))==0){
                            //Escriure a fitxer.
                            //printf("[DEBUG] Coincidència MD5\n");


                            //bucle per cada usuari
                            //comprovar si existeix fitxer
                            i = 0;
                            while (nomUsers[i] != NULL){

                                SEM_wait(&sem);
                                sprintf(text, "%s.db", nomUsers[i]);
                                fitxerUsuariFd = open (text,O_RDONLY);
                                if (fitxerUsuariFd<0){
                                    //printf("[DEBUG] Fitxer %s no exiteix\n", text);
                                    close(fitxerUsuariFd);
                                    fitxerUsuariFd = open (text,O_WRONLY|O_CREAT,0640);
                                    write (fitxerUsuariFd, nomFitxer, strlen(nomFitxer));
                                    write (fitxerUsuariFd, "\n", 1);
                                    sprintf(text,"%lu\n", (unsigned long)time(NULL));
                                    write (fitxerUsuariFd, text, strlen(text));
                                    close(fitxerUsuariFd);
                                }else{
                                    //printf("[DEBUG] Fitxer %s exiteix\n", text);
                                    close(fitxerUsuariFd);
                                    fitxerUsuariFd = open (text, O_WRONLY|O_APPEND);
                                    write (fitxerUsuariFd, nomFitxer, strlen(nomFitxer));
                                    write (fitxerUsuariFd, "\n", 1);
                                    sprintf(text,"%lu\n", (unsigned long)time(NULL));
                                    write (fitxerUsuariFd, text, strlen(text));
                                    close(fitxerUsuariFd);
                                }

                                SEM_signal(&sem);
                                i++;
                            }

                            enviaTramaOKmd5(uploadSocketFd);
                            //printf("[DEBUG] UPLOAD OK\n");
                                 
                        }else{
                            //MD5 no coincideix
                            enviaTramaKOmd5(uploadSocketFd);
                            //printf("[DEBUG] UPLOAD KO\n");

                        }
                        close (nouFitxerFd);

                    }else{
                        enviaTramaKO(uploadSocketFd);
                    }

                }   
            freePort(uploadPort-portBase-1);      
            break;
            exit(0);
        }
    }
}

void gestionaDownload(int newsockfd, Trama trama, int portBase, char gunganName[INFO_PPAL+1],  int timeOut){
    char text[MAXC];

    //*** GESTIONAR TRAMA ***
    char nomFitxer[11];
    int downldPort;
    int downldFd;
    int downldSocketFd;
    struct sockaddr_in cliente_addr;
    socklen_t cliente_len = sizeof(cliente_addr);
    int restant;
    int fd;
    int midaFitxer;
    char* dataTramaDATA;

    if (fork() == 0){
        strcpy (nomFitxer, trama.infoPpal);

        sprintf(text,"Nom Fitxer: %s\n",trama.infoPpal);
        write(1,text,strlen(text));

        //getNextPort
        downldPort = getNextPort(portBase);

        switch (downldPort){
            case -1:
                //KO
                enviaTramaKO(newsockfd);
                close (newsockfd);
                exit (-1);

            break;
            default:
                //OK

                if (comrpovarUsuariFitxer(nomFitxer, gunganName, timeOut)==1){

                downldFd = preparaSocketFd(downldPort);



                enviaTramaPort (downldPort, newsockfd);

                sprintf(text,"Esperant conexió\n");
                write(1,text,strlen(text));
                enviaTramaInit(newsockfd);
                downldSocketFd = accept(downldFd, (void *)&cliente_addr, &cliente_len);

                if (downldSocketFd < 0) {
                    //*** ERROR ***
                    sprintf(text,"ERROR al accept\n");
                    write(1,text,strlen(text));
                }else{
                    close(downldFd);
                    sprintf(text,"Conectat!\n");
                    write(1,text,strlen(text)); 
                    //espero trama ok
                    trama = llegeixTrama(downldSocketFd);

                    //*****************************
                      //INICI DOWNLOAD
                      //*****************************

                      fd=open(nomFitxer,O_RDONLY);

                      midaFitxer=getMidaFitxer(fd);
                      sprintf(text,"Medida fichero %d\n",midaFitxer);
                      write(1,text,strlen(text));
                      restant=midaFitxer;
                      dataTramaDATA=malloc(DATA*sizeof(char)+1);
                      if (dataTramaDATA==NULL){
                          sprintf(text,"ERROR al demanar memoria\n");
                          write(1,text,strlen(text));

                      }else{
                         while (restant>DATA){
                            extreuBytes(midaFitxer,restant, fd, trama.data);
                            //printf("DATA: %s\n", trama.data);

                            enviaTramaDATA(downldSocketFd, trama, 0);
                            restant -= 100;
                          }
                          if (restant > 0){
                            extreuBytes(midaFitxer,restant, fd, trama.data);
                            enviaTramaDATA(downldSocketFd, trama, restant);
                          }
                          enviaTramaMD5(downldSocketFd,nomFitxer);

                          trama = llegeixTrama(downldSocketFd);

                          if (strcmp(trama.tipoTrama, "OK")==0){
                            //printf("[DEBUG] UPLOAD OK\n");
                            borrarUsuariFitxer(nomFitxer, gunganName);

                          }else{
                            //printf("[DEBUG] UPLOAD KO\n");
                          }
                      }

                }   
            freePort(downldPort-portBase-1);      
            break;
            }else{
                enviaTramaKO(newsockfd);
            }
            exit(0);
        }
    }
}

void gestionaTrama(int newsockfd, Trama trama, char gunganName[INFO_PPAL+1], int portBase, int timeOut){
    int opcio;
    char text[MAXC];

    //*** OBTENIR TIPUS TRAMA ***
    opcio = tipusTrama(trama);


    switch (opcio){
        case 0:
            sprintf(text,"Client socket went unexpectedly down. Exiting %s.\n",gunganName);
            write(1,text,strlen(text));
            close(newsockfd);
            exit(0);

        case 1:
            // TRAMA DCON
            sprintf(text,"Exiting %s.\n",gunganName);
            write(1,text,strlen(text));
            close(newsockfd);
            exit(0);
        break;

        case 2:
            // TRAMA UPLD
            gestionaUpload(newsockfd, trama, portBase);
        break;

        case 3:
            // TRAMA DWNLD
            gestionaDownload(newsockfd, trama, portBase, gunganName, timeOut);
        break;

        default:
            sprintf(text,"Server received an unknown TRAMA type from %s. TRAMA type: %s \n",gunganName, trama.tipoTrama);
            write(1,text,strlen(text));

        break;                          
    }
}

void inicialitzaSemafors(){
    int control, i;
    char text[MAXC];

    control = 0;
    i=0;

    while(!control && i<9){
        //printf("Bucle: %d\n", i);
        if (SEM_constructor(&freePortSem[i]) == 0){
            //printf("hola\n");
            SEM_init(&freePortSem[i], 1);
            i++;
        }else {
            control = 1;
        }
    }
    i--;
    if (control){
        while (i<=0){
            SEM_destructor(&freePortSem[i]);
            i--;
        }

        sprintf(text,"Error al inicialitzar els semafors dels ports lliures. \n");
        write(1,text,strlen(text));
        exit(-1);
    }
}

void destroySemafors(){
    int i;

    for (i=0; i<9 ; i++){
        SEM_destructor(&freePortSem[i]);
    }
    SEM_destructor(&sem);
}

void inicialitzaSharedMem(){
    int i;

    memid=shmget(IPC_PRIVATE,sizeof(int)*9,IPC_CREAT|0600);
    if(memid<0){
        write(1,"Error en crear memoria\n",23);
        exit(-1);
    }

    freePortFlag=(int*)shmat(memid,0,0);

    for (i=0; i<10 ; i++){
        freePortFlag[i] = 0;
    }
}

void freeSharedMem(){
    shmdt(freePortFlag);
    shmctl(memid, IPC_RMID, NULL );
}


