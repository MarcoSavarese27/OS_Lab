#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void filtro(int i, int n, char c, int d){
    while (read(d, &c, 1)){
        if(c == '\n'){
            ++i;
        }
        write(1, &c, 1);
        if(i == n){
            break;
        }
    }
}

int main(int argc, char const *argv[]){
    int i = 0;
    if(argc == 2){
        if(argv[1][0] != '-'){
            puts("Errore, invocazione errata del comando, usare i seguenti formati:\n-./myhead3\n-./myhead3 -numero\n-./myhead3 -numero file");
            exit(1);
        }
        int n = atoi(&(argv[1][1]));
        char buffer = 0;
        filtro(i, n, buffer, 0);
    }
    else if(argc == 1){
        int n = 10;
        char buffer = 0;
        filtro(i, n, buffer, 0);
    }
    else if(argc == 3){
        int infile;
        if(argv[1][0] != '-'){
            puts("Errore, invocazione errata del comando, usare i seguenti formati:\n-./myhead3\n-./myhead3 -numero\n-./myhead3 -numero file");
            exit(1);
        }
        if((infile = open(argv[2], O_RDONLY)) < 0){
            puts("Errore in apertura del file");
            exit(2);
        }
        int n = atoi(&(argv[1][1]));
        char c = 0;
        filtro(i, n, c, infile);
    }
    else{
        puts("Errore sul numero dei parametri");
        exit(3);
    }
    return 0;
}
