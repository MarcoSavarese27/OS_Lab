#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    if(argc != 3){
        puts("ERRORE: passare esattamente due parametri");
        exit(1);
    }

    if((open(argv[1], O_RDONLY) < 0)){
        puts("ERRORE: il primo parametro deve essere un file");
        exit(2);
    }

    if(strlen(argv[2]) != 1){
        puts("ERRORE: il secondo parametro deve essere un carattere");
        exit(3);
    }
    printf("Il nome dell'eseguibile è %s.\nIl primo parametro è un file e si chiama %s, mentre il secondo è un carattere ed è \"%s\"\n", argv[0], argv[1], argv[2]);
    char buffer, Cx = argv[2][0];
    long int counter = 0;
    int nread, f1 = open(argv[1], O_RDONLY); 

    while((nread = read(f1, &buffer, 1)) > 0){
        if(buffer == Cx){
            ++counter;
        }
    }
    close(f1);
    printf("Il carattere %c compare %ld volte nel file %s\n", Cx, counter, argv[1]);
    return 0;
}
