#!/bin/sh

cd $PAPARAZZI_HOME
. ./ENV
make AIRCRAFT=$AIRCRAFT clean_ac ap ap.upload
