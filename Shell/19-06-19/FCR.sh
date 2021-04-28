#!/bin/sh

cd $1													#mi sposto nella directory passata
lines=													#conterrà il numero di linee di un file
count=0													#conterrà il contatore che mi confermerà se trovo due o più files che rispettino la specifica
files=
for i in *
do
	if test -f $i											#controllo che quello che sto esplorando sia un file
	then
		lines=`wc -l<$i`
		if test $lines -lt $2
		then 
			count=`expr $count + 1`
			files="$files $i"								#se il controllo è rispettato aggiungo il file agli altri che lo rispettano
		fi
	fi
done

if test $count -ge 2											#se non ho almeno due files in questa gerarchia passo direttamente alla chiamata ricorsiva
	then 											
	echo "I found $count files in $1, do you want to call the C script?(y/n)">/dev/tty		#chiedo all'utente se vuole passare alla parte C
	read ans
	case $ans in 
		y* | Y* | s* | S*) echo "---Calling the C script with $files---";;

		*) echo "---C script not called---";;
	esac
fi

for i in * 
do 
	if test -d $i -a -x $i
	then
		FCR.sh $1/$i $2
	fi
done

