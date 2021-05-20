#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#define PERM 0644

int main(int argc, char const *argv[]){
    if(argc < 4){
        puts("Errore sul numero dei parametri");
        exit(1);
    }

    for(int i = 1; i < argc; ++i){
        if((open(argv[i], O_RDONLY) < 0)){
            printf("Errore sul parametro no. %d", i);
            exit(2);
        }
    }
    int pid, pidn;
    int pidFiglio, pidNipote, status_F, status_N, exit_F, exit_N;
    int FdW;
    char sort[5] =".sort", *FOut;

    for(int i = 0; i < (argc - 1); ++i){
        pid = fork();
        if(pid < 0){
            puts("Errore in fork(figlio)");
            exit(3);
        }else if(pid == 0){
            FOut = (char *) malloc(strlen(argv[i + 1]) + 6);
            if(FOut == NULL){
                exit(-1);
            }
            strcpy(FOut, argv[i + 1]);
            strcat(FOut, sort);
            FdW = creat(FOut, PERM);
            if(FdW < 0){
                printf("Impossibile creare il file %s\n", FOut);
                exit(-1);
            }
            close(FdW);
            pidn = fork();
            if(pidn < 0){
                puts("Errore in fork(nipote)");
                exit(4);
            }else if(pidn == 0){
                close(0);
                open(argv[i + 1], O_RDONLY);
                close(1);
                open(FOut, O_WRONLY);
                execlp("sort", "sort", (char *) 0);
                perror("Il nipote non ha fatto la sort\n");
                exit(-1);
            }
            pidNipote = wait(&status_N);
            if(pidNipote < 0){
                puts("Errore in wait del nipote");
                exit(5);
            }
            if((status_N & 0xFF) != 0){
                puts("Nipote terminato in modo anomalo");
                exit(6);
            }else{
                exit_N = (status_N >> 8) & 0xFF;
                exit(exit_N);
            }
        }
        pidFiglio = wait(&status_F);
        if(pidFiglio < 0){
            puts("Errore in wait del figlio");
            exit(7);
        }
        if((status_F & 0xFF) != 0){
            puts("Figlio ritornato in modo anomalo");
            exit(8);
        }else{
            exit_F = (status_F >> 8) & 0xFF;
            printf("Sono il processo padre, il mio figlio con pid %d mi ha ritornato %d\n", pidFiglio, exit_F);
        }
    }
    return 0;
}
