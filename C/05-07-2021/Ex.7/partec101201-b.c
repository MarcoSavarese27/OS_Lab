#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
/*Scrivere un programma C partec191201-b.c che accetta un numero variabile di parametri (almeno 2) che
rappresentano un nome di file F e singoli caratteri C1 ...CN. Il processo padre deve creare un numero di
figli pari al numero di caratteri passati come parametri (N). Ogni processo figlio esegue in modo
concorrente ed esamina il file F contando le occorrenze del carattere assegnato Ci: terminato il file, ogni
figlio comunica al padre quante occorrenze di Ci sono presenti e termina. Il padre deve riportare sullo
standard output il numero totale delle occorrenze specificando a quale carattere Ci si riferisce il conteggio.
Al termine, il padre deve stampare su standard output il PID di ogni figlio e il valore ritornato.
NOTA BENE: si usi una sola pipe su cui ogni figlio scrive una struct con due campi (carattere e numero
occorrenze); questa soluzione può essere accettabile visto che il testo non richiede che le informazioni
inviate dal figlio vengano recuperate dal padre in un ordine specifico.
OSSERVAZIONE: nei testi recenti viene specificato se va usata una struct o altra struttura dati!*/

int main(int argc, char const *argv[]){
	typedef struct{
		char ch;
		int num;
	}occorrenze_ch;

	if(argc < 3){
		puts("Errore sul numero di parametri, devono essere almeno 2");
		exit(1);
	}
	
	int pid;
	int pidFiglio, status, ritorno;
	int p[2];
	int fd;
	char ch;
	occorrenze_ch *carattere = malloc(sizeof(occorrenze_ch));

	printf("Sono il processo padre con PID %d e creerò %d figli\n", getpid(), (argc-2));
	for(int i = 0; i < argc-2; ++i){
		if(pipe(p) < 0){
			puts("Errore in crezione della pipe");
			exit(2);
		}
	pid = fork();
		if(pid < 0){
			puts("Errore in fork");
			exit(3);
		}
		if(pid == 0){
			close(p[0]);
			carattere->num = 0;
			carattere->ch = argv[i + 2][0];
			fd = open(argv[1], O_RDONLY);
			if(fd < 0){
				printf("Errore in apertura del file %s\n", argv[1]);
				exit(-1);
			}
			while(read(fd, &ch, 1)){
				if(ch == carattere->ch){
					++(carattere->num);
				}
			}
			write(p[1], &carattere->num, sizeof(int));
			write(p[1], &carattere->ch, 1);
			exit(0);
		}
		close(p[1]);
		read(p[0], &carattere->num, sizeof(int));
		read(p[0], &carattere->ch, 1);
		printf("Il carattere %c compare %d volte\n", carattere->ch, carattere->num);

		pidFiglio = wait(&status);
		if(pidFiglio < 0){
			puts("Errore in wait");
			exit(4);
		}
		if((status % 2) != 0){
			printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
			exit(5);
		}else{
			ritorno = (status >> 8) & 0xFF;
			printf("Il figlio con PID %d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
		}
	}
	exit(0);
}
