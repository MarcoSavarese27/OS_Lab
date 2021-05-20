#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
	if(argc < 3){
		puts("Errore sul numero di parametri, devono essere almeno 2");
		exit(1);
	}

	int count;									/*counter per le occorrenze*/

	int pid;									/*necessario per la fork*/
	int pidFiglio, status, ritorno;				/*necessari per ottenere il risultato dal processo figlio*/

	int p[argc-2][2];							/*array di pipe*/

	char buf, ch;
	int fd;
	for(int i = 0; i < (argc - 2); ++i){
		if(pipe(p[i]) < 0){
			puts("Errore in creazione della pipe");
			exit(2);
		}
	}
	
	printf("Sono il processo padre con PID %d e sto per creare %d figli\n", getpid(), (argc-2));
	for(int i = 0; i < (argc - 2); ++i){
		pid = fork();
		if(pid < 0){
			puts("Errore in fork");
			exit(3);
		}else if(pid == 0){							/*figlio*/
		 	fd = open(argv[1], O_RDONLY);
			close(p[i][0]);
			count = 0;
			while(read(fd, &buf, 1)){
				ch = argv[i + 2][0];
				if(buf == ch){
					++count;
				}
			}
			write(p[i][1], &count, sizeof(int));
			exit(0);
		}	
		close(p[i][1]);
		read(p[i][0], &count, sizeof(int));
		printf("Il carattere \"%c\" compare %d volte in %s\n", argv[i + 2][0], count, argv[1]);
		pidFiglio = wait(&status);
		if(pidFiglio < 0){
			puts("Errore in wait");
			exit(4);
		}
		if((status & 0xFF) != 0){
			printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
			exit(5);
		}else{
			ritorno = (status >> 8) & 0xFF;
			printf("Il figlio con pid %d è terminato con %d (se 255 probelmi!)\n", pidFiglio, ritorno);
		}
	}
	exit(0);
}
