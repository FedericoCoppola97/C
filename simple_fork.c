#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>


#define SRV_PORT 8888
#define DIM_BUFF 2048
#define DIM_RISP 256

int main()
{
    int server_socket; //variabile per socket_tcp
    int esito_bind=0; //variabile per esito bind()
    int dimensione_msg_ricevuto=0; //intero dimensione messaggio
    struct sockaddr_in srv_addr; //struct per gestione indirizzo IP
    char buffer[DIM_BUFF]; //buffer ricezione
    char risposta[DIM_RISP]; //buffer per messaggio di risposta al client

    printf("*** SERVER SOCKET TCP ***\n\n\n");

    //creazione socket TCP + IPv4
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket<0)
        printf("Errore SOCKET!\a\n\n");
    else
        printf("SOCKET creato con successo!\n");

    //configurazione indirizzo IP
    srv_addr.sin_family= AF_INET; //uso IPv4
    srv_addr.sin_port=htons(SRV_PORT); //porta TCP Server (htons affinchè sono sicuro che venga letta nel giusto ordine
    srv_addr.sin_addr.s_addr = INADDR_ANY; //connessioni da qualsiasi IP

    //bind socket + struct address
    esito_bind=bind(server_socket,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    if(esito_bind<0)
     {
        printf("Errore BIND!\n\n\a");
        return 1; //fine programma
     } //end if
    else
        printf("Bind creato con successo!\n");

    //server in ascolto (max 5 connessioni simultanee)
    if(listen(server_socket, 5) < 0)
        printf("Errore Listen!\n\n");
    else
        printf("\n\n+++ SERVER IN ASCOLTO +++\n\n");

    //ciclo infinito per rimanere sempre in ascolto sulla porta TCP-8888
    while(1)
    {
        int client_socket;
        struct sockaddr_in client_addr;

        //client_socket=accept(server_socket,(struct sockaddr*)&client_addr,sizeof(client_addr));
        client_socket=accept(server_socket,NULL,NULL); //creazione socket TCP, poichè localhost posso mettere altri valori come NULL
        //verifica stato della connessione
        if(client_socket>-1)
            printf("Connessione ricevuta!\n");
        else
            printf("Errore connessione!\n");

        //ricezione messaggio e salvataggio in array "buffer"
        recv(client_socket,buffer,sizeof(buffer),0);
        dimensione_msg_ricevuto=strlen(buffer); //misuro dimensione messaggio ricevuto

        //mostro su display il messaggio e la sua dimensione (numero di caratteri che lo compongono)
        printf("Messaggio: %s - Dim ricevuto: %d\n\n",buffer,dimensione_msg_ricevuto);

        //effettuo conversione da numero intero a stringa e poi invio risposta al client
        sprintf(risposta,"%d",dimensione_msg_ricevuto);
        send(client_socket, risposta,sizeof(risposta), 0);

        close(client_socket); //chiudo connessione TCP con clent (in attesa della prossima!)

    } //ciclo infinito

    printf("-- Fine esecuzione server TCP. Arresto in corso... --");

    return 0;
}
