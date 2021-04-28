#!/bin/sh

cd $1 
fq=
fn=
for i in *
do
	if test -f $i -a -r $i 
	then 
		lines=`wc -l<$i`
		if test $lines -ge $2
		then
			if test $lines -lt 5
			then 
				fn=$i.NOquinta
				touch $fn
				echo `pwd`/$fn >> $3
			else
				Linea=`head -5 $i | tail -1`
				fq=$i.quinta
				echo $Linea >> $fq
				echo `pwd`/$fq >> $3
			fi
		else 
			touch $i.NOquinta
			fn=$i.NOquinta
                        echo `pwd`/$fn>>$3
		fi
	fi
done

for i in *
do
	if test -d $i -a -x $i
	then 
		FCR.sh $1/$i $2 $3
	fi
done
		
