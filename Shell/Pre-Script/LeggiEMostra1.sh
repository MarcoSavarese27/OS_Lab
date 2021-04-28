#!/bin/bash
#file comandi leggi e mostra

if test $# -lt 1
then echo ERRORE: Inserire uno o più parametri
     exit 1
fi

for i in $* 
do if test !-f $i -o !-r $i
   then echo ERRORE: $i non è un file oppure non è leggibile
   exit 2
   fi
   echo "Vuoi visualizzare il file $i (si/no)?" > /dev/tty
   read var1
   if test $var1 = si
   then ls -la $i; cat $i
   else echo niente stampa di $i
   fi
done
