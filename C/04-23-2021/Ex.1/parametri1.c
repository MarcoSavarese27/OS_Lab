#include <stdio.h>

int main (int argc, char **argv){
    if (argc == 1){
        printf("NON SONO STATI PASSATI PARAMETRI\n");
    }
    else{
        printf("%s\n", argv[0]);
        for(int i = 1; i < argc; ++i){
            printf("%d. %s\n", i, argv[i]);
        }
    }
    return 0;
}