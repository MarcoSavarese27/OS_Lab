#!/bin/sh

cd $1
lines=
linesF=
FILE=
for i in *
do
	if test -f $i -a -r $i
	then 
		lines=`wc -l < $i`
		linesF=`grep '^a' $i | wc -l`
		if test $lines -eq $linesF
		then
			FILE="$FILE $i"
			echo `pwd`/$i >> $2
		fi
	fi
done

echo "Nella gerarchia $1 ho trovato i file $FILE"

for i in *
do
	if test -d $i -a -x $i
	then
		FCR.sh $1/$i $2
	fi
done
