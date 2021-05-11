#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){

    if(argc != 3){
        puts("Errore sul numero di parametri");
        exit(1);
    }
    int infile;
    if((infile = open(argv[1], O_RDONLY)) < 0){
        puts("Errore, il primo parametro deve essere un file");
        exit(2);
    }

    int N = atoi(argv[2]);

    if(N < 1){
        puts("Errore, il secondo parametro deve essere un numero intero strettamente positivo");
        exit(3);
    }

    int c = N, nread;
    char b;
    while((nread = read(infile, &b, 1)) > 0){
        if((c % N) == 0){
            printf("%d.\t%c\n", c, b);
            ++c;
            continue;
        }
        ++c;
    }
    close(infile);
    return 0;
}
