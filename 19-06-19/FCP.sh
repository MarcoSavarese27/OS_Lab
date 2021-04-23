#!/bin/sh

if test $# -lt 3												#controllo preliminare sui parametri (>= 3)
then echo "ERROR(01): You must pass 3 or more parameters"; exit 1
fi

if test $1 -lt 1 -o $1 -gt 255											#svolgo inoltre un controllo sul fatto che sia compreso tra 1 e 255
then 
	echo "ERROR(02): First parameter must be greater than 1 and lower than 255"; exit 2
fi

first=$1													#salvo il primo parametro in una variabile e eseguo uno shift per controllare con un for
shift														#che i successivi parametri siano nomi assoluti


PATH=`pwd`:$PATH												#esporto la variabile PATH
export PATH

for i in $*
do
	case $i in
	/*)if test ! -d $i -o ! -x $i										#controllo che le directory siano passate con nome assoluto e che siano attraversabili
	   then 
		echo "ERROR(03): $i does not exist or is not executable"; exit 3				#se non lo sono esco, se lo sono entro nel file ricorsivo
	   else FCR.sh $i $first 
	   fi
	;;

        *)echo "ERROR(04): $i is not an absolute name"; exit 4;;
	esac
done


		
