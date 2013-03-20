#!/bin/sh

PATH=/opt/local/bin:$PATH:.

#
# start OPENOCD
#
$( dirname $0 )/openocd.sh
$( dirname $0 )/arm-none-eabi-gdb.sh "$@"
