/*
    Federico Coppola

    Dichiarazione struct
    Creazione array utilizzando lo struct persona
    Input e Output utilizzando l'array dello struct persona
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct persona
{
    char nome[50];
    char citta[50];
    int eta;
}Persona; //end struct Persona



int main()
{
    Persona elenco_cittadini[3];

    for(int i=0; i < 3; i++)
    {
        printf("Digitare nome cittadino: ");
        scanf("%s",elenco_cittadini[i].nome);
        printf("Digitare citta' di nascita: ");
        scanf("%s",elenco_cittadini[i].citta);
        printf("Digitare anni del cittaino: ");
        scanf("%d",&elenco_cittadini[i].eta);
        system("clear");
    } //end for

    printf("\n\nElenco cittadini: \n\n");

    for(int k=0; k<3;k++)
        printf("Nome: %s - Citta': %s - Anni: %d\n",elenco_cittadini[k].nome,elenco_cittadini[k].citta,elenco_cittadini[k].eta);


    printf("\n\nFine!\n");

    return 0;
} //end main
