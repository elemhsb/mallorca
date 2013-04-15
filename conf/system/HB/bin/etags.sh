#!/bin/sh

cd $PAPARAZZI_HOME
etags `find $PAPARAZZI_HOME -name \*.[ch]`
