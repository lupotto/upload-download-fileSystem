//
//  main.c
//  LsTransfer
//
//  Created by Alex Gracia Lupotto on 21/10/15.
//  Copyright © 2015 Alex Gracia Lupotto. All rights reserved.
//
#include "api.h"

int sock;


void ksighandler(int signum){
    char text[MAXC];

    switch (signum){
        case SIGINT:

            enviaTramaDCON(sock);

            sprintf(text,"\nA10\n");
            write(PANTALLA,text,strlen(text));

            exitGungan(1);
        break;
        default:
        break;
    }
}

int main(void)
{
    Usuari usuari;
    char text[MAXC];
    char  *argv[MAXP]; 
    int opcio;
    Trama trama;
    char* comanda; 

    
    signal(SIGINT, ksighandler);
    
    usuari=llegirFitxerConfig();
    
    sock = preparaSocket(usuari);

    comanda = (char *) malloc (MAXC);

    //ENVIO CON

    enviaTramaCON(sock, usuari);

    //RECIBO OK/KO

    trama = llegeixTrama(sock);


    if (tipusTrama(trama)==0){
        sprintf(text, "[Connected]\n");
        write(PANTALLA,text,strlen(text));
    }else{
        sprintf(text, "Error: El servidor ha respós amb una trama KO l'intent de conexió\n");
        write(PANTALLA,text,strlen(text));
        exitGungan(-1);
    }

    //TRAMA P_QRY
    enviaTramaP_QRY();

    trama = llegeixTrama(sock);
    //MOSTRA PER PANTALLA DOWNLOADS PENDENTS
    mostraDownloadsPendents(trama);



    while ( 1 ){
        sprintf(text,"Gungan>> ");
        write(PANTALLA,text,strlen(text));
        opcio = llegeixComanda(comanda);
        
        if (opcio){
            opcio = identificaComanda(comanda);
            
            switch (opcio){
                case 1:
                    //*** UPLOAD ***
                    gestionaUpload(comanda, usuari);
                    
                    break;
                case 2:
                    //*** DOWNLOAD ***
                    gestionaDownload(comanda, usuari);

                    break;
                case 3:
                    //*** EXIT ***
                    gestionaExit(sock);

                    break;
                case 4:
                    //*** UNIX ***
                    gestionaComandaUnix(comanda, argv);

                    break;
            }
            
        }else{
            sprintf(text,"La comanda que has escrit es massa llarga, parla amb l'administrador del software per qualsevol ampliació\n");
            write(PANTALLA,text,strlen(text));
        }
    
    }
    
    
    return 0;
}
