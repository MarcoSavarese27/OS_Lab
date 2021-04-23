#!/bin/sh

if test $# -lt 3
then 
	echo "Devi passare 3 o più parametri"; exit 1
fi

case $1 in
	?);;

	*)echo "Il primo parametro deve essere un singolo carattere"; exit 2
esac

C=$1
shift

PATH=`pwd`:$PATH
export PATH

>/tmp/nomiAssoluti

for i in $*
do 
	case $i in
	   /*)if test -d $i -a -x $i
	      then
		   FCR.sh $C $i /tmp/nomiAssoluti 
	      fi;;

	   *)echo "$i non è un nome assoluto"; exit 3;;
	   esac
done

lines=`wc -l < /tmp/nomiAssoluti`
echo "Ho trovato $lines directory che rispettano la specifica"
for i in `cat /tmp/nomiAssoluti`
do 
	echo "Elena, vuoi visualizzare il contenuto di $i?(sì/no)">/dev/tty
	read answer
	case $answer in
		s* | S*)ls -la $i;;

		*);;
	esac
done

rm /tmp/nomiAssoluti

