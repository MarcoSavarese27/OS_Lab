#!/bin/bash

case $# in

	1)if test -f $1	
	  then echo "Inserisci il contenuto che vuoi inserire nel file $1" > /dev/tty
	  cat >> $1
          else echo "$1 non è un file"
	  fi
	  exit 1;;

	2)if test -f $1 -a -f $2
	  then cat $1 >> $2
          else echo "$1 o $2 non è un file"
          fi
	  exit 2;;
	
	*)echo Numero di parametri errati, passa o uno o due parametri
	  exit 3;;
esac

