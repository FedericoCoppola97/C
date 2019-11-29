#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 8
#define C 6
#define DIM 3
#define DIM_ARRAY 10

int mat_combinazioni[R][C]= { //0->7 combianzioni
                            {0,0,0,1,0,2}, // combinazione A
                            {1,0,1,1,1,2}, // combinazione B
                            {2,0,2,1,2,2}, // combinazione C
                            {0,0,1,0,2,0}, // combinazione D
                            {0,1,1,1,2,1}, // combinazione E
                            {0,2,1,2,2,2}, // combinazione F
                            {0,0,1,1,2,2}, // combinazione G
                            {0,2,1,1,2,0}  // combinazione H
                       }; //end matrice combinazioni

int matrice_gioco[DIM][DIM]; //matrice gioco 3 x 3


typedef struct esito_scansione {
   int evento;
   int giocatore_evento;
} Esito;


//prototipi funzioni
void setup_matrice(); //funzione che configura la matrice con tutte le celle pari a 0
void presentazione_gioco(); //funzione di stampa delle regole del gioco e modalità disponibili
void print_mat(); //funzione per visualizzare la matrice
void print_mat_gioco(); //funzione per visualizzare la matrice di gioco
void primo_input_computer(); //funzione per effettuare il primo input random da parte del computer
int modalita_gioco(); //si sceglie la modalità di gioco (giocatore vs computer oppure giocatore 1 vs giocatore 2)
void modalita_robot(); //funzione che permette di giocare umano vs computer
void modalita_giocatore(); //funzione che permette di giocare giocatore1 vs giocatore2
void input_giocatore(unsigned short int player); //funzione che gestisce l'input del giocatore
Esito scansione(int identificatore_1, int identificatore_2, int opzione); //funzione che si occupa di scansionare la matrice
void azione_robot(int blocco_giocatore[],int dim_giocatore,int continuare_robot[],int dim_robot,int misto[],int dim_misto);
void scrittura_log(Esito x,int inizio_match,int modalita_match); //funzione per scrivere log in un file di testo
void inizializzo_random(); //funzione per inizializzare il seme della funzione "rand()"


int main()
{
    int scelta=0;
    Esito e;
    char continuare;

    e.evento=0; //inizializzo variabile evento della struct

  do{
        presentazione_gioco(); //stampo informazioni sul gioco
        setup_matrice(); //inizializzo matrice
        scelta = modalita_gioco(); //funzione per scegliere modalità di gioco

        //switch case per avviare modalità di gioco scelta
        switch(scelta)
        {
            case 1: //scelta 1 modalità giocatore vs computer
                system("clear");
                scrittura_log(e,1,1); //scrittura log che inizia la partita
                modalita_robot(); //funzione per partita giocatore vs computer
            break;

            case 2:
                system("clear");
                scrittura_log(e,1,2); //scrittura log che inizia la partita
                modalita_giocatore(); //funzione per partita giocatore1 vs giocatore2
            break;
        } //end switch-case

        //ripetere gioco del tris?
        printf("\nRipetere il gioco? Premere Y per continuare, premere un altro carattere per finire il gioco: ");
        scanf(" %c",&continuare);

        system("clear");

}while(continuare=='y' || continuare=='Y'); //end do-while loop


    printf("**** Fine del gioco ****"); //output che comunica la fine del gioco

    return 0;
} //end main



/****** FUNZIONI ******/

int modalita_gioco()
{
    int scelta_modalita=0;


    do{
        printf("Scegliere la modalità di gioco [1 oppure 2]: ");
        scanf("%d",&scelta_modalita);

        if(scelta_modalita!=1 && scelta_modalita!=2)
            printf("Errore! Ripetere scelta della modalita' di gioco\n");

    }while(scelta_modalita!=1 && scelta_modalita!=2); //end do-while

    return scelta_modalita; //return valore scelta modalità di gioco

} //end modalita gioco


void modalita_robot()
{
    Esito risultato;
    int continua=0;
    int turno=0; //variabile che stabilisce il turno ( 0 ==> giocatore e 1 ==> computer)
    primo_input_computer();

    printf(">> Modalita Giocatore1 vs Robot! << \n");
    system("sleep 3");

    while(continua!=1) //da cambiare con la verifica del tris o matrice piena
    {
        system("clear"); //pulizia console
        print_mat_gioco(); //visualizzo matrice di gioco

        if(turno==0)
        {
            input_giocatore(1);
            risultato=scansione(1,3,0); //eseguo scansione della matrice di gioco solamente per determinare se è possibile continuare
        } //end if
        else if(turno==1)
        {
            risultato=scansione(1,3,1); //eseguo scansione della matrice di gioco per eseguire input del robot
            risultato=scansione(1,3,0); //eseguo scansione della matrice di gioco solamente per determinare se è possibile continuare
        } //end else-if


        //verifico se si è scatenato evento
        if(risultato.evento>0)
        {
            continua=1; //variabile che fa terminare il loop
            scrittura_log(risultato,0,2); //richiamo la funzione per scrivere log riguardo la fine della partita
        }

        turno=!turno; //nego turno (0-->1 e 1-->0)

    } //end ciclo while

} //end modalita_robot


void setup_matrice()
{
    for(int i=0; i < DIM; i++)
        for(int j=0;j<DIM;j++)
            matrice_gioco[i][j]=0; //azzero valori della matrice di gioco
} //end setup_matrice


//funzione per visualizzare celle matrice di gioco
void print_mat_gioco()
{
    for(int i=0; i < DIM; i++)
    {
        for(int j=0;j<DIM;j++)
            printf("%d", matrice_gioco[i][j]);
         printf("\n");
    } //end matrice

    printf("\n\n");

} //end print_mat_gioco


void presentazione_gioco()
{
    system("clear"); //pulizia console
    printf("Benvenuto nel gioco del tris!\n\n");
    printf("Sono presenti due modalita' di gioco:\n1 - Giocatore VS Computer\n2 - Giocatore1 VS Giocatore2\n\n");
} //end presentazione gioco


void primo_input_computer()
{
    int num1=0,num2=0;

    inizializzo_random();

    num1 = rand() % 3; //genero numero casuale
    num2 = rand() % 3; //genero numero casuale

    matrice_gioco[num1][num2]=3; //robot esegue input (casuale)
} //end primo_input_computer

void input_giocatore(unsigned short int player)
{
    int r_giocatore=0,c_giocatore=0; //variabili per indicare riga e colonna della matrice selezionate
    unsigned short int input_ok; //variabile che indica che indica che l'input è possibile

    input_ok=0; //inizializzo variabile

    //ciclo per gestione input giocatore
    while(input_ok==0)
    {
        printf("Giocatore %d - Digitare riga: ",player);
        scanf("%d",&r_giocatore);
        printf("Giocatore %d - Digitare colonna: ",player);
        scanf("%d",&c_giocatore);

        r_giocatore = r_giocatore - 1; //decremento riga scelta poichè gli indici della matrice partono da zero
        c_giocatore = c_giocatore - 1; //decremento colonna scelta poichè gli indici della matrice partono da zero

        //verifica input corretto ed è possibile
        if((matrice_gioco[r_giocatore][c_giocatore]==0) && (r_giocatore > -1 && r_giocatore < 3 ) && (c_giocatore > -1 && c_giocatore < 3))
        {
            matrice_gioco[r_giocatore][c_giocatore]=player;
            input_ok = 1;
        }
        else
            printf("Input non valido, ripetere la propria scelta!\n\a");
    } //end ciclo while


} //end input_giocatore

Esito scansione(int identificatore_1, int identificatore_2,int opzione)
{
    int conta_mat_combinazioni=0; //variabile contatore
    int temp1=0,temp2=1;//variabili temporanee per confrontare valori della matrice di gioco
    int conta_input_identificatore1=0, conta_input_identificatore2=0,conta_cella_vuota=0,conta_combinazioni_terminate=0;
    int index_array_bloccare=-1, index_array_continuare=-1, index_array_misto=-1, index_array_terminato=-1; //indici array

    Esito esito;
    esito.evento=0;

    int valori_temp[3];
    int array_giocatore_da_bloccare[DIM_ARRAY];
    int array_robot_da_continuare[DIM_ARRAY];
    int array_combinazioni_misto[DIM_ARRAY];
    int array_combinazioni_terminato[DIM_ARRAY];

    int x=0, y=1, k=0;

    do
    {

        while(x<=4 && y<=5)
        {
            temp1 = mat_combinazioni[conta_mat_combinazioni][x]; //seleziono cella pari    (riga)
            temp2 = mat_combinazioni[conta_mat_combinazioni][y]; //seleziono cella dispari (colonna)

            valori_temp[k]=matrice_gioco[temp1][temp2]; //estraggo valore utilizzando le coordinate recuperate da mat_combinazioni

            x=y+1; //ottengo solo indice pari
            y=x+1; //ottengo solo indice dispari
            k++;   //incremento indice array "valori_temp"
        } //end while

        x=0;y=1;k=0; //reset valori

        /*
            Verifica di quanti input del giocatore ci sono, verifica di dove il robot ha eseguito l'input
            Se ci sono due input del giocatore --> da bloccare
            Se c'è un input del computer senza input del giocatore  --> aggiungere input per fare tris
            Se ci sono entrambi gli input, ma non tutte le celle sono piene --> terza opzione di tris
            Se tutte le celle sono piene combinazione viene messa in un'array temporaneo "combinazioni_esaurite"
         */
        for(int i=0; i < 3; i++)
        {
            if(valori_temp[i]==identificatore_1)
                conta_input_identificatore1++; //incremento contatore input giocatore
            else if(valori_temp[i]==identificatore_2)
                conta_input_identificatore2++; //incremento contatore input computer
            else if(valori_temp[i]==0)
                conta_cella_vuota++; //incremento contatore celle vuote non usate
        } //end for

        //inserisco indentificatore delle combinazioni nei rispettivi array
        if(conta_input_identificatore1==2 && conta_input_identificatore2==0 && conta_cella_vuota==1) //considero input giocatore solo se ha quasi fatto tris
        {
            index_array_bloccare++; //incremento indice per prossimo input
            array_giocatore_da_bloccare[index_array_bloccare]=conta_mat_combinazioni; //salvo valore nell'array
        }
        else if(conta_input_identificatore1==0 && conta_input_identificatore2>=1 && conta_cella_vuota>=1) // considero input robot da continuare se c'è un suo input esclusivo nella combinazione
        {
            index_array_continuare++; //incremento indice per prossimo input
            array_robot_da_continuare[index_array_continuare]=conta_mat_combinazioni; //salvo valore nell'array
        }
        else if(conta_input_identificatore1<=2 && conta_input_identificatore2<=2 && conta_cella_vuota==0) // considero solamente se ci sono input del giocatore e robot, ma senza celle libere
        {
            index_array_terminato++; //incremento indice per prossimo input
            array_combinazioni_terminato[index_array_terminato]=conta_mat_combinazioni; //salvo valore nell'array
            conta_combinazioni_terminate++; //contatore combinazioni piene e non più utilizzabili
        }
        else if((conta_input_identificatore1==3 || conta_input_identificatore2==3) && conta_cella_vuota==0)
        {
            system("clear");
            print_mat_gioco();
            printf("\n\nFINE MATCH: TRIS!!!\n\n");
            esito.evento=1;

            if(conta_input_identificatore1==3)
                esito.giocatore_evento=identificatore_1; //comunico giocatore vincitore
            else
                esito.giocatore_evento=identificatore_2; //comunico giocatore vincitore

        } //verifico che ci sia tris
        else
        {
            index_array_misto++; //incremento indice per prossimo input
            array_combinazioni_misto[index_array_misto]=conta_mat_combinazioni;
        }

        conta_mat_combinazioni=conta_mat_combinazioni+1; //incremento contatore numero totali di cicli while
        conta_input_identificatore1=0;conta_cella_vuota=0;conta_input_identificatore2=0; //azzero contatori

    }while(conta_mat_combinazioni < 8 && esito.evento==0); //end while

    //se tutte le combinazioni per ottenere il tris sono state esaurite senza successo, si verifica pareggio
    if(conta_combinazioni_terminate==8)
    {
        system("clear");
        print_mat_gioco();
        printf("FINE MATCH: PAREGGIO!!!\n\n");
        esito.evento=2; //esito partita
    } //end if


    //richiamo funzione solamente se è il robot che deve eseguire input (opzione == 1)
    if(opzione==1 && esito.evento==0)
    {
        index_array_bloccare=index_array_bloccare+1; //dimensione = indice + 1
        index_array_continuare=index_array_continuare+1; //dimensione = indice + 1
        index_array_misto=index_array_misto+1; //dimensione = indice + 1
        azione_robot(array_giocatore_da_bloccare,index_array_bloccare,array_robot_da_continuare,index_array_continuare,array_combinazioni_misto,index_array_misto); //richiamo funzione dopo scansione
    } //end if

    index_array_bloccare=-1; index_array_continuare=-1; index_array_misto=-1; index_array_terminato=-1; //reset indici array temporanei
    conta_combinazioni_terminate=0; //azzero contatore

    return esito; //restituisco valore

} //end scansione_robot

void azione_robot(int blocco_giocatore[],int dim_giocatore,int continuare_robot[],int dim_robot,int misto[],int dim_misto)
{
    char array_scelta[3]; //array che contiene la scelta

    char char_scelta;
    int estr_combinazione=0,index_combinazione=0, val_attuale=0;
    int x=0,y=0;
    int temp=0;

    //se gli indici hanno valore maggiore o uguale a zero significa che sono stati usati e conosco dim array
    if(dim_giocatore > 0)
    {
        array_scelta[i]='a'; //blocco giocatore
        i++;
    } //end if

    if(dim_robot > 0)
    {
        array_scelta[i]='b'; //continuare robot
        i++;
    } //end if

    if(dim_misto > 0)
    {
        array_scelta[i]='c'; //mix
        i++;
    } //end if

    //numero random in range determinato da quanti array sono davvero utilizzabili
    if(i > 1)
    {
        inizializzo_random(); //inizalizzo seme per generazione numeri casuali
        scelta=rand()%i; //salvo scelta --> range da 0 fino a i-1 (idiale per indice array)
        char_scelta=array_scelta[scelta];
    }
    else if(i == 1)
        char_scelta=array_scelta[0]; //c'è una sola possibilità, indico prima combinazione dell'array (si può eliminare, da verificare)


    //switch case
    switch(char_scelta)
    {
        case 'a': //blocco giocatore
                inizializzo_random(); //inizializzo seme per generazione numeri casuali
                temp=rand()%dim_giocatore; //estrazione numero casuale
                estr_combinazione = blocco_giocatore[temp]; //estraggo numero casuale (0 --> dim_giocatore-1) per scegliere la combinazione
        break;


        case 'b': //continuare robot

          inizializzo_random(); //inizializzo seme per generazione numeri casuali
          temp=rand()%dim_robot; //estrazione numero casuale
          estr_combinazione = continuare_robot[temp]; //estraggo numero casuale (0 --> dim_giocatore-1) per scegliere la combinazione
        break;

        case 'c': //mix
            inizializzo_random(); //inizializzo seme per generazione numeri casuali
            temp=rand()%dim_misto; //estrazione numero casuale
            estr_combinazione = misto[temp]; //estraggo numero casuale (0 --> dim_giocatore-1) per scegliere la combinazione
        break;
    } //end


        //estrazione di due numeri che sono la riga e la colonna della combinazione scelta prima
        do{
            inizializzo_random();  //inizializzo seme per generazione numeri casuali
            index_combinazione = rand()%5; //estrazione numero casuale  range 0 --> 4

            //determino coordinate da considerare
            if(index_combinazione%2==0 || index_combinazione==0)
            {
                x = mat_combinazioni[estr_combinazione][index_combinazione];
                y = mat_combinazioni[estr_combinazione][index_combinazione+1];
            } //end if
            else if(index_combinazione%2==1)
            {
                y = mat_combinazioni[estr_combinazione][index_combinazione];
                x = mat_combinazioni[estr_combinazione][index_combinazione-1];
            } //end else if

            val_attuale = matrice_gioco[x][y]; //leggo valore attuale della cella scelta della matrice

            //se il contenuto della cella è pari a zero allora è vuota
            if(val_attuale==0)
            {
                matrice_gioco[x][y]=3; //scrivo valore nella cella scelta
                input_completato=1; //cambio valore variabile di stato che indica che l'input è stato eseguito
            } //end if se è possibile eseguire l'input con i numeri estratti, altrimenti ripetere ciclo while

        }while(input_completato!=1); //fine del ciclo se computer ha eseguito input nella matrice

} //end funzione azione robot


//funzione per scrivere nel file di log
void scrittura_log(Esito x,int inizio_match,int modalita_match)
{
    FILE *f_ptr; //puntatore per gestire il file
    //Esito accaduto;
    char messaggio[150];

    //ottengo orario
    time_t t;
    time(&t);

   f_ptr = fopen("partita.txt", "a"); //apro il file in modalità lettura

    /* scrittura dei log in base agli eventi/stati del gioco */
    if(inizio_match==1)
    {
        sprintf(messaggio,"Inizio Partita - Modalita': %d - Orario: %s!\n",modalita_match,ctime(&t)); //creazione string di log inizio partita
        fprintf(f_ptr,messaggio); //scrivo nel file
    }

    else if(x.evento==1 && inizio_match==0)
    {
        sprintf(messaggio, "Fine della partita: TRIS! Ha vinto il giocatore: %d - Orario: %s\n",x.giocatore_evento, ctime(&t)); //creazione string di log vittoria tris
        fprintf(f_ptr,messaggio); //scrivo nel file
    } //end if
    else if(x.evento==2 && inizio_match==0)
    {
        sprintf(messaggio, "Fine della partita: PAREGGIO! - Orario: %s\n",ctime(&t)); //creazione string di log vittoria tris
        fprintf(f_ptr,messaggio); //scrivo nel file
    }
   fclose(f_ptr); //chiusura file
} //end scrittura_log


void modalita_giocatore()
{
    int turno_giocatore=1; //variabile che serve per indicare il turno del giocatore (giocatore1 o giocatore2)
    Esito e; //dato di tipo struct Esito

    printf(">> Modalita Giocatore1 vs Giocatore2! << \n");
    system("sleep 3");

    //finchè l'evento è zero si continua a giocare (è possibile continuare il gioco)
    while(e.evento==0)
    {
        system("clear"); //pulizia console
        print_mat_gioco(); //visualizzo matrice di gioco

        if(turno_giocatore==1)
        {
            input_giocatore(turno_giocatore); //richiamo la funzione per effettuare input giocatore
            turno_giocatore++;
        } //end if
        else if(turno_giocatore==2)
        {
            input_giocatore(turno_giocatore); //richiamo la funzione per effettuare input giocatore
            turno_giocatore--;
        } //end else if

        e=scansione(1,2,0); //eseguo scansione matrice post input del giocatore

        //richiamo la funzione per scrivere i log in base all'evento
        if(e.evento==1)
            scrittura_log(e,0,1);
        else if(e.evento==2)
            scrittura_log(e,0,2);

    } //end while
} //end modalita_giocatore

//funzione per inizializzare seme utilizzando il tempo
void inizializzo_random()
{
    time_t t;
    srand((unsigned) time(&t));
} //end inizializzo_random
