#!/bin/sh

if test $# -ne 2										#controllo di avere esattamente due parametri
then echo "ERROR(01): You must pass two parameters"; exit 1
fi

case $1 in 											#controllo che $1 sia un nome assoluto e che sia una directory esistente e attraversabile
	/*)if test ! -d $1 -o ! -x $1
	then echo "ERROR(02): Directory does not exist or is not executable"; exit 2
	fi
      	;;	
	*)echo "ERROR(03): First parameter must be an absolute name"; exit 3;;
esac

												#controllo che $2 sia una stringa
case $2 in 
	*/*)echo "ERROR(04): Second parameter must be a string"; exit 4;;
	
	*);;
esac

PATH=`pwd`:$PATH										#settiamo la variabile PATH
export PATH

>/tmp/filetmp1$$

FCR.sh $1 $2 /tmp/filetmp1$$

echo "I found `wc -l < /tmp/filetmp1$$` directories"

for i in `cat /tmp/filetmp1$$`
do 
	echo "The directory $i contains $2.1 and $2.2, do you want to call the C script?">/dev/tty
	read ans
	case $ans in
		y* | Y* | S* | s*)echo "---Calling C sript with $2.1 and $2.2---";;

		*)echo "---C script not called---";;
	esac
done

rm /tmp/filetmp1$$

