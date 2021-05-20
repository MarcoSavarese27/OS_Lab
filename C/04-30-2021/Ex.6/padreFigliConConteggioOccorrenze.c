#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    if(argc < 4){
        puts("Errore sul numero dei parametri");
        exit(1);
    }
    char Cx;
    for(int i = 1; i < argc; ++i){
        if(i == argc -1){
            if(strlen(argv[i]) != 1){
                puts("Errore, l'ultimo parametro non è un carattere");
                exit(2);
            }
            Cx = argv[i][0];
            break;
        }
        if(open(argv[i], O_RDONLY) < 0){
            printf("Errore sul file numero %d\n", (i+1));
            exit(3);
        }
    }

    int pid;
    int pidFiglio, status, exit_s;
    int infile, counter = 0, nread;
    char c;

    for(int i = 1; i < (argc - 1); ++i){
        pid = fork();
        if(pid < 0){
            puts("Errore in fork");
            exit(4);
        }else if(pid == 0){
            infile = open(argv[i], O_RDONLY);
            while((nread = read(infile, &c, 1)) > 0){
                if(Cx == c){
                    ++counter;
                }
            }
            exit(counter);
        }
        pidFiglio = wait(&status);
        if(pidFiglio < 0){
            puts("Errore in wait");
            exit(5);
        }
        if((status & 0xFF) != 0){
            puts("Figlio terminato in modo anomalo");
            exit(6);
        }else{
            exit_s = (status >> 8) & 0xFF;
            printf("Sono il processo padre, il mio figlio numero %d con pid %d ha trovato %d occorrenze del carattere %c nel file %s\n", i, pidFiglio, exit_s, Cx, argv[i]);
        }
    }
    return 0;
}
