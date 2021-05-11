#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int mia_random(int n){
    int casuale;
    casuale = rand() % n;
    return casuale;
}

int main (int argc, char **argv){
    int FPID = getpid();
    printf("PID processo padre: %d\n", FPID);
    int pid = fork();
    int CPID;
    int status, exit_s;
    int random;
    if (pid < 0){
        printf("ERRORE fork non andata a buon fine\n");
        exit(1);
    }
    if(pid == 0){
        srand(time(NULL));
        printf("PID processo figlio: %d\nIl PID del suo processo padre è: %d\n", getpid(), FPID);
        random = mia_random(100);
        exit(random);
    }

    if ((CPID=wait(&status))<0){
        printf("Errore in wait \n");
        exit(2);
    }
    if((status & 0xFF)!= 0){
        printf("figlio terminato in modo involontario\n");
    }else{
        exit_s=status >> 8;
        exit_s &= 0xFF;
    }
    printf("Ho generato il figlio %d e ha calcolato %d\n", pid, exit_s);
    return 0;
}