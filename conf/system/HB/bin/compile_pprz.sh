#!/bin/sh

cd $PAPARAZZI_HOME
. ./ENV

for i in $( grep name conf/conf.xml | sed 's/.*="//; s/"//' )
do
	AIRCRAFT=$i
	bin/compile.sh 2>&1 | egrep -i 'ap.elf  :|error|warning|\*' | uniq | grep -v waypoint
done
