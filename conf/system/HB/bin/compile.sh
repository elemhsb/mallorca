#!/bin/sh

cd $PAPARAZZI_HOME
. ./ENV

echo "*** $AIRCRAFT ********************************************************************************" | cut -c -79
make AIRCRAFT=$AIRCRAFT clean_ac ap
echo "*** $AIRCRAFT ********************************************************************************" | cut -c -79; echo
