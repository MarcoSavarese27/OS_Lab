#!/bin/sh

cd $1
file=$2.txt
dim=
if test -f $file -a -r $file -a -w $file
then 
	echo `pwd`/$file >> $3
fi

for i in *
do 
	if test -d $i -a -x $i
	then FCR.sh $1/$i $2 $3
	fi
done
