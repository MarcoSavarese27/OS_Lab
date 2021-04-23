#!/bin/bash

if test $# -ne 1
then echo numero parametri errati; exit 1
fi

case $1 in 
	*/*)echo passa un nome relativo semplice
	   exit 2;;

	*)if test -f $1
	  then echo il file esiste nella dir corrente
	  else echo il file non esiste nella dir corrente
	  fi 
	  exit 3;;

esac
	
