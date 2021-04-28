#!/bin/sh
#file comandi con altro esempio di for
#supponiamo che nel file t siano stati memorizzati i nomi di alcuni file insieme con la loro lunghezza in linee
c=0				 #variabile che ci serve all'interno del for per capire se siamo su un elemento dispari (nomefile) o su un elemento pari (numero di linee)
for i in `cat t`
do
c=`expr $c + 1`
if test `expr $c % 2` -eq 1 	 #se il resto dell’operazione modulo 2 è 1 vuol dire che l’elemento è dispari
then
echo elemento dispari, quindi nome di file $i
if test -f $i
then cat $i
fi
else				 #se il resto dell’operazione modulo 2 è 0 vuol dire che l’elemento è pari
echo elemento pari, quindi lunghezza in linee del file appena visualizzato = $i
fi
done
