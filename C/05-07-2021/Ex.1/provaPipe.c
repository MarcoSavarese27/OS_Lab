#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main(int argc, char const *argv[]){
	int fd1, fd2;
	if (argc != 2){
		puts("Errore nel numero dei parametri");
		exit(1);
	}
	if ((fd1 = open(argv[1], O_RDONLY)) < 0){
		puts("Errore in apertura del file");
		exit(2);
	}else{
		printf("Valore di fd1 = %d\n", fd1);
	}

	if((fd2 = open(argv[1], O_RDONLY)) < 0){
		puts("Errore in apertura del file");
		exit(2);
	}else{
		printf("Valore di fd2 = %d\n", fd2);
	}
	close(fd1);
	int piped[2];
	if(pipe(piped) < 0){
		puts("Errore in pipe");
		exit(3);
	}
	for (int i = 0; i < 2; i++){
		printf("%d\n", piped[i]);
	}

	return 0;
}
