#!/bin/sh
#
# $Id:$ olri
#
[ $# == 1 ] || { echo "Usage: $0 <AirframeName>"; exit 5; }

cd $PAPARAZZI_HOME

make AIRCRAFT="$1" clean_ac
