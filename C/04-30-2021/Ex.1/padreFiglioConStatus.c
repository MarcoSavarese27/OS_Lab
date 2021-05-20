#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char const *argv[]){
    int pidf = getpid();
    printf("Questo è l'id del processo padre -> %d\n", pidf);
    srand(time(NULL));
    int pids, status, exit_s;

    if((pids = fork()) < 0){
        puts("Errore in fork");
        exit(1);
    }

    if (pids == 0){
        printf("Sono il processo figlio, il mio pid è -> %d\nIl pid di mio padre è -> %d\n", getpid(), pidf);
        int casuale=rand() % 100;
        exit(casuale);
    }

    pids = wait(&status);
    if (pids < 0){
    puts("Errore wait");
    exit(2);
    }

    if((status & 0xFF)!= 0){
        puts("Figlio terminato in modo involontario");
    }else{
        exit_s=status >> 8;
        exit_s &= 0xFF;
    }

    printf("Sono il processo padre con pid %d, ho creato il processo figlio con pid %d\nIl processo figlio ha generato il numero %d\n", pidf, pids, exit_s);
    return 0;
}
