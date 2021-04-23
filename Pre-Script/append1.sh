#!/bin/bash

if test $# -ne 2
then echo Numero parametri errato, sono richiesti due parametri;exit 1
fi

case $1 in 
	*/*) echo "$1 non è un nome relativo semplice"; exit 2;;

	*) if test -f $1 -a -r $1
	   then case $2 in 
	        */*) echo "$2 non è un nome relativo semplice"; exit 3;;
                *) if test -f $2
		   then if test -w $2
		        then cat $1 >> $2
			else if test -w `pwd`
			     then echo "La directory corrente è scrivibile"; exit 4
		  	     else echo "La directory corrente non è scrivibile"; exit 5
		             fi
		        fi
	            else "$2 non esiste"; exit 6
		    fi
	    	    exit 7;;	    
                esac		
           else echo "$1 non esiste o non è leggibile"; exit 8
	   fi
	   exit 9;;
esac
