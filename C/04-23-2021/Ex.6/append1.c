#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define PERM 0644

int appendfile(char *fi){
    int outfile, nread;
    char buffer[BUFSIZ];
    
    if((outfile=open(fi,O_WRONLY | O_APPEND | O_CREAT, PERM))<0){
        return 1;
    }

    while((nread = read (0, buffer, BUFSIZ)) > 0){
        if(write(outfile, buffer, nread) < nread){
            close(outfile);
            return 2;
        }
    }
    close(outfile); 
    return 0;
}


int main (int argc, char ** argv){ 
    int integi;

    if (argc != 2){
        printf("ERRORE: ci vuole un argomento \n"); 
        exit (3);
    }   

    integi = appendfile(argv[1]);
    exit(integi);
}
