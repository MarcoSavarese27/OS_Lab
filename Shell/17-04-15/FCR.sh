#!/bin/sh
cd $2

for i in *
do 
	if test -f $i -a -r $i
	then 
		numt=`grep 't$' $i|wc -l`
		if test $numt -ge $1
		then echo `pwd`/$i>>$3
		fi
	fi
done

for i in * 
do 
	if test -d $i -a -x $i
	then FCR.sh $1 $2/$i $3
	fi
done	
