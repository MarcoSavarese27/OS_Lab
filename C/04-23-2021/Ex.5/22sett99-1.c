#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]){
    int fd;
    char c;

    if (argc < 3 || argc > 4){
        puts("Errore nel numero dei parametri");
        exit(1);
    }

    if((fd = open(argv[1], O_RDWR)) < 0){
        puts("Errore in apertura del file");
        exit(2);
    }

    if(strlen(argv[2]) != 1){
        puts("Errore secondo parametro non è un carattere");
        exit(3);
    }

    

    if(argv[3] == NULL){
        while(read(fd, &c, 1)){
            if(c == argv[2][0]){
                lseek(fd, -1L, 1);
                write(fd, " ", 1);
            }
        }
        return 0;
    }

    if(strlen(argv[3]) != 1){
        puts("Errore secondo parametro non è un carattere");
        exit(4);
    }

    char s = argv[3][0];

    while(read(fd, &c, 1)){
        if(c == argv[2][0]){
            lseek(fd, -1L, 1);
            write(fd, &s, 1);
        }
    }
    return 0;
}
