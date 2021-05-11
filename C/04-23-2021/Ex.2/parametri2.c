#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    if(argc != 4){
        puts("ERRORE: passare esattamente 3 parametri");
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0){
        puts("ERRORE: il primo parametro non è un file o non esiste");
        exit(2);
    }else{
        printf("Il nome dell'eseguibile è %s \n", argv[0]);
        printf("%s è un file\n", argv[1]);
    }
    int n = atoi(argv[2]);
    if(n < 1){
        puts("ERRORE: il secondo parametro deve essere un numero strettamente positivo");
        exit(3);
    }else{
        printf("%d è un numero intero positivo\n", n);
    }
    char c;
    if (strlen(argv[3])!= 1){
        puts("ERRORE: il terzo parametro deve essere un carattere");
        exit (4);
    }else{
        c = argv[3][0];
        printf("%c è un carattere\n", c);
    }

    return 0;
}
