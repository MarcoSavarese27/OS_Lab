#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#define MSGSIZE 512

int main(int argc, char const *argv[]){
	int pid, j, piped[2], c = 0;
	char mess[MSGSIZE], msg1;
	char inpbuf[MSGSIZE];

	int pidFiglio, status, ritorno;

	if (argc != 2){
		printf("Numero di parametri errato %d: ci vuole un singolo parametro\n", (argc -1));
		exit(1);
	}

	if(pipe(piped) < 0){
		printf("Errore in creazione pipe\n");
		exit(2);
	}
	if ((pid = fork()) < 0){
		printf("Errore creazione figlio\n");
		exit (3);
	}
	if (pid == 0){															
		int fd;
		close (piped [0]);													
		if ((fd = open(argv[1], O_RDONLY)) < 0){
			printf("Errore in apertura file %s\n", argv[1]);
			exit(-1); 														
		}
		printf("Figlio %d sta per iniziare a scrivere una serie di messaggi, ognuno di lunghezza variabile, sulla pipe dopo averli letti dal file passato come parametro\n", getpid());
		j=0; 										
		while (read(fd, &msg1, 1) > 0){ 							     	
			if(msg1 == '\n'){
				mess[c] = 0;
				++c;
				write(piped[1], &c, sizeof(int));
				write(piped[1], mess, c);
				c = 0;
				j++;
				continue;
			}
			mess[c] = msg1;
			++c;
		}
		c = 513;
		write(piped[1], &c, sizeof(int));
		printf("Figlio %d scritto %d messaggi sulla pipe\n", getpid(), j);
		exit(0);
	}
	close(piped[1]);
	printf("Padre %d sta per iniziare a leggere i messaggi dalla pipe\n", getpid());
	j = 0;
	
	while(1){
		read(piped[0], &c, sizeof(int));
		if(c == 513){
			break;
		}
		read(piped[0], inpbuf, c);
		printf("%d: %s\n", j, inpbuf);
		j++;
	}
	printf("Padre %d ha letto %d messaggi dalla pipe\n", getpid(), j);
	pidFiglio = wait(&status);
	if(pidFiglio < 0){
		printf("Errore in wait\n");
		exit(5);
	}
	if ((status & 0xFF) != 0){
		printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
	}else{
		ritorno=(int)((status >> 8) & 0xFF);
		printf("Il figlio con pid=%d ha ritornato %d (se 255 problema!)\n", pidFiglio, ritorno);
		}
	exit(0);
}