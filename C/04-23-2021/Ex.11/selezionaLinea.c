#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char const *argv[]){

    if(argc != 3){
        puts("Errore sul numero dei parametri");
        exit(1);
    }

    int infile;
    if((infile = open(argv[1], O_RDONLY)) < 0){
        puts("Errore sul file, non esistente o non apribile");
        exit(2);
    }

    int N = atoi(argv[2]);

    if(N < 1){
        puts("Errore sul secondo parametro, deve essere un numero intero strettamente positivo");
        exit(3);
    }

    int i = 1, s = 0;
    char c;

    while(read(infile, &c, 1)){
        if(c == '\n'){
            ++i;
            continue;
        }
        if(i == N){
            s = 1;
            write(1, &c, 1);
        }
    }
    if(s == 0){
        puts("Il file è più corto");
    }else{
    printf("\n");
    }
    return 0;
}
