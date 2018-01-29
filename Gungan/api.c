//
//  api.c
//  LsTransfer
//
//  Created by Alex Gracia Lupotto on 21/10/15.
//  Copyright © 2015 Alex Gracia Lupotto. All rights reserved.
//

#include "api.h"

char* buildTrama (Trama trama){
    char* tramaBuilded;
    

    //*** CRASH ***
    tramaBuilded = (char*)malloc(TRAMA*sizeof(char)+1);
    //*** CRASH ***

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

void enviaTramaCON (int sock, Usuari usuari){
  char* tramaOutput;
  char text[MAXC];
  Trama trama;

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
  }

  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  bzero(trama.data, sizeof(trama.data));

  strcpy(trama.tipoTrama,"CON");
  strcpy(trama.infoPpal,usuari.nomUsuari);

  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama CON \n");
  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
}

void enviaTramaDWNLD (char* comanda){
  char* tramaOutput;
  Trama trama;
  char aux[MAXC];
  int i = 0;
  int j = 0;


  /*tramaOutput = (char*) malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
  }
  */
  while (comanda[i] != ' '){
    i++;
  }
  i++;
  while (comanda[i] != '\0'){
    aux[j] = comanda[i];
    i++;
    j++;
  }

  aux[j] = comanda[i];



  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  bzero(trama.data, sizeof(trama.data));

  strcpy(trama.tipoTrama,"DWNLD");
  strcpy(trama.infoPpal,aux);



  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama DWNLD \n");
  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
}

void enviaTramaUPLD(  char* comanda){
  char* tramaOutput;
  char  *argv[MAXP];
  char text[MAXC];
  Trama trama;
  int i;
  int j;
  int k;
  int aux;
  tramaOutput = malloc(TRAMA * sizeof(char));
  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
  }
  parseComandaUNIX(comanda,argv);

  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  bzero(trama.data, sizeof(trama.data));

  for (i=0; i<DATA; i++){
    trama.data[i] = ' ';
  }

  //printf ("%s\n", trama.data);

  strcpy(trama.tipoTrama,"UPLD");
  strcpy(trama.infoPpal,argv[1]);

  i=2;
  j=0;
  k=0;
  while(argv[i]!= NULL){
    while(argv[i][k]!= '\0'){
      trama.data[j]=argv[i][k];
      j++;
      k++;
    }
    while(j%10!=0){
      j++;
    }
    k=0;
    i++; 
  }
  if (j<DATA){

    //printf("j : %d", j);
    trama.data[j]= '\0';
  }

  aux=2;
  //printf("TramaUpload: TIPO--> %s\n", trama.tipoTrama);
  //printf("TramaUpload: INFOPPAL--> %s\n", trama.infoPpal);
  while (argv[aux] != NULL){
    //printf("TramaUpload: DATA--> %s\n", trama.data);
    aux++;
  }
    
  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama UPLD \n");
  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
}

void enviaTramaP_QRY(){
  char* tramaOutput;
  char text[MAXC];
  Trama trama;

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
  }

  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  bzero(trama.data, sizeof(trama.data));

  strcpy(trama.tipoTrama,"P_QRY");

  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama P_QRY \n");
  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
}

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

void mostraDownloadsPendents(Trama trama){
  char text[MAXC];
  int i=0;
  int j=0;

  if (trama.data[0] == '\0'){
    sprintf(text,"\nNo hi han descàrregues pendents\n");
    write(PANTALLA,text,strlen(text));
  }else{
    sprintf(text,"\nDescàrregues pendents:\n");
    write(PANTALLA,text,strlen(text));

    while(trama.data[i] != '\0'){
      j=0;
      while(trama.data[i] != '\0' && j<10){
        sprintf(text,"%c", trama.data[i]);
        write(PANTALLA,text,strlen(text));
        j++;
        i++;
      }
      sprintf(text,"\n");
      write(PANTALLA,text,strlen(text));

      while (i%10 != 0) i++;
    } 
    sprintf(text,"\n");
    write(PANTALLA,text,strlen(text));
    write(PANTALLA,text,strlen(text));
  }
}

void enviaTramaMD5(char* nomFitxer){
  char* tramaOutput;
  char text[MAXC];
  Trama trama;

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
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

void enviaTramaDCON (int sock){
  char* tramaOutput;
  char text[MAXC];
  Trama trama;

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
  }

  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  bzero(trama.data, sizeof(trama.data));

  strcpy(trama.tipoTrama,"DCON");

  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama DCON \n");
  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
}

void enviaTramaDATA (int sock, Trama trama, int restant){
  char* tramaOutput;
  char text[MAXC];
  char buffer[2];

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
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

int connexio(Usuari usuari){
  int fd;
  struct sockaddr_in s_addr;   
  
  fd=socket(AF_INET,SOCK_STREAM,0);

   if (fd<0){
        myPrint("Error al crear socket del client\n");
        close (fd);
        exit(-1);
   }
   memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(usuari.portTCP);
    s_addr.sin_addr.s_addr = inet_addr(usuari.ipUsuari);
    if (connect(fd, (void *)&s_addr, sizeof(s_addr))<0){
        myPrint("Error al hacer el connect del cliente\n");
        close(fd);
        exit(-1);   
    }

  return fd;
}

int preparaSocket (Usuari usuari){
  char text[MAXC];

  if (usuari.portTCP<0){
        sprintf(text, "%s",usuari.ipUsuari);
        write(PANTALLA,text,strlen(text));
        exit(-1);
   } 
    sprintf(text, "[Connecting Naboo...]\n");
    write(PANTALLA,text,strlen(text));
    return connexio(usuari);
}

int parseComandaUNIX (char* line, char *argv[]){
     int i=0;
     int j=0;
     int k=0;
     char aux[MAXC];

     if (line[i] == ' '){
          i++;
     }

     while (line[i] != '\0'){
          bzero(aux, sizeof(aux));
          j=0;

          while (line[i] != ' ' && line[i] != '\0'){
               aux[j] = line[i];
               i++;
               j++;
          }
          //printf("malloc %d \n", k);
          argv[k] = (char *) malloc (MAXC * sizeof(char));
          if(argv[k] == NULL){
               return 0;
          }
          strcpy(argv[k], aux);

          k++;

          if (line[i] != '\0'){
             i++;  
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

void executaComandaUNIX (char *argv[]){
     pid_t pid;
     char text[MAXC];

     if ((pid = fork()) < 0) { 
        sprintf(text,"\nError: fork denegat.\n\n");
        write(PANTALLA,text,strlen(text));
        exitGungan(-1);
     }
     else if (pid == 0) {          
          if (execvp(argv[0], argv) < 0) {    
            sprintf(text,"\nError: comanda no vàlida\n\n");
            write(PANTALLA,text,strlen(text));
            exitGungan(-1);
          }
     }
     else {                                 
          wait(NULL); 
     }
}

Usuari llegirFitxerConfig (){
  Usuari usuari;
  int fd;
  int i;
  char aux;
  char strPort[MAXC];
  char text[MAXC];
    
  //INIT
  bzero(usuari.nomUsuari, sizeof(usuari.nomUsuari));
  bzero(usuari.ipUsuari, sizeof(usuari.ipUsuari));
  bzero(strPort, sizeof(strPort));
  usuari.portTCP = -1;
  i=0;
    
    
  fd=open("gungan.cfg",O_RDONLY);
    
  if (fd < 0){
    strcpy( usuari.ipUsuari , "NULL");
    return usuari;
  }
    //printf("Fichero existe\n");
  read(fd, &aux, 1);
    
  while ( aux != '\n' ){
        
    usuari.nomUsuari[i]=aux;

    i++;

    if ( i > 10) {
      sprintf(text,"\nError: Fitxer de configuració, La llargaria de nom es major a 10 caracters.\n\n");
      write(PANTALLA,text,strlen(text));
      exit(-1);
    }
        
    read(fd, &aux, 1);
  }
    
  usuari.nomUsuari[i] = '\0';
    
    
  i=0;
    
  read(fd, &aux, 1);
    
  while ( aux != '\n' ){
        
    usuari.ipUsuari[i]=aux;
        
    i++;
    if ( i >= MAXC) {
      sprintf(text,"\nError: el fitxer de configuració no es troba en el format correcte.\n\n");
      write(PANTALLA,text,strlen(text));
      exit(-1);
    }
        
    read(fd, &aux, 1);
  }
    
  usuari.ipUsuari[i] = '\0';
    
  i=0;
    
  read(fd, &aux, 1);
    
  while ( aux != '\n' ){
        
    strPort[i]=aux;
        
    i++;
    if ( i >= MAXC) {
      sprintf(text,"\nError: el fitxer de configuració no es troba en el format correcte.\n\n");
      write(PANTALLA,text,strlen(text));
      exit(-1);
    }
        
    read(fd, &aux, 1);
  }
  strPort[i]='\0';
  usuari.portTCP= atoi(strPort); 
  return usuari;
}

int funcioUpload (char* aux){
    int i = 0;
    if ( aux[i] == 'U' || aux[i] == 'u'){
        i++;
        if ( aux[i] == 'P' || aux[i] == 'p'){
            i++;
            if ( aux[i] == 'L' || aux[i] == 'l'){
                i++;
                if ( aux[i] == 'O' || aux[i] == 'o'){
                    i++;
                    if ( aux[i] == 'A' || aux[i] == 'a'){
                        i++;
                        if ( aux[i] == 'D' || aux[i] == 'd'){
                            return 1;
                        }
                        
                    }
                }
            }
        }
    }

    return 0;
}

int funcioDownload (char* aux){
    int i = 0;
    if ( aux[i] == 'D' || aux[i] == 'd'){
        i++;
        if ( aux[i] == 'O' || aux[i] == 'o'){
            i++;
            if ( aux[i] == 'W' || aux[i] == 'w'){
                i++;
                if ( aux[i] == 'N' || aux[i] == 'n'){
                    i++;
                    if ( aux[i] == 'L' || aux[i] == 'l'){
                        i++;
                        if ( aux[i] == 'O' || aux[i] == 'o'){
                            i++;
                            if ( aux[i] == 'A' || aux[i] == 'a'){
                                i++;
                                if ( aux[i] == 'D' || aux[i] == 'd'){
                                    i++;
                                    return 1;
                                }
                            }
                        }
                        
                    }
                }
            }
        }
    }
    
    return 0;
}

int funcioExit (char* aux){
    int i = 0;
    if ( aux[i] == 'E' || aux[i] == 'e'){
        i++;
        if ( aux[i] == 'X' || aux[i] == 'x'){
            i++;
            if ( aux[i] == 'I' || aux[i] == 'i'){
                i++;
                if ( aux[i] == 'T' || aux[i] == 't'){
                    i++;
                    return 1;
                }
            }
        }
    }
    
    return 0;
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

void treuTabuladors (char* comanda){
  int i=0;

  while (comanda[i] != '\0'){
    if (comanda[i] == '\t'){
      comanda[i] = ' ';
    }
    i++;
  }
}

void gestionaExit (int sock){
  char text[MAXC];

  enviaTramaDCON(sock);

  sprintf(text,"\nA10\n");
  write(PANTALLA,text,strlen(text));
  exitGungan(1);
}

void gestionaComandaUnix (char* comanda,char* argv[]){
  char text[MAXC];
  int i;

  if (parseComandaUNIX(comanda, argv)){
    executaComandaUNIX(argv);
    i=0;
    while (argv[i] != NULL){
      free (argv[i]);
      i++;
    }
  }else{
      sprintf(text,"\nError: Memòria insuficient\n\n");
      write(PANTALLA,text,strlen(text));
  }
}

int preparaSocketUPLD(int port, Usuari usuari){
  //Preparem el socket per realitzar el upload
  char text[MAXC];
  if (port<0){
        sprintf(text, "No hi ha ports disponibles\n");
        write(PANTALLA,text,strlen(text));
        exit(-1);
   } 
    //sprintf(text, "[Fent upload...]\n");
    //write(PANTALLA,text,strlen(text));
    return connexioUPLD(port, usuari);
}

int connexioUPLD(int port, Usuari usuari){
  //Connectannos al servidor dedicat per fer l'upload
  int fd;
  struct sockaddr_in s_addr;   
  
  fd=socket(AF_INET,SOCK_STREAM,0);

   if (fd<0){
        myPrint("Error al connectar-nos a naboo per fer l'upload\n");
        close (fd);
        exit(-1);
   }
   memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = inet_addr(usuari.ipUsuari);
    if (connect(fd, (void *)&s_addr, sizeof(s_addr))<0){
        myPrint("Error al connectar-nos al servidor dedicat d'upload\n");
        close(fd);
        exit(-1);   
    }

  return fd;
}

int getPortUpload(){
  Trama trama;
  trama=llegeixTrama();
  return atoi(trama.infoPpal);
}

void gestionaDownload (char* comanda, Usuari usuari){
  char text[MAXC];
  int espais;
  int port;
  char* nomFitxer;
  Trama trama;

  espais = contaEspais(comanda);
  nomFitxer = malloc(MAXC * sizeof(char));

  int i = 0;
  int j = 0;

  while (comanda[i] != ' '){
    i++;
  }
  i++;
  while (comanda[i] != '\0'){
    nomFitxer[j] = comanda[i];
    i++;
    j++;
  }

  nomFitxer[j] = '\0';


  if (espais == 1){
    //nomFitxer=existeixFitxer(comanda);
    //if (nomFitxer[0]!='\0'){
      //sprintf(text,"\nOK: comanda reconeguda.\n\n");
      //write(PANTALLA,text,strlen(text)); 
      //Enviar TramaUpload
      enviaTramaDWNLD(comanda);

      //Llegeixo port de naboo

      trama=llegeixTrama();
      //printf("TRAMA %s recibida\n", trama.tipoTrama);
      if (strcmp(trama.tipoTrama, "PORT")==0){
          port = atoi(trama.infoPpal);

          sprintf(text,"[downloading %s...]\n", nomFitxer);
          write(1,text,strlen(text));

          creaForkGunganDownload(port, usuari, nomFitxer);
      }else{
          sprintf(text,"[ERROR: el fitxer no existeix]\n");
          write(1,text,strlen(text));
      }

      //Faig gungan jr.
      
  }else{
      sprintf(text,"\nError: falten paràmetres\n\n");
      write(PANTALLA,text,strlen(text));
  }
}

void gestionaUpload (char* comanda, Usuari usuari){
  char text[MAXC];
  int espais;
  int port;
  char* nomFitxer;

  espais = contaEspais(comanda);
  nomFitxer = malloc(MAXC * sizeof(char));

  if (espais > 1 && espais < 12){
    nomFitxer=existeixFitxer(comanda);
    if (nomFitxer[0]!='\0'){
      //sprintf(text,"\nOK: comanda reconeguda.\n\n");
      //write(PANTALLA,text,strlen(text)); 
      //Enviar TramaUpload
      enviaTramaUPLD(comanda);
      //Llegeixo port de naboo

      port=getPortUpload();
      //Faig gungan jr.

      sprintf(text,"[uploading %s...]\n", nomFitxer);
      write(1,text,strlen(text));

     
      creaForkGunganUpload(port, usuari, nomFitxer);
      
    }else{
        sprintf(text,"\nError: El fitxer no existeix\n\n");
        write(PANTALLA,text,strlen(text));
    }
  }else if (espais > 11){
      sprintf(text,"\nError: només es poden introduïr un màxim de 10 usuaris\n\n");
      write(PANTALLA,text,strlen(text)); 
  }else{
      sprintf(text,"\nError: falten paràmetres\n\n");
      write(PANTALLA,text,strlen(text));
  }
}


void creaForkGunganDownload(int port,Usuari usuari, char* nomFitxer){
    int pid;
    char text[MAXC];
    Trama trama;
    int restant;

    //*** GESTIONAR TRAMA ***
    int nouFitxerFd;
    
    pid=fork();

    if (pid < 0){
        //*** ERROR ***
        //ERROR AL CREAR LA TRAMA UPLOAD (Enviar a naboo dienli que no es pot fer l'upload)
        sprintf(text,"ERROR al crear el fork\n");
        write(1,text,strlen(text));
        //enviaTramaKO(newsockfd);
        //close(newsockfd);
        exit(-1);
    }else if(pid==0){


      //*******GUNGAN JR**********
        //Eespero trama INIT
        trama = llegeixTrama();   
      //Ens connectem al port que ens ha proporcionat naboo per fer l'upload
        sock=preparaSocketUPLD(port, usuari);
         
      

          //*****************************
          //INICI DOWNLOAD
          //*****************************

          nouFitxerFd=open(nomFitxer,O_WRONLY|O_CREAT,0640); //,0640

          //printf("Tipo trama: %s", trama.tipoTrama );

          if (strcmp (trama.tipoTrama, "INIT") == 0 && nouFitxerFd>0){
            enviaTramaOK(sock);
            //printf("Començant download\n");
            //bucle copia
            trama = llegeixTrama();
            //printf("Tipo trama: %s", trama.tipoTrama );
            while (strcmp (trama.tipoTrama, "MD5")!=0){
            restant = atoi(trama.infoPpal);
            //printf("Restant : %d\n", restant);
            if (!restant){
                write (nouFitxerFd, trama.data, DATA);
            }else{
                write (nouFitxerFd, trama.data, restant);
            }
            trama = llegeixTrama();
          }
          close(nouFitxerFd);
          //printf("[DEBUG] He rebut trama MD5: %s \n", trama.data);

          if (strcmp (trama.data, getMd5FromFile(nomFitxer))==0){
            //Escriure a fitxer.
            //printf("[DEBUG] Coincidència MD5\n");

            
          enviaTramaOKmd5(sock);
          //printf("[DEBUG] DOWNLOAD OK\n");
          sprintf(text,"[%s downloaded]\n", nomFitxer);
          write(1,text,strlen(text));
                                 
        }else{
          //MD5 no coincideix
          enviaTramaKOmd5(sock);
          printf("[DEBUG] DOWNLOAD KO\n");

        }
        close (nouFitxerFd);

      }else{
        enviaTramaKO(sock);
      }
          //Escriure ERROR PER PANTALLA exit(-1)
          //Recibido KO despues de init
      
      exit(0);
    
  }
}

void creaForkGunganUpload(int port,Usuari usuari, char* nomFitxer){
    int pid;
    char text[MAXC];
    int ok = -1;
    Trama tramaOK;
    Trama trama;
    int fd;
    int midaFitxer;
    int restant;
    char* dataTramaDATA;
   
    pid=fork();

    if (pid < 0){
        //*** ERROR ***
        //ERROR AL CREAR LA TRAMA UPLOAD (Enviar a naboo dienli que no es pot fer l'upload)
        sprintf(text,"ERROR al crear el fork\n");
        write(1,text,strlen(text));
        //enviaTramaKO(newsockfd);
        //close(newsockfd);
        exit(-1);
    }else if(pid==0){
      //*******GUNGAN JR**********
      //Ens connectem al port que ens ha proporcionat naboo per fer l'upload
        sock=preparaSocketUPLD(port, usuari);
      //Enviem trama INIT
        enviaTramaINIT();
      //Espero ok/ko de naboo
        tramaOK=llegeixTrama();
        ok=strcmp("OK",tramaOK.tipoTrama);
        if (ok==0){

          fd=open(nomFitxer,O_RDONLY);

          midaFitxer=getMidaFitxer(fd);
          //sprintf(text,"Medida fichero %d\n",midaFitxer);
          //write(1,text,strlen(text));
          restant=midaFitxer;
          dataTramaDATA=malloc(DATA*sizeof(char)+1);
          if (dataTramaDATA==NULL){
              sprintf(text,"ERROR al demanar memoria\n");
              write(1,text,strlen(text));

          }else{
             while (restant>DATA){
                extreuBytes(midaFitxer,restant, fd, trama.data);
                //printf("DATA: %s\n", trama.data);

                enviaTramaDATA(sock, trama, 0);
                restant -= 100;
              }
              if (restant > 0){
                extreuBytes(midaFitxer,restant, fd, trama.data);
                enviaTramaDATA(sock, trama, restant);
              }
              enviaTramaMD5(nomFitxer);

              trama = llegeixTrama();

              if (strcmp(trama.tipoTrama, "OK")==0){
                //printf("[DEBUG] UPLOAD OK\n");
                sprintf(text,"[%s uploaded]\n", nomFitxer);
                write(1,text,strlen(text));
              }else{
                //printf("[DEBUG] UPLOAD KO\n");
              }
          }

        }else{
          //Escriure ERROR PER PANTALLA exit(-1)
          //Recibido KO despues de init
        }
        exit(0);
    }
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

void enviaTramaINIT(int sock){
  char* tramaOutput;
  char text[MAXC];
  Trama trama;

  tramaOutput = malloc(TRAMA * sizeof(char));

  if (tramaOutput==NULL){
    sprintf(text,"ERROR al demanar memoria\n");
    write(1,text,sizeof(text));
    exitGungan(-1);
  }

  bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
  bzero(trama.infoPpal, sizeof(trama.infoPpal));
  bzero(trama.data, sizeof(trama.data));

  strcpy(trama.tipoTrama,"INIT");

  tramaOutput = buildTrama(trama);

  //printf("[DEBUG] Enviant trama INIT \n");
  write(sock, tramaOutput, TRAMA);

  free (tramaOutput);
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

int identificaComanda (char* comanda){
    char aux[MAXC];
    int i = 0;
    int j = 0;


    bzero(aux, sizeof(aux));
    if (comanda[i] == ' '){
      i++;

    } 

    while ( comanda[i] != ' ' && comanda[i] != '\0' ){
        aux[j]=comanda[i];
        i++;
        j++;
    }

    if (funcioUpload(aux)) return 1;
    if (funcioDownload(aux)) return 2;
    if (funcioExit(aux)) return 3;

    return 4;
}

int llegeixComanda (char* comanda){
    //char* comanda;
    char aux[MAXC];
    int i = 0;
    
    bzero(aux,sizeof(aux));
    read(TECLADO, aux, sizeof(aux));

    i=0;
    while ( aux[i] != '\n' ){
        comanda[i] = aux[i];
        i++;
        if (i>=MAXC){
            return 0;
        }
    }
    comanda[i]='\0';
    treuTabuladors(comanda);
    treuEspais(comanda);
    i=0;
    while (comanda[i] != '\0') i++;
    if (comanda[i-1] == ' '){
       comanda[i-1]='\0';
    }
    
    return 1;
}

int contaEspais (char* comanda){
    int espais;
    int i;
    
    i=0;
    espais=0;
    if (comanda[i] == ' ')
    {
      i++;
    }

    while (comanda[i] != '\0'){
        if (comanda[i] == ' '){
            espais++;
        }
        i++;
    }
    
    return espais;
}

char* existeixFitxer (char* comanda){

  int i=0;
  int j=0;
  int fd;
  char* aux;

  aux = malloc(MAXC * sizeof(char));

  bzero (aux, sizeof(MAXC * sizeof(char)));
  if (comanda[i] == ' ') i++;
  while (comanda[i] != ' ') i++;
  i++;

  while (comanda[i] != ' '){
    aux[j] = comanda[i];
    i++;
    j++;
  } 

  fd = open (aux,O_RDONLY);

  if (fd<0){
    bzero (aux, sizeof(MAXC * sizeof(char)));
    return aux;
  }

  return aux;
}

Trama parseTrama (char* tramaInput){
    int i;
    int j;
    Trama trama;

    bzero(trama.tipoTrama, sizeof(trama.tipoTrama));
    bzero(trama.infoPpal, sizeof(trama.infoPpal));
    bzero(trama.data, sizeof(trama.data));

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

Trama llegeixTrama (){
  char tramaInput[TRAMA];
  Trama trama;
  //printf("[DEBUG] Esperant trama \n");
  read(sock, tramaInput, TRAMA);

  trama = parseTrama(tramaInput);

  return trama;
}

int tipusTrama (Trama trama){

  if(strcmp(trama.tipoTrama, "KO")==0){
    return -1;
  }

  if(strcmp(trama.tipoTrama, "OK")==0){
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

void exitGungan (int i){ 
  close (sock);
  exit(i);
}

void myPrint (char * sOut){
  write(1, sOut, strlen(sOut));
  ///
}






