#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numero=0,somma=0;
    int *p_numero; //puntatore per variabile numero

    //input numero
    printf("Digitare numero: ");
    scanf("%d",&numero);

    p_numero = &numero; //salvo indirizzo nella variabile puntatore

    printf("Indirizzo variabile %p\n",p_numero);

    //somma utilizzando il puntatore (leggo valore nella cella tramite address e sommo 5)
    somma = *p_numero + 5;

    //output somma
    printf("Somma: %d",somma);

    printf("\nFine!\n");

    return 0;
}
