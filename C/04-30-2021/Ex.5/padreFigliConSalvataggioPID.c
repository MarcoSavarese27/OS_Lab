#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char const *argv[]){
    if(argc != 2){
        puts("Errore sul numero dei parametri");
        exit(1);
    }

    int N = atoi(argv[1]);

    if(N < 0 || N > 155){
        puts("Errore, il parametro deve essere compreso tra 0 e 155");
        exit(2);
    }
    int pid;
    int pidFiglio, status, exit_s;
    int rando;

    for (int i = 0; i < N; i++){
        pid = fork();
        if(pid < 0){
            puts("Errore in fork");
            exit(3);
        }else if(pid == 0){
            srand(time(NULL));
            printf("Sono il processo figlio numero %d, e ho pid %d\n", (i+1), getpid());
            rando = rand() % (101 + i);
            exit(rando);
        } 
        pidFiglio = wait(&status);
        if(pidFiglio < 0){
            puts("Errore in wait");
            exit(4);
        }
        if((status & 0xFF) != 0){
            puts("Figlio terminato in modo anomalo");
            exit(5);
        }else{
            exit_s = ((status >> 8) & 0xFF);
            printf("Sono il processo padre con pid %d, il mio processo figlio numero %d con pid %d ha generato il numero %d\n", getpid(), (i + 1), pidFiglio, exit_s);
        }
    }
    
    return 0;
}
