#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){

    if(argc == 2){
        if(argv[1][0] != '-'){
            puts("Errore, il comando deve essere invocato come ./myhead1 -numero o solo ./myhead");
            exit(1);
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

    }else if(argc == 1){
        int n = 10;

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
    }else{
        puts("Errore sul numero dei parametri");
        exit(2);
    }

    

    return 0;
}
