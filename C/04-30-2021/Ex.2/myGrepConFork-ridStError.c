#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main (int argc, char** argv){
int pid;
int pidFiglio, status, ritorno;

if (argc != 3){
    printf("Errore nel numero di parametri che devono essere due (stringa da cercare e nome del file dove cercare): %d\n", argc);
    exit(1);
}

pid = fork();
if (pid < 0){
    printf("Errore in fork\n");
    exit(2);
}
if (pid == 0){
    printf("Esecuzione di grep da parte del figlio con pid %d\n", getpid());
    close(1);
    open("/dev/null", O_WRONLY);
    execlp("grep", "grep", argv[1], argv[2], (char *)0);
    exit(-1);
}

pidFiglio = wait(&status);
if (pidFiglio < 0){
    printf("Errore wait\n");
    exit(3);
}
if ((status & 0xFF) != 0){
    printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
}
else{
    ritorno=(int)((status >> 8) & 0xFF);
    printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
}
exit (0);
}