#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    if (argc != 2){                                                                 /*controllo sul numero di parametri*/
        puts("Errore nel numero dei parametri, devono essere 2");
        exit(1);
    }
    
    int N = atoi(argv[1]);                                                          /*controllo sul primo e unico parametro*/
    if(N < 0 || N >255){
        puts("Errore, il primo parametro deve essere compreso tra 0 e 255");
        exit(2);
    }

    int pid;                                                                           /*necessario alla fork()*/
    int pidFiglio, status, ritorno;                                                    /*per wait padre*/

    printf("Sono il processo padre con pid %d e creerò %d figli\n", getpid(), N);

    for(int i = 0; i < N; ++i){
        if((pid = fork()) < 0){
            puts("Errore in fork");
            exit(3);
        }else if(pid == 0){
            printf("Sono il processo figlio numero %d e ho pid %d\n", (i+1), getpid());
            exit((i+1));
        }
        if((pidFiglio = wait(&status)) < 0){
            puts("Errore in wait");
            exit(4);
        }
        if((status & 0xFF) != 0){
            printf("Processo figlio con pid %d terminato in modo anomalo", pidFiglio);
        }else{
            ritorno = (status >> 8) & 0xFF;
            printf("E io sono il padre, mio figlio con indice %d ha pid %d\n", ritorno, pidFiglio);
        }
    }


    return 0;
}
