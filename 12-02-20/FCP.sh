#!/bin/sh

if test $# -lt 4														#controllo che i parametri siano almeno 4, contando i due numeri
then																#e almeno due nomi assoluti
	echo "ERRORE: Passare almeno 4 parametri"; exit 1
fi

case $1 in															
	*[!0-9]*)echo "ERRORE: Il primo parametro deve essere un numero intero dispari"; exit 2;;				#controllo che il primo parametro sia un numero intero dispari, 
	*)if test $(($1 % 2)) -eq 0												#come richiesto dal testo
	  then
		 echo "ERRORE: Il primo parametro deve essere un numero intero dispari"; exit 3
	  fi
	  ;;
esac

case $2 in
        *[!0-9]*)echo "ERRORE: Il secondo parametro deve essere un numero intero pari"; exit 4;;				#controllo che il secondo parametro sia un numero intero pari
        *)if test $(($2 % 2)) -ne 0												#come richiesto dal testo 
          then
                 echo "ERRORE: Il secondo parametro deve essere un numero intero pari"; exit 5
          fi
          ;;
esac

K1=$1																#salvo i numeri in due variabili,e li shifto in modo da poter fare
K2=$2																#controlli sui successivi parametri con il for
shift
shift

PATH=`pwd`:$PATH														#esporto la variabile PATH
export PATH

for i in $*															#controllo che tutti i parametri, oltre i due numeri, siano nomi
do 																#assoluti
	case $i in 
		/*);;

		*)echo "ERRORE: $i non è un nome assoluto"; exit 6;;
	esac
done

>/tmp/nomiAssolutiPD														#creo un file temporaneo in cui andrò a salvare i nomi assoluti 
																#dei file da passare allo script C
for i in $*
do
	FCR.sh $K1 $K2 $i /tmp/nomiAssolutiPD											#passo al file ricorsivo
done

echo "---Passo alla parte C con i files `cat /tmp/nomiAssolutiPD`---"

rm /tmp/nomiAssolutiPD														#rimuovo il file temporaneo per evitare conflitti
