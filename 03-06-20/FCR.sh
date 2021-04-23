#!/bin/sh

cd $2

for i in *
do
	if test -d $i -a -x $i
	then 
		case $i in
			$1?$1) echo `pwd`/$i >> $3;;
			*);;
		esac
	fi
done

for i in *
do 
	if test -d $i -a -x $i
	then 
		FCR.sh $1 $2/$i $3
	fi
done
