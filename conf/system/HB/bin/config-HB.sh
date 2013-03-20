#!/bin/sh

[ "$PAPARAZZI_HOME" = "" ] && echo "Set PAPARAZZI_HOME first" && exit 10

cd $PAPARAZZI_HOME

[ -h ENV ] || ln -s conf/system/HB/ENV
[ -h bin ] || ln -s conf/system/HB/bin

. ./ENV

cp $PAPARAZZI_HOME/conf/HB/conf.xml $PAPARAZZI_HOME/conf/
cp $PAPARAZZI_HOME/conf/HB/control_panel.xml $PAPARAZZI_HOME/conf/
