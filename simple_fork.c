##include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //libreria per fork
#include <sys/wait.h> //libreria per usare "wait()"

int main()
{
    int pid;
    pid = fork(); //creazione duplicazione processo

    if(pid==0)
    {
        int id_proc_figlio = getppid(); //ottengo ID processo figlio
        printf("Sono nel processo figlio! - ID: %d\n",id_proc_figlio); //output processo figlio con ID

        int somma=5+3; //eseguo somma nel processo figlio
        exit(somma); //restituisco valore al processo chiamante (in questo caso è il processo padre)
    } //end if (processo figlio)
    else if(pid>0)
    {
        int id_proc_padre = getpid();
        printf("Sono nel processo padre! - ID: %d\n",id_proc_padre);

        int x,y;
        int val_proc_figlio;
        x=1+3; //viene calcolata somma anche senza aspettare processo figlio
        wait(&val_proc_figlio); //attendo processo figlio termini e prende valore restituito
        y = WEXITSTATUS(val_proc_figlio); //converte valore da byte -> decimale

        int z = x + y; //eseguo somma (valore proc padre + val proc figlio)
        printf("Valore ottenuto: %d\n", z);

    } //end if (processo padre)

    printf("Operazione finale eseguita da tutti!- Fine!\n");

    return 0;
} //end main
