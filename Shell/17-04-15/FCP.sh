#!/bin/sh

if test $# -lt 3									#controllo sul numero di parametri
then echo "Devi passare 3 o più parametri"; exit 1
fi

if test $1 -lt 1
then echo "Il primo parametro deve essere strettamente positivo"; exit 2		#controllo che il primo parametro sia strettamente positivo
fi


echo "---INIZIO FILE FCP.sh---"

numt=$1											#salvo in una variabile il primo parametro

PATH=`pwd`:$PATH									#settata la variabile PATH
export PATH

>/tmp/temp1

shift 											#shifto i parametri per fare il controllo sulle gerarchie

for i in $*
do case $i in 
       	/*)FCR.sh $numt $i /tmp/temp1;;

	*)echo "$i non è un nome assoluto";;
   esac
done

integerrimo=`wc -l</tmp/temp1`
echo "Ho trovato $integerrimo files che hanno $numt linee che finiscono per t"
for j in `cat /tmp/temp1`
do
	echo "Sei nel file $j, quale linea vuoi vedere?"
	read numr
	while test $numr -lt 1 -o $numr -ge $numt
	do 
		echo "$numr non è compreso tra 1 e $numt, riprova"
		read numr
	done
	linea=`head -$numr $j|tail -1`
	echo "La linea è: $linea"
done 

#rm /tmp/temp1

echo "---FINE FILE FCP.sh---"
