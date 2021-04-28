#!/bin/sh

first=

if test $# -lt 3
then "Three or more parameters needed"; exit 1
fi


case $1 in
	*[!0-9]*) echo "First parameter must be an integer"; exit 2;;
	*)if test $1 -lt 1
	  then
	  	echo "First parameter must be greater than 0"; exit 3
	  fi;;
esac

first=$1
shift


PATH=`pwd`:$PATH
export PATH

>/tmp/temp1

for i in $*
do 
	case $i in
		/*)if test -d $i -a -x $i
		   then 
			   FCR.sh $i $first /tmp/temp1
		   fi;;
		 *)echo "$i is not an absolute name"; exit 4;;
	 esac
done

echo "I found `wc -l</tmp/temp1` files"

for i in `cat /tmp/temp1`
do 
	echo "This is $i"
	case $i in 
		*.NOquinta) echo "This file does not have a fifth line";;
		*.quinta)cat $i;;
	esac
done

rm /tmp/temp1
