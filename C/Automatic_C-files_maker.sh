#!/bin/bash

echo "Tutte le gerarchie verranno create nella cartella corrente"
echo "Fai dunque in modo di far partire questo script nella cartella delle esercitazioni"

echo "Inserisci il la data dell'esercitazione nel formato mm-gg-aaaa"
read dat

for i in *
do
	if test $i = $dat 2>/dev/null
	then
		echo Errore, cartella già esistente;exit 1
	fi
done

mkdir $dat
cd $dat

echo "Quanti esercizi ha l'esercitazione?"
read ex
case $ex in
	*[!0-9])echo "$ex non è un numero"; exit 2;;
esac

i=1
while test $i -le $ex
do
	mkdir Ex.$i
	cd Ex.$i
	touch makefile
	echo "Come si chiama il file .c che devi creare nella cartella Ex.$i?"; echo "Scrivi il nome del file senza .c!"
	read filec
	echo "CC=gcc">>makefile
        echo "CFLAGS=-Wall -std=c11">>makefile
        echo "BIN=$filec">>makefile
        echo "all: \$(BIN)">>makefile
        echo "">>makefile
        echo "%:	%.c">>makefile
        echo "	\$(CC) \$(CFLAGS) -o \$@ \$<">>makefile
	echo "">>makefile
	touch $filec.c
	echo "Vuoi autocompliare $filec.c?"
	read answ
	case $answ in
        	s* | S* | y* | Y*)echo "#include <stdlib.h>">>$filec.c
		       		  echo "#include <unistd.h>">>$filec.c
			  	  echo "#include <fcntl.h>">>$filec.c
				  echo "#include <stdio.h>">>$filec.c
				  echo "#include <sys/wait.h>">>$filec.c
				  echo "">>$filec.c
				  echo "int main(int argc, char const *argv[]){">>$filec.c
				  echo "	/*code*/">>$filec.c
				  echo "	return 0;">>$filec.c
				  echo "}">>$filec.c
                            	  ;;
                        	*)echo "Hai deciso di non autocompilare";;
	esac

	cd ..
	i=`expr $i + 1`
done

echo "Cartelle create con successo";
echo "Vuoi cominciare con il primo esercizio? (S/N)"
read answ
case $answ in
	s* | S* | y* | Y*) cd Ex.1
			   `code .`
			    ;;
		        *)echo "Hai deciso di non cominciare l'esercizio uno";;
esac


