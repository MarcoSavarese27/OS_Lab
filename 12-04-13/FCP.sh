#!/bin/sh

if test $# -ne 3 
then
	echo "3 parametri richiesti"; exit 1									#controllo di avere esattamente 3 parametri
fi

case $1 in													#controllo che il primo parametro sia un nome assoluto
	/*);;

	*)echo "Il primo parametro deve essere un nome assoluto"; exit 2;;
esac

case $2 in
	*/*)echo "Il secondo parametro deve essere una stringa"; exit 3;;					#controllo che il secondo parametro sia una stringa
	
	*);;
esac

PATH=`pwd`:$PATH												#setto ed esporto la variabile PATH
export PATH

>/tmp/nomiAssolutiS												#creo un file temporaneo su cui salvare le directory che rispettano la specifica

case $3 in
	*[!0-9]*)echo "Il terzo parametro deve essere un numero strettamente positivo"; exit 4;;		#controllo che il terzo parametro sia un numero, se è così allora inizio con il file 
														#ricorsivo
	*)if test $3 -lt 1
	  then
		  echo "Il terzo parametro deve essere un numero strettamente positivo"; exit 5
	  fi
	  FCR.sh $1 /tmp/nomiAssolutiS $2
	  ;;
esac

dimtmp=`wc -l < /tmp/nomiAssolutiS`										#salvo in una variabile la dimensione del file temporaneo, ovvero il numero di directory
echo "Ho trovato $dimtmp directory che rispettano la specifica"							#che rispettano la specifica
cat /tmp/nomiAssolutiS

if test $dimtmp -le $3 												#se queste directory sono minori del terzo parametro, la fase B non verrà chiamata
then
	echo "Fase B non eseguita"										#per la fase B non chiamo il file ricorsivo ma uso il file temporaneo
else
	echo "Scegli un numero da 1 a $3">/dev/tty								#chiedo all'utente (ridireziono la richiesta sulla finestra di terminale locale) di 
	read answer												#scegliere un numero compreso tra 1 e il terzo parametro passato
	while test $answer -lt 1 -o $answer -gt $3
	do
		echo "Errore, scegli un numero da 1 a $3"							#nonostante non sia richiesto, uso questo while in modo che se il numero scelto non è 
		read answer											#compreso tra 1 e $3 richiedo nuovamente il numero
	done
	directory=`head -$answer /tmp/nomiAssolutiS | tail -1`							#salvo in questa variabile la directory scelta
	for i in `ls -l $directory`										#per tutti i file contenuti nella directory (ls -l)...
	do
	   	case $i in
	   	*.$2)echo $directory/$i; head -1 $directory/$i;;						#stampa i file che terminano per .$2 e stampane la prima riga
	   	esac
	done
fi

rm /tmp/nomiAssolutiS
