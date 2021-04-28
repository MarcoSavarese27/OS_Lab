#!/bin/sh
echo "---INIZIA FCP.sh---"
if test $# -lt 3
then echo 'ERROR(01):3 or more parameters required'; exit 1
fi

c=1
for i in $*
do 
	if test $c -eq $#
	then last=$i
	fi
	c=`expr $c + 1`
done

#echo $last
expr $last + 0 >/dev/null 2>&1
ris=$?

if test $ris -eq 0 -o $ris -eq 1
then echo "ERROR(02): $last is not a string value"; exit 2
else case $last in
	*/*)echo "ERROR(03): $last must not be a directory"; exit 3;;

	*);;
	esac
fi

c=1
>/tmp/tempolino
PATH=`pwd`:$PATH
export PATH
for i in $*
do 
	if test $c -ne $#
	then 
		case $i in
		/*) FCR.sh $i $last /tmp/tempolino;;
		*) echo "ERROR(04): $i must be a directory"; exit 4;;
		esac
	fi
	c=`expr $c + 1`
done

dim=`wc -l</tmp/tempolino`
echo "I found $dim files"

for i in `cat /tmp/tempolino`
do 
	echo "$i `wc -c<$i`"
	echo "Do you want to sort this file?(yes/no)">/dev/tty
	read answ
	case $answ in 
		y* | Y*) sort -f $i;;
	        *)echo $i not sorted;;
	esac
done

rm /tmp/tempolino
echo "---FINISCE FCP.sh---"
