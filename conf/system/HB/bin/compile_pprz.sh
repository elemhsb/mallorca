#!/bin/sh

LANG=C

for i in $( grep name conf/conf.xml | sed 's/.*="//; s/"//' )
do
	echo "----------------------------------------------------------------------------"
	AIRCRAFT=$i
	echo $AIRCRAFT ...
	bin/compile.sh 2>&1 | egrep -i 'ap.elf  :|error|warning|\*'
	echo "----------------------------------------------------------------------------"; echo
done
