#!/bin/bash
#file comandi leggi e mostra

if test -z $1 
then echo ERRORE:voglio un parametro
     exit 1
fi

if test !-f $1 -o !-r $1
then echo ERRORE: $1 non è un file oppure non è leggibile
     exit 2
fi
echo "Vuoi visualizzare il file $1 (si/no)?" > /dev/tty
read var1
if test $var1 = si
then ls -la $1; cat $1
else echo niente stampa di $1
fi

