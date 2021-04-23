#!/bin/bash

if test $# -lt 1
then echo passa almeno un parametro; exit 1
fi

for i in $*
do echo $i
done

