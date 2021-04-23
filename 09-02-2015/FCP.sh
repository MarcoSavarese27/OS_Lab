#!/bin/sh

if test $# -ne 2							#controllo di avere esattamente due parametri 
then echo PASSA ESATTAMENTE DUE PARAMETRI; exit 1
fi

case $1 in 								#controllo che il primo parametro sia un nome assoluto
	/*);;

	*)echo DEVI PASSARE UN NOME ASSOLUTO; exit 2;;
esac

if test $2 -lt 1							#dopodiché controllo che il secondo sia strettamente positivo
then echo $2 DEVE ESSERE STRETTAMENTE POSTIVO; exit 3
fi

echo "---INIZIO FCP.sh---"
PATH=`pwd`:$PATH							#inserimento variabile PATH
export PATH

>/tmp/temp1$$

FCR.sh $1 $2 /tmp/temp1$$						#chiamata ricorsiva

for i in `cat /tmp/temp1$$`
	do echo "Inserisci un numero compreso tra 1 e $2" >/dev/tty
	read var 
		while test $var -lt 1 -o $var -gt $2
		do
		       	echo "SBAGLIATO! $var non è compreso tra 1 e $2. Riprova"
			read var
		done
	echo "passo alla parte C con i parametri $i e $var"
done
echo "---FINE FCP.sh---"
