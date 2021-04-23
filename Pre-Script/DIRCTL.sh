#!/bin/bash
echo SONO DIR.sh
case $# in
	0) echo non hai passato parametri
	   exit 0;;

	1) echo '$0 ===>' $0
	   echo '$1 ===>' $1
           echo `ls -l $1`
	   exit 1;;

	*) echo hai passato troppi parametri
	   exit 2;;
esac

	
