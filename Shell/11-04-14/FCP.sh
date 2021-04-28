#!/bin/sh

if test $# -lt 2
then 
	echo "Due o più parametri richiesti"; exit 1
fi
PATH=`pwd`:$PATH
export PATH
>/tmp/nomiAssoluti1

for i in $*
do 
	case $i in

		/*)if test -d $i -a -x $i
	           then 
			   FCR.sh $i /tmp/nomiAssoluti1
		   fi
		   ;;

		*)echo "$i non è un nome assoluto"; exit 2;;
	esac
done

for i in `cat /tmp/nomiAssoluti1`
do 
	echo "Quante linee del file $i vuoi visualizzare?">/dev/tty
	read answer
	while test $answer -gt `wc -l < $i`
	do 
		echo "Il file $i contiene `wc -l < $i` linee, riprova"
		read answer
	done
	echo "La prime $answer linee del file sono"
done

rm /tmp/nomiAssoluti1
	
