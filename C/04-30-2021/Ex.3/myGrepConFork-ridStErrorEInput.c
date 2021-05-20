#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    int pid;
    int pidFiglio, status, ritorno;
    if (argc != 3){
        printf("Errore nel numero dei parametri, devono essere due (stringa da cercare e dove cercarla): %d\n", argc);
        exit(1);
    }

    pid = fork();
    if(pid < 0){
        puts("Errore in fork");
        exit(2);
    }

    if(pid == 0){
        printf("Esecuzione del grep da parte del figlio con pid %d\n", getpid());
        close(0);
        if((open(argv[2], O_RDONLY)) < 0){
            printf("Errore nell'apertura del file\n");
            exit(-1);
        }
        close(1);
        open("/dev/null", O_WRONLY);
        close(2);
        open("/dev/null", O_WRONLY);
        execlp("grep", "grep", argv[1], (char*) 0);
        exit(-1);
    }

    pidFiglio = wait(&status);
    if (pidFiglio < 0){
        printf("Errore wait\n");
        exit(3);
    }
    if ((status & 0xFF) != 0)
        printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
    else{
        ritorno=(int)((status >> 8) & 0xFF);
        printf("Il figlio con pid=%d ha ritornato %d (se 255 è un problema!)\n", pidFiglio, ritorno);
    }
    return 0;
}
