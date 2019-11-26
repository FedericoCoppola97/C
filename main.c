//Federico Coppola
//scrittura su file di testo

#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE *p_file; //puntatore file
    char frase_in[50];
    char frase_out[50];

    p_file = fopen("file.txt", "w"); //apro file di testo

    //input della frase da scrivere
    printf("Digitare messaggio da salvare [no spazi]: \n");
    fgets(frase_in,sizeof(frase_in),stdin);

    //scrivo su file + chiusura del file
    fopen("file.txt","w");
    fprintf(p_file,frase_in);
    fclose(p_file);

    //leggo dal file
    fopen("file.txt","r");
    fscanf(p_file,"%s",frase_out);
    fclose(p_file);

    printf("Frase scritta:\n%s",frase_out);


    return 0;
}
