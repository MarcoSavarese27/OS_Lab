#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){
    char buffer [BUFSIZ];
    int nread, fd = 0;
    if(argc == 1){
        puts("Nessun file passato");
        return 0;
    }
    for (size_t i = 1; i < argc; i++){
        if((fd = open(argv[i], O_RDONLY))< 0){
            puts("Errore in apertuta del file");
            exit(1);
        }
        printf("-------------------------------\nStai leggendo il file %s\n-------------------------------\n", argv[i]);
        while((nread = read (fd, buffer, BUFSIZ)) > 0){
            write(1, buffer, nread);
        }
    }
    return 0;
}