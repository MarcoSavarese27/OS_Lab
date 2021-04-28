#!/bin/sh

cd $1							#mi posiziono nella directory passata
f1=$2.1							#inserisco in f1 e f2 i nomi dei file che devo trovare
f2=$2.2
fd1=0							#setto due variabili a 0, in questo modo se ho trovato i file diventeranno true
fd2=0
for i in *
do
	if test $fd1 = true -a $fd2 = true		#eseguo questo controllo in cui esco dal ciclo se trovo i due file prima della fine del ciclo
	then break
	fi

	if test -f $i 					#controllo che l'elemento esplorato si riferisca a un file
	then 
		if test $i = $f1			#se ho trovato il file $2.1 setto la prima variabile a 1
		then fd1=1
		fi

		if test $i = $f2			#se ho trovato il file $2.2 setto la seconda variabile a 1
		then fd2=1
		fi
	fi

done

if test $fd1 -eq 1 -a $fd2 = 1				#rieseguo il controllo, in caso io non abbia effettivamente trovato i file
then
	dim1=`wc -l < $f1`
	dim2=`wc -l < $f2`

	if test $dim1 -eq $dim2				#controllo che il numero di righe sia uguale
	then 
		echo `pwd` >> $3
	fi

fi

for i in *
do
	if test -d $i -a -x $i				#se la directory esplorata esiste ed è attraversabile allora si esegue la ricorsione
	then FCR.sh $1/$i $2 $3
	fi
done
