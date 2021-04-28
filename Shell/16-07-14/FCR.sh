#!/bin/sh

cd $1
FILES=

for i in *
do
	if test -f $i -a -r $i
	then
		lines=`wc -l < $i`
		if test $lines -eq $2
		then
			min=`grep '^[a-z]' $i | wc -l`
			if test $min -eq $2
			then
				FILES="$FILES $i"
			fi
		fi
	fi
done

echo "Nella directory $1 ho trovato questi file$FILES"
echo "Vuoi passare allo script C con i file trovati? (S/N)"
read answer
case $answer in
	s* | S* | y* | Y*) echo "---Passo allo script C con i parametri$FILES---";;

	*)echo "---Script C non invocato---";;
esac

for i in *
do
	if test -d $i -a -x $i 
	then
		FCR.sh $1/$i $2
	fi
done	
