#!/bin/bash
echo SONO DIR.sh
case $# in
	0) ls -lR| more
	   exit 0;;

	1)if test -d $1 > /dev/null
	  then echo mi hai passato una directory
	  else echo mi hai passato un file
	  fi

	   echo '$0 ===>' $0
	   echo '$1 ===>' $1
           echo `ls -l $1`
	   exit 1;;

	*) echo hai passato troppi parametri
	   exit 2;;
esac

	
