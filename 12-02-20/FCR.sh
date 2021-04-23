#!/bin/sh

cd $3									#Mi muovo sulla directory passata

trovatop=0								#La variabile trovatop è un contatore che viene incrementato ogni qual volta che trovo un file con linee pari a K2
trovatod=0								#La variabile trovatod è un contatore che viene incrementato ogni qual volta che trovo un file con linee pari a K1
FILEP=									#La variabile FILEP salverà temporaneamente il nome del file che ha un numero di linee pari a K2
FILED=									#La variabile FILED salverà temporaneamente il nome del file che ha un numero di linee pari a K1

for i in *
do
	if test -f $i -a -r $i						#Controllo che $i sia un file e, anche se non richiesto dal testo, che sia leggibile in modo da non avere problemi con il comando
	then								#wc
		if test $trovatop -gt 1 -o $trovatod -gt 1		#Esco dal ciclo se ho trovato più di un file che rispetta una delle due specifiche
		then break
		fi

		if test `wc -l < $i` -eq $2				#Se il file ha un numero di linee pari al numero intero pari passato allora incremento il suo rispettivo contatore e salvo 
		then							#temporaneamente il suo nome.
			trovatop=`expr $trovatop + 1`
			FILEP="$i"
			continue					#se entro in questo if è inutile controllare anche quello successivo, quindi passo direttamente all'iterazione successiva
		fi

		if test `wc -l < $i` -eq $1				#Se il file ha un numero di linee pari al numero intero dispari passato allora incremento il suo rispettivo contatore e salvo
		then							#temporaneamente il suo nome
			FILED="$i"
			trovatod=`expr $trovatod + 1`
		fi
	fi
done

if test $trovatop -eq 1 -a $trovatod -eq 1				#Entro in questo if se e solo se ho trovato esattamente un file con linee pari a K2 e esattamente un file con linee pari a K1
then
	echo `pwd`/$FILEP >> $4						#Salvo sul file temporaneo il nome assoluto dei due file, secondo la formattazione richiesta dal testo, ovvero prima il file con
	echo `pwd`/$FILED >> $4						#linee pari a K2 poi il file con linee pari a K1
	echo "La directory $3 rispetta la specifica"			#Stampo su stdout la directory che rispetta la specifica
fi

for i in *
do
	if test -d $i -a -x $i 						#Controllo che quella esplorata sia una directory e che sia attraversabile, se sì procedo alla chiamata ricorsiva
	then
		FCR.sh $1 $2 $3/$i $4
	fi
done
