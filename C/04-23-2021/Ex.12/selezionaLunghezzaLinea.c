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

    int i = 1, s = 0, find = 0;
    char c[255];

    while((read(infile, &c[s], 1)) != 0){
        if (c[s] == '\n'){
            if (N == (s + 1)){
                c[s + 1] = '\0';
                find = 1;
                printf("La linea numero %d del file %s ha la lunghezza cercata %d:\n%s", i, argv[1], N, c);
            }
            ++i;
            s = 0;
        }else{
            ++s;
        }
    }
    if(!find)
        puts("Nessuna linea trovata");
    return 0;
}
