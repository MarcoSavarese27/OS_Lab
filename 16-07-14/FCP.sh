#!/bin/sh

if test $# -ne 2												#controllo sul numero dei parametri, se non sono esattamente due, esco dallo script
then
	echo "Numero errato di parametri, due parametri richiesti"; exit 1
fi

case $1 in 													#controllo sul primo parametro, deve essere un nome assoluto 
	/*);;

	*)echo "Il primo parametro deve essere un nome assoluto"; exit 2;;
esac

PATH=`pwd`:$PATH												#esporto la variabile PATH
export PATH

case $2 in 													#controllo sul secondo parametro
	*[!0-9]*) echo "Errore il secondo parametro deve essere un numero intero"; exit 3;;			#innanzitutto se è un numero intero

	*)if test $2 -lt 1
	then 
		echo "Errore il secondo parametro deve essere strettamente positivo"; exit 4			#e poi se è strettamente positivo
	fi
	FCR.sh $1 $2												#inizio con la chiamata ricorsiva
	;;
esac

