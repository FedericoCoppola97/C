#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>

#define REMOTE_PORT	8888
#define DIM_MSG	2048
#define DIM_RISP 256


int main()
{

    int socket_client;
    int connessione;
    int invio_mex;
    struct sockaddr_in remote_address;
    char messaggio[DIM_MSG]="Ciao mondo!";
    char risposta_server[DIM_RISP];

    //creazione socket TCP con IPv4
    socket_client=socket(AF_INET,SOCK_STREAM,0);
    if(socket_client<0)
    {
        printf("Errore socket!\n\n\a");
        return 1;
    }
    else
        printf("Socket creato con successo!\n\n");

    //struct IP + porta remota sever (127.0.0.1:8888)
    remote_address.sin_family = AF_INET;
    remote_address.sin_port=htons(REMOTE_PORT);
    remote_address.sin_addr.s_addr = INADDR_ANY;

    //connessione verso server remoto
    connessione=connect(socket_client, (struct sockaddr*)&remote_address,sizeof(remote_address));
    if(connessione<0)
        printf("Errore connessione!\n\a");
    else
        printf("Connessione OK!\n\n");


    //invio messaggio a server TCP su porta TCP-8888
    invio_mex=send(socket_client,messaggio,sizeof(messaggio), 0);
     if(invio_mex<0)
        printf("Errore invio messaggio!\n\a");
     else
        printf("Messaggio inviato al server!\n");

    //ricezione risposta da server TCP
    recv(socket_client,risposta_server,sizeof(risposta_server),0);
    printf("Risposta server TCP: %s\n",risposta_server);

    close(socket_client); //chiudo connessione

    printf("Fine connessione TCP!\n");

    return 0;
}
