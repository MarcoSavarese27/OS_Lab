#!/bin/bash
if test $# -ne 1 
then echo numero parametri errato; exit 1
fi

case $1 in
/*)  echo hai passato un nome assoluto
     exit 2;;
*/*) echo hai passato un nome relativo
     exit 3;;
*)   echo hai passato un nome relativo semplice
     exit 4;;
esac	      
