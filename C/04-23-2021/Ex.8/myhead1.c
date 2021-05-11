#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){
    if(argc != 2){
        puts("Errore sul numero dei parametri");
        exit(1);
    }

    if(argv[1][0] != '-'){
        puts("Errore, il comando deve essere invocato come ./myhead1 -numero");
        exit(2);
    }

    int n = atoi(&(argv[1][1]));

    int i = 0;
    char buffer;

    while (read(0, &buffer, 1)){
        if(buffer == '\n'){
            ++i;
        }
        write(1, &buffer, 1);
        if(i == n){
            break;
        }
    }

    return 0;
}
