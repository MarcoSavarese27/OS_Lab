#!/bin/bash

if test $# -lt 1
then echo passa almeno un parametro; exit 1
fi
c=1
for i in $*
do echo '$'$c"==>" $i
	c=$(($c+1))
done

