#!/bin/sh

cd $PAPARAZZI_HOME
. ./ENV

echo "*** $AIRCRAFT -------------------------------------------------------------------------------"
make AIRCRAFT=$AIRCRAFT clean_ac ap
echo "*** $AIRCRAFT -------------------------------------------------------------------------------"; echo
