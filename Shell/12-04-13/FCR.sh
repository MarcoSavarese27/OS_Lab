#!/bin/sh

#$1 contiene la gerarchia
#$2 contiene il file temporaneo su cui salvare il file
#$3 contiene la teminazione dei file

cd $1					#mi sposto sulla gerarchia passata

trovato=0
for i in *					
do
	if test -f $i -a -r $i		#se quello che sto esplorando è un file allora entro...
	then
		case $i in
		*.$3)trovato=1		#...se il file termina per la terminazione richiesta allora ho trovato almeno un file leggibile e la directory segue la specifica
		esac
	fi
done

if test $trovato -eq 1			#se nella fase precedente ho trovato almeno un file che rispetta la specifica...
then
	echo `pwd` >> $2		#...salvo sul file temporaneo la directory
fi

for i in *				#effettuo la chiamata ricorsiva sulle gerarchie sottostanti
do 
	if test -d $i -a -x $i 		
	then
		FCR.sh $1/$i $2 $3
	fi
done
