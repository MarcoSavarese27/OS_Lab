#!/bin/sh
cd $1 
dim= 					#conterrà il numero di linee

echo "---INIZIO FCR.sh---"
for j in *
do 
	if test -f $j
	then dim=`wc -l < $j`
		if test $dim -eq $2
		then 
			echo `pwd`/$j
			echo `pwd`/$j>>$3	
		fi
	fi
done

for i in *
do
	
	if test -d $i -a -x $i
	then FCR.sh $1/$i $2 $3
	fi
done
echo "---FINE FCR.sh---"
