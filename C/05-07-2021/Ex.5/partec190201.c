#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char const *argv[]){
	if(argc < 3){
		puts("Errore nel numero dei parametri");
		exit(1);
	}
	
	int pid;
	int pidFiglio, status, ritorno;
	int count = 0, count0 = 0, count1 = 0;
	int piped[2][2];
	int infile;
	char buf, buf0, buf1;

	pipe(piped[0]);
	pipe(piped[1]);

	for(int i = 0; i < (argc - 1); ++i){
		if((pid = fork()) < 0){
			puts("Errore in fork");
			exit(4);
		}else if(pid == 0){
			close(piped[0][0]);
			close(piped[1][0]);
			close(piped[i % 2][1]);
			if((infile = open(argv[i+1], O_RDONLY)) < 0){
				printf("Errore nell'apertura di %s\n", argv[i]);
				exit(-1);
			}
			while(read(infile, &buf, 1) > 0){
				if((((i % 2) == 0) && isalpha(buf)) || ((((i % 2) == 1) && isdigit(buf)))){
					write(piped[(i+1) % 2][1], &buf, 1);
				}
			}
			exit(0);
		}
	}
		close(piped[0][1]);
		close(piped[1][1]);
		count0 = read(piped[0][0], &buf0, 1);
		count1 = read(piped[0][1], &buf1, 1);
		while((count0 != 0) || (count1 != 0)){
			count = count + count0 + count1;
			write(1, &buf1, count1);
			write(1, &buf0, count0);
			count0 = read(piped[0][0], &buf0, 1);
			count1 = read(piped[1][0], &buf1, 1);
		}
		printf("\nSono il padre e ho letto %d caratteri\n", count);
		for (int i = 1; i < argc; i++){
			pidFiglio = wait(&status);
			if(pidFiglio < 0){
				puts("Errore in wait");
				exit(5);
			}
			if((status & 0xFF) != 0){
				puts("Figlio terminato in modo anomalo");
				exit(6);
			}else{
				ritorno = (status >> 8) & 0xFF;
				printf("Il figlio con pid %d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
			}
		}
	return 0;
}
